/*******************************************************************************
| Module Name: Calculate the Blowout and Temp offset according to the velocity
| File Name: VEL.h
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
| 2015-08-06  2.00        Zhang Shuncong    Add RTE ,Copyright and cfg
| 2016-09-21  0100        Li Jiaye          interface updated
********************************************************************************/

#ifndef 	VEL_H
#define 	VEL_H

/* System-headerfiles */
#include "General.h"					/* General type definitions */


/* Foreign headerfiles */


/* Own headerfiles */
#include "VEL_Cfg.h"                                         /* General definitions and datatypes */


/*this is for uint16 type variables*/
typedef enum VEL_enu16VarNumbers
{
    VEL_nu16SwVersion=0,
	VEL_nu16Velocity,           /*Fast change value*/
	VEL_nu16RfaValue,           /*Slow change value*/
	VEL_nu16OatValue,  		    /*More slow change value when velocity increasing*/
	VEL_nu16BlowerOffset ,
	VEL_nu16TempOffset,
	VEL_nu16ErrCode,
	VEL_nu16Max                    
}VEL_tenu16VarNumber;

/*this is for uint8 type variables*/
typedef enum VEL_enu8VarNumbers
{   
	VEL_nu8Valid=0,
	VEL_nu8Max                     
}VEL_tenu8VarNumber;


void VEL_vReset  (void);               /* Reset container                   */
void VEL_vInit   (void);                   /* Active -> On transition           */
void VEL_vDeinit (void);               /* On -> Active transition           */
void VEL_vMain   (void);               /* On Container (background) */
void VEL_vActive(void);
uint8 VEL_u8GetValue(VEL_tenu8VarNumber enIndex);
uint16 VEL_u16GetValue(VEL_tenu16VarNumber enIndex);


#endif
/*****************************************************************************
* EOF: VEL.H
******************************************************************************/
