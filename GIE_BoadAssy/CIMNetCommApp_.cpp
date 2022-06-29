#include "StdAfx.h"
#include "GIE_BoadAssy.h"

#include "atlbase.h"
#include "atlcom.h"
#include <string>

#include "CIMNetCommApp.h"


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Message Receive Class
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
const UINT SINK_ID = 1;

CString m_sReceiveMessage;
BOOL	m_nMessageReceiveFlag;


static _ATL_FUNC_INFO HandleTibRvMsgEvent = { CC_STDCALL, VT_EMPTY, 1, { VT_BSTR } };
static _ATL_FUNC_INFO HandleTibRvStateEvent = { CC_STDCALL, VT_EMPTY, 1, { VT_BSTR} };

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////


CCimNetCommApi::CCimNetCommApi(void)
{
	m_nMessageReceiveFlag	= 0;
	m_bIsGmesLocalTestMode	= FALSE;
	m_bIsEasLocalTestMode	= FALSE;
}


CCimNetCommApi::~CCimNetCommApi(void)
{
}

BOOL CCimNetCommApi::ConnectTibRv(int nServerType)
{
	CString sLog;

	if(nServerType == SERVER_MES)
	{
		VARIANT_BOOL resultConnect = gmes->Connect();

		if(resultConnect == VARIANT_TRUE)
		{
			sLog.Format(_T("MES Connection Succeeded"));
			m_pApp->Gf_writeLogData(_T("[INIT]"), sLog);

			m_pApp->m_bIsGmesConnect = TRUE;
			return TRUE;
		}
		else
		{
			sLog.Format(_T("MES Connection Retry"));
			m_pApp->Gf_writeLogData(_T("[INIT]"), sLog);

			resultConnect = gmes->Connect();

			if(resultConnect == VARIANT_TRUE)
			{
				sLog.Format(_T("MES Connection Succeeded"));
				m_pApp->Gf_writeLogData(_T("[INIT]"), sLog);

				m_pApp->m_bIsGmesConnect = TRUE;
				return TRUE;
			}
			else
			{
				sLog.Format(_T("MES Connection Fail"));
				m_pApp->Gf_writeLogData(_T("[INIT]"), sLog);

				m_pApp->m_bIsGmesConnect = FALSE;
			}
		}
	}

	else if(nServerType == SERVER_EAS)
	{
		VARIANT_BOOL resultConnect = eas->Connect();

		if(resultConnect == VARIANT_TRUE)
		{
			sLog.Format(_T("EAS Connection Succeeded"));
			m_pApp->Gf_writeLogData(_T("[INIT]"), sLog);

			m_pApp->m_bIsEasConnect = TRUE;
			return TRUE;
		}
		else
		{
			sLog.Format(_T("EAS Connection Retry"));
			m_pApp->Gf_writeLogData(_T("[INIT]"), sLog);

			resultConnect = eas->Connect();

			if(resultConnect == VARIANT_TRUE)
			{
				sLog.Format(_T("EAS Connection Succeeded"));
				m_pApp->Gf_writeLogData(_T("[INIT]"), sLog);

				m_pApp->m_bIsEasConnect = TRUE;
				return TRUE;
			}
			else
			{
				sLog.Format(_T("EAS Connection Fail"));
				m_pApp->Gf_writeLogData(_T("[INIT]"), sLog);

				m_pApp->m_bIsEasConnect = FALSE;
			}
		}
	}

	return FALSE;
}

BOOL CCimNetCommApi::CloseTibRv(int nServerType)
{
	if(nServerType == SERVER_MES)
	{
		VARIANT_BOOL resultDisConnect = gmes->Terminate();

		if(resultDisConnect == VARIANT_TRUE)
			return TRUE;
	}
	else if(nServerType == SERVER_EAS)
	{
		VARIANT_BOOL resultDisConnect = eas->Terminate();

		if(resultDisConnect == VARIANT_TRUE)
			return TRUE;
	}

	return FALSE;
}

void CCimNetCommApi::getLocalSubjectIPAddress()

{	// Add 'ws2_32.lib' to your linker options

	WSADATA WSAData;
	CString sLog;
	m_strLocalSubjectIP = (_T(""));

 	if(m_bIsGmesLocalTestMode==FALSE)
	{
		m_strLocalSubject = (_T(""));
		m_strLocalSubjectMesF = (_T(""));
		m_strLocalSubjectEasF = (_T(""));
	}

	// Initialize winsock dll
	if(::WSAStartup(MAKEWORD(1, 0), &WSAData))
	{
		sLog.Format(_T("Winsock dll Initialize Fail"));
		m_pApp->Gf_writeLogData(_T("[ERROR]"), sLog);
	}

	// Get local host name
	char szHostName[128] = "";

	if(::gethostname(szHostName, sizeof(szHostName)))
	{
		sLog.Format(_T("Get Local Host Name Error"));
		m_pApp->Gf_writeLogData(_T("[ERROR]"), sLog);
	}

	// Get local IP addresses
	struct sockaddr_in SocketAddress;
	struct hostent     *pHost        = 0;

	pHost = ::gethostbyname(szHostName);
	if(!pHost)
	{
		sLog.Format(_T("Get Local IP Addresses Error"));
		m_pApp->Gf_writeLogData(_T("[ERROR]"), sLog);
	}

	char aszIPAddresses[20]; // maximum of ten IP addresses


	for(int iCnt = 0; ((pHost->h_addr_list[iCnt]) && (iCnt < 10)); ++iCnt)
	{
		memcpy(&SocketAddress.sin_addr, pHost->h_addr_list[iCnt], pHost->h_length);
		sprintf_s(aszIPAddresses, "%s", inet_ntoa(SocketAddress.sin_addr));

		if(aszIPAddresses[0] == '1' && aszIPAddresses[1] == '0' && aszIPAddresses[2] =='.')
		{
			m_strLocalSubjectIP.Format(_T("%s"), char_To_wchar(aszIPAddresses));
			sLog.Format(_T("STATION Local IP Addresses = %s"), m_strLocalSubjectIP);
			m_pApp->Gf_writeLogData(_T("[INIT]"), sLog);
			break;
		}
	}

	// Cleanup
	WSACleanup();

}

BOOL CCimNetCommApi::Init(int nServerType)
{
	CString sLog;

	// Host 접속 정보를 가져온다.
	if(nServerType == SERVER_MES){

		CoInitialize(NULL);

		getLocalSubjectIPAddress();

		SetMesHostInterface();

		if(m_bIsGmesLocalTestMode==FALSE)
		{
			m_strLocalSubjectMesF.Format(_T("%s.%s"), m_strLocalSubject, m_strLocalSubjectIP);
		}
		else
		{
			m_strLocalSubjectMesF.Format(_T("%s"), m_strLocalSubject);
		}

		HRESULT mesHr = CoCreateInstance(CLSID_DllGmes, NULL, CLSCTX_INPROC_SERVER, IID_ICallGmesClass, reinterpret_cast<void**>(&gmes));

		if (SUCCEEDED(mesHr)){

			gmes->SetTimeOut(20);

			VARIANT_BOOL resultIni = gmes->Init(
				(_bstr_t)m_strServicePort,
				(_bstr_t)m_strNetwork,
				(_bstr_t)m_strDaemon,
				(_bstr_t)m_strRemoteSubject,
				(_bstr_t)m_strLocalSubjectMesF
				);

			if(resultIni == VARIANT_TRUE)
				return TRUE;

		}

		m_pApp->Gf_writeLogData("[INIT]", "MES MES TIB INIT Fail");
		return FALSE;
	}
	else if(nServerType == SERVER_EAS)
	{

		SetEasHostInterface();

		if(m_bIsEasLocalTestMode==FALSE)
		{
			m_strLocalSubjectEasF.Format(_T("%s.%s"), m_strLocalSubjectEAS, m_strLocalSubjectIP);
		}
		else
		{
			m_strLocalSubjectEasF.Format(_T("%s"), m_strLocalSubjectEAS);
		}

		HRESULT easHr = CoCreateInstance(CLSID_DllEas, NULL, CLSCTX_INPROC_SERVER, IID_ICallEASClass, reinterpret_cast<void**>(&eas));

		if (SUCCEEDED(easHr)) {

			eas->SetTimeOut(20);

			VARIANT_BOOL resultIni = eas->Init(
				(_bstr_t)m_strServicePortEAS,
				(_bstr_t)m_strNetworkEAS,
				(_bstr_t)m_strDaemonEAS,
				(_bstr_t)m_strRemoteSubjectEAS,
				(_bstr_t)m_strLocalSubjectEasF
				);

			if(resultIni == VARIANT_TRUE)
				return TRUE;

		}

		sLog.Format(_T("EAS TIB INIT Fail"));
		m_pApp->Gf_writeLogData(_T("[INIT]"), sLog);
		return FALSE;
	}

	return FALSE;
}

BOOL CCimNetCommApi::MessageSend (int nMode)	// Event
{
	_bstr_t bstBuff = (LPSTR)(LPCTSTR) m_strRemoteSubject;
	BSTR m_remoteTemp = bstBuff.copy ();
	//	_bstr_t m_remoteTemp = bstBuff.copy ();

	CString strBuff (_T (""));
	CString sLog;

	switch (nMode)
	{
	case ECS_MODE_EAYT:
		m_strHostSendMessage = m_strEAYT;
		break;
	case ECS_MODE_UCHK:
		m_strHostSendMessage = m_strUCHK;
		break;
	case ECS_MODE_EDTI:
		m_strHostSendMessage = m_strEDTI;
		break;
	case ECS_MODE_FLDR:
		m_strHostSendMessage = m_strFLDR;
		break;
	case ECS_MODE_PCHK:
		m_strHostSendMessage = m_strPCHK;
		break;
	case ECS_MODE_EICR:
		m_strHostSendMessage = m_strEICR;
		break;
	case ECS_MODE_APDR:
		m_strHostSendMessage = m_strAPDR;
		break;
	case ECS_MODE_WDCR:
		m_strHostSendMessage = m_strWDCR;
		break;
	case ECS_MODE_AGCM:
		m_strHostSendMessage = m_strAGCM;
		break;
	case ECS_MODE_AGN_IN:
		m_strHostSendMessage = m_strAGNIN;
		break;
	case ECS_MODE_AGN_OUT:
		m_strHostSendMessage = m_strAGNOUT;
		break;
	default:
		return RTN_MSG_NOT_SEND;	// 통신 NG
	}

	m_pApp->Gf_writeLogData(_T("[HOST_S]"), m_strHostSendMessage);
	m_strHostRecvMessage.Format(_T("EMPTY"));

	Sleep (10);
	if(nMode != ECS_MODE_APDR)
	{
		VARIANT_BOOL bRetCode = gmes->SendTibMessage((_bstr_t)m_strHostSendMessage);
		do
		{
			if(gmes->GetreceivedDataFlag() == VARIANT_TRUE)
			{
				m_sReceiveMessage = (LPCTSTR)gmes->GetReceiveData();
				break;
			}
			if(bRetCode == VARIANT_FALSE)
			{
				m_pApp->Gf_writeLogData("[HOST_S]", "Did not send a MES Message. Retry !!!");
				break;
			}

		}while(1);


		if(bRetCode == VARIANT_FALSE)
		{

			bRetCode = gmes->SendTibMessage((_bstr_t)m_strHostSendMessage);

			m_pApp->Gf_writeLogData(_T("[HOST_S]"), m_strHostSendMessage);

			do{
				if(gmes->GetreceivedDataFlag() == VARIANT_TRUE){
					m_sReceiveMessage = (LPCTSTR)gmes->GetReceiveData();
					break;
				}
				if(bRetCode == VARIANT_FALSE){

					AfxMessageBox (_T ("Did not send a message !!!"));
					return RTN_MSG_NOT_SEND;	// 통신 NG
				}

			}while(1);
		}

	}
	else
	{
		VARIANT_BOOL bRetCode = eas->SendTibMessage((_bstr_t)m_strHostSendMessage);

		do{
			if(eas->GetreceivedDataFlag() == VARIANT_TRUE){
				m_sReceiveMessage = (LPCTSTR)eas->GetReceiveData();
				break;
			}
			if(bRetCode == VARIANT_FALSE)
			{
				m_pApp->Gf_writeLogData("[HOST_S]", "Did not send a EAS Message. Retry !!!");
				break;
			}

		}while(1);

		if(bRetCode == VARIANT_FALSE){

			bRetCode = eas->SendTibMessage((_bstr_t)m_strHostSendMessage);

			m_pApp->Gf_writeLogData(_T("[HOST_S]"), m_strHostSendMessage);

			do{
				if(eas->GetreceivedDataFlag() == VARIANT_TRUE){
					m_sReceiveMessage = (LPCTSTR)eas->GetReceiveData();
					break;
				}
				if(bRetCode == VARIANT_FALSE){

					AfxMessageBox (_T ("Did not send a message !!!"));
					return RTN_MSG_NOT_SEND;	// 통신 NG
				}

			}while(1);
		}
	}

	m_strHostRecvMessage = m_sReceiveMessage;

	return RTN_OK;		// normal...
}

BOOL CCimNetCommApi::MessageReceive() 
{
	if(m_sReceiveMessage.IsEmpty() == TRUE)
		return FALSE;

	m_strHostRecvMessage.Format(_T("%s"), m_sReceiveMessage);
	m_nMessageReceiveFlag = 1;

	return TRUE;
}

void CCimNetCommApi::MakeClientTimeString ()
{
	CString strBuff;
	CTime time = CTime::GetCurrentTime ();

	strBuff.Format(_T("%04d%02d%02d%02d%02d%02d"),
		time.GetYear (),
		time.GetMonth (),
		time.GetDay (),
		time.GetHour (),
		time.GetMinute (),
		time.GetSecond ()
		);

	m_strClientDate.Format (_T("%s"), strBuff);
}

BOOL CCimNetCommApi::GetFieldData (CString* pstrReturn, TCHAR* wszToken, int nMode)
{
 	char * pszBuff = new char [2048];
 	ZeroMemory (pszBuff, 2048);
 
//	m_strHostRecvMessage.Format(_T("PCHK_R ADDR=M2.G3.EQP.MOD.172_25_54_230,M2.G3.EQP.MOD.172_25_54_230  EQP=M2AMAL51BE01 PID=P8YG64000C17B1 SERIAL_NO= BLID=[] PPALLET= SKD_BOX_ID= USER_ID=670138 MODE=AUTO CLIENT_DATE=20160619022242 COMMENT=[] RTN_CD=0 ERR_MSG_LOC=[] ERR_MSG_ENG=[] HOST_DATE=20160619022244  RTN_PID=P8YG64000C17B1 RTN_SERIAL_NO=770F5P1X000RF RTN_BLID=[] RTN_PCBID=[] MODEL=LC770LQD-LGP3-X31-B GRADE=FIRST_CLASS LANE=2 REMARK=[] BUYER=[LGE] PF=P RWK_CD= RWK_DESC=[] QA_LOT_ID= EXPECTED_RWK= AGING_RWK= AGING_RWK_DESC=[] CVD_POS=[] PD_POS=[] PXL_CD= CELL_GAP= USD=[] LAMP_LOT_NO=[] CUSTOMER_GROUP_CODE= CUSTOMER_LABEL_ID= VTH_PREVALUE=-.0854481 CURRENT_VTH_COUNT=0 TOTAL_VTH_COUNT=7 BD_INFO=[90:0:GB_LV] WDR_INFO=[0:0:R:90W:LCM] FNI_CODE=FNI1 DEPOSITION_GROUP=065_01_41_16_SP081024 TOP_MODEL_NAME=LC770LQD-LGP3-X31-B LASER_REPAIR_COUNT=2"));
//	m_strHostRecvMessage.Format(_T("PCHK_R ADDR=M2.G3.EQP.MOD.172_25_55_39,M2.G3.EQP.MOD.172_25_55_39 EQP=M2AMALAVBE04 PID=P8SP67018G14A1 SERIAL_NO= BLID= PPALLET=B1067 SKD_BOX_ID= USER_ID=x070400103 MODE=AUTO CLIENT_DATE=20160906001553 COMMENT=[] RTN_CD=0 ERR_MSG_LOC=[] ERR_MSG_ENG=[] HOST_DATE=20160906001554  RTN_PID=P8SP67018G14A1 RTN_SERIAL_NO=650F9P1Y00A9K RTN_BLID=[] RTN_PCBID=[] MODEL=LC650AQD-GJA8-Y31-B GRADE=FIRST_CLASS LANE=3 REMARK=[] BUYER=[LGE] PF=P RWK_CD= RWK_DESC=[] QA_LOT_ID= EXPECTED_RWK= AGING_RWK= AGING_RWK_DESC=[] CVD_POS=[] PD_POS=[] PXL_CD= CELL_GAP= USD=[] LAMP_LOT_NO=[] CUSTOMER_GROUP_CODE= CUSTOMER_LABEL_ID= VTH_PREVALUE= CURRENT_VTH_COUNT=0 TOTAL_VTH_COUNT=0 BD_INFO=[] WDR_INFO=[7768:756:R:90W:LCM,10913:1017:W:90V:CELL,10941:1057:W:90V:CELL] FNI_CODE=FNI1 DEPOSITION_GROUP=065_01_41_16_SP081024 TOP_MODEL_NAME=LC650AQD-GJA8-Y31-B LASER_REPAIR_COUNT=0"));
//	m_strHostRecvMessage.Format(_T("PCHK_R ADDR=M2.G3.EQP.MOD.172_25_54_230,M2.G3.EQP.MOD.172_25_54_230  EQP=M2AMAL51G001 PID= SERIAL_NO=770FAP5X000BD BLID=[] PPALLET= SKD_BOX_ID= USER_ID=744995 MODE=AUTO CLIENT_DATE=20161027103836 COMMENT=[] RTN_CD=0 ERR_MSG_LOC=[] ERR_MSG_ENG=[] HOST_DATE=20161027103838  RTN_PID=P8Y369000209B1 RTN_SERIAL_NO=770FAP5X000BD RTN_BLID=[] RTN_PCBID=[] MODEL=LC770AQP-AKA3-X31-S GRADE=FIRST_CLASS LANE=1 REMARK=[] BUYER=[SONY E] PF=P RWK_CD= RWK_DESC=[] QA_LOT_ID= EXPECTED_RWK= AGING_RWK= AGING_RWK_DESC=[] CVD_POS=[458:251] PD_POS=[] PXL_CD= CELL_GAP= USD=[] LAMP_LOT_NO=[] CUSTOMER_GROUP_CODE= CUSTOMER_LABEL_ID= BD_INFO=[3121:1228:ADPD3_WHITE,145:0:GB_LV,3122:1228:ADPD3_WHITE,3119:1229:ADPD3_WHITE,3120:1229:ADPD3_WHITE,3071:1230:ADPD3_WHITE,3115:1230:ADPD3_WHITE,3117:1230:ADPD3_WHITE,3119:1230:ADPD3_WHITE,3069:1232:ADPD3_WHITE,3071:1232:ADPD3_WHITE,3071:1219:ADPD3_WHITE,3099:1232:ADPD3_WHITE,3070:1233:ADPD3_WHITE,3122:1233:ADPD3_WHITE,3069:1234:ADPD3_WHITE,3070:1234:ADPD3_WHITE,3073:1234:ADPD3_WHITE,3089:1234:ADPD3_WHITE,3059:1235:ADPD3_WHITE,3070:1235:ADPD3_WHITE,3071:1235:ADPD3_WHITE,3069:1220:ADPD3_WHITE,3073:1235:ADPD3_WHITE,3074:1235:ADPD3_WHITE,3067:1236:ADPD3_WHITE,3070:1236:ADPD3_WHITE,3073:1236:ADPD3_WHITE,3099:1236:ADPD3_WHITE,3102:1236:ADPD3_WHITE,3064:1237:ADPD3_WHITE,3067:1237:ADPD3_WHITE,3068:1237:ADPD3_WHITE,3071:1220:ADPD3_WHITE,3071:1237:ADPD3_WHITE,3078:1237:ADPD3_WHITE,3099:1237:ADPD3_WHITE,3123:1237:ADPD3_WHITE,3060:1238:ADPD3_WHITE,3061:1238:ADPD3_WHITE,3064:1238:ADPD3_WHITE,3067:1238:ADPD3_WHITE,3068:1238:ADPD3_WHITE,3069:1238:ADPD3_WHITE,3073:1220:ADPD3_WHITE,3070:1238:ADPD3_WHITE,3071:1238:ADPD3_WHITE,3073:1238:ADPD3_WHITE,3059:1239:ADPD3_WHITE,3068:1239:ADPD3_WHITE,3069:1239:ADPD3_WHITE,3070:1239:ADPD3_WHITE,3071:1239:ADPD3_WHITE,3073:1239:ADPD3_WHITE,3125:1239:ADPD3_WHITE,3067:1222:ADPD3_WHITE,3065:1240:ADPD3_WHITE,3068:1240:ADPD3_WHITE,3070:1240:ADPD3_WHITE,3071:1240:ADPD3_WHITE,3072:1240:ADPD3_WHITE,3073:1240:ADPD3_WHITE,3074:1240:ADPD3_WHITE,3075:1240:ADPD3_WHITE,3077:1240:ADPD3_WHITE,3078:1240:ADPD3_WHITE,3057:1226:ADPD3_WHITE,3081:1240:ADPD3_WHITE,3085:1240:ADPD3_WHITE,3116:1240:ADPD3_WHITE,3122:1240:ADPD3_WHITE,3125:1240:ADPD3_WHITE,3066:1241:ADPD3_WHITE,3069:1241:ADPD3_WHITE,3072:1241:ADPD3_WHITE,3073:1241:ADPD3_WHITE,3074:1241:ADPD3_WHITE,3070:1226:ADPD3_WHITE,3076:1241:ADPD3_WHITE,3061:1242:ADPD3_WHITE,3063:1242:ADPD3_WHITE,3066:1242:ADPD3_WHITE,3067:1242:ADPD3_WHITE,3068:1242:ADPD3_WHITE,3069:1242:ADPD3_WHITE,3070:1242:ADPD3_WHITE,3071:1242:ADPD3_WHITE,3073:1242:ADPD3_WHITE,3118:1226:ADPD3_WHITE,3074:1242:ADPD3_WHITE,3075:1242:ADPD3_WHITE,3077:1242:ADPD3_WHITE,3098:1242:ADPD3_WHITE,3099:1242:ADPD3_WHITE,3123:1242:ADPD3_WHITE,3057:1243:ADPD3_WHITE,3059:1243:ADPD3_WHITE,3068:1243:ADPD3_WHITE,3069:1243:ADPD3_WHITE] WDR_INFO=[2100:505:R:90W:TFT,250:457:B:90W:TFT,260:1675:R:90W:TFT,5787:1520:G:90W:TFT,9372:1071:R:90W:TFT,10933:1102:W:90V:CELL,10933:1107:W:90V:CELL,10941:1103:W:90V:CELL,15009:433:W:90W:TFT] FNI_CODE=FNI1 DEPOSITION_GROUP=077_01_31_16_Y3100224 TOP_MODEL_NAME=LC770AQP-AKA3-X31-S LASER_REPAIR_COUNT=0"));
	// - default ng 로 셋팅.  
	m_strNgComment.Format (_T ("0"));
	CString strBuff;
 	if (0 == nMode)
 	{
 		strBuff.Format (m_strHostRecvMessage);
 		pstrReturn->Empty();
 	}
 	else
 	{
 		strBuff.Format(_T("%s"), *pstrReturn);
 	}
 
 	int nPos = strBuff.Find (wszToken, 0);
 
	if (0 > nPos)
	{
		// no data
		delete[] pszBuff;
		return TRUE;
	}

	char temp [2] = {0,};
	// TOKEN=DATA	 // 'D' s position
	//       _       

	int nStartPos = nPos + (int)wcslen(wszToken) + 1;
	int nEndPos= 0;

	switch (strBuff.GetAt (nStartPos))
	{
		case '0':
		{
			//DEPOSITION_GROUP 정보는 0으로 시작 할수 있다.20160907
			if (!wcscmp (wszToken, _T("DEPOSITION_GROUP")))
			{
				nEndPos = strBuff.Find (' ', nStartPos);

				if (nEndPos <= 0)
				{
					nEndPos = strBuff.GetLength ();
				}
				else
				{
				}

				pstrReturn->Format(_T("%s"), strBuff.Mid (nStartPos, nEndPos-nStartPos));
				break;
			}

			if (!wcscmp (wszToken, _T("RTN_CD")))
			{
				m_strNgComment.Format (_T("0"));	// normal 로 셋팅.

				if (pstrReturn->GetLength() <= 0)
				{
					pstrReturn->Format(_T("%s"), m_strNgComment);
				}

				delete [] pszBuff;
				return FALSE;	// ng 없음. - 통신 정상. ex) RTN_CD=0
			}

			// ng....error string 내의 첫 byte 가 char 0 이라는 의미...
			// 발생 가능성 매우 희박함.
			if (pstrReturn->GetLength() <= 0)
			{
				pstrReturn->Format(_T("%s"), m_strNgComment);
			}

			delete [] pszBuff;
			return FALSE;

		} break;

		case '[':
		{
			// [ 로 묶여진 error, error 내용안에 space 가 포함될수 있음.

			nEndPos = strBuff.Find (']', nStartPos);
			if (0 >= nEndPos)
			{
				nEndPos = strBuff.GetLength ();
			}
			else
			{
			}

			// 2009. 02. 22
			pstrReturn->Format(_T("%s"), strBuff.Mid (nStartPos+1, (nEndPos-nStartPos)-1));
		} break;

 		default :
 		{
 			// [ ] 가 없는 error messgae... 
 			// 에러내용 안에 space 가 포함될수 없으므로 space 를 token 으로 다시 data 검색..
 
 			nEndPos = strBuff.Find (' ', nStartPos);

			if (nEndPos <= 0)
			{
				nEndPos = strBuff.GetLength ();
			}
			else
			{
			}

 			pstrReturn->Format(_T("%s"), strBuff.Mid (nStartPos, nEndPos-nStartPos));
 		} break;
 	}

	if (m_strNgComment.GetLength() <= 0)
	{
		pstrReturn->Format(_T("%s"), m_strNgComment);
	}
 	delete[] pszBuff;

	return FALSE;
}

CString CCimNetCommApi::GetHostSendMessage()
{
	return m_strHostSendMessage;
}

CString CCimNetCommApi::GetHostRecvMessage()
{
	return m_strHostRecvMessage;
}

void CCimNetCommApi::SetMesHostInterface()
{
	CString strbuf;

	if(m_bIsGmesLocalTestMode==TRUE)	return;

	Read_GmesFile(_T("VH"), _T("SERVICE_PORT"),		&m_strServicePort);
	Read_GmesFile(_T("VH"), _T("HOST_IP"),			&m_strNetwork);
	Read_GmesFile(_T("VH"), _T("DAEMON_PORT"),		&m_strDaemon);
	Read_GmesFile(_T("VH"), _T("LOCAL_SUBJECT"),	&m_strLocalSubject);
	Read_GmesFile(_T("VH"), _T("REMOTE_SUBJECT"),	&m_strRemoteSubject);
	Read_GmesFile(_T("VH"), _T("LOCAL_IP"),			&m_strLocalIP);
}

void CCimNetCommApi::SetEasHostInterface()
{

	if(m_bIsEasLocalTestMode==TRUE)	return;

	Read_GmesFile(_T("EAS"),	_T("EAS_SERVICE"),			&m_strServicePortEAS);
	Read_GmesFile(_T("EAS"),	_T("EAS_NETWORK"),			&m_strNetworkEAS);
	Read_GmesFile(_T("EAS"),	_T("EAS_DAEMON_PORT"),		&m_strDaemonEAS);
	Read_GmesFile(_T("EAS"),	_T("EAS_LOCAL_SUBJECT"),	&m_strLocalSubjectEAS);
	Read_GmesFile(_T("EAS"),	_T("EAS_REMOTE_SUBJECT"),	&m_strRemoteSubjectEAS);
	Read_GmesFile(_T("EAS"),	_T("EAS_LOCAL_IP"),			&m_strLocalIPEAS);
}

void CCimNetCommApi::SetLocalTest(int nServerType)
{
	if(nServerType==SERVER_MES)
	{
		m_bIsGmesLocalTestMode	= TRUE;

		m_strLocalSubject	= (_T("EQP.TEST"));
		m_strNetwork		= (_T(""));
		m_strRemoteSubject	= (_T("MES.TEST"));
		m_strServicePort	= (_T("7600"));
		m_strDaemon			= (_T("tcp::7600"));
	}
	else if(nServerType==SERVER_EAS)
	{
		m_bIsEasLocalTestMode	= TRUE;

		m_strLocalSubjectEAS	= (_T("EQP.TEST"));
		m_strNetworkEAS			= (_T(""));
		m_strRemoteSubjectEAS	= (_T("MES.TEST"));
		m_strServicePortEAS		= (_T("7800"));
		m_strDaemonEAS			= (_T("tcp::7800"));
	}
}

void CCimNetCommApi::SetLocalTimeData (CString strTime)
{

	SYSTEMTIME HostTime;

	TCHAR rdata[250];

	// Host 시간과 동기화
	GetLocalTime(&HostTime);

	rdata[0]=strTime.GetAt(0);
	rdata[1]=strTime.GetAt(1);
	rdata[2]=strTime.GetAt(2);
	rdata[3]=strTime.GetAt(3);
	rdata[4]=NULL;
	HostTime.wYear = _ttoi(rdata);

	rdata[0]=strTime.GetAt(4);
	rdata[1]=strTime.GetAt(5);
	rdata[2]=NULL;
	HostTime.wMonth = _ttoi(rdata);

	rdata[0]=strTime.GetAt(6);
	rdata[1]=strTime.GetAt(7);
	rdata[2]=NULL;
	HostTime.wDay = _ttoi(rdata);

	rdata[0]=strTime.GetAt(8);
	rdata[1]=strTime.GetAt(9);
	rdata[2]=NULL;
	HostTime.wHour = _ttoi(rdata);

	rdata[0]=strTime.GetAt(10);
	rdata[1]=strTime.GetAt(11);
	rdata[2]=NULL;
	HostTime.wMinute = _ttoi(rdata);

	rdata[0]=strTime.GetAt(12);
	rdata[1]=strTime.GetAt(13);
	rdata[2]=NULL;
	HostTime.wSecond = _ttoi(rdata);

	HostTime.wMilliseconds = 0;

	SetLocalTime(&HostTime);
}

void CCimNetCommApi::SetMachineName (CString strBuff)
{
	m_strMachineName.Format(_T("%s"), strBuff);
}

void CCimNetCommApi::SetUserId (CString strBuff)
{
	m_strUserID.Format(_T("%s"), strBuff);
}

void CCimNetCommApi::SetRwkCode(CString strBuff)
{
	m_strRwkCode.Format(_T("%s"), strBuff);
}

void CCimNetCommApi::SetFLDRFileName(CString strBuff)
{
	m_strFLDRFileName.Format(_T("%s"), strBuff);
}

void CCimNetCommApi::SetPanelID (CString strBuff)
{
	m_strPanelID.Format(_T("%s"), strBuff);
}

void CCimNetCommApi::SetPCBID (CString strBuff)
{
	m_strPCBID.Format(_T("%s"), strBuff);
}

void CCimNetCommApi::SetChannelID (CString strBuff)
{
	m_strChannelID.Format(_T("%s"), strBuff);
}

void CCimNetCommApi::SetBLID (CString strBuff)
{
	m_strBLID.Format(_T("%s"), strBuff);
}

void CCimNetCommApi::SetSerialNumber (CString strBuff)
{
	m_strSerialNumber.Format(_T("%s"), strBuff);
}

void CCimNetCommApi::SetModelName (CString strBuff)
{
	m_strModelName.Format(_T("%s"), strBuff);
}

void CCimNetCommApi::SetPalletID (CString strBuff)
{
	m_strPalletID.Format(_T("%s"), strBuff);
}

void CCimNetCommApi::SetPF (CString strBuff)
{
	m_strPF.Format(_T("%s"), strBuff);
}

void CCimNetCommApi::SetDefectPattern (CString strBuff)
{
	m_strDefectPattern.Format(_T("%s"), strBuff);
}

void CCimNetCommApi::SetPvcomAdjustValue(CString strBuff)
{
	m_strPvcomAdjustValue.Format(_T("%s"), strBuff);
}

void CCimNetCommApi::SetPvcomAdjustDropValue(CString strBuff)
{
	m_strPvcomAdjustDropValue.Format(_T("%s"), strBuff);
}

void CCimNetCommApi::SetPatternInfo(CString strBuff)
{
	m_strPatternInfo.Format(_T("%s"), strBuff);
}

void CCimNetCommApi::SetEdidStatus(CString strBuff)
{
	m_strEdidStatus.Format(_T("%s"), strBuff);
}

void CCimNetCommApi::SetOverHaulFlag(CString strBuff)
{
	m_strOverHaulFlag.Format(_T("%s"), strBuff);
}

void CCimNetCommApi::SetBaExiFlag(CString strBuff)
{
	m_strBaExiFlag.Format(_T("%s"), strBuff);
}

void CCimNetCommApi::SetBuyerSerialNo(CString strBuff)
{
	m_strBuyerSerialNo.Format(_T("%s"), strBuff);
}

void CCimNetCommApi::SetVthValue(CString strBuff)
{
	m_strVthValue.Format(_T("%s"), strBuff);
}

void CCimNetCommApi::SetBDInfo(CString strBuff)
{
	m_strBDInfo.Format(_T("%s"), strBuff);
}

void CCimNetCommApi::SetWDRInfo(CString strBuff)
{
	m_strWDRInfo.Format(_T("%s"), strBuff);
}

void CCimNetCommApi::SetWDREnd(CString strBuff)
{
	m_strWDREnd.Format(_T("%s"), strBuff);
}

void CCimNetCommApi::SetAPDInfo(CString strBuff)
{
	m_strAPDInfo.Format(_T("%s"), strBuff);
}
void CCimNetCommApi::SetDefectCommentCode(CString strBuff)
{
	m_strDefectComCode.Format(_T("%s"), strBuff);
}

//////////////////////////////////////////////////////////////////////////////
CString CCimNetCommApi::GetRwkCode()
{
	return m_strRwkCode;
}

//////////////////////////////////////////////////////////////////////////////
BOOL CCimNetCommApi::EAYT ()
{
	MakeClientTimeString ();

	m_strEAYT.Format (_T ("EAYT ADDR=%s,%s EQP=%s NET_IP=%s NET_PORT=%s MODE=AUTO CLIENT_DATE=%s"),
		m_strLocalSubjectMesF,
		m_strLocalSubjectMesF,
		m_strMachineName,
		m_strLocalIP,
		m_strServicePort,
		m_strClientDate
	);

	return MessageSend (ECS_MODE_EAYT);
}

BOOL CCimNetCommApi::UCHK ()
{
	// -- user id...
	MakeClientTimeString ();
	m_strClientOldDate = m_strClientDate;
	m_strUCHK.Format (_T ("UCHK ADDR=%s,%s EQP=%s USER_ID=%s MODE=AUTO CLIENT_DATE=%s"),
		m_strLocalSubjectMesF,
		m_strLocalSubjectMesF,
		m_strMachineName,
		m_strUserID,
		m_strClientDate
		);

	int nRetCode = MessageSend (ECS_MODE_UCHK);
	if (0 != nRetCode)
	{
		return nRetCode;
	}

	//-------------------------------------------
	// Receive Message 처리.
	//-------------------------------------------
	CString strMsg;
	GetFieldData(&strMsg, _T("RTN_CD"), 0);
	if (strMsg.Compare(_T("0")))	// 
	{	
		// if return code is not zero...
		return 3;	// return code is not zero...
	}

	// return code is zero...
	GetFieldData(&strMsg, _T("HOST_DATE"), 0);
	if (strMsg.GetLength() != 14)
	{
		return 4;
	}
	m_strClientNewDate.Format(strMsg);

	if (m_bIsGmesLocalTestMode == FALSE)
	{
		// 시스템 시간을 HOST 시간과 동기화 시킨다.
		SetLocalTimeData (m_strClientNewDate);
	}

	MakeClientTimeString ();
 //	m_strTimeDate.Format (m_strClientDate);
 
// 	delete [] pszBuff;
	return 0;
}

BOOL CCimNetCommApi::EDTI ()
{
	MakeClientTimeString ();
	m_strEDTI.Format (_T ("EDTI ADDR=%s,%s EQP=%s OLD_DATE=%s NEW_DATE=%s USER_ID=%s MODE=AUTO CLIENT_DATE=%s"),
		m_strLocalSubjectMesF,
		m_strLocalSubjectMesF,
		m_strMachineName,
		m_strClientOldDate,
		m_strClientNewDate,
		m_strUserID,
		m_strClientDate
		);

	return MessageSend (ECS_MODE_EDTI);
}

BOOL CCimNetCommApi::FLDR ()
{
	MakeClientTimeString ();

	m_strFLDR.Format (_T ("FLDR ADDR=%s,%s EQP=%s FILE_NAME=[%s] FILE_TYPE=DEFECT USER_ID=%s MODE=AUTO DOWNLOAD_TIME=%s CLIENT_DATE=%s COMMENT=[%s]"),
		m_strLocalSubjectMesF,
		m_strLocalSubjectMesF,
		m_strMachineName,
		m_strFLDRFileName,
		m_strUserID,
		m_strClientOldDate,
		m_strClientDate,
		_T("")	// Comment
		);
	return MessageSend (ECS_MODE_FLDR);
}

BOOL CCimNetCommApi::PCHK (int ipa_mode, int ipa_value)
{
	MakeClientTimeString ();

	m_strPCHK.Format (_T ("PCHK ADDR=%s,%s EQP=%s PID=%s SERIAL_NO=%s BLID=[%s] PPALLET=%s SKD_BOX_ID= USER_ID=%s MODE=AUTO CLIENT_DATE=%s COMMENT=[%s]"),
		m_strLocalSubjectMesF,
		m_strLocalSubjectMesF,
		m_strMachineName,
		m_strPanelID,
		m_strSerialNumber,
		m_strBLID,
		m_strPalletID,
		m_strUserID,
		m_strClientDate,
		_T("")	// Comment
	);

	int nRetCode = MessageSend (ECS_MODE_PCHK);
	if (nRetCode != RTN_OK)
	{	
		return nRetCode;
	}

	CString strMsg;
	GetFieldData(&strMsg, _T("RTN_CD"));
	if (strMsg.Compare(_T("0")))
	{	
		return 3;	// return code is not zero...
	}

	return RTN_OK;	// normal
}


BOOL CCimNetCommApi::EICR ()
{
//	정밀검사 default: N, 정밀검사 사용시 Y
	MakeClientTimeString ();

	if (m_strEdidStatus.GetLength() <= 0)
		m_strEdidStatus.Format (_T("N"));
	if (m_strPF.GetLength() <= 0)
	{
		if (m_strRwkCode.GetLength() <= 0)
			m_strPF.Format(_T("P"));	// ok
		else
			m_strPF.Format(_T("F"));	// ng
	}
	m_strEICR.Format(_T ("EICR ADDR=%s,%s EQP=%s PID=%s SERIAL_NO=%s BLID=[%s] PF=%s RWK_CD=%s PPALLET=%s EXPECTED_RWK=%s PATTERN_INFO=[%s] DEFECT_PATTERN=%s EDID=%s PVCOM_ADJUST_VALUE=%s PVCOM_ADJUST_DROP_VALUE=%s OVERHAUL_FLAG=%s DEFECT_COMMENT_CODE=%s MODE=AUTO CLIENT_DATE=%s USER_ID=%s COMMENT=[%s] BA_EXI_FLAG=%s MATERIAL_INFO=[] BUYER_SERIAL_NO=%s CGID= VTH_VALUE=%s BD_INFO=[%s] WDR_INFO=[%s] WDR_END=%s"),
						  m_strLocalSubjectMesF,
						  m_strLocalSubjectMesF,
						  m_strMachineName,
						  m_strPanelID,
						  m_strSerialNumber,
						  m_strBLID,
						  m_strPF,
						  m_strRwkCode,
						  m_strPalletID,
						  m_strExpectedRwk,
						  m_strPatternInfo,
						  m_strDefectPattern,
						  m_strEdidStatus,
						  m_strPvcomAdjustValue,
						  m_strPvcomAdjustDropValue,
						  m_strOverHaulFlag,
						  m_strDefectComCode,//DefectCommentcomde 추가 CNZ 20150624
						  m_strClientDate,
						  m_strUserID,
						  _T(""),	// Comment
						  m_strBaExiFlag,
						  m_strBuyerSerialNo,
						  m_strVthValue,
						  m_strBDInfo,
						  m_strWDRInfo,
						  m_strWDREnd
						  );


	int nRetCode = MessageSend (ECS_MODE_EICR);
	if (nRetCode != RTN_OK)
	{	
		return nRetCode;
	}

	CString strMsg;
	GetFieldData(&strMsg, _T("RTN_CD"));
	if (strMsg.Compare(_T("0")))
	{	
		return 3;	// return code is not zero...
	}

	return RTN_OK;	// normal
}


BOOL CCimNetCommApi::APDR ()
{
	//	정밀검사 default: N, 정밀검사 사용시 Y
	MakeClientTimeString ();

	m_strAPDR.Format(_T ("APDR ADDR=%s,%s EQP=%s MODEL=%s PID=%s SERIAL_NO=%s APD_INFO=[%s] USER_ID=%s MODE=AUTO CLIENT_DATE=%s COMMENT=[%s]"),
		m_strLocalSubjectEasF,
		m_strLocalSubjectEasF,
		m_strMachineName,
		m_strModelName,
		m_strPanelID,
		m_strSerialNumber,
		m_strAPDInfo,
		m_strUserID,
		m_strClientDate,
		_T("")	// Comment
		);


	int nRetCode = MessageSend (ECS_MODE_APDR);
	if (nRetCode != RTN_OK)
	{	
		return nRetCode;
	}

	CString strMsg;
	GetFieldData(&strMsg, _T("RTN_CD"));
	if (strMsg.Compare(_T("0")))
	{	
		return 3;	// return code is not zero...
	}

	return RTN_OK;	// normal
}

BOOL CCimNetCommApi::WDCR ()
{
	//	정밀검사 default: N, 정밀검사 사용시 Y
	MakeClientTimeString ();

	m_strWDCR.Format(_T ("WDCR ADDR=%s,%s EQP=%s MODE=AUTO PID=%s SERIAL_NO= BLID= WDR_INFO=[%s] USER_ID=%s CLIENT_DATE=%s"),
		m_strLocalSubjectMesF,
		m_strLocalSubjectMesF,
		m_strMachineName,
		m_strPanelID,
		m_strWDRInfo,
		m_strUserID,
		m_strClientDate
	);


	int nRetCode = MessageSend (ECS_MODE_WDCR);
	if (nRetCode != RTN_OK)
	{	
		return nRetCode;
	}

	CString strMsg;
	GetFieldData(&strMsg, _T("RTN_CD"));
	if (strMsg.Compare(_T("0")))
	{	
		return 3;	// return code is not zero...
	}

	return RTN_OK;	// normal
}

BOOL CCimNetCommApi::AGCM ()
{
	MakeClientTimeString ();

	m_strAGCM.Format (_T ("AGCM ADDR=%s,%s EQP=%s PID= PCBID=%s SERIAL_NO= BLID=[] CHANNEL_ID=%s BOARD_ID=LH128FT2GIENGAGINGBOARDFLAT1 USER_ID=%s MODE=AUTO CLIENT_DATE=%s COMMENT=[]"),
		m_strLocalSubjectMesF,
		m_strLocalSubjectMesF,
		m_strMachineName,		
		m_strPCBID,//m_strPanelID,		
		m_strChannelID,
		m_strUserID,
		m_strClientDate
		);

	int nRetCode = MessageSend (ECS_MODE_AGCM);
	if (nRetCode != RTN_OK)
	{	
		return nRetCode;
	}

	CString strMsg;
	GetFieldData(&strMsg, _T("RTN_CD"));
	if (strMsg.Compare(_T("0")))
	{	
		return 3;	// return code is not zero...
	}

	return RTN_OK;	// normal
}

BOOL CCimNetCommApi::AGN_IN()
{
	MakeClientTimeString ();

	m_strAGNIN.Format (_T ("AGN_IN ADDR=%s,%s EQP=%s PID= PCBID=%s PPALLET=%s FULL_YN=Y USER_ID=%s MODE=AUTO CLIENT_DATE=%s COMMENT=[]"),
		m_strLocalSubjectMesF,
		m_strLocalSubjectMesF,
		m_strMachineName,		
		m_strPCBID,//m_strPanelID,
		m_strChannelID,
		m_strUserID,
		m_strClientDate
		);

	int nRetCode = MessageSend (ECS_MODE_AGN_IN);
	if (nRetCode != RTN_OK)
	{	
		return nRetCode;
	}

	CString strMsg;
	GetFieldData(&strMsg, _T("RTN_CD"));
	if (strMsg.Compare(_T("0")))
	{	
		return 3;	// return code is not zero...
	}

	return RTN_OK;	// normal
}

BOOL CCimNetCommApi::AGN_OUT()
{
	MakeClientTimeString ();

	m_strAGNOUT.Format (_T ("AGN_OUT ADDR=%s,%s EQP=%s PID= PCBID=%s PPALLET=%s FULL_YN=Y USER_ID=%s MODE=AUTO CLIENT_DATE=%s COMMENT=[]"),
		m_strLocalSubjectMesF,
		m_strLocalSubjectMesF,
		m_strMachineName,		
		m_strPCBID,//m_strPanelID,
		m_strChannelID,
		m_strUserID,
		m_strClientDate
		);

	int nRetCode = MessageSend (ECS_MODE_AGN_OUT);
	if (nRetCode != RTN_OK)
	{	
		return nRetCode;
	}

	CString strMsg;
	GetFieldData(&strMsg, _T("RTN_CD"));
	if (strMsg.Compare(_T("0")))
	{	
		return 3;	// return code is not zero...
	}

	return RTN_OK;	// normal
}

