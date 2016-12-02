[y Fs] = wavread('mystery.wav');
y = y(:,1);

n = size(y,1)

power = abs(fft(y));

frequencies = linspace(0.0, Fs, n);

n_for_1KHz = round(n * 1000/Fs);

plot( frequencies(2:n_for_1KHz), power(2:n_for_1KHz) )
title('power spectrum for the tune')

figure
plot( frequencies(2:n_for_1KHz), power(2:n_for_1KHz), 'b', 5/4 * frequencies(2:n_for_1KHz), - power(2:n_for_1KHz), 'g' )
title('power spectrum, with the spectrum shifted by 5/4 (= Harmony)')

spikes = [110 82 55 78 148 156 160 165 220 300 528]

key = spikes(1)
%  The key is 'A':    110 = 440 * 2^(-2)  =  'A'

spikes / key

%  1.00000   0.74545   0.50000   0.70909   1.34545   1.41818   1.45455   1.50000   2.00000   2.72727   4.80000

%    key     fifth/2   octave    min.fifth fourth   min.fifth   fifth    fifth   octave  fourth*2  min.third*4
%
%  the 'major third'  =  1.189; in the piano scale this is about 5/4 = 1.20
%  the 'minor fifth'  =  1.141


