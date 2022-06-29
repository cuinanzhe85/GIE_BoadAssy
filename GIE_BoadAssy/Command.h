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
	BOOL Gf_setPacketSend(BYTE nId, int nCommand, int nSize, char* pdata);
	BOOL Gf_setPacketSendGfd250(BYTE nTarget, BYTE nMSCmd, BYTE nId, BYTE nCmd, int nLength, char* pData);
	BOOL Gf_setPacketSendBLU(BYTE nCmd, int nLength, char* pData);

	BOOL Gf_setFusingSystemInfo();
	BOOL gf_setPGInfoPatternString(CString ptn_string);
	CString MakeT2PtnDataGFD250(CString szPtnName, BOOL bHotKeyFlags, BOOL bHkeyFlags);
	CString MakeT2PtnFusingData(CString strPtnName, BOOL bHotKeyFlags, BOOL bHkeyFlags);


	BOOL Gf_getPowerMeasure(int nID=0);
	
	BOOL Gf_getAreYouReady();
	BOOL Gf_setI2cClock(int nID);


	BOOL Gf_setPowerVoltage( float fVcc, float fVdd, float fVbl, float fVbr);
	BOOL Gf_setPowerOnOff(int nID, int nSel, int nOnOff);
	BOOL Gf_setPowerSeqOnOff(int nOnOff);
	void Gf_setIF5VPowerOffOn(BOOL onoff);

	BOOL Gf_set810BitSel(int nID, int nBit);
	BOOL Gf_setLGDISMsel(int nID, int nLgDism);
	BOOL Gf_setPGInfoGFD250(CString strPtnName, BOOL bHotKeyFlags=FALSE, BOOL bHkeyFlags=FALSE);
	BOOL Gf_setPGInfo(CString strPtnName, BOOL bHotKeyFlags=FALSE, BOOL bHkeyFlags=FALSE);
	BOOL Gf_setpgGrayInfo(CString ptn_str);
	BOOL Gf_setPG_F1Key_VttSet(int nBitsSwap);
	BOOL Gf_setZoneSel(int nZoneSel);
	BOOL Gf_setPowerVoltSet(int nVoltName, float nVoltValue);
	BOOL Gf_setI2CPullupEnable(int nID=0);
	void Gf_ShowMessageBox(CString strMessage);
	BOOL Gf_setBluMinMax(BOOL bMinMax, int nPtnIndex);
	BOOL Gf_setBackLightFreqSet(int nFreq);
	BOOL Gf_setEEPRomReadData();

	BOOL Gf_getFirmwareVersion();	
	BOOL Gf_setGoToBootSection();	

	BOOL Gf_setGFD250Timeing();
	BOOL Gf_serGfd250SignalOnOff(char onoff);
	BOOL Gf_serGfd250SignalSelect(char sel);
	BOOL Gf_serGfd250FirmwareVersion();
	BOOL Gf_serGfd250GoToBootSection();
	BOOL Gf_getGfd250I2CReadPacketSend(int nStartReg, int ReadNum, int Cmd);
protected:
	LPMODELSETINFO	lpModelInfo;
	LPSYSTEMINFO	lpSystemInfo;
	LPINSPWORKINFO	lpWorkInfo;

	char m_szPacket[4096];
	int m_PacketLength;

	void Lf_makeSystemFusingData(char* packet);
	BOOL Lf_SyncAckFusingMessage(int nMessage);
	BOOL Lf_setIF5VPowerOffOn(int offon);
	CString Lf_MakeF1Key_VttData(int nBitsSwap);
	CString Lf_ModifyPtn_RGB(CString strPtnName, CString lpData, int nPtnIndex, BOOL bHotKeyEnable);
protected:
	DECLARE_MESSAGE_MAP()


};


