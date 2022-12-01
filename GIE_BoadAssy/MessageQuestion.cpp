// MessageQuestion.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GIE_BoadAssy.h"
#include "MessageQuestion.h"


// CMessageQuestion 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMessageQuestion, CDialog)

CMessageQuestion::CMessageQuestion(CWnd* pParent /*=NULL*/)
	: CDialog(CMessageQuestion::IDD, pParent)
{
	m_nMessageColor = 0;
}

CMessageQuestion::~CMessageQuestion()
{
}

void CMessageQuestion::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STT_MSG_MESSAGE, m_sttMsgMessage);
	DDX_Control(pDX, IDC_BTN_MSG_CONFIRM, m_btnMsgConfirm);
	DDX_Control(pDX, IDC_BTN_MSG_CLOSE, m_btnMsgClose);
}


BEGIN_MESSAGE_MAP(CMessageQuestion, CDialog)
	ON_WM_DESTROY()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_MSG_CONFIRM, &CMessageQuestion::OnBnClickedBtnMsgConfirm)
	ON_BN_CLICKED(IDC_BTN_MSG_CLOSE, &CMessageQuestion::OnBnClickedBtnMsgClose)
END_MESSAGE_MAP()


// CMessageQuestion 메시지 처리기입니다.

BOOL CMessageQuestion::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_pApp->Gf_writeLogData("<WND>", "Question Dialog OPEN");

	Lf_initLocalValue();
	Lf_initFontset();
	Lf_initColorBrush();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CMessageQuestion::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	for(int i=0; i<COLOR_IDX_MAX; i++)
	{
		Brush[i].DeleteObject();
	}

	for(int i=0; i<FONT_IDX_MAX; i++)
	{
		mFontH1[i].DeleteObject();
	}
}

HBRUSH CMessageQuestion::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
	case CTLCOLOR_STATIC:		// Static, CheckBox control
		if(pWnd->GetDlgCtrlID()==IDC_STT_MSG_MESSAGE)
		{
			if (m_nMessageColor == 0)
			{
				pDC->SetBkColor(COLOR_JADEGREEN);
				pDC->SetTextColor(COLOR_BLACK);
				return Brush[COLOR_IDX_JADEGREEN];
			}
			else
			{
				pDC->SetBkColor(COLOR_RED128);
				pDC->SetTextColor(COLOR_WHITE);
				return Brush[COLOR_IDX_RED128];
			}
		}
		break;
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}

void CMessageQuestion::OnBnClickedBtnMsgConfirm()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_pApp->Gf_writeLogData(_T("<WND>"), _T("Question Dialog Confirm"));
	CDialog::OnOK();
}

void CMessageQuestion::OnBnClickedBtnMsgClose()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_pApp->Gf_writeLogData(_T("<WND>"), _T("Question Dialog Cancel"));
	CDialog::OnCancel();
}

void CMessageQuestion::Lf_initLocalValue()
{
	m_sttMsgMessage.SetWindowText(m_strQMessage);

	m_pApp->Gf_writeLogData(_T("<WND>"), m_strQMessage);

	if(m_strLButton.IsEmpty() == FALSE)
		m_btnMsgConfirm.SetWindowText(m_strLButton);

	if(m_strRButton.IsEmpty() == FALSE)
		m_btnMsgClose.SetWindowText(m_strRButton);
}

void CMessageQuestion::Lf_initFontset()
{
	mFontH1[0].CreateFont(150, 70, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("ARIAL"));

	mFontH1[1].CreateFont(60, 26, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("ARIAL"));

	mFontH1[2].CreateFont(30, 13, 0, 0, FW_BOLD, TRUE, 0, 0, 0, 0, 0, 0, 0, _T("ARIAL"));
	m_btnMsgConfirm.SetFont(&mFontH1[2]);
	m_btnMsgClose.SetFont(&mFontH1[2]);

	mFontH1[3].CreateFont(24, 11, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("ARIAL"));
	m_sttMsgMessage.SetFont(&mFontH1[3]);

	mFontH1[4].CreateFont(19, 8, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("ARIAL"));

	mFontH1[5].CreateFont(16, 7, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("ARIAL"));
}

void CMessageQuestion::Lf_initColorBrush()
{
	// 각 Control의 COLOR 설정을 위한 Brush를 Setting 한다.
	Brush[COLOR_IDX_BLACK].CreateSolidBrush (COLOR_BLACK);
	Brush[COLOR_IDX_WHITE].CreateSolidBrush (COLOR_WHITE);
	Brush[COLOR_IDX_RED].CreateSolidBrush (COLOR_RED);
	Brush[COLOR_IDX_RED128].CreateSolidBrush(COLOR_RED128);
	Brush[COLOR_IDX_GREEN].CreateSolidBrush (COLOR_GREEN);
	Brush[COLOR_IDX_BLUE].CreateSolidBrush (COLOR_BLUE);
	Brush[COLOR_IDX_JADEGREEN].CreateSolidBrush (COLOR_JADEGREEN);
	Brush[COLOR_IDX_LIGHT_RED].CreateSolidBrush (COLOR_LIGHT_RED);
	Brush[COLOR_IDX_LIGHT_GREEN].CreateSolidBrush (COLOR_LIGHT_GREEN);
	Brush[COLOR_IDX_LIGHT_BLUE].CreateSolidBrush (COLOR_LIGHT_BLUE);
	Brush[COLOR_IDX_LIGHT_ORANGE].CreateSolidBrush (COLOR_LIGHT_ORANGE);
	Brush[COLOR_IDX_DARK_RED].CreateSolidBrush (COLOR_DARK_RED);
	Brush[COLOR_IDX_DARK_ORANGE].CreateSolidBrush (COLOR_DARK_ORANGE);
	Brush[COLOR_IDX_GRAY224].CreateSolidBrush (COLOR_GRAY224);
}