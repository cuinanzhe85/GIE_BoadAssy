// PanelID.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GIE_BoadAssy.h"
#include "PanelID.h"


// CPanelID 대화 상자입니다.

IMPLEMENT_DYNAMIC(CPanelID, CDialog)

CPanelID::CPanelID(CWnd* pParent /*=NULL*/)
	: CDialog(CPanelID::IDD, pParent)
{

}

CPanelID::~CPanelID()
{
}

void CPanelID::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDT_PID, m_edtPanelId);
}


BEGIN_MESSAGE_MAP(CPanelID, CDialog)
	ON_BN_CLICKED(IDOK, &CPanelID::OnBnClickedOk)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDCANCEL, &CPanelID::OnBnClickedCancel)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CPanelID 메시지 처리기입니다.

BOOL CPanelID::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_pApp->Gf_writeLogData("<WND>", "Panel ID Input Dialog Open");
	lpSystemInfo	= m_pApp->GetSystemInfo();
	lpModelInfo		= m_pApp->GetModelInfo();
	lpWorkInfo		= m_pApp->GetWorkInfo();

	Lf_InitValue();
	Lf_InitFont();
	Lf_InitBrush();

	SetTimer(1, 100, NULL);	// EDIT Foucs set
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CPanelID::OnDestroy()
{
	CDialog::OnDestroy();
	for (int i = 0; i < COLOR_IDX_MAX; i++)
	{
		m_Brush[i].DeleteObject();
	}

	for (int i = 0; i < FONT_IDX_MAX; i++)
	{
		m_Font[i].DeleteObject();
	}
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

void CPanelID::Lf_InitValue()
{
	if (lpModelInfo->m_nIdInputType == ID_TYPE_PID)
		GetDlgItem(IDC_STT_PID_INPUT_TITLE)->SetWindowText(_T("PID INPUT"));
	else if (lpModelInfo->m_nIdInputType == ID_TYPE_SERIAL_NO)
		GetDlgItem(IDC_STT_PID_INPUT_TITLE)->SetWindowText(_T("SERIAL NO INPUT"));
	else if (lpModelInfo->m_nIdInputType == ID_TYPE_PCBID)
		GetDlgItem(IDC_STT_PID_INPUT_TITLE)->SetWindowText(_T("PCB ID INPUT"));

}

void CPanelID::Lf_InitFont()
{
	
	m_Font[0].CreateFont(30, 13, 0, 0, FW_SEMIBOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("Segoe UI Symbol"));
	GetDlgItem(IDC_EDT_PID)->SetFont(&m_Font[0]);
	GetDlgItem(IDOK)->SetFont(&m_Font[0]);
	GetDlgItem(IDCANCEL)->SetFont(&m_Font[0]);

	m_Font[1].CreateFont(60, 26, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("Segoe UI Symbol"));
	GetDlgItem(IDC_STT_PID_INPUT_TITLE)->SetFont(&m_Font[1]);
}
void CPanelID::Lf_InitBrush()
{
	
	m_Brush[COLOR_IDX_ORANGE].CreateSolidBrush(COLOR_ORANGE);
	m_Brush[COLOR_IDX_RED].CreateSolidBrush(COLOR_RED);
	m_Brush[COLOR_IDX_BLACK].CreateSolidBrush(COLOR_BLACK);
	m_Brush[COLOR_IDX_GRAY64].CreateSolidBrush(COLOR_GRAY64);
	m_Brush[COLOR_IDX_GRAY94].CreateSolidBrush(COLOR_GRAY94);
	m_Brush[COLOR_IDX_LIGHT_GREEN].CreateSolidBrush(COLOR_LIGHT_GREEN);
	m_Brush[COLOR_IDX_WHITE].CreateSolidBrush(COLOR_WHITE);
	m_Brush[COLOR_IDX_DEEP_BLUE].CreateSolidBrush(COLOR_DEEP_BLUE);
	m_Brush[COLOR_IDX_CYAN].CreateSolidBrush(COLOR_CYAN);
	m_Brush[COLOR_IDX_BLUISH].CreateSolidBrush(COLOR_BLUISH);
}

void CPanelID::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sLog, sdata;
	CString strInputID=_T("");
	BOOL isDataOK = TRUE;
	char cbuff[128]={0,};
	int i=0,len=0;
	WORD wPID[20];

	int len_min, len_max;
	if (lpModelInfo->m_nIdInputType == ID_TYPE_PID)
	{
		len_min = 7;
		len_max = 20;
	}
	else if (lpModelInfo->m_nIdInputType == ID_TYPE_SERIAL_NO)
	{
		len_min = 7;
		len_max = 20;
	}
	else if (lpModelInfo->m_nIdInputType == ID_TYPE_PCBID)
	{
		len_min = 7;
		len_max = 20;
	}

	m_edtPanelId.GetWindowText(strInputID);
	if(((strInputID.GetLength() < len_min) || (strInputID.GetLength() > len_max)) && (strInputID != _T("ESC")) )
	{
		sdata.Format(_T("<BCR> ID Range Min 7, Max 20"));
		m_pApp->Gf_ShowMessageBox(sdata);
		m_edtPanelId.SetWindowText(_T(""));
		return;
	}
	strInputID.Replace(_T("\r"), _T(""));
	strInputID.Replace(_T("\n"), _T(""));

	sLog.Format(_T("ID Input Data : %s"), strInputID);
	m_pApp->Gf_writeLogData(_T("<BCR>"), sLog);
	wchar_To_char(strInputID.GetBuffer(0), cbuff);
	len = (int)strlen(cbuff);
	for(i=0; i<len; i++)
	{
		if((('0' <= cbuff[i]) && (cbuff[i] <= '9'))
		|| (('a' <= cbuff[i]) && (cbuff[i] <= 'z'))
		|| (('A' <= cbuff[i]) && (cbuff[i] <= 'Z')) )
		{
		}
		else
		{
			isDataOK = FALSE;
			break;
		}
	}

	if( isDataOK == FALSE )
	{
		m_pApp->Gf_ShowMessageBox(_T("<BCR> Incorrected ID data"));
		m_edtPanelId.SetSel(0, strInputID.GetLength());
		return;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// PLC PID Write
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (lpSystemInfo->m_nPlcDeviceUse == TRUE)
	{
		memset(wPID, 0x00, sizeof(wPID));
		memcpy(wPID, cbuff, strlen(cbuff));
		m_pApp->m_pPlcCtrl->plc_tcpDisConnection();
		delayMS(200);
		if (m_pApp->m_pPlcCtrl->plc_tcpConnection() == TRUE)
		{
			if (m_pApp->m_pPlcCtrl->plc_sendInputPID(lpSystemInfo->m_nPlcDeviceNum, wPID, len) == TRUE)
			{
				m_pApp->Gf_writeLogData(_T("<PLC>"), _T("PLC Panel ID Write Success"));

				m_pApp->m_pPlcCtrl->plc_sendPidWriteComplete(lpSystemInfo->m_nPlcDeviceNum, _SET_);
				delayMS(500);
				if (m_pApp->m_pPlcCtrl->plc_sendPidWriteComplete(lpSystemInfo->m_nPlcDeviceNum, _CLEAR_) == TRUE)
				{
					m_pApp->Gf_writeLogData(_T("<PLC>"), _T("PLC Panel ID Write Complete Bit ON"));
				}
				else
				{
					m_pApp->Gf_ShowMessageBox(_T("<PLC> PLC Panel ID Write Complete Bit ON => Fail"));
					return;
				}
			}
			else
			{
				m_pApp->Gf_ShowMessageBox(_T("<PLC> PLC Panel ID Write Fail"));
				return;
			}
		}
		else
		{
			m_pApp->Gf_ShowMessageBox(_T("<PLC> TCP/IP Connection Fail"));
			return;
		}
		m_pApp->m_pPlcCtrl->plc_tcpDisConnection();
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	lpWorkInfo->m_sPanelID.Empty();
	lpWorkInfo->m_sSerialNumber.Empty();
	lpWorkInfo->m_sPcbID.Empty();

	if (lpModelInfo->m_nIdInputType == ID_TYPE_PID)					lpWorkInfo->m_sPanelID = strInputID;
	else if (lpModelInfo->m_nIdInputType == ID_TYPE_SERIAL_NO)		lpWorkInfo->m_sSerialNumber = strInputID;
	else if (lpModelInfo->m_nIdInputType == ID_TYPE_PCBID)			lpWorkInfo->m_sPcbID = strInputID;

	CDialog::OnOK();
}

void CPanelID::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if(nIDEvent == 1)
	{
		KillTimer(1);
		m_edtPanelId.SetFocus();
	}
	CDialog::OnTimer(nIDEvent);
}


void CPanelID::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialog::OnCancel();
}


BOOL CPanelID::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_RETURN:
		{
			OnBnClickedOk();
			return TRUE;
		}
		case VK_ESCAPE:
		{
			CDialog::OnCancel();
			return TRUE;
		}
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}


void CPanelID::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialog::OnPaint()을(를) 호출하지 마십시오.
	CRect rect;
	GetClientRect(&rect);
	dc.FillSolidRect(rect, COLOR_WHITE);

}


HBRUSH CPanelID::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
		if (pWnd->GetDlgCtrlID() == IDC_STT_PID_INPUT_TITLE)
		{
			pDC->SetBkColor(COLOR_BLUISH);
			pDC->SetTextColor(COLOR_WHITE);
			return m_Brush[COLOR_IDX_BLUISH];
		}
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}
