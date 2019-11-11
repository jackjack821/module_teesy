/*******************************************************************************
| Module Name: Seat Heat Control
| File Name: SHC_Type.c
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
| Luo Xindian                             Desay SV Automotive Co., Ltd
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date             Ver         Author               Description
| ----------  -------  -------------  -------------------------------------------------
| 10/21/2014    1.0  Luo Xindian		  this module for new seat heating modules development
********************************************************************************/

#ifndef SHC1CI_H
#define SHC1CI_H

/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
******************************************************************************/
/* system-headerfiles*/


/* foreign headerfiles*/


/* Own headerfiles */



/**************************** .BLOCK_COMMENT_BEGIN ***************************
* EXPORT CONFIGURATION CONSTANTS AND MACROS
*
* In this section define
* - constants and macros to configure your export interface. These constants
*   are public for other modules
***************************** .BLOCK_COMMENT_END *****************************/


/******************************************************************************
* SHC Configuration 
**
**
******************************************************************************/
/* ======================================================================== */
typedef enum SHC_enHeatSeatStates
{                                 		/* The Blower States */
   SHC_nHeatSeatOff = 0U,
   SHC_nHeatSeatLevel1,
   SHC_nHeatSeatLevel2,
   SHC_nHeatSeat_Error    	/* <--This state used to detect out of range values */
}  SHC_tenHeatSeatStates;

typedef enum SHC_enSeatNum
{
	SHC_nLeft=0U,
       SHC_nRight ,
       SHC_nSeatMax
}SHC_tenSeatNum;

/*define the Num. of variable that will be used by other modules.*/
typedef enum SHC_enu8VarNum
{	
	SHC_nu8Valid = 0,
	SHC_nu8SwVersion,
	SHC_nu8ErrorCode,
	SHC_nu8LastStateDr,
	SHC_nu8LastStatePs,
	SHC_nu8DisplayDr,
	SHC_nu8DisplayPs,
	SHC_nu8LeftSeatHeatCtrlTimer,
	SHT_nu8RightSeatHeatCtrlTimer,
	SHC_nMax
}SHC_tenu8VarNum;

typedef enum
{
	SHC_nSetRequestDr,
    SHC_nSetRequestPs,
	SHC_nCcpForceMax
}CcpControl_Shc;

typedef struct SHC_stInputLists        
{
    uint8 u8IgnDelay;
    uint8 u8LowVoltage;
    uint8 u8HighVoltage;	
    uint8 u8SeatHeatStateL;
    uint8 u8SeatHeatStateR;
    uint16 u16SeatHeatFeedbackL;
    uint16 u16SeatHeatFeedbackR;
}SHC_tstInputLists;

#endif

/*****************************************************************************
* EOF: 
******************************************************************************/

