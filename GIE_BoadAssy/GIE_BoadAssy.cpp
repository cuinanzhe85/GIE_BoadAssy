
// GIE_BoadAssy.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
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


// CGIE_BoadAssyApp ����

CGIE_BoadAssyApp::CGIE_BoadAssyApp()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	// InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.
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


// ������ CGIE_BoadAssyApp ��ü�Դϴ�.

CGIE_BoadAssyApp theApp;
CGIE_BoadAssyApp* m_pApp;

// CGIE_BoadAssyApp �ʱ�ȭ

BOOL CGIE_BoadAssyApp::InitInstance()
{
	// ���� ���α׷� �Ŵ��佺Ʈ�� ComCtl32.dll ���� 6 �̻��� ����Ͽ� ���־� ��Ÿ����
	// ����ϵ��� �����ϴ� ���, Windows XP �󿡼� �ݵ�� InitCommonControlsEx()�� �ʿ��մϴ�.
	// InitCommonControlsEx()�� ������� ������ â�� ���� �� �����ϴ�.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ���� ���α׷����� ����� ��� ���� ��Ʈ�� Ŭ������ �����ϵ���
	// �� �׸��� �����Ͻʽÿ�.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	// ǥ�� �ʱ�ȭ
	// �̵� ����� ������� �ʰ� ���� ���� ������ ũ�⸦ ���̷���
	// �Ʒ����� �ʿ� ���� Ư�� �ʱ�ȭ
	// ��ƾ�� �����ؾ� �մϴ�.
	// �ش� ������ ����� ������Ʈ�� Ű�� �����Ͻʽÿ�.
	// TODO: �� ���ڿ��� ȸ�� �Ǵ� ������ �̸��� ����
	// ������ �������� �����ؾ� �մϴ�.
	SetRegistryKey(_T("���� ���� ���α׷� �����翡�� ������ ���� ���α׷�"));
	Lf_initVariable();//����ü �ʱ�ȭ
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
		// TODO: ���⿡ [Ȯ��]�� Ŭ���Ͽ� ��ȭ ���ڰ� ������ �� ó����
		//  �ڵ带 ��ġ�մϴ�.
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: ���⿡ [���]�� Ŭ���Ͽ� ��ȭ ���ڰ� ������ �� ó����
		//  �ڵ带 ��ġ�մϴ�.
	}

	// ��ȭ ���ڰ� �������Ƿ� ���� ���α׷��� �޽��� ������ �������� �ʰ�  ���� ���α׷��� ���� �� �ֵ��� FALSE��
	// ��ȯ�մϴ�.
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
	// Receive Message ó���� ������ �ڽ��� IP�� GateIP�� �����´�.
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

	// Receive Packet���� Group, Command ������ �����Ѵ�.
	sprintf_s(szbuf, "%c%c", wParam[PACKET_PT_CMD], wParam[PACKET_PT_CMD + 1]);
	recvCMD = strtol(szbuf, 0, 16);
	recvRet = wParam[PACKET_PT_RET];

	memcpy(m_pCommand->gszudpRcvPacket, wParam, lParam);

	// Message ó��
	switch (recvCMD)
	{
	case CMD_CTRL_FUSING_SYSTEM:
		break;
	case CMD_ARE_YOU_READY:
		switch (recvRet)
		{
		case '0':
			m_bAreYouReady = true;
			break;
		}break;
	case CMD_MEASURE_ALL_POWER :
		Lf_parsingMeasureAllPower(char_To_wchar(wParam));
		break;
	case CMD_CTRL_FW_VERSION:
	{
		if (recvRet == '0')
		{
			int nEndIndex;
			CString strAckData;
			strAckData = char_To_wchar(wParam);
			nEndIndex = strAckData.GetLength();
			lpWorkInfo->m_sFirmwareVersion = strAckData.Mid(PACKET_PT_DATA, nEndIndex - PACKET_PT_DATA - 3);
		}
		else
		{
			lpWorkInfo->m_sFirmwareVersion.Empty();
		}
	}break;
	case CMD_FPGA_VER_READ:
	{
		if (recvRet == '0')
		{
			int nEndIndex;
			CString strAckData;
			strAckData = char_To_wchar(wParam);
			nEndIndex = strAckData.GetLength();
			lpWorkInfo->m_sFpgaVersion = strAckData.Mid(PACKET_PT_DATA, nEndIndex - PACKET_PT_DATA - 3);
		}
		else
		{
			lpWorkInfo->m_sFpgaVersion.Empty();
		}
	}break;
	case CMD_CTRL_FW_GOTO_BOOT_DOWNLOAD:
	{
		if (recvRet == '0')
		{
			m_nDownloadReadyAckCount++;
		}
		else
		{
			m_nDownloadReadyAckCount = 0;
		}
	}break;
	case CMD_BMP_DOWNLOAD_DONE_CHECK:
	{
		if (recvRet == '0')
		{
			int nEndIndex;
			CString strAckData;
			strAckData = char_To_wchar(wParam);
			nEndIndex = strAckData.GetLength();
			lpWorkInfo->m_bBmpDoneCheck = (int)_ttoi(strAckData.Mid(PACKET_PT_DATA, nEndIndex - PACKET_PT_DATA - 3));
		}
	}break;
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
	lpSystemInfo->m_nBluType=0;
	lpSystemInfo->m_nBluFreq=0;
	lpSystemInfo->m_nTestStartDelay=0;
	lpSystemInfo->m_nI2CPullUp=0;
	lpSystemInfo->m_nI2CClock=0;
	lpSystemInfo->m_nPGSystemType=0;
	lpSystemInfo->m_nPgPort=0;
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

	lpModelInfo->m_nEdidUse=0;
	lpModelInfo->m_nEdidAddr=0;
	lpModelInfo->m_nEdidLine=0;
	lpModelInfo->m_nEdidSize=0;
	lpModelInfo->m_nEEPRomType=0;
	lpModelInfo->m_nEEPRomAddr=0;

	lpModelInfo->m_nGfd100Use=0;
	lpModelInfo->m_nSolomonMipi=0;
	lpModelInfo->m_nBluMin=0;
	lpModelInfo->m_nDp501InitCode=0;

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

	lpModelInfo->m_nPixelType =0;
	lpModelInfo->m_nLcmInfoMode=0;
	lpModelInfo->m_nLcmInfoBitsSwap=0;

	lpModelInfo->m_nSignalType=0;
	lpModelInfo->m_nSignalBit=0;
	lpModelInfo->m_nSignalInterface=0;
	lpModelInfo->m_nSignalBitSwap=0;
	lpModelInfo->m_nBitSel=0;
	lpModelInfo->m_nLGDISMSelect=0;
	lpModelInfo->m_nALPDPModelSel=0;
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
		lpModelInfo->m_sLbPtnVcc[i].Empty();
		lpModelInfo->m_sLbPtnVdd[i].Empty();
		lpModelInfo->m_sLbPtnTms[i].Empty();
		lpModelInfo->m_sLbPtnVsync[i].Empty();
		lpModelInfo->m_sLbPtnBlu[i].Empty();
		lpModelInfo->m_sLbPtnIccLow[i].Empty();
		lpModelInfo->m_sLbPtnIccHigh[i].Empty();
		lpModelInfo->m_sLbPtnIddLow[i].Empty();
		lpModelInfo->m_sLbPtnIddHigh[i].Empty();
	}

	lpWorkInfo->m_bPIDReadComplete = false;

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
	Read_SysIniFile(_T("SYSTEM"),		_T("BLU_TYPE"),						&lpSystemInfo->m_nBluType);
	Read_SysIniFile(_T("SYSTEM"),		_T("BLU_FREQ"),						&lpSystemInfo->m_nBluFreq);
	Read_SysIniFile(_T("SYSTEM"),		_T("TEST_START_DELAY"),				&lpSystemInfo->m_nTestStartDelay);
	



	Read_SysIniFile(_T("SYSTEM"),		_T("I2C_PULL_UP"),					&lpSystemInfo->m_nI2CPullUp);
	Read_SysIniFile(_T("SYSTEM"),		_T("I2C_FREQ"),						&lpSystemInfo->m_nI2CClock);
	Read_SysIniFile(_T("SYSTEM"),		_T("PG_TYPE"),						&lpSystemInfo->m_nPGSystemType);
	Read_SysIniFile(_T("SYSTEM"),		_T("IRDA_PORT"),					&lpSystemInfo->m_nPgPort);
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

void CGIE_BoadAssyApp::Gf_loadModelData()
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
	

	//-------------------------------------- EDID INFO
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("EDID_USE"),				&lpModelInfo->m_nEdidUse);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("EDID_ADDR"),			&lpModelInfo->m_nEdidAddr);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("EDID_LINE"),			&lpModelInfo->m_nEdidLine);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("EEPROM_ADDR"),			&lpModelInfo->m_nEEPRomAddr);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("EEPROM_TYPE"),			&lpModelInfo->m_nEEPRomType);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("EDID_SIZE"),			&lpModelInfo->m_nEdidSize);


	//-------------------------------------- Function INFO
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("GFD100_USE"),			&lpModelInfo->m_nGfd100Use);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("DP501_INIT_CODE"),		&lpModelInfo->m_nDp501InitCode);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("SOLOMON_MIPI"),			&lpModelInfo->m_nSolomonMipi);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("SPI_MODE"),				&lpModelInfo->m_nSpiMode);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("SPI_LEVEL"),			&lpModelInfo->m_nSpiLevel);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("BLU_MIN"),				&lpModelInfo->m_nBluMin);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("CABLE_OPEN_USE"),		&lpModelInfo->m_nCableOpenUse);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("SHORT_TEST_USE"),		&lpModelInfo->m_nShortTestUse);
	
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("VCC"),					&lpModelInfo->m_fVoltVcc);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("VDD"),					&lpModelInfo->m_fVoltVdd);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("VGH"),					&lpModelInfo->m_fVoltVgh);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("VGL"),					&lpModelInfo->m_fVoltVgl);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("VCC_HIGH_LIMIT"),		&lpModelInfo->m_fLimitVccMax);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("VCC_LOW_LIMIT"),		&lpModelInfo->m_fLimitVccMin);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("VDD_HIGH_LIMIT"),		&lpModelInfo->m_fLimitVddMax);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("VDD_LOW_LIMIT"),		&lpModelInfo->m_fLimitVddMin);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("ICC_HIGH_LIMIT"),		&lpModelInfo->m_fLimitIccMax);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("ICC_LOW_LIMIT"),		&lpModelInfo->m_fLimitIccMin);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("IDD_HIGH_LIMIT"),		&lpModelInfo->m_fLimitIddMax);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("IDD_LOW_LIMIT"),		&lpModelInfo->m_fLimitIddMin);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("VGL_HIGH_LIMIT"),		&lpModelInfo->m_fLimitVglMax);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("VGL_LOW_LIMIT"),		&lpModelInfo->m_fLimitVglMin);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("VGH_HIGH_LIMIT"),		&lpModelInfo->m_fLimitVghMax);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("VGH_LOW_LIMIT"),		&lpModelInfo->m_fLimitVghMin);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("IGL_HIGH_LIMIT"),		&lpModelInfo->m_fLimitIglMax);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("IGL_LOW_LIMIT"),		&lpModelInfo->m_fLimitIglMin);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("IGH_HIGH_LIMIT"),		&lpModelInfo->m_fLimitIghMax);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("IGH_LOW_LIMIT"),		&lpModelInfo->m_fLimitIghMin);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("IBL_HIGH_LIMIT"), &lpModelInfo->m_fLimitIblMax);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("IBL_LOW_LIMIT"), &lpModelInfo->m_fLimitIblMin);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("VBL_HIGH_LIMIT"), &lpModelInfo->m_fLimitVblMax);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("VBL_LOW_LIMIT"), &lpModelInfo->m_fLimitVblMin);

	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("SIGNAL_TYPE"),			&lpModelInfo->m_nSignalType);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("SIGNAL_BIT"),			&lpModelInfo->m_nSignalBit);
	Read_ModelFile(modelName,	_T("MODEL_INFO"),	_T("BIT_SELECT"),			&lpModelInfo->m_nBitSel);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("PIXEL_TYPE"), &lpModelInfo->m_nPixelType);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("BITSWAP"), &lpModelInfo->m_nLcmInfoBitsSwap);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("CLOCK_DELAY"), &lpModelInfo->m_nClockDelay);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("CLOCK_RISING"), &lpModelInfo->m_nClockRising);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("HSYNC_POLARITY"), &lpModelInfo->m_nHSyncPolarity);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("VSYNC_POLARITY"), &lpModelInfo->m_nVSyncPolarity);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("ODD_EVEN"), &lpModelInfo->m_nOddEven);

	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_ON_SEQ_OP_01"), &lpModelInfo->m_nPowerOnSeqType01);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_ON_SEQ_OP_02"), &lpModelInfo->m_nPowerOnSeqType02);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_ON_SEQ_OP_03"), &lpModelInfo->m_nPowerOnSeqType03);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_ON_SEQ_OP_04"), &lpModelInfo->m_nPowerOnSeqType04);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_ON_SEQ_OP_05"), &lpModelInfo->m_nPowerOnSeqType05);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_ON_SEQ_OP_06"), &lpModelInfo->m_nPowerOnSeqType06);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_ON_SEQ_OP_07"), &lpModelInfo->m_nPowerOnSeqType07);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_ON_SEQ_OP_08"), &lpModelInfo->m_nPowerOnSeqType08);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_ON_SEQ_OP_09"), &lpModelInfo->m_nPowerOnSeqType09);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_ON_SEQ_OP_10"), &lpModelInfo->m_nPowerOnSeqType10);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_ON_SEQ_OP_11"), &lpModelInfo->m_nPowerOnSeqType11);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_ON_SEQ_OP_12"), &lpModelInfo->m_nPowerOnSeqType12);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_ON_SEQ_OP_13"), &lpModelInfo->m_nPowerOnSeqType13);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_ON_SEQ_OP_14"), &lpModelInfo->m_nPowerOnSeqType14);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_ON_SEQ_OP_15"), &lpModelInfo->m_nPowerOnSeqType15);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_ON_SEQ_OP_16"), &lpModelInfo->m_nPowerOnSeqType16);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_ON_SEQ_OP_17"), &lpModelInfo->m_nPowerOnSeqType17);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_OFF_SEQ_OP_01"), &lpModelInfo->m_nPowerOffSeqType01);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_OFF_SEQ_OP_02"), &lpModelInfo->m_nPowerOffSeqType02);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_OFF_SEQ_OP_03"), &lpModelInfo->m_nPowerOffSeqType03);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_OFF_SEQ_OP_04"), &lpModelInfo->m_nPowerOffSeqType04);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_OFF_SEQ_OP_05"), &lpModelInfo->m_nPowerOffSeqType05);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_OFF_SEQ_OP_06"), &lpModelInfo->m_nPowerOffSeqType06);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_OFF_SEQ_OP_07"), &lpModelInfo->m_nPowerOffSeqType07);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_OFF_SEQ_OP_08"), &lpModelInfo->m_nPowerOffSeqType08);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_OFF_SEQ_OP_09"), &lpModelInfo->m_nPowerOffSeqType09);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_OFF_SEQ_OP_10"), &lpModelInfo->m_nPowerOffSeqType10);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_OFF_SEQ_OP_11"), &lpModelInfo->m_nPowerOffSeqType11);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_OFF_SEQ_OP_12"), &lpModelInfo->m_nPowerOffSeqType12);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_OFF_SEQ_OP_13"), &lpModelInfo->m_nPowerOffSeqType13);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_OFF_SEQ_OP_14"), &lpModelInfo->m_nPowerOffSeqType14);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_OFF_SEQ_OP_15"), &lpModelInfo->m_nPowerOffSeqType15);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_OFF_SEQ_OP_16"), &lpModelInfo->m_nPowerOffSeqType16);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_OFF_SEQ_OP_17"), &lpModelInfo->m_nPowerOffSeqType17);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_ON_SEQ_DELAY_01"), &lpModelInfo->m_nPowerOnSeqDelay01);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_ON_SEQ_DELAY_02"), &lpModelInfo->m_nPowerOnSeqDelay02);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_ON_SEQ_DELAY_03"), &lpModelInfo->m_nPowerOnSeqDelay03);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_ON_SEQ_DELAY_04"), &lpModelInfo->m_nPowerOnSeqDelay04);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_ON_SEQ_DELAY_05"), &lpModelInfo->m_nPowerOnSeqDelay05);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_ON_SEQ_DELAY_06"), &lpModelInfo->m_nPowerOnSeqDelay06);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_ON_SEQ_DELAY_07"), &lpModelInfo->m_nPowerOnSeqDelay07);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_ON_SEQ_DELAY_08"), &lpModelInfo->m_nPowerOnSeqDelay08);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_ON_SEQ_DELAY_09"), &lpModelInfo->m_nPowerOnSeqDelay09);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_ON_SEQ_DELAY_10"), &lpModelInfo->m_nPowerOnSeqDelay10);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_ON_SEQ_DELAY_11"), &lpModelInfo->m_nPowerOnSeqDelay11);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_ON_SEQ_DELAY_12"), &lpModelInfo->m_nPowerOnSeqDelay12);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_ON_SEQ_DELAY_13"), &lpModelInfo->m_nPowerOnSeqDelay13);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_ON_SEQ_DELAY_14"), &lpModelInfo->m_nPowerOnSeqDelay14);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_ON_SEQ_DELAY_15"), &lpModelInfo->m_nPowerOnSeqDelay15);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_ON_SEQ_DELAY_16"), &lpModelInfo->m_nPowerOnSeqDelay16);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_ON_SEQ_DELAY_17"), &lpModelInfo->m_nPowerOnSeqDelay17);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_OFF_SEQ_DELAY_01"), &lpModelInfo->m_nPowerOffSeqDelay01);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_OFF_SEQ_DELAY_02"), &lpModelInfo->m_nPowerOffSeqDelay02);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_OFF_SEQ_DELAY_03"), &lpModelInfo->m_nPowerOffSeqDelay03);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_OFF_SEQ_DELAY_04"), &lpModelInfo->m_nPowerOffSeqDelay04);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_OFF_SEQ_DELAY_05"), &lpModelInfo->m_nPowerOffSeqDelay05);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_OFF_SEQ_DELAY_06"), &lpModelInfo->m_nPowerOffSeqDelay06);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_OFF_SEQ_DELAY_07"), &lpModelInfo->m_nPowerOffSeqDelay07);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_OFF_SEQ_DELAY_08"), &lpModelInfo->m_nPowerOffSeqDelay08);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_OFF_SEQ_DELAY_09"), &lpModelInfo->m_nPowerOffSeqDelay09);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_OFF_SEQ_DELAY_10"), &lpModelInfo->m_nPowerOffSeqDelay10);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_OFF_SEQ_DELAY_11"), &lpModelInfo->m_nPowerOffSeqDelay11);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_OFF_SEQ_DELAY_12"), &lpModelInfo->m_nPowerOffSeqDelay12);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_OFF_SEQ_DELAY_13"), &lpModelInfo->m_nPowerOffSeqDelay13);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_OFF_SEQ_DELAY_14"), &lpModelInfo->m_nPowerOffSeqDelay14);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_OFF_SEQ_DELAY_15"), &lpModelInfo->m_nPowerOffSeqDelay15);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_OFF_SEQ_DELAY_16"), &lpModelInfo->m_nPowerOffSeqDelay16);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_OFF_SEQ_DELAY_17"), &lpModelInfo->m_nPowerOffSeqDelay17);

	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("I2C_PULLUP"), &lpModelInfo->m_nI2cPullup);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("I2C_FREQ"), &lpModelInfo->m_nI2cFreq);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("I2C_LEVEL"), &lpModelInfo->m_nI2cLevel);

	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("VBR"), &lpModelInfo->m_fVoltVbr);
	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("VBL"), &lpModelInfo->m_fVoltVbl);

	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("VCOM1"), &lpModelInfo->m_fVoltVcom1);

	Read_ModelFile(modelName, _T("MODEL_INFO"), _T("VCOM2"), &lpModelInfo->m_fVoltVcom2);

	for (int i = 0; i < 32; i++)
	{
		strKey.Format(_T("GAMMA_CH%02d"), i + 1);
		Read_ModelFile(modelName, _T("MODEL_INFO"), strKey, &lpModelInfo->m_fVoltGamma[i]);
	}

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
			lpModelInfo->m_sLbPtnVcc[nLoop].Empty();
			lpModelInfo->m_sLbPtnVdd[nLoop].Empty();
			lpModelInfo->m_sLbPtnTms[nLoop].Empty();
			lpModelInfo->m_sLbPtnVsync[nLoop].Empty();
			lpModelInfo->m_sLbPtnBlu[nLoop].Empty();
			lpModelInfo->m_sLbPtnIccLow[nLoop].Empty();
			lpModelInfo->m_sLbPtnIccHigh[nLoop].Empty();
			lpModelInfo->m_sLbPtnIddLow[nLoop].Empty();
			lpModelInfo->m_sLbPtnIddHigh[nLoop].Empty();
		}
		else
		{	
			lpModelInfo->m_sLbPtnName[nLoop]=szParseData[0];
			lpModelInfo->m_sLbPtnVcc[nLoop]=szParseData[1];
			lpModelInfo->m_sLbPtnVdd[nLoop]=szParseData[2];
			lpModelInfo->m_sLbPtnTms[nLoop]=szParseData[3];
			lpModelInfo->m_sLbPtnVsync[nLoop]=szParseData[4];
			lpModelInfo->m_sLbPtnIccLow[nLoop] = szParseData[5];
			lpModelInfo->m_sLbPtnIccHigh[nLoop] = szParseData[6];
			lpModelInfo->m_sLbPtnIddLow[nLoop] = szParseData[7];
			lpModelInfo->m_sLbPtnIddHigh[nLoop] = szParseData[8];
			lpModelInfo->m_sLbPtnBlu[nLoop].Format(_T("%s"), ((_tcslen(szParseData[6])==0) ? _T("100") :szParseData[9]));
			lpModelInfo->m_nLbCnt = nLoop+1;
		}

		// Data�� NULL���� ������ Pasing�� �ߴ��Ѵ�.
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

	strDataFolder.Format(_T(".\\%s\\*.mod"), _T("Model"));
	hSearch = FindFirstFile(strDataFolder, &wfd);

	if (hSearch != INVALID_HANDLE_VALUE)
	{
		if (wfd.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
		{
			while(nLoof)
			{
				strLFileName.Format(_T("%s.mod"), lpSystemInfo->m_sModelName);		strLFileName.MakeUpper();
				strNFileName.Format(_T("%s"), wfd.cFileName);						strNFileName.MakeUpper();
				if(strLFileName.Compare(strNFileName)) // When model file is't existed in folder, this sentence is executed. : Difference
				{
					nLoof = FindNextFile (hSearch, &wfd);
					if(nLoof==0)
					{
						//default.mod setting
						m_sModelFile.Format(_T("%s"),_T("Model file load NG!!!"));
						Gf_loadModelData();
						return FALSE;
					}
				}

				strLFileName.Format(_T("%s.mod"), lpSystemInfo->m_sModelName);		strLFileName.MakeUpper();
				strNFileName.Format(_T("%s"), wfd.cFileName);						strNFileName.MakeUpper();
				if(!strLFileName.Compare(strNFileName)) // When model file is existed in folder, this sentence is executed. : equal
				{		
					Gf_loadModelData();
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
		Gf_loadModelData();
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

	CString strError = _T("");
	CString sLogcal[200], sBmp[200];
	int nLogcalIndex=0, nBmpIndex = 0;

	for (i = 0; !lpModelInfo->m_sLbPtnName[i].IsEmpty(); i++)
	{
		if (lpModelInfo->m_sLbPtnName[i].Find(_T(".BMP")) != -1)
		{
			sBmp[nBmpIndex] = lpModelInfo->m_sLbPtnName[i];
			nBmpIndex++;
		}
		else
		{
			sLogcal[nLogcalIndex] = lpModelInfo->m_sLbPtnName[i];
			nLogcalIndex++;
		}
	}
	if (nLogcalIndex > 0)
	{
		strDatafolder.Format(_T(".\\Pattern\\*.pdb"));
		hSearch = FindFirstFile(strDatafolder, &wfd);

		if (hSearch != INVALID_HANDLE_VALUE)
		{
			if (wfd.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
			{
				for (i = 0; !sLogcal[i].IsEmpty(); i++)
				{
					strFileName.Format(_T("%s.PDB"), sLogcal[i]);
					while (nLoof)
					{
						strNFileName.Format(_T("%s"), wfd.cFileName);	strNFileName.MakeUpper();
						if (strFileName.Compare(strNFileName))
						{
							nLoof = FindNextFile(hSearch, &wfd);
							if (nLoof == 0) // end of Folder
							{
								strError.Append(strFileName);
								strError.Append(_T(" "));
								hSearch = FindFirstFile(strDatafolder, &wfd);
								FindClose(hSearch);
								return FALSE;
							}
						}
						else if (!strFileName.Compare(strNFileName))
						{
							hSearch = FindFirstFile(strDatafolder, &wfd);
							break;
						}
					}
					if (nLoof == 0) break;
				}
			}
		}
	}
	if (nBmpIndex > 0)
	{
		strDatafolder.Format(_T(".\\Pattern\\BMP\\*.BMP"));
		hSearch = FindFirstFile(strDatafolder, &wfd);

		if (hSearch != INVALID_HANDLE_VALUE)
		{
			if (wfd.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
			{
				for (i = 0; !sBmp[i].IsEmpty(); i++)
				{
					strFileName.Format(_T("%s"), sBmp[i]);
					while (nLoof)
					{
						strNFileName.Format(_T("%s"), wfd.cFileName);	strNFileName.MakeUpper();
						if (strFileName.Compare(strNFileName))
						{
							nLoof = FindNextFile(hSearch, &wfd);
							if (nLoof == 0) // end of Folder
							{
								strError.Append(strFileName);
								strError.Append(_T(" "));
								hSearch = FindFirstFile(strDatafolder, &wfd);
								FindClose(hSearch);
								return FALSE;
							}
						}
						else if (!strFileName.Compare(strNFileName))
						{
							hSearch = FindFirstFile(strDatafolder, &wfd);
							break;
						}
					}
					if (nLoof == 0) break;
				}
			}
		}
	}

	if( (strError.IsEmpty()==FALSE) || ( lpModelInfo->m_sLbPtnName[0].IsEmpty() ) )
	{
		m_sPtnFile.Format(_T("%s"),_T("Pattern file load NG!!!"));
		//AfxMessageBox(_T("Error Pattern File"), MB_ICONSTOP);
		return FALSE;
	}
	else
	{
		m_sPtnFile.Format(_T("%s"), _T("Pattern file load OK!!!"));
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
	//if(nDataLen < 8)// Noise�� ���� PGM Down ����.
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
	if (strAckData.Mid(PACKET_PT_RET, 1) == _T("0"))
	{
		int nstartLength= PACKET_PT_DATA + 15;
		m_nLcmPInfo[PINFO_VCC] = (int)_ttoi(strAckData.Mid(nstartLength, 5));
		nstartLength += 5;
		m_nLcmPInfo[PINFO_ICC] = (int)_ttoi(strAckData.Mid(nstartLength, 5));
		nstartLength += 5;
		m_nLcmPInfo[PINFO_VDD] = (int)_ttoi(strAckData.Mid(nstartLength, 5));
		nstartLength += 5;
		m_nLcmPInfo[PINFO_IDD] = (int)_ttoi(strAckData.Mid(nstartLength, 5));
		nstartLength += 5; // VBL
		m_nLcmPInfo[PINFO_VBL] = (int)_ttoi(strAckData.Mid(nstartLength, 5));
		nstartLength += 5; // IBL
		m_nLcmPInfo[PINFO_IBL] = (int)_ttoi(strAckData.Mid(nstartLength, 5));
		nstartLength += 5;
		m_nLcmPInfo[PINFO_VGH] = (int)_ttoi(strAckData.Mid(nstartLength, 5));
		nstartLength += 5;
		m_nLcmPInfo[PINFO_IGH] = (int)_ttoi(strAckData.Mid(nstartLength, 5));
		nstartLength += 5;
		m_nLcmPInfo[PINFO_VGL] = (int)_ttoi(strAckData.Mid(nstartLength, 5));
		nstartLength += 5;
		m_nLcmPInfo[PINFO_IGL] = (int)_ttoi(strAckData.Mid(nstartLength, 5));
		nstartLength += 5;
		m_nLcmPInfo[PINFO_VCC_FB] = (int)_ttoi(strAckData.Mid(nstartLength, 5));
		nstartLength += 5; //VBL_FB
		nstartLength += 5;
		m_nLcmPInfo[PINFO_VLED_FB] = (int)_ttoi(strAckData.Mid(nstartLength, 5));
		nstartLength += 5;
		m_nLcmPInfo[PINFO_THERMISTOR] = (int)_ttoi(strAckData.Mid(nstartLength, 5));

		m_nLcmPInfo[PINFO_ERR_RESULT] = (int)_ttoi(strAckData.Mid(PACKET_PT_DATA+1, 1));
		m_nLcmPInfo[PINFO_ERR_NAME] = (int)_ttoi(strAckData.Mid(PACKET_PT_DATA + 1 + 1, 1));
		m_nLcmPInfo[PINFO_ERR_VALUE] = (int)_ttoi(strAckData.Mid(PACKET_PT_DATA + 1 + 1 + 1, 5));
	}
	
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

	recvCMD	= _tcstol(strAckData.Mid(PACKET_PT_CMD, 2), NULL, 16);
	nResult = strAckData.GetAt(PACKET_PT_RET);

	if(DEBUG_RS232C_LOG)
	{
		sLog.Format(_T("CMD:0x%02X  DATA:%s"), recvCMD, strAckData); 

		Gf_writeLogData(_T("<PG_R>"), sLog.GetBuffer(0));
	}

	switch(recvCMD)
	{

	case CMD_CTRL_FW_VERSION:
		{
			if(nResult=='0')
			{
				int nEndIndex;
				nEndIndex = strAckData.GetLength();
				lpWorkInfo->m_sFirmwareVersion = strAckData.Mid(PACKET_PT_DATA, nEndIndex- PACKET_PT_DATA -2);
			}
			else
			{
				lpWorkInfo->m_sFirmwareVersion.Empty();
			}
		}break;

	case CMD_CTRL_FW_GOTO_BOOT_DOWNLOAD:
		{
			if(nResult=='0')
			{
				m_nDownloadReadyAckCount++;
			}
			else
			{
				m_nDownloadReadyAckCount = 0;
			}
		}break;
	case CMD_CTRL_COMMUNICATION_TIMEOUT:
	{
		// Time out
	}
	break;
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

	case CMD_CTRL_FW_GOTO_BOOT_DOWNLOAD:
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
	m_nPtnLockTime[nPtnNum] = m_nELockTime - m_nSLockTime;		// Pattern �˻� �ð� ����.
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
			sdata1.Format(_T("%d:%s:%2.2f,"),Num,lpModelInfo->m_sLbPtnName[Num-1],chk);
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
}

void CGIE_BoadAssyApp::Gf_setGMesBGradeInfo()
{
	m_pCimNet->SetPF(_T("P"));
	m_pCimNet->SetRwkCode(lpWorkInfo->m_sBadCode.GetBuffer(0));
}

void CGIE_BoadAssyApp::Gf_setGMesBadInfo()
{
	m_pCimNet->SetPF(_T("F"));
	m_pCimNet->SetRwkCode(lpWorkInfo->m_sBadCode.GetBuffer(0));
}

void CGIE_BoadAssyApp::Lf_setGmesValueEICR()
{
	// 2009-03-05 PDH. PCHK �������� �ʰ� �ҷ����� Key In�ϴ� ��� Panel ID ��
	// Pallet ID �������� ���Ͽ� EICR ����ÿ��� Panel ID, Pallet Update �ϵ��� ����.
	m_pCimNet->SetPanelID(lpWorkInfo->m_sPID);	
	m_pCimNet->SetBLID(_T(""));
	m_pCimNet->SetSerialNumber(_T(""));
	m_pCimNet->SetPalletID(_T(""));

	// ��ǰ/�ҷ� ����.
	if(!m_pCimNet->GetRwkCode().Compare(_T("")))
	{
		m_pCimNet->SetPF(_T("P"));
		m_pCimNet->SetDefectPattern(_T(""));
	}
	else
	{
		m_pCimNet->SetPF(_T("F"));
		// �ҷ� Pattern ���� ����.
		CString strBadPtn;
		strBadPtn.Format(_T("%s"), lpWorkInfo->m_sBadPattern);
		strBadPtn.Replace(_T(" "), _T("_"));
		m_pCimNet->SetDefectPattern(strBadPtn.GetBuffer(0));
	}

	m_pCimNet->SetPvcomAdjustValue(_T(""));
	m_pCimNet->SetPvcomAdjustDropValue(_T(""));

	// Pattern ���� ����
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
		Gf_showLocalErrorMsg();
	}
	return FALSE;
}
BOOL CGIE_BoadAssyApp::udp_sendPacket(CString ipAddress, int nTarget, int nCommand, int nLength, char* pData, int recvACK, int waitTime)
{
	char szlog[1024] = { 0, };
	char szpacket[1024*16] = { 0, };
	int  packetlen;
	char lpbuff[20] = { 0, };
	BYTE nChkSum = 0;

	// data �ձ��� Packet ����
	sprintf_s(szpacket, "%cA1%02X00%02X%04X", PACKET_STX, nTarget, nCommand, nLength);

	// data�� �����Ͽ� packet ����. hex�� ������ data�� �����Ƿ� memcpy�� ���
	packetlen = (int)strlen(szpacket);
	memcpy(&szpacket[packetlen], pData, nLength);

	// data �� ������ packet�� ���̸� ���Ѵ�.
	packetlen += nLength;

	// ������ Packet�� �̿��Ͽ� CheckSum�� ���Ѵ�.
	for (int j = 1; j < packetlen; j++)		// Check Sum
	{
		nChkSum += szpacket[j];
	}
	sprintf_s(lpbuff, "%02X%c", nChkSum, PACKET_ETX);

	// Checksum�� ETX 3byte�� �ٿ� �ٽ� Packet�� �����.
	memcpy(&szpacket[packetlen], lpbuff, 3);
	packetlen += 3;

	// Packet�� �������� String�� ���� �˸��� ���Ͽ� NULL�� �߰��Ѵ�.
	szpacket[packetlen] = 0x00;


	// Receive Buff�� Clear
	ZeroMemory(m_pCommand->gszudpRcvPacket, sizeof(m_pCommand->gszudpRcvPacket));

	// ������ Packet�� ����.
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
void CGIE_BoadAssyApp::Gf_ShowMessageBox(CString strMessage)
{
	CMessageError err_dlg;

	err_dlg.m_strEMessage = strMessage;
	err_dlg.DoModal();
}