#pragma once
#include "afxdialogex.h"


// CMaint 대화 상자

class CMaint : public CDialog
{
	DECLARE_DYNAMIC(CMaint)

public:
	CMaint(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CMaint();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAINT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

protected:
	LPMODELSETINFO lpModelInfo;
	LPINSPWORKINFO lpWorkInfo;

	unsigned int m_uDioOutBit;

	void Lf_InitItemValue();
	void Lf_initFontSet();
	void Lf_InitBrush();
	void Lf_setCombPatternList();
	BOOL Lf_getPowerMeasureAll();

	CFont m_Font[FONT_IDX_MAX];
	CBrush m_Brush[COLOR_IDX_MAX];
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CButton m_chkDioIn01;
	CButton m_chkDioIn02;
	CButton m_chkDioIn03;
	CButton m_chkDioIn04;
	CButton m_chkDioIn05;
	CButton m_chkDioIn06;
	CButton m_chkDioIn07;
	CButton m_chkDioIn08;
	afx_msg void OnBnClickedCheckDo01();
	afx_msg void OnBnClickedCheckDo02();
	afx_msg void OnBnClickedCheckDo03();
	afx_msg void OnBnClickedCheckDo04();
	afx_msg void OnBnClickedCheckDo05();
	afx_msg void OnBnClickedCheckDo06();
	afx_msg void OnBnClickedCheckDo07();
	afx_msg void OnBnClickedCheckDo08();
	CButton m_chkDioOut01;
	CButton m_chkDioOut02;
	CButton m_chkDioOut03;
	CButton m_chkDioOut04;
	CButton m_chkDioOut05;
	CButton m_chkDioOut06;
	CButton m_chkDioOut07;
	CButton m_chkDioOut08;
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedBtnPowerOn();
	afx_msg void OnBnClickedBtnPowerOff();
	afx_msg void OnCbnSelchangeCmbPatternList();
	CComboBox m_cmbMtPatternList;
	afx_msg void OnBnClickedBtnClose();
	afx_msg void OnBnClickedBtnBluDutySet();
	afx_msg void OnBnClickedBtnBluOn();
	afx_msg void OnBnClickedBtnBluOff();
	afx_msg void OnBnClickedBtnBcrRead();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
};
