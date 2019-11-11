/**************************** .FILE_HEADER_BEGIN *****************************
  .TITLE  [Bctl_Type, Type define for blower control  ]
*-----------------------------------------------------------------------------
  .FILE   [ Bctl_Type.h                                                         ]
*-----------------------------------------------------------------------------

 Version Date        		Author                       Change                      
 -----------------------------------------------------------------------------
 Rev 01.00.01  2014/04/13     OuyangBihuan       	    	The first version               

*****************************************************************************/

#ifndef BCTL_TYPE_H
#define BCTL_TYPE_H

/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
******************************************************************************/

/* System-headerfiles */
/*#include "General.h"*/
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
 typedef enum
 {
    BCTL_nInvalid=0u,
    BCTL_nValid,
    BCTL_nDefault,
    BCTL_nLastValue
 }BCTL_tenValueSts;


/*this is for uint8 type variables*/
typedef enum 
{   
	BCTL_nCalBoOffsetInit = 1U,     /*- 1 -----> Init.-*/
	BCTL_nCalBoOffsetInc,           /*- 1 -----> Blowout Increase.-*/
	BCTL_nCalBoOffsetDec            /*- 2 -----> Blowout Decrease.-*/
}BCTL_tenCalBoOffsetSlices;



/*this is for uint8 type variables*/
typedef enum 
{   
	BCTL_nCalInc,          /*- 1 -----> Increase.-*/
	BCTL_nCalDec           /*- 2 -----> Decrease.-*/
}BCTL_tenCalSlices;

typedef struct         
{
    const uint16        * const pu16TblAddrX;           
    const uint16        * const pu16TblAddrIncY;
    const uint16        * const pu16TblAddrDecY;
    BCTL_tenCalSlices   * const ptrSlices;
    const uint8         u8TblLen;
}BCTL_tstTblAttr;

typedef struct         
{
	const uint16 *const pu16TableX;
	const uint16 *const pu16TableY;
	const uint16 *const pu16TableZ[4U];
	const uint8 nu8SizeX;
	const uint8 nu8SizeY;
}BCTL_tstTblAttr2D;

/* The Air Distribution States*/
typedef enum
{                                           
    BCTL_nAirDisFace=0u,
    BCTL_nAirDisBilevel,	
    BCTL_nAirDisFloor,
    BCTL_nAirDisMixed,	
    BCTL_nAirDisScreen,
    BCTL_nAirDisScrFace,
    BCTL_nAirDisScrFaceFloor
}BCTL_tenAirdControlSts;

/* The Air Conpressor States*/
typedef enum
{                                           
    BCTL_nAcOff=0u,
    BCTL_nAcOn=1u,	
}BCTL_tenAcDisSts;


/* The IGN enable signal States*/
typedef enum
{                                           
    BCTL_nIgnLimited=0u,
    BCTL_nIgnEnable=1u,	
}BCTL_tenIgnEnableSts;

/* The ISTP States*/
typedef enum
{                                           
    BCTL_nIsEngineRunning=0u,
    BCTL_nIsEngineStopped=1u,	
}BCTL_tenIsEngineSts;

/*The BCTL mode state*/
typedef enum
{
    BCTL_nMmiModeOff = 0u,
    BCTL_nMmiModeManual,
    BCTL_nMmiModeAuto,  
    BCTL_nMmiModeDef,
    BCTL_nMmiModeMaxAc,  
}BCTL_tenMmiModeStates;

/*The BCTL mode state*/
typedef enum
{
    BCTL_nMmiLevel0 = 0u,
    BCTL_nMmiLevel1,
    BCTL_nMmiLevel2,  
    BCTL_nMmiLevel3,
    BCTL_nMmiLevel4,
    BCTL_nMmiLevel5,
    BCTL_nMmiLevel6,
    BCTL_nMmiLevel7,
    BCTL_nMmiLevel8
}BCTL_tenMmiCtrlStates;

typedef enum 
{     /* The Recirc States */
   BCTL_nRecircFresh = 0,
   BCTL_nRecircle
} BCTL_tenRecircStates;

typedef struct
{
    BCTL_tenValueSts Sts;
    uint8 Val;
} BCTL_tstU8InOutType;

typedef struct
{
    BCTL_tenValueSts Sts;
    uint16 Val;
} BCTL_tstU16InOutType;

typedef struct         
{
    BCTL_tstU8InOutType InAirdDisplay;
    BCTL_tstU8InOutType InAcDisplay;
    BCTL_tstU8InOutType InIgnEn;
    BCTL_tstU8InOutType InIsStaus;
    BCTL_tstU8InOutType InMmiSetTempDr;
    BCTL_tstU8InOutType InMmiSetTempPs;
    BCTL_tstU8InOutType InMmiBlwEvent;
    BCTL_tstU8InOutType InMmiBlwMode;
    BCTL_tstU8InOutType InMmiBlwCtrl;
    BCTL_tstU8InOutType InPowFail;
    BCTL_tstU8InOutType InRfaDisplay;

    BCTL_tstU16InOutType InCcsSetTempDr;
    BCTL_tstU16InOutType InCcsSetTempPs;
    BCTL_tstU16InOutType InCcsBlowoutAvg;
    BCTL_tstU16InOutType InCcsTempDiffDr;
    BCTL_tstU16InOutType InCcsTempDiffPs;
    BCTL_tstU16InOutType InEvapValue;
    BCTL_tstU16InOutType InHctValue;
    BCTL_tstU16InOutType InOatValue;
    BCTL_tstU16InOutType InSunValue;
    BCTL_tstU16InOutType InVelValue;
}BCTL_tstMainIn;


typedef struct         
{
    BCTL_tstU16InOutType OatCcsSetTempVolOffsetDr;
    BCTL_tstU16InOutType OatCcsSetTempVolOffsetPs;
    BCTL_tstU16InOutType SiVolOffsetDr;
    BCTL_tstU16InOutType SiVolOffsetPs;
    BCTL_tstU16InOutType SunVolOffset;
    BCTL_tstU16InOutType VelVolOffset;    
    BCTL_tstU16InOutType CcsTrgVol;
    BCTL_tstU16InOutType TrgVol;
    BCTL_tstU16InOutType WuCdVolLmt;
    BCTL_tstU16InOutType OatVolLmt;
    BCTL_tstU16InOutType VolLmt;
    BCTL_tstU16InOutType CcsTrgVlt;
    BCTL_tstU16InOutType TrgVlt;
    BCTL_tstU16InOutType SwVer;
    BCTL_tstU8InOutType DisplayInfo;
}BCTL_tstMainOut;

typedef BCTL_tstMainOut BCTL_tstMainBankOut;

typedef struct         
{
    BCTL_tstU8InOutType InMmiBlwCtrl;
}BCTL_tstCalDefTrgVolIn;

typedef struct         
{
    BCTL_tstU16InOutType CcsTrgVol;
    BCTL_tstU16InOutType TrgVol;    
    
}BCTL_tstCalDefTrgVolOut;

typedef struct         
{
    BCTL_tstU8InOutType InMmiBlwCtrl;
}BCTL_tstCalManualTrgVolIn;

typedef struct         
{
    BCTL_tstU16InOutType CcsTrgVol;
    BCTL_tstU16InOutType TrgVol;    
    
}BCTL_tstCalManualTrgVolOut;

typedef struct         
{
    uint8 u8MmiBlwMode;
    uint8 u8MmiBlwCtrl;
    uint16 u16TrgVol;
    
}BCTL_tstHandleIncDecIn;

typedef struct         
{
    uint8   *pu8LastMmiBlwCtrl;
    uint8   *pu8Off2OnIncFlag;
    uint8   *pu8Off2OnBlwLvlSet;
    uint16 *pu16TrgVolLmt;
}BCTL_tstHandleIncDecOut;

typedef struct
{
    uint16 u16TrgVol;
    uint16 u16CcsTrgVol;
}BCTL_tstCalTrgVoltIn;

typedef struct
{
    BCTL_tstU16InOutType TrgVolt;
    BCTL_tstU16InOutType CcsTrgVolt;
}BCTL_tstCalTrgVoltOut;

typedef struct
{
    //uint16 u16TrgVol;
    uint8 u8MmiBlwMode;
    uint8 u8MmiBlwCtrl;
    uint16 u16TrgVol;
}BCTL_tstCalDisInfoIn;

typedef struct
{
    BCTL_tstU8InOutType DisInfo;
}BCTL_tstCalDisInfoOut;

typedef struct
{
    BCTL_tstU8InOutType InMmiSetTempDr;
    BCTL_tstU8InOutType InMmiSetTempPs;
    BCTL_tstU16InOutType InCcsBlowoutAvg;
    BCTL_tstU16InOutType InEvapValue;
    BCTL_tstU16InOutType InHctValue;
    BCTL_tstU16InOutType InOatValue;    
}BCTL_tstCalVolLimitIn;

typedef struct
{
    BCTL_tstU16InOutType WuCdVolLmt;
    BCTL_tstU16InOutType OatVolLmt;
    BCTL_tstU16InOutType VolLmt;
}BCTL_tstCalVolLimitOut;

typedef struct         
{
    BCTL_tstU16InOutType InCcsSetTempDr;
    BCTL_tstU16InOutType InCcsSetTempPs;
    BCTL_tstU16InOutType InCcsTempDiffDr;
    BCTL_tstU16InOutType InCcsTempDiffPs;
    BCTL_tstU16InOutType InOatValue;
    BCTL_tstU16InOutType InIncomingValue;
    BCTL_tstU16InOutType InSunValue;
    BCTL_tstU16InOutType InVelValue;
}BCTL_tstCalAutoTrgVolIn;

typedef struct         
{
    BCTL_tstU16InOutType OatCcsSetTempVolOffsetDr;
    BCTL_tstU16InOutType OatCcsSetTempVolOffsetPs;
    BCTL_tstU16InOutType SiVolOffsetDr;
    BCTL_tstU16InOutType SiVolOffsetPs;
    BCTL_tstU16InOutType SunVolOffset;
    BCTL_tstU16InOutType VelVolOffset;    
    BCTL_tstU16InOutType CcsTrgVol;
    BCTL_tstU16InOutType TrgVol;    
    
}BCTL_tstCalAutoTrgVolOut;



typedef struct         
{
    const uint16 n16MinVal;            /*- Min value for this input. -*/
    const uint16 n16MaxVal;            /*- Max value for this input. -*/
    const uint16 n16Default;           /*- Default value for this input. -*/
    const uint8  n8ErrWaitTime;       /*- If the time is reached, nDefault would be used.-*/
    uint16 u16Last;
    uint8  u8ErrCounter;

}BCTL_tstU16InputAttributes;

typedef struct
{
    BCTL_tstU16InputAttributes *pstU16Attr;
    uint16 u16Input;
}BCTL_tstU16InAttrType;


typedef struct         
{
    const uint8 n8MinVal;            /*- Min value for this input. -*/
    const uint8 n8MaxVal;            /*- Max value for this input. -*/
    const uint8 n8Default;           /*- Default value for this input. -*/
    const uint8  n8ErrWaitTime;       /*- If the time is reached, nDefault would be used.-*/
    uint8 u8Last;
    uint8 u8ErrCounter;

}BCTL_tstU8InputAttributes;

typedef struct
{
    BCTL_tstU8InputAttributes *pstU8Attr;
    uint8 u8Input;
}BCTL_tstU8InAttrType;
/*
 typedef struct
{
    uint8   CcpCommandFlag;
    uint8   CcpCommand;
    uint16  CcpContronData;
}tstCcpContronType;
*/
typedef enum         
{
    BCTL_u8InputAirdDisplay	=	0U,
    BCTL_u8InputAcDisplay,
    BCTL_u8InputIgnLimit,
    BCTL_u8InputIsStaus,
    BCTL_u8InputMmiSetTempDr,
    BCTL_u8InputMmiSetTempPs,
    BCTL_u8InputMmiBlwEvent,
    BCTL_u8InputMmiBlwMode,
    BCTL_u8InputMmiBlwCtrl,
    BCTL_u8InputPowFail,
    BCTL_u8InputRfaDisplay,

    BCTL_nNumOfU8Inputs
}BCTL_tenu8InputChannels;

typedef enum         
{
    BCTL_u16InputCcsSetTempDr	=	0U,
    BCTL_u16InputCcsSetTempPs,
    BCTL_u16InputCcsBlowoutAvg,
    BCTL_u16InputCcsTempDiffDr,
    BCTL_u16InputCcsTempDiffPs,
    BCTL_u16InputEvapValue,
    BCTL_u16InputHctValue,
    BCTL_u16InputOatValue,
    BCTL_u16InputSunValue,
    BCTL_u16InputVelValue,

    BCTL_nNumOfU16Inputs
}BCTL_tenu16InputChannels;
/*****************************************************************************
* End of check if informations are already included
******************************************************************************/
#endif                                  /* ifndef BCTL_TYPE_H */
/*****************************************************************************
* EOF: Mac_Type.h
******************************************************************************/
