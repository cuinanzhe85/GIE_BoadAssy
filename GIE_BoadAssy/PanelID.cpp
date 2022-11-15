// PanelID.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "GIE_BoadAssy.h"
#include "PanelID.h"


// CPanelID ��ȭ �����Դϴ�.

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


// CPanelID �޽��� ó�����Դϴ�.

BOOL CPanelID::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_pApp->Gf_writeLogData("<WND>", "Panel ID Input Dialog Open");
	lpSystemInfo	= m_pApp->GetSystemInfo();
	lpModelInfo		= m_pApp->GetModelInfo();
	lpWorkInfo		= m_pApp->GetWorkInfo();

	Lf_InitFont();
	Lf_InitBrush();

	SetTimer(1, 100, NULL);	// EDIT Foucs set
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString strPanelId=_T("");
	BOOL isDataOK = TRUE;
	char cbuff[128]={0,};
	int i=0,len=0;
	WORD wPID[20];
	
	m_edtPanelId.GetWindowText(strPanelId);
	if(((strPanelId.GetLength() < 7) || (strPanelId.GetLength() > 20)) && (strPanelId != _T("ESC")) )
	{
		m_pApp->Gf_ShowMessageBox(_T("<BCR> Panel ID Min 7, Max 20"));
		m_edtPanelId.SetWindowText(_T(""));
		return;
	}
	strPanelId.Replace(_T("\r"), _T(""));
	strPanelId.Replace(_T("\n"), _T(""));

	m_pApp->Gf_writeLogData(_T("<PID INPUT>"), strPanelId.GetBuffer(0));
	wchar_To_char(strPanelId.GetBuffer(0), cbuff);
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
		m_pApp->Gf_ShowMessageBox(_T("<BCR> Incorrected Panel ID"));
		m_edtPanelId.SetSel(0, strPanelId.GetLength());
		return;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// PLC PID Write
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
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
				lpWorkInfo->m_sPID = strPanelId;
				CDialog::OnOK();

				return;
			}
		}
		else
		{
			m_pApp->Gf_ShowMessageBox(_T("<PLC> PLC Panel ID Write Fail"));
		}
	}
	else
	{
		m_pApp->Gf_ShowMessageBox(_T("<PLC> TCP/IP Connection Fail"));
	}
	m_pApp->m_pPlcCtrl->plc_tcpDisConnection();
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
}

void CPanelID::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if(nIDEvent == 1)
	{
		KillTimer(1);
		m_edtPanelId.SetFocus();
	}
	CDialog::OnTimer(nIDEvent);
}


void CPanelID::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDialog::OnCancel();
}


BOOL CPanelID::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
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
					   // TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
					   // �׸��� �޽����� ���ؼ��� CDialog::OnPaint()��(��) ȣ������ ���ʽÿ�.
	CRect rect;
	GetClientRect(&rect);
	dc.FillSolidRect(rect, COLOR_WHITE);

}


HBRUSH CPanelID::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
		if (pWnd->GetDlgCtrlID() == IDC_STT_PID_INPUT_TITLE)
		{
			pDC->SetBkColor(COLOR_BLUISH);
			pDC->SetTextColor(COLOR_WHITE);
			return m_Brush[COLOR_IDX_BLUISH];
		}
	}
	// TODO:  �⺻���� �������� ������ �ٸ� �귯�ø� ��ȯ�մϴ�.
	return hbr;
}
