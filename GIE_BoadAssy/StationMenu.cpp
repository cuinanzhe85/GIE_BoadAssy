// StationMenu.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GIE_BoadAssy.h"
#include "StationMenu.h"
#include "Initialize.h"

// CStationMenu 대화 상자입니다.

IMPLEMENT_DYNAMIC(CStationMenu, CDialog)

CStationMenu::CStationMenu(CWnd* pParent /*=NULL*/)
	: CDialog(CStationMenu::IDD, pParent)
{

}

CStationMenu::~CStationMenu()
{
}

void CStationMenu::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CBO_AUTO_BCR_COMPORT, m_cboBcrComPort);
	DDX_Control(pDX, IDC_CBO_BLU_COMPORT, m_cboBluComPort);
	DDX_Control(pDX, IDC_EDT_EQP_NAME, m_edtEqpName);
	DDX_Control(pDX, IDC_EDT_TEST_START_DELAY, m_edtTestStartDelay);
	DDX_Control(pDX, IDC_EDIT_MES_SERVICEPORT, m_edtMesServicePort);
	DDX_Control(pDX, IDC_EDIT_MES_NETWORK, m_edtMesNetwork);
	DDX_Control(pDX, IDC_EDIT_MES_DEMONPORT, m_edtMesDaemonPort);
	DDX_Control(pDX, IDC_EDIT_MES_LOCALSUBJECT, m_edtMesLocalSubject);
	DDX_Control(pDX, IDC_EDIT_MES_REMOTESUBJECT, m_edtMesRemoteSubject);
	DDX_Control(pDX, IDC_IPADDRESS_LOCAL_IP, m_ipaMesLocalIp);
	DDX_Control(pDX, IDC_EDT_MOD_FILE_PATH, m_edtModFilePath);
	DDX_Control(pDX, IDC_EDT_PTN_FILE_PATH, m_edtPtnFilePath);
	DDX_Control(pDX, IDC_EDT_EDID_FILE_PATH, m_edtEdidFilePath);
	DDX_Control(pDX, IDC_CBO_EAS_USE, m_cmbEasUse);
	DDX_Control(pDX, IDC_EDIT_EAS_SERVICEPORT, m_edtEasServicePort);
	DDX_Control(pDX, IDC_EDIT_EAS_NETWORK, m_edtEasNetwork);
	DDX_Control(pDX, IDC_EDIT_EAS_DEMONPORT, m_edtEasDaemonPort);
	DDX_Control(pDX, IDC_EDIT_EAS_LOCALSUBJECT, m_edtEasLocalSubject);
	DDX_Control(pDX, IDC_EDIT_EAS_REMOTESUBJECT, m_edtEasRemoteSubject);
	DDX_Control(pDX, IDC_CMB_PLC_DEVICE_NUM, m_cmbPlcDeviceNum);
	DDX_Control(pDX, IDC_IPA_TCPIP_PLC_IPADDR, m_ipaPlcIPAddress);
	DDX_Control(pDX, IDC_EDT_TCPIP_PLC_PORT, m_edtPlcPort);
	DDX_Control(pDX, IDC_CMB_PINBLOCK_OPEN_CHECK, m_cmbPinBlockOpenCheck);
}


BEGIN_MESSAGE_MAP(CStationMenu, CDialog)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_SAVE, &CStationMenu::OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_QUALITY_SETUP, &CStationMenu::OnBnClickedBtnQualitySetup)
	ON_BN_CLICKED(IDC_BTN_QUALITY_FTP_SETUP, &CStationMenu::OnBnClickedBtnQualityFtpSetup)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_CANCEL, &CStationMenu::OnBnClickedBtnCancel)
	ON_BN_CLICKED(IDC_BTN_MOD_FILE_PATH, &CStationMenu::OnBnClickedBtnModFilePath)
	ON_BN_CLICKED(IDC_BTN_PTN_FILE_PATH, &CStationMenu::OnBnClickedBtnPtnFilePath)
	ON_BN_CLICKED(IDC_BTN_EDID_FILE_PATH, &CStationMenu::OnBnClickedBtnEdidFilePath)
	ON_CBN_SELCHANGE(IDC_CMB_PLC_DEVICE_NUM, &CStationMenu::OnCbnSelchangeCmbPlcDeviceNum)
	ON_BN_CLICKED(IDC_BTN_QUANTITY_COUNT_RESET, &CStationMenu::OnBnClickedBtnQuantityCountReset)
END_MESSAGE_MAP()


// CStationMenu 메시지 처리기입니다.

BOOL CStationMenu::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	lpSystemInfo = m_pApp->GetSystemInfo();	

	Lf_initFontSet();
	Lf_initControls();

	HICON hIcon;
	CButton* pBtn;
	hIcon = AfxGetApp()->LoadIconW(IDI_ICON_SAVE);
	pBtn = (CButton*)GetDlgItem(IDC_BTN_SAVE);
	pBtn->SetIcon(hIcon);

	hIcon = AfxGetApp()->LoadIconW(IDI_ICON_CLOSE);
	pBtn = (CButton*)GetDlgItem(IDC_BTN_CANCEL);
	pBtn->SetIcon(hIcon);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CStationMenu::OnDestroy()
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

HBRUSH CStationMenu::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
		if(pWnd->GetDlgCtrlID()==IDC_STT_STATIONDLG_TIT)
		{
			pDC->SetBkColor(COLOR_DEEP_BLUE);
			pDC->SetTextColor(COLOR_WHITE);
			return m_Brush[COLOR_IDX_DEEP_BLUE];
		}
		if((pWnd->GetDlgCtrlID()==IDC_STT_SYS_TIT)
			|| (pWnd->GetDlgCtrlID()==IDC_STT_PORT_TIT)
			|| (pWnd->GetDlgCtrlID()==IDC_STT_MES_TIT)
			|| (pWnd->GetDlgCtrlID()==IDC_STT_PATH_TIT)
			|| (pWnd->GetDlgCtrlID() == IDC_STT_EAS_TIT)
			|| (pWnd->GetDlgCtrlID() == IDC_STT_TCPIP_PLC_TIT)
			)
		{
			pDC->SetBkColor(COLOR_LIGHT_BLUE);
			pDC->SetTextColor(COLOR_BLACK);
			return m_Brush[COLOR_IDX_LIGHT_BLUE];
		}
		if ((pWnd->GetDlgCtrlID() == IDC_STT_EQP_NAME)
			|| (pWnd->GetDlgCtrlID() == IDC_STT_TEST_START_DELAY)
			|| (pWnd->GetDlgCtrlID() == IDC_STT_PINBLOCK_OPEN_CHECK)
			|| (pWnd->GetDlgCtrlID() == IDC_STT_AUTO_BCR_PORT)
			|| (pWnd->GetDlgCtrlID() == IDC_STT_BLU_PORT)
			|| (pWnd->GetDlgCtrlID() == IDC_STT_MES_SERV_PORT)
			|| (pWnd->GetDlgCtrlID() == IDC_STT_MES_NETWORK)
			|| (pWnd->GetDlgCtrlID() == IDC_STT_MES_DEAMON)
			|| (pWnd->GetDlgCtrlID() == IDC_STT_MES_LOCAL_SUBJ)
			|| (pWnd->GetDlgCtrlID() == IDC_STT_MES_REMOTE_SUBJ)
			|| (pWnd->GetDlgCtrlID() == IDC_STT_MES_LOCAL_IP)
			|| (pWnd->GetDlgCtrlID() == IDC_STT_MODEL_PATH)
			|| (pWnd->GetDlgCtrlID() == IDC_STT_PATTERN_PATH)
			|| (pWnd->GetDlgCtrlID() == IDC_STT_EDID_FILE_PATH)
			|| (pWnd->GetDlgCtrlID() == IDC_STT_EAS_SERV_PORT)
			|| (pWnd->GetDlgCtrlID() == IDC_STT_EAS_NETWORK)
			|| (pWnd->GetDlgCtrlID() == IDC_STT_EAS_DEAMON)
			|| (pWnd->GetDlgCtrlID() == IDC_STT_EAS_LOCAL_SUBJ)
			|| (pWnd->GetDlgCtrlID() == IDC_STT_EAS_REMOTE_SUBJ)
			|| (pWnd->GetDlgCtrlID() == IDC_STT_EAS_USE)
			|| (pWnd->GetDlgCtrlID() == IDC_STT_PLC_DEVICE_NUM)
			|| (pWnd->GetDlgCtrlID() == IDC_STT_TCPIP_PLC_IPADDR)
			|| (pWnd->GetDlgCtrlID() == IDC_STT_TCPIP_PLC_PORT)
			)
		{
			pDC->SetBkColor(COLOR_BLUISH);
			pDC->SetTextColor(COLOR_WHITE);
			return m_Brush[COLOR_IDX_BLUISH];
		}
		break;
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}

void CStationMenu::OnPaint()
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
	dc.FillSolidRect(rect, COLOR_ORANGE);

	GetClientRect(&rect);
	rect.top = 92;
	dc.FillSolidRect(rect, COLOR_WHITE);
}

void CStationMenu::Lf_initFontSet()
{
	/*************************************************************************************************/
	// Font Set
	m_Font[0].CreateFont(24, 11, 0, 0, FW_SEMIBOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("Segoe UI Symbol"));

	m_Font[1].CreateFont(60, 26, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("Segoe UI Symbol"));
	GetDlgItem(IDC_STT_STATIONDLG_TIT)->SetFont(&m_Font[1]);
	

	m_Font[2].CreateFont(34, 14, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("Segoe UI Symbol"));
	GetDlgItem(IDC_BTN_SAVE)->SetFont(&m_Font[2]);
	GetDlgItem(IDC_BTN_CANCEL)->SetFont(&m_Font[2]);

	m_Font[3].CreateFont(19, 8, 0, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0, 0, 0, _T("Segoe UI  Symbol"));
	GetDlgItem(IDC_STT_SYS_TIT)->SetFont(&m_Font[3]);
	GetDlgItem(IDC_STT_PORT_TIT)->SetFont(&m_Font[3]);
	GetDlgItem(IDC_STT_MES_TIT)->SetFont(&m_Font[3]);
	GetDlgItem(IDC_STT_EAS_TIT)->SetFont(&m_Font[3]);
	GetDlgItem(IDC_STT_PATH_TIT)->SetFont(&m_Font[3]);
	GetDlgItem(IDC_STT_TCPIP_PLC_TIT)->SetFont(&m_Font[3]);

	m_Font[4].CreateFont(15, 8, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("Segoe UI Symbol"));
	GetDlgItem(IDC_EDT_EQP_NAME)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_EDT_TEST_START_DELAY)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_CMB_PINBLOCK_OPEN_CHECK)->SetFont(&m_Font[4]);

	GetDlgItem(IDC_CBO_AUTO_BCR_COMPORT)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_CBO_BLU_COMPORT)->SetFont(&m_Font[4]);

	GetDlgItem(IDC_EDIT_MES_SERVICEPORT)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_EDIT_MES_NETWORK)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_EDIT_MES_DEMONPORT)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_EDIT_MES_LOCALSUBJECT)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_EDIT_MES_REMOTESUBJECT)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_IPADDRESS_LOCAL_IP)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_BTN_QUALITY_SETUP)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_BTN_QUALITY_FTP_SETUP)->SetFont(&m_Font[4]);

	GetDlgItem(IDC_EDT_MOD_FILE_PATH)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_EDT_PTN_FILE_PATH)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_EDT_EDID_FILE_PATH)->SetFont(&m_Font[4]);

	GetDlgItem(IDC_STT_EQP_NAME)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_TEST_START_DELAY)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_PINBLOCK_OPEN_CHECK)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_AUTO_BCR_PORT)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_BLU_PORT)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_MES_SERV_PORT)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_MES_NETWORK)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_MES_DEAMON)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_MES_LOCAL_SUBJ)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_MES_REMOTE_SUBJ)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_MES_LOCAL_IP)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_MODEL_PATH)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_PATTERN_PATH)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_EDID_FILE_PATH)->SetFont(&m_Font[4]);

	GetDlgItem(IDC_STT_PLC_DEVICE_NUM)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_CMB_PLC_DEVICE_NUM)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_TCPIP_PLC_IPADDR)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_IPA_TCPIP_PLC_IPADDR)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_TCPIP_PLC_PORT)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_EDT_TCPIP_PLC_PORT)->SetFont(&m_Font[4]);

	GetDlgItem(IDC_STT_EAS_USE)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_EAS_SERV_PORT)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_EAS_NETWORK)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_EAS_DEAMON)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_EAS_LOCAL_SUBJ)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_EAS_REMOTE_SUBJ)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_EDIT_EAS_SERVICEPORT)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_EDIT_EAS_NETWORK)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_EDIT_EAS_DEMONPORT)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_EDIT_EAS_LOCALSUBJECT)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_EDIT_EAS_REMOTESUBJECT)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_CBO_EAS_USE)->SetFont(&m_Font[4]);

	m_Font[5].CreateFont(150, 70, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("ARIAL"));

	/*************************************************************************************************/
	// Brush Set
	m_Brush[COLOR_IDX_ORANGE].CreateSolidBrush (COLOR_ORANGE);
	m_Brush[COLOR_IDX_RED].CreateSolidBrush (COLOR_RED);
	m_Brush[COLOR_IDX_GRAY64].CreateSolidBrush (COLOR_GRAY64);
	m_Brush[COLOR_IDX_GRAY94].CreateSolidBrush (COLOR_GRAY94);
	m_Brush[COLOR_IDX_LIGHT_GREEN].CreateSolidBrush (COLOR_LIGHT_GREEN);
	m_Brush[COLOR_IDX_LIGHT_BLUE].CreateSolidBrush (COLOR_LIGHT_BLUE);
	m_Brush[COLOR_IDX_WHITE].CreateSolidBrush (COLOR_WHITE);
	m_Brush[COLOR_IDX_DEEP_BLUE].CreateSolidBrush (COLOR_DEEP_BLUE);
	m_Brush[COLOR_IDX_BLUISH].CreateSolidBrush(COLOR_BLUISH);
}

void CStationMenu::Lf_initControls()
{
	CString sdata=_T("");

	m_edtEqpName.SetWindowText(lpSystemInfo->m_sMachinName);

	sdata.Format(_T("%d"), lpSystemInfo->m_nTestStartDelay);
	m_edtTestStartDelay.SetWindowText(sdata);


	m_cboBcrComPort.SetCurSel(lpSystemInfo->m_nAutoBcrPort);

	m_cboBluComPort.SetCurSel(lpSystemInfo->m_nLedBlPort);

	m_edtMesServicePort.SetWindowText(lpSystemInfo->sMesServicePort);
	m_edtMesNetwork.SetWindowText(lpSystemInfo->sMesNetWork);
	m_edtMesDaemonPort.SetWindowText(lpSystemInfo->sMesDaemonPort);
	m_edtMesLocalSubject.SetWindowText(lpSystemInfo->sMesLocalSubject);
	m_edtMesRemoteSubject.SetWindowText(lpSystemInfo->sMesRemoteSubject);
	m_ipaMesLocalIp.SetWindowText(lpSystemInfo->sLocalIP);

	m_cmbEasUse.SetCurSel(lpSystemInfo->bEasUse);
	m_edtEasServicePort.SetWindowText(lpSystemInfo->sEasServicePort);
	m_edtEasNetwork.SetWindowText(lpSystemInfo->sEasNetWork);
	m_edtEasDaemonPort.SetWindowText(lpSystemInfo->sEasDaemonPort);
	m_edtEasLocalSubject.SetWindowText(lpSystemInfo->sEasLocalSubject);
	m_edtEasRemoteSubject.SetWindowText(lpSystemInfo->sEasRemoteSubject);

	m_cmbPlcDeviceNum.SetCurSel(lpSystemInfo->m_nPlcDeviceNum);
	m_ipaPlcIPAddress.SetWindowText(lpSystemInfo->m_sPlcIPAddress);
	m_edtPlcPort.SetWindowText(lpSystemInfo->m_sPlcPort);

	m_cmbPinBlockOpenCheck.SetCurSel(lpSystemInfo->m_nPinBlockOpenCheck);

	m_edtModFilePath.SetWindowText(lpSystemInfo->m_sModelDnPath);
	m_edtPtnFilePath.SetWindowText(lpSystemInfo->m_sPatternPath);
	m_edtEdidFilePath.SetWindowText(lpSystemInfo->m_sEdidDnPath);

	UpdateData(FALSE);
}

void CStationMenu::Lf_saveSystemInfo()
{
	UpdateData(TRUE);

	CString sdata=_T("");

	m_pApp->Gf_writeLogData(_T("<WND>"),_T("SYSTEM Setting Save"));

	m_edtEqpName.GetWindowText(sdata);
	lpSystemInfo->m_sMachinName.Format(_T("%s"),sdata);
	Write_SysIniFile(_T("SYSTEM"), _T("MACHIN_NAME"), lpSystemInfo->m_sMachinName);

	m_edtTestStartDelay.GetWindowText(sdata);
	lpSystemInfo->m_nTestStartDelay = _ttoi(sdata);
	Write_SysIniFile(_T("SYSTEM"), _T("TEST_START_DELAY"), lpSystemInfo->m_nTestStartDelay);

	lpSystemInfo->m_nAutoBcrPort = m_cboBcrComPort.GetCurSel();
	Write_SysIniFile(_T("SYSTEM"), _T("AUTO_BCR_PORT"), lpSystemInfo->m_nAutoBcrPort);

	lpSystemInfo->m_nLedBlPort = m_cboBluComPort.GetCurSel();
	Write_SysIniFile(_T("SYSTEM"), _T("LED_BL_PORT"), lpSystemInfo->m_nLedBlPort);

	m_edtMesServicePort.GetWindowText(lpSystemInfo->sMesServicePort);
	Write_SysIniFile(_T("GMES"), _T("SERVICE"),							lpSystemInfo->sMesServicePort);

	m_edtMesNetwork.GetWindowText(lpSystemInfo->sMesNetWork);
	Write_SysIniFile(_T("GMES"), _T("NETWORK"),									lpSystemInfo->sMesNetWork);

	m_edtMesDaemonPort.GetWindowText(lpSystemInfo->sMesDaemonPort);
	Write_SysIniFile(_T("GMES"), _T("DAEMON_PORT"),								lpSystemInfo->sMesDaemonPort);

	m_edtMesLocalSubject.GetWindowText(lpSystemInfo->sMesLocalSubject);
	Write_SysIniFile(_T("GMES"), _T("LOCAL_SUBJECT"),							lpSystemInfo->sMesLocalSubject);

	m_edtMesRemoteSubject.GetWindowText(lpSystemInfo->sMesRemoteSubject);
	Write_SysIniFile(_T("GMES"), _T("REMOTE_SUBJECT"),							lpSystemInfo->sMesRemoteSubject);

	m_ipaMesLocalIp.GetWindowText(lpSystemInfo->sLocalIP);
	Write_SysIniFile(_T("GMES"), _T("LOCAL_IP"),								lpSystemInfo->sLocalIP);

	lpSystemInfo->bEasUse = m_cmbEasUse.GetCurSel();
	Write_SysIniFile(_T("EAS"), _T("EAS_USE"), lpSystemInfo->bEasUse);

	m_edtEasServicePort.GetWindowText(lpSystemInfo->sEasServicePort);
	Write_SysIniFile(_T("EAS"), _T("EAS_SERVICE"), lpSystemInfo->sEasServicePort);

	m_edtEasNetwork.GetWindowText(lpSystemInfo->sEasNetWork);
	Write_SysIniFile(_T("EAS"), _T("EAS_NETWORK"), lpSystemInfo->sEasNetWork);

	m_edtEasDaemonPort.GetWindowText(lpSystemInfo->sEasDaemonPort);
	Write_SysIniFile(_T("EAS"), _T("EAS_DAEMON_PORT"), lpSystemInfo->sEasDaemonPort);

	m_edtEasLocalSubject.GetWindowText(lpSystemInfo->sEasLocalSubject);
	Write_SysIniFile(_T("EAS"), _T("EAS_LOCAL_SUBJECT"), lpSystemInfo->sEasLocalSubject);

	m_edtEasRemoteSubject.GetWindowText(lpSystemInfo->sEasRemoteSubject);
	Write_SysIniFile(_T("EAS"), _T("EAS_REMOTE_SUBJECT"), lpSystemInfo->sEasRemoteSubject);

	lpSystemInfo->m_nPlcDeviceNum = m_cmbPlcDeviceNum.GetCurSel();
	Write_SysIniFile(_T("TCPIP_PLC"), _T("PLC_DEVICE_NUM"), lpSystemInfo->m_nPlcDeviceNum);

	m_ipaPlcIPAddress.GetWindowText(lpSystemInfo->m_sPlcIPAddress);
	Write_SysIniFile(_T("TCPIP_PLC"), _T("PLC_IP_ADDRESS"), lpSystemInfo->m_sPlcIPAddress);

	m_edtPlcPort.GetWindowText(lpSystemInfo->m_sPlcPort);
	Write_SysIniFile(_T("TCPIP_PLC"), _T("PLC_PORT"), lpSystemInfo->m_sPlcPort);


	lpSystemInfo->m_nPinBlockOpenCheck = m_cmbPinBlockOpenCheck.GetCurSel();
	Write_SysIniFile(_T("SYSTEM"), _T("PIN_BLOCK_OPEN_CHECK"), lpSystemInfo->m_nPinBlockOpenCheck);

 	m_edtModFilePath.GetWindowText(lpSystemInfo->m_sModelDnPath);
 	Write_SysIniFile(_T("SYSTEM"), _T("MODEL_FILE_PATH"), lpSystemInfo->m_sModelDnPath);
 
 	m_edtPtnFilePath.GetWindowText(lpSystemInfo->m_sPatternPath);
 	Write_SysIniFile(_T("SYSTEM"), _T("PATTERN_FILE_PATH"), lpSystemInfo->m_sPatternPath);
 
 	m_edtEdidFilePath.GetWindowText(lpSystemInfo->m_sEdidDnPath);
 	Write_SysIniFile(_T("SYSTEM"), _T("EDID_PATH"), lpSystemInfo->m_sEdidDnPath);
}

CString CStationMenu::Lf_FileLoadDialog(CString Temp)
{
	LPITEMIDLIST pidlBrowse;
	
	BOOL bRtn = FALSE;

	wchar_t wszPathName[256] = { 0, };
	wsprintf(wszPathName, _T("%s"), Temp.GetBuffer(0));

	BROWSEINFO BrInfo;
	BrInfo.hwndOwner = GetSafeHwnd();
	BrInfo.pidlRoot = NULL;
	memset(&BrInfo, 0, sizeof(BrInfo));
	BrInfo.pszDisplayName = NULL;

	BrInfo.lpszTitle = _T("Select Folder");
	BrInfo.ulFlags = BIF_RETURNONLYFSDIRS;

	BrInfo.ulFlags = BIF_RETURNONLYFSDIRS;
	BrInfo.lpfn = BrowseForFolder_CallbackProc;
	BrInfo.lParam = (LPARAM)wszPathName;


	if (pidlBrowse = SHBrowseForFolder(&BrInfo))
	{
		if (SUCCEEDED(SHGetPathFromIDList(pidlBrowse, wszPathName)))
			bRtn = TRUE;

		LPMALLOC pMalloc;
		if (SUCCEEDED(SHGetMalloc(&pMalloc)))
		{
			pMalloc->Free(pidlBrowse);
			pMalloc->Release();
		}
	}

	if (pidlBrowse != NULL)
	{
		return  wszPathName;
	}
	else
	{
		return Temp;
	}
}

void CStationMenu::OnBnClickedBtnSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_saveSystemInfo();

	CInitialize initDlg;

	initDlg.DoModal();

	CDialog::OnOK();
}

void CStationMenu::OnBnClickedBtnCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialog::OnCancel();
}

void CStationMenu::OnBnClickedBtnQualitySetup()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ShowDefectCodeSet(GetSafeOwner());
}

void CStationMenu::OnBnClickedBtnQualityFtpSetup()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ShowDefectCodeSetFTP(GetSafeOwner());
}

void CStationMenu::OnBnClickedBtnModFilePath()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sdata;

	UpdateData(TRUE);
	m_edtModFilePath.GetWindowText(sdata);
	m_edtModFilePath.SetWindowText(Lf_FileLoadDialog(sdata));
	UpdateData(FALSE);
}

void CStationMenu::OnBnClickedBtnPtnFilePath()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sdata;

	UpdateData(TRUE);
	m_edtPtnFilePath.GetWindowText(sdata);
	m_edtPtnFilePath.SetWindowText(Lf_FileLoadDialog(sdata));
	UpdateData(FALSE);
}

void CStationMenu::OnBnClickedBtnEdidFilePath()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sdata;

	UpdateData(TRUE);
	m_edtEdidFilePath.GetWindowText(sdata);
	m_edtEdidFilePath.SetWindowText(Lf_FileLoadDialog(sdata));
	UpdateData(FALSE);
}


void CStationMenu::OnCbnSelchangeCmbPlcDeviceNum()
{
	// TODO: Add your control notification handler code here
	if (m_cmbPlcDeviceNum.GetCurSel() == 0)
		m_edtPlcPort.SetWindowText(_T("4000"));
	else
		m_edtPlcPort.SetWindowText(_T("4001"));
}


void CStationMenu::OnBnClickedBtnQuantityCountReset()
{
	// TODO: Add your control notification handler code here
	m_pApp->Gf_QtyCountReset();
}
