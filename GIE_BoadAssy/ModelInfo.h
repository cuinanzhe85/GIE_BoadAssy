#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CModelInfo ��ȭ �����Դϴ�.

class CModelInfo : public CDialog
{
	DECLARE_DYNAMIC(CModelInfo)

public:
	CModelInfo(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CModelInfo();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_MODEL_INFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	CComboBox m_cboSignalType;
	CComboBox m_cboSignalBit;
	CComboBox m_cboCurEmp;
	CComboBox m_cboLvdsSel;
	CComboBox m_cboBitSel;
	CComboBox m_cboBistOnOff;
	CComboBox m_cboInterface;
	CComboBox m_cboHsyncPol;
	CComboBox m_cboVsyncPol;
	CComboBox m_cboBitSwap;
	CComboBox m_cboClkIncDec;
	CComboBox m_cboClkInv;
	CEdit m_edtHorTotal;
	CEdit m_edtHorActive;
	CEdit m_edtHorWidth;
	CEdit m_edtHorFrontPor;
	CEdit m_edtHorBackPor;
	CEdit m_edtVerTotal;
	CEdit m_edtVerActive;
	CEdit m_edtVerWidth;
	CEdit m_edtVerFrontPor;
	CEdit m_edtVerBackPor;
	CEdit m_edtFreq;
	CEdit m_edtVccSet;
	CEdit m_edtVddSet;
	CEdit m_edtVccHighLimitSet;
	CEdit m_edtVddHighLimitSet;
	CEdit m_edtIccHighLimitSet;
	CEdit m_edtIddHighLimitSet;
	CEdit m_edtIccCheck;
	CComboBox m_cboPowerSeqSel;
	CEdit m_edtPwrSeqDelay;
	CComboBox m_cboEdidOnOff;
	CComboBox m_cboEdidSize;
	CComboBox m_cboEdidLine;
	CComboBox m_cboEepType;
	CComboBox m_cboVcomLine;
	CComboBox m_cboVcomAddr;
	CComboBox m_cboVcomBitShift;
	CEdit m_edtVcomMin;
	CEdit m_edtVcomMax;
	CEdit m_edtVcomDrop;
	CEdit m_edtVcomDefault;
	CComboBox m_cboGfd100OnOff;
	CComboBox m_cboSolomonMipi;
	CComboBox m_cboInitCode;
	CEdit m_edtMicroPtnCnt;
	CEdit m_edtBluMin;
	CComboBox m_cboSpiOnOff;
	CComboBox m_cboSpiLevel;

protected:
	void Lf_initItemValue();
	void Lf_initFontSet();
	void Lf_loadModelData();
	void Lf_saveCtrlData(CString modelName);
	void Lf_setPatternList();
	void Lf_insertListColum();
	void Lf_setSwapData(int pos1, int pos2);
	void Lf_setPtnDataChange(int sel);
	void Lf_setChangeFont();

protected:
	LPMODELSETINFO	lpModelInfo;
	LPSYSTEMINFO	lpSystemInfo;
	CComboBox*		m_pCmbPatternListName;

	int m_nSelClkFlags;
	int m_nChangeFont;
	bool m_bfusingflag,m_bgfd250flag;
public:
	CEdit m_edtClkDelay;
	CListCtrl m_lcPtnSetList;
	afx_msg void OnBnClickedBtnSave();
	CComboBox m_cboPtnName;
	CComboBox m_cboPtnVcom;
	CEdit m_edtPtnFg;
	CEdit m_edtPtnBg;
	CEdit m_edtPtnVCC;
	CEdit m_edtPtnVDD;
	CEdit m_edtPtnTMS;
	CEdit m_edtPtnVSync;

	afx_msg void OnBnClickedBtnAdd();
	afx_msg void OnBnClickedBtnDelete();
	afx_msg void OnBnClickedBtnUp();
	afx_msg void OnBnClickedBtnDown();
	afx_msg void OnBnClickedBtnChange();
	afx_msg void OnLvnItemchangedListPatternset(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnAll();

private:
	CFont m_Font[FONT_IDX_MAX];
	CBrush m_Brush[COLOR_IDX_MAX];

public:
	afx_msg void OnStnClickedSttFgClk();
	afx_msg void OnStnClickedSttBgClk();
	afx_msg void OnStnClickedSttVccClk();
	afx_msg void OnStnClickedSttVddClk();
	afx_msg void OnStnClickedSttTmsClk();
	afx_msg void OnStnClickedSttVsyncClk();
	afx_msg void OnStnClickedSttVcomClk();
	afx_msg void OnBnClickedBtnCancel();
	afx_msg void OnBnClickedBtnFusing();
	afx_msg void OnStnClickedSttBluClk();
	afx_msg void OnStnClickedSttTouchClk();
	CEdit m_edtPtnBlu;
	CComboBox m_cboPtnTouch;
	CComboBox m_cboEepAddr;
	afx_msg void OnBnClickedBtnMicroPtnPath();
	CStatic m_sttMicroPtnPath;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	CComboBox m_cboGfd250Use;
	afx_msg void OnBnClickedBtnBluOnoff();
	afx_msg void OnBnClickedBtnApply();
	CStatic m_picPatternPreview;
	afx_msg void OnCbnSelchangeCmbPtnName();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
};