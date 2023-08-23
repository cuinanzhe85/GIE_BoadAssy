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
	DDX_Control(pDX, IDC_LIST_PATTERN_TEST_MASSAGE, m_listPtnTestEvent);
	DDX_Control(pDX, IDC_PIC_PTN_IMAGE_VIEW, m_picPtnImageView);
}


BEGIN_MESSAGE_MAP(CPatternTest, CDialog)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CPatternTest 메시지 처리기입니다.

BOOL CPatternTest::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	lpModelInfo		= m_pApp->GetModelInfo();
	lpSystemInfo	= m_pApp->GetSystemInfo();		
	lpWorkInfo		= m_pApp->GetWorkInfo();

	m_pApp->Gf_writeLogData(_T("<WND>"), _T("PatternTest Dialog Open"));
	
	Lf_initVariable();
	Lf_initFontSet();
	Lf_insertListColum();
	Lf_insertListItem();

	m_pApp->m_pCommand->Gf_setPGInfoPatternName(_T("BLACK"));
	m_pApp->m_pCommand->Gf_setPowerSeqOnOff(POWER_ON);
	m_pApp->Gf_setPatStartCheckTime(m_nSelNum);
	Lf_sendPatternBluData();

	SetTimer(1,200,NULL);	// EDID
	SetTimer(3, 1000, NULL);  // OK,NG DIO Input Check
	SetTimer(5, 500, NULL);  // 첫번째 패턴 이미지 출력

	SetTimer(100,100,NULL);

	m_pApp->Gf_setStartPtnLockTime(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
void CPatternTest::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialog::OnPaint()을(를) 호출하지 마십시오.
	CRect rect;
	GetClientRect(&rect);
	dc.FillSolidRect(rect, COLOR_GRAY64);
}

void CPatternTest::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	for (int i = 0; i < COLOR_IDX_MAX; i++)
	{
		m_Brush[i].DeleteObject();
	}
	for (int i = 0; i < FONT_IDX_MAX; i++)
	{
		m_Font[i].DeleteObject();
	}

	CString sLog;
	sLog.Format(_T("BLU Duty (min) : %d"), lpModelInfo->m_nBluMin);
	m_pApp->Gf_writeLogData(_T("<TEST>"), sLog);
	m_pApp->m_pCommand->Gf_setBluDuty(lpModelInfo->m_nBluMin);

	m_pApp->m_pCommand->Gf_setPowerSeqOnOff(POWER_OFF);
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
		case VK_SPACE:
			// ALT 또는 CONTROL 또는 SHIFT Key 입력 방지.
			if((GetKeyState(VK_MENU)<0) || (GetKeyState(VK_CONTROL)<0) || (GetKeyState(VK_SHIFT)<0))
				return TRUE;
		case VK_HOME:
		case VK_BACK:
		case VK_END:
			{
				if (Lf_PatternLockTimeCheck() != TRUE)
					return TRUE;

#if (SUMMARY_LOG_VOLT_CURR==1)
				if (m_bPowerMeasureComplete[m_nSelNum] == FALSE)
					return TRUE;
#endif

				Lf_writeLogKeyIn((int)pMsg->wParam);
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

				Lf_writeLogKeyIn((int)pMsg->wParam);
				Lf_setPatternGrayLevel((int)pMsg->wParam);
				return TRUE;
			}

		case VK_ESCAPE:
			{
				lpWorkInfo->m_sBadPattern.Format(_T("%s"), lpModelInfo->m_sLbPtnName[m_nSelNum].GetBuffer(0));
				lpWorkInfo->m_bEscDetect = true;

				Lf_PtnTestEventView(_T("'ESC' Key In"));
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
		case 'h':				
			return TRUE;	
		case 'W':
		case 'w':
			return TRUE;
		case 'x':
		case 'X':
			return TRUE;
		case 'Q':
		case 'q':
			return TRUE;
		case 'Z':
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
	{
		if (pWnd->GetDlgCtrlID() == IDC_LIST_PATTERN_TEST_MASSAGE)
		{
			pDC->SetBkColor(COLOR_BLACK);
			pDC->SetTextColor(COLOR_CYAN);
			return m_Brush[COLOR_IDX_BLACK];
		}
	}
		break;
	case CTLCOLOR_SCROLLBAR:
		break;
	case CTLCOLOR_BTN:
		break;
	case CTLCOLOR_STATIC:
		if((pWnd->GetDlgCtrlID()==IDC_STT_VCC_MEA_TIT)
		|| (pWnd->GetDlgCtrlID()==IDC_STT_ICC_MEA_TIT)
		|| (pWnd->GetDlgCtrlID()==IDC_STT_VDD_MEA_TIT)
		|| (pWnd->GetDlgCtrlID()==IDC_STT_IDD_MEA_TIT)
			|| (pWnd->GetDlgCtrlID() == IDC_STT_VBL_MEA_TIT)
			|| (pWnd->GetDlgCtrlID() == IDC_STT_IBL_MEA_TIT)
			|| (pWnd->GetDlgCtrlID() == IDC_STT_VGH_MEA_TIT)
			|| (pWnd->GetDlgCtrlID() == IDC_STT_VGL_MEA_TIT)
			|| (pWnd->GetDlgCtrlID() == IDC_STT_IGH_MEA_TIT)
			|| (pWnd->GetDlgCtrlID() == IDC_STT_IGL_MEA_TIT)
		|| (pWnd->GetDlgCtrlID()==IDC_STT_TT_TIT))
		{
			pDC->SetBkColor(COLOR_DEEP_BLUE);
			pDC->SetTextColor(COLOR_WHITE);
			return m_Brush[COLOR_IDX_DEEP_BLUE];
		}
		if((pWnd->GetDlgCtrlID()==IDC_STT_VCC_MEASURE)
		|| (pWnd->GetDlgCtrlID()==IDC_STT_VDD_MEASURE)
		|| (pWnd->GetDlgCtrlID()==IDC_STT_ICC_MEASURE)
		|| (pWnd->GetDlgCtrlID()==IDC_STT_IDD_MEASURE)
			|| (pWnd->GetDlgCtrlID() == IDC_STT_VBL_MEASURE)
			|| (pWnd->GetDlgCtrlID() == IDC_STT_IBL_MEASURE)
			|| (pWnd->GetDlgCtrlID() == IDC_STT_VGH_MEASURE)
			|| (pWnd->GetDlgCtrlID() == IDC_STT_VGL_MEASURE)
			|| (pWnd->GetDlgCtrlID() == IDC_STT_IGH_MEASURE)
			|| (pWnd->GetDlgCtrlID() == IDC_STT_IGL_MEASURE)
		|| (pWnd->GetDlgCtrlID()==IDC_STT_TACT_TIME))
		{
			pDC->SetBkColor(COLOR_BLACK);
			pDC->SetTextColor(COLOR_GREEN);
			return m_Brush[COLOR_IDX_BLACK];
		}
		if (pWnd->GetDlgCtrlID() == IDC_STT_PTN_LIST_TITLE
			|| pWnd->GetDlgCtrlID() == IDC_STT_PTN_TEST_MESSAGE
			|| pWnd->GetDlgCtrlID() == IDC_STT_PTN_IMAGE_TITLE)
		{
			pDC->SetBkColor(COLOR_LIGHT_BLUE);
			pDC->SetTextColor(COLOR_BLACK);
			return m_Brush[COLOR_IDX_LIGHT_BLUE];
		}
		if (pWnd->GetDlgCtrlID() == IDC_STT_TP_COLOR_R_VAL)
		{
			pDC->SetBkColor(COLOR_RED);
			pDC->SetTextColor(COLOR_WHITE);
			return m_Brush[COLOR_IDX_RED];
		}
		if (pWnd->GetDlgCtrlID() == IDC_STT_TP_COLOR_G_VAL)
		{
			pDC->SetBkColor(COLOR_GREEN);
			pDC->SetTextColor(COLOR_WHITE);
			return m_Brush[COLOR_IDX_GREEN];
		}
		if (pWnd->GetDlgCtrlID() == IDC_STT_TP_COLOR_B_VAL)
		{
			pDC->SetBkColor(COLOR_BLUE);
			pDC->SetTextColor(COLOR_WHITE);
			return m_Brush[COLOR_IDX_BLUE];
		}
		if (pWnd->GetDlgCtrlID() == IDC_STT_TP_EDID_RESULT)
		{
			if (lpModelInfo->m_nEdidUse != TRUE)
			{
				pDC->SetBkColor(COLOR_GRAY96);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_GRAY96];
			}
			else
			{
				CString strResult;
				GetDlgItem(IDC_STT_TP_EDID_RESULT)->GetWindowTextW(strResult);
				if (strResult == _T("OK"))
				{
					pDC->SetBkColor(COLOR_GREEN);
					pDC->SetTextColor(COLOR_WHITE);
					return m_Brush[COLOR_IDX_GREEN];
				}
				else if (strResult == _T("NG"))
				{
					pDC->SetBkColor(COLOR_RED);
					pDC->SetTextColor(COLOR_WHITE);
					return m_Brush[COLOR_IDX_RED];
				}
			}
		}
		break;
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}

void CPatternTest::Lf_initVariable()
{
	m_nBluDutyOld = 0;
	m_nSelNum=0;	

#if (SUMMARY_LOG_VOLT_CURR==1)
	memset(m_bPowerMeasureComplete, 0x00, sizeof(m_bPowerMeasureComplete));
#endif

	m_pApp->m_nOldVsync = 0;
	m_pApp->pPtnIndex = &m_nSelNum;
	lpWorkInfo->m_bEscDetect = false;
	lpWorkInfo->m_nFastDioJudge = FAST_JUDGE_NONE;
	m_nInspStartTime = ::GetTickCount ();
	memset(m_pApp->m_nPatLock, 0x00, sizeof(m_pApp->m_nPatLock));	

	lpWorkInfo->m_bIsEdidFail = false;

	// 제품의 해상도 설정
	CRect rcLCD, rcFrame;

	rcLCD.top = 0;
	rcLCD.left = 0;
	rcLCD.right = lpModelInfo->m_nTimingHorActive;
	rcLCD.bottom = lpModelInfo->m_nTimingVerActive;

	// Preview 영역 설정
	GetDlgItem(IDC_STT_PTN_IMAGE_VIEW_SIZE)->GetWindowRect(rcFrame);
	ScreenToClient(rcFrame);

	// Preview 영역 초기화
	m_pApp->m_pPatternView->InitPatternRect(GetDC(), rcLCD, rcFrame);
	m_pApp->m_pPatternView->InitPatternPath(_T(""));
	m_pApp->m_pPatternView->InitBmpPatternPath(_T(""));
}

void CPatternTest::Lf_initFontSet()
{
	/*************************************************************************************************/
	// Font Set
	m_Font[0].CreateFont(24, 11, 0, 0, FW_SEMIBOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("Segoe UI Symbol"));
	GetDlgItem(IDC_STT_TACT_TIME)->SetFont(&m_Font[0]);

	m_Font[1].CreateFont(16, 6, 0, 0, FW_SEMIBOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("Segoe UI Symbol"));
	GetDlgItem(IDC_STT_VCC_MEA_TIT)->SetFont(&m_Font[1]);
	GetDlgItem(IDC_STT_ICC_MEA_TIT)->SetFont(&m_Font[1]);
	GetDlgItem(IDC_STT_VDD_MEA_TIT)->SetFont(&m_Font[1]);
	GetDlgItem(IDC_STT_IDD_MEA_TIT)->SetFont(&m_Font[1]);
	GetDlgItem(IDC_STT_VBL_MEA_TIT)->SetFont(&m_Font[1]);
	GetDlgItem(IDC_STT_IBL_MEA_TIT)->SetFont(&m_Font[1]);
	GetDlgItem(IDC_STT_VGH_MEA_TIT)->SetFont(&m_Font[1]);
	GetDlgItem(IDC_STT_VGL_MEA_TIT)->SetFont(&m_Font[1]);
	GetDlgItem(IDC_STT_IGH_MEA_TIT)->SetFont(&m_Font[1]);
	GetDlgItem(IDC_STT_IGL_MEA_TIT)->SetFont(&m_Font[1]);
	GetDlgItem(IDC_STT_TT_TIT)->SetFont(&m_Font[1]);
	GetDlgItem(IDC_STT_VCC_MEASURE)->SetFont(&m_Font[1]);
	GetDlgItem(IDC_STT_ICC_MEASURE)->SetFont(&m_Font[1]);
	GetDlgItem(IDC_STT_VDD_MEASURE)->SetFont(&m_Font[1]);
	GetDlgItem(IDC_STT_IDD_MEASURE)->SetFont(&m_Font[1]);
	GetDlgItem(IDC_STT_VBL_MEASURE)->SetFont(&m_Font[1]);
	GetDlgItem(IDC_STT_IBL_MEASURE)->SetFont(&m_Font[1]);
	GetDlgItem(IDC_STT_VGH_MEASURE)->SetFont(&m_Font[1]);
	GetDlgItem(IDC_STT_VGL_MEASURE)->SetFont(&m_Font[1]);
	GetDlgItem(IDC_STT_IGH_MEASURE)->SetFont(&m_Font[1]);
	GetDlgItem(IDC_STT_IGL_MEASURE)->SetFont(&m_Font[1]);

	GetDlgItem(IDC_LIST__PTN_VIEW)->SetFont(&m_Font[1]);
	GetDlgItem(IDC_LIST_PATTERN_TEST_MASSAGE)->SetFont(&m_Font[1]);

	GetDlgItem(IDC_STT_TP_COLOR_R_VAL)->SetFont(&m_Font[1]);
	GetDlgItem(IDC_STT_TP_COLOR_G_VAL)->SetFont(&m_Font[1]);
	GetDlgItem(IDC_STT_TP_COLOR_B_VAL)->SetFont(&m_Font[1]);

	GetDlgItem(IDC_STT_TP_EDID_RESULT)->SetFont(&m_Font[1]);

	m_Font[2].CreateFont(15, 8, 0, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0, 0, 0, _T("Segoe UI Symbol"));

	m_Font[3].CreateFont(34, 14, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("Segoe UI Symbol"));

	m_Font[4].CreateFont(60, 26, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("Segoe UI Symbol"));

	m_Font[5].CreateFont(150, 70, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("ARIAL"));

	/*************************************************************************************************/
	// Brush Set
	m_Brush[COLOR_IDX_ORANGE].CreateSolidBrush (COLOR_ORANGE);
	m_Brush[COLOR_IDX_BLACK].CreateSolidBrush(COLOR_BLACK);
	m_Brush[COLOR_IDX_RED].CreateSolidBrush (COLOR_RED);
	m_Brush[COLOR_IDX_GREEN].CreateSolidBrush(COLOR_GREEN);
	m_Brush[COLOR_IDX_BLUE].CreateSolidBrush(COLOR_BLUE);
	m_Brush[COLOR_IDX_GRAY64].CreateSolidBrush (COLOR_GRAY64);
	m_Brush[COLOR_IDX_GRAY94].CreateSolidBrush (COLOR_GRAY94);
	m_Brush[COLOR_IDX_GRAY96].CreateSolidBrush(COLOR_GRAY96);
	m_Brush[COLOR_IDX_LIGHT_GREEN].CreateSolidBrush (COLOR_LIGHT_GREEN);
	m_Brush[COLOR_IDX_GRAY192].CreateSolidBrush (COLOR_GRAY192);
	m_Brush[COLOR_IDX_GREEN128].CreateSolidBrush(COLOR_GREEN128);
	m_Brush[COLOR_IDX_WHITE].CreateSolidBrush (COLOR_WHITE);
	m_Brush[COLOR_IDX_DEEP_BLUE].CreateSolidBrush (COLOR_DEEP_BLUE);
	m_Brush[COLOR_IDX_LIGHT_BLUE].CreateSolidBrush(COLOR_LIGHT_BLUE);
}


void CPatternTest::Lf_sendPtnData()
{
	CString sdata=_T(""),microPtn=_T("");

	CString strPacket;
	strPacket = m_pApp->m_pCommand->Gf_makePGPatternString(lpModelInfo->m_sLbPtnName[m_nSelNum]);
	int nRedData, nGreenData, nBlueData;
	Lf_getPatternGrayLevel(strPacket, &nRedData, &nGreenData, &nBlueData);

	Lf_PtnTestEventView(strPacket);

	sdata.Format(_T("%d"), nRedData);
	GetDlgItem(IDC_STT_TP_COLOR_R_VAL)->SetWindowTextW(sdata);
	sdata.Format(_T("%d"), nGreenData);
	GetDlgItem(IDC_STT_TP_COLOR_G_VAL)->SetWindowTextW(sdata);
	sdata.Format(_T("%d"), nBlueData);
	GetDlgItem(IDC_STT_TP_COLOR_B_VAL)->SetWindowTextW(sdata);

	sdata.Format( _T("%s (%sHz)"), lpModelInfo->m_sLbPtnName[m_nSelNum].GetBuffer(0)
		, lpModelInfo->m_sLbPtnVsync[m_nSelNum].GetBuffer(0) );

	Lf_PtnTestEventView(sdata);
	m_pApp->m_pCommand->Gf_setPGInfoPatternName(lpModelInfo->m_sLbPtnName[m_nSelNum]);

	Lf_setPatternImageView(lpModelInfo->m_sLbPtnName[m_nSelNum]);
}

BOOL CPatternTest::Lf_sendBluData()
{
	if(lpSystemInfo->m_nLedBlPort == 0)
		return TRUE;
	int nBluDuty = (int)_ttoi(lpModelInfo->m_sLbPtnBlu[m_nSelNum]);
	if (m_nBluDutyOld == nBluDuty)
	{
		return TRUE;
	}
	m_nBluDutyOld = nBluDuty;
	CString strmsg;
	strmsg.Format(_T("BLU Duty : %d"), nBluDuty);
	Lf_PtnTestEventView(strmsg);
	if(m_pApp->m_pCommand->Gf_setBluDuty(nBluDuty) == FALSE)
	{
		m_pApp->Gf_ShowMessageBox(_T("BLU Communication Error"));//AfxMessageBox(_T("BLU Communication Error"));
	}

	return TRUE;
}

void CPatternTest::Lf_sendPatternBluData()
{
	Lf_sendPtnData();
	Lf_sendBluData();
	/*if (Lf_PatternVoltageSetting() == FALSE)
	{
		CDialog::OnCancel();
	}
	if (Lf_PatternCurrentCheck() == FALSE)
	{
		CDialog::OnCancel();
	}*/
}

void CPatternTest::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if(nIDEvent==1)
	{	
		KillTimer(1);
		if (Lf_updateMeasureInfo() == TRUE)
		{
			Lf_compareEEPRomData();

			// 아래는 Power On이후 패턴검사 진행 시 필요한 Timer이다.
			SetTimer(2, 1000, NULL);	// Power Measure
			SetTimer(99, 200, NULL);	// 마우스 고정
		}
	}
	else if(nIDEvent==2)
	{
		KillTimer(2);
		if (Lf_updateMeasureInfo() == TRUE)
		{
			SetTimer(2, 1000, NULL);
		}
		else
		{
			KillTimer(99);	// 마우스 고정
		}

#if (SUMMARY_LOG_VOLT_CURR==1)
		m_bPowerMeasureComplete[m_nSelNum] = TRUE;		// Power Measure가 동작했으면 Flag를 ON 한다.
#endif
	}
	else if(nIDEvent==3)
	{
		KillTimer(3);

		if (m_pApp->m_pDio7230->Gf_getDIOJudgeOK())
		{
			m_pApp->Gf_writeLogData(_T("<DIO>"), _T("PATTERN TEST - JUDGE OK ON, FAST JUDGE"));
			lpWorkInfo->m_nFastDioJudge = FAST_JUDGE_OK;
			CDialog::OnCancel();
		}
		else if (m_pApp->m_pDio7230->Gf_getDIOJudgeNG())
		{
			m_pApp->Gf_writeLogData(_T("<DIO>"), _T("PATTERN TEST - JUDGE NG ON, FAST JUDGE"));
			lpWorkInfo->m_nFastDioJudge = FAST_JUDGE_NG;
			CDialog::OnCancel();
		}

		SetTimer(3, 100, NULL); 
	}
	else if (nIDEvent == 5)
	{
		KillTimer(5);
		Lf_setPatternImageView(lpModelInfo->m_sLbPtnName[m_nSelNum]);
	}
	else if (nIDEvent == 99)
	{
		KillTimer(99);
		CRect rcFrame;
		GetDlgItem(IDC_STT_PTN_IMAGE_VIEW_SIZE)->GetWindowRect(rcFrame);
		::SetCursorPos(rcFrame.left + rcFrame.Width() / 2, rcFrame.top + rcFrame.Height() / 2);

		SetTimer(99, 200, NULL);
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

BOOL CPatternTest::Lf_updateMeasureInfo()
{
	CString sdata=_T("");
	memset(m_pApp->m_nLcmPInfo, 0x00, sizeof(m_pApp->m_nLcmPInfo));
	if (m_pApp->m_pCommand->Gf_getPowerMeasure() == TRUE)
	{
		if (m_pApp->m_nLcmPInfo[PINFO_ERR_RESULT] == OVER_CURRENT)
		{
			if (m_pApp->m_nLcmPInfo[PINFO_ERR_NAME] == PINFO_VCC)
			{
				sdata.Format(_T("VCC Over Voltage (High Set: %.2fV, Measure: %.2fV)"), (float)lpModelInfo->m_fLimitVccMax, (float)(m_pApp->m_nLcmPInfo[PINFO_ERR_VALUE] / 1000.f));
				m_pApp->Gf_ShowMessageBox(sdata);//AfxMessageBox(sdata);
			}
			else if (m_pApp->m_nLcmPInfo[PINFO_ERR_NAME] == PINFO_VDD)
			{
				sdata.Format(_T("VDD Over Voltage (High Set: %.2fV, Measure: %.2fV)"), (float)lpModelInfo->m_fLimitVddMax, (float)(m_pApp->m_nLcmPInfo[PINFO_ERR_VALUE] / 1000.f));
				m_pApp->Gf_ShowMessageBox(sdata);//AfxMessageBox(sdata);
			}
			else if (m_pApp->m_nLcmPInfo[PINFO_ERR_NAME] == PINFO_VBL)
			{
				sdata.Format(_T("VBL Over Voltage (High Set: %.2fV, Measure: %.2fV)"), (float)lpModelInfo->m_fLimitVblMax, (float)(m_pApp->m_nLcmPInfo[PINFO_ERR_VALUE] / 1000.f));
				m_pApp->Gf_ShowMessageBox(sdata);//AfxMessageBox(sdata);
			}
			else if (m_pApp->m_nLcmPInfo[PINFO_ERR_NAME] == PINFO_ICC)
			{
				sdata.Format(_T("ICC Over Current (High Set: %.2fA, Measure: %.2fA)"), (float)lpModelInfo->m_fLimitIccMax, m_pApp->m_nLcmPInfo[PINFO_ERR_VALUE] / 1000.f);
				m_pApp->Gf_ShowMessageBox(sdata);//AfxMessageBox(sdata);
			}
			else if (m_pApp->m_nLcmPInfo[PINFO_ERR_NAME] == PINFO_IDD)
			{
				sdata.Format(_T("IDD Over Current (High Set: %.2fA, Measure: %.2fA)"), (float)lpModelInfo->m_fLimitIddMax, m_pApp->m_nLcmPInfo[PINFO_ERR_VALUE] / 1000.f);
				m_pApp->Gf_ShowMessageBox(sdata);//AfxMessageBox(sdata);
			}
			else if (m_pApp->m_nLcmPInfo[PINFO_ERR_NAME] == PINFO_IBL)
			{
				sdata.Format(_T("IBL Over Current (High Set: %.2fA, Measure: %.2fA)"), (float)lpModelInfo->m_fLimitIblMax, m_pApp->m_nLcmPInfo[PINFO_ERR_VALUE] / 1000.f);
				m_pApp->Gf_ShowMessageBox(sdata);//AfxMessageBox(sdata);
			}
			if (m_pApp->m_nLcmPInfo[PINFO_ERR_NAME] == PINFO_VGH)
			{
				sdata.Format(_T("VGH Over Voltage (High Set: %.2fV, Measure: %.2fV)"), (float)lpModelInfo->m_fLimitVghMax, (float)(m_pApp->m_nLcmPInfo[PINFO_ERR_VALUE] / 1000.f));
				m_pApp->Gf_ShowMessageBox(sdata);//AfxMessageBox(sdata);
			}
			else if (m_pApp->m_nLcmPInfo[PINFO_ERR_NAME] == PINFO_VGL)
			{
				sdata.Format(_T("VGL Over Voltage (High Set: %.2fV, Measure: %.2fV)"), (float)lpModelInfo->m_fLimitVddMax, (float)(m_pApp->m_nLcmPInfo[PINFO_ERR_VALUE] / 1000.f));
				m_pApp->Gf_ShowMessageBox(sdata);//AfxMessageBox(sdata);
			}
			else if (m_pApp->m_nLcmPInfo[PINFO_ERR_NAME] == PINFO_IGH)
			{
				sdata.Format(_T("IGH Over Current (High Set: %.2fA, Measure: %.2fA)"), (float)lpModelInfo->m_fLimitIghMax, m_pApp->m_nLcmPInfo[PINFO_ERR_VALUE] / 1000.f);
				m_pApp->Gf_ShowMessageBox(sdata);//AfxMessageBox(sdata);
			}
			else if (m_pApp->m_nLcmPInfo[PINFO_ERR_NAME] == PINFO_IGL)
			{
				sdata.Format(_T("IGL Over Current (High Set: %.2fA, Measure: %.2fA)"), (float)lpModelInfo->m_fLimitIglMax, m_pApp->m_nLcmPInfo[PINFO_ERR_VALUE] / 1000.f);
				m_pApp->Gf_ShowMessageBox(sdata);//AfxMessageBox(sdata);
			}

			CDialog::OnCancel();
			return FALSE;
		}
		else if (m_pApp->m_nLcmPInfo[PINFO_ERR_RESULT] == LOW_CURRENT)
		{
			if (m_pApp->m_nLcmPInfo[PINFO_ERR_NAME] == PINFO_VCC)
			{
				sdata.Format(_T("VCC Low Voltage (Low Set: %.2fV, Measure: %.2fV)"), (float)lpModelInfo->m_fLimitVccMin, (float)(m_pApp->m_nLcmPInfo[PINFO_ERR_VALUE] / 1000.f));
				m_pApp->Gf_ShowMessageBox(sdata);//AfxMessageBox(sdata);
			}
			else if (m_pApp->m_nLcmPInfo[PINFO_ERR_NAME] == PINFO_VDD)
			{
				sdata.Format(_T("VDD Low Voltage (Low Set: %.2fV, Measure: %.2fV)"), (float)lpModelInfo->m_fLimitVddMin, (float)(m_pApp->m_nLcmPInfo[PINFO_ERR_VALUE] / 1000.f));
				m_pApp->Gf_ShowMessageBox(sdata);//AfxMessageBox(sdata);
			}
			else if (m_pApp->m_nLcmPInfo[PINFO_ERR_NAME] == PINFO_VBL)
			{
				sdata.Format(_T("VBL Low Voltage (Low Set: %.2fV, Measure: %.2fV)"), (float)lpModelInfo->m_fLimitVblMin, (float)(m_pApp->m_nLcmPInfo[PINFO_ERR_VALUE] / 1000.f));
				m_pApp->Gf_ShowMessageBox(sdata);//AfxMessageBox(sdata);
			}
			else if (m_pApp->m_nLcmPInfo[PINFO_ERR_NAME] == PINFO_ICC)
			{
				sdata.Format(_T("ICC Low Current (Low Set: %.2fA, Measure: %.2fA)"), (float)lpModelInfo->m_fLimitIccMin, m_pApp->m_nLcmPInfo[PINFO_ERR_VALUE] / 1000.f);
				m_pApp->Gf_ShowMessageBox(sdata);//AfxMessageBox(sdata);
			}
			else if (m_pApp->m_nLcmPInfo[PINFO_ERR_NAME] == PINFO_IDD)
			{
				sdata.Format(_T("IDD Low Current (Low Set: %.2fA, Measure: %.2fA)"), (float)lpModelInfo->m_fLimitIddMin, m_pApp->m_nLcmPInfo[PINFO_ERR_VALUE] / 1000.f);
				m_pApp->Gf_ShowMessageBox(sdata);//AfxMessageBox(sdata);
			}
			else if (m_pApp->m_nLcmPInfo[PINFO_ERR_NAME] == PINFO_IBL)
			{
				sdata.Format(_T("IBL Low Current (Low Set: %.2fA, Measure: %.2fA)"), (float)lpModelInfo->m_fLimitIblMin, m_pApp->m_nLcmPInfo[PINFO_ERR_VALUE] / 1000.f);
				m_pApp->Gf_ShowMessageBox(sdata);//AfxMessageBox(sdata);
			}
			if (m_pApp->m_nLcmPInfo[PINFO_ERR_NAME] == PINFO_VGH)
			{
				sdata.Format(_T("VGH Low Voltage (Low Set: %.2fV, Measure: %.2fV)"), (float)lpModelInfo->m_fLimitVghMin, (float)(m_pApp->m_nLcmPInfo[PINFO_ERR_VALUE] / 1000.f));
				m_pApp->Gf_ShowMessageBox(sdata);//AfxMessageBox(sdata);
			}
			else if (m_pApp->m_nLcmPInfo[PINFO_ERR_NAME] == PINFO_VGL)
			{
				sdata.Format(_T("VGL Low Voltage (Low Set: %.2fV, Measure: %.2fV)"), (float)lpModelInfo->m_fLimitVddMin, (float)(m_pApp->m_nLcmPInfo[PINFO_ERR_VALUE] / 1000.f));
				m_pApp->Gf_ShowMessageBox(sdata);//AfxMessageBox(sdata);
			}
			else if (m_pApp->m_nLcmPInfo[PINFO_ERR_NAME] == PINFO_IGH)
			{
				sdata.Format(_T("IGH Low Current (Low Set: %.2fA, Measure: %.2fA)"), (float)lpModelInfo->m_fLimitIghMin, m_pApp->m_nLcmPInfo[PINFO_ERR_VALUE] / 1000.f);
				m_pApp->Gf_ShowMessageBox(sdata);//AfxMessageBox(sdata);
			}
			else if (m_pApp->m_nLcmPInfo[PINFO_ERR_NAME] == PINFO_IGL)
			{
				sdata.Format(_T("IGL Low Current (Low Set: %.2fA, Measure: %.2fA)"), (float)lpModelInfo->m_fLimitIglMin, m_pApp->m_nLcmPInfo[PINFO_ERR_VALUE] / 1000.f);
				m_pApp->Gf_ShowMessageBox(sdata);//AfxMessageBox(sdata);
			}
			CDialog::OnCancel();
			return FALSE;
		}
		sdata.Format(_T("%.3f"), (float)(m_pApp->m_nLcmPInfo[PINFO_VCC] / 1000.f));
		GetDlgItem(IDC_STT_VCC_MEASURE)->SetWindowText(sdata);
		sdata.Format(_T("%.3f"), (float)(m_pApp->m_nLcmPInfo[PINFO_VDD] / 1000.f));
		GetDlgItem(IDC_STT_VDD_MEASURE)->SetWindowText(sdata);
		sdata.Format(_T("%.3f"), (float)(m_pApp->m_nLcmPInfo[PINFO_VBL] / 1000.f));
		GetDlgItem(IDC_STT_VBL_MEASURE)->SetWindowText(sdata);
		sdata.Format(_T("%.3f"), (float)(m_pApp->m_nLcmPInfo[PINFO_VGH] / 1000.f));
		GetDlgItem(IDC_STT_VGH_MEASURE)->SetWindowText(sdata);
		sdata.Format(_T("%.3f"), (float)(m_pApp->m_nLcmPInfo[PINFO_VGL] / 1000.f));
		GetDlgItem(IDC_STT_VGL_MEASURE)->SetWindowText(sdata);

		sdata.Format(_T("%.3f"), (float)(m_pApp->m_nLcmPInfo[PINFO_ICC] / 1000.f));
		GetDlgItem(IDC_STT_ICC_MEASURE)->SetWindowText(sdata);
		sdata.Format(_T("%.3f"), (float)(m_pApp->m_nLcmPInfo[PINFO_IDD] / 1000.f));
		GetDlgItem(IDC_STT_IDD_MEASURE)->SetWindowText(sdata);
		sdata.Format(_T("%.3f"), (float)(m_pApp->m_nLcmPInfo[PINFO_IBL] / 1000.f));
		GetDlgItem(IDC_STT_IBL_MEASURE)->SetWindowText(sdata);
		sdata.Format(_T("%.3f"), (float)(m_pApp->m_nLcmPInfo[PINFO_IGH] / 1000.f));
		GetDlgItem(IDC_STT_IGH_MEASURE)->SetWindowText(sdata);
		sdata.Format(_T("%.3f"), (float)(m_pApp->m_nLcmPInfo[PINFO_IGL] / 1000.f));
		GetDlgItem(IDC_STT_IGL_MEASURE)->SetWindowText(sdata);


#if (SUMMARY_LOG_VOLT_CURR==1)
		lpWorkInfo->m_nMeasPowerVCC[m_nSelNum] = m_pApp->m_nLcmPInfo[PINFO_VCC];
		lpWorkInfo->m_nMeasPowerVDD[m_nSelNum] = m_pApp->m_nLcmPInfo[PINFO_VDD];
		lpWorkInfo->m_nMeasPowerICC[m_nSelNum] = m_pApp->m_nLcmPInfo[PINFO_ICC];
		lpWorkInfo->m_nMeasPowerIDD[m_nSelNum] = m_pApp->m_nLcmPInfo[PINFO_IDD];
#endif
	}
	return TRUE;
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
			CDialog::OnOK();
			return;
		}
		m_nSelNum++;

		break;
	case VK_BACK:
		if(m_nSelNum <= 0)  
		{ 
			return;
		}		
		m_nSelNum--;
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
	m_LCctrlPtnTestView.SetSelectionMark(m_nSelNum);
	m_LCctrlPtnTestView.SetItemState(m_nSelNum, LVIS_SELECTED | LVIS_FOCUSED, LVNI_SELECTED | LVNI_FOCUSED);
	m_LCctrlPtnTestView.SetFocus();

	RemoveMessageFromQueue();
	m_pApp->Gf_setPatStartCheckTime(m_nSelNum);
	m_pApp->Gf_setStartPtnLockTime(m_nSelNum);
	Lf_sendPatternBluData();

	SetTimer(2, 200, NULL);	// Power Measure
}


void CPatternTest::Lf_insertListColum()
{
	CRect rect,rect2;
	DWORD dwStype;

	m_LCctrlPtnTestView.GetClientRect(&rect);
	m_LCctrlPtnTestView.InsertColumn( 0, _T("No"), LVCFMT_LEFT, -1, -1);
	m_LCctrlPtnTestView.InsertColumn( 1, _T("Pattern Name"), LVCFMT_LEFT, -1, -1 );
	m_LCctrlPtnTestView.InsertColumn( 2, _T("VCC"), LVCFMT_LEFT, -1, -1 );
	m_LCctrlPtnTestView.InsertColumn( 3, _T("VDD"), LVCFMT_LEFT, -1, -1 );
	m_LCctrlPtnTestView.InsertColumn( 4, _T("T(s)"), LVCFMT_LEFT, -1, -1 );
	m_LCctrlPtnTestView.InsertColumn( 5, _T("VSync"), LVCFMT_LEFT, -1, -1 );
	m_LCctrlPtnTestView.InsertColumn(6, _T("ICC L"), LVCFMT_LEFT, -1, -1);
	m_LCctrlPtnTestView.InsertColumn(7, _T("ICC H"), LVCFMT_LEFT, -1, -1);
	m_LCctrlPtnTestView.InsertColumn(8, _T("IDD L"), LVCFMT_LEFT, -1, -1);
	m_LCctrlPtnTestView.InsertColumn(9, _T("IDD H"), LVCFMT_LEFT, -1, -1);
	m_LCctrlPtnTestView.InsertColumn(10, _T("BLU"), LVCFMT_LEFT, -1, -1);

	m_LCctrlPtnTestView.SetColumnWidth( 0, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER ); // NO
	GetDlgItem(IDC_STT_NUM)->GetWindowRect(&rect2);
	m_LCctrlPtnTestView.SetColumnWidth( 0, rect2.Width());

	m_LCctrlPtnTestView.SetColumnWidth( 1, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER ); // Pattern
	GetDlgItem(IDC_STT_PTN_NAME)->GetWindowRect(&rect2);
	m_LCctrlPtnTestView.SetColumnWidth( 1, rect2.Width());

	m_LCctrlPtnTestView.SetColumnWidth( 2, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER ); // VCC
	GetDlgItem(IDC_STT_VCC)->GetWindowRect(&rect2);
	m_LCctrlPtnTestView.SetColumnWidth( 2, rect2.Width());

	m_LCctrlPtnTestView.SetColumnWidth( 3, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER ); // VDD
	GetDlgItem(IDC_STT_VDD)->GetWindowRect(&rect2);
	m_LCctrlPtnTestView.SetColumnWidth( 3, rect2.Width());

	m_LCctrlPtnTestView.SetColumnWidth( 4, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER ); // T(ms)
	GetDlgItem(IDC_STT_TMS)->GetWindowRect(&rect2);
	m_LCctrlPtnTestView.SetColumnWidth( 4, rect2.Width());

	m_LCctrlPtnTestView.SetColumnWidth( 5, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER ); // VSYNC
	GetDlgItem(IDC_STT_VSYNC)->GetWindowRect(&rect2);
	m_LCctrlPtnTestView.SetColumnWidth( 5, rect2.Width());

	m_LCctrlPtnTestView.SetColumnWidth(6, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER); // ICC LOW
	GetDlgItem(IDC_STT_PTN_ICC_LOW)->GetWindowRect(&rect2);
	m_LCctrlPtnTestView.SetColumnWidth(6, rect2.Width());

	m_LCctrlPtnTestView.SetColumnWidth(7, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER); // ICC HIGH
	GetDlgItem(IDC_STT_PTN_ICC_HIGH)->GetWindowRect(&rect2);
	m_LCctrlPtnTestView.SetColumnWidth(7, rect2.Width());

	m_LCctrlPtnTestView.SetColumnWidth(8, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER); // IDD LOW
	GetDlgItem(IDC_STT_PTN_IDD_LOW)->GetWindowRect(&rect2);
	m_LCctrlPtnTestView.SetColumnWidth(8, rect2.Width());

	m_LCctrlPtnTestView.SetColumnWidth(9, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER); // IDD HIGH
	GetDlgItem(IDC_STT_PTN_IDD_HIGH)->GetWindowRect(&rect2);
	m_LCctrlPtnTestView.SetColumnWidth(9, rect2.Width());

	m_LCctrlPtnTestView.SetColumnWidth(10, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER); // BLU
	GetDlgItem(IDC_STT_PTN_BLU)->GetWindowRect(&rect2);
	m_LCctrlPtnTestView.SetColumnWidth(10, rect2.Width());

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
		strNum.Format(_T("%d"), loop+1);
		m_LCctrlPtnTestView.InsertItem(loop, strNum);
		m_LCctrlPtnTestView.SetItemText(loop, 1,lpModelInfo->m_sLbPtnName[loop]);
		m_LCctrlPtnTestView.SetItemText(loop, 2, lpModelInfo->m_sLbPtnVcc[loop]);
		m_LCctrlPtnTestView.SetItemText(loop, 3, lpModelInfo->m_sLbPtnVdd[loop]);
		m_LCctrlPtnTestView.SetItemText(loop, 4, lpModelInfo->m_sLbPtnTms[loop]);
		m_LCctrlPtnTestView.SetItemText(loop, 5, lpModelInfo->m_sLbPtnVsync[loop]);
		m_LCctrlPtnTestView.SetItemText(loop, 6, lpModelInfo->m_sLbPtnIccLow[loop]);
		m_LCctrlPtnTestView.SetItemText(loop, 7, lpModelInfo->m_sLbPtnIccHigh[loop]);
		m_LCctrlPtnTestView.SetItemText(loop, 8, lpModelInfo->m_sLbPtnIddLow[loop]);
		m_LCctrlPtnTestView.SetItemText(loop, 9, lpModelInfo->m_sLbPtnIddHigh[loop]);
		m_LCctrlPtnTestView.SetItemText(loop, 10, lpModelInfo->m_sLbPtnBlu[loop]);
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

	m_bRtnCode = m_pApp->m_pCommand->Gf_getEEPRomReadData();

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
					GetDlgItem(IDC_STT_TP_EDID_RESULT)->SetWindowTextW(_T("NG"));
					break;
				}
			}

			for(i=0; i<size; i++)
			{
				sdata1.Format(_T("%02X "), (BYTE)m_pApp->m_nEEPRomFileData[i]);
				sdata2.Append(sdata1);
			}
			m_pApp->Gf_writeLogData(_T("<EDID>"),_T("File Data"));
			m_pApp->Gf_writeLogData(_T("<FILE>"), sdata2.GetBuffer(0));

			sdata1.Empty();
			sdata2.Empty();
			for(i=0; i<size; i++)
			{
				sdata1.Format(_T("%02X "), (BYTE)m_pApp->m_nEEPRomReadData[i]);
				sdata2.Append(sdata1);
			}
			m_pApp->Gf_writeLogData(_T("<EDID>"), _T("Read Data"));
			m_pApp->Gf_writeLogData(_T("<I2C>"), sdata2.GetBuffer(0));

			if(bCompResult == FALSE)
			{
	#ifdef	USE_GMES
				lpWorkInfo->Edid = 'F';
	#endif
				lpWorkInfo->m_bIsEdidFail = true;
				m_pApp->Gf_ShowMessageBox(_T("EDID Read Compare Fail!!!"));//AfxMessageBox(_T("EDID Read Compare Fail!!!"));
				m_pApp->m_pCommand->Gf_setPowerSeqOnOff(POWER_OFF);	
				CDialog::OnCancel();
				return;
			}
			else
			{
	#ifdef	USE_GMES
				lpWorkInfo->Edid = 'P';
	#endif
				Lf_PtnTestEventView(_T("EDID Compare OK"));
				GetDlgItem(IDC_STT_TP_EDID_RESULT)->SetWindowTextW(_T("OK"));
			}
		} 
		else
		{
			GetDlgItem(IDC_STT_TP_EDID_RESULT)->SetWindowTextW(_T("NG"));
			lpWorkInfo->m_bIsEdidFail = true;
			m_pApp->Gf_ShowMessageBox(_T("EDID Read Communication Error!!!"));//AfxMessageBox(_T("EDID Read Communication Error!!!"));
			m_pApp->m_pCommand->Gf_setPowerSeqOnOff(POWER_OFF);
		}	
	}
}

void CPatternTest::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CString sdata=_T("");

#if (SUMMARY_LOG_VOLT_CURR==1)
	if (m_bPowerMeasureComplete[m_nSelNum] == FALSE)
		return;
#endif

	m_pApp->Gf_setPatEndCheckTime(m_nSelNum);
	m_pApp->m_nPatTime[m_nSelNum] = (m_pApp->m_nEndCheckTime[m_nSelNum] - m_pApp->m_nStartCheckTime[m_nSelNum]);

	int SetTime;
	m_pApp->Gf_setEndPtnLockTime(m_nSelNum);
	SetTime = _ttoi(lpModelInfo->m_sLbPtnTms[m_nSelNum])*1000;

	if((m_pApp->m_nPtnLockTime[m_nSelNum] < SetTime) && (m_pApp->m_nPatLock[m_nSelNum]==FALSE))	
		return;	
	else
		m_pApp->m_nPatLock[m_nSelNum] = TRUE;

	Lf_PtnTestEventView(_T("Mouse LEFT - NEXT"));
	// on 일때 reset 기능
	if(m_nSelNum <= lpModelInfo->m_nLbCnt-1)
	{
		if(lpModelInfo->m_nLbCnt-1 <= m_nSelNum)  
		{ 
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

	SetTimer(2, 200, NULL);	// Power Measure

	CDialog::OnLButtonDown(nFlags, point);
}

void CPatternTest::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if(m_nSelNum <= 0)  
	{ 
		return;
	}

#if (SUMMARY_LOG_VOLT_CURR==1)
	if (m_bPowerMeasureComplete[m_nSelNum] == FALSE)
		return;
#endif

	m_LCctrlPtnTestView.SetSelectionMark(--m_nSelNum); 
	m_LCctrlPtnTestView.SetItemState(m_nSelNum, LVIS_SELECTED | LVIS_FOCUSED, LVNI_SELECTED | LVNI_FOCUSED);
	m_LCctrlPtnTestView.SetFocus();

	RemoveMessageFromQueue();
	m_pApp->Gf_setStartPtnLockTime(m_nSelNum);
	Lf_sendPatternBluData();

	SetTimer(2, 200, NULL);	// Power Measure

	CDialog::OnRButtonDown(nFlags, point);
}
void CPatternTest::Lf_PtnTestEventView(CString Event)
{
	CTime time = CTime::GetCurrentTime();
	SYSTEMTIME sysTime;
	::GetSystemTime(&sysTime);
	CString sMsg;
	sMsg.Format(_T("[%02d:%02d:%02d %03d] %s"), time.GetHour(), time.GetMinute(), time.GetSecond(), sysTime.wMilliseconds, Event);

	m_listPtnTestEvent.SetCurSel(m_listPtnTestEvent.AddString(sMsg));

	m_pApp->Gf_writeLogData(_T("<TEST>"), Event);
}
void CPatternTest::Lf_setPatternGrayLevel(int wParam)
{
	CString strPattern;
	CString strPacket;
	int colorConf = 0;
	int adjustValue = 0;
	int R_Val = 0, G_Val = 0, B_Val = 0;

	// 1. Pattern Name과 Index를 가져온다.

	strPattern = lpModelInfo->m_sLbPtnName[m_nSelNum];

	strPattern.MakeUpper();

	// 2. Pattern 이름을 기준으로 가변할 Color 정보를 가져온다.
	// Pattern String을 만든다.
	int nPtnGrayLevel, nRedData, nGreenData, nBlueData;
	CString sdata;
	GetDlgItem(IDC_STT_TP_COLOR_R_VAL)->GetWindowTextW(sdata);
	nRedData = (int)_ttoi(sdata);
	GetDlgItem(IDC_STT_TP_COLOR_G_VAL)->GetWindowTextW(sdata);
	nGreenData = (int)_ttoi(sdata);
	GetDlgItem(IDC_STT_TP_COLOR_B_VAL)->GetWindowTextW(sdata);
	nBlueData = (int)_ttoi(sdata);

	//    하위 3bit만 사용하며 R:2 G:1 B:0  bit를 할당한다. 
	if (strPattern.Find(_T("GRAY")) != -1)			{ colorConf = 0x07;	nPtnGrayLevel = nRedData; }
	else if (strPattern.Find(_T("WHITE")) != -1)	{ colorConf = 0x07;	nPtnGrayLevel = nRedData; }
	else if (strPattern.Find(_T("BLACK")) != -1)	{ colorConf = 0x07;	nPtnGrayLevel = nRedData; }
	else if (strPattern.Find(_T("RED")) != -1)		{ colorConf = 0x04;	nPtnGrayLevel = nRedData; }
	else if (strPattern.Find(_T("GREEN")) != -1)	{ colorConf = 0x02;	nPtnGrayLevel = nGreenData; }
	else if (strPattern.Find(_T("BLUE")) != -1)		{ colorConf = 0x01;	nPtnGrayLevel = nBlueData; }
	else if (strPattern.Find(_T("CYAN")) != -1)		{ colorConf = 0x03;	nPtnGrayLevel = nBlueData; }
	else if (strPattern.Find(_T("MAGENTA")) != -1)	{ colorConf = 0x05;	nPtnGrayLevel = nRedData; }
	else if (strPattern.Find(_T("YELLOW")) != -1)	{ colorConf = 0x06;	nPtnGrayLevel = nRedData; }
	else { return; }

	// 3. Gray 가변 Step 정보를 가져온다.
	if (wParam == VK_UP)	adjustValue = 5;
	if (wParam == VK_DOWN)	adjustValue = -5;
	if (wParam == VK_LEFT)	adjustValue = -2;
	if (wParam == VK_RIGHT)	adjustValue = 2;

	// 4. Gray Level 값을 변경한다.
	if (colorConf & 0x04)		R_Val = nPtnGrayLevel + adjustValue;
	if (colorConf & 0x02)		G_Val = nPtnGrayLevel + adjustValue;
	if (colorConf & 0x01)		B_Val = nPtnGrayLevel + adjustValue;

	// 5. Gray Level의 Limit를 계산한다.
	int upLimit = 0;
	if (lpModelInfo->m_nSignalBit == SIG_6BIT)	upLimit = 63;	// 6bit
	if (lpModelInfo->m_nSignalBit == SIG_8BIT)	upLimit = 255;	// 8bit
	if (lpModelInfo->m_nSignalBit == SIG_10BIT)	upLimit = 1023;	// 10bit
	if (lpModelInfo->m_nSignalBit == SIG_12BIT)	upLimit = 4095;	// 10bit

	if (R_Val < 0)			R_Val = 0;
	if (R_Val > upLimit)	R_Val = upLimit;
	if (G_Val < 0)			G_Val = 0;
	if (G_Val > upLimit)	G_Val = upLimit;
	if (B_Val < 0)			B_Val = 0;
	if (B_Val > upLimit)	B_Val = upLimit;

	// 6. 현재의 Gray Level 값을 Update 한다.
	/*if (colorConf & 0x04)		nPtnGrayLevel = R_Val;
	if (colorConf & 0x02)		nPtnGrayLevel = G_Val;
	if (colorConf & 0x01)		nPtnGrayLevel = B_Val;*/

	// 6. PG에 전달할 String을 만든다.
	int nBitShift;
	if (lpModelInfo->m_nSignalBit == SIG_6BIT) // 6bit
	{
		nBitShift = 10;
		R_Val = (R_Val << nBitShift) | 0x03FF;
		G_Val = (G_Val << nBitShift) | 0x03FF;
		B_Val = (B_Val << nBitShift) | 0x03FF;
	}
	if (lpModelInfo->m_nSignalBit == SIG_8BIT) // 8bit
	{
		nBitShift = 8;
		R_Val = (R_Val << nBitShift) | 0xFF;
		G_Val = (G_Val << nBitShift) | 0xFF;
		B_Val = (B_Val << nBitShift) | 0xFF;
	}
	if (lpModelInfo->m_nSignalBit == SIG_10BIT) // 10bit
	{
		nBitShift = 6;
		R_Val = (R_Val << nBitShift) | 0x3F;
		G_Val = (G_Val << nBitShift) | 0x3F;
		B_Val = (B_Val << nBitShift) | 0x3F;
	}
	if (lpModelInfo->m_nSignalBit == SIG_12BIT) // 12bit
	{
		nBitShift = 4;
		R_Val = (R_Val << nBitShift) | 0x0F;
		G_Val = (G_Val << nBitShift) | 0x0F;
		B_Val = (B_Val << nBitShift) | 0x0F;
	}

	CString sLog;
	sLog.Format(_T("Gray Level Set (R:%d) (G:%d) (b:%d)"), (R_Val >> nBitShift), (G_Val >> nBitShift), (B_Val >> nBitShift));
	m_pApp->Gf_writeLogData(_T("<TEST>"), sLog);


	strPacket.Format(_T("CFG%04X%04X%04X"), R_Val, G_Val, B_Val);

	BOOL ret;
	ret = m_pApp->m_pCommand->Gf_setPGInfoPatternString(strPacket, FALSE);
	// 7. Pattern Data를 PG에 전송한다.
	if (ret == TRUE)
	{
		sdata.Format(_T("%d"), (R_Val >> nBitShift));
		GetDlgItem(IDC_STT_TP_COLOR_R_VAL)->SetWindowText(sdata);
		sdata.Format(_T("%d"), (G_Val >> nBitShift));
		GetDlgItem(IDC_STT_TP_COLOR_G_VAL)->SetWindowText(sdata);
		sdata.Format(_T("%d"), (B_Val >> nBitShift));
		GetDlgItem(IDC_STT_TP_COLOR_B_VAL)->SetWindowText(sdata);
	}
	
}
void CPatternTest::Lf_getPatternGrayLevel(CString strPattern, int* r_level, int* g_level, int* b_level)
{
	int p_st;

	p_st = strPattern.Find(_T("CFG"));
	int gray = 0;
	if (lpModelInfo->m_nSignalBit == SIG_6BIT)	gray = 63;
	if (lpModelInfo->m_nSignalBit == SIG_8BIT)	gray = 255;
	if (lpModelInfo->m_nSignalBit == SIG_10BIT)	gray = 1023;
	if (lpModelInfo->m_nSignalBit == SIG_12BIT)	gray = 4095;

	if (p_st == -1)
	{
		*r_level = gray;
		*g_level = gray;
		*b_level = gray;
	}
	else
	{
		*r_level = _tcstol(strPattern.Mid(p_st + 3, 4), 0, 16);
		*g_level = _tcstol(strPattern.Mid(p_st + 7, 4), 0, 16);
		*b_level = _tcstol(strPattern.Mid(p_st + 11, 4), 0, 16);

		if (lpModelInfo->m_nSignalBit == SIG_6BIT)
		{
			*r_level = *r_level >> 10;
			*g_level = *g_level >> 10;
			*b_level = *b_level >> 10;
		}
		if (lpModelInfo->m_nSignalBit == SIG_8BIT)
		{
			*r_level = *r_level >> 8;
			*g_level = *g_level >> 8;
			*b_level = *b_level >> 8;
		}
		if (lpModelInfo->m_nSignalBit == SIG_10BIT)
		{
			*r_level = *r_level >> 6;
			*g_level = *g_level >> 6;
			*b_level = *b_level >> 6;
		}
		if (lpModelInfo->m_nSignalBit == SIG_12BIT)
		{
			*r_level = *r_level >> 4;
			*g_level = *g_level >> 4;
			*b_level = *b_level >> 4;
		}
		
		if (*r_level > gray)		*r_level = gray;
		if (*g_level > gray)		*g_level = gray;
		if (*b_level > gray)		*b_level = gray;
	}
}
BOOL CPatternTest::Lf_PatternLockTimeCheck()
{
	m_pApp->Gf_setPatEndCheckTime(m_nSelNum);
 	m_pApp->m_nPatTime[m_nSelNum] = (m_pApp->m_nEndCheckTime[m_nSelNum] - m_pApp->m_nStartCheckTime[m_nSelNum]);

	int setTime;
	m_pApp->Gf_setEndPtnLockTime(m_nSelNum);
	setTime = _ttoi(lpModelInfo->m_sLbPtnTms[m_nSelNum]) * 1000;

	if ((m_pApp->m_nPtnLockTime[m_nSelNum] < setTime) && (m_pApp->m_nPatLock[m_nSelNum] == FALSE))
		return FALSE;
	else
		m_pApp->m_nPatLock[m_nSelNum] = TRUE;

	return TRUE;
}
BOOL CPatternTest::Lf_PatternVoltageSetting()
{
	float fVcc, fVdd;
	fVcc = (float)_ttof(lpModelInfo->m_sLbPtnVcc[m_nSelNum]);
	fVdd = (float)_ttof(lpModelInfo->m_sLbPtnVdd[m_nSelNum]);
	if ((m_fPatternVccOld != fVcc) || (m_fPatternVddOld != fVdd))
	{
		m_fPatternVccOld = fVcc;
		m_fPatternVddOld = fVdd;

		char szPacket[128];
		int length;
		sprintf_s(szPacket, "%05d%05d%05d%05d%05d", (int)(fVcc * 1000 + 0.5), (int)(fVdd * 1000 + 0.5), (int)(lpModelInfo->m_fVoltVbl * 1000 + 0.5), (int)(lpModelInfo->m_fVoltVgh * 1000 + 0.5), (int)(lpModelInfo->m_fVoltVgl * 1000 + 0.5));
		length = (int)strlen(szPacket);
		if (m_pApp->udp_sendPacket(UDP_MAIN_IP, TARGET_CTRL, CMD_CTRL_POWER_VOLTAGE_SET, length, szPacket) == FALSE)
		{
			m_pApp->Gf_ShowMessageBox(_T("Pattern Voltage Setting Fail"));
			return FALSE;
		}
	}
	return TRUE;
}
BOOL CPatternTest::Lf_PatternCurrentCheck()
{
	CString strmsg;
	int nIccLow, nIccHigh, nIddLow, nIddHigh;
	nIccLow = (int)_ttoi(lpModelInfo->m_sLbPtnIccLow[m_nSelNum]);
	nIccHigh = (int)_ttoi(lpModelInfo->m_sLbPtnIccHigh[m_nSelNum]);
	nIddLow = (int)_ttoi(lpModelInfo->m_sLbPtnIddLow[m_nSelNum]);
	nIddHigh = (int)_ttoi(lpModelInfo->m_sLbPtnIddHigh[m_nSelNum]);

	if (nIccLow > 0 || nIccHigh > 0 || nIddLow > 0 || nIddHigh > 0)
	{
		if (m_nSelNum == 0)
		{
			Lf_updateMeasureInfo();
		}
		delayMS(2000);
	}
	if (nIccLow > 0)
	{
		if (nIccLow < m_pApp->m_nLcmPInfo[PINFO_ICC])
		{
			m_pApp->m_pCommand->Gf_setPowerSeqOnOff(POWER_OFF);
			strmsg.Format(_T("Pattern ICC LOW Limit NG. (Setting:%dmA Measure:%dmA)"), nIccLow, m_pApp->m_nLcmPInfo[PINFO_ICC]);
			m_pApp->Gf_ShowMessageBox(strmsg);
			return FALSE;
		}
	}
	if (nIccHigh > 0)
	{
		if (nIccHigh < m_pApp->m_nLcmPInfo[PINFO_ICC])
		{
			m_pApp->m_pCommand->Gf_setPowerSeqOnOff(POWER_OFF);
			strmsg.Format(_T("Pattern ICC HIGH Limit NG. (Setting:%dmA Measure:%dmA)"), nIccHigh, m_pApp->m_nLcmPInfo[PINFO_ICC]);
			m_pApp->Gf_ShowMessageBox(strmsg);
			return FALSE;
		}
	}
	if (nIddLow > 0)
	{
		if (nIddLow < m_pApp->m_nLcmPInfo[PINFO_IDD])
		{
			m_pApp->m_pCommand->Gf_setPowerSeqOnOff(POWER_OFF);
			strmsg.Format(_T("Pattern IDD LOW Limit NG. (Setting:%dmA Measure:%dmA)"), nIccLow, m_pApp->m_nLcmPInfo[PINFO_IDD]);
			m_pApp->Gf_ShowMessageBox(strmsg);
			return FALSE;
		}
	}
	if (nIddHigh > 0)
	{
		if (nIddHigh < m_pApp->m_nLcmPInfo[PINFO_IDD])
		{
			m_pApp->m_pCommand->Gf_setPowerSeqOnOff(POWER_OFF);
			strmsg.Format(_T("Pattern IDD HIGH Limit NG. (Setting:%dmA Measure:%dmA)"), nIccHigh, m_pApp->m_nLcmPInfo[PINFO_IDD]);
			m_pApp->Gf_ShowMessageBox(strmsg);
			return FALSE;
		}
	}
	return TRUE;
}

void CPatternTest::Lf_setPatternImageView(CString strPtnName)
{
	if (strPtnName.Find(_T(".BMP")) != -1)
	{
		CRect rc;
		CString sPath;
		GetDlgItem(IDC_STT_PTN_IMAGE_VIEW_SIZE)->GetWindowRect(rc);
		ScreenToClient(rc);
		rc.right -= 5;
		rc.bottom -= 10;
		sPath.Format(_T(".\\Pattern\\BMP\\%s"), strPtnName);
		HBITMAP hBitmap = (HBITMAP)LoadImage(AfxGetInstanceHandle(), sPath, IMAGE_BITMAP, rc.Width(), rc.Height(), LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		m_picPtnImageView.SetBitmap(hBitmap);
		m_picPtnImageView.Invalidate(FALSE);
	}
	else
		m_pApp->m_pPatternView->drawPattern(strPtnName);
}

void CPatternTest::Lf_writeLogKeyIn(int keyValue)
{
	CString sLog;
	if(keyValue == VK_RETURN)			sLog.Format(_T("'ENTER' Key In"));
	else if (keyValue == VK_SPACE)		sLog.Format(_T("'SPACE' Key In"));
	else if (keyValue == VK_HOME)		sLog.Format(_T("'HOME' Key In"));
	else if (keyValue == VK_BACK)		sLog.Format(_T("'BACK SPACE' Key In"));
	else if (keyValue == VK_END)		sLog.Format(_T("'END' Key In"));
	else if (keyValue == VK_RIGHT)		sLog.Format(_T("'RIGHT' Key In"));
	else if (keyValue == VK_LEFT)		sLog.Format(_T("'LEFT' Key In"));
	else if (keyValue == VK_UP)			sLog.Format(_T("'UP' Key In"));
	else if (keyValue == VK_DOWN)		sLog.Format(_T("'DOWN' Key In"));
	else								sLog.Format(_T("Key In (Key Value=%02X)"), keyValue);

	m_pApp->Gf_writeLogData(_T("<TEST>"), sLog);
}