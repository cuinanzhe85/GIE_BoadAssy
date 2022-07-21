
// GIE_BoadAssyDlg.h : 헤더 파일
//

#pragma once


// CGIE_BoadAssyDlg 대화 상자
class CGIE_BoadAssyDlg : public CDialog
{
// 생성입니다.
public:
	CGIE_BoadAssyDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_GIE_BOADASSY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;
	LPSYSTEMINFO	lpSystemInfo;
	LPMODELSETINFO	lpModelInfo;
	LPINSPWORKINFO	lpWorkInfo;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnUpdateSystemInfo(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedBtnUserid();
	afx_msg void OnBnClickedBtnModelChange();
	afx_msg void OnBnClickedBtnModelinfo();
	afx_msg void OnBnClickedBtnTest();
	afx_msg void OnBnClickedBtnSystem();	
	afx_msg void OnBnClickedBtnInitialize();
	afx_msg void OnBnClickedBtnAutofirmware();
	afx_msg void OnBnClickedBtnExit();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

protected:
	void Lf_InitFontSet();

private:
	CFont m_Font[FONT_IDX_MAX];
	CBrush m_Brush[COLOR_IDX_MAX];	
public:
	afx_msg void OnDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
};
