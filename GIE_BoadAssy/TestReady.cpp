// TestReady.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GIE_BoadAssy.h"
#include "TestReady.h"
#include "PatternTest.h"
#include "PanelID.h"
#include "GieJudge.h"
#include "MessageQuestion.h"
#include "DefectResult.h"
// CTestReady 대화 상자입니다.

IMPLEMENT_DYNAMIC(CTestReady, CDialog)

CTestReady::CTestReady(CWnd* pParent /*=NULL*/)
	: CDialog(CTestReady::IDD, pParent)
{

}

CTestReady::~CTestReady()
{
}

void CTestReady::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_TEST_START, m_btnTestStart);
}


BEGIN_MESSAGE_MAP(CTestReady, CDialog)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_TEST_START, &CTestReady::OnBnClickedBtnTestStart)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_STN_CLICKED(IDC_STT_RDY_QTY_RESET, &CTestReady::OnStnClickedSttRdyQtyReset)
END_MESSAGE_MAP()


// CTestReady 메시지 처리기입니다.

BOOL CTestReady::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	lpSystemInfo = m_pApp->GetSystemInfo();	
	lpWorkInfo	= m_pApp->GetWorkInfo();
	lpModelInfo = m_pApp->GetModelInfo();

	Lf_initFontSet();
	Lf_initVariable();
	Lf_updateCount();

	SetTimer(1, 100, NULL);
	SetTimer(TIMER_PID_CHECK, 100, NULL);

	if ((m_pApp->m_bUserIdPM == TRUE) || (m_pApp->m_bUserIdGieng == TRUE))
	{
		GetDlgItem(IDC_BTN_TEST_START)->EnableWindow(TRUE);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CTestReady::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	for(int i=0; i<COLOR_IDX_MAX; i++)
	{
		m_Brush[i].DeleteObject();
	}

	for(int i=0; i<FONT_IDX_MAX; i++)
	{
		m_Font[i].DeleteObject();
	}
}

void CTestReady::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialog::OnPaint()을(를) 호출하지 마십시오.
	CRect rect;
	GetClientRect(&rect);
	rect.bottom = 90;
	dc.FillSolidRect(rect, COLOR_DEEP_BLUE);

	GetClientRect(&rect);
	rect.top = 91;
	dc.FillSolidRect(rect, COLOR_BLUE);

	GetClientRect(&rect);
	rect.top = 92;
	dc.FillSolidRect(rect, COLOR_GRAY64);
}

void CTestReady::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if(nIDEvent == 1)
	{
		KillTimer(1);
		int timerInterval = 500;
		if (m_pApp->m_pDio7230->Gf_getDIOJigTilting() == TRUE)
		{
			m_dioInputBit |= DI_START_READY;
			GetDlgItem(IDC_STT_DIO_INPUT_2)->Invalidate(FALSE);
			GetDlgItem(IDC_STT_STATUS_MSG)->SetWindowText(_T("PANEL TILTING ON"));

			if (m_pApp->m_pDio7230->Gf_getDIOTestStart())
			{
				m_dioInputBit |= DI_TEST_SWITCH1;
				GetDlgItem(IDC_STT_DIO_INPUT_3)->Invalidate(FALSE);
				GetDlgItem(IDC_STT_STATUS_MSG)->SetWindowText(_T("TEST START SIGNAL ON"));

				Lf_startTest();
				timerInterval = 1000;
			}
			else
			{
				m_dioInputBit &= ~DI_TEST_SWITCH1;
				GetDlgItem(IDC_STT_DIO_INPUT_3)->Invalidate(FALSE);
			}
		}
		else
		{
			m_dioInputBit &= ~ DI_START_READY;
			GetDlgItem(IDC_STT_DIO_INPUT_2)->Invalidate(FALSE);
		}
		SetTimer(1, timerInterval, NULL);
		
	}
	else if(nIDEvent == TIMER_PID_CHECK)
	{
		if (m_pApp->m_pDio7230->Dio_DI_ReadPort() & DI_BCR_READ_DONE)
		{
			m_dioInputBit |= DI_BCR_READ_DONE;
			GetDlgItem(IDC_STT_DIO_INPUT_1)->Invalidate(FALSE);
			KillTimer(TIMER_PID_CHECK);
			if (Lf_checkPanelId() == FALSE)
				SetTimer(TIMER_PID_CHECK, 100, NULL);
		}
		else
		{
			m_dioInputBit &= ~DI_BCR_READ_DONE;
			GetDlgItem(IDC_STT_DIO_INPUT_1)->Invalidate(FALSE);
		}
			
		
	}

	CDialog::OnTimer(nIDEvent);
}


void CTestReady::OnBnClickedBtnTestStart()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if ((m_pApp->m_bUserIdPM == TRUE) || (m_pApp->m_bUserIdGieng == TRUE))
	{
		KillTimer(1);
		Lf_startTest();
		SetTimer(1, 1000, NULL);
	}
}

HBRUSH CTestReady::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
		if(pWnd->GetDlgCtrlID()==IDC_STT_MODEL_NAME)
		{
			pDC->SetBkColor(COLOR_DEEP_BLUE);
			pDC->SetTextColor(COLOR_WHITE);
			return m_Brush[COLOR_IDX_DEEP_BLUE];
		}
		if(pWnd->GetDlgCtrlID()==IDC_STT_STATUS_MSG)
		{
			pDC->SetBkColor(COLOR_LIGHT_GREEN);
			pDC->SetTextColor(COLOR_BLACK);
			return m_Brush[COLOR_IDX_LIGHT_GREEN];
		}
		if (pWnd->GetDlgCtrlID() == IDC_STT_PANEL_ID_TIT
			|| pWnd->GetDlgCtrlID() == IDC_STT_TOTAL_CNT_TIT
			|| pWnd->GetDlgCtrlID() == IDC_STT_GOOD_CNT_TIT
			|| pWnd->GetDlgCtrlID() == IDC_STT_BAD_CNT_TIT
			|| pWnd->GetDlgCtrlID() == IDC_STT_DIO_INPUT_TITLE
			)
		{
			pDC->SetBkColor(COLOR_LIGHT_YELLOW);
			pDC->SetTextColor(COLOR_BLACK);
			return m_Brush[COLOR_IDX_LIGHT_YELLOW];
		}
		if (pWnd->GetDlgCtrlID() == IDC_STT_PANEL_ID_VALUE)
		{
			pDC->SetBkColor(COLOR_WHITE);
			pDC->SetTextColor(COLOR_BLACK);
			return m_Brush[COLOR_IDX_WHITE];
		}
		if (pWnd->GetDlgCtrlID() == IDC_STT_RDY_QTY_RESET)
		{
			pDC->SetBkColor(COLOR_ORANGE);
			pDC->SetTextColor(COLOR_WHITE);
			return m_Brush[COLOR_IDX_ORANGE];
		}
		if (pWnd->GetDlgCtrlID() == IDC_STT_TOTAL_CNT_VALUE)
		{
			pDC->SetBkColor(COLOR_WHITE);
			pDC->SetTextColor(COLOR_ORANGE);
			return m_Brush[COLOR_IDX_WHITE];
		}
		if (pWnd->GetDlgCtrlID() == IDC_STT_GOOD_CNT_VALUE)
		{
			pDC->SetBkColor(COLOR_WHITE);
			pDC->SetTextColor(COLOR_GREEN);
			return m_Brush[COLOR_IDX_WHITE];
		}
		if (pWnd->GetDlgCtrlID() == IDC_STT_BAD_CNT_VALUE)
		{
			pDC->SetBkColor(COLOR_WHITE);
			pDC->SetTextColor(COLOR_RED);
			return m_Brush[COLOR_IDX_WHITE];
		}

		if (pWnd->GetDlgCtrlID() == IDC_STT_DIO_INPUT_1)
		{
			if (m_dioInputBit & DI_BCR_READ_DONE)
			{
				pDC->SetBkColor(COLOR_GREEN128);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_GREEN128];
			}
			else
			{
				pDC->SetBkColor(COLOR_BLACK);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_BLACK];
			}
		}
		if (pWnd->GetDlgCtrlID() == IDC_STT_DIO_INPUT_2)
		{
			if (m_dioInputBit & DI_START_READY)
			{
				pDC->SetBkColor(COLOR_GREEN128);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_GREEN128];
			}
			else
			{
				pDC->SetBkColor(COLOR_BLACK);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_BLACK];
			}
		}
		if (pWnd->GetDlgCtrlID() == IDC_STT_DIO_INPUT_3)
		{
			if (m_dioInputBit & DI_TEST_SWITCH1)
			{
				pDC->SetBkColor(COLOR_GREEN128);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_GREEN128];
			}
			else
			{
				pDC->SetBkColor(COLOR_BLACK);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_BLACK];
			}
		}
		break;
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}

BOOL CTestReady::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN)
	{
		switch(pMsg->wParam)
		{
		case VK_F12:
			{
				m_pApp->Gf_writeLogData(_T("<WND>"), _T("F12"));
			}return TRUE;

		case '1':		
			{
				return TRUE;
			}
		case '2':		
			{
				return TRUE;
			}
		case '3':		
			{
				return TRUE;
			}
		case VK_RETURN:
		{
			return TRUE;
		}
		case VK_SPACE:
			if ((m_pApp->m_bUserIdPM == TRUE) || (m_pApp->m_bUserIdGieng == TRUE))
			{
				KillTimer(1);
				Lf_startTest();
				SetTimer(1, 1000, NULL);
				return 1;
			}
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CTestReady::OnStnClickedSttRdyQtyReset()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMessageQuestion que_dlg;
	que_dlg.m_strQMessage.Format(_T("Do you want clear quantity count?"));
	que_dlg.m_strLButton = _T("YES");
	que_dlg.m_strRButton = _T("NO");
	if (que_dlg.DoModal() == IDOK)
	{
		CString sLog;
		sLog.Format(_T("Quentity Count Reset."));
		m_pApp->Gf_writeLogData(_T("<TEST> "), sLog);

		m_pApp->Gf_QtyCountReset();
		Lf_updateCount();
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CTestReady::Lf_initFontSet()
{
	/**************************************************************************************************************************/
	//Font Set
	m_Font[0].CreateFont(24, 11, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("Segoe UI Symbol"));
	GetDlgItem(IDC_STT_PANEL_ID_TIT)->SetFont(&m_Font[0]);
	GetDlgItem(IDC_STT_TOTAL_CNT_TIT)->SetFont(&m_Font[0]);
	GetDlgItem(IDC_STT_GOOD_CNT_TIT)->SetFont(&m_Font[0]);
	GetDlgItem(IDC_STT_BAD_CNT_TIT)->SetFont(&m_Font[0]);
	GetDlgItem(IDC_STT_DIO_INPUT_TITLE)->SetFont(&m_Font[0]);
	GetDlgItem(IDC_STT_RDY_QTY_RESET)->SetFont(&m_Font[0]);

	GetDlgItem(IDC_STT_DIO_INPUT_1)->SetFont(&m_Font[0]);
	GetDlgItem(IDC_STT_DIO_INPUT_2)->SetFont(&m_Font[0]);
	GetDlgItem(IDC_STT_DIO_INPUT_3)->SetFont(&m_Font[0]);

	m_Font[1].CreateFont( 15, 8, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("Segoe UI Symbol"));

	m_Font[2].CreateFont( 15, 8, 0, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0, 0, 0, _T("Segoe UI Symbol"));

	m_Font[3].CreateFont( 34, 14, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("Segoe UI Symbol"));
	GetDlgItem(IDC_STT_STATUS_MSG)->SetFont(&m_Font[3]);
	GetDlgItem(IDC_STT_TOTAL_CNT_VALUE)->SetFont(&m_Font[3]);
	GetDlgItem(IDC_STT_GOOD_CNT_VALUE)->SetFont(&m_Font[3]);
	GetDlgItem(IDC_STT_BAD_CNT_VALUE)->SetFont(&m_Font[3]);
	GetDlgItem(IDC_STT_PANEL_ID_VALUE)->SetFont(&m_Font[3]);


	m_Font[4].CreateFont(60, 26, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("Segoe UI Symbol"));
	GetDlgItem(IDC_STT_MODEL_NAME)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_BTN_TEST_START)->SetFont(&m_Font[4]);

	m_Font[5].CreateFont( 150, 70, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("ARIAL"));

	/**************************************************************************************************************************/
	//Brush Set
	m_Brush[COLOR_IDX_ORANGE].CreateSolidBrush (COLOR_ORANGE);
	m_Brush[COLOR_IDX_RED].CreateSolidBrush(COLOR_RED);
	m_Brush[COLOR_IDX_GREEN].CreateSolidBrush(COLOR_GREEN);
	m_Brush[COLOR_IDX_GREEN128].CreateSolidBrush(COLOR_GREEN128);
	m_Brush[COLOR_IDX_BLACK].CreateSolidBrush(COLOR_BLACK);
	m_Brush[COLOR_IDX_GRAY240].CreateSolidBrush (COLOR_GRAY240);
	m_Brush[COLOR_IDX_GRAY64].CreateSolidBrush (COLOR_GRAY64);
	m_Brush[COLOR_IDX_GRAY94].CreateSolidBrush (COLOR_GRAY94);
	m_Brush[COLOR_IDX_DEEP_BLUE].CreateSolidBrush (COLOR_DEEP_BLUE);
	m_Brush[COLOR_IDX_LIGHT_GREEN].CreateSolidBrush (COLOR_LIGHT_GREEN);
	m_Brush[COLOR_IDX_LIGHT_YELLOW].CreateSolidBrush(COLOR_LIGHT_YELLOW);
}

void CTestReady::Lf_initVariable()
{
	GetDlgItem(IDC_STT_MODEL_NAME)->SetWindowText(lpSystemInfo->m_sModelName);

	m_dioInputBit = 0x0000;
}

bool CTestReady::Lf_getControlBdReady()
{
	int nCnt=0;
	CString strMsg;

	m_pApp->Gf_writeLogData(_T("<PG>"),_T("CTRL B/D Ready Check START"));
	GetDlgItem(IDC_STT_STATUS_MSG)->SetWindowText(_T("CTRL B/D Ready Check"));

	if(DEBUG_UDP_RECEIVE_OK)
		return TRUE;

	while(m_pApp->m_bAreYouReady==FALSE)
	{
		if (m_pApp->m_pCommand->Gf_getAreYouReady() == TRUE)
			break;
		delayMS(20);

		if(nCnt > 3)
		{
			GetDlgItem(IDC_STT_STATUS_MSG)->SetWindowText(_T("No Response PG!"));

			strMsg.Format(_T("<PG> PG Communication Error. No Reponse PG"));
			m_pApp->Gf_ShowMessageBox(strMsg);
			return FALSE;

		}
		nCnt++;
	}
	m_pApp->Gf_writeLogData(_T("<PG>"), _T("CTRL B/D Ready Check END"));

	return TRUE;
}

BOOL CTestReady::Lf_checkPanelId()
{
	CString sdata=_T(""), strlog;
	strlog.Format(_T("BCR [%s]"), lpWorkInfo->m_sReceivePID);
	m_pApp->Gf_writeLogData(_T("<BCR>"), strlog);
	
	if(lpWorkInfo->m_sReceivePID.GetLength() <= 9)
	{
		strlog.Format(_T("BCR ID LENGTH ERROR] LESS 9 [%s]"), lpWorkInfo->m_sReceivePID);
		m_pApp->Gf_ShowMessageBox(strlog);
		lpWorkInfo->m_sPanelID.Empty();
		lpWorkInfo->m_sSerialNumber.Empty();
		CPanelID pidDlg;
		if (pidDlg.DoModal() == IDCANCEL)
			return FALSE;
	}
	else
	{
		sdata.Format(_T("%s"), lpWorkInfo->m_sReceivePID);
		sdata.MakeUpper();

		if(sdata == _T("ERROR") || sdata == _T("NOREAD"))
		{
			strlog.Format(_T("BCR ID DATA ERROR [%s]"), lpWorkInfo->m_sReceivePID);
			m_pApp->Gf_ShowMessageBox(strlog);
			lpWorkInfo->m_sPanelID.Empty();
			lpWorkInfo->m_sSerialNumber.Empty();
			CPanelID pidDlg;
			if (pidDlg.DoModal() == IDCANCEL)
				return FALSE;
		}
	}

	if (lpWorkInfo->m_sReceivePID.GetLength() > 15)
	{
		lpWorkInfo->m_sPanelID.Empty();
		lpWorkInfo->m_sSerialNumber = lpWorkInfo->m_sReceivePID;

		m_pApp->m_pCimNet->SetSerialNumber(lpWorkInfo->m_sSerialNumber);
	}
	else
	{
		lpWorkInfo->m_sPanelID = lpWorkInfo->m_sReceivePID;
		lpWorkInfo->m_sSerialNumber.Empty();

		m_pApp->m_pCimNet->SetPanelID(lpWorkInfo->m_sPanelID);
	}

	GetDlgItem(IDC_STT_PANEL_ID_VALUE)->SetWindowText(lpWorkInfo->m_sReceivePID);
	m_pApp->Gf_writeLogData(_T("<MES>"), lpWorkInfo->m_sReceivePID);
	return TRUE;
}

/*****************************************************************************************************************/
// 이 함수는 기존  BA소스 그대로다. 따로 새로 작성하는것보다 그냥 보던대로 보고 기존 flow대로 돌아가게 놔둔다.
/*****************************************************************************************************************/
BOOL CTestReady::Lf_sendGMESData()
{
	CString sdata=_T(""), outLog=_T("");

	m_pApp->Gf_writeLogData(_T("<MES>"), _T("SEND DATA"));

	if(lpWorkInfo->m_nFastDioJudge == FAST_JUDGE_OK)
	{
		if (lpWorkInfo->m_bIsEdidFail == true)
		{
			//EDID 결과 NG인 경우, NG로만 배출이 가능 하도록 한다.
			//작업자 OK 배출 시도 시에는 상위 통신을 못하도록 막는다.
			m_pApp->Gf_ShowMessageBox(_T("EDID Fail. Can not decide OK."));//AfxMessageBox(_T("EDID Fail. Can not decide OK."));
			return FALSE;
		}
 		lpWorkInfo->m_nPassOrFail = GMES_PNF_PASS;
	}
	else
	{
		int defecetResult = 0;

#if (MES_COMBI_CODE_USE==1)
		m_pApp->Gf_writeLogData(_T("<MES>"), _T("QualityCode Dialog Open"));
		defecetResult = ShowDefectResult(GetSafeOwner());
		lpWorkInfo->m_sRwkCD = GetRWK_CD();
#else
		m_pApp->Gf_writeLogData(_T("<MES>"), _T("DefectCode Dialog Open"));
		CDefectResult dlg;
		dlg.retReasonCode = &lpWorkInfo->m_sRwkCD;
		defecetResult = (int)dlg.DoModal();
#endif
		m_pApp->m_pCimNet->SetRwkCode(lpWorkInfo->m_sRwkCD);
		if ((defecetResult == IDOK) && (lpWorkInfo->m_sRwkCD.IsEmpty() == TRUE))
		{
			lpWorkInfo->m_nPassOrFail = GMES_PNF_PASS;
		}
		else if (((defecetResult == IDOK) && (lpWorkInfo->m_sRwkCD.IsEmpty() == FALSE)) || (lpWorkInfo->m_bDioJudgeNg == true))
		{
			outLog.Format(_T("Select Reason Code - %s"), lpWorkInfo->m_sRwkCD);
			m_pApp->Gf_writeLogData(_T("<MES>"), outLog);

			lpWorkInfo->m_nPassOrFail = GMES_PNF_FAIL;
		}
		else
		{
			m_pApp->Gf_writeLogData(_T("<MES>"), _T("CANCEL"));
			return FALSE;
		}
	}

	
	GetForegroundWindow()->PostMessage (WM_KEYDOWN, VK_F12, 0);
	return TRUE;
}

void CTestReady::Lf_openResult()
{
	m_pApp->Gf_writeLogData(_T("<WND>"), _T("Judge Start"));
	
	if(Lf_sendGMESData()==TRUE)
	{
		if (m_pApp->Gf_PinBlockOpenCheck() == FALSE)
		{
			return;
		}

		if(lpWorkInfo->m_nPassOrFail == GMES_PNF_PASS) 
		{
			if (m_pApp->Gf_gmesSendHost(HOST_EICR) == TRUE)
			{
				m_pApp->m_pDio7230->Gf_setDioOutOK();
				Lf_createCount(GOOD_CNT);
			}
		}
		else if(lpWorkInfo->m_nPassOrFail == GMES_PNF_FAIL)
		{
			if (m_pApp->Gf_gmesSendHost(HOST_EICR) == TRUE)
			{
				m_pApp->m_pDio7230->Gf_setDioOutNG();
				Lf_createCount(BAD_CNT);
			}
		}
	}
}

void CTestReady::Lf_updateCount()
{
	CString sdata=_T("");

	sdata.Format(_T("%d"), lpWorkInfo->m_nGoodCnt + lpWorkInfo->m_nBadCnt);
	GetDlgItem(IDC_STT_TOTAL_CNT_VALUE)->SetWindowText(sdata);

	sdata.Format(_T("%d"), lpWorkInfo->m_nGoodCnt);
	GetDlgItem(IDC_STT_GOOD_CNT_VALUE)->SetWindowText(sdata);

	sdata.Format(_T("%d"), lpWorkInfo->m_nBadCnt);
	GetDlgItem(IDC_STT_BAD_CNT_VALUE)->SetWindowText(sdata);

	sdata.Format(_T("TOTAL : %d, OK : %d, NG : %d"), lpWorkInfo->m_nGoodCnt + lpWorkInfo->m_nBadCnt,lpWorkInfo->m_nGoodCnt, lpWorkInfo->m_nBadCnt);
	m_pApp->Gf_writeLogData(_T("<TEST> "), sdata);
}

void CTestReady::Lf_createCount(int typ)
{
	m_pApp->Gf_writeInspCount(typ);
	
	Lf_updateCount();
}

bool CTestReady::Lf_startTest()
{
	bool bRet;

	bRet = Lf_startTestOn();

	// after test initialize
	Lf_setVariableReset();

	SetTimer(1, 1000, NULL);
	return bRet;
}

bool CTestReady::Lf_startTestOn()
{
	BYTE dioRd=0;

	lpWorkInfo->tt_startTime = CTime::GetCurrentTime();

	GetDlgItem(IDC_STT_STATUS_MSG)->SetWindowText(_T("[DIO PLC -> PC] JIG IN"));
	if ((lpWorkInfo->m_sPanelID.IsEmpty() == TRUE) && (lpWorkInfo->m_sSerialNumber.IsEmpty() == TRUE))
	{
		CPanelID piddlg;
		if (piddlg.DoModal() == IDOK)
		{
			if (lpWorkInfo->m_sPanelID.IsEmpty() == FALSE)
			{
				GetDlgItem(IDC_STT_PANEL_ID_VALUE)->SetWindowText(lpWorkInfo->m_sPanelID);
			}
			else if (lpWorkInfo->m_sSerialNumber.IsEmpty() == FALSE)
			{
				GetDlgItem(IDC_STT_PANEL_ID_VALUE)->SetWindowText(lpWorkInfo->m_sSerialNumber);
			}
		}
		else
		{
			return false;
		}
	}

	if(Lf_getControlBdReady() == false)
	{
		return false;
	}

	if (Lf_SystemAutoFusing() == FALSE)
	{
		return FALSE;
	}

	lpWorkInfo->m_nPassOrFail = GMES_PNF_NONE;
	lpWorkInfo->m_sRwkCD.Empty();
	
	if (m_pApp->Gf_gmesSendHost(HOST_PCHK) == FALSE)
	{
		return false;
	}

	if (Lf_AutoModelChange() == FALSE)
	{
		return false;
	}

	if (Lf_CableOpenCheck() == FALSE)
	{
		return false;
	}


	GetDlgItem(IDC_BTN_TEST_START)->EnableWindow(FALSE);

	// 검사 시작하면 배출할때까지 TEST_ING DIO 신호 살린다.
	m_pApp->m_pDio7230->Gf_setDioOutTesting();

	CString sLog;
	sLog.Format(_T("TEST Start Delay (%dms)"), lpSystemInfo->m_nTestStartDelay);
	m_pApp->Gf_writeLogData(_T("<TEST>"), sLog);
	delayMS(lpSystemInfo->m_nTestStartDelay);

	GetDlgItem(IDC_STT_STATUS_MSG)->SetWindowText(_T("Pattern Test START"));
	CPatternTest ptnDlg;
	ptnDlg.DoModal();
	m_pApp->Gf_writeLogData(_T("<TEST>"), _T("Pattern Test END"));


	Lf_openResult();
	m_btnTestStart.SetFocus();

	lpWorkInfo->tt_endTime = CTime::GetCurrentTime();
	m_pApp->Gf_writeSummaryLog();

	/*********************************************************************************************************************/	
	GetDlgItem(IDC_STT_STATUS_MSG)->SetWindowText(_T("TEST READY"));
	if ((m_pApp->m_bUserIdPM == TRUE) || (m_pApp->m_bUserIdGieng == TRUE))
	{
		GetDlgItem(IDC_BTN_TEST_START)->EnableWindow(TRUE);
	}
	return true;
}

void CTestReady::Lf_setVariableReset()
{
	ZeroMemory(m_pApp->m_nStartCheckTime, sizeof(m_pApp->m_nStartCheckTime));
	ZeroMemory(m_pApp->m_nEndCheckTime, sizeof(m_pApp->m_nEndCheckTime));
	ZeroMemory(m_pApp->m_nPatTime, sizeof(m_pApp->m_nPatTime));
	lpWorkInfo->m_bIsEdidFail = false;
	m_pApp->m_pCimNet->SetRwkCode(_T(""));

	// 검사 함번할때마다 PID 다시 입력하도록 수정.(최종검수때 요청) 2022-10-04 CNZ
	lpWorkInfo->m_sPanelID.Empty();
	lpWorkInfo->m_sSerialNumber.Empty();
	GetDlgItem(IDC_STT_PANEL_ID_VALUE)->SetWindowText(_T(""));

	m_dioInputBit = 0x0000;
	SetTimer(TIMER_PID_CHECK, 100, NULL);

	CString sLog;
	sLog.Format(_T("============================================= %s (%s) ============================================="), m_pApp->m_sSoftwareVersion, lpSystemInfo->m_sModelName);
	m_pApp->Gf_writeLogData(sLog, _T(""));
}

BOOL CTestReady::Lf_SystemAutoFusing()
{
	if (lpSystemInfo->m_nSystemAutoFusing == TRUE)
	{
		m_pApp->Gf_writeLogData(_T("<TEST>"), _T("System Auto Fusing"));
		if (m_pApp->m_pCommand->Gf_setFusingSystemInfo() == TRUE)
		{
			m_pApp->Gf_writeLogData(_T("<TEST>"), _T("System Auto Fusing => OK"));
			return TRUE;
		}
		else
		{
			m_pApp->Gf_writeLogData(_T("<TEST>"), _T("System Auto Fusing => NG"));

			CString strMsg;
			strMsg.Format(_T("<PG> System Auto Fusing Error. No Reponse PG"));
			m_pApp->Gf_ShowMessageBox(strMsg);

			return FALSE;
		}
	}
	else
	{
		m_pApp->Gf_writeLogData(_T("<TEST>"), _T("System Auto Fusing => SKIP"));
	}
}

BOOL CTestReady::Lf_CableOpenCheck()
{
	int nOpenValue1, nOpenValue2;
	BOOL bOpenLvds40P=0, bOpenLvds50P=0, bOpenDP;
	if (lpModelInfo->m_nCableOpenUse == _ON_)
	{
		if (m_pApp->m_pCommand->Gf_CheckCableOpen() == TRUE)
		{
			sscanf_s(&m_pApp->m_pCommand->gszudpRcvPacket[PACKET_PT_DATA], "%04X%04X", &nOpenValue1, &nOpenValue2);

			CString sLog;
			sLog.Format(_T("Cable Open Check Return Value : %04X %04X"), nOpenValue1, nOpenValue2);
			m_pApp->Gf_writeLogData(_T("<TEST>"), sLog);

			if (lpModelInfo->m_nSignalType == SIGNAL_TYPE_LVDS)
			{
				bOpenLvds40P = nOpenValue1 & 0x000C;
				bOpenLvds50P = nOpenValue1 & 0x0003;
				if ((bOpenLvds40P == 0) && (bOpenLvds50P == 0))
				{
					return TRUE;
				}
				else
				{
					CString strMsg;
					strMsg.Format(_T("User Cable Open Check Fail. "));
					if (bOpenLvds40P != 0)	strMsg.Append(_T("(40P) "));
					if (bOpenLvds50P != 0)	strMsg.Append(_T("(50P or PIN Block)"));
					m_pApp->Gf_ShowMessageBox(strMsg);
				}
				return FALSE;
			}
			else if (lpModelInfo->m_nSignalType == SIGNAL_TYPE_DP)
			{
				bOpenLvds40P = nOpenValue1 & 0x000C;
				bOpenDP = nOpenValue2 & 0x0400;
				if ((bOpenLvds40P == 0) && (bOpenDP == 0))
				{
					return TRUE;
				}
				else
				{
					CString strMsg;
					strMsg.Format(_T("User Cable Open Check Fail. "));
					if (bOpenLvds40P != 0)	strMsg.Append(_T("(DP 40P Cable Open)"));
					if (bOpenDP != 0)	strMsg.Append(_T("(DP IPEX Cable Open)"));
					m_pApp->Gf_ShowMessageBox(strMsg);
				}
				return FALSE;
			}
		}
	}

	return TRUE;
}

BOOL CTestReady::Lf_AutoModelChange()
{
	if ((m_pApp->m_bUserIdGieng == TRUE) || (m_pApp->m_bUserIdPM == TRUE))
		return TRUE;

	// 현재 모델과 MES TOP_MODEL이 서로 다르면 자동 M/C를 진행한다.
	if (lpSystemInfo->m_sModelName != lpWorkInfo->m_sMesTopModelName)
	{
		if (m_pApp->Gf_findModelFile(lpWorkInfo->m_sMesTopModelName) == TRUE)
		{
			CString sLog;
			sLog.Format(_T("Auto Model Change OK.  [%s] => [%s]"), lpSystemInfo->m_sModelName, lpWorkInfo->m_sMesTopModelName);
			m_pApp->Gf_writeLogData(_T("<AUTO M/C>"), sLog);

			lpSystemInfo->m_sModelName = lpWorkInfo->m_sMesTopModelName;
			Write_SysIniFile(_T("SYSTEM"), _T("LAST_MODELNAME"), lpSystemInfo->m_sModelName);

			m_pApp->Gf_loadMedelFile();
			AfxGetApp()->GetMainWnd()->SendMessage(WM_UPDATE_SYSTEM_INFO, NULL, NULL);
		}
		else
		{
			CString sMsg;
			sMsg.Format(_T("Auto Model Change Fail. '%s' model file does not exist."), lpWorkInfo->m_sMesTopModelName);
			m_pApp->Gf_ShowMessageBox(sMsg);
			return FALSE;
		}
	}

	return TRUE;
}



