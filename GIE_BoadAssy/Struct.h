#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CommApi.h : header file
//
#include "GlobalDefine.h"


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
	int m_nLaneCurrPreEmp;
	int m_nSpiMode;
	int m_nSpiLevel;
	
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

	int m_nLcmInfoInterface;
	int m_nLcmInfoMode;
	int m_nLcmInfoBitsSwap;
	int m_nLcmInfoDotClockInv;
	int m_nLcmInfoHsyncPolarity;
	int m_nLcmInfoVsyncPolarity;

	int m_nClockIncDec;
	float m_fClockDelay;

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
	float m_fLimitVccMax;
	float m_fLimitVddMax;
	float m_fLimitIccMax;
	float m_fLimitIddMax;
	int	  m_nIccCheck;

	BYTE gucFGColor;
	BYTE gucLineColor;

	int m_nMicroPtnCnt;
	int m_nGfd100Use;
	int m_nBluMin;
	int m_nSolomonMipi;
	int m_nDp501InitCode;

	int m_nPwrSeq;
	int m_nSeqDelay;

	int m_nAgpOnOff;
	int m_nBistOnOff;
	int m_nGfd250;

	int		m_nLbCnt;
	CString m_sLbPtnName[TOTALPATTERN];
	CString m_sLbPtnFg[TOTALPATTERN];
	CString m_sLbPtnBg[TOTALPATTERN];
	CString m_sLbPtnVcc[TOTALPATTERN];
	CString m_sLbPtnVdd[TOTALPATTERN];
	CString m_sLbPtnTms[TOTALPATTERN];
	CString m_sLbPtnVsync[TOTALPATTERN];
	CString m_sLbPtnVcom[TOTALPATTERN];
	CString m_sLbPtnBlu[TOTALPATTERN];
	CString m_sLbPtnTouch[TOTALPATTERN];
	CString m_sHotPattern[10];
	int m_nHotPatternGrayFg[10];
	int m_nHotPatternGrayBg[10];

	CString m_sMicroPtnPath;

}MODELSETINFO, *LPMODELSETINFO;


typedef struct _ST_SYSTEMINFO_{

	CString m_sMachinName;
	CString m_sModelName;
	int		m_nOperationMode;
	int		m_nBluType;
	int		m_nBluFreq;
	int		m_nTestStartDelay;
	int		m_nFastJudge;
	int		m_nPidNg;

	int		m_nPGSystemType;
	int		m_nMeasureInterval;

	int		m_nPgPort;
	int		m_nAutoBcrPort;	
	int		m_nGfd250Port;
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

	bool m_bDioDebugTestStart;
	bool m_bDioDebugJudgeOk;
	bool m_bDioDebugJudgeNg;

	bool	m_bPIDReadComplete;
	CString	m_sReceivePID;
	CString	m_sPID;

	int m_nFastJudge;
	
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
	
	bool m_bMicroPtnDone;
	bool m_bEscDetect;

	CString m_sFirmwareVersion;

}INSPWORKINFO, *LPINSPWORKINFO;

