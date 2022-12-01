#include "stdafx.h"
#include "SocketTcp.h"
#include <winsock2.h>

/////////////////////////////////////////////////////////////////////////////
CSocketTCP* pSocketTcpApp;

/////////////////////////////////////////////////////////////////////////////
UINT ThreadSocketPLC(LPVOID pParam)
{
	CSocketTCP* pSocketTcp = (CSocketTCP*)pParam;
	int nLength=0;
	while(1)
	{
		pSocketTcp->rcvDataLen[SOC_SERVER_PLC] = recv(pSocketTcp->hSocket[SOC_SERVER_PLC], pSocketTcp->szPlcRcvData, sizeof(pSocketTcp->szPlcRcvData), 0);

		nLength = pSocketTcp->rcvDataLen[SOC_SERVER_PLC];

		if((nLength==0) || (nLength==-1) || (nLength==0xFFFF))
		{
			pSocketTcp->m_bPlcReconnectFlag = true;
			pSocketTcp->rcvDataLen[SOC_SERVER_PLC] = 0;
			Sleep(10);
			continue;
		}
		pSocketTcp->m_bPlcReconnectFlag = false;
		pSocketTcp->szPlcRcvData[nLength] = NULL;	// << NULL

		pSocketTcp->m_bSoRcv[SOC_SERVER_PLC] = true;
	}
}


/////////////////////////////////////////////////////////////////////////////
CSocketTCP::CSocketTCP(void)
{
	nSID = 0;
	memset(rcvDataLen, 0x00, sizeof(rcvDataLen));
}

CSocketTCP::~CSocketTCP(void)
{
	for(int i=0; i<SOC_SERVER_MAX; i++)
	{
		if(m_bCon[i])
		{
			shutdown(hSocket[i], SD_SEND);
		}
		closesocket(hSocket[i]);
	}

	WSACleanup();	// WSACleanup은 한번만 한다.
}


void CSocketTCP::eth_setControlSID(int nSetSID)
{
	nSID = nSetSID;
}

BYTE CSocketTCP::eth_SockInit()
{
	WORD wversionRequested;
	WSADATA wsadata;
	int err; 
	wversionRequested = MAKEWORD( 2, 2 ); 
	err = ::WSAStartup( wversionRequested, &wsadata );

	if ( err != 0 ) 
	{
		sprintf_s(szErrorCode, "WSAStartup Error");
		return -1;
	}
	if ( LOBYTE( wsadata.wVersion ) != 2 ||
		HIBYTE( wsadata.wVersion ) != 2 ) 
	{
		sprintf_s(szErrorCode, "wVersion invalid");
		return -1;
	}

	sprintf_s(szErrorCode, "Socket Initialize Complete");
	return 0;
}

// 소켓연결 실패 시 기다리는 시간을 줄이기 위한 함수.
BOOL CSocketTCP::eth_Connection(char* ipAddr, int nPort)
{
	int nTimeout=ETH_CONNECT_WAIT_TIME;

	if (0 != eth_SockInit())
	{
		//AfxMessageBox(_T("fucSockInit() Fail"));
		return FALSE;
	}

	hSocket[nSID]=socket(PF_INET, SOCK_STREAM, 0);

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_addr.s_addr=inet_addr(ipAddr);
	servAddr.sin_family=AF_INET;
	servAddr.sin_port=htons(nPort);

	ULONG nonBlk = TRUE;
	if(ioctlsocket(hSocket[nSID], FIONBIO, &nonBlk ) == SOCKET_ERROR)
	{
		//AfxMessageBox(_T("ioctlsocket1() Fail"));
		return FALSE;
	}

	int ret = connect(hSocket[nSID], (LPSOCKADDR)&servAddr, sizeof(servAddr));

	if(ret == SOCKET_ERROR && WSAGetLastError() != WSAEWOULDBLOCK)
	{
		//AfxMessageBox(_T("WSAGetLastError() Fail"));
		return FALSE;
	}

	fd_set fdset;
	FD_ZERO( &fdset );
	FD_SET( hSocket[nSID], &fdset );

	struct  timeval     timevalue;
	timevalue.tv_sec = nTimeout/1000;
	timevalue.tv_usec = 0;

	if(select(0, NULL, &fdset, NULL, &timevalue ) == SOCKET_ERROR)
	{
		//AfxMessageBox(_T("select() Fail"));
		return FALSE;
	}

	if ( !FD_ISSET( hSocket[nSID], &fdset ) )
	{       
		closesocket(hSocket[nSID]);
		hSocket[nSID] = INVALID_SOCKET;
		//AfxMessageBox(_T("FD_ISSET() Fail"));
		return FALSE;
	}

	nonBlk = FALSE;
	if(ioctlsocket(hSocket[nSID], FIONBIO, &nonBlk ) == SOCKET_ERROR)
	{
		//AfxMessageBox(_T("ioctlsocket2() Fail"));
		return FALSE;
	}

	//////////////////////////////////////////////////////////////
	// Socket Variable Init
	//////////////////////////////////////////////////////////////
	m_bCon[nSID] = true;
	m_bSoRcv[nSID] = false;

	memset(szPlcRcvData, 0x00, sizeof(szPlcRcvData));
	memset(szErrorCode, 0x00, sizeof(szErrorCode));

	//////////////////////////////////////////////////////////////
	// Socket Thread Start
	//////////////////////////////////////////////////////////////
	if(nSID==SOC_SERVER_PLC)				AfxBeginThread(ThreadSocketPLC, this);

	return TRUE;
}

void CSocketTCP::eth_DisConnection()
{
	// TODO: Add your control notification handler code here

	if(m_bCon[nSID]==true)
	{
		shutdown(hSocket[nSID], SD_SEND);
	}
	closesocket(hSocket[nSID]);

	m_bCon[nSID] = false;
}


/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
BOOL CSocketTCP::eth_PlcSendQuery(char *data, WORD nDataLen)
{
	int sendlength=0;

	// Receive Buff를 Clear 한다.
	rcvDataLen[SOC_SERVER_PLC] = 0;

	// Socket Send
	sendlength = send(hSocket[SOC_SERVER_PLC], data, nDataLen, 0);

	if(sendlength==0)	return FALSE;
	else				return TRUE;
}

bool CSocketTCP::eth_getPlcRcvPacket(char* szRcvPacket)
{
	if(rcvDataLen[SOC_SERVER_PLC]==0)
	{
		return false;
	}
	else
	{
		memcpy(szRcvPacket, szPlcRcvData, rcvDataLen[SOC_SERVER_PLC]);
		memset(szPlcRcvData, 0x00, sizeof(szPlcRcvData));

		rcvDataLen[SOC_SERVER_PLC] = 0;
		return true;
	}
}

int CSocketTCP::eth_getPlcRcvPacketSize()
{
	return rcvDataLen[SOC_SERVER_PLC];
}

char* CSocketTCP::eth_getErrorCode()
{
	return szErrorCode;
}

