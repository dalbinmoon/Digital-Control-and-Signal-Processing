clear all; close all; clc

N = 2^5;
x(1:N) = 0;
x(1:9) = [1 2 3 4 5 4 3 2 1];
t = 0:T:(N-1)*T;

ts = 0.005 ; 

dft = zeros([1 N]);

for m=0:1:N-1
 temp_Re = 0;
 temp_Im = 0;
 X_Re = 0;
 X_Im = 0;
 
 for n=0:1:N-1
 [Re,Im] = my_dft(n,m,N);
 Re = x(n+1)*Re;
 Im = x(n+1)*Im;
 X_Re = Re + temp_Re;
 temp_Re = X_Re;
 X_Im = Im + temp_Im;
 temp_Im = X_Im;
 end
dft(m+1) = X_Re-j*X_Im;
 
end



for m = 1:1:N
    
    subplot(2,1,1)
    hold on;
    stem((1/ts/N)*m,abs(dft(m)),'b'); xlabel('Frequency [Hz]') ; ylabel('Magnitude [db]') ; grid on ; str = sprintf('N = %4.2f', N) ; title(str);
    subplot(2,1,2)
    hold on;
    stem(m,angle(dft(m))*180/pi,'b'); xlabel('Frequency [Hz]') ; ylabel('Phase [deg]') ; grid on ;
    
end
