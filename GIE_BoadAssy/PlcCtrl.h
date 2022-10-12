#pragma once

class CPLCCtrl
{
public:
	CPLCCtrl();
	~CPLCCtrl();

	BOOL m_bPlcTcpConnect;
	BOOL plc_tcpConnection();
	BOOL plc_tcpIsConnection();
	BOOL plc_tcpDisConnection();

	int  plc_melsec_makePacketWrite(char* packet_buff, UINT addr, int dataLen, WORD* wszData);
	int  plc_melsec_makePacketRead(char* packet_buff, UINT addr, int dataLen);

	BOOL plc_sendInputPID(WORD* wData, int nLength);
	BOOL plc_sendPidWriteComplete();

	int m_nPlcDioRetry;

protected:


private:

};

