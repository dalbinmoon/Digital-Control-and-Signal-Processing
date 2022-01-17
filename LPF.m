function  [Output, State] = LPF(k, Ts, Wn, State, input) %Ts = sampling period, hz = cut of freqeuncy, Input = 상태변수

N = 2; % Order
Fs = 1/Ts; % Sampling freq

Ws = 2*pi*Fs;

%digital filter
[b, a] = butter(N, Wn/(Ws/2), 'low') ;

%System Martrix
temp = [0 1 ; -a(3) -a(2)];
temp1 = [0;1] ; 


Output = (b(2) - b(1)*a(2))*State(2,k-1) + (b(3) - b(1)*a(3))*State(1,k-1) + b(1)*input(k);
State(:,k) = temp*State(:,k-1)+temp1*input(k) ; 

end