// PortController.h: interface for the CPortController class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PORTCONTROLLER_H__026116A1_CB26_11D4_9A54_444553540000__INCLUDED_)
#define AFX_PORTCONTROLLER_H__026116A1_CB26_11D4_9A54_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// User Define
#define	WM_RS232_RECEIVED1		(WM_USER+100)
#define	WM_RS232_RECEIVED2		(WM_USER+101)

//__________________________________________________________________
#define BUFF_SIZE			2048
#define WM_COMM_READ		(WM_USER+1)
#define ASCII_LF			0x0A
#define ASCII_CR			0x0D
#define ASCII_XON			0x11
#define ASCII_XOFF			0x13
//__________________________________________________________________
//class CGIE_BoadAssyApp;

class CPortController  
{
public:
	CPortController();
	virtual ~CPortController();
//__________________________________________________________________
	BOOL OpenPort1 (CString strPortName, DWORD dwBaud, WORD wParam);
	BOOL OpenPort2 (CString strPortName, DWORD dwBaud, WORD wParam);
	BOOL OpenPort3 (CString strPortName, DWORD dwBaud, WORD wParam);
	BOOL OpenPort4 (CString strPortName, DWORD dwBaud, WORD wParam);
	BOOL OpenPort5 (CString strPortName, DWORD dwBaud, WORD wParam);
	BOOL OpenPort6 (CString strPortName, DWORD dwBaud, WORD wParam); 

	void ClosePort1 ();
	void ClosePort2 ();
	void ClosePort3 ();
	void ClosePort4 ();
	void ClosePort5 ();
	void ClosePort6 ();

	DWORD WritePort1 (BYTE* pBuff, DWORD nToWrite);
	DWORD WritePort2 (BYTE* pBuff, DWORD nToWrite);
	DWORD WritePort3 (BYTE* pBuff, DWORD nToWrite);
	DWORD WritePort4 (BYTE* pBuff, DWORD nToWrite);
	DWORD WritePort5 (BYTE* pBuff, DWORD nToWrite);
	DWORD WritePort6 (BYTE* pBuff, DWORD nToWrite); 

	DWORD ReadPort1 (BYTE *pBuff, DWORD nToRead);
	DWORD ReadPort2 (BYTE *pBuff, DWORD nToRead);
	DWORD ReadPort3 (BYTE *pBuff, DWORD nToRead);
	DWORD ReadPort4 (BYTE *pBuff, DWORD nToRead);
	DWORD ReadPort5 (BYTE *pBuff, DWORD nToRead);
	DWORD ReadPort6 (BYTE *pBuff, DWORD nToRead); 

//__________________________________________________________________
	HANDLE m_hComm1, m_hComm2,m_hComm3,m_hComm4,m_hComm5,m_hComm6; 
	CString m_strPortName1,m_strPortName2,m_strPortName3,m_strPortName4,m_strPortName5,m_strPortName6; 
	BOOL m_boolConnected1, m_boolConnected2, m_boolConnected3, m_boolConnected4, m_boolConnected5, m_boolConnected6; 
	OVERLAPPED m_osRead1, m_osRead2, m_osRead3, m_osRead4, m_osRead5, m_osRead6, m_osWrite1, m_osWrite2, m_osWrite3, m_osWrite4, m_osWrite5, m_osWrite6; 
	HANDLE m_hThreadWatchComm1, m_hThreadWatchComm2, m_hThreadWatchComm3, m_hThreadWatchComm4, m_hThreadWatchComm5, m_hThreadWatchComm6; 
	WORD m_wPortID1, m_wPortID2, m_wPortID3, m_wPortID4, m_wPortID5, m_wPortID6;
	int n;
	void SetNumber (int i)	{n = i;}
	int GetNumber ()		{return n;}
	CString strBuff [3];

//	CGIE_BoadAssyApp* m_pApp;
protected:
};


DWORD ThreadWatchComm1 (CPortController* port_controller);
DWORD ThreadWatchComm2 (CPortController* port_controller);
DWORD ThreadWatchComm3 (CPortController* port_controller);
DWORD ThreadWatchComm4 (CPortController* port_controller);
DWORD ThreadWatchComm5 (CPortController* port_controller);
DWORD ThreadWatchComm6 (CPortController* port_controller); 

BOOL ThreadWatchCommParse(CPortController* port_controller, char *pBuff);
BOOL ThreadWatchCommParseHex(CPortController* port_controller, char *pBuff, DWORD dwSize);
BOOL ThreadWatchCommParse2(CPortController* port_controller, char *pBuff);
#endif // !defined(AFX_PORTCONTROLLER_H__026116A1_CB26_11D4_9A54_444553540000__INCLUDED_)
