#pragma once
#include "afxwin.h"


// CMessageQuestion 대화 상자입니다.

class CMessageQuestion : public CDialog
{
	DECLARE_DYNAMIC(CMessageQuestion)

public:
	CMessageQuestion(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CMessageQuestion();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_MESSAGE_QUESTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedBtnMsgConfirm();
	afx_msg void OnBnClickedBtnMsgClose();

public:
	CString m_strQMessage;
	CString m_strLButton;
	CString m_strRButton;
	CStatic m_sttMsgMessage;
	CButton m_btnMsgConfirm;
	CButton m_btnMsgClose;

protected:
	void Lf_initLocalValue();
	void Lf_initFontset();
	void Lf_initColorBrush();

private:
	CFont mFontH1[FONT_IDX_MAX];
	CBrush Brush[COLOR_IDX_MAX];
};
