#pragma once

/////////////////////////////////////////////////////////////////////////////
// User Define
#define ETH_ACK_PWR_WAIT_TIME		10000	// Power On/Off Receive Wait time : 10Sec
#define ETH_ACK_NOT_WAIT			0		// ACK를 기다리지 않음. : 0Sec
#define ETH_ACK_NOR_WAIT_TIME		2000	// Normal Control Receive Wait time : 2Sec
#define ETH_CONNECT_WAIT_TIME		2000	// Connect Wait time : 2Sec
#define MAX_SOCKET					255

#define SOC_SERVER_PLC				2


#define SOC_SERVER_MAX				255






class CSocketTCP
{
public:
	CSocketTCP(void);
	~CSocketTCP(void);

	void eth_setControlSID(int nSetSID);
	BYTE eth_SockInit();
	BOOL eth_Connection(char* ipAddr, int nPort);
	void eth_DisConnection();

	BOOL eth_PlcSendQuery(char *data, WORD nDataLen);
	bool eth_getPlcRcvPacket(char* szRcvPacket);
	int eth_getPlcRcvPacketSize();
	char* eth_getErrorCode();



public:
	SOCKADDR_IN servAddr;
	SOCKET hSocket[MAX_SOCKET];

	int nSID;					// Socket의 ID 번호.
	bool m_bCon[MAX_SOCKET];	// is Connection.
	bool m_bSoRcv[MAX_SOCKET];	// receive data 있음.

	char szPlcRcvData[4096];
	bool m_bPlcReconnectFlag;

	char szErrorCode[256];

	WORD rcvDataLen[MAX_SOCKET];

};

extern CSocketTCP* pSocketTcpApp;
