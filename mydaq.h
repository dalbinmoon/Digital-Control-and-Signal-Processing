#define CREATE_CHAI(Task, Chan)  DAQmxCreateAIVoltageChan(Task, Chan, "", DAQmx_Val_RSE, -10.0, 10.0, DAQmx_Val_Volts, NULL)  
#define CREATE_CHAO(Task, Chan)  DAQmxCreateAOVoltageChan(Task, Chan, "", 0, 5.0, DAQmx_Val_Volts, NULL)                   
#define CREATE_CHPO(Task, Chan)  DAQmxCreateDOChan(Task, Chan, "", DAQmx_Val_GroupByChannel)

#define READ_CHAI(Task, Data) DAQmxReadAnalogF64(Task, -1, 5.0, DAQmx_Val_GroupByChannel, Data, sizeof(float64) * 4, NULL, NULL)

#define WRITE_CHAI(Task, Data) DAQmxWriteAnalogF64(Task, 1, 1, 10.0, DAQmx_Val_GroupByChannel, Data, NULL, NULL);
#define WRITE_CHPO(Task, Data) DAQmxWriteDigitalLines(Task, 1, 1, 10.0, DAQmx_Val_GroupByChannel, Data, NULL, NULL);

