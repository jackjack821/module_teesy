/*******************************************************************************
| Module Name: Ion Control
| File Name: Ion_Type.h
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
| Yang Shengli                        Desay SV Automotive Co., Ltd
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date             Ver         Author               Description
| ----------  -------  -------------  -------------------------------------------------
| 2016-02-25  1.00        Yang Shengli      First implementation
********************************************************************************/

#ifndef ION_TYPE_H
#define ION_TYPE_H

/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
******************************************************************************/

/* System-headerfiles */

/* Please put the headerfiles which related to system here! */

/* Foreign headerfiles */

/* Please put the headerfiles which related to foreign here! */


/* Own headerfiles */
#include "General.h"

/*****************************************************************************
*Data structures define
******************************************************************************/
/*define the Num. of variable that will be used by other modules.*/
typedef enum ION_enu8VarNumbers
{
	ION_nu8SwVersion = 0,
	ION_nu8PM25StsReq,
	ION_nu8IONStsReq,
	ION_nu8PM25Sts,
	ION_nu8IONErrSts,
	ION_nu8PM25ErrSts, /*5*/
	ION_nu8IONIZEState,
	ION_nu8AirOutQLevel,
	ION_nu8AirInQLevel,
	ION_nu8ErrorCode1,
	ION_nu8ErrorCode2, /*10*/
	ION_nu8TboxRequest,
	ION_nu8PM25Exceed,
	ION_nu8PM25PopupReq,
	ION_nu8SleepFlag,
	ION_nu8AirInQuality,
	ION_nu8PM25EnableCheckLostDtc,
	ION_nu8Max
}ION_tu8enVarNumber;

typedef enum ION_enu16VarNumbers
{
	ION_nu16PM25OutDen = 0,
	ION_nu16PM25InDen,
	ION_nu16ErrorCode,	
	ION_nu16DIG,
	ION_nu16Max
}ION_tu16enVarNumber;

typedef enum ION_enMmiIonModeStates
{
	ION_nMmiIonOff = 0,
	ION_nMmiIonManual,
	ION_nMmiIonAuto,
	ION_nMmiIonModeError
}ION_tenMmiIonModeStates;

typedef enum ION_enMmiIonStates
{
   ION_nMmiIonCleanerOff=0, 	/* the same as mmi, cleaner are off */ 
   //ION_nMmiIonCleanMode,
   ION_nMmiIonIonMode,
   ION_nMmiIonError    /* <--This state used to detect out of range values */
} ION_tenMmiIonStates;

enum
{
	ION_nPM25Off = 0,
 	ION_nPM25Init,
	ION_nPM25Running,	    /*Cancel control*/
	ION_nPM25Error
};

typedef enum
{
	PM25_nCanAcPm25Init=0,
	PM25_nCanAcPm25Collecting=1,
	PM25_nCanAcPm25Complete=2,
	PM25_nCanAcPm25Err
}PM25_tenCanAcPm25States;

/*air condition status*/
typedef enum
{
	PM25_Initing=0,
	PM25_AirCondition_Good=1,
	PM25_AirCondition_LittleBad=2,
	PM25_AirCondition_VeryBad
}PM25_AIRCONDITPM25;

/*OBD test command*/
enum
{
 	ION_nObdCtrIon = 0,
	ION_nObdCancelCtrLed,	    /*Cancel control*/
};

enum
{
	ION_nPM25PopNone = 0,
	ION_nPM25PopFirst,
 	ION_nPM25PopSecond,
	ION_nPM25PopError
};

/*****************************************************************************
* End of check if informations are already included
******************************************************************************/
#endif                                  /* ifndef ION_TYPE_H */
/*****************************************************************************
* EOF: ION_Type.h
******************************************************************************/

