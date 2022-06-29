#pragma once


// CGieJudge 대화 상자입니다.

class CGieJudge : public CDialog
{
	DECLARE_DYNAMIC(CGieJudge)

public:
	CGieJudge(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CGieJudge();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_GIE_JUDGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
