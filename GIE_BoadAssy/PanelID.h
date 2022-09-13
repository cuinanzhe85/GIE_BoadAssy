#pragma once
#include "afxwin.h"


// CPanelID ��ȭ �����Դϴ�.

class CPanelID : public CDialog
{
	DECLARE_DYNAMIC(CPanelID)

public:
	CPanelID(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CPanelID();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_PANELID };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
