/***************************************************************************************************
                                     KNOB PROCESS                                                                            
 
  .File Name  : KNOB_Type.h

  .Description: This file is used to define the struc or enum type.

  --------------------------------------------------------------------------------------------------
    Version     Date            Author              Change
    
  --------------------------------------------------------------------------------------------------
    Rev 1.0     2014-11-09      Xu Xianglin         - module template update.
    Rev 2.0     2015-02-05      Xu xianglin	        - inquiry mode.
    Rev 3.0     2015-03-10      Xu xianglin		    - inquiry mode optimization.
***************************************************************************************************/

#ifndef KNOB_TYPE_H
#define KNOB_TYPE_H

/***************************************************************************************************
                                        HEADER FILES
***************************************************************************************************/

/* System-headerfiles */
#include "General.h"
#include "KNOB_cfg.h"
/* Please put the headerfiles which related to system here! */
/* Foreign headerfiles */
/* Please put the headerfiles which related to foreign here! */
/* Own headerfiles */


#if (KNOBType==KNOB_TWO_LINE_HALF_PHASE) || (KNOBType==KNOB_TWO_LINE_FULL_PHASE) || (KNOBType==KNOB_DETECTOR)
typedef enum 
{
   KNOB_nLowLow=0,
   KNOB_nLowHigh,
   KNOB_nHighLow,
   KNOB_nHighHigh
}KNOB_tenPinStatus;
#elif (KNOBType==KNOB_THREE_LINE)
typedef enum 
{
   KNOB_nLowLowLow=0,
   KNOB_nHighLowHigh,
   KNOB_nLowHighHigh,
   KNOB_nHighHighLow,
   KNOB_nHighHighHigh
}KNOB_tenPinStatus;
#endif

typedef enum
{
    KNOB_nTempId,
    KNOB_nBlowerId,
    #if 0
	 KNOB_nLeftTemp = 0,
	 KNOB_nRightTemp,
	 KNOB_nMode,
	#endif 
	 KNOB_nMaxNum
}KNOB_tenID;



typedef enum KNOB_enRotary
{
	KNOB_nNoRot=0,	
	KNOB_nRotaryUp, 
	KNOB_nRotaryDn,
	KNOB_nNumber
}KNOB_tenRotary;

/*define the Num. of variable that will be used by other modules.
typedef enum
{
	KNOB_nu8SwVersion,

   #if 0 
	KNOB_nu8TempLeftOperated,
	KNOB_nu8TempRightOperated,
   #endif
   	
	KNOB_nu8BlowerOperated,		
	KNOB_nu8TempOperated,
   #if 0
	KNOB_nu8Mode,
	KNOB_nu8TempLeftPlusCounter,
	KNOB_nu8TempLeftMinusCounter,
	KNOB_nu8TempRightPlusCounter,
	KNOB_nu8TempRightMinusCounter,
   #endif 
	KNOB_nu8BlowerPlusCounter,
	KNOB_nu8BlowerMinusCounter,
	KNOB_nu8TempPlusCounter,
	KNOB_nu8TempMinusCounter,
	//KNOB_nu8ModePlusCounter,
	//KNOB_nu8ModeMinusCounter,

    KNOB_nu8PtsTempPlusCounter,
	KNOB_nu8PtsTempMinusCounter,
    KNOB_nu8PtsBlowerPlusCounter,
	KNOB_nu8PtsBlowerMinusCounter, 
   
	KNOB_nu8PTSTest,
	KNOB_nu8Max
}KNOB_tenVarNum;*/

enum{
		KNOB_enu8PTSBlwrUp,	
		KNOB_enu8PTSBlwrDown,
		KNOB_enu8Err,
};

typedef struct
{
    uint8 u8Flag;
    uint8 u8Command;
    uint16 u16ControlValue;      
}KNOB_tstCcpControlInput;

typedef struct
{
    uint8 u8PlusCounter;
    uint8 u8MinusCounter;
    KNOB_tenRotary enRotaryOperate;
}KNOB_tstMainOut;

typedef struct
{
    uint16 u16PlusCounter;
    uint16 u16MinusCounter;
}KNOB_tstPtsOutput;


typedef enum
{
	KNOB_nRecordCounter,
	KNOB_nCcpForceMax
}CcpControl_Key;

 typedef enum
 {
    KNOB_nInvalid=0u,
    KNOB_nValid,
    KNOB_nDefault,
    KNOB_nLastValid
 }KNOB_tenValueSts;

typedef uint8 (*tfpKNOBInput) (uint16 *Value);

typedef struct
{
    const uint16 u16FilterTime;
    const uint16 u16MaxTransitionTime;
    const tfpKNOBInput fpKnobGetStatusA;
    const tfpKNOBInput fpKnobGetStatusB;
    #if (KNOBType==KNOB_THREE_LINE)
    const tfpKNOBInput fpKnobGetStatusC;
    #endif
}KNOB_tstProperty;

#if (KNOBType==KNOB_TWO_LINE_HALF_PHASE) || (KNOBType==KNOB_TWO_LINE_FULL_PHASE) || (KNOBType==KNOB_DETECTOR)

#define KnobDefineTwoLine(KnobName, FilterTime, MaxTransitionTime,fpKnobGetStatusA,fpKnobGetStatusB)    \
{(FilterTime), (MaxTransitionTime),(fpKnobGetStatusA),(fpKnobGetStatusB)}

#elif(KNOBType==KNOB_THREE_LINE)

#define KnobDefineThreeLine(KnobName, FilterTime, MaxTransitionTime,fpKnobGetStatusA,fpKnobGetStatusB,fpKnobGetStatusC)    \
{(FilterTime), (MaxTransitionTime),(fpKnobGetStatusA),(fpKnobGetStatusB),fpKnobGetStatusC}
#endif
#endif       



/***************************************************************************************************
* EOF: KEY_Type.h
***************************************************************************************************/

