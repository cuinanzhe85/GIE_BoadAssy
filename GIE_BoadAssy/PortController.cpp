
#include "stdafx.h"
#include "PortController.h"
#include "GIE_BoadAssy.h"
/*
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
*/
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

extern HWND hCommWnd;

CPortController::CPortController()
{
	n = 0;
	m_hComm1 = (HANDLE) -1; 
	m_hComm2 = (HANDLE) -1; 
	m_hComm3 = (HANDLE) -1; 
	m_hComm4 = (HANDLE) -1; 
	m_hComm5 = (HANDLE) -1; 
	m_hComm6 = (HANDLE) -1;
//	m_pApp = (CGIE_BoadAssyApp* ) AfxGetApp();
}

CPortController::~CPortController()
{
	m_boolConnected1 = FALSE; 
	m_boolConnected2 = FALSE;
	m_boolConnected3 = FALSE; 
	m_boolConnected4 = FALSE; 
	m_boolConnected5 = FALSE; 
	m_boolConnected6 = FALSE;

	if (((HANDLE) -1) != m_hComm1)
		ClosePort1 ();
	if (((HANDLE) -1) != m_hComm2)
		ClosePort2 ();
	if (((HANDLE) -1) != m_hComm3)
		ClosePort3 ();
	if (((HANDLE) -1) != m_hComm4)
		ClosePort4 ();
	if (((HANDLE) -1) != m_hComm5)
		ClosePort5 ();
	if (((HANDLE) -1) != m_hComm6)
		ClosePort6 ();
}


BOOL CPortController::OpenPort1 (CString sPortName, DWORD dwBaud, WORD wPortID)
{
	COMMTIMEOUTS timeouts;
	DCB dcb;
	DWORD dwThreadID;
	m_boolConnected1 = FALSE;
	m_wPortID1 = wPortID;
	m_osRead1.Offset = 0;
	m_osRead1.OffsetHigh = 0;
	m_osRead1.hEvent = CreateEvent (NULL, TRUE, FALSE, NULL);
	if (!m_osRead1.hEvent)
		return FALSE;
	m_osWrite1.Offset = 0;
	m_osWrite1.OffsetHigh = 0;
	m_osWrite1.hEvent = CreateEvent (NULL, TRUE, FALSE, NULL);
	if (!m_osWrite1.hEvent)
		return FALSE;
	m_strPortName1 = sPortName;
	m_hComm1 = CreateFile (sPortName, 
							GENERIC_READ | GENERIC_WRITE, 
							0, 
							NULL, 
							OPEN_EXISTING, 
							FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, 
							NULL);
  if (m_hComm1 == (HANDLE) -1)		return FALSE;
	SetCommMask (m_hComm1, EV_RXCHAR);
	SetupComm (m_hComm1, 4096, 4096);
	timeouts.ReadIntervalTimeout = 10;
	timeouts.ReadTotalTimeoutMultiplier = 0;
	timeouts.ReadTotalTimeoutConstant = 0;
	timeouts.WriteTotalTimeoutMultiplier = 2*CBR_115200 / dwBaud;
	timeouts.WriteTotalTimeoutConstant = 0;
	SetCommTimeouts (m_hComm1, &timeouts);

	dcb.DCBlength = sizeof (DCB);
	GetCommState (m_hComm1, &dcb);
	dcb.BaudRate = dwBaud;
	dcb.ByteSize = 8;	// Keyence default = Data Bits : 7
	dcb.Parity = 0;		// Keyence default = Parity Bits : 2(even) (0-4: no, odd, even, mark, space)
	dcb.StopBits = 0;	// Keyence default = Stop Bits : 0(1Bits) (0-2, 1, 1.5, 2)

	dcb.fInX = dcb.fOutX = 0;
	dcb.XonChar = ASCII_XON;
	dcb.XoffChar = ASCII_XOFF;
	dcb.XonLim = 100;

  if (!SetCommState (m_hComm1, &dcb))		return FALSE;
	m_boolConnected1 = TRUE;

	m_hThreadWatchComm1 = CreateThread (NULL,
									   0,
									   (LPTHREAD_START_ROUTINE)ThreadWatchComm1,
									   this,
									   0,
									   &dwThreadID);

	if (!m_hThreadWatchComm1)
	{
		ClosePort1 ();
		return FALSE;
	}
	return TRUE;
}

BOOL CPortController::OpenPort2 (CString sPortName, DWORD dwBaud, WORD wPortID)
{
	COMMTIMEOUTS timeouts;
	DCB dcb;
	DWORD dwThreadID;
	m_boolConnected2 = FALSE;
	m_wPortID2 = wPortID;
	m_osRead2.Offset = 0;
	m_osRead2.OffsetHigh = 0;

	m_osRead2.hEvent = CreateEvent (NULL, TRUE, FALSE, NULL);

	if (!m_osRead2.hEvent)	return FALSE;

	m_osWrite2.Offset = 0;
	m_osWrite2.OffsetHigh = 0;
	m_osWrite2.hEvent = CreateEvent (NULL, TRUE, FALSE, NULL);
	if (!m_osWrite2.hEvent)
		return FALSE;
	m_strPortName2 = sPortName;
	m_hComm2 = CreateFile (sPortName, 
							GENERIC_READ | GENERIC_WRITE, 
							0, 
							NULL, 
							OPEN_EXISTING, 
							FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, 
							NULL);
  if (m_hComm2 == (HANDLE) -1)		return FALSE;
	SetCommMask (m_hComm2, EV_RXCHAR);
	SetupComm (m_hComm2, 4096, 4096);
	timeouts.ReadIntervalTimeout = 10;
	timeouts.ReadTotalTimeoutMultiplier = 0;
	timeouts.ReadTotalTimeoutConstant = 0;
	timeouts.WriteTotalTimeoutMultiplier = 2*CBR_115200 / dwBaud;// = 2*CBR_19200 / dwBaud;
	timeouts.WriteTotalTimeoutConstant = 0;
	SetCommTimeouts (m_hComm2, &timeouts);
//____________________________________________________________________
	dcb.DCBlength = sizeof (DCB);
	GetCommState (m_hComm2, &dcb);
	dcb.BaudRate = dwBaud;
	dcb.ByteSize = 8;	// Keyence default = Data Bits : 7
	dcb.Parity = 0;		// Keyence default = Parity Bits : 2(even) (0-4: no, odd, even, mark, space)
	dcb.StopBits = 0;	// Keyence default = Stop Bits : 0(1Bits) (0-2, 1, 1.5, 2)

	dcb.fInX = dcb.fOutX = 0;
	dcb.XonChar = ASCII_XON;
	dcb.XoffChar = ASCII_XOFF;
	dcb.XonLim = 100;

  if (!SetCommState (m_hComm2, &dcb))		return FALSE;
	m_boolConnected2 = TRUE;

	m_hThreadWatchComm2 = CreateThread (NULL,
									   0,
									   (LPTHREAD_START_ROUTINE)ThreadWatchComm2,
									   this,
									   0,
									   &dwThreadID);

	if (!m_hThreadWatchComm2)
	{
		ClosePort2 ();
		return FALSE;
	}
	return TRUE;
}

BOOL CPortController::OpenPort3 (CString sPortName, DWORD dwBaud, WORD wPortID)//Auto BCR
{
	COMMTIMEOUTS timeouts;
	DCB dcb;
	DWORD dwThreadID;
	m_boolConnected3 = FALSE;
	m_wPortID3 = wPortID;
	m_osRead3.Offset = 0;
	m_osRead3.OffsetHigh = 0;
	m_osRead3.hEvent = CreateEvent (NULL, TRUE, FALSE, NULL);
	if (!m_osRead3.hEvent)
		return FALSE;
	m_osWrite3.Offset = 0;
	m_osWrite3.OffsetHigh = 0;
	m_osWrite3.hEvent = CreateEvent (NULL, TRUE, FALSE, NULL);
	if (!m_osWrite3.hEvent)
		return FALSE;
	m_strPortName3 = sPortName;
	m_hComm3 = CreateFile (sPortName, 
							GENERIC_READ | GENERIC_WRITE, 
							0, 
							NULL, 
							OPEN_EXISTING, 
							FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, 
							NULL);
  if (m_hComm3 == (HANDLE) -1)		return FALSE;
	SetCommMask (m_hComm3, EV_RXCHAR);
	SetupComm (m_hComm3, 4096, 4096);
	timeouts.ReadIntervalTimeout = 10;
	timeouts.ReadTotalTimeoutMultiplier = 0;
	timeouts.ReadTotalTimeoutConstant = 0;
	timeouts.WriteTotalTimeoutMultiplier = 2*CBR_38400 / dwBaud;
	timeouts.WriteTotalTimeoutConstant = 0;
	SetCommTimeouts (m_hComm3, &timeouts);

	dcb.DCBlength = sizeof (DCB);
	GetCommState (m_hComm3, &dcb);
	dcb.BaudRate = dwBaud;
	dcb.ByteSize = 8;	// Keyence default = Data Bits : 7
	dcb.Parity = 0;		// Keyence default = Parity Bits : 2(even) (0-4: no, odd, even, mark, space)
	dcb.StopBits = 2;	// Keyence default = Stop Bits : 0(1Bits) (0-2, 1, 1.5, 2)

	dcb.fInX = dcb.fOutX = 0;
	dcb.XonChar = ASCII_XON;
	dcb.XoffChar = ASCII_XOFF;
	dcb.XonLim = 100;

  if (!SetCommState (m_hComm3, &dcb))		return FALSE;
	m_boolConnected3 = TRUE;

	m_hThreadWatchComm3 = CreateThread (NULL,
									   0,
									   (LPTHREAD_START_ROUTINE)ThreadWatchComm3,
									   this,
									   0,
									   &dwThreadID);

	if (!m_hThreadWatchComm3)
	{
		ClosePort3 ();
		return FALSE;
	}
	return TRUE;
}

BOOL CPortController::OpenPort4 (CString sPortName, DWORD dwBaud, WORD wPortID)
{
	COMMTIMEOUTS timeouts;
	DCB dcb;
	DWORD dwThreadID;
	m_boolConnected4 = FALSE;
	m_wPortID4 = wPortID;
	m_osRead4.Offset = 0;
	m_osRead4.OffsetHigh = 0;
	m_osRead4.hEvent = CreateEvent (NULL, TRUE, FALSE, NULL);
	if (!m_osRead4.hEvent)
		return FALSE;
	m_osWrite4.Offset = 0;
	m_osWrite4.OffsetHigh = 0;
	m_osWrite4.hEvent = CreateEvent (NULL, TRUE, FALSE, NULL);
	if (!m_osWrite4.hEvent)
		return FALSE;
	m_strPortName4 = sPortName;
	m_hComm4 = CreateFile (sPortName, 
							GENERIC_READ | GENERIC_WRITE, 
							0, 
							NULL, 
							OPEN_EXISTING, 
							FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, 
							NULL);
  if (m_hComm4 == (HANDLE) -1)		return FALSE;
	SetCommMask (m_hComm4, EV_RXCHAR);
	SetupComm (m_hComm4, 4096, 4096);
	timeouts.ReadIntervalTimeout = 10;
	timeouts.ReadTotalTimeoutMultiplier = 0;
	timeouts.ReadTotalTimeoutConstant = 0;
	timeouts.WriteTotalTimeoutMultiplier = 2*CBR_9600 / dwBaud;
	timeouts.WriteTotalTimeoutConstant = 0;
	SetCommTimeouts (m_hComm4, &timeouts);

	dcb.DCBlength = sizeof (DCB);
	GetCommState (m_hComm4, &dcb);
	dcb.BaudRate = dwBaud;
	dcb.ByteSize = 8;	// Keyence default = Data Bits : 7
	dcb.Parity = 0;		// Keyence default = Parity Bits : 2(even) (0-4: no, odd, even, mark, space)
	dcb.StopBits = 0;	// Keyence default = Stop Bits : 0(1Bits) (0-2, 1, 1.5, 2)

	dcb.fInX = dcb.fOutX = 0;
	dcb.XonChar = ASCII_XON;
	dcb.XoffChar = ASCII_XOFF;
	dcb.XonLim = 100;

  if (!SetCommState (m_hComm4, &dcb))		return FALSE;
	m_boolConnected4 = TRUE;

	m_hThreadWatchComm4 = CreateThread (NULL,
									   0,
									   (LPTHREAD_START_ROUTINE)ThreadWatchComm4,
									   this,
									   0,
									   &dwThreadID);

	if (!m_hThreadWatchComm4)
	{
		ClosePort4 ();
		return FALSE;
	}
	return TRUE;
}

BOOL CPortController::OpenPort5 (CString sPortName, DWORD dwBaud, WORD wPortID)
{
	COMMTIMEOUTS timeouts;
	DCB dcb;
	DWORD dwThreadID;
	m_boolConnected5 = FALSE;
	m_wPortID5 = wPortID;
	m_osRead5.Offset = 0;
	m_osRead5.OffsetHigh = 0;
	m_osRead5.hEvent = CreateEvent (NULL, TRUE, FALSE, NULL);
	if (!m_osRead5.hEvent)
		return FALSE;
	m_osWrite5.Offset = 0;
	m_osWrite5.OffsetHigh = 0;
	m_osWrite5.hEvent = CreateEvent (NULL, TRUE, FALSE, NULL);
	if (!m_osWrite5.hEvent)
		return FALSE;
	m_strPortName5 = sPortName;
	m_hComm5 = CreateFile (sPortName, 
							GENERIC_READ | GENERIC_WRITE, 
							0, 
							NULL, 
							OPEN_EXISTING, 
							FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, 
							NULL);
  if (m_hComm5 == (HANDLE) -1)		return FALSE;
	SetCommMask (m_hComm5, EV_RXCHAR);
	SetupComm (m_hComm5, 4096, 4096);
	timeouts.ReadIntervalTimeout = 10;
	timeouts.ReadTotalTimeoutMultiplier = 0;
	timeouts.ReadTotalTimeoutConstant = 0;
	timeouts.WriteTotalTimeoutMultiplier = 2*CBR_38400 / dwBaud;
	timeouts.WriteTotalTimeoutConstant = 0;
	SetCommTimeouts (m_hComm5, &timeouts);

	dcb.DCBlength = sizeof (DCB);
	GetCommState (m_hComm5, &dcb);
	dcb.BaudRate = dwBaud;
	dcb.ByteSize = 8;	// Keyence default = Data Bits : 7
	dcb.Parity = 0;		// Keyence default = Parity Bits : 2(even) (0-4: no, odd, even, mark, space)
	dcb.StopBits = 2;	// Keyence default = Stop Bits : 0(1Bits) (0-2, 1, 1.5, 2)

	dcb.fInX = dcb.fOutX = 1;
	dcb.XonChar = ASCII_XON;
	dcb.XoffChar = ASCII_XOFF;
	dcb.XonLim = 100;

  if (!SetCommState (m_hComm5, &dcb))		return FALSE;
	m_boolConnected5 = TRUE;

	m_hThreadWatchComm5 = CreateThread (NULL,
									   0,
									   (LPTHREAD_START_ROUTINE)ThreadWatchComm5,
									   this,
									   0,
									   &dwThreadID);

	if (!m_hThreadWatchComm5)
	{
		ClosePort5 ();
		return FALSE;
	}
	return TRUE;
}

BOOL CPortController::OpenPort6 (CString sPortName, DWORD dwBaud, WORD wPortID) // 2005-03-07 : AutoBCR2
{
	COMMTIMEOUTS timeouts;
	DCB dcb;
	DWORD dwThreadID;
	m_boolConnected6 = FALSE;
	m_wPortID6 = wPortID;
	m_osRead6.Offset = 0;
	m_osRead6.OffsetHigh = 0;
	m_osRead6.hEvent = CreateEvent (NULL, TRUE, FALSE, NULL);
	if (!m_osRead6.hEvent)
		return FALSE;
	m_osWrite6.Offset = 0;
	m_osWrite6.OffsetHigh = 0;
	m_osWrite6.hEvent = CreateEvent (NULL, TRUE, FALSE, NULL);
	if (!m_osWrite6.hEvent)
		return FALSE;
	m_strPortName6 = sPortName;
	m_hComm6 = CreateFile (sPortName, 
							GENERIC_READ | GENERIC_WRITE, 
							0, 
							NULL, 
							OPEN_EXISTING, 
							FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, 
							NULL);
  if (m_hComm6 == (HANDLE) -1)		return FALSE;
	SetCommMask (m_hComm6, EV_RXCHAR);
	SetupComm (m_hComm6, 4096, 4096);
	timeouts.ReadIntervalTimeout = 10;
	timeouts.ReadTotalTimeoutMultiplier = 0;
	timeouts.ReadTotalTimeoutConstant = 0;
	timeouts.WriteTotalTimeoutMultiplier = 2*CBR_38400 / dwBaud;
	timeouts.WriteTotalTimeoutConstant = 0;
	SetCommTimeouts (m_hComm6, &timeouts);
//____________________________________________________________________
	dcb.DCBlength = sizeof (DCB);
	GetCommState (m_hComm6, &dcb);
	dcb.BaudRate = dwBaud;
	dcb.ByteSize = 8;	// Keyence default = Data Bits : 7
	dcb.Parity = 0;		// Keyence default = Parity Bits : 2(even) (0-4: no, odd, even, mark, space)
	dcb.StopBits = 0;	// Keyence default = Stop Bits : 0(1Bits) (0-2, 1, 1.5, 2)

	dcb.fInX = dcb.fOutX = 0;
	dcb.XonChar = ASCII_XON;
	dcb.XoffChar = ASCII_XOFF;
	dcb.XonLim = 100;

  if (!SetCommState (m_hComm6, &dcb))		return FALSE;
	m_boolConnected6 = TRUE;

	m_hThreadWatchComm6 = CreateThread (NULL,
									   0,
									   (LPTHREAD_START_ROUTINE)ThreadWatchComm6,
									   this,
									   0,
									   &dwThreadID);

	if (!m_hThreadWatchComm6)
	{
		ClosePort6 ();
		return FALSE;
	}
	return TRUE;
}

void CPortController::ClosePort1 ()
{
	m_boolConnected1 = FALSE;
	SetCommMask ((void *)(m_hComm1), (unsigned long)0);
	PurgeComm (m_hComm1, PURGE_TXABORT | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_RXCLEAR | EV_RXFLAG | EV_TXEMPTY | EV_ERR | EV_BREAK);
	CloseHandle (m_hComm1);
	m_hComm1 = (HANDLE) -1;
}

void CPortController::ClosePort2 ()
{
	m_boolConnected2 = FALSE;
	SetCommMask ((void *)(m_hComm2), (unsigned long)0);
	PurgeComm (m_hComm2, PURGE_TXABORT | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_RXCLEAR | EV_RXFLAG | EV_TXEMPTY | EV_ERR | EV_BREAK);
	CloseHandle (m_hComm2);
	m_hComm2 = (HANDLE) -1;
}

void CPortController::ClosePort3 ()
{
	m_boolConnected3 = FALSE;
	SetCommMask ((void *)(m_hComm3), (unsigned long)0);
	PurgeComm (m_hComm3, PURGE_TXABORT | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_RXCLEAR | EV_RXFLAG | EV_TXEMPTY | EV_ERR | EV_BREAK);
	CloseHandle (m_hComm3);
	m_hComm3 = (HANDLE) -1;
}
void CPortController::ClosePort4 ()
{
	m_boolConnected4 = FALSE;
	SetCommMask ((void *)(m_hComm4), (unsigned long)0);
	PurgeComm (m_hComm4, PURGE_TXABORT | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_RXCLEAR | EV_RXFLAG | EV_TXEMPTY | EV_ERR | EV_BREAK);
	CloseHandle (m_hComm4);
	m_hComm4 = (HANDLE) -1;
}
void CPortController::ClosePort5 ()
{
	m_boolConnected5 = FALSE;
	SetCommMask ((void *)(m_hComm5), (unsigned long)0);
	PurgeComm (m_hComm5, PURGE_TXABORT | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_RXCLEAR | EV_RXFLAG | EV_TXEMPTY | EV_ERR | EV_BREAK);
	CloseHandle (m_hComm5);
	m_hComm5 = (HANDLE) -1;
}

void CPortController::ClosePort6 () // 2005-03-07 : AutoBCR2
{
	m_boolConnected6 = FALSE;
	SetCommMask ((void *)(m_hComm6), (unsigned long)0);
	PurgeComm (m_hComm6, PURGE_TXABORT | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_RXCLEAR | EV_RXFLAG | EV_TXEMPTY | EV_ERR | EV_BREAK);
	CloseHandle (m_hComm6);
	m_hComm6 = (HANDLE) -1;
}

DWORD CPortController::WritePort1 (BYTE* pBuff, DWORD nToWrite)
{
	DWORD dwWritten, dwError, dwErrorFlags;
	COMSTAT comstat;

	if (!WriteFile (m_hComm1, pBuff, nToWrite, &dwWritten, &m_osWrite1))
	{
		if (GetLastError () == ERROR_IO_PENDING)
		{
			while (!GetOverlappedResult (m_hComm1, &m_osWrite1, &dwWritten, TRUE))
			{
				dwError = GetLastError ();
				if (dwError != ERROR_IO_INCOMPLETE)
				{
					ClearCommError (m_hComm1, &dwErrorFlags, &comstat);
					break;
				}
			}
		}
		else
		{
			dwWritten = 0;
			ClearCommError (m_hComm1, &dwErrorFlags, &comstat);
		}
	}
	return dwWritten;
}


DWORD CPortController::WritePort2 (BYTE* pBuff, DWORD nToWrite)
{
	DWORD dwWritten, dwError, dwErrorFlags;
	COMSTAT comstat;

	if (!WriteFile (m_hComm2, pBuff, nToWrite, &dwWritten, &m_osWrite2))
	{
		if (GetLastError () == ERROR_IO_PENDING)
		{
			while (!GetOverlappedResult (m_hComm2, &m_osWrite2, &dwWritten, TRUE))
			{
				dwError = GetLastError ();
				if (dwError != ERROR_IO_INCOMPLETE)
				{
					ClearCommError (m_hComm2, &dwErrorFlags, &comstat);
					break;
				}
			}
		}
		else
		{
			dwWritten = 0;
			ClearCommError (m_hComm2, &dwErrorFlags, &comstat);
		}
	}
	return dwWritten;
}

DWORD CPortController::WritePort3 (BYTE* pBuff, DWORD nToWrite)
{
	DWORD dwWritten, dwError, dwErrorFlags;
	COMSTAT comstat;
	if (!WriteFile (m_hComm3, pBuff, nToWrite, &dwWritten, &m_osWrite3))
	{
//		DWORD dwErrorCode = GetLastError ();
		if (GetLastError () == ERROR_IO_PENDING)
		{
			while (!GetOverlappedResult (m_hComm3, &m_osWrite3, &dwWritten, TRUE))
			{
				dwError = GetLastError ();
				if (dwError != ERROR_IO_INCOMPLETE)
				{
					ClearCommError (m_hComm3, &dwErrorFlags, &comstat);
					break;
				}
			}
		}
		else
		{
			dwWritten = 0;
			ClearCommError (m_hComm3, &dwErrorFlags, &comstat);
		}
	}
	return dwWritten;
}
DWORD CPortController::WritePort4 (BYTE* pBuff, DWORD nToWrite)
{
	DWORD dwWritten, dwError, dwErrorFlags;
	COMSTAT comstat;
	if (!WriteFile (m_hComm4, pBuff, nToWrite, &dwWritten, &m_osWrite4))
	{
		if (GetLastError () == ERROR_IO_PENDING)
		{
			while (!GetOverlappedResult (m_hComm4, &m_osWrite4, &dwWritten, TRUE))
			{
				dwError = GetLastError ();
				if (dwError != ERROR_IO_INCOMPLETE)
				{
					ClearCommError (m_hComm4, &dwErrorFlags, &comstat);
					break;
				}
			}
		}
		else
		{
			dwWritten = 0;
			ClearCommError (m_hComm4, &dwErrorFlags, &comstat);
		}
	}
	return dwWritten;
}
DWORD CPortController::WritePort5 (BYTE* pBuff, DWORD nToWrite)
{
	DWORD dwWritten, dwError, dwErrorFlags;
	COMSTAT comstat;
	if (!WriteFile (m_hComm5, pBuff, nToWrite, &dwWritten, &m_osWrite5))
	{
		if (GetLastError () == ERROR_IO_PENDING)
		{
			while (!GetOverlappedResult (m_hComm5, &m_osWrite5, &dwWritten, TRUE))
			{
				dwError = GetLastError ();
				if (dwError != ERROR_IO_INCOMPLETE)
				{
					ClearCommError (m_hComm5, &dwErrorFlags, &comstat);
					break;
				}
			}
		}
		else
		{
			dwWritten = 0;
			ClearCommError (m_hComm5, &dwErrorFlags, &comstat);
		}
	}
	return dwWritten;
}

DWORD CPortController::WritePort6 (BYTE* pBuff, DWORD nToWrite)
{
	DWORD dwWritten, dwError, dwErrorFlags;
	COMSTAT comstat;
	if (!WriteFile (m_hComm6, pBuff, nToWrite, &dwWritten, &m_osWrite6))
	{
//		DWORD dwErrorCode = GetLastError ();
		if (GetLastError () == ERROR_IO_PENDING)
		{
			while (!GetOverlappedResult (m_hComm6, &m_osWrite6, &dwWritten, TRUE))
			{
				dwError = GetLastError ();
				if (dwError != ERROR_IO_INCOMPLETE)
				{
					ClearCommError (m_hComm6, &dwErrorFlags, &comstat);
					break;
				}
			}
		}
		else
		{
			dwWritten = 0;
			ClearCommError (m_hComm6, &dwErrorFlags, &comstat);
		}
	}
	return dwWritten;
}

DWORD CPortController::ReadPort1 (BYTE* pBuff, DWORD nToRead)
{
	BOOL		fReadStat ;
	DWORD		dwLength, dwError, dwErrorFlags;
	COMSTAT		ComStat ;
	OVERLAPPED	osRead = {0};
	
	osRead.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	
	// only try to read number of bytes in queue
	ClearCommError(m_hComm1, &dwErrorFlags, &ComStat ) ;
	dwLength = ComStat.cbInQue;
	
	if(0 < dwLength)
	{
		fReadStat = ReadFile(m_hComm1, pBuff, dwLength, &dwLength, &osRead);

		if (!fReadStat)
		{
			if (GetLastError() == ERROR_IO_PENDING)
			{	
				while(!GetOverlappedResult(m_hComm1, &osRead, &dwLength, TRUE))
				{
					dwError = GetLastError();
					if(dwError == ERROR_IO_INCOMPLETE)
					{			
						continue;
					}
					else
					{
						ClearCommError(m_hComm1, &dwErrorFlags, &ComStat);
						break;
					}					
				}
			}
			else
			{
				dwLength = 0 ;
				ClearCommError(m_hComm1, &dwErrorFlags, &ComStat);
			}
		}
	}
	
	CloseHandle(osRead.hEvent);
	return dwLength;
}

DWORD CPortController::ReadPort2 (BYTE* pBuff, DWORD nToRead)
{
	BOOL fReadStat ;
	DWORD dwRead, dwError, dwErrorFlags;
	COMSTAT comstat;
	OVERLAPPED	osRead = {0};

	osRead.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	ClearCommError (m_hComm2, &dwErrorFlags, &comstat);
	dwRead = comstat.cbInQue;

	if(dwRead > 0)
	{
		fReadStat = ReadFile(m_hComm2, pBuff, dwRead, &dwRead, &osRead);
		if (!fReadStat)
		{
			if (GetLastError () == ERROR_IO_PENDING)
			{
				while (!GetOverlappedResult (m_hComm2, &osRead, &dwRead, TRUE))
				{
					dwError = GetLastError ();
					if (dwError != ERROR_IO_INCOMPLETE)
					{
						continue;
					}
					else
					{
						ClearCommError (m_hComm2, &dwErrorFlags, &comstat);
						break;
					}
				}
			}
			else
			{
				dwRead = 0;
				ClearCommError (m_hComm2, &dwErrorFlags, &comstat);
			}
		}
	}
	return dwRead;
}

DWORD CPortController::ReadPort3 (BYTE* pBuff, DWORD nToRead)
{
	DWORD dwRead, dwError, dwErrorFlags;
	COMSTAT comstat;
	ClearCommError (m_hComm3, &dwErrorFlags, &comstat);
	dwRead = comstat.cbInQue;
	if (dwRead > 0)
	{
		if (!ReadFile (m_hComm3, pBuff, nToRead, &dwRead, &m_osRead3))
		{
			if (GetLastError () == ERROR_IO_PENDING)
			{
				while (!GetOverlappedResult (m_hComm3, &m_osRead3, &dwRead, TRUE))
				{
					dwError = GetLastError ();
					if (dwError != ERROR_IO_INCOMPLETE)
					{
						ClearCommError (m_hComm3, &dwErrorFlags, &comstat);
						break;
					}
				}
			}
			else
			{
				dwRead = 0;
				ClearCommError (m_hComm3, &dwErrorFlags, &comstat);
			}
		}
	}
	return dwRead;
}

DWORD CPortController::ReadPort4 (BYTE* pBuff, DWORD nToRead)
{
	DWORD dwRead, dwError, dwErrorFlags;
	COMSTAT comstat;
	ClearCommError (m_hComm4, &dwErrorFlags, &comstat);
	dwRead = comstat.cbInQue;
	if (dwRead > 0)
	{
		Sleep (50);
		if (!ReadFile(m_hComm4, pBuff, nToRead, &dwRead, &m_osRead4))
		{
			if(GetLastError () == ERROR_IO_PENDING)
			{
				while (!GetOverlappedResult (m_hComm4, &m_osRead4, &dwRead, TRUE))
				{
					dwError = GetLastError ();
					if (dwError != ERROR_IO_INCOMPLETE)
					{
						ClearCommError (m_hComm4, &dwErrorFlags, &comstat);
						break;
					}
				}
			}
			else
			{
				dwRead = 0;
				ClearCommError (m_hComm4, &dwErrorFlags, &comstat);
			}
		}
	}
	return dwRead;
}

DWORD CPortController::ReadPort5 (BYTE* pBuff, DWORD nToRead)
{
	DWORD dwRead, dwError, dwErrorFlags;
	COMSTAT comstat;
	ClearCommError (m_hComm5, &dwErrorFlags, &comstat);
	dwRead = comstat.cbInQue;
	if (dwRead > 0)
	{
		Sleep (10);
		if (!ReadFile (m_hComm5, pBuff, nToRead, &dwRead, &m_osRead5))
		{
			if (GetLastError () == ERROR_IO_PENDING)
			{
				while (!GetOverlappedResult (m_hComm5, &m_osRead5, &dwRead, TRUE))
				{
					dwError = GetLastError ();
					if (dwError != ERROR_IO_INCOMPLETE)
					{
						ClearCommError (m_hComm5, &dwErrorFlags, &comstat);
						break;
					}
				}
			}
			else
			{
				dwRead = 0;
				ClearCommError (m_hComm5, &dwErrorFlags, &comstat);
			}
		}
	}
	return dwRead;
}

DWORD CPortController::ReadPort6 (BYTE* pBuff, DWORD nToRead) // 2005-03-07 : AutoBCR2
{
	DWORD dwRead, dwError, dwErrorFlags;
	COMSTAT comstat;
	ClearCommError (m_hComm6, &dwErrorFlags, &comstat);
	dwRead = comstat.cbInQue;
	if (dwRead > 0)
	{
		Sleep (10);
		if (!ReadFile (m_hComm6, pBuff, nToRead, &dwRead, &m_osRead6))
		{
			if (GetLastError () == ERROR_IO_PENDING)
			{
				while (!GetOverlappedResult (m_hComm6, &m_osRead6, &dwRead, TRUE))
				{
					dwError = GetLastError ();
					if (dwError != ERROR_IO_INCOMPLETE)
					{
						ClearCommError (m_hComm6, &dwErrorFlags, &comstat);
						break;
					}
				}
			}
			else
			{
				dwRead = 0;
				ClearCommError (m_hComm6, &dwErrorFlags, &comstat);
			}
		}
	}
	return dwRead;
}

DWORD ThreadWatchComm1(CPortController* port_controller)
{
	DWORD dwEvent;
	OVERLAPPED os;
	BOOL bOK = TRUE;
	BYTE buff[BUFF_SIZE] = {0,};
	DWORD dwRead;

	memset (&os, 0, sizeof (OVERLAPPED));
	//memset (port_controller->m_pApp->szCommRxBuff, 0, sizeof(port_controller->m_pApp->szCommRxBuff));
	memset (m_pApp->szCommRxBuff, 0, sizeof(m_pApp->szCommRxBuff));

	os.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	if(!os.hEvent)
		bOK = FALSE;

//	if (!SetCommMask (port_controller->m_hComm1, EV_RXCHAR))
//		bOK = FALSE;

	if(!bOK)
	{
		AfxMessageBox (_T("Error while creating ThreadWatchComm 'COM1'"));
		return FALSE;
	}
	while(port_controller->m_boolConnected1)
	{
		dwEvent = 0;
		WaitCommEvent (port_controller->m_hComm1, &dwEvent, NULL);
		if((dwEvent & EV_RXCHAR) == EV_RXCHAR)
		{
			dwRead = port_controller->ReadPort1(buff, BUFF_SIZE);
 			if(dwRead > 0)
			{
//*********************************************************************
				if(m_pApp->m_bRcvHex == false)
					ThreadWatchCommParse(port_controller, (char*)buff);
				else
					ThreadWatchCommParseHex(port_controller, (char*)buff,dwRead);
//*********************************************************************
				memset (buff, 0x00, BUFF_SIZE);
			}
		}
		else
		{
			dwRead = port_controller->ReadPort1 (buff, BUFF_SIZE);
			if (dwRead > 0)
			{
				memset (buff, 0x00, BUFF_SIZE);
			}
		}
	}
	CloseHandle (os.hEvent);
	port_controller->m_hThreadWatchComm1 = NULL;
	return TRUE;
}

DWORD ThreadWatchComm2(CPortController* port_controller) //GFD250
{
	DWORD dwEvent;
	OVERLAPPED os;
	BOOL bOK = TRUE;
	BYTE buff[BUFF_SIZE] = {0,};
	DWORD dwRead;

	memset (&os, 0, sizeof (OVERLAPPED));
	memset (m_pApp->szCommRxBuff2, 0, sizeof(m_pApp->szCommRxBuff2));

	os.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	if(!os.hEvent)
		bOK = FALSE;

	if(!bOK)
	{
		AfxMessageBox (_T("Error while creating ThreadWatchComm 'COM2'"));
		return FALSE;
	}
	while(port_controller->m_boolConnected2)
	{
		dwEvent = 0;
		WaitCommEvent (port_controller->m_hComm2, &dwEvent, NULL);
		if((dwEvent & EV_RXCHAR) == EV_RXCHAR)
		{
			dwRead = port_controller->ReadPort2(buff, BUFF_SIZE);
 			if(dwRead > 0)
			{
				ThreadWatchCommParse2(port_controller, (char*)buff);
				memset (buff, 0x00, BUFF_SIZE);
			}
		}
		else
		{
			dwRead = port_controller->ReadPort2(buff, BUFF_SIZE);
			if (dwRead > 0)
			{
				memset (buff, 0x00, BUFF_SIZE);
			}
		}
	}
	CloseHandle (os.hEvent);
	port_controller->m_hThreadWatchComm2 = NULL;
	return TRUE;
}

DWORD ThreadWatchComm3 (CPortController* port_controller)
{
	DWORD dwEvent;
	OVERLAPPED os;
	BOOL bOK = TRUE;
	BYTE buff [BUFF_SIZE] = {0,};
	DWORD dwRead;
	memset (&os, 0, sizeof (OVERLAPPED));
	os.hEvent = CreateEvent (NULL, TRUE, FALSE, NULL);
	if (!os.hEvent)
		bOK = FALSE;
	if (!SetCommMask (port_controller->m_hComm3, EV_RXCHAR))
		bOK = FALSE;
	if (!bOK)
	{
//		AfxMessageBox ("Error while creating ThreadWatchComm, "+port_controller->m_strPortName3);
		return FALSE;
	}
	while (port_controller->m_boolConnected3)
	{
		dwEvent = 0;
		WaitCommEvent (port_controller->m_hComm3, &dwEvent, NULL);
		if ((dwEvent & EV_RXCHAR) == EV_RXCHAR)
		{
			dwRead = port_controller->ReadPort3 (buff, BUFF_SIZE);
 			if (dwRead > 0)
			{
//*********************************************************************
				m_pApp->Gf_receivedBCRAckInfo(buff);
//*********************************************************************
				memset (buff, 0x00, BUFF_SIZE);
			}
		}
		else
		{
			dwRead = port_controller->ReadPort3 (buff, BUFF_SIZE);
			if (dwRead > 0)
			{
				memset (buff, 0, BUFF_SIZE);
			}
		}
	}
	CloseHandle (os.hEvent);
	port_controller->m_hThreadWatchComm3 = NULL;

	return TRUE;
}

DWORD ThreadWatchComm4 (CPortController* port_controller)  // Auto BCR
{
	DWORD dwEvent;
	OVERLAPPED os;
	BOOL bOK = TRUE;
	BYTE buff [BUFF_SIZE] = {0,};
	DWORD dwRead;

	memset (&os, 0, sizeof (OVERLAPPED));

	os.hEvent = CreateEvent (NULL, TRUE, FALSE, NULL);
	if(!os.hEvent)
		bOK = FALSE;

	if(!SetCommMask (port_controller->m_hComm4, EV_RXCHAR))
		bOK = FALSE;

	if(!bOK)
	{
		AfxMessageBox (_T("Error while creating ThreadWatchComm 'COM4'"));
		return FALSE;
	}

	while (port_controller->m_boolConnected4)
	{
		dwEvent = 0;
		WaitCommEvent (port_controller->m_hComm4, &dwEvent, NULL);
		if ((dwEvent & EV_RXCHAR) == EV_RXCHAR)
		{
			dwRead = port_controller->ReadPort4(buff, BUFF_SIZE);
 			if (dwRead > 0)
			{
				m_pApp->Gf_receivedBLUAckInfo((char*)buff);
				memset (buff, 0x00, BUFF_SIZE);
			}
		}
		else
		{
			dwRead = port_controller->ReadPort4 (buff, BUFF_SIZE);
			if (dwRead > 0)
			{
				memset (buff, 0, BUFF_SIZE);
			}
		}
	}
	CloseHandle (os.hEvent);
	port_controller->m_hThreadWatchComm4 = NULL;
	return TRUE;
}

DWORD ThreadWatchComm5 (CPortController* port_controller)
{

	DWORD dwEvent;
	OVERLAPPED os;
	BOOL bOK = TRUE;
	BYTE buff [4096] = {0,}; // BUFF_SIZE
	DWORD dwRead;
	memset (&os, 0, sizeof (OVERLAPPED));
	os.hEvent = CreateEvent (NULL, TRUE, FALSE, NULL);
	if (!os.hEvent)
		bOK = FALSE;
	if (!SetCommMask (port_controller->m_hComm5, EV_RXCHAR))
		bOK = FALSE;
	if (!bOK)
	{
	//	AfxMessageBox ("Error while creating ThreadWatchComm, "+port_controller->m_strPortName5);
		return FALSE;
	}
	while (port_controller->m_boolConnected5)
	{
		dwEvent = 0;
		WaitCommEvent (port_controller->m_hComm5, &dwEvent, NULL);
		if ((dwEvent & EV_RXCHAR) == EV_RXCHAR)
		{
			dwRead = port_controller->ReadPort5 (buff, BUFF_SIZE);
 			if (dwRead > 0)
			{
//*********************************************************************
	//			port_controller->m_pApp->ReceivedLEDBacklightInfo((char* )buff, (int) dwRead);
//*********************************************************************
				Sleep (1);
				memset (buff, 0x00, BUFF_SIZE);
			}
		}
		else
		{
			dwRead = port_controller->ReadPort5 (buff, BUFF_SIZE);
			if (dwRead > 0)
			{
				memset (buff, 0, BUFF_SIZE);
			}
		}
	}
	CloseHandle (os.hEvent);
	port_controller->m_hThreadWatchComm5 = NULL;

	return TRUE;
}

DWORD ThreadWatchComm6 (CPortController* port_controller) // 2005-03-07 : AutoBCR2
{
	DWORD dwEvent;
	OVERLAPPED os;
	BOOL bOK = TRUE;
	BYTE buff [BUFF_SIZE] = {0,};
	DWORD dwRead;
	memset (&os, 0, sizeof (OVERLAPPED));
	os.hEvent = CreateEvent (NULL, TRUE, FALSE, NULL);
	if (!os.hEvent)
		bOK = FALSE;
	if (!SetCommMask (port_controller->m_hComm6, EV_RXCHAR))
		bOK = FALSE;
	if (!bOK)
	{
	//	AfxMessageBox ("Error while creating ThreadWatchComm, "+port_controller->m_strPortName6);
		return FALSE;
	}
	while (port_controller->m_boolConnected6)
	{
		dwEvent = 0;
		WaitCommEvent (port_controller->m_hComm6, &dwEvent, NULL);
		if ((dwEvent & EV_RXCHAR) == EV_RXCHAR)
		{
			dwRead = port_controller->ReadPort6 (buff, BUFF_SIZE);
 			if (dwRead > 0)
			{
//*********************************************************************


//*********************************************************************
//				Sleep(20);
				memset (buff, 0x00, BUFF_SIZE);
			}
		}
		else
		{
			dwRead = port_controller->ReadPort6 (buff, BUFF_SIZE);
			if (dwRead > 0)
			{
				memset (buff, 0x00, BUFF_SIZE);
			}
		}
	}
	CloseHandle (os.hEvent);
	port_controller->m_hThreadWatchComm6 = NULL;
	return TRUE;
}


BOOL ThreadWatchCommParse(CPortController* port_controller, char *pBuff)
{
	UINT nStP=0, nEdP=0;
	BYTE TxBuff[BUFF_SIZE] = {0,};
	UINT i;

	if(pBuff[0] == 0x02)
	{
		memset (m_pApp->szCommRxBuff, 0, sizeof(m_pApp->szCommRxBuff));
		sprintf_s((char*)m_pApp->szCommRxBuff, BUFF_SIZE, "%s", pBuff);
	}
	else
	{
		sprintf_s((char*)m_pApp->szCommRxBuff, BUFF_SIZE, "%s%s", m_pApp->szCommRxBuff, pBuff);
	}

	if(strlen((char*)m_pApp->szCommRxBuff) >= 16)
	{
		while(1)
		{			
			BOOL bStxIn=FALSE;
			BOOL bEtxIn=FALSE;
			BYTE nCheckSum=0;
		
			UINT nLength = (int)strlen(m_pApp->szCommRxBuff);
			for(i=0; i<nLength; i++)
			{
				if(m_pApp->szCommRxBuff[i] == 0x02)
				{
					bStxIn = TRUE;
					break;
				}
			}
			nStP = i;
			
			if(i==nLength)
			{
				memset (m_pApp->szCommRxBuff, 0, sizeof(m_pApp->szCommRxBuff));
				break;
			}

			for(; i<nLength; i++)
			{
				if(m_pApp->szCommRxBuff[i] == 0x03)
				{
					bEtxIn = TRUE;
					break;
				}
			}
			nEdP = i;
	
			if((bStxIn==FALSE) || (bEtxIn==FALSE))	break;		

			memcpy (TxBuff, m_pApp->szCommRxBuff+nStP, (nEdP-nStP)+1);

			m_pApp->Gf_receivedPgAckInfo(TxBuff);	

			memset (TxBuff, 0, sizeof(TxBuff));


			memcpy (TxBuff, (m_pApp->szCommRxBuff+(nEdP-nStP)+1), (nLength - (nEdP-nStP)-1));
			memset (m_pApp->szCommRxBuff, 0, BUFF_SIZE);
			sprintf_s((char*)m_pApp->szCommRxBuff, BUFF_SIZE, "%s", TxBuff);

			memset (TxBuff, 0, sizeof(TxBuff));
		}
	}

	memset (pBuff, 0x00, BUFF_SIZE);
	memset (TxBuff, 0x00, sizeof(TxBuff));

	return TRUE;
}

BOOL ThreadWatchCommParseHex(CPortController* port_controller, char *pBuff, DWORD dwSize)
{
	UINT nStP=0, nEdP=0, nCommRxSize;
	BYTE TxBuff[BUFF_SIZE] = {0,};

	// *********************************************************************
	// Hex RS232C Receive
	// *********************************************************************

	// Hex 값에는 Receive Data가 STX값이 입력될 수 있으므로 Receive Data 모두를 Receive Buff에 쌓는다.
	memcpy(m_pApp->szCommRxBuff+m_pApp->m_nCommRxTotData, pBuff, dwSize);

	// Receive된 Hex Data의 Byte 수를 누적한다.
	m_pApp->m_nCommRxTotData += dwSize;

	// Hex Data로 Receive할 전체 Data Size를 구한다.
	if(m_pApp->m_nCommRxTotData > 13)
	{
		// RX Packet의 9~12 위치는 전송하는 순수 Data Size이다.
		sscanf_s((char*)&m_pApp->szCommRxBuff[9], "%04X", &m_pApp->m_nRcvHexSize);
		// RX Packet에서 STX, TARGET, CMD, LENGTH, CHECKSUM, ETX의 Total값은 16이다. 16+Data가 전체 RX Packet의 Size가 된다.
		nCommRxSize = 16 + m_pApp->m_nRcvHexSize;
	}

	// Receive Buff에 쌓인 Data의 길이가 Read해야하는 Size와 같으면 Data를 처리한다.
	if(m_pApp->m_nCommRxTotData >= nCommRxSize)
	{
		while(1)
		{
			// STX, ETX, Packet Length 등의 변수를 설정한다.
			BOOL bStxIn=FALSE;
			BOOL bEtxIn=FALSE;
			BYTE nCheckSum=0;

			// Receive Buff에서 STX 값을 확인한다.
			if(m_pApp->szCommRxBuff[0] != 0x02)
			{
				memset (m_pApp->szCommRxBuff, 0, sizeof(m_pApp->szCommRxBuff));
				break;
			}

			// Receive Buff에서 ETX 값을 확인한다.
			if(m_pApp->szCommRxBuff[nCommRxSize-1] != 0x03)
			{
				memset (m_pApp->szCommRxBuff, 0, sizeof(m_pApp->szCommRxBuff));
				break;
			}

			// Receive Data에 대한 Check Sum 값을 구한다.
			for(UINT i=1; i<(nCommRxSize-3); i++)
			{
				nCheckSum += m_pApp->szCommRxBuff[i];
			}
			CString strCalChkSum;
			strCalChkSum.Format(_T("%02X"), nCheckSum);

			// Receive Check Sum값을 가져와서 비교한다.
			CString strRxChkSum;
			strRxChkSum.Format(_T("%c%c"), m_pApp->szCommRxBuff[nCommRxSize-3], m_pApp->szCommRxBuff[nCommRxSize-2]);

			// Check Sum값이 같으면 STX부터 ETX까지의 Packet Data를 전달한다.
			if(!strRxChkSum.Compare(strCalChkSum))
			{
				// Receive Buff에서 RX Receive Size 만큼의 Data를 TX Buff에 Copy한다.
				memcpy (TxBuff, m_pApp->szCommRxBuff, nCommRxSize);
				/////////////////////////////////////////////////////////////////
				// Packet Data를 처리한다.
				m_pApp->Gf_receivedPgAckInfo(TxBuff);
				/////////////////////////////////////////////////////////////////
			}
			// 다음 Packet 전송을 위하여 TxBuff를 Clear한다.
			memset (TxBuff, 0, sizeof(TxBuff));
			memset (m_pApp->szCommRxBuff, 0, sizeof(m_pApp->szCommRxBuff));

			break;
		}
		// Total Rx Size를 초기화 한다.
		m_pApp->m_nCommRxTotData = 0;

		// OK/NG 상관없이 하나의 Packet를 처리 완료했으면 Hex Receive Flag는 Clear한다.
		m_pApp->m_bRcvHex = false;
	}
	// Rx Receive Buff를 Cloear한다.
	memset (pBuff, 0x00, BUFF_SIZE);
	// Data전달 Buff를 Clear한다.
	memset (TxBuff, 0x00, sizeof(TxBuff));

	//*********************************************************************
	// Normal RS232C Receive
	// *********************************************************************

	return TRUE;
}


BOOL ThreadWatchCommParse2(CPortController* port_controller, char *pBuff)
{
	UINT nStP=0, nEdP=0;
	BYTE TxBuff[BUFF_SIZE] = {0,};
	UINT i;

	if(pBuff[0] == 0x02)
	{
		memset (m_pApp->szCommRxBuff2, 0, sizeof(m_pApp->szCommRxBuff2));
		sprintf_s((char*)m_pApp->szCommRxBuff2, BUFF_SIZE, "%s", pBuff);
	}
	else
	{
		sprintf_s((char*)m_pApp->szCommRxBuff2, BUFF_SIZE, "%s%s", m_pApp->szCommRxBuff2, pBuff);
	}

	if(strlen((char*)m_pApp->szCommRxBuff2) >= 16)
	{
		while(1)
		{			
			BOOL bStxIn=FALSE;
			BOOL bEtxIn=FALSE;
			BYTE nCheckSum=0;

			UINT nLength = (int)strlen(m_pApp->szCommRxBuff2);
			for(i=0; i<nLength; i++)
			{
				if(m_pApp->szCommRxBuff2[i] == 0x02)
				{
					bStxIn = TRUE;
					break;
				}
			}
			nStP = i;

			if(i==nLength)
			{
				memset (m_pApp->szCommRxBuff2, 0, sizeof(m_pApp->szCommRxBuff2));
				break;
			}

			for(; i<nLength; i++)
			{
				if(m_pApp->szCommRxBuff2[i] == 0x03)
				{
					bEtxIn = TRUE;
					break;
				}
			}
			nEdP = i;

			if((bStxIn==FALSE) || (bEtxIn==FALSE))	break;		

			memcpy (TxBuff, m_pApp->szCommRxBuff2+nStP, (nEdP-nStP)+1);

			m_pApp->Gf_receivedGFD250AckInfo(TxBuff);	

			memset (TxBuff, 0, sizeof(TxBuff));


			memcpy (TxBuff, (m_pApp->szCommRxBuff2+(nEdP-nStP)+1), (nLength - (nEdP-nStP)-1));
			memset (m_pApp->szCommRxBuff2, 0, BUFF_SIZE);
			sprintf_s((char*)m_pApp->szCommRxBuff2, BUFF_SIZE, "%s", TxBuff);

			memset (TxBuff, 0, sizeof(TxBuff));
		}
	}

	memset (pBuff, 0x00, BUFF_SIZE);
	memset (TxBuff, 0x00, sizeof(TxBuff));

	return TRUE;
}