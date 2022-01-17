#pragma once

#ifndef HEADER_USER_DEFINED_FUNCTION
#define HEADER_USER_DEFINED_FUNCTION

#include <windows.h>
#include <time.h>

/*Simulation Variables*/
#define FINISH_TIME      (double)(10.0) // final time
#define SAMPLING_TIME    (double)(0.005) // [5ms]
#define SIZE_DATA        (int)(FINISH_TIME/SAMPLING_TIME+1000) 

/* Functions Prototype */
double CheckWindowsTime(void); // check the window time in [ms]
extern void Triangular_Input(double freq); // Input the triangular wave available adjusting frequency
extern void Linearization(void);
extern void Recording_Data(void);
extern void Gyro_offset(void);
extern void Modeling(double freq);
extern void Reading_Data(void);
extern void LPF_N2(void);
extern void Step(void);
extern void DAQ_analog_write(double Vss);
extern void Recording_Data(void);
extern void Ramp(void);

extern double Simul_Time;
extern int Simul_count;
extern double bufOutput[SIZE_DATA];
extern double bufOutput2[SIZE_DATA];
extern double bufOutput3[SIZE_DATA];
extern double	bufOutput4[SIZE_DATA];
extern double	bufOutput5[SIZE_DATA];
extern double	bufOutput6[SIZE_DATA];
extern double	bufOutput7[SIZE_DATA];
extern double   bufInput[SIZE_DATA];
extern double   Input[SIZE_DATA];
extern double Vcmd;
extern double Vss;
extern int N; // Traingular wave
extern double	 gyro_raw[SIZE_DATA];
extern double	 sum;
extern double	 gyro_offset;
extern double    read[4];
extern void DAQ_read(void);
extern int index;
//extern double freq[15]; //Modeling
extern double freq; //Modeling Validation
extern double err_cur;
extern double Vpot;
//extern double freq; // Modelig Validation

/*LPF*/
extern double	P[2];
extern double	C[2];
extern double	a[3];
extern double	b[3];
extern double   input[SIZE_DATA];


/*Variables related with Ramp function*/
static int Ramp_check ;
static double resolution ;
extern int flag;

#endif