
#include "stdafx.h"
#include "GIE_BoadAssy.h"

#include "PLCCtrl.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPLCCtrl::CPLCCtrl()
{
	m_nPlcDioRetry		= 0;
	m_bPlcTcpConnect	= FALSE;
}

CPLCCtrl::~CPLCCtrl()
{

}

BOOL CPLCCtrl::plc_tcpConnection()
{
	m_bPlcTcpConnect = m_pApp->m_pCommand->plc_Connection();
	return m_bPlcTcpConnect;
}

BOOL CPLCCtrl::plc_tcpIsConnection()
{
	return m_bPlcTcpConnect;
}

BOOL CPLCCtrl::plc_tcpDisConnection()
{
	return m_pApp->m_pCommand->plc_DisConnection();
}

int CPLCCtrl::plc_melsec_makePacketWrite(char* packet_buff, UINT addr, int dataLen, WORD* wszData)
{
	int packet_len=0;
	int requestDataLen=0;

	packet_len = 0;
	requestDataLen = 12 + (dataLen*2);	// 12는 고정길이 이며, Word Type이므로 DataLen * 2Byte가 된다.

	// 서브 머리글 구성 (6Byte)
	packet_buff[packet_len++]  = (BYTE)(MELSEC_SUB_HEAD >> 8);		// 서브 머리글
	packet_buff[packet_len++]  = (BYTE)(MELSEC_SUB_HEAD >> 0);

	packet_buff[packet_len++]  = (BYTE)MELSEC_NETWORK_NO;			// 네트워크 번호

	packet_buff[packet_len++]  = (BYTE)MELSEC_PLC_NO;				// PLC 번호

	packet_buff[packet_len++]  = (BYTE)(MELSEC_MODULE_IO_NO >> 0);	// 요구대상 모듈 I/O 번호
	packet_buff[packet_len++]  = (BYTE)(MELSEC_MODULE_IO_NO >> 8);

	packet_buff[packet_len++]  = (BYTE)MELSEC_MODULE_COUNTRY_NO;	// 요구대상 모듈 국 번호

	packet_buff[packet_len++]  = (BYTE)(requestDataLen >> 0);		// 요구Data 길이 (CPU감시 타이머 ~ Data 마지막 Byte까지의 Length)
	packet_buff[packet_len++]  = (BYTE)(requestDataLen >> 8);

	packet_buff[packet_len++]  = (BYTE)(MELSEC_CPU_TIMER >> 0);		// CPU 감시 타이머
	packet_buff[packet_len++]  = (BYTE)(MELSEC_CPU_TIMER >> 8);

	packet_buff[packet_len++]  = (BYTE)(MELSEC_CMD_WRITE >> 0);		// 커맨드
	packet_buff[packet_len++]  = (BYTE)(MELSEC_CMD_WRITE >> 8);

	packet_buff[packet_len++]  = (BYTE)(MELSEC_SUBCMD_WORD >> 0);	// 서브 커맨드
	packet_buff[packet_len++]  = (BYTE)(MELSEC_SUBCMD_WORD >> 8);

	packet_buff[packet_len++]  = (BYTE)(addr>>0);					// Write Address (24bit)
	packet_buff[packet_len++]  = (BYTE)(addr>>8);
	packet_buff[packet_len++]  = (BYTE)(addr>>16);

	packet_buff[packet_len++]  = (BYTE)MELSEC_CMD_DEVICE_CODE;		// 디바이스 코드

	packet_buff[packet_len++]  = (BYTE)(dataLen >> 0);				// Write Byte수
	packet_buff[packet_len++]  = (BYTE)(dataLen >> 8);

	for(int ptr=0; ptr<dataLen; ptr++)
	{
		packet_buff[packet_len++]  = (BYTE)(wszData[ptr]>>0);		// Write Data (첫번째 Data L)
		packet_buff[packet_len++]  = (BYTE)(wszData[ptr]>>8);		// Write Data (첫번째 Data H)
	}

	return packet_len;
}

int CPLCCtrl::plc_melsec_makePacketRead(char* packet_buff, UINT addr, int dataLen)
{
	int packet_len=0;
	int requestDataLen=0;

	packet_len = 0;
	requestDataLen = 12;	// 12는 고정길이

	// 서브 머리글 구성 (6Byte)
	packet_buff[packet_len++]  = (BYTE)(MELSEC_SUB_HEAD >> 8);		// 서브 머리글
	packet_buff[packet_len++]  = (BYTE)(MELSEC_SUB_HEAD >> 0);

	packet_buff[packet_len++]  = (BYTE)MELSEC_NETWORK_NO;			// 네트워크 번호

	packet_buff[packet_len++]  = (BYTE)MELSEC_PLC_NO;				// PLC 번호

	packet_buff[packet_len++]  = (BYTE)(MELSEC_MODULE_IO_NO >> 0);	// 요구대상 모듈 I/O 번호
	packet_buff[packet_len++]  = (BYTE)(MELSEC_MODULE_IO_NO >> 8);

	packet_buff[packet_len++]  = (BYTE)MELSEC_MODULE_COUNTRY_NO;	// 요구대상 모듈 국 번호

	packet_buff[packet_len++]  = (BYTE)(requestDataLen >> 0);		// 요구Data 길이 (CPU감시 타이머 ~ Data 마지막 Byte까지의 Length)
	packet_buff[packet_len++]  = (BYTE)(requestDataLen >> 8);

	packet_buff[packet_len++]  = (BYTE)(MELSEC_CPU_TIMER >> 0);		// CPU 감시 타이머
	packet_buff[packet_len++]  = (BYTE)(MELSEC_CPU_TIMER >> 8);

	packet_buff[packet_len++]  = (BYTE)(MELSEC_CMD_READ >> 0);		// 커맨드
	packet_buff[packet_len++]  = (BYTE)(MELSEC_CMD_READ >> 8);

	packet_buff[packet_len++]  = (BYTE)(MELSEC_SUBCMD_WORD >> 0);	// 서브 커맨드
	packet_buff[packet_len++]  = (BYTE)(MELSEC_SUBCMD_WORD >> 8);

	packet_buff[packet_len++]  = (BYTE)(addr>>0);					// Read Address (24bit)
	packet_buff[packet_len++]  = (BYTE)(addr>>8);
	packet_buff[packet_len++]  = (BYTE)(addr>>16);

	packet_buff[packet_len++]  = (BYTE)MELSEC_CMD_DEVICE_CODE;		// 디바이스 코드

	packet_buff[packet_len++]  = (BYTE)(dataLen >> 0);				// Read Byte수
	packet_buff[packet_len++]  = (BYTE)(dataLen >> 8);

	return packet_len;
}

BOOL CPLCCtrl::plc_sendInputPID(int deviceNum, WORD* wData, int nLength)
{
	char szPacket[1024] = { 0, };
	int packetLen = 0;
	UINT wAddr;

	if (deviceNum == 0)
		wAddr = PLC_PID_WRITE_START_ADDR_1;
	else
		wAddr = PLC_PID_WRITE_START_ADDR_2;

	packetLen = plc_melsec_makePacketWrite(szPacket, wAddr, nLength, wData);
	if (m_pApp->m_pCommand->plc_sendQuery(szPacket, packetLen) == FALSE)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPLCCtrl::plc_sendPidWriteComplete(int deviceNum, BOOL set_clear)
{
	char szPacket[1024] = { 0, };
	int packetLen = 0;
	WORD wData[1];
	UINT wAddr;

	if (deviceNum == 0)
		wAddr = PLC_PID_WRITE_COMPLETE_ADDR_1;
	else
		wAddr = PLC_PID_WRITE_COMPLETE_ADDR_2;

	if(set_clear == _CLEAR_)
		wData[0] = 0x0000;
	else if(set_clear == _SET_)
		wData[0] = 0x0001;

	packetLen = plc_melsec_makePacketWrite(szPacket, wAddr, 1, wData);
	if (m_pApp->m_pCommand->plc_sendQuery(szPacket, packetLen) == FALSE)
	{
		return FALSE;
	}

	return TRUE;
}



