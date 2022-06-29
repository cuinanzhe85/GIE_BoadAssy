#pragma once


// CInitialize ��ȭ �����Դϴ�.
#define ST_SYS		0
#define ST_MOD		1
#define ST_PTN		2
#define ST_EDID		3
#define ST_IRDA		4
#define ST_GFD250	5
#define ST_BCR		6
#define ST_LED_BLU	7


class CInitialize : public CDialog
{
	DECLARE_DYNAMIC(CInitialize)

public:
	CInitialize(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CInitialize();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_INITIALIZE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

protected:
	void Lf_initFontSet();
	void Lf_loadData();

protected:
	LPMODELSETINFO	lpModelInfo;

	int m_nChkPoint;
	int m_nStatus[20];
public:
	afx_msg void OnBnClickedBtnRetry();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();

private:
	CFont m_Font[FONT_IDX_MAX];
	CBrush m_Brush[COLOR_IDX_MAX];
};
