/*******************************************************************************
| Module Name: start stop Function module(Idle engine stop )
| File Name: EVAP_Private.h
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
| Luo Xindian                             Desay SV Automotive Co., Ltd
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date             Ver         Author               Description
| ----------  -------  -------------  -------------------------------------------------
| 2015-10-15    1.0  Luo Xindian		 frist created,for general start stop function 
| 2016-2-18      1.1  Luo Xindian		Modified for KC-2
********************************************************************************/

/*****************************************************************************
* FILE DECLARATION
******************************************************************************/
#ifndef RFA_PRIVATE_H
#define RFA_PRIVATE_H


/*****************************************************************************
* LOCATION-DEFINES -only when the location assignment is needed.
******************************************************************************/

/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
******************************************************************************/
/* System-headerfiles */

/* Please put the headerfiles which related to system here! */

/* Foreign headerfiles */

/* Please put the headerfiles which related to foreign here! */


/* Own headerfiles */


/*****************************************************************************
* EXPORT INTERFACE DEFINITIONS AND DECLARATIONS
*
* In this section
* - define helpful macros for easy data access and for a comfortable function use, if 
*   necessary.
* - define all macros for accessing the external module interfaces variables
* - define all macros which not need to be configed and changed for this module 
******************************************************************************/
#define EVAP_nSwVersion		(0xA3)
/**************************Extern Module Interface*******************************/

#define EVAP_OpenInterfaces_Cfg   (Yes)  /* Yes is to open Getvalue and GetBuffer interfaces*/

/* */
#define EVAP_u8Valid					EVAP_au8Array[EVAP_nu8Valid]
#define EVAP_u8SwVersion				EVAP_au8Array[EVAP_nu8SwVersion]
#define EVAP_u8SensorFailsafe			EVAP_au8Array[EVAP_nu8SensorFailsafe]

#define EVAP_u16SensorAdValue			EVAP_au16Array[EVAP_nu16SensorAdValue]
#define EVAP_u16RawValue				EVAP_au16Array[EVAP_nu16RawValue]
#define EVAP_u16ResultTemp				EVAP_au16Array[EVAP_nu16ResultTemp]
#define EVAP_u16FastEvapTemp			EVAP_au16Array[EVAP_nu16AcValue]
#define EVAP_u16ErrorCode				EVAP_au16Array[EVAP_nu16ErrorCode]

#define EVAP_nUseCCP    True
#if(EVAP_nMacEvapTempCfg == True)
#define EVAP_u16MacValue				EVAP_au16Array[EVAP_nu16MacValue]
#endif

#if (EVAP_nDynOffsCfg == True)
#define EVAP_u16DynOffset				EVAP_au16Array[EVAP_nu16DynOffset]
#endif

#if( EVAP_nUseRTE == False)
#define EVAP_u8GetPtaValue(Num)			PTA_u8GetValue(Num)
#define EVAP_u16GetPtaValue(Num)		PTA_u16GetValue(Num)

//get diag tag and value
#define   Evap_u16GetDiaValue(Num)    	CCP_u16GetValue(Num)// CCP_u8GetValue(Num) 
#define   Evap_boGetDiaValue(Num)     	       CCP_boGetValue(Num)//CCP_boGetValue(Num) 
#define   EVAP_u8PtaPowValue(Num)		PTA_u8GetPowValue(Num)

#endif

#define EVAP_u8GetSysValue()		FRAME_u16GetValue(SYS_nu16Flag1000MS_BG)

/*************************Extern Module Interface End****************************/

/***************************No Config Parameter********************************/
//here will define the macro which not to be changed for ever

/* Macros */
#define EVAP_u8FilterTimer			2

#define EVAP_u8FilterKMac			3

#define EVAP_u8FilterK				1

#define EVAP_u16DadaOffset			0x0280 /*according to 16 bit value format,0 is 0x0280(640)*/

#if( EVAP_nDynOffsCfg == True)
/* EVAP Dyn offset cal*/
#define EVAP_nEvaDynOffsTblLen   		(EVAP_nEvapDynOffsTbl_Len)//(EED_nEvapDynOffs_X_Len ) 
#define EVAP_au16EvaDynOffsX_Tbl  		(EVAP_au16EvapDynOffs_X)//(EED_au16EvapDynOffs_X)
#define EVAP_au16EvaDynOffsY_Tbl  		(EVAP_au16EvapDynOffs_Y)//(EED_au16EvapDynOffs_Y)
#endif

#define Evap_Temp_MAX					((uint16)(120+40)*10)
#define Evap_Temp_MIN					((uint16)(-40+40)*10)

#define Evap_TempDiff_UMAX				(uint16)(640*2)
#define Evap_TempDiff_UMIN				(uint16)(0)

#if (EVAP_nUseCCP == True)
/*Ccp control*/
typedef enum
{
	EVAP_nSetSensorAD=0,
	EVAP_nSetSensorTemp,
	EVAP_nCcpForceMax
}CcpControl_EVAP;

#define EVAP_vGetCcpForceBit(index)	((EVAP_u8CcpForceFlag>>index)&0x01)
#define EVAP_vSetCcpForceBit(index)	(EVAP_u8CcpForceFlag=EVAP_u8CcpForceFlag|(0x01<<index))
#define EVAP_vClrCcpForceBit(index)	(EVAP_u8CcpForceFlag=EVAP_u8CcpForceFlag&(~(0x01<<index)))
#define EVAP_vClrCcpForceByte(void)	(EVAP_u8CcpForceFlag=0)
#endif

/*************************No Config Parameter End******************************/


/*****************************************************************************
* End of check if informations are already included
******************************************************************************/
#endif                                  /* ifndef RFA_PRIVATE_H*/

/*****************************************************************************
* EOF: RFA.h
******************************************************************************/
