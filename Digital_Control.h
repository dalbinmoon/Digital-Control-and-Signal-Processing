#pragma once
#include <stdio.h>
#include "Functions.h"
#define _CRT_SECURE_NO_WARNINGS


/* Function Prototype*/
extern void clear_DAQ(void);
extern void set_DAQ(void);
extern void DAQ_read(void);
extern void DAQ_analog_write(double Vss);
extern void DAQ_digital_write(int status);
extern void Triangular_Input(double freq); // Input the triangular wave available adjusting frequency
extern void Linearization(void);
extern void Recording_Data(void);
extern void Gyro_offset(void);
extern void Modeling(double freq);
extern void Reading_Data(void);
extern void LPF_N2(void);
extern void Step(void);
extern void PID_Controller(double Input);
void moving_gimbal(void);
extern void Ramp(void);
extern void Position_Init(void);
extern void Tracking_Controller(void);


/* Simulation Variables */

int i = 0;
extern double Start_Time = 0.0;
extern double Current_Time = 0.0;
extern double Processing_Time = 0.0;
double Time1 = 0.0;
double Time2 = 0.0;
extern double Simul_Time = 0;
extern int Simul_count = 0;

/* Simulation Buffer*/

double   bufTime[SIZE_DATA];
double   bufChkTaskTime[SIZE_DATA];
extern double   bufInput[SIZE_DATA] = { 0.0 };
extern double   bufOutput[SIZE_DATA] = { 0.0 };
extern double	 gyro_raw[SIZE_DATA] = { 0.0 };
extern double	 sum = 0;
extern double	 gyro_offset = 0;



/*Variables related with DAQ Interface*/
extern double read[4];
extern double Vcmd;
extern double Vss;

/* Variables related with Triangular wave */
extern int N = 0; //This is used for deciding y intercept

/* Variables related with Modeling & Model Validation */
//extern double freq[15] = { 0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2,1.3,1.4,1.5 }; // [Hz]
//extern int index = 0;
extern double freq = 0.1; //[Hz]

/* Variables related with LPF Validation */
extern double   input[SIZE_DATA] = { 0.0, };
extern double	P[2] = { 0.0, };
extern double	C[2] = { 0.0, };

/*LPF Filter (Cut-Off : 25 Hz)*/
extern double	a[3] = { 1,-0.9428,0.3333 }; // in MATLAB
extern double	b[3] = { 0.0976, 0.1953, 0.0976 };// in MATLAB

/* Variables related with Inner Control Loop */
extern double Win = 0;
extern double Wout = 0;


/* Variables related with Inner Loop Controller */
extern double err_cur = 0;
extern double P_result = 0;
extern double I_result = 0;
extern double D_result = 0;
extern double x_d[2] = { 0.0 };
extern double x_i[2] = { 0.0 };

/*Ramp*/
extern int flag = 1;

/* Variables related with Outer Loop Controller */
extern double angle_in = 0;
extern double error_angle = 0;
extern double angle_feedback = 0;
extern double    Vpot;
extern double	 DOA;
extern double    DIR_analog;