// Maint.cpp: 구현 파일
//

#include "stdafx.h"
#include "GIE_BoadAssy.h"
#include "afxdialogex.h"
#include "Maint.h"


// CMaint 대화 상자

IMPLEMENT_DYNAMIC(CMaint, CDialog)

CMaint::CMaint(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_MAINT, pParent)
{

}

CMaint::~CMaint()
{
}

void CMaint::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_DI_01, m_chkDioIn01);
	DDX_Control(pDX, IDC_CHECK_DI_02, m_chkDioIn02);
	DDX_Control(pDX, IDC_CHECK_DI_03, m_chkDioIn03);
	DDX_Control(pDX, IDC_CHECK_DI_04, m_chkDioIn04);
	DDX_Control(pDX, IDC_CHECK_DI_05, m_chkDioIn05);
	DDX_Control(pDX, IDC_CHECK_DI_06, m_chkDioIn06);
	DDX_Control(pDX, IDC_CHECK_DI_07, m_chkDioIn07);
	DDX_Control(pDX, IDC_CHECK_DI_08, m_chkDioIn08);
	DDX_Control(pDX, IDC_CHECK_DO_01, m_chkDioOut01);
	DDX_Control(pDX, IDC_CHECK_DO_02, m_chkDioOut02);
	DDX_Control(pDX, IDC_CHECK_DO_03, m_chkDioOut03);
	DDX_Control(pDX, IDC_CHECK_DO_04, m_chkDioOut04);
	DDX_Control(pDX, IDC_CHECK_DO_05, m_chkDioOut05);
	DDX_Control(pDX, IDC_CHECK_DO_06, m_chkDioOut06);
	DDX_Control(pDX, IDC_CHECK_DO_07, m_chkDioOut07);
	DDX_Control(pDX, IDC_CHECK_DO_08, m_chkDioOut08);
	DDX_Control(pDX, IDC_CMB_PATTERN_LIST, m_cmbMtPatternList);
}


BEGIN_MESSAGE_MAP(CMaint, CDialog)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CHECK_DO_01, &CMaint::OnBnClickedCheckDo01)
	ON_BN_CLICKED(IDC_CHECK_DO_02, &CMaint::OnBnClickedCheckDo02)
	ON_BN_CLICKED(IDC_CHECK_DO_03, &CMaint::OnBnClickedCheckDo03)
	ON_BN_CLICKED(IDC_CHECK_DO_04, &CMaint::OnBnClickedCheckDo04)
	ON_BN_CLICKED(IDC_CHECK_DO_05, &CMaint::OnBnClickedCheckDo05)
	ON_BN_CLICKED(IDC_CHECK_DO_06, &CMaint::OnBnClickedCheckDo06)
	ON_BN_CLICKED(IDC_CHECK_DO_07, &CMaint::OnBnClickedCheckDo07)
	ON_BN_CLICKED(IDC_CHECK_DO_08, &CMaint::OnBnClickedCheckDo08)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_POWER_ON, &CMaint::OnBnClickedBtnPowerOn)
	ON_BN_CLICKED(IDC_BTN_POWER_OFF, &CMaint::OnBnClickedBtnPowerOff)
	ON_CBN_SELCHANGE(IDC_CMB_PATTERN_LIST, &CMaint::OnCbnSelchangeCmbPatternList)
END_MESSAGE_MAP()


// CMaint 메시지 처리기


BOOL CMaint::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	lpModelInfo = m_pApp->GetModelInfo();

	m_uDioOutBit = 0;
	Lf_setCombPatternList();

	SetTimer(1, 500, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
void CMaint::OnDestroy()
{
	CDialog::OnDestroy();
	m_pApp->m_pCommand->Gf_setPowerSeqOnOff(POWER_OFF); 
	m_pApp->m_pDio7230->Dio_DO_WritePort(DIO_OUT_RESET);
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

void CMaint::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	// DIO Input
	if (nIDEvent == 1)
	{
		KillTimer(1);
		U32 uDioIn;
		uDioIn = m_pApp->m_pDio7230->Dio_DI_ReadPort();
		if (uDioIn & DIO_IN_01)
		{
			m_chkDioIn01.SetCheck(TRUE);
		}
		else
		{
			m_chkDioIn01.SetCheck(FALSE);
		}
		if (uDioIn & DIO_IN_02)
		{
			m_chkDioIn02.SetCheck(TRUE);
		}
		else
		{
			m_chkDioIn02.SetCheck(FALSE);
		}
		if (uDioIn & DIO_IN_03)
		{
			m_chkDioIn03.SetCheck(TRUE);
		}
		else
		{
			m_chkDioIn03.SetCheck(FALSE);
		}
		if (uDioIn & DIO_IN_04)
		{
			m_chkDioIn04.SetCheck(TRUE);
		}
		else
		{
			m_chkDioIn04.SetCheck(FALSE);
		}
		if (uDioIn & DIO_IN_05)
		{
			m_chkDioIn05.SetCheck(TRUE);
		}
		else
		{
			m_chkDioIn05.SetCheck(FALSE);
		}
		if (uDioIn & DIO_IN_06)
		{
			m_chkDioIn06.SetCheck(TRUE);
		}
		else
		{
			m_chkDioIn06.SetCheck(FALSE);
		}
		if (uDioIn & DIO_IN_07)
		{
			m_chkDioIn07.SetCheck(TRUE);
		}
		else
		{
			m_chkDioIn07.SetCheck(FALSE);
		}
		if (uDioIn & DIO_IN_08)
		{
			m_chkDioIn08.SetCheck(TRUE);
		}
		else
		{
			m_chkDioIn08.SetCheck(FALSE);
		}

		SetTimer(1, 500, NULL);
	}
	if (nIDEvent == 10)
	{
		Lf_getPowerMeasureAll();
	}
	CDialog::OnTimer(nIDEvent);
}


void CMaint::OnBnClickedCheckDo01()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_chkDioOut01.GetCheck() == TRUE)
		m_uDioOutBit |= DIO_OUT_01;
	else
		m_uDioOutBit &= ~DIO_OUT_01;
	m_pApp->m_pDio7230->Dio_DO_WritePort(m_uDioOutBit);
}


void CMaint::OnBnClickedCheckDo02()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_chkDioOut02.GetCheck() == TRUE)
		m_uDioOutBit |= DIO_OUT_02;
	else
		m_uDioOutBit &= ~DIO_OUT_02;
	m_pApp->m_pDio7230->Dio_DO_WritePort(m_uDioOutBit);
}


void CMaint::OnBnClickedCheckDo03()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_chkDioOut03.GetCheck() == TRUE)
		m_uDioOutBit |= DIO_OUT_03;
	else
		m_uDioOutBit &= ~DIO_OUT_03;
	m_pApp->m_pDio7230->Dio_DO_WritePort(m_uDioOutBit);
}


void CMaint::OnBnClickedCheckDo04()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_chkDioOut04.GetCheck() == TRUE)
		m_uDioOutBit |= DIO_OUT_04;
	else
		m_uDioOutBit &= ~DIO_OUT_04;
	m_pApp->m_pDio7230->Dio_DO_WritePort(m_uDioOutBit);
}


void CMaint::OnBnClickedCheckDo05()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_chkDioOut05.GetCheck() == TRUE)
		m_uDioOutBit |= DIO_OUT_05;
	else
		m_uDioOutBit &= ~DIO_OUT_05;
	m_pApp->m_pDio7230->Dio_DO_WritePort(m_uDioOutBit);
}


void CMaint::OnBnClickedCheckDo06()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_chkDioOut06.GetCheck() == TRUE)
		m_uDioOutBit |= DIO_OUT_06;
	else
		m_uDioOutBit &= ~DIO_OUT_06;
	m_pApp->m_pDio7230->Dio_DO_WritePort(m_uDioOutBit);
}


void CMaint::OnBnClickedCheckDo07()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_chkDioOut07.GetCheck() == TRUE)
		m_uDioOutBit |= DIO_OUT_07;
	else
		m_uDioOutBit &= ~DIO_OUT_07;
	m_pApp->m_pDio7230->Dio_DO_WritePort(m_uDioOutBit);
}


void CMaint::OnBnClickedCheckDo08()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_chkDioOut08.GetCheck() == TRUE)
		m_uDioOutBit |= DIO_OUT_08;
	else
		m_uDioOutBit &= ~DIO_OUT_08;
	m_pApp->m_pDio7230->Dio_DO_WritePort(m_uDioOutBit);
}

void CMaint::Lf_setCombPatternList()
{
	CString strfilename;
	WIN32_FIND_DATA wfd;
	HANDLE hSearch;
	CComboBox* m_pCmb; 
	m_pCmb = (CComboBox*)GetDlgItem(IDC_CMB_PATTERN_LIST);
	hSearch = FindFirstFile(_T(".\\Pattern\\*.pdb"), &wfd);

	if (hSearch != INVALID_HANDLE_VALUE)
	{
		if (wfd.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
		{
			strfilename.Format(_T("%s"), wfd.cFileName);
			strfilename = strfilename.Mid(0, strfilename.GetLength() - 4);
			strfilename.MakeUpper();
			m_pCmb->AddString(strfilename);
		}
		while (FindNextFile(hSearch, &wfd))
		{
			if (wfd.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
			{
				strfilename.Format(_T("%s"), wfd.cFileName);
				strfilename = strfilename.Mid(0, strfilename.GetLength() - 4);
				strfilename.MakeUpper();
				m_pCmb->AddString(strfilename);
			}
		}
		FindClose(hSearch);
	}
	hSearch = FindFirstFile(_T(".\\Pattern\\BMP\\*.bmp"), &wfd);

	if (hSearch != INVALID_HANDLE_VALUE)
	{
		if (wfd.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
		{
			strfilename.Format(_T("%s"), wfd.cFileName);
			strfilename.MakeUpper();
			m_pCmb->AddString(strfilename);
		}
		while (FindNextFile(hSearch, &wfd))
		{
			if (wfd.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
			{
				strfilename.Format(_T("%s"), wfd.cFileName);
				strfilename.MakeUpper();
				m_pCmb->AddString(strfilename);
			}
		}
		FindClose(hSearch);
	}

	m_pCmb->SetCurSel(0);
}



void CMaint::OnBnClickedBtnPowerOn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_pApp->m_pCommand->Gf_setPowerSeqOnOff(POWER_ON);
	SetTimer(10, 1000, NULL);
}


void CMaint::OnBnClickedBtnPowerOff()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	KillTimer(10);
	m_pApp->m_pCommand->Gf_setPowerSeqOnOff(POWER_OFF);
}
BOOL CMaint::Lf_getPowerMeasureAll()
{
	CString sdata;
	memset(m_pApp->m_nLcmPInfo, 0x00, sizeof(m_pApp->m_nLcmPInfo));
	if (m_pApp->m_pCommand->Gf_getPowerMeasure() == TRUE)
	{
		if (m_pApp->m_nLcmPInfo[PINFO_ERR_RESULT] == OVER_CURRENT)
		{
			if (m_pApp->m_nLcmPInfo[PINFO_ERR_NAME] == PINFO_VCC)
			{
				sdata.Format(_T("VCC Over Voltage (High Set: %.2f, Measure: %.2f)"), (float)lpModelInfo->m_fLimitVccMax, (float)(m_pApp->m_nLcmPInfo[PINFO_ERR_VALUE] / 1000.f));
				m_pApp->Gf_ShowMessageBox(sdata);//AfxMessageBox(sdata);
			}
			else if (m_pApp->m_nLcmPInfo[PINFO_ERR_NAME] == PINFO_VDD)
			{
				sdata.Format(_T("VDD Over Voltage (High Set: %.2f, Measure: %.2f)"), (float)lpModelInfo->m_fLimitVddMax, (float)(m_pApp->m_nLcmPInfo[PINFO_ERR_VALUE] / 1000.f));
				m_pApp->Gf_ShowMessageBox(sdata);//AfxMessageBox(sdata);
			}
			else if (m_pApp->m_nLcmPInfo[PINFO_ERR_NAME] == PINFO_ICC)
			{
				sdata.Format(_T("ICC Over Current (High Set: %.2f, Measure: %d)"), (float)lpModelInfo->m_fLimitIccMax, m_pApp->m_nLcmPInfo[PINFO_ERR_VALUE] / 1000.f);
				m_pApp->Gf_ShowMessageBox(sdata);//AfxMessageBox(sdata);
			}
			else if (m_pApp->m_nLcmPInfo[PINFO_ERR_NAME] == PINFO_IDD)
			{
				sdata.Format(_T("IDD Over Current (High Set: %d, Measure: %d)"), (float)lpModelInfo->m_fLimitIddMax, m_pApp->m_nLcmPInfo[PINFO_ERR_VALUE]/1000.f);
				m_pApp->Gf_ShowMessageBox(sdata);//AfxMessageBox(sdata);
			}
			if (m_pApp->m_nLcmPInfo[PINFO_ERR_NAME] == PINFO_VGH)
			{
				sdata.Format(_T("VGH Over Voltage (High Set: %.2f, Measure: %.2f)"), (float)lpModelInfo->m_fLimitVghMax, (float)(m_pApp->m_nLcmPInfo[PINFO_ERR_VALUE] / 1000.f));
				m_pApp->Gf_ShowMessageBox(sdata);//AfxMessageBox(sdata);
			}
			else if (m_pApp->m_nLcmPInfo[PINFO_ERR_NAME] == PINFO_VGL)
			{
				sdata.Format(_T("VGL Over Voltage (High Set: %.2f, Measure: %.2f)"), (float)lpModelInfo->m_fLimitVddMax, (float)(m_pApp->m_nLcmPInfo[PINFO_ERR_VALUE] / 1000.f));
				m_pApp->Gf_ShowMessageBox(sdata);//AfxMessageBox(sdata);
			}
			else if (m_pApp->m_nLcmPInfo[PINFO_ERR_NAME] == PINFO_IGH)
			{
				sdata.Format(_T("IGH Over Current (High Set: %.2f, Measure: %d)"), (float)lpModelInfo->m_fLimitIghMax, m_pApp->m_nLcmPInfo[PINFO_ERR_VALUE] / 1000.f);
				m_pApp->Gf_ShowMessageBox(sdata);//AfxMessageBox(sdata);
			}
			else if (m_pApp->m_nLcmPInfo[PINFO_ERR_NAME] == PINFO_IGL)
			{
				sdata.Format(_T("IGL Over Current (High Set: %d, Measure: %d)"), (float)lpModelInfo->m_fLimitIglMax, m_pApp->m_nLcmPInfo[PINFO_ERR_VALUE] / 1000.f);
				m_pApp->m_pCommand->Gf_ShowMessageBox(sdata);//AfxMessageBox(sdata);
			}

			return FALSE;
		}
		else if (m_pApp->m_nLcmPInfo[PINFO_ERR_RESULT] == LOW_CURRENT)
		{
			if (m_pApp->m_nLcmPInfo[PINFO_ERR_NAME] == PINFO_VCC)
			{
				sdata.Format(_T("VCC Low Voltage (Low Set: %.2f, Measure: %.2f)"), (float)lpModelInfo->m_fLimitVccMin, (float)(m_pApp->m_nLcmPInfo[PINFO_ERR_VALUE] / 1000.f));
				m_pApp->Gf_ShowMessageBox(sdata);//AfxMessageBox(sdata);
			}
			else if (m_pApp->m_nLcmPInfo[PINFO_ERR_NAME] == PINFO_VDD)
			{
				sdata.Format(_T("VDD Low Voltage (Low Set: %.2f, Measure: %.2f)"), (float)lpModelInfo->m_fLimitVddMin, (float)(m_pApp->m_nLcmPInfo[PINFO_ERR_VALUE] / 1000.f));
				m_pApp->Gf_ShowMessageBox(sdata);//AfxMessageBox(sdata);
			}
			else if (m_pApp->m_nLcmPInfo[PINFO_ERR_NAME] == PINFO_ICC)
			{
				sdata.Format(_T("ICC Low Current (Low Set: %.2f, Measure: %d)"), (float)lpModelInfo->m_fLimitIccMin, m_pApp->m_nLcmPInfo[PINFO_ERR_VALUE] / 1000.f);
				m_pApp->Gf_ShowMessageBox(sdata);//AfxMessageBox(sdata);
			}
			else if (m_pApp->m_nLcmPInfo[PINFO_ERR_NAME] == PINFO_IDD)
			{
				sdata.Format(_T("IDD Low Current (Low Set: %d, Measure: %d)"), (float)lpModelInfo->m_fLimitIddMin, m_pApp->m_nLcmPInfo[PINFO_ERR_VALUE] / 1000.f);
				m_pApp->Gf_ShowMessageBox(sdata);//AfxMessageBox(sdata);
			}
			if (m_pApp->m_nLcmPInfo[PINFO_ERR_NAME] == PINFO_VGH)
			{
				sdata.Format(_T("VGH Low Voltage (Low Set: %.2f, Measure: %.2f)"), (float)lpModelInfo->m_fLimitVghMin, (float)(m_pApp->m_nLcmPInfo[PINFO_ERR_VALUE] / 1000.f));
				m_pApp->Gf_ShowMessageBox(sdata);//AfxMessageBox(sdata);
			}
			else if (m_pApp->m_nLcmPInfo[PINFO_ERR_NAME] == PINFO_VGL)
			{
				sdata.Format(_T("VGL Low Voltage (Low Set: %.2f, Measure: %.2f)"), (float)lpModelInfo->m_fLimitVddMin, (float)(m_pApp->m_nLcmPInfo[PINFO_ERR_VALUE] / 1000.f));
				m_pApp->Gf_ShowMessageBox(sdata);//AfxMessageBox(sdata);
			}
			else if (m_pApp->m_nLcmPInfo[PINFO_ERR_NAME] == PINFO_IGH)
			{
				sdata.Format(_T("IGH Low Current (Low Set: %.2f, Measure: %d)"), (float)lpModelInfo->m_fLimitIghMin, m_pApp->m_nLcmPInfo[PINFO_ERR_VALUE] / 1000.f);
				m_pApp->Gf_ShowMessageBox(sdata);//AfxMessageBox(sdata);
			}
			else if (m_pApp->m_nLcmPInfo[PINFO_ERR_NAME] == PINFO_IGL)
			{
				sdata.Format(_T("IGL Low Current (Low Set: %d, Measure: %d)"), (float)lpModelInfo->m_fLimitIglMin, m_pApp->m_nLcmPInfo[PINFO_ERR_VALUE] / 1000.f);
				m_pApp->Gf_ShowMessageBox(sdata);//AfxMessageBox(sdata);
			}
			return FALSE;
		}
	}

	sdata.Format(_T("%.3f V"), (float)(m_pApp->m_nLcmPInfo[PINFO_VCC] /1000.f));
	GetDlgItem(IDC_STT_MT_VCC_MEASURE)->SetWindowText(sdata);
	sdata.Format(_T("%.3f V"), (float)(m_pApp->m_nLcmPInfo[PINFO_VDD] / 1000.f));
	GetDlgItem(IDC_STT_MT_VDD_MEASURE)->SetWindowText(sdata);
	sdata.Format(_T("%.3f V"), (float)(m_pApp->m_nLcmPInfo[PINFO_VGH] / 1000.f));
	GetDlgItem(IDC_STT_MT_VGH_MEASURE)->SetWindowText(sdata);
	sdata.Format(_T("%.3f V"), (float)(m_pApp->m_nLcmPInfo[PINFO_VGL] / 1000.f));
	GetDlgItem(IDC_STT_MT_VGL_MEASURE)->SetWindowText(sdata);

	sdata.Format(_T("%.3f A"), (float)(m_pApp->m_nLcmPInfo[PINFO_ICC] / 1000.f));
	GetDlgItem(IDC_STT_MT_ICC_MEASURE)->SetWindowText(sdata);
	sdata.Format(_T("%.3f A"), (float)(m_pApp->m_nLcmPInfo[PINFO_IDD] / 1000.f));
	GetDlgItem(IDC_STT_MT_IDD_MEASURE)->SetWindowText(sdata);
	sdata.Format(_T("%.3f A"), (float)(m_pApp->m_nLcmPInfo[PINFO_IGH] / 1000.f));
	GetDlgItem(IDC_STT_MT_IGH_MEASURE)->SetWindowText(sdata);
	sdata.Format(_T("%.3f A"), (float)(m_pApp->m_nLcmPInfo[PINFO_IGL] / 1000.f));
	GetDlgItem(IDC_STT_MT_IGL_MEASURE)->SetWindowText(sdata);


	return TRUE;
}

void CMaint::OnCbnSelchangeCmbPatternList()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strPtnName;
	m_cmbMtPatternList.GetWindowTextW(strPtnName);
	strPtnName.MakeUpper();

	if (lpModelInfo->m_nGfd250 == TRUE)
		m_pApp->m_pCommand->Gf_setPGInfoGFD250(strPtnName);
	else
		m_pApp->m_pCommand->Gf_setPGInfoPatternName(strPtnName);
}
