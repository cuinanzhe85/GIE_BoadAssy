#pragma once

#ifndef _GOLBAL_DEFINE_
#define _GOLBAL_DEFINE_


/////////////////////////////////////////////////////////////////////////////
#define _STR_DEFAULTMODEL			"DEFAULT_MODEL"
#define PGM_VERSION					_T("1.1.2")
/////////////////////////////////////////////////////////////////////////////
#define MLOG_MAX_LENGTH				16*1024

/////////////////////////////////////////////////////////////////////////////
#define	APG_LIST_COUNT_MAX			300
#define	DEBUG_GMES_TEST_SERVER		0
#define DEBUG_232RECEIVE_OK			0
#define DEBUG_RS232C_LOG			0
#define DEBUG_PALLET_ARRIVE			0

/////////////////////////////////////////////////////////////////////////////
// DebugMode
#define DEBUG_DIO_SKIP				0
/////////////////////////////////////////////////////////////////////////////
#define UDP_MAIN_IP					_T("192.168.10.15")		// CString type define


/////////////////////////////////////////////////////////////////////////////
#define PACKET_SIZE					1024*64

/////////////////////////////////////////////////////////////////////////////
// ON/OFF와 TRUE/FALSE에 관련된 Define은 여기에서 한다.
/////////////////////////////////////////////////////////////////////////////
#define _OFF_						0
#define _ON_						1

#define _DISABLE_					0
#define _ENABLE_					1

#define POWER_OFF					0
#define POWER_ON					1

#define SIG_TYPE_TMDS				0
#define SIG_TYPE_LVDS				1
#define SIG_TYPE_DP					2
#define SIG_TYPE_EDP				3
#define SIG_TYPE_MIPI				4
#define SIG_TYPE_ALPLD				5

#define SINGLE						0
#define DUAL						1
#define QUAD						2

/////////////////////////////////////////////////////////////////////////////
#define PTNLST_MAX					200

/////////////////////////////////////////////////////////////////////////////
#define OFF_LINE					0
#define IN_LINE						1

/////////////////////////////////////////////////////////////////////////////
//DIO 
#define DIO_OUT_RESET	0x0000

#define DIO_OUT_01		(1<<0)
#define DIO_OUT_02		(1<<1)
#define DIO_OUT_03		(1<<2)
#define DIO_OUT_04		(1<<3)
#define DIO_OUT_05		(1<<4)
#define DIO_OUT_06		(1<<5)
#define DIO_OUT_07		(1<<6)
#define DIO_OUT_08		(1<<7)

#define DIO_IN_01		(1<<0)
#define DIO_IN_02		(1<<1)
#define DIO_IN_03		(1<<2)
#define DIO_IN_04		(1<<3)
#define DIO_IN_05		(1<<4)
#define DIO_IN_06		(1<<5)
#define DIO_IN_07		(1<<6)
#define DIO_IN_08		(1<<7)

enum
{
	DIO_GUMI_M5_PRESS_DOWN = 0,
	DIO_GUMI_M5_SPARE,
	DIO_GUMI_M5_EDID_NG,
	DIO_GUMI_M5_BCR_READ_OK,
	DIO_GUMI_M5_JUDGE_OK,
	DIO_GUMI_M5_JUDGE_NG,
	DIO_GUMI_M5_TEST_OK,
	DIO_GUMI_M5_PRESS_NOMAL_UP,
	DIO_GUMI_M5_MAX
};

enum
{
	DIO_PRESS_DOWN = 0,
	DIO_BCR_OK,
	DIO_BCR_NG,
	DIO_TEST_ON,
	DIO_JUDGE_OK,
	DIO_JUDGE_NG,
	DIO_PRESS_NOMAL_UP,
	DIO_PRESS_FAST_UP,
	DIO_MAX
};
////////////////////////////////////////////
//------------GMES DEFINE-------------------
#define	HOST_EAYT					0
#define	HOST_UCHK					1
#define	HOST_EDTI					2
#define	HOST_PCHK					3
#define	HOST_EPCR					4
#define	HOST_FLDR					5
#define	HOST_EICR					6
#define	HOST_AGN_INSP				7
#define	HOST_EQCC					8
#define	HOST_APDR_YB				9
#define	HOST_APDR_GB				10
#define	HOST_APDR_CB				11
#define HOST_APDR_LD				12
#define	HOST_APDR_ADDLD				13
#define HOST_WDCR					14
#define HOST_APDR_ADPD				15


#define SERVER_MES					0
#define SERVER_EAS					1

/////////////////////////////////////////////////////////////////////////////
// COLORREF
/////////////////////////////////////////////////////////////////////////////
#define COLOR_BLACK					RGB(0,0,0)
#define COLOR_WHITE					RGB(255,255,255)
#define COLOR_RED					RGB(255,0,0)
#define COLOR_GREEN					RGB(0,255,0)
#define COLOR_BLUE					RGB(0,0,255)
#define COLOR_YELLOW				RGB(255,255,0)
#define COLOR_CYAN					RGB(0,255,255)
#define COLOR_SKYBLUE				RGB(173,216,230)
#define COLOR_GRAY32				RGB(32,32,32)
#define COLOR_GRAY64				RGB(64,64,64)
#define COLOR_GRAY94				RGB(94,94,94)
#define COLOR_GRAY96				RGB(96,96,96)
#define COLOR_GRAY127				RGB(127,127,127)
#define COLOR_GRAY159				RGB(159,159,159)
#define COLOR_GRAY192				RGB(192,192,192)
#define COLOR_GRAY224				RGB(224,224,224)
#define COLOR_GRAY240				RGB(240,240,240)
#define COLOR_GREEN128				RGB(0,128,0)
#define COLOR_PINK					RGB(255,192,192)
#define COLOR_MAGENTA				RGB(224,0,224)
#define COLOR_DARK_RED				RGB(255,63,63)
#define COLOR_DARK_GREEN			RGB(63,192,63)
#define COLOR_DARK_BLUE				RGB(63,63,255)
#define COLOR_DARK_ORANGE			RGB(230,160,0)
#define COLOR_DARK_YELLOW			RGB(127,127,32)
#define COLOR_DARK_MAGENTA			RGB(125,100,125)
#define COLOR_BLUISH				RGB(65, 105, 225)
#define COLOR_LIGHT_RED				RGB(255,224,224)
#define COLOR_LIGHT_GREEN			RGB(224,255,224)
#define COLOR_LIGHT_BLUE			RGB(224,224,255)
#define COLOR_LIGHT_ORANGE			RGB(255,234,218)
#define COLOR_LIGHT_CYAN			RGB(150,230,220)
#define COLOR_LIGHT_YELLOW			RGB(254,250,205)
#define COLOR_JADEGREEN				RGB(192,220,192)
#define COLOR_ORANGE				RGB(255,127,39)
#define COLOR_DEEP_BLUE				RGB(77,97,128)

typedef enum _COLOR_IDX_{
	COLOR_IDX_BLACK=0,
	COLOR_IDX_RED,
	COLOR_IDX_GREEN,
	COLOR_IDX_BLUE,
	COLOR_IDX_YELLOW,
	COLOR_IDX_ORANGE,
	COLOR_IDX_CYAN,
	COLOR_IDX_MAGENTA,
	COLOR_IDX_SKYBLUE,
	COLOR_IDX_LIGHT_RED,
	COLOR_IDX_LIGHT_GREEN,
	COLOR_IDX_LIGHT_BLUE,
	COLOR_IDX_LIGHT_ORANGE,
	COLOR_IDX_LIGHT_CYAN,
	COLOR_IDX_LIGHT_YELLOW,
	COLOR_IDX_GRAY64,
	COLOR_IDX_GRAY94,
	COLOR_IDX_GRAY96,
	COLOR_IDX_GRAY127,
	COLOR_IDX_GRAY159,
	COLOR_IDX_GRAY192,
	COLOR_IDX_GRAY224,
	COLOR_IDX_GRAY240,
	COLOR_IDX_GREEN128,
	COLOR_IDX_PINK,
	COLOR_IDX_BLUISH,
	COLOR_IDX_JADEGREEN,
	COLOR_IDX_DARK_RED,
	COLOR_IDX_DARK_GREEN,
	COLOR_IDX_DARK_BLUE,
	COLOR_IDX_DARK_ORANGE,
	COLOR_IDX_DARK_YELLOW,
	COLOR_IDX_DARK_MAGENTA,
	COLOR_IDX_WHITE,
	COLOR_IDX_DEEP_BLUE,
	COLOR_IDX_MAX
}_COLOR_IDX_;

#define FONT_IDX_MAX			10

/////////////////////////////////////////////////////////////////////////////
// UD Pattern Generator Control Command
/////////////////////////////////////////////////////////////////////////////
#define TARGET_PC								0xA1
#define TARGET_CTRL								0xA2
#define TARGET_IF								0xA3
#define TARGET_GFD250							0xAB

#define PACKET_STX								0x02
#define PACKET_ETX								0x03

#define PG_CMD									0x10						
#define NIOS_CMD								0x20

#define PACKET_PT_SOURCE					1
#define PACKET_PT_DEST						3
#define PACKET_PT_ID						5
#define PACKET_PT_CMD						7//+6
#define PACKET_PT_LEN						9//+6
#define PACKET_PT_RET						13//+6
#define PACKET_PT_DATA						14//+6

/////////////////////////////////////////////////////////////////////////////
// Command Packet
/////////////////////////////////////////////////////////////////////////////
// Command Define
#define CMD_CTRL_FUSING_SYSTEM					0xA0	// CTRL/Fusing SystemInfo
#define CMD_CTRL_CABLE_OPEN_TEST				0xA5	// CTRL_Cable Open Test
#define CMD_CTRL_SSA_START_STOP					0xA9	// CTRL_Erase Flash Sector
#define CMD_CTRL_POWER_SEQ_ONOFF				0xAC	// CTRL_Power Sequence On Off

#define CMD_ZONE_SET							0xB0	// CTRL_Zone Set
#define CMD_CTRL_SIGNAL_ONOFF					0xB1	// CTRL_Signal ON/OFF
#define CMD_CTRL_PWM_SET						0xB2	// CTRL_PWM Set
#define CMD_CTRL_INV_POWER_ONOFF				0xB3	// CTRL_Inverter Power On/Off
#define CMD_CTRL_PULLUP_SHORT					0xB4	// CTRL_089 Model Pullup open /Short Test
#define CMD_MEASURE_POWER						0xB5	// CTRL_Measure Power
#define CMD_CTRL_BL_CABLE						0xB6	// CTRL_BL Cable Check
#define CMD_CTRL_POWER_VOLTAGE_SET				0xBA	// CTRL_Power Voltage Setting
#define	CMD_CTRM_AGING_LOG						0xBC	// CTRL_Get_AgingLog Data
#define	CMD_MEASURE_ALL_POWER					0xBD	// CTRL_Measure All Power

#define CMD_ARE_YOU_READY						0xC0
//----------------------------------------------------------------------------


#define CMD_CTRL_FW_DOWNLOAD					0xF0
#define CMD_CTRL_FW_COMPLETE					0xF2
#define CMD_CTRL_FW_GOTO_BOOT_DOWNLOAD			0xF3	// CTRL_Boot Daownload
#define CMD_CTRL_FW_GOTO_BOOT_UPDATE			0xF4	// CTRL_Boot Update
#define CMD_GFD250_FPGA_VER_READ				0xFC	// CTRL_Reset Control Board
#define CMD_CTRL_RESET_CTRLBOARD				0xFD	// CTRL_Reset Control Board
#define CMD_CTRL_FW_VERSION						0xFE    // CTRL_Firmware Version check
#define CMD_CTRL_COMMUNICATION_TIMEOUT			0xFF    // CTRL_Communication Timeout

//----------------------------------------------------------------------------
#define	CMD_T2PTN_SEND							0x10
#define CMD_PG_CLOCK_DELAY						0x11
#define CMD_BMP_DISPLAY							0x12

#define CMD_BMP_DOWNLOAD_PTN_INFO				0x15
#define CMD_BMP_DOWNLOAD_RAW_DATA				0x17
#define CMD_BMP_DOWNLOAD_DONE_CHECK				0x18

#define CMD_CTRL_I2C_WRITE						0x30	// I2C Write
#define CMD_CTRL_I2C_READ						0x31	// I2C Read
#define CMD_IF_I2C_CLOCK						0x35	// IF I2C Clock
#define CMD_IF_GET_EDID_ODC_AI_DATA				0x39
#define CMD_IF_GET_EDID_ODC_AI_DATA_EXPAND		0x3B

#define CMD_CTRL_SRUNNER_CONTROL				0x40
#define CMD_CTRL_SRUNNER_STATUS_READ			0x42
#define CMD_CTRL_SRUNNER_DATA_WRITE				0x43
#define CMD_CTRL_SRUNNER_COPLETE				0x45
//----------------------------------------------------------------------------
// LED B/L 점등기 제어 Command

#define	_MIN_									0
#define	_MAX_									1
#define	_USERSET_								2

//----------------------------------------------------------------------------
// GFD250Command
#define CMD_NIOS_DPCD_WRITE						0x01
#define CMD_NIOS_DPCD_READ						0x02
#define CMD_NIOS_I2C_WRITE_BYTE					0x06
#define CMD_NIOS_I2C_WRITE_PAGE					0x07
#define CMD_NIOS_I2C_READ						0x08

#define TOTALPATTERN							200

#define OFF										FALSE
#define ON										TRUE

#define SIG_6BIT	0
#define SIG_8BIT	1
#define SIG_10BIT	2
#define SIG_12BIT	3

/////////////////////////////////////////////////////////////////////////////
// Macro Define
/////////////////////////////////////////////////////////////////////////////
#define round(a) ( int ) ( a + .5 )


#define	WM_UPDATE_SYSTEM_INFO					(WM_USER+102)

#define SEQ_MAX_ITEM 4

// 0xBD : CTRL_Measure_All_Power
//VCC,ICC,VDD,IDD,VBL,IBL,VGH,IGH,VGL,IGL,VCC_FB,VBL_FB,VLED_FB,THERMISTOR
enum
{
	PINFO_VCC =0,
	PINFO_ICC,
	PINFO_VDD,
	PINFO_IDD,
	PINFO_VBL,
	PINFO_IBL,
	PINFO_VGH,
	PINFO_IGH,
	PINFO_VGL,
	PINFO_IGL,
	PINFO_VCC_FB,
	PINFO_VBL_FB,
	PINFO_VLED_FB,
	PINFO_THERMISTOR,
	PINFO_ERR_RESULT,
	PINFO_ERR_NAME,
	PINFO_ERR_VALUE
};

#define NORMAL									0x00
#define	OVER_CURRENT							0x01
#define	LOW_CURRENT								0x02

#define SPLIT_MODE								1

#define EQP_OFFLINE								0
#define EQP_INLINE								1

#define	FAST_JUDGE_NONE							0
#define	FAST_JUDGE_OK							1
#define	FAST_JUDGE_NG							2
#define	FAST_JUDGE_MAX							3

#define	GMES_PNF_NONE							0
#define	GMES_PNF_PASS							1
#define	GMES_PNF_FAIL							2
#define	GMES_PNF_MAX							3

#define GOOD_CNT								0
#define BAD_CNT									1


#endif