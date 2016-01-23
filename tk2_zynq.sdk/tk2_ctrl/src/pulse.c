

/***************************** Include Files *******************************/
#include <math.h>

#include "pulse.h"
#include "xil_io.h"
#include "xil_types.h"

/************************** Function Definitions ***************************/



void SetFreq(u32 address,int freq)
{
	int div = abs(INPUT_FREQ/freq);
	if(freq>0){
		PULSE_mWriteReg(address,PULSE_S00_AXI_SLV_REG2_OFFSET,0x1);
	}else{
		PULSE_mWriteReg(address,PULSE_S00_AXI_SLV_REG2_OFFSET,0x0);
	}
	PULSE_mWriteReg(address,PULSE_S00_AXI_SLV_REG0_OFFSET,div);
}

void SetCnt(u32 address,int cnt)
{
	PULSE_mWriteReg(address,PULSE_S00_AXI_SLV_REG1_OFFSET,cnt*2);
}

int GetCnt(u32 address)
{
	return (int)PULSE_mReadReg(address,PULSE_S00_AXI_SLV_REG3_OFFSET);
}
