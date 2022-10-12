// ModelGamma.cpp: 구현 파일
//

#include "stdafx.h"
#include "GIE_BoadAssy.h"
#include "afxdialogex.h"
#include "ModelGamma.h"


// CModelGamma 대화 상자

IMPLEMENT_DYNAMIC(CModelGamma, CDialog)

CModelGamma::CModelGamma(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_MODEL_GAMMA, pParent)
{

}

CModelGamma::~CModelGamma()
{
}

void CModelGamma::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDT_GAMMA_CH1, m_edtPowerGammaCh01);
	DDX_Control(pDX, IDC_EDT_GAMMA_CH2, m_edtPowerGammaCh02);
	DDX_Control(pDX, IDC_EDT_GAMMA_CH3, m_edtPowerGammaCh03);
	DDX_Control(pDX, IDC_EDT_GAMMA_CH4, m_edtPowerGammaCh04);
	DDX_Control(pDX, IDC_EDT_GAMMA_CH5, m_edtPowerGammaCh05);
	DDX_Control(pDX, IDC_EDT_GAMMA_CH6, m_edtPowerGammaCh06);
	DDX_Control(pDX, IDC_EDT_GAMMA_CH7, m_edtPowerGammaCh07);
	DDX_Control(pDX, IDC_EDT_GAMMA_CH8, m_edtPowerGammaCh08);
	DDX_Control(pDX, IDC_EDT_GAMMA_CH9, m_edtPowerGammaCh09);
	DDX_Control(pDX, IDC_EDT_GAMMA_CH10, m_edtPowerGammaCh10);
	DDX_Control(pDX, IDC_EDT_GAMMA_CH11, m_edtPowerGammaCh11);
	DDX_Control(pDX, IDC_EDT_GAMMA_CH12, m_edtPowerGammaCh12);
	DDX_Control(pDX, IDC_EDT_GAMMA_CH13, m_edtPowerGammaCh13);
	DDX_Control(pDX, IDC_EDT_GAMMA_CH14, m_edtPowerGammaCh14);
	DDX_Control(pDX, IDC_EDT_GAMMA_CH15, m_edtPowerGammaCh15);
	DDX_Control(pDX, IDC_EDT_GAMMA_CH16, m_edtPowerGammaCh16);
	DDX_Control(pDX, IDC_EDT_GAMMA_CH17, m_edtPowerGammaCh17);
	DDX_Control(pDX, IDC_EDT_GAMMA_CH18, m_edtPowerGammaCh18);
	DDX_Control(pDX, IDC_EDT_GAMMA_CH19, m_edtPowerGammaCh19);
	DDX_Control(pDX, IDC_EDT_GAMMA_CH20, m_edtPowerGammaCh20);
	DDX_Control(pDX, IDC_EDT_GAMMA_CH21, m_edtPowerGammaCh21);
	DDX_Control(pDX, IDC_EDT_GAMMA_CH22, m_edtPowerGammaCh22);
	DDX_Control(pDX, IDC_EDT_GAMMA_CH23, m_edtPowerGammaCh23);
	DDX_Control(pDX, IDC_EDT_GAMMA_CH24, m_edtPowerGammaCh24);
	DDX_Control(pDX, IDC_EDT_GAMMA_CH25, m_edtPowerGammaCh25);
	DDX_Control(pDX, IDC_EDT_GAMMA_CH26, m_edtPowerGammaCh26);
	DDX_Control(pDX, IDC_EDT_GAMMA_CH27, m_edtPowerGammaCh27);
	DDX_Control(pDX, IDC_EDT_GAMMA_CH28, m_edtPowerGammaCh28);
	DDX_Control(pDX, IDC_EDT_GAMMA_CH29, m_edtPowerGammaCh29);
	DDX_Control(pDX, IDC_EDT_GAMMA_CH30, m_edtPowerGammaCh30);
	DDX_Control(pDX, IDC_EDT_GAMMA_CH31, m_edtPowerGammaCh31);
	DDX_Control(pDX, IDC_EDT_GAMMA_CH32, m_edtPowerGammaCh32);
}


BEGIN_MESSAGE_MAP(CModelGamma, CDialog)
	ON_BN_CLICKED(IDC_BTN_SAVE, &CModelGamma::OnBnClickedBtnSave)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_CLOSE, &CModelGamma::OnBnClickedBtnClose)
	ON_WM_DESTROY()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CModelGamma 메시지 처리기


BOOL CModelGamma::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	lpModelInfo = m_pApp->GetModelInfo();
	lpSystemInfo = m_pApp->GetSystemInfo();

	Lf_initFontSet();
	Lf_InitBrush();
	Lf_InitItemDataSet();
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CModelGamma::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	for (int i = 0; i < COLOR_IDX_MAX; i++)
	{
		m_Brush[i].DeleteObject();
	}
	for (int j = 0; j < FONT_IDX_MAX; j++)
	{
		m_Font[j].DeleteObject();
	}
}


void CModelGamma::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialog::OnPaint()을(를) 호출하지 마십시오.
	CRect rect;

	GetClientRect(&rect);
	dc.FillSolidRect(rect, COLOR_WHITE);
}


HBRUSH CModelGamma::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
		if (pWnd->GetDlgCtrlID() == IDC_STATIC)
		{
			pDC->SetBkColor(COLOR_DEEP_BLUE);
			pDC->SetTextColor(COLOR_WHITE);
			return m_Brush[COLOR_IDX_DEEP_BLUE];
		}
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}

void CModelGamma::OnBnClickedBtnSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strKey, sdata;
	for (int i = 0; i < 32; i++)
	{
		strKey.Format(_T("GAMMA_CH%02d"), i + 1);
		GetDlgItem(IDC_EDT_GAMMA_CH1 + i)->GetWindowTextW(sdata);
		lpModelInfo->m_fVoltGamma[i] = (float)_tstof(sdata);
		Write_ModelFile(lpSystemInfo->m_sModelName, _T("MODEL_INFO"), strKey, lpModelInfo->m_fVoltGamma[i]);
	}
}
void CModelGamma::OnBnClickedBtnClose()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialog::OnOK();
}
void CModelGamma::Lf_initFontSet()
{
	/*******************************************************************************************************************/
	// Fonts set
	m_Font[0].CreateFont(15, 8, 0, 0, FW_SEMIBOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("Segoe UI Symbol"));

	m_Font[1].CreateFont(15, 8, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("Segoe UI Symbol"));

	m_Font[2].CreateFont(15, 8, 0, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0, 0, 0, _T("Segoe UI Symbol"));

	m_Font[3].CreateFont(34, 14, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("Segoe UI Symbol"));

	m_Font[4].CreateFont(60, 26, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("Segoe UI Symbol"));

	m_Font[5].CreateFont(24, 9, 0, 0, FW_SEMIBOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("Segoe UI Symbol"));
	GetDlgItem(IDC_BTN_SAVE)->SetFont(&m_Font[5]);
	GetDlgItem(IDC_BTN_CLOSE)->SetFont(&m_Font[5]);

}
void CModelGamma::Lf_InitBrush()
{
	m_Brush[COLOR_IDX_BLACK].CreateSolidBrush(COLOR_BLACK);
	m_Brush[COLOR_IDX_ORANGE].CreateSolidBrush(COLOR_ORANGE);
	m_Brush[COLOR_IDX_GRAY240].CreateSolidBrush(COLOR_GRAY240);
	m_Brush[COLOR_IDX_GRAY64].CreateSolidBrush(COLOR_GRAY64);
	m_Brush[COLOR_IDX_BLUISH].CreateSolidBrush(COLOR_BLUISH);
	m_Brush[COLOR_IDX_GRAY224].CreateSolidBrush(COLOR_GRAY224);
	m_Brush[COLOR_IDX_GREEN128].CreateSolidBrush(COLOR_GREEN128);
	m_Brush[COLOR_IDX_DEEP_BLUE].CreateSolidBrush(COLOR_DEEP_BLUE);
	m_Brush[COLOR_IDX_LIGHT_YELLOW].CreateSolidBrush(COLOR_LIGHT_YELLOW);
	m_Brush[COLOR_IDX_MAGENTA].CreateSolidBrush(COLOR_MAGENTA);
}
void CModelGamma::Lf_InitItemDataSet()
{
	CString sdata;
	for (int i = 0; i < 32; i++)
	{
		sdata.Format(_T("%.3f"), lpModelInfo->m_fVoltGamma[i]);
		GetDlgItem(IDC_EDT_GAMMA_CH1 + i)->SetWindowTextW(sdata);
	}
}

