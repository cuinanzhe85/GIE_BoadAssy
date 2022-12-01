// ModelChange.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GIE_BoadAssy.h"
#include "ModelChange.h"
#include "initialize.h"

// CModelChange 대화 상자입니다.

IMPLEMENT_DYNAMIC(CModelChange, CDialog)

CModelChange::CModelChange(CWnd* pParent /*=NULL*/)
	: CDialog(CModelChange::IDD, pParent)
{

}

CModelChange::~CModelChange()
{
}

void CModelChange::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_MODELLIST, m_lcModelList);
	DDX_Control(pDX, IDC_CMB_MODEL_INCH, m_cmbModelInch);
}


BEGIN_MESSAGE_MAP(CModelChange, CDialog)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_LOAD, &CModelChange::OnBnClickedBtnLoad)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_CBN_SELCHANGE(IDC_CMB_MODEL_INCH, &CModelChange::OnCbnSelchangeCmbModelInch)
	ON_BN_CLICKED(IDC_BTN_ALL_MODEL, &CModelChange::OnBnClickedBtnAllModel)
END_MESSAGE_MAP()


// CModelChange 메시지 처리기입니다.

BOOL CModelChange::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	lpSystemInfo	= m_pApp->GetSystemInfo();
	lpModelInfo		= m_pApp->GetModelInfo();

	m_pApp->Gf_writeLogData("<WND>", "Model Change Dialog Open");

	Lf_initFont();
	Lf_initLoadModelList();
	Lf_InitModelInchInfo();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CModelChange::OnDestroy()
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

void CModelChange::Lf_initFont()
{
	m_Font[0].CreateFont(150, 70, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("ARIAL"));

	m_Font[1].CreateFont(60, 26, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("Segoe UI Symbol"));
	GetDlgItem(IDC_STT_MCDLG_TIT)->SetFont(&m_Font[1]);

	m_Font[2].CreateFont(60, 18, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("ARIAL"));

	m_Font[3].CreateFont(24, 11, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("Segoe UI Symbol"));	
	GetDlgItem(IDC_STT_MODEL_SIZE_TITLE)->SetFont(&m_Font[3]);
	GetDlgItem(IDC_CMB_MODEL_INCH)->SetFont(&m_Font[3]);
	GetDlgItem(IDC_STT_INCH)->SetFont(&m_Font[3]);
	GetDlgItem(IDC_BTN_ALL_MODEL)->SetFont(&m_Font[3]);
	GetDlgItem(IDC_STT_MC_DRIVE_PATH)->SetFont(&m_Font[3]);
	GetDlgItem(IDC_STT_MODEL_LIST_TITLE)->SetFont(&m_Font[3]);

	m_Font[4].CreateFont( 16, 6, 0, 0, FW_SEMIBOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("Segoe UI Symbol"));	

	m_Font[5].CreateFont( 36, 16, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0,_T("Segoe UI Symbol"));
	GetDlgItem(IDC_BTN_LOAD)->SetFont(&m_Font[5]);
	GetDlgItem(IDC_EDIT_MODELLIST)->SetFont(&m_Font[5]);

	/*************************************************************************************************/
	// Brush Set
	m_Brush[COLOR_IDX_ORANGE].CreateSolidBrush (COLOR_ORANGE);
	m_Brush[COLOR_IDX_GRAY240].CreateSolidBrush (COLOR_GRAY240);
	m_Brush[COLOR_IDX_DEEP_BLUE].CreateSolidBrush (COLOR_DEEP_BLUE);
	m_Brush[COLOR_IDX_GRAY127].CreateSolidBrush (COLOR_GRAY127);
	m_Brush[COLOR_IDX_GRAY64].CreateSolidBrush(COLOR_GRAY64);
	m_Brush[COLOR_IDX_BLUISH].CreateSolidBrush(COLOR_BLUISH);
	m_Brush[COLOR_IDX_LIGHT_YELLOW].CreateSolidBrush(COLOR_LIGHT_YELLOW);
}

void CModelChange::Lf_initLoadModelList()
{
	CString strfilename=_T("");
	CString strfilepath=_T("");
	WIN32_FIND_DATA wfd;
	HANDLE hSearch;

	strfilepath.Format(_T(".\\Model\\*.mod"));
	hSearch = FindFirstFile (strfilepath, &wfd);

	if (hSearch != INVALID_HANDLE_VALUE)
	{
		if (wfd.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
		{
			strfilename.Format(_T("%s"), wfd.cFileName);
			strfilename = strfilename.Mid(0, strfilename.GetLength()-4);
			strfilename.MakeUpper();
			m_lcModelList.AddString(strfilename);
		}
		while (FindNextFile (hSearch, &wfd))
		{
			if (wfd.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
			{
				strfilename.Format(_T("%s"), wfd.cFileName);
				strfilename = strfilename.Mid(0, strfilename.GetLength()-4);
				strfilename.MakeUpper();
				m_lcModelList.AddString(strfilename);
			}
		}
		FindClose (hSearch);
	}

	for(int i=0; i<m_lcModelList.GetCount(); i++)
	{
		m_lcModelList.GetText(i, strfilename);
		if(strfilename == lpSystemInfo->m_sModelName)
		{
			m_lcModelList.SetCurSel(i);
			break;
		}
	}
}

void CModelChange::OnBnClickedBtnLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString modelName=_T("");

	m_lcModelList.GetText(m_lcModelList.GetCurSel(), modelName);

	Write_SysIniFile(_T("SYSTEM"),		_T("LAST_MODELNAME"),			modelName);

	m_pApp->Gf_writeLogData(_T("<WND>"), modelName);

	//	m_pApp->CopyModelDataFromServer(TRUE);
	//	m_pApp->CopyPatternDataFromServer();

	CInitialize initDlg;
	initDlg.DoModal();

	CDialog::OnOK();
}

HBRUSH CModelChange::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
		if(pWnd->GetDlgCtrlID()==IDC_STT_MCDLG_TIT)
		{
			pDC->SetBkColor(COLOR_DEEP_BLUE);
			pDC->SetTextColor(COLOR_WHITE);
			return m_Brush[COLOR_IDX_DEEP_BLUE];
		}
		if (pWnd->GetDlgCtrlID() == IDC_STT_MODEL_SIZE_TITLE
			|| pWnd->GetDlgCtrlID() == IDC_STT_MODEL_LIST_TITLE)
		{
			pDC->SetBkColor(COLOR_BLUISH);
			pDC->SetTextColor(COLOR_WHITE);
			return m_Brush[COLOR_IDX_BLUISH];
		}
		if (pWnd->GetDlgCtrlID() == IDC_STT_MC_DRIVE_PATH)
		{
			pDC->SetBkColor(COLOR_LIGHT_YELLOW);
			pDC->SetTextColor(COLOR_RED);
			return m_Brush[COLOR_IDX_LIGHT_YELLOW];
		}
		if (pWnd->GetDlgCtrlID() == IDC_STT_INCH)
		{
			pDC->SetBkColor(COLOR_GRAY64);
			pDC->SetTextColor(COLOR_WHITE);
			return m_Brush[COLOR_IDX_GRAY64];
		}
		break;
	}	
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}

void CModelChange::OnPaint()
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
	dc.FillSolidRect(rect, COLOR_RED);

	GetClientRect(&rect);
	rect.top = 92;
	dc.FillSolidRect(rect, COLOR_GRAY64);
}

void CModelChange::Lf_InitModelInchInfo()
{
	CString sDatafolder;
	CString sFile, sInch, sDrive;
	int find_idx;
	WIN32_FIND_DATA wfd;
	HANDLE hSearch;

	m_cmbModelInch.ResetContent();
	m_cmbModelInch.AddString(_T("ALL"));

	// ********* Host에서 MOD List를 불러올떄  **********
	sDatafolder.Format(_T("%s\\*.MOD"), lpSystemInfo->m_sModelDnPath);
	hSearch = FindFirstFile(sDatafolder, &wfd);
	if (hSearch != INVALID_HANDLE_VALUE)
	{
		sDrive.Format(_T("DRIVE : %s"), lpSystemInfo->m_sModelDnPath.Left(1));
		GetDlgItem(IDC_STT_MC_DRIVE_PATH)->SetWindowText(sDrive);

		if (wfd.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
		{
			sFile.Format(_T("%s"), wfd.cFileName);
			sInch.Format(_T("%s"), sFile.Mid(2, 3));
			m_cmbModelInch.AddString(sInch);
		}
		while (FindNextFile(hSearch, &wfd))
		{
			if (wfd.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
			{
				sFile.Format(_T("%s"), wfd.cFileName);
				sInch.Format(_T("%s"), sFile.Mid(2, 3));
				find_idx = m_cmbModelInch.FindStringExact(0, sInch);
				if (find_idx == -1)
				{
					m_cmbModelInch.AddString(sInch);
				}
			}
		}
		FindClose(hSearch);
	}
	else
	{
		TCHAR szCurrentPath[1024] = { 0, };
		GetCurrentDirectory(sizeof(szCurrentPath), szCurrentPath);

		sDrive.Format(_T("DRIVE : %c"), szCurrentPath[0]);
		GetDlgItem(IDC_STT_MC_DRIVE_PATH)->SetWindowText(sDrive);

		// Local Folder에서 Model List를 가져올 때
		sDatafolder.Format(_T(".\\Model\\*.MOD"));
		hSearch = FindFirstFile(sDatafolder, &wfd);

		if (hSearch != INVALID_HANDLE_VALUE)
		{
			if (wfd.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
			{
				sFile.Format(_T("%s"), wfd.cFileName);
				sInch.Format(_T("%s"), sFile.Mid(2, 3));
				m_cmbModelInch.AddString(sInch);
			}
			while (FindNextFile(hSearch, &wfd))
			{
				sFile.Format(_T("%s"), wfd.cFileName);
				sInch.Format(_T("%s"), sFile.Mid(2, 3));
				find_idx = m_cmbModelInch.FindStringExact(0, sInch);
				if (find_idx == -1)
				{
					m_cmbModelInch.AddString(sInch);
				}
			}
			FindClose(hSearch);
		}
		else
		{
		}
	}

	m_cmbModelInch.SetCurSel(0);
}
void CModelChange::Lf_LoadModelList()
{
	CString sDatafolder;
	CString sInch;
	WIN32_FIND_DATA wfd;
	HANDLE hSearch;

	GetDlgItem(IDC_CMB_MODEL_INCH)->GetWindowText(sInch);

	if (sInch == _T("ALL"))
		sDatafolder.Format(_T("%s\\*.MOD"), lpSystemInfo->m_sModelDnPath);
	else
		sDatafolder.Format(_T("%s\\*%s*.MOD"), lpSystemInfo->m_sModelDnPath, sInch);

	m_lcModelList.ResetContent();
	// ********* Host에서 MOD List를 불러올떄  **********
	hSearch = FindFirstFile(sDatafolder, &wfd);
	if (hSearch != INVALID_HANDLE_VALUE)
	{
		if (wfd.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
		{
			CString filename;
			filename = wfd.cFileName;
			filename.Delete(filename.GetLength() - 4, 4);
			m_lcModelList.AddString(filename);
		}
		while (FindNextFile(hSearch, &wfd))
		{
			if (wfd.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
			{
				CString filename;
				filename = wfd.cFileName;
				filename.Delete(filename.GetLength() - 4, 4);
				m_lcModelList.AddString(filename);
			}
		}
		FindClose(hSearch);
	}
	else
	{
		// Local Folder에서 Model List를 가져올 때
		if (sInch == _T("ALL"))
			sDatafolder.Format(_T(".\\Model\\*.MOD"));
		else
			sDatafolder.Format(_T(".\\Model\\*%s*.MOD"), sInch);

		hSearch = FindFirstFile(sDatafolder, &wfd);

		if (hSearch != INVALID_HANDLE_VALUE)
		{
			if (wfd.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
			{
				CString filename;
				filename = wfd.cFileName;
				filename.Delete(filename.GetLength() - 4, 4);
				m_lcModelList.AddString(filename);
			}
			while (FindNextFile(hSearch, &wfd))
			{
				if (wfd.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
				{
					CString filename;
					filename = wfd.cFileName;
					filename.Delete(filename.GetLength() - 4, 4);
					m_lcModelList.AddString(filename);
				}
			}
			FindClose(hSearch);
		}
		else
		{
		}
	}
	UpdateData(FALSE);


	CString buff;

	m_lcModelList.SetCurSel(0);
	for (int i = 0; i < m_lcModelList.GetCount(); i++)
	{
		m_lcModelList.GetText(i, buff);
		if (!lpSystemInfo->m_sModelName.Compare(buff))
		{
			m_lcModelList.SetCurSel(i);
			break;
		}
	}
}

void CModelChange::OnCbnSelchangeCmbModelInch()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lf_LoadModelList();
}


void CModelChange::OnBnClickedBtnAllModel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_cmbModelInch.SetCurSel(0);	// 0번 Index는 무조건 ALL 이다.
	Lf_LoadModelList();
}
