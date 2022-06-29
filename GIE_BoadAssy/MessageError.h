#pragma once


// CMessageError 대화 상자입니다.

class CMessageError : public CDialog
{
	DECLARE_DYNAMIC(CMessageError)

public:
	CMessageError(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CMessageError();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_MESSAGE_ERROR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL PreTranslateMessage(MSG* pMsg);

public:
	CString m_strEMessage;
	CStatic m_sttErrMessage;
	CButton m_btnErrClose;

protected:
	void Lf_initLocalValue();
	void Lf_initFontset();
	void Lf_initColorBrush();

private:
	CFont mFontH1[FONT_IDX_MAX];
	CBrush Brush[COLOR_IDX_MAX];
public:
	afx_msg void OnBnClickedBtnErrClose();
};
