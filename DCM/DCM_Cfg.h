/*******************************************************************************
| Module Name: directed current motor
| File Name: DCM_Cfg.h
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
#ifndef DCM_CFG_H
#define DCM_CFG_H


#include "DCM_Private.h"






/*****************************************************************************
* PIN defined
*
* PIN defined for this mode
******************************************************************************/
/*Motor 0****************************************************************/
#define DCM_LeftMix_Hot_Port		(PORT_ID_12)
#define DCM_LeftMix_Hot_Pin		(PIN_ID_7)
#define DCM_LeftMix_Cold_Port		(PORT_ID_12)
#define DCM_LeftMix_Cold_Pin		(PIN_ID_6)

/*Motor 1**************************************************************/
#define DCM_Mode_Def_Port		(PORT_ID_10)
#define DCM_Mode_Def_Pin		(PIN_ID_3)
#define DCM_Mode_Vent_Port		(PORT_ID_10)
#define DCM_Mode_Vent_Pin		(PIN_ID_2)

/*Motor 2**************************************************************/
#define DCM_REC_Port			(PORT_ID_9)
#define DCM_REC_Pin			(PIN_ID_7)
#define DCM_Fresh_Port			(PORT_ID_10)
#define DCM_Fresh_Pin			(PIN_ID_0)

/*Motor 3***************************************************************/
#define DCM_RightMix_Hot_Port	(PORT_ID_6)
#define DCM_RightMix_Hot_Pin	(PIN_ID_6)
#define DCM_RightMix_Cold_Port	(PORT_ID_6)
#define DCM_RightMix_Cold_Pin	(PIN_ID_5)

/**==============================================================================*
#define DCM_biMotor0_1_Mode()    HAL_PinConfig( DCM_LeftMix_Hot_Port, DCM_LeftMix_Hot_Pin,  PIN_DIR_OUTPUT)
#define DCM_biMotor0_2_Mode()    HAL_PinConfig( DCM_LeftMix_Cold_Port, DCM_LeftMix_Cold_Pin,  PIN_DIR_OUTPUT)

#define DCM_biMotor0_1(value)    HAL_PinWrite( DCM_LeftMix_Hot_Port, DCM_LeftMix_Hot_Pin,  value)
#define DCM_biMotor0_2(value)    HAL_PinWrite( DCM_LeftMix_Cold_Port, DCM_LeftMix_Cold_Pin,  value)

*-------------------------------------------------------------------------------*

#define DCM_biMotor1_1_Mode()    HAL_PinConfig( DCM_Mode_Def_Port, DCM_Mode_Def_Pin,  PIN_DIR_OUTPUT)
#define DCM_biMotor1_2_Mode()    HAL_PinConfig( DCM_Mode_Vent_Port, DCM_Mode_Vent_Pin,  PIN_DIR_OUTPUT)

#define DCM_biMotor1_1(value)    HAL_PinWrite( DCM_Mode_Def_Port, DCM_Mode_Def_Pin,  value)
#define DCM_biMotor1_2(value)    HAL_PinWrite( DCM_Mode_Vent_Port, DCM_Mode_Vent_Pin,  value)

*-------------------------------------------------------------------------------*

#define DCM_biMotor2_1_Mode()    HAL_PinConfig( DCM_Fresh_Port, DCM_Fresh_Pin,  PIN_DIR_OUTPUT)
#define DCM_biMotor2_2_Mode()    HAL_PinConfig( DCM_REC_Port, DCM_REC_Pin,  PIN_DIR_OUTPUT)

#define DCM_biMotor2_1(value)    HAL_PinWrite( DCM_Fresh_Port, DCM_Fresh_Pin,  value)
#define DCM_biMotor2_2(value)    HAL_PinWrite( DCM_REC_Port, DCM_REC_Pin,  value)

**==============================================================================*/


/*****************************************************************************
*SPI dcm driver Channel define
*****************************************************************************/
#define DCMspi_nChannel1        (0)
#define DCMspi_nChannel2        (1)
#define DCMspi_nChannel3        (2)
#define DCMspi_nChannel4        (3)
#define DCMspi_nChannel5        (4)
#define DCMspi_nChannel6        (5)
#define DCM_biMix1Channel		(DCMspi_nChannel1)
#define DCM_biMix2Channel		(DCMspi_nChannel2)
#define DCM_biAird1Channel		(DCMspi_nChannel3)
#define DCM_biAird2Channel		(DCMspi_nChannel4)
#define DCM_biRFA1Channel		(DCMspi_nChannel5)
#define DCM_biRFA2Channel		(DCMspi_nChannel6)


/*****************************************************************************
* MACROS
*
* Functional macros defined.
******************************************************************************/
#define ENABLECORRECTPTAFB		/*correct PTA FB function*/
#define DISABLERESTDRIVING
#define ENABLEBLOCKCHECKDRIVING

/*****************************************************************************
* MACROS
*
* In this section declare
* - all macros used in the configuration file and C file.
******************************************************************************/



/*****************************************************************************
* MODULE CONFIGURATION DEFINITIONS
*
* In this section declare
* - all module configuration defines which should be generated.
******************************************************************************/
#define nRest_Config							(16u)
#define DCM_u16RestActiveTime_Config			(300u)/*rest driving time*/
#define DCM_RestDuty_Config						(3u)/*rest driving duty  for example 2 driving duty 1/3*/

#define DCM_DetectTime_Config					(50u)/*0.5seconds*/
#define DCM_BlockPreTrime1_Config				(250u)/*2.5seconds*/
#define DCM_BlockPreTrime2_Config				(200u)/*2.0seconds*/
#define DCM_BlockPreTrime3_Config				(250u)/*2.0seconds*/
#define DCM_BlockRetryTmr                       (1800)/*1800seconds*/
#define DCM_BlockRetryCounter                   (3)


#define DCM_DeltaADFactor_Config				(8u)/*256*/
#define DCM_PreTrime1_Config					(250u)/*2.5seconds*/
#define DCM_PreDringCounter_Config				(8u)
#define DCM_PreTrime2_Config				  	(200u)/*2.0seconds*/

#define    MotorNum     (DCM_nPort)
/*****************************************************************************
* MODULE CONFIGURATION DECLARATIONS
*
* In this section declare
* - module variable declarations for the variable in the cfg.c file, which will be used in module
     functions.
******************************************************************************/

/**************************Config Parameter************************************/
extern DCM_tstMotorProperty DCM_stMotorProperty[MotorNum];
#ifdef PINDRIVER
extern DCM_tstMotorPinSts DCM_astMotorSetPIN[MotorNum];
#endif



/*****************************************************************************
* End of check if informations are already included
******************************************************************************/
#endif                                  /* ifndef */

/*****************************************************************************
* EOF: DCM_Cfg.h
******************************************************************************/

