#include <stdlib.h>

#include "xparameters.h"
#include "cmdProcess.h"
#include "pulse.h"
#include "xil_types.h"

tCmdLineEntry g_psCmdTable[] =
{
	{ "UP", UploadInfoHandler, "UploadInfo" },
	{ "EN", EnableHandler, "Enable" },
	{ "DIS", DisableHandler, "Disable" },
	{ "SS", SetSpeedHandler, "SetSpeed" },
	{ "SP", SetPosHandler, "SetPos" },
	{ "SG", SetGearHandler, "SetGear" },
	{ 0, 0, 0 }
};

u32 g_motorAddress[4]={
	XPAR_PULSE_1_0,
	XPAR_PULSE_2_0,
	XPAR_PULSE_3_0,
	XPAR_PULSE_4_0
};

void GetRealCnt(int* realCnt)
{
	uint8_t i;
	for (i = 0; i < 4; i++) {
		realCnt[i]=GetCnt(g_motorAddress[i]);
	}
}

int UploadInfoHandler(int argc, char *argv[])
{
	return 0;
}

int EnableHandler(int argc, char *argv[])
{
	return 0;
}

int DisableHandler(int argc, char *argv[])
{
	return 0;
}

int SetSpeedHandler(int argc, char *argv[])
{
	const int correctArgc = 5;
	if (argc == correctArgc) {
		uint8_t i;
		for (i = 0; i < 4; i++) {
			int speed = atoi(argv[i + 1]);
			SetFreq(g_motorAddress[i],speed);
		}
		return 0;
	}else if (argc < correctArgc) {
		return CMDLINE_TOO_FEW_ARGS;
	}else{
		return CMDLINE_TOO_MANY_ARGS;
	}
}

int SetPosHandler(int argc, char *argv[])
{
	const int correctArgc = 5;
	if (argc == correctArgc) {
		uint8_t i;
		for (i = 0; i < 4; i++) {
			int pos = atoi(argv[i + 1]);
			SetCnt(g_motorAddress[i],pos);
		}
		return 0;
	}else if (argc < correctArgc) {
		return CMDLINE_TOO_FEW_ARGS;
	}else{
		return CMDLINE_TOO_MANY_ARGS;
	}
}

int SetGearHandler(int argc, char *argv[])
{
	return 0;
}
