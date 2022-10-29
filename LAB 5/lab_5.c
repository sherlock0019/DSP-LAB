/*
 * main.c
 */

#include <stdio.h>
#include "usbstk5515.h"

#define IR_length //order of the filter
#define In_length //length of input signal
#define tmp_l IR_length+In_length-1

Int16 x[tmp_l];
Int16 array[tmp_l];
void linearbuff();
Int16 *inPtr;
Int16 *outPtr;
Int16 *coeff;
Int16 coefs[IR_length];
Int16 input;
Int16 output;
static Int16 buffer[IR_length];

static void dataInput();             // dummy function to be used with ProbePoint
static void dataCoefs();


void linearbuff(void) 		// Commented by ketan
{
	int i;
	long int accumulator=0;

   	         /*
                  write convolution code here;
               */

   	(*outPtr)=(Int16)accumulator;
}


main(void)
{
int j=0,k=0;

for (k=0;k<IR_length;k++)
{
	buffer[k]=0;
}

for (k=0;k<tmp_l;k++)
{
	x[k]=0;
}

dataInput();
dataCoefs();

coeff = &coefs[0]; 	//coefs is coefficient of impulse response defined in fdacoefs_int.h
inPtr = &input;		//inPtr is a globally declared pointer to a Int16
outPtr = &output;
//	SYS_EXBUSSEL = 0x6100;
//    USBSTK5515_init( );


    while(put your condition) // loop
    {
        /*  Read input data and also coefficients using a probe-point connected to a host file. */
      //printf("x=%d\n",x[j]);

    	input=x[j];
    	//write your code for function call;
    	
    	array[j]=output;

      j=j+1;
    }



return 0;

}
/*
 * FUNCTION:     Read input signal and write processed output signal
 *              using ProbePoints
 * PARAMETERS: none.
 * RETURN VALUE: none.
 */
static void dataInput()
{
//    do data I/O
    return;
}

static void dataCoefs()
{
//    do data I/O
    return;
}
