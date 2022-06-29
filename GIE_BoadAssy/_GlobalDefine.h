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
#define COLOR_GRAY127				RGB(127,127,127)
#define COLOR_GRAY159				RGB(159,159,159)
#define COLOR_GRAY192				RGB(192,192,192)
#define COLOR_GRAY224				RGB(224,224,224)
#define COLOR_GRAY240				RGB(240,240,240)
#define COLOR_PINK					RGB(255,192,192)
#define COLOR_MAGENTA				RGB(224,0,224)
#define COLOR_DARK_RED				RGB(255,63,63)
#define COLOR_DARK_GREEN			RGB(63,192,63)
#define COLOR_DARK_BLUE				RGB(63,63,255)
#define COLOR_DARK_ORANGE			RGB(230,160,0)
#define COLOR_DARK_YELLOW			RGB(127,127,32)
#define COLOR_DARK_MAGENTA			RGB(125,100,125)
#define COLOR_LIGHT_RED				RGB(255,224,224)
#define COLOR_LIGHT_GREEN			RGB(224,255,224)
#define COLOR_LIGHT_BLUE			RGB(224,224,255)
#define COLOR_LIGHT_ORANGE			RGB(255,234,218)
#define COLOR_LIGHT_CYAN			RGB(150,230,220)
#define COLOR_JADEGREEN				RGB(192,220,192)
#define COLOR_ORANGE				RGB(255,127,39)
#define COLOR_DEEP_BLUE				RGB(77,97,128)

typedef enum _COLOR_IDX_{
	COLOR_IDX_BLACK=0,
	COLOR_IDX_RED,
	COLOR_IDX_GREEN,
	COLOR_IDX_BLUE,
	COLOR_IDX_YELLOW,
	COLOR_IDX_CYAN,
	COLOR_IDX_SKYBLUE,
	COLOR_IDX_LIGHT_RED,
	COLOR_IDX_LIGHT_GREEN,
	COLOR_IDX_LIGHT_BLUE,
	COLOR_IDX_LIGHT_ORANGE,
	COLOR_IDX_LIGHT_CYAN,
	COLOR_IDX_GRAY64,
	COLOR_IDX_GRAY127,
	COLOR_IDX_GRAY159,
	COLOR_IDX_GRAY192,
	COLOR_IDX_GRAY224,
	COLOR_IDX_GRAY240,
	COLOR_IDX_PINK,
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

/////////////////////////////////////////////////////////////////////////////
// Command Packet
/////////////////////////////////////////////////////////////////////////////
// Command Define
#define CMD_CTRL_FUSING_SYSTEM					0xA0	// CTRL/Fusing SystemInfo
#define	CMD_CTRL_FUSING_ODCAI					0xA1	// CTRL_Fusing ODC
#define	CMD_CTRL_FUSING_EDID					0xA2	// CTRL_Fusing EDID
#define	CMD_CTRL_FUSING_AI						0xA3	// CTRL_Fusing AI
#define	CMD_CTRL_FUSING_PID						0xA4	// CTRL_Fusing Pallet & Pannel ID
#define CMD_CTRL_FUSING_CONTROL_PTN				0xA5	// CTRL_Fusing Control Pattern
#define CMD_CTRL_FUSING_AGING_PTN				0xA6	// CTRL_Fusing Aging Pattern
#define CMD_CTRL_FUSING_PTN_NEXTINFO			0xA7	// CTRL_Fusing Pattern Next Info
#define	CMD_CTRL_GET_PALLET_PANEL_ID			0xA8	// CTRL_Get Pallet & Pannel ID
#define CMD_CTRL_ERASE_FLASH					0xA9	// CTRL_Erase Flash Sector
#define CMD_CTRL_POWER_VOLT						0xAA	// CTRL_Power Voltage Set
#define CMD_CTRL_POWER_ONOFF_SET				0xAB	// CTRL_Power OnOff Set
#define CMD_CTRL_POWER_SEQ_ONOFF				0xAC	// CTRL_Power Sequence On Off
#define CMD_CTRL_AI_ENABLE						0xAD	// CTRL_AI Enable
#define CMD_CTRL_AI_SENSING_START				0xAE	// CTRL_AI Sensing start
#define CMD_CTRL_LG_DISM_SEL					0xAF	// CTRL_LG DISM Sel

#define CMD_CTRL_810_BIT_SEL					0xB0	// CTRL_8/10 Bit Sel
#define CMD_CTRL_SIGNAL_ONOFF					0xB1	// CTRL_Signal ON/OFF
#define CMD_CTRL_PWM_SET						0xB2	// CTRL_PWM Set
#define CMD_CTRL_INV_POWER_ONOFF				0xB3	// CTRL_Inverter Power On/Off
#define CMD_CTRL_PULLUP_SHORT					0xB4	// CTRL_089 Model Pullup open /Short Test
#define CMD_MEASURE_POWER						0xB5	// CTRL_Measure Power
#define CMD_CTRL_BL_CABLE						0xB6	// CTRL_BL Cable Check
#define	CMD_ZONE_SET							0xB7
#define	CMD_CTRM_AGING_LOG						0xBC	// CTRL_Get_AgingLog Data
#define	CMD_MEASURE_ALL_POWER					0xBD	// CTRL_Measure All Power

#define CMD_ARE_YOU_READY						0xC0
#define	CMD_POWER_VOLTAGE_SET					0xC1
#define CTRL_PTN_PROGRESS						0xC2
#define	CMD_CTRL_LAMPSTATUS						0xC3
#define CMD_CTRL_MEASURE_BRTPFREQ				0xC5
#define CMD_CTRL_FUSING_PREDISP_PTN				0xC6	// CTRL_Fusing PreDisplay Pattern
#define CMD_CTRL_AGING_LOG_CLEAR				0xC7	// Aging Log Data Clear
#define	CMD_CTRL_PID_CLEAR						0xC8	// Pallet/PID Clear
#define CMD_CTRL_POWER_OFFON_WITHOUT_LP			0xCD	// 2012-10-16 PDH. MIPI Power Off/On시 LP COMMAND를 전송하지 않음.
#define CMD_CTRL_SMBUS							0xCE	// 2010-09-17 PDH. SMBUS I2C MinMax Control
#define CMD_CTRL_MIPI_CABC_CONTROL				0xCF	// 2012-07-24 PDH.

//----------------------------------------------------------------------------
// Touch Control Command
#define	CMD_CTRL_MAX3421_USB_CONTACT			0xD0
#define CMD_CTRL_TOUCH_SENSING_START			0xD1
#define CMD_CTRL_TOUCH_POSITION_INFO			0xD2
#define CMD_CTRL_TOUCH_INFO_SET					0xD3
#define CMD_CTRL_TOUCH_RAW_DATA					0xD4
#define CMD_CTRL_TOUCH_CALIBRATION				0xD5
#define CMD_CTRL_TOUCH_READFIRMWAREVER			0xD6
#define CMD_CTRL_HID_I2C_RD_DESCRIPTOR			0xD7
#define CMD_CTRL_HID_I2C_RD_GENERIC_MEMORY_MAP	0xD8
#define CMD_CTRL_HID_I2C_WR_GENERIC_MEMORY_MAP	0xD9
#define CMD_CTRL_HID_I2C_RD_AUTORETURN_MSG		0xDA
#define CMD_CTRL_USB_RD_DESCRIPTOR				0xDB
#define CMD_CTRL_HID_I2C_RD_AUTORETURN_SELFTEST	0xDC
#define CMD_CTRL_I2C_TEMPERATURE_SENSOR			0xDD
#define CMD_CTRL_USB_INT_DATA_SET				0xDE
#define CMD_CTRL_USB_INT_DATA_GET				0xDF


#define CMD_CTRL_MICROSOFT_LOGO					0xE2
#define CMD_CTRL_NORMAL_I2C_POSITION_REGISTER	0xE4
#define CMD_CTRL_LED_CONTROLLER					0xE5

#define CTRL_RESET_CTRLBOARD					0xFD	// CTRL_Reset Control Board
#define CMD_CTRL_FW_DOWNLOAD					0xF0
#define CMD_CTRL_FW_COMPLETE					0xF2
#define CMD_CTRL_FW_GOTO_BOOT_SECTION			0xF3    
#define CMD_CTRL_FW_VERSION						0xFE    // CTRL_Firmware Version check

//----------------------------------------------------------------------------
#define	CMD_T2PTN_SEND							0x10
#define CMD_PG_CLOCK_DELAY						0x11

#define CMD_IF_TOUCH_TYPE_SELECT				0x20	// s2k_debug
#define CMD_IF_PULLUP_ENABLE					0x21	// IF_Pullup Set
#define CMD_IF_HDP_VIDEO_ON_CHECK				0x22	// IF_HDP & Video On Check
#define CMD_IF_SHORT_TEST						0x24	// IF_Short Test
#define CMD_IF_SYNC_TEST						0x25	// IF_Sync Test
#define CMD_IF_HDCP_ONOFF						0x26	// IF_HDCP On/Off
#define CMD_IF_GET_HDCP_DATA					0x27	// IF_GET HDCP DATA
#define CMD_IF_EQ_SET							0x28	// IF_EQ_Set
#define CMD_IF_PVCOM_SET						0x29	// IF_PVcom Set
#define CMD_IF_GET_PVCOM_DATA					0x2A	// IF_Get PVcom Data
#define CMD_IF_USER_CABLE						0x2B	// IF_User Cable Contack Check
#define CMD_IF_EDID_WRITE						0x2C	// IF_EDID Write
#define	CMD_IF_EDID_CHECK						0x2D	// IF_EDID Check
#define	CMD_IF_ODC_CHECK						0x2E	// IF_ODC Check
#define CMD_IF_AI_CHECK							0x2F	// IF_AI Check

#define CMD_IF_CHIP_CHECK						0x34	// IF_I2C Chip Check
#define CMD_IF_I2C_CLOCK						0x35	// IF I2C Clock
#define CMD_IF_PGAMMA_WRITE						0x37	// IF PGamma Write
#define CMD_IF_7172_SET							0x38	// IF_7172 Set
#define CMD_IF_GET_EDID_ODC_AI_DATA				0x39
#define CMD_IF_PGAMMA_READ						0x3A
#define CMD_IF_GET_EDID_ODC_AI_DATA_EXPAND		0x3B
#define	CMD_IF_TVLED_SENDPACKET					0x3D	// 2009-11-10 PDH. TV LED Module Send Data
#define	CMD_IF_TVLED_RECEIVEPACKET				0x3E	// 2009-11-10 PDH. TV LED Module Receive Data

#define CMD_IF_DP501SIGNALRST_SET				0x40
#define CMD_IF_PGAMMA_WRITE_MAXIM				0x41
#define CMD_IF_PGAMMA_READ_MAXIM				0x42
#define	CMD_IF_USB_5V_POWER_ONOFF				0x46	//2013.03.07. KSM. USB Touch Power ON/OFF
#define CMD_IF_SPI_DATA_SET						0x47	// 2011.07.08 KSM. SPI Data Set.
#define CMD_IF_DBC_ONOFF						0x48	// 2012-02-23 PDH. DBC OnOff
#define CMD_IF_PSR_ONOFF						0x49	//s2k_psr
#define CMD_IF_eKTF5751_SET						0x4A	
#define CMD_IF_eKTF5751_GET						0x4B	
#define CMD_IF_MIPI_DATA_SET					0x4C	// 2012-05-08 PDH. MIPI Data Set.
#define CMD_IF_MIPI_CMD_SET						0x4D
#define CMD_IF_MIPI_REGEEP_RD					0x4E
#define CMD_IF_MIPI_REGEEP_WR					0x4F

#define CMD_IF_5V_POWER_ONOFF					0x50
#define CMD_CTRL_ALWAYS_BLU_ON					0x51
#define CMD_CTRL_VCC_CALIBRATION				0x52
#define CMD_IF_PAPER_MODE						0x53
#define CMD_CTRL_I2C_READ						0x54	
#define CMD_CTRL_I2C_WRITE						0x55	
#define CMD_CTRL_FREQ							0x56	
#define CMD_CTRL_TOUCH_I2C_RD_BIG_DATA			0x57
#define CMD_IF_MIPI_SOLOMON_CMD_SET				0x58
#define CMD_IF_MIPI_SOLOMON_VCOM_SET			0x5A
#define CMD_IF_MIPI_SOLOMON_VCOM_GET			0x5B
#define CMD_IF_SERIAL_LABEL_WRITE_TO_EEPROM		0x5C
#define CMD_IF_SERIAL_LABEL_READ_FROM_EEPROM	0x5D
#define CMD_IF_INIT_CODE						0x5E
#define CMD_IF_eDP_BERT_READ					0x5F

//----------------------------------------------------------------------------
// LED B/L 점등기 제어 Command
#define	CMD_LEDBL_ONOFF							0xE2
#define	CMD_LEDBL_MINMAX						0x8A
#define	CMD_LEDBL_MINMAX_SET					0x88
#define	CMD_LEDBL_FREQ_SET						0x89
#define	CMD_LEDBL_LIGHT_ONOFF					0xFE

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
#define	PINFO_VCC								0x00
#define	PINFO_VDD								0x01
#define	PINFO_VBL								0x02
#define	PINFO_ICC								0x03
#define	PINFO_IDD								0x04
#define	PINFO_IBL								0x05
#define	PINFO_BRTI								0x06
#define	PINFO_NAME								0x07
#define	PINFO_ERR								0x08
#define	PINFO_LIMIT								0x09

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