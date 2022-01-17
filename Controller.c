#include "Controller.h"

#define FINISH_TIME      (double)(10.0) // final time
#define Ts (double)(0.005) // [5ms]
#define SIZE_DATA          (int)(FINISH_TIME/Ts+1000) 

/*Wbar = 0.75 OS = 10*/ 
#define Kp		(double)0.013775
#define Ki  	(double)0.470956
#define Kd		(double)0.000071
#define Wc		(double)31.5590
#define Kpt  (double)3.5 // P controller gain of Outer Loop 3.5 

extern void PID_Controller(double Input)
{
	P_result = Kp * Input;//P_제어기

	x_i[0] = 0.5*(Input + 2 * x_i[1]);
	x_i[1] = x_i[0];
	I_result = Ki * Ts* 0.5 * (Input + 2 * x_i[1]) + Ki * Ts * x_i[1];// I_제어기

	x_d[0] = ((Input - (10 * Wc*Ts - 2)*x_d[1]) / (10 * Wc*Ts + 2));
	x_d[1] = x_d[0];
	D_result = (20 * Kd*Wc*Input) / (10 * Wc*Ts + 2) - (10 * Wc*Ts - 2) * 20 * Wc*Kd*x_d[1] / (10 * Wc*Ts + 2) - 20 * Wc*Kd*x_d[1];// I_제어기

	Vcmd = P_result + I_result + D_result;

}
extern void Tracking_Controller(void)
{

	if (DIR_analog >= 2.5 && DOA > 0.7 && DOA < 2.1) {
		angle_feedback = (DOA - 0.186) / 0.1403;

	}
	else if (DIR_analog < 2.5 && DOA > 0.7 && DOA < 2.1) {
		angle_feedback = -((DOA - 0.186) / 0.1403);
	}
	else {
		DOA = 0;
		angle_feedback = 0;
	}




	error_angle = angle_in + angle_feedback;


	Win = error_angle * Kpt;
}

