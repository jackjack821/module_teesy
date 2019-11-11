/*******************************************************************************
| Module Name: directed current motor
| File Name: DCM.h
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
#ifndef DCM_H
#define DCM_H


/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
******************************************************************************/
/* Own headerfiles */
#include "DCM_Type.h"

 typedef enum 
{
	DCM_nu8MixDrDirection=0, 
	DCM_nu8AirdDirection, 
	DCM_nu8RfaDirection, 
	DCM_nu8MixPsDirection, 
	DCM_nu8MixDrErrorCode,
	DCM_nu8AirdErrorCode,
	DCM_nu8RfaErrorCode,
	DCM_nu8MixPsErrorCode,
	DCM_nu8SwVersion, 
	DCM_nu8Valid,
	DCM_nu8MotorDriver,
	DCM_nu8OutputMax
}DCM_nu8OutputVarNumber;

 typedef enum 
{
	DCM_nu16AdValueMixDr=0, 
	DCM_nu16AdValueAird, 
	DCM_nu16AdValueRfa, 
	DCM_nu16AdValueMixPs,
	DCM_nu16AdRawValueMixDr, 
	DCM_nu16AdRawValueAird, 
	DCM_nu16AdRawValueRfa, 
	DCM_nu16AdRawValueMixPs,
	DCM_nu16KeyPress, /*GET touch*/
	DCM_nu16ForcePress,
	DCM_nu16KeyRawPress,
	DCM_nu16OutputMax
}DCM_nu16OutputVarNumber;
/*****************************************************************************
* EXPORT INTERFACE FUNCTION PROTOTYPES
*
* In this section declare
* - all system global function prototypes of your module.
******************************************************************************/

void DCM_vMain(void);
void DCM_vOBD(void);
void DCM_vInit(void);
void DCM_vReset(void);
void DCM_vDeinit (void);

uint8 DCM_u8GetValue(DCM_nu8OutputVarNumber enIndex);
uint16 DCM_u16GetValue(DCM_nu16OutputVarNumber enIndex);
Std_ReturnType DCM_u8ForceIoControl_Write (/*IN*/uint32 ForceIoControlWord);


 void MotorGSID_duty_set(uint32 y);
 void DCM_MCU_u8motortime_set(uint32 y);
 void DCM_MotorVibrateCycle_set(uint32 y);
 void DCM_motor_duty_set(uint32 y);



/*****************************************************************************
* End of check if informations are already included
******************************************************************************/
#endif                                  /* ifndef */

/*****************************************************************************
* EOF: DCM.h
******************************************************************************/

