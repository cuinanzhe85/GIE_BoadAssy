#pragma once
#include "afxwin.h"


// CModelChange 대화 상자입니다.

class CModelChange : public CDialog
{
	DECLARE_DYNAMIC(CModelChange)

public:
	CModelChange(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CModelChange();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_MODEL_CHANGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();

protected:
	LPMODELSETINFO	lpModelInfo;
	LPSYSTEMINFO	lpSystemInfo;

protected:
	void Lf_initLoadModelList();
	void Lf_initFont();

public:
	CListBox m_lcModelList;
	afx_msg void OnBnClickedBtnLoad();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();

private:
	CFont m_Font[FONT_IDX_MAX];
	CBrush m_Brush[COLOR_IDX_MAX];

};
