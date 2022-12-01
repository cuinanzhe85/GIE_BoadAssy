// MessageError.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GIE_BoadAssy.h"
#include "MessageError.h"


// CMessageError 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMessageError, CDialog)

CMessageError::CMessageError(CWnd* pParent /*=NULL*/)
	: CDialog(CMessageError::IDD, pParent)
{

}

CMessageError::~CMessageError()
{
}

void CMessageError::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STT_ERR_MESSAGE, m_sttErrMessage);
	DDX_Control(pDX, IDC_BTN_ERR_CLOSE, m_btnErrClose);
}


BEGIN_MESSAGE_MAP(CMessageError, CDialog)
	ON_WM_DESTROY()
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_ERR_CLOSE, &CMessageError::OnBnClickedBtnErrClose)
END_MESSAGE_MAP()


// CMessageError 메시지 처리기입니다.

BOOL CMessageError::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_pApp->Gf_writeLogData("<WND>", "Message Dialog OPEN");

	Lf_initLocalValue();
	Lf_initFontset();
	Lf_initColorBrush();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CMessageError::OnDestroy()
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

HBRUSH CMessageError::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
		if(pWnd->GetDlgCtrlID()==IDC_STT_ERR_MESSAGE)
		{
			pDC->SetBkColor(COLOR_RED);
			pDC->SetTextColor(COLOR_WHITE);
			return Brush[COLOR_IDX_RED];
		}
		break;
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}

void CMessageError::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialog::OnTimer(nIDEvent);
}

void CMessageError::OnBnClickedBtnErrClose()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_pApp->Gf_writeLogData(_T("<WND>"), _T("Message Dialog Close"));
	CDialog::OnCancel();
}

BOOL CMessageError::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if(pMsg->message == WM_SYSKEYDOWN && pMsg->wParam == VK_F4)
	{
		if (::GetKeyState(VK_MENU)<0)	return TRUE;
	}

	// 일반 Key 동작에 대한 Event
	if (pMsg->message == WM_KEYDOWN)
	{
		switch(pMsg->wParam)
		{
		case VK_ESCAPE:		return 1;
		case VK_RETURN:		return 1;
		case VK_SPACE:		return 1;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CMessageError::Lf_initLocalValue()
{
	m_sttErrMessage.SetWindowText(m_strEMessage);

	m_pApp->Gf_writeLogData(_T("<WND>"), m_strEMessage);
}

void CMessageError::Lf_initFontset()
{
	mFontH1[0].CreateFont(150, 70, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("ARIAL"));

	mFontH1[1].CreateFont(60, 26, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("ARIAL"));

	mFontH1[2].CreateFont(30, 13, 0, 0, FW_BOLD, TRUE, 0, 0, 0, 0, 0, 0, 0, _T("ARIAL"));
	m_btnErrClose.SetFont(&mFontH1[2]);

	mFontH1[3].CreateFont(24, 11, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("ARIAL"));
	m_sttErrMessage.SetFont(&mFontH1[3]);

	mFontH1[4].CreateFont(19, 8, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("ARIAL"));

	mFontH1[5].CreateFont(16, 7, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("ARIAL"));
}

void CMessageError::Lf_initColorBrush()
{
	// 각 Control의 COLOR 설정을 위한 Brush를 Setting 한다.
	Brush[COLOR_IDX_BLACK].CreateSolidBrush (COLOR_BLACK);
	Brush[COLOR_IDX_WHITE].CreateSolidBrush (COLOR_WHITE);
	Brush[COLOR_IDX_RED].CreateSolidBrush (COLOR_RED);
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

