// GieJudge.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GIE_BoadAssy.h"
#include "GieJudge.h"


// CGieJudge 대화 상자입니다.

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


// CGieJudge 메시지 처리기입니다.

BOOL CGieJudge::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	lpSystemInfo	= m_pApp->GetSystemInfo();
	lpModelInfo		= m_pApp->GetModelInfo();
	lpWorkInfo		= m_pApp->GetWorkInfo();

	lpWorkInfo->m_bGieJudgeOk = false;
	lpWorkInfo->m_bGieJudgeNg = false;

	SetTimer(1, 20, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CGieJudge::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

void CGieJudge::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	KillTimer(1);
	lpWorkInfo->m_bGieJudgeOk = true;
	m_pApp->Gf_writeLogData(_T("<WND>"), _T("GIE JUDGE BUTTORN OK"));
	CDialog::OnCancel();
}

void CGieJudge::OnBnClickedBtnNg()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	KillTimer(1);
	lpWorkInfo->m_bGieJudgeNg = true;
	m_pApp->Gf_writeLogData(_T("<WND>"), _T("GIE JUDGE BUTTORN NG"));
	CDialog::OnCancel();	
}
