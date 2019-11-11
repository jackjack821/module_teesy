/*******************************************************************************
| Module Name: Non-Aspirated Temperature Private definition
| File Name: NAT_Private.h
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
| 2016-8-18    1.0  Luo Xindian		 frist created 
********************************************************************************/

/*****************************************************************************
* FILE DECLARATION
******************************************************************************/
#ifndef NAT_PRIVATE_H
#define NAT_PRIVATE_H


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

/**************************Extern Module Interface*******************************/

/*************************Extern Module Interface End****************************/

/***************************No Config Parameter********************************/
//here will define the macro which not to be changed for ever
#define NAT_nUseForDebug				False

#define NAT_OpenInterfaces_Cfg   (Yes)  /* Yes is to open Getvalue and GetBuffer interfaces*/

#define NAT_Get100msFlag		(uint8)FRAME_u16GetValue(SYS_nu16Flag1000MS_BG)

#define NAT_GetHighVoltage		(uint8)POW_u16GetValue(POW_nu16AppHighVoltage)
#define NAT_GetLowVoltage		(uint8)POW_u16GetValue(POW_nu16AppLowVoltage)

#define NAT_GetOatValue			OAT_u16GetValue(OAT_nu16Value)

#define NAT_GetSurfaceTempAd(Value)	Rte_Call_IoHwAd_IoHwAd_ReadAd_IncarTemp_Read(Value)
#define NAT_GetPCBTempAd(Value)		Rte_Call_IoHwAd_IoHwAd_ReadAd_PcbNtcValue_Read(Value)
#define NAT_GetIRAd(Value)				Rte_Call_IoHwAd_IoHwAd_ReadAd_IncarSun_Read(Value)

/*************************No Config Parameter End******************************/
#if(NAT_nUseCCP ==True)

#define NatGetCcpForceBit(index)	((NAT_CcpForceFlag>>index)&0x01u)
#define NatSetCcpForceBit(index)	(NAT_CcpForceFlag=NAT_CcpForceFlag|(0x01u<<index))
#define NatClrCcpForceBit(index)	(NAT_CcpForceFlag=NAT_CcpForceFlag&(~(0x01u<<index)))
#define NatClrCcpForceByte()	    (NAT_CcpForceFlag=0u)

#endif

#define NAT_n8DynTmr				(10u)

#define NAT_u8Valid					(NAT_au8Array[NAT_nu8Valid])
#define NAT_u8Value					(NAT_au8Array[NAT_nu8Value])

#define NAT_u16Value				(NAT_au16Array[NAT_nu16Value])
#define NAT_u16ErrorCode			(NAT_au16Array[NAT_nu16ErrorCode])
#define NAT_u16SurfaceTemp			(NAT_au16Array[NAT_nu16SurfaceTemp])
#define NAT_u16PcbTemp				(NAT_au16Array[NAT_nu16PcbTemp])
#define NAT_u16IRSunLoad			(NAT_au16Array[NAT_nu16IRSunLoad])
#define NAT_u16DynOffset			(NAT_au16Array[NAT_nu16DynOffset])
#define NAT_u16StaOffset				(NAT_au16Array[NAT_nu16StaOffset])
#define NAT_u16TmlOffset			(NAT_au16Array[NAT_nu16TmlOffset])
#define NAT_u16RayOffset			(NAT_au16Array[NAT_nu16RayOffset])
#define NAT_u16TempDiff				(NAT_au16Array[NAT_nu16TempDiff])

#define NAT_au8OatOfsStep			(5u)
#define NAT_nOffsetMin				(- 0x280U)
#define NAT_nOffsetMax				(SCHAR_MAX*5)
#define NAT_nOffset					(0x280U)

#define NAT_nNumOf10Sec					(1u)
/*NATS Filter parameter.*/
#define NAT__DampingK						(6u)

#define NAT_nDynFilterK						(7u)

#define NAT_nSwVersion				(0x0001)
/*****************************************************************************
* End of check if informations are already included
******************************************************************************/
#endif                                  /* ifndef NAT_PRIVATE_H*/

/*****************************************************************************
* EOF: 
******************************************************************************/
