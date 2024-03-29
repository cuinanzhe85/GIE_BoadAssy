﻿#include "stdafx.h"
#include "GIE_BoadAssy.h"

#include "DIO7230.h"


CDIO7230::CDIO7230(void)
{
	lpSystemInfo = m_pApp->GetSystemInfo();
	lpWorkInfo = m_pApp->GetWorkInfo();
}


CDIO7230::~CDIO7230(void)
{
}


BOOL CDIO7230::Dio_Initialize()
{
	Release_Card(DIO_CARD_NUM);

	if(Register_Card(PCI_7230, DIO_CARD_NUM) == NoError)
	{
		Dio_DO_WritePort(DIO_OUT_RESET);
		return TRUE;
	}

	return FALSE;
}

void CDIO7230::Dio_DO_WritePort(U32 ulDOut)
{
	DO_WritePort(DIO_CARD_NUM, 0, ulDOut);
	CString slog;
	slog.Format(_T("OUT VALUE : 0x%04X"), ulDOut);
	m_pApp->Gf_writeLogData(_T("<DIO>"), slog);
}

U32 CDIO7230::Dio_DI_ReadPort()
{
	U32 ulDIn=0;

	DI_ReadPort(DIO_CARD_NUM, 0, &ulDIn);

	return ulDIn;
}

void CDIO7230::Gf_setDioWrite(U32 ulDOut)
{
	Dio_DO_WritePort(ulDOut);
	Sleep(500);
	Dio_DO_WritePort(DIO_OUT_RESET);
}

void CDIO7230::Gf_setDioOutOK()
{
	Gf_setDioWrite(DO_TEST_JUDGE_OK);
	m_pApp->Gf_writeLogData("<DIO>", "Out OK");
}

void CDIO7230::Gf_setDioOutNG()
{
	Gf_setDioWrite(DO_TEST_JUDGE_NG);
	m_pApp->Gf_writeLogData("<DIO>", "Out NG");
}

void CDIO7230::Gf_setDioOutTesting()
{
	Dio_DO_WritePort(DO_TEST_TESTING);
	m_pApp->Gf_writeLogData("<DIO>", "Out Testing");
}

bool CDIO7230::Gf_getDIOJigTilting()
{
	U32 dio_in;

	dio_in = Dio_DI_ReadPort();

	if (DEBUG_PALLET_ARRIVE == 1)
		return true;

	if (dio_in & DI_START_READY)
	{
		m_pApp->Gf_writeLogData("<DIO>", "Input Tilting ON");
		return true;
	}
	return false;
}

bool CDIO7230::Gf_getDIOTestStart()
{
	U32 dio_in;

	dio_in = Dio_DI_ReadPort();

	if (DEBUG_DIO_SKIP)
	{
		return true;
	}

	if ((dio_in & DI_TEST_SWITCH1) && (dio_in & DI_TEST_SWITCH2))
	{
		m_pApp->Gf_writeLogData("<DIO>", "Input Start Switch 1,2 ON");
		return true;
	}
	return false;
}

bool CDIO7230::Gf_getDIOJudgeOK()
{
	U32 dio_in;

	dio_in = Dio_DI_ReadPort();

	if (DEBUG_DIO_SKIP)
	{
		return true;
	}

	if (dio_in & DI_PANEL_OUT_OK)
	{
		m_pApp->Gf_writeLogData("<DIO>", "Input OK Button ON");
		return true;
	}
	return false;
}

bool CDIO7230::Gf_getDIOJudgeNG()
{
	U32 dio_in;

	dio_in = Dio_DI_ReadPort();

	if (DEBUG_DIO_SKIP)
	{
		return true;
	}

	if (dio_in & DI_PANEL_OUT_NG)
	{
		m_pApp->Gf_writeLogData("<DIO>", "Input NG Button ON");
		return true;
	}
	return false;
}

void CDIO7230::Gf_getDioGetInput()
{
	BYTE readValue = 0;
	readValue = (BYTE)Dio_DI_ReadPort();
	Lf_setDioFlow(readValue);
}

void CDIO7230::Lf_setDioFlow(BYTE newReadVal)
{
	if (newReadVal & JIG_ARRIVE)
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

	if (newReadVal & TEST_START)
	{
		if (lpWorkInfo->m_bDioTestStart == false)
		{
			lpWorkInfo->m_bDioTestStart = true;
		}
	}
	else
	{
		lpWorkInfo->m_bDioTestStart = false;
	}

	if (newReadVal & JUDGE_OK)
	{
		if (lpWorkInfo->m_bDioJudgeOk == false && lpWorkInfo->m_bIsEdidFail == false)
		{
			//Pattern Test 진행 중에는 판정 OK, NG 버튼은 무시한다. Fast Judge의 경우 제외.
//imsi			if (pUiPorc->comm.curData.iStartTest != SEQ_PTN_TEST_START || lpSystemInfo->m_nFastDioJudge == TRUE)
			{
				lpWorkInfo->m_bDioJudgeOk = true;
			}
		}
	}
	else
	{
		lpWorkInfo->m_bDioJudgeOk = false;
	}

	if (newReadVal & START_SW1)
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

	if (newReadVal & START_SW2)
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

	if (newReadVal & JUDGE_NG)
	{
		if (lpWorkInfo->m_bDioJudgeNg == false)
		{
			lpWorkInfo->m_bDioJudgeNg = true;
		}
	}
	else
	{
		lpWorkInfo->m_bDioJudgeNg = false;
	}

	if (newReadVal & PASSMODE)
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
