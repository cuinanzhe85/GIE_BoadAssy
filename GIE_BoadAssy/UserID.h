#pragma once
#include "afxwin.h"


// CUserID 대화 상자입니다.

class CUserID : public CDialog
{
	DECLARE_DYNAMIC(CUserID)

public:
	CUserID(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CUserID();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_USERID };

	

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	CEdit m_edtInputId;
	afx_msg void OnBnClickedOk();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();

protected:
	void Lf_initFont();

protected:
	LPMODELSETINFO	lpModelInfo;
	LPSYSTEMINFO	lpSystemInfo;
	LPINSPWORKINFO	lpWorkInfo;	

private:
	CFont m_Font[FONT_IDX_MAX];
	CBrush m_Brush[COLOR_IDX_MAX];


};
