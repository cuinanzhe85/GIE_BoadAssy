#pragma once
#include "afxdialogex.h"


typedef struct _ST_BMPDOWNINFO_
{
	int				m_nBmpIndex;		// BMP파일이 저장될 Nand Flash의 Index 번호.

	CString			m_sBmpFileName;		// BMP파일 이름
	CString			m_sBmpFilePath;		// BMP파일 Full Path & 파일이름
	int				m_nBmpFileSize;		// BMP파일 Size
	int				m_nLcmHActive;		// LCM의 Horizontal Active Size
	int				m_nLcmVActive;		// LCM의 Vertical Active Size
	CProgressCtrl* m_pProgress;		// Progress 상태Bar
	CStatic* m_pSttMessage;
}BMPDOWNINFO, * LPBMPDOWNINFO;
// CBmpDownload 대화 상자

class CBmpDownload : public CDialog
{
	DECLARE_DYNAMIC(CBmpDownload)

public:
	CBmpDownload(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CBmpDownload();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BMP_DOWNLOAD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

protected:
	LPMODELSETINFO lpModelInfo;
	LPINSPWORKINFO lpWorkInfo;

	void Lf_InitBmpList();
	void Lf_InitListCtrlStyle();

	void Lf_InitItemFont();
	void Lf_InitColorBrush();

	BOOL Lf_startDownloadBMP(LPBMPDOWNINFO pBmpInfo);
	BOOL Lf_sendBmpHeadData(LPBMPDOWNINFO pBmpInfo);
	BOOL Lf_sendBmpRawData(LPBMPDOWNINFO pBmpInfo);
	BOOL Lf_getDoneCheck();

	CFont m_Font[FONT_IDX_MAX];
	CBrush m_brush[COLOR_IDX_MAX];

public:
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	CListCtrl m_listBmpDownload;
	afx_msg void OnLbnDblclkListBmpTotal();
	CListBox m_listBmpTotal;
	afx_msg void OnBnClickedBtnBmpDelete();
	CProgressCtrl m_progBmpDownloadStatus;
	CStatic m_sttBmpMessage;
	afx_msg void OnBnClickedBtnBmpDownloadStart();
	CStatic m_Image;
	afx_msg void OnLbnSelchangeListBmpTotal();
	afx_msg void OnLvnItemchangedListBmpDownload(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedBtnBmpAdd();
};
