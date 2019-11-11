/*******************************************************************************
| Module Name: Mmi, Man machine interface
| File Name: Mmi_Type.h
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
| Yang Tingyu                        Desay SV Automotive Co., Ltd
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date             Ver         Author               Description
| ----------  -------  -------------  ------------------------------------------
| 2016-03-08  A1        Yang Tingyu         First implementation
| 

  ,-~~-.___. 
 / |  ' 	\ 
(  )		0 
 \_/-, ,----' 
	====		   // 
   /  \-'~;    /~~~(O)
  /  __/~|	 /		 |
=(	_____| (_________|

********************************************************************************/

#ifndef MMI_TYPE_H
#define MMI_TYPE_H

/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
******************************************************************************/

/* System-headerfiles */
/* Please put the headerfiles which related to system here! */

/* Foreign headerfiles */

/* Please put the headerfiles which related to foreign here! */


/* Own headerfiles */


/*****************************************************************************
* EXPORT INTERFACE DEFINITIONS AND DECLARATIONS
*
* In this section
* - define all type definitions of your module.
******************************************************************************/


typedef void (*MMI_tstKeyAction) (void);

/* ======================================================================== */
typedef enum MMI_enSysState
{/* The System States */
   MMI_nSysStateOff = 0,     
   MMI_nSysStateManual,
   MMI_nSysStateAuto,
   MMI_nSysStateDefrost,
   MMI_nSysStateMaxAc,
   MMI_nSysStateError=255U      
} MMI_tenSysState;

/* ======================================================================== */

typedef enum MMI_enAirdState
{/* The Air Distribution states*/
    MMI_nAirdStateOff = 0,
    MMI_nAirdStateManual,
    MMI_nAirdStateAuto, 
    MMI_nAirdStateDefrost,
    MMI_nAirdStateMaxAc,
    MMI_nAirdStateError=255U
} MMI_tenAirdState;

/* ======================================================================== */

typedef enum MMI_enBctlState
{/*The Blower states*/
    MMI_nBctlStateOff = 0,
    MMI_nBctlStateManual,
    MMI_nBctlStateAuto,
    MMI_nBctlStateDefrost,
    MMI_nBctlStateMaxAc, 
    MMI_nBctlStateDefManu,
	MMI_nBctlStateMaxAcManu,
    MMI_nBctlStateError=255U
} MMI_tenBctlState;

/*========================================================================*/

typedef enum MMI_enAcState
{/* The Compressor states*/
    MMI_nAcStateOff = 0,
    MMI_nAcStateManual,
    MMI_nAcStateAuto,
    MMI_nAcStateDefrost,
    MMI_nAcStateMaxAc, 
    MMI_nAcStateDefManu,
    MMI_nAcStateMaxAcManu,
    MMI_nAcStateError=255U
} MMI_tenAcState;

/* ======================================================================== */

typedef enum MMI_enRfaState
{/* The air intake (Recirc & Fresh) states */ 
	MMI_nRfaStateOff = 0,
	MMI_nRfaStateManual,
	MMI_nRfaStateAuto,	
	MMI_nRfaStateDefrost,
	MMI_nRfaStateMaxAc,
	
	MMI_nRfaStateDefManu,
	MMI_nRfaStateMaxAcManu,
	MMI_nRfaStateError=255U
}MMI_tenRfaState;

typedef enum MMI_enAqsState
{/* The Aqs states */ 
	MMI_nAqsStateOff = 0,
	MMI_nAqsStateManual,
	MMI_nAqsStateAuto,	
	MMI_nAqsStateDefrost,
	MMI_nAqsStateMaxAc,
	
	MMI_nAqsStateDefManu,
	MMI_nAqsStateMaxAcManu,
	MMI_nAqsStateError=255U
}MMI_tenAqsState;
/* ======================================================================== */
typedef enum MMI_enIonState
{/* The Ion States */
   MMI_nIonStateOff=0,	 
   MMI_nIonStateManual, 	
   MMI_nIonStateAuto, 
   MMI_nIonStateDefrost,
   MMI_nIonStateMaxAc,
   
   MMI_nIonStateDefManu,
   MMI_nIonStateMaxAcManu,
   MMI_nIonStateError=255U   
} MMI_tenIonState;


/* ======================================================================== */
/* ======================================================================== */
typedef enum MMI_enBctlCtrl
{ /* The blower speeds control items */ 
   MMI_nBctlOff = 0,
   MMI_nBctlSpeed1,
   MMI_nBctlSpeed2,
   MMI_nBctlSpeed3,
   MMI_nBctlSpeed4,
   MMI_nBctlSpeed5,
   MMI_nBctlSpeed6,
   MMI_nBctlSpeed7,
   MMI_nBctlError=255U   
}  MMI_tenBctlCtrl;

/* ======================================================================== */

typedef enum MMI_enAirdCtrl
{ /* The Air Distribution mode control items */
    MMI_nAirdFace=0,
    MMI_nAirdBilevel,	
    MMI_nAirdFloor,
    MMI_nAirdMixed,	
    MMI_nAirdScreen,
   MMI_nAirdisError=255U   
} MMI_tenAirdCtrl;

/* ======================================================================== */

typedef enum MMI_enAcCtrl
{ /* The Compressor control items */
   MMI_nAcOff=0,
   MMI_nAcOn,   
   MMI_nAcEcon,
   MMI_nAcError=255U    
} MMI_tenAcCtrl;


/* ======================================================================== */
typedef enum MMI_enRfaCtrl
{ /* The air intake control items */
   MMI_nRfaFresh =0,
   MMI_nRfaRecirc,
   MMI_nRfaError=255U    
} MMI_tenRfaCtrl;


/* ======================================================================== */
typedef enum MMI_enIonCtrl
{/* The Ion Control items */
   MMI_nIonStandby=0,	 
   //MMI_nIonCleanMode, 	
   MMI_nIonIonMode,
   MMI_nIonError   
} MMI_tenIonCtrl;

typedef enum MMI_enAqsStatus
{
   MMI_nAQSOff,				/* Added for AQS control  */ 
   MMI_nAQSOn,				/* Added for AQS control  */ 
}MMI_tenAqsStatus;
/* ======================================================================== */
typedef enum MMI_enRearDefCtrl
{/* The Rear Defrost Control items */
   MMI_nRearDefOff=0,	 
   MMI_nRearDefOn, 	
   MMI_nRearDefError=255U   
} MMI_tenRearDefCtrl;


/* ======================================================================== */
typedef enum MMI_enDualCtrl
{/* The Dual Control items */
   MMI_nDualOff=0,	 
   MMI_nDualOn, 	
   MMI_nDualError=255U   
} MMI_tenDualCtrl;

/* ======================================================================== */
typedef enum MMI_enSeatHeatLeftCtrl
{/* The seat heating on left items */
   MMI_nSeatHeatLeftOff=0,	 
   MMI_nSeatHeatLeft1,
   MMI_nSeatHeatLeftError=255U   
} MMI_tenSeatHeatLeftCtrl;

typedef enum MMI_enSeatHeatRightCtrl
{/* The seat heating on right items */
   MMI_nSeatHeatRightOff=0,	 
   MMI_nSeatHeatRight1,
   MMI_nSeatHeatRightError=255U   
} MMI_tenSeatHeatRightCtrl;

/* ======================================================================== */
typedef enum MMI_enRotary
{
	MMI_nNoRot = 0,
	MMI_nTempRotUp, 
	MMI_nTempRotDn,	
	MMI_nBlowerRotUp, 
	MMI_nBlowerRotDn,
	MMI_nNumber
}MMI_tenRotary;

/* ======================================================================== */

/*define the Num. of variable that will be used by other modules.*/
typedef enum MMI_enu8VarNum
{

	MMI_nu8SysState=0,
	MMI_nu8SetTempDr,				/* 0 The user setting temperature of driver side*/
	MMI_nu8SetTempPs,				/* 1 The user setting temperature of passenger side*/
	MMI_nu8SetTempPrevR,                     	/* 2 previous value of the user setting temperature of passenger side*/ 
	MMI_nu8ModeControl,			       	/* 3 The Climate Controller control mode of current moment, Auto/Manual/Off/Error*/
	MMI_nu8BlwControl,				/* 4 The blower control level of current moment, Level 1 to level 8*/
	MMI_nu8BlwModeControl,			/* 5 The blower control mode of current moment, Auto/Manual/Off*/
	MMI_nu8ACControl,				/* 6 The compress control state of current moment, AC on or Off*/
	MMI_nu8ACMode,			/* 7 The compress control mode of current moment, Auto/Manual/Off*/
	MMI_nu8AirdControl,				/* 8 The air distribute control state of current moment, Face/face&foot/foot/foot&screen*/
	MMI_nu8AirdModeControl,			/* 9 The air distribute control mode of current moment, Auto/Manual/Off*/
	MMI_nu8RecirControl,				/* 10 The recirculation control state of current moment, Rec or Fre*/
	MMI_nu8RecirMode,			/* 11 The recirculation control mode of current moment,, Auto/Manual/Off*/
	MMI_nu8DefrostControl,			/* 12 The defrost control state of current moment,Def on or off*/
	MMI_nu8DualControl,				/* 15 The Dual control state of current moment*/		
	MMI_nu8MaxAcControl,				/* 16 The Max A/C control state of current moment, Max AC on or off*/	
	MMI_nu8UseTempInF,				/* 19 */ 
	MMI_nu8SelfTest,					/* 20 */ 
	MMI_nu8IonMode,					/* 21 */ 
	MMI_nu8IonCtrl,					/* 22 */ 
	MMI_nu8AqsRequest,				/*23*/
	MMI_nu8AQSstatus,				/*24 for AQS restore*/
	MMI_nError,						/* MMI module is error */ 
	//MMI_nRearLock,
	MMI_nRearDefrost,
	MMI_nRemoteCtrl,
	MMI_nLockIndicate_front,
	MMI_nLockIndicate_Rear,

	//MMI_nIonNeedReplaceFilter,
	MMI_nu8SHL,
	MMI_nu8SHR,
	MMI_nu8SHLFromeBus,
	MMI_nu8SHRFromeBus,
	
    MMI_nPm25PopupOerationSts,
	MMI_nPm25Enable,
	MMI_nPm25PopActive,
	
	MMI_nu8SwVersion,					/* SW Version */ 
	MMI_nu8Max
}MMI_tenu8VarNum;


typedef enum MMI_enu16VarNum
{
	MMI_nu16ErrorCode,
	MMI_nu16LcdDispInfo1,			/*  transmit the status to LCD */ 
	MMI_nu16LcdDispInfo2,			/*  transmit the status to LCD */ 
	MMI_nu16IndicatorInfo1,
	MMI_nu16IndicatorInfo2,
	MMI_nu16Max
}MMI_tenu16VarNum;


typedef struct MMI_stState
{
	uint8 u8State;
	uint8 u8Ctrl;

}MMI_tstState;



typedef struct MMI_stStStore
{
	uint8  nSystemState;
	uint8  nDualCtrl;
	uint8  nSetTempL;
	uint8  nSetTempR;
	uint8  nIonCtrl;
	uint8  nIonState;
	uint8  nBctlSpd;
	uint8  nBctlState;
	uint8  nAirdCtrl;
	uint8  nAirdState;
	uint8  nAcccCtrl;
	uint8  nAcccState;
	uint8  nRfaCtrl;
	uint8  nRfaState;
    uint8  nAqsCtrl;
    uint8  nAqsState;
}MMI_tstStStore;

typedef struct 
{
	uint8 CurrentStatus;
	uint8 OFFpreStatus;
	//uint8 DEFpreStatus;
}MMI_stSysStatus;

typedef struct 
{
	struct
		{
			uint8 mode:4;   /*2->4, BY ZSC,160524*/
			uint8 controlsts:4; /*6->4, BY ZSC,160524*/
		}MMI_stCurrentStatus;
	
	struct
		{
			uint8 mode:4;
			uint8 controlsts:4;
		}MMI_stOFFpreStatus;
	
	struct
		{
			uint8 mode:4;
			uint8 controlsts:4;
		}MMI_stDEFpreStatus;
	
}MMI_stStatus;

typedef struct
{
	MMI_stStatus MMI_u8SaveAC;
	MMI_stStatus MMI_u8SaveAird;
	MMI_stStatus MMI_u8SaveBCTL;
	MMI_stStatus MMI_u8SaveMode;
	MMI_stStatus MMI_u8SaveRFA;
	MMI_stStatus MMI_u8SaveION;
	MMI_stSysStatus MMI_u8SaveDual;
	MMI_stSysStatus MMI_u8SaveSetTempDr;/*set temp Dr*/
	MMI_stSysStatus MMI_u8SaveSetTempPs;/*set temp Dr*/
    MMI_stStatus MMI_u8SaveAqs;
	//uint8 MMI_u8SaveByte1;/*set temp Dr*/
	//uint8 MMI_u8SaveByte2;/*set temp Ps*/
}MMI_tstStatusSave;

/*
typedef struct MMI_stMmiStateSave1
{
	union 
	{
		struct
		{
		uint8 SysState : 3U;
		uint8 DualCtrl : 2U;
		uint8 Reserve : 3U;
		} bits1;
		uint8 byte1;
	}MMI_SaveByte1;

	union 
	{
		struct
		{
		uint8 AirdState : 3U;
		uint8 AirdCtrl : 3U;
		uint8 Reserve : 2U;
		} bits2;
		uint8 byte2;
	}MMI_SaveByte2;
	
	union 
	{
		struct
		{
		uint8 BctlState : 3U;
		uint8 BctlCtrl : 5U;
		} bits3;
		uint8 byte3;
	}MMI_SaveByte3;
	
	union 
	{
		struct
		{
		uint8 AcState : 3U;
		uint8 AcCtrl : 3U;
		uint8 Reserve : 2U;
		} bits4;
		uint8 byte4;
	}MMI_SaveByte4;
	
	union 
	{
		struct
		{
		uint8 RfaState : 3U;
		uint8 RfaCtrl : 2U;
		uint8 Reserve : 3U;
		} bits5;
		uint8 byte5;
	}MMI_SaveByte5;
	
	union 
	{
		struct
		{
		uint8 SetTempLeft;
		} bits6;
		uint8 byte6;
	}MMI_SaveByte6;
	
	union 
	{
		struct
		{
		uint8 SetTempRight;
		} bits7;
		uint8 byte7;
	}MMI_SaveByte7;
	
	union 
	{
		uint8 Reserve;
	}MMI_SaveByte8;
	
}MMI_tstMmiStateSave1;


typedef struct MMI_stMmiStateSave2
{
	union 
	{
		struct
		{
		uint8 SysStatePre : 3U;
		uint8 DualCtrlPre : 2U;
		uint8 Reserve : 3U;
		} bits9;
		uint8 byte9;
	}MMI_SaveByte9;

	union 
	{
		struct
		{
		uint8 AirdStatePre : 3U;
		uint8 AirdCtrlPre : 3U;
		uint8 Reserve : 2U;
		} bits10;
		uint8 byte10;
	}MMI_SaveByte10;
	
	union 
	{
		struct
		{
		uint8 BctlStatePre : 3U;
		uint8 BctlCtrlPre : 5U;
		} bits11;
		uint8 byte11;
	}MMI_SaveByte11;
	
	union 
	{
		struct
		{
		uint8 AcStatePre : 3U;
		uint8 AcCtrlPre : 3U;
		uint8 Reserve : 2U;
		} bits12;
		uint8 byte12;
	}MMI_SaveByte12;
	
	union 
	{
		struct
		{
		uint8 RfaStatePre : 3U;
		uint8 RfaCtrlPre : 2U;
		uint8 Reserve : 3U;
		} bits13;
		uint8 byte13;
	}MMI_SaveByte13;
	
	union 
	{
		struct
		{
		uint8 SetTempLeftPre;
		} bits14;
		uint8 byte14;
	}MMI_SaveByte14;
	
	union 
	{
		struct
		{
		uint8 SetTempRightPre;
		} bits15;
		uint8 byte15;
	}MMI_SaveByte15;
	
	union 
	{
		uint8 Reserve;
	}MMI_SaveByte16;
	
}MMI_tstMmiStateSave2;
*/

typedef struct MMI_stLcdInfo
{
	union 
	{
		struct 
		{
		/***0~7 bit***************/
		uint8 AutoSymbol :1u;
		uint8 AcSymbol :1u;
		uint8 DualSymbol :1u;
		uint8 EconSymbol :1u;
		uint8 FreSymbol :1u;
		uint8 RecSymbol :1u;
		uint8 RDefSymbol :1u;
		uint8 AqsSymbol :1u;
		/***8~15 bit***************/
		uint8 MaxAcSymbol :1u;
		uint8 DefSymbol :1u;
		uint8 OffFlag :1u;
		uint8 RearLock :1u;
		uint8 ManualSymbol :1u;
		uint8 Reserve13 :1u;
		uint8 Reserve14 :1u;
		uint8 Reserve15 :1u;
		}tstLcdInfo1;
		uint16 u16LcdInfo1;
	}tunLcdInfo1;
	
	union 
	{
		struct 
		{
			/***0~7 bit***************/
			uint8 TempFlag :1u;
			uint8 BlwFlag :1u;
			uint8 AirdFlag :1u;
			uint8 Reserve3:1u;
			uint8 Reserve4 :1u;
			uint8 RecFlag :1u;
			uint8 Reserve6 :1u;
			uint8 Reserve7 :1u;
			/***8~15 bit***************/
			uint8 Reserve8 :1u;
			uint8 Reserve9 :1u;
			uint8 Reserve10 :1u;
			uint8 Reserve11 :1u;
			uint8 Reserve12 :1u;
			uint8 Reserve13 :1u;
			uint8 Reserve14 :1u;
			uint8 Reserve15 :1u;
		}tstLcdInfo2;
		uint16 u16LcdInfo2;

	}tunLcdInfo2;
}MMI_tstLcdInfo;

typedef struct MMI_stIndiInfo
{
union 
{
	struct 
	{
		/***0~7 bit***************/
		uint8 AutoIndi :1U;
		uint8 AcIndi :1U;
		uint8 DualIndi :1U;
		uint8 FreshIndi :1U;
		uint8 RecIndi :1U;
		uint8 RDefIndi :1U;
		uint8 MaxAcIndi :1U;
		uint8 DefIndi :1U;
		/***8~15 bit***************/
		uint8 MixedIndi :1U;
		uint8 FloorIndi :1U;
		uint8 FaceIndi :1U;
		uint8 BilevelIndi :1U;
		uint8 Reserve12 :1U;
		uint8 IonIndi :1U;
		uint8 Reserve14 :1U;
		uint8 LcdBLFlag :1U;
	}tstIndiInfo1;
	uint16 u16IndiInfo1;
}nu16IndiInfo1;

union 
{
	struct 
	{
		/***0~7 bit***************/
		uint8 Hsl1Indi :1U;
		uint8 Hsl2Indi :1U;
		uint8 Hsl3Indi :1U;
		uint8 Hsr1Indi :1U;
		uint8 Hsr2Indi :1U;
		uint8 Hsr3Indi :1U;
		uint8 Hcl1Indi :1U;
		uint8 Hcl2Indi :1U;
		/***8~15 bit***************/
		uint8 Hcl3Indi :1U;
		uint8 Hcr1Indi :1U;
		uint8 Hcr2Indi :1U;
		uint8 Hcr3Indi :1U;
		uint8 Reserve12 :1U;			
		uint8 Reserve13 :1U;
		uint8 Reserve14 :1U;
		uint8 Reserve15 :1U;
	}tstIndiInfo2;
	uint16 u16IndiInfo2;

}nu16IndiInfo2;

}MMI_tstIndiInfo;
	
/*****************************************************************************
* End of check if informations are already included
******************************************************************************/
#endif                                  /* ifndef MMI_TYPE_H */
/*****************************************************************************
* EOF: Mmi_Type.h
******************************************************************************/
