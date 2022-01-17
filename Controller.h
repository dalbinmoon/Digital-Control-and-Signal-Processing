#pragma once
#define FINISH_TIME      (double)(10.0) // final time
#define Ts (double)(0.005) // [5ms]
#define SIZE_DATA          (int)(FINISH_TIME/Ts+1000)

extern double Vcmd;
extern double err_cur ;
extern double P_result ;
extern double I_result ;
extern double D_result ;
extern double x_d[2];
extern double x_i[2];
extern double Vpot ;
extern double DOA;
extern double DIR_analog;
extern double angle_in ;
extern double error_angle ;
extern double angle_feedback ;
extern double Win;

extern void PID_Controller(double Input);
extern void Tracking_Controller(void);

extern double   bufOutput[SIZE_DATA];
extern double	bufOutput2[SIZE_DATA];
extern double	bufOutput3[SIZE_DATA];

