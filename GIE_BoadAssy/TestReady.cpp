// TestReady.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "GIE_BoadAssy.h"
#include "TestReady.h"
#include "PatternTest.h"
#include "PanelID.h"
#include "GieJudge.h"
// CTestReady ��ȭ �����Դϴ�.

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


// CTestReady �޽��� ó�����Դϴ�.

BOOL CTestReady::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	lpSystemInfo = m_pApp->GetSystemInfo();	
	lpWorkInfo	= m_pApp->GetWorkInfo();

	Lf_initFontSet();
	Lf_initVariable();
	Lf_updateCount();

	SetTimer(1, 100, NULL);
	SetTimer(TIMER_PID_CHECK, 100, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CTestReady::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	Lf_startTest();
}

HBRUSH CTestReady::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  ���⼭ DC�� Ư���� �����մϴ�.
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
	// TODO:  �⺻���� �������� ������ �ٸ� �귯�ø� ��ȯ�մϴ�.
	return hbr;
}

BOOL CTestReady::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
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
// �� �Լ��� ����  BA�ҽ� �״�δ�. ���� ���� �ۼ��ϴ°ͺ��� �׳� ������� ���� ���� flow��� ���ư��� ���д�.
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
		Sleep(50); //Dio Data�� ������ ���� �����Ͽ� Ȯ���ϱ� ���ؼ�.
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

			// NG ��ư�� ������ ���� ������ NG ó�� ��. BAD CODE�� �Է� �� ���¿����� NG ��ư ��ȣ �Է� �� NG ����.
			if(lpWorkInfo->m_bDioJudgeNg == true)
			{
				//������ ��� �۾��ڰ� JUDGE NG ��ư���� ���� �� BAD �ڵ尡 ���� ��� ���� ���� ���� �ƴ��ϰ� NG �����Ѵ�.
				lpWorkInfo->m_sPID.Empty();
//imsi				pUiPorc->comm.curData.iPatternEndESC = 0;
				lpWorkInfo->m_nPassOrFail = GMES_PNF_FAIL;
				m_pApp->Gf_writeLogData(_T("<MES>"), _T("DO NOT SEND EICR"));

				//TEST OK ��ȣ�� ����Ͽ� JIG�� ��� ��ġ�� �̵� �ϵ��� �Ѵ�. 
				//���� OK, NG ��ȣ�� PLC�� �����Ͽ� OUT �����Ⱑ ���� �ϵ��� �Ѵ�.
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
				//B�޵� ��ǰ ó���Ѵ�.
				//B�� ��ư�� ��쿡�� BAD CODE�� B�� CODE�� ������ CODE�� ����Ѵ�.
				//������ BAD CODE�� B�� �ڵ�� LGD���� ������.
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
		//EDID ��� NG�� ���, NG�θ� ������ ���� �ϵ��� �Ѵ�.
		//�۾��� OK ���� �õ� �ÿ��� ���� ����� ���ϵ��� ���´�.
		m_pApp->m_pCommand->Gf_ShowMessageBox(_T("EDID Fail. Can not decide OK."));//AfxMessageBox(_T("EDID Fail. Can not decide OK."));
		return FALSE;
	}
	GetForegroundWindow()->PostMessage (WM_KEYDOWN, VK_F12, 0);
	m_pApp->Gf_sendGmesHost(HOST_EICR);

	//TEST OK ��ȣ�� ����Ͽ� JIG�� ��� ��ġ�� �̵� �ϵ��� �Ѵ�. 
	//���� OK, NG ��ȣ�� PLC�� �����Ͽ� OUT �����Ⱑ ���� �ϵ��� �Ѵ�. 
	//���� ��� ��� ��ö��S ��û ����.
	//���� ����� �ް� NG LABEL �ٿ����ϴ� ������ JIG OUT ��ġ ����. �� ���� ������.
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
				//TEST OK ��ȣ�� ����Ͽ� JIG�� ��� ��ġ�� �̵� �ϵ��� �Ѵ�. 
				//���� OK, NG ��ȣ�� PLC�� �����Ͽ� OUT �����Ⱑ ���� �ϵ��� �Ѵ�.				
				m_pApp->m_pDio7230->Gf_setDioWrite(DIO_GUMI_M5_TEST_OK);//Dio_OutPut(DIO_GUMI_M5_TEST_OK, 1);

				Sleep(500); //PLC�� TEST OK, NG ��ȣ�� ���ÿ� ���� ����� ������ �ϴ� ���������� FLOW�� ���� ���� Delay ��. T/T �� �������

				m_pApp->m_pDio7230->Gf_setDioWrite(DIO_GUMI_M5_JUDGE_NG);//Dio_OutPut(DIO_JUDGE_NG, 1);
				m_pApp->Gf_writeLogData(_T("<DIO>"), _T("OUT -> JUDGE NG"));
				Lf_createCount(BAD_CNT); 
			}
			else if(lpWorkInfo->m_bGieJudgeOk == true || lpWorkInfo->m_nFastJudge == FAST_JUDGE_OK)
			{
				//TEST OK ��ȣ�� ����Ͽ� JIG�� ��� ��ġ�� �̵� �ϵ��� �Ѵ�. 
				//���� OK, NG ��ȣ�� PLC�� �����Ͽ� OUT �����Ⱑ ���� �ϵ��� �Ѵ�.
				m_pApp->m_pDio7230->Gf_setDioWrite(DIO_GUMI_M5_TEST_OK);//Dio_OutPut(DIO_GUMI_M5_TEST_OK, 1);	

				Sleep(500);  //PLC�� TEST OK, NG ��ȣ�� ���ÿ� ���� ����� ������ �ϴ� ���������� FLOW�� ���� ���� Delay ��. T/T �� �������

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
					   // TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
					   // �׸��� �޽����� ���ؼ��� CDialog::OnPaint()��(��) ȣ������ ���ʽÿ�.
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
