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
END_MESSAGE_MAP()


// CPanelID �޽��� ó�����Դϴ�.

BOOL CPanelID::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	lpSystemInfo	= m_pApp->GetSystemInfo();
	lpModelInfo		= m_pApp->GetModelInfo();
	lpWorkInfo		= m_pApp->GetWorkInfo();

	Lf_InitFont();
	SetTimer(1, 100, NULL);	// EDIT Foucs set
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CPanelID::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}
void CPanelID::Lf_InitFont()
{
	CFont m_Font[2];
	m_Font[0].CreateFont(24, 11, 0, 0, FW_SEMIBOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("Segoe UI Symbol"));
	GetDlgItem(IDC_EDT_PID)->SetFont(&m_Font[0]);
	GetDlgItem(IDOK)->SetFont(&m_Font[0]);
	GetDlgItem(IDCANCEL)->SetFont(&m_Font[0]);
}
void CPanelID::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString strPanelId=_T("");
	BOOL isDataOK = FALSE;
	char cbuff[128]={0,};
	int i=0,len=0;
	
	m_edtPanelId.GetWindowText(strPanelId);
	if(((strPanelId.GetLength() < 7) || (strPanelId.GetLength() > 20)) && (strPanelId != _T("ESC")) )
	{
		AfxMessageBox(_T("Panel ID Min 7, Max 20"));
		m_edtPanelId.SetWindowText(_T(""));
		return;
	}

	m_pApp->Gf_writeLogData(_T("<PID INPUT>"), strPanelId.GetBuffer(0));
	wchar_To_char(strPanelId.GetBuffer(0), cbuff);
	len = (int)strlen(cbuff);
	for(i=0; i<len; i++)
	{
		if((('0' <= cbuff[i]) && (cbuff[i] <= '9'))
		|| (('a' <= cbuff[i]) && (cbuff[i] <= 'z'))
		|| (('A' <= cbuff[i]) && (cbuff[i] <= 'Z')) )
		{
			isDataOK = TRUE;
		}
		else
		{
			isDataOK = FALSE;
			break;
		}
	}

	if( isDataOK == FALSE )
	{
		AfxMessageBox(_T("Incorrected Panel ID."));
		m_edtPanelId.SetSel(0, strPanelId.GetLength());
		return;
	}

	lpWorkInfo->m_sPID = strPanelId;
	CDialog::OnOK();
}

void CPanelID::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if(nIDEvent == 1)
	{
		m_edtPanelId.SetFocus();
	}
	CDialog::OnTimer(nIDEvent);
}


void CPanelID::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDialog::OnCancel();
}
