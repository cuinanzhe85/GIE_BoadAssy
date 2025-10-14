#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CModelInfo 대화 상자입니다.

class CModelInfo : public CDialog
{
	DECLARE_DYNAMIC(CModelInfo)

public:
	CModelInfo(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CModelInfo();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_MODEL_INFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	CComboBox m_cboSignalType;
	CComboBox m_cboSignalBit;
	CComboBox m_cboPixelType;
	CComboBox m_cboBitSwap;
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
	CEdit m_edtBluMin;

protected:
	void Lf_initItemValue();
	void Lf_initFontSet();
	void Lf_loadModelData();
	void Lf_saveCtrlData(CString modelName);
	void Lf_setPatternList();
	void Lf_insertListColum();
	void Lf_saveModelInfoData();
	void Lf_setSwapData(int pos1, int pos2);
	void Lf_setPtnDataChange(int sel);
	void Lf_setChangeFont();

protected:
	LPMODELSETINFO	lpModelInfo;
	LPSYSTEMINFO	lpSystemInfo;
	CComboBox*		m_pCmbPatternListName;

	int m_nSelClkFlags;
	int m_nChangeFont;
	int m_bfusingflag;
public:
	CEdit m_edtClkDelay;
	CListCtrl m_lcPtnSetList;
	afx_msg void OnBnClickedBtnSave();
	CComboBox m_cboPtnName;
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
	afx_msg void OnStnClickedSttVccClk();
	afx_msg void OnStnClickedSttVddClk();
	afx_msg void OnStnClickedSttTmsClk();
	afx_msg void OnStnClickedSttVsyncClk();
	afx_msg void OnBnClickedBtnCancel();
	afx_msg void OnStnClickedSttBluClk();
	CEdit m_edtPtnBlu;
	CComboBox m_cmbPtnPower;
	CComboBox m_cboEepAddr;
	CStatic m_sttMicroPtnPath;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	afx_msg void OnBnClickedBtnBluOnoff();
	afx_msg void OnBnClickedBtnApply();
	CStatic m_picPatternPreview;
	afx_msg void OnCbnSelchangeCmbPtnName();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	CEdit m_edtPtnIccLow;
	CEdit m_edtPtnIccHigh;
	CEdit m_edtPtnIddLow;
	CEdit m_edtPtnIddHigh;
	CEdit m_edtVghSet;
	CEdit m_edtVglSet;
	CEdit m_edtVbrSet;
	CEdit m_edtVblSet;
	CEdit m_edtVccLowLimitSet;
	CEdit m_edtVddLowLimitSet;
	CEdit m_edtVghHighLimitSet;
	CEdit m_edtVghLowLimitSet;
	CEdit m_edtVglHighLimitSet;
	CEdit m_edtVglLowLimitSet;
	CEdit m_edtIccLowLimitSet;
	CEdit m_edtIddLowLimitSet;
	CEdit m_edtIghHighLimitSet;
	CEdit m_edtIghLowLimitSet;
	CEdit m_edtIglHighLimitSet;
	CEdit m_edtIglLowLimitSet;
	CEdit m_edtVblHighLimitSet;
	CEdit m_edtVblLowLimitSet;
	CEdit m_edtIblHighLimitSet;
	CEdit m_edtIblLowLimitSet;
	CComboBox m_cmbI2cPullUp;
	CComboBox m_cmbI2cFreq;
	CComboBox m_cmbI2cLevel;
	CComboBox m_cmbCableOpenUse;
	CComboBox m_cmbShortTestUse;
	CComboBox m_cmbIdInputType;
	CEdit m_edtIdLengthMin;
	CEdit m_edtIdLengthMax;
	CComboBox m_cmbClockDelay;
	CComboBox m_cmbClockRising;
	CComboBox m_cmbHSyncPolarity;
	CComboBox m_cmbVSyncPolarity;
	CComboBox m_cmbOddEven;
	CComboBox m_cmbOnSeqOp01;
	CComboBox m_cmbOnSeqOp02;
	CComboBox m_cmbOnSeqOp03;
	CComboBox m_cmbOnSeqOp04;
	CComboBox m_cmbOnSeqOp05;
	CComboBox m_cmbOnSeqOp06;
	CComboBox m_cmbOnSeqOp07;
	CComboBox m_cmbOnSeqOp08;
	CComboBox m_cmbOnSeqOp09;
	CComboBox m_cmbOnSeqOp10;
	CComboBox m_cmbOnSeqOp11;
	CComboBox m_cmbOnSeqOp12;
	CComboBox m_cmbOnSeqOp13;
	CComboBox m_cmbOnSeqOp14;
	CComboBox m_cmbOnSeqOp15;
	CComboBox m_cmbOnSeqOp16;
	CComboBox m_cmbOnSeqOp17;
	CComboBox m_cmbOffSeqOp01;
	CComboBox m_cmbOffSeqOp02;
	CComboBox m_cmbOffSeqOp03;
	CComboBox m_cmbOffSeqOp04;
	CComboBox m_cmbOffSeqOp05;
	CComboBox m_cmbOffSeqOp06;
	CComboBox m_cmbOffSeqOp07;
	CComboBox m_cmbOffSeqOp08;
	CComboBox m_cmbOffSeqOp09;
	CComboBox m_cmbOffSeqOp10;
	CComboBox m_cmbOffSeqOp11;
	CComboBox m_cmbOffSeqOp12;
	CComboBox m_cmbOffSeqOp13;
	CComboBox m_cmbOffSeqOp14;
	CComboBox m_cmbOffSeqOp15;
	CComboBox m_cmbOffSeqOp16;
	CComboBox m_cmbOffSeqOp17;
	CEdit m_edtOnSeqDelay01;
	CEdit m_edtOnSeqDelay02;
	CEdit m_edtOnSeqDelay03;
	CEdit m_edtOnSeqDelay04;
	CEdit m_edtOnSeqDelay05;
	CEdit m_edtOnSeqDelay06;
	CEdit m_edtOnSeqDelay07;
	CEdit m_edtOnSeqDelay08;
	CEdit m_edtOnSeqDelay09;
	CEdit m_edtOnSeqDelay10;
	CEdit m_edtOnSeqDelay11;
	CEdit m_edtOnSeqDelay12;
	CEdit m_edtOnSeqDelay13;
	CEdit m_edtOnSeqDelay14;
	CEdit m_edtOnSeqDelay15;
	CEdit m_edtOnSeqDelay16;
	CEdit m_edtOnSeqDelay17;
	CEdit m_edtOffSeqDelay01;
	CEdit m_edtOffSeqDelay02;
	CEdit m_edtOffSeqDelay03;
	CEdit m_edtOffSeqDelay04;
	CEdit m_edtOffSeqDelay05;
	CEdit m_edtOffSeqDelay06;
	CEdit m_edtOffSeqDelay07;
	CEdit m_edtOffSeqDelay08;
	CEdit m_edtOffSeqDelay09;
	CEdit m_edtOffSeqDelay10;
	CEdit m_edtOffSeqDelay11;
	CEdit m_edtOffSeqDelay12;
	CEdit m_edtOffSeqDelay13;
	CEdit m_edtOffSeqDelay14;
	CEdit m_edtOffSeqDelay15;
	CEdit m_edtOffSeqDelay16;
	CEdit m_edtOffSeqDelay17;
	CEdit m_edtPowerVcom1;
	CEdit m_edtPowerVcom2;
	CEdit m_edtPwmFreq;
	CEdit m_edtPwmDuty;
	CEdit m_edtClockDelay;
	CComboBox m_cboPixelOverlapMode;

	afx_msg void OnEnChangeEdtHActive();
	afx_msg void OnEnChangeEdtHWidth();
	afx_msg void OnEnChangeEdtHFrontPorch();
	afx_msg void OnEnChangeEdtHBackPorch();
	afx_msg void OnEnChangeEdtVActive();
	afx_msg void OnEnChangeEdtVWidth();
	afx_msg void OnEnChangeEdtVFrontPorch();
	afx_msg void OnEnChangeEdtVBackPorch();
	
	afx_msg void OnBnClickedBtnGammaVoltageSet();
	afx_msg void OnStnClickedSttFusing();
	afx_msg void OnStnClickedSttIccLow();
	afx_msg void OnStnClickedSttIccHigh();
	afx_msg void OnStnClickedSttIddLow();
	afx_msg void OnStnClickedSttIddHigh();
	afx_msg void OnStnClickedSttPtnPowerClk();
};
