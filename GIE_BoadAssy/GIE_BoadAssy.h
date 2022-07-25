
// GIE_BoadAssy.h : PROJECT_NAME 응용 프로그램에 대한 주 헤더 파일입니다.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'stdafx.h'를 포함합니다."
#endif

#include "resource.h"		// 주 기호입니다.
#include "DIO7230.h"
#include "PortController.h"
#include "Command.h"
#include "CIMNetCommApp.h"
#include "SocketUDP.h"
// CGIE_BoadAssyApp:
// 이 클래스의 구현에 대해서는 GIE_BoadAssy.cpp을 참조하십시오.
//

class CGIE_BoadAssyApp : public CWinAppEx
{
public:
	CGIE_BoadAssyApp();

// 재정의입니다.
	public:
	virtual BOOL InitInstance();

// 구현입니다.


	DECLARE_MESSAGE_MAP()
public:
	CDIO7230* m_pDio7230;
	CPortController*	m_pPort;
	CCommand*			m_pCommand;
	CCimNetCommApi*		m_pCimNet;
	CPatternView* m_pPatternView;
	CSocketUDP* m_pSocketUDP;

	LPFUSINGINFO		GetFusingInfo();
	LPSYSTEMINFO		GetSystemInfo();
	LPMODELSETINFO		GetModelInfo();
	LPINSPWORKINFO		GetWorkInfo();

public:
	void Gf_writeLogData(CString strEvent,CString strData);
	void Gf_writeLogData(char Event[MLOG_MAX_LENGTH],char Data[MLOG_MAX_LENGTH]);
	void Gf_writeInspCount(int Type);
	void Gf_loadInspCount();
	void Gf_loadSystemInfo();	
	BOOL Gf_loadMedelFile();
	BOOL Gf_loadPatternFile();
	void Gf_setSerialPort();
	void Gf_sendGfd250Data(BYTE* lpData, DWORD nSize);
	void Gf_sendBLUData(BYTE* lpData, DWORD nSize) ;
	void Gf_receivedPgAckInfo (BYTE* aByte);
	void Gf_receivedGFD250AckInfo(BYTE* aByte);
	void Gf_receivedBCRAckInfo (BYTE* aByte);
	void Gf_receivedBLUAckInfo(char* lpBuff);
	void Gf_setStartPtnLockTime(int nPtnNum);
	void Gf_setEndPtnLockTime(int nPtnNum);
	BOOL Gf_readEdidFile();
	void Gf_setPatStartCheckTime(int i);
	void Gf_setPatEndCheckTime(int i);

	BOOL Gf_gmesConnect(int nServerType);
	BOOL Gf_gmesDisConnect(int nServerType);
	BOOL Gf_gmesInitServer(BOOL nServerType);
	void Gf_setGMesGoodInfo();
	void Gf_setGMesBGradeInfo();
	void Gf_setGMesBadInfo();
	CString Gf_getGmesRTNCD();
	void Gf_showLocalErrorMsg();
	void Gf_showPanelIdNg();
	BOOL Gf_sendGmesHost(int nHostCmd);

	void InitCreateUdpSocket();
	void InitLocalHostIPAddress();
	void udp_processPacket(char* wParam, int lParam);

	BOOL udp_sendPacket(CString ipAddress, int nTarget, int nCommand, int nLength, char* pData, int recvACK=TRUE, int waitTime=2000);
	BOOL udp_procWaitRecvACK(int cmd, DWORD waitTime);
	int m_nAckCmd[255];
	char m_szMainFwVersion[256];
public:
	CString m_sModelFile;
	CString m_sSysIniFile;
	CString m_sPtnFile;
	CString m_sSerialPort1,m_sSerialPort2,m_sSerialPort3,m_sSerialPort4,m_sSerialPort5,m_sSerialPort6;

	int *pPtnIndex;
	int m_nOldVsync;
	int m_nGrayValueFg;
	int m_nGrayValueBg;
	int m_nSLockTime,m_nELockTime,m_nPtnLockTime[TOTALPATTERN],m_nPatLock[TOTALPATTERN];
	WORD m_nGrayRed,m_nGrayGreen,m_nGrayBlue;
	int m_nStartCheckTime[TOTALPATTERN],m_nEndCheckTime[TOTALPATTERN],m_nPatTime[TOTALPATTERN];

	char szCommRxBuff[BUFF_SIZE];
	char szCommRxBuff2[BUFF_SIZE];
	UINT m_nCommRxTotData;
	bool m_bRcvHex;
	int m_nRcvHexSize;

	int m_nRcvPgMsg,m_nRcvGfd250Msg,m_nRcvMsgBlu;
	int	m_nDownloadReadyAckCount;
	int	m_nDownloadCountUp;	
	
	bool m_bAreYouReady;
	int m_nLcmPInfo[10];//[0]:VCC [1]:VDD [2]:VBL [3]:ICC [4]:IDD [5]:IBL [6]:BRTI(VBR) [7]:Name [8]:Hi/Low [9]:Limit

	char m_nEEPRomReadData[1024];
	char m_nEEPRomFileData[1024];

	bool m_bMesComuCheck;
	bool m_bUserIdCheck;
	bool m_bUserIdPM;
	bool m_bUserIdGieng;

	bool m_bIsGmesConnect;
	bool m_bIsEasConnect;

	int m_nI2CCmdNumber;
	int m_nBMtoggle;
protected:
	BOOL Lf_loadEdidFile(CString spath);
	void Lf_initVariable();
	void Lf_loadModelInfo();
	void Lf_readGmesInfo();
	void Lf_parseHexData(BYTE* aByte);
	void Lf_parsingModFileData(CString szData, TCHAR (*szParseData)[255]);
	void Lf_parsingAckData(CString strAckData);
	void Lf_parsingAckGfd250Data(CString strAckData);
	void Lf_parsingMeasureAllPower(CString strAckData);
	void Lf_parseAutoBcr(BYTE* aByte);	
	void Lf_parsingEdidDataGfd250(CString strAckData);

	CString Lf_getPatternData();
	void Lf_setGmesValueEICR();

protected:
	LPFUSINGINFO			lpFusingInfo;
	LPMODELSETINFO			lpModelInfo;
	LPSYSTEMINFO			lpSystemInfo;
	LPINSPWORKINFO			lpWorkInfo;
};

extern CGIE_BoadAssyApp theApp;
extern CGIE_BoadAssyApp* m_pApp;