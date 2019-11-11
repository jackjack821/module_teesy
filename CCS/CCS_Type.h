/*******************************************************************************
| Module Name: Calculate the target blowout temp ,target set temo and SI
| File Name: CCS.c
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
| Sui Yanchun                        Desay SV Automotive Co., Ltd
| Zhang Shuncong                     Desay SV Automotive Co., Ltd
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date             Ver         Author               Description
| ----------  -------  -------------  -------------------------------------------------
| 2013-04-09  1.00        Sui Yanchun       First implementation
| 2015/07/14  2.00        Zhang Shuncong    Add CW and CCW,RTE define
| 2015-09-06  3.00        Zhang Shuncong    Add mix air curve according to hct temp
********************************************************************************/
#ifndef CCS_TYPE_H
#define CCS_TYPE_H

#define CCS_IctSensorNum 2
#define CCS_UseCtsInput

/*****************************************************************************
* Define the enum to present the variable for extern model call.
******************************************************************************/

/******************************************************************************/

/*define the bit position for Error Code*/
typedef enum
{
	CCS_nBitInputValueErr = 0,
	CCS_nBitMax,
}CCS_tenErrorCode;

#endif                                  /* ifndef */
