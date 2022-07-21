#pragma once
#include "Dask64.h"

#define DIO_CARD_NUM		0

#define DIO_INIT			0x00

#define JIG_ARRIVE			0x01
#define TEST_START			0x02
#define JUDGE_OK			0x08
#define START_SW1			0x10
#define START_SW2			0x20
#define JUDGE_NG			0x40
#define PASSMODE			0x80

class CDIO7230
{
public:
	CDIO7230(void);
	~CDIO7230(void);

	BOOL Dio_Initialize();
	void Dio_DO_WritePort(U32 ulDOut);
	U32 Dio_DI_ReadPort();

	void Dio_DO_WriteSetBit(U32 ulDOut, BOOL bOnOff);

	void Gf_setDioWrite(U32 ulDOut);
	bool Gf_getDIOJigArrive();
	bool Gf_getDIOTestStart();
	bool Gf_getDIOJudgeOK();
	bool Gf_getDIOJudgeNG();
	void Gf_getDioGetInput();


protected:
	LPSYSTEMINFO		lpSystemInfo;
	LPINSPWORKINFO	lpWorkInfo;

	U32 nOffLineDOValue;

	void Lf_setDioFlow(BYTE newReadVal);
};
