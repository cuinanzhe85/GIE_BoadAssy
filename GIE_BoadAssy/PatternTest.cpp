// PatternTest.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GIE_BoadAssy.h"
#include "PatternTest.h"
#include "T2CmdGen.h"

// CPatternTest 대화 상자입니다.

IMPLEMENT_DYNAMIC(CPatternTest, CDialog)

CPatternTest::CPatternTest(CWnd* pParent /*=NULL*/)
	: CDialog(CPatternTest::IDD, pParent)
{

}

CPatternTest::~CPatternTest()
{
}

void CPatternTest::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST__PTN_VIEW, m_LCctrlPtnTestView);
}


BEGIN_MESSAGE_MAP(CPatternTest, CDialog)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CPatternTest 메시지 처리기입니다.

BOOL CPatternTest::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	lpModelInfo		= m_pApp->GetModelInfo();
	lpSystemInfo	= m_pApp->GetSystemInfo();		
	lpWorkInfo		= m_pApp->GetWorkInfo();

	m_pApp->Gf_writeLogData(_T("PatternTest Dialog"), _T("OPEN"));

	Lf_initVariable();
	Lf_initFontSet();
	Lf_insertListColum();
	Lf_insertListItem();
	Lf_sendPatternBluData();
	
	m_pApp->m_pCommand->Gf_setPowerSeqOnOff(TRUE);
	Sleep(lpModelInfo->m_nSeqDelay+500);
	m_pApp->m_pCommand->Gf_setI2CPullupEnable();

	SetTimer(1,200,NULL);
	SetTimer(2,1000,NULL);
	
	if(lpSystemInfo->m_nFastJudge == TRUE)
		SetTimer(3, 100, NULL); 

	SetTimer(4,100,NULL);
	SetTimer(100,100,NULL);

	m_pApp->Gf_setStartPtnLockTime(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CPatternTest::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	m_pApp->m_pCommand->Gf_setBluMinMax(_MIN_, 0);

	m_pApp->m_pCommand->Gf_setPowerSeqOnOff(FALSE);
}

void CPatternTest::RemoveMessageFromQueue()
{
	MSG msg;
	while (PeekMessage (&msg, m_hWnd, WM_KEYDOWN, WM_LBUTTONUP, PM_NOREMOVE))
		PeekMessage (&msg, GetSafeHwnd (), NULL, NULL, PM_REMOVE);
}

BOOL CPatternTest::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if( pMsg->message == WM_KEYDOWN)
	{
		RemoveMessageFromQueue();
		switch(pMsg->wParam)
		{
		case VK_RETURN:
			pMsg->wParam = VK_SPACE;
		case VK_SPACE:
			// ALT 또는 CONTROL 또는 SHIFT Key 입력 방지.
			if((GetKeyState(VK_MENU)<0) || (GetKeyState(VK_CONTROL)<0) || (GetKeyState(VK_SHIFT)<0))
				return TRUE;
		case VK_HOME:
		case VK_BACK:
		case VK_END:
			{
				m_pApp->Gf_setPatEndCheckTime(m_nSelNum);
				m_pApp->m_nPatTime[m_nSelNum] = (m_pApp->m_nEndCheckTime[m_nSelNum] - m_pApp->m_nStartCheckTime[m_nSelNum]);

				int SetTime;
				m_pApp->Gf_setEndPtnLockTime(m_nSelNum);
				SetTime = _ttoi(lpModelInfo->m_sLbPtnTms[m_nSelNum])*1000;

				if((m_pApp->m_nPtnLockTime[m_nSelNum] < SetTime) && (m_pApp->m_nPatLock[m_nSelNum]==FALSE))	
					return TRUE;	
				else
					m_pApp->m_nPatLock[m_nSelNum] = TRUE;

				Lf_excutePatternList(pMsg);

				return TRUE;
			}

		case VK_RIGHT:
		case VK_LEFT:
		case VK_UP:
		case VK_DOWN:
			{
				RemoveMessageFromQueue();

				m_LCctrlPtnTestView.SetSelectionMark(m_nSelNum); 
				m_LCctrlPtnTestView.SetItemState(m_nSelNum, LVIS_SELECTED | LVIS_FOCUSED, LVNI_SELECTED | LVNI_FOCUSED);
				m_LCctrlPtnTestView.SetFocus();			
				//			Lf_GrayDataWrite(pMsg->wParam);					
				return TRUE;
			}

		case VK_ESCAPE:
			{
				lpWorkInfo->m_sBadPattern.Format(_T("%s"), lpModelInfo->m_sLbPtnName[m_nSelNum].GetBuffer(0));
				lpWorkInfo->m_bEscDetect = true;
				m_pApp->Gf_writeLogData("KEY", "ESC Key");
				CDialog::OnCancel();
				return TRUE;
			}

		case 'A':
		case 'a':
			return TRUE;
		case 'C':
		case 'c':

			return TRUE;
		case 'E':
		case'e':
			return TRUE;
		case 'H':
		case'h':				
			return TRUE;	
		case 'W':
		case'w':
			return TRUE;
		case 'x':
		case 'X':
			return TRUE;
		case 'Q':
		case'q':
			return TRUE;
		case'Z':
		case 'z':
			return TRUE;

		case '1':	case '2':	case '3':	case '4':	case '5':
		case '6':	case '7':	case '8':	case '9':	case '0':
			{
				return TRUE;
			}
		case VK_F4:
			{
			}
			return TRUE;

		default:
			return TRUE;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}

HBRUSH CPatternTest::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	switch (nCtlColor)
	{
	case CTLCOLOR_MSGBOX:
		break;
	case CTLCOLOR_EDIT:
		break;
	case CTLCOLOR_LISTBOX:
		break;
	case CTLCOLOR_SCROLLBAR:
		break;
	case CTLCOLOR_BTN:
		break;
	case CTLCOLOR_STATIC:
		if((pWnd->GetDlgCtrlID()==IDC_STT_VCC_SET_TIT)
		|| (pWnd->GetDlgCtrlID()==IDC_STT_VCC_MEA_TIT)
		|| (pWnd->GetDlgCtrlID()==IDC_STT_ICC_MEA_TIT)
		|| (pWnd->GetDlgCtrlID()==IDC_STT_VDD_SET_TIT)
		|| (pWnd->GetDlgCtrlID()==IDC_STT_VDD_MEA_TIT)
		|| (pWnd->GetDlgCtrlID()==IDC_STT_IDD_MEA_TIT)
		|| (pWnd->GetDlgCtrlID()==IDC_STT_TT_TIT))
		{
			pDC->SetBkColor(COLOR_DEEP_BLUE);
			pDC->SetTextColor(COLOR_WHITE);
			return m_Brush[COLOR_IDX_DEEP_BLUE];
		}
		if((pWnd->GetDlgCtrlID()==IDC_STT_VCC_SET)
		|| (pWnd->GetDlgCtrlID()==IDC_STT_VDD_SET)
		|| (pWnd->GetDlgCtrlID()==IDC_STT_VCC_MEASURE)
		|| (pWnd->GetDlgCtrlID()==IDC_STT_VDD_MEASURE)
		|| (pWnd->GetDlgCtrlID()==IDC_STT_ICC_MEASURE)
		|| (pWnd->GetDlgCtrlID()==IDC_STT_IDD_MEASURE)
		|| (pWnd->GetDlgCtrlID()==IDC_STT_TACT_TIME))
		{
			pDC->SetBkColor(COLOR_GRAY192);
			pDC->SetTextColor(COLOR_BLACK);
			return m_Brush[COLOR_IDX_GRAY192];
		}
		break;
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}

void CPatternTest::Lf_initVariable()
{
	m_nSelNum=0;	
	m_pApp->m_nOldVsync = 0;
	m_pApp->pPtnIndex = &m_nSelNum;
	lpWorkInfo->m_bMicroPtnDone = false;
	lpWorkInfo->m_bEscDetect = false;
	lpWorkInfo->m_nFastJudge = FAST_JUDGE_NONE;
	m_nInspStartTime = ::GetTickCount ();
	memset(m_pApp->m_nPatLock, 0x00, sizeof(m_pApp->m_nPatLock));	
}

void CPatternTest::Lf_initFontSet()
{
	/*************************************************************************************************/
	// Font Set
	m_Font[0].CreateFont(24, 11, 0, 0, FW_SEMIBOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("Segoe UI Symbol"));

	m_Font[1].CreateFont(16, 6, 0, 0, FW_SEMIBOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("Segoe UI"));
	GetDlgItem(IDC_STT_VCC_SET_TIT)->SetFont(&m_Font[1]);
	GetDlgItem(IDC_STT_VCC_MEA_TIT)->SetFont(&m_Font[1]);
	GetDlgItem(IDC_STT_ICC_MEA_TIT)->SetFont(&m_Font[1]);
	GetDlgItem(IDC_STT_VDD_SET_TIT)->SetFont(&m_Font[1]);
	GetDlgItem(IDC_STT_VDD_MEA_TIT)->SetFont(&m_Font[1]);
	GetDlgItem(IDC_STT_IDD_MEA_TIT)->SetFont(&m_Font[1]);
	GetDlgItem(IDC_STT_TT_TIT)->SetFont(&m_Font[1]);
	GetDlgItem(IDC_STT_VCC_SET)->SetFont(&m_Font[1]);
	GetDlgItem(IDC_STT_VDD_SET)->SetFont(&m_Font[1]);
	GetDlgItem(IDC_STT_VCC_MEASURE)->SetFont(&m_Font[1]);
	GetDlgItem(IDC_STT_ICC_MEASURE)->SetFont(&m_Font[1]);
	GetDlgItem(IDC_STT_VDD_MEASURE)->SetFont(&m_Font[1]);
	GetDlgItem(IDC_STT_IDD_MEASURE)->SetFont(&m_Font[1]);
	GetDlgItem(IDC_STT_TACT_TIME)->SetFont(&m_Font[1]);

	m_Font[2].CreateFont(15, 8, 0, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0, 0, 0, _T("Segoe UI Symbol"));

	m_Font[3].CreateFont(34, 14, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("Segoe UI Symbol"));

	m_Font[4].CreateFont(60, 26, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("Segoe UI Symbol"));

	m_Font[5].CreateFont(150, 70, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("ARIAL"));

	/*************************************************************************************************/
	// Brush Set
	m_Brush[0].CreateSolidBrush (COLOR_ORANGE);
	m_Brush[COLOR_IDX_RED].CreateSolidBrush (COLOR_RED);
	m_Brush[2].CreateSolidBrush (COLOR_GRAY64);
	m_Brush[3].CreateSolidBrush (COLOR_GRAY94);
	m_Brush[COLOR_IDX_LIGHT_GREEN].CreateSolidBrush (COLOR_LIGHT_GREEN);
	m_Brush[COLOR_IDX_GRAY192].CreateSolidBrush (COLOR_GRAY192);
	m_Brush[COLOR_IDX_WHITE].CreateSolidBrush (COLOR_WHITE);
	m_Brush[COLOR_IDX_DEEP_BLUE].CreateSolidBrush (COLOR_DEEP_BLUE);	
}

bool CPatternTest::Lf_checkMicroPattern()
{
	int total=0;

	if((m_nSelNum == 0)&&(lpModelInfo->m_nMicroPtnCnt != 0))
	{
		total = lpWorkInfo->m_nGoodCnt+lpWorkInfo->m_nBadCnt;
		if ((total%lpModelInfo->m_nMicroPtnCnt) == 0)
		{
			return true;
		}
	}

	return false;
}

void CPatternTest::Lf_sendPtnData()
{
	CString sdata=_T(""),microPtn=_T("");

	if(Lf_checkMicroPattern() == true)
	{
		microPtn = lpModelInfo->m_sMicroPtnPath.Mid(lpModelInfo->m_sMicroPtnPath.ReverseFind(TEXT('\\'))+1);
		microPtn = microPtn.Mid(0, microPtn.GetLength()-4);
		sdata.Format( _T("%s  %s  (%sHz)"), microPtn.GetBuffer(0),
			lpModelInfo->m_sLbPtnFg[m_nSelNum].GetBuffer(0),
			lpModelInfo->m_sLbPtnVsync[m_nSelNum].GetBuffer(0));
		m_pApp->Gf_writeLogData(_T("PATTERN INFO"), sdata.GetBuffer(0));

		m_pApp->m_pCommand->Gf_setPGInfo(microPtn);
		lpWorkInfo->m_bMicroPtnDone = true;
	}
	else
	{
		sdata.Format( _T("%s  %s  (%sHz)"), lpModelInfo->m_sLbPtnName[m_nSelNum].GetBuffer(0)
			, lpModelInfo->m_sLbPtnFg[m_nSelNum].GetBuffer(0)
			, lpModelInfo->m_sLbPtnVsync[m_nSelNum].GetBuffer(0) );

		m_pApp->Gf_writeLogData(_T("PATTERN INFO"), sdata.GetBuffer(0));

		if(lpModelInfo->m_nGfd250 == TRUE)
			m_pApp->m_pCommand->Gf_setPGInfoGFD250(lpModelInfo->m_sLbPtnName[m_nSelNum]);
		else
			m_pApp->m_pCommand->Gf_setPGInfo(lpModelInfo->m_sLbPtnName[m_nSelNum]);
	}

	Lf_showDisplayLockTimeText();
}

BOOL CPatternTest::Lf_sendBluData()
{
	if(lpSystemInfo->m_nLedBlPort == 0)
		return TRUE;

	if(lpSystemInfo->m_nBluType == /*BLU_TYPE_AURORA*/2)
	{
// 		if (iBluValue < 0 || iBluValue > 255)
// 		{
// 			iBluValue = 90;
// 			strBluValue.Format("90");
// 		}
// 		retValue = pUiPorc->BackLight_AuroraSetData(iBluValue);
// 		outLog.Format("[BACK LIGHT] INDEX %d - VALUE : %s", index, strBluValue);
// 		pUiPorc->Message_Write(outLog, 0);
	}
	else if (lpSystemInfo->m_nBluType == 1/*BLU_TYPE_NEW*/ || lpSystemInfo->m_nBluType == 0/*BLU_TYPE_OLD*/)
	{
		if(m_pApp->m_pCommand->Gf_setBluMinMax(_MAX_, m_nSelNum) == FALSE)
		{			
			m_pApp->m_pCommand->Gf_ShowMessageBox(_T("BLU Communication Error"));//AfxMessageBox(_T("BLU Communication Error"));
		}
	}

	return TRUE;
}

void CPatternTest::Lf_sendPatternBluData()
{
	Lf_sendPtnData();
	Lf_sendBluData();
}

void CPatternTest::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if(nIDEvent==1)
	{	
		KillTimer(1);
		m_pApp->m_pCommand->Gf_getPowerMeasure();
		Lf_updateMeasureInfo();
		Lf_compareEEPRomData();
	}
	else if(nIDEvent==2)
	{
		KillTimer(2);
		m_pApp->m_pCommand->Gf_getPowerMeasure();
		Lf_updateMeasureInfo();
	}
	else if(nIDEvent==3)
	{
		KillTimer(3);

		if (m_pApp->m_pDio7250->Gf_getDIOJudgeOK())
		{
			m_pApp->Gf_writeLogData(_T("[PATTERN TEST]"), _T("DIO - JUDGE OK ON, FAST JUDGE"));
			lpWorkInfo->m_nFastJudge = FAST_JUDGE_OK;
			CDialog::OnCancel();
		}
		else if (m_pApp->m_pDio7250->Gf_getDIOJudgeNG())
		{
			m_pApp->Gf_writeLogData(_T("[PATTERN TEST]"), _T("DIO - JUDGE NG ON, FAST JUDGE"));
			lpWorkInfo->m_nFastJudge = FAST_JUDGE_NG;
			CDialog::OnCancel();
		}

		SetTimer(3, 100, NULL); 
	}
	else if(nIDEvent==4)
	{
		int locktime = _ttoi(lpModelInfo->m_sLbPtnTms[m_nSelNum])*1000;
		m_pApp->Gf_setEndPtnLockTime(m_nSelNum);	

		if(m_pApp->m_nPtnLockTime[m_nSelNum] > locktime)
		{
			int m_PacketLength=0;
			char m_szPacket[1024]={0,};

//			pUiPorc->comm.curData.iLockTimeDone = 1;

			if(m_pApp->m_nBMtoggle == 'S')
			{				
				CString sdata=_T(""),str=_T("");							
				str.Format(_T("%04d%04d%04d%04d%s"), ((lpModelInfo->m_nTimingHorActive-100)/2), (lpModelInfo->m_nTimingVerActive/2),200/*텍스트 길이*/,17/*텍스트 높이*/,"         ");
				sdata.Format(_T("CBTFFFF00000000BS%03d%s"),str.GetLength()+5,str);

				wchar_To_char(sdata.GetBuffer(0), m_szPacket);
				m_PacketLength = (int)strlen(m_szPacket);
				m_pApp->m_pCommand->Gf_setPacketSend(0, CMD_T2PTN_SEND, m_PacketLength, m_szPacket);
			}
			m_pApp->m_nBMtoggle = 0;
		}
	}
	else if(nIDEvent==100)
	{
		m_nInspTackTime = ::GetTickCount();
		m_nInspTackTime = m_nInspTackTime - m_nInspStartTime;
		if(m_nInspTackTime < 0)	m_nInspTackTime = 0;
		m_sTackTime.Format(_T("%.1f"), (m_nInspTackTime/1000.0));
		GetDlgItem(IDC_STT_TACT_TIME)->SetWindowText(m_sTackTime);
	}
	CDialog::OnTimer(nIDEvent);
}

void CPatternTest::Lf_updateMeasureInfo()
{
	CString sdata=_T("");

	if(m_pApp->m_nLcmPInfo[PINFO_ERR] == OVER_CURRENT)
	{
		if(m_pApp->m_nLcmPInfo[PINFO_NAME] == PINFO_VCC)
		{
			sdata.Format(_T("VCC Over Voltage (Set: %.2f, Measure: %.2f) VCC Over Voltage . Test End"), (float)lpModelInfo->m_fLimitVccMax, (float)(m_pApp->m_nLcmPInfo[PINFO_LIMIT]/100.f));
			m_pApp->m_pCommand->Gf_ShowMessageBox(sdata);//AfxMessageBox(sdata);
		}
		else if(m_pApp->m_nLcmPInfo[PINFO_NAME] == PINFO_VDD)
		{
			sdata.Format(_T("VDD Over Voltage (Set: %.2f, Measure: %.2f) VDD Over Voltage . Test End"), (float)lpModelInfo->m_fLimitVddMax, (float)(m_pApp->m_nLcmPInfo[PINFO_LIMIT]/100.f));
			m_pApp->m_pCommand->Gf_ShowMessageBox(sdata);//AfxMessageBox(sdata);
		}
		else if(m_pApp->m_nLcmPInfo[PINFO_NAME] == PINFO_ICC)
		{
			sdata.Format(_T("ICC Over Current (Set: %.2f, Measure: %d) ICC Over Current . Test End"), (float)lpModelInfo->m_fLimitIccMax, m_pApp->m_nLcmPInfo[PINFO_LIMIT]);
			m_pApp->m_pCommand->Gf_ShowMessageBox(sdata);//AfxMessageBox(sdata);
		}
		else if(m_pApp->m_nLcmPInfo[PINFO_NAME] == PINFO_IDD)
		{
			sdata.Format(_T("IDD Over Current (Set: %d, Measure: %d) IDD Over Current . Test End"), (float)lpModelInfo->m_fLimitIddMax, m_pApp->m_nLcmPInfo[PINFO_LIMIT]);
			m_pApp->m_pCommand->Gf_ShowMessageBox(sdata);//AfxMessageBox(sdata);
		}

		CDialog::OnCancel();
		return;
	}
	else if(m_pApp->m_nLcmPInfo[PINFO_ERR] == LOW_CURRENT)
	{
/*
		if(m_pApp->nLcmPInfo[m_pApp->nCTRL_ID][PINFO_NAME] == PINFO_VCC)
		{
			sprintf(m_pApp->szLog, "(Set: %.2f, Measure: %.2f) VCC Low Voltage . Test End", 
				(float)lpFusingInfo->gnAgingCtrlVccLow, (float)(m_pApp->nLcmPInfo[m_pApp->nCTRL_ID][PINFO_LIMIT]/100.f));
			m_pApp->pCommApi->ShowMessageBox2("VCC Low Voltage", m_pApp->szLog);
		}
		else if(m_pApp->nLcmPInfo[m_pApp->nCTRL_ID][PINFO_NAME] == PINFO_VDD)
		{
			sprintf(m_pApp->szLog, "(Set: %.2f, Measure: %.2f) VDD Low Voltage . Test End", 
				(float)lpFusingInfo->gnAgingCtrlVddLow, (float)(m_pApp->nLcmPInfo[m_pApp->nCTRL_ID][PINFO_LIMIT]/100.f));
			m_pApp->pCommApi->ShowMessageBox2("VDD Low Voltage", m_pApp->szLog);
		}
		else if(m_pApp->nLcmPInfo[m_pApp->nCTRL_ID][PINFO_NAME] == PINFO_VBL)
		{
			sprintf(m_pApp->szLog, "(Set: %.2f, Measure: %.2f) VBL Low Voltage . Test End", 
				(float)lpFusingInfo->gnAgingCtrlVblLow, (float)(m_pApp->nLcmPInfo[m_pApp->nCTRL_ID][PINFO_LIMIT]/100.f));
			m_pApp->pCommApi->ShowMessageBox2("VBL Low Voltage", m_pApp->szLog);
		}
		else if(m_pApp->nLcmPInfo[m_pApp->nCTRL_ID][PINFO_NAME] == PINFO_ICC)
		{
			sprintf(m_pApp->szLog, "(Set: %d, Measure: %d) ICC Low Current . Test End", 
				lpFusingInfo->gnAgingCtrlIccLow, m_pApp->nLcmPInfo[m_pApp->nCTRL_ID][PINFO_LIMIT]);
			m_pApp->pCommApi->ShowMessageBox2("ICC Low Current", m_pApp->szLog);
		}
		else if(m_pApp->nLcmPInfo[m_pApp->nCTRL_ID][PINFO_NAME] == PINFO_IDD)
		{
			sprintf(m_pApp->szLog, "(Set: %d, Measure: %d) IDD Low Current . Test End",
				lpFusingInfo->gnAgingCtrlIddLow, m_pApp->nLcmPInfo[m_pApp->nCTRL_ID][PINFO_LIMIT]);
			m_pApp->pCommApi->ShowMessageBox2("IDD Low Current", m_pApp->szLog);
		}
		else if(m_pApp->nLcmPInfo[m_pApp->nCTRL_ID][PINFO_NAME] == PINFO_IBL)
		{
			sprintf(m_pApp->szLog, "(Set: %d, Measure: %d) IBL Low Current . Test End", 
				lpFusingInfo->gnAgingCtrlIblLow, m_pApp->nLcmPInfo[m_pApp->nCTRL_ID][PINFO_LIMIT]*10);
			m_pApp->pCommApi->ShowMessageBox2("IBL Low Current", m_pApp->szLog);
		}

		CDialog::OnCancel();
		return;
*/
	}
	else
	{
		SetTimer(2, 1000, NULL);
	}
	sdata.Format(_T("%.2f V"), (float)(lpModelInfo->m_fVoltVcc));
	GetDlgItem(IDC_STT_VCC_SET)->SetWindowText(sdata);	

	sdata.Format(_T("%.2f V"), (float)(m_pApp->m_nLcmPInfo[0]*0.01));
	GetDlgItem(IDC_STT_VCC_MEASURE)->SetWindowText(sdata);

	sdata.Format(_T("%d mA"), m_pApp->m_nLcmPInfo[3]);
	GetDlgItem(IDC_STT_ICC_MEASURE)->SetWindowText(sdata);	

	sdata.Format(_T("%.2f V"), (float)(lpModelInfo->m_fVoltVdd));
	GetDlgItem(IDC_STT_VDD_SET)->SetWindowText(sdata);

	sdata.Format(_T("%.2f V"), (float)(m_pApp->m_nLcmPInfo[1]*0.01));
	GetDlgItem(IDC_STT_VDD_MEASURE)->SetWindowText(sdata);

	sdata.Format(_T("%d mA"), m_pApp->m_nLcmPInfo[4]);
	GetDlgItem(IDC_STT_IDD_MEASURE)->SetWindowText(sdata);
}

void CPatternTest::Lf_excutePatternList(MSG* pMsg)
{
	if((GetKeyState(VK_MENU)<0) || (GetKeyState(VK_CONTROL)<0) || (GetKeyState(VK_SHIFT)<0))
		return;

	switch(pMsg->wParam)
	{
	case VK_SPACE:
	case VK_RETURN:
		if(lpModelInfo->m_nLbCnt-1 <= m_nSelNum)  
		{ 
			m_pApp->Gf_writeLogData(_T("Pattern Test"), _T("END"));

			CDialog::OnOK();
			return;
		}

		m_LCctrlPtnTestView.SetSelectionMark(++m_nSelNum); 
		m_LCctrlPtnTestView.SetItemState(m_nSelNum, LVIS_SELECTED | LVIS_FOCUSED, LVNI_SELECTED | LVNI_FOCUSED);
		m_LCctrlPtnTestView.SetFocus();

		break;
	case VK_BACK:
		if(m_nSelNum <= 0)  
		{ 
			return;
		}		
		m_LCctrlPtnTestView.SetSelectionMark(--m_nSelNum); 
		m_LCctrlPtnTestView.SetItemState(m_nSelNum, LVIS_SELECTED | LVIS_FOCUSED, LVNI_SELECTED | LVNI_FOCUSED);
		m_LCctrlPtnTestView.SetFocus();
		break;

	case VK_HOME:
		if(m_nSelNum == 0)	return;
		m_nSelNum = 0;
		break;

	case VK_END:
		if(m_nSelNum == lpModelInfo->m_nLbCnt-1)	return;
		m_nSelNum = lpModelInfo->m_nLbCnt-1;
		break;
	}

	RemoveMessageFromQueue();
	m_pApp->Gf_setPatStartCheckTime(m_nSelNum);
	m_pApp->Gf_setStartPtnLockTime(m_nSelNum);
	Lf_sendPatternBluData();
}


void CPatternTest::Lf_insertListColum()
{
	CRect rect,rect2;
	DWORD dwStype;

	m_LCctrlPtnTestView.GetClientRect(&rect);
	m_LCctrlPtnTestView.InsertColumn( 0, _T("No"), LVCFMT_LEFT, -1, -1);
	m_LCctrlPtnTestView.InsertColumn( 1, _T("Pattern Name"), LVCFMT_LEFT, -1, -1 );
	m_LCctrlPtnTestView.InsertColumn( 2, _T("FG"), LVCFMT_LEFT, -1, -1 );
	m_LCctrlPtnTestView.InsertColumn( 3, _T("BG"), LVCFMT_LEFT, -1, -1 );
	m_LCctrlPtnTestView.InsertColumn( 4, _T("VCC"), LVCFMT_LEFT, -1, -1 );
	m_LCctrlPtnTestView.InsertColumn( 5, _T("VDD"), LVCFMT_LEFT, -1, -1 );
	m_LCctrlPtnTestView.InsertColumn( 6, _T("T(s)"), LVCFMT_LEFT, -1, -1 );
	m_LCctrlPtnTestView.InsertColumn( 7, _T("VSync"), LVCFMT_LEFT, -1, -1 );
	m_LCctrlPtnTestView.InsertColumn( 8, _T("VCOM"), LVCFMT_LEFT, -1, -1 );

	m_LCctrlPtnTestView.SetColumnWidth( 0, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER ); // NO
	GetDlgItem(IDC_STT_NUM)->GetWindowRect(&rect2);
	m_LCctrlPtnTestView.SetColumnWidth( 0, rect2.Width());

	m_LCctrlPtnTestView.SetColumnWidth( 1, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER ); // Pattern
	GetDlgItem(IDC_STT_PTN_NAME)->GetWindowRect(&rect2);
	m_LCctrlPtnTestView.SetColumnWidth( 1, rect2.Width());

	m_LCctrlPtnTestView.SetColumnWidth( 2, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER ); // FG
	GetDlgItem(IDC_STT_FG)->GetWindowRect(&rect2);
	m_LCctrlPtnTestView.SetColumnWidth( 2, rect2.Width());

	m_LCctrlPtnTestView.SetColumnWidth( 3, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER ); // BG
	GetDlgItem(IDC_STT_BG)->GetWindowRect(&rect2);
	m_LCctrlPtnTestView.SetColumnWidth( 3, rect2.Width());

	m_LCctrlPtnTestView.SetColumnWidth( 4, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER ); // VCC
	GetDlgItem(IDC_STT_VCC)->GetWindowRect(&rect2);
	m_LCctrlPtnTestView.SetColumnWidth( 4, rect2.Width());

	m_LCctrlPtnTestView.SetColumnWidth( 5, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER ); // VDD
	GetDlgItem(IDC_STT_VDD)->GetWindowRect(&rect2);
	m_LCctrlPtnTestView.SetColumnWidth( 5, rect2.Width());

	m_LCctrlPtnTestView.SetColumnWidth( 6, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER ); // T(ms)
	GetDlgItem(IDC_STT_TMS)->GetWindowRect(&rect2);
	m_LCctrlPtnTestView.SetColumnWidth( 6, rect2.Width());

	m_LCctrlPtnTestView.SetColumnWidth( 7, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER ); // VSYNC
	GetDlgItem(IDC_STT_VSYNC)->GetWindowRect(&rect2);
	m_LCctrlPtnTestView.SetColumnWidth( 7, rect2.Width());

	m_LCctrlPtnTestView.SetColumnWidth( 8, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER ); // VCOM
	GetDlgItem(IDC_STT_VCOM)->GetWindowRect(&rect2);
	m_LCctrlPtnTestView.SetColumnWidth( 8, rect2.Width());

	dwStype = m_LCctrlPtnTestView.GetExtendedStyle();
	dwStype |= LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES;
	m_LCctrlPtnTestView.SetExtendedStyle(dwStype);
}

void CPatternTest::Lf_insertListItem()
{
	int loop=0;
	CString strNum= _T("");

	for(loop=0; loop< lpModelInfo->m_nLbCnt; loop++)
	{
		strNum.Format(_T("%d"), loop);
		m_LCctrlPtnTestView.InsertItem(loop, strNum);
		m_LCctrlPtnTestView.SetItemText(loop, 1,lpModelInfo->m_sLbPtnName[loop]);
		m_LCctrlPtnTestView.SetItemText(loop, 2, lpModelInfo->m_sLbPtnFg[loop]);
		m_LCctrlPtnTestView.SetItemText(loop, 3, lpModelInfo->m_sLbPtnBg[loop]);
		m_LCctrlPtnTestView.SetItemText(loop, 4, lpModelInfo->m_sLbPtnVcc[loop]);
		m_LCctrlPtnTestView.SetItemText(loop, 5, lpModelInfo->m_sLbPtnVdd[loop]);
		m_LCctrlPtnTestView.SetItemText(loop, 6, lpModelInfo->m_sLbPtnTms[loop]);
		m_LCctrlPtnTestView.SetItemText(loop, 7, lpModelInfo->m_sLbPtnVsync[loop]);
		m_LCctrlPtnTestView.SetItemText(loop, 8, lpModelInfo->m_sLbPtnVcom[loop]);
	}

	m_LCctrlPtnTestView.SetSelectionMark(m_nSelNum); 
	m_LCctrlPtnTestView.SetItemState(m_nSelNum, LVIS_SELECTED | LVIS_FOCUSED, LVNI_SELECTED | LVNI_FOCUSED);
	m_LCctrlPtnTestView.SetFocus();
}

BOOL CPatternTest::Lf_cmpEdidData()
{
	BOOL m_bRtnCode=FALSE;
	int size=0;

	if(lpModelInfo->m_nEdidSize == 0)	
		size = 128;
	else								
		size = 256;

	if(lpModelInfo->m_nGfd250 == TRUE)
		m_bRtnCode = m_pApp->m_pCommand->Gf_getGfd250I2CReadPacketSend(0, size, 1/*I2C_CMD_EDID_READ*/);
	else
		m_bRtnCode = m_pApp->m_pCommand->Gf_setEEPRomReadData();

	return m_bRtnCode;
}

void CPatternTest::Lf_compareEEPRomData()
{
	if(lpModelInfo->m_nEdidUse == TRUE)
	{
		if(Lf_cmpEdidData() == TRUE)
		{
			int i=0,size=0;			
			CString sdata1=_T(""),sdata2=_T("");
			BOOL bCompResult=TRUE;

			if(lpModelInfo->m_nEdidSize == 0)	
				size = 128;
			else								
				size = 256;

			for(i=0; i<size; i++)
			{
				if(m_pApp->m_nEEPRomFileData[i] != m_pApp->m_nEEPRomReadData[i])
				{
					bCompResult = FALSE;
					break;
				}
			}

			for(i=0; i<size; i++)
			{
				sdata1.Format(_T("%02X "), (BYTE)m_pApp->m_nEEPRomFileData[i]);
				sdata2.Append(sdata1);
			}
			m_pApp->Gf_writeLogData(_T("EDID File Data  "), sdata2.GetBuffer(0));

			sdata1.Empty();
			sdata2.Empty();
			for(i=0; i<size; i++)
			{
				sdata1.Format(_T("%02X "), (BYTE)m_pApp->m_nEEPRomReadData[i]);
				sdata2.Append(sdata1);
			}
			m_pApp->Gf_writeLogData(_T("EDID Read Data"), sdata2.GetBuffer(0));

			if(bCompResult == FALSE)
			{
	#ifdef	USE_GMES
				lpWorkInfo->Edid = 'F';
	#endif
				lpWorkInfo->m_bIsEdidFail = true;
				m_pApp->m_pCommand->Gf_ShowMessageBox(_T("EDID Read Compare Fail!!!"));//AfxMessageBox(_T("EDID Read Compare Fail!!!"));
				m_pApp->m_pCommand->Gf_setPowerSeqOnOff(POWER_OFF);	
				CDialog::OnCancel();
				return;
			}
			else
			{
	#ifdef	USE_GMES
				lpWorkInfo->Edid = 'P';
	#endif
				m_pApp->Gf_writeLogData(_T("EDID Data Compare"), _T("Compare OK"));
			}
		} 
		else
		{
			lpWorkInfo->m_bIsEdidFail = true;
			m_pApp->m_pCommand->Gf_ShowMessageBox(_T("EDID Read Communication Error!!!"));//AfxMessageBox(_T("EDID Read Communication Error!!!"));
			m_pApp->m_pCommand->Gf_setPowerSeqOnOff(POWER_OFF);
		}	
	}
}

void CPatternTest::Lf_showDisplayLockTimeText()
{
	char m_szPacket[1024]={0,};
	int m_PacketLength=0;

	if(lpSystemInfo->m_nOperationMode == IN_LINE)
	{		
		// 문자열이랑 "+"가 PG에서 같은 layer를 쓰고 있어서..... "BM"에 대한 Flag 이다. 130418
		if((lpSystemInfo->m_sModelName.Find(_T("LP079Q")) == -1) 
		//&& (!pUiPorc->comm.curData.cPG_BitmapFlag) 
		&& (!(lpModelInfo->m_sLbPtnName[m_nSelNum] == _T("RG2Dot_127.pdb"))) 
		&& (!(lpModelInfo->m_sLbPtnName[m_nSelNum] == _T("RG2Dot_255.pdb"))) 
		)	
		{
			CString sdata=_T(""),str=_T("");							
			str.Format(_T("%04d%04d%04d%04d%s"), ((lpModelInfo->m_nTimingHorActive-100)/2), (lpModelInfo->m_nTimingVerActive/2),200/*텍스트 길이*/,17/*텍스트 높이*/,_T("LOCK TIME"));
			sdata.Format(_T("CBTFFFF00000000BS%03d%s"),str.GetLength()+5,str);
			
			wchar_To_char(sdata.GetBuffer(0), m_szPacket);
			m_PacketLength = (int)strlen(m_szPacket);
			m_pApp->m_pCommand->Gf_setPacketSend(0, CMD_T2PTN_SEND, m_PacketLength, m_szPacket);

			m_pApp->m_nBMtoggle = 'S';
		}
	}
}

void CPatternTest::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CString sdata=_T("");
	
	m_pApp->Gf_setPatEndCheckTime(m_nSelNum);
	m_pApp->m_nPatTime[m_nSelNum] = (m_pApp->m_nEndCheckTime[m_nSelNum] - m_pApp->m_nStartCheckTime[m_nSelNum]);

	int SetTime;
	m_pApp->Gf_setEndPtnLockTime(m_nSelNum);
	SetTime = _ttoi(lpModelInfo->m_sLbPtnTms[m_nSelNum])*1000;

	if((m_pApp->m_nPtnLockTime[m_nSelNum] < SetTime) && (m_pApp->m_nPatLock[m_nSelNum]==FALSE))	
		return;	
	else
		m_pApp->m_nPatLock[m_nSelNum] = TRUE;

	m_pApp->Gf_writeLogData(_T("[BUTTON DOWN]"), _T("LEFT - NEXT"));

	// on 일때 reset 기능
	if(m_nSelNum <= lpModelInfo->m_nLbCnt-1)
	{
		if(lpModelInfo->m_nLbCnt-1 <= m_nSelNum)  
		{ 
			m_pApp->Gf_writeLogData(_T("Pattern Test"), _T("END"));

			CDialog::OnOK();
			return;
		}

		m_LCctrlPtnTestView.SetSelectionMark(++m_nSelNum); 
		m_LCctrlPtnTestView.SetItemState(m_nSelNum, LVIS_SELECTED | LVIS_FOCUSED, LVNI_SELECTED | LVNI_FOCUSED);
		m_LCctrlPtnTestView.SetFocus();
	}

	RemoveMessageFromQueue();
	m_pApp->Gf_setStartPtnLockTime(m_nSelNum);
	Lf_sendPatternBluData();

	CDialog::OnLButtonDown(nFlags, point);
}

void CPatternTest::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if(m_nSelNum <= 0)  
	{ 
		return;
	}		
	m_LCctrlPtnTestView.SetSelectionMark(--m_nSelNum); 
	m_LCctrlPtnTestView.SetItemState(m_nSelNum, LVIS_SELECTED | LVIS_FOCUSED, LVNI_SELECTED | LVNI_FOCUSED);
	m_LCctrlPtnTestView.SetFocus();

	RemoveMessageFromQueue();
	m_pApp->Gf_setStartPtnLockTime(m_nSelNum);
	Lf_sendPatternBluData();

	CDialog::OnRButtonDown(nFlags, point);
}

