/*******************************************************************************
| Module Name: Calculate the ambient temperature
| File Name: OAT_Interface.h
|
|-------------------------------------------------------------------------------
|               C O P Y R I G H T
|-------------------------------------------------------------------------------
| Copyright (c) 2016 Huizhou Desay SV Automotive Co., Ltd.    All rights reserved.
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
|Zou Riming                        Desay SV Automotive Co., Ltd
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date             Ver         Author               Description
| ----------  -------  -------------  -------------------------------------------------
| 2016-06-21   0100      Zou Riming          First Create  
| 2016-09-22   0200      Zou Riming          Delet condition 2 of cold start 
| 
| 
********************************************************************************/

/*****************************************************************************
* FILE DECLARATION
******************************************************************************/
#ifndef OAT_Interface_H
#define OAT_Interface_H

/* System-headerfiles */

/* Foreign headerfiles */

/* Own headerfiles */
#include "OAT_Type.h"   

/*****************************************************************************
* MACROS
*
* Functional macros defined.
******************************************************************************/


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

/*****************************************************************************
* MODULE CONFIGURATION DECLARATIONS
*
* In this section declare
* - module variable declarations for the variable in the cfg.c file, which will be used in module
     functions.
******************************************************************************/
    OAT_tenValueSts OAT_u16IgnDelayFlagImport(uint16*Value);
    OAT_tenValueSts OAT_u16Sys1000msFlagImport(uint16*Value);
    OAT_tenValueSts OAT_u16BusQualityFlagImport(uint16*Value);   
    OAT_tenValueSts OAT_u16BusRawValueImport(uint16*Value); 
    OAT_tenValueSts OAT_u16PowAdValidFlagImport(uint16*Value); 
    OAT_tenValueSts OAT_u16SensorAdRawValueImport(uint16*Value);   
    OAT_tenValueSts OAT_u16VechileSpeedValueImport(uint16*Value);       
    OAT_tenValueSts OAT_u16HctValueImport(uint16*Value);
    OAT_tenValueSts OAT_enGetErrorCode(uint16 *ErrorCode);
    #if (OAT_UseNewCCP==True)
    void OAT_vCcpOutputForce(uint16 *Value);
    void OAT_ClrCcpForceByte(void);
    #endif
    Std_ReturnType OAT_u8ForceIoControl_Write(/*IN*/uint32 ForceIoControlWord);

/*****************************************************************************
* End of check if informations are already included
******************************************************************************/
#endif                                  /* ifndef */

/*****************************************************************************
* EOF: OAT_Interface.h
******************************************************************************/

