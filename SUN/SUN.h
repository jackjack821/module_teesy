/*******************************************************************************
| Module Name: Calculate the Blowout and Temp offset according to the solar
| File Name: SUN.h
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
| 2015-08-05  2.00        Zhang Shuncong    Add RTE ,Copyright and cfg
********************************************************************************/

#ifndef SUN_H
#define SUN_H

/* System-headerfiles*/
#include "General.h"					/* General type definitions */


/* Foreign headerfiles */


/* Own headerfiles */
#include "SUN_Cfg.h" 

/*this is for uint16 type variables*/
typedef enum SUN_enu16VarNumbers
{   
    SUN_nu16SwVersion,
    SUN_nu16ADRawValueLeft,
    SUN_nu16ADRawValueRight,
    SUN_nu16SensorRawValueLeft,
    SUN_nu16SensorRawValueRight,
    SUN_nu16ValueDr,                    /*Fast change value*/
    SUN_nu16ValuePs,                   /*Fast change value*/
    SUN_nu16FilterSolar,              /*Slow change value*/
    SUN_nu16TempOffsetDr,   
    SUN_nu16TempOffsetPs,
    SUN_nu16BlowerOffset,
    SUN_nu16ErrCode,
    SUN_nu16Max                     
}SUN_tenu16VarNumber;

/*this is for uint8 type variables*/
typedef enum SUN_enu8VarNumbers
{   
	SUN_nu8Valid=0,
	SUN_nu8Max                     
}SUN_tenu8VarNumber;


void SUN_vInit (void);           /* StandbyActive Container */
void SUN_vDeinit (void);      /* ActiveStandby Container */
void SUN_vReset (void);      /* Reset Container */
void SUN_vMain (void);        /* On Container (background) */
void SUN_vActive (void); 
uint8 SUN_u8GetValue( SUN_tenu8VarNumber enIndex );
uint16 SUN_u16GetValue( SUN_tenu16VarNumber enIndex );

#endif                      /* ifndef */

/*****************************************************************************
* EOF:SUN1C1.H
*****************************************************************************/

