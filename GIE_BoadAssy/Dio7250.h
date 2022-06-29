#pragma once
#ifdef _X64
	#include "Dask64.h"
#else
	#include "Dask.h"
#endif

#define DIO_CARD_NUM		0

#define DIO_INIT			0x00

#define JIG_ARRIVE			0x01
#define TEST_START			0x02
#define JUDGE_OK			0x08
#define START_SW1			0x10
#define START_SW2			0x20
#define JUDGE_NG			0x40
#define PASSMODE			0x80

enum
{
	DIO_GUMI_M5_PRESS_DOWN = 0,      
	DIO_GUMI_M5_SPARE,	
	DIO_GUMI_M5_EDID_NG,
	DIO_GUMI_M5_BCR_READ_OK,
	DIO_GUMI_M5_JUDGE_OK,
	DIO_GUMI_M5_JUDGE_NG,
	DIO_GUMI_M5_TEST_OK,
	DIO_GUMI_M5_PRESS_NOMAL_UP,
	DIO_GUMI_M5_MAX
};

enum
{
	DIO_PRESS_DOWN = 0,      
	DIO_BCR_OK,	
	DIO_BCR_NG,
	DIO_TEST_ON,
	DIO_JUDGE_OK,
	DIO_JUDGE_NG,
	DIO_PRESS_NOMAL_UP,
	DIO_PRESS_FAST_UP,
	DIO_MAX
};

class CDIO7250
{
public:
	CDIO7250(void);
	~CDIO7250(void);

	BOOL Dio_Initialize();
	void Dio_DO_WritePort(U32 ulDOut);
	U32 Dio_DI_ReadPort();
	void Gf_setDioWrite(U32 ulDOut);
	bool Gf_getDIOJigArrive();
	bool Gf_getDIOTestStart();
	bool Gf_getDIOJudgeOK();
	bool Gf_getDIOJudgeNG();
	void Gf_getDioGetInput();
protected:
	LPINSPWORKINFO	lpWorkInfo;
	LPSYSTEMINFO	lpSystemInfo;

protected:
	void Lf_setDioFlow(BYTE newReadVal);
};
