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
	char szpacket[512];
	int packetlen;
	sprintf_s(szpacket, "B0%04d%c", Duty, 0x0d);
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

	sprintf_s(szpacket, "L1%c", 0x0d);
	packetlen = (int)strlen(szpacket);

	m_pApp->m_nRcvMsgBlu = 0x00;

	m_pApp->Gf_sendBLUData((BYTE*)szpacket, packetlen);
	nRecCnt = 0;
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

	strTmp.Format(_T(".\\PATTERN\\%s"), strPtnName);
	strTmp = CT2CmdGen::makeT2dataStrFromFile(strTmp);
	strTmp = CT2CmdGen::makeT2PatternStr(lpModelInfo->m_nLcmInfoInterface, strTmp, lpModelInfo->m_nTimingHorActive, lpModelInfo->m_nTimingVerActive);

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

	strTmp.Format(_T(".\\PATTERN\\%s"), strPtnName);
	strTmp = CT2CmdGen::makeT2dataStrFromFile(strTmp);
	strTmp = CT2CmdGen::makeT2PatternStr(lpModelInfo->m_nLcmInfoInterface, strTmp, lpModelInfo->m_nTimingHorActive, lpModelInfo->m_nTimingVerActive);

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
	strTmp.Format(_T(".\\PATTERN\\%s"), strPtnName);
	strTmp = CT2CmdGen::makeT2dataStrFromFile(strTmp);
	retString = CT2CmdGen::makeT2PatternStr(lpModelInfo->m_nLcmInfoInterface, strTmp, lpModelInfo->m_nTimingHorActive, lpModelInfo->m_nTimingVerActive);
	return retString;
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
		bRet = m_pApp->udp_sendPacket(UDP_MAIN_IP, TARGET_CTRL, CMD_T2PTN_SEND, m_PacketLength, m_szPacket);
	}

	return bRet;
}

BOOL CCommand::Gf_getAreYouReady()
{
	BOOL bRtnCode=FALSE;

	bRtnCode = m_pApp->udp_sendPacket(UDP_MAIN_IP, TARGET_CTRL, CMD_ARE_YOU_READY, 0, NULL);

	return bRtnCode;
}

BOOL CCommand::Gf_setPowerVoltage(float fVcc, float fVdd, float fVbl, float fVbr)
{
	BOOL bRtnCode=FALSE;
	CString sdata=_T("");

	sdata.Format(_T("%03d%03d%03d%03d"), (int)(fVcc*10.0+0.5), (int)(fVdd*10.0+0.5), (int)(fVbl*10.0+0.5), (int)(fVbr*10.0+0.5));
	wchar_To_char(sdata.GetBuffer(0), m_szPacket);
	m_PacketLength = (int)strlen(m_szPacket);

	bRtnCode = m_pApp->udp_sendPacket(UDP_MAIN_IP, TARGET_CTRL, CMD_POWER_VOLTAGE_SET, m_PacketLength, m_szPacket);

	return bRtnCode;	
}

BOOL CCommand::Gf_setPowerOnOff(int nSel, int nOnOff)
{
	BOOL bRtnCode=FALSE;
	CString sdata=_T("");

	sdata.Format(_T("%01d%01d"), nSel, nOnOff);

	wchar_To_char(sdata.GetBuffer(0), m_szPacket);
	m_PacketLength = (int)strlen(m_szPacket);

	bRtnCode = m_pApp->udp_sendPacket(UDP_MAIN_IP, TARGET_CTRL, CMD_CTRL_POWER_ONOFF_SET, m_PacketLength, m_szPacket);

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

	bRtnCode = m_pApp->udp_sendPacket(UDP_MAIN_IP, TARGET_CTRL, CMD_CTRL_POWER_SEQ_ONOFF, m_PacketLength, m_szPacket);
	if (bRtnCode == TRUE)
	{
		DWORD dWait;
		if (nOnOff == POWER_ON)
			dWait = (lpModelInfo->m_nPowerOnSeqDelay01 + lpModelInfo->m_nPowerOnSeqDelay02 + lpModelInfo->m_nPowerOnSeqDelay03 + lpModelInfo->m_nPowerOnSeqDelay04 + lpModelInfo->m_nPowerOnSeqDelay05
			+ lpModelInfo->m_nPowerOnSeqDelay06 + lpModelInfo->m_nPowerOnSeqDelay07 + lpModelInfo->m_nPowerOnSeqDelay08 + lpModelInfo->m_nPowerOnSeqDelay09 + lpModelInfo->m_nPowerOnSeqDelay10
			+ lpModelInfo->m_nPowerOnSeqDelay11 + lpModelInfo->m_nPowerOnSeqDelay12 + lpModelInfo->m_nPowerOnSeqDelay13 + lpModelInfo->m_nPowerOnSeqDelay14);
		else
			dWait = (lpModelInfo->m_nPowerOffSeqDelay01 + lpModelInfo->m_nPowerOffSeqDelay02 + lpModelInfo->m_nPowerOffSeqDelay03 + lpModelInfo->m_nPowerOffSeqDelay04 + lpModelInfo->m_nPowerOffSeqDelay05
				+ lpModelInfo->m_nPowerOffSeqDelay06 + lpModelInfo->m_nPowerOffSeqDelay07 + lpModelInfo->m_nPowerOffSeqDelay08 + lpModelInfo->m_nPowerOffSeqDelay09 + lpModelInfo->m_nPowerOffSeqDelay10
				+ lpModelInfo->m_nPowerOffSeqDelay11 + lpModelInfo->m_nPowerOffSeqDelay12 + lpModelInfo->m_nPowerOffSeqDelay13 + lpModelInfo->m_nPowerOffSeqDelay14);
		delayMS(dWait + 500);
	}
	return bRtnCode;
}

BOOL CCommand::Gf_getFirmwareVersion()
{
	BOOL bRtnCode=FALSE;

	bRtnCode = m_pApp->udp_sendPacket(UDP_MAIN_IP, TARGET_CTRL, CMD_CTRL_FW_VERSION , 0, NULL);

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

	return m_pApp->udp_sendPacket(UDP_MAIN_IP, TARGET_CTRL, CMD_IF_5V_POWER_ONOFF, m_PacketLength, m_szPacket);
}

void CCommand::Gf_setIF5VPowerOffOn(BOOL onoff)
{
	if(lpModelInfo->m_nSignalType == SIG_TYPE_EDP)
	{
		Lf_setIF5VPowerOffOn(onoff);
	}
	else
	{
		Lf_setIF5VPowerOffOn(ON);
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

	bRtnCode = m_pApp->udp_sendPacket(UDP_MAIN_IP, TARGET_CTRL, CMD_MEASURE_ALL_POWER, 0, NULL);
	return bRtnCode;
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

BOOL CCommand::Gf_setPowerVoltSet(int nVoltName, float nVoltValue)
{
	BOOL bRtnCode=FALSE;
	CString sdata = _T("");

	sdata.Format(_T("%01d%03d"), nVoltName, (int)((nVoltValue*10.0)+0.5));
	wchar_To_char(sdata.GetBuffer(0), m_szPacket);
	m_PacketLength = (int)strlen(m_szPacket);

	bRtnCode = m_pApp->udp_sendPacket(UDP_MAIN_IP, TARGET_CTRL, CMD_CTRL_POWER_VOLT, m_PacketLength, m_szPacket);

	return bRtnCode;
}


BOOL CCommand::Gf_setGoToBootSection()
{
	return m_pApp->udp_sendPacket(UDP_MAIN_IP, TARGET_CTRL, CMD_CTRL_FW_GOTO_BOOT_SECTION, 0, NULL);
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
