/*******************************************************************************
| Module Name: Calculate the mixed air motor position according to blowout temp 
| File Name: MAC.h
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
#ifndef MAC_H
#define MAC_H


/*****************************************************************************
* LOCATION-DEFINES -only when the location assignment is needed.
******************************************************************************/

/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
******************************************************************************/
/* System-headerfiles */
#include "General.h"
/* Please put the headerfiles which related to system here! */

/* Foreign headerfiles */
#include "Rte_Type.h"
/* Please put the headerfiles which related to foreign here! */


/* Own headerfiles */
#include "Mac_Type.h"
#include "Mac_Cfg.h"

/*****************************************************************************
* EXPORT INTERFACE VARIABLE DEFINITIONS 
*
* In this section define
* - all variables will be accessed by other module.
******************************************************************************/

/*this is for uint16 type variables*/
typedef enum MAC_enu16VarNumbers
{
	MAC_nu16ErrorCode = 0,
	MAC_nu16BlowoutTempDr,		
	MAC_nu16BlowoutTempPs,
	MAC_nu16BlowoutTempAvg,
	
	MAC_nu16MixedAirPosDr,		
	MAC_nu16MixedAirPosPs,  /*5*/
	
	MAC_nu16FlapRatioDr,
	MAC_nu16FlapRatioPs,
	MAC_nu16FlapRatioAvg,
	
	MAC_nu16BlowSpeedHys,
	MAC_nu16EvapTempHys,  /*10*/
	MAC_nu16HctHys,
	
	MAC_nu16Max                     
}MAC_tenu16VarNumber;

/*this is for uint8 type variables*/
typedef enum MAC_enu8VarNumbers
{   
	MAC_nu8Valid = 0,
	MAC_nu8SwVersion,
	MAC_nu8Max                   
}MAC_tenu8VarNumber;


#ifndef MAC_UseRTE
void MAC_vReset  (void);        /* Reset Container */
void MAC_vInit   (void);       	 /* StandbyActive Container */
void MAC_vDeinit (void);        /* ActiveStandby Container */
void MAC_vMain   (void);        /* On Container*/
void MAC_vActive(void);			/* Active Container */
#endif
uint8 MAC_u8GetValue( MAC_tenu8VarNumber enIndex );
uint16 MAC_u16GetValue( MAC_tenu16VarNumber enIndex );
Std_ReturnType MAC_u8ForceIoControl_Write(/*IN*/UInt32 ForceIoControlWord);
/*****************************************************************************
* End of check if informations are already included
******************************************************************************/
#endif                                  /* ifndef MAC_H*/

/*****************************************************************************
* EOF: Mac.h
******************************************************************************/

