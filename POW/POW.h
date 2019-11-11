/*******************************************************************************
| Module Name: Power manage model
| File Name: pow.h
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
| Du Zejia                             Desay SV Automotive Co., Ltd
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date             Ver        	Author               Description
| ----------  -------  -------------  -------------------------------------------------
| 
|2014/08/01 Rev 01.00.00      Syc       			 The first version  
********************************************************************************/

/*****************************************************************************
* FILE DECLARATION
******************************************************************************/
#ifndef POW_H
#define POW_H

#ifndef POW_C
  #define pow_ext extern
#else
  #define pow_ext
#endif

#include "Pow_Type.h" 
#include "POW_If.h"

pow_ext void POW_vReset(void);
pow_ext void POW_vMain(void);
pow_ext void POW_vWakeUp(void);
pow_ext void POW_vObdMain(void);
pow_ext void POW_vInit(void);
//pow_ext void Std_ReturnType POW_u8ForceIoControl_Write(/*IN*/uint32 ForceIoControlWord);
Std_ReturnType POW_u8ForceIoControl_Write(/*IN*/uint32 ForceIoControlWord);




/*****************************************************************************
* End of check if informations are already included
******************************************************************************/
#endif                                  /* ifndef POW_H */

/*****************************************************************************
* EOF: Pow.h
******************************************************************************/

