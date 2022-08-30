// UserID.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "GIE_BoadAssy.h"
#include "UserID.h"


// CUserID ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CUserID, CDialog)

CUserID::CUserID(CWnd* pParent /*=NULL*/)
	: CDialog(CUserID::IDD, pParent)
{

}

CUserID::~CUserID()
{
}

void CUserID::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_INPUT_ID, m_edtInputId);
}


BEGIN_MESSAGE_MAP(CUserID, CDialog)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDOK, &CUserID::OnBnClickedOk)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CUserID �޽��� ó�����Դϴ�.

BOOL CUserID::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	lpSystemInfo	= m_pApp->GetSystemInfo();
	lpModelInfo		= m_pApp->GetModelInfo();
	lpWorkInfo		= m_pApp->GetWorkInfo();

	Lf_initFont();

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CUserID::OnDestroy()
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

void CUserID::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString	m_sUserId=_T("");
	UpdateData ();

	GetDlgItem(IDOK)->EnableWindow(FALSE);
	m_pApp->m_bMesComuCheck = true;

	m_edtInputId.GetWindowText(m_sUserId);

	if(m_sUserId.IsEmpty() == FALSE)
	{
		m_pApp->m_bUserIdCheck = false;
		m_pApp->m_bUserIdPM = false;
		m_pApp->m_bUserIdGieng = false;

		if((!m_sUserId.Compare(_T("GIENG"))) || (!m_sUserId.Compare(_T("gieng"))))
		{
			m_sUserId.MakeUpper();			
			lpWorkInfo->m_sUserID.Format(_T("%s"), m_sUserId);
			lpWorkInfo->m_sUserName.Empty();

			m_pApp->m_bUserIdCheck = true;
			m_pApp->m_bMesComuCheck = false;
			m_pApp->m_bUserIdGieng = true;
			m_pApp->Gf_writeLogData(_T("USER ID"),m_sUserId.GetBuffer(0));
			CDialog::OnOK();
		}
		else if((!m_sUserId.Compare(_T("PM"))) || (!m_sUserId.Compare(_T("pm"))))
		{
			m_sUserId.MakeUpper();
			lpWorkInfo->m_sUserID.Format(_T("%s"), m_sUserId);
			lpWorkInfo->m_sUserName.Empty();

			m_pApp->m_bUserIdCheck = true;
			m_pApp->m_bMesComuCheck = false;
			m_pApp->m_bUserIdPM = true;
			m_pApp->Gf_writeLogData(_T("USER ID"),m_sUserId.GetBuffer(0));
			CDialog::OnOK();
		}
		else
		{
			if (m_pApp->m_bIsGmesConnect == FALSE)
			{
				if (m_pApp->Gf_gmesConnect(SERVER_MES) == FALSE)
				{
					//AfxMessageBox(_T("MES CONNECTION FAIL - MES can not be connected."), MB_ICONERROR);
					m_pApp->Gf_writeLogData("<MES>", "Connection Fail");
				}
			}
			
			if(m_sUserId.GetLength() > 4)
			{
				if(m_pApp->Gf_sendGmesHost(HOST_EAYT)==FALSE)	
				{
//						m_pApp->m_bHostComuChk = FALSE;
					GetDlgItem(IDOK)->EnableWindow(TRUE);
					return;
				}
			
				m_pApp->m_pCimNet->SetUserId(m_sUserId);
				lpWorkInfo->m_sUserID.Format(_T("%s"), m_sUserId);					

				if(m_pApp->Gf_sendGmesHost(HOST_UCHK)==FALSE)
				{
//						m_pApp->m_bHostComuChk = FALSE;
					GetDlgItem(IDOK)->EnableWindow(TRUE);
					return;
				}
				if(m_pApp->Gf_sendGmesHost(HOST_EDTI)==FALSE)
				{
//						m_pApp->m_bHostComuChk = FALSE;
					GetDlgItem(IDOK)->EnableWindow(TRUE);
					return;
				}
// 					m_pApp->m_bUserIdCheck = TRUE;
// 					m_pApp->Gf_writeLogData(_T("UserID"), m_pApp->m_pTibDrive->m_sTibUserId);
// 
// 					if((m_pApp->m_bPgmStart == FALSE) && (m_pApp->m_bFldrSendOn == TRUE))
// 					{
// 						CString strBuff;
// 						if((m_pApp->m_bUserIdGieng == FALSE) && (m_pApp->m_bUserIdPM == FALSE))
// 						{
// 						}
// 					}
// 					m_pApp->m_bFldrSendOn = TRUE;

				CDialog::OnOK();
			}
			else
			{
				MessageBox(_T("Input again 'UserID'"));
				GetDlgItem (IDC_EDIT_INPUT_ID)->SetWindowText (_T(""));
			}
		}
	}
	GetDlgItem(IDC_EDIT_INPUT_ID)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(TRUE);
}

BOOL CUserID::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	if ((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == 0x1b))
	{
		return 1;
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void CUserID::Lf_initFont()
{
	m_Font[0].CreateFont( 150, 70, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("ARIAL"));

	m_Font[1].CreateFont( 60, 26, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("Segoe UI Symbol"));
	GetDlgItem(IDC_STT_USERDLG_TIT)->SetFont(&m_Font[1]);

	m_Font[2].CreateFont( 60, 18, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("ARIAL"));

	m_Font[3].CreateFont( 19, 8, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("Segoe UI Symbol"));

	m_Font[4].CreateFont( 16, 6, 0, 0, FW_SEMIBOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("Segoe UI Symbol"));

	m_Font[5].CreateFont( 36, 16, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0,_T("Segoe UI Symbol"));
	GetDlgItem(IDC_STT_USERID_TIT)->SetFont(&m_Font[5]);
	GetDlgItem(IDC_EDIT_INPUT_ID)->SetFont(&m_Font[5]);
	GetDlgItem(IDOK)->SetFont(&m_Font[5]);

	m_Brush[COLOR_IDX_ORANGE].CreateSolidBrush (COLOR_ORANGE);
	m_Brush[COLOR_IDX_GRAY240].CreateSolidBrush (COLOR_GRAY240);
	m_Brush[COLOR_IDX_DEEP_BLUE].CreateSolidBrush (COLOR_DEEP_BLUE);
	m_Brush[COLOR_IDX_GRAY127].CreateSolidBrush (COLOR_GRAY127);
	m_Brush[COLOR_IDX_GRAY96].CreateSolidBrush (COLOR_GRAY96);
	m_Brush[COLOR_IDX_GRAY64].CreateSolidBrush(COLOR_GRAY64);
}

HBRUSH CUserID::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
		if(pWnd->GetDlgCtrlID()==IDC_STT_USERDLG_TIT)
		{
			pDC->SetBkColor(COLOR_DEEP_BLUE);
			pDC->SetTextColor(COLOR_WHITE);
			return m_Brush[COLOR_IDX_DEEP_BLUE];
		}

		if (pWnd->GetDlgCtrlID() == IDC_STT_USERID_TIT)
		{
			pDC->SetBkColor(COLOR_GRAY64);
			pDC->SetTextColor(COLOR_WHITE);
			return m_Brush[COLOR_IDX_GRAY64];
		}
		break;
	}	
	// TODO:  �⺻���� �������� ������ �ٸ� �귯�ø� ��ȯ�մϴ�.
	return hbr;
}

void CUserID::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	// �׸��� �޽����� ���ؼ��� CDialog::OnPaint()��(��) ȣ������ ���ʽÿ�.
	CRect rect;

	GetClientRect(&rect);
	rect.bottom=90;
	dc.FillSolidRect(rect,COLOR_DEEP_BLUE);

	GetClientRect(&rect);
	rect.top = 90;
	rect.bottom = 91;
	dc.FillSolidRect(rect, COLOR_GREEN);

	GetClientRect(&rect);
	rect.top = 92;
	dc.FillSolidRect(rect, COLOR_GRAY64);
}
