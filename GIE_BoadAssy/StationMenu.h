#pragma once
#include "afxwin.h"


// CStationMenu 대화 상자입니다.

class CStationMenu : public CDialog
{
	DECLARE_DYNAMIC(CStationMenu)

public:
	CStationMenu(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CStationMenu();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_STATION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

	LPSYSTEMINFO	lpSystemInfo;

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedBtnQualitySetup();
	afx_msg void OnBnClickedBtnQualityFtpSetup();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	afx_msg void OnBnClickedBtnSave();

protected:
	void Lf_initControls();
	void Lf_saveSystemInfo();
	void Lf_initFontSet();
	CString Lf_FileLoadDialog(CString Temp);

public:	
	CEdit m_edtEqpName;
	CComboBox m_cboTestMode;
	CComboBox m_cboBluType;
	CEdit m_edtTestStartDelay;
	CComboBox m_cboFastJudge;
	CComboBox m_cboPidNg;
	CComboBox m_cboPgComPort;
	CComboBox m_cboBcrComPort;
	CComboBox m_cboGfd250ComPort;
	CComboBox m_cboBluComPort;
	CEdit m_edtMesServicePort;
	CEdit m_edtMesNetwork;
	CEdit m_edtMesDaemonPort;
	CEdit m_edtMesLocalSubject;
	CEdit m_edtMesRemoteSubject;
	CIPAddressCtrl m_ipaMesLocalIp;

private:
	CFont m_Font[FONT_IDX_MAX];
	CBrush m_Brush[COLOR_IDX_MAX];
public:
	afx_msg void OnBnClickedBtnCancel();
	CEdit m_edtBluFreq;

	CEdit m_edtModFilePath;
	CEdit m_edtPtnFilePath;
	CEdit m_edtEdidFilePath;
	afx_msg void OnBnClickedBtnModFilePath();
	afx_msg void OnBnClickedBtnPtnFilePath();
	afx_msg void OnBnClickedBtnEdidFilePath();
};
