
/**************************** .FILE_HEADER_BEGIN *****************************
  .TITLE  [air distribution                                                  ]
*-----------------------------------------------------------------------------
  .FILE   [ AIRD_Tpye.h                                                        ]
  .AUTHOR [  duzj				                                     ]
*-----------------------------------------------------------------------------

 Version Date             Author     Change                      
 -----------------------------------------------------------------------------
 Rev 1.0 2013-9-26    duzj        update the module.        

*****************************************************************************
****************************** .FILE_HEADER_END ******************************/

#ifndef AIRD_Type_H
#define AIRD_Type_H


#define AIRD_UseRTE
/*****************************************************************************
* Define the enum to present the variable for extern model call.
******************************************************************************/
/*this is for uint16 type variables*/
typedef enum AIRD_enu16VarNumbers
{
	AIRD_nu16SetPos = 0,		/* the target position of air distribution */
	AIRD_nu16ErrCode,		   	/*AIRD module error code*/
	AIRD_nu16SWVersion,
	AIRD_nu16Max                     
}AIRD_tenu16VarNumber;

/*this is for uint8 type variables*/
typedef enum AIRD_enu8VarNumbers
{
	AIRD_nu8Valid = 0,		   	/*The valid flag of air distribution door position.*/
	AIRD_nu8Display,		   	/*The Aird display information for MMI.*/
	AIRD_nu8AirdAutoControl,   	/*The result of air distribution door position index in auto mode.*/
	AIRD_nu8SwVersion,			/*The AIRD module SW version.*/
	AIRD_nu8Max
}AIRD_tenu8VarNumber;

/* AIRD Posion index************************************************/
typedef enum
{
	AIRD_nAutoFace = 0,
	AIRD_nAutoBilevel1,
	AIRD_nAutoBilevel2,
	AIRD_nAutoBilevel3,
	AIRD_nAutoFloor,
	AIRD_nAutoMixed,
	AIRD_nAutoScreen
}AIRD_tenMMIAutoControlSts;

/*define the bit position for Error Code*/
enum
{
	AIRD_nBitAirdModeErr = 0,
	AIRD_nBitAirdControlErr,	
	AIRD_nBitOatValueErr,
	AIRD_nBitEvapValueErr,
	AIRD_nBitHctValueErr,
	AIRD_nBitMacTempErr,
	AIRD_nBitCcsTempErr,
};

/* The Air Distribution States*/
typedef enum
{                                           
    AIRD_nMmiAirDisFace=0,
    AIRD_nMmiAirDisBilevel,	
    AIRD_nMmiAirDisFloor,
    AIRD_nMmiAirDisMixed,	
   	AIRD_nMmAirDisScreen,
}AIRD_tenMMIControlSts;


/*The System Control Mode*/
enum
{
   AIRD_nMmiModeOff=0,                                   
   AIRD_nMmiModeManual,
   AIRD_nMmiModeAuto,
   AIRD_nMmiModeDef,
   AIRD_nMmModeError,
};

/*The aird mode state*/
typedef enum
{
    AIRD_nMmiAirdModeOff = 0,
    AIRD_nMmiAirdModeManual,
    AIRD_nMmiAirdModeAuto,  
    AIRD_nMmiAirdModeDef,
    AIRD_nMmiAirdModeMaxAc,  
}AIRD_tenMMIModeSts;
 typedef enum
 {
    AIRD_nInvalid=0u,
    AIRD_nValid,
    AIRD_nDefault,
    AIRD_nLastValue
 }AIRD_tenValueSts;
 /*Ccp control*/
typedef enum
{
	Aird_nSetPosition,
	Aird_nCcpForceMax
}CcpControl_Aird;

/* input value Error */
typedef enum
{
	Aird_nMmiModule=0u,
    Aird_nOatModule,
    Aird_nPowModule,
    Aird_nHctModule,
    Aird_nCcsModule,
	Aird_nModuleMax
}Aird_tenInputMode;

typedef struct
{
    uint8 u8PowFailure;
    AIRD_tenMMIModeSts enMmiAirdMode;
    AIRD_tenMMIControlSts enMmiAirdControl;
}Aird_tstMainIn;
 typedef struct
{
    AIRD_tenMMIControlSts enAirdDisplay;
    uint16 u16SetPosition;
    AIRD_tenMMIAutoControlSts enAutoControlsts;
    uint16 u16ErrorCode;    
}Aird_tstMainOut;
 typedef struct
{
    uint16 u16CcsBloutTemp;
    AIRD_tenMMIAutoControlSts enAutoControlsts;
    uint16 u16OATValue;
    uint16 u16HctValue;
    uint8  u8PurgeAirFlag;
}Aird_tstAutoCalcIn;

 typedef struct
{
    uint8 u8BlowoutTempFlag;
    uint8 u8OatFlag;
    uint8 u8HctWaterFlag;
    uint8 boWinterFlag;
}Aird_tstColdStartCondiction;
 typedef struct
{
    uint16 u16OatValue;
    uint16 u16PurgeAirTmr;
}Aird_tstPurgeAirIn;
 typedef struct
{
    uint8 u8PurgeAirFlag;
    uint16 u16PurgeAirTmr;
}Aird_tstPurgeAirOut;


typedef struct         
{
    uint16 u16InputValue;
    uint16 *u16LastInput;
    uint16 u16MinVal;            /*- Min value for this input. -*/
    uint16 u16MaxVal;            /*- Max value for this input. -*/
    uint16 u16Default;           /*- Default value for this input. -*/
    uint8  u8ErrWaitTime;       /*- If the time is reached, nDefault would be used.-*/
    uint8  u8ErrCounter;
}AIRD_tstU16InputAttributes;
typedef struct         
{
    uint8 u8InputValue;
    uint8 *u8LastInput;
    uint8 u8MinVal;            /*- Min value for this input. -*/
    uint8 u8MaxVal;            /*- Max value for this input. -*/
    uint8 u8Default;           /*- Default value for this input. -*/
    uint8  u8ErrWaitTime;       /*- If the time is reached, nDefault would be used.-*/
    uint8  u8ErrCounter;
}AIRD_tstU8InputAttributes;


#endif                                 

