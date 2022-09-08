#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CAutoFirmware 대화 상자입니다.
#define MAX_FILE_SIZE		1024*1024		// 최대 1M Buff 할당.
#define MAX_DATASIZE 400000 //FW File에서 읽을 수있는 최대 크기
#define FLASH_PAGE_SIZE		1024

#define	SIZE_OF_EPCQ16A				(32*1024*1024)	// 2MByte
#define SIZE_OF_WRITE_PACKET		1024			// raw data write packet size
#define SIZE_OF_READ_PACKET			512				// raw data read packet size
#define EPCQ16A_BYTE_PER_PAGE		256				// 256byte write per page
#define EPCQ16A_PAGE_WR_DELAY		3				// page write time (max 3ms)
#define EPCQ16A_CHIP_ERASE_DELAY	25000			// chip erase time (typ. 5sec, max 25sec)

class CAutoFirmware : public CDialog
{
	DECLARE_DYNAMIC(CAutoFirmware)

public:
	CAutoFirmware(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CAutoFirmware();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_AUTO_FIRMWARE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	afx_msg void OnBnClickedBtnFileSelect();
	afx_msg void OnBnClickedBtnFwVersion();
	afx_msg void OnBnClickedBtnDownload();

protected:
	void Lf_initFontSet();
	void Lf_initVariable();
	void Lf_loadFirmwareFile();
	void Lf_readFirmwareFile(CString strFilePath);
	void Lf_parseDataRecord(CString strRecord, BYTE* pData);
	void Lf_readyInitialize();
	BOOL Lf_checkDownloadReady();
	BOOL Lf_sendFirmwareFile();
	BOOL Lf_sendDownloadComplete();
	BOOL Lf_firmwareDownloadStart();

	void Lf_loadFpgaFile();
	void Lf_readFpgaFile(CString strFilePath);
	BOOL Lf_FpgaDownloadStart();
	BOOL Lf_checkDownloadReady1();
	BOOL Lf_checkDownloadReady2();
	BOOL Lf_sendFpgaFile();


protected:
	LPINSPWORKINFO	lpWorkInfo;

	int		m_nFirmwareDataLen;
	BYTE*	m_pFirmwareData;
	BYTE*	szParsingData;

	BYTE* p_fpga_raw;
	BYTE m_nFlashStatus;
	UINT m_fpgaFileSize;

private:
	CFont m_Font[FONT_IDX_MAX];
	CBrush m_Brush[COLOR_IDX_MAX];


public:
	CProgressCtrl m_progDownload;
	CComboBox m_cboTargetSel;
	CComboBox m_cmbFwType;
};
