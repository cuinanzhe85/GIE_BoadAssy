// TestReady.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GIE_BoadAssy.h"
#include "TestReady.h"
#include "PatternTest.h"
#include "PanelID.h"
#include "GieJudge.h"
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
END_MESSAGE_MAP()


// CTestReady 메시지 처리기입니다.

BOOL CTestReady::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	lpSystemInfo = m_pApp->GetSystemInfo();	
	lpWorkInfo	= m_pApp->GetWorkInfo();

	Lf_initFontSet();
	Lf_initVariable();
	Lf_updateCount();

	SetTimer(1, 100, NULL);
	SetTimer(TIMER_PID_CHECK, 100, NULL);
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

void CTestReady::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if(nIDEvent == 1)
	{
		KillTimer(1);

		if(m_pApp->m_pDio7230->Gf_getDIOJigArrive())
		{
			GetDlgItem(IDC_STT_STATUS_MSG)->SetWindowText(_T("JIG ARRIVED"));

			if(m_pApp->m_pDio7230->Gf_getDIOTestStart())
			{
				GetDlgItem(IDC_STT_STATUS_MSG)->SetWindowText(_T("TEST START SIGNAL ON"));

				Lf_startTest();

				SetTimer(1,100,NULL);

			}
			else
			{
				SetTimer(1,100,NULL);
			}
		}
		else
		{
			SetTimer(1,100,NULL);
		}		
	}
	else if(nIDEvent == TIMER_PID_CHECK)
	{
		KillTimer(TIMER_PID_CHECK);
		if(lpWorkInfo->m_bPIDReadComplete==true)
		{			
			m_pApp->m_pDio7230->Gf_setDioWrite(DIO_GUMI_M5_BCR_READ_OK);
			m_pApp->Gf_writeLogData(_T("<DIO>"), _T("OUT -> BCR READ OK"));
			lpWorkInfo->m_bPIDReadComplete=false;
		}
		SetTimer(TIMER_PID_CHECK, 100, NULL);
	}

	CDialog::OnTimer(nIDEvent);
}


void CTestReady::OnBnClickedBtnTestStart()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_startTest();
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
				lpWorkInfo->m_bDioDebugTestStart = true;
				return TRUE;
			}
		case '2':		
			{
				lpWorkInfo->m_bDioDebugJudgeOk = true;
				return TRUE;
			}
		case '3':		
			{
				lpWorkInfo->m_bDioDebugJudgeNg = true;
				return TRUE;
			}
		case VK_SPACE:		return 1;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CTestReady::Lf_initFontSet()
{
	/**************************************************************************************************************************/
	//Font Set
	m_Font[0].CreateFont(24, 11, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("Segoe UI Symbol"));
	GetDlgItem(IDC_STT_PANEL_ID_TIT)->SetFont(&m_Font[0]);
	GetDlgItem(IDC_STT_TOTAL_CNT_TIT)->SetFont(&m_Font[0]);
	GetDlgItem(IDC_STT_GOOD_CNT_TIT)->SetFont(&m_Font[0]);
	GetDlgItem(IDC_STT_BAD_CNT_TIT)->SetFont(&m_Font[0]);
	GetDlgItem(IDC_STT_PANEL_ID_VALUE)->SetFont(&m_Font[0]);

	m_Font[1].CreateFont( 15, 8, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("Segoe UI Symbol"));

	m_Font[2].CreateFont( 15, 8, 0, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0, 0, 0, _T("Segoe UI Symbol"));

	m_Font[3].CreateFont( 34, 14, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("Segoe UI Symbol"));
	GetDlgItem(IDC_STT_STATUS_MSG)->SetFont(&m_Font[3]);
	GetDlgItem(IDC_STT_TOTAL_CNT_VALUE)->SetFont(&m_Font[3]);
	GetDlgItem(IDC_STT_GOOD_CNT_VALUE)->SetFont(&m_Font[3]);
	GetDlgItem(IDC_STT_BAD_CNT_VALUE)->SetFont(&m_Font[3]);

	GetDlgItem(IDC_BTN_TEST_START)->SetFont(&m_Font[3]);

	m_Font[4].CreateFont(60, 26, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("Segoe UI Symbol"));
	GetDlgItem(IDC_STT_MODEL_NAME)->SetFont(&m_Font[4]);

	m_Font[5].CreateFont( 150, 70, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("ARIAL"));

	/**************************************************************************************************************************/
	//Brush Set
	m_Brush[COLOR_IDX_ORANGE].CreateSolidBrush (COLOR_ORANGE);
	m_Brush[COLOR_IDX_RED].CreateSolidBrush(COLOR_RED);
	m_Brush[COLOR_IDX_GREEN].CreateSolidBrush(COLOR_GREEN);
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
	lpWorkInfo->m_bDioDebugTestStart = false;
}

bool CTestReady::Lf_getControlBdReady()
{
	int nCnt=0;

	m_pApp->Gf_writeLogData(_T("<PG>"),_T("CTRL B/D Ready Check START"));
	GetDlgItem(IDC_STT_STATUS_MSG)->SetWindowText(_T("CTRL B/D Ready Check"));

	if(DEBUG_232RECEIVE_OK)	
		return TRUE;

	while(m_pApp->m_bAreYouReady==FALSE)
	{
		m_pApp->m_pCommand->Gf_getAreYouReady();
		Sleep(20);

		if(nCnt > 3)
		{
			GetDlgItem(IDC_STT_STATUS_MSG)->SetWindowText(_T("No Response PG.!!!!"));
			return FALSE;

		}
		nCnt++;
	}
	m_pApp->Gf_writeLogData(_T("<PG>"), _T("CTRL B/D Ready Check END"));

	return TRUE;
}

void CTestReady::Lf_checkPanelId()
{
	CString sdata=_T(""), strlog;
	strlog.Format(_T("SEEK BCR [%s]"), lpWorkInfo->m_sReceivePID);
	m_pApp->Gf_writeLogData(_T("<BCR>"), strlog);

	lpWorkInfo->m_sPID = lpWorkInfo->m_sReceivePID;
	
	if(lpWorkInfo->m_sPID.GetLength() <= 9)
	{
		strlog.Format(_T("PANEL ID LENGTH ERROR] LESS 9 [%s]"), lpWorkInfo->m_sPID);
		m_pApp->Gf_writeLogData(_T("<BCR>"), strlog);
		CPanelID pidDlg;
		pidDlg.DoModal();
	}
	else
	{		
		sdata.Format(_T("%s"), lpWorkInfo->m_sPID);
		sdata.MakeUpper();

		if(sdata == _T("ERROR") || sdata == _T("NOREAD"))
		{ 
			strlog.Format(_T("PANEL ID DATA ERROR [%s]"), lpWorkInfo->m_sPID);
			m_pApp->Gf_writeLogData(_T("<BCR>"), strlog);
			lpWorkInfo->m_sPID.Empty();
			CPanelID pidDlg;
			pidDlg.DoModal();
		}
	}

	GetDlgItem(IDC_STT_PANEL_ID_VALUE)->SetWindowText(lpWorkInfo->m_sPID);	
	m_pApp->m_pCimNet->SetPanelID(lpWorkInfo->m_sPID);//pUiPorc->pCimNet->SetPanelId (pUiPorc->comm.curData.strUsePanelId.GetBuffer(0));
	m_pApp->Gf_writeLogData(_T("<MES>"), lpWorkInfo->m_sPID);
}

/*****************************************************************************************************************/
// 이 함수는 기존  BA소스 그대로다. 따로 새로 작성하는것보다 그냥 보던대로 보고 기존 flow대로 돌아가게 놔둔다.
/*****************************************************************************************************************/
BOOL CTestReady::Lf_sendGMESData()
{
	CString sdata=_T(""), outLog=_T("");

	m_pApp->Gf_writeLogData(_T("<MES>"), _T("SEND DATA"));

	if(lpWorkInfo->m_nFastJudge == FAST_JUDGE_OK)
	{
 		lpWorkInfo->m_nPassOrFail = GMES_PNF_PASS;
		m_pApp->Gf_setGMesGoodInfo();
 		sdata.Format(_T(""));
		m_pApp->m_pCimNet->SetOverHaulFlag(sdata.GetBuffer(0));
	}
	else
	{
		int defecetResult = 0;
		BYTE readDio;

		m_pApp->Gf_writeLogData(_T("<MES>"), _T("Bad Code Dialog Open"));
		m_pApp->Gf_writeLogData(_T("<MES>"), lpWorkInfo->m_sBadCode);

		defecetResult = ShowDefectResult(GetSafeOwner());
		Sleep(50); //Dio Data가 들어오는 시점 관련하여 확인하기 위해서.
		if(defecetResult == IDOK	
		|| lpWorkInfo->m_bDioJudgeNg == true
		|| lpWorkInfo->m_bDioJudgeOk == true 
		|| lpWorkInfo->m_nPassOrFail == GMES_PNF_PASS 
		|| lpWorkInfo->m_nPassOrFail == GMES_PNF_FAIL)
		{
			readDio = (BYTE)m_pApp->m_pDio7230->Dio_DI_ReadPort();
			outLog.Format(_T("OK - %d, NG - %d, B - %d, PnF - %d, BAD DLG - %d, DIO - %d"), 
				lpWorkInfo->m_bDioJudgeOk, 
				lpWorkInfo->m_bDioJudgeNg, 
				lpWorkInfo->m_bDioPajuJudgeBGrade, 
				lpWorkInfo->m_nPassOrFail, 
				defecetResult, 
				readDio);

			m_pApp->Gf_writeLogData(_T("<MES>"), outLog.GetBuffer(0));

			lpWorkInfo->m_sBadCode = GetRWK_CD();
			lpWorkInfo->m_sExpectedCode = GetExpected_RWK();

			outLog.Format(_T("RWKs- %s, EXPECTED_RWK - %s"), lpWorkInfo->m_sBadCode, lpWorkInfo->m_sExpectedCode);
			m_pApp->Gf_writeLogData(_T("<MES>"), outLog);

			UpdateData(FALSE);

			// NG 버튼을 눌렀을 경우는 무조건 NG 처리 함. BAD CODE가 입력 된 상태에서도 NG 버튼 신호 입력 시 NG 배출.
			if(lpWorkInfo->m_bDioJudgeNg == true)
			{
				//구미의 경우 작업자가 JUDGE NG 버튼으로 판정 시 BAD 코드가 없는 경우 상위 보고를 하지 아니하고 NG 배출한다.
				lpWorkInfo->m_sPID.Empty();
//imsi				pUiPorc->comm.curData.iPatternEndESC = 0;
				lpWorkInfo->m_nPassOrFail = GMES_PNF_FAIL;
				m_pApp->Gf_writeLogData(_T("<MES>"), _T("DO NOT SEND EICR"));

				//TEST OK 신호를 출력하여 JIG가 대기 위치로 이동 하도록 한다. 
				//이후 OK, NG 신호를 PLC로 전달하여 OUT 이제기가 배출 하도록 한다.
				m_pApp->m_pDio7230->Gf_setDioWrite(DIO_GUMI_M5_TEST_OK);
				return TRUE;
			}
			else if(lpWorkInfo->m_bDioJudgeOk == true)
			{
				m_pApp->m_pCimNet->SetRwkCode(_T(""));//pUiPorc->pCimNet->ResetRwkCode();
				//m_pApp->m_pCimNet->SetExpectedCode(_T(""));
				lpWorkInfo->m_sBadCode.Empty();
				lpWorkInfo->m_sExpectedCode.Empty();
			}

			if ((lpWorkInfo->m_sBadCode.GetLength() == 0 && lpWorkInfo->m_bDioJudgeNg == false) 
			 || (lpWorkInfo->m_sBadCode.GetLength() > 0 && lpWorkInfo->m_sExpectedCode.GetLength() > 0)
			 || (lpWorkInfo->m_bDioJudgeOk == true)
			 || (lpWorkInfo->m_bDioPajuJudgeBGrade == true)
			 || (lpWorkInfo->m_nPassOrFail == GMES_PNF_PASS))
			{
				//B급도 양품 처리한다.
				//B급 버튼의 경우에는 BAD CODE와 B급 CODE는 정해진 CODE를 사용한다.
				//지정된 BAD CODE와 B급 코드는 LGD에서 받은다.
				if(lpWorkInfo->m_bDioPajuJudgeBGrade == true)   
				{
					m_pApp->Gf_writeLogData(_T("<MES>"), _T("SET B GRADE"));

					if (lpWorkInfo->m_sBadCode.GetLength() == 0)
					{																  
						lpWorkInfo->m_sBadCode.Format(_T("A0G-B04----F04-G5G----------------------------"));
					}
					if (lpWorkInfo->m_sExpectedCode.GetLength() == 0)
					{
						lpWorkInfo->m_sExpectedCode.Format(_T("B11"));
					}
					m_pApp->Gf_setGMesBGradeInfo();
				}
				else
				{
					m_pApp->Gf_setGMesGoodInfo();
				}
				lpWorkInfo->m_nPassOrFail = GMES_PNF_PASS;
			}
			else
			{	
				lpWorkInfo->m_nPassOrFail = GMES_PNF_FAIL;
				m_pApp->Gf_setGMesBadInfo();
			}

			sdata.Format(_T(""));
			m_pApp->m_pCimNet->SetOverHaulFlag(sdata.GetBuffer(0));//pUiPorc->pCimNet->ResetOverHaulFlag(strTemp.GetBuffer(0));			
		}
		else
		{
			readDio = (BYTE)m_pApp->m_pDio7230->Dio_DI_ReadPort();
			outLog.Format(_T("[GMES BAD CODE] OK - %d, NG - %d, B - %d, PnF - %d, BAD DLG - %d, DIO - %d"), 
				lpWorkInfo->m_bDioJudgeOk, 
				lpWorkInfo->m_bDioJudgeNg, 
				lpWorkInfo->m_bDioPajuJudgeBGrade, 
				lpWorkInfo->m_nPassOrFail, 
				defecetResult, 
				readDio);
			m_pApp->Gf_writeLogData(_T("<MES>"), outLog);

			m_pApp->Gf_writeLogData(_T("MES"), _T("CANCEL"));
			return FALSE;
		}
	}

	if (lpWorkInfo->m_bIsEdidFail == true && lpWorkInfo->m_nPassOrFail == GMES_PNF_PASS)
	{
		//EDID 결과 NG인 경우, NG로만 배출이 가능 하도록 한다.
		//작업자 OK 배출 시도 시에는 상위 통신을 못하도록 막는다.
		m_pApp->m_pCommand->Gf_ShowMessageBox(_T("EDID Fail. Can not decide OK."));//AfxMessageBox(_T("EDID Fail. Can not decide OK."));
		return FALSE;
	}
	GetForegroundWindow()->PostMessage (WM_KEYDOWN, VK_F12, 0);
	m_pApp->Gf_sendGmesHost(HOST_EICR);

	//TEST OK 신호를 출력하여 JIG가 대기 위치로 이동 하도록 한다. 
	//이후 OK, NG 신호를 PLC로 전달하여 OUT 이제기가 배출 하도록 한다. 
	//구미 장비 기술 안철민S 요청 사항.
	//상위 결과를 받고서 NG LABEL 붙여야하는 이유로 JIG OUT 위치 변경. 위 내용 무시함.
	m_pApp->Gf_writeLogData(_T("<DIO>"), _T("OUT -> TEST OK - JIG OUT"));
	m_pApp->m_pDio7230->Gf_setDioWrite(DIO_GUMI_M5_TEST_OK);//(DIO_GUMI_M5_TEST_OK, 1);
//imsi		pUiPorc->comm.curData.strUsePanelId = "";
	return TRUE;
}

void CTestReady::Lf_openResult()
{
	m_pApp->Gf_writeLogData(_T("<WND>"), _T("Judge Start"));

	if(lpSystemInfo->m_nOperationMode == IN_LINE) 
	{
		if(m_pApp->m_bUserIdPM == true || m_pApp->m_bUserIdGieng == true)
		{
			int boxResult = 0;
			m_pApp->Gf_writeLogData(_T("<WND>"), _T("[TEST MODE] TECH or GIENG"));

			if (lpWorkInfo->m_nFastJudge != FAST_JUDGE_OK && lpWorkInfo->m_nFastJudge != FAST_JUDGE_NG)
			{
				CGieJudge gieDlg;
				gieDlg.DoModal();
			}

			if(lpWorkInfo->m_bGieJudgeNg == true || lpWorkInfo->m_nFastJudge == FAST_JUDGE_NG)
			{
				//TEST OK 신호를 출력하여 JIG가 대기 위치로 이동 하도록 한다. 
				//이후 OK, NG 신호를 PLC로 전달하여 OUT 이제기가 배출 하도록 한다.				
				m_pApp->m_pDio7230->Gf_setDioWrite(DIO_GUMI_M5_TEST_OK);//Dio_OutPut(DIO_GUMI_M5_TEST_OK, 1);

				Sleep(500); //PLC로 TEST OK, NG 신호를 동시에 들어가도 상관은 없으나 일단 안정적으로 FLOW를 가기 위해 Delay 줌. T/T 과 상관없음

				m_pApp->m_pDio7230->Gf_setDioWrite(DIO_GUMI_M5_JUDGE_NG);//Dio_OutPut(DIO_JUDGE_NG, 1);
				m_pApp->Gf_writeLogData(_T("<DIO>"), _T("OUT -> JUDGE NG"));
				Lf_createCount(BAD_CNT); 
			}
			else if(lpWorkInfo->m_bGieJudgeOk == true || lpWorkInfo->m_nFastJudge == FAST_JUDGE_OK)
			{
				//TEST OK 신호를 출력하여 JIG가 대기 위치로 이동 하도록 한다. 
				//이후 OK, NG 신호를 PLC로 전달하여 OUT 이제기가 배출 하도록 한다.
				m_pApp->m_pDio7230->Gf_setDioWrite(DIO_GUMI_M5_TEST_OK);//Dio_OutPut(DIO_GUMI_M5_TEST_OK, 1);	

				Sleep(500);  //PLC로 TEST OK, NG 신호를 동시에 들어가도 상관은 없으나 일단 안정적으로 FLOW를 가기 위해 Delay 줌. T/T 과 상관없음

				m_pApp->m_pDio7230->Gf_setDioWrite(DIO_GUMI_M5_JUDGE_OK);//Dio_OutPut(DIO_JUDGE_OK, 1);	
				m_pApp->Gf_writeLogData(_T("<DIO>"), _T("OUT -> JUDGE OK"));
				Lf_createCount(GOOD_CNT);
			}
			else
			{
				m_pApp->m_pDio7230->Gf_setDioWrite(DIO_INIT);//Dio_OutPut(DIO_MAX, 1);
				m_pApp->Gf_writeLogData(_T("<DIO>"), _T("OUT -> NO SIGNAL"));
			}
		}
		else
		{
			if(Lf_sendGMESData()==TRUE)
			{
				if(lpWorkInfo->m_nPassOrFail == GMES_PNF_PASS) 
				{
					Lf_createCount(GOOD_CNT);

					m_pApp->m_pDio7230->Gf_setDioWrite(DIO_JUDGE_OK);//Dio_OutPut(DIO_JUDGE_OK, 1);
					m_pApp->Gf_writeLogData(_T("<DIO>"), _T("OUT -> JUDGE OK"));
	
				}
				else if(lpWorkInfo->m_nPassOrFail == GMES_PNF_FAIL)
				{
					Lf_createCount(BAD_CNT);

					m_pApp->m_pDio7230->Gf_setDioWrite(DIO_JUDGE_NG);//Dio_OutPut(DIO_JUDGE_NG, 1);
					m_pApp->Gf_writeLogData(_T("<DIO>"), _T("OUT -> JUDGE NG"));
				}
			}
		}
	}
	else
	{
		if (lpWorkInfo->m_bEscDetect == false)
			Lf_createCount(GOOD_CNT);
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
	BYTE dioRd=0;
	CPatternTest ptnDlg;

	if(lpSystemInfo->m_nOperationMode == EQP_INLINE)
	{
		if(m_pApp->m_pDio7230->Gf_getDIOJigArrive())
		{
			GetDlgItem(IDC_STT_STATUS_MSG)->SetWindowText(_T("[DIO PLC -> PC] JIG IN - START PATTERN TEST"));
		}
		else
		{
			GetDlgItem(IDC_STT_STATUS_MSG)->SetWindowText(_T("[DIO PLC -> PC] JIG OUT - CAN NOT START PATTERN TEST"));
			return false;
		}
	}

	m_pApp->m_pCommand->Gf_setIF5VPowerOffOn(TRUE);

	if(Lf_getControlBdReady() == false)
	{
		return false;
	}

	lpWorkInfo->m_nPassOrFail = GMES_PNF_NONE;

	// 	pUiPorc->comm.curData.strErrorMessage = "";
	// 	pUiPorc->comm.curData.iStartTest = SEQ_PTN_TEST_START;
	// 	pUiPorc->comm.curData.strPtnTestInfo = "";
	// 
	if(lpSystemInfo->m_nOperationMode == EQP_INLINE)
	{
		Lf_checkPanelId();
	}

	delayMS(lpSystemInfo->m_nTestStartDelay);

	GetDlgItem(IDC_STT_STATUS_MSG)->SetWindowText(_T("Start Pattern Test"));
	ptnDlg.DoModal();

	if(lpSystemInfo->m_nOperationMode == EQP_INLINE)
	{
		delayMS(lpSystemInfo->m_nTestStartDelay);
		m_pApp->m_pDio7230->Gf_setDioWrite(DIO_GUMI_M5_PRESS_NOMAL_UP);
		m_pApp->Gf_writeLogData(_T("<DIO>"), _T("OUT -> PRESS UP"));
		if(lpWorkInfo->m_bIsEdidFail == true)
		{
			m_pApp->m_pDio7230->Gf_setDioWrite(DIO_GUMI_M5_EDID_NG);
			m_pApp->Gf_writeLogData(_T("<DIO>"), _T("OUT -> EDID NG"));
		}
	}

	//imsi	pUiPorc->comm.curData.iStartTest = SEQ_PTN_TEST_END;
	Lf_openResult();
	//imsi	CreateInfoUpdate();
	//imsi	pUiPorc->comm.curData.iStartTest = SEQ_JUDGE_END;
	m_btnTestStart.SetFocus();

	m_pApp->Gf_writeLogData(_T("<TEST>"), _T("Pattern Test END"));

	/*********************************************************************************************************************/
	// after test initialize
	Lf_setVariableAfter();

	m_pApp->m_pCommand->Gf_setIF5VPowerOffOn(FALSE);

	return true;
}

void CTestReady::Lf_setVariableAfter()
{
	ZeroMemory(m_pApp->m_nStartCheckTime, sizeof(m_pApp->m_nStartCheckTime));
	ZeroMemory(m_pApp->m_nEndCheckTime, sizeof(m_pApp->m_nEndCheckTime));
	ZeroMemory(m_pApp->m_nPatTime, sizeof(m_pApp->m_nPatTime));
	lpWorkInfo->m_bIsEdidFail = false;
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
