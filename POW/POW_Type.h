/*******************************************************************************
| Module Name:Power manage model
| File Name: pow_type.h
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

#ifndef POW_TYPE_H
#define POW_TYPE_H

/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
******************************************************************************/

/* System-headerfiles */
#include "General.h"
/* Please put the headerfiles which related to system here! */

/* Foreign headerfiles */

/* Please put the headerfiles which related to foreign here! */


/* Own headerfiles */
#include "Pow_Cfg.h"                 /* Configuration head file */


/*****************************************************************************
* EXPORT INTERFACE DEFINITIONS AND DECLARATIONS
*
* In this section
* - define all type definitions of your module.
******************************************************************************/


/*define the Num. of variable that will be used by other modules.*/
typedef enum
{	
	POW_nu16AppLowVoltage=0,
	POW_nu16AppHighVoltage,
	POW_nu16ComLowVoltage,
	POW_nu16ComHighVoltage,
	POW_nu16DiagLowVoltage,
	POW_nu16DiagHighVoltage,
	POW_nu16Ref4LowVoltage,
	POW_nu16Ref4HighVoltage,
	POW_nu16AdValid,	
	POW_nu16RawK30VoltFb,
	POW_nu16ResultK30VoltFb,
	POW_nu16RawIGN2VoltFb,
	POW_nu16ResultIGN2VoltFb,
	POW_nu16SwVersion,
	POW_nu16ErrorCode,
	POW_nu165vOutputStable,
	POW_nu16Raw5vOutputFb,
	POW_nu16Result5vOutputFb,
	POW_nu16Max
}POW_tenu16VarNum;


/*for pts ,feeaback value is raw value*/
typedef struct POW_stForceSort
{
	uint8 POW_u85vOutPutFbFlag;
	uint8 POW_u8K30VoltageFbFlag;
	uint8 POW_u8K15VoltageFbFlag;
	uint8 POW_u8SensorFbFlag;
	uint8 POW_u85vOutPutCtrlFlag;	
	uint8 POW_u8SensorSupplyCtrlFlag;
	uint16 POW_u165vOutPutFbValue;
	uint16 POW_u16K30VoltageFbValue;
	uint16 POW_u16K15VoltageFbValue;
	uint16 POW_u16SensorFbValue;
	uint16 POW_u165vOutPutCtrlValue;	
	uint16 POW_u16SensorSupplyValue;
		
}tstPOW_ForceSort;



/*****************************************************************************
* End of check if informations are already included
******************************************************************************/
#endif                                  /* ifndef POW_TYPE_H */
/*****************************************************************************
* EOF: Pow_Type.h
******************************************************************************/
