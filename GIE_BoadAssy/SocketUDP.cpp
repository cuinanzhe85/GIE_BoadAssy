// UDPSocket.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#if (DEBUG_RECV_COUNT==1)
#include "GORTAutoAging.h"
#endif
#include "SocketUDP.h"
#include "ipHlpapi.h"

#pragma comment(lib, "ipHlpapi.lib")


// CSocketUDP
CSocketUDP::CSocketUDP()
{
	ZeroMemory(m_sendBuf, sizeof(m_sendBuf));
	ZeroMemory(m_recvBuf, sizeof(m_recvBuf));

	m_bEthernetInit		= TRUE;
	m_bUDPSendFail		= FALSE;
	m_recvSize			= 0;
	m_bIsContinueRecv	= FALSE;

	m_recvSocketAddr = new SOCKADDR_IN;
	m_recvSocketAddr->sin_family = AF_INET;
	m_recvSocketAddr->sin_port = htons(UDP_SOCKET_PORT);
	m_recvSocketAddr->sin_addr.s_addr = htonl(INADDR_ANY);
	//m_recvSocketAddr->sin_addr.s_addr = inet_addr("192.168.10.98"); 

#if (DEBUG_RECV_COUNT==1)
	lpInspWorkInfo		= m_pApp->GetInspWorkInfo();
#endif
}

CSocketUDP::~CSocketUDP()
{
	free(m_recvSocketAddr);
}

BOOL CSocketUDP::CreatSocket(UINT nSocketPort, int nSocketType)
{
	CString m_stError;

	ZeroMemory(m_sendBuf, sizeof(m_sendBuf)); // �����ʱ�ȭ

	//������ ����
//	if (!Create(nSocketPort, nSocketType, FD_READ|FD_WRITE|FD_OOB|FD_ACCEPT|FD_CONNECT|FD_CLOSE, _T("192.168.10.98")))
	if (!Create(nSocketPort, nSocketType))
	{ // ���� ������ �����ϸ�
		m_stError.Format(_T("Socket Create Fail -> %d"), GetLastError());
		AfxMessageBox(m_stError);
		return FALSE;
	}

	// ��ε� ĳ��Ʈ�� ���ϸ� �Ʒ� �߰� /////////////////////////////////////////////
	int flag=TRUE;
	int len, rflag;

	if (!SetSockOpt(SO_BROADCAST, &flag, sizeof(int)))
	{
		m_stError.Format(_T("SetSockOpt failed to set SO_BROADCAST:% d"), GetLastError());
		AfxMessageBox (m_stError);

		return FALSE;
	}

	len = sizeof(rflag);
	if (!GetSockOpt(SO_BROADCAST, &rflag, &len) && rflag == 0)
	{
		m_stError.Format(_T("GetSockOpt failed to get SO_BROADCAST:% d"), GetLastError());
		AfxMessageBox (m_stError);

		return FALSE;
	}
	//////////////////////////////////////////////////////////////////////////////

	return TRUE;
}

BOOL CSocketUDP::CloseSocket()
{
	Close();
	return TRUE;
}

void CSocketUDP::getLocalIPAddress()
{
	CString LocalIP1, LocalIP2;

	PIP_ADAPTER_INFO pAdapterInfo;
	DWORD dwRetVal = 0;
	BOOL m_bBreak = FALSE;

	pAdapterInfo = (IP_ADAPTER_INFO *)malloc(sizeof(IP_ADAPTER_INFO));
	unsigned long ulOutBufLen = sizeof(IP_ADAPTER_INFO);

	if(GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) != ERROR_SUCCESS)
	{
		//GlobalFree(pAdapterInfo);
		pAdapterInfo = (IP_ADAPTER_INFO*)malloc(ulOutBufLen);
	}

	if((dwRetVal=GetAdaptersInfo(pAdapterInfo, &ulOutBufLen)) == NO_ERROR)
	{
		m_strLocalIP1.Format (_T("%s"), char_To_wchar(pAdapterInfo->IpAddressList.IpAddress.String));

		if(m_strLocalIP1==_T("0.0.0.0"))
		{
			if(pAdapterInfo->IpAddressList.Next != NULL)
			{
				m_strLocalIP2.Format (_T("%s"), char_To_wchar(pAdapterInfo->IpAddressList.Next->IpAddress.String));
			}
		}
		else
		{
			if(pAdapterInfo->IpAddressList.Next != NULL)
			{
				m_strLocalIP2.Format (_T("%s"), char_To_wchar(pAdapterInfo->IpAddressList.Next->IpAddress.String));
			}
		}
	}
}

void CSocketUDP::getLocalGateWay()
{
	int gateway;
    DWORD dwStatus;
    IP_ADAPTER_INFO *pAdapterInfo = NULL;
    IP_ADAPTER_INFO *pOriginalPtr = NULL;
    ULONG ulSizeAdapterInfo = 0;
 
    dwStatus = GetAdaptersInfo(pAdapterInfo,&ulSizeAdapterInfo);
    //***********************************************************************
    //���� ���� �÷ο� �϶� ulSizeAdapterInfo ũ��� �޸𸮸� �Ҵ��ϰ� 
    //�ٽ� GetAdaptersInfo�� ȣ���Ѵ�.
    if( dwStatus == ERROR_BUFFER_OVERFLOW)
    {
        if(!(pAdapterInfo = (PIP_ADAPTER_INFO)malloc(ulSizeAdapterInfo)))
        {
            AfxMessageBox(_T("Get Gateway Address Error"));
        }
 
        dwStatus = GetAdaptersInfo(pAdapterInfo,&ulSizeAdapterInfo);
    }
 
    char Gageway_Addr[16];
 
	if(pAdapterInfo!=NULL)
	{
		for(int x=0; x<16; x++)
			Gageway_Addr[x] = pAdapterInfo->GatewayList.IpAddress.String[x];
	 
		gateway = inet_addr(pAdapterInfo->GatewayList.IpAddress.String);
		m_strGateway.Format(_T("%d.%d.%d.%d"), (gateway&0xFF), (gateway>>8&0xFF), (gateway>>16&0xFF), (gateway>>24&0xFF));
		free(pAdapterInfo);
	}
}

// CSocketUDP ��� �Լ�
void CSocketUDP::parseReceivePacket(int nRead, char* buf)
{
	int source, dest;
	CString recvpacket=_T("");

	// Receive Buff�� �������� NULL�� �־��ش�.		
	buf[nRead] = NULL;

	if(m_bIsContinueRecv==FALSE)
	{
		sscanf_s(&buf[PACKET_PT_SOURCE],"%02X", &source);
		sscanf_s(&buf[PACKET_PT_DEST],	"%02X", &dest);
		sscanf_s(&buf[PACKET_PT_CMD],	"%02X", &m_recvCommand);
		sscanf_s(&buf[PACKET_PT_LEN],	"%04X", &m_recvTotalLength);

		// �������� PC�� �ƴϸ� Return�Ѵ�.
		if(dest != TARGET_PC)	return;

		m_recvSize += nRead;
		if(m_recvSize >= (m_recvTotalLength+16))
		{
			memcpy(m_recvBuf, buf, m_recvSize);
			m_recvBuf[m_recvSize] = NULL;
		}
		else
		{
			memcpy(m_recvBuf, buf, m_recvSize);
			m_bIsContinueRecv = TRUE;

			// �� ���� Data�� �ִٸ� Message Send���� �ʰ�Retrun�Ѵ�.
			return;
		}
	}
	else
	{
		memcpy(&m_recvBuf[m_recvSize], buf, nRead);
		m_recvSize += nRead;
		if(m_recvSize < (m_recvTotalLength+16))
		{
			// �� ���� Data�� �ִٸ� Message Send���� �ʰ�Retrun�Ѵ�.
			return;
		}
	}

	// IPAddress�� Message ���� �����Ѵ�.
//	char szmsg[1024*8] = {0,};
//	sprintf_s(szmsg, "%s", szipa, m_recvBuf);
	AfxGetApp()->GetMainWnd()->SendMessage(WM_UDP_RECEIVE, (WPARAM)m_recvBuf, (LPARAM)m_recvSize);


	// ������ �ʱ�ȭ �Ѵ�.
	m_bIsContinueRecv = FALSE;
	m_recvSize = 0;
	m_recvCommand = 0;
	m_recvTotalLength = 0;
	ZeroMemory(m_recvBuf, sizeof(m_recvBuf));

}

void CSocketUDP::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	int dd=0;
	char buf[PACKET_SIZE]={0,};
	CString recvpacket=_T("");
	CString recvIP=_T("");
	int nRead, addrlen=sizeof(SOCKADDR);

	nRead=ReceiveFrom(buf, PACKET_SIZE, (SOCKADDR*)m_recvSocketAddr, &addrlen, 0);
	recvIP.Format(_T("%d.%d.%d.%d"),
					m_recvSocketAddr->sin_addr.S_un.S_un_b.s_b1,
					m_recvSocketAddr->sin_addr.S_un.S_un_b.s_b2,
					m_recvSocketAddr->sin_addr.S_un.S_un_b.s_b3,
					m_recvSocketAddr->sin_addr.S_un.S_un_b.s_b4
				);

	// Local Host IP�ּҿ��� ���۵� Packet�� ������.
	if((recvIP==m_strLocalIP1) || (recvIP==m_strLocalIP2) || (recvIP==LOCAL_HOST_IP))
		return;

#if (DEBUG_RECV_COUNT==1)
	lpInspWorkInfo->nDebugAckRecv++;
#endif

	switch(nRead)
	{
		case 0:
		{
			Close();
			break;
		}
		case SOCKET_ERROR:
		{
			if (GetLastError() != WSAEWOULDBLOCK) // WSAEWOULDBLOCK�̵Ǹ� �� ������
			{
				if(GetLastError() != WSAEMSGSIZE)
				{   // �Ϲ����� �ޱ� ����ó��
					CString stErr;
					stErr.Format(_T("�ޱ⿡��, LastError() Code => %d"), GetLastError());
					recvpacket.Format(_T("<<SOCKET RECEVIE FAIL>>   %s#%s"), recvIP, stErr);
				}
				else
				{
					recvpacket.Format(_T("<<SOCKET RECEVIE FAIL>>   %s#%s"), recvIP, _T("�����ͱ׷� ����� �ʹ�Ŀ�� �߷Ƚ��ϴ�."));
				}
				//AfxMessageBox(recvpacket, MB_ICONERROR);
			}
			break;
		}
		default: // ������ �ƴϸ�
		{
			if (nRead != SOCKET_ERROR && nRead != 0)
			{
				parseReceivePacket(nRead, buf);
			}
		}
	}

	CAsyncSocket::OnReceive(nErrorCode);	
}

BOOL CSocketUDP::SendToUDP(CString remoteIP, int length, char* m_sendPacket)
{
	int m_nBytesSent=0;
	int m_nBytesBufSize;

	m_nBytesBufSize = length;

	while(m_nBytesSent < m_nBytesBufSize)
	{
		int dwBytes;
		int sendlen;

		if((m_nBytesBufSize-m_nBytesSent) < 1450)
			sendlen = m_nBytesBufSize-m_nBytesSent;
		else
			sendlen = 1450;

		// SendTo(�����޽���, �޽���������, ������Ʈ, ����IP)
		dwBytes = SendTo((m_sendPacket+m_nBytesSent), sendlen, UDP_SOCKET_PORT, remoteIP);
		if(dwBytes == SOCKET_ERROR)
		{
			if (GetLastError() ==  WSAEWOULDBLOCK)
			{
				//Sleep(10);
				ProcessMessage();
				continue;;
			}
			else
			{
				Close();
				return FALSE;
			}
		}
		else // ������ �ȳ���
		{
			m_nBytesSent += dwBytes;
		}
	}

	ZeroMemory(m_sendBuf, sizeof(m_sendBuf));;

	return TRUE;
}
