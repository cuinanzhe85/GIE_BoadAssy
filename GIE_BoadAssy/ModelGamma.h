#pragma once
#include "afxdialogex.h"


// CModelGamma 대화 상자

class CModelGamma : public CDialog
{
	DECLARE_DYNAMIC(CModelGamma)

public:
	CModelGamma(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CModelGamma();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MODEL_GAMMA };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

protected:
	LPMODELSETINFO lpModelInfo;
	LPSYSTEMINFO	lpSystemInfo;

	void Lf_initFontSet();
	void Lf_InitBrush();
	void Lf_InitItemDataSet();

	CFont m_Font[FONT_IDX_MAX];
	CBrush m_Brush[COLOR_IDX_MAX];

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnSave();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedBtnClose();
	afx_msg void OnDestroy();
	afx_msg void OnPaint();

	CEdit m_edtPowerGammaCh01;
	CEdit m_edtPowerGammaCh02;
	CEdit m_edtPowerGammaCh03;
	CEdit m_edtPowerGammaCh04;
	CEdit m_edtPowerGammaCh05;
	CEdit m_edtPowerGammaCh06;
	CEdit m_edtPowerGammaCh07;
	CEdit m_edtPowerGammaCh08;
	CEdit m_edtPowerGammaCh09;
	CEdit m_edtPowerGammaCh10;
	CEdit m_edtPowerGammaCh11;
	CEdit m_edtPowerGammaCh12;
	CEdit m_edtPowerGammaCh13;
	CEdit m_edtPowerGammaCh14;
	CEdit m_edtPowerGammaCh15;
	CEdit m_edtPowerGammaCh16;
	CEdit m_edtPowerGammaCh17;
	CEdit m_edtPowerGammaCh18;
	CEdit m_edtPowerGammaCh19;
	CEdit m_edtPowerGammaCh20;
	CEdit m_edtPowerGammaCh21;
	CEdit m_edtPowerGammaCh22;
	CEdit m_edtPowerGammaCh23;
	CEdit m_edtPowerGammaCh24;
	CEdit m_edtPowerGammaCh25;
	CEdit m_edtPowerGammaCh26;
	CEdit m_edtPowerGammaCh27;
	CEdit m_edtPowerGammaCh28;
	CEdit m_edtPowerGammaCh29;
	CEdit m_edtPowerGammaCh30;
	CEdit m_edtPowerGammaCh31;
	CEdit m_edtPowerGammaCh32;
	
};
