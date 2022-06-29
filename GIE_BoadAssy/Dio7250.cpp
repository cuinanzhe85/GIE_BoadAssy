#include "StdAfx.h"
#include "GIE_BoadAssy.h"
#include "DIO7250.h"


CDIO7250::CDIO7250(void)
{
	lpSystemInfo	= m_pApp->GetSystemInfo();
	lpWorkInfo	= m_pApp->GetWorkInfo();
}


CDIO7250::~CDIO7250(void)
{
}


BOOL CDIO7250::Dio_Initialize()
{
	Release_Card(DIO_CARD_NUM);

	if(Register_Card(PCI_7250, DIO_CARD_NUM) == NoError)
	{
		DO_WritePort(DIO_CARD_NUM, 0, DIO_INIT);
		return TRUE;
	}

	return FALSE;
}

void CDIO7250::Dio_DO_WritePort(U32 ulDOut)
{
	DO_WritePort(DIO_CARD_NUM, 0, ulDOut);
}

U32 CDIO7250::Dio_DI_ReadPort()
{
	U32 ulDIn=0;

	DI_ReadPort(DIO_CARD_NUM, 0, &ulDIn);

	return ulDIn;
}

void CDIO7250::Gf_setDioWrite(U32 ulDOut)
{
	DO_WritePort(DIO_CARD_NUM, 0, ulDOut);
	Sleep(500);
	DO_WritePort(DIO_CARD_NUM, 0, DIO_INIT);
}

bool CDIO7250::Gf_getDIOJigArrive()
{
	U32 dio_in;

	dio_in = Dio_DI_ReadPort();

	if(DEBUG_PALLET_ARRIVE==1)
		return true;
	
	if(dio_in & JIG_ARRIVE)
	{
		return true;
	}
	return false;
}

bool CDIO7250::Gf_getDIOTestStart()
{
	U32 dio_in;

	dio_in = Dio_DI_ReadPort();

	if(lpWorkInfo->m_bDioDebugTestStart == true)
	{
		lpWorkInfo->m_bDioDebugTestStart = false;
		return true;
	}

	if(dio_in & TEST_START)
	{
		return true;
	}
	return false;
}

bool CDIO7250::Gf_getDIOJudgeOK()
{
	U32 dio_in;

	dio_in = Dio_DI_ReadPort();

	if(lpWorkInfo->m_bDioDebugJudgeOk == true)
	{
		lpWorkInfo->m_bDioDebugJudgeOk = false;
		return true;
	}

	if(dio_in & JUDGE_OK)
	{
		return true;
	}
	return false;
}

bool CDIO7250::Gf_getDIOJudgeNG()
{
	U32 dio_in;

	dio_in = Dio_DI_ReadPort();

	if(lpWorkInfo->m_bDioDebugJudgeNg == true)
	{
		lpWorkInfo->m_bDioDebugJudgeNg = false;
		return true;
	}

	if(dio_in & JUDGE_NG)
	{
		return true;
	}
	return false;
}

void CDIO7250::Gf_getDioGetInput()
{
	BYTE readValue = 0;
	readValue = (BYTE)Dio_DI_ReadPort();
	Lf_setDioFlow(readValue);
}

void CDIO7250::Lf_setDioFlow(BYTE newReadVal)
{
	if(newReadVal&JIG_ARRIVE)
	{
		if (lpWorkInfo->m_bDioJigArrived == false)
		{
			lpWorkInfo->m_bDioJigArrived = true;
		}
	}
	else 
	{
		lpWorkInfo->m_bDioJigArrived = false;
	}

	if(newReadVal&TEST_START)
	{
		if(lpWorkInfo->m_bDioTestStart == false)
		{
			lpWorkInfo->m_bDioTestStart = true;
		}
	}
	else 
	{
		lpWorkInfo->m_bDioTestStart = false;
	}

	if(newReadVal&JUDGE_OK) 
	{
		if (lpWorkInfo->m_bDioJudgeOk == false && lpWorkInfo->m_bIsEdidFail == false)
		{
			//Pattern Test 진행 중에는 판정 OK, NG 버튼은 무시한다. Fast Judge의 경우 제외.
//imsi			if (pUiPorc->comm.curData.iStartTest != SEQ_PTN_TEST_START || lpSystemInfo->m_nFastJudge == TRUE)
			{
				lpWorkInfo->m_bDioJudgeOk = true;
			}
		}
	}
	else 
	{
		lpWorkInfo->m_bDioJudgeOk = false;
	}

	if(newReadVal&START_SW1)
	{
		if (lpWorkInfo->m_bDioSwitch1 == false)
		{
			lpWorkInfo->m_bDioSwitch1 = true;
		}
	}
	else 
	{
		lpWorkInfo->m_bDioSwitch1 = false;
	}

	if(newReadVal & START_SW2)
	{
		if (lpWorkInfo->m_bDioSwitch2 == false)
		{
			lpWorkInfo->m_bDioSwitch2 = true;
		}
	}
	else
	{
		lpWorkInfo->m_bDioSwitch2 = false;
	}

	if(newReadVal&JUDGE_NG)
	{
		if (lpWorkInfo->m_bDioJudgeNg == false)
		{
			//Pattern Test 진행 중에는 판정 OK, NG 버튼은 무시한다. Fast Judge의 경우 제외.
//imsi			if (pUiPorc->comm.curData.iStartTest != SEQ_PTN_TEST_START || lpSystemInfo->m_nFastJudge == TRUE)
			{
				lpWorkInfo->m_bDioJudgeNg = true;
			}
		}
	}
	else 
	{
		lpWorkInfo->m_bDioJudgeNg = false;
	}

	if(newReadVal&PASSMODE)
	{
		if (lpWorkInfo->m_bDioPassMode == false)
		{
			lpWorkInfo->m_bDioPassMode = true;
		}
	}
	else 
	{
		lpWorkInfo->m_bDioPassMode = false;
	}
}
