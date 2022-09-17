#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CommApi.h : header file
//
#include "_GlobalDefine.h"


typedef struct _ST_FUSINGINFO_{
	// Page1. Power Setting
	int   m_nPowerSequenceV;
	int   m_nSequence1stDelay;
	int   m_nSequence2ndDelay;
	int   m_nSequence3rdDelay;
	float m_fLimitVccHigh;
	float m_fLimitVccLow;


	// Page1. Aging Setting
	int		m_nAgingAGPModeSet;
	float	m_fAgingPatternInterval;
	int		m_nAgingCurPatternIdx;
	int		m_nAgingPatternCount;
	CString	m_sAgingPtnListName[PTNLST_MAX];
	int		m_nAgingPtnListFG[PTNLST_MAX];
	int		m_nAgingPtnListScrollSpeed[PTNLST_MAX];

	// Page1. GB Pattern Info
	int		m_nGBCurPatternIdx;
	int		m_nGBPatternCount;
	CString	m_sGBPtnListName[PTNLST_MAX];
	int		m_nGBPtnListFG[PTNLST_MAX];

	// Page1. CB Pattern Info
	int		m_nCBCurPatternIdx;
	int		m_nCBPatternCount;
	CString	m_sCBPtnListName[PTNLST_MAX];
	int		m_nCBPtnListFG[PTNLST_MAX];

	// Page1. I2C Info
	int		m_nI2CClockSet;
	int		m_nI2CPullUpSet;

	// Page1. Burnt Check OnOff
	int		m_nBurntCheck;

	float	m_fCycleStart;
	float	m_fCycleEnd;
	float	m_fCycleTime;
	int		m_nCycleOnDelay;
	int		m_nPowerOffOnUsed;

	CString m_sPatternGroupName;

}FUSINGINFO, *LPFUSINGINFO;


typedef struct _ST_MODELSETINFO_{

	char gszModelName[32];
	CString gstrModelCode;

	int m_nSignalType;
	int m_nSignalBit;
	int m_nSignalInterface;
	int m_nSignalBitSwap;
	int m_nBitSel;
	int m_nLGDISMSelect;
	int m_nALPDPModelSel;
	int m_nSpiMode;
	int m_nSpiLevel;
	int m_nCableOpenUse;
	int m_nShortTestUse;
	
	int m_nEdidUse;
	int m_nEdidAddr;
	int m_nEdidLine;
	int m_nEdidSize;
	int m_nEEPRomType;
	int m_nEEPRomAddr;

	int m_nVocmAddr;
	int m_nVcomLine;
	int m_nVcomMinMaxUse;
	int m_nVcomMin;
	int m_nVcomMax;
	int m_nVcomDefault;
	int m_nVcomDrop;	
	int m_nVcomBitShift;

	int m_nPixelType;
	int m_nLcmInfoMode;
	int m_nLcmInfoBitsSwap;
	int m_nClockDelay;
	int m_nClockRising;
	int m_nHSyncPolarity;
	int m_nVSyncPolarity;
	int m_nOddEven;

	int m_nPowerOnSeqType01;
	int m_nPowerOnSeqType02;
	int m_nPowerOnSeqType03;
	int m_nPowerOnSeqType04;
	int m_nPowerOnSeqType05;
	int m_nPowerOnSeqType06;
	int m_nPowerOnSeqType07;
	int m_nPowerOnSeqType08;
	int m_nPowerOnSeqType09;
	int m_nPowerOnSeqType10;
	int m_nPowerOnSeqType11;
	int m_nPowerOnSeqType12;
	int m_nPowerOnSeqType13;
	int m_nPowerOnSeqType14;
	int m_nPowerOnSeqType15;
	int m_nPowerOnSeqType16;
	int m_nPowerOnSeqType17;
	int m_nPowerOffSeqType01;
	int m_nPowerOffSeqType02;
	int m_nPowerOffSeqType03;
	int m_nPowerOffSeqType04;
	int m_nPowerOffSeqType05;
	int m_nPowerOffSeqType06;
	int m_nPowerOffSeqType07;
	int m_nPowerOffSeqType08;
	int m_nPowerOffSeqType09;
	int m_nPowerOffSeqType10;
	int m_nPowerOffSeqType11;
	int m_nPowerOffSeqType12;
	int m_nPowerOffSeqType13;
	int m_nPowerOffSeqType14;
	int m_nPowerOffSeqType15;
	int m_nPowerOffSeqType16;
	int m_nPowerOffSeqType17;
	int m_nPowerOnSeqDelay01;
	int m_nPowerOnSeqDelay02;
	int m_nPowerOnSeqDelay03;
	int m_nPowerOnSeqDelay04;
	int m_nPowerOnSeqDelay05;
	int m_nPowerOnSeqDelay06;
	int m_nPowerOnSeqDelay07;
	int m_nPowerOnSeqDelay08;
	int m_nPowerOnSeqDelay09;
	int m_nPowerOnSeqDelay10;
	int m_nPowerOnSeqDelay11;
	int m_nPowerOnSeqDelay12;
	int m_nPowerOnSeqDelay13;
	int m_nPowerOnSeqDelay14;
	int m_nPowerOnSeqDelay15;
	int m_nPowerOnSeqDelay16;
	int m_nPowerOnSeqDelay17;
	int m_nPowerOffSeqDelay01;
	int m_nPowerOffSeqDelay02;
	int m_nPowerOffSeqDelay03;
	int m_nPowerOffSeqDelay04;
	int m_nPowerOffSeqDelay05;
	int m_nPowerOffSeqDelay06;
	int m_nPowerOffSeqDelay07;
	int m_nPowerOffSeqDelay08;
	int m_nPowerOffSeqDelay09;
	int m_nPowerOffSeqDelay10;
	int m_nPowerOffSeqDelay11;
	int m_nPowerOffSeqDelay12;
	int m_nPowerOffSeqDelay13;
	int m_nPowerOffSeqDelay14;
	int m_nPowerOffSeqDelay15;
	int m_nPowerOffSeqDelay16;
	int m_nPowerOffSeqDelay17;

	float m_fTimingFreq;
	int	m_nTimingHorActive;
	int	m_nTimingHorBack_P;
	int	m_nTimingHorFront_P;
	int	m_nTimingHorTotal;
	int	m_nTimingHorWidth;
	int	m_nTimingVerActive;
	int	m_nTimingVerBack_P;
	int	m_nTimingVerFront_P;
	int	m_nTimingVerTotal;
	int	m_nTimingVerWidth;

	float m_fVoltVcc;
	float m_fVoltVdd;
	float m_fVoltVgh;
	float m_fVoltVgl;
	float m_fVoltVbr;
	float m_fVoltVbl;
	float m_fLimitVccMax;
	float m_fLimitVccMin;
	float m_fLimitVddMax;
	float m_fLimitVddMin;
	float m_fLimitVblMax;
	float m_fLimitVblMin;
	float m_fLimitIccMax;
	float m_fLimitIccMin;
	float m_fLimitIddMax;
	float m_fLimitIddMin;
	float m_fLimitVghMax;
	float m_fLimitVghMin;
	float m_fLimitVglMax;
	float m_fLimitVglMin;
	float m_fLimitIghMax;
	float m_fLimitIghMin;
	float m_fLimitIglMax;
	float m_fLimitIglMin;
	float m_fLimitIblMax;
	float m_fLimitIblMin;
	int	  m_nIccCheck;

	float m_fVoltVcom1;
	float m_fVoltVcom2;
	float m_fVoltGamma[32];

	BYTE gucFGColor;
	BYTE gucLineColor;

	int m_nGfd100Use;
	int m_nBluMin;
	int m_nSolomonMipi;
	int m_nDp501InitCode;

	int m_nAgpOnOff;

	int m_nI2cPullup;
	int m_nI2cFreq;
	int m_nI2cLevel;

	int		m_nLbCnt;
	CString m_sLbPtnName[TOTALPATTERN];
	CString m_sLbPtnVcc[TOTALPATTERN];
	CString m_sLbPtnVdd[TOTALPATTERN];
	CString m_sLbPtnTms[TOTALPATTERN];
	CString m_sLbPtnVsync[TOTALPATTERN];
	CString m_sLbPtnBlu[TOTALPATTERN];
	CString m_sLbPtnIccLow[TOTALPATTERN];
	CString m_sLbPtnIccHigh[TOTALPATTERN];
	CString m_sLbPtnIddLow[TOTALPATTERN];
	CString m_sLbPtnIddHigh[TOTALPATTERN];
	CString m_sHotPattern[10];
	int m_nHotPatternGrayFg[10];
	int m_nHotPatternGrayBg[10];

	CString m_sMicroPtnPath;

}MODELSETINFO, *LPMODELSETINFO;


typedef struct _ST_SYSTEMINFO_{

	CString m_sMachinName;
	CString m_sModelName;
	int		m_nBluType;
	int		m_nBluFreq;
	int		m_nTestStartDelay;

	int		m_nPGSystemType;
	int		m_nMeasureInterval;

	int		m_nPgPort;
	int		m_nAutoBcrPort;	
	int		m_nLedBlPort;

	CString m_sModelDnPath;
	CString m_sPatternPath;
	CString m_sEdidDnPath;
	CString	m_sPmIcDnPath;
	CString m_sAitRefSpecDnPath;

	int		m_nGrayAdjustStepUpDown;
	int		m_nGrayAdjustStepLeftRight;
	int		m_nPvcomAdjStepUpDown;
	int		m_nPvcomAdjStepLeftRight;

	int m_nI2CPullUp;
	int m_nI2CClock;

	int m_nFinalIdInputMode;
	int m_nIFBoardSelect;
	int m_neDPInitCodeSelect;

	int gucIdReadMode;
	int gnVblMaxVol;

	CString strHotPattern[10];
	int nHotPatternGrayFg[10];
	int nHotPatternGrayBg[10];

	int nAbnormalCode;


	int gnITLEDType;




	int m_nPalletSystem;

	int gucOfflinePVcom;
	int gnPowerOnDelay;

	int gnI2CReadDelay;



	BOOL	m_bEthernetEnable;

	BOOL	m_bLan1Enable;
	int		m_nLan1IPAddress0;
	int		m_nLan1IPAddress1;
	int		m_nLan1IPAddress2;
	int		m_nLan1IPAddress3;



	// GMES 정보
	CString		sMesServicePort;
	CString		sMesNetWork;
	CString		sMesDaemonPort;
	CString		sMesLocalSubject;
	CString		sMesRemoteSubject;
	CString		sLocalIP;

	CString		sEasServicePort;
	CString		sEasNetWork;
	CString		sEasDaemonPort;
	CString		sEasLocalSubject;
	CString		sEasRemoteSubject;


}SYSTEMINFO, *LPSYSTEMINFO;


typedef struct _ST_INSPWORKINFO_{
	char m_szUserID[20];
	char m_szUserName[20];
	char szHostModel[50];
	char szHostError[255];
	char szHostBuff[1024];
	char szBadPattern[30];
	int gnNgCnt;
	int gnTotalCnt;
	int gnGoodCnt;

	char chJudge;
	char szNgCode[20];
	char Edid;
	char szPass[16];
	CString strAgingYN;

	//= Variable for Abnormal Insp =//
	char strAbnormal_BeforePanelID[20];
	char strAbnormal_Defect_Code[50];
	char strAbnormal_NowPanelID[20];			//2009.09.09 add KSM.
	BOOL bAbnormal_ESC;
	CString strAbnormal_LogTT[20];
	//==============================//

	// 2011-01-04 PDH. Work Log 변경 관련 Variable 추가
	int logT1PalletIn;
	int logT1PowerOn;
	BOOL logMKey;
	CString logEdidRdChkSum;
	CString logVcomCompare;
	CString logOdcCompare;
	CString logPGammaCompare;
	CString logIRDAConnect;
	CString logRFIDConnect;
	CString logDSUBConnect;
	CString m_slogStartTime;			// Control Work Log
	CString m_slogEndTime;				// Control Work Log
	CString logErrMessage;			// Control Work Log




	//==============================//

	CString m_sUserID;
	CString m_sUserName;


	bool	m_bPIDReadComplete;
	CString	m_sReceivePID;
	CString	m_sPID;

	int m_nFastDioJudge;
	
	bool m_bGieJudgeOk;
	bool m_bGieJudgeNg;
	
	int m_nGoodCnt;
	int m_nBadCnt;

	bool m_bDioJigArrived;
	bool m_bDioTestStart;
	bool m_bDioJudgeOk;
	bool m_bDioSwitch1;
	bool m_bDioSwitch2;
	bool m_bDioJudgeNg;
	bool m_bDioPassMode;
	bool m_bDioPajuJudgeBGrade;

	bool m_bIsEdidFail;

	CString m_sBadCode;
	CString m_sExpectedCode;
	CString m_sBadPattern;
	int m_nPassOrFail;
	
	bool m_bEscDetect;

	CString m_sFirmwareVersion;
	CString m_sFpgaVersion;

	BOOL m_bBmpDoneCheck;

}INSPWORKINFO, *LPINSPWORKINFO;

