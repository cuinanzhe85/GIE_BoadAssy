#pragma once
#include "afxwin.h"


// CUserID ��ȭ �����Դϴ�.

class CUserID : public CDialog
{
	DECLARE_DYNAMIC(CUserID)

public:
	CUserID(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CUserID();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_USERID };

	

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
