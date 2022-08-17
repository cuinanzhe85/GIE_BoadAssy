
// GIE_BoadAssy.cpp : 응용 프로그램에 대한 클래스 동작을 정의합니다.
//

#include "stdafx.h"
#include "GIE_BoadAssy.h"
#include "GIE_BoadAssyDlg.h"
#include "UserID.h"
#include "MessageError.h"
#include "MessageQuestion.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGIE_BoadAssyApp

BEGIN_MESSAGE_MAP(CGIE_BoadAssyApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CGIE_BoadAssyApp 생성

CGIE_BoadAssyApp::CGIE_BoadAssyApp()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
	m_pApp			= (CGIE_BoadAssyApp*)AfxGetApp();
	lpSystemInfo	= new SYSTEMINFO;
	lpFusingInfo	= new FUSINGINFO;
	lpModelInfo		= new MODELSETINFO;
	lpWorkInfo		= new INSPWORKINFO;
	m_pDio7230 = new CDIO7230;
	m_pPort			= new CPortController();
	m_pCommand		= new CCommand();
	m_pCimNet		= new CCimNetCommApi;
	m_pPatternView = new CPatternView();
	m_pSocketUDP = new CSocketUDP();
}


// 유일한 CGIE_BoadAssyApp 개체입니다.

CGIE_BoadAssyApp theApp;
CGIE_BoadAssyApp* m_pApp;

// CGIE_BoadAssyApp 초기화

BOOL CGIE_BoadAssyApp::InitInstance()
{
	// 응용 프로그램 매니페스트가 ComCtl32.dll 버전 6 이상을 사용하여 비주얼 스타일을
	// 사용하도록 지정하는 경우, Windows XP 상에서 반드시 InitCommonControlsEx()가 필요합니다.
	// InitCommonControlsEx()를 사용하지 않으면 창을 만들 수 없습니다.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 응용 프로그램에서 사용할 모든 공용 컨트롤 클래스를 포함하도록
	// 이 항목을 설정하십시오.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	// 표준 초기화
	// 이들 기능을 사용하지 않고 최종 실행 파일의 크기를 줄이려면
	// 아래에서 필요 없는 특정 초기화
	// 루틴을 제거해야 합니다.
	// 해당 설정이 저장된 레지스트리 키를 변경하십시오.
	// TODO: 이 문자열을 회사 또는 조직의 이름과 같은
	// 적절한 내용으로 수정해야 합니다.
	SetRegistryKey(_T("로컬 응용 프로그램 마법사에서 생성된 응용 프로그램"));
	Lf_initVariable();//구조체 초기화
	Gf_loadSystemInfo();
	Gf_loadInspCount();
	Lf_readGmesInfo();

	InitCreateUdpSocket();
	// GMES DLL Initialize

	if (Gf_gmesInitServer(SERVER_MES) == FALSE)
	{
		AfxMessageBox(_T("TIB Driver Init Fail.\r\nPlease check whether you have installed the TibDriver and registered the MES DLL."), MB_ICONERROR);
	}
	
	CUserID idDlg;
	if(idDlg.DoModal() == IDCANCEL)
		return FALSE;

	CGIE_BoadAssyDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 여기에 [확인]을 클릭하여 대화 상자가 없어질 때 처리할
		//  코드를 배치합니다.
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 여기에 [취소]를 클릭하여 대화 상자가 없어질 때 처리할
		//  코드를 배치합니다.
	}

	// 대화 상자가 닫혔으므로 응용 프로그램의 메시지 펌프를 시작하지 않고  응용 프로그램을 끝낼 수 있도록 FALSE를
	// 반환합니다.
	return FALSE;
}

LPSYSTEMINFO CGIE_BoadAssyApp::GetSystemInfo()
{
	ASSERT (NULL!= lpSystemInfo);
	VERIFY (NULL != lpSystemInfo);

	return lpSystemInfo;
}

LPFUSINGINFO CGIE_BoadAssyApp::GetFusingInfo()
{
	ASSERT (NULL!= lpFusingInfo);
	VERIFY (NULL != lpFusingInfo);

	return lpFusingInfo;
}

LPMODELSETINFO CGIE_BoadAssyApp::GetModelInfo()
{
	ASSERT (NULL!= lpModelInfo);
	VERIFY (NULL != lpModelInfo);

	return lpModelInfo;
}

LPINSPWORKINFO CGIE_BoadAssyApp::GetWorkInfo()
{
	ASSERT (NULL!= lpWorkInfo);
	VERIFY (NULL != lpWorkInfo);

	return lpWorkInfo;
}
void CGIE_BoadAssyApp::InitCreateUdpSocket()
{
	if (m_pSocketUDP->CreatSocket(UDP_SOCKET_PORT, SOCK_DGRAM) == FALSE)
	{
		AfxMessageBox(_T("UDP Socket Create Fail"), MB_ICONERROR);
		return;
	}

	InitLocalHostIPAddress();
}

void CGIE_BoadAssyApp::InitLocalHostIPAddress()
{
	// Receive Message 처리를 제외할 자신의 IP와 GateIP를 가져온다.
	//	m_pSocketUDP->m_bEthernetInit = FALSE;

	m_pSocketUDP->getLocalIPAddress();
	m_pSocketUDP->getLocalGateWay();
}
void CGIE_BoadAssyApp::udp_processPacket(char* wParam, int lParam)
{
	char szbuf[10] = { 0, };
	int recvCMD = 0;
	int ntoken = 0;
	int recvRet = 0;

	// Receive Packet에서 Group, Command 정보를 추출한다.
	sprintf_s(szbuf, "%c%c", wParam[PACKET_PT_CMD], wParam[PACKET_PT_CMD + 1]);
	recvCMD = strtol(szbuf, 0, 16);
	recvRet = wParam[PACKET_PT_RET];

	memcpy(m_pCommand->gszudpRcvPacket, wParam, lParam);

	// Message 처리
	switch (recvCMD)
	{
	case CMD_CTRL_FUSING_SYSTEM:
		break;
	}

	m_nAckCmd[recvCMD] = TRUE;
}

void CGIE_BoadAssyApp::Gf_writeLogData(char Event[MLOG_MAX_LENGTH],char Data[MLOG_MAX_LENGTH])
{
	CString strEvent, strData;
	strEvent = char_To_wchar(Event);
	strData = char_To_wchar(Data);
}
void CGIE_BoadAssyApp::Gf_writeLogData(CString Event, CString Data)
{
	CFile file;
	USHORT nShort = 0xfeff;
	CString strFileName, strLog, path;
	CString pStrWideChar;

	SYSTEMTIME sysTime;
	::GetSystemTime(&sysTime);
	CTime time = CTime::GetCurrentTime();
	pStrWideChar.Format(_T("%s %s"), Event, Data);
	strLog.Format(_T("[%02d:%02d:%02d %03d] %06d%03d\t: %s\r\n"), time.GetHour(), time.GetMinute(), time.GetSecond(), sysTime.wMilliseconds, (time.GetHour() * 3600) + (time.GetMinute() * 60) + time.GetSecond(), sysTime.wMilliseconds, pStrWideChar);


	//	Read_SysIniFile(_T("SYSTEM"), _T("STATION_NO"), &lpSystemInfo->m_sStationNo);
	strFileName.Format(_T("%s_%04d%02d%02d"), lpSystemInfo->m_sMachinName, time.GetYear(), time.GetMonth(), time.GetDay());
	path.Format(_T(".\\MLog\\%s.txt"), strFileName);

	if ((_access(".\\MLog", 0)) == -1)
		_mkdir(".\\MLog");

	if ((_access(".\\Logs\\MLog", 0)) == -1)
		_mkdir(".\\Logs\\MLog");


	if (file.Open(path, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::typeBinary))
	{
		if (file.GetLength() == 0)
		{
			file.Write(&nShort, 2);
		}
		file.SeekToEnd();
		file.Write(strLog, (strLog.GetLength() * 2));
		file.Close();
	}
}

void CGIE_BoadAssyApp::Lf_initVariable()
{
	int i=0;

	m_bRcvHex=false;
	m_nCommRxTotData = 0;
	lpSystemInfo->m_sModelName=_T("");
	lpSystemInfo->m_sMachinName=_T("");
	lpSystemInfo->m_nMeasureInterval=0;
	lpSystemInfo->m_nOperationMode=0;
	lpSystemInfo->m_nBluType=0;
	lpSystemInfo->m_nBluFreq=0;
	lpSystemInfo->m_nTestStartDelay=0;
	lpSystemInfo->m_nPidNg=0;
	lpSystemInfo->m_nFastJudge=0;
	lpSystemInfo->m_nI2CPullUp=0;
	lpSystemInfo->m_nI2CClock=0;
	lpSystemInfo->m_nPGSystemType=0;
	lpSystemInfo->m_nPgPort=0;
	lpSystemInfo->m_nGfd250Port=0;
	lpSystemInfo->m_nAutoBcrPort=0;
	lpSystemInfo->m_nLedBlPort=0;
	lpSystemInfo->m_sModelDnPath=_T("");
	lpSystemInfo->m_sPatternPath=_T("");
	lpSystemInfo->m_sEdidDnPath=_T("");
	lpSystemInfo->m_sPmIcDnPath=_T("");
	lpSystemInfo->m_sAitRefSpecDnPath=_T("");
	lpSystemInfo->m_nFinalIdInputMode=0;
	lpSystemInfo->m_nGrayAdjustStepUpDown=0;
	lpSystemInfo->m_nGrayAdjustStepLeftRight=0;
	lpSystemInfo->m_nPvcomAdjStepUpDown=0;
	lpSystemInfo->m_nPvcomAdjStepLeftRight=0;
	lpSystemInfo->m_nIFBoardSelect=0;
	lpSystemInfo->m_neDPInitCodeSelect=0;

	lpSystemInfo->sMesServicePort.Empty();
	lpSystemInfo->sMesNetWork.Empty();
	lpSystemInfo->sMesDaemonPort.Empty();
	lpSystemInfo->sMesLocalSubject.Empty();
	lpSystemInfo->sMesRemoteSubject.Empty();
	lpSystemInfo->sLocalIP.Empty();

	lpSystemInfo->sEasServicePort.Empty();
	lpSystemInfo->sEasNetWork.Empty();
	lpSystemInfo->sEasDaemonPort.Empty();
	lpSystemInfo->sEasLocalSubject.Empty();
	lpSystemInfo->sEasRemoteSubject.Empty();

	lpModelInfo->m_nGfd250 = 0;
	lpModelInfo->m_nEdidUse=0;
	lpModelInfo->m_nEdidAddr=0;
	lpModelInfo->m_nEdidLine=0;
	lpModelInfo->m_nEdidSize=0;
	lpModelInfo->m_nEEPRomType=0;
	lpModelInfo->m_nEEPRomAddr=0;

	lpModelInfo->m_nGfd100Use=0;
	lpModelInfo->m_nSolomonMipi=0;
	lpModelInfo->m_nMicroPtnCnt=0;
	lpModelInfo->m_nBluMin=0;
	lpModelInfo->m_nDp501InitCode=0;

	lpModelInfo->m_nVocmAddr=0;
	lpModelInfo->m_nVcomLine=0;
	lpModelInfo->m_nVcomMinMaxUse=0;
	lpModelInfo->m_nVcomMin=0;
	lpModelInfo->m_nVcomMax=0;
	lpModelInfo->m_nVcomDefault=0;
	lpModelInfo->m_nVcomDrop=0;	
	lpModelInfo->m_nVcomBitShift=0;

	lpModelInfo->m_fTimingFreq=0.0;
	lpModelInfo->m_nTimingHorActive=0;
	lpModelInfo->m_nTimingHorBack_P=0;
	lpModelInfo->m_nTimingHorFront_P=0;
	lpModelInfo->m_nTimingHorTotal=0;
	lpModelInfo->m_nTimingHorWidth=0;
	lpModelInfo->m_nTimingVerActive=0;
	lpModelInfo->m_nTimingVerBack_P=0;
	lpModelInfo->m_nTimingVerFront_P=0;
	lpModelInfo->m_nTimingVerTotal=0;
	lpModelInfo->m_nTimingVerWidth=0;

	lpModelInfo->m_nLcmInfoInterface=0;
	lpModelInfo->m_nLcmInfoMode=0;
	lpModelInfo->m_nLcmInfoBitsSwap=0;
	lpModelInfo->m_nLcmInfoDotClockInv=0;
	lpModelInfo->m_nLcmInfoHsyncPolarity=0;
	lpModelInfo->m_nLcmInfoVsyncPolarity=0;
	lpModelInfo->m_nClockIncDec=0;
	lpModelInfo->m_fClockDelay=0.0;	

	lpModelInfo->m_nSignalType=0;
	lpModelInfo->m_nSignalBit=0;
	lpModelInfo->m_nSignalInterface=0;
	lpModelInfo->m_nSignalBitSwap=0;
	lpModelInfo->m_nBitSel=0;
	lpModelInfo->m_nBistOnOff=0;
	lpModelInfo->m_nLGDISMSelect=0;
	lpModelInfo->m_nALPDPModelSel=0;
	lpModelInfo->m_nLaneCurrPreEmp=0;
	lpModelInfo->m_nAgpOnOff=0;
	lpModelInfo->m_nSpiMode=0;
	lpModelInfo->m_nSpiLevel=0;

	lpModelInfo->m_fVoltVcc=0.0;
	lpModelInfo->m_fVoltVdd=0.0;
	lpModelInfo->m_fLimitVccMax=0;
	lpModelInfo->m_fLimitVddMax=0;
	lpModelInfo->m_fLimitIccMax=0;
	lpModelInfo->m_fLimitIddMax=0;
	lpModelInfo->m_nIccCheck=0;
	lpModelInfo->m_nPwrSeq=0;
	lpModelInfo->m_nSeqDelay=0;

	for(i=0; i<10; i++)
	{
		lpModelInfo->m_sHotPattern[i].Empty();
		lpModelInfo->m_nHotPatternGrayFg[i]=0;
		lpModelInfo->m_nHotPatternGrayBg[i]=0;
	}

	lpModelInfo->m_nLbCnt=0;

	for(i=0; i<TOTALPATTERN; i++)
	{
		lpModelInfo->m_sLbPtnName[i].Empty();
		lpModelInfo->m_sLbPtnFg[i].Empty();
		lpModelInfo->m_sLbPtnBg[i].Empty();
		lpModelInfo->m_sLbPtnVcc[i].Empty();
		lpModelInfo->m_sLbPtnVdd[i].Empty();
		lpModelInfo->m_sLbPtnTms[i].Empty();
		lpModelInfo->m_sLbPtnVsync[i].Empty();
		lpModelInfo->m_sLbPtnVcom[i].Empty();
		lpModelInfo->m_sLbPtnBlu[i].Empty();
		lpModelInfo->m_sLbPtnTouch[i].Empty();
	}

	lpWorkInfo->m_bPIDReadComplete = false;
	lpWorkInfo->m_bDioDebugTestStart = false;
	lpWorkInfo->m_bDioDebugJudgeOk = false;
	lpWorkInfo->m_bDioDebugJudgeNg = false;

	lpWorkInfo->m_bGieJudgeNg = false;
	lpWorkInfo->m_bGieJudgeOk = false;


	lpWorkInfo->m_bDioJigArrived = false;
	lpWorkInfo->m_bDioTestStart = false;
	lpWorkInfo->m_bDioJudgeOk = false;
	lpWorkInfo->m_bDioSwitch1 = false;
	lpWorkInfo->m_bDioSwitch2 = false;
	lpWorkInfo->m_bDioJudgeNg = false;
	lpWorkInfo->m_bDioPassMode = false;
	lpWorkInfo->m_bDioPajuJudgeBGrade = false;

	lpWorkInfo->m_nPassOrFail=0;

	lpWorkInfo->m_nGoodCnt=0;
	lpWorkInfo->m_nBadCnt=0;
	lpWorkInfo->m_bMicroPtnDone=false;
	lpWorkInfo->m_sBadPattern.Empty();
}

void CGIE_BoadAssyApp::Lf_readGmesInfo()
{
	Read_SysIniFile(_T("GMES"), _T("SERVICE"), &lpSystemInfo->sMesServicePort);
	Read_SysIniFile(_T("GMES"), _T("NETWORK"), &lpSystemInfo->sMesNetWork);
	Read_SysIniFile(_T("GMES"), _T("DAEMON_PORT"), &lpSystemInfo->sMesDaemonPort);
	Read_SysIniFile(_T("GMES"), _T("LOCAL_SUBJECT"), &lpSystemInfo->sMesLocalSubject);
	Read_SysIniFile(_T("GMES"), _T("REMOTE_SUBJECT"), &lpSystemInfo->sMesRemoteSubject);
	Read_SysIniFile(_T("GMES"), _T("LOCAL_IP"), &lpSystemInfo->sLocalIP);
}

void CGIE_BoadAssyApp::Lf_parsingModFileData(CString szData, TCHAR (*szParseData)[255])
{
	TCHAR szTemp[100];

	int nCnt=0;
	int nItemCnt=0;
	int nLoop=0;

	memset(szTemp, 0, sizeof(szTemp));
	int nCmdLength = szData.GetLength();//_tcslen(szData);

	for(nLoop=0; nLoop<=nCmdLength; nLoop++)
	{
		szTemp[nCnt] = szData[nLoop];
		if( (szData[nLoop]==',') || (nLoop == nCmdLength) )
		{
			szTemp[nCnt]=NULL; 
			_stprintf_s(szParseData[nItemCnt++],100,_T("%s"),szTemp);
			for(int i=0; i<=nCnt; i++)
				szTemp[i]=NULL;
			nCnt=0;
		}
		nCnt++;
		if(szData[nLoop]==',') nCnt = 0;
	}
}

void CGIE_BoadAssyApp::Gf_loadSystemInfo()
{
	Read_SysIniFile(_T("SYSTEM"),		_T("LAST_MODELNAME"),				&lpSystemInfo->m_sModelName);
	Read_SysIniFile(_T("SYSTEM"),		_T("MACHIN_NAME"),					&lpSystemInfo->m_sMachinName);
	Read_SysIniFile(_T("SYSTEM"),		_T("MEASURE_INTERVAL"),				&lpSystemInfo->m_nMeasureInterval);
	Read_SysIniFile(_T("SYSTEM"),		_T("OPERATION_MODE"),				&lpSystemInfo->m_nOperationMode);
	Read_SysIniFile(_T("SYSTEM"),		_T("BLU_TYPE"),						&lpSystemInfo->m_nBluType);
	Read_SysIniFile(_T("SYSTEM"),		_T("BLU_FREQ"),						&lpSystemInfo->m_nBluFreq);
	Read_SysIniFile(_T("SYSTEM"),		_T("TEST_START_DELAY"),				&lpSystemInfo->m_nTestStartDelay);
	Read_SysIniFile(_T("SYSTEM"),		_T("FAST_JUDGE"),					&lpSystemInfo->m_nFastJudge);
	Read_SysIniFile(_T("SYSTEM"),		_T("PID_NG"),						&lpSystemInfo->m_nPidNg);
	



	Read_SysIniFile(_T("SYSTEM"),		_T("I2C_PULL_UP"),					&lpSystemInfo->m_nI2CPullUp);
	Read_SysIniFile(_T("SYSTEM"),		_T("I2C_FREQ"),						&lpSystemInfo->m_nI2CClock);
	Read_SysIniFile(_T("SYSTEM"),		_T("PG_TYPE"),						&lpSystemInfo->m_nPGSystemType);
	Read_SysIniFile(_T("SYSTEM"),		_T("IRDA_PORT"),					&lpSystemInfo->m_nPgPort);
	Read_SysIniFile(_T("SYSTEM"),		_T("GFD250_PORT"),					&lpSystemInfo->m_nGfd250Port);
	Read_SysIniFile(_T("SYSTEM"),		_T("AUTO_BCR_PORT"),				&lpSystemInfo->m_nAutoBcrPort);
	Read_SysIniFile(_T("SYSTEM"),		_T("LED_BL_PORT"),					&lpSystemInfo->m_nLedBlPort);
	Read_SysIniFile(_T("SYSTEM"),		_T("MODEL_FILE_PATH"),				&lpSystemInfo->m_sModelDnPath);
	Read_SysIniFile(_T("SYSTEM"),		_T("PATTERN_FILE_PATH"),			&lpSystemInfo->m_sPatternPath);
	Read_SysIniFile(_T("SYSTEM"),		_T("EDID_PATH"),					&lpSystemInfo->m_sEdidDnPath);
	Read_SysIniFile(_T("SYSTEM"),		_T("PMIC_PATH"),					&lpSystemInfo->m_sPmIcDnPath);
	Read_SysIniFile(_T("SYSTEM"),		_T("AIT_REF_SPEC"),					&lpSystemInfo->m_sAitRefSpecDnPath);
	Read_SysIniFile(_T("SYSTEM"),		_T("INPUT_MODE"),					&lpSystemInfo->m_nFinalIdInputMode);
	Read_SysIniFile(_T("SYSTEM"),		_T("PVCOM_ADJ_UD"),					&lpSystemInfo->m_nPvcomAdjStepUpDown);
	Read_SysIniFile(_T("SYSTEM"),		_T("PVCOM_ADJ_LR"),					&lpSystemInfo->m_nPvcomAdjStepLeftRight);
	Read_SysIniFile(_T("SYSTEM"),		_T("GRAY_ADJ_UD"),					&lpSystemInfo->m_nGrayAdjustStepUpDown);
	Read_SysIniFile(_T("SYSTEM"),		_T("GRAY_ADJ_LR"),					&lpSystemInfo->m_nGrayAdjustStepLeftRight);
	Read_SysIniFile(_T("SYSTEM"),		_T("IF_BD_SELECT"),					&lpSystemInfo->m_nIFBoardSelect);
	Read_SysIniFile(_T("SYSTEM"),		_T("EDP_INIT_CODE_SEL"),			&lpSystemInfo->m_neDPInitCodeSelect);

	m_sSysIniFile.Format(_T("%s"),_T("Module Load OK"));
}

void CGIE_BoadAssyApp::Gf_loadInspCount()
{
	Read_SysIniFile(_T("SYSTEM"),		_T("GOOD_COUNT"),						&lpWorkInfo->m_nGoodCnt);
	Read_SysIniFile(_T("SYSTEM"),		_T("BAD_COUNT"),						&lpWorkInfo->m_nBadCnt);
}

void CGIE_BoadAssyApp::Gf_writeInspCount(int Type)
{
	if(Type == GOOD_CNT) 
	{
		lpWorkInfo->m_nGoodCnt++;
		Write_SysIniFile(_T("SYSTEM"), _T("GOOD_COUNT"), lpWorkInfo->m_nGoodCnt);
	}

	if(Type == BAD_CNT)
	{
		lpWorkInfo->m_nBadCnt++;
		Write_SysIniFile(_T("SYSTEM"), _T("BAD_COUNT"), lpWorkInfo->m_nBadCnt);
	}

//	CreateInfoUpdate();
}

void CGIE_BoadAssyApp::Lf_loadModelInfo()
{
	CString sdata = _T("");
	CString strKey = _T("");
	int nLoop = 0;
	TCHAR szParseData[255][255] = {0,};
	char modelName[64]={0,};

	Read_SysIniFile(_T("SYSTEM"),		_T("LAST_MODELNAME"),				&lpSystemInfo->m_sModelName);
	wchar_To_char(lpSystemInfo->m_sModelName.GetBuffer(0), modelName);

	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("MAIN_CLOCK"),		&lpModelInfo->m_fTimingFreq);	
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("HOR_TOTAL"),		&lpModelInfo->m_nTimingHorTotal);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("HOR_ACTIVE"),		&lpModelInfo->m_nTimingHorActive);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("HOR_BACKPORCH"),	&lpModelInfo->m_nTimingHorBack_P);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("HOR_FRONTPORCH"),	&lpModelInfo->m_nTimingHorFront_P);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("HOR_WIDTH"),		&lpModelInfo->m_nTimingHorWidth);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("VER_TOTAL"),		&lpModelInfo->m_nTimingVerTotal);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("VER_ACTIVE"),		&lpModelInfo->m_nTimingVerActive);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("VER_BACKPORCH"),	&lpModelInfo->m_nTimingVerBack_P);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("VER_FRONTPORCH"),	&lpModelInfo->m_nTimingVerFront_P);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("VER_WIDTH"),		&lpModelInfo->m_nTimingVerWidth);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("INTERFACE"),		&lpModelInfo->m_nLcmInfoInterface);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("BITSWAP"),			&lpModelInfo->m_nLcmInfoBitsSwap);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("INCDEC"),			&lpModelInfo->m_nClockIncDec);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("CLKDELAY"),			&lpModelInfo->m_fClockDelay);

	//-------------------------------------- EDID INFO
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("EDID_USE"),				&lpModelInfo->m_nEdidUse);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("EDID_ADDR"),			&lpModelInfo->m_nEdidAddr);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("EDID_LINE"),			&lpModelInfo->m_nEdidLine);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("EEPROM_ADDR"),			&lpModelInfo->m_nEEPRomAddr);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("EEPROM_TYPE"),			&lpModelInfo->m_nEEPRomType);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("EDID_SIZE"),			&lpModelInfo->m_nEdidSize);

	//-------------------------------------- PVCOM INFO
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("VCOM_ADDR"),			&lpModelInfo->m_nVocmAddr);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("VCOM_LINE"),			&lpModelInfo->m_nVcomLine);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("VCOM_BITSHIFT"),		&lpModelInfo->m_nVcomBitShift);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("VCOM_MIN"),				&lpModelInfo->m_nVcomMin);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("VCOM_MAX"),				&lpModelInfo->m_nVcomMax);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("VCOM_DEFAULT"),			&lpModelInfo->m_nVcomDefault);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("VCOM_DROP"),			&lpModelInfo->m_nVcomDrop);

	//-------------------------------------- Function INFO
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("GFD100_USE"),			&lpModelInfo->m_nGfd100Use);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("DP501_INIT_CODE"),		&lpModelInfo->m_nDp501InitCode);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("SOLOMON_MIPI"),			&lpModelInfo->m_nSolomonMipi);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("SPI_MODE"),				&lpModelInfo->m_nSpiMode);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("SPI_LEVEL"),			&lpModelInfo->m_nSpiLevel);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("BLU_MIN"),				&lpModelInfo->m_nBluMin);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("GFD250"),				&lpModelInfo->m_nGfd250);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("MICRO_PTN_CNT"),		&lpModelInfo->m_nMicroPtnCnt);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("MICRO_PTN_PATH"),		&lpModelInfo->m_sMicroPtnPath);
	
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("VCC"),					&lpModelInfo->m_fVoltVcc);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("VDD"),					&lpModelInfo->m_fVoltVdd);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("VCC_HIGH_LIMIT"),		&lpModelInfo->m_fLimitVccMax);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("VDD_HIGH_LIMIT"),		&lpModelInfo->m_fLimitVddMax);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("ICC_HIGH_LIMIT"),		&lpModelInfo->m_fLimitIccMax);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("IDD_HIGH_LIMIT"),		&lpModelInfo->m_fLimitIddMax);

	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("SIGNAL_TYPE"),			&lpModelInfo->m_nSignalType);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("SIGNAL_BIT"),			&lpModelInfo->m_nSignalBit);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("LG_DISM"),				&lpModelInfo->m_nLGDISMSelect);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("BIT_SELECT"),			&lpModelInfo->m_nBitSel);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("LANE_CUR_EMP"),			&lpModelInfo->m_nLaneCurrPreEmp);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("BIST_ONOFF"),			&lpModelInfo->m_nBistOnOff);

	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("POWER_SEQ_SEL"),		&lpModelInfo->m_nPwrSeq);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("POWER_SEQ_DELAY"),		&lpModelInfo->m_nSeqDelay);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////// Pattern File 
	lpModelInfo->m_nLbCnt = 0;

	for(nLoop=0; ;nLoop++)
	{
		strKey.Format(_T("PTN%2d"), nLoop);
		Read_ModelFile(modelName,	_T("PATTERN_INFO"),	strKey,					&sdata);
		Lf_parsingModFileData(sdata, szParseData);

		//if(*szData == NULL)//if(strParseData.IsEmpty())
		if(sdata.IsEmpty())
		{
			memset(szParseData, NULL, sizeof(szParseData));

			lpModelInfo->m_sLbPtnName[nLoop].Empty();
			//lpModelInfo->m_sLbPtnFg[nLoop].Empty();
			//lpModelInfo->m_sLbPtnBg[nLoop].Empty();
			lpModelInfo->m_sLbPtnVcc[nLoop].Empty();
			lpModelInfo->m_sLbPtnVdd[nLoop].Empty();
			lpModelInfo->m_sLbPtnTms[nLoop].Empty();
			lpModelInfo->m_sLbPtnVsync[nLoop].Empty();
			lpModelInfo->m_sLbPtnVcom[nLoop].Empty();
			lpModelInfo->m_sLbPtnBlu[nLoop].Empty();
			lpModelInfo->m_sLbPtnTouch[nLoop].Empty();
		}
		else
		{	
			lpModelInfo->m_sLbPtnName[nLoop]=szParseData[0];
			//lpModelInfo->m_sLbPtnFg[nLoop]	=szParseData[1];
			//lpModelInfo->m_sLbPtnBg[nLoop]	=szParseData[2];
			lpModelInfo->m_sLbPtnVcc[nLoop]=szParseData[1];
			lpModelInfo->m_sLbPtnVdd[nLoop]=szParseData[2];
			lpModelInfo->m_sLbPtnTms[nLoop]=szParseData[3];
			lpModelInfo->m_sLbPtnVsync[nLoop]=szParseData[4];
			lpModelInfo->m_sLbPtnVcom[nLoop].Format(_T("%s"), ((_tcslen(szParseData[5])==0) ? _T("OFF") :szParseData[5]));
			lpModelInfo->m_sLbPtnBlu[nLoop].Format(_T("%s"), ((_tcslen(szParseData[6])==0) ? _T("100") :szParseData[6]));
			lpModelInfo->m_sLbPtnTouch[nLoop].Format(_T("%s"), ((_tcslen(szParseData[7])==0) ? _T("OFF") :szParseData[7]));
			lpModelInfo->m_nLbCnt = nLoop+1;
		}

		// Data가 NULL값이 있으면 Pasing을 중단한다.
		//if(*szData==NULL)	break;
		if(sdata.IsEmpty())	
			break;
	}
}

BOOL CGIE_BoadAssyApp::Gf_loadMedelFile()
{
	CString strLFileName, strNFileName, strDataFolder;

	WIN32_FIND_DATA wfd;
	HANDLE hSearch;
	int nLoof=1;

	strDataFolder.Format(_T(".\\%s\\*.MOL"), _T("Model"));
	hSearch = FindFirstFile(strDataFolder, &wfd);

	if (hSearch != INVALID_HANDLE_VALUE)
	{
		if (wfd.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
		{
			while(nLoof)
			{
				strLFileName.Format(_T("%s.MOL"), lpSystemInfo->m_sModelName);		strLFileName.MakeUpper();
				strNFileName.Format(_T("%s"), wfd.cFileName);						strNFileName.MakeUpper();
				if(strLFileName.Compare(strNFileName)) // When model file is't existed in folder, this sentence is executed. : Difference
				{
					nLoof = FindNextFile (hSearch, &wfd);
					if(nLoof==0)
					{
						//default.mod setting
						m_sModelFile.Format(_T("%s"),_T("Model file load NG!!!"));
						Lf_loadModelInfo();
						return FALSE;
					}
				}

				strLFileName.Format(_T("%s.MOL"), lpSystemInfo->m_sModelName);		strLFileName.MakeUpper();
				strNFileName.Format(_T("%s"), wfd.cFileName);						strNFileName.MakeUpper();
				if(!strLFileName.Compare(strNFileName)) // When model file is existed in folder, this sentence is executed. : equal
				{		
					Lf_loadModelInfo();
					m_sModelFile.Format(_T("%s"),_T("Model file load OK!!"));
					break;
				}
			}
		}
		FindClose (hSearch);
	}
	else // case : When Model folder is empty,
	{
		AfxMessageBox(_T("Error Module File"), MB_ICONSTOP);
		m_sModelFile.Format(_T("%s"),_T("Error Model File"));
		Lf_loadModelInfo();
		FindClose (hSearch);
	}
	return TRUE;
}

BOOL CGIE_BoadAssyApp::Gf_loadPatternFile()
{
	CString strDatafolder=_T(""),strFileName=_T(""), strNFileName=_T("");
	WIN32_FIND_DATA wfd;
	HANDLE hSearch;
	int nLoof=1;	
	int i=0;

	strDatafolder.Format(_T(".\\Pattern\\*.pdb"));
	hSearch = FindFirstFile(strDatafolder, &wfd);

	if (hSearch != INVALID_HANDLE_VALUE)
	{		
		if (wfd.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
		{
			for(i=0; !lpModelInfo->m_sLbPtnName[i].IsEmpty(); i++)
			{	
				strFileName.Format(_T("%s.PDB"), lpModelInfo->m_sLbPtnName[i]);
				while(nLoof)
				{					
					strNFileName.Format(_T("%s"), wfd.cFileName);	strNFileName.MakeUpper();
					if(strFileName.Compare(strNFileName))
					{
						nLoof = FindNextFile (hSearch, &wfd);
						if(nLoof==0) // end of Folder
						{
							m_sPtnFile.Format(_T("%s"), _T("Pattern file load NG!!!"));
							hSearch = FindFirstFile(strDatafolder, &wfd);
							FindClose (hSearch);
							return FALSE;
						}
					}
					else if(!strFileName.Compare(strNFileName))
					{
						m_sPtnFile.Format(_T("%s"),_T("Pattern file load OK!!!"));
						hSearch = FindFirstFile(strDatafolder, &wfd);
						break;
					}
				}
				if(nLoof==0) break;
			}
		}
	}

	if( (hSearch == INVALID_HANDLE_VALUE) || ( lpModelInfo->m_sLbPtnName[0].IsEmpty() ) )
	{
		m_sPtnFile.Format(_T("%s"),_T("Pattern file load NG!!!"));
		//AfxMessageBox(_T("Error Pattern File"), MB_ICONSTOP);
		return FALSE;
	}
	return TRUE;
}

void CGIE_BoadAssyApp::Gf_setSerialPort()
{
	CString strPort = _T("");

	m_pPort->ClosePort1();
	m_pPort->ClosePort2();
	m_pPort->ClosePort3();
	m_pPort->ClosePort4();
	m_pPort->ClosePort5();
	m_pPort->ClosePort6();

	delayMS(100);

	if(lpSystemInfo->m_nGfd250Port)
	{
		strPort.Format(_T("COM%d"), lpSystemInfo->m_nGfd250Port);
		if(!(m_pPort->OpenPort2(strPort, (DWORD) 115200, NULL)))	m_sSerialPort2.Format(_T("%s"),_T("GFD250 NG."));
		else														m_sSerialPort2.Format(_T("%s"),_T("GFD250 OK."));	
	}
	else
	{
		m_sSerialPort2.Format(_T("%s"),_T("Unuse"));
	}

	if(lpSystemInfo->m_nAutoBcrPort)
	{
		strPort.Format(_T("COM%d"), lpSystemInfo->m_nAutoBcrPort);
		if(!(m_pPort->OpenPort3(strPort, (DWORD) 9600, NULL)))	m_sSerialPort3.Format(_T("%s"),_T("Auto BCR NG."));
		else													m_sSerialPort3.Format(_T("%s"),_T("Auto BCR OK."));	
	}
	else
	{
		m_sSerialPort3.Format(_T("%s"),_T("Unuse"));
	}

	if(lpSystemInfo->m_nLedBlPort)
	{
		strPort.Format(_T("COM%d"), lpSystemInfo->m_nLedBlPort);
		if(!(m_pPort->OpenPort4(strPort, (DWORD) 115200, NULL)))	m_sSerialPort4.Format(_T("%s"),_T("LED BLU NG."));
		else													m_sSerialPort4.Format(_T("%s"),_T("LED BLU OK."));	
	}
	else
	{
		m_sSerialPort4.Format(_T("%s"),_T("Unuse"));
	}
}

void CGIE_BoadAssyApp::Gf_sendGfd250Data(BYTE* lpData, DWORD nSize)
{		
	m_pPort->WritePort2(lpData, nSize);
}

void CGIE_BoadAssyApp::Gf_sendBLUData(BYTE* lpData, DWORD nSize) 
{
	m_pPort->WritePort4(lpData, nSize);
}

void CGIE_BoadAssyApp::Gf_receivedPgAckInfo (BYTE* aByte)
{
	char ucBuff[BUFF_SIZE] = {0,};
	CString strAckData=_T("");
	int nDataCnt = 0,nStart=0, nEnd=0,i=0,j=0;
	BYTE bChkStxEtx=0;
	
	if(m_bRcvHex == true)
	{
		Lf_parseHexData(aByte);
	}
	else
	{
		for(i=0; i<1024 ; i++)
		{
			if((*(aByte + i) == PACKET_STX) && (nStart==0))
			{
				nStart = i;
				bChkStxEtx |= 0x01;
			}
			if((*(aByte + i) == PACKET_ETX) && (nEnd==0))
			{
				nEnd = i;
				bChkStxEtx |= 0x10;
			}

			if(bChkStxEtx == 0x11) 
				break;
		}
		if(bChkStxEtx != 0x11)	
			return;
	}

	for(j=0; j<=(nEnd-nStart); j++)
	{
		ucBuff[j] = *(aByte + nStart + j);
	}

	strAckData.Format(_T("%s"), char_To_wchar(ucBuff));

	if(strAckData.GetLength() < 13)		
		return;
	else								
		Lf_parsingAckData(strAckData);
}

void CGIE_BoadAssyApp::Gf_receivedGFD250AckInfo(BYTE* aByte)
{
	char ucBuff[BUFF_SIZE] = {0,};
	CString strAckData=_T("");
	int nDataCnt = 0;
	int nStart=0, nEnd=0;
	BYTE bChkStxEtx=0;

	for(int i=0; i<BUFF_SIZE ; i++)
	{
		if((*(aByte + i) == PACKET_STX) && (nStart==0))
		{
			nStart = i;
			bChkStxEtx |= 0x01;
		}
		if((*(aByte + i) == PACKET_ETX) && (nEnd==0))
		{
			nEnd = i;
			bChkStxEtx |= 0x10;
		}
		if(bChkStxEtx == 0x11) 
			break;
	}

	if(bChkStxEtx != 0x11)
		return;

	for(int j=0; j<=(nEnd-nStart); j++)
	{
		ucBuff[j] = *(aByte + nStart + j);
	}

	strAckData.Format(_T("%s"), char_To_wchar(ucBuff));

	if(strAckData.GetLength() < 13)
		return;
	else
		Lf_parsingAckGfd250Data(strAckData);
}

void CGIE_BoadAssyApp::Gf_receivedBCRAckInfo(BYTE* aByte)
{
	CString sdata=_T(""),sAckData=_T("");
	
	sdata.Format(_T("Receive : %s"), char_To_wchar((char*)aByte));
	Gf_writeLogData(_T("<BCR>"), sdata);
	Lf_parseAutoBcr(aByte);
}

void CGIE_BoadAssyApp::Gf_receivedBLUAckInfo(char* lpBuff)
{
	CString sdata=_T("");
	int nDataLen=0;

	nDataLen = (int)strlen(lpBuff);

	if (nDataLen > 0)
		m_nRcvMsgBlu = TRUE;
	//if(nDataLen < 8)// Noise로 인한 PGM Down 방지.
	//	return;		

	//if((lpBuff[0]==PACKET_STX) && (lpBuff[nDataLen-1]==PACKET_ETX))
	//{
	//	sdata.Format(_T("%s"), char_To_wchar((char*)lpBuff));
	//	m_nRcvMsgBlu = _tcstol(sdata.Mid(7, 2), NULL, 16);
	//}
}

void CGIE_BoadAssyApp::Lf_parseHexData(BYTE* aByte)
{
	int total=0;
	int cmd=0;

	if(lpModelInfo->m_nEdidSize == 0)
		total = 128;
	else
		total = 256;

	if(*aByte == PACKET_STX)  
	{
		sscanf_s((char*)&aByte[7], "%02X", &cmd);			
		if(aByte[13] == '0')
		{
			memcpy(m_nEEPRomReadData, &aByte[14], total);
		}

		m_nRcvPgMsg = cmd; 
		m_bRcvHex = false;
	}
}

void CGIE_BoadAssyApp::Lf_parseAutoBcr(BYTE* aByte)
{
	int i=0, len=0, err=0;
	bool bError = true;
	CString sdata=_T("");

	len = (int)strlen((char*)aByte);

	for(i=0; i<len;i++)
	{
		if((('0' <= aByte[i]) && (aByte[i] <= '9')) 
		|| (('a' <= aByte[i]) && (aByte[i] <= 'z'))
		|| (('A' <= aByte[i]) && (aByte[i] <= 'Z')))
		{
		}
		else
		{
			bError = false;
			break;
		}
	}

	if (bError)
	{	
		sdata.Format(_T("%s"), char_To_wchar((char*)aByte));
		lpWorkInfo->m_sReceivePID = sdata;//comm.curData.strReceivePanelId = bcrData;
		lpWorkInfo->m_bPIDReadComplete = true;//comm.dio.iPcGumiBcrReadOk = TRUE;	
	}
}

void CGIE_BoadAssyApp::Lf_parsingMeasureAllPower(CString strAckData)
{
	for(int i=0; i<7; i++)
	{
		if(i==PINFO_IBL)
		{
			m_nLcmPInfo[i] = _ttoi(strAckData.Mid(14+(i*4),4)) * 10;
		}
		else
		{
			m_nLcmPInfo[i] = _ttoi(strAckData.Mid(14+(i*4),4));
		}
	}
	m_nLcmPInfo[PINFO_NAME] =	_ttoi(strAckData.Mid(42,1));
	m_nLcmPInfo[PINFO_ERR] =	_ttoi(strAckData.Mid(43,1));
	m_nLcmPInfo[PINFO_LIMIT] =	_ttoi(strAckData.Mid(44,4));
}

void CGIE_BoadAssyApp::Lf_parsingEdidDataGfd250(CString strAckData)
{
	CString sdata=_T("");
	int nLoop=0, total=0;

	if(lpModelInfo->m_nEdidSize == 0)
		total = 128;
	else
		total = 256;

	memset(m_nEEPRomReadData, 0, sizeof(m_nEEPRomReadData));

	for(nLoop=0; nLoop < total; nLoop++)
	{
		sdata = strAckData.Mid(16+(nLoop*2), 2);
		m_nEEPRomReadData[nLoop] = (char)(_tcstol(sdata.Mid(0, 2), NULL, 16));
	}
}

void CGIE_BoadAssyApp::Lf_parsingAckData(CString strAckData)
{
	CString sLog=_T("");
	int recvCMD=0;
	int nResult=0;

	if(strAckData.GetAt(0) != PACKET_STX)								
		return;						
	if(strAckData.GetAt((strAckData.GetLength()-1)) != PACKET_ETX)		
		return;

	recvCMD	= _tcstol(strAckData.Mid(7, 2), NULL, 16);
	nResult = strAckData.GetAt(13);

	if(DEBUG_RS232C_LOG)
	{
		sLog.Format(_T("CMD:0x%02X  DATA:%s"), recvCMD, strAckData); 

		Gf_writeLogData(_T("<RS232_R>"), sLog.GetBuffer(0));
	}

	switch(recvCMD)
	{
	case CMD_CTRL_FUSING_SYSTEM:
		{
			switch(nResult)
			{
			case '0':
				break;
			}			
		}break;
	
	case CMD_ARE_YOU_READY:
		switch(nResult)
		{
		case '0':
			m_bAreYouReady = true;
			break;
		}break;

	case CMD_MEASURE_ALL_POWER:
		{
			Lf_parsingMeasureAllPower(strAckData);
		}break;

	case CMD_CTRL_FW_VERSION:
		{
			if(nResult=='0')
			{
				int nEndIndex;
				nEndIndex = strAckData.GetLength();
				lpWorkInfo->m_sFirmwareVersion = strAckData.Mid(13, nEndIndex-14-2);
			}
			else
			{
				lpWorkInfo->m_sFirmwareVersion.Empty();
			}
		}break;

	case CMD_CTRL_FW_GOTO_BOOT_SECTION:
		{
			if(nResult=='0')
			{
				m_nDownloadReadyAckCount++;
			}
		}break;
	}

	m_nRcvPgMsg = recvCMD;
}

void CGIE_BoadAssyApp::Lf_parsingAckGfd250Data(CString strAckData)
{
	CString sLog=_T("");
	int recvCMD=0;
	int nResult=0;

	if(strAckData.GetAt(0) != PACKET_STX)								return;						
	if(strAckData.GetAt((strAckData.GetLength()-1)) != PACKET_ETX)		return;

	recvCMD	= _tcstol(strAckData.Mid(9, 2), NULL, 16);
	nResult = strAckData.GetAt(13);

	if(DEBUG_RS232C_LOG)
	{
		sLog.Format(_T("CMD:0x%02X  DATA:%s"), recvCMD, strAckData); 

		Gf_writeLogData(_T("<RS232_R>"), sLog.GetBuffer(0));
	}

	switch(recvCMD)
	{
	case CMD_CTRL_FW_VERSION:
		{
			lpWorkInfo->m_sFirmwareVersion = strAckData.Mid(16, strAckData.GetLength()-19);
		}break;

	case CMD_CTRL_FW_GOTO_BOOT_SECTION :
		{			
			nResult	= _ttoi(strAckData.Mid(15, 1));
			if(nResult==0)
			{
				if(m_nDownloadCountUp==TRUE)
				{
					m_nDownloadCountUp=FALSE;
					m_nDownloadReadyAckCount++;
				}
			}
			break;
		}
	case CMD_CTRL_FW_COMPLETE :
		{			
			nResult = _ttoi(strAckData.Mid(15, 1));
			break;
		}
	case CMD_NIOS_DPCD_WRITE:
		{
// 			bDPCDWrite = FALSE;
// 			switch(cResult)
// 			{
// 			case '0':	
// 				bDPCDWrite = TRUE;			
// 				break;
// 			default:
// 				ErrorMsgCode(nCmd, cResult , 0);				
// 				break;
// 			}
		}
		break;

	case CMD_NIOS_DPCD_READ:
		{
// 			nDpcdReadValue = 0;
// 			switch(cResult)
// 			{
// 			case '0':	
// 				AckParsingDPCDReadData(strAckData);
// 				break;
// 			default:	
// 				ErrorMsgCode(nCmd, cResult , 0);				
// 				break;
// 			}
		}
		break;

	case CMD_NIOS_I2C_READ:
		{				
			switch(nResult)
			{
			case '0':
				{
//					if(m_nI2CCmdNumber == I2C_CMD_EDID_READ)
					{
						Lf_parsingEdidDataGfd250(strAckData);
						Gf_writeLogData(_T("<GFD250>"), _T("EDID Read OK"));
					}
// 					else if(m_nI2CCmdNumber == I2C_CMD_PMIC_READ)
// 					{
// 						AckParsingPMICReceiveDataEDP1V4(strAckData);	
// 						beDP1V4PmIcRead = TRUE;
// 					}
// 					else if(m_nI2CCmdNumber == I2C_CMD_PGMA_READ)
// 					{
// 						AckParsingPGMAReceiveDataEDP1V4(strAckData);	
// 						beDP1V4PgmaRead = TRUE;
// 					}
// 					else if(nI2CCmdNumber == I2C_CMD_PVCOM_READ)
// 					{
// 						AckParsingPVcomReceiveDataEDP1V4(strAckData);	
// 						beDP1V4PvcomRead = TRUE;
// 					}
// 					else if(nI2CCmdNumber == I2C_CMD_CUSTOMER_LABEL_READ)
// 					{
// 						AckParsingCustomerLabelReceiveDataEDP1V4(strAckData);
// 					}
// 					else if(nI2CCmdNumber == I2C_CMD_MODEL_SUFFIX_READ)
// 					{
// 						CString strTmp=_T("");
// 
// 						for(int nLoop=0; nLoop < 13; nLoop++)
// 						{
// 							strTmp = strAckData.Mid(16+(nLoop*2), 2);
// 							szSerialLabelData_Read[nLoop] = StrToHex(strTmp);
// 						}
// 					}
				}					
				break;
			default:	
/*				ErrorMsgCode(nCmd, cResult , 0);	*/			
				break;
			}
		}
		break;

// 	case CMD_NIOS_I2C_WRITE_BYTE:
// 		{
// 			switch(cResult)
// 			{
// 			case '0':
// 				bFlickerWRtn = TRUE;	
// 				break;
// 			default:			
// 				ErrorMsgCode(nCmd, cResult , 0);		
// 				break;
// 			}
// 		}
// 		break;

	default:
		break;
	}

	m_nRcvGfd250Msg = recvCMD;
/*	if(cResult != '0')	strRetryMsg.Format("%s", szLog);*/
}

void CGIE_BoadAssyApp::Gf_setStartPtnLockTime(int nPtnNum)
{
	m_nSLockTime = ::GetTickCount();
}

void CGIE_BoadAssyApp::Gf_setEndPtnLockTime(int nPtnNum)
{
	m_nELockTime = ::GetTickCount();
	m_nPtnLockTime[nPtnNum] = m_nELockTime - m_nSLockTime;		// Pattern 검사 시간 저장.
}

BOOL CGIE_BoadAssyApp::Lf_loadEdidFile(CString spath)
{
	CFile fp;

	fp.Open(spath,CFile::modeRead);

	ZeroMemory(m_nEEPRomFileData,sizeof(m_nEEPRomFileData));

	if(fp)
	{
		if(fp.Read(m_nEEPRomFileData, 1024) )
		{
// 			lpModelInfo->m_nEdidSize[0] = (int)fp.GetLength();	
// 			lpModelInfo->m_sEdidChecksum[0].Format(_T("%s"),  EdidCheckSumCalc(szEdidRdFileData, (int)fp.GetLength()).GetBuffer(0));
// 			gf_fucWriteMLog(_T("Read EDID(Read) Checksum From File:"), lpModelInfo->m_sEdidChecksum[0].GetBuffer(0));
// 			m_nEdidFileSize = (int)fp.GetLength();

			fp.Close();
		} 
		else 
		{
			fp.Close();
			return FALSE;
		}
	} 
	else
	{
		fp.Close();
		return FALSE;
	}
	return TRUE;	
}

BOOL CGIE_BoadAssyApp::Gf_readEdidFile()
{
	CString sdata=_T("");
#ifdef	USE_GMES
	lpWorkInfo->Edid = 'N';
#endif

	if( _access(".\\EDID\\",0) == -1 )
		_mkdir(".\\EDID");
	
	sdata.Format(_T(".\\EDID\\%s.edi"), lpSystemInfo->m_sModelName);//sprintf (szData, ".\\EDID_WRITE\\%s.edi", lpSystemInfo->m_sModelName);

	WIN32_FIND_DATA wfd;		
	HANDLE hSearch;

	hSearch = FindFirstFile (sdata, &wfd);

	if (hSearch != INVALID_HANDLE_VALUE)
	{
		FindClose (hSearch);
#ifdef	USE_GMES
		lpWorkInfo->Edid = 'P';
#endif
		if(Lf_loadEdidFile(sdata))
		{
			return TRUE;
		}
		else
		{
			AfxMessageBox(_T("It is registration as EDID model, but there is no (.edi) file."));
			return FALSE;
		}
	}
	else
	{
		return FALSE;
	}
}

CString CGIE_BoadAssyApp::Lf_getPatternData()
{
	CString sdata1=_T(""),sdata2=_T(""),rtnData=_T("");
	int cnt=0, Num=0;
	float chk=0.0;

	while(cnt < lpModelInfo->m_nLbCnt)
	{
		cnt++;
		chk = (float)(m_nPatTime[Num]*0.001);
		if(chk != 0)
		{
			Num++;
			sdata1.Format(_T("%d:%s(%d):%2.2f,"),Num,lpModelInfo->m_sLbPtnName[Num-1],_ttoi(lpModelInfo->m_sLbPtnFg[Num-1]),chk);
			sdata2.Append(sdata1);
		}
	}

	rtnData = sdata2.Left(sdata2.GetLength()-1);
	return rtnData;
}

void CGIE_BoadAssyApp::Gf_setPatStartCheckTime(int i)
{
	m_nStartCheckTime[i] = ::GetTickCount ();
}

void CGIE_BoadAssyApp::Gf_setPatEndCheckTime(int i)
{
	m_nEndCheckTime[i] = ::GetTickCount ();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL CGIE_BoadAssyApp::Gf_gmesConnect(int nServerType)
{
	char szBuffer[64]={0,};

	m_pCimNet->SetMachineName(lpSystemInfo->m_sMachinName);

	if(m_pCimNet->ConnectTibRv(nServerType) == TRUE)
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CGIE_BoadAssyApp::Gf_gmesDisConnect(int nServerType)
{
	return m_pCimNet->CloseTibRv(nServerType);
}
BOOL CGIE_BoadAssyApp::Gf_gmesInitServer(BOOL nServerType)
{
	m_pCimNet->SetMachineName(lpSystemInfo->m_sMachinName);

	if ((DEBUG_GMES_TEST_SERVER == TRUE) && (nServerType == SERVER_MES))
	{
		m_pCimNet->SetLocalTest(nServerType);
	}
	else if (nServerType == SERVER_EAS)
	{
		m_pCimNet->SetLocalTest(nServerType);
	}


	if (m_pCimNet->Init(nServerType) == TRUE)
	{
		return TRUE;
	}

	return FALSE;
}
void CGIE_BoadAssyApp::Gf_setGMesGoodInfo()
{
 	m_pCimNet->SetPF(_T("P"));
	m_pCimNet->SetRwkCode(lpWorkInfo->m_sBadCode.GetBuffer(0));
 	//m_pCimNet->SetExpectedCode(lpWorkInfo->m_sExpectedCode.GetBuffer(0));
 	//if(lpWorkInfo->m_sExpectedCode.GetLength() > 0)
 	//{
 	//	m_pCimNet->SetPatternInfo(_T("imsi"));//pUiPorc->pCimNet->SetPatternInfo(pUiPorc->comm.curData.strPtnTestInfo.GetBuffer(0));
 	//}
}

void CGIE_BoadAssyApp::Gf_setGMesBGradeInfo()
{
	m_pCimNet->SetPF(_T("P"));
	m_pCimNet->SetRwkCode(lpWorkInfo->m_sBadCode.GetBuffer(0));
 //	m_pCimNet->SetExpectedCode(lpWorkInfo->m_sExpectedCode.GetBuffer(0));
// 	pUiPorc->pCimNet->SetPatternInfo(pUiPorc->comm.curData.strPtnTestInfo.GetBuffer(0));
// 	pUiPorc->pCimNet->SetDefectPattern(pUiPorc->comm.curData.strDefectPattern.GetBuffer(0));
}

void CGIE_BoadAssyApp::Gf_setGMesBadInfo()
{
	m_pCimNet->SetPF(_T("F"));
	m_pCimNet->SetRwkCode(lpWorkInfo->m_sBadCode.GetBuffer(0));
//	m_pCimNet->SetExpectedCode(lpWorkInfo->m_sExpectedCode.GetBuffer(0));
 //	m_pCimNet->SetPatternInfo(pUiPorc->comm.curData.strPtnTestInfo.GetBuffer(0));
 //	m_pCimNet->SetDefectPattern(pUiPorc->comm.curData.strDefectPattern.GetBuffer(0));
}

void CGIE_BoadAssyApp::Lf_setGmesValueEICR()
{
	// 2009-03-05 PDH. PCHK 진행하지 않고 불량으로 Key In하는 경우 Panel ID 및
	// Pallet ID 없음으로 인하여 EICR 보고시에도 Panel ID, Pallet Update 하도록 수정.
	m_pCimNet->SetPanelID(lpWorkInfo->m_sPID);	
	m_pCimNet->SetBLID(_T(""));
	m_pCimNet->SetSerialNumber(_T(""));
	m_pCimNet->SetPalletID(_T(""));

	// 양품/불량 설정.
	if(!m_pCimNet->GetRwkCode().Compare(_T("")))
	{
		m_pCimNet->SetPF(_T("P"));
		m_pCimNet->SetDefectPattern(_T(""));
	}
	else
	{
		m_pCimNet->SetPF(_T("F"));
		// 불량 Pattern 정보 설정.
		CString strBadPtn;
		strBadPtn.Format(_T("%s"), lpWorkInfo->m_sBadPattern);
		strBadPtn.Replace(_T(" "), _T("_"));
		m_pCimNet->SetDefectPattern(strBadPtn.GetBuffer(0));
	}

	m_pCimNet->SetPvcomAdjustValue(_T(""));
	m_pCimNet->SetPvcomAdjustDropValue(_T(""));

	// Pattern 정보 설정
	m_pCimNet->SetPatternInfo(Lf_getPatternData());
}

CString CGIE_BoadAssyApp::Gf_getGmesRTNCD()
{
	CString strBuff;

	m_pCimNet->GetFieldData(&strBuff, _T("RTN_CD"));
	return strBuff;
}

void CGIE_BoadAssyApp::Gf_showLocalErrorMsg()
{
	CString strMsg;
	CString strVal;
	CMessageError msg_dlg;

	m_pCimNet->GetFieldData(&strMsg, _T("ERR_MSG_LOC"));	//ERR_MSG_ENG	ERR_MSG_LOC
	Read_ErrorCode(_T("EQP"), _T("2"), &strVal);
	msg_dlg.m_strEMessage.Format(_T("%s. %s"), strVal.GetBuffer(0), strMsg.GetBuffer(0));

	msg_dlg.DoModal();
}

void CGIE_BoadAssyApp::Gf_showPanelIdNg()
{
	CString strMsg=_T(""),sdata=_T("");
	CString strVal=_T("");
	CMessageError msg_dlg;

	m_pCimNet->GetFieldData(&strMsg, _T("ERR_MSG_LOC"));	//ERR_MSG_ENG	ERR_MSG_LOC
	sdata = strMsg.Mid(0, 8);
	if(sdata == _T("Panel ID"))
	{
		m_pDio7230->Gf_setDioWrite(/*DIO_PANEL_ID_NG*/3);
	}
	Read_ErrorCode(_T("EQP"), _T("2"), &strVal);
	msg_dlg.m_strEMessage.Format(_T("%s. %s"), strVal.GetBuffer(0), strMsg.GetBuffer(0));
	msg_dlg.DoModal();
}

BOOL CGIE_BoadAssyApp::Gf_sendGmesHost(int nHostCmd)
{
	CMessageQuestion RetryMsgDlg;
	int nRtnCD;
	CString strBuff;
	char Luc_PF = 0;

	if(m_bUserIdGieng==TRUE || m_bUserIdPM==TRUE)
		return TRUE;

Send_RETRY:

	if(nHostCmd==HOST_EAYT)
	{
		nRtnCD = m_pCimNet->EAYT();
	}
	else if(nHostCmd==HOST_UCHK)
	{
		nRtnCD = m_pCimNet->UCHK();
		if(nRtnCD==0)
		{
			m_pCimNet->GetFieldData(&lpWorkInfo->m_sUserName, _T("USER_NAME"));
			m_pCimNet->SetUserId(lpWorkInfo->m_sUserID);
		}
	}
	else if(nHostCmd==HOST_EDTI)
	{
		nRtnCD = m_pCimNet->EDTI();
	}	
	else if(nHostCmd==HOST_EICR)
	{
		Lf_setGmesValueEICR();
		nRtnCD = m_pCimNet->EICR();
	}

	Gf_writeLogData(_T("[HOST_R]"), m_pCimNet->GetHostRecvMessage());

	if(nRtnCD==RTN_OK)
	{
		return TRUE;
	}
	else if(nRtnCD==RTN_MSG_NOT_SEND)
	{
		CString strVal;
		CMessageQuestion start_dlg;

		start_dlg.m_strQMessage.Format(_T("Failed to send message. "));
		start_dlg.m_strLButton = _T(" Retry");

		Read_ErrorCode(_T("EQP"), _T("0"), &strVal);

		if(start_dlg.DoModal() == IDOK)
			goto Send_RETRY;
		else
			return FALSE;
	}
	else if(nRtnCD==RTN_RCV_TIMEOUT)
	{
		CString strVal;
		CMessageQuestion start_dlg;

		start_dlg.m_strQMessage.Format(_T("No response frome MES Host"));
		start_dlg.m_strLButton = _T(" Retry");

		Read_ErrorCode(_T("EQP"), _T("1"), &strVal);
		if(start_dlg.DoModal() == IDOK)
			goto Send_RETRY;
		else
			return FALSE;
	}
	else
	{
// 		while(Gf_getGmesRTNCD()==_T("2705"))
// 		{
// 			Gf_showLocalErrorMsg();
// 
// 			return FALSE;
// 		}
		if(lpSystemInfo->m_nPidNg == TRUE)
			Gf_showPanelIdNg();
		else
			Gf_showLocalErrorMsg();
	}
	return FALSE;
}
BOOL CGIE_BoadAssyApp::udp_sendPacket(CString ipAddress, int nTarget, int nCommand, int nLength, char* pData, int recvACK, int waitTime)
{
	char szlog[1024] = { 0, };
	char szpacket[4096] = { 0, };
	int  packetlen;
	char lpbuff[20] = { 0, };
	BYTE nChkSum = 0;

	// data 앞까지 Packet 생성
	sprintf_s(szpacket, "%cA1%02X00%02X%04X", PACKET_STX, nTarget, nCommand, nLength);

	// data를 포함하여 packet 생성. hex로 전송할 data가 있으므로 memcpy를 사용
	packetlen = (int)strlen(szpacket);
	memcpy(&szpacket[packetlen], pData, nLength);

	// data 를 포함한 packet의 길이를 구한다.
	packetlen += nLength;

	// 생성된 Packet을 이용하여 CheckSum을 구한다.
	for (int j = 1; j < packetlen; j++)		// Check Sum
	{
		nChkSum += szpacket[j];
	}
	sprintf_s(lpbuff, "%02X%c", nChkSum, PACKET_ETX);

	// Checksum과 ETX 3byte를 붙여 다시 Packet을 만든다.
	memcpy(&szpacket[packetlen], lpbuff, 3);
	packetlen += 3;

	// Packet의 마지막에 String의 끝을 알리기 위하여 NULL을 추가한다.
	szpacket[packetlen] = 0x00;


	// Receive Buff를 Clear
	ZeroMemory(m_pCommand->gszudpRcvPacket, sizeof(m_pCommand->gszudpRcvPacket));

	// 생성된 Packet을 전송.
	m_pSocketUDP->SendToUDP(ipAddress, packetlen, szpacket);

	// ACK Receive
	UINT ret = TRUE;
	m_nAckCmd[nCommand] = FALSE;

	if (recvACK == TRUE)
	{
		if (udp_procWaitRecvACK(nCommand, waitTime) == TRUE)
			ret = TRUE;
		else
			ret = FALSE;
	}

	return ret;
}

BOOL CGIE_BoadAssyApp::udp_procWaitRecvACK(int cmd, DWORD waitTime)
{
	DWORD stTick = ::GetTickCount();

	while (1)
	{
		DWORD edTick = GetTickCount();
		if ((edTick - stTick) > waitTime)
		{
			return FALSE;
		}

		if (m_nAckCmd[cmd] == TRUE)
		{
			return TRUE;
		}

		ProcessMessage();
	}
	return FALSE;
}