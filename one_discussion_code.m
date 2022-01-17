%%
clear all; close all; clc;
%%
N = 2;
Ts = 0.001;
Tf = 2 ; 

Nstep=floor(Tf/Ts) ; 
dtime = 0 : Ts : (Nstep-1)*Ts ; 
dtime1 = 0 : Ts : Nstep*Ts ; 

Wc1 = 2*pi*20;
Wc2 = 2*pi*70;
Wc_BPF = [2*pi*30 2*pi*40];
Wc_BSF = [2*pi*30 2*pi*40];

% Analog Filter Desgin

[CT_LPF_NUM1, CT_LPF_DEN1] = butter (N,Wc1,'low','s');
[CT_LPF_NUM2, CT_LPF_DEN2] = butter (N,Wc2,'low','s');
[CT_HPF_NUM1, CT_HPF_DEN1] = butter (N,Wc1,'high','s');
[CT_HPF_NUM2, CT_HPF_DEN2] = butter (N,Wc2,'high','s');
[CT_BPF_NUM, CT_BPF_DEN] = butter (N,Wc_BPF,'bandpass','s');
[CT_BSF_NUM, CT_BSF_DEN] = butter (N,Wc_BSF,'stop','s');
HsLPF1 = tf(CT_LPF_NUM1,CT_LPF_DEN1);
HsLPF2 = tf(CT_LPF_NUM2,CT_LPF_DEN2);
HsHPF1 = tf(CT_HPF_NUM1,CT_HPF_DEN1);
HsHPF2 = tf(CT_HPF_NUM2,CT_HPF_DEN2);
HsBPF = tf(CT_BPF_NUM,CT_BPF_DEN);
HsBSF = tf(CT_BSF_NUM,CT_BSF_DEN);

% Digital Filter Design

HzLPF1 = c2d(HsLPF1,Ts,'tustin');
HzLPF2 = c2d(HsLPF2,Ts,'tustin');
HzHPF1 = c2d(HsHPF1,Ts,'tustin');
HzHPF2 = c2d(HsHPF2,Ts,'tustin');

% Q : Is Wc is correct?
opt1 = c2dOptions('Method','tustin','PrewarpFrequency',35);
HzBPF=c2d(HsBPF,Ts,opt1);
opt2 = c2dOptions('Method','tustin','PrewarpFrequency',2*pi*35);
HzBSF=c2d(HsBSF,Ts,opt2);

%%
%drawing bode plot
% figure(),
% subplot 321, bode(HsLPF1); title('HsLPF1 20[Hz]') ; 
% subplot 322, bode(HsHPF1); title('HsHPF1 20[Hz]') ; 
% subplot 323, bode(HsLPF2); title('HsLPF2 70[Hz]') ; 
% subplot 324, bode(HsHPF2); title('HsHPF2 70[Hz]') ; 
% subplot 325, bode(HsBPF); title('Bandpass Filter') ; 
% subplot 326, bode(HsBSF); title('Bandstop Filter') ; 
% 
% figure(),
% subplot 321, bode(HzLPF1); title('HzLPF1 20[Hz]') ; 
% subplot 322, bode(HzHPF1); title('HzHPF1 20[Hz]') ; 
% subplot 323, bode(HzLPF2); title('HzLPF2 70[Hz]') ; 
% subplot 324, bode(HzHPF2); title('HzHPF2 70[Hz]') ; 
% subplot 325, bode(HzBPF); title('Bandpass Filter') ; 
% subplot 326, bode(HzBSF); title('Bandstop Filter') ;

%%
%plot data from simulink
% sim('one_two') ;

% figure(),
% subplot 321, plot(ans.CT_LPF1_20); 
% hold on, plot(ans.DT_LPF1_20); title('CT&DT LPF 20[Hz]') ; xlim([0 100]) ; 
% subplot 322, plot(ans.CT_LPF2_70); 
% hold on, plot(ans.DT_LPF2_70); title('CT&DT LPF 70[Hz]') ; xlim([0 100]) ; 
% subplot 323, plot(ans.CT_HPF1_20); 
% hold on, plot(ans.DT_HPF1_20); title('CT&DT HPF 20[Hz]') ; xlim([0 100]) ; 
% subplot 324, plot(ans.CT_HPF2_70); 
% hold on, plot(ans.DT_HPF2_70); title('CT&DT HPF 70[Hz]') ; xlim([0 100]) ; 
% subplot 325, plot(ans.CT_BPF); 
% hold on, plot(ans.DT_BPF); title('CT&DT Bandpass Filter') ; xlim([0 100]) ; 
% subplot 326, plot(ans.CT_BSF); 
% hold on, plot(ans.DT_BSF); title('CT&DT Stopband Filter') ; xlim([0 100]) ; 

%%
fin = 2 ; 
sigma = 0.2 ;

white_noise = sigma^2*Ts ; 

stt = sin(2*pi*fin*dtime) ; 
st = [dtime'  stt'] ; %from workplace


%start simulink
sim('one_third') ;

%plot data from simulink
% figure(),
% subplot 321, plot(ans.CT_LPF1_20_noise); 
% hold on, plot(ans.DT_LPF1_20_noise); title('CT&DT LPF 20[Hz]') ; 
% subplot 322, plot(ans.CT_LPF2_70_noise); 
% hold on, plot(ans.DT_LPF2_70_noise); title('CT&DT LPF 70[Hz]') ; 
% subplot 323, plot(ans.CT_HPF1_20_noise); 
% hold on, plot(ans.DT_HPF1_20_noise); title('CT&DT HPF 20[Hz]') ; 
% subplot 324, plot(ans.CT_HPF2_70_noise); 
% hold on, plot(ans.DT_HPF2_70_noise); title('CT&DT HPF 70[Hz]') ; 
% subplot 325, plot(ans.CT_BPF_noise);  
% hold on, plot(ans.DT_BPF_noise); title('CT&DT Bandpass Filter') ; 
% subplot 326, plot(ans.CT_BSF_noise); 
% hold on, plot(ans.DT_BSF_noise); title('CT&DT Stopband Filter') ; 

%%
Cstate = zeros(1,Nstep) ; % Initalize State Variable to 0
Pstate = zeros(1,Nstep) ; % Initialize State Variable to 0

State_20 = [Pstate ; Cstate]; % State Variable Vector
State_70 = [Pstate ; Cstate]; % State Variable Vector

% Input and Output
input = ans.noise ; 
output_LPF_20 = zeros(1, Nstep) ;
output_LPF_70 = zeros(1, Nstep) ;

for k = 2 : Nstep %Real Time
    
   [output_LPF_20(k), State_20] = LPF(k, Ts, Wc1, State_20, input) ; 
   [output_LPF_70(k), State_70] = LPF(k, Ts, Wc2, State_70, input) ; 
   
end

figure(),
subplot 211, plot(dtime, output_LPF_20, 'linewidth', 2); 
hold on, plot(dtime1, ans.DT_LPF1_20_noise); title('DT LPF 20[Hz]_simulink/fuc') ; 
legend('LPF function', 'Simulink');
subplot 212, plot(dtime, output_LPF_70, 'linewidth', 2) ; 
hold on, plot(dtime1, ans.DT_LPF2_70_noise); title('DT LPF 70[Hz]_simulink/fuc') ; 
legend('LPF function', 'Simulink');

%%
StateBF = [Pstate ; Pstate ; Pstate ; Cstate]; % State Variable Vector

% Input and Output 
output_BPF = zeros(1, Nstep) ;

for k = 4 : Nstep %Real Time
    
   [output_BPF(k), StateBF] = BPF(k, Ts, Wc_BPF, StateBF, input) ; 
   
end

figure(),
plot(dtime, output_BPF, 'linewidth', 2);
hold on, plot(dtime1, ans.DT_BPF_noise); title('BandPass Filter [30,40]_simulink/fuc') ; 
legend('BPF function', 'Simulink') ; 
