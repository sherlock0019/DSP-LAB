#include "stdio.h"
#include "math.h"
#include "usbstk5515.h"

float x[8]={1,1,2,2,3,3,4,4};
float y_real[8],y_imag[8];

// int bitrev_of(int dec)
// Takes in a value between 0 and 7 and returns its bit-reversed form.
// For ex. bitrev_of(3)=6.
int bitrev_of(int dec)
{
    int units_place_bin,tens_place_bin,hund_place_bin;
    units_place_bin=dec%2;
    tens_place_bin=(dec/2)%2;
    hund_place_bin=(dec/4)%2;
    return 4*units_place_bin + 2*tens_place_bin+hund_place_bin;
}

// void complex_multiply(float* ip1_real, float* ip1_imag, float* ip2_real, float* ip2_imag, float* res_real, float* res_imag)
// Computes the product of 2 complex numbers.
// ip1_real and ip1_imag are POINTERS to the real and imaginary parts of 1st operand
// ip2_real and ip2_imag are POINTERS to the real and imaginary parts of 2nd operand
// res_real and res_imag are POINTERS to the real and imaginary parts of the product of the 2 complex numbers.
void complex_multiply(float* ip1_real, float* ip1_imag, float* ip2_real, float* ip2_imag, float* res_real, float* res_imag)
{
	float t1,t2;

	/*
	taking two complex numbers - a+ib, c+id

	real part of product = ac - bd
	imaginary part of product = ad + bc
	*/

	//assigning real part to temporary 1
	t1 = (*ip1_real) * (*ip2_real) - (*ip1_imag) * (*ip2_imag);

	//assigning imaginary part to temporary 2
	t2 = (*ip1_real) * (*ip2_imag) + (*ip1_imag) * (*ip2_real);

	//set variables
	*res_real = t1;
	*res_imag = t2;
}

// void butterfly(float*x0_real, float*x0_imag, float*x1_real, float*x1_imag, float*y0_real, float*y0_imag, float*y1_real, float*y1_imag)
// x0_real and x0_imag are the POINTERS to the real and imaginary parts of 1st operand
// x1_real and x1_imag are the POINTERS to the real and imaginary parts of 2nd operand
// y0_real and y0_imag are the POINTERS to the real and imaginary parts of 1st output
// y1_real and y1_imag are the POINTERS to the real and imaginary parts of 2nd output
void butterfly(float*x0_real, float*x0_imag, float*x1_real, float*x1_imag, float*y0_real, float*y0_imag, float*y1_real, float*y1_imag)
{
	*y0_real = *x0_real + *x1_real;
	*y0_imag = *x0_imag + *x1_imag;
	*y1_real = *x0_real - *x1_real;
	*y1_imag = *x0_imag - *x1_imag;
}

void sw_fft(float* x, float* y_real, float* y_imag)
{
    int i=0,j=0;
    float dummy_imag=0;
    float twiddle_real[8]={1,0.7071,0,-0.7071,-1,-0.7071,0,0.7071};// twiddle_real[k]=cos((2pi/8)*k) ; 0<=k<=7
    float twiddle_imag[8]={0,-0.7071,-1,-0.7071,0,0.7071,1,0.7071};// twiddle_imag[k]=-sin((2pi/8)*k); 0<=k<=7
	float x_bitrev_real[8],x_bitrev_imag[8],stage_1_real[8],stage_1_imag[8],stage_2_real[8],stage_2_imag[8];

    // Calculate the bit-reversed form of x in x_bitrev.
	for(i=0;i<8;i++)
	{
	    x_bitrev_real[i]=x[bitrev_of(i)];
	    x_bitrev_imag[i]=0;
	}

/*
    You can pass the POINTER of a variable to a function by preceding its name with an "&".
    For ex. void foo(float* input, float* output) can be called as foo(&myinput,&myoutput) if myinput and myoutput are float variables.
    Function "foo" will process the value whose address is stored in "input", store the output in a variable and return its address in "myoutput".
*/

    // Calculate the stage 1 values with the help of butterfly() function.
    // You can omit the "multiplication by twiddle factor" stage here as all of them are 1.
	for(i=0;i<4;i++)
	{
	    butterfly(&x_bitrev_real[2*i],&x_bitrev_imag[2*i],&x_bitrev_real[2*i+1],&x_bitrev_imag[2*i+1],&stage_1_real[2*i],&stage_1_imag[2*i],&stage_1_real[2*i+1],&stage_1_imag[2*i+1]);
	}

    // Calculate the stage 2 values from stage 1 values with the help of complex_multiply() and butterfly() functions.
	for(i=0;i<2;i++)
	{
		for(j=0;j<2;j++)
		{
			// Multiply selected values in stage 1 by the twiddle factors before calculating the butterfly.
			complex_multiply(&stage_1_real[4*i+j+2],&stage_1_imag[4*i+j+2],&twiddle_real[2*i],&twiddle_imag[2*i],&stage_1_real[4*i+j+2],&stage_1_imag[4*i+j+2]);
			// Butterfly calculation
			butterfly(&stage_1_real[4*i+j],&stage_1_imag[4*i+j],&stage_1_real[4*i+j+2],&stage_1_imag[4*i+j+2],&stage_2_real[4*i+j],&stage_2_imag[4*i+j],&stage_2_real[4*i+j+2],&stage_2_imag[4*i+j+2]);
		}
	}

	// Calculate the output values from stage 2 values with the help of complex_multiply() and butterfly() functions.
	for(i=0;i<4;i++)
	{
		// Multiply selected values in stage 2 by the twiddle factors appropriately before calculating the butterfly.
		complex_multiply(&stage_2_real[i+4],&stage_2_imag[i+4],&twiddle_real[i],&twiddle_imag[i],&stage_2_real[i+4],&stage_2_imag[i+4]);
		
		// Butterfly calculation (Note that y_real and y_imag themselves are POINTERS)
		butterfly(&stage_2_real[i],&stage_2_imag[i],&stage_2_real[i+4],&stage_2_imag[i+4],&y_real[i],&y_imag[i],&y_real[i+4],&y_imag[i+4]);
	}
}
/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  main( )                                                                 *
 *                                                                          *
 * ------------------------------------------------------------------------ */
int main( void )
{
	USBSTK5515_init( );

    sw_fft(x,y_real,y_imag);

    return 0;
}
