#pragma once
#include "afxwin.h"


// CTestReady 대화 상자입니다.
#define TIMER_PID_CHECK		2

class CTestReady : public CDialog
{
	DECLARE_DYNAMIC(CTestReady)

public:
	CTestReady(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CTestReady();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_TEST_READY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedBtnTestStart();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL PreTranslateMessage(MSG* pMsg);

public:	
	CButton m_btnTestStart;

protected:
	void Lf_initFontSet();
	void Lf_initVariable();
	void Lf_updateCount();
	bool Lf_getControlBdReady();
	void Lf_checkPanelId();
	bool Lf_startTest();
	void Lf_openResult();
	void Lf_createCount(int typ);
	BOOL Lf_sendGMESData();
	void Lf_setVariableAfter();

protected:
	LPSYSTEMINFO	lpSystemInfo;
	LPINSPWORKINFO	lpWorkInfo;

private:
	CFont m_Font[FONT_IDX_MAX];
	CBrush m_Brush[COLOR_IDX_MAX];
};
