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
}


BEGIN_MESSAGE_MAP(CModelChange, CDialog)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_LOAD, &CModelChange::OnBnClickedBtnLoad)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CModelChange 메시지 처리기입니다.

BOOL CModelChange::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	lpSystemInfo	= m_pApp->GetSystemInfo();
	lpModelInfo		= m_pApp->GetModelInfo();

	m_pApp->Gf_writeLogData("[Model Change]", "Dialog Open");

	Lf_initFont();
	Lf_initLoadModelList();

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

	m_Font[4].CreateFont( 16, 6, 0, 0, FW_SEMIBOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("Segoe UI Symbol"));	

	m_Font[5].CreateFont( 36, 16, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0,_T("Segoe UI Symbol"));
	GetDlgItem(IDC_BTN_LOAD)->SetFont(&m_Font[5]);
	GetDlgItem(IDC_EDIT_MODELLIST)->SetFont(&m_Font[5]);

	/*************************************************************************************************/
	// Brush Set
	m_Brush[0].CreateSolidBrush (COLOR_ORANGE);
	m_Brush[1].CreateSolidBrush (COLOR_GRAY240);
	m_Brush[COLOR_IDX_DEEP_BLUE].CreateSolidBrush (COLOR_DEEP_BLUE);
	m_Brush[3].CreateSolidBrush (RGB(128,128,128));
	m_Brush[4].CreateSolidBrush (RGB(128,128,128));
}

void CModelChange::Lf_initLoadModelList()
{
	CString strfilename=_T("");
	CString strfilepath=_T("");
	WIN32_FIND_DATA wfd;
	HANDLE hSearch;

	strfilepath.Format(_T(".\\Model\\*.mol"));
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

	m_pApp->Gf_writeLogData(_T("[Model Change]"), modelName);

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
}
