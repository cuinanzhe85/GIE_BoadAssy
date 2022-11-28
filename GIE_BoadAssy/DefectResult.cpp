// DefectResult.cpp: 구현 파일
//

#include "stdafx.h"
#include "GIE_BoadAssy.h"
#include "DefectResult.h"
#include "afxdialogex.h"


// CDefectResult 대화 상자

IMPLEMENT_DYNAMIC(CDefectResult, CDialog)

CDefectResult::CDefectResult(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DEFECT_RESULT, pParent)
{

}

CDefectResult::~CDefectResult()
{
}

void CDefectResult::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STT_DEF_1_TO_1, m_sttButton_1to1);
	DDX_Control(pDX, IDC_STT_DEF_1_TO_2, m_sttButton_1to2);
	DDX_Control(pDX, IDC_STT_DEF_1_TO_3, m_sttButton_1to3);
	DDX_Control(pDX, IDC_STT_DEF_1_TO_4, m_sttButton_1to4);
	DDX_Control(pDX, IDC_STT_DEF_1_TO_5, m_sttButton_1to5);
	DDX_Control(pDX, IDC_STT_DEF_1_TO_6, m_sttButton_1to6);
	DDX_Control(pDX, IDC_STT_DEF_1_TO_7, m_sttButton_1to7);
	DDX_Control(pDX, IDC_STT_DEF_1_TO_8, m_sttButton_1to8);
	DDX_Control(pDX, IDC_STT_DEF_1_TO_9, m_sttButton_1to9);
	DDX_Control(pDX, IDC_STT_DEF_1_TO_10, m_sttButton_1to10);
	DDX_Control(pDX, IDC_STT_DEF_2_TO_1, m_sttButton_2to1);
	DDX_Control(pDX, IDC_STT_DEF_2_TO_2, m_sttButton_2to2);
	DDX_Control(pDX, IDC_STT_DEF_2_TO_3, m_sttButton_2to3);
	DDX_Control(pDX, IDC_STT_DEF_2_TO_4, m_sttButton_2to4);
	DDX_Control(pDX, IDC_STT_DEF_2_TO_5, m_sttButton_2to5);
	DDX_Control(pDX, IDC_STT_DEF_2_TO_6, m_sttButton_2to6);
	DDX_Control(pDX, IDC_STT_DEF_2_TO_7, m_sttButton_2to7);
	DDX_Control(pDX, IDC_STT_DEF_2_TO_8, m_sttButton_2to8);
	DDX_Control(pDX, IDC_STT_DEF_2_TO_9, m_sttButton_2to9);
	DDX_Control(pDX, IDC_STT_DEF_2_TO_10, m_sttButton_2to10);
	DDX_Control(pDX, IDC_STT_DEF_3_TO_1, m_sttButton_3to1);
	DDX_Control(pDX, IDC_STT_DEF_3_TO_2, m_sttButton_3to2);
	DDX_Control(pDX, IDC_STT_DEF_3_TO_3, m_sttButton_3to3);
	DDX_Control(pDX, IDC_STT_DEF_3_TO_4, m_sttButton_3to4);
	DDX_Control(pDX, IDC_STT_DEF_3_TO_5, m_sttButton_3to5);
	DDX_Control(pDX, IDC_STT_DEF_3_TO_6, m_sttButton_3to6);
	DDX_Control(pDX, IDC_STT_DEF_3_TO_7, m_sttButton_3to7);
	DDX_Control(pDX, IDC_STT_DEF_3_TO_8, m_sttButton_3to8);
	DDX_Control(pDX, IDC_STT_DEF_3_TO_9, m_sttButton_3to9);
	DDX_Control(pDX, IDC_STT_DEF_3_TO_10, m_sttButton_3to10);
	DDX_Control(pDX, IDC_STT_DEF_4_TO_1, m_sttButton_4to1);
	DDX_Control(pDX, IDC_STT_DEF_4_TO_2, m_sttButton_4to2);
	DDX_Control(pDX, IDC_STT_DEF_4_TO_3, m_sttButton_4to3);
	DDX_Control(pDX, IDC_STT_DEF_4_TO_4, m_sttButton_4to4);
	DDX_Control(pDX, IDC_STT_DEF_4_TO_5, m_sttButton_4to5);
	DDX_Control(pDX, IDC_STT_DEF_4_TO_6, m_sttButton_4to6);
	DDX_Control(pDX, IDC_STT_DEF_4_TO_7, m_sttButton_4to7);
	DDX_Control(pDX, IDC_STT_DEF_4_TO_8, m_sttButton_4to8);
	DDX_Control(pDX, IDC_STT_DEF_4_TO_9, m_sttButton_4to9);
	DDX_Control(pDX, IDC_STT_DEF_4_TO_10, m_sttButton_4to10);
	DDX_Control(pDX, IDC_STT_DEF_5_TO_1, m_sttButton_5to1);
	DDX_Control(pDX, IDC_STT_DEF_5_TO_2, m_sttButton_5to2);
	DDX_Control(pDX, IDC_STT_DEF_5_TO_3, m_sttButton_5to3);
	DDX_Control(pDX, IDC_STT_DEF_5_TO_4, m_sttButton_5to4);
	DDX_Control(pDX, IDC_STT_DEF_5_TO_5, m_sttButton_5to5);
	DDX_Control(pDX, IDC_STT_DEF_5_TO_6, m_sttButton_5to6);
	DDX_Control(pDX, IDC_STT_DEF_5_TO_7, m_sttButton_5to7);
	DDX_Control(pDX, IDC_STT_DEF_5_TO_8, m_sttButton_5to8);
	DDX_Control(pDX, IDC_STT_DEF_5_TO_9, m_sttButton_5to9);
	DDX_Control(pDX, IDC_STT_DEF_5_TO_10, m_sttButton_5to10);
	DDX_Control(pDX, IDC_STT_DEF_6_TO_1, m_sttButton_6to1);
	DDX_Control(pDX, IDC_STT_DEF_6_TO_2, m_sttButton_6to2);
	DDX_Control(pDX, IDC_STT_DEF_6_TO_3, m_sttButton_6to3);
	DDX_Control(pDX, IDC_STT_DEF_6_TO_4, m_sttButton_6to4);
	DDX_Control(pDX, IDC_STT_DEF_6_TO_5, m_sttButton_6to5);
	DDX_Control(pDX, IDC_STT_DEF_6_TO_6, m_sttButton_6to6);
	DDX_Control(pDX, IDC_STT_DEF_6_TO_7, m_sttButton_6to7);
	DDX_Control(pDX, IDC_STT_DEF_6_TO_8, m_sttButton_6to8);
	DDX_Control(pDX, IDC_STT_DEF_6_TO_9, m_sttButton_6to9);
	DDX_Control(pDX, IDC_STT_DEF_6_TO_10, m_sttButton_6to10);
	DDX_Control(pDX, IDC_STT_DEF_7_TO_1, m_sttButton_7to1);
	DDX_Control(pDX, IDC_STT_DEF_7_TO_2, m_sttButton_7to2);
	DDX_Control(pDX, IDC_STT_DEF_7_TO_3, m_sttButton_7to3);
	DDX_Control(pDX, IDC_STT_DEF_7_TO_4, m_sttButton_7to4);
	DDX_Control(pDX, IDC_STT_DEF_7_TO_5, m_sttButton_7to5);
	DDX_Control(pDX, IDC_STT_DEF_7_TO_6, m_sttButton_7to6);
	DDX_Control(pDX, IDC_STT_DEF_7_TO_7, m_sttButton_7to7);
	DDX_Control(pDX, IDC_STT_DEF_7_TO_8, m_sttButton_7to8);
	DDX_Control(pDX, IDC_STT_DEF_7_TO_9, m_sttButton_7to9);
	DDX_Control(pDX, IDC_STT_DEF_7_TO_10, m_sttButton_7to10);
	DDX_Control(pDX, IDC_STT_DEF_8_TO_1, m_sttButton_8to1);
	DDX_Control(pDX, IDC_STT_DEF_8_TO_2, m_sttButton_8to2);
	DDX_Control(pDX, IDC_STT_DEF_8_TO_3, m_sttButton_8to3);
	DDX_Control(pDX, IDC_STT_DEF_8_TO_4, m_sttButton_8to4);
	DDX_Control(pDX, IDC_STT_DEF_8_TO_5, m_sttButton_8to5);
	DDX_Control(pDX, IDC_STT_DEF_8_TO_6, m_sttButton_8to6);
	DDX_Control(pDX, IDC_STT_DEF_8_TO_7, m_sttButton_8to7);
	DDX_Control(pDX, IDC_STT_DEF_8_TO_8, m_sttButton_8to8);
	DDX_Control(pDX, IDC_STT_DEF_8_TO_9, m_sttButton_8to9);
	DDX_Control(pDX, IDC_STT_DEF_8_TO_10, m_sttButton_8to10);
	DDX_Control(pDX, IDC_STT_DEF_9_TO_1, m_sttButton_9to1);
	DDX_Control(pDX, IDC_STT_DEF_9_TO_2, m_sttButton_9to2);
	DDX_Control(pDX, IDC_STT_DEF_9_TO_3, m_sttButton_9to3);
	DDX_Control(pDX, IDC_STT_DEF_9_TO_4, m_sttButton_9to4);
	DDX_Control(pDX, IDC_STT_DEF_9_TO_5, m_sttButton_9to5);
	DDX_Control(pDX, IDC_STT_DEF_9_TO_6, m_sttButton_9to6);
	DDX_Control(pDX, IDC_STT_DEF_9_TO_7, m_sttButton_9to7);
	DDX_Control(pDX, IDC_STT_DEF_9_TO_8, m_sttButton_9to8);
	DDX_Control(pDX, IDC_STT_DEF_9_TO_9, m_sttButton_9to9);
	DDX_Control(pDX, IDC_STT_DEF_9_TO_10, m_sttButton_9to10);
	DDX_Control(pDX, IDC_STT_DEF_10_TO_1, m_sttButton_10to1);
	DDX_Control(pDX, IDC_STT_DEF_10_TO_2, m_sttButton_10to2);
	DDX_Control(pDX, IDC_STT_DEF_10_TO_3, m_sttButton_10to3);
	DDX_Control(pDX, IDC_STT_DEF_10_TO_4, m_sttButton_10to4);
	DDX_Control(pDX, IDC_STT_DEF_10_TO_5, m_sttButton_10to5);
	DDX_Control(pDX, IDC_STT_DEF_10_TO_6, m_sttButton_10to6);
	DDX_Control(pDX, IDC_STT_DEF_10_TO_7, m_sttButton_10to7);
	DDX_Control(pDX, IDC_STT_DEF_10_TO_8, m_sttButton_10to8);
	DDX_Control(pDX, IDC_STT_DEF_10_TO_9, m_sttButton_10to9);
	DDX_Control(pDX, IDC_STT_DEF_10_TO_10, m_sttButton_10to10);

}


BEGIN_MESSAGE_MAP(CDefectResult, CDialog)
	ON_WM_DESTROY()
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CDefectResult 메시지 처리기


BOOL CDefectResult::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	Lf_InitLocalValue();
	Lf_InitFontset();
	Lf_InitColorBrush();

	Lf_initStaticButton();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CDefectResult::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


BOOL CDefectResult::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CDialog::PreTranslateMessage(pMsg);
}


HBRUSH CDefectResult::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void CDefectResult::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialog::OnPaint()을(를) 호출하지 마십시오.
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CDefectResult::Lf_InitLocalValue()
{
}

void CDefectResult::Lf_InitFontset()
{
	m_Font[0].CreateFont(150, 70, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("ARIAL"));
	m_Font[1].CreateFont(60, 26, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("ARIAL"));
	m_Font[2].CreateFont(24, 11, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("ARIAL"));
	m_Font[3].CreateFont(32, 13, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("ARIAL"));
	m_Font[4].CreateFont(17, 6, 0, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0, 0, 0, _T("ARIAL"));
}

void CDefectResult::Lf_InitColorBrush()
{

}

void CDefectResult::Lf_initStaticButton()
{
	CString fileName, strSection, strKey, strValue;

	fileName.Format(_T("./Module_Defect_Ini/HB_MODULE_20220622_01_VN.ANSI.ini"));
	strSection.Format(_T("SIMPLIFY"));

	for (int x = 0; x < 10; x++)
	{
		for (int y = 0; y < 10; y++)
		{
			strKey.Format(_T("MATRIX(%d,%d)"), x + 1, y + 1);
			//Read_ProfileString(fileName, strSection, strKey, &strValue);
			Read_DefectIniFile(fileName, strSection, strKey, &strValue);

			if (strValue == _T(""))
			{
				m_pDefectButton[x][y].m_pButtonControl = Lf_getStaticControl(x, y);
				m_pDefectButton[x][y].m_sButtonName.Empty();
				m_pDefectButton[x][y].m_sButtonReasonCode.Empty();
				m_pDefectButton[x][y].m_ButtonColor = RGB(255, 255, 255);
			}
			else
			{
				m_pDefectButton[x][y].m_pButtonControl		= Lf_getStaticControl(x, y);
				m_pDefectButton[x][y].m_sButtonName			= Lf_getStaticButtonName(x, y, strValue);
				m_pDefectButton[x][y].m_sButtonReasonCode	= Lf_getStaticReasonCode(x, y, strValue);
				m_pDefectButton[x][y].m_ButtonColor			= Lf_getStaticButtonColor(x, y, strValue);

				m_pDefectButton[x][y].m_pButtonControl->SetWindowText(m_pDefectButton[x][y].m_sButtonName);
				m_pApp->Gf_setGradientStatic(m_pDefectButton[x][y].m_pButtonControl, m_pDefectButton[x][y].m_ButtonColor, &m_Font[4], 0);
			}
		}
	}
}

CGradientStatic* CDefectResult::Lf_getStaticControl(int x, int y)
{
	if (x == 0)
	{
		if (y == 0)	return &m_sttButton_1to1;
		if (y == 1)	return &m_sttButton_1to2;
		if (y == 2)	return &m_sttButton_1to3;
		if (y == 3)	return &m_sttButton_1to4;
		if (y == 4)	return &m_sttButton_1to5;
		if (y == 5)	return &m_sttButton_1to6;
		if (y == 6)	return &m_sttButton_1to7;
		if (y == 7)	return &m_sttButton_1to8;
		if (y == 8)	return &m_sttButton_1to9;
		if (y == 9)	return &m_sttButton_1to10;
	}
	else if (x == 1)
	{
		if (y == 0)	return &m_sttButton_2to1;
		if (y == 1)	return &m_sttButton_2to2;
		if (y == 2)	return &m_sttButton_2to3;
		if (y == 3)	return &m_sttButton_2to4;
		if (y == 4)	return &m_sttButton_2to5;
		if (y == 5)	return &m_sttButton_2to6;
		if (y == 6)	return &m_sttButton_2to7;
		if (y == 7)	return &m_sttButton_2to8;
		if (y == 8)	return &m_sttButton_2to9;
		if (y == 9)	return &m_sttButton_2to10;
	}
	else if (x == 2)
	{
		if (y == 0)	return &m_sttButton_3to1;
		if (y == 1)	return &m_sttButton_3to2;
		if (y == 2)	return &m_sttButton_3to3;
		if (y == 3)	return &m_sttButton_3to4;
		if (y == 4)	return &m_sttButton_3to5;
		if (y == 5)	return &m_sttButton_3to6;
		if (y == 6)	return &m_sttButton_3to7;
		if (y == 7)	return &m_sttButton_3to8;
		if (y == 8)	return &m_sttButton_3to9;
		if (y == 9)	return &m_sttButton_3to10;
	}
	else if (x == 3)
	{
		if (y == 0)	return &m_sttButton_4to1;
		if (y == 1)	return &m_sttButton_4to2;
		if (y == 2)	return &m_sttButton_4to3;
		if (y == 3)	return &m_sttButton_4to4;
		if (y == 4)	return &m_sttButton_4to5;
		if (y == 5)	return &m_sttButton_4to6;
		if (y == 6)	return &m_sttButton_4to7;
		if (y == 7)	return &m_sttButton_4to8;
		if (y == 8)	return &m_sttButton_4to9;
		if (y == 9)	return &m_sttButton_4to10;
	}
	else if (x == 4)
	{
		if (y == 0)	return &m_sttButton_5to1;
		if (y == 1)	return &m_sttButton_5to2;
		if (y == 2)	return &m_sttButton_5to3;
		if (y == 3)	return &m_sttButton_5to4;
		if (y == 4)	return &m_sttButton_5to5;
		if (y == 5)	return &m_sttButton_5to6;
		if (y == 6)	return &m_sttButton_5to7;
		if (y == 7)	return &m_sttButton_5to8;
		if (y == 8)	return &m_sttButton_5to9;
		if (y == 9)	return &m_sttButton_5to10;
	}
	else if (x == 5)
	{
		if (y == 0)	return &m_sttButton_6to1;
		if (y == 1)	return &m_sttButton_6to2;
		if (y == 2)	return &m_sttButton_6to3;
		if (y == 3)	return &m_sttButton_6to4;
		if (y == 4)	return &m_sttButton_6to5;
		if (y == 5)	return &m_sttButton_6to6;
		if (y == 6)	return &m_sttButton_6to7;
		if (y == 7)	return &m_sttButton_6to8;
		if (y == 8)	return &m_sttButton_6to9;
		if (y == 9)	return &m_sttButton_6to10;
	}
	else if (x == 6)
	{
		if (y == 0)	return &m_sttButton_7to1;
		if (y == 1)	return &m_sttButton_7to2;
		if (y == 2)	return &m_sttButton_7to3;
		if (y == 3)	return &m_sttButton_7to4;
		if (y == 4)	return &m_sttButton_7to5;
		if (y == 5)	return &m_sttButton_7to6;
		if (y == 6)	return &m_sttButton_7to7;
		if (y == 7)	return &m_sttButton_7to8;
		if (y == 8)	return &m_sttButton_7to9;
		if (y == 9)	return &m_sttButton_7to10;
	}
	else if (x == 7)
	{
		if (y == 0)	return &m_sttButton_8to1;
		if (y == 1)	return &m_sttButton_8to2;
		if (y == 2)	return &m_sttButton_8to3;
		if (y == 3)	return &m_sttButton_8to4;
		if (y == 4)	return &m_sttButton_8to5;
		if (y == 5)	return &m_sttButton_8to6;
		if (y == 6)	return &m_sttButton_8to7;
		if (y == 7)	return &m_sttButton_8to8;
		if (y == 8)	return &m_sttButton_8to9;
		if (y == 9)	return &m_sttButton_8to10;
	}
	else if (x == 8)
	{
		if (y == 0)	return &m_sttButton_9to1;
		if (y == 1)	return &m_sttButton_9to2;
		if (y == 2)	return &m_sttButton_9to3;
		if (y == 3)	return &m_sttButton_9to4;
		if (y == 4)	return &m_sttButton_9to5;
		if (y == 5)	return &m_sttButton_9to6;
		if (y == 6)	return &m_sttButton_9to7;
		if (y == 7)	return &m_sttButton_9to8;
		if (y == 8)	return &m_sttButton_9to9;
		if (y == 9)	return &m_sttButton_9to10;
	}
	else if (x == 9)
	{
		if (y == 0)	return &m_sttButton_10to1;
		if (y == 1)	return &m_sttButton_10to2;
		if (y == 2)	return &m_sttButton_10to3;
		if (y == 3)	return &m_sttButton_10to4;
		if (y == 4)	return &m_sttButton_10to5;
		if (y == 5)	return &m_sttButton_10to6;
		if (y == 6)	return &m_sttButton_10to7;
		if (y == 7)	return &m_sttButton_10to8;
		if (y == 8)	return &m_sttButton_10to9;
		if (y == 9)	return &m_sttButton_10to10;
	}

	return &m_sttButton_1to1;
}

CString CDefectResult::Lf_getStaticButtonName(int x, int y, CString strValue)
{
	CStringArray arrString;
	CString sdata = _T(""), strRtnValue = _T("");

	if (strValue.GetLength() == 0)
		return _T("");

	int nPos = 0;
	while (1)
	{
		arrString.Add(strValue.Tokenize(_T(","), nPos));
		if (nPos == -1)	break;
	}

	for (int i = 0; i < arrString.GetCount()-4; i++)
	{
		sdata = arrString.GetAt(i);
		sdata.Delete(0, (sdata.Find(_T(">"))+1));
		strRtnValue.Append(sdata.Mid((sdata.Find(_T("-")) + 1)));
		strRtnValue.Append(_T("-"));
	}

	// 마지막 하이픈(-)은 삭제한다.
	strRtnValue.Delete((strRtnValue.GetLength() - 1), 1);

	return strRtnValue;
}

CString CDefectResult::Lf_getStaticReasonCode(int x, int y, CString strValue)
{
	CStringArray arrString;
	CString sdata = _T(""), strRtnValue = _T("");

	if (strValue.GetLength() == 0)
		return _T("");

	int nPos = 0;
	while (1)
	{
		arrString.Add(strValue.Tokenize(_T(","), nPos));
		if (nPos == -1)	break;
	}

	for (int i = 0; i < arrString.GetCount() - 4; i++)
	{
		sdata = arrString.GetAt(i);
		sdata.Delete(0, (sdata.Find(_T(">"))+1));
		strRtnValue.Append(sdata.Left(sdata.Find(_T("-"))));
		strRtnValue.Append(_T("-"));
	}

	// 마지막 하이픈(-)은 삭제한다.
	strRtnValue.Delete((strRtnValue.GetLength() - 1), 1);

	return strRtnValue;
}

long CDefectResult::Lf_getStaticButtonColor(int x, int y, CString strValue)
{
	CStringArray arrString;
	CString sdata = _T("");
	long longRtnValue;

	if (strValue.GetLength() == 0)
		return RGB(255, 255, 255);

	int nPos = 0;
	while (1)
	{
		arrString.Add(strValue.Tokenize(_T(","), nPos));
		if (nPos == -1)	break;
	}

	sdata = arrString.GetAt(arrString.GetCount() - 2);
	if (sdata.Left(1) != _T("$"))
		return RGB(255, 255, 255);

	sdata.Delete(0);
	longRtnValue = _tcstol(sdata, NULL, 16);

	return longRtnValue;
}
