#pragma once


// CGieJudge ��ȭ �����Դϴ�.

class CGieJudge : public CDialog
{
	DECLARE_DYNAMIC(CGieJudge)

public:
	CGieJudge(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CGieJudge();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_GIE_JUDGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

protected:
	LPMODELSETINFO	lpModelInfo;
	LPSYSTEMINFO	lpSystemInfo;
	LPINSPWORKINFO	lpWorkInfo;
public:
	afx_msg void OnBnClickedBtnOk();
	afx_msg void OnBnClickedBtnNg();
};
