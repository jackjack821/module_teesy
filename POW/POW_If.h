/*******************************************************************************
| Module Name: Power manage model
| File Name: pow_If.h
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
|2015/08/10 Rev 01.10.00      Li Ning       			 The second version  
********************************************************************************/

/*****************************************************************************
* FILE DECLARATION
******************************************************************************/
#ifndef POW_IF_H
#define POW_IF_H

#ifndef POW_C
  #define pow_ext extern
#else
  #define pow_ext
#endif


#include "Pow_Type.h" 
#include "Pow_cfg.h" 

/*import*/
 pow_ext uint16 POW_vImpIDIgnStaticOn(void);
 pow_ext uint16 POW_vImpIDIgnStable(void);
 pow_ext  uint16 POW_vImpIDGetAnalogValue5VOutputFb(void);
 pow_ext  uint16 POW_vImpIDGetAnalogValueBatFb(void);
 pow_ext  uint16 POW_vImpIDGetAnalogValueIgn2Fb(void);
 pow_ext  uint16 POW_vImpIDGet5vSensorSupplyFb(void);

 /*export*/
pow_ext  uint16 POW_vExpIDAll(void);
pow_ext uint16  POW_u16GetValue(POW_tenu16VarNum Num);
pow_ext uint16 POW_u16Array[POW_nu16Max];

/*other*/

pow_ext uint16 POW_vMcuSupplyEnable( void);
pow_ext uint16 POW_vMcuSupplyDisable( void);
pow_ext uint16 POW_vSensorSupplyEnable( void);
pow_ext uint16 POW_vSensorSupplyDisable( void);
pow_ext uint16 POW_v5vOutputEnable( void);
pow_ext uint16 POW_v5vOutputDisable( void);
pow_ext  void POW_vSupplyReset(void);
pow_ext  void POW_vSupplyWakeup(void);
pow_ext  void POW_vSupplyOff(void);
pow_ext uint16 POW_v5vAmpOutputEnable( void);
pow_ext uint16 POW_v5vAmpOutputDisable( void);
/*****************************************************************************
* End of check if informations are already included
******************************************************************************/
#endif                                  /* ifndef POW_if_H */

/*****************************************************************************
* EOF: Pow_Cfg.h
******************************************************************************/

