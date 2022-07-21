// Initialize.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "GIE_BoadAssy.h"
#include "Initialize.h"


// CInitialize ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CInitialize, CDialog)

CInitialize::CInitialize(CWnd* pParent /*=NULL*/)
	: CDialog(CInitialize::IDD, pParent)
{

}

CInitialize::~CInitialize()
{
}

void CInitialize::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CInitialize, CDialog)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_RETRY, &CInitialize::OnBnClickedBtnRetry)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CInitialize �޽��� ó�����Դϴ�.

BOOL CInitialize::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	lpModelInfo		= m_pApp->GetModelInfo();
	
	Lf_initFontSet();

	SetTimer(1,20,NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CInitialize::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	for(int i=0; i<COLOR_IDX_MAX; i++)
	{
		m_Brush[i].DeleteObject();
	}

	for(int i=0; i<FONT_IDX_MAX; i++)
	{
		m_Font[i].DeleteObject();
	}
}

void CInitialize::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if(nIDEvent == 1)
	{
		KillTimer(1);

		Lf_loadData();
	}
	CDialog::OnTimer(nIDEvent);
}

HBRUSH CInitialize::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  ���⼭ DC�� Ư���� �����մϴ�.
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
		if(pWnd->GetDlgCtrlID()==IDC_STT_INITDLG_TIT)
		{
			pDC->SetBkColor(COLOR_DEEP_BLUE);
			pDC->SetTextColor(COLOR_WHITE);
			return m_Brush[COLOR_IDX_DEEP_BLUE];
		}
		if(pWnd->GetDlgCtrlID()==IDC_STT_SYSTEM_VALUE)
		{
			pDC->SetBkColor(COLOR_GREEN);
			pDC->SetTextColor(COLOR_WHITE);
			return m_Brush[COLOR_IDX_GREEN];
		}
		if(pWnd->GetDlgCtrlID()==IDC_STT_MODEL_VALUE)
		{
			if(m_nStatus[ST_MOD] == FALSE)
			{
				pDC->SetBkColor(COLOR_RED);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_RED];
			}
			else
			{
				pDC->SetBkColor(COLOR_GREEN);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_GREEN];
			}
		}
		if(pWnd->GetDlgCtrlID()==IDC_STT_PTNFILE_VALUE)
		{
			if(m_nStatus[ST_PTN] == FALSE)
			{
				pDC->SetBkColor(COLOR_RED);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_RED];
			}
			else
			{
				pDC->SetBkColor(COLOR_GREEN);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_GREEN];
			}
		}	
		if(pWnd->GetDlgCtrlID()==IDC_STT_EDID_VALUE)
		{
			if(m_nStatus[ST_EDID] == FALSE)
			{
				pDC->SetBkColor(COLOR_RED);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_RED];
			}
			else
			{
				pDC->SetBkColor(COLOR_GREEN);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_GREEN];
			}
		}
		if(pWnd->GetDlgCtrlID()==IDC_STT_PG_VALUE)
		{
			if(m_nStatus[ST_IRDA] == FALSE)
			{
				pDC->SetBkColor(COLOR_RED);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_RED];
			}
			else
			{
				pDC->SetBkColor(COLOR_GREEN);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_GREEN];
			}
		}
		if(pWnd->GetDlgCtrlID()==IDC_STT_BCR_VALUE)
		{
			if(m_nStatus[ST_BCR] == FALSE)
			{
				pDC->SetBkColor(COLOR_RED);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_RED];
			}
			else
			{
				pDC->SetBkColor(COLOR_GREEN);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_GREEN];
			}
		}
		if(pWnd->GetDlgCtrlID()==IDC_STT_BCR_VALUE)
		{
			if(m_nStatus[ST_BCR] == FALSE)
			{
				pDC->SetBkColor(COLOR_RED);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_RED];
			}
			else
			{
				pDC->SetBkColor(COLOR_GREEN);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_GREEN];
			}
		}
		if(pWnd->GetDlgCtrlID()==IDC_STT_GFD250_VALUE)
		{
			if(m_nStatus[ST_GFD250] == FALSE)
			{
				pDC->SetBkColor(COLOR_RED);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_RED];
			}
			else
			{
				pDC->SetBkColor(COLOR_GREEN);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_GREEN];
			}
		}
		if(pWnd->GetDlgCtrlID()==IDC_STT_BLU_VALUE)
		{
			if(m_nStatus[ST_LED_BLU] == FALSE)
			{
				pDC->SetBkColor(COLOR_RED);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_RED];
			}
			else
			{
				pDC->SetBkColor(COLOR_GREEN);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_GREEN];
			}
		}
		break;
	}
	// TODO:  �⺻���� �������� ������ �ٸ� �귯�ø� ��ȯ�մϴ�.
	return hbr;
}

void CInitialize::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	// �׸��� �޽����� ���ؼ��� CDialog::OnPaint()��(��) ȣ������ ���ʽÿ�.
	CRect rect;

	GetClientRect(&rect);
	rect.bottom=90;
	dc.FillSolidRect(rect,COLOR_DEEP_BLUE);

	GetClientRect(&rect);
	rect.top = 91;
	dc.FillSolidRect(rect, COLOR_CYAN);

	GetClientRect(&rect);
	rect.top = 92;
	dc.FillSolidRect(rect, COLOR_GRAY64);
}

void CInitialize::Lf_initFontSet()
{
	/*************************************************************************************************/
	// Font Set
	m_Font[0].CreateFont(24, 11, 0, 0, FW_SEMIBOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("Segoe UI Symbol"));
	GetDlgItem(IDC_STT_SYSTEM_VALUE)->SetFont(&m_Font[0]);
	GetDlgItem(IDC_STT_MODEL_VALUE)->SetFont(&m_Font[0]);
	GetDlgItem(IDC_STT_PTNFILE_VALUE)->SetFont(&m_Font[0]);
	GetDlgItem(IDC_STT_EDID_VALUE)->SetFont(&m_Font[0]);
	GetDlgItem(IDC_STT_PG_VALUE)->SetFont(&m_Font[0]);
	GetDlgItem(IDC_STT_BCR_VALUE)->SetFont(&m_Font[0]);
	GetDlgItem(IDC_STT_GFD250_VALUE)->SetFont(&m_Font[0]);
	GetDlgItem(IDC_STT_BLU_VALUE)->SetFont(&m_Font[0]);

	m_Font[1].CreateFont(15, 8, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("Segoe UI Symbol"));

	m_Font[2].CreateFont(15, 8, 0, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0, 0, 0, _T("Segoe UI Symbol"));

	m_Font[3].CreateFont(34, 14, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("Segoe UI Symbol"));
	GetDlgItem(IDC_BTN_RETRY)->SetFont(&m_Font[3]);
	GetDlgItem(IDCANCEL)->SetFont(&m_Font[3]);

	m_Font[4].CreateFont(60, 26, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("Segoe UI Symbol"));
	GetDlgItem(IDC_STT_INITDLG_TIT)->SetFont(&m_Font[4]);

	m_Font[5].CreateFont(150, 70, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("ARIAL"));

	/*************************************************************************************************/
	// Brush Set
	m_Brush[COLOR_IDX_ORANGE].CreateSolidBrush (COLOR_ORANGE);
	m_Brush[COLOR_IDX_RED].CreateSolidBrush (COLOR_RED);
	m_Brush[COLOR_IDX_GREEN].CreateSolidBrush(COLOR_GREEN);
	m_Brush[COLOR_IDX_GRAY64].CreateSolidBrush (COLOR_GRAY64);
	m_Brush[COLOR_IDX_GRAY94].CreateSolidBrush (COLOR_GRAY94);
	m_Brush[COLOR_IDX_LIGHT_GREEN].CreateSolidBrush (COLOR_LIGHT_GREEN);
	m_Brush[COLOR_IDX_WHITE].CreateSolidBrush (COLOR_WHITE);
	m_Brush[COLOR_IDX_DEEP_BLUE].CreateSolidBrush (COLOR_DEEP_BLUE);	
}

void CInitialize::Lf_loadData()
{
	int i=0;

	memset(m_nStatus, 1, sizeof(m_nStatus));
	GetDlgItem(IDC_BTN_RETRY)->EnableWindow(FALSE);
	GetDlgItem(IDCANCEL)->EnableWindow(FALSE);

	m_pApp->Gf_loadSystemInfo();
	//SetDlgItemText(IDC_STT_SYSTEM_VALUE, m_pApp->m_sSysIniFile);
	GetDlgItem(IDC_STT_SYSTEM_VALUE)->Invalidate(FALSE);

	//if(!m_pApp->m_sModelFile.Compare(_T("Model file load NG!!!")))
	if (m_pApp->Gf_loadMedelFile() != TRUE)
	{
		m_nStatus[ST_MOD] = TRUE;
	}
	//SetDlgItemText (IDC_STT_MODEL_VALUE, m_pApp->m_sModelFile);
	GetDlgItem(IDC_STT_MODEL_VALUE)->Invalidate(FALSE);

	//if(!m_pApp->m_sPtnFile.Compare(_T("Pattern file load NG!!!")))
	if (m_pApp->Gf_loadPatternFile() != TRUE)
	{
		m_nStatus[ST_PTN] = TRUE;
	}
	//SetDlgItemText (IDC_STT_PTNFILE_VALUE, m_pApp->m_sPtnFile);
	GetDlgItem(IDC_STT_PTNFILE_VALUE)->Invalidate(FALSE);

	if(m_pApp->Gf_readEdidFile())
	{
		if(lpModelInfo->m_nEdidUse == TRUE)
		{
			m_nStatus[ST_EDID] = TRUE;
			//SetDlgItemText(IDC_STT_EDID_VALUE, _T("Edid Data check success."));
		}
		else
		{
			m_nStatus[ST_EDID] = FALSE;
			//SetDlgItemText(IDC_STT_EDID_VALUE, _T("Edid Data check fail."));
		}
	}
	else
	{
		if(lpModelInfo->m_nEdidUse == TRUE)
		{
			m_nStatus[ST_EDID] = FALSE;
			//SetDlgItemText (IDC_STT_EDID_VALUE, _T("Edid Data check fail."));
		}
		else
		{
			m_nStatus[ST_EDID] = TRUE;
			//SetDlgItemText(IDC_STT_EDID_VALUE, _T("Edid Data check 'OK'."));
		}
	}
	GetDlgItem(IDC_STT_EDID_VALUE)->Invalidate(FALSE);
	//==================================================================================== SERIAL PORT
	m_pApp->Gf_setSerialPort();

	if(!m_pApp->m_sSerialPort1.Compare(_T("PG NG.")))
		m_nStatus[ST_IRDA] = FALSE;
	else
		m_nStatus[ST_IRDA] = TRUE;

	//SetDlgItemText(IDC_STT_PG_VALUE, m_pApp->m_sSerialPort1);
	GetDlgItem(IDC_STT_PG_VALUE)->Invalidate(FALSE);

	if(!m_pApp->m_sSerialPort2.Compare(_T("GFD250 OK.")))
		m_nStatus[ST_GFD250] = TRUE;
	else
		m_nStatus[ST_GFD250] = FALSE;

	//SetDlgItemText (IDC_STT_GFD250_VALUE, m_pApp->m_sSerialPort2);
	GetDlgItem(IDC_STT_GFD250_VALUE)->Invalidate(FALSE);

	if(!m_pApp->m_sSerialPort3.Compare(_T("Auto BCR OK.")))
		m_nStatus[ST_BCR] = TRUE;
	else
		m_nStatus[ST_BCR] = FALSE;

	//SetDlgItemText (IDC_STT_BCR_VALUE, m_pApp->m_sSerialPort3);
	GetDlgItem(IDC_STT_BCR_VALUE)->Invalidate(FALSE);

	if(!m_pApp->m_sSerialPort4.Compare(_T("LED BLU OK.")))
		m_nStatus[ST_LED_BLU] = TRUE;
	else
		m_nStatus[ST_LED_BLU] = FALSE;

	//SetDlgItemText (IDC_STT_BLU_VALUE, m_pApp->m_sSerialPort4);
	GetDlgItem(IDC_STT_BLU_VALUE)->Invalidate(FALSE);

	UpdateData(FALSE);

	if(m_nStatus[ST_IRDA] == TRUE)
	{
		m_pApp->m_pCommand->Gf_setPowerSeqOnOff(OFF);
		delayMS(500);
		m_pApp->m_pCommand->Gf_getFirmwareVersion();
	}	

	for(int i=0;i<20;i++)
	{
		if(m_nStatus[i] == FALSE)
			m_nChkPoint++;
	}

	AfxGetApp()->GetMainWnd()->SendMessage(WM_UPDATE_SYSTEM_INFO, NULL, NULL);

	if(m_nChkPoint == 0)
		CDialog::OnOK();

	GetDlgItem(IDC_BTN_RETRY)->EnableWindow(TRUE);
	GetDlgItem(IDCANCEL)->EnableWindow(TRUE);
}

void CInitialize::OnBnClickedBtnRetry()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	SetDlgItemText(IDC_STT_SYSTEM_VALUE, _T(""));
	SetDlgItemText(IDC_STT_MODEL_VALUE, _T(""));
	SetDlgItemText(IDC_STT_PTNFILE_VALUE, _T(""));
	SetDlgItemText(IDC_STT_EDID_VALUE, _T(""));
	SetDlgItemText(IDC_STT_PG_VALUE, _T(""));
	SetDlgItemText(IDC_STT_BCR_VALUE, _T(""));
	SetDlgItemText(IDC_STT_GFD250_VALUE, _T(""));
	SetDlgItemText(IDC_STT_BLU_VALUE, _T(""));

	SetTimer(1,20,NULL);
}