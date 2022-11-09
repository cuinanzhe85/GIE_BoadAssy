#include "stdafx.h"

#include "SocketTcpApp.h"

/////////////////////////////////////////////////////////////////////////////
CSocketTcpApp* lpSocketTcpApp;

/////////////////////////////////////////////////////////////////////////////

CSocketTcpApp::CSocketTcpApp(void)
{
	pSocketTcp = new CSocketTCP;
}

CSocketTcpApp::~CSocketTcpApp(void)
{
	delete pSocketTcp;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
// TCP PLC Function
//////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL CSocketTcpApp::tcp_plc_Connection(CString ipAddress, int nPort)
{
	char szIPAddress[20] = { 0, };
	pSocketTcp->nSID = SOC_SERVER_PLC;
	pSocketTcp->m_bPlcReconnectFlag = false;

	sprintf_s(szIPAddress, "%S", ipAddress.GetBuffer(0));
	return pSocketTcp->eth_Connection(szIPAddress, nPort);
}

BOOL CSocketTcpApp::tcp_plc_DisConnection()
{
	pSocketTcp->nSID = SOC_SERVER_PLC;
	pSocketTcp->eth_DisConnection();

	return TRUE;
}

BOOL CSocketTcpApp::tcp_plc_SendQuery(char *data, WORD nDataLen)
{
	pSocketTcp->nSID = SOC_SERVER_PLC;
	return pSocketTcp->eth_PlcSendQuery(data, nDataLen);
}

BOOL CSocketTcpApp::tcp_plc_GetReceivePacketData(char* szRcvPacket)
{
	pSocketTcp->nSID = SOC_SERVER_PLC;
	return pSocketTcp->eth_getPlcRcvPacket(szRcvPacket);
}

int CSocketTcpApp::tcp_plc_GetReceivePacketSize()
{
	pSocketTcp->nSID = SOC_SERVER_PLC;
	return pSocketTcp->eth_getPlcRcvPacketSize();
}

BOOL CSocketTcpApp::tcp_plc_GetReconnectFlag()
{
	return pSocketTcp->m_bPlcReconnectFlag;
}

