#pragma once
#include "afxwin.h"


// CPanelID 대화 상자입니다.

class CPanelID : public CDialog
{
	DECLARE_DYNAMIC(CPanelID)

public:
	CPanelID(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CPanelID();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_PANELID };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

protected:
	LPMODELSETINFO	lpModelInfo;
	LPSYSTEMINFO	lpSystemInfo;
	LPINSPWORKINFO	lpWorkInfo;

	void Lf_InitFont();

public:
	afx_msg void OnBnClickedOk();
	CEdit m_edtPanelId;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedCancel();
};
