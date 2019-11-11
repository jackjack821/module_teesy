/*******************************************************************************
| Module Name: Recirc fresh control type definition
| File Name: RFA_Type.h
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
| 2015-10-15    1.0  Luo Xindian		 frist created 
| 2016-2-18     1.1  Luo Xindian		Modified for KC-2
| 2016-6-26		1.1  Luo Xindian		change for base code
********************************************************************************/

#ifndef RFA_TYPE_H
#define RFA_TYPE_H

/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
******************************************************************************/

/* System-headerfiles */
#include "General.h"
/* Please put the headerfiles which related to system here! */

/* Foreign headerfiles */

/* Please put the headerfiles which related to foreign here! */


/* Own headerfiles */


/*****************************************************************************
* DEFINE DATA TYPE INTERNAL
*
* In this section
* - define all the private data types of this module.
******************************************************************************/

/*this is for uint8 type variables*/
typedef enum RFA_enu8VarNumbers
{
	RFA_nu8Valid = 0,
	RFA_nu8Display, /* The display of Recirc in LCD or Telltale          */
	RFA_nu8SetPercent,/* The percent of the Recirc position*/
	RFA_nu8AutoPercent,
	RFA_nu8SwVersion,
	RFA_nu8Max
}RFA_tenu8VarNumber;

/*this is for uint16 type variables*/
typedef enum RFA_enu16VarNumbers
{
	RFA_nu16SetPos = 0,/* the target position of recir */
	RFA_nu16MaxPos,
	RFA_nu16MinPos,
	RFA_nu16RecircTime,
	RFA_nu16ErrorCode,
	RFA_nu16Priority,
	RFA_nu16Max                     
}RFA_tenu16VarNumber;

/*The following is the Percent of RFA mode*/
typedef enum RFA_enu8RfaPercent
{
	RFA_u8FreshPos = 0,				/*the recirculation is 0%*/
	RFA_u8RecPosPercent75 = 75, 	/*the recirculation is 75%*/
	RFA_u8RecPosPercent80 = 80, 	/*the recirculation is 80%*/
	RFA_u8RecPosPercent90 = 90, 	/*the recirculation is 90%*/
	RFA_u8RecPos = 100				/*the recirculation is 100%*/
}RFA_tenu8RfaPercent;

/* MMI RFA MODE  ***********************************************************/ 
/*The RFA mode state*/
typedef enum
{
    RFA_nMmiRfaModeOff = 0,
    RFA_nMmiRfaModeManual,
    RFA_nMmiRfaModeAuto,  
    RFA_nMmiRfaModeDef,
    RFA_nMmiRfaModeMaxAc,  
}RFA_tenRecircModeStates;

/* MMI RFA control *****************************************************/ 
typedef enum RFA_enRecircStates
{     /* The Recirc States */
   RFA_nRecircFresh = 0,
   RFA_nRecircle,
   RFA_nRecircError    /* <--This state used to detect out of range values */
} RFA_tenRecircStates;


#if (RFA_biStartStop_Cfg == True)
typedef enum RFA_enIstpStates
{
	RFA_nIsNormal = 0,
	RFA_nIsStop,
	RFA_nIsRestart,
	RFA_nIstp_Max
} RFA_tenIstpStates;
#endif

#if(RFA_nUseCCP ==True)

typedef enum
{
	Rfa_nSetRfaPosition,
	Rfa_nSetRfaReirecTime,
	Rfa_nSetRfaSetPercent,
	Rfa_nCcpForceMax
}CcpControl_Rfa;
#endif

#if(RFA_biAQS_Cfg ==True)
/* AQS */
typedef enum RFA_enAqsReqState
{
	RFA_nAqsReqFresh=0,
	RFA_nAqsReqRecir,
	RFA_nAqsReqMax
}RFA_tenAqsReqState;

#endif

typedef enum RFA_enPriority
{
	RFA_nBreath=0,
	RFA_nAmbientTAllow,
	RFA_nAQS,
	RFA_nPM25,
	RFA_nIsState,
	RFA_nAmbientTForbid,
	RFA_nBlowoutT,
	RFA_nPriorityMax
}RFA_tenPriority;


/* input value Error */
typedef enum
{
	RFA_nMmiModule=0u,
    RFA_nOatModule,
    RFA_nPowModule,
    RFA_nCcsModule,
    RFA_nAqsModule,
    RFA_nPM25Module,
	RFA_nModuleMax
}RFA_tenInputMode;

typedef struct
{
    uint8 u8PowFailure;
    RFA_tenRecircModeStates enMmiRfaMode;
    RFA_tenRecircStates enMmiRfaControl;
	#if(RFA_biSystemState== True)
	uint8 u8Sys1000ms;
	uint16 u16CcsBloutTemp;
    uint16 u16OATValue;
	#endif
	#if(RFA_biAQS_Cfg ==True)
	uint8 u8MmiAqsRequest;
	uint8 u8AqsState;
	#endif
	#if(RFA_nPM25Cfg == True)
	uint16 u16PM25InCarDen;
	uint16 u16PM25OutSideDen;
	#endif
}RFA_tstMainIn;

 typedef struct
{
    RFA_tenRecircStates enRfaDisplay;
	uint16 u16SetPercent;
	uint16 u16AutoPercent;
    uint16 u16SetPosition;
	uint16 u16Priority;
	uint16 u16Version;
	uint16 u16RecirTime;
    uint16 u16ErrorCode;    
}RFA_tstMainOut;

typedef struct         
{
    uint16 u16InputValue;
    uint16 *u16LastInput;
    uint16 u16MinVal;            /*- Min value for this input. -*/
    uint16 u16MaxVal;            /*- Max value for this input. -*/
    uint16 u16Default;           /*- Default value for this input. -*/
    uint8  u8ErrWaitTime;       /*- If the time is reached, nDefault would be used.-*/
    uint8  u8ErrCounter;
}RFA_tstU16InputAttributes;

typedef struct         
{
    uint8 u8InputValue;
    uint8 *u8LastInput;
    uint8 u8MinVal;            /*- Min value for this input. -*/
    uint8 u8MaxVal;            /*- Max value for this input. -*/
    uint8 u8Default;           /*- Default value for this input. -*/
    uint8  u8ErrWaitTime;       /*- If the time is reached, nDefault would be used.-*/
    uint8  u8ErrCounter;
}RFA_tstU8InputAttributes;

 typedef enum
 {
    RFA_nInvalid=0u,
    RFA_nValid,
    RFA_nDefault,
    RFA_nLastValue
 }RFA_tenValueSts;
/*
 typedef struct
{
	uint8 CcpCommandFlag;
	uint8 CcpCommand;
	uint16 CcpContronData;
}tstCcpContronType;
*/
/*****************************************************************************
* End of check if informations are already included
******************************************************************************/
#endif                                  /* ifndef RFA_TYPE_H */
/*****************************************************************************
* EOF: RFA_Type.h
******************************************************************************/

