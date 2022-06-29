#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CAutoFirmware ��ȭ �����Դϴ�.
#define MAX_FILE_SIZE		1024*1024		// �ִ� 1M Buff �Ҵ�.
#define MAX_DATASIZE 400000 //FW File���� ���� ���ִ� �ִ� ũ��
#define FLASH_PAGE_SIZE		2048//1024

class CAutoFirmware : public CDialog
{
	DECLARE_DYNAMIC(CAutoFirmware)

public:
	CAutoFirmware(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CAutoFirmware();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_AUTO_FIRMWARE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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


protected:
	LPINSPWORKINFO	lpWorkInfo;

	int		m_nFirmwareDataLen;
	BYTE*	m_pFirmwareData;
	BYTE*	szParsingData;

private:
	CFont m_Font[FONT_IDX_MAX];
	CBrush m_Brush[COLOR_IDX_MAX];


public:
	CProgressCtrl m_progDownload;
	CComboBox m_cboTargetSel;
};
