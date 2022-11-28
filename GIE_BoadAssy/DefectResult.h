#pragma once


// CDefectResult 대화 상자
struct DEFECT_BUTTON
{
	CGradientStatic* m_pButtonControl;
	CString m_sButtonName;
	CString m_sButtonReasonCode;
	COLORREF m_ButtonColor;
};


class CDefectResult : public CDialog
{
	DECLARE_DYNAMIC(CDefectResult)

public:
	CDefectResult(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDefectResult();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DEFECT_RESULT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////////////
// 사용자 정의 Function
///////////////////////////////////////////////////////////////////////////
public:
	void Lf_InitLocalValue();
	void Lf_InitFontset();
	void Lf_InitColorBrush();

	void Lf_initStaticButton();
	CGradientStatic* Lf_getStaticControl(int x, int y);
	CString Lf_getStaticButtonName(int x, int y, CString strValue);
	CString Lf_getStaticReasonCode(int x, int y, CString strValue);
	long Lf_getStaticButtonColor(int x, int y, CString strValue);

protected:
	DEFECT_BUTTON m_pDefectButton[10][10];


private:
	CFont m_Font[FONT_IDX_MAX];
	CBrush m_Brush[COLOR_IDX_MAX];

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////





public:
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	CGradientStatic m_sttButton_1to1;
	CGradientStatic m_sttButton_1to2;
	CGradientStatic m_sttButton_1to3;
	CGradientStatic m_sttButton_1to4;
	CGradientStatic m_sttButton_1to5;
	CGradientStatic m_sttButton_1to6;
	CGradientStatic m_sttButton_1to7;
	CGradientStatic m_sttButton_1to8;
	CGradientStatic m_sttButton_1to9;
	CGradientStatic m_sttButton_1to10;
	CGradientStatic m_sttButton_2to1;
	CGradientStatic m_sttButton_2to2;
	CGradientStatic m_sttButton_2to3;
	CGradientStatic m_sttButton_2to4;
	CGradientStatic m_sttButton_2to5;
	CGradientStatic m_sttButton_2to6;
	CGradientStatic m_sttButton_2to7;
	CGradientStatic m_sttButton_2to8;
	CGradientStatic m_sttButton_2to9;
	CGradientStatic m_sttButton_2to10;
	CGradientStatic m_sttButton_3to1;
	CGradientStatic m_sttButton_3to2;
	CGradientStatic m_sttButton_3to3;
	CGradientStatic m_sttButton_3to4;
	CGradientStatic m_sttButton_3to5;
	CGradientStatic m_sttButton_3to6;
	CGradientStatic m_sttButton_3to7;
	CGradientStatic m_sttButton_3to8;
	CGradientStatic m_sttButton_3to9;
	CGradientStatic m_sttButton_3to10;
	CGradientStatic m_sttButton_4to1;
	CGradientStatic m_sttButton_4to2;
	CGradientStatic m_sttButton_4to3;
	CGradientStatic m_sttButton_4to4;
	CGradientStatic m_sttButton_4to5;
	CGradientStatic m_sttButton_4to6;
	CGradientStatic m_sttButton_4to7;
	CGradientStatic m_sttButton_4to8;
	CGradientStatic m_sttButton_4to9;
	CGradientStatic m_sttButton_4to10;
	CGradientStatic m_sttButton_5to1;
	CGradientStatic m_sttButton_5to2;
	CGradientStatic m_sttButton_5to3;
	CGradientStatic m_sttButton_5to4;
	CGradientStatic m_sttButton_5to5;
	CGradientStatic m_sttButton_5to6;
	CGradientStatic m_sttButton_5to7;
	CGradientStatic m_sttButton_5to8;
	CGradientStatic m_sttButton_5to9;
	CGradientStatic m_sttButton_5to10;
	CGradientStatic m_sttButton_6to1;
	CGradientStatic m_sttButton_6to2;
	CGradientStatic m_sttButton_6to3;
	CGradientStatic m_sttButton_6to4;
	CGradientStatic m_sttButton_6to5;
	CGradientStatic m_sttButton_6to6;
	CGradientStatic m_sttButton_6to7;
	CGradientStatic m_sttButton_6to8;
	CGradientStatic m_sttButton_6to9;
	CGradientStatic m_sttButton_6to10;
	CGradientStatic m_sttButton_7to1;
	CGradientStatic m_sttButton_7to2;
	CGradientStatic m_sttButton_7to3;
	CGradientStatic m_sttButton_7to4;
	CGradientStatic m_sttButton_7to5;
	CGradientStatic m_sttButton_7to6;
	CGradientStatic m_sttButton_7to7;
	CGradientStatic m_sttButton_7to8;
	CGradientStatic m_sttButton_7to9;
	CGradientStatic m_sttButton_7to10;
	CGradientStatic m_sttButton_8to1;
	CGradientStatic m_sttButton_8to2;
	CGradientStatic m_sttButton_8to3;
	CGradientStatic m_sttButton_8to4;
	CGradientStatic m_sttButton_8to5;
	CGradientStatic m_sttButton_8to6;
	CGradientStatic m_sttButton_8to7;
	CGradientStatic m_sttButton_8to8;
	CGradientStatic m_sttButton_8to9;
	CGradientStatic m_sttButton_8to10;
	CGradientStatic m_sttButton_9to1;
	CGradientStatic m_sttButton_9to2;
	CGradientStatic m_sttButton_9to3;
	CGradientStatic m_sttButton_9to4;
	CGradientStatic m_sttButton_9to5;
	CGradientStatic m_sttButton_9to6;
	CGradientStatic m_sttButton_9to7;
	CGradientStatic m_sttButton_9to8;
	CGradientStatic m_sttButton_9to9;
	CGradientStatic m_sttButton_9to10;
	CGradientStatic m_sttButton_10to1;
	CGradientStatic m_sttButton_10to2;
	CGradientStatic m_sttButton_10to3;
	CGradientStatic m_sttButton_10to4;
	CGradientStatic m_sttButton_10to5;
	CGradientStatic m_sttButton_10to6;
	CGradientStatic m_sttButton_10to7;
	CGradientStatic m_sttButton_10to8;
	CGradientStatic m_sttButton_10to9;
	CGradientStatic m_sttButton_10to10;
};
