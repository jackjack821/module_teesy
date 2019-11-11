/*******************************************************************************
| Module Name: Climate Calibration Processing Module. 
| File Name: CCP.c
|
|-------------------------------------------------------------------------------
|               C O P Y R I G H T
|-------------------------------------------------------------------------------
| Copyright (c) 2015 Huizhou Desay SV Automotive Co., Ltd.    All rights reserved.
|
| This software is copyright protected and proprietary to Desay SV Automotive Co., Ltd.
| Desay SV Automotive Co., Ltd grants to you only those rights as set out in the
| license conditions. All other rights remain with Desay SV Automotive Co., Ltd.
|
| REMOVAL OF THESE COMMENTS IS A VIOLATION OF THE LICENSE AGREEMENT.
|-------------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-------------------------------------------------------------------------------
| Name                                  Company
| ---------------------     ---------------------------------------
| Zhong bin                       Desay SV Automotive Co., Ltd
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date            Ver         Author               Description
| ----------  -------  -------------  ------------------------------------------
 13/8/2012        V1.1            Zhong Bin           Creation.
 16/12/2015       V1.2            Lin Tao             First release for J72L  

*****************************************************************************/

#ifndef CCP_DEF_H
#define CCP_DEF_H

/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
******************************************************************************/
/* system-headerfiles*/


/* foreign headerfiles*/

/* Own headerfiles */




/**************************** .BLOCK_COMMENT_BEGIN ***************************
* In this section
* - adapt external symbols to internally used names if necessary. This
*   synonym adaption is unknown for other modules
***************************** .BLOCK_COMMENT_END *****************************/
/* Define const */
#define CCP_MAP_TABLE_SIZE                          8
#define PASSWORDNUM				7
#define CCP_WRITE_EEPROM			0xAA
#define CCP_CALIBRATION_START_ID	0x00//0x81
#define CCP_ADJUST_CONTROL			0x03
#define CCP_NORMAL_CONTROL		0x0F
 /* define eeprom access const */
#define CCP_nClrWriteGlbBuff		(uint8)(0x01)
#define CCP_nClrReadGlbBuff 		(uint8)(0x02)
#define CCP_nCalWriteCheckSum	(uint8)(0x01)
#define CCP_nCalReadCheckSum	(uint8)(0x02)
/* eeprom access const end */

/* Define CCP2000 negative service ID */
#define KWP_NEGATIVE_SID			0x7F
/* Define Kwp2000 negative code */
#define KWP_ERR_GENERAL_REJECT	0x10
#define KWP_ERR_SERVICE_NOT_SUPPORTED		0x11
#define KWP_ERR_SUB_SERVICE_NOT_SUPPORT		0x12
#define KWP_ERR_BUSY_REPEAT_REQUEST			0x21
#define KWP_ERR_CONDITION_NOT_CRRECT			0x22
#define KWP_ERR_REQUEST_OUT_OF_RANGE		0x31
#define KWP_ERR_INVALID_KEY					0x35
/*- Calibration data timing circle -*/
#define CCP_nTimingCircle					(106U)

/* Define CCP module using flage */
#define CCP_biServiceActive 	CCP_unLocalFlage.f._0
#define CCP_biSecurityChk    	CCP_unLocalFlage.f._1
#define CCP_biEepromAccess 	    CCP_unLocalFlage.f._2
/* define the proper CAN mappings */
#define CCP_stCanTxMessage				(CCP_Calibration_Read)
#define CCP_stCanRxMessage				(CCP_Calibration_Write)

#define CCP_EepromInd_b				CCP_Calibration_Write_ind_b

#define CCP_nbRC_OK						0//EEXT_nbRC_OK
#define CCP_nbRC_BUSY					1//EEXT_nbRC_BUSY
#define CCP_EEPROM_TABLE_LENGTH		1024//sizeof(EED__stROMLayout)

#define CCP_nbiByteMax	((CCP_nbiMax/8) + 1)
#define CCP_SetBit(Index)				CCP_u8BitArray[Index / 8] |= (0x01 << (Index % 8))
#define CCP_ClearBit(Index)			CCP_u8BitArray[Index / 8] &= (~(0x01 << (Index % 8)))
#define CCP_GetBitValue(Index)		(((CCP_u8BitArray[Index / 8]) >> (Index % 8)) & 0x01)
/* Tx */
#define CCP_stDatastrct	(*CCP_stDataPtr)
/* Rx */

#define CCP_stCmdPtr		(*CCP_tstCmdPtr)


typedef void (*CCP_tpfService) (void);

typedef struct 
{
    const CCP_tpfService vfpCidAction;
    const uint8 boTxCfg;
}CCP_tpfCidService;

/*- Data structure. -*/
typedef struct tCCPData                 /* Dword data type with single */
{/*  accessable words and bytes */
	/*- Data label, differrent means of buffers in differrent labels. -*/
	uint8 u8CmdID;
	uint8 u8Data1;
	uint8 u8Data2;
	uint8 u8Data3;
	uint8 u8Data4;
	uint8 u8Data5;
	uint8 u8Data6;
	uint8 u8Data7;	
} tstCcpdata;

typedef struct
{
	uint8 u8SID;
	CCP_tpfService pfService;
} CCP_tstMapTable;

/* this is for bool type variables */
typedef enum CCP_enbiVarNumber
{
	CCP_nbiSecurityChk = 0,
	CCP_nbiServiceActive,
	CCP_nbiMax	
}CCP_tenbiVarNumber;

#define CCP_RCID_START 		(0x00)
typedef enum CCP_enCIDs
{
	CCP_RCID_00 = 0,
	CCP_RCID_01,
	CCP_RCID_02,
	CCP_RCID_03,
	CCP_RCID_04,
	CCP_RCID_05,
	CCP_RCID_06,
	CCP_RCID_07,
	CCP_RCID_08,
	CCP_RCID_09,
	CCP_RCID_0A,
	CCP_RCID_0B,
	CCP_RCID_0C,
	CCP_RCID_0D,
	CCP_RCID_0E,
	CCP_RCID_0F,
	CCP_RCID_10,
	CCP_RCID_11,
	CCP_RCID_12,
	CCP_RCID_13,
	CCP_RCID_14,
	CCP_RCID_15,
	CCP_RCID_16,
	CCP_RCID_17,
	CCP_RCID_18,
	CCP_RCID_19,
	CCP_RCID_1A,
	CCP_RCID_1B,
	CCP_RCID_1C,
	CCP_RCID_1D,
	CCP_RCID_1E,
	CCP_RCID_1F,
	CCP_RCID_20,
	CCP_RCID_21,
	CCP_RCID_22,
	CCP_RCID_23,
	CCP_RCID_24,
	CCP_RCID_25,
	CCP_RCID_26,
	CCP_RCID_27,
	CCP_RCID_28,
	CCP_RCID_29,
	CCP_RCID_2A,
	CCP_RCID_2B,
	CCP_RCID_2C,
	CCP_RCID_2D,
	CCP_RCID_2E,
	CCP_RCID_2F,
	CCP_RCID_30,
	CCP_RCID_31,
	CCP_RCID_32,
	CCP_RCID_33,
	CCP_RCID_34,
	CCP_RCID_35,
	CCP_RCID_36,
	CCP_RCID_37,
	CCP_RCID_38,
	CCP_RCID_39,
	CCP_RCID_3A,
	CCP_RCID_3B,
	CCP_RCID_3C,
	CCP_RCID_3D,
	CCP_RCID_3E,
	CCP_RCID_3F,
	CCP_RCID_40,
	CCP_RCID_41,
	CCP_RCID_42,
	CCP_RCID_43,
	CCP_RCID_44,
	CCP_RCID_45,
	CCP_RCID_46,
	CCP_RCID_47,
	CCP_RCID_48,
	CCP_RCID_49,
	CCP_RCID_4A,
	CCP_RCID_4B,
	CCP_RCID_4C,
	CCP_RCID_4D,
	CCP_RCID_4E,
	CCP_RCID_4F,
	CCP_RCID_50,
    CCP_RCID_51,
    CCP_RCID_52,
    CCP_RCID_53,
    CCP_RCID_54,
    CCP_RCID_55,
    CCP_RCID_56,		
    CCP_RCID_57,
    CCP_RCID_58,
    CCP_RCID_59,
    CCP_RCID_5A,
    CCP_RCID_5B,
    CCP_RCID_5C,
    CCP_RCID_5D,
    CCP_RCID_5E,
    CCP_RCID_5F,
	CCP_RCID_60,
    CCP_RCID_61,
    CCP_RCID_62,
    CCP_RCID_63,
    CCP_RCID_64,
    CCP_RCID_65,
    CCP_RCID_66,		
    CCP_RCID_67,
    CCP_RCID_68,
    CCP_RCID_69,
    CCP_RCID_6A,
    CCP_RCID_6B,
    CCP_RCID_6C,
    CCP_RCID_6D,
    CCP_RCID_6E,
    CCP_RCID_6F,
	CCP_RCID_70,
    CCP_RCID_71,
    CCP_RCID_72,
    CCP_RCID_73,
    CCP_RCID_74,
    CCP_RCID_75,
    CCP_RCID_76,		
    CCP_RCID_77,
    CCP_RCID_78,
    CCP_RCID_79,
    CCP_RCID_7A,
    CCP_RCID_7B,
    CCP_RCID_7C,
    CCP_RCID_7D,
    CCP_RCID_7E,
	CCP_RCID_7F,
	CCP_RCID_80,
	CCP_RCID_81,
	CCP_RCID_82,
	CCP_RCID_83,
	CCP_RCID_84,
	CCP_RCID_85,
	CCP_RCID_86,
	CCP_RCID_87,
	CCP_RCID_88,
	CCP_RCID_89,
	CCP_RCID_8A,
	CCP_RCID_8B,
	CCP_RCID_8C,
	CCP_RCID_8D,
	CCP_RCID_8E,
	CCP_RCID_8F,
	CCP_RCID_90,
	CCP_RCID_91,
	CCP_RCID_92,
	CCP_RCID_93,
	CCP_RCID_94,
	CCP_RCID_95,
	CCP_RCID_96,
	CCP_RCID_97,
	CCP_RCID_98,
	CCP_RCID_99,
	CCP_RCID_9A,
	CCP_RCID_9B,
	CCP_RCID_9C,
	CCP_RCID_9D,
	CCP_RCID_9E,
	CCP_RCID_9F,
	CCP_RCID_A0,
	CCP_RCID_A1,
	CCP_RCID_A2,
	CCP_RCID_A3,
	CCP_RCID_A4,
	CCP_RCID_A5,
	CCP_RCID_A6,
	CCP_RCID_A7,
	CCP_RCID_A8,
	CCP_RCID_A9,
	CCP_RCID_AA,
	CCP_RCID_AB,
	CCP_RCID_AC,
	CCP_RCID_AD,
	CCP_RCID_AE,
	CCP_RCID_AF,
	CCP_RCID_B0,
	CCP_RCID_B1,
	CCP_RCID_B2,
	CCP_RCID_B3,
	CCP_RCID_B4,
	CCP_RCID_B5,
	CCP_RCID_B6,
	CCP_RCID_B7,
	CCP_RCID_B8,
	CCP_RCID_B9,
	CCP_RCID_BA,
	CCP_RCID_BB,
	CCP_RCID_BC,
	CCP_RCID_BD,
	CCP_RCID_BE,
	CCP_RCID_BF,
	CCP_RCID_C0,
	CCP_RCID_C1,
	CCP_RCID_C2,
	CCP_RCID_C3,
	CCP_RCID_C4,
	CCP_RCID_C5,
	CCP_RCID_C6,
	CCP_RCID_C7,
	CCP_RCID_C8,
	CCP_RCID_C9,
	CCP_RCID_CA,
	CCP_RCID_CB,
	CCP_RCID_CC,
	CCP_RCID_CD,
	CCP_RCID_CE,
	CCP_RCID_CF,
	CCP_RCID_D0,
	CCP_RCID_D1,
    CCP_RCID_D2,
    CCP_RCID_D3,
    CCP_RCID_D4,
    CCP_RCID_D5,
    CCP_RCID_D6,
    CCP_RCID_D7,		
    CCP_RCID_D8,
    CCP_RCID_D9,
    CCP_RCID_DA,
    CCP_RCID_DB,
    CCP_RCID_DC,
    CCP_RCID_DD,
    CCP_RCID_DE,
    CCP_RCID_DF,
    CCP_RCID_E0,
	CCP_RCID_E1,
    CCP_RCID_E2,
    CCP_RCID_E3,
    CCP_RCID_E4,
    CCP_RCID_E5,
    CCP_RCID_E6,
    CCP_RCID_E7,		
    CCP_RCID_E8,
    CCP_RCID_E9,
    CCP_RCID_EA,
    CCP_RCID_EB,
    CCP_RCID_EC,
    CCP_RCID_ED,
    CCP_RCID_EE,
    CCP_RCID_EF,
    CCP_RCID_F0,
	CCP_RCID_F1,
    CCP_RCID_F2,
    CCP_RCID_F3,
    CCP_RCID_F4,
    CCP_RCID_F5,
    CCP_RCID_F6,
    CCP_RCID_F7,		
    CCP_RCID_F8,
    CCP_RCID_F9,
    CCP_RCID_FA,
    CCP_RCID_FB,
    CCP_RCID_FC,
    CCP_RCID_FD,
    CCP_RCID_FE,
	CCP_RCID_NUM
} CCP_tenCIDs;
/* Define CCP Io control enum */
#define CCP_IO_CONTROL_START		(0x10)
typedef enum CCP_enIoControlNumber
{
	CCP_IO_CONTROL_10 = 0,
	CCP_IO_CONTROL_11,
	CCP_IO_CONTROL_12,
	CCP_IO_CONTROL_13,
	CCP_IO_CONTROL_14,
	CCP_IO_CONTROL_15,
	CCP_IO_CONTROL_16,
	CCP_IO_CONTROL_17,
	CCP_IO_CONTROL_18,
	CCP_IO_CONTROL_19,
	CCP_IO_CONTROL_1A,
	CCP_IO_CONTROL_1B,
	CCP_IO_CONTROL_1C,
	CCP_IO_CONTROL_1D,
	CCP_IO_CONTROL_1E,
	CCP_IO_CONTROL_1F,
	CCP_IO_CONTROL_20,
	CCP_IO_CONTROL_21,
	CCP_IO_CONTROL_22,
	CCP_IO_CONTROL_23,
	CCP_IO_CONTROL_24,
	CCP_IO_CONTROL_25,
	CCP_IO_CONTROL_26,
	CCP_IO_CONTROL_27,
	CCP_IO_CONTROL_28,
	CCP_IO_CONTROL_29,
	CCP_IO_CONTROL_2A,
	CCP_IO_CONTROL_2B,
	CCP_IO_CONTROL_2C,
	CCP_IO_CONTROL_2D,
	CCP_IO_CONTROL_2E,
	CCP_IO_CONTROL_2F,
	CCP_IO_CONTROL_30,
	CCP_IO_CONTROL_31,
	CCP_IO_CONTROL_32,
	CCP_IO_CONTROL_33,
	CCP_IO_CONTROL_34,
	CCP_IO_CONTROL_35,
	CCP_IO_CONTROL_36,
	CCP_IO_CONTROL_37,
	CCP_IO_CONTROL_38,
	CCP_IO_CONTROL_39,
	CCP_IO_CONTROL_3A,
	CCP_IO_CONTROL_3B,
	CCP_IO_CONTROL_3C,
	CCP_IO_CONTROL_3D,
	CCP_IO_CONTROL_3E,
	CCP_IO_CONTROL_3F,
	CCP_IO_CONTROL_40,
	CCP_IO_CONTROL_41,
	CCP_IO_CONTROL_42,
	CCP_IO_CONTROL_43,
	CCP_IO_CONTROL_44,
	CCP_IO_CONTROL_45,
	CCP_IO_CONTROL_46,
	CCP_IO_CONTROL_47,
	CCP_IO_CONTROL_48,
	CCP_IO_CONTROL_49,
	CCP_IO_CONTROL_4A,
	CCP_IO_CONTROL_4B,
	CCP_IO_CONTROL_4C,
	CCP_IO_CONTROL_4D,
	CCP_IO_CONTROL_4E,
	CCP_IO_CONTROL_4F,
	CCP_IO_CONTROL_50,
	CCP_IO_CONTROL_51,
	CCP_IO_CONTROL_52,
	CCP_IO_CONTROL_53,
	CCP_IO_CONTROL_54,
	CCP_IO_CONTROL_55,
	CCP_IO_CONTROL_56,
	CCP_IO_CONTROL_57,
	CCP_IO_CONTROL_58,
	CCP_IO_CONTROL_59,
	CCP_IO_CONTROL_5A,
	CCP_IO_CONTROL_5B,
	CCP_IO_CONTROL_5C,
	CCP_IO_CONTROL_5D,
	CCP_IO_CONTROL_5E,
	CCP_IO_CONTROL_5F,
	CCP_IO_CONTROL_60,
	CCP_IO_CONTROL_61,
	CCP_IO_CONTROL_62,
	CCP_IO_CONTROL_63,
	CCP_IO_CONTROL_NUM
}CCP_tenIoControl;

/* Define PTS  control enum */
#define CCP_PTS_CONTROL_START		(0x21)
typedef enum CCP_enPtsControlNumber
{
	CCP_PTS_CONTROL_21 = 0,
	CCP_PTS_CONTROL_22,
	CCP_PTS_CONTROL_23,
	CCP_PTS_CONTROL_24,
	CCP_PTS_CONTROL_25,
	CCP_PTS_CONTROL_26,
	CCP_PTS_CONTROL_27,
	CCP_PTS_CONTROL_28,
	CCP_PTS_CONTROL_29,
	CCP_PTS_CONTROL_2A,
	CCP_PTS_CONTROL_2B,
	CCP_PTS_CONTROL_2C,
	CCP_PTS_CONTROL_2D,
	CCP_PTS_CONTROL_2E,
	CCP_PTS_CONTROL_2F,
	CCP_PTS_CONTROL_NUM
}CCP_tenPtsControl;

/* Define PTS  control enum */
#define CCP_PTS_READINF_START		(0x01)
typedef enum CCP_enPtsReadInfNumber
{
	CCP_PTS_READINF_01 = 0,
	CCP_PTS_READINF_02,
	CCP_PTS_READINF_03,
	CCP_PTS_READINF_04,
	CCP_PTS_READINF_05,
	CCP_PTS_READINF_06,
	CCP_PTS_READINF_07,
	CCP_PTS_READINF_08,
	CCP_PTS_READINF_09,
	CCP_PTS_READINF_0A,
	CCP_PTS_READINF_0B,
	CCP_PTS_READINF_0C,
	CCP_PTS_READINF_0D,
	CCP_PTS_READINF_0E,
	CCP_PTS_READINF_0F,
	CCP_PTS_READINF_NUM
}CCP_tenPtsReadInf;

typedef enum CCP_enu8VarNumber
{
	CCP_nu8CaliMsgTxSwitch = 0,
	CCP_nu8WriteEeprom = 1,
	CCP_nu8SessionState,
	CCP_nu8Max
}CCP_tenu8VarNumber;


/* Define Eeprom operation type */
typedef enum CCP_enFrameType
{
	CCP_nNullFrame = 0x00,		//null frame :  free mode
	CCP_nStartFrame = 0x01,		//including:frame_type(start/mid/end),length,address,eep_data_type(data/field end),data 
	CCP_nMidFrame	= 0x02,		//including:frame_type(start/mid/end),data
	CCP_nEndFrame = 0x03,		//including:frame_type(start/mid/end),data and checksum
	CCP_nInvalidFrame = 0xFF
}CCP_tenFrameType;

typedef enum CCP_enDataType
{
	CCP_nData = 0x00,			//the frame is the data
	CCP_nFieldEnd = 0x01,		//the frame is the end of the field
	CCP_nInvalidData=0xFF
}CCP_tenDataType;

typedef enum CCP_enAckType
{
	CCP_nNullAction = 0x00,
	CCP_nSuccessful,			//transmit or receive msg successfully
	CCP_nCheckSumErr,			//checksum error
	CCP_nTimeOutErr,			//timer out error
	CCP_nFormatErr = 0xFF		//take other condition as error frame
}CCP_tenAckType;

typedef enum CCP_enEepAccessType
{
	CCP_nRWNullAction = 0x00,	//neither read nor write	
	CCP_nReadRamByID = 0x01,	//read ram by id
	CCP_nWriteRamByID = 0x02,	//write ram bye id
	CCP_nReadWholeEep = 0x04,	//Read the whole eeprom table
	CCP_nWriteWholeEep = 0x08,	//write the whole eeprom table
	CCP_nReadEepByID = 0x10,	//read eeprom by id
	CCP_nWriteEepByID = 0x20,	//write eeprom by id
	CCP_nRWError = 0xFF			//error
}CCP_tenEepAccessType;


typedef enum CCP_enDelayResCmd
{
	CCP_nResNullDelay = 0x00,		
	CCP_nDTCCmdDelayRes = 0x01,	
	CCP_nResDelayMax = 0xFF			
}CCP_tenDelayResCmd;

/* define the CCP mode */
typedef enum CCP_enModeType
{
	CCP_nDefaultMode = 0x20,
	CCP_nCalibrationMode = 0x21, /* using in calibration */
	CCP_nObdMode = 0x22, /* using in PTS */
	CCP_nMaxMode = 0x23
}CCP_tenModeType;

typedef enum CCP_enCaliTxType
{
	CCP_nTxCaliByPeroid = 0x00, /*send the calibration frame automatic*/
	CCP_nTxCaliByCommand = 0x01,  /*send the calibration frame when receivce the request,one reuqest one respone*/
	CCP_nTxWayMax=0x02
}CCP_tenCaliTxType;

typedef struct CCP_stRWInfo
{
	uint16 u16DataLen;				//the data length of one line in *.eed
	uint16 u16Address;			//the start address of the current line in *.eed
	uint8 u8DataType;			//data type[data/end]
	uint8 u8FrameType;			//frame type[start/mid/end]	
	uint8 u8Data[16];				//data
	uint8 u8CheckSum;			//check sum
} CCP_tstRWInfo;

typedef struct 
{
	CCP_tstRWInfo ReadInfo;
	CCP_tstRWInfo WriteInfo;
}CCP_tstGlobals;
/* Eeprom operation type end */
typedef struct
{
	uint16 u16Address;
	uint8 u8DataLeft;	
} CCP_tstEEPOperation;



typedef enum CCP_enu8MACCtr
{
    CCP_nu8MACCancleCtr = 0,
	CCP_nu8MACPosDrForce = 0x01,
    CCP_nu8MACPosDrNormal = 0x02,
	CCP_nu8MACPosPsForce = 0x03,
    CCP_nu8MACPosPsNormal = 0x04,    
	CCP_nu8MACCtrMax
}CCP_tenu8MACCtrVarNum;


typedef enum CCP_enu8AirdCtr
{
    CCP_nu8AirdCancleCtr = 0,
	CCP_nu8AirdPosForce = 0x01,
    CCP_nu8AirdPosNormal = 0x02, 
 	CCP_nu8AirdModeStsForce = 0x03,
    CCP_nu8AirdModeStsNormal = 0x04,    
	CCP_nu8AirdCtrMax
}CCP_tenu8AirdCtrVarNum;


typedef enum CCP_enu8RfaCtr
{
    CCP_nu8RfaCancleCtr = 0,
	CCP_nu8RfaPosForce = 0x01,
    CCP_nu8RfaPosNormal = 0x02, 
	CCP_nu8RfaPercentForce = 0x03,
    CCP_nu8RfaPercentNormal = 0x04,     
	CCP_nu8RfaCtrMax
}CCP_tenu8RfaCtrVarNum;

typedef enum CCP_enu8BctlCtr
{
    CCP_nu8BctlCancleCtr = 0,
	CCP_nu8BctlVoltageCaliForce = 0x01,
    CCP_nu8BctlVoltageCaliNormal = 0x02, 
    CCP_nu8BctlSpdCaliForce = 0x03,
    CCP_nu8BctlSpdCaliNormal = 0x04,
    CCP_nu8BctlRelayPTSForce = 0x81,
    CCP_nu8BctlSpdPTSForce = 0x82,    
	CCP_nu8BctlCtrMax
}CCP_tenu8BctlCtrVarNum;



typedef enum CCP_enu8AcccCtr
{
    CCP_nu8AcccCancleCtr = 0,
	CCP_nu8AcccActualReqCaliForce = 0x01,
    CCP_nu8AcccActualReqCaliNormal = 0x02, 
 	CCP_nu8AcccActualReqPTSForce = 0x81,
 	CCP_nu8AcccChillerPTSCtr = 0x82,
 	CCP_nu8AcccRefrigerationPTSCtr = 0x83,
	CCP_nu8AcccCtrMax
}CCP_tenu8AcccCtrVarNum;

typedef enum CCP_enu8IONCtr
{
    CCP_nu8IONCancleCtr = 0,
	CCP_nu8IONReqForce = 0xA1,
    CCP_nu8IONReqNormal = 0xA2, 
	CCP_nu8IONPM25OutPutPTSForce = 0x81,
	CCP_nu8IONPM25CleanModePTSForce = 0x82,
	CCP_nu8IONPM25IonModePTSForce = 0x83,
	CCP_nu8IONCtrMax
}CCP_tenu8IONCtrVarNum;

typedef enum CCP_enu8DIMCtr
{
    CCP_nu8DIMCancleCtr = 0, 
 	CCP_nu8LedPWMPTSForce = 0x81, 
 	CCP_nu8LcdPWMPTSForce = 0x82, 
 	CCP_nu8SymbolPWMPTSForce = 0x83, 
 	CCP_nu8LedGroup1PTSForce = 0x84, 
 	CCP_nu8LedGroup2PTSForce = 0x85,  	     
	CCP_nu8DIMCtrMax
}CCP_tenu8DIMCtrVarNum;


typedef enum CCP_enu8PowCtr
{
    CCP_nu8PowCancleCtr = 0,
	CCP_nu8Pow5vFbCaliForce = 0x01,
    CCP_nu8Pow5vFbCaliNormal = 0x02, 
	CCP_nu8PowKL30FbCaliForce = 0x03,
    CCP_nu8PowKL30FbCaliNormal = 0x04, 
	CCP_nu8PowKL15FbCaliForce = 0x05,
    CCP_nu8PowKL15FbCaliNormal = 0x06,
	CCP_nu8Pow5vOutPutPTSForce = 0x81,    
 	CCP_nu8PowSenSupplyPTSForce = 0x82, 
	CCP_nu8PowCtrMax
}CCP_tenu8PowCtrVarNum;

typedef enum CCP_enu8KnobCtr
{
    CCP_nu8KnobCancleCtr = 0,
	CCP_nu8KnobStartTestPTSForce = 0x81,
    CCP_nu8KnobStopTestPTSForce = 0x82, 
	CCP_nu8KnobCtrMax
}CCP_tenu8KnobCtrVarNum;


typedef enum CCP_enu8DcmCtr
{
    CCP_nu8DcmCancleCtr = 0,
	CCP_nu8DcmMixAirDrPTSForce = 0x81,
    CCP_nu8DcmMixAirPsPTSForce = 0x82, 
	CCP_nu8DcmAirdPTSForce = 0x83,
    CCP_nu8DcmRfaPTSForce = 0x84, 
    CCP_nu8DcmDefPTSForce = 0x85,
    CCP_nu8DcmAllPTSForce = 0x86,
	CCP_nu8DcmCtrMax
}CCP_tenu8DcmCtrVarNum;


typedef enum CCP_enu8LcdCtr
{   
    CCP_nu8LcdAllOffCtr = 0, 
    CCP_nu8LcdAllOnCtr,     
	CCP_nu8LcdOddSegOnCtr,
    CCP_nu8LcdEvenSegOnCtr, 
    CCP_nu8LcdOddComOnCtr,    
    CCP_nu8LcdEvenComOnCtr,  
    CCP_nu8LcdOnlyCom1OnCtr,    
    CCP_nu8LcdOnlyCom2OnCtr,  
    CCP_nu8LcdOnlyCom3OnCtr,    
    CCP_nu8LcdOnlyCom4OnCtr,      
	CCP_nu8LcdCtrMax
}CCP_tenu8LcdCtrVarNum;

typedef enum CCP_enu8BtmCtr
{
    CCP_nu8BtmCancleCtr = 0,
	CCP_nu8BtmBattBumpPTSForce = 0x81,
    CCP_nu8BtmMotorBumpPTSForce = 0x82, 
    CCP_nu8BtmMainRelayPTSForce = 0x83,
	CCP_nu8BtmCtrMax
}CCP_tenu8BtmCtrVarNum;

typedef enum CCP_enu8HctCtr
{
    CCP_nu8HctCancleCtr = 0,
	CCP_nu8HctPtcBumpPTSForce = 0x81,
	CCP_nu8HctCtrMax
}CCP_tenu8HctCtrVarNum;

#define CCP_nu32ForceFlag       (0x01000000U)


#define CCP_nu32AcccActualReqCaliCtr       (CCP_nu32ForceFlag|((uint32)CCP_nu8AcccActualReqCaliForce<<16u))
#define CCP_nu32AcccActualReqCaliNormal    (CCP_nu32ForceFlag|((uint32)CCP_nu8AcccActualReqCaliNormal<<16u)) 

#define CCP_nu32AcccChillerPTSCtr       (CCP_nu32ForceFlag|((uint32)CCP_nu8AcccChillerPTSCtr<<16u))
#define CCP_nu32AcccRefrigerationPTSCtr    (CCP_nu32ForceFlag|((uint32)CCP_nu8AcccRefrigerationPTSCtr<<16u))

#define  CCP_nu32Pow5vFbCaliForce            (CCP_nu32ForceFlag|((uint32)CCP_nu8Pow5vFbCaliForce<<16u))
#define  CCP_nu32Pow5vFbCaliNormal           (CCP_nu32ForceFlag|((uint32)CCP_nu8Pow5vFbCaliNormal<<16u))
#define  CCP_nu32PowKL30FbCaliForce          (CCP_nu32ForceFlag|((uint32)CCP_nu8PowKL30FbCaliForce<<16u))
#define  CCP_nu32PowKL30FbCaliNormal         (CCP_nu32ForceFlag|((uint32)CCP_nu8PowKL30FbCaliNormal<<16u))
#define  CCP_nu32PowKL15FbCaliForce          (CCP_nu32ForceFlag|((uint32)CCP_nu8PowKL15FbCaliForce<<16u))
#define  CCP_nu32PowKL15FbCaliNormal         (CCP_nu32ForceFlag|((uint32)CCP_nu8PowKL15FbCaliNormal<<16u))
#define  CCP_nu32Pow5vOutPutPTSForce         (CCP_nu32ForceFlag|((uint32)CCP_nu8Pow5vOutPutPTSForce<<16u))    
#define  CCP_nu32PowSenSupplyPTSForce        (CCP_nu32ForceFlag|((uint32)CCP_nu8PowSenSupplyPTSForce<<16u))


#define  CCP_nu32KnobStartTestPTSForce         (CCP_nu32ForceFlag|((uint32)CCP_nu8KnobStartTestPTSForce<<16u))    
#define  CCP_nu32KnobStopTestPTSForce        (CCP_nu32ForceFlag|((uint32)CCP_nu8KnobStopTestPTSForce<<16u))

#define  CCP_nu32DcmMixAirDrPTSForce         (CCP_nu32ForceFlag|((uint32)CCP_nu8DcmMixAirDrPTSForce<<16u))    
#define  CCP_nu32DcmMixAirPsPTSForce        (CCP_nu32ForceFlag|((uint32)CCP_nu8DcmMixAirPsPTSForce<<16u))
#define  CCP_nu32DcmAirdPTSForce         (CCP_nu32ForceFlag|((uint32)CCP_nu8DcmAirdPTSForce<<16u))    
#define  CCP_nu32DcmRfaPTSForce        (CCP_nu32ForceFlag|((uint32)CCP_nu8DcmRfaPTSForce<<16u))
#define  CCP_nu32DcmDefPTSForce        (CCP_nu32ForceFlag|((uint32)CCP_nu8DcmDefPTSForce<<16u))
#define  CCP_nu32DcmAllPTSForce        (CCP_nu32ForceFlag|((uint32)CCP_nu8DcmAllPTSForce<<16u))


#define CCP_nu32AcccActualReqPTSForce    (CCP_nu32ForceFlag|((uint32)CCP_nu8AcccActualReqPTSForce<<16u))

#define  CCP_nu32BctlVoltageCaliForce    (CCP_nu32ForceFlag|((uint32)CCP_nu8BctlVoltageCaliForce<<16u))
#define  CCP_nu32BctlVoltageCaliNormal   (CCP_nu32ForceFlag|((uint32)CCP_nu8BctlVoltageCaliNormal<<16u))
#define  CCP_nu32BctlSpdCaliForce        (CCP_nu32ForceFlag|((uint32)CCP_nu8BctlSpdCaliForce<<16u))
#define  CCP_nu32BctlSpdCaliNormal       (CCP_nu32ForceFlag|((uint32)CCP_nu8BctlSpdCaliNormal<<16u))
#define  CCP_nu32BctlRelayPTSForce       (CCP_nu32ForceFlag|((uint32)CCP_nu8BctlRelayPTSForce<<16u))
#define  CCP_nu32BctlSpdPTSForce         (CCP_nu32ForceFlag|((uint32)CCP_nu8BctlSpdPTSForce<<16u))

#define  CCP_nu32LedPWMPTSForce          (CCP_nu32ForceFlag|((uint32)CCP_nu8LedPWMPTSForce<<16u))
#define  CCP_nu32LcdPWMPTSForce          (CCP_nu32ForceFlag|((uint32)CCP_nu8LcdPWMPTSForce<<16u))
#define  CCP_nu32SymbolPWMPTSForce       (CCP_nu32ForceFlag|((uint32)CCP_nu8SymbolPWMPTSForce<<16u))
#define  CCP_nu32LedGroup1PTSForce       (CCP_nu32ForceFlag|((uint32)CCP_nu8LedGroup1PTSForce<<16u))
#define  CCP_nu32LedGroup2PTSForce       (CCP_nu32ForceFlag|((uint32)CCP_nu8LedGroup2PTSForce<<16u))

#define  CCP_nu32LcdTestPTSCtr            (CCP_nu32ForceFlag|((uint32)0x81U<<16)) 
#define  CCP_nu32MMIResetPTSCtr           (CCP_nu32ForceFlag|((uint32)0x81U<<16)) 
#define  CCP_nu32DTClearPTSCtr            (CCP_nu32ForceFlag|((uint32)0x81U<<16)) 
#define  CCP_nu32SysQuiescentPTSCtr       (CCP_nu32ForceFlag|((uint32)0x81U<<16)) 

#define  CCP_nu32IONPM25OutPutPTSForce        (CCP_nu32ForceFlag|((uint32)CCP_nu8IONPM25OutPutPTSForce<<16u))
#define  CCP_nu32IONPM25CleanModePTSForce        (CCP_nu32ForceFlag|((uint32)CCP_nu8IONPM25CleanModePTSForce<<16u))
#define  CCP_nu32IONPM25IonModePTSForce        (CCP_nu32ForceFlag|((uint32)CCP_nu8IONPM25IonModePTSForce<<16u))

#define  CCP_nu32RdcPTSCtr       (CCP_nu32ForceFlag|((uint32)0x81U<<16))
#define  CCP_nu32ShcLPTSCtr       (CCP_nu32ForceFlag|((uint32)0x81U<<16)) 
#define  CCP_nu32ShcRPTSCtr       (CCP_nu32ForceFlag|((uint32)0x82U<<16))
#define  CCP_nu32KeyStartTestPTSForce         (CCP_nu32ForceFlag|((uint32)0x81U<<16u))

#define CCP_nu32BtmBattBumpPTSForce    (CCP_nu32ForceFlag|((uint32)CCP_nu8BtmBattBumpPTSForce<<16u))
#define CCP_nu32BtmMotorBumpPTSForce    (CCP_nu32ForceFlag|((uint32)CCP_nu8BtmMotorBumpPTSForce<<16u))
#define CCP_nu32HctPtcBumpPTSForce    (CCP_nu32ForceFlag|((uint32)CCP_nu8HctPtcBumpPTSForce<<16u))

#define CCP_nu32BtmMainRelayPTSForce    (CCP_nu32ForceFlag|((uint32)CCP_nu8BtmMainRelayPTSForce<<16u))

#define nRESET_VECTOR 		0
typedef  void(**tppvFunc)(void);
#define  vSysReset()  (*(tppvFunc)(nRESET_VECTOR))()


#endif

/*****************************************************************************
* EOF:
******************************************************************************/
