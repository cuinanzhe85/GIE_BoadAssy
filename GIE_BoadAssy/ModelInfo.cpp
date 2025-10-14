// ModelInfo.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GIE_BoadAssy.h"
#include "ModelInfo.h"
#include "Initialize.h"

#include "ModelGamma.h"

// CModelInfo 대화 상자입니다.

IMPLEMENT_DYNAMIC(CModelInfo, CDialog)

CModelInfo::CModelInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CModelInfo::IDD, pParent)
{

}

CModelInfo::~CModelInfo()
{
}

void CModelInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMB_SIGNAL_TYPE, m_cboSignalType);
	DDX_Control(pDX, IDC_CMB_SIGNAL_BIT, m_cboSignalBit);
	DDX_Control(pDX, IDC_CMB_INTERFACE, m_cboPixelType);
	DDX_Control(pDX, IDC_CMB_LVDS_SEL, m_cboBitSwap);
	DDX_Control(pDX, IDC_EDT_H_TOTAL, m_edtHorTotal);
	DDX_Control(pDX, IDC_EDT_H_ACTIVE, m_edtHorActive);
	DDX_Control(pDX, IDC_EDT_H_WIDTH, m_edtHorWidth);
	DDX_Control(pDX, IDC_EDT_H_FRONT_PORCH, m_edtHorFrontPor);
	DDX_Control(pDX, IDC_EDT_H_BACK_PORCH, m_edtHorBackPor);
	DDX_Control(pDX, IDC_EDT_V_TOTAL, m_edtVerTotal);
	DDX_Control(pDX, IDC_EDT_V_ACTIVE, m_edtVerActive);
	DDX_Control(pDX, IDC_EDT_V_WIDTH, m_edtVerWidth);
	DDX_Control(pDX, IDC_EDT_V_FRONT_PORCH, m_edtVerFrontPor);
	DDX_Control(pDX, IDC_EDT_V_BACK_PORCH, m_edtVerBackPor);
	DDX_Control(pDX, IDC_EDT_FREQ, m_edtFreq);
	DDX_Control(pDX, IDC_EDT_VCC_SET, m_edtVccSet);
	DDX_Control(pDX, IDC_EDT_VDD_SET, m_edtVddSet);
	DDX_Control(pDX, IDC_EDT_VCC_HIGH_LIMIT, m_edtVccHighLimitSet);
	DDX_Control(pDX, IDC_EDT_VDD_HIGH_LIMIT, m_edtVddHighLimitSet);
	DDX_Control(pDX, IDC_EDT_ICC_HIGH_LIMIT, m_edtIccHighLimitSet);
	DDX_Control(pDX, IDC_EDT_IDD_HIGH_LIMIT, m_edtIddHighLimitSet);
	DDX_Control(pDX, IDC_CMB_EDID_ONOFF, m_cboEdidOnOff);
	DDX_Control(pDX, IDC_CMB_EDID_SIZE, m_cboEdidSize);
	DDX_Control(pDX, IDC_CMB_EDID_LINE, m_cboEdidLine);
	DDX_Control(pDX, IDC_CMB_EEPROM_TYPE, m_cboEepType);
	DDX_Control(pDX, IDC_EDT_BLU_MIN, m_edtBluMin);
	DDX_Control(pDX, IDC_LIST_PATTERNSET, m_lcPtnSetList);
	DDX_Control(pDX, IDC_CMB_PTN_NAME, m_cboPtnName);
	DDX_Control(pDX, IDC_EDT_PTN_VCC, m_edtPtnVCC);
	DDX_Control(pDX, IDC_EDT_PTN_VDD, m_edtPtnVDD);
	DDX_Control(pDX, IDC_EDT_PTN_TMS, m_edtPtnTMS);
	DDX_Control(pDX, IDC_EDT_PTN_VSYNC, m_edtPtnVSync);
	DDX_Control(pDX, IDC_EDT_PTN_BLU, m_edtPtnBlu);
	DDX_Control(pDX, IDC_CMB_PTN_POWER, m_cmbPtnPower);
	DDX_Control(pDX, IDC_CMB_EEPROM_ADDR, m_cboEepAddr);
	DDX_Control(pDX, IDC_PIC_MD_PTN_PREVIEW, m_picPatternPreview);
	DDX_Control(pDX, IDC_EDT_PTN_ICC_LOW, m_edtPtnIccLow);
	DDX_Control(pDX, IDC_EDT_PTN_ICC_HIGH, m_edtPtnIccHigh);
	DDX_Control(pDX, IDC_EDT_PTN_IDD_LOW, m_edtPtnIddLow);
	DDX_Control(pDX, IDC_EDT_PTN_IDD_HIGH, m_edtPtnIddHigh);
	DDX_Control(pDX, IDC_EDT_VGH_SET, m_edtVghSet);
	DDX_Control(pDX, IDC_EDT_VGL_SET, m_edtVglSet);
	DDX_Control(pDX, IDC_EDT_VBR_SET, m_edtVbrSet);
	DDX_Control(pDX, IDC_EDT_VBL_SET, m_edtVblSet);
	DDX_Control(pDX, IDC_EDT_VCC_LOW_LIMIT, m_edtVccLowLimitSet);
	DDX_Control(pDX, IDC_EDT_VDD_LOW_LIMIT, m_edtVddLowLimitSet);
	DDX_Control(pDX, IDC_EDT_VBL_LOW_LIMIT, m_edtVblLowLimitSet);
	DDX_Control(pDX, IDC_EDT_VBL_HIGH_LIMIT, m_edtVblHighLimitSet);
	DDX_Control(pDX, IDC_EDT_IBL_LOW_LIMIT, m_edtIblLowLimitSet);
	DDX_Control(pDX, IDC_EDT_IBL_HIGH_LIMIT, m_edtIblHighLimitSet);
	DDX_Control(pDX, IDC_EDT_VGH_HIGH_LIMIT, m_edtVghHighLimitSet);
	DDX_Control(pDX, IDC_EDT_VGH_LOW_LIMIT, m_edtVghLowLimitSet);
	DDX_Control(pDX, IDC_EDT_VGL_HIGH_LIMIT, m_edtVglHighLimitSet);
	DDX_Control(pDX, IDC_EDT_VGL_LOW_LIMIT, m_edtVglLowLimitSet);
	DDX_Control(pDX, IDC_EDT_ICC_LOW_LIMIT, m_edtIccLowLimitSet);
	DDX_Control(pDX, IDC_EDT_IDD_LOW_LIMIT, m_edtIddLowLimitSet);
	DDX_Control(pDX, IDC_EDT_IGH_HIGH_LIMIT, m_edtIghHighLimitSet);
	DDX_Control(pDX, IDC_EDT_IGH_LOW_LIMIT, m_edtIghLowLimitSet);
	DDX_Control(pDX, IDC_EDT_IGL_HIGH_LIMIT, m_edtIglHighLimitSet);
	DDX_Control(pDX, IDC_EDT_IGL_LOW_LIMIT, m_edtIglLowLimitSet);
	DDX_Control(pDX, IDC_CMB_I2C_PULLUP, m_cmbI2cPullUp);
	DDX_Control(pDX, IDC_CMB_I2C_FREQ, m_cmbI2cFreq);
	DDX_Control(pDX, IDC_CMB_I2C_LEVEL, m_cmbI2cLevel);
	DDX_Control(pDX, IDC_CMB_CABLE_OPEN, m_cmbCableOpenUse);
	DDX_Control(pDX, IDC_CMB_SHORT_TEST, m_cmbShortTestUse);
	DDX_Control(pDX, IDC_CMB_ID_INPUT_TYPE, m_cmbIdInputType);
	DDX_Control(pDX, IDC_EDT_ID_LENGTH_MIN, m_edtIdLengthMin);
	DDX_Control(pDX, IDC_EDT_ID_LENGTH_MAX, m_edtIdLengthMax);
	DDX_Control(pDX, IDC_CMB_CLOCK_RISING, m_cmbClockRising);
	DDX_Control(pDX, IDC_CMB_HSYNC_POLARITY, m_cmbHSyncPolarity);
	DDX_Control(pDX, IDC_CMB_VSYNC_POLARITY, m_cmbVSyncPolarity);
	DDX_Control(pDX, IDC_CMB_ODD_EVEN, m_cmbOddEven);
	DDX_Control(pDX, IDC_CMB_ON_SEQ_OP_1, m_cmbOnSeqOp01);
	DDX_Control(pDX, IDC_CMB_ON_SEQ_OP_2, m_cmbOnSeqOp02);
	DDX_Control(pDX, IDC_CMB_ON_SEQ_OP_3, m_cmbOnSeqOp03);
	DDX_Control(pDX, IDC_CMB_ON_SEQ_OP_4, m_cmbOnSeqOp04);
	DDX_Control(pDX, IDC_CMB_ON_SEQ_OP_5, m_cmbOnSeqOp05);
	DDX_Control(pDX, IDC_CMB_ON_SEQ_OP_6, m_cmbOnSeqOp06);
	DDX_Control(pDX, IDC_CMB_ON_SEQ_OP_7, m_cmbOnSeqOp07);
	DDX_Control(pDX, IDC_CMB_ON_SEQ_OP_8, m_cmbOnSeqOp08);
	DDX_Control(pDX, IDC_CMB_ON_SEQ_OP_9, m_cmbOnSeqOp09);
	DDX_Control(pDX, IDC_CMB_ON_SEQ_OP_10, m_cmbOnSeqOp10);
	DDX_Control(pDX, IDC_CMB_ON_SEQ_OP_11, m_cmbOnSeqOp11);
	DDX_Control(pDX, IDC_CMB_ON_SEQ_OP_12, m_cmbOnSeqOp12);
	DDX_Control(pDX, IDC_CMB_ON_SEQ_OP_13, m_cmbOnSeqOp13);
	DDX_Control(pDX, IDC_CMB_ON_SEQ_OP_14, m_cmbOnSeqOp14);
	DDX_Control(pDX, IDC_CMB_ON_SEQ_OP_15, m_cmbOnSeqOp15);
	DDX_Control(pDX, IDC_CMB_ON_SEQ_OP_16, m_cmbOnSeqOp16);
	DDX_Control(pDX, IDC_CMB_ON_SEQ_OP_17, m_cmbOnSeqOp17);
	DDX_Control(pDX, IDC_CMB_OFF_SEQ_OP_1, m_cmbOffSeqOp01);
	DDX_Control(pDX, IDC_CMB_OFF_SEQ_OP_2, m_cmbOffSeqOp02);
	DDX_Control(pDX, IDC_CMB_OFF_SEQ_OP_3, m_cmbOffSeqOp03);
	DDX_Control(pDX, IDC_CMB_OFF_SEQ_OP_4, m_cmbOffSeqOp04);
	DDX_Control(pDX, IDC_CMB_OFF_SEQ_OP_5, m_cmbOffSeqOp05);
	DDX_Control(pDX, IDC_CMB_OFF_SEQ_OP_6, m_cmbOffSeqOp06);
	DDX_Control(pDX, IDC_CMB_OFF_SEQ_OP_7, m_cmbOffSeqOp07);
	DDX_Control(pDX, IDC_CMB_OFF_SEQ_OP_8, m_cmbOffSeqOp08);
	DDX_Control(pDX, IDC_CMB_OFF_SEQ_OP_9, m_cmbOffSeqOp09);
	DDX_Control(pDX, IDC_CMB_OFF_SEQ_OP_10, m_cmbOffSeqOp10);
	DDX_Control(pDX, IDC_CMB_OFF_SEQ_OP_11, m_cmbOffSeqOp11);
	DDX_Control(pDX, IDC_CMB_OFF_SEQ_OP_12, m_cmbOffSeqOp12);
	DDX_Control(pDX, IDC_CMB_OFF_SEQ_OP_13, m_cmbOffSeqOp13);
	DDX_Control(pDX, IDC_CMB_OFF_SEQ_OP_14, m_cmbOffSeqOp14);
	DDX_Control(pDX, IDC_CMB_OFF_SEQ_OP_15, m_cmbOffSeqOp15);
	DDX_Control(pDX, IDC_CMB_OFF_SEQ_OP_16, m_cmbOffSeqOp16);
	DDX_Control(pDX, IDC_CMB_OFF_SEQ_OP_17, m_cmbOffSeqOp17);
	DDX_Control(pDX, IDC_EDT_ON_SEQ_DEL_1, m_edtOnSeqDelay01);
	DDX_Control(pDX, IDC_EDT_ON_SEQ_DEL_2, m_edtOnSeqDelay02);
	DDX_Control(pDX, IDC_EDT_ON_SEQ_DEL_3, m_edtOnSeqDelay03);
	DDX_Control(pDX, IDC_EDT_ON_SEQ_DEL_4, m_edtOnSeqDelay04);
	DDX_Control(pDX, IDC_EDT_ON_SEQ_DEL_5, m_edtOnSeqDelay05);
	DDX_Control(pDX, IDC_EDT_ON_SEQ_DEL_6, m_edtOnSeqDelay06);
	DDX_Control(pDX, IDC_EDT_ON_SEQ_DEL_7, m_edtOnSeqDelay07);
	DDX_Control(pDX, IDC_EDT_ON_SEQ_DEL_8, m_edtOnSeqDelay08);
	DDX_Control(pDX, IDC_EDT_ON_SEQ_DEL_9, m_edtOnSeqDelay09);
	DDX_Control(pDX, IDC_EDT_ON_SEQ_DEL_10, m_edtOnSeqDelay10);
	DDX_Control(pDX, IDC_EDT_ON_SEQ_DEL_11, m_edtOnSeqDelay11);
	DDX_Control(pDX, IDC_EDT_ON_SEQ_DEL_12, m_edtOnSeqDelay12);
	DDX_Control(pDX, IDC_EDT_ON_SEQ_DEL_13, m_edtOnSeqDelay13);
	DDX_Control(pDX, IDC_EDT_ON_SEQ_DEL_14, m_edtOnSeqDelay14);
	DDX_Control(pDX, IDC_EDT_ON_SEQ_DEL_15, m_edtOnSeqDelay15);
	DDX_Control(pDX, IDC_EDT_ON_SEQ_DEL_16, m_edtOnSeqDelay16);
	DDX_Control(pDX, IDC_EDT_ON_SEQ_DEL_17, m_edtOnSeqDelay17);
	DDX_Control(pDX, IDC_EDT_OFF_SEQ_DEL_1, m_edtOffSeqDelay01);
	DDX_Control(pDX, IDC_EDT_OFF_SEQ_DEL_2, m_edtOffSeqDelay02);
	DDX_Control(pDX, IDC_EDT_OFF_SEQ_DEL_3, m_edtOffSeqDelay03);
	DDX_Control(pDX, IDC_EDT_OFF_SEQ_DEL_4, m_edtOffSeqDelay04);
	DDX_Control(pDX, IDC_EDT_OFF_SEQ_DEL_5, m_edtOffSeqDelay05);
	DDX_Control(pDX, IDC_EDT_OFF_SEQ_DEL_6, m_edtOffSeqDelay06);
	DDX_Control(pDX, IDC_EDT_OFF_SEQ_DEL_7, m_edtOffSeqDelay07);
	DDX_Control(pDX, IDC_EDT_OFF_SEQ_DEL_8, m_edtOffSeqDelay08);
	DDX_Control(pDX, IDC_EDT_OFF_SEQ_DEL_9, m_edtOffSeqDelay09);
	DDX_Control(pDX, IDC_EDT_OFF_SEQ_DEL_10, m_edtOffSeqDelay10);
	DDX_Control(pDX, IDC_EDT_OFF_SEQ_DEL_11, m_edtOffSeqDelay11);
	DDX_Control(pDX, IDC_EDT_OFF_SEQ_DEL_12, m_edtOffSeqDelay12);
	DDX_Control(pDX, IDC_EDT_OFF_SEQ_DEL_13, m_edtOffSeqDelay13);
	DDX_Control(pDX, IDC_EDT_OFF_SEQ_DEL_14, m_edtOffSeqDelay14);
	DDX_Control(pDX, IDC_EDT_OFF_SEQ_DEL_15, m_edtOffSeqDelay15);
	DDX_Control(pDX, IDC_EDT_OFF_SEQ_DEL_16, m_edtOffSeqDelay16);
	DDX_Control(pDX, IDC_EDT_OFF_SEQ_DEL_17, m_edtOffSeqDelay17);
	DDX_Control(pDX, IDC_EDT_CLOCK_DELAY, m_edtClockDelay);
	DDX_Control(pDX, IDC_CMB_PIXEL_OVERLAP_MODE, m_cboPixelOverlapMode);
	DDX_Control(pDX, IDC_EDT_VCOM1, m_edtPowerVcom1);
	DDX_Control(pDX, IDC_EDT_VCOM2, m_edtPowerVcom2);
	DDX_Control(pDX, IDC_EDT_PWM_FREQ, m_edtPwmFreq);
	DDX_Control(pDX, IDC_EDT_PWM_DUTY, m_edtPwmDuty);

	
}


BEGIN_MESSAGE_MAP(CModelInfo, CDialog)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_SAVE, &CModelInfo::OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_ADD, &CModelInfo::OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTN_DELETE, &CModelInfo::OnBnClickedBtnDelete)
	ON_BN_CLICKED(IDC_BTN_UP, &CModelInfo::OnBnClickedBtnUp)
	ON_BN_CLICKED(IDC_BTN_DOWN, &CModelInfo::OnBnClickedBtnDown)
	ON_BN_CLICKED(IDC_BTN_CHANGE, &CModelInfo::OnBnClickedBtnChange)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_PATTERNSET, &CModelInfo::OnLvnItemchangedListPatternset)
	ON_BN_CLICKED(IDC_BTN_ALL, &CModelInfo::OnBnClickedBtnAll)
	ON_STN_CLICKED(IDC_STT_VCC_CLK, &CModelInfo::OnStnClickedSttVccClk)
	ON_STN_CLICKED(IDC_STT_VDD_CLK, &CModelInfo::OnStnClickedSttVddClk)
	ON_STN_CLICKED(IDC_STT_TMS_CLK, &CModelInfo::OnStnClickedSttTmsClk)
	ON_STN_CLICKED(IDC_STT_VSYNC_CLK, &CModelInfo::OnStnClickedSttVsyncClk)
	ON_BN_CLICKED(IDC_BTN_CANCEL, &CModelInfo::OnBnClickedBtnCancel)
	ON_STN_CLICKED(IDC_STT_BLU_CLK, &CModelInfo::OnStnClickedSttBluClk)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_BLU_ONOFF, &CModelInfo::OnBnClickedBtnBluOnoff)
	ON_BN_CLICKED(IDC_BTN_APPLY, &CModelInfo::OnBnClickedBtnApply)
	ON_CBN_SELCHANGE(IDC_CMB_PTN_NAME, &CModelInfo::OnCbnSelchangeCmbPtnName)
	ON_WM_DRAWITEM()
	ON_EN_CHANGE(IDC_EDT_H_ACTIVE, &CModelInfo::OnEnChangeEdtHActive)
	ON_EN_CHANGE(IDC_EDT_H_WIDTH, &CModelInfo::OnEnChangeEdtHWidth)
	ON_EN_CHANGE(IDC_EDT_H_FRONT_PORCH, &CModelInfo::OnEnChangeEdtHFrontPorch)
	ON_EN_CHANGE(IDC_EDT_H_BACK_PORCH, &CModelInfo::OnEnChangeEdtHBackPorch)
	ON_EN_CHANGE(IDC_EDT_V_ACTIVE, &CModelInfo::OnEnChangeEdtVActive)
	ON_EN_CHANGE(IDC_EDT_V_WIDTH, &CModelInfo::OnEnChangeEdtVWidth)
	ON_EN_CHANGE(IDC_EDT_V_FRONT_PORCH, &CModelInfo::OnEnChangeEdtVFrontPorch)
	ON_EN_CHANGE(IDC_EDT_V_BACK_PORCH, &CModelInfo::OnEnChangeEdtVBackPorch)
	ON_BN_CLICKED(IDC_BTN_GAMMA_VOLTAGE_SET, &CModelInfo::OnBnClickedBtnGammaVoltageSet)
	ON_STN_CLICKED(IDC_STT_FUSING, &CModelInfo::OnStnClickedSttFusing)
	ON_STN_CLICKED(IDC_STT_ICC_LOW, &CModelInfo::OnStnClickedSttIccLow)
	ON_STN_CLICKED(IDC_STT_ICC_HIGH, &CModelInfo::OnStnClickedSttIccHigh)
	ON_STN_CLICKED(IDC_STT_IDD_LOW, &CModelInfo::OnStnClickedSttIddLow)
	ON_STN_CLICKED(IDC_STT_IDD_HIGH, &CModelInfo::OnStnClickedSttIddHigh)
	ON_STN_CLICKED(IDC_STT_PTN_POWER_CLK, &CModelInfo::OnStnClickedSttPtnPowerClk)
END_MESSAGE_MAP()


// CModelInfo 메시지 처리기입니다.

BOOL CModelInfo::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_pApp->Gf_writeLogData("<WND>", "Model Info Dialog Open");
	lpModelInfo	= m_pApp->GetModelInfo();
	lpSystemInfo = m_pApp->GetSystemInfo();
	m_pCmbPatternListName = (CComboBox* ) GetDlgItem(IDC_CMB_PTN_NAME);

	Lf_initItemValue();
	Lf_initFontSet();
	Lf_setPatternList();
	Lf_insertListColum();
	Lf_loadModelData();

	GetDlgItem(IDC_STT_CUR_MODEL)->SetWindowText(lpSystemInfo->m_sModelName);
	GetDlgItem(IDC_EDT_CREATE_MODEL)->SetWindowText(lpSystemInfo->m_sModelName);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CModelInfo::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	for(int i=0; i<COLOR_IDX_MAX; i++)
	{
		m_Brush[i].DeleteObject();
	}

	for(int i=0; i<FONT_IDX_MAX; i++)
	{
		m_Font[i].DeleteObject();
	}
}
void CModelInfo::Lf_initItemValue()
{
	m_bfusingflag = 0;

	// 제품의 해상도 설정
	CRect rcLCD, rcFrame;

	rcLCD.top = 0;
	rcLCD.left = 0;
	rcLCD.right = lpModelInfo->m_nTimingHorActive;
	rcLCD.bottom = lpModelInfo->m_nTimingVerActive;

	// Preview 영역 설정
	GetDlgItem(IDC_STT_PTN_IMAGE_SIZE)->GetWindowRect(rcFrame);
	ScreenToClient(rcFrame);

	// Preview 영역 초기화
	m_pApp->m_pPatternView->InitPatternRect(GetDC(), rcLCD, rcFrame);
	m_pApp->m_pPatternView->InitPatternPath(_T(""));
	m_pApp->m_pPatternView->InitBmpPatternPath(_T(""));

	SetWindowTheme(GetDlgItem(IDC_STT_GRP_SIGNAL)->m_hWnd, _T(""), _T(""));
	SetWindowTheme(GetDlgItem(IDC_STT_GRP_TIMING)->m_hWnd, _T(""), _T(""));
	SetWindowTheme(GetDlgItem(IDC_STT_GRP_POWER)->m_hWnd, _T(""), _T(""));
	SetWindowTheme(GetDlgItem(IDC_STT_GRP_POWER_SEQ)->m_hWnd, _T(""), _T(""));
	SetWindowTheme(GetDlgItem(IDC_STT_GRP_POWER_LIMIT)->m_hWnd, _T(""), _T(""));
	SetWindowTheme(GetDlgItem(IDC_STT_GRP_EDID)->m_hWnd, _T(""), _T(""));
	SetWindowTheme(GetDlgItem(IDC_STT_GRP_OTHERS)->m_hWnd, _T(""), _T(""));
	SetWindowTheme(GetDlgItem(IDC_STT_GRP_PATTERN)->m_hWnd, _T(""), _T(""));
	SetWindowTheme(GetDlgItem(IDC_STT_GRP_I2C_OPTION)->m_hWnd, _T(""), _T(""));
	SetWindowTheme(GetDlgItem(IDC_STT_GRP_PWM_SET)->m_hWnd, _T(""), _T(""));
	SetWindowTheme(GetDlgItem(IDC_STT_GRP_ID_INPUT_TYPE)->m_hWnd, _T(""), _T(""));

	HICON hIcon;
	CButton* pBtn;
	hIcon = AfxGetApp()->LoadIconW(IDI_ICON_ADD);
	pBtn = (CButton*)GetDlgItem(IDC_BTN_ADD);
	pBtn->SetIcon(hIcon);

	hIcon = AfxGetApp()->LoadIconW(IDI_ICON_DELETE);
	pBtn = (CButton*)GetDlgItem(IDC_BTN_DELETE);
	pBtn->SetIcon(hIcon);

	hIcon = AfxGetApp()->LoadIconW(IDI_ICON_UP);
	pBtn = (CButton*)GetDlgItem(IDC_BTN_UP);
	pBtn->SetIcon(hIcon);

	hIcon = AfxGetApp()->LoadIconW(IDI_ICON_DOWN);
	pBtn = (CButton*)GetDlgItem(IDC_BTN_DOWN);
	pBtn->SetIcon(hIcon);

	hIcon = AfxGetApp()->LoadIconW(IDI_ICON_CHANGE);
	pBtn = (CButton*)GetDlgItem(IDC_BTN_CHANGE);
	pBtn->SetIcon(hIcon);

	hIcon = AfxGetApp()->LoadIconW(IDI_ICON_SAVE);
	pBtn = (CButton*)GetDlgItem(IDC_BTN_SAVE);
	pBtn->SetIcon(hIcon);

	hIcon = AfxGetApp()->LoadIconW(IDI_ICON_CLOSE);
	pBtn = (CButton*)GetDlgItem(IDC_BTN_CANCEL);
	pBtn->SetIcon(hIcon);
}
void CModelInfo::Lf_initFontSet()
{
	/*******************************************************************************************************************/
	// Fonts set
	m_Font[0].CreateFont( 15, 8, 0, 0, FW_SEMIBOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("Segoe UI Symbol"));
	GetDlgItem(IDC_STT_GRP_SIGNAL)->SetFont(&m_Font[0]);
	GetDlgItem(IDC_STT_GRP_PATTERN)->SetFont(&m_Font[0]);
	GetDlgItem(IDC_STT_GRP_OTHERS)->SetFont(&m_Font[0]);
	GetDlgItem(IDC_STT_GRP_POWER)->SetFont(&m_Font[0]);
	GetDlgItem(IDC_STT_GRP_POWER_SEQ)->SetFont(&m_Font[0]);
	GetDlgItem(IDC_STT_GRP_POWER_LIMIT)->SetFont(&m_Font[0]);
	GetDlgItem(IDC_STT_GRP_TIMING)->SetFont(&m_Font[0]);
	GetDlgItem(IDC_STT_GRP_EDID)->SetFont(&m_Font[0]);
	GetDlgItem(IDC_STT_GRP_I2C_OPTION)->SetFont(&m_Font[0]);
	GetDlgItem(IDC_STT_GRP_PWM_SET)->SetFont(&m_Font[0]);
	GetDlgItem(IDC_STT_GRP_ID_INPUT_TYPE)->SetFont(&m_Font[0]);

	m_Font[1].CreateFont( 17, 9, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("Segoe UI Symbol"));

	m_Font[2].CreateFont( 15, 8, 0, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0, 0, 0, _T("Segoe UI Symbol"));

	m_Font[3].CreateFont( 34, 14, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("Segoe UI Symbol"));
	GetDlgItem(IDC_STT_CUR_MODELNAME_TIT)->SetFont(&m_Font[3]);
	GetDlgItem(IDC_STT_CUR_MODEL)->SetFont(&m_Font[3]);
	GetDlgItem(IDC_STT_CREATE_MODEL_TIT)->SetFont(&m_Font[3]);
	GetDlgItem(IDC_EDT_CREATE_MODEL)->SetFont(&m_Font[3]);

	m_Font[4].CreateFont(60, 26, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("Segoe UI Symbol"));
	GetDlgItem(IDC_STT_MODELINFODLG_TIT)->SetFont(&m_Font[4]);

	m_Font[5].CreateFont(24, 11, 0, 0, FW_SEMIBOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("Segoe UI Symbol"));
	GetDlgItem(IDC_STT_FUSING)->SetFont(&m_Font[5]);
	GetDlgItem(IDC_BTN_SAVE)->SetFont(&m_Font[5]);
	GetDlgItem(IDC_BTN_CANCEL)->SetFont(&m_Font[5]);
	GetDlgItem(IDC_BTN_GAMMA_VOLTAGE_SET)->SetFont(&m_Font[5]);

	/*******************************************************************************************************************/
	// Brush set
	m_Brush[COLOR_IDX_BLACK].CreateSolidBrush(COLOR_BLACK);
	m_Brush[COLOR_IDX_ORANGE].CreateSolidBrush (COLOR_ORANGE);
	m_Brush[COLOR_IDX_GRAY240].CreateSolidBrush (COLOR_GRAY240);
	m_Brush[COLOR_IDX_GRAY64].CreateSolidBrush (COLOR_GRAY64);
	m_Brush[COLOR_IDX_GRAY96].CreateSolidBrush(COLOR_GRAY96);
	m_Brush[COLOR_IDX_BLUISH].CreateSolidBrush(COLOR_BLUISH);
	m_Brush[COLOR_IDX_GRAY224].CreateSolidBrush (COLOR_GRAY224);
	m_Brush[COLOR_IDX_GREEN128].CreateSolidBrush(COLOR_GREEN128);
	m_Brush[COLOR_IDX_RED128].CreateSolidBrush(COLOR_RED128);
	m_Brush[COLOR_IDX_DEEP_BLUE].CreateSolidBrush (COLOR_DEEP_BLUE);
	m_Brush[COLOR_IDX_LIGHT_YELLOW].CreateSolidBrush(COLOR_LIGHT_YELLOW);
	m_Brush[COLOR_IDX_MAGENTA].CreateSolidBrush(COLOR_MAGENTA);
}

void CModelInfo::Lf_loadModelData()
{
	CString sdata = _T("");
	int loop=0;

	m_cboSignalType.SetCurSel(lpModelInfo->m_nSignalType);

	m_cboSignalBit.SetCurSel(lpModelInfo->m_nSignalBit);

	m_cboPixelType.SetCurSel(lpModelInfo->m_nPixelType);

	m_cboBitSwap.SetCurSel(lpModelInfo->m_nLcmInfoBitsSwap);
	
	m_cmbClockRising.SetCurSel(lpModelInfo->m_nClockRising);

	m_cmbHSyncPolarity.SetCurSel(lpModelInfo->m_nHSyncPolarity);

	m_cmbVSyncPolarity.SetCurSel(lpModelInfo->m_nVSyncPolarity);

	m_cmbOddEven.SetCurSel(lpModelInfo->m_nOddEven);

	sdata.Format(_T("%d"), lpModelInfo->m_nClockDelay);
	m_edtClockDelay.SetWindowTextW(sdata);

	m_cboPixelOverlapMode.SetCurSel(lpModelInfo->m_nPixelOverlapMode);
	

	m_cmbOnSeqOp01.SetCurSel(lpModelInfo->m_nPowerOnSeqType01);
	m_cmbOnSeqOp02.SetCurSel(lpModelInfo->m_nPowerOnSeqType02);
	m_cmbOnSeqOp03.SetCurSel(lpModelInfo->m_nPowerOnSeqType03);
	m_cmbOnSeqOp04.SetCurSel(lpModelInfo->m_nPowerOnSeqType04);
	m_cmbOnSeqOp05.SetCurSel(lpModelInfo->m_nPowerOnSeqType05);
	m_cmbOnSeqOp06.SetCurSel(lpModelInfo->m_nPowerOnSeqType06);
	m_cmbOnSeqOp07.SetCurSel(lpModelInfo->m_nPowerOnSeqType07);
	m_cmbOnSeqOp08.SetCurSel(lpModelInfo->m_nPowerOnSeqType08);
	m_cmbOnSeqOp09.SetCurSel(lpModelInfo->m_nPowerOnSeqType09);
	m_cmbOnSeqOp10.SetCurSel(lpModelInfo->m_nPowerOnSeqType10);
	m_cmbOnSeqOp11.SetCurSel(lpModelInfo->m_nPowerOnSeqType11);
	m_cmbOnSeqOp12.SetCurSel(lpModelInfo->m_nPowerOnSeqType12);
	m_cmbOnSeqOp13.SetCurSel(lpModelInfo->m_nPowerOnSeqType13);
	m_cmbOnSeqOp14.SetCurSel(lpModelInfo->m_nPowerOnSeqType14);
	m_cmbOnSeqOp15.SetCurSel(lpModelInfo->m_nPowerOnSeqType15);
	m_cmbOnSeqOp16.SetCurSel(lpModelInfo->m_nPowerOnSeqType16);
	m_cmbOnSeqOp17.SetCurSel(lpModelInfo->m_nPowerOnSeqType17);
	m_cmbOffSeqOp01.SetCurSel(lpModelInfo->m_nPowerOffSeqType01);
	m_cmbOffSeqOp02.SetCurSel(lpModelInfo->m_nPowerOffSeqType02);
	m_cmbOffSeqOp03.SetCurSel(lpModelInfo->m_nPowerOffSeqType03);
	m_cmbOffSeqOp04.SetCurSel(lpModelInfo->m_nPowerOffSeqType04);
	m_cmbOffSeqOp05.SetCurSel(lpModelInfo->m_nPowerOffSeqType05);
	m_cmbOffSeqOp06.SetCurSel(lpModelInfo->m_nPowerOffSeqType06);
	m_cmbOffSeqOp07.SetCurSel(lpModelInfo->m_nPowerOffSeqType07);
	m_cmbOffSeqOp08.SetCurSel(lpModelInfo->m_nPowerOffSeqType08);
	m_cmbOffSeqOp09.SetCurSel(lpModelInfo->m_nPowerOffSeqType09);
	m_cmbOffSeqOp10.SetCurSel(lpModelInfo->m_nPowerOffSeqType10);
	m_cmbOffSeqOp11.SetCurSel(lpModelInfo->m_nPowerOffSeqType11);
	m_cmbOffSeqOp12.SetCurSel(lpModelInfo->m_nPowerOffSeqType12);
	m_cmbOffSeqOp13.SetCurSel(lpModelInfo->m_nPowerOffSeqType13);
	m_cmbOffSeqOp14.SetCurSel(lpModelInfo->m_nPowerOffSeqType14);
	m_cmbOffSeqOp15.SetCurSel(lpModelInfo->m_nPowerOffSeqType15);
	m_cmbOffSeqOp16.SetCurSel(lpModelInfo->m_nPowerOffSeqType16);
	m_cmbOffSeqOp17.SetCurSel(lpModelInfo->m_nPowerOffSeqType17);

	sdata.Format(_T("%d"), lpModelInfo->m_nPowerOnSeqDelay01);
	m_edtOnSeqDelay01.SetWindowTextW(sdata);
	sdata.Format(_T("%d"), lpModelInfo->m_nPowerOnSeqDelay02);
	m_edtOnSeqDelay02.SetWindowTextW(sdata);
	sdata.Format(_T("%d"), lpModelInfo->m_nPowerOnSeqDelay03);
	m_edtOnSeqDelay03.SetWindowTextW(sdata);
	sdata.Format(_T("%d"), lpModelInfo->m_nPowerOnSeqDelay04);
	m_edtOnSeqDelay04.SetWindowTextW(sdata);
	sdata.Format(_T("%d"), lpModelInfo->m_nPowerOnSeqDelay05);
	m_edtOnSeqDelay05.SetWindowTextW(sdata);
	sdata.Format(_T("%d"), lpModelInfo->m_nPowerOnSeqDelay06);
	m_edtOnSeqDelay06.SetWindowTextW(sdata);
	sdata.Format(_T("%d"), lpModelInfo->m_nPowerOnSeqDelay07);
	m_edtOnSeqDelay07.SetWindowTextW(sdata);
	sdata.Format(_T("%d"), lpModelInfo->m_nPowerOnSeqDelay08);
	m_edtOnSeqDelay08.SetWindowTextW(sdata);
	sdata.Format(_T("%d"), lpModelInfo->m_nPowerOnSeqDelay09);
	m_edtOnSeqDelay09.SetWindowTextW(sdata);
	sdata.Format(_T("%d"), lpModelInfo->m_nPowerOnSeqDelay10);
	m_edtOnSeqDelay10.SetWindowTextW(sdata);
	sdata.Format(_T("%d"), lpModelInfo->m_nPowerOnSeqDelay11);
	m_edtOnSeqDelay11.SetWindowTextW(sdata);
	sdata.Format(_T("%d"), lpModelInfo->m_nPowerOnSeqDelay12);
	m_edtOnSeqDelay12.SetWindowTextW(sdata);
	sdata.Format(_T("%d"), lpModelInfo->m_nPowerOnSeqDelay13);
	m_edtOnSeqDelay13.SetWindowTextW(sdata);
	sdata.Format(_T("%d"), lpModelInfo->m_nPowerOnSeqDelay14);
	m_edtOnSeqDelay14.SetWindowTextW(sdata);
	sdata.Format(_T("%d"), lpModelInfo->m_nPowerOnSeqDelay15);
	m_edtOnSeqDelay15.SetWindowTextW(sdata);
	sdata.Format(_T("%d"), lpModelInfo->m_nPowerOnSeqDelay16);
	m_edtOnSeqDelay16.SetWindowTextW(sdata);
	sdata.Format(_T("%d"), lpModelInfo->m_nPowerOnSeqDelay17);
	m_edtOnSeqDelay17.SetWindowTextW(sdata);

	sdata.Format(_T("%d"), lpModelInfo->m_nPowerOffSeqDelay01);
	m_edtOffSeqDelay01.SetWindowTextW(sdata);
	sdata.Format(_T("%d"), lpModelInfo->m_nPowerOffSeqDelay02);
	m_edtOffSeqDelay02.SetWindowTextW(sdata);
	sdata.Format(_T("%d"), lpModelInfo->m_nPowerOffSeqDelay03);
	m_edtOffSeqDelay03.SetWindowTextW(sdata);
	sdata.Format(_T("%d"), lpModelInfo->m_nPowerOffSeqDelay04);
	m_edtOffSeqDelay04.SetWindowTextW(sdata);
	sdata.Format(_T("%d"), lpModelInfo->m_nPowerOffSeqDelay05);
	m_edtOffSeqDelay05.SetWindowTextW(sdata);
	sdata.Format(_T("%d"), lpModelInfo->m_nPowerOffSeqDelay06);
	m_edtOffSeqDelay06.SetWindowTextW(sdata);
	sdata.Format(_T("%d"), lpModelInfo->m_nPowerOffSeqDelay07);
	m_edtOffSeqDelay07.SetWindowTextW(sdata);
	sdata.Format(_T("%d"), lpModelInfo->m_nPowerOffSeqDelay08);
	m_edtOffSeqDelay08.SetWindowTextW(sdata);
	sdata.Format(_T("%d"), lpModelInfo->m_nPowerOffSeqDelay09);
	m_edtOffSeqDelay09.SetWindowTextW(sdata);
	sdata.Format(_T("%d"), lpModelInfo->m_nPowerOffSeqDelay10);
	m_edtOffSeqDelay10.SetWindowTextW(sdata);
	sdata.Format(_T("%d"), lpModelInfo->m_nPowerOffSeqDelay11);
	m_edtOffSeqDelay11.SetWindowTextW(sdata);
	sdata.Format(_T("%d"), lpModelInfo->m_nPowerOffSeqDelay12);
	m_edtOffSeqDelay12.SetWindowTextW(sdata);
	sdata.Format(_T("%d"), lpModelInfo->m_nPowerOffSeqDelay13);
	m_edtOffSeqDelay13.SetWindowTextW(sdata);
	sdata.Format(_T("%d"), lpModelInfo->m_nPowerOffSeqDelay14);
	m_edtOffSeqDelay14.SetWindowTextW(sdata);
	sdata.Format(_T("%d"), lpModelInfo->m_nPowerOffSeqDelay15);
	m_edtOffSeqDelay15.SetWindowTextW(sdata);
	sdata.Format(_T("%d"), lpModelInfo->m_nPowerOffSeqDelay16);
	m_edtOffSeqDelay16.SetWindowTextW(sdata);
	sdata.Format(_T("%d"), lpModelInfo->m_nPowerOffSeqDelay17);
	m_edtOffSeqDelay17.SetWindowTextW(sdata);

	sdata.Format(_T("%.2f"),lpModelInfo->m_fTimingFreq);
	m_edtFreq.SetWindowText(sdata);

	sdata.Format(_T("%d"),lpModelInfo->m_nTimingHorTotal);
	m_edtHorTotal.SetWindowText(sdata);

	sdata.Format(_T("%d"),lpModelInfo->m_nTimingHorActive);
	m_edtHorActive.SetWindowText(sdata);

	sdata.Format(_T("%d"),lpModelInfo->m_nTimingHorWidth);
	m_edtHorWidth.SetWindowText(sdata);

	sdata.Format(_T("%d"),lpModelInfo->m_nTimingHorFront_P);
	m_edtHorFrontPor.SetWindowText(sdata);

	sdata.Format(_T("%d"),lpModelInfo->m_nTimingHorBack_P);
	m_edtHorBackPor.SetWindowText(sdata);

	sdata.Format(_T("%d"),lpModelInfo->m_nTimingVerTotal);
	m_edtVerTotal.SetWindowText(sdata);

	sdata.Format(_T("%d"),lpModelInfo->m_nTimingVerActive);
	m_edtVerActive.SetWindowText(sdata);

	sdata.Format(_T("%d"),lpModelInfo->m_nTimingVerWidth);
	m_edtVerWidth.SetWindowText(sdata);

	sdata.Format(_T("%d"),lpModelInfo->m_nTimingVerFront_P);
	m_edtVerFrontPor.SetWindowText(sdata);

	sdata.Format(_T("%d"),lpModelInfo->m_nTimingVerBack_P);
	m_edtVerBackPor.SetWindowText(sdata);


	sdata.Format(_T("%d"),lpModelInfo->m_nBluMin);
	m_edtBluMin.SetWindowText(sdata);

	m_cmbCableOpenUse.SetCurSel(lpModelInfo->m_nCableOpenUse);
	m_cmbShortTestUse.SetCurSel(lpModelInfo->m_nShortTestUse);

	m_cmbIdInputType.SetCurSel(lpModelInfo->m_nIdInputType);
	sdata.Format(_T("%d"), lpModelInfo->m_nIdLengthMin);
	m_edtIdLengthMin.SetWindowText(sdata);
	sdata.Format(_T("%d"), lpModelInfo->m_nIdLengthMax);
	m_edtIdLengthMax.SetWindowText(sdata);

	m_cboEdidOnOff.SetCurSel(lpModelInfo->m_nEdidUse);
	m_cboEdidSize.SetCurSel(lpModelInfo->m_nEdidSize);
	m_cboEdidLine.SetCurSel(lpModelInfo->m_nEdidLine);
	m_cboEepType.SetCurSel(lpModelInfo->m_nEEPRomType);
	m_cboEepAddr.SetCurSel(lpModelInfo->m_nEEPRomAddr);

	sdata.Format(_T("%.3f"), lpModelInfo->m_fVoltVcc);
	m_edtVccSet.SetWindowText(sdata);

	sdata.Format(_T("%.3f"), lpModelInfo->m_fVoltVdd);
	m_edtVddSet.SetWindowText(sdata);

	sdata.Format(_T("%.3f"), lpModelInfo->m_fVoltVgh);
	m_edtVghSet.SetWindowText(sdata);

	sdata.Format(_T("%.3f"), lpModelInfo->m_fVoltVgl);
	m_edtVglSet.SetWindowText(sdata);

	sdata.Format(_T("%.2f"), lpModelInfo->m_fLimitVccMax);
	m_edtVccHighLimitSet.SetWindowText(sdata);

	sdata.Format(_T("%.2f"), lpModelInfo->m_fLimitVccMin);
	m_edtVccLowLimitSet.SetWindowText(sdata);

	sdata.Format(_T("%.2f"), lpModelInfo->m_fLimitVddMax);
	m_edtVddHighLimitSet.SetWindowText(sdata);

	sdata.Format(_T("%.2f"), lpModelInfo->m_fLimitVddMin);
	m_edtVddLowLimitSet.SetWindowText(sdata);

	sdata.Format(_T("%.2f"), lpModelInfo->m_fLimitVblMax);
	m_edtVblHighLimitSet.SetWindowText(sdata);

	sdata.Format(_T("%.2f"), lpModelInfo->m_fLimitVblMin);
	m_edtVblLowLimitSet.SetWindowText(sdata);

	sdata.Format(_T("%.2f"), lpModelInfo->m_fLimitIccMax);
	m_edtIccHighLimitSet.SetWindowText(sdata);

	sdata.Format(_T("%.2f"), lpModelInfo->m_fLimitIccMin);
	m_edtIccLowLimitSet.SetWindowText(sdata);

	sdata.Format(_T("%.2f"), lpModelInfo->m_fLimitIddMax);
	m_edtIddHighLimitSet.SetWindowText(sdata);

	sdata.Format(_T("%.2f"), lpModelInfo->m_fLimitIddMin);
	m_edtIddLowLimitSet.SetWindowText(sdata);

	sdata.Format(_T("%.2f"), lpModelInfo->m_fLimitIblMax);
	m_edtIblHighLimitSet.SetWindowText(sdata);

	sdata.Format(_T("%.2f"), lpModelInfo->m_fLimitIblMin);
	m_edtIblLowLimitSet.SetWindowText(sdata);

	sdata.Format(_T("%.2f"), lpModelInfo->m_fLimitVghMax);
	m_edtVghHighLimitSet.SetWindowText(sdata);

	sdata.Format(_T("%.2f"), lpModelInfo->m_fLimitVghMin);
	m_edtVghLowLimitSet.SetWindowText(sdata);

	sdata.Format(_T("%.2f"), lpModelInfo->m_fLimitVglMax);
	m_edtVglHighLimitSet.SetWindowText(sdata);

	sdata.Format(_T("%.2f"), lpModelInfo->m_fLimitVglMin);
	m_edtVglLowLimitSet.SetWindowText(sdata);

	sdata.Format(_T("%.2f"), lpModelInfo->m_fLimitIghMax);
	m_edtIghHighLimitSet.SetWindowText(sdata);

	sdata.Format(_T("%.2f"), lpModelInfo->m_fLimitIghMin);
	m_edtIghLowLimitSet.SetWindowText(sdata);

	sdata.Format(_T("%.2f"), lpModelInfo->m_fLimitIglMax);
	m_edtIglHighLimitSet.SetWindowText(sdata);

	sdata.Format(_T("%.2f"), lpModelInfo->m_fLimitIglMin);
	m_edtIglLowLimitSet.SetWindowText(sdata);

	sdata.Format(_T("%.3f"), lpModelInfo->m_fVoltVbr);
	m_edtVbrSet.SetWindowText(sdata);

	sdata.Format(_T("%.3f"), lpModelInfo->m_fVoltVbl);
	m_edtVblSet.SetWindowText(sdata);

	sdata.Format(_T("%.3f"), lpModelInfo->m_fVoltVcom1);
	m_edtPowerVcom1.SetWindowText(sdata);

	sdata.Format(_T("%.3f"), lpModelInfo->m_fVoltVcom2);
	m_edtPowerVcom2.SetWindowText(sdata);

	sdata.Format(_T("%d"), lpModelInfo->m_nPwmFreq);
	m_edtPwmFreq.SetWindowText(sdata);

	sdata.Format(_T("%d"), lpModelInfo->m_nPwmDuty);
	m_edtPwmDuty.SetWindowText(sdata);

	m_cmbI2cPullUp.SetCurSel(lpModelInfo->m_nI2cPullup);
	m_cmbI2cFreq.SetCurSel(lpModelInfo->m_nI2cFreq);
	m_cmbI2cLevel.SetCurSel(lpModelInfo->m_nI2cLevel);

	m_cboPtnName.SetCurSel(0);

	sdata.Format(_T("%s"), lpModelInfo->m_sLbPtnVcc[0]);
	m_edtPtnVCC.SetWindowText(sdata);

	sdata.Format(_T("%s"), lpModelInfo->m_sLbPtnVdd[0]);
	m_edtPtnVDD.SetWindowText(sdata);

	sdata.Format(_T("%s"), lpModelInfo->m_sLbPtnTms[0]);
	m_edtPtnTMS.SetWindowText(sdata);

	sdata.Format(_T("%s"), lpModelInfo->m_sLbPtnVsync[0]);
	m_edtPtnVSync.SetWindowText(sdata);

	sdata.Format(_T("%s"), lpModelInfo->m_sLbPtnIccLow[0]);
	m_edtPtnIccLow.SetWindowTextW(sdata);

	sdata.Format(_T("%s"), lpModelInfo->m_sLbPtnIccHigh[0]);
	m_edtPtnIccHigh.SetWindowTextW(sdata);

	sdata.Format(_T("%s"), lpModelInfo->m_sLbPtnIddLow[0]);
	m_edtPtnIddLow.SetWindowTextW(sdata);

	sdata.Format(_T("%s"), lpModelInfo->m_sLbPtnIddHigh[0]);
	m_edtPtnIddHigh.SetWindowTextW(sdata);

	sdata.Format(_T("%s"), lpModelInfo->m_sLbPtnBlu[0]);
	m_edtPtnBlu.SetWindowText(sdata);

	m_cmbPtnPower.SetCurSel(lpModelInfo->m_nLbPtnPower[0]);

	for(loop = 0;loop < lpModelInfo->m_nLbCnt; loop++)
	{
		m_lcPtnSetList.InsertItem(loop, lpModelInfo->m_sLbPtnName[loop]);
		m_lcPtnSetList.SetItemText(loop, 1, lpModelInfo->m_sLbPtnVcc[loop]);
		m_lcPtnSetList.SetItemText(loop, 2, lpModelInfo->m_sLbPtnVdd[loop]);
		m_lcPtnSetList.SetItemText(loop, 3, lpModelInfo->m_sLbPtnTms[loop]);
		m_lcPtnSetList.SetItemText(loop, 4, lpModelInfo->m_sLbPtnVsync[loop]);
		m_lcPtnSetList.SetItemText(loop, 5, lpModelInfo->m_sLbPtnIccLow[loop]);
		m_lcPtnSetList.SetItemText(loop, 6, lpModelInfo->m_sLbPtnIccHigh[loop]);
		m_lcPtnSetList.SetItemText(loop, 7, lpModelInfo->m_sLbPtnIddLow[loop]);
		m_lcPtnSetList.SetItemText(loop, 8, lpModelInfo->m_sLbPtnIddHigh[loop]);
		m_lcPtnSetList.SetItemText(loop, 9, lpModelInfo->m_sLbPtnBlu[loop]);

		if(lpModelInfo->m_nLbPtnPower[loop] == TRUE)
			m_lcPtnSetList.SetItemText(loop, 10, _T("ON"));
		else
			m_lcPtnSetList.SetItemText(loop, 10, _T("OFF"));
	}


	UpdateData(FALSE);
}

void CModelInfo::Lf_setPatternList()
{
	CString strfilename;
	WIN32_FIND_DATA wfd;
	HANDLE hSearch;

	hSearch = FindFirstFile (_T(".\\Pattern\\*.pdb"), &wfd);

	if (hSearch != INVALID_HANDLE_VALUE)
	{
		if (wfd.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
		{
			strfilename.Format(_T("%s"), wfd.cFileName);
			strfilename = strfilename.Mid(0, strfilename.GetLength()-4);
			strfilename.MakeUpper();
			m_pCmbPatternListName->AddString (strfilename);
		}
		while (FindNextFile (hSearch, &wfd))
		{
			if (wfd.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
			{
				strfilename.Format(_T("%s"), wfd.cFileName);
				strfilename = strfilename.Mid(0, strfilename.GetLength()-4);
				strfilename.MakeUpper();
				m_pCmbPatternListName->AddString (strfilename);
			}
		}
		FindClose (hSearch);
	}
	hSearch = FindFirstFile(_T(".\\Pattern\\BMP\\*.bmp"), &wfd);

	if (hSearch != INVALID_HANDLE_VALUE)
	{
		if (wfd.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
		{
			strfilename.Format(_T("%s"), wfd.cFileName);
			strfilename.MakeUpper();
			m_pCmbPatternListName->AddString(strfilename);
		}
		while (FindNextFile(hSearch, &wfd))
		{
			if (wfd.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
			{
				strfilename.Format(_T("%s"), wfd.cFileName);
				strfilename.MakeUpper();
				m_pCmbPatternListName->AddString(strfilename);
			}
		}
		FindClose(hSearch);
	}

	m_cboPtnName.SetCurSel(0);
}

void CModelInfo::Lf_insertListColum()
{
	CRect rect,rect2;
	int offset=2;

	m_lcPtnSetList.GetClientRect(&rect);
	m_lcPtnSetList.InsertColumn(0, _T("PATTERN NAME"), LVCFMT_LEFT, -1, -1 );
	m_lcPtnSetList.InsertColumn(1, _T("VCC"), LVCFMT_LEFT, -1, -1 );
	m_lcPtnSetList.InsertColumn(2, _T("VDD"), LVCFMT_LEFT, -1, -1 );
	m_lcPtnSetList.InsertColumn(3, _T("T(s)"), LVCFMT_LEFT, -1, -1 );
	m_lcPtnSetList.InsertColumn(4, _T("Vsync"), LVCFMT_LEFT, -1, -1 );
	m_lcPtnSetList.InsertColumn(5, _T("ICC L"), LVCFMT_LEFT, -1, -1);
	m_lcPtnSetList.InsertColumn(6, _T("ICC H"), LVCFMT_LEFT, -1, -1);
	m_lcPtnSetList.InsertColumn(7, _T("IDD L"), LVCFMT_LEFT, -1, -1);
	m_lcPtnSetList.InsertColumn(8, _T("IDD H"), LVCFMT_LEFT, -1, -1);
	m_lcPtnSetList.InsertColumn(9, _T("BLU"), LVCFMT_LEFT, -1, -1 );
	m_lcPtnSetList.InsertColumn(10, _T("Power"), LVCFMT_LEFT, -1, -1);

	m_lcPtnSetList.SetColumnWidth(0, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER ); // Pattern
	GetDlgItem(IDC_CMB_PTN_NAME)->GetWindowRect(&rect2);
	m_lcPtnSetList.SetColumnWidth(0, rect2.Width());

	m_lcPtnSetList.SetColumnWidth(1, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER ); // VCC
	GetDlgItem(IDC_EDT_PTN_VCC)->GetWindowRect(&rect2);
	m_lcPtnSetList.SetColumnWidth(1, rect2.Width()+offset);

	m_lcPtnSetList.SetColumnWidth(2, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER ); // VDD
	GetDlgItem(IDC_EDT_PTN_VDD)->GetWindowRect(&rect2);
	m_lcPtnSetList.SetColumnWidth(2, rect2.Width()+offset);

	m_lcPtnSetList.SetColumnWidth(3, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER ); // T(ms)
	GetDlgItem(IDC_EDT_PTN_TMS)->GetWindowRect(&rect2);
	m_lcPtnSetList.SetColumnWidth(3, rect2.Width()+offset);

	m_lcPtnSetList.SetColumnWidth(4, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER ); // VSYNC
	GetDlgItem(IDC_EDT_PTN_VSYNC)->GetWindowRect(&rect2);
	m_lcPtnSetList.SetColumnWidth(4, rect2.Width()+offset);

	m_lcPtnSetList.SetColumnWidth(5, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER); // ICC LOW
	GetDlgItem(IDC_EDT_PTN_ICC_LOW)->GetWindowRect(&rect2);
	m_lcPtnSetList.SetColumnWidth(5, rect2.Width() + offset);

	m_lcPtnSetList.SetColumnWidth(6, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER); // ICC HIGH
	GetDlgItem(IDC_EDT_PTN_ICC_HIGH)->GetWindowRect(&rect2);
	m_lcPtnSetList.SetColumnWidth(6, rect2.Width() + offset);

	m_lcPtnSetList.SetColumnWidth(7, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER); // IDD LOW
	GetDlgItem(IDC_EDT_PTN_IDD_LOW)->GetWindowRect(&rect2);
	m_lcPtnSetList.SetColumnWidth(7, rect2.Width() + offset);

	m_lcPtnSetList.SetColumnWidth(8, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER); // IDD HIGH
	GetDlgItem(IDC_EDT_PTN_IDD_HIGH)->GetWindowRect(&rect2);
	m_lcPtnSetList.SetColumnWidth(8, rect2.Width() + offset);

	m_lcPtnSetList.SetColumnWidth( 9, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER ); // BLU
	GetDlgItem(IDC_EDT_PTN_BLU)->GetWindowRect(&rect2);
	m_lcPtnSetList.SetColumnWidth( 9, rect2.Width()+offset);

	m_lcPtnSetList.SetColumnWidth(10, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER); // POWER
	GetDlgItem(IDC_CMB_PTN_POWER)->GetWindowRect(&rect2);
	m_lcPtnSetList.SetColumnWidth(10, rect2.Width() + offset);

	DWORD dwStype = m_lcPtnSetList.GetExtendedStyle();
	dwStype |= LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES;
	m_lcPtnSetList.SetExtendedStyle(dwStype);
}

void CModelInfo::Lf_saveCtrlData(CString modelName)
{
	CString sdata=_T("");

	UpdateData(TRUE);

	lpModelInfo->m_nSignalType = m_cboSignalType.GetCurSel();
	Write_ModelFile(modelName,	_T("MODEL_INFO"),	_T("SIGNAL_TYPE"),			lpModelInfo->m_nSignalType);	

	lpModelInfo->m_nSignalBit = m_cboSignalBit.GetCurSel();
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("SIGNAL_BIT"),				lpModelInfo->m_nSignalBit);

	m_edtFreq.GetWindowText(sdata);
	lpModelInfo->m_fTimingFreq = (float)_tstof(sdata);
	Write_ModelFile(modelName,	_T("MODEL_INFO"),	_T("MAIN_CLOCK"),			lpModelInfo->m_fTimingFreq);

	m_edtHorTotal.GetWindowText(sdata);
	lpModelInfo->m_nTimingHorTotal = _ttoi(sdata);
	Write_ModelFile(modelName,	_T("MODEL_INFO"),	_T("HOR_TOTAL"),			lpModelInfo->m_nTimingHorTotal);

	m_edtHorActive.GetWindowText(sdata);
	lpModelInfo->m_nTimingHorActive = _ttoi(sdata);
	Write_ModelFile(modelName,	_T("MODEL_INFO"),	_T("HOR_ACTIVE"),			lpModelInfo->m_nTimingHorActive);

	m_edtHorBackPor.GetWindowText(sdata);
	lpModelInfo->m_nTimingHorBack_P = _ttoi(sdata);
	Write_ModelFile(modelName,	_T("MODEL_INFO"),	_T("HOR_BACKPORCH"),		lpModelInfo->m_nTimingHorBack_P);

	m_edtHorFrontPor.GetWindowText(sdata);
	lpModelInfo->m_nTimingHorFront_P = _ttoi(sdata);
	Write_ModelFile(modelName,	_T("MODEL_INFO"),	_T("HOR_FRONTPORCH"),		lpModelInfo->m_nTimingHorFront_P);

	m_edtHorWidth.GetWindowText(sdata);
	lpModelInfo->m_nTimingHorWidth = _ttoi(sdata);
	Write_ModelFile(modelName,	_T("MODEL_INFO"),	_T("HOR_WIDTH"),			lpModelInfo->m_nTimingHorWidth);

	m_edtVerTotal.GetWindowText(sdata);
	lpModelInfo->m_nTimingVerTotal = _ttoi(sdata);
	Write_ModelFile(modelName,	_T("MODEL_INFO"),	_T("VER_TOTAL"),			lpModelInfo->m_nTimingVerTotal);

	m_edtVerActive.GetWindowText(sdata);
	lpModelInfo->m_nTimingVerActive = _ttoi(sdata);
	Write_ModelFile(modelName,	_T("MODEL_INFO"),	_T("VER_ACTIVE"),			lpModelInfo->m_nTimingVerActive);

	m_edtVerBackPor.GetWindowText(sdata);
	lpModelInfo->m_nTimingVerBack_P = _ttoi(sdata);
	Write_ModelFile(modelName,	_T("MODEL_INFO"),	_T("VER_BACKPORCH"),		lpModelInfo->m_nTimingVerBack_P);

	m_edtVerFrontPor.GetWindowText(sdata);
	lpModelInfo->m_nTimingVerFront_P = _ttoi(sdata);
	Write_ModelFile(modelName,	_T("MODEL_INFO"),	_T("VER_FRONTPORCH"),		lpModelInfo->m_nTimingVerFront_P);

	m_edtVerWidth.GetWindowText(sdata);
	lpModelInfo->m_nTimingVerWidth = _ttoi(sdata);
	Write_ModelFile(modelName,	_T("MODEL_INFO"),	_T("VER_WIDTH"),			lpModelInfo->m_nTimingVerWidth);

	lpModelInfo->m_nPixelType = m_cboPixelType.GetCurSel();
	Write_ModelFile(modelName,	_T("MODEL_INFO"),	_T("PIXEL_TYPE"),			lpModelInfo->m_nPixelType);

	lpModelInfo->m_nLcmInfoBitsSwap = m_cboBitSwap.GetCurSel();
	Write_ModelFile(modelName,	_T("MODEL_INFO"),	_T("BITSWAP"),				lpModelInfo->m_nLcmInfoBitsSwap);

	m_edtClockDelay.GetWindowTextW(sdata);
	lpModelInfo->m_nClockDelay = (int)_ttoi(sdata);
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("CLOCK_DELAY"),				lpModelInfo->m_nClockDelay);

	lpModelInfo->m_nPixelOverlapMode = m_cboPixelOverlapMode.GetCurSel();
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("PIXEL_OVERLAP_MODE"),		lpModelInfo->m_nPixelOverlapMode);

	lpModelInfo->m_nClockRising = m_cmbClockRising.GetCurSel();
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("CLOCK_RISING"),			lpModelInfo->m_nClockRising);

	lpModelInfo->m_nHSyncPolarity = m_cmbHSyncPolarity.GetCurSel();
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("HSYNC_POLARITY"),			lpModelInfo->m_nHSyncPolarity);

	lpModelInfo->m_nVSyncPolarity = m_cmbVSyncPolarity.GetCurSel();
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("VSYNC_POLARITY"),			lpModelInfo->m_nVSyncPolarity);

	lpModelInfo->m_nOddEven = m_cmbOddEven.GetCurSel();
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("ODD_EVEN"),				lpModelInfo->m_nOddEven);

	lpModelInfo->m_nPowerOnSeqType01 = m_cmbOnSeqOp01.GetCurSel();
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_ON_SEQ_OP_01"), lpModelInfo->m_nPowerOnSeqType01);

	lpModelInfo->m_nPowerOnSeqType02 = m_cmbOnSeqOp02.GetCurSel();
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_ON_SEQ_OP_02"), lpModelInfo->m_nPowerOnSeqType02);

	lpModelInfo->m_nPowerOnSeqType03 = m_cmbOnSeqOp03.GetCurSel();
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_ON_SEQ_OP_03"), lpModelInfo->m_nPowerOnSeqType03);

	lpModelInfo->m_nPowerOnSeqType04 = m_cmbOnSeqOp04.GetCurSel();
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_ON_SEQ_OP_04"), lpModelInfo->m_nPowerOnSeqType04);

	lpModelInfo->m_nPowerOnSeqType05 = m_cmbOnSeqOp05.GetCurSel();
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_ON_SEQ_OP_05"), lpModelInfo->m_nPowerOnSeqType05);

	lpModelInfo->m_nPowerOnSeqType06 = m_cmbOnSeqOp06.GetCurSel();
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_ON_SEQ_OP_06"), lpModelInfo->m_nPowerOnSeqType06);

	lpModelInfo->m_nPowerOnSeqType07 = m_cmbOnSeqOp07.GetCurSel();
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_ON_SEQ_OP_07"), lpModelInfo->m_nPowerOnSeqType07);

	lpModelInfo->m_nPowerOnSeqType08 = m_cmbOnSeqOp08.GetCurSel();
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_ON_SEQ_OP_08"), lpModelInfo->m_nPowerOnSeqType08);

	lpModelInfo->m_nPowerOnSeqType09 = m_cmbOnSeqOp09.GetCurSel();
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_ON_SEQ_OP_09"), lpModelInfo->m_nPowerOnSeqType09);

	lpModelInfo->m_nPowerOnSeqType10 = m_cmbOnSeqOp10.GetCurSel();
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_ON_SEQ_OP_10"), lpModelInfo->m_nPowerOnSeqType10);

	lpModelInfo->m_nPowerOnSeqType11 = m_cmbOnSeqOp11.GetCurSel();
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_ON_SEQ_OP_11"), lpModelInfo->m_nPowerOnSeqType11);

	lpModelInfo->m_nPowerOnSeqType12 = m_cmbOnSeqOp12.GetCurSel();
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_ON_SEQ_OP_12"), lpModelInfo->m_nPowerOnSeqType12);

	lpModelInfo->m_nPowerOnSeqType13 = m_cmbOnSeqOp13.GetCurSel();
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_ON_SEQ_OP_13"), lpModelInfo->m_nPowerOnSeqType13);

	lpModelInfo->m_nPowerOnSeqType14 = m_cmbOnSeqOp14.GetCurSel();
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_ON_SEQ_OP_14"), lpModelInfo->m_nPowerOnSeqType14);

	lpModelInfo->m_nPowerOnSeqType15 = m_cmbOnSeqOp15.GetCurSel();
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_ON_SEQ_OP_15"), lpModelInfo->m_nPowerOnSeqType15);

	lpModelInfo->m_nPowerOnSeqType16 = m_cmbOnSeqOp16.GetCurSel();
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_ON_SEQ_OP_16"), lpModelInfo->m_nPowerOnSeqType16);

	lpModelInfo->m_nPowerOnSeqType17 = m_cmbOnSeqOp17.GetCurSel();
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_ON_SEQ_OP_17"), lpModelInfo->m_nPowerOnSeqType17);

	lpModelInfo->m_nPowerOffSeqType01 = m_cmbOffSeqOp01.GetCurSel();
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_OFF_SEQ_OP_01"), lpModelInfo->m_nPowerOffSeqType01);

	lpModelInfo->m_nPowerOffSeqType02 = m_cmbOffSeqOp02.GetCurSel();
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_OFF_SEQ_OP_02"), lpModelInfo->m_nPowerOffSeqType02);

	lpModelInfo->m_nPowerOffSeqType03 = m_cmbOffSeqOp03.GetCurSel();
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_OFF_SEQ_OP_03"), lpModelInfo->m_nPowerOffSeqType03);

	lpModelInfo->m_nPowerOffSeqType04 = m_cmbOffSeqOp04.GetCurSel();
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_OFF_SEQ_OP_04"), lpModelInfo->m_nPowerOffSeqType04);

	lpModelInfo->m_nPowerOffSeqType05 = m_cmbOffSeqOp05.GetCurSel();
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_OFF_SEQ_OP_05"), lpModelInfo->m_nPowerOffSeqType05);

	lpModelInfo->m_nPowerOffSeqType06 = m_cmbOffSeqOp06.GetCurSel();
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_OFF_SEQ_OP_06"), lpModelInfo->m_nPowerOffSeqType06);

	lpModelInfo->m_nPowerOffSeqType07 = m_cmbOffSeqOp07.GetCurSel();
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_OFF_SEQ_OP_07"), lpModelInfo->m_nPowerOffSeqType07);

	lpModelInfo->m_nPowerOffSeqType08 = m_cmbOffSeqOp08.GetCurSel();
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_OFF_SEQ_OP_08"), lpModelInfo->m_nPowerOffSeqType08);

	lpModelInfo->m_nPowerOffSeqType09 = m_cmbOffSeqOp09.GetCurSel();
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_OFF_SEQ_OP_09"), lpModelInfo->m_nPowerOffSeqType09);

	lpModelInfo->m_nPowerOffSeqType10 = m_cmbOffSeqOp10.GetCurSel();
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_OFF_SEQ_OP_10"), lpModelInfo->m_nPowerOffSeqType10);

	lpModelInfo->m_nPowerOffSeqType11 = m_cmbOffSeqOp11.GetCurSel();
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_OFF_SEQ_OP_11"), lpModelInfo->m_nPowerOffSeqType11);

	lpModelInfo->m_nPowerOffSeqType12 = m_cmbOffSeqOp12.GetCurSel();
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_OFF_SEQ_OP_12"), lpModelInfo->m_nPowerOffSeqType12);

	lpModelInfo->m_nPowerOffSeqType13 = m_cmbOffSeqOp13.GetCurSel();
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_OFF_SEQ_OP_13"), lpModelInfo->m_nPowerOffSeqType13);

	lpModelInfo->m_nPowerOffSeqType14 = m_cmbOffSeqOp14.GetCurSel();
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_OFF_SEQ_OP_14"), lpModelInfo->m_nPowerOffSeqType14);

	lpModelInfo->m_nPowerOffSeqType15 = m_cmbOffSeqOp15.GetCurSel();
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_OFF_SEQ_OP_15"), lpModelInfo->m_nPowerOffSeqType15);

	lpModelInfo->m_nPowerOffSeqType16 = m_cmbOffSeqOp16.GetCurSel();
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_OFF_SEQ_OP_16"), lpModelInfo->m_nPowerOffSeqType16);

	lpModelInfo->m_nPowerOffSeqType17 = m_cmbOffSeqOp17.GetCurSel();
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_OFF_SEQ_OP_17"), lpModelInfo->m_nPowerOffSeqType17);

	m_edtOnSeqDelay01.GetWindowTextW(sdata);
	lpModelInfo->m_nPowerOnSeqDelay01 = (int)_ttoi(sdata);
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_ON_SEQ_DELAY_01"), lpModelInfo->m_nPowerOnSeqDelay01);

	m_edtOnSeqDelay02.GetWindowTextW(sdata);
	lpModelInfo->m_nPowerOnSeqDelay02 = (int)_ttoi(sdata);
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_ON_SEQ_DELAY_02"), lpModelInfo->m_nPowerOnSeqDelay02);

	m_edtOnSeqDelay03.GetWindowTextW(sdata);
	lpModelInfo->m_nPowerOnSeqDelay03 = (int)_ttoi(sdata);
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_ON_SEQ_DELAY_03"), lpModelInfo->m_nPowerOnSeqDelay03);

	m_edtOnSeqDelay04.GetWindowTextW(sdata);
	lpModelInfo->m_nPowerOnSeqDelay04 = (int)_ttoi(sdata);
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_ON_SEQ_DELAY_04"), lpModelInfo->m_nPowerOnSeqDelay04);

	m_edtOnSeqDelay05.GetWindowTextW(sdata);
	lpModelInfo->m_nPowerOnSeqDelay05 = (int)_ttoi(sdata);
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_ON_SEQ_DELAY_05"), lpModelInfo->m_nPowerOnSeqDelay05);

	m_edtOnSeqDelay06.GetWindowTextW(sdata);
	lpModelInfo->m_nPowerOnSeqDelay06 = (int)_ttoi(sdata);
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_ON_SEQ_DELAY_06"), lpModelInfo->m_nPowerOnSeqDelay06);

	m_edtOnSeqDelay07.GetWindowTextW(sdata);
	lpModelInfo->m_nPowerOnSeqDelay07 = (int)_ttoi(sdata);
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_ON_SEQ_DELAY_07"), lpModelInfo->m_nPowerOnSeqDelay07);

	m_edtOnSeqDelay08.GetWindowTextW(sdata);
	lpModelInfo->m_nPowerOnSeqDelay08 = (int)_ttoi(sdata);
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_ON_SEQ_DELAY_08"), lpModelInfo->m_nPowerOnSeqDelay08);

	m_edtOnSeqDelay09.GetWindowTextW(sdata);
	lpModelInfo->m_nPowerOnSeqDelay09 = (int)_ttoi(sdata);
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_ON_SEQ_DELAY_09"), lpModelInfo->m_nPowerOnSeqDelay09);

	m_edtOnSeqDelay10.GetWindowTextW(sdata);
	lpModelInfo->m_nPowerOnSeqDelay10 = (int)_ttoi(sdata);
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_ON_SEQ_DELAY_10"), lpModelInfo->m_nPowerOnSeqDelay10);

	m_edtOnSeqDelay11.GetWindowTextW(sdata);
	lpModelInfo->m_nPowerOnSeqDelay11 = (int)_ttoi(sdata);
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_ON_SEQ_DELAY_11"), lpModelInfo->m_nPowerOnSeqDelay11);

	m_edtOnSeqDelay12.GetWindowTextW(sdata);
	lpModelInfo->m_nPowerOnSeqDelay12 = (int)_ttoi(sdata);
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_ON_SEQ_DELAY_12"), lpModelInfo->m_nPowerOnSeqDelay12);

	m_edtOnSeqDelay13.GetWindowTextW(sdata);
	lpModelInfo->m_nPowerOnSeqDelay13= (int)_ttoi(sdata);
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_ON_SEQ_DELAY_13"), lpModelInfo->m_nPowerOnSeqDelay13);

	m_edtOnSeqDelay14.GetWindowTextW(sdata);
	lpModelInfo->m_nPowerOnSeqDelay14 = (int)_ttoi(sdata);
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_ON_SEQ_DELAY_14"), lpModelInfo->m_nPowerOnSeqDelay14);

	m_edtOnSeqDelay15.GetWindowTextW(sdata);
	lpModelInfo->m_nPowerOnSeqDelay15 = (int)_ttoi(sdata);
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_ON_SEQ_DELAY_15"), lpModelInfo->m_nPowerOnSeqDelay15);

	m_edtOnSeqDelay16.GetWindowTextW(sdata);
	lpModelInfo->m_nPowerOnSeqDelay16 = (int)_ttoi(sdata);
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_ON_SEQ_DELAY_16"), lpModelInfo->m_nPowerOnSeqDelay16);

	m_edtOnSeqDelay17.GetWindowTextW(sdata);
	lpModelInfo->m_nPowerOnSeqDelay17 = (int)_ttoi(sdata);
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_ON_SEQ_DELAY_17"), lpModelInfo->m_nPowerOnSeqDelay17);

	m_edtOffSeqDelay01.GetWindowTextW(sdata);
	lpModelInfo->m_nPowerOffSeqDelay01 = (int)_ttoi(sdata);
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_OFF_SEQ_DELAY_01"), lpModelInfo->m_nPowerOffSeqDelay01);

	m_edtOffSeqDelay02.GetWindowTextW(sdata);
	lpModelInfo->m_nPowerOffSeqDelay02 = (int)_ttoi(sdata);
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_OFF_SEQ_DELAY_02"), lpModelInfo->m_nPowerOffSeqDelay02);

	m_edtOffSeqDelay03.GetWindowTextW(sdata);
	lpModelInfo->m_nPowerOffSeqDelay03 = (int)_ttoi(sdata);
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_OFF_SEQ_DELAY_03"), lpModelInfo->m_nPowerOffSeqDelay03);

	m_edtOffSeqDelay04.GetWindowTextW(sdata);
	lpModelInfo->m_nPowerOffSeqDelay04 = (int)_ttoi(sdata);
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_OFF_SEQ_DELAY_04"), lpModelInfo->m_nPowerOffSeqDelay04);

	m_edtOffSeqDelay05.GetWindowTextW(sdata);
	lpModelInfo->m_nPowerOffSeqDelay05 = (int)_ttoi(sdata);
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_OFF_SEQ_DELAY_05"), lpModelInfo->m_nPowerOffSeqDelay05);

	m_edtOffSeqDelay06.GetWindowTextW(sdata);
	lpModelInfo->m_nPowerOffSeqDelay06 = (int)_ttoi(sdata);
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_OFF_SEQ_DELAY_06"), lpModelInfo->m_nPowerOffSeqDelay06);

	m_edtOffSeqDelay07.GetWindowTextW(sdata);
	lpModelInfo->m_nPowerOffSeqDelay07 = (int)_ttoi(sdata);
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_OFF_SEQ_DELAY_07"), lpModelInfo->m_nPowerOffSeqDelay07);

	m_edtOffSeqDelay08.GetWindowTextW(sdata);
	lpModelInfo->m_nPowerOffSeqDelay08 = (int)_ttoi(sdata);
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_OFF_SEQ_DELAY_08"), lpModelInfo->m_nPowerOffSeqDelay08);

	m_edtOffSeqDelay09.GetWindowTextW(sdata);
	lpModelInfo->m_nPowerOffSeqDelay09 = (int)_ttoi(sdata);
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_OFF_SEQ_DELAY_09"), lpModelInfo->m_nPowerOffSeqDelay09);

	m_edtOffSeqDelay10.GetWindowTextW(sdata);
	lpModelInfo->m_nPowerOffSeqDelay10 = (int)_ttoi(sdata);
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_OFF_SEQ_DELAY_10"), lpModelInfo->m_nPowerOffSeqDelay10);

	m_edtOffSeqDelay11.GetWindowTextW(sdata);
	lpModelInfo->m_nPowerOffSeqDelay11 = (int)_ttoi(sdata);
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_OFF_SEQ_DELAY_11"), lpModelInfo->m_nPowerOffSeqDelay11);

	m_edtOffSeqDelay12.GetWindowTextW(sdata);
	lpModelInfo->m_nPowerOffSeqDelay12 = (int)_ttoi(sdata);
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_OFF_SEQ_DELAY_12"), lpModelInfo->m_nPowerOffSeqDelay12);

	m_edtOffSeqDelay13.GetWindowTextW(sdata);
	lpModelInfo->m_nPowerOffSeqDelay13 = (int)_ttoi(sdata);
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_OFF_SEQ_DELAY_13"), lpModelInfo->m_nPowerOffSeqDelay13);

	m_edtOffSeqDelay14.GetWindowTextW(sdata);
	lpModelInfo->m_nPowerOffSeqDelay14 = (int)_ttoi(sdata);
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_OFF_SEQ_DELAY_14"), lpModelInfo->m_nPowerOffSeqDelay14);

	m_edtOffSeqDelay15.GetWindowTextW(sdata);
	lpModelInfo->m_nPowerOffSeqDelay15 = (int)_ttoi(sdata);
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_OFF_SEQ_DELAY_15"), lpModelInfo->m_nPowerOffSeqDelay15);

	m_edtOffSeqDelay16.GetWindowTextW(sdata);
	lpModelInfo->m_nPowerOffSeqDelay16 = (int)_ttoi(sdata);
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_OFF_SEQ_DELAY_16"), lpModelInfo->m_nPowerOffSeqDelay16);

	m_edtOffSeqDelay17.GetWindowTextW(sdata);
	lpModelInfo->m_nPowerOffSeqDelay17 = (int)_ttoi(sdata);
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("POWER_OFF_SEQ_DELAY_17"), lpModelInfo->m_nPowerOffSeqDelay17);

	m_edtVccSet.GetWindowText(sdata);
	lpModelInfo->m_fVoltVcc	= (float)_tstof(sdata);
	Write_ModelFile(modelName,	_T("MODEL_INFO"),	_T("VCC"),					lpModelInfo->m_fVoltVcc);

	m_edtVddSet.GetWindowText(sdata);
	lpModelInfo->m_fVoltVdd	= (float)_tstof(sdata);
	Write_ModelFile(modelName,	_T("MODEL_INFO"),	_T("VDD"),					lpModelInfo->m_fVoltVdd);

	m_edtVghSet.GetWindowText(sdata);
	lpModelInfo->m_fVoltVgh = (float)_tstof(sdata);
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("VGH"), lpModelInfo->m_fVoltVgh);

	m_edtVglSet.GetWindowText(sdata);
	lpModelInfo->m_fVoltVgl = (float)_tstof(sdata);
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("VGL"), lpModelInfo->m_fVoltVgl);

	m_edtVccHighLimitSet.GetWindowText(sdata);
	lpModelInfo->m_fLimitVccMax	= (float)_tstof(sdata);
	Write_ModelFile(modelName,	_T("MODEL_INFO"),	_T("VCC_HIGH_LIMIT"),		lpModelInfo->m_fLimitVccMax);

	m_edtVccLowLimitSet.GetWindowText(sdata);
	lpModelInfo->m_fLimitVccMin = (float)_tstof(sdata);
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("VCC_LOW_LIMIT"), lpModelInfo->m_fLimitVccMin);

	m_edtVddHighLimitSet.GetWindowText(sdata);
	lpModelInfo->m_fLimitVddMax	= (float)_tstof(sdata);
	Write_ModelFile(modelName,	_T("MODEL_INFO"),	_T("VDD_HIGH_LIMIT"),		lpModelInfo->m_fLimitVddMax);

	m_edtVddLowLimitSet.GetWindowText(sdata);
	lpModelInfo->m_fLimitVddMin = (float)_tstof(sdata);
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("VDD_LOW_LIMIT"), lpModelInfo->m_fLimitVddMin);

	m_edtIccHighLimitSet.GetWindowText(sdata);
	lpModelInfo->m_fLimitIccMax	= (float)_tstof(sdata);
	Write_ModelFile(modelName,	_T("MODEL_INFO"),	_T("ICC_HIGH_LIMIT"),		lpModelInfo->m_fLimitIccMax);

	m_edtIccLowLimitSet.GetWindowText(sdata);
	lpModelInfo->m_fLimitIccMin = (float)_tstof(sdata);
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("ICC_LOW_LIMIT"), lpModelInfo->m_fLimitIccMin);

	m_edtIddHighLimitSet.GetWindowText(sdata);
	lpModelInfo->m_fLimitIddMax	= (float)_tstof(sdata);
	Write_ModelFile(modelName,	_T("MODEL_INFO"),	_T("IDD_HIGH_LIMIT"),		lpModelInfo->m_fLimitIddMax);

	m_edtIddLowLimitSet.GetWindowText(sdata);
	lpModelInfo->m_fLimitIddMin = (float)_tstof(sdata);
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("IDD_LOW_LIMIT"), lpModelInfo->m_fLimitIddMin);

	m_edtIblHighLimitSet.GetWindowText(sdata);
	lpModelInfo->m_fLimitIblMax = (float)_tstof(sdata);
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("IBL_HIGH_LIMIT"), lpModelInfo->m_fLimitIblMax);

	m_edtIblLowLimitSet.GetWindowText(sdata);
	lpModelInfo->m_fLimitIblMin = (float)_tstof(sdata);
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("IBL_LOW_LIMIT"), lpModelInfo->m_fLimitIblMin);

	m_edtVblHighLimitSet.GetWindowText(sdata);
	lpModelInfo->m_fLimitVblMax = (float)_tstof(sdata);
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("VBL_HIGH_LIMIT"), lpModelInfo->m_fLimitVblMax);

	m_edtVblLowLimitSet.GetWindowText(sdata);
	lpModelInfo->m_fLimitVblMin = (float)_tstof(sdata);
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("VBL_LOW_LIMIT"), lpModelInfo->m_fLimitVblMin);

	m_edtVglHighLimitSet.GetWindowText(sdata);
	lpModelInfo->m_fLimitVglMax = (float)_tstof(sdata);
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("VGL_HIGH_LIMIT"), lpModelInfo->m_fLimitVglMax);

	m_edtVglLowLimitSet.GetWindowText(sdata);
	lpModelInfo->m_fLimitVglMin = (float)_tstof(sdata);
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("VGL_LOW_LIMIT"), lpModelInfo->m_fLimitVglMin);

	m_edtVghHighLimitSet.GetWindowText(sdata);
	lpModelInfo->m_fLimitVghMax = (float)_tstof(sdata);
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("VGH_HIGH_LIMIT"), lpModelInfo->m_fLimitVghMax);

	m_edtVghLowLimitSet.GetWindowText(sdata);
	lpModelInfo->m_fLimitVghMin = (float)_tstof(sdata);
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("VGH_LOW_LIMIT"), lpModelInfo->m_fLimitVghMin);

	m_edtIglHighLimitSet.GetWindowText(sdata);
	lpModelInfo->m_fLimitIglMax = (float)_tstof(sdata);
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("IGL_HIGH_LIMIT"), lpModelInfo->m_fLimitIglMax);

	m_edtIglLowLimitSet.GetWindowText(sdata);
	lpModelInfo->m_fLimitIglMin = (float)_tstof(sdata);
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("IGL_LOW_LIMIT"), lpModelInfo->m_fLimitIglMin);

	m_edtIghHighLimitSet.GetWindowText(sdata);
	lpModelInfo->m_fLimitIghMax = (float)_tstof(sdata);
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("IGH_HIGH_LIMIT"), lpModelInfo->m_fLimitIghMax);

	m_edtIghLowLimitSet.GetWindowText(sdata);
	lpModelInfo->m_fLimitIghMin = (float)_tstof(sdata);
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("IGH_LOW_LIMIT"), lpModelInfo->m_fLimitIghMin);

	lpModelInfo->m_nEdidUse = m_cboEdidOnOff.GetCurSel();
	Write_ModelFile(modelName,	_T("MODEL_INFO"),	_T("EDID_USE"),				lpModelInfo->m_nEdidUse);

	lpModelInfo->m_nEdidLine = m_cboEdidLine.GetCurSel();
	Write_ModelFile(modelName,	_T("MODEL_INFO"),	_T("EDID_LINE"),			lpModelInfo->m_nEdidLine);

	lpModelInfo->m_nEEPRomType = m_cboEepType.GetCurSel();
	Write_ModelFile(modelName,	_T("MODEL_INFO"),	_T("EEPROM_TYPE"),			lpModelInfo->m_nEEPRomType);

	lpModelInfo->m_nEEPRomAddr = m_cboEepAddr.GetCurSel();
	Write_ModelFile(modelName,	_T("MODEL_INFO"),	_T("EEPROM_ADDR"),			lpModelInfo->m_nEEPRomAddr);

	lpModelInfo->m_nEdidSize = m_cboEdidSize.GetCurSel();
	Write_ModelFile(modelName,	_T("MODEL_INFO"),	_T("EDID_SIZE"),			lpModelInfo->m_nEdidSize);

	lpModelInfo->m_nCableOpenUse = m_cmbCableOpenUse.GetCurSel();
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("CABLE_OPEN_USE"), lpModelInfo->m_nCableOpenUse);

	lpModelInfo->m_nShortTestUse = m_cmbShortTestUse.GetCurSel();
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("SHORT_TEST_USE"), lpModelInfo->m_nShortTestUse);

	lpModelInfo->m_nIdInputType = m_cmbIdInputType.GetCurSel();
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("ID_INPUT_TYPE"), lpModelInfo->m_nIdInputType);

	m_edtIdLengthMin.GetWindowText(sdata);
	lpModelInfo->m_nIdLengthMin = _ttoi(sdata);
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("ID_LENGTH_MIN"), lpModelInfo->m_nIdLengthMin);

	m_edtIdLengthMax.GetWindowText(sdata);
	lpModelInfo->m_nIdLengthMax = _ttoi(sdata);
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("ID_LENGTH_MAX"), lpModelInfo->m_nIdLengthMax);

	m_edtBluMin.GetWindowText(sdata);
	lpModelInfo->m_nBluMin = _ttoi(sdata);
	Write_ModelFile(modelName,	_T("MODEL_INFO"),	_T("BLU_MIN"),				lpModelInfo->m_nBluMin);

	lpModelInfo->m_nI2cPullup = m_cmbI2cPullUp.GetCurSel();
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("I2C_PULLUP"), lpModelInfo->m_nI2cPullup);

	lpModelInfo->m_nI2cFreq = m_cmbI2cFreq.GetCurSel();
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("I2C_FREQ"), lpModelInfo->m_nI2cFreq);

	lpModelInfo->m_nI2cLevel = m_cmbI2cLevel.GetCurSel();
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("I2C_LEVEL"), lpModelInfo->m_nI2cLevel);

	m_edtVbrSet.GetWindowText(sdata);
	lpModelInfo->m_fVoltVbr = (float)_tstof(sdata);
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("VBR"), lpModelInfo->m_fVoltVbr);

	m_edtVblSet.GetWindowText(sdata);
	lpModelInfo->m_fVoltVbl = (float)_tstof(sdata);
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("VBL"), lpModelInfo->m_fVoltVbl);

	m_edtPowerVcom1.GetWindowText(sdata);
	lpModelInfo->m_fVoltVcom1 = (float)_tstof(sdata);
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("VCOM1"), lpModelInfo->m_fVoltVcom1);

	m_edtPowerVcom2.GetWindowText(sdata);
	lpModelInfo->m_fVoltVcom2 = (float)_tstof(sdata);
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("VCOM2"), lpModelInfo->m_fVoltVcom2);

	m_edtPwmFreq.GetWindowText(sdata);
	lpModelInfo->m_nPwmFreq = _ttoi(sdata);
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("PWM_FREQ"), lpModelInfo->m_nPwmFreq);

	m_edtPwmDuty.GetWindowText(sdata);
	lpModelInfo->m_nPwmDuty = _ttoi(sdata);
	Write_ModelFile(modelName, _T("MODEL_INFO"), _T("PWM_DUTY"), lpModelInfo->m_nPwmDuty);


	int i = 0, nLbItemCnt = 0;
	CString strKey = _T(""), strPtnInfo = _T(""), strTemp = _T("");

	nLbItemCnt = m_lcPtnSetList.GetItemCount();

	if(nLbItemCnt < lpModelInfo->m_nLbCnt ) // When ListControl Item is deleted, Compare gnLbCnt to nLbItenCnt. 
	{
		strTemp.Empty();

		for(i = nLbItemCnt; i < lpModelInfo->m_nLbCnt; i++)
		{
			strKey.Format(_T("PTN%2d"), i);

			Write_ModelFile(modelName,	_T("PATTERN_INFO"),	strKey,	strTemp);//Write_ModFile(_T("PATTERN"), strKey.GetBuffer(0)/*szKey*/, NULL, m_strModelNamde.GetBuffer(0));
		}
		lpModelInfo->m_nLbCnt = nLbItemCnt;
	}

	for(i=0; i<nLbItemCnt; i++)
	{
		strTemp.Format(_T("%s"),m_lcPtnSetList.GetItemText(i, 0) );	
		strPtnInfo = strTemp;

		strTemp.Format(_T(",%s"),m_lcPtnSetList.GetItemText(i, 1) );
		strPtnInfo += strTemp;

		strTemp.Format(_T(",%s"),m_lcPtnSetList.GetItemText(i, 2) );		
		strPtnInfo += strTemp;

		strTemp.Format(_T(",%s"),m_lcPtnSetList.GetItemText(i, 3) );
		strPtnInfo += strTemp;

		strTemp.Format(_T(",%s"),m_lcPtnSetList.GetItemText(i, 4) );		
		strPtnInfo += strTemp;

		strTemp.Format(_T(",%s"),m_lcPtnSetList.GetItemText(i, 5) );
		strPtnInfo += strTemp;

		strTemp.Format(_T(",%s"),m_lcPtnSetList.GetItemText(i, 6) );		
		strPtnInfo += strTemp;

		strTemp.Format(_T(",%s"),m_lcPtnSetList.GetItemText(i, 7) );
		strPtnInfo += strTemp;

		strTemp.Format(_T(",%s"),m_lcPtnSetList.GetItemText(i, 8) );		
		strPtnInfo += strTemp;

		strTemp.Format(_T(",%s"),m_lcPtnSetList.GetItemText(i, 9) );
		strPtnInfo += strTemp;

		strTemp.Format(_T(",%s"),m_lcPtnSetList.GetItemText(i, 10) );
		strPtnInfo += strTemp;

		strTemp.Format(_T(",%s"),m_lcPtnSetList.GetItemText(i, 11) );
		strPtnInfo += strTemp;

		strTemp.Format(_T(",%s"),m_lcPtnSetList.GetItemText(i, 12) );
		if(!strTemp.CompareNoCase(_T("ON")))
			strPtnInfo += _T("1");
		else
			strPtnInfo += _T("0");

		strTemp.Format(_T(",%s"),m_lcPtnSetList.GetItemText(i, 13) );
		strPtnInfo += strTemp;

		strTemp.Format(_T(",%s"),m_lcPtnSetList.GetItemText(i, 14) );
		strPtnInfo += strTemp;

		strKey.Format(_T("PTN%2d"), i);

		Write_ModelFile(modelName,	_T("PATTERN_INFO"),	strKey,	NULL);//Write_ModFile(_T("PATTERN"), strKey.GetBuffer(0), NULL, m_strModelNamde.GetBuffer(0));

		Write_ModelFile(modelName,	_T("PATTERN_INFO"),	strKey,	strPtnInfo);//Write_ModFile(_T("PATTERN"), strKey.GetBuffer(0), strPtnInfo.GetBuffer(0), m_strModelNamde.GetBuffer(0));
	}
}

void CModelInfo::OnBnClickedBtnSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_saveModelInfoData();
}

void CModelInfo::Lf_saveModelInfoData()
{
	CString strCurrentModel, strSaveModel, strSource, strTarget;

	GetDlgItem(IDC_STT_CUR_MODEL)->GetWindowText(strCurrentModel);
	GetDlgItem(IDC_EDT_CREATE_MODEL)->GetWindowText(strSaveModel);

	if (strCurrentModel.Compare(strSaveModel))
	{
		strSource.Format(_T(".\\Model\\%s.mod"), strCurrentModel);
		strTarget.Format(_T(".\\Model\\%s.mod"), strSaveModel);

		// Model File Copy
		CopyFile(strSource, strTarget, FALSE);

		Lf_saveCtrlData(strSaveModel);

		Write_SysIniFile(_T("SYSTEM"), _T("LAST_MODELNAME"), strSaveModel);

	}
	else
	{
		Lf_saveCtrlData(lpSystemInfo->m_sModelName);

	}
	m_pApp->Gf_loadModelData();
	/*CInitialize initDlg;
	initDlg.DoModal();*/
	UpdateData(FALSE);
	AfxGetApp()->GetMainWnd()->SendMessage(WM_UPDATE_SYSTEM_INFO, NULL, NULL);
}

void CModelInfo::Lf_setSwapData(int pos1, int pos2)
{
	UpdateData(TRUE);
	WCHAR temp1 [64] = {0,};
	WCHAR temp2 [64] = {0,};
	CString strTemp1 = _T(""), strTemp2 = _T("");
	int i = 0;

	for(i=0;i<11;i++)
	{		
		m_lcPtnSetList.GetItemText(pos1, i, temp1, 30);
		m_lcPtnSetList.GetItemText(pos2, i, temp2, 30);
		m_lcPtnSetList.SetItem( pos2, i, LVIF_TEXT, temp1, 0, LVIF_STATE, 0, 0);
		m_lcPtnSetList.SetItem( pos1, i, LVIF_TEXT, temp2, 0, LVIF_STATE, 0, 0);
	}

	POSITION pos = m_lcPtnSetList.GetFirstSelectedItemPosition();
	int position = m_lcPtnSetList.GetNextSelectedItem(pos);

	UpdateData(FALSE);
}

void CModelInfo::Lf_setPtnDataChange(int sel)
{
	CString sdata=_T("");
	CString strPtnName;
	int nAllPtn=0;

	UpdateData(TRUE);

	strPtnName = m_lcPtnSetList.GetItemText(sel,0);
	nAllPtn = m_cboPtnName.FindStringExact(nAllPtn, strPtnName);
	 
	if(nAllPtn == CB_ERR)
	{
		AfxMessageBox(_T("Pattern File Can Not Search..."));
		return;
	}
	if(nAllPtn == -1)
		nAllPtn = 0;

	m_cboPtnName.SetCurSel(nAllPtn);

	m_edtPtnVCC.SetWindowText(m_lcPtnSetList.GetItemText(sel,1));
	m_edtPtnVDD.SetWindowText(m_lcPtnSetList.GetItemText(sel,2));
	m_edtPtnTMS.SetWindowText(m_lcPtnSetList.GetItemText(sel,3));
	m_edtPtnVSync.SetWindowText(m_lcPtnSetList.GetItemText(sel,4));
	m_edtPtnIccLow.SetWindowText(m_lcPtnSetList.GetItemText(sel, 5));
	m_edtPtnIccHigh.SetWindowText(m_lcPtnSetList.GetItemText(sel, 6));
	m_edtPtnIddLow.SetWindowText(m_lcPtnSetList.GetItemText(sel, 7));
	m_edtPtnIddHigh.SetWindowText(m_lcPtnSetList.GetItemText(sel, 8));
	m_edtPtnBlu.SetWindowText(m_lcPtnSetList.GetItemText(sel,9));
	
	sdata = m_lcPtnSetList.GetItemText(sel, 10);
	if(!sdata.CompareNoCase(_T("ON")))
		m_cmbPtnPower.SetCurSel(1);
	else
		m_cmbPtnPower.SetCurSel(0);


	////////////////////////////////////////////////////////////////////////////////
	if (strPtnName.Find(_T(".BMP")) != -1)
	{
		CRect rc;
		CString sPath;
		GetDlgItem(IDC_STT_PTN_IMAGE_SIZE)->GetWindowRect(rc);
		ScreenToClient(rc);
		rc.right -= 10;
		rc.bottom -= 20;
		sPath.Format(_T(".\\Pattern\\BMP\\%s"), strPtnName);
		HBITMAP hBitmap = (HBITMAP)LoadImage(AfxGetInstanceHandle(), sPath, IMAGE_BITMAP, rc.Width(), rc.Height(), LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		m_picPatternPreview.SetBitmap(hBitmap);
		Invalidate(FALSE);
	}
	else
		m_pApp->m_pPatternView->drawPattern(strPtnName);

	
	////////////////////////////////////////////////////////////////////////////////
	UpdateData(FALSE);
}

void CModelInfo::Lf_setChangeFont()
{

	if (m_nChangeFont & 0x0001)	{GetDlgItem(IDC_STT_VCC_CLK)->SetFont(&m_Font[1]);}
	else						{GetDlgItem(IDC_STT_VCC_CLK)->SetFont(&m_Font[2]);}

	if (m_nChangeFont & 0x0002)	{GetDlgItem(IDC_STT_VDD_CLK)->SetFont(&m_Font[1]);}
	else						{GetDlgItem(IDC_STT_VDD_CLK)->SetFont(&m_Font[2]);}

	if (m_nChangeFont & 0x0004)	{GetDlgItem(IDC_STT_TMS_CLK)->SetFont(&m_Font[1]);}
	else						{GetDlgItem(IDC_STT_TMS_CLK)->SetFont(&m_Font[2]);}

	if (m_nChangeFont & 0x0008)	{GetDlgItem(IDC_STT_VSYNC_CLK)->SetFont(&m_Font[1]);}
	else						{GetDlgItem(IDC_STT_VSYNC_CLK)->SetFont(&m_Font[2]);}

	if (m_nChangeFont & 0x0010)	{GetDlgItem(IDC_STT_ICC_LOW)->SetFont(&m_Font[1]);}
	else						{GetDlgItem(IDC_STT_ICC_LOW)->SetFont(&m_Font[2]);}

	if (m_nChangeFont & 0x0020) { GetDlgItem(IDC_STT_ICC_HIGH)->SetFont(&m_Font[1]); }
	else						{ GetDlgItem(IDC_STT_ICC_HIGH)->SetFont(&m_Font[2]); }

	if (m_nChangeFont & 0x0040) { GetDlgItem(IDC_STT_IDD_LOW)->SetFont(&m_Font[1]); }
	else						{ GetDlgItem(IDC_STT_IDD_LOW)->SetFont(&m_Font[2]); }

	if (m_nChangeFont & 0x0080) { GetDlgItem(IDC_STT_IDD_HIGH)->SetFont(&m_Font[1]); }
	else						{ GetDlgItem(IDC_STT_IDD_HIGH)->SetFont(&m_Font[2]); }

	if (m_nChangeFont & 0x0100) { GetDlgItem(IDC_STT_BLU_CLK)->SetFont(&m_Font[1]); }
	else						{ GetDlgItem(IDC_STT_BLU_CLK)->SetFont(&m_Font[2]); }

	if (m_nChangeFont & 0x0200) { GetDlgItem(IDC_STT_PTN_POWER_CLK)->SetFont(&m_Font[1]); }
	else						{ GetDlgItem(IDC_STT_PTN_POWER_CLK)->SetFont(&m_Font[2]); }
}

void CModelInfo::OnBnClickedBtnAdd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	//int nFgValue;
	int nPos, nCnt;
	CString sdata=_T("");

	nCnt = m_lcPtnSetList.GetItemCount();

	POSITION Pos = m_lcPtnSetList.GetFirstSelectedItemPosition();
	nPos = m_lcPtnSetList.GetNextSelectedItem(Pos);

	if(nPos < 0)
	{
		nPos = nCnt;
	}

	m_cboPtnName.GetWindowText(sdata);
	m_lcPtnSetList.InsertItem(nPos, sdata);

	m_edtPtnVCC.GetWindowText(sdata);
	m_lcPtnSetList.SetItem(nPos, 1, LVIF_TEXT, sdata, 0, LVIF_STATE, 0, 0);

	m_edtPtnVDD.GetWindowText(sdata);
	m_lcPtnSetList.SetItem(nPos, 2, LVIF_TEXT, sdata, 0, LVIF_STATE, 0, 0);

	m_edtPtnTMS.GetWindowText(sdata);
	m_lcPtnSetList.SetItem(nPos, 3, LVIF_TEXT, sdata, 0, LVIF_STATE, 0, 0);

	m_edtPtnVSync.GetWindowText(sdata);
	m_lcPtnSetList.SetItem(nPos, 4, LVIF_TEXT, sdata, 0, LVIF_STATE, 0, 0);

	m_edtPtnIccLow.GetWindowText(sdata);
	m_lcPtnSetList.SetItem(nPos, 5, LVIF_TEXT, sdata, 0, LVIF_STATE, 0, 0);

	m_edtPtnIccHigh.GetWindowText(sdata);
	m_lcPtnSetList.SetItem(nPos, 6, LVIF_TEXT, sdata, 0, LVIF_STATE, 0, 0);

	m_edtPtnIddLow.GetWindowText(sdata);
	m_lcPtnSetList.SetItem(nPos, 7, LVIF_TEXT, sdata, 0, LVIF_STATE, 0, 0);

	m_edtPtnIddHigh.GetWindowText(sdata);
	m_lcPtnSetList.SetItem(nPos, 8, LVIF_TEXT, sdata, 0, LVIF_STATE, 0, 0);

	m_edtPtnBlu.GetWindowText(sdata);
	m_lcPtnSetList.SetItem(nPos, 9, LVIF_TEXT, sdata, 0, LVIF_STATE, 0, 0);

	m_cmbPtnPower.GetWindowText(sdata);
	m_lcPtnSetList.SetItem(nPos, 10, LVIF_TEXT, sdata, 0, LVIF_STATE, 0, 0);


	m_lcPtnSetList.SetSelectionMark(nPos); // Item Select & Focus
	m_lcPtnSetList.SetItemState(nPos, LVIS_SELECTED | LVIS_FOCUSED, LVNI_SELECTED | LVNI_FOCUSED);

	UpdateData(FALSE);
}

void CModelInfo::OnBnClickedBtnDelete()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	POSITION Pos = m_lcPtnSetList.GetFirstSelectedItemPosition();
	int nPos = m_lcPtnSetList.GetNextSelectedItem(Pos);
	if(nPos < 0)
	{
		return;
	}

	m_lcPtnSetList.DeleteItem(nPos);

	if(!m_lcPtnSetList.GetItemCount())
	{
		return;
	}
	else
	{
		if (m_lcPtnSetList.GetItemCount() <= nPos)
			nPos--;

		m_lcPtnSetList.SetSelectionMark(nPos);
		m_lcPtnSetList.SetItemState(nPos, LVIS_SELECTED | LVIS_FOCUSED, LVNI_SELECTED | LVNI_FOCUSED);
		m_lcPtnSetList.SetFocus();
	}
}

void CModelInfo::OnBnClickedBtnUp()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	POSITION pos = m_lcPtnSetList.GetFirstSelectedItemPosition();
	int position = m_lcPtnSetList.GetNextSelectedItem(pos);
	if(position < 1)
	{
		return;
	}

	Lf_setSwapData(position, position-1);

	m_lcPtnSetList.SetSelectionMark(position);
	m_lcPtnSetList.SetItemState(position-1, LVIS_SELECTED | LVIS_FOCUSED, LVNI_SELECTED | LVNI_FOCUSED);
	m_lcPtnSetList.SetFocus();
	UpdateData(FALSE);
}

void CModelInfo::OnBnClickedBtnDown()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	POSITION pos = m_lcPtnSetList.GetFirstSelectedItemPosition();

	int position = m_lcPtnSetList.GetNextSelectedItem(pos);
	int count = m_lcPtnSetList.GetItemCount();

	if(position > (count-2))
	{
		return;
	}

	Lf_setSwapData(position, position+1);

	m_lcPtnSetList.SetSelectionMark(position);
	m_lcPtnSetList.SetItemState(position+1, LVIS_SELECTED | LVIS_FOCUSED, LVNI_SELECTED | LVNI_FOCUSED);
	m_lcPtnSetList.SetFocus();
	UpdateData(FALSE);
}

void CModelInfo::OnBnClickedBtnChange()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	//int nFgValue;
	int nPos;
	CString sdata = _T("");

	/*m_edtPtnFg.GetWindowTextW(sdata);
	nFgValue=_ttoi(sdata);	

	switch(lpModelInfo->m_nSignalBit)
	{
	case SIG_6BIT:
		if(nFgValue>63)
		{
			AfxMessageBox(_T("GRAY VALUE ERROR. Setting Signal Bit 6, Gray Value Over"));
			return;
		}
		break;
	case SIG_8BIT:
		if(nFgValue>255)
		{
			AfxMessageBox(_T("GRAY VALUE ERROR. Setting Signal Bit 8, Gray Value Over"));
			return;
		}
		break;

	case SIG_10BIT:
		if(nFgValue>1023)
		{
			AfxMessageBox(_T("GRAY VALUE ERROR. Setting Signal Bit 10, Gray Value Over"));
			return;
		}
		break;
	}*/

	POSITION pos = m_lcPtnSetList.GetFirstSelectedItemPosition();
	nPos = m_lcPtnSetList.GetNextSelectedItem(pos);
	if(nPos < 0)
	{
		return;
	}
	
	m_cboPtnName.GetLBText(m_cboPtnName.GetCurSel(),sdata);
	m_lcPtnSetList.SetItem( nPos, 0, LVIF_TEXT, sdata, 0, LVIF_STATE, 0, 0);
	m_edtPtnVCC.GetWindowText(sdata);	m_lcPtnSetList.SetItem( nPos, 1, LVIF_TEXT, sdata, 0, LVIF_STATE, 0, 0);
	m_edtPtnVDD.GetWindowText(sdata);	m_lcPtnSetList.SetItem( nPos, 2, LVIF_TEXT, sdata, 0, LVIF_STATE, 0, 0);
	m_edtPtnTMS.GetWindowText(sdata);	m_lcPtnSetList.SetItem( nPos, 3, LVIF_TEXT, sdata, 0, LVIF_STATE, 0, 0);
	m_edtPtnVSync.GetWindowText(sdata);	m_lcPtnSetList.SetItem( nPos, 4, LVIF_TEXT, sdata, 0, LVIF_STATE, 0, 0);
	m_edtPtnIccLow.GetWindowText(sdata);	m_lcPtnSetList.SetItem( nPos, 5, LVIF_TEXT, sdata, 0, LVIF_STATE, 0, 0);
	m_edtPtnIccHigh.GetWindowText(sdata);	m_lcPtnSetList.SetItem(nPos, 6, LVIF_TEXT, sdata, 0, LVIF_STATE, 0, 0);
	m_edtPtnIddLow.GetWindowText(sdata);	m_lcPtnSetList.SetItem(nPos, 7, LVIF_TEXT, sdata, 0, LVIF_STATE, 0, 0);
	m_edtPtnIddHigh.GetWindowText(sdata);	m_lcPtnSetList.SetItem(nPos, 8, LVIF_TEXT, sdata, 0, LVIF_STATE, 0, 0);
	m_edtPtnBlu.GetWindowText(sdata);	m_lcPtnSetList.SetItem(nPos, 9, LVIF_TEXT, sdata, 0, LVIF_STATE, 0, 0);
	m_cmbPtnPower.GetWindowText(sdata);	m_lcPtnSetList.SetItem(nPos, 10, LVIF_TEXT, sdata, 0, LVIF_STATE, 0, 0);

	m_lcPtnSetList.EnsureVisible( nPos, FALSE);

	m_lcPtnSetList.SetSelectionMark(nPos); // 2007-09-12 : Item Select & Focus
	m_lcPtnSetList.SetItemState(nPos, LVIS_SELECTED | LVIS_FOCUSED, LVNI_SELECTED | LVNI_FOCUSED);
}

void CModelInfo::OnLvnItemchangedListPatternset(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if(pNMLV->iItem < 0)	return;
	if(pNMLV->uOldState && !pNMLV->uNewState)	return;
	if(!pNMLV->uOldState && !pNMLV->uNewState)	return;
	*pResult = 0;

	Lf_setPtnDataChange(pNMLV->iItem);
}

void CModelInfo::OnBnClickedBtnAll()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nVertical = 0, nHorizen = 0, nCnt = 0;
	CString sdata = _T("");

	nCnt = m_lcPtnSetList.GetItemCount();

	UpdateData(TRUE);


	if(m_nSelClkFlags == 1)
	{
		for(nVertical = 0; nVertical < nCnt; nVertical++)
		{
			m_edtPtnVCC.GetWindowText(sdata);
			m_lcPtnSetList.SetItem(nVertical, m_nSelClkFlags, LVIF_TEXT, sdata.GetBuffer(0), 0, LVIF_STATE,0 ,0);
		}
	}

	if(m_nSelClkFlags == 2)
	{
		for(nVertical = 0; nVertical < nCnt; nVertical++)
		{
			m_edtPtnVDD.GetWindowText(sdata);
			m_lcPtnSetList.SetItem(nVertical, m_nSelClkFlags, LVIF_TEXT, sdata.GetBuffer(0), 0, LVIF_STATE,0 ,0);
		}
	}

	if(m_nSelClkFlags == 3)
	{
		for(nVertical = 0; nVertical < nCnt; nVertical++)
		{
			m_edtPtnTMS.GetWindowText(sdata);
			m_lcPtnSetList.SetItem(nVertical, m_nSelClkFlags, LVIF_TEXT, sdata.GetBuffer(0), 0, LVIF_STATE,0 ,0);
		}
	}

	if(m_nSelClkFlags == 4)
	{
		for(nVertical = 0; nVertical < nCnt; nVertical++)
		{
			m_edtPtnVSync.GetWindowText(sdata);
			m_lcPtnSetList.SetItem(nVertical, m_nSelClkFlags, LVIF_TEXT, sdata.GetBuffer(0), 0, LVIF_STATE,0 ,0);
		}
	}
	if(m_nSelClkFlags == 5)
	{
		for(nVertical = 0; nVertical < nCnt; nVertical++)
		{ 
			m_edtPtnIccLow.GetWindowText(sdata);
			m_lcPtnSetList.SetItem(nVertical, m_nSelClkFlags, LVIF_TEXT, sdata.GetBuffer(0), 0, LVIF_STATE,0 ,0);
		}
	}
	if (m_nSelClkFlags == 6)
	{
		for (nVertical = 0; nVertical < nCnt; nVertical++)
		{
			m_edtPtnIccHigh.GetWindowText(sdata);
			m_lcPtnSetList.SetItem(nVertical, m_nSelClkFlags, LVIF_TEXT, sdata.GetBuffer(0), 0, LVIF_STATE, 0, 0);
		}
	}
	if (m_nSelClkFlags == 7)
	{
		for (nVertical = 0; nVertical < nCnt; nVertical++)
		{
			m_edtPtnIddLow.GetWindowText(sdata);
			m_lcPtnSetList.SetItem(nVertical, m_nSelClkFlags, LVIF_TEXT, sdata.GetBuffer(0), 0, LVIF_STATE, 0, 0);
		}
	}
	if (m_nSelClkFlags == 8)
	{
		for (nVertical = 0; nVertical < nCnt; nVertical++)
		{
			m_edtPtnIddHigh.GetWindowText(sdata);
			m_lcPtnSetList.SetItem(nVertical, m_nSelClkFlags, LVIF_TEXT, sdata.GetBuffer(0), 0, LVIF_STATE, 0, 0);
		}
	}
	if (m_nSelClkFlags == 9)
	{
		for (nVertical = 0; nVertical < nCnt; nVertical++)
		{
			m_edtPtnBlu.GetWindowText(sdata);
			m_lcPtnSetList.SetItem(nVertical, m_nSelClkFlags, LVIF_TEXT, sdata.GetBuffer(0), 0, LVIF_STATE, 0, 0);
		}
	}
	if (m_nSelClkFlags == 10)
	{
		for (nVertical = 0; nVertical < nCnt; nVertical++)
		{
			m_cmbPtnPower.GetWindowText(sdata);
			m_lcPtnSetList.SetItem(nVertical, m_nSelClkFlags, LVIF_TEXT, sdata.GetBuffer(0), 0, LVIF_STATE, 0, 0);
		}
	}
	UpdateData(FALSE);
}

void CModelInfo::OnStnClickedSttVccClk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_nSelClkFlags=1;
	m_nChangeFont&=0x0000;
	m_nChangeFont|=0x0001;
	Lf_setChangeFont();
}

void CModelInfo::OnStnClickedSttVddClk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_nSelClkFlags=2;
	m_nChangeFont&=0x0000;
	m_nChangeFont|=0x0002;
	Lf_setChangeFont();
}

void CModelInfo::OnStnClickedSttTmsClk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_nSelClkFlags=3;
	m_nChangeFont&=0x0000;
	m_nChangeFont|=0x0004;
	Lf_setChangeFont();
}

void CModelInfo::OnStnClickedSttVsyncClk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_nSelClkFlags=4;
	m_nChangeFont&=0x0000;
	m_nChangeFont|=0x0008;
	Lf_setChangeFont();
}

void CModelInfo::OnStnClickedSttIccLow()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_nSelClkFlags = 5;
	m_nChangeFont &= 0x0000;
	m_nChangeFont |= 0x0010;
	Lf_setChangeFont();
}

void CModelInfo::OnStnClickedSttIccHigh()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_nSelClkFlags = 6;
	m_nChangeFont &= 0x0000;
	m_nChangeFont |= 0x0020;
	Lf_setChangeFont();
}

void CModelInfo::OnStnClickedSttIddLow()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_nSelClkFlags = 7;
	m_nChangeFont &= 0x0000;
	m_nChangeFont |= 0x0040;
	Lf_setChangeFont();
}


void CModelInfo::OnStnClickedSttIddHigh()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_nSelClkFlags = 8;
	m_nChangeFont &= 0x0000;
	m_nChangeFont |= 0x0080;
	Lf_setChangeFont();
}

void CModelInfo::OnStnClickedSttBluClk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_nSelClkFlags=9;
	m_nChangeFont&=0x0000;
	m_nChangeFont|=0x0100;
	Lf_setChangeFont();
}

void CModelInfo::OnStnClickedSttPtnPowerClk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_nSelClkFlags = 10;
	m_nChangeFont &= 0x0000;
	m_nChangeFont |= 0x0200;
	Lf_setChangeFont();
}

void CModelInfo::OnBnClickedBtnCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialog::OnOK();
}


HBRUSH CModelInfo::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	switch (nCtlColor)
	{
	case CTLCOLOR_MSGBOX:
		break;
	case CTLCOLOR_EDIT:
		break;
	case CTLCOLOR_LISTBOX:
		break;
	case CTLCOLOR_SCROLLBAR:
		break;
	case CTLCOLOR_BTN:
		break;
	case CTLCOLOR_STATIC:
		if(pWnd->GetDlgCtrlID()==IDC_STT_MODELINFODLG_TIT)
		{
			pDC->SetBkColor(COLOR_DEEP_BLUE);
			pDC->SetTextColor(COLOR_WHITE);
			return m_Brush[COLOR_IDX_DEEP_BLUE];
		}
		if(pWnd->GetDlgCtrlID()== IDC_STT_FUSING)
		{
			if(m_bfusingflag==1)
			{
				pDC->SetBkColor(COLOR_GREEN128);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_GREEN128];
			}
			else if (m_bfusingflag == 2)
			{
				pDC->SetBkColor(COLOR_RED128);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_RED128];
			}
			else
			{
				pDC->SetBkColor(COLOR_GRAY96);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_GRAY96];
			}
		}
		if((pWnd->GetDlgCtrlID()==IDC_STT_CUR_MODELNAME_TIT)
		|| (pWnd->GetDlgCtrlID()==IDC_STT_CREATE_MODEL_TIT))
		{
			pDC->SetBkColor(COLOR_BLUISH);
			pDC->SetTextColor(COLOR_WHITE);
			return m_Brush[COLOR_IDX_BLUISH];
		}
		if (pWnd->GetDlgCtrlID() == IDC_STT_CUR_MODEL)
		{
			pDC->SetBkColor(COLOR_BLACK);
			pDC->SetTextColor(COLOR_WHITE);
			return m_Brush[COLOR_IDX_BLACK];
		}
		if (pWnd->GetDlgCtrlID() == IDC_STATIC
			|| pWnd->GetDlgCtrlID() == IDC_STT_VCC_CLK
			|| pWnd->GetDlgCtrlID() == IDC_STT_VDD_CLK
			|| pWnd->GetDlgCtrlID() == IDC_STT_TMS_CLK
			|| pWnd->GetDlgCtrlID() == IDC_STT_VSYNC_CLK
			|| pWnd->GetDlgCtrlID() == IDC_STT_BLU_CLK
			|| pWnd->GetDlgCtrlID() == IDC_STT_PTN_ICC
			|| pWnd->GetDlgCtrlID() == IDC_STT_PTN_IDD
			|| pWnd->GetDlgCtrlID() == IDC_STT_ICC_LOW
			|| pWnd->GetDlgCtrlID() == IDC_STT_ICC_HIGH
			|| pWnd->GetDlgCtrlID() == IDC_STT_IDD_LOW
			|| pWnd->GetDlgCtrlID() == IDC_STT_IDD_HIGH
			|| pWnd->GetDlgCtrlID() == IDC_STT_PTN_POWER_CLK
			)
		{
			pDC->SetBkColor(COLOR_BLUISH);
			pDC->SetTextColor(COLOR_WHITE);
			return m_Brush[COLOR_IDX_BLUISH];
		}
		if ((pWnd->GetDlgCtrlID() == IDC_STT_GRP_SIGNAL)
			|| (pWnd->GetDlgCtrlID() == IDC_STT_GRP_TIMING)
			|| (pWnd->GetDlgCtrlID() == IDC_STT_GRP_POWER)
			|| (pWnd->GetDlgCtrlID() == IDC_STT_GRP_POWER_SEQ)
			|| (pWnd->GetDlgCtrlID() == IDC_STT_GRP_POWER_LIMIT)
			|| (pWnd->GetDlgCtrlID() == IDC_STT_GRP_OTHERS)
			|| (pWnd->GetDlgCtrlID() == IDC_STT_GRP_EDID)
			|| (pWnd->GetDlgCtrlID() == IDC_STT_GRP_PATTERN)
			|| (pWnd->GetDlgCtrlID() == IDC_STT_GRP_I2C_OPTION)
			|| (pWnd->GetDlgCtrlID() == IDC_STT_GRP_PWM_SET)
			|| (pWnd->GetDlgCtrlID() == IDC_STT_GRP_ID_INPUT_TYPE)
			)
		{
			pDC->SetBkColor(COLOR_WHITE);
			pDC->SetTextColor(COLOR_GRAY64);
			return m_Brush[COLOR_IDX_WHITE];
		}
		if (pWnd->GetDlgCtrlID() == IDC_STT_ID_LENGTH_UNIT)
		{
			pDC->SetBkColor(COLOR_WHITE);
			pDC->SetTextColor(COLOR_BLACK);
			return m_Brush[COLOR_IDX_WHITE];
		}
		break;
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}

void CModelInfo::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CDialog::OnPaint()을(를) 호출하지 마십시오.
	CRect rect;

	GetClientRect(&rect);
	rect.bottom=90;
	dc.FillSolidRect(rect,COLOR_DEEP_BLUE);

	GetClientRect(&rect);
	rect.top = 91;
	dc.FillSolidRect(rect, COLOR_YELLOW);

	GetClientRect(&rect);
	rect.top = 92;
	dc.FillSolidRect(rect, COLOR_WHITE);
}

void CModelInfo::OnBnClickedBtnBluOnoff()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int bluOnValue=0, bluMin=0,len=0;
	int m_nValue=0,vLine=2, hLine=4, lineOn=1, nMin=5; 
	CString sdata=_T("");
	char m_szPacket[128]={0,};

	bluOnValue = lpModelInfo->m_nBluMin;	

	m_edtBluMin.GetWindowText(sdata);
	bluMin = _ttoi(sdata);

	
	if (bluMin > 100 || bluMin < 0)
	{
		AfxMessageBox(_T("BLU Max is 100!! Min is 0!!"));
		return;
	}
	lpModelInfo->m_nBluMin = bluMin;		


	m_pApp->m_pCommand->Gf_setBluDuty(bluMin);
	
	lpModelInfo->m_nBluMin = bluOnValue;
}

void CModelInfo::OnBnClickedBtnApply()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nItemIndex;
	int nItemCnt=0;
	CString sdata=_T("");

	UpdateData(TRUE);

	nItemCnt = m_lcPtnSetList.GetItemCount();

	for( nItemIndex=0; nItemIndex<nItemCnt; nItemIndex++)
	{
		m_edtVccSet.GetWindowText(sdata);
		m_lcPtnSetList.SetItem( nItemIndex, 1, LVIF_TEXT, sdata, 0, LVIF_STATE, 0, 0);

		m_edtVddSet.GetWindowText(sdata);
		m_lcPtnSetList.SetItem( nItemIndex, 2, LVIF_TEXT, sdata, 0, LVIF_STATE, 0, 0);
	}
	UpdateData(FALSE);
}


void CModelInfo::OnCbnSelchangeCmbPtnName()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strPtnName;
	m_cboPtnName.GetWindowTextW(strPtnName);
	////////////////////////////////////////////////////////////////////////////////
	if (strPtnName.Find(_T(".BMP")) != -1)
	{
		CRect rc;
		CString sPath;
		GetDlgItem(IDC_STT_PTN_IMAGE_SIZE)->GetWindowRect(rc);
		ScreenToClient(rc);
		rc.right -= 10;
		rc.bottom -= 20;
		sPath.Format(_T(".\\Pattern\\BMP\\%s"), strPtnName);
		HBITMAP hBitmap = (HBITMAP)LoadImage(AfxGetInstanceHandle(), sPath, IMAGE_BITMAP, rc.Width(), rc.Height(), LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		m_picPatternPreview.SetBitmap(hBitmap);
		Invalidate(FALSE);
	}
	else
		m_pApp->m_pPatternView->drawPattern(strPtnName);
	////////////////////////////////////////////////////////////////////////////////
}


void CModelInfo::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}


void CModelInfo::OnEnChangeEdtHActive()
{
	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strValue;
	int nValue=0, nTotal=0;
	m_edtHorActive.GetWindowTextW(strValue);
	nValue = (int)_ttoi(strValue);
	nTotal += nValue;
	m_edtHorWidth.GetWindowTextW(strValue);
	nValue = (int)_ttoi(strValue);
	nTotal += nValue;
	m_edtHorFrontPor.GetWindowTextW(strValue);
	nValue = (int)_ttoi(strValue);
	nTotal += nValue;
	m_edtHorBackPor.GetWindowTextW(strValue);
	nValue = (int)_ttoi(strValue);
	nTotal += nValue;

	strValue.Format(_T("%d"), nTotal);
	m_edtHorTotal.SetWindowTextW(strValue);
}


void CModelInfo::OnEnChangeEdtHWidth()
{
	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strValue;
	int nValue = 0, nTotal = 0;
	m_edtHorActive.GetWindowTextW(strValue);
	nValue = (int)_ttoi(strValue);
	nTotal += nValue;
	m_edtHorWidth.GetWindowTextW(strValue);
	nValue = (int)_ttoi(strValue);
	nTotal += nValue;
	m_edtHorFrontPor.GetWindowTextW(strValue);
	nValue = (int)_ttoi(strValue);
	nTotal += nValue;
	m_edtHorBackPor.GetWindowTextW(strValue);
	nValue = (int)_ttoi(strValue);
	nTotal += nValue;

	strValue.Format(_T("%d"), nTotal);
	m_edtHorTotal.SetWindowTextW(strValue);
}


void CModelInfo::OnEnChangeEdtHFrontPorch()
{
	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strValue;
	int nValue = 0, nTotal = 0;
	m_edtHorActive.GetWindowTextW(strValue);
	nValue = (int)_ttoi(strValue);
	nTotal += nValue;
	m_edtHorWidth.GetWindowTextW(strValue);
	nValue = (int)_ttoi(strValue);
	nTotal += nValue;
	m_edtHorFrontPor.GetWindowTextW(strValue);
	nValue = (int)_ttoi(strValue);
	nTotal += nValue;
	m_edtHorBackPor.GetWindowTextW(strValue);
	nValue = (int)_ttoi(strValue);
	nTotal += nValue;

	strValue.Format(_T("%d"), nTotal);
	m_edtHorTotal.SetWindowTextW(strValue);
}


void CModelInfo::OnEnChangeEdtHBackPorch()
{
	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strValue;
	int nValue = 0, nTotal = 0;
	m_edtHorActive.GetWindowTextW(strValue);
	nValue = (int)_ttoi(strValue);
	nTotal += nValue;
	m_edtHorWidth.GetWindowTextW(strValue);
	nValue = (int)_ttoi(strValue);
	nTotal += nValue;
	m_edtHorFrontPor.GetWindowTextW(strValue);
	nValue = (int)_ttoi(strValue);
	nTotal += nValue;
	m_edtHorBackPor.GetWindowTextW(strValue);
	nValue = (int)_ttoi(strValue);
	nTotal += nValue;

	strValue.Format(_T("%d"), nTotal);
	m_edtHorTotal.SetWindowTextW(strValue);
}


void CModelInfo::OnEnChangeEdtVActive()
{
	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strValue;
	int nValue = 0, nTotal = 0;
	m_edtVerActive.GetWindowTextW(strValue);
	nValue = (int)_ttoi(strValue);
	nTotal += nValue;
	m_edtVerWidth.GetWindowTextW(strValue);
	nValue = (int)_ttoi(strValue);
	nTotal += nValue;
	m_edtVerFrontPor.GetWindowTextW(strValue);
	nValue = (int)_ttoi(strValue);
	nTotal += nValue;
	m_edtVerBackPor.GetWindowTextW(strValue);
	nValue = (int)_ttoi(strValue);
	nTotal += nValue;

	strValue.Format(_T("%d"), nTotal);
	m_edtVerTotal.SetWindowTextW(strValue);
}


void CModelInfo::OnEnChangeEdtVWidth()
{
	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strValue;
	int nValue = 0, nTotal = 0;
	m_edtVerActive.GetWindowTextW(strValue);
	nValue = (int)_ttoi(strValue);
	nTotal += nValue;
	m_edtVerWidth.GetWindowTextW(strValue);
	nValue = (int)_ttoi(strValue);
	nTotal += nValue;
	m_edtVerFrontPor.GetWindowTextW(strValue);
	nValue = (int)_ttoi(strValue);
	nTotal += nValue;
	m_edtVerBackPor.GetWindowTextW(strValue);
	nValue = (int)_ttoi(strValue);
	nTotal += nValue;

	strValue.Format(_T("%d"), nTotal);
	m_edtVerTotal.SetWindowTextW(strValue);
}


void CModelInfo::OnEnChangeEdtVFrontPorch()
{
	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strValue;
	int nValue = 0, nTotal = 0;
	m_edtVerActive.GetWindowTextW(strValue);
	nValue = (int)_ttoi(strValue);
	nTotal += nValue;
	m_edtVerWidth.GetWindowTextW(strValue);
	nValue = (int)_ttoi(strValue);
	nTotal += nValue;
	m_edtVerFrontPor.GetWindowTextW(strValue);
	nValue = (int)_ttoi(strValue);
	nTotal += nValue;
	m_edtVerBackPor.GetWindowTextW(strValue);
	nValue = (int)_ttoi(strValue);
	nTotal += nValue;

	strValue.Format(_T("%d"), nTotal);
	m_edtVerTotal.SetWindowTextW(strValue);
}


void CModelInfo::OnEnChangeEdtVBackPorch()
{
	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strValue;
	int nValue = 0, nTotal = 0;
	m_edtVerActive.GetWindowTextW(strValue);
	nValue = (int)_ttoi(strValue);
	nTotal += nValue;
	m_edtVerWidth.GetWindowTextW(strValue);
	nValue = (int)_ttoi(strValue);
	nTotal += nValue;
	m_edtVerFrontPor.GetWindowTextW(strValue);
	nValue = (int)_ttoi(strValue);
	nTotal += nValue;
	m_edtVerBackPor.GetWindowTextW(strValue);
	nValue = (int)_ttoi(strValue);
	nTotal += nValue;

	strValue.Format(_T("%d"), nTotal);
	m_edtVerTotal.SetWindowTextW(strValue);
}


void CModelInfo::OnBnClickedBtnGammaVoltageSet()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CModelGamma gammadlg;
	gammadlg.DoModal();
}


void CModelInfo::OnStnClickedSttFusing()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_pApp->Gf_writeLogData("<TEST>", "MANUAL Fusing Start");
	GetDlgItem(IDC_STT_FUSING)->EnableWindow(FALSE);
	m_bfusingflag = 0;

	Lf_saveModelInfoData();
	m_pApp->m_pCommand->Gf_setZoneSel();
	if (m_pApp->m_pCommand->Gf_setFusingSystemInfo() == TRUE)
	{
		m_bfusingflag = 1;
		GetDlgItem(IDC_STT_FUSING)->SetWindowTextW(_T("FUSING OK"));
	}
	else
	{
		m_bfusingflag = 2;
		GetDlgItem(IDC_STT_FUSING)->SetWindowTextW(_T("FUSING NG"));
	}

	GetDlgItem(IDC_STT_FUSING)->EnableWindow(TRUE);
	GetDlgItem(IDC_STT_FUSING)->Invalidate(FALSE);
}


