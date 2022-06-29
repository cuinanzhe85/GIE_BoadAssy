#pragma once


// CMessageError ��ȭ �����Դϴ�.

class CMessageError : public CDialog
{
	DECLARE_DYNAMIC(CMessageError)

public:
	CMessageError(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CMessageError();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_MESSAGE_ERROR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
