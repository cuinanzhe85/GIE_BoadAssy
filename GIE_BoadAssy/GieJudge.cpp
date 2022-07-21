// GieJudge.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "GIE_BoadAssy.h"
#include "GieJudge.h"


// CGieJudge ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CGieJudge, CDialog)

CGieJudge::CGieJudge(CWnd* pParent /*=NULL*/)
	: CDialog(CGieJudge::IDD, pParent)
{

}

CGieJudge::~CGieJudge()
{
}

void CGieJudge::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGieJudge, CDialog)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_OK, &CGieJudge::OnBnClickedBtnOk)
	ON_BN_CLICKED(IDC_BTN_NG, &CGieJudge::OnBnClickedBtnNg)
END_MESSAGE_MAP()


// CGieJudge �޽��� ó�����Դϴ�.

BOOL CGieJudge::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	lpSystemInfo	= m_pApp->GetSystemInfo();
	lpModelInfo		= m_pApp->GetModelInfo();
	lpWorkInfo		= m_pApp->GetWorkInfo();

	lpWorkInfo->m_bGieJudgeOk = false;
	lpWorkInfo->m_bGieJudgeNg = false;

	SetTimer(1, 20, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CGieJudge::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}

void CGieJudge::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (nIDEvent == 1)
	{
		if (m_pApp->m_pDio7230->Gf_getDIOJudgeNG() == TRUE)
		{
			KillTimer(nIDEvent);
			lpWorkInfo->m_bGieJudgeNg = true;
			m_pApp->Gf_writeLogData(_T("<DIO>"), _T("JUDGE S/W NG"));
			CDialog::OnCancel();
		}
		if (m_pApp->m_pDio7230->Gf_getDIOJudgeOK() == TRUE)
		{
			KillTimer(nIDEvent);
			lpWorkInfo->m_bGieJudgeOk = true;
			m_pApp->Gf_writeLogData(_T("<DIO>"), _T("JUDGE S/W OK"));
			CDialog::OnCancel();
		}
	}
	CDialog::OnTimer(nIDEvent);
}

void CGieJudge::OnBnClickedBtnOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	KillTimer(1);
	lpWorkInfo->m_bGieJudgeOk = true;
	m_pApp->Gf_writeLogData(_T("<WND>"), _T("GIE JUDGE BUTTORN OK"));
	CDialog::OnCancel();
}

void CGieJudge::OnBnClickedBtnNg()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	KillTimer(1);
	lpWorkInfo->m_bGieJudgeNg = true;
	m_pApp->Gf_writeLogData(_T("<WND>"), _T("GIE JUDGE BUTTORN NG"));
	CDialog::OnCancel();	
}
