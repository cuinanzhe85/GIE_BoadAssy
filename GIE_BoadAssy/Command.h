#pragma once


// CCommand

class CCommand : public CWnd
{
	DECLARE_DYNAMIC(CCommand)

public:
	CCommand();
	virtual ~CCommand();

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
public:
	

	BOOL Gf_setBluDuty(int Duty);
	BOOL Gf_setBluOnOff(BOOL onoff);

	BOOL Gf_setFusingSystemInfo();
	BOOL Gf_setPGInfoPatternString(CString ptn_string, BOOL Ack = TRUE);
	CString MakeT2PtnFusingData(CString strPtnName, BOOL bHotKeyFlags, BOOL bHkeyFlags);


	BOOL Gf_getPowerMeasure(int nID=0);
	
	BOOL Gf_getAreYouReady();
	BOOL Gf_setI2cClock(int nID);
	BOOL Gf_setI2cWrite(int line, int slave, int startReg, int addrType, int wrLength, BYTE* wrpData, BOOL bMlogWrite);
	BOOL Gf_getI2cRead(int line, int slave, int startReg, int addrType, int rdLength, BYTE* rdpData);
	int makeI2cClock(int index);


	BOOL Gf_setPowerSeqOnOff(int nOnOff , int nCh = 0);	// 0: ch1, 1: ch2, 2: All

	BOOL Gf_setPGInfoPatternName(CString strPtnName, BOOL bHotKeyFlags=FALSE, BOOL bHkeyFlags=FALSE);
	BOOL Gf_setBmpPtnDisplay(CString bmpname);
	BOOL Gf_setZoneSel(int nZoneSel = 1);
	BOOL Gf_setPowerVoltSet(float vcc, float vdd, float vgh, float vgl);
	BOOL Gf_getEEPRomReadData();

	BOOL Gf_CheckCableOpen();	// 2022-08-31 cnz
	BOOL Gf_setSignalOnOff(int nCh, int OnOff);	// 0: ch1, 1: ch2, 2: All
	BOOL Gf_setPwmOnOff(int OnOff, int duty, int freq);
	BOOL Gf_setSRunnerControl(int EnableDisable);

	CString Gf_makePGPatternString(CString strPtnName);

	BOOL Gf_getFirmwareVersion();
	BOOL Gf_getFpgaeVersion();
	BOOL Gf_setGoToBootDownload();
	BOOL Gf_setGoToBootUpdate();
	BOOL Gf_setMainBoardReset();
	BOOL Gf_getGfd250FpgaVersion();

	BOOL Gf_setPacketSendGfd250(BYTE nTarget, BYTE nMSCmd, BYTE nId, BYTE nCmd, int nLength, char* pData, BOOL Ack = TRUE);
	BOOL Gf_setPGInfoGFD250(CString strPtnName, BOOL bHotKeyFlags = FALSE, BOOL bHkeyFlags = FALSE);
	CString MakeT2PtnDataGFD250(CString szPtnName, BOOL bHotKeyFlags, BOOL bHkeyFlags);
	BOOL Gf_setGFD250InfoPatternString(CString strPtnPacket, BOOL Ack = TRUE);
	BOOL Gf_setGFD250Timeing();
	BOOL Gf_serGfd250SignalOnOff(char onoff);
	BOOL Gf_serGfd250SignalSelect(char sel);
	BOOL Gf_serGfd250FirmwareVersion();
	BOOL Gf_serGfd250GoToBootSection();
	BOOL Gf_getGfd250I2CReadPacketSend(int nStartReg, int ReadNum, int Cmd);
	


	char gszudpRcvPacket[4096];
protected:
	LPMODELSETINFO	lpModelInfo;
	LPSYSTEMINFO	lpSystemInfo;
	LPINSPWORKINFO	lpWorkInfo;

	char m_szPacket[4096];
	int m_PacketLength;
	

	void Lf_makeSystemFusingData(char* packet);
	CString Lf_MakeF1Key_VttData(int nBitsSwap);
	CString Lf_ModifyPtn_RGB(CString strPtnName, CString lpData, int nPtnIndex, BOOL bHotKeyEnable);
protected:
	DECLARE_MESSAGE_MAP()


};


