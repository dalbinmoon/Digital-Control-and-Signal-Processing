#include "NIDAQmx.h"

/* Preprocessing */

#define SAMPLING_TIME (double)(0.005) // [5ms]
#define FINISH_TIME      (double)(10.0) // final time
#define SIZE_DATA          (int)(FINISH_TIME/SAMPLING_TIME+1000) 

extern double	 gyro_offset;
extern double bufOutput[SIZE_DATA];
extern double bufOutput2[SIZE_DATA];
extern double bufOutput3[SIZE_DATA];
extern double bufOutput4[SIZE_DATA];
extern int Simul_count;
extern double Wout;

/*Function Prototype*/
extern void set_DAQ(void);
extern void clear_DAQ(void);
extern void DAQ_read(void);
extern void DAQ_analog_write(double Vss);
extern void DAQ_digital_write(int status);

/*DAQ Handlers*/

static TaskHandle   handle_r = 0;
static TaskHandle   handle_w1 = 0;
static TaskHandle   handle_w2 = 0;
static TaskHandle   handle_w3 = 0;
static TaskHandle   handle_dr = 0;



/*Preprocessing for DAQ*/

#define MAX_AI  (double)( 10.0) 
#define MIN_AI  (double)(-10.0) 
#define MAX_AO  (double)(  5.0) 
#define MIN_AO  (double)(  0.0) 
#define AI_CREATE(Taskhandle, Channel)  DAQmxCreateAIVoltageChan(Taskhandle, Channel, "", DAQmx_Val_Diff, MIN_AI, MAX_AI, DAQmx_Val_Volts, NULL); 
#define AO_CREATE(Taskhandle, Channel)  DAQmxCreateAOVoltageChan(Taskhandle, Channel, "", MIN_AO, MAX_AO, DAQmx_Val_Volts, NULL);               
#define DO_CREATE(Taskhandle,Channel)   DAQmxCreateDOChan(Taskhandle, Channel, "", DAQmx_Val_GroupByChannel);
#define DI_CREATE(Taskhandle,Channel)   DAQmxCreateDIChan(Taskhandle, Channel,"",DAQmx_Val_ChanPerLine);
#define Analog_Read_Vector(Taskhandle,read_vector,N) DAQmxReadAnalogF64(Taskhandle, -1, 5.0, DAQmx_Val_GroupByChannel, read_vector, sizeof(float64) * N, NULL, NULL);
#define Analog_Write_Scalar(Taskhandle,data_address) DAQmxWriteAnalogF64(Taskhandle, 1, 1, 10.0, DAQmx_Val_GroupByChannel, data_address, NULL, NULL);
#define Digital_Write_Vector(Taskhandle,array_address) DAQmxWriteDigitalLines(Taskhandle, 1, 1, 10, DAQmx_Val_GroupByChannel, array_address, NULL, NULL);
#define Digital_Read_Vector(Taskhandle,read_vector,N) DAQmxReadDigitalLines(Taskhandle,-1,10.0,DAQmx_Val_GroupByChannel,read_vector,sizeof(uInt32) * N,NULL,NULL,NULL);

extern float64	  read[4] = { 0.0 };
extern uInt8	  DIR_data[2] = {0};
extern float64    Vcmd= 0; // -2.5~2.5[V]
extern float64    Vss = 0; // 0~5[V]

static uInt8      Digital_ON[1] = { 1 };
static uInt8      Digital_OFF[1] = { 0 };

extern float64	  Vpot = 0;
extern float64    DOA = 0;
extern float64    DIR_analog = 0;



