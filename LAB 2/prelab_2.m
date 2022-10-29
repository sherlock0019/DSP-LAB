clc;

%SINE WAVE GENERATION

fs= 500e3;  %sampling frequency
f= 1000;  %frequency of the sinosoid
nCyl=5;  %number of cycles to be obtained in the graph
amplitude = 1;

period = 1/f; %period of the sinosoid

t = 0:1/fs:nCyl*period;  %time scale to produce sinosoid with the above specs

%saving time axis in .dat format
save 'time.dat' t -ascii   % save to time.dat

sinosoid = amplitude*sin(2*pi*f*t);  %generation of the sine wave

plot(t,sinosoid);
shg;
title ('Continuous sinusoidal signal')  
xlabel('Time(s)');  
ylabel('Amplitude');

%saving the file in .dat format
save 'Sine Wave.dat' sinosoid -ascii   % save to Sine Wave.dat

%SQUARE WAVE GENERATION

square_Wave = amplitude*square(2*pi*f*t); %generation of the sqaure wave

plot(t,square_Wave);
shg;
title ('Continuous square wave signal')  
xlabel('Time(s)');  
ylabel('Amplitude');

%saving the file in .dat format
save 'Sqaure Wave.dat' square_Wave -ascii   % save to Sqaure Wave.dat

%TRIANGLE WAVE GENERATION

triangular_Wave = amplitude*sawtooth(2*pi*f*t, 0.5); %generation of the sqaure wave

plot(t,triangular_Wave);
shg;
title ('Continuous square wave signal')  
xlabel('Time(s)');  
ylabel('Amplitude');

%saving the file in .dat format
save 'Triangular Wave.dat' triangular_Wave -ascii   % save to Sqaure Wave.dat