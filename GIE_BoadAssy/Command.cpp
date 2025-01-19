// CCommand.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GIE_BoadAssy.h"
#include "T2CmdGen.h"
#include "Command.h"
#include "MessageError.h"

// CCommand
IMPLEMENT_DYNAMIC(CCommand, CWnd)

CCommand::CCommand()
{
	lpSystemInfo	= m_pApp->GetSystemInfo();
	lpModelInfo		= m_pApp->GetModelInfo();
	lpWorkInfo		= m_pApp->GetWorkInfo();
}

CCommand::~CCommand()
{
}


BEGIN_MESSAGE_MAP(CCommand, CWnd)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// eDP 1.4 Bridge보드에 CMD전송을 위한 함수.
BOOL CCommand::Gf_setPacketSendGfd250(BYTE nTarget, BYTE nMSCmd, BYTE nId, BYTE nCmd, int nLength, char* pData, BOOL Ack)
{
	int target=0;
	int datalen=0;
	int packetlen=0;
	BYTE nChkSum=0;
	char szbuff[5]={0,};
	char sendPacket[4096]={0,};

	datalen = nLength;

	// data 앞까지 Packet 생성
	sprintf_s(sendPacket, "%cA1%02X%02X%02X%02X%04X", PACKET_STX, TARGET_GFD250, nId, nMSCmd, nCmd, datalen);

	// data를 포함하여 packet 생성. hex로 전송할 data가 있으므로 memcpy를 사용
	packetlen = (int)strlen(sendPacket);
	memcpy(&sendPacket[packetlen], pData, datalen);

	// data 를 포함한 packet의 길이를 구한다.
	packetlen += datalen;

	// 생성된 Packet을 이용하여 CheckSum을 구한다.
	for(int j=1; j<packetlen; j++)		// Check Sum
	{
		nChkSum += sendPacket[j];
	}
	sprintf_s(szbuff, "%02X%c", nChkSum, 0x03);

	// Checksum과 ETX 3byte를 붙여 다시 Packet을 만든다.
	memcpy(&sendPacket[packetlen], szbuff, 3);
	packetlen += 3;

	// Packet의 마지막에 String의 끝을 알리기 위하여 NULL을 추가한다.
	sendPacket[packetlen] = 0x00;

	m_pApp->m_nRcvGfd250Msg = 0;

	m_pApp->Gf_sendGfd250Data((BYTE*)sendPacket, packetlen);	

	if (Ack == TRUE)
	{
		delayMS(200);
		return TRUE;
	}
	int nRecCnt=0;
	while(1)
	{
		if(m_pApp->m_nRcvGfd250Msg == nCmd)	
			break;

		if(nRecCnt++ > 100)					
			return FALSE;
		delayMS(50);
	}

	return TRUE;
}
BOOL CCommand::Gf_setBluDuty(int Duty)
{
	int nRecCnt = 0;
	char szpacket[512];
	int packetlen;

	sprintf_s(szpacket, "B0%04d%c", Duty, 0x0d);
	packetlen = (int)strlen(szpacket);

	m_pApp->m_nRcvMsgBlu = 0x00;

	m_pApp->Gf_sendBLUData((BYTE*)szpacket, packetlen);
	if (DEBUG_UDP_RECEIVE_OK == 0)
	{
		nRecCnt = 0;
		while (1)
		{
			if (m_pApp->m_nRcvMsgBlu == TRUE)
				break;
			if (nRecCnt++ > 30)
				return FALSE;
			delayMS(10);
		}
	}

	sprintf_s(szpacket, "L1%c", 0x0d);
	packetlen = (int)strlen(szpacket);

	m_pApp->m_nRcvMsgBlu = 0x00;

	m_pApp->Gf_sendBLUData((BYTE*)szpacket, packetlen);
	if (DEBUG_UDP_RECEIVE_OK == 0)
	{
		nRecCnt = 0;
		while (1)
		{
			if (m_pApp->m_nRcvMsgBlu == TRUE)
				break;
			if (nRecCnt++ > 30)
				return FALSE;
			delayMS(10);
		}
	}

	return TRUE;
}
BOOL CCommand::Gf_setBluOnOff(BOOL onoff)
{
	char szpacket[512];
	int packetlen;

	sprintf_s(szpacket, "L%01d%c", onoff, 0x0d);
	packetlen = (int)strlen(szpacket);

	m_pApp->m_nRcvMsgBlu = 0x00;

	m_pApp->Gf_sendBLUData((BYTE*)szpacket, packetlen);
	int nRecCnt = 0;
	while (1)
	{
		if (m_pApp->m_nRcvMsgBlu == TRUE)
			break;
		if (nRecCnt++ > 30)
			return FALSE;
		delayMS(10);
	}

	return TRUE;
}
/////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CCommand::Lf_makeSystemFusingData(char* packet)
{
	CString makePacket = _T("");
	CString sdata = _T("");
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	int nInterface = 0;
	int nMode = 0;
	int nBitsSwap = lpModelInfo->m_nLcmInfoBitsSwap << 5;
	int nHsyncPolarity = lpModelInfo->m_nHSyncPolarity<<1;
	int nVsyncPolarity = lpModelInfo->m_nVSyncPolarity;

	sdata.Format(_T("INFO"));														makePacket.Append(sdata);

	if(lpModelInfo->m_nPixelType == SINGLE)			nInterface=0;
	else if(lpModelInfo->m_nPixelType == DUAL)		nInterface=1;
	else if(lpModelInfo->m_nPixelType == QUAD)		nInterface=2;

	sdata.Format(_T("%02X"), (nInterface | nBitsSwap));								makePacket.Append(sdata);	// MODE
	sdata.Format(_T("%01X"), (nHsyncPolarity | nVsyncPolarity));					makePacket.Append(sdata);	// Polarity
	sdata.Format(_T("%04d"), lpModelInfo->m_nTimingHorActive);						makePacket.Append(sdata);	// H Active
	sdata.Format(_T("%04d"), lpModelInfo->m_nTimingVerActive);						makePacket.Append(sdata);	// V Active

	float fMclock = lpModelInfo->m_fTimingFreq;
	if (lpModelInfo->m_nSignalType == SIGNAL_TYPE_DP)	// DP Type 일때 MCLOCK/2
	{
		fMclock = lpModelInfo->m_fTimingFreq / 2;
	}
	if (lpModelInfo->m_nPixelType == SINGLE)
	{
		sdata.Format(_T("%06.2f"), fMclock);										makePacket.Append(sdata);	// M Clock
	}
	else if (lpModelInfo->m_nPixelType == DUAL)
	{
		sdata.Format(_T("%06.2f"), fMclock / 2.f);									makePacket.Append(sdata);	// M Clock
	}
	else if (lpModelInfo->m_nPixelType == QUAD)
	{
		sdata.Format(_T("%06.2f"), fMclock / 4.f);									makePacket.Append(sdata);	// M Clock
	}

	sdata.Format(_T("%04d"), lpModelInfo->m_nTimingHorWidth);						makePacket.Append(sdata);	// H Width
	sdata.Format(_T("%04d"), lpModelInfo->m_nTimingHorFront_P);						makePacket.Append(sdata);	// H Front P
	sdata.Format(_T("%04d"), lpModelInfo->m_nTimingHorBack_P);						makePacket.Append(sdata);	// H Back P

	sdata.Format(_T("%04d"), lpModelInfo->m_nTimingVerWidth);						makePacket.Append(sdata);	// V Width
	sdata.Format(_T("%04d"), lpModelInfo->m_nTimingVerFront_P);						makePacket.Append(sdata);	// V Front P
	sdata.Format(_T("%04d"), lpModelInfo->m_nTimingVerBack_P);						makePacket.Append(sdata);	// V Back P

	sdata.Format(_T("%01d"), lpModelInfo->m_nSignalType);							makePacket.Append(sdata);	// Signal Type
	sdata.Format(_T("%01d"), lpModelInfo->m_nSignalBit);							makePacket.Append(sdata);	// Signal Bit
	sdata.Format(_T("%01d"), lpModelInfo->m_nPixelType);							makePacket.Append(sdata);	// Pixel Type
	sdata.Format(_T("%01d"), lpModelInfo->m_nOddEven);								makePacket.Append(sdata);	// ODD/EVEN
	sdata.Format(_T("%01d"), lpModelInfo->m_nClockRising);							makePacket.Append(sdata);	// Clock Rising
	sdata.Format(_T("%04d"), lpModelInfo->m_nClockDelay);							makePacket.Append(sdata);	// Clock Delay

	sdata.Format(_T("%05d"), (int)(lpModelInfo->m_fVoltVcc * 1000 + 0.5));			makePacket.Append(sdata);	// Vcc
	sdata.Format(_T("%05d"), (int)(lpModelInfo->m_fVoltVdd * 1000 + 0.5));			makePacket.Append(sdata);	// Vdd
	sdata.Format(_T("%05d"), (int)(lpModelInfo->m_fVoltVbl * 1000 + 0.5));			makePacket.Append(sdata);	// Vbl
	sdata.Format(_T("%05d"), (int)(lpModelInfo->m_fVoltVgh * 1000 + 0.5));			makePacket.Append(sdata);	// Vgh
	sdata.Format(_T("%05d"), (int)(lpModelInfo->m_fVoltVgl * 1000 + 0.5));			makePacket.Append(sdata);	// Vgl
	sdata.Format(_T("%05d"), (int)(lpModelInfo->m_fVoltVbr * 1000 + 0.5));			makePacket.Append(sdata);	// Vbr
	sdata.Format(_T("%05d"), (int)(lpModelInfo->m_fVoltVcom1 * 1000 + 0.5));		makePacket.Append(sdata);	// VCOM1
	sdata.Format(_T("%05d"), (int)(lpModelInfo->m_fVoltVcom2 * 1000 + 0.5));		makePacket.Append(sdata);	// VCOM2

	// gamma
	for (int i = 0; i < 32; i++)
	{
		sdata.Format(_T("%05d"), (int)(lpModelInfo->m_fVoltGamma[i] * 1000 + 0.5));		makePacket.Append(sdata);	// VCOM2
	}

	sdata.Format(_T("%05d"), (int)(lpModelInfo->m_fLimitVccMin * 1000 + 0.5));		makePacket.Append(sdata);	// Vcc low
	sdata.Format(_T("%05d"), (int)(lpModelInfo->m_fLimitVccMax * 1000 + 0.5));		makePacket.Append(sdata);	// Vcc high
	sdata.Format(_T("%05d"), (int)(lpModelInfo->m_fLimitVddMin * 1000 + 0.5));		makePacket.Append(sdata);	// Vdd low
	sdata.Format(_T("%05d"), (int)(lpModelInfo->m_fLimitVddMax * 1000 + 0.5));		makePacket.Append(sdata);	// Vdd high
	sdata.Format(_T("%05d"), (int)(lpModelInfo->m_fLimitVblMin * 1000 + 0.5));		makePacket.Append(sdata);	// Vbl low
	sdata.Format(_T("%05d"), (int)(lpModelInfo->m_fLimitVblMax * 1000 + 0.5));		makePacket.Append(sdata);	// Vbl high
	sdata.Format(_T("%05d"), (int)(lpModelInfo->m_fLimitVghMin * 1000 + 0.5));		makePacket.Append(sdata);	// Vgh low
	sdata.Format(_T("%05d"), (int)(lpModelInfo->m_fLimitVghMax * 1000 + 0.5));		makePacket.Append(sdata);	// Vgh high
	sdata.Format(_T("%05d"), (int)(lpModelInfo->m_fLimitVglMin * 1000 + 0.5));		makePacket.Append(sdata);	// Vgl low
	sdata.Format(_T("%05d"), (int)(lpModelInfo->m_fLimitVglMax * 1000 + 0.5));		makePacket.Append(sdata);	// Vgl high
	sdata.Format(_T("%05d"), (int)(lpModelInfo->m_fLimitIccMin * 1000 + 0.5));		makePacket.Append(sdata);	// Icc low
	sdata.Format(_T("%05d"), (int)(lpModelInfo->m_fLimitIccMax * 1000 + 0.5));		makePacket.Append(sdata);	// Icc high
	sdata.Format(_T("%05d"), (int)(lpModelInfo->m_fLimitIddMin * 1000 + 0.5));		makePacket.Append(sdata);	// Idd low
	sdata.Format(_T("%05d"), (int)(lpModelInfo->m_fLimitIddMax * 1000 + 0.5));		makePacket.Append(sdata);	// Idd high
	sdata.Format(_T("%05d"), (int)(lpModelInfo->m_fLimitIblMin * 1000 + 0.5));		makePacket.Append(sdata);	// Ibl low
	sdata.Format(_T("%05d"), (int)(lpModelInfo->m_fLimitIblMax * 1000 + 0.5));		makePacket.Append(sdata);	// Ibl high
	sdata.Format(_T("%05d"), (int)(lpModelInfo->m_fLimitIghMin * 1000 + 0.5));		makePacket.Append(sdata);	// Igh low
	sdata.Format(_T("%05d"), (int)(lpModelInfo->m_fLimitIghMax * 1000 + 0.5));		makePacket.Append(sdata);	// Igh high
	sdata.Format(_T("%05d"), (int)(lpModelInfo->m_fLimitIglMin * 1000 + 0.5));		makePacket.Append(sdata);	// Igl low
	sdata.Format(_T("%05d"), (int)(lpModelInfo->m_fLimitIglMax * 1000 + 0.5));		makePacket.Append(sdata);	// Igl high

	// Power On Sequence
	sdata.Format(_T("%02d"), lpModelInfo->m_nPowerOnSeqType01);						makePacket.Append(sdata);	// Power On Seq Type 1
	sdata.Format(_T("%02d"), lpModelInfo->m_nPowerOnSeqType02);						makePacket.Append(sdata);	// Power On Seq Type 2
	sdata.Format(_T("%02d"), lpModelInfo->m_nPowerOnSeqType03);						makePacket.Append(sdata);	// Power On Seq Type 3
	sdata.Format(_T("%02d"), lpModelInfo->m_nPowerOnSeqType04);						makePacket.Append(sdata);	// Power On Seq Type 4
	sdata.Format(_T("%02d"), lpModelInfo->m_nPowerOnSeqType05);						makePacket.Append(sdata);	// Power On Seq Type 5
	sdata.Format(_T("%02d"), lpModelInfo->m_nPowerOnSeqType06);						makePacket.Append(sdata);	// Power On Seq Type 6
	sdata.Format(_T("%02d"), lpModelInfo->m_nPowerOnSeqType07);						makePacket.Append(sdata);	// Power On Seq Type 7
	sdata.Format(_T("%02d"), lpModelInfo->m_nPowerOnSeqType08);						makePacket.Append(sdata);	// Power On Seq Type 8
	sdata.Format(_T("%02d"), lpModelInfo->m_nPowerOnSeqType09);						makePacket.Append(sdata);	// Power On Seq Type 9
	sdata.Format(_T("%02d"), lpModelInfo->m_nPowerOnSeqType10);						makePacket.Append(sdata);	// Power On Seq Type 10
	sdata.Format(_T("%02d"), lpModelInfo->m_nPowerOnSeqType11);						makePacket.Append(sdata);	// Power On Seq Type 11
	sdata.Format(_T("%02d"), lpModelInfo->m_nPowerOnSeqType12);						makePacket.Append(sdata);	// Power On Seq Type 12
	sdata.Format(_T("%02d"), lpModelInfo->m_nPowerOnSeqType13);						makePacket.Append(sdata);	// Power On Seq Type 13
	sdata.Format(_T("%02d"), lpModelInfo->m_nPowerOnSeqType14);						makePacket.Append(sdata);	// Power On Seq Type 14
	sdata.Format(_T("%02d"), lpModelInfo->m_nPowerOnSeqType15);						makePacket.Append(sdata);	// Power On Seq Type
	sdata.Format(_T("%02d"), lpModelInfo->m_nPowerOnSeqType16);						makePacket.Append(sdata);	// Power On Seq Type
	sdata.Format(_T("%02d"), lpModelInfo->m_nPowerOnSeqType17);						makePacket.Append(sdata);	// Power On Seq Type

	sdata.Format(_T("%04d"), lpModelInfo->m_nPowerOnSeqDelay01);					makePacket.Append(sdata);	// Power On Seq Delay 1
	sdata.Format(_T("%04d"), lpModelInfo->m_nPowerOnSeqDelay02);					makePacket.Append(sdata);	// Power On Seq Delay 2
	sdata.Format(_T("%04d"), lpModelInfo->m_nPowerOnSeqDelay03);					makePacket.Append(sdata);	// Power On Seq Delay 3
	sdata.Format(_T("%04d"), lpModelInfo->m_nPowerOnSeqDelay04);					makePacket.Append(sdata);	// Power On Seq Delay 4
	sdata.Format(_T("%04d"), lpModelInfo->m_nPowerOnSeqDelay05);					makePacket.Append(sdata);	// Power On Seq Delay 5
	sdata.Format(_T("%04d"), lpModelInfo->m_nPowerOnSeqDelay06);					makePacket.Append(sdata);	// Power On Seq Delay 6
	sdata.Format(_T("%04d"), lpModelInfo->m_nPowerOnSeqDelay07);					makePacket.Append(sdata);	// Power On Seq Delay 7
	sdata.Format(_T("%04d"), lpModelInfo->m_nPowerOnSeqDelay08);					makePacket.Append(sdata);	// Power On Seq Delay 8
	sdata.Format(_T("%04d"), lpModelInfo->m_nPowerOnSeqDelay09);					makePacket.Append(sdata);	// Power On Seq Delay 9
	sdata.Format(_T("%04d"), lpModelInfo->m_nPowerOnSeqDelay10);					makePacket.Append(sdata);	// Power On Seq Delay 10
	sdata.Format(_T("%04d"), lpModelInfo->m_nPowerOnSeqDelay11);					makePacket.Append(sdata);	// Power On Seq Delay 11
	sdata.Format(_T("%04d"), lpModelInfo->m_nPowerOnSeqDelay12);					makePacket.Append(sdata);	// Power On Seq Delay 12
	sdata.Format(_T("%04d"), lpModelInfo->m_nPowerOnSeqDelay13);					makePacket.Append(sdata);	// Power On Seq Delay 13
	sdata.Format(_T("%04d"), lpModelInfo->m_nPowerOnSeqDelay14);					makePacket.Append(sdata);	// Power On Seq Delay 14
	sdata.Format(_T("%04d"), lpModelInfo->m_nPowerOnSeqDelay15);					makePacket.Append(sdata);	// Power On Seq Delay
	sdata.Format(_T("%04d"), lpModelInfo->m_nPowerOnSeqDelay16);					makePacket.Append(sdata);	// Power On Seq Delay
	sdata.Format(_T("%04d"), lpModelInfo->m_nPowerOnSeqDelay17);					makePacket.Append(sdata);	// Power On Seq Delay

	// Power Off Sequence
	sdata.Format(_T("%02d"), lpModelInfo->m_nPowerOffSeqType01);					makePacket.Append(sdata);	// Power Off Seq Type 1
	sdata.Format(_T("%02d"), lpModelInfo->m_nPowerOffSeqType02);					makePacket.Append(sdata);	// Power Off Seq Type 2
	sdata.Format(_T("%02d"), lpModelInfo->m_nPowerOffSeqType03);					makePacket.Append(sdata);	// Power Off Seq Type 3
	sdata.Format(_T("%02d"), lpModelInfo->m_nPowerOffSeqType04);					makePacket.Append(sdata);	// Power Off Seq Type 4
	sdata.Format(_T("%02d"), lpModelInfo->m_nPowerOffSeqType05);					makePacket.Append(sdata);	// Power Off Seq Type 5
	sdata.Format(_T("%02d"), lpModelInfo->m_nPowerOffSeqType06);					makePacket.Append(sdata);	// Power Off Seq Type 6
	sdata.Format(_T("%02d"), lpModelInfo->m_nPowerOffSeqType07);					makePacket.Append(sdata);	// Power Off Seq Type 7
	sdata.Format(_T("%02d"), lpModelInfo->m_nPowerOffSeqType08);					makePacket.Append(sdata);	// Power Off Seq Type 8
	sdata.Format(_T("%02d"), lpModelInfo->m_nPowerOffSeqType09);					makePacket.Append(sdata);	// Power Off Seq Type 9
	sdata.Format(_T("%02d"), lpModelInfo->m_nPowerOffSeqType10);					makePacket.Append(sdata);	// Power Off Seq Type 10
	sdata.Format(_T("%02d"), lpModelInfo->m_nPowerOffSeqType11);					makePacket.Append(sdata);	// Power Off Seq Type 11
	sdata.Format(_T("%02d"), lpModelInfo->m_nPowerOffSeqType12);					makePacket.Append(sdata);	// Power Off Seq Type 12
	sdata.Format(_T("%02d"), lpModelInfo->m_nPowerOffSeqType13);					makePacket.Append(sdata);	// Power Off Seq Type 13
	sdata.Format(_T("%02d"), lpModelInfo->m_nPowerOffSeqType14);					makePacket.Append(sdata);	// Power Off Seq Type 14
	sdata.Format(_T("%02d"), lpModelInfo->m_nPowerOffSeqType15);					makePacket.Append(sdata);	// Power Off Seq Type
	sdata.Format(_T("%02d"), lpModelInfo->m_nPowerOffSeqType16);					makePacket.Append(sdata);	// Power Off Seq Type
	sdata.Format(_T("%02d"), lpModelInfo->m_nPowerOffSeqType17);					makePacket.Append(sdata);	// Power Off Seq Type

	sdata.Format(_T("%04d"), lpModelInfo->m_nPowerOffSeqDelay01);					makePacket.Append(sdata);	// Power Off Seq Delay 1
	sdata.Format(_T("%04d"), lpModelInfo->m_nPowerOffSeqDelay02);					makePacket.Append(sdata);	// Power Off Seq Delay 2
	sdata.Format(_T("%04d"), lpModelInfo->m_nPowerOffSeqDelay03);					makePacket.Append(sdata);	// Power Off Seq Delay 3
	sdata.Format(_T("%04d"), lpModelInfo->m_nPowerOffSeqDelay04);					makePacket.Append(sdata);	// Power Off Seq Delay 4
	sdata.Format(_T("%04d"), lpModelInfo->m_nPowerOffSeqDelay05);					makePacket.Append(sdata);	// Power Off Seq Delay 5
	sdata.Format(_T("%04d"), lpModelInfo->m_nPowerOffSeqDelay06);					makePacket.Append(sdata);	// Power Off Seq Delay 6
	sdata.Format(_T("%04d"), lpModelInfo->m_nPowerOffSeqDelay07);					makePacket.Append(sdata);	// Power Off Seq Delay 7
	sdata.Format(_T("%04d"), lpModelInfo->m_nPowerOffSeqDelay08);					makePacket.Append(sdata);	// Power Off Seq Delay 8
	sdata.Format(_T("%04d"), lpModelInfo->m_nPowerOffSeqDelay09);					makePacket.Append(sdata);	// Power Off Seq Delay 9
	sdata.Format(_T("%04d"), lpModelInfo->m_nPowerOffSeqDelay10);					makePacket.Append(sdata);	// Power Off Seq Delay 10
	sdata.Format(_T("%04d"), lpModelInfo->m_nPowerOffSeqDelay11);					makePacket.Append(sdata);	// Power Off Seq Delay 11
	sdata.Format(_T("%04d"), lpModelInfo->m_nPowerOffSeqDelay12);					makePacket.Append(sdata);	// Power Off Seq Delay 12
	sdata.Format(_T("%04d"), lpModelInfo->m_nPowerOffSeqDelay13);					makePacket.Append(sdata);	// Power Off Seq Delay 13
	sdata.Format(_T("%04d"), lpModelInfo->m_nPowerOffSeqDelay14);					makePacket.Append(sdata);	// Power Off Seq Delay 14
	sdata.Format(_T("%04d"), lpModelInfo->m_nPowerOffSeqDelay15);					makePacket.Append(sdata);	// Power Off Seq Delay
	sdata.Format(_T("%04d"), lpModelInfo->m_nPowerOffSeqDelay16);					makePacket.Append(sdata);	// Power Off Seq Delay
	sdata.Format(_T("%04d"), lpModelInfo->m_nPowerOffSeqDelay17);					makePacket.Append(sdata);	// Power Off Seq Delay

	sdata.Format(_T("%01d"), 0);													makePacket.Append(sdata);	// LED Type
	sdata.Format(_T("%05d"), 0);													makePacket.Append(sdata);	// LED Ovp
	sdata.Format(_T("%03d"), 0);													makePacket.Append(sdata);	// LED ISet
	sdata.Format(_T("%01d"), 0);													makePacket.Append(sdata);	// Cable Open Check (Chamber용)
	sdata.Format(_T("%05d"), lpModelInfo->m_nPwmFreq);								makePacket.Append(sdata);	// PWM Freq
	sdata.Format(_T("%03d"), lpModelInfo->m_nPwmDuty);								makePacket.Append(sdata);	// PWM Duty
	sdata.Format(_T("%01d"), lpModelInfo->m_nI2cLevel);								makePacket.Append(sdata);	// I2C Level 
	sdata.Format(_T("%01d"), lpModelInfo->m_nI2cPullup);							makePacket.Append(sdata);	// I2C PullUP
	sdata.Format(_T("%03d"), 100);													makePacket.Append(sdata);	// I2C Clock (Khz)

	if (lpModelInfo->m_nPixelOverlapMode == FALSE)
	{
		sdata.Format(_T("%01d"), 0);												makePacket.Append(sdata);	// Pixel Overlap Mode, 0=1:1출력, 1=2분할 모드, 2=OverlapMode
	}
	else
	{
		sdata.Format(_T("%01d"), 2);												makePacket.Append(sdata);	// Pixel Overlap Mode, 0=1:1출력, 1=2분할 모드, 2=OverlapMode
	}
	sdata.Format(_T("%03d"), 4);													makePacket.Append(sdata);	// Pixel Overlap Count, 일단은 16인치 4Pixel 모델만 있다. 향후 필요시 옵션 추가한다.

	wchar_To_char(makePacket.GetBuffer(), packet);
}



BOOL CCommand::Gf_setFusingSystemInfo()
{
	BOOL bRet=FALSE;
	int length=0;
	char szPacket[4096]={0,};

	Lf_makeSystemFusingData(szPacket);
	length = (int)strlen(szPacket);

	bRet = m_pApp->udp_sendPacket(UDP_MAIN_IP, TARGET_CTRL, CMD_CTRL_FUSING_SYSTEM, length, szPacket);

	return bRet;
}
BOOL CCommand::Gf_setPGInfoPatternString(CString strPtnPacket, BOOL Ack)
{
	BOOL bRet = FALSE;
	int length = 0;
	char szPacket[4096] = { 0, };
	wchar_To_char(strPtnPacket.GetBuffer(0), szPacket);
	length = (int)strlen(szPacket);

	bRet = m_pApp->udp_sendPacket(UDP_MAIN_IP, TARGET_CTRL, CMD_T2PTN_SEND, length, szPacket, Ack);

	return bRet;
}
BOOL CCommand::Gf_setGFD250InfoPatternString(CString strPtnPacket, BOOL Ack)
{
	BOOL bRet = FALSE;
	int length = 0;
	char szPacket[4096] = { 0, };
	wchar_To_char(strPtnPacket.GetBuffer(0), szPacket);
	length = (int)strlen(szPacket);

	bRet = Gf_setPacketSendGfd250(TARGET_GFD250, PG_CMD, 0x00, CMD_T2PTN_SEND, length, szPacket);

	return bRet;
}
CString CCommand::MakeT2PtnDataGFD250(CString strPtnName, BOOL bHotKeyFlags, BOOL bHkeyFlags)
{
	int nFG=0, nIndex=0;
	CString lpData=_T("");
	CString strTmp=_T("");
	CString strFG=_T("");

	lpData.Empty();
	strTmp.Empty();
	strFG.Empty();

	strTmp = CT2CmdGen::makeT2dataStrFromFile(strPtnName);
	strTmp = CT2CmdGen::makeT2PatternStr(strTmp, lpModelInfo->m_nTimingHorActive, lpModelInfo->m_nTimingVerActive);

	lpData = strTmp;
#if 0
	nIndex = lpData.Find(_T("CBT"), 0);

	nFG = _ttoi(lpModelInfo->m_sLbPtnFg[*m_pApp->pPtnIndex]);

	switch(lpModelInfo->m_nSignalBit)
	{
	case 0: // 6bit
		nFG <<= 10;
		nFG |= 0x03FF;
		break;
	case 1: // 8bit
		nFG <<= 8;
		nFG |= 0x00FF;
		break;
	case 2: // 10bit
		nFG <<= 6;
		nFG |= 0x003F;
		break;
	case 3: // 12bit
		nFG <<= 4;
		nFG |= 0x000F;
		break;
	}

	if(nIndex != -1)//패턴 파일에 CBT가 있으면 아래 내용을 수행 한다.
	{
		strFG.Format(_T("%04X%04X%04X"), nFG,nFG,nFG);
		lpData.Delete(nIndex+3, 12);
		lpData.Insert(nIndex+3, strFG);	
	}

	if(!strPtnName.Compare(_T("RED")) || !strPtnName.Compare(_T("GREEN")) || !strPtnName.Compare(_T("BLUE")) || !strPtnName.Compare(_T("GRAY"))
		||!strPtnName.Compare(_T("RECTAREA")) || !strPtnName.Compare(_T("GRAYBLOCK")) || !strPtnName.Compare(_T("CHESS")) || !strPtnName.Compare(_T("MOSAIC")))
	{
		lpData = Lf_ModifyPtn_RGB(strPtnName, lpData, 0, bHotKeyFlags);
	}
#endif // 0
	return lpData;
}

CString CCommand::MakeT2PtnFusingData(CString strPtnName, BOOL bHotKeyFlags, BOOL bHkeyFlags)
{
	int nFG=0, nIndex=0;
	CString lpData=_T("");
	CString strTmp=_T("");
	CString strFG=_T("");

	lpData.Empty();
	strTmp.Empty();
	strFG.Empty();

	strTmp = CT2CmdGen::makeT2dataStrFromFile(strPtnName);
	strTmp = CT2CmdGen::makeT2PatternStr(strTmp, lpModelInfo->m_nTimingHorActive, lpModelInfo->m_nTimingVerActive);

	lpData = strTmp;
#if 0


	nIndex = lpData.Find(_T("CBT"), 0);

	nFG = _ttoi(lpModelInfo->m_sLbPtnFg[*m_pApp->pPtnIndex]);

	switch(lpModelInfo->m_nSignalBit)
	{
	case 0: // 6bit
		nFG <<= 10;
		nFG |= 0x03FF;
		break;
	case 1: // 8bit
		nFG <<= 8;
		nFG |= 0x00FF;
		break;
	case 2: // 10bit
		nFG <<= 6;
		nFG |= 0x003F;
		break;
	case 3: // 12bit
		nFG <<= 4;
		nFG |= 0x000F;
		break;
	}

	if(nIndex != -1)//패턴 파일에 CBT가 있으면 아래 내용을 수행 한다.
	{
		strFG.Format(_T("%04X%04X%04X"), nFG,nFG,nFG);
		lpData.Delete(nIndex+3, 12);
		lpData.Insert(nIndex+3, strFG);	
	}

	if(!strPtnName.Compare(_T("RED")) || !strPtnName.Compare(_T("GREEN")) || !strPtnName.Compare(_T("BLUE")) || !strPtnName.Compare(_T("GRAY"))
	 ||!strPtnName.Compare(_T("RECTAREA")) || !strPtnName.Compare(_T("GRAYBLOCK")) || !strPtnName.Compare(_T("CHESS")) || !strPtnName.Compare(_T("MOSAIC")))
	{
		lpData = Lf_ModifyPtn_RGB(strPtnName, lpData, 0, bHotKeyFlags);
	}

	int nMainClk = 0;
	float fMainClk = 0.f;
	nMainClk = lpModelInfo->m_nTimingHorTotal * lpModelInfo->m_nTimingVerTotal * _ttoi(lpModelInfo->m_sLbPtnVsync[*m_pApp->pPtnIndex]);

	if(lpModelInfo->m_nLcmInfoInterface == 1)// Dual
	{
		nMainClk/=2;
	}
	else if(lpModelInfo->m_nLcmInfoInterface == 0) // Quad
	{
		nMainClk/=4;
	}

	int nNewVsync = _ttoi(lpModelInfo->m_sLbPtnVsync[*m_pApp->pPtnIndex]);	

	if(lpModelInfo->m_nGfd100Use == TRUE)
	{
		if(m_pApp->m_nOldVsync != nNewVsync)
		{
			m_pApp->m_nOldVsync = nNewVsync;
			fMainClk = float((float)nMainClk * 0.000001);
			strTmp.Format(_T("DCLK%06.2f%s"),fMainClk, lpData);
			lpData.Format(_T("%s"), strTmp);
		}
	}
	else
	{
		if(m_pApp->m_nOldVsync != nNewVsync)
		{
			m_pApp->m_nOldVsync = nNewVsync;
			fMainClk = float((float)nMainClk * 0.000001);
			strTmp.Format(_T("DCLK%06.2f%s"),fMainClk, lpData);
			lpData.Format(_T("%s"), strTmp);
		}
	}

#endif // 0
	return lpData;
}

CString CCommand::Lf_ModifyPtn_RGB(CString strPtnName, CString lpData, int nPtnIndex, BOOL bHotKeyEnable)
{
	CString strGray=_T("");

	if(!strPtnName.Compare(_T("RED")))
	{
		m_pApp->m_nGrayRed = 0xFFFF;
		m_pApp->m_nGrayGreen = 0;
		m_pApp->m_nGrayBlue = 0;
	}
	else if(!strPtnName.Compare(_T("GREEN")))
	{
		m_pApp->m_nGrayRed = 0;
		m_pApp->m_nGrayGreen = 0xFFFF;
		m_pApp->m_nGrayBlue = 0;
	}
	else if(!strPtnName.Compare(_T("BLUE")))
	{
		m_pApp->m_nGrayRed = 0;
		m_pApp->m_nGrayGreen = 0;
		m_pApp->m_nGrayBlue = 0xFFFF;
	}
	else
	{
		m_pApp->m_nGrayRed = 0xFFFF;
		m_pApp->m_nGrayGreen = 0xFFFF;
		m_pApp->m_nGrayBlue = 0xFFFF;
	}

	int nFindIndex = 0;
	int nCnt = 0;
	if(!strPtnName.Compare(_T("RED")) || !strPtnName.Compare(_T("GREEN")) || !strPtnName.Compare(_T("BLUE"))|| !strPtnName.Compare(_T("GRAY")))
	{
		lpData.Delete(12, 1);
		lpData.Insert(12, _T("9"));
	}
	while(TRUE)
	{
		nFindIndex = lpData.Find(_T(","), nFindIndex+1);
		nCnt++;
		if(nCnt==5) break;
	}

	if(bHotKeyEnable == TRUE)
	{
		//		m_pApp->m_nGrayValueFg = lpSystemInfo->m_nHotPtnFg[m_pApp->nHotKeyIndex];
		//		m_pApp->m_nGrayValueBg = lpSystemInfo->m_nHotPtnBg[m_pApp->nHotKeyIndex];
	}
	else
	{
		//m_pApp->m_nGrayValueFg = _ttoi(lpModelInfo->m_sLbPtnFg[*m_pApp->pPtnIndex]);
		//m_pApp->m_nGrayValueBg = _ttoi(lpModelInfo->m_sLbPtnBg[*m_pApp->pPtnIndex]);
	}

	short int snFgBitCalc, snBgBitCalc;
	snFgBitCalc = m_pApp->m_nGrayValueFg;
	snBgBitCalc = m_pApp->m_nGrayValueBg;

	switch(lpModelInfo->m_nSignalBit)
	{
	case SIG_6BIT:
		if(snFgBitCalc>63){ snFgBitCalc = 63; }
		snFgBitCalc <<= 10;
		snFgBitCalc |= 0x0FFF;

		if(snBgBitCalc>63){ snBgBitCalc = 63; }
		snBgBitCalc <<= 10;
		snBgBitCalc |= 0x0FFF;

		break;
	case SIG_8BIT:
		if(snFgBitCalc>255){ snFgBitCalc = 255; }
		snFgBitCalc <<= 8;
		snFgBitCalc |= 0x00FF;

		if(snBgBitCalc>255){ snBgBitCalc = 255; }
		snBgBitCalc <<= 8;
		snBgBitCalc |= 0x00FF;

		break;
	case SIG_10BIT:
		if(snFgBitCalc>1023){ snFgBitCalc = 1023; }
		snFgBitCalc <<= 6;
		snFgBitCalc |= 0x00FF;

		if(snBgBitCalc>1023){ snBgBitCalc = 1023; }
		snBgBitCalc <<= 6;
		snBgBitCalc |= 0x00FF;

		break;		
	}

	strGray.Format(_T("CFG%04X%04X%04XCBG%04X%04X%04X%s"), snFgBitCalc & m_pApp->m_nGrayRed, snFgBitCalc & m_pApp->m_nGrayGreen, snFgBitCalc & m_pApp->m_nGrayBlue, snBgBitCalc & m_pApp->m_nGrayRed, snBgBitCalc & m_pApp->m_nGrayGreen, snBgBitCalc & m_pApp->m_nGrayBlue, lpData);

	lpData.Format(_T("%s"), strGray);

	return lpData;
}
CString CCommand::Gf_makePGPatternString(CString strPtnName)
{
	CString strTmp, retString;
	strTmp = CT2CmdGen::makeT2dataStrFromFile(strPtnName);
	retString = CT2CmdGen::makeT2PatternStr(strTmp, lpModelInfo->m_nTimingHorActive, lpModelInfo->m_nTimingVerActive);
	return retString;
}
BOOL CCommand::Gf_setPGInfoPatternName(CString strPtnName, BOOL bHotKeyFlags, BOOL bHkeyFlags)
{
	BOOL bRet=FALSE;
	CString ptn_str;

	if (strPtnName.Find(_T(".BMP")) != -1)
	{
		Gf_setBmpPtnDisplay(strPtnName);
	}
	else
	{
		ptn_str = MakeT2PtnFusingData(strPtnName, bHotKeyFlags, bHkeyFlags);
		wchar_To_char(ptn_str.GetBuffer(0), m_szPacket);
		m_PacketLength = (int)strlen(m_szPacket);

		bRet = m_pApp->udp_sendPacket(UDP_MAIN_IP, TARGET_CTRL, CMD_T2PTN_SEND, m_PacketLength, m_szPacket);
	}
	return bRet;
}
BOOL CCommand::Gf_setBmpPtnDisplay(CString bmpname)
{
	char szPacket[50];
	int length;
	sprintf_s(szPacket, "%03d%s", bmpname.GetLength(), wchar_To_char(bmpname.GetBuffer(0)));
	length = (int)strlen(szPacket);
	return m_pApp->udp_sendPacket(UDP_MAIN_IP, TARGET_CTRL, CMD_BMP_DISPLAY, length, szPacket);
}
BOOL CCommand::Gf_getAreYouReady()
{
	BOOL bRtnCode=FALSE;

	bRtnCode = m_pApp->udp_sendPacket(UDP_MAIN_IP, TARGET_CTRL, CMD_ARE_YOU_READY, 0, NULL);

	return bRtnCode;
}

BOOL CCommand::Gf_setPowerSeqOnOff(int nOnOff, int nCh)
{
	BOOL bRtnCode;
	CString strCmd=_T(""), sLog=_T("");
	int len=0;
	DWORD dWait;

	if (nOnOff == POWER_ON)
	{
		dWait = (lpModelInfo->m_nPowerOnSeqDelay01 + lpModelInfo->m_nPowerOnSeqDelay02 + lpModelInfo->m_nPowerOnSeqDelay03 + lpModelInfo->m_nPowerOnSeqDelay04
			+ lpModelInfo->m_nPowerOnSeqDelay05 + lpModelInfo->m_nPowerOnSeqDelay06 + lpModelInfo->m_nPowerOnSeqDelay07 + lpModelInfo->m_nPowerOnSeqDelay08
			+ lpModelInfo->m_nPowerOnSeqDelay09 + lpModelInfo->m_nPowerOnSeqDelay10 + lpModelInfo->m_nPowerOnSeqDelay11 + lpModelInfo->m_nPowerOnSeqDelay12
			+ lpModelInfo->m_nPowerOnSeqDelay13 + lpModelInfo->m_nPowerOnSeqDelay14);
		sLog.Format(_T("Power Sequence ON (Delay : %dms)"), dWait);
		m_pApp->Gf_writeLogData(_T("<TEST"), sLog);
	}
	else
	{
		dWait = (lpModelInfo->m_nPowerOffSeqDelay01 + lpModelInfo->m_nPowerOffSeqDelay02 + lpModelInfo->m_nPowerOffSeqDelay03 + lpModelInfo->m_nPowerOffSeqDelay04
			+ lpModelInfo->m_nPowerOffSeqDelay05 + lpModelInfo->m_nPowerOffSeqDelay06 + lpModelInfo->m_nPowerOffSeqDelay07 + lpModelInfo->m_nPowerOffSeqDelay08
			+ lpModelInfo->m_nPowerOffSeqDelay09 + lpModelInfo->m_nPowerOffSeqDelay10 + lpModelInfo->m_nPowerOffSeqDelay11 + lpModelInfo->m_nPowerOffSeqDelay12
			+ lpModelInfo->m_nPowerOffSeqDelay13 + lpModelInfo->m_nPowerOffSeqDelay14);
		sLog.Format(_T("Power Sequence OFF (Delay : %dms)"), dWait);
		m_pApp->Gf_writeLogData(_T("<TEST"), sLog);
	}

	// Power On/Off Packet 전송
	strCmd.Format(_T("%01d%01d"), nOnOff, nCh);
	wchar_To_char(strCmd.GetBuffer(0), m_szPacket);
	m_PacketLength = (int)strlen(m_szPacket);
	bRtnCode = m_pApp->udp_sendPacket(UDP_MAIN_IP, TARGET_CTRL, CMD_CTRL_POWER_SEQ_ONOFF, m_PacketLength, m_szPacket);

	if(bRtnCode==TRUE)
	{
		delayMS(10);
	}

	return bRtnCode;
}

BOOL CCommand::Gf_getFirmwareVersion()
{
	BOOL bRtnCode=FALSE;

	bRtnCode = m_pApp->udp_sendPacket(UDP_MAIN_IP, TARGET_CTRL, CMD_CTRL_FW_VERSION , 0, NULL);

	return bRtnCode;
}
BOOL CCommand::Gf_getFpgaeVersion()
{
	BOOL bRtnCode = FALSE;

	bRtnCode = m_pApp->udp_sendPacket(UDP_MAIN_IP, TARGET_CTRL, CMD_FPGA_VER_READ, 0, NULL);

	return bRtnCode;
}


BOOL CCommand::Gf_getPowerMeasure(int nID)
{
	BOOL ret;

	ret = m_pApp->udp_sendPacket(UDP_MAIN_IP, TARGET_CTRL, CMD_MEASURE_ALL_POWER, 0, NULL);
	return ret;
}


BOOL CCommand::Gf_setZoneSel(int nZoneSel)
{
	BOOL bRtnCode=FALSE;
	CString sdata;

	sdata.Format(_T("%01d"), nZoneSel);
	wchar_To_char(sdata.GetBuffer(0), m_szPacket);
	m_PacketLength = (int)strlen(m_szPacket);

	bRtnCode = m_pApp->udp_sendPacket(UDP_MAIN_IP, TARGET_CTRL, CMD_ZONE_SET, m_PacketLength, m_szPacket);

	return bRtnCode;
}
BOOL CCommand::Gf_setSignalOnOff(int nCh, int OnOff)
{
	BOOL ret = FALSE;
	char szPacket[50];
	int length;

	sprintf_s(szPacket, "%01d%01d", nCh, OnOff);
	length = (int)strlen(szPacket);

	ret = m_pApp->udp_sendPacket(UDP_MAIN_IP, TARGET_CTRL, CMD_CTRL_SIGNAL_ONOFF, length, szPacket);

	return ret;
}
BOOL CCommand::Gf_setPwmOnOff(int OnOff, int duty, int freq)
{
	BOOL ret = FALSE;
	char szPacket[50];
	int length;

	sprintf_s(szPacket, "%01d%03d%05d%01d%03d%05d", OnOff, duty, freq, OnOff, duty, freq); // Chanel 1,2 동일한 값으로 전달. CNZ
	length = (int)strlen(szPacket);

	ret = m_pApp->udp_sendPacket(UDP_MAIN_IP, TARGET_CTRL, CMD_CTRL_PWM_SET, length, szPacket);

	return ret;
}
BOOL CCommand::Gf_setI2cClock(int nID)
{
	CString sdata=_T("");
	BOOL bRtnCode=FALSE;
	nID |= 0x10;

	nID&=0xF0;

	sdata.Format(_T("%03d"), lpSystemInfo->m_nI2CClock);
	wchar_To_char(sdata.GetBuffer(0), m_szPacket);
	m_PacketLength = (int)strlen(m_szPacket);

	bRtnCode = m_pApp->udp_sendPacket(UDP_MAIN_IP, TARGET_CTRL, CMD_IF_I2C_CLOCK, m_PacketLength, m_szPacket);

	return bRtnCode;
}
BOOL CCommand::Gf_setI2cWrite(int line, int slave, int startReg, int addrType, int wrLength, BYTE* wrpData, BOOL bMlogWrite)
{
	CString sdata = _T("");
	BOOL bRtnCode = FALSE;
	char szPacket[1024 * 4];
	int nLength;

	int nI2cFreq = makeI2cClock(lpModelInfo->m_nI2cFreq);

	sprintf_s(szPacket, "%01d%03d%02X%04X%01d%04X", line, nI2cFreq, slave, startReg, addrType, wrLength);
	nLength = (int)strlen(szPacket);
	memcpy(&szPacket[nLength], wrpData, wrLength);

	nLength += wrLength;

	bRtnCode = m_pApp->udp_sendPacket(UDP_MAIN_IP, TARGET_CTRL, CMD_CTRL_I2C_WRITE, nLength, m_szPacket);
	if (bRtnCode == TRUE)
	{
		if (gszudpRcvPacket[PACKET_PT_RET] == '0')
		{
			m_pApp->Gf_writeLogData("<I2C>", "Write OK");
			return TRUE;
		}
		else
		{
			m_pApp->Gf_writeLogData("<I2C>", "Write ACK Fail");
			return FALSE;
		}
	}
	m_pApp->Gf_writeLogData("<I2C>", "Write NACK NG");
	return bRtnCode;
}
BOOL CCommand::Gf_getI2cRead(int line, int slave, int startReg, int addrType, int rdLength, BYTE* rdpData)
{
	BOOL ret = FALSE;
	int length;
	int i2c_freq = 200;
	char szPacket[4096] = { 0, };

	i2c_freq = makeI2cClock(lpModelInfo->m_nI2cFreq);

	sprintf_s(szPacket, "%01d%03d%02X%04X%01d%04X", line, i2c_freq, slave, startReg, addrType, rdLength);
	length = (int)strlen(szPacket);

	ret = m_pApp->udp_sendPacket(UDP_MAIN_IP, TARGET_CTRL, CMD_CTRL_I2C_READ, length, m_szPacket);
	
	if (ret == TRUE)
	{
		if (gszudpRcvPacket[PACKET_PT_RET] == '0')	// I2C Result Code Check
		{
			memcpy(rdpData, &gszudpRcvPacket[PACKET_PT_DATA], rdLength);
			m_pApp->Gf_writeLogData("<I2C>", "Read OK");
		}
		else
		{
			ret = FALSE; // 2019.04.12 CNZ
			m_pApp->Gf_writeLogData("<I2C>", "Read ACK Fail");
		}
	}
	else
	{
		ret = FALSE;
		m_pApp->Gf_writeLogData("<I2C>", "Read NACK NG");
	}
	return ret;
}
int CCommand::makeI2cClock(int index)
{
	int i2c_freq = 100;

	if (index == 0)		i2c_freq = 20;	//실제20
	if (index == 1)		i2c_freq = 50;	//실제50
	if (index == 2)		i2c_freq = 100;	//실제100
	if (index == 3)		i2c_freq = 154;	//실제150
	if (index == 4)		i2c_freq = 208;	//실제200
	if (index == 5)		i2c_freq = 250;	//실제240
	if (index == 6)		i2c_freq = 319;	//실제300
	if (index == 7)		i2c_freq = 376;	//실제350
	if (index == 8)		i2c_freq = 422;	//실제400

	return i2c_freq;
}
BOOL CCommand::Gf_CheckCableOpen()
{
	BOOL ret = TRUE;
	ret = m_pApp->udp_sendPacket(UDP_MAIN_IP, TARGET_CTRL, CMD_CTRL_CABLE_OPEN_TEST, 0, "");
	if (ret == TRUE)
	{
		if (gszudpRcvPacket[PACKET_PT_RET] == '0')
		{
			return TRUE;
		}
	}
	return FALSE;
}
BOOL CCommand::Gf_setPowerVoltSet(float vcc, float vdd, float vgh, float vgl)
{
	BOOL ret=FALSE;
	char szpacket[50];
	int length;

	sprintf_s(szpacket, "%05d%05d%05d%05d%05d", (int)vcc * 1000, (int)vdd * 1000, 0, (int)vgh * 1000, (int)vgl * 1000);
	length = (int)strlen(szpacket);

	ret = m_pApp->udp_sendPacket(UDP_MAIN_IP, TARGET_CTRL, CMD_CTRL_POWER_VOLTAGE_SET, length, szpacket);

	return ret;
}
BOOL CCommand::Gf_setSRunnerControl(int nTarget, int EnableDisable)
{
	BOOL ret = FALSE;
	char szpacket[50];
	int length;

	// Target 0: LVDS PG 1:DP Module
	// Enable 0: Disable 1: Enable
	sprintf_s(szpacket, "%01d%01d", nTarget, EnableDisable);
	length = (int)strlen(szpacket);

	ret = m_pApp->udp_sendPacket(UDP_MAIN_IP, TARGET_CTRL, CMD_CTRL_SRUNNER_CONTROL, length, szpacket);

	return ret;
}
BOOL CCommand::Gf_setSRunerComplete()
{
	return m_pApp->udp_sendPacket(UDP_MAIN_IP, TARGET_CTRL, CMD_CTRL_SRUNNER_COPLETE, 0, NULL);
}
BOOL CCommand::Gf_setSRunerTypeSelect(int nType)
{
	char szpacket[10];
	sprintf_s(szpacket, "%01d", nType);
	return m_pApp->udp_sendPacket(UDP_MAIN_IP, TARGET_CTRL, CMD_CTRL_SRUNNER_TYPE_SELECT, 1, szpacket);
}
BOOL CCommand::Gf_setGoToBootDownload()
{
	return m_pApp->udp_sendPacket(UDP_MAIN_IP, TARGET_CTRL, CMD_CTRL_FW_GOTO_BOOT_DOWNLOAD, 0, NULL);
}
BOOL CCommand::Gf_setGoToBootUpdate()
{
	return m_pApp->udp_sendPacket(UDP_MAIN_IP, TARGET_CTRL, CMD_CTRL_FW_GOTO_BOOT_UPDATE, 0, NULL);
}
BOOL CCommand::Gf_setMainBoardReset()
{
	return m_pApp->udp_sendPacket(UDP_MAIN_IP, TARGET_CTRL, CMD_CTRL_RESET_CTRLBOARD, 0, NULL);
}

BOOL CCommand::Gf_getEEPRomReadData()
{
	CString sdata=_T("");
	int stReg=0;

	m_pApp->m_bRcvHex = true;
	memset(m_pApp->m_nEEPRomReadData, 0, sizeof(m_pApp->m_nEEPRomReadData));

	if(lpModelInfo->m_nEdidSize == 0)
		m_pApp->m_nRcvHexSize = 128;
	else
		m_pApp->m_nRcvHexSize = 256;	
	
	sdata.Format(_T("%04dA%01X%01d%01d%04X"), m_pApp->m_nRcvHexSize, (lpModelInfo->m_nEEPRomAddr*2),lpModelInfo->m_nEdidLine,lpModelInfo->m_nEEPRomType, stReg);
	wchar_To_char(sdata.GetBuffer(0), m_szPacket);
	m_PacketLength = (int)strlen(m_szPacket);

	return m_pApp->udp_sendPacket(UDP_MAIN_IP, TARGET_CTRL, CMD_IF_GET_EDID_ODC_AI_DATA_EXPAND, m_PacketLength, m_szPacket);
}

/**************************************************************************************************************************************************************/
// GFD250 Command List
BOOL CCommand::Gf_setPGInfoGFD250(CString strPtnName, BOOL bHotKeyFlags, BOOL bHkeyFlags)
{
	BOOL bRtnCode = FALSE;
	CString sdata;

	sdata = MakeT2PtnDataGFD250(strPtnName, bHotKeyFlags, bHkeyFlags);

	wchar_To_char(sdata.GetBuffer(0), m_szPacket);
	m_PacketLength = (int)strlen(m_szPacket);

	if(m_PacketLength > 1000)
	{
#if 0
		// 이 알고리즘은 특정 Pattern에서 무조건 Error가 발생할 것이다.	
		// 언젠가는 수정해야만 한다.
		int nFindPtr=0;			// Packet을 자를 위치를 찾기 위한 변수.
		int nReadPtr=0;			// Packet을 읽을 위치를 저장하기 위한 변수.
		BYTE nX = 0;			// 현재 전송하는 Packet의 번호.
		BYTE nY = 0;			// 전송해야할 전체 Packet의 수.
		CString strReData;
		CStringArray strArry;

		while(1)
		{
			// 800Byte 이후부터 "TA" Command를 찾는다.
			nFindPtr = strCmd.Find(_T("TA"), (nFindPtr+800));

			// "TA" Command를 찾지 못했을 경우. (-1)
			if(nFindPtr == -1)
			{
				// 읽어야 하는 위치부터 남아있는 String의 값을 가져온다.
				strReData.Format("%s", strCmd.Mid(nReadPtr));

				// 지금은 1000Byte이하의 패턴만 있으므로 문제되지 않지만 이후 문제되면 이부분 수정하자.
				if(strReData.GetLength() < 1000)
				{	// 남아있는 String의 길이가 1000Byte 이하일 경우 Array에 Add후 종료한다.
					strArry.Add(strReData);
					break;
				}
				else
				{	// 남아있는 String의 길이가 1000Byte 이상일 경우 다른 Command를 검색한다.
					// "TB", "TD", "LC", "TC", "RH", "OL", "LH", "LV", "LT", "LP", "LR", "BS", "RV", "BM", "CD", "CLN", "CBT", "CFG", "CBG"
					// 위 Command를 모두 찾으려면 String 검색에 다소 시간이 소요되므로 알고리즘을 잘 판단하자.

				}
			}
			// 읽어야할 위치에서 부터 "TA" Command 앞까지의 String을 자른다.
			strReData.Format("%s", strCmd.Mid(nReadPtr, nFindPtr-nReadPtr));
			strArry.Add(strReData);

			// 다음 Packet 읽을 위치를 "TA" Command의 앞으로 이동 시킨다.
			nReadPtr = nFindPtr;
		}

		// 저장된 Packet을 차례대로 전송한다.
		nX = 0;
		nY = strArry.GetSize();
		for(int i=0; i<nY; i++)
		{
			nX = i;
			strReData = strArry.GetAt(i);
			bRtnCode = Gf_setPacketSendGfd250(TARGET_GFD250, PG_CMD, ((nX<<4)|nY), CMD_T2PTN_SEND, strReData.GetLength(), strReData.GetBuffer(0));
			if(i==0)	m_pApp->Gf_writeLogData("3D Pattern", "First Packet Send");
			if(i==1)	m_pApp->Gf_writeLogData("3D Pattern", "Second Packet Send");
		}
#endif
	}
	else
	{
		bRtnCode = Gf_setPacketSendGfd250(TARGET_GFD250, PG_CMD, 0x00, CMD_T2PTN_SEND, m_PacketLength, m_szPacket);
	}			   

	return bRtnCode;
}

BOOL CCommand::Gf_setGFD250Timeing()
{
	int nInterface = 0;
	int nMode = 0;
	int nBitsSwap = lpModelInfo->m_nLcmInfoBitsSwap << 4;
	int nDotClockInv=0;
	int nHsyncPolarity = 0x00;
	int nVsyncPolarity = 0x00;
	CString sdata=_T("");
	CString makePacket;

	sdata.Format(_T("INFO"));														makePacket.Append(sdata);

	if(lpModelInfo->m_nPixelType == SINGLE)			nInterface=0;
	else if(lpModelInfo->m_nPixelType == DUAL)		nInterface=1;
	else if(lpModelInfo->m_nPixelType == QUAD)		nInterface=2;

	sdata.Format(_T("%02X"), (nInterface | nMode | nBitsSwap));						makePacket.Append(sdata);
	sdata.Format(_T("%01X"), (nDotClockInv | nHsyncPolarity | nVsyncPolarity));		makePacket.Append(sdata);
	sdata.Format(_T("%04d"), lpModelInfo->m_nTimingHorActive);						makePacket.Append(sdata);
	sdata.Format(_T("%04d"), lpModelInfo->m_nTimingVerActive);						makePacket.Append(sdata);

	float fMclk;
	if(lpModelInfo->m_nPixelType == SINGLE)
		fMclk = lpModelInfo->m_fTimingFreq;
	else if(lpModelInfo->m_nPixelType == DUAL)
		fMclk = (lpModelInfo->m_fTimingFreq / 2.f);
	else if(lpModelInfo->m_nPixelType == QUAD)
		fMclk = (lpModelInfo->m_fTimingFreq / 4.f);

	// HBR3는 /2 를 한번 더 함
	fMclk = fMclk / 2.0f;				
	sdata.Format(_T("%06.2f"), fMclk);												makePacket.Append(sdata);

	sdata.Format(_T("%04d"), lpModelInfo->m_nTimingHorWidth);						makePacket.Append(sdata);
	sdata.Format(_T("%04d"), lpModelInfo->m_nTimingHorFront_P);						makePacket.Append(sdata);
	sdata.Format(_T("%04d"), lpModelInfo->m_nTimingHorBack_P);						makePacket.Append(sdata);

	sdata.Format(_T("%04d"), lpModelInfo->m_nTimingVerWidth);						makePacket.Append(sdata);
	sdata.Format(_T("%04d"), lpModelInfo->m_nTimingVerFront_P);						makePacket.Append(sdata);
	sdata.Format(_T("%04d"), lpModelInfo->m_nTimingVerBack_P);						makePacket.Append(sdata);

	sdata.Format(_T("%01d"), 2);													makePacket.Append(sdata);	// Division Mode

	wchar_To_char(makePacket.GetBuffer(0), m_szPacket);
	m_PacketLength = (int)strlen(m_szPacket);

	return Gf_setPacketSendGfd250(TARGET_GFD250, PG_CMD, 0x00, CMD_T2PTN_SEND, m_PacketLength, m_szPacket);
}

BOOL CCommand::Gf_serGfd250SignalOnOff(char onoff)
{
	BOOL bRtnCode=FALSE;
	CString sdata=_T("");

	sdata.Format(_T("%d"), onoff);

	wchar_To_char(sdata.GetBuffer(0), m_szPacket);
	m_PacketLength = (int)strlen(m_szPacket);

	bRtnCode = Gf_setPacketSendGfd250(TARGET_GFD250, PG_CMD, 0x00, 0x14, m_PacketLength, m_szPacket);
	return bRtnCode;
}

BOOL CCommand::Gf_serGfd250SignalSelect(char sel)
{
	BOOL bRtnCode=FALSE;
	CString sdata=_T("");

	sdata.Format(_T("%d"), sel);
	wchar_To_char(sdata.GetBuffer(0), m_szPacket);
	m_PacketLength = (int)strlen(m_szPacket);

	bRtnCode = Gf_setPacketSendGfd250(TARGET_GFD250, PG_CMD, 0x00, 0x30, m_PacketLength, m_szPacket);
	return bRtnCode;
}

BOOL CCommand::Gf_serGfd250FirmwareVersion()
{
	BOOL bRtnCode=FALSE;

	bRtnCode = Gf_setPacketSendGfd250(TARGET_GFD250, PG_CMD, 0x00, 0xFE, NULL, 0);
	return bRtnCode;
}

BOOL CCommand::Gf_serGfd250GoToBootSection()
{
	BOOL bRtnCode=FALSE;

	bRtnCode = Gf_setPacketSendGfd250(TARGET_GFD250, PG_CMD, 0x00, 0xF3, NULL, 0);
	return bRtnCode;
}

BOOL CCommand::Gf_getGfd250I2CReadPacketSend(int nStartReg, int ReadNum, int Cmd)
{
	BOOL bRtnCode = TRUE;
	CString sdata=_T("");

	m_pApp->m_nI2CCmdNumber = Cmd;

	sdata.Format(_T("%01d0A%01X%04X%04X"),lpModelInfo->m_nEEPRomType,(lpModelInfo->m_nEEPRomAddr*2), nStartReg, ReadNum);
	wchar_To_char(sdata.GetBuffer(0), m_szPacket);
	m_PacketLength = (int)strlen(m_szPacket);

	bRtnCode = Gf_setPacketSendGfd250(TARGET_GFD250, NIOS_CMD, 0, CMD_NIOS_I2C_READ, m_PacketLength, m_szPacket);

	return bRtnCode;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PLC Control
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL CCommand::plc_Connection()
{
	int nPort = _ttoi(lpSystemInfo->m_sPlcPort);

	return m_pApp->m_pSocketTCPApp->tcp_plc_Connection(lpSystemInfo->m_sPlcIPAddress, nPort);
}

BOOL CCommand::plc_DisConnection()
{
	return m_pApp->m_pSocketTCPApp->tcp_plc_DisConnection();
}

BOOL CCommand::plc_sendQuery(char* data, int nDataLen)
{
	int ret;

	ret = m_pApp->m_pSocketTCPApp->tcp_plc_SendQuery(data, nDataLen);

	memset(gszplcRcvPacket, 0x00, sizeof(gszplcRcvPacket));

	if (m_pApp->m_pPlcCtrl->plc_tcpIsConnection() == TRUE)
		return plc_getReceivePacket(gszplcRcvPacket);
	else
		return FALSE;
}

BOOL CCommand::plc_getReceivePacket(char* m_szRcvPacket)
{
	DWORD sTick, eTick;
	sTick = ::GetTickCount();

	while (1)
	{
		if (m_pApp->m_pSocketTCPApp->tcp_plc_GetReceivePacketSize() != NULL)
		{
			m_pApp->m_pSocketTCPApp->tcp_plc_GetReceivePacketData(m_szRcvPacket);
			return TRUE;
		}

		// Ack를 기다린다. Wait Time안에 Ack가 들어오지 않으면 False를 Return한다.
		eTick = ::GetTickCount();
		if ((eTick - sTick) > ETH_ACK_NOR_WAIT_TIME)
			break;

		ProcessMessage();
	}

	return FALSE;
}
