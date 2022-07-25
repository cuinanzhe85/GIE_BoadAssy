
// GIE_BoadAssyDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "GIE_BoadAssy.h"
#include "GIE_BoadAssyDlg.h"
#include "UserId.h"
#include "TestReady.h"
#include "ModelInfo.h"
#include "Initialize.h"
#include "StationMenu.h"
#include "ModelChange.h"
#include "AutoFirmware.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

UINT ThreadDioRead(LPVOID pParam)
{
	CGIE_BoadAssyDlg* pBdAssyDlg = (CGIE_BoadAssyDlg*)pParam;

	while(1)
	{
		m_pApp->m_pDio7230->Gf_getDioGetInput();
		Sleep(10);
	}
	return (0);
}

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CGIE_BoadAssyDlg 대화 상자




CGIE_BoadAssyDlg::CGIE_BoadAssyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGIE_BoadAssyDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGIE_BoadAssyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGIE_BoadAssyDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_USERID, &CGIE_BoadAssyDlg::OnBnClickedBtnUserid)
	ON_BN_CLICKED(IDC_BTN_MODELINFO, &CGIE_BoadAssyDlg::OnBnClickedBtnModelinfo)
	ON_BN_CLICKED(IDC_BTN_TEST, &CGIE_BoadAssyDlg::OnBnClickedBtnTest)
	ON_BN_CLICKED(IDC_BTN_SYSTEM, &CGIE_BoadAssyDlg::OnBnClickedBtnSystem)
	ON_BN_CLICKED(IDC_BTN_EXIT, &CGIE_BoadAssyDlg::OnBnClickedBtnExit)
	ON_MESSAGE(WM_UPDATE_SYSTEM_INFO, OnUpdateSystemInfo)
	ON_MESSAGE(WM_UDP_RECEIVE, OnUdpReceive)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_MODEL_CHANGE, &CGIE_BoadAssyDlg::OnBnClickedBtnModelChange)
	ON_BN_CLICKED(IDC_BTN_AUTOFIRMWARE, &CGIE_BoadAssyDlg::OnBnClickedBtnAutofirmware)
	ON_BN_CLICKED(IDC_BTN_INITIALIZE, &CGIE_BoadAssyDlg::OnBnClickedBtnInitialize)
	ON_WM_CTLCOLOR()
	ON_WM_DESTROY()
	ON_WM_DRAWITEM()
END_MESSAGE_MAP()


// CGIE_BoadAssyDlg 메시지 처리기

BOOL CGIE_BoadAssyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	ShowWindow(SW_MAXIMIZE);

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	lpSystemInfo = m_pApp->GetSystemInfo();
	lpModelInfo	= m_pApp->GetModelInfo();
	lpWorkInfo = m_pApp->GetWorkInfo();

	Lf_InitFontSet();

	AfxBeginThread(ThreadDioRead, this);
	SetTimer(1, 200, NULL);
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CGIE_BoadAssyDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CGIE_BoadAssyDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);

		
	}
	else
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트
		CRect rect;
		GetClientRect(&rect);
		rect.bottom = 100;
		dc.FillSolidRect(rect, COLOR_GRAY64);
		GetClientRect(&rect);
		rect.top = 101;
		dc.FillSolidRect(rect, COLOR_GRAY64);

		CDialog::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CGIE_BoadAssyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

HBRUSH CGIE_BoadAssyDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
		if((pWnd->GetDlgCtrlID()==IDC_STT_STATION_INFO_TIT)
		|| (pWnd->GetDlgCtrlID()==IDC_STT_MODEL_INFO_TIT))
		{
			pDC->SetBkColor(COLOR_DEEP_BLUE);
			pDC->SetTextColor(COLOR_WHITE);
			return m_Brush[COLOR_IDX_DEEP_BLUE];
		}
		if((pWnd->GetDlgCtrlID()==IDC_STT_EQP_NAME_VALUE)
		|| (pWnd->GetDlgCtrlID()==IDC_STT_OP_MODE_VALUE)
		|| (pWnd->GetDlgCtrlID()==IDC_STT_USER_ID_VALUE)
		|| (pWnd->GetDlgCtrlID()==IDC_STT_USER_NAME_VALUE)
		|| (pWnd->GetDlgCtrlID()==IDC_STT_MODEL_NAME_VALUE)
		|| (pWnd->GetDlgCtrlID()==IDC_STT_RESOLUTION_VALUE)
		|| (pWnd->GetDlgCtrlID()==IDC_STT_SIGNALBIT_VALUE)
		|| (pWnd->GetDlgCtrlID()==IDC_STT_VCC_VALUE)
		|| (pWnd->GetDlgCtrlID()==IDC_STT_VDD_VALUE)
		|| (pWnd->GetDlgCtrlID()==IDC_STT_ICC_VALUE)
		|| (pWnd->GetDlgCtrlID()==IDC_STT_IDD_VALUE))
		{
			pDC->SetBkColor(COLOR_WHITE);
			pDC->SetTextColor(COLOR_BLACK);
			return m_Brush[COLOR_IDX_WHITE];
		}
		if((pWnd->GetDlgCtrlID()==IDC_STT_EQP_NAME_TIT)
		|| (pWnd->GetDlgCtrlID()==IDC_STT_OP_MODE_TIT)
		|| (pWnd->GetDlgCtrlID()==IDC_STT_USER_ID_TIT)
		|| (pWnd->GetDlgCtrlID()==IDC_STT_USER_NAME_TIT)		
		||(pWnd->GetDlgCtrlID()==IDC_STT_MODEL_NAME_TIT)
		|| (pWnd->GetDlgCtrlID()==IDC_STT_RESOLUTION_TIT)
		|| (pWnd->GetDlgCtrlID()==IDC_STT_SIGNALBIT_TIT)
		|| (pWnd->GetDlgCtrlID()==IDC_STT_VOLT_TIT)
		|| (pWnd->GetDlgCtrlID()==IDC_STT_CURR_TIT))		
		{
			pDC->SetBkColor(COLOR_LIGHT_YELLOW);
			pDC->SetTextColor(COLOR_BLACK);
			return m_Brush[COLOR_IDX_LIGHT_YELLOW];
		}
		if ((pWnd->GetDlgCtrlID() == IDC_STT_VCC_TIT)
			|| (pWnd->GetDlgCtrlID() == IDC_STT_VDD_TIT))
		{
			pDC->SetBkColor(COLOR_LIGHT_BLUE);
			pDC->SetTextColor(COLOR_BLACK);
			return m_Brush[COLOR_IDX_LIGHT_BLUE];
		}
		break;
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}

void CGIE_BoadAssyDlg::OnBnClickedBtnUserid()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CUserID userDlg;
	userDlg.DoModal();
}

void CGIE_BoadAssyDlg::OnBnClickedBtnModelChange()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CModelChange mcDlg;
	mcDlg.DoModal();
}

void CGIE_BoadAssyDlg::OnBnClickedBtnModelinfo()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CModelInfo modDlg;
	modDlg.DoModal();
}

void CGIE_BoadAssyDlg::OnBnClickedBtnTest()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CTestReady TestDlg;
	TestDlg.DoModal();
}

void CGIE_BoadAssyDlg::OnBnClickedBtnSystem()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CStationMenu stDlg;
	stDlg.DoModal();
}

void CGIE_BoadAssyDlg::OnBnClickedBtnAutofirmware()
{
	CAutoFirmware fwDlg;
	fwDlg.DoModal();
}

void CGIE_BoadAssyDlg::OnBnClickedBtnInitialize()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CInitialize initDlg;
	initDlg.DoModal();
}

void CGIE_BoadAssyDlg::OnBnClickedBtnExit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialog::OnOK();
}

void CGIE_BoadAssyDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if(nIDEvent==1)
	{
		KillTimer(1);

		CInitialize initDlg;
		initDlg.DoModal();
	}
	CDialog::OnTimer(nIDEvent);
}
LRESULT CGIE_BoadAssyDlg::OnUdpReceive(WPARAM wParam, LPARAM lParam)
{
	CString strPacket;
	CString recvPacket;
	CString recvIP;

	//	strPacket.Format(_T("%s"), char_To_wchar((char*)wParam));
	m_pApp->udp_processPacket((char*)wParam, (int)lParam);

	return 0;
}
LRESULT CGIE_BoadAssyDlg::OnUpdateSystemInfo(WPARAM wParam, LPARAM lParam)
{
	CString sdata=_T("");
	
	GetDlgItem(IDC_STT_EQP_NAME_VALUE)->SetWindowText(lpSystemInfo->m_sMachinName);

	if(lpSystemInfo->m_nOperationMode == OFF_LINE)
		GetDlgItem(IDC_STT_OP_MODE_VALUE)->SetWindowText(_T("OFF-LINE"));
	else
		GetDlgItem(IDC_STT_OP_MODE_VALUE)->SetWindowText(_T("IN-LINE"));

	GetDlgItem(IDC_STT_USER_ID_VALUE)->SetWindowText(lpWorkInfo->m_sUserID);
	GetDlgItem(IDC_STT_USER_NAME_VALUE)->SetWindowText(lpWorkInfo->m_sUserName);

	GetDlgItem(IDC_STT_MODEL_NAME_VALUE)->SetWindowText(lpSystemInfo->m_sModelName);

	sdata.Format(_T("%d x %d"), lpModelInfo->m_nTimingHorActive, lpModelInfo->m_nTimingVerActive);
	GetDlgItem(IDC_STT_RESOLUTION_VALUE)->SetWindowText(sdata);

	if(lpModelInfo->m_nSignalBit==SIG_6BIT)
		GetDlgItem(IDC_STT_SIGNALBIT_VALUE)->SetWindowText(_T("6 Bit"));
	else if(lpModelInfo->m_nSignalBit== SIG_8BIT)
		GetDlgItem(IDC_STT_SIGNALBIT_VALUE)->SetWindowText(_T("8 Bit"));
	else if (lpModelInfo->m_nSignalBit == SIG_10BIT)
		GetDlgItem(IDC_STT_SIGNALBIT_VALUE)->SetWindowText(_T("10 Bit"));
	else if (lpModelInfo->m_nSignalBit == SIG_12BIT)
		GetDlgItem(IDC_STT_SIGNALBIT_VALUE)->SetWindowText(_T("12 Bit"));

	sdata.Format(_T("%.2fV"), lpModelInfo->m_fVoltVcc);
	GetDlgItem(IDC_STT_VCC_VALUE)->SetWindowText(sdata);
	
	sdata.Format(_T("%.2fV"), lpModelInfo->m_fVoltVdd);
	GetDlgItem(IDC_STT_VDD_VALUE)->SetWindowText(sdata);

	sdata.Format(_T("%.2fA"), lpModelInfo->m_fLimitIccMax);
	GetDlgItem(IDC_STT_ICC_VALUE)->SetWindowText(sdata);

	sdata.Format(_T("%.2fA"), lpModelInfo->m_fLimitIddMax);
	GetDlgItem(IDC_STT_IDD_VALUE)->SetWindowText(sdata);

	GetDlgItem(IDC_STT_MAIN_FW_VERSION_VIEW)->SetWindowText(char_To_wchar(m_pApp->m_szMainFwVersion));

	return (0);
}

void CGIE_BoadAssyDlg::Lf_InitFontSet()
{
	/*************************************************************************************************/
	// Font Set
	m_Font[0].CreateFont( 150, 70, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("ARIAL"));
	m_Font[1].CreateFont( 60, 26, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("ARIAL"));
	m_Font[2].CreateFont( 60, 18, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("ARIAL"));
	m_Font[3].CreateFont( 32, 13, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("System"));
	GetDlgItem(IDC_STT_STATION_INFO_TIT)->SetFont(&m_Font[3]);
	GetDlgItem(IDC_STT_MODEL_INFO_TIT)->SetFont(&m_Font[3]);

	m_Font[4].CreateFont( 21, 9, 0, 0, FW_SEMIBOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("System"));
	GetDlgItem(IDC_STT_EQP_NAME_TIT)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_EQP_NAME_VALUE)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_OP_MODE_TIT)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_OP_MODE_VALUE)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_USER_ID_TIT)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_USER_ID_VALUE)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_USER_NAME_TIT)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_USER_NAME_VALUE)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_MODEL_NAME_TIT)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_MODEL_NAME_VALUE)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_RESOLUTION_TIT)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_RESOLUTION_VALUE)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_SIGNALBIT_TIT)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_SIGNALBIT_VALUE)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_VOLT_TIT)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_CURR_TIT)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_VCC_TIT)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_VDD_TIT)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_VCC_VALUE)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_VDD_VALUE)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_ICC_VALUE)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_IDD_VALUE)->SetFont(&m_Font[4]);

	/*************************************************************************************************/
	// Brush Set
	m_Brush[COLOR_IDX_ORANGE].CreateSolidBrush (COLOR_ORANGE);
	m_Brush[COLOR_IDX_RED].CreateSolidBrush (COLOR_RED);
	m_Brush[COLOR_IDX_GRAY64].CreateSolidBrush (COLOR_GRAY64);
	m_Brush[COLOR_IDX_GRAY94].CreateSolidBrush (COLOR_GRAY94);
	m_Brush[COLOR_IDX_LIGHT_GREEN].CreateSolidBrush (COLOR_LIGHT_GREEN);
	m_Brush[COLOR_IDX_GRAY192].CreateSolidBrush (COLOR_GRAY192);
	m_Brush[COLOR_IDX_GRAY224].CreateSolidBrush (COLOR_GRAY224);
	m_Brush[COLOR_IDX_WHITE].CreateSolidBrush (COLOR_WHITE);
	m_Brush[COLOR_IDX_DEEP_BLUE].CreateSolidBrush (COLOR_DEEP_BLUE);	
	m_Brush[COLOR_IDX_LIGHT_YELLOW].CreateSolidBrush(COLOR_LIGHT_YELLOW);
	m_Brush[COLOR_IDX_LIGHT_BLUE].CreateSolidBrush(COLOR_LIGHT_BLUE);
}

void CGIE_BoadAssyDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if(m_pApp->m_bIsGmesConnect == TRUE)
		m_pApp->Gf_gmesDisConnect(SERVER_MES);
}

BOOL CGIE_BoadAssyDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if( pMsg->message == WM_KEYDOWN)
	{
		switch(pMsg->wParam)
		{
		case VK_ESCAPE:
			{
				return TRUE;
			}
		case VK_SPACE:
			{
				CTestReady testrdyDlg;
				testrdyDlg.DoModal();
				return TRUE;
			}
		case 'c':
		case 'C':
			{
				CModelChange mcDlg;
				mcDlg.DoModal();
				return TRUE;
			}
		case 'd':
		case 'D':
			{
				CModelInfo modelDlg;
				modelDlg.DoModal();
				return TRUE;
			}
		case 'i':
		case 'I':
			{
				CInitialize initDlg;
				initDlg.DoModal();
				return TRUE;
			}
		case 's':
		case 'S':
			{
				CStationMenu stationDlg;
				stationDlg.DoModal();
				return TRUE;
			}
		case 'a':
		case 'A':
			{
				CAutoFirmware autofwDlg;
				autofwDlg.DoModal();
				return TRUE;
			}
		case 'u':
		case 'U':
			{
				CUserID userDlg;
				userDlg.DoModal();
				return TRUE;
			}
		default:
			return TRUE;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}


void CGIE_BoadAssyDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if ((nIDCtl == IDC_BTN_USERID) || (nIDCtl == IDC_BTN_MODEL_CHANGE) || (nIDCtl == IDC_BTN_MODELINFO)
		|| (nIDCtl == IDC_BTN_SYSTEM) || (nIDCtl == IDC_BTN_TEST) || (nIDCtl == IDC_BTN_INITIALIZE)
		|| (nIDCtl == IDC_BTN_AUTOFIRMWARE) ||(nIDCtl == IDC_BTN_BMP_DOWNLOAD)|| (nIDCtl == IDC_BTN_EXIT)
		)
	{
		CDC dc;
		RECT rect;
		dc.Attach(lpDrawItemStruct->hDC);   // Get the Button DC to CDC

		rect = lpDrawItemStruct->rcItem;     //Store the Button rect to our local rect.
		dc.Draw3dRect(&rect, COLOR_RED, COLOR_RED);
		dc.FillSolidRect(&rect,COLOR_GRAY127);//Here you can define the required color to appear on the Button.

		TRIVERTEX vert1[2];
		GRADIENT_RECT grt;
		CPen pen1, pen2, pen3, pen4;
		CBrush brush1(RGB(154, 128, 110));
		CBrush brush2(RGB(229, 127, 57));//229,127,57	255,127,39
		CBrush brush3(RGB(0, 0, 0));
		CBrush brush4(RGB(126, 126, 126));

		pen1.CreatePen(PS_SOLID, 1, RGB(154, 128, 110));//154,128,110
		pen2.CreatePen(PS_SOLID, 1, RGB(229, 127, 57));//229,127,57
		pen3.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		pen4.CreatePen(PS_SOLID, 1, RGB(126, 126, 126));//126,126,126

		dc.SelectObject(&brush1);
		dc.SelectObject(&pen1);
		dc.RoundRect(rect.left, rect.top, rect.right, rect.bottom, 0, 0);

		rect.top += 1;
		rect.bottom -= 1;
		rect.left += 1;
		rect.right -= 1;
		dc.SelectObject(&brush2);
		dc.SelectObject(&pen2);
		dc.RoundRect(rect.left, rect.top, rect.right, rect.bottom, 0, 0);

		rect.top += 1;
		rect.bottom -= 1;
		rect.left += 1;
		rect.right -= 1;
		dc.SelectObject(&brush3);
		dc.SelectObject(&pen3);
		dc.RoundRect(rect.left, rect.top, rect.right, rect.bottom, 0, 0);

		rect.top += 1;
		rect.bottom -= 1;
		rect.left += 1;
		rect.right -= 1;
		dc.SelectObject(&brush4);
		dc.SelectObject(&pen4);
		dc.RoundRect(rect.left, rect.top, rect.right, rect.bottom, 0, 0);

		rect.top += 1;
		rect.bottom -= 1;
		rect.left += 1;
		rect.right -= 1;
		vert1[0].x = rect.left;
		vert1[0].y = rect.top;
		vert1[0].Red = 0x4000;
		vert1[0].Green = 0x4000;
		vert1[0].Blue = 0x4000;
		vert1[0].Alpha = 0;
		vert1[1].x = rect.right;
		vert1[1].y = rect.bottom;
		vert1[1].Red = 0x5E00;
		vert1[1].Green = 0x5E00;
		vert1[1].Blue = 0x5E00;
		vert1[1].Alpha = 0;

		grt.LowerRight = 0;
		grt.UpperLeft = 1;
		dc.GradientFill(vert1, 2, &grt, 1, GRADIENT_FILL_RECT_V);

		UINT state = lpDrawItemStruct->itemState;  //This defines the state of the Push button either pressed or not. 
		if ((state & ODS_SELECTED))
		{
			//dc.DrawEdge(&rect,EDGE_SUNKEN,BF_RECT);
			vert1[0].x = rect.left;
			vert1[0].y = rect.top;
			vert1[0].Red = 0x1600;
			vert1[0].Green = 0x1600;
			vert1[0].Blue = 0x1600;
			vert1[0].Alpha = 0;

			vert1[1].x = rect.right;
			vert1[1].y = rect.bottom;
			vert1[1].Red = 0x5E00;
			vert1[1].Green = 0x5E00;
			vert1[1].Blue = 0x5E00;
			vert1[1].Alpha = 0;
			grt.LowerRight = 0;
			grt.UpperLeft = 1;
			dc.GradientFill(vert1, 2, &grt, 1, GRADIENT_FILL_RECT_V);
		}
		else
		{
			//dc.DrawEdge(&rect,EDGE_RAISED,BF_RECT);
			vert1[0].x = rect.left;
			vert1[0].y = rect.top;
			vert1[0].Red = 0x4000;
			vert1[0].Green = 0x4000;
			vert1[0].Blue = 0x4000;
			vert1[0].Alpha = 0;

			vert1[1].x = rect.right;
			vert1[1].y = rect.bottom;
			vert1[1].Red = 0x5E00;
			vert1[1].Green = 0x5E00;
			vert1[1].Blue = 0x5E00;
			vert1[1].Alpha = 0;
			grt.LowerRight = 0;
			grt.UpperLeft = 1;
			dc.GradientFill(vert1, 2, &grt, 1, GRADIENT_FILL_RECT_V);
		}

		//dc.SetBkColor(RGB(104,104,104));   //Setting the Text Background color
		dc.SetTextColor(RGB(255, 255, 255));     //Setting the Text Color
		::SetBkMode(dc, TRANSPARENT);
		TCHAR buffer[MAX_PATH];           //To store the Caption of the button.
		ZeroMemory(buffer, MAX_PATH);     //Intializing the buffer to zero
		::GetWindowText(lpDrawItemStruct->hwndItem, buffer, MAX_PATH); //Get the Caption of Button Window 

		dc.DrawText(buffer, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//Redraw the  Caption of Button Window 
		dc.Detach();
	}
	CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}
