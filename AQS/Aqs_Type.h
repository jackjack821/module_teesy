/*******************************************************************************
| Module Name: AQS Control
| File Name: Aqs_Type.h
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

#ifndef AQS_TYPE_H
#define AQS_TYPE_H

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
enum
{
	AQS_Initing=0,
	AQS_AirGood,
	AQS_AirBad,
	AQS_Error,
	AQS_ShutToPlus,
	AQS_ShutToGnd,
};



typedef enum
{
	AQS_nu8State=0,
	AQS_nu8SwVersion,
	AQS_nu8Valid,
	AQS_nu8ErrorCode,
	AQS_nu8AirBadTime,
	AQS_nu8AirBadPercent,
	AQS_nu8Max
}AQS_tu8enVarNumber;

typedef enum
{
	AQS_nu16PwmValue=0,
	AQS_nu16Max
}AQS_tu16enVarNumber;

/*****************************************************************************
* End of check if informations are already included
******************************************************************************/
#endif                                  /* ifndef AQS_TYPE_H */
/*****************************************************************************
* EOF: AQS_Type.h
******************************************************************************/

