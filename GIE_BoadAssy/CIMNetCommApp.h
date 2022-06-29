#pragma once

#define RTN_OK						0
#define RTN_MSG_NOT_SEND			1
#define RTN_RCV_TIMEOUT				5

#define ECS_WAIT_TIME				10000	// 10Sec

#define	ECS_MODE_EAYT				0x01
#define	ECS_MODE_UCHK				0x02
#define	ECS_MODE_EDTI				0x03
#define	ECS_MODE_PCHK				0x04
#define	ECS_MODE_IISQ				0x05
#define	ECS_MODE_EICR				0x06
#define	ECS_MODE_BICD				0x07
#define	ECS_MODE_SCLR				0x08
#define	ECS_MODE_EESR				0x09
#define	ECS_MODE_EEER				0x0A
#define	ECS_MODE_EQCC				0x0B
#define	ECS_MODE_FLDR				0x0C
#define	ECS_MODE_EPCR				0x0D
#define ECS_MODE_AGN_INSP			0x0E
#define ECS_MODE_EICR_ABNORMAL		0x0F
#define	ECS_MODE_MSET				0x10
#define	ECS_MODE_MILT				0x11
#define ECS_MODE_APDR				0x12
#define ECS_MODE_WDCR				0x13
#define ECS_MODE_AGCM				0x14
#define ECS_MODE_AGN_IN				0x15
#define ECS_MODE_AGN_OUT			0x16

class CCimNetCommApi
{
public:
	CCimNetCommApi(void);
	~CCimNetCommApi(void);

	ITIBrvDriverPtr	tib_ptr;

	CLSID			clsid_ECS;
	HRESULT			hr;

	// ----------------------------------------
	BOOL Connect();
	BOOL Init();
	BOOL CloseTibRv();
	BOOL MessageSend(int nMode);
	BOOL MessageReceive();

	BOOL GetFieldData(CString* pszSource, TCHAR* wszToken, int nMode=0);
	CString GetHostSendMessage();
	CString GetHostRecvMessage();


	void SetMessagReceiveFlag();
	void ResetMessageReceiveFlag();
	// ----------------------------------------
	// ---------------------------------------
	// ----------------------------------------
	BOOL EAYT ();
	BOOL UCHK ();
	BOOL EDTI ();
	BOOL PCHK (int ipa_mode=FALSE, int ipa_value=FALSE);
	// ----------------------------------------
	BOOL EPCR ();
	// ----------------------------------------

	BOOL IISQ ();
	BOOL EICR ();
	BOOL EICR_Abnormal ();
	BOOL MSET ();			// 2009-12-24 추가.
	BOOL APDR ();			// 2011-08-18 PDH. APDR Message 추가.
	BOOL MILT ();			// 2013.03.28. KSM. MILT Message 추가.
	BOOL WDCR ();			// 2014-11-20 PDH. WDCR Message 추가.
	BOOL FLDR ();

	// ---------------------------------------
	BOOL BICD (char * pszBuff);
	BOOL SCLR ();
	BOOL EESR ();
	BOOL EEER ();
	BOOL EQCC ();
	BOOL AGN_INSP (char * pszBcrData, char * pszBuff,char * pszNgCode, char * pszGradeCode);
	BOOL AGCM ();
	BOOL AGN_IN ();
	BOOL AGN_OUT ();
	// ---------------------------------------
	void SetLocalTest();

	// ---------------------------------------
	void MakeClientTimeString();
	void SetMesHostInterface();
	void SetLocalTimeData(CString strTime);
	void SetMachineName(char* strBuff);
	void SetUserId (CString strBuff);
	void SetRwkCode(CString strBuff);
	void SetFLDRFileName(CString strBuff);
	void SetPanelID(CString strBuff);
	void SetChannelID (CString strBuff);
	void SetBLID(CString strBuff);
	void SetSerialNumber(CString strBuff);
	void SetModelName(CString strBuff);
	void SetPalletID(CString strBuff);
	void SetPF(CString strBuff);
	void SetDefectPattern(CString strBuff);
	void SetPvcomAdjustValue(CString strBuff);
	void SetPvcomAdjustDropValue(CString strBuff);
	void SetPatternInfo(CString strBuff);
	void SetEdidStatus(CString strBuff);
	void SetOverHaulFlag(CString strBuff);
	void SetBaExiFlag(CString strBuff);
	void SetBuyerSerialNo(CString strBuff);
	void SetVthValue(CString strBuff);
	void SetBDInfo(CString strBuff);
	void SetWDRInfo(CString strBuff);
	void SetWDREnd(CString strBuff);
	void SetAPDInfo(CString strBuff);
	void SetDefectCommentCode(CString strBuff);
	void SetExpectedCode(CString strBuff);
	// ---------------------------------------
	CString GetRwkCode();




protected:
	BOOL	m_bIsLocalTestMode;

	CString m_strRemoteSubject;
	CString m_strLocalSubject;
	CString m_strNetwork;
	CString m_strServicePort;
	CString m_strDaemon;
	CString m_strLocalIP;

	CString m_strNgComment;

	CString m_strClientDate;
	CString m_strClientOldDate;
	CString m_strClientNewDate;

	CString m_strMachineName;
	CString m_strUserID;
	CString m_strRwkCode;
	CString m_strFLDRFileName;
	CString m_strPanelID;
	CString m_strBLID;
	CString m_strSerialNumber;
	CString m_strModelName;
	CString m_strPalletID;
	CString m_strPF;
	CString m_strDefectPattern;
	CString m_strPvcomAdjustValue;
	CString m_strPvcomAdjustDropValue;
	CString m_strPatternInfo;
	CString m_strEdidStatus;
	CString m_strOverHaulFlag;
	CString m_strExpectedRwk;
	CString m_strBaExiFlag;
	CString m_strBuyerSerialNo;
	CString m_strVthValue;
	CString m_strBDInfo;
	CString m_strWDRInfo;
	CString m_strWDREnd;
	CString m_strAPDInfo;
	CString m_strChannelID;

	CString m_strHostSendMessage;
	CString m_strHostRecvMessage;
	CString m_strEAYT;
	CString m_strUCHK;
	CString m_strEDTI;
	CString m_strFLDR;
	CString m_strPCHK;
	CString m_strEICR;
	CString m_strAPDR;
	CString m_strWDCR;
	CString m_strAGCM;
	CString m_strAGNIN;
	CString m_strAGNOUT;
	CString m_strDefectComCode;

};
