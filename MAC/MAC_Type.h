/*******************************************************************************
| Module Name: Calculate the mixed air motor position according to blowout temp 
| File Name: MAC_Type.h
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

#ifndef MAC_TYPE_H
#define MAC_TYPE_H

/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
******************************************************************************/

/* System-headerfiles */
#include "General.h"
#define MAC_EvapTempFilter	/*Evapfilter*/
#define MAC_LimitHctEvapDiff  /*limit HctEvapDiff*/
//#define MAC_UseCW            /*if use CW and CCW curve*/
#define MAC_StopInOffMode       /*If stop motor driving in off mode,*/
//#define MAC_UseDiffHctCurve       /*use diff erent hct curve*/
/*****************************************************************************
* DEFINE DATA TYPE INTERNAL
*
* In this section
* - define all the private data types of this module.
******************************************************************************/

typedef struct
{
        uint32    u32PT2_Save[2];
        uint16    u16Raw;
        uint16    u16Hyst;
        uint16    u16Value;
        uint16    u16Nominal;
        uint16    u16TarPosCW;
        uint16    u16TarPosCCW;
} MAC_tstPosition;

typedef enum
{
	MAC_nDirectCW = 0,
	MAC_nDirectCCW,
	MAC_nDirectMax
} MAC_tenCurveDire;

/* The index of Air Distribution position */
typedef enum
{                                          
	MAC_nAirdPosFace = 0,
	MAC_nAirdPosBilevel1,
	MAC_nAirdPosBilevel2,
	MAC_nAirdPosBilevel3,
	MAC_nAirdPosFoot,	
	MAC_nAirdPosMixed,
	MAC_nAirdPosScreen,
	MAC_nAirdPosMax,
}MAC_tenAirdMode;

/*define the bit position for Error Code*/
typedef enum
{
	MAC_nBitInputValueErr = 0,
	MAC_nBitMax,
}MAC_tenErrorCode;

/*****************************************************************************
* End of check if informations are already included
******************************************************************************/
#endif                                  /* ifndef MAC_TYPE_H */
/*****************************************************************************
* EOF: MAC_Type.h
******************************************************************************/
