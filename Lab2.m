%%
clear all ; close all ; clc ; 

% node1 = load('nocap_node1.csv') ; 
% node2 = load('nocap_node2.csv') ; 
% node3 = load('nocap_node3.csv') ; 
% node4 = load('nocap_node4.csv') ;
% node34 = load('nocap_node3,4.csv') ;
nonode1fft = load('nocap_node1_fft.csv') ; 
nonode2fft = load('nocap_node2_fft.csv') ;
nonode3fft = load('nocap_node3_fft.csv') ;
nonode4fft = load('nocap_node4_fft.csv') ;
node2fft = load('cap_node2_fft.csv') ;
node3fft = load('cap_node3_fft.csv') ;
node4fft = load('cap_node4_fft.csv') ;

% figure(), plot(node1(:,1),node1(:,2)) ; title('nocap node1') ; 
% figure(), plot(node2(:,1),node2(:,2)) ; title('nocap node2') ; 
% figure(), plot(node3(:,1),node3(:,2)) ; title('nocap node3') ; 
% figure(), plot(node4(:,1),node4(:,2)) ; title('nocap node4') ; 
% figure(), plot(node34(:,1),node34(:,2)) ; hold on, plot(node34(:,3),node34(:,4)) ; title('nocap node3,4') ;
figure(), plot(nonode1fft(:,1),db2mag(nonode1fft(:,2))) ; title('nocap node1fft') ; xlim([0 500]);
figure(), plot(nonode2fft(:,1),db2mag(nonode2fft(:,2))) ; title('nocap node2fft') ; xlim([0 500]);
figure(), plot(nonode3fft(:,1),db2mag(nonode3fft(:,2))) ; title('nocap node3fft') ; xlim([0 500]);
figure(), plot(nonode4fft(:,1), db2mag(nonode4fft(:,2))) ; title('nocap node4fft') ; xlim([0 500]);
figure(), plot(node2fft(:,1), db2mag(node2fft(:,2))) ; title('cap node2fft') ; xlim([0 500]);
figure(), plot(node3fft(:,1),db2mag(node3fft(:,2))) ; title('cap node3fft') ; xlim([0 500]);
figure(), plot(node4fft(:,1),node4fft(:,2)) ; title('cap node4fft') ; xlim([0 500]);

%% signal 1
clear all ; close all ; clc ; 
N1 = 2^2 ; N2 = 2^3 ; N3 = 2^4 ; N4 = 2^5 ;  

buffer1 = zeros(1, N1) ; buffer2 = zeros(1,N2) ; buffer3 = zeros(1,N3) ; buffer4 = zeros(1,N4) ; 
signal = zeros(1,5) ; 

for i = 0 : 1 : 5
        if i == 1 
            signal(1,i) = -1 ;
        end
            if i == 2
                signal(1,i) = -1 ; 
            end
            if i == 3
                signal(1,i) = -1 ; 
            end
end
            
 N = 256 ;        

buffer(1:N) = signal ; 
% buffer1(1:N1) = signal ; 

Xw1 = fft(buffer1, N1) ; Xw2 = fft(buffer2, N2) ; Xw3 = fft(buffer3, N3) ; Xw4 = fft(buffer4, N4) ; 
hax1 = ifft(Xw1, N1) ;  hax2 = ifft(Xw2, N2) ; hax3 = ifft(buffer3, N3) ; hax4 = ifft(buffer4, N4) ; 

figure(1)
plot(Xw1) 
