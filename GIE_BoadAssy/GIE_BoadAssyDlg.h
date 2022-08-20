
// GIE_BoadAssyDlg.h : ��� ����
//

#pragma once


// CGIE_BoadAssyDlg ��ȭ ����
class CGIE_BoadAssyDlg : public CDialog
{
// �����Դϴ�.
public:
	CGIE_BoadAssyDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_GIE_BOADASSY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;
	LPSYSTEMINFO	lpSystemInfo;
	LPMODELSETINFO	lpModelInfo;
	LPINSPWORKINFO	lpWorkInfo;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnUpdateSystemInfo(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUdpReceive(WPARAM wParam, LPARAM lParam);
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
	void Lf_InitItemValue();

private:
	CFont m_Font[FONT_IDX_MAX];
	CBrush m_Brush[COLOR_IDX_MAX];	
public:
	afx_msg void OnDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	CStatic m_sttMainFwVerView;
	afx_msg void OnBnClickedBtnBmpDownload();
	afx_msg void OnBnClickedBtnMint();
	CButton m_btnMainUserID;
	CButton m_btnMainMC;
	CButton m_btnMainModel;
	CButton m_btnMainTest;
	CButton m_btnMainMaint;
	CButton m_btnMainSystem;
	CButton m_btnMainInit;
	CButton m_btnMainFW;
	CButton m_btnMainBmp;
	CButton m_btnMainExit;
};
