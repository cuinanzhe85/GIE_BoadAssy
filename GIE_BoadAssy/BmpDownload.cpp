// BmpDownload.cpp: 구현 파일
//

#include "stdafx.h"
#include "GIE_BoadAssy.h"
#include "afxdialogex.h"
#include "BmpDownload.h"

#include "XImageInc/ximage.h"

#define SIZE_OF_1PIXEL				4				// R/G/B/Dummy 4Byte
#define NAMD_PAGE_SIZE				2048	

#define SEND_PAGE_SIZE				6//512(1MByte)				// 한번에 Send할 Nand Page수를 설정한다. (Min:1, Max:31)
#define SEND_PACKET_SIZE			4096


// CBmpDownload 대화 상자

IMPLEMENT_DYNAMIC(CBmpDownload, CDialog)

CBmpDownload::CBmpDownload(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_BMP_DOWNLOAD, pParent)
{

}

CBmpDownload::~CBmpDownload()
{
}

void CBmpDownload::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_BMP_DOWNLOAD, m_listBmpDownload);
	DDX_Control(pDX, IDC_LIST_BMP_TOTAL, m_listBmpTotal);
	DDX_Control(pDX, IDC_PROG_BMP_DOWNLOAD_STATUS, m_progBmpDownloadStatus);
	DDX_Control(pDX, IDC_STT_DOWNLOAD_STATUS, m_sttBmpMessage);
	DDX_Control(pDX, IDC_PICTURE_IMAGE, m_Image);
}


BEGIN_MESSAGE_MAP(CBmpDownload, CDialog)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_LBN_DBLCLK(IDC_LIST_BMP_TOTAL, &CBmpDownload::OnLbnDblclkListBmpTotal)
	ON_BN_CLICKED(IDC_BTN_BMP_DELETE, &CBmpDownload::OnBnClickedBtnBmpDelete)
	ON_BN_CLICKED(IDC_BTN_BMP_DOWNLOAD_START, &CBmpDownload::OnBnClickedBtnBmpDownloadStart)
	ON_LBN_SELCHANGE(IDC_LIST_BMP_TOTAL, &CBmpDownload::OnLbnSelchangeListBmpTotal)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_BMP_DOWNLOAD, &CBmpDownload::OnLvnItemchangedListBmpDownload)
END_MESSAGE_MAP()


// CBmpDownload 메시지 처리기


BOOL CBmpDownload::OnInitDialog()
{
	CDialog::OnInitDialog();
	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	lpModelInfo = m_pApp->GetModelInfo();
	lpWorkInfo = m_pApp->GetWorkInfo();

	Lf_InitItemFont();
	Lf_InitColorBrush();
	Lf_InitBmpList();
	Lf_InitListCtrlStyle();

	HICON hIcon;
	CButton* pBtn;
	hIcon = AfxGetApp()->LoadIconW(IDI_ICON_DELETE2);
	pBtn = (CButton*)GetDlgItem(IDC_BTN_BMP_DELETE);
	pBtn->SetIcon(hIcon);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


HBRUSH CBmpDownload::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
		if (pWnd->GetDlgCtrlID() == IDC_STT_BMP_TITLE)
		{
			pDC->SetBkColor(COLOR_DEEP_BLUE);
			pDC->SetTextColor(COLOR_WHITE);
			return m_brush[COLOR_IDX_DEEP_BLUE];
		}
		if (pWnd->GetDlgCtrlID() == IDC_STT_DOWNLOAD_STATUS)
		{
			CString str;
			m_sttBmpMessage.GetWindowTextW(str);
			if (str.Find(_T("Fail")) != -1)				pDC->SetTextColor(COLOR_RED);
			else if (str.Find(_T("Complete")) != -1)	pDC->SetTextColor(COLOR_GREEN);
			else	pDC->SetTextColor(COLOR_CYAN);
			pDC->SetBkColor(COLOR_GRAY64);
			
			return m_brush[COLOR_IDX_GRAY64];
		}
		if (pWnd->GetDlgCtrlID() == IDC_STT_BMP_STATUS_COUNT)
		{
			pDC->SetTextColor(COLOR_WHITE);
			pDC->SetBkColor(COLOR_GRAY64);

			return m_brush[COLOR_IDX_GRAY64];
		}
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void CBmpDownload::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialog::OnPaint()을(를) 호출하지 마십시오.
	CRect rect;

	GetClientRect(&rect);
	rect.bottom = 90;
	dc.FillSolidRect(rect, COLOR_DEEP_BLUE);

	GetClientRect(&rect);
	rect.top = 91;
	dc.FillSolidRect(rect, COLOR_YELLOW);

	GetClientRect(&rect);
	rect.top = 92;
	dc.FillSolidRect(rect, COLOR_GRAY64);
}


void CBmpDownload::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}
void CBmpDownload::Lf_InitItemFont()
{
	m_Font[0].CreateFont(15, 6, 0, 0, FW_SEMIBOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("System"));
	GetDlgItem(IDC_LIST_BMP_TOTAL)->SetFont(&m_Font[0]);
	GetDlgItem(IDC_LIST_BMP_DOWNLOAD)->SetFont(&m_Font[0]);
	GetDlgItem(IDC_STT_DOWNLOAD_STATUS)->SetFont(&m_Font[0]);

	m_Font[1].CreateFont(15, 8, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("System"));

	m_Font[2].CreateFont(15, 8, 0, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0, 0, 0, _T("System"));

	m_Font[3].CreateFont(34, 14, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("System"));

	m_Font[4].CreateFont(60, 26, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("System"));
	GetDlgItem(IDC_STT_BMP_TITLE)->SetFont(&m_Font[4]);

	m_Font[5].CreateFont(24, 11, 0, 0, FW_SEMIBOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("System"));
	GetDlgItem(IDC_BTN_BMP_DELETE)->SetFont(&m_Font[5]);
	GetDlgItem(IDC_BTN_BMP_DOWNLOAD_START)->SetFont(&m_Font[5]);
}
void CBmpDownload::Lf_InitColorBrush()
{
	m_brush[COLOR_IDX_RED].CreateSolidBrush(COLOR_RED);
	m_brush[COLOR_IDX_BLACK].CreateSolidBrush(COLOR_BLACK);
	m_brush[COLOR_IDX_ORANGE].CreateSolidBrush(COLOR_ORANGE);
	m_brush[COLOR_IDX_GRAY240].CreateSolidBrush(COLOR_GRAY240);
	m_brush[COLOR_IDX_GRAY64].CreateSolidBrush(COLOR_GRAY64);
	m_brush[COLOR_IDX_BLUISH].CreateSolidBrush(COLOR_BLUISH);
	m_brush[COLOR_IDX_GRAY224].CreateSolidBrush(COLOR_GRAY224);
	m_brush[COLOR_IDX_DEEP_BLUE].CreateSolidBrush(COLOR_DEEP_BLUE);
}
void CBmpDownload::Lf_InitBmpList()
{
	CString strfilename;
	WIN32_FIND_DATA wfd;
	HANDLE hSearch;

	CListBox* m_pList;
	m_pList = (CListBox*)GetDlgItem(IDC_LIST_BMP_TOTAL);

	hSearch = FindFirstFile(_T(".\\Pattern\\BMP\\*.bmp"), &wfd);

	if (hSearch != INVALID_HANDLE_VALUE)
	{
		if (wfd.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
		{
			strfilename.Format(_T("%s"), wfd.cFileName);
			strfilename = strfilename.Mid(0, strfilename.GetLength() - 4);
			strfilename.MakeUpper();
			m_pList->AddString(strfilename);
		}
		while (FindNextFile(hSearch, &wfd))
		{
			if (wfd.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
			{
				strfilename.Format(_T("%s"), wfd.cFileName);
				strfilename = strfilename.Mid(0, strfilename.GetLength() - 4);
				strfilename.MakeUpper();
				m_pList->AddString(strfilename);
			}
		}
		FindClose(hSearch);
	}
}
void CBmpDownload::Lf_InitListCtrlStyle()
{
	m_listBmpDownload.InsertColumn(0, _T("NO"), LVCFMT_CENTER, -1, -1);
	m_listBmpDownload.SetColumnWidth(0, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER); // NO
	m_listBmpDownload.SetColumnWidth(0, 30);

	m_listBmpDownload.InsertColumn(1, _T("BMP NAME"), LVCFMT_CENTER, -1, -1);
	m_listBmpDownload.SetColumnWidth(1, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER); // BMP Name
	m_listBmpDownload.SetColumnWidth(1, 200);

	DWORD dwStype = m_listBmpDownload.GetExtendedStyle();
	dwStype |= LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
	m_listBmpDownload.SetExtendedStyle(dwStype);
}
void CBmpDownload::OnLbnSelchangeListBmpTotal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRect rc;
	GetDlgItem(IDC_STT_IMAGE_DISPLAY)->GetWindowRect(rc);
	ScreenToClient(rc);
	rc.right -= 10;
	rc.bottom -= 20;
	CString sName, sPath;
	m_listBmpTotal.GetText(m_listBmpTotal.GetCurSel(), sName);
	sPath.Format(_T(".\\Pattern\\BMP\\%s.bmp"), sName);
	HBITMAP hBitmap = (HBITMAP)LoadImage(AfxGetInstanceHandle(), sPath, IMAGE_BITMAP, rc.Width(), rc.Height(), LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_Image.SetBitmap(hBitmap);
	Invalidate(FALSE);
}


void CBmpDownload::OnLvnItemchangedListBmpDownload(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	NM_LISTVIEW* pNMView = (NM_LISTVIEW*)pNMHDR;
	int index = pNMView->iItem;

	CRect rc;
	GetDlgItem(IDC_STT_IMAGE_DISPLAY)->GetWindowRect(rc);
	ScreenToClient(rc);
	rc.right -= 10;
	rc.bottom -= 20;
	CString sName, sPath;
	sName = m_listBmpDownload.GetItemText(index, 1);

	sPath.Format(_T(".\\Pattern\\BMP\\%s.bmp"), sName);
	HBITMAP hBitmap = (HBITMAP)LoadImage(AfxGetInstanceHandle(), sPath, IMAGE_BITMAP, rc.Width(), rc.Height(), LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_Image.SetBitmap(hBitmap);
	Invalidate(FALSE);

	*pResult = 0;
}

void CBmpDownload::OnLbnDblclkListBmpTotal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_listBmpTotal.GetCurSel() == -1)
		return;

	CString strBmpName;
	m_listBmpTotal.GetText(m_listBmpTotal.GetCurSel(), strBmpName);

	int nbmpcount = m_listBmpDownload.GetItemCount();
	for (int i = 0; i < nbmpcount; i++)
	{
		if (m_listBmpDownload.GetItemText(i, 1) == strBmpName)
		{
			return;
		}
	}
	CString strNomber;
	strNomber.Format(_T("%d"), nbmpcount + 1);
	m_listBmpDownload.InsertItem(nbmpcount, strNomber);
	m_listBmpDownload.SetItemText(nbmpcount, 1, strBmpName);

	m_listBmpDownload.SetSelectionMark(nbmpcount + 1); // Item Select & Focus
	m_listBmpDownload.SetItemState(nbmpcount + 1, LVIS_SELECTED | LVIS_FOCUSED, LVNI_SELECTED | LVNI_FOCUSED);
	m_listBmpDownload.SetFocus();
}



void CBmpDownload::OnBnClickedBtnBmpDelete()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	POSITION pSelectItemPos = m_listBmpDownload.GetFirstSelectedItemPosition();
	int nItemPosition = m_listBmpDownload.GetNextSelectedItem(pSelectItemPos);

	if (nItemPosition < 0)
	{
		return;
	}

	m_listBmpDownload.DeleteItem(nItemPosition);

	if (!m_listBmpDownload.GetItemCount())
	{
		return;
	}
	else
	{
		if (m_listBmpDownload.GetItemCount() <= nItemPosition)
			nItemPosition--;

		m_listBmpDownload.SetSelectionMark(nItemPosition); // Item Select & Focus
		m_listBmpDownload.SetItemState(nItemPosition, LVIS_SELECTED | LVIS_FOCUSED, LVNI_SELECTED | LVNI_FOCUSED);
		m_listBmpDownload.SetFocus();
	}

	CString tstr;


	for (int i = 0; i < m_listBmpDownload.GetItemCount(); i++)
	{
		tstr.Format(_T("%d"), i + 1);
		m_listBmpDownload.SetItem(i, 0, LVIF_TEXT, tstr, 0, LVIF_STATE, 0, 0);
	}
}


void CBmpDownload::OnBnClickedBtnBmpDownloadStart()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_sttBmpMessage.SetWindowTextW(_T("Ready"));
	int nTotalCount = m_listBmpDownload.GetItemCount();
	
	BMPDOWNINFO		pBmpInfo;
	BITMAPFILEHEADER bmpHeader;
	int nHorResol, nVerResol;

	nHorResol = lpModelInfo->m_nTimingHorActive;
	nVerResol = lpModelInfo->m_nTimingVerActive;

	CxImage* m_pImage;
	m_pImage = new CxImage();
	
	for (int index = 0; index < nTotalCount; index++)
	{
		CString sfilename, status;
		sfilename = m_listBmpDownload.GetItemText(index, 1);

		m_listBmpDownload.SetSelectionMark(index); // Item Select & Focus
		m_listBmpDownload.SetItemState(index, LVIS_SELECTED | LVIS_FOCUSED, LVNI_SELECTED | LVNI_FOCUSED);
		m_listBmpDownload.SetFocus();

		status.Format(_T("(%d/%d)"), index + 1, nTotalCount);
		GetDlgItem(IDC_STT_BMP_STATUS_COUNT)->SetWindowTextW(status);

		sfilename.Append(_T(".bmp"));
		sfilename.MakeUpper();
		CString resizefilepath, filepath;
		filepath.Format(_T(".\\Pattern\\BMP\\%s"), sfilename);

		////////////////////////////////////////////////////////////////
		// BMP를 해상도에 맞춰 사이즈 변경하고 새 파일로 저장한다.
		DeleteFile(resizefilepath);	// 동일한 파일이 있으면 삭제한다.

		resizefilepath.Format(_T(".\\Pattern\\BMP\\%s_%d_%d.~bmp"), sfilename, nHorResol, nVerResol);
		
		m_pImage->Load(filepath, CXIMAGE_FORMAT_BMP);
		m_pImage->Resample(nHorResol, nVerResol);
		m_pImage->Save(resizefilepath, CXIMAGE_FORMAT_BMP);
		m_pImage->Destroy();

		// BMP File을 Read하여 Size를 가져온다.
		HANDLE fd = CreateFile(resizefilepath, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (fd < 0)
		{
			continue;
		}
		DWORD len;
		ReadFile(fd, (LPSTR)&bmpHeader, sizeof(bmpHeader), &len, NULL);
		CloseHandle(fd);

		// BMP Download에 필요한 구제체 정보를 저장한다.
		pBmpInfo.m_nBmpIndex = index;

		pBmpInfo.m_sBmpFileName = sfilename;
		pBmpInfo.m_sBmpFilePath = resizefilepath;
		pBmpInfo.m_nBmpFileSize = bmpHeader.bfSize;

		pBmpInfo.m_nLcmHActive = nHorResol;
		pBmpInfo.m_nLcmVActive = nVerResol;

		pBmpInfo.m_pProgress = &m_progBmpDownloadStatus;
		pBmpInfo.m_pSttMessage = &m_sttBmpMessage;

		if (Lf_startDownloadBMP(&pBmpInfo) == FALSE)
		{
			DeleteFile(resizefilepath);
			m_sttBmpMessage.SetWindowTextW(_T("BMP Download Fail"));
			DeleteFile(resizefilepath);
			return;
		}
		DeleteFile(resizefilepath);
	}
	m_sttBmpMessage.SetWindowTextW(_T("BMP Download Complete"));
}

BOOL CBmpDownload::Lf_startDownloadBMP(LPBMPDOWNINFO pBmpInfo)
{
	if (Lf_sendBmpHeadData(pBmpInfo) == FALSE)
	{
		return FALSE;
	}

	if (Lf_sendBmpRawData(pBmpInfo) == FALSE)
	{
		return FALSE;
	}

	if (Lf_getDoneCheck() == FALSE)
	{
		return FALSE;
	}

	return TRUE;
}
BOOL CBmpDownload::Lf_sendBmpHeadData(LPBMPDOWNINFO pBmpInfo)
{
	BOOL bRet = FALSE;
	CString sPacket;
	char szName[256] = { 0, };
	char szPacket[2048] = { 0, };
	int nNameLen, nPacketLen;

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 0. BMP File NAME의 길이를 구한다.(한글/UNICODE 대응을 위하여char로 변환하여 길이를구한다.)
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// File Name이 255보다 크면 255까지 자른다.
	if (pBmpInfo->m_sBmpFileName.GetLength() >= 255)
	{
		pBmpInfo->m_sBmpFileName = pBmpInfo->m_sBmpFileName.Left(255);
	}

	wchar_To_char(pBmpInfo->m_sBmpFileName.GetBuffer(0), szName);
	nNameLen = (int)strlen(szName);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 1. BMP File NAME을 먼저 전송한다.
	sprintf_s(szPacket, "%02d%04d%04d%03d%s", pBmpInfo->m_nBmpIndex, pBmpInfo->m_nLcmHActive, pBmpInfo->m_nLcmVActive, nNameLen, szName);
	nPacketLen = (int)strlen(szPacket);

	bRet = m_pApp->udp_sendPacket(UDP_MAIN_IP, TARGET_CTRL, CMD_BMP_DOWNLOAD_PTN_INFO, nPacketLen, szPacket, TRUE, 2000);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////

	return bRet;
}
BOOL CBmpDownload::Lf_sendBmpRawData(LPBMPDOWNINFO pBmpInfo)
{
	CString sdata;
	int m_status;

	BYTE tempStr[4096 * 3] = { 0, };
	char sPacket[1024 * 8] = { 0, };
	char stemp[20] = { 0, };

	BITMAPFILEHEADER bmpHeader;
	LPBITMAPINFO pBitmapInfo;
	LPSTR tDib = NULL;
	LPSTR pRaw = NULL;

	BOOL ret = TRUE;
	int	WidthRead, WidthCell, HeightCell;
	int LineNo = 0, nandWriteAddr = 0;
	int bmpIndex;
	DWORD size, len;

	HANDLE fd = CreateFile(pBmpInfo->m_sBmpFilePath, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (fd < 0)
	{
		AfxMessageBox(_T("File HANDLE Create Error."));
		CloseHandle(fd);
		return FALSE;
	}

	if (!ReadFile(fd, (LPSTR)&bmpHeader, sizeof(bmpHeader), &len, NULL))
	{
		AfxMessageBox(_T("File Read Error."));
		CloseHandle(fd);
		return FALSE;
	}

	size = bmpHeader.bfSize - sizeof(bmpHeader);
	tDib = new char[size];
	pRaw = new char[size * 2];	// Dummy Pixel을 넣어야 하므로 실제 Size보다 크게 Buff를 잡는다.
	if (!ReadFile(fd, tDib, size, &len, NULL))
	{
		CloseHandle(fd);
		return FALSE;
	}
	CloseHandle(fd);

	pBitmapInfo = (LPBITMAPINFO)tDib;

	WidthCell = pBitmapInfo->bmiHeader.biWidth * 3;
	HeightCell = pBitmapInfo->bmiHeader.biHeight;
	WidthRead = WidthCell;

	if (WidthCell % 4 != 0)
		WidthRead += 4 - (WidthCell % 4);

	bmpIndex = pBmpInfo->m_nBmpIndex;

	if (pBmpInfo->m_pProgress != NULL)
	{
		pBmpInfo->m_pProgress->SetPos(0);
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 1. BMP 이미지를 반전하고 RGB의 순서를 변경한다.
	int iptr = 0, iptr_width = 0, hor = 0;

	iptr_width = (pBitmapInfo->bmiHeader.biWidth * SIZE_OF_1PIXEL);

	// point offset의 값을 256배수로 맞춘다.
	while (1)
	{
		if ((iptr_width % 512) == 0)
			break;
		iptr_width++;
	}

	for (LineNo = 0; LineNo < pBitmapInfo->bmiHeader.biHeight; LineNo++)
	{
		// 1Line의 Pixel Data를 가져온다.(40은 BMP Header의 사이즈다.)
		memset(tempStr, 0, sizeof(tempStr));
		memcpy(tempStr, tDib + (WidthRead * (pBitmapInfo->bmiHeader.biHeight - 1 - LineNo)) + 40, WidthRead);
		iptr = (LineNo * iptr_width);

		// BGR 순서를 RGB로 변경하고 Pixel Dummy를 추가한다.
		for (hor = 0; hor < iptr_width; hor++)
		{
			pRaw[iptr + (hor * SIZE_OF_1PIXEL) + 1] = tempStr[(hor * 3) + 0];	// BGR to RGB : R
			pRaw[iptr + (hor * SIZE_OF_1PIXEL) + 0] = tempStr[(hor * 3) + 1];	// BGR to RGB : G
			pRaw[iptr + (hor * SIZE_OF_1PIXEL) + 3] = tempStr[(hor * 3) + 2];	// BGR to RGB : B
			pRaw[iptr + (hor * SIZE_OF_1PIXEL) + 2] = NULL;
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 2. BMP File RAW Data를 전송한다.f
	while (1)
	{
		// BMP write Packet 을 만든다.
		sprintf_s(stemp, "%02d%08X", bmpIndex, nandWriteAddr);			// BMP Index, NAND flash write address
		sPacket[0] = stemp[0];
		sPacket[1] = stemp[1];
		sPacket[2] = stemp[2];
		sPacket[3] = stemp[3];
		sPacket[4] = stemp[4];
		sPacket[5] = stemp[5];
		sPacket[6] = stemp[6];
		sPacket[7] = stemp[7];
		sPacket[8] = stemp[8];
		sPacket[9] = stemp[9];

		size = SEND_PACKET_SIZE;

		// Packet size만큼 Data를 전송한다.
		// +10은 Packet Head부분이다.
		memcpy(&sPacket[10], &pRaw[nandWriteAddr], size);
		size = size + (DWORD)strlen(stemp);
		if (m_pApp->udp_sendPacket(UDP_MAIN_IP, TARGET_CTRL, CMD_BMP_DOWNLOAD_RAW_DATA, size, sPacket,TRUE,2000) == FALSE)
		{
			ret = FALSE;
			break;
		}

		// 다음에 Write할 NAND Address를 증가시킨다.
		nandWriteAddr += SEND_PACKET_SIZE;

		// Packet buff를 Clear한다.
		ZeroMemory(sPacket, sizeof(sPacket));
		ZeroMemory(stemp, sizeof(stemp));

		// Progress Bar를 업데이트한다.
		m_status = (nandWriteAddr * 100) / (iptr_width * pBitmapInfo->bmiHeader.biHeight);
		if (pBmpInfo->m_pProgress != NULL)
			pBmpInfo->m_pProgress->SetPos(m_status);

		CString status;
		status.Format(_T("BMP Download ... (%d%%)"), m_status);
		pBmpInfo->m_pSttMessage->SetWindowTextW(status);
		// 모든 Data를 전송했으면 Packet 전송을 종료한다.
		if (nandWriteAddr >= (iptr_width * pBitmapInfo->bmiHeader.biHeight))
			break;

		//	ProcessMessage();
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 3. Progress
	if (pBmpInfo->m_pProgress != NULL)
	{
		pBmpInfo->m_pProgress->SetPos(100);
		pBmpInfo->m_pProgress = NULL;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 4. Release
	if (tDib)	delete tDib;
	if (pRaw)	delete pRaw;

	return ret;
}

BOOL CBmpDownload::Lf_getDoneCheck()
{
	int ma = 0, cnt = 0;

	lpWorkInfo->m_bBmpDoneCheck = FALSE;

	m_pApp->udp_sendPacket(UDP_MAIN_IP, TARGET_CTRL, CMD_BMP_DOWNLOAD_DONE_CHECK, NULL, "");

	if (lpWorkInfo->m_bBmpDoneCheck == TRUE)
		return TRUE;
	else
		return FALSE;
}