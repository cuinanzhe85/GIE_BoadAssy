// Initialize.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GIE_BoadAssy.h"
#include "GIE_BoadAssyDlg.h"
#include "Initialize.h"


// CInitialize 대화 상자입니다.

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


// CInitialize 메시지 처리기입니다.

BOOL CInitialize::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_pApp->Gf_writeLogData("<WND>", "Test Ready Dialog Open");
	lpModelInfo		= m_pApp->GetModelInfo();
	lpSystemInfo	= m_pApp->GetSystemInfo();
	lpWorkInfo		= m_pApp->GetWorkInfo();
	
	Lf_initFontSet();

	SetTimer(1,20,NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CInitialize::OnDestroy()
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

void CInitialize::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if(nIDEvent == 1)
	{
		KillTimer(1);

		Lf_loadData();

		if (lpSystemInfo->m_nDfsUse == TRUE)
		{
			m_pApp->Gf_ftpConnectDFS();
			m_pApp->Gf_ftpDownloadModuleIniFile();
			m_pApp->Gf_ftpDisConnectDFS();
		}
	}
	CDialog::OnTimer(nIDEvent);
}

HBRUSH CInitialize::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
		if(pWnd->GetDlgCtrlID()==IDC_STT_INITDLG_TIT)
		{
			pDC->SetBkColor(COLOR_DEEP_BLUE);
			pDC->SetTextColor(COLOR_WHITE);
			return m_Brush[COLOR_IDX_DEEP_BLUE];
		}
		if(pWnd->GetDlgCtrlID()==IDC_STT_SYSTEM_VALUE)
		{
			pDC->SetBkColor(COLOR_GREEN128);
			pDC->SetTextColor(COLOR_WHITE);
			return m_Brush[COLOR_IDX_GREEN128];
		}
		if(pWnd->GetDlgCtrlID()==IDC_STT_MODEL_VALUE)
		{
			if(m_nStatus[ST_MOD] == FALSE)
			{
				pDC->SetBkColor(COLOR_RED);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_RED];
			}
			else if (m_nStatus[ST_MOD] == TRUE)
			{
				pDC->SetBkColor(COLOR_GREEN128);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_GREEN128];
			}
			else
			{
				pDC->SetBkColor(COLOR_GRAY96);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_GRAY96];
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
			else if (m_nStatus[ST_PTN] == TRUE)
			{
				pDC->SetBkColor(COLOR_GREEN128);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_GREEN128];
			}
			else
			{
				pDC->SetBkColor(COLOR_GRAY96);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_GRAY96];
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
			else if (m_nStatus[ST_EDID] == TRUE)
			{
				pDC->SetBkColor(COLOR_GREEN128);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_GREEN128];
			}
			else
			{
				pDC->SetBkColor(COLOR_GRAY96);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_GRAY96];
			}
		}
		if(pWnd->GetDlgCtrlID()==IDC_STT_PG_VALUE)
		{
			if(m_nStatus[ST_PG] == FALSE)
			{
				pDC->SetBkColor(COLOR_RED);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_RED];
			}
			else if (m_nStatus[ST_PG] == TRUE)
			{
				pDC->SetBkColor(COLOR_GREEN128);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_GREEN128];
			}
			else
			{
				pDC->SetBkColor(COLOR_GRAY96);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_GRAY96];
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
			else if (m_nStatus[ST_BCR] == TRUE)
			{
				pDC->SetBkColor(COLOR_GREEN128);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_GREEN128];
			}
			else
			{
				pDC->SetBkColor(COLOR_GRAY96);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_GRAY96];
			}
		}
		if(pWnd->GetDlgCtrlID()== IDC_STT_DIO_VALUE)
		{
			if(m_nStatus[ST_DIO] == FALSE)
			{
				pDC->SetBkColor(COLOR_RED);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_RED];
			}
			else if (m_nStatus[ST_DIO] == TRUE)
			{
				pDC->SetBkColor(COLOR_GREEN128);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_GREEN128];
			}
			else
			{
				pDC->SetBkColor(COLOR_GRAY96);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_GRAY96];
			}
		}
		if(pWnd->GetDlgCtrlID()==IDC_STT_PLC_VALUE)
		{
			if(m_nStatus[ST_PLC] == FALSE)
			{
				pDC->SetBkColor(COLOR_RED);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_RED];
			}
			else if (m_nStatus[ST_PLC] == TRUE)
			{
				pDC->SetBkColor(COLOR_GREEN128);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_GREEN128];
			}
			else
			{
				pDC->SetBkColor(COLOR_GRAY96);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_GRAY96];
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
			else if (m_nStatus[ST_LED_BLU] == TRUE)
			{
				pDC->SetBkColor(COLOR_GREEN128);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_GREEN128];
			}
			else
			{
				pDC->SetBkColor(COLOR_GRAY96);
				pDC->SetTextColor(COLOR_WHITE);
				return m_Brush[COLOR_IDX_GRAY96];
			}
		}
		break;
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}

void CInitialize::OnPaint()
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
	GetDlgItem(IDC_STT_BLU_VALUE)->SetFont(&m_Font[0]);
	GetDlgItem(IDC_STT_DIO_VALUE)->SetFont(&m_Font[0]);
	GetDlgItem(IDC_STT_PLC_VALUE)->SetFont(&m_Font[0]);

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
	m_Brush[COLOR_IDX_GREEN128].CreateSolidBrush(COLOR_GREEN128);
	m_Brush[COLOR_IDX_GRAY64].CreateSolidBrush (COLOR_GRAY64);
	m_Brush[COLOR_IDX_GRAY94].CreateSolidBrush (COLOR_GRAY94);
	m_Brush[COLOR_IDX_GRAY96].CreateSolidBrush(COLOR_GRAY96);
	m_Brush[COLOR_IDX_LIGHT_GREEN].CreateSolidBrush (COLOR_LIGHT_GREEN);
	m_Brush[COLOR_IDX_WHITE].CreateSolidBrush (COLOR_WHITE);
	m_Brush[COLOR_IDX_DEEP_BLUE].CreateSolidBrush (COLOR_DEEP_BLUE);	
}

void CInitialize::Lf_loadData()
{
	int i=0;

	memset(m_nStatus, TRUE, sizeof(m_nStatus));
	Invalidate(FALSE);
	GetDlgItem(IDC_BTN_RETRY)->EnableWindow(FALSE);
	GetDlgItem(IDCANCEL)->EnableWindow(FALSE);

	m_pApp->Gf_loadSystemInfo();
	m_nStatus[ST_SYS] = TRUE;
	//SetDlgItemText(IDC_STT_SYSTEM_VALUE, m_pApp->m_sSysIniFile);
	GetDlgItem(IDC_STT_SYSTEM_VALUE)->Invalidate(FALSE);

	//if(!m_pApp->m_sModelFile.Compare(_T("Model file load NG!!!")))
	if (m_pApp->Gf_loadMedelFile() != TRUE)
	{
		m_nStatus[ST_MOD] = FALSE;
	}
	else
	{
		m_nStatus[ST_MOD] = TRUE;
	}
	//SetDlgItemText (IDC_STT_MODEL_VALUE, m_pApp->m_sModelFile);
	GetDlgItem(IDC_STT_MODEL_VALUE)->Invalidate(FALSE);

	//if(!m_pApp->m_sPtnFile.Compare(_T("Pattern file load NG!!!")))
	if (m_pApp->Gf_loadPatternFile() != TRUE)
	{
		m_nStatus[ST_PTN] = FALSE;
	}
	else
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
	

	if(m_pApp->m_pCommand->Gf_getAreYouReady() != TRUE)
		m_nStatus[ST_PG] = FALSE;
	else
		m_nStatus[ST_PG] = TRUE;

	//SetDlgItemText(IDC_STT_PG_VALUE, m_pApp->m_sSerialPort1);
	GetDlgItem(IDC_STT_PG_VALUE)->Invalidate(FALSE);

	m_pApp->Gf_setSerialPort();

	if (!m_pApp->m_sSerialPort4.Compare(_T("LED BLU OK.")))
		m_nStatus[ST_LED_BLU] = TRUE;
	else
		m_nStatus[ST_LED_BLU] = FALSE;

	//SetDlgItemText (IDC_STT_BLU_VALUE, m_pApp->m_sSerialPort4);
	GetDlgItem(IDC_STT_BLU_VALUE)->Invalidate(FALSE);
	
	if (!m_pApp->m_sSerialPort3.Compare(_T("Auto BCR OK.")))
		m_nStatus[ST_BCR] = TRUE;
	else
		m_nStatus[ST_BCR] = FALSE;

	//SetDlgItemText (IDC_STT_BCR_VALUE, m_pApp->m_sSerialPort3);
	GetDlgItem(IDC_STT_BCR_VALUE)->Invalidate(FALSE);

	if (m_pApp->m_pDio7230->Dio_Initialize() == TRUE)
	{
		m_nStatus[ST_DIO] = TRUE;
	}
	else
	{
		m_nStatus[ST_DIO] = FALSE;
	}
	GetDlgItem(IDC_STT_DIO_VALUE)->Invalidate(FALSE);

	if (lpSystemInfo->m_nPlcDeviceUse == TRUE)
	{
		m_pApp->m_pPlcCtrl->plc_tcpDisConnection();
		delayMS(500);
		if (m_pApp->m_pPlcCtrl->plc_tcpConnection() == TRUE)
		{
			delayMS(100);
			m_pApp->m_pPlcCtrl->plc_tcpDisConnection();
			m_nStatus[ST_PLC] = TRUE;
		}
		else
		{
			m_nStatus[ST_PLC] = FALSE;
		}
	}
	GetDlgItem(IDC_STT_PLC_VALUE)->Invalidate(FALSE);

	UpdateData(FALSE);

	if(m_nStatus[ST_PG] == TRUE)
	{
		m_pApp->m_pCommand->Gf_setPowerSeqOnOff(POWER_OFF);
		delayMS(500);
		if (m_pApp->m_pCommand->Gf_getFirmwareVersion() == TRUE)
		{
			int nLength = 0;
			sscanf_s(&m_pApp->m_pCommand->gszudpRcvPacket[PACKET_PT_LEN], "%04X", &nLength);
			memcpy(&m_pApp->m_szMainFwVersion,&m_pApp->m_pCommand->gszudpRcvPacket[PACKET_PT_DATA],  nLength);
			
			CString strlog;
			strlog.Format(_T("Main FW Ver : %s"), char_To_wchar(m_pApp->m_szMainFwVersion));
			m_pApp->Gf_writeLogData(_T("<PG>"), strlog);
		}

		if (lpModelInfo->m_nSignalType == 0)
		{
			m_pApp->m_pCommand->Gf_setSRunerTypeSelect(0);
			if (m_pApp->m_pCommand->Gf_getFpgaeVersion() == TRUE)
			{
				CString strlog;
				strlog.Format(_T("LVDS FPGA FW Ver : %s"), lpWorkInfo->m_sFpgaVersion);
				m_pApp->Gf_writeLogData(_T("<FPGA>"), strlog);
			}
		}
		else
		{
			m_pApp->m_pCommand->Gf_setSRunerTypeSelect(1);
			if (m_pApp->m_pCommand->Gf_getFpgaeVersion() == TRUE)
			{
				CString strlog;
				strlog.Format(_T("DP FPGA FW Ver : %s"), lpWorkInfo->m_sFpgaVersion);
				m_pApp->Gf_writeLogData(_T("<FPGA>"), strlog);
			}
		}
	}
	
	int m_nChkPoint = 0;
	for(int i=0; i<20; i++)
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SetTimer(1,20,NULL);
}
