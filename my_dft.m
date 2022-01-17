function [Re,Im] = my_dft(n,m,N)

Re = cos(2*pi*(n)*(m)/N);
Im = sin(2*pi*(n)*(m)/N);

end