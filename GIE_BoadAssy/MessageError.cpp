// MessageError.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "GIE_BoadAssy.h"
#include "MessageError.h"


// CMessageError ��ȭ �����Դϴ�.

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


// CMessageError �޽��� ó�����Դϴ�.

BOOL CMessageError::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_pApp->Gf_writeLogData("<WND>", "Message Dialog OPEN");

	Lf_initLocalValue();
	Lf_initFontset();
	Lf_initColorBrush();

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CMessageError::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
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
	case CTLCOLOR_STATIC:		// Static, CheckBox control
		if(pWnd->GetDlgCtrlID()==IDC_STT_ERR_MESSAGE)
		{
			pDC->SetBkColor(COLOR_RED);
			pDC->SetTextColor(COLOR_WHITE);
			return Brush[COLOR_IDX_RED];
		}
		break;
	}
	// TODO:  �⺻���� �������� ������ �ٸ� �귯�ø� ��ȯ�մϴ�.
	return hbr;
}

void CMessageError::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CDialog::OnTimer(nIDEvent);
}

void CMessageError::OnBnClickedBtnErrClose()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_pApp->Gf_writeLogData(_T("<WND>"), _T("Message Dialog Close"));
	CDialog::OnCancel();
}

BOOL CMessageError::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	if(pMsg->message == WM_SYSKEYDOWN && pMsg->wParam == VK_F4)
	{
		if (::GetKeyState(VK_MENU)<0)	return TRUE;
	}

	// �Ϲ� Key ���ۿ� ���� Event
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
	// �� Control�� COLOR ������ ���� Brush�� Setting �Ѵ�.
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

