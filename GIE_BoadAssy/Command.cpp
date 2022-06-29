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


BOOL CCommand::Lf_SyncAckFusingMessage(int nMessage)
{
	BOOL bRtnCode=FALSE;
	int nCnt=0;

	if(DEBUG_232RECEIVE_OK)	return TRUE;

	while(TRUE)
	{
		if(nMessage == m_pApp->m_nRcvPgMsg)
		{
			bRtnCode = TRUE;
			break;
		}
		Sleep(10);

		if(nCnt > 300)
		{
			bRtnCode = FALSE;
			break;
		}
		nCnt++;

	}
	m_pApp->m_nRcvPgMsg = 0x00;
	return bRtnCode;
}

BOOL CCommand::Gf_setPacketSend(BYTE nId, int nCommand, int nSize, char* pdata)
{
	int target=0;
	int datalen=0;
	int packetlen=0;
	BYTE nChkSum=0;
	char szbuff[5]={0,};
	char sendPacket[4096]={0,};

	datalen = nSize;

	// data 앞까지 Packet 생성
	sprintf_s(sendPacket, "%cA1%02X%02X%02X%04X", PACKET_STX, TARGET_CTRL, nId, nCommand, datalen);

	// data를 포함하여 packet 생성. hex로 전송할 data가 있으므로 memcpy를 사용
	packetlen = (int)strlen(sendPacket);
	memcpy(&sendPacket[packetlen], pdata, datalen);

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

	// 생성된 Packet을 전송.
	UINT ret=TRUE;
	int waitTime = 3000;

	m_pApp->Gf_sendPgData((BYTE*)sendPacket, packetlen);

	return Lf_SyncAckFusingMessage(nCommand);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// eDP 1.4 Bridge보드에 CMD전송을 위한 함수.
BOOL CCommand::Gf_setPacketSendGfd250(BYTE nTarget, BYTE nMSCmd, BYTE nId, BYTE nCmd, int nLength, char* pData)
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

	int nRecCnt=0;
	while(1)
	{
		if(m_pApp->m_nRcvGfd250Msg == nCmd)	
			break;

		if(nRecCnt++ > 100)					
			return FALSE;
		Sleep(40);
	}

	return TRUE;
}

BOOL CCommand::Gf_setPacketSendBLU(BYTE nCmd, int nLength, char* pData)
{
	int target=0;
	int datalen=0;
	int packetlen=0;
	BYTE nChkSum=0;
	char szbuff[5]={0,};
	char sendPacket[1024]={0,};

// 	if(lpStationInfo->gucLedBlPort==0)
// 	{
// 		return TRUE;
// 	}

	m_pApp->m_nRcvMsgBlu = 0x00;

	// data 앞까지 Packet 생성
	sprintf_s(sendPacket, "%cA1%02X%02X%02X%04X", PACKET_STX, TARGET_CTRL, 0, nCmd, nLength);

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

	m_pApp->Gf_sendBLUData((BYTE*)sendPacket, packetlen);

	int nRecCnt=0;
	while(1)
	{
		if(m_pApp->m_nRcvMsgBlu == nCmd)	
			break;
		if(nRecCnt++ > 30)					
			return FALSE;
		Sleep(10);
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CCommand::Lf_makeSystemFusingData(char* packet)
{
	CString makePacket;
	CString sdata = _T("");
	SYSTEMTIME sysTime;
	unsigned char LaneCurrent[16]={0x00,0x55,0xAA,0xFF,0x00,0x55,0xAA,0xFF,0x00,0x55,0xAA,0xFF,0x00,0x55,0xAA,0xFF};
	unsigned char PreEmphasis[16]={0x00,0x00,0x00,0x00,0x55,0x55,0x55,0x55,0xAA,0xAA,0xAA,0xAA,0xFF,0xFF,0xFF,0xFF};

	::GetSystemTime (&sysTime);
	CTime time = CTime::GetCurrentTime ();

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	sdata.Format(_T("%s******************************"),	_T("DEFUALT_LCM_NAME"));
	sdata = sdata.Left(30);															makePacket.Append(sdata);
	sdata.Format(_T("%02d"),time.GetDay());											makePacket.Append(sdata);// Date

	int nInterface = 0;
	int nMode = 0;
	int nBitsSwap = lpModelInfo->m_nLcmInfoBitsSwap << 4;
	int nDotClockInv=0;
	int nHsyncPolarity = 0x00;
	int nVsyncPolarity = 0x00;

	if(lpModelInfo->m_nLcmInfoInterface == SINGLE)			nInterface=3;
	else if(lpModelInfo->m_nLcmInfoInterface == DUAL)		nInterface=2;
	else if(lpModelInfo->m_nLcmInfoInterface == QUAD)		nInterface=0;

	sdata.Format(_T("%02X"), (nInterface | nMode | nBitsSwap));						makePacket.Append(sdata);
	sdata.Format(_T("%01X"), (nDotClockInv | nHsyncPolarity | nVsyncPolarity));		makePacket.Append(sdata);
	sdata.Format(_T("%04d"), lpModelInfo->m_nTimingHorActive);						makePacket.Append(sdata);
	sdata.Format(_T("%04d"), lpModelInfo->m_nTimingVerActive);						makePacket.Append(sdata);

	if(lpModelInfo->m_nLcmInfoInterface == SINGLE)
	{
		sdata.Format(_T("%06.2f"), lpModelInfo->m_fTimingFreq);						makePacket.Append(sdata);
	}
	else if(lpModelInfo->m_nLcmInfoInterface == DUAL)
	{
		sdata.Format(_T("%06.2f"), lpModelInfo->m_fTimingFreq / 2.f);				makePacket.Append(sdata);
	}
	else if(lpModelInfo->m_nLcmInfoInterface == QUAD)
	{
		sdata.Format(_T("%06.2f"), lpModelInfo->m_fTimingFreq / 4.f);				makePacket.Append(sdata);
	}

	sdata.Format(_T("%03d"), lpModelInfo->m_nTimingHorWidth);						makePacket.Append(sdata);
	sdata.Format(_T("%04d"), lpModelInfo->m_nTimingHorFront_P);						makePacket.Append(sdata);
	sdata.Format(_T("%04d"), lpModelInfo->m_nTimingHorBack_P);						makePacket.Append(sdata);

	sdata.Format(_T("%03d"), lpModelInfo->m_nTimingVerWidth);						makePacket.Append(sdata);
	sdata.Format(_T("%04d"), lpModelInfo->m_nTimingVerFront_P);						makePacket.Append(sdata);
	sdata.Format(_T("%04d"), lpModelInfo->m_nTimingVerBack_P);						makePacket.Append(sdata);

	sdata.Format(_T("%01d"), lpModelInfo->m_nClockIncDec);							makePacket.Append(sdata);
	sdata.Format(_T("%03d"), (int)((lpModelInfo->m_fClockDelay*10)+0.5));			makePacket.Append(sdata);
	sdata.Format(_T("%01d"), lpModelInfo->m_nClockIncDec);							makePacket.Append(sdata);
	sdata.Format(_T("%03d"), (int)((lpModelInfo->m_fClockDelay*10)+0.5));			makePacket.Append(sdata);

	// Aging Info
	sdata.Format(_T("%04d"), 0);													makePacket.Append(sdata);// Total Aging Time
	sdata.Format(_T("%03d"), 0);													makePacket.Append(sdata);// Aging Pattern Interval
	sdata.Format(_T("%03d"), 0);													makePacket.Append(sdata);// Start LCM Time		
	sdata.Format(_T("%03d"), 0);													makePacket.Append(sdata);// Auto ON Time
	sdata.Format(_T("%03d"), 0);													makePacket.Append(sdata);// Auto OFF Time	
	sdata.Format(_T("%02d"), 0);													makePacket.Append(sdata);// NG Count
	sdata.Format(_T("%01d"), 0);													makePacket.Append(sdata);// Current check
	sdata.Format(_T("%02d"), 0);													makePacket.Append(sdata);// Low Limit Count
	sdata.Format(_T("%03d"), 0);													makePacket.Append(sdata);// NG Off->On Time(S)
	sdata.Format(_T("%02d"), 0);													makePacket.Append(sdata);// Unchanged Current Count
	sdata.Format(_T("%04d"), 0);													makePacket.Append(sdata);// Unchanged Current
	sdata.Format(_T("%01d"), 0);													makePacket.Append(sdata);// Aging Monitoring Pattern On/Off
	sdata.Format(_T("%03d"), 0);													makePacket.Append(sdata);// Aging Monitoring Pattern Display Time

	sdata.Format(_T("%01d"), lpModelInfo->m_nSignalType);							makePacket.Append(sdata);
	sdata.Format(_T("%01d"), lpModelInfo->m_nSignalBit);							makePacket.Append(sdata);
	sdata.Format(_T("%01d"), lpModelInfo->m_nLcmInfoInterface);						makePacket.Append(sdata);

	sdata.Format(_T("%01d"), lpModelInfo->m_nLGDISMSelect);							makePacket.Append(sdata);				
	sdata.Format(_T("%01d"), lpModelInfo->m_nBitSel);								makePacket.Append(sdata);					
	sdata.Format(_T("%01d"), 0);													makePacket.Append(sdata);//lpModelInfo->m_nUserCableCheck			
	sdata.Format(_T("%01d"), lpModelInfo->m_nAgpOnOff);								makePacket.Append(sdata);//Aging AGP Mode
	sdata.Format(_T("%01d"), lpModelInfo->m_nSpiMode);								makePacket.Append(sdata);
	
	sdata.Format(_T("%03d"), (int)(lpModelInfo->m_fVoltVcc*10+0.5));				makePacket.Append(sdata);
	sdata.Format(_T("%03d"), (int)(lpModelInfo->m_fVoltVdd*10+0.5));				makePacket.Append(sdata);
	sdata.Format(_T("%03d"), 0);													makePacket.Append(sdata);//vbl
	sdata.Format(_T("%03d"), 0);													makePacket.Append(sdata);//vbr

	sdata.Format(_T("%03d"), 0);													makePacket.Append(sdata);//vcc offset
	sdata.Format(_T("%03d"), 0);													makePacket.Append(sdata);//vdd offset
	sdata.Format(_T("%03d"), 0);													makePacket.Append(sdata);//vbl offset

	sdata.Format(_T("%01s"), (lpModelInfo->m_nPwrSeq==0)?_T("V"):_T("S"));			makePacket.Append(sdata);
	
	sdata.Format(_T("%03d"), lpModelInfo->m_nSeqDelay);								makePacket.Append(sdata);
	sdata.Format(_T("%03d"), 0);													makePacket.Append(sdata);
	sdata.Format(_T("%03d"), 0);													makePacket.Append(sdata);
	sdata.Format(_T("%03d"), 0);													makePacket.Append(sdata);
	sdata.Format(_T("%03d"), 0);													makePacket.Append(sdata);

	// Inverter
	sdata.Format(_T("%01d"), 0);													makePacket.Append(sdata);//lpModelInfo->m_nInvType
	sdata.Format(_T("%01d"), 0);													makePacket.Append(sdata);//lpModelInfo->m_nInvMode
	sdata.Format(_T("%02d"), 00);													makePacket.Append(sdata);// BL Cable Check Off
	sdata.Format(_T("%01d"), 0);													makePacket.Append(sdata);// Public Ch1 On/Off
	sdata.Format(_T("%01d"), 0);													makePacket.Append(sdata);// Public Ch2 On/Off
	sdata.Format(_T("%01d"), 0);													makePacket.Append(sdata);// Public Ch3 On/Off
	sdata.Format(_T("%01d"), 0);													makePacket.Append(sdata);// Public Ch4 On/Off
	sdata.Format(_T("%01d"), 0);													makePacket.Append(sdata);// Public Ch5 On/Off
	sdata.Format(_T("%01d"), 0);													makePacket.Append(sdata);// Public Ch6 On/Off
	sdata.Format(_T("%01d"), 0);													makePacket.Append(sdata);// Public All off /ng ch off
	sdata.Format(_T("%02d"), 0);													makePacket.Append(sdata);// public Freq;
	sdata.Format(_T("%01d"), 0);													makePacket.Append(sdata);// public inch info
	sdata.Format(_T("%01d"), 0);													makePacket.Append(sdata);// Retry When NG

	sdata.Format(_T("%01d"), 0);													makePacket.Append(sdata);// Public Ch1 Shut Down
	sdata.Format(_T("%01d"), 0);													makePacket.Append(sdata);// Public Ch1 Shut Down
	sdata.Format(_T("%01d"), 0);													makePacket.Append(sdata);// Public Ch1 Shut Down
	sdata.Format(_T("%01d"), 0);													makePacket.Append(sdata);// Public Ch1 Shut Down
	sdata.Format(_T("%01d"), 0);													makePacket.Append(sdata);// Public Ch1 Shut Down
	sdata.Format(_T("%01d"), 0);													makePacket.Append(sdata);// Public Ch1 Shut Down

	sdata.Format(_T("%01d"), 0);													makePacket.Append(sdata);//lpModelInfo->m_nInvSyncEnb					
	sdata.Format(_T("%05d"), 0);													makePacket.Append(sdata);//lpModelInfo->m_nInvPwmFreq					
	sdata.Format(_T("%03d"), 0);													makePacket.Append(sdata);//lpModelInfo->m_nInvPwmDutyHigh			
	sdata.Format(_T("%01d"), 0);													makePacket.Append(sdata);//lpModelInfo->m_nInvPwmLevel		
	sdata.Format(_T("%01d"), 0);													makePacket.Append(sdata);//lpModelInfo->m_nInvMode
	sdata.Format(_T("%01d"), 1);													makePacket.Append(sdata);// BRTI/P On Off
	sdata.Format(_T("%01d"), 0);													makePacket.Append(sdata);// AI Model. AI MODEL Set is Always '0'

	sdata.Format(_T("%04d"), 0);													makePacket.Append(sdata);
	sdata.Format(_T("%04d"), (int)(lpModelInfo->m_fLimitVccMax*100));				makePacket.Append(sdata);
	sdata.Format(_T("%04d"), 0);													makePacket.Append(sdata);
	sdata.Format(_T("%04d"), (int)(lpModelInfo->m_fLimitVddMax*100));				makePacket.Append(sdata);
	sdata.Format(_T("%04d"), 0);													makePacket.Append(sdata);
	sdata.Format(_T("%04d"), 9999);													makePacket.Append(sdata);

	sdata.Format(_T("%04d"), 0);													makePacket.Append(sdata);
	sdata.Format(_T("%04d"), (int)(lpModelInfo->m_fLimitIccMax*1000));				makePacket.Append(sdata);
	sdata.Format(_T("%04d"), 0);													makePacket.Append(sdata);
	sdata.Format(_T("%04d"), (int)(lpModelInfo->m_fLimitIddMax*1000));				makePacket.Append(sdata);
	sdata.Format(_T("%04d"), 0);													makePacket.Append(sdata);
	sdata.Format(_T("%04d"), 9999);													makePacket.Append(sdata);

	sdata.Format(_T("%02d"), 0);													makePacket.Append(sdata);//lpModelInfo->m_nInvPwmDutyLow
	
	// NBPC LED B/L Info
	sdata.Format(_T("%01d"), 0);													makePacket.Append(sdata);// I2C Line Sel.
	sdata.Format(_T("%02X"), 0);													makePacket.Append(sdata);// SMBUS Salve Addr
	sdata.Format(_T("%02X"), 0);													makePacket.Append(sdata);// SMBUS Reg Addr
	sdata.Format(_T("%02X"), 0);													makePacket.Append(sdata);// SMBUS Data
	sdata.Format(_T("%02X"), 0);													makePacket.Append(sdata);// NBPC VSet
	sdata.Format(_T("%01d"), 0);													makePacket.Append(sdata);// IT-LED Inverter IC Sel
	// ALS/089 Model Set
	sdata.Format(_T("%01d"), 0);													makePacket.Append(sdata);// NBPC ALS Model
	sdata.Format(_T("%01d"), 0);													makePacket.Append(sdata);// NBPC 089 Model
	sdata.Format(_T("%04d"), 0);													makePacket.Append(sdata);// NBPC 089 Current Set
	sdata.Format(_T("%04d"), 0);													makePacket.Append(sdata);// NBPC 089 Current Sensing Time Set

	sdata.Format(_T("%01d"), lpSystemInfo->m_nI2CPullUp);							makePacket.Append(sdata);
	sdata.Format(_T("%01d"), 0);													makePacket.Append(sdata);// Inspection Mode (InLine or OffLine)	1:조정 0:오프라인.
	sdata.Format(_T("%03d"), lpSystemInfo->m_nI2CClock);							makePacket.Append(sdata);
	sdata.Format(_T("%01d"), lpModelInfo->m_nSpiLevel);								makePacket.Append(sdata);

	sdata.Format(_T("%01d"), 0);													makePacket.Append(sdata);// PreDisplay On/Off
	sdata.Format(_T("%01d"), 0);													makePacket.Append(sdata);// PreDisplay Aging Error Pallet Display
	sdata.Format(_T("%01d"), 0);													makePacket.Append(sdata);// PreDisplay Display Pattern Type

	sdata.Format(_T("%01d"), 0);													makePacket.Append(sdata);//	Lamp Status NG Mode 0:OFF, 1:Low NG, 2:High NG
	sdata.Format(_T("%03d"), 0);													makePacket.Append(sdata);//	Lamp Status NG Voltage
	sdata.Format(_T("%01d"), 0);													makePacket.Append(sdata);//	AGP BIST Control
	sdata.Format(_T("%01d"), 0);													makePacket.Append(sdata);// Always BLU Mode
// 	sdata.Format(_T("%01d"), 0);													makePacket.Append(sdata);// SOLOMON MIPI USE/UNUSE
// 	sdata.Format(_T("%01d"), 0);													makePacket.Append(sdata);// PARADE CHIP SELECT
// 	sdata.Format(_T("%02X%02X"), LaneCurrent[lpModelInfo->m_nLaneCurrPreEmp], PreEmphasis[lpModelInfo->m_nLaneCurrPreEmp]);	makePacket.Append(sdata);
// 	sdata.Format(_T("%01d"),lpSystemInfo->m_neDPInitCodeSelect);					makePacket.Append(sdata);
// 	sdata.Format(_T("%01d"), 0);													makePacket.Append(sdata);//Auto Model PDC Signal

	wchar_To_char(makePacket.GetBuffer(0), packet);
}


BOOL CCommand::Gf_setFusingSystemInfo()
{
	BOOL bRet=FALSE;
	int length=0;
	char szPacket[4096]={0,};

	Lf_makeSystemFusingData(szPacket);
	length = (int)strlen(szPacket);

 	bRet = Gf_setPacketSend(0, CMD_CTRL_FUSING_SYSTEM, length, szPacket);

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

	strTmp.Format(_T(".\\PATTERN\\%s"), strPtnName);
	strTmp = CT2CmdGen::makeT2dataStrFromFile(strTmp);

	strTmp = CT2CmdGen::makeT2PatternStr(lpModelInfo->m_nLcmInfoInterface, strTmp, lpModelInfo->m_nTimingHorActive, lpModelInfo->m_nTimingVerActive);

	lpData = strTmp;

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

	strTmp.Format(_T(".\\PATTERN\\%s"), strPtnName);
	strTmp = CT2CmdGen::makeT2dataStrFromFile(strTmp);

	strTmp = CT2CmdGen::makeT2PatternStr(lpModelInfo->m_nLcmInfoInterface, strTmp, lpModelInfo->m_nTimingHorActive, lpModelInfo->m_nTimingVerActive);

	lpData = strTmp;

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
		m_pApp->m_nGrayValueFg = _ttoi(lpModelInfo->m_sLbPtnFg[*m_pApp->pPtnIndex]);
		m_pApp->m_nGrayValueBg = _ttoi(lpModelInfo->m_sLbPtnBg[*m_pApp->pPtnIndex]);
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

BOOL CCommand::Gf_setPGInfo(CString strPtnName, BOOL bHotKeyFlags, BOOL bHkeyFlags)
{
	BOOL bRet=FALSE;
	CString ptn_str;

	ptn_str = MakeT2PtnFusingData(strPtnName, bHotKeyFlags, bHkeyFlags);
	wchar_To_char(ptn_str.GetBuffer(0), m_szPacket);
	m_PacketLength = (int)strlen(m_szPacket);
#if 0
	if(m_PacketLength > 1000)
	{
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
			nFindPtr = strCmd.Find("TA", (nFindPtr+800));

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
			bRet = Gf_setPacketSend(((nX<<4)|nY), CMD_T2PTN_SEND, m_PacketLength, m_szPacket);
			if(i==0)	m_pApp->gf_LogDataWrite(_T("3D Pattern", _T("First Packet Send"));
			if(i==1)	m_pApp->gf_LogDataWrite(_T("3D Pattern", _T("Second Packet Send"));
		}
	}
	else
#endif
	{
		bRet = Gf_setPacketSend(0, CMD_T2PTN_SEND, m_PacketLength, m_szPacket);
	}

	return bRet;
}

BOOL CCommand::Gf_getAreYouReady()
{
	BOOL bRtnCode=FALSE;

	bRtnCode = Gf_setPacketSend(0, CMD_ARE_YOU_READY, 0, NULL);

	return bRtnCode;
}

BOOL CCommand::Gf_setPowerVoltage(float fVcc, float fVdd, float fVbl, float fVbr)
{
	BOOL bRtnCode=FALSE;
	CString sdata=_T("");

	sdata.Format(_T("%03d%03d%03d%03d"), (int)(fVcc*10.0+0.5), (int)(fVdd*10.0+0.5), (int)(fVbl*10.0+0.5), (int)(fVbr*10.0+0.5));
	wchar_To_char(sdata.GetBuffer(0), m_szPacket);
	m_PacketLength = (int)strlen(m_szPacket);

	bRtnCode = Gf_setPacketSend(0, CMD_POWER_VOLTAGE_SET, m_PacketLength, m_szPacket);

	return bRtnCode;	
}

BOOL CCommand::Gf_setPowerOnOff(int nID, int nSel, int nOnOff)
{
	BOOL bRtnCode=FALSE;
	CString sdata=_T("");

	sdata.Format(_T("%01d%01d"), nSel, nOnOff);

	wchar_To_char(sdata.GetBuffer(0), m_szPacket);
	m_PacketLength = (int)strlen(m_szPacket);

	bRtnCode = Gf_setPacketSend(nID, CMD_CTRL_POWER_ONOFF_SET, m_PacketLength, m_szPacket);

	return bRtnCode;
}

BOOL CCommand::Gf_setPowerSeqOnOff(int nOnOff)
{
	BOOL bRtnCode;
	CString strCmd=_T("");
	int len=0;

	strCmd.Format(_T("%01d"), nOnOff);

	wchar_To_char(strCmd.GetBuffer(0), m_szPacket);
	m_PacketLength = (int)strlen(m_szPacket);

	bRtnCode = Gf_setPacketSend(0, CMD_CTRL_POWER_SEQ_ONOFF, m_PacketLength, m_szPacket);

	return bRtnCode;
}

BOOL CCommand::Gf_getFirmwareVersion()
{
	BOOL bRtnCode=FALSE;

	bRtnCode = Gf_setPacketSend(0, CMD_CTRL_FW_VERSION, 0, NULL);

	return bRtnCode;
}

BOOL CCommand::Lf_setIF5VPowerOffOn(int offon)
{
	BYTE nID=0;
	CString strCmd=_T("");
	CString lpData=_T("");

	nID = 0x10;

	strCmd.Format(_T("%01d"), offon);
	wchar_To_char(strCmd.GetBuffer(0), m_szPacket);
	m_PacketLength = (int)strlen(m_szPacket);

	Gf_setPacketSend(0, CMD_IF_5V_POWER_ONOFF, m_PacketLength, m_szPacket);	// 2012-08-28 PDH. IF 5V제어는 ACK를 Check하지 않는다. 강제 100ms Delay를 가져가도록 한다.
	Sleep(100);

	return TRUE;
}

void CCommand::Gf_setIF5VPowerOffOn(BOOL onoff)
{
	if(lpModelInfo->m_nSignalType == SIG_TYPE_EDP)
	{
		Lf_setIF5VPowerOffOn(onoff);
	}
	else
	{
		Lf_setIF5VPowerOffOn(TRUE);
	}
}

void CCommand::Gf_ShowMessageBox(CString strMessage)
{

	CMessageError err_dlg;

	err_dlg.m_strEMessage = strMessage;
	err_dlg.DoModal();
}


BOOL CCommand::Gf_getPowerMeasure(int nID)
{
	BOOL bRtnCode;

	bRtnCode = Gf_setPacketSend(nID, CMD_MEASURE_ALL_POWER, 0, NULL);

	return bRtnCode;
}

BOOL CCommand::Gf_set810BitSel(int nID, int nBit)
{
	BOOL bRtnCode=FALSE;
	CString sdata=_T("");

	sdata.Format(_T("%01d"), nBit);
	wchar_To_char(sdata.GetBuffer(0), m_szPacket);
	m_PacketLength = (int)strlen(m_szPacket);

	bRtnCode = Gf_setPacketSend(nID, CMD_CTRL_810_BIT_SEL, m_PacketLength, m_szPacket);
	return bRtnCode;
}

BOOL CCommand::Gf_setLGDISMsel(int nID, int nLgDism)
{
	BOOL bRtnCode=FALSE;
	CString sdata=_T("");

	sdata.Format(_T("%01d"), nLgDism);
	wchar_To_char(sdata.GetBuffer(0), m_szPacket);
	m_PacketLength = (int)strlen(m_szPacket);

	bRtnCode = Gf_setPacketSend(nID, CMD_CTRL_LG_DISM_SEL, m_PacketLength, m_szPacket);

	return bRtnCode;
}

BOOL CCommand::Gf_setZoneSel(int nZoneSel)
{
	BOOL bRtnCode=FALSE;
	CString sdata;

	sdata.Format(_T("%01d"), nZoneSel);
	wchar_To_char(sdata.GetBuffer(0), m_szPacket);
	m_PacketLength = (int)strlen(m_szPacket);
	bRtnCode = Gf_setPacketSend(0, CMD_ZONE_SET, m_PacketLength, m_szPacket);

	return bRtnCode;
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
	bRtnCode = Gf_setPacketSend(nID, CMD_IF_I2C_CLOCK, m_PacketLength, m_szPacket);

	return bRtnCode;
}

BOOL CCommand::Gf_setPowerVoltSet(int nVoltName, float nVoltValue)
{
	BOOL bRtnCode=FALSE;
	CString sdata = _T("");

	sdata.Format(_T("%01d%03d"), nVoltName, (int)((nVoltValue*10.0)+0.5));
	wchar_To_char(sdata.GetBuffer(0), m_szPacket);
	m_PacketLength = (int)strlen(m_szPacket);
	bRtnCode = Gf_setPacketSend(0x00, CMD_CTRL_POWER_VOLT, m_PacketLength, m_szPacket);

	return bRtnCode;
}

BOOL CCommand::Gf_setI2CPullupEnable(int nID)
{
	CString sdata=_T("");
	BOOL bRtnCode=FALSE;
	nID |= 0x10;

	nID&=0xF0;

	sdata.Format(_T("%01d"), lpSystemInfo->m_nI2CPullUp);
	wchar_To_char(sdata.GetBuffer(0), m_szPacket);
	m_PacketLength = (int)strlen(m_szPacket);
	bRtnCode = Gf_setPacketSend(0x00, CMD_IF_PULLUP_ENABLE, m_PacketLength, m_szPacket);

	return bRtnCode;
}

BOOL CCommand::Gf_setGoToBootSection()
{
	return Gf_setPacketSend(0x00, CMD_CTRL_FW_GOTO_BOOT_SECTION, 0, NULL);
}

BOOL CCommand::Gf_setBluMinMax(BOOL bMinMax, int nPtnIndex)
{
	int m_nValue=0,vLine=2, hLine=4, lineOn=1, nMin=5; 
	CString sdata=_T("");

	m_nValue = _ttoi(lpModelInfo->m_sLbPtnBlu[nPtnIndex]);

	sdata.Format(_T("%02X%02X%02X%02X%02X"), m_nValue,vLine,hLine,lineOn, lpModelInfo->m_nBluMin);
	wchar_To_char(sdata.GetBuffer(0), m_szPacket);
	m_PacketLength = (int)strlen(m_szPacket);

	if(Gf_setPacketSendBLU(CMD_LEDBL_MINMAX_SET, m_PacketLength, m_szPacket) == TRUE)
	{
		if(bMinMax==_MIN_)
		{
			return Gf_setPacketSendBLU(CMD_LEDBL_MINMAX, 2, "01");
		}
		else
		{
			return Gf_setPacketSendBLU(CMD_LEDBL_MINMAX, 2, "02");
		}
	}
	else
	{
		return FALSE;
	}
}

BOOL CCommand::Gf_setBackLightFreqSet(int nFreq)
{
	CString sdata=_T("");

	sdata.Format(_T("04x"), lpSystemInfo->m_nBluFreq);
	wchar_To_char(sdata.GetBuffer(0), m_szPacket);
	m_PacketLength = (int)strlen(m_szPacket);

	return Gf_setPacketSendBLU(CMD_LEDBL_FREQ_SET, m_PacketLength, m_szPacket);
}

BOOL CCommand::Gf_setEEPRomReadData()
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

	return Gf_setPacketSend(0/*nID*/, CMD_IF_GET_EDID_ODC_AI_DATA_EXPAND,m_PacketLength, m_szPacket);	 
}

/**************************************************************************************************************************************************************/
// GFD250 Command List
BOOL CCommand::Gf_setPGInfoGFD250(CString strPtnName, BOOL bHotKeyFlags, BOOL bHkeyFlags)
{
	BOOL bRtnCode;
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

	if(lpModelInfo->m_nLcmInfoInterface == SINGLE)			nInterface=0;
	else if(lpModelInfo->m_nLcmInfoInterface == DUAL)		nInterface=1;
	else if(lpModelInfo->m_nLcmInfoInterface == QUAD)		nInterface=2;

	sdata.Format(_T("%02X"), (nInterface | nMode | nBitsSwap));						makePacket.Append(sdata);
	sdata.Format(_T("%01X"), (nDotClockInv | nHsyncPolarity | nVsyncPolarity));		makePacket.Append(sdata);
	sdata.Format(_T("%04d"), lpModelInfo->m_nTimingHorActive);						makePacket.Append(sdata);
	sdata.Format(_T("%04d"), lpModelInfo->m_nTimingVerActive);						makePacket.Append(sdata);

	float fMclk;
	if(lpModelInfo->m_nLcmInfoInterface == SINGLE)
		fMclk = lpModelInfo->m_fTimingFreq;
	else if(lpModelInfo->m_nLcmInfoInterface == DUAL)
		fMclk = (lpModelInfo->m_fTimingFreq / 2.f);
	else if(lpModelInfo->m_nLcmInfoInterface == QUAD)
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

	bRtnCode = Gf_setPacketSendGfd250(TARGET_GFD250, NIOS_CMD, 0/*nID*/, 0x08, m_PacketLength, m_szPacket);

	return bRtnCode;
}
