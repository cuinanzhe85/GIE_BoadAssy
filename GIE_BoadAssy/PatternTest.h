#pragma once
#include "afxcmn.h"


// CPatternTest ��ȭ �����Դϴ�.

class CPatternTest : public CDialog
{
	DECLARE_DYNAMIC(CPatternTest)

public:
	CPatternTest(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CPatternTest();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_PATTERN_TEST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

protected:
	LPMODELSETINFO	lpModelInfo;
	LPSYSTEMINFO	lpSystemInfo;
	LPINSPWORKINFO	lpWorkInfo;

	int m_nSelNum;
	CString m_sTackTime;
	int m_nInspTackTime;
	int m_nInspStartTime;

protected:
	void RemoveMessageFromQueue();
	bool Lf_checkMicroPattern();
	void Lf_sendPtnData();
	BOOL Lf_sendBluData();
	void Lf_sendPatternBluData();
	BOOL Lf_updateMeasureInfo();
	void Lf_excutePatternList(MSG* pMsg);
	void Lf_insertListColum();
	void Lf_insertListItem();
	void Lf_compareEEPRomData();
	BOOL Lf_cmpEdidData();
	void Lf_showDisplayLockTimeText();
	void Lf_initFontSet();
	void Lf_initVariable();
	void Lf_setPatternGrayLevel(int wParam);
	void Lf_getPatternGrayLevel(CString strPattern, int* r_level, int* g_level, int* b_level);

	void Lf_PtnTestEventView(CString Event);
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CListCtrl m_LCctrlPtnTestView;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);

private:
	CFont m_Font[FONT_IDX_MAX];
	CBrush m_Brush[COLOR_IDX_MAX];
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	CListBox m_listPtnTestEvent;
};
