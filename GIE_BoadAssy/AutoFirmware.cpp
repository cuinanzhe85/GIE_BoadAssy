// AutoFirmware.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "GIE_BoadAssy.h"
#include "AutoFirmware.h"


// CAutoFirmware ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CAutoFirmware, CDialog)

CAutoFirmware::CAutoFirmware(CWnd* pParent /*=NULL*/)
	: CDialog(CAutoFirmware::IDD, pParent)
{

}

CAutoFirmware::~CAutoFirmware()
{
}

void CAutoFirmware::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS_DOWNLOAD, m_progDownload);
	DDX_Control(pDX, IDC_CMB_TARGET_SELECT, m_cboTargetSel);
}


BEGIN_MESSAGE_MAP(CAutoFirmware, CDialog)
	ON_WM_DESTROY()
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_FILE_SELECT, &CAutoFirmware::OnBnClickedBtnFileSelect)
	ON_BN_CLICKED(IDC_BTN_FW_VERSION, &CAutoFirmware::OnBnClickedBtnFwVersion)
	ON_BN_CLICKED(IDC_BTN_DOWNLOAD, &CAutoFirmware::OnBnClickedBtnDownload)
END_MESSAGE_MAP()


// CAutoFirmware �޽��� ó�����Դϴ�.

BOOL CAutoFirmware::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	lpWorkInfo		= m_pApp->GetWorkInfo();

	Lf_initFontSet();
	Lf_initVariable();

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CAutoFirmware::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}

HBRUSH CAutoFirmware::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
		if(pWnd->GetDlgCtrlID()==IDC_STT_AUTOFWDLG_TIT)
		{
			pDC->SetBkColor(COLOR_DEEP_BLUE);
			pDC->SetTextColor(COLOR_WHITE);
			return m_Brush[COLOR_IDX_DEEP_BLUE];
		}
		if (pWnd->GetDlgCtrlID() == IDC_STT_FILE_PATH
			|| pWnd->GetDlgCtrlID() == IDC_STT_FW_VERSION)
		{
			pDC->SetBkColor(COLOR_WHITE);
			pDC->SetTextColor(COLOR_BLACK);
			return m_Brush[COLOR_IDX_WHITE];
		}
		if (pWnd->GetDlgCtrlID() == IDC_STT_FW_STATUS)
		{
			pDC->SetBkColor(COLOR_GRAY64);
			pDC->SetTextColor(COLOR_CYAN);
			return m_Brush[COLOR_IDX_GRAY64];
		}
		if (pWnd->GetDlgCtrlID() == IDC_STT_TARGET_SEL)
		{
			pDC->SetBkColor(COLOR_BLUISH);
			pDC->SetTextColor(COLOR_WHITE);
			return m_Brush[COLOR_IDX_BLUISH];
		}
		break;
	}
	// TODO:  �⺻���� �������� ������ �ٸ� �귯�ø� ��ȯ�մϴ�.
	return hbr;
}

void CAutoFirmware::OnPaint()
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
	dc.FillSolidRect(rect, COLOR_GRAY64);
}

void CAutoFirmware::Lf_initFontSet()
{
	/*************************************************************************************************/
	// Font Set
	m_Font[0].CreateFont(24, 11, 0, 0, FW_SEMIBOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("Segoe UI Symbol"));		
	GetDlgItem(IDC_STT_FILE_PATH)->SetFont(&m_Font[0]);
	GetDlgItem(IDC_STT_FW_VERSION)->SetFont(&m_Font[0]);
	GetDlgItem(IDC_STT_FW_STATUS)->SetFont(&m_Font[0]);
	GetDlgItem(IDC_BTN_FILE_SELECT)->SetFont(&m_Font[0]);
	GetDlgItem(IDC_BTN_FW_VERSION)->SetFont(&m_Font[0]);
	GetDlgItem(IDC_BTN_DOWNLOAD)->SetFont(&m_Font[0]);
	GetDlgItem(IDC_STT_TARGET_SEL)->SetFont(&m_Font[0]);	
	GetDlgItem(IDC_CMB_TARGET_SELECT)->SetFont(&m_Font[0]);

	m_Font[1].CreateFont(15, 8, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("Segoe UI Symbol"));

	m_Font[2].CreateFont(42, 20, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("Segoe UI Symbol"));
	

	m_Font[3].CreateFont(34, 14, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("Segoe UI Symbol"));
	GetDlgItem(IDCANCEL)->SetFont(&m_Font[3]);	

	m_Font[4].CreateFont(60, 26, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("Segoe UI Symbol"));
	GetDlgItem(IDC_STT_AUTOFWDLG_TIT)->SetFont(&m_Font[4]);

	m_Font[5].CreateFont(150, 70, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("ARIAL"));

	/*************************************************************************************************/
	// Brush Set
	m_Brush[COLOR_IDX_ORANGE].CreateSolidBrush (COLOR_ORANGE);
	m_Brush[COLOR_IDX_RED].CreateSolidBrush (COLOR_RED);
	m_Brush[COLOR_IDX_GRAY64].CreateSolidBrush (COLOR_GRAY64);
	m_Brush[COLOR_IDX_GRAY94].CreateSolidBrush (COLOR_GRAY94);
	m_Brush[COLOR_IDX_LIGHT_GREEN].CreateSolidBrush (COLOR_LIGHT_GREEN);
	m_Brush[COLOR_IDX_WHITE].CreateSolidBrush (COLOR_WHITE);
	m_Brush[COLOR_IDX_DEEP_BLUE].CreateSolidBrush (COLOR_DEEP_BLUE);
	m_Brush[COLOR_IDX_CYAN].CreateSolidBrush(COLOR_CYAN);
	m_Brush[COLOR_IDX_BLUISH].CreateSolidBrush(COLOR_BLUISH);
}

void CAutoFirmware::Lf_initVariable()
{
	m_pApp->m_nDownloadReadyAckCount	= 0;						//Firmware Download ACK Receive Count �ʱ�ȭ.	
	m_nFirmwareDataLen					= 0;						//Firmware File Length �ʱ�ȭ
	m_pFirmwareData						= new BYTE [MAX_FILE_SIZE];	//Firmware File Buff Memory 1M �Ҵ�.
	ZeroMemory(m_pFirmwareData, MAX_FILE_SIZE);						//Buff Memory �ʱ�ȭ

	m_cboTargetSel.SetCurSel(0);

	GetDlgItem(IDC_STT_FW_STATUS)->SetWindowText(_T("Ready"));		
}

void CAutoFirmware::Lf_loadFirmwareFile()
{
	CString m_sFirmwarePath;
	TCHAR szFilePath[1024]={0,};

	GetCurrentDirectory(sizeof(szFilePath), szFilePath);

	CFileDialog m_ldFile( TRUE, _T("hex|*"), NULL, OFN_READONLY, _T("Intel Hex File(*.hex)|*.hex|All File(*.*)|*.*|") );

	if( m_ldFile.DoModal() == IDOK ) 
	{
		m_sFirmwarePath = m_ldFile.GetPathName();

		GetDlgItem(IDC_STT_FILE_PATH)->SetWindowText(m_sFirmwarePath);
		Lf_readFirmwareFile(m_sFirmwarePath);
	}
	SetCurrentDirectory(szFilePath);
}

void CAutoFirmware::Lf_readFirmwareFile(CString strFilePath)
{
	CStdioFile* pFile;
	pFile = new CStdioFile();

	// File�� Open�Ѵ�.
	if(pFile->Open(strFilePath, CStdioFile::modeRead | CStdioFile::typeText)==NULL)
	{
		AfxMessageBox(_T("File Open Fail !!!"), MB_OK | MB_ICONERROR);
		delete pFile;
		return;
	}

	// Firmware Data�� ������ Buff �Ҵ��ϰ� �ʱ�ȭ �Ѵ�.
	unsigned long filesize;
	filesize =(unsigned long) pFile->GetLength();
	szParsingData = (unsigned char *)malloc(filesize*sizeof(unsigned char));
	memset((char*)szParsingData, 0, filesize);

	// Firmware Data�� ������ Buff�� �ʱ�ȭ �Ѵ�.
	m_nFirmwareDataLen	= 0;								//Firmware File Length �ʱ�ȭ

	// Line�� Null�϶����� �д´�.
	CString lineString;
	CString recStart, recData;
	int recLength, recOffset, recType, recChksum;
	while(pFile->ReadString(lineString)==TRUE)
	{
		recStart	= lineString.Left(1);
		recChksum	= _tcstol(lineString.Right(2),  NULL, 16);

		// ���ڵ��� ���۹���(:)�� Ȯ���Ѵ�.
		if(recStart == ":")
		{
			recLength	= _tcstol(lineString.Mid(1, 2), NULL, 16);
			recOffset	= _tcstol(lineString.Mid(3, 4), NULL, 16);
			recType		= _tcstol(lineString.Mid(7, 2), NULL, 16);
			recData		= lineString.Mid(9, (recLength*2));

			//00 - Data record 
			//01 - End of file record 
			//02 - Extended segment address record 
			//03 - Start segment address record 
			//04 - Extended linear address record 
			//05 - Start linear address record 
			if(recType == 0x01)
			{	// ������ ���̹Ƿ� ����.
				break;
			}
			else if((recType == 0x02) || (recType == 0x04))
			{	// Address Record�� Data�� �������� �ʴ´�.
			}
			else
			{	// Data Record�� Parsing�Ѵ�.
				Lf_parseDataRecord(recData, &szParsingData[m_nFirmwareDataLen]);
				m_nFirmwareDataLen += recLength;
			}
		}
		else
		{
			AfxMessageBox(_T("Not the Intel hex file type."), MB_OK | MB_ICONERROR);
			// Data Buff Memory�� �ʱ�ȭ �Ѵ�.
			memset((char*)szParsingData, 0, filesize);
			// Data Length�� �ʱ�ȭ �Ѵ�.
			m_nFirmwareDataLen = 0;
		}
	}

	// File�� �ݴ´�.
	pFile->Close();
	delete pFile;
}

void CAutoFirmware::Lf_parseDataRecord(CString strRecord, BYTE* pData)
{
	int nLen=0;
	int point=0;

	nLen = strRecord.GetLength() / 2;
	for(int i=0; i<nLen; i++)
	{
		*pData = (BYTE)_tcstol(strRecord.Mid(point, 2), NULL, 16);

		point += 2;
		pData++;
	}
}

void CAutoFirmware::Lf_readyInitialize()
{
	m_pApp->m_nDownloadReadyAckCount	= 0;				//Firmware Download ACK Receive Count �ʱ�ȭ.
	//	m_bAckReceived						= FALSE;
	//	m_nAckCommand						= 0x00;
}

BOOL CAutoFirmware::Lf_checkDownloadReady()
{
	DWORD sTick, eTick;

	GetDlgItem(IDC_STT_FW_STATUS)->SetWindowText(_T("Go To Boot Section!"));
	sTick = ::GetTickCount();
	while(1)
	{
		m_pApp->m_nDownloadCountUp=TRUE;
		m_pApp->m_pCommand->Gf_setGoToBootSection();
		Sleep(100);

		if(m_pApp->m_nDownloadReadyAckCount > 10)
		{
			return TRUE;
		}

		eTick = ::GetTickCount();
		if((eTick - sTick) > 30000)
			break;

		ProcessMessage();
	}

	return FALSE;
}

BOOL CAutoFirmware::Lf_sendFirmwareFile()
{
	BOOL bRet=FALSE;
	int startAddr = 0;
	int packetLen = 0;
	char szpacket[4096]={0,};
	CString strpacket=_T("");
	int nsize=0;

	int nProg, nLoop=0;
	int nsendPageCnt=0;
	int nRemainPageCnt =0;
	char szTempBuf[4096];

	nsendPageCnt = m_nFirmwareDataLen / FLASH_PAGE_SIZE;
	nRemainPageCnt = m_nFirmwareDataLen % FLASH_PAGE_SIZE;

	GetDlgItem(IDC_STT_FW_STATUS)->SetWindowText(_T("File Downloading!"));

	for (nLoop=0; nLoop<nsendPageCnt; nLoop++)
	{
		memset((char*)szTempBuf, 0 , sizeof(szTempBuf));

		startAddr=nLoop*FLASH_PAGE_SIZE;
		sprintf_s(szTempBuf, "%05X", startAddr);

		packetLen= (int)strlen(szTempBuf);

		memcpy((char*)(&szTempBuf[packetLen]),(char*)(szParsingData+(nLoop*FLASH_PAGE_SIZE)), FLASH_PAGE_SIZE);		
		
		bRet = m_pApp->udp_sendPacket(UDP_MAIN_IP, TARGET_CTRL, CMD_CTRL_FW_DOWNLOAD, (packetLen + FLASH_PAGE_SIZE), (char*)szTempBuf);

		nProg= (startAddr*100)/m_nFirmwareDataLen;
		m_progDownload.SetPos(nProg);
		CString strPro;
		strPro.Format(_T("%d%%"),nProg);
		m_progDownload.SetWindowText(strPro);

		if (bRet == FALSE)
		{
			free(szParsingData);
			return FALSE;
		}

		ProcessMessage();
	}
	if (nRemainPageCnt != 0)
	{
		memset((char*)szTempBuf, 0 , sizeof(szTempBuf));

		startAddr=nLoop*FLASH_PAGE_SIZE;
		sprintf_s(szTempBuf, "%05X", startAddr);

		packetLen= (int)strlen(szTempBuf);

		memcpy((char*)(&szTempBuf[packetLen]),(char*)(szParsingData+(nLoop*FLASH_PAGE_SIZE)), FLASH_PAGE_SIZE);

		bRet = m_pApp->udp_sendPacket(UDP_MAIN_IP, TARGET_CTRL, CMD_CTRL_FW_DOWNLOAD, (packetLen + FLASH_PAGE_SIZE), (char*)szTempBuf);

		nProg= (startAddr*100)/m_nFirmwareDataLen;
		m_progDownload.SetPos(nProg);		

		if (bRet == FALSE)
		{
			free(szParsingData);
			return FALSE;
		}
	}

	free(szParsingData);
	return TRUE;
}

BOOL CAutoFirmware::Lf_sendDownloadComplete()
{
	return m_pApp->udp_sendPacket(UDP_MAIN_IP, TARGET_CTRL, CMD_CTRL_FW_COMPLETE, 0, NULL);
}

BOOL CAutoFirmware::Lf_firmwareDownloadStart()
{
	m_progDownload.SetPos(0);

	// Step1. Download Ready Check
	if(Lf_checkDownloadReady()==FALSE)
	{
		AfxMessageBox(_T("xxx   Firmware Download Fail - Ready Check   xxx"));
		goto ERR_EXCEPT;
	}

	// Step2. Download Start
	Sleep(100);
	if(Lf_sendFirmwareFile()==FALSE)
	{
		AfxMessageBox(_T("xxx   Firmware Download Fail - Data Download   xxx"));
		goto ERR_EXCEPT;
	}

	// Step3. Download Complete Check
	Sleep(100);
	if(Lf_sendDownloadComplete()==FALSE)
	{
		AfxMessageBox(_T("xxx   Firmware Download Fail - Complete Check  xxx"));
		goto ERR_EXCEPT;
	}
	GetDlgItem(IDC_STT_FW_STATUS)->SetWindowText(_T("Firmware Download Complete!"));

	// Step4. Download Initialize & Ready
	Lf_readyInitialize();

	m_progDownload.SetPos(100);

	return TRUE;

ERR_EXCEPT:
	// Error Exception. Initialize.
	Lf_readyInitialize();
	GetDlgItem(IDC_STT_FW_STATUS)->SetWindowText(_T(""));

	return FALSE;
}

void CAutoFirmware::OnBnClickedBtnFileSelect()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	Lf_loadFirmwareFile();
}

void CAutoFirmware::OnBnClickedBtnFwVersion()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	lpWorkInfo->m_sFirmwareVersion.Empty();
	GetDlgItem(IDC_STT_FW_VERSION)->SetWindowText(_T(""));
	if(m_cboTargetSel.GetCurSel()==0)
	{
		if(m_pApp->m_pCommand->Gf_getFirmwareVersion() == TRUE)
		{
			GetDlgItem(IDC_STT_FW_VERSION)->SetWindowText(lpWorkInfo->m_sFirmwareVersion);		
		}
		else
		{
			GetDlgItem(IDC_STT_FW_VERSION)->SetWindowText(_T("Fail"));	
		}
	}
	else
	{
		if(m_pApp->m_pCommand->Gf_serGfd250FirmwareVersion() == TRUE)
		{
			GetDlgItem(IDC_STT_FW_VERSION)->SetWindowText(lpWorkInfo->m_sFirmwareVersion);		
		}
		else
		{
			GetDlgItem(IDC_STT_FW_VERSION)->SetWindowText(_T("Fail"));	
		}		
	}
}

void CAutoFirmware::OnBnClickedBtnDownload()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	GetDlgItem(IDC_BTN_FILE_SELECT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_FW_VERSION)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_DOWNLOAD)->EnableWindow(FALSE);
	GetDlgItem(IDCANCEL)->EnableWindow(FALSE);

	Lf_firmwareDownloadStart();

	GetDlgItem(IDC_BTN_FILE_SELECT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_FW_VERSION)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_DOWNLOAD)->EnableWindow(TRUE);
	GetDlgItem(IDCANCEL)->EnableWindow(TRUE);
}
