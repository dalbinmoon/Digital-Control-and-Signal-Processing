#include "Interface.h"
#define gyro_factor 1000/0.67;

extern void set_DAQ(void)
{
	/* Configuring the DAQ*/

//Create Tasks

	DAQmxCreateTask("", &handle_r);
	DAQmxCreateTask("", &handle_w1);
	DAQmxCreateTask("", &handle_w2);
	DAQmxCreateTask("", &handle_w3);
	DAQmxCreateTask("", &handle_dr);

	//Open DAQ Channels
	AI_CREATE(handle_r,  "Dev2/ai0:3");
	AO_CREATE(handle_w1, "Dev2/ao0");
	AO_CREATE(handle_w2, "Dev2/ao1");
	DO_CREATE(handle_w3, "Dev2/port0/line0");
	DI_CREATE(handle_dr, "Dev2/port0/line1:2");


	// Start Tasks
	DAQmxStartTask(handle_r);
	DAQmxStartTask(handle_w1);
	DAQmxStartTask(handle_w2);
	DAQmxStartTask(handle_w3);
	DAQmxStartTask(handle_dr);

}

extern void clear_DAQ(void)
{
	/* Close all tasks associated with the DAQ*/


	DAQmxStopTask(handle_r); // stop  the handle_r task
	DAQmxStopTask(handle_w1); // stop  the handle_w1 task
	DAQmxStopTask(handle_w2); // stop the handle_w2 task
	DAQmxStopTask(handle_w3); // stop  the handle_w3 task
	DAQmxStopTask(handle_dr); // stop  the handle_w3 task

	DAQmxClearTask(handle_r); // clear the handle_r task
	DAQmxClearTask(handle_w1); // clear the handle_w1 task
	DAQmxClearTask(handle_w2); // clear the handle_w2 task
	DAQmxClearTask(handle_w3); // clear the handle_w3 task
	DAQmxClearTask(handle_dr); // clear the handle_w3 task
}
extern void DAQ_read(void)
{
	Analog_Read_Vector(handle_r, read, 4);
	Wout = (read[0] - gyro_offset)*gyro_factor; // [deg/s]
	Vpot = read[1]+1.4; // Vpot(0~5) // 
	DOA = read[2];
	DIR_analog = read[3];
	//printf("Wout=%.4lf\tDIR = %.4lf\tVpot = %.4lf\tDOA = %.4lf \n",Wout,DIR_analog,Vpot, DOA);


}

extern void DAQ_analog_write(double Vss)
{	
	Analog_Write_Scalar(handle_w1, &Vss);
	
}

extern void DAQ_digital_write(int status)
{
	if (status == 1) {
		Digital_Write_Vector(handle_w3, Digital_ON);
	}
	if (status == 0) {
		Digital_Write_Vector(handle_w3, Digital_OFF);
	}
	
}

