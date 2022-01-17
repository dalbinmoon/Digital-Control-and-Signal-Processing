function  [Output, State] = BPF(k, Ts, Wc, State, input) %Ts = sampling period, hz = cut of freqeuncy, Input = 상태변수

N = 2; % Order
Fs = 1/Ts; % Sampling freq

Ws = [(2*pi*Fs)/2];

division = [Wc(1)/Ws Wc(2)/Ws] ; 

%digital filter
[b, a] = butter(N, division, 'bandpass') ;

%System Martrix
temp = [0 1 0 0 ; 0 0 1 0 ; 0 0 0 1 ; -a(5) -a(4) -a(3) -a(2)];
temp1 = [0; 0 ; 0 ; 1] ; 


Output = (b(2) - b(1)*a(2))*State(4,k-1) + (b(3) - b(1)*a(3))*State(3,k-1) + (b(4)- b(1)*a(4))*State(2, k-1) + (b(5) - b(1)*a(5))*State(1,k-1) + b(1)*input(k);
State(:,k) = temp*State(:,k-1)+temp1*input(k) ; 

end