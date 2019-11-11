/*******************************************************************************
| Module Name: directed current motor
| File Name: DCM_Private.c
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
| Li Jiaye                        Desay SV Automotive Co., Ltd
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date             Ver         Author               Description
| ----------  -------  -------------  ------------------------------------------
| 2014.7.17         A0      Li jiaye         module template update. 
| 2014.8.21         A1      Li jiaye         module code updated after coding reviewed.
| 2015.3.29	        A2      Li Jiaye	     add DCM property config
| 2016.2.17         A3      Li Jiaye         module upgraded
| 2016.4.19         A4      Li Jiaye         For base code creating
| 
| 
********************************************************************************/

/*****************************************************************************
* FILE DECLARATION
******************************************************************************/
#ifndef DCM_PRIVATE_H
#define DCM_PRIVATE_H



/*****************************************************************************
* LOCATION-DEFINES -only when the location assignment is needed.
******************************************************************************/

/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
******************************************************************************/
/* System-headerfiles */

/* Please put the headerfiles which related to system here! */

/* Foreign headerfiles */
#include "Rte_internal.h"


/* Own headerfiles */


/*******************************************************************************
* EXPORT INTERFACE DEFINITIONS AND DECLARATIONS
*
* In this section
* - define helpful macros for easy data access and for a comfortable function use, if 
*   necessary.
* - define all macros for accessing the external module interfaces variables
* - define all macros which not need to be configed and changed for this module 
******************************************************************************/
/*Ccp/diag/pts force control*/
typedef enum
{
	Dcm_nSetMixDrMotorFb=0u,
	Dcm_nSetAirdMotorFb,
	Dcm_nSetRfaMotorFb,
	Dcm_nSetMixPsMotorFb,
	Dcm_nCcpForceMax
}CcpControl_Dcm;
#define DcmGetCcpForceBit(index)	((uint8)(Dcm_CcpForceFlag>>(index))&0x01u)
#define DcmSetCcpForceBit(index)	(Dcm_CcpForceFlag=((uint16)Dcm_CcpForceFlag|(uint16)(((uint16)0x01u<<(index)))))
#define DcmClrCcpForceBit(index)	(Dcm_CcpForceFlag=((uint16)Dcm_CcpForceFlag&(uint16)(~(uint16)((uint16)0x01u<<(index)))))
#define DcmClrCcpForceByte(void)	(Dcm_CcpForceFlag=0u)

/**************************Internal Module define******************************/
#define DCM_u8Shot2VccErrCodeSet(index)		do{DCM_au8ErrorCode[(index)]|=0x01u;}while(0)
#define DCM_u8Shot2VccErrCodeClr(index)		do{DCM_au8ErrorCode[(index)]&=0xFEu;}while(0)
#define DCM_u8Shot2GndErrCodeSet(index)		do{DCM_au8ErrorCode[(index)]|=0x02u;}while(0)
#define DCM_u8Shot2GndErrCodeClr(index)		do{DCM_au8ErrorCode[(index)]&=0xFDu;}while(0)
#define DCM_u8BlockErrCodeSet(index)		do{DCM_au8ErrorCode[(index)]|=0x04u;}while(0)
#define DCM_u8BlockErrCodeClr(index)		do{DCM_au8ErrorCode[(index)]&=0xFBu;}while(0)
#define DCM_u8PowFailErrCodeSet(index)		do{DCM_au8ErrorCode[(index)]|=0x08u;}while(0)
#define DCM_u8PowFailErrCodeClr(index)		do{DCM_au8ErrorCode[(index)]&=0xF7u;}while(0)
#define DCM_u8OpenLoadErrCodeSet(index)	    do{DCM_au8ErrorCode[(index)]|=0x10u;}while(0)
#define DCM_u8OpenLoadErrCodeClr(index)		do{DCM_au8ErrorCode[(index)]&=0xEFu;}while(0)
#define DCM_u8OverCurrentErrCodeSet(index)	do{DCM_au8ErrorCode[(index)]|=0x20u;}while(0)
#define DCM_u8OverCurrentErrCodeClr(index)	do{DCM_au8ErrorCode[(index)]&=0xDFu;}while(0)
#define DCM_u8OverTempErrCodeSet(index)	    do{DCM_au8ErrorCode[(index)]|=0x40u;}while(0)
#define DCM_u8OverTempErrCodeClr(index)		do{DCM_au8ErrorCode[(index)]&=0xBFu;}while(0)

#define DCM_boGetFeedbackError(index)       ((DCM_au8ErrorCode[(index)]&0x03u)>0u)

/**************************Extern Module Interface*****************************/

#define DCM_GetMacTargetPos              Mac_u16GetTargetPosDr 
#define DCM_GetAirdTargetPos              Aird_u16GetTargetPos
#define DCM_GetRfaTargetPos               Rfa_u16GetTargetPos
#define DCM_GetMacPsTargetPos             Mac_u16GetTargetPosPs

//#define DCM_GetMacCurrentPos              Rte_Call_Dcm_DcmProto_Dcm_ReadAd_MixMotorPsFb_Read	/*dr and ps invert*/
#define DCM_GetAirdCurrentPos             Rte_Call_IoHwAd_IoHwAd_ReadAd_DcmAirdMotorFB_Read
#define DCM_GetRfaCurrentPos              Rte_Call_IoHwAd_IoHwAd_ReadAd_DcmRfaMotorFB_Read
//#define DCM_GetMacPsCurrentPos            Rte_Call_Dcm_DcmProto_Dcm_ReadAd_MixMotorDrFb_Read 


#define DCM_GetMacCurrentPos              Rte_Call_IoHwAd_IoHwAd_ReadAd_DcmMixMotorDrFB_Read
#define DCM_GetMacPsCurrentPos            Rte_Call_IoHwAd_IoHwAd_ReadAd_DcmMixMotorPsFB_Read

//#define DCM_MotorVibrateTimer           2/**20ms**/
//#define DCM_MotorVibrateCycle           10/**50ms**/

//#define MotorVibrateType           MotorVibrate_PWM
#define MotorVibrate_Timer           1u
#define MotorVibrate_PWM           2u

#define DCM_u16GetKeyKeyPressed      		 (KEY_u16PressedKey())
#define DCM_u8GetForceSensorPressed(Num)             (ForceSensor_u8GetValue(Num))
#define DCM_u32GetKeyKeyPressed      		 (KEY_u32KeyStatusIsPress())  //
/*******************************************************************************
* End of check if informations are already included
*******************************************************************************/
#endif                                  /* ifndef DCM_PRIVATE_H*/

/*******************************************************************************
* EOF: DCM.h
*******************************************************************************/


