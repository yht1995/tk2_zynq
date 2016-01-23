#ifndef __CMDPROCESS_H_
#define __CMDPROCESS_H_

#include "cmdline/cmdline.h"

void GetRealCnt(int* realCnt);

int UploadInfoHandler(int argc, char *argv[]);
int EnableHandler(int argc, char *argv[]);
int DisableHandler(int argc, char *argv[]);
int SetSpeedHandler(int argc, char *argv[]);
int SetPosHandler(int argc, char *argv[]);
int SetGearHandler(int argc, char *argv[]);
#endif
