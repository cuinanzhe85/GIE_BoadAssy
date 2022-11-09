#pragma once

#include "SocketTcp.h"
/////////////////////////////////////////////////////////////////////////////
// User Define

class CSocketTcpApp
{
public:
	CSocketTcpApp(void);
	~CSocketTcpApp(void);

	CSocketTCP* pSocketTcp;

	//////////////////////////////////////////////////////////////////////
	// PLC Control Function
	BOOL tcp_plc_Connection(CString ipAddress, int nPort);
	BOOL tcp_plc_DisConnection();
	BOOL tcp_plc_SendQuery(char *data, WORD nDataLen);
	BOOL tcp_plc_GetReceivePacketData(char* szRcvPacket);
	int  tcp_plc_GetReceivePacketSize();
	BOOL tcp_plc_GetReconnectFlag();


};

extern CSocketTcpApp* lpSocketTcpApp;
