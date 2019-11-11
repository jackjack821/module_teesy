/**************************** .FILE_HEADER_BEGIN *****************************
  .TITLE  [Alg, Algorith Library	 ]
*-----------------------------------------------------------------------------
  .FILE   [ Alg.h                                                         ]
*-----------------------------------------------------------------------------

 Version Date        		Author                       Change                      
 -----------------------------------------------------------------------------
 Rev 01.00.00 2014/07/28     ZB      			 The first version                  

*****************************************************************************/

/*****************************************************************************
* FILE DECLARATION
******************************************************************************/
#ifndef ALG_H
#define ALG_H


/*****************************************************************************
* LOCATION-DEFINES -only when the location assignment is needed.
******************************************************************************/


/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
******************************************************************************/
/* System-headerfiles */
#include "General.h"


/* Own headerfiles */
//#include "Alg_Cfg.h"                 /* Configuration head file */
//#include "Alg_Type.h"                 /* General definitions and datatypes */

#if 1

/* Indicate need to init the sensor parameter */
typedef enum 
{
	ColdBoot = 0, /* Need to init the sensor parameter */
	HotBoot
}tenSensorState;

/* The SensorFilter Parameters: all the datas are constant  */
typedef struct
{
	uint16 *au16Raw; /* The Sensor Constant Table X */
     	uint16 *au16Result; /* The Sensor Constant Table Y */
    	uint16 u16MinLimitValue; /* The Min limit value of the valid range*/
     	uint16 u16MaxLimitValue; /* The Max limit value of the valid range */
     	uint16 u16SensorDefaultValue; /* Will be used when AD over the valid range  */
     	uint8 u8ErrorCountTimeout; /* For using to declare a sensor is faulty  */ 
     	uint8 u8FilterParameter; /* The filter level:0-7  */
     	uint8 u8Length; /* The length of the Sensor Constant Table  */
}tstSensorFilterConstantType;

/* The SensorFilter Parameters: all the datas will be changed  */
typedef struct
{
	uint32 u32InterimValue;/* For store the higher-resulution values for first order filters */
     	uint16 u16SensorAD;/* The sensor AD value */
     	uint16 u16SensorValue;/* The filter sensor value for use  */
     	uint8 u8ErrorCount;/* For using to count the time of sensor error  */ 
     	uint8 u8SensorErrorFlag;/* Indicate the sensor is in error state  */
     	tenSensorState u8InitFlag;/* Is used to init the SensorValue  */
}tstSensorFilterVariableType;
#endif

typedef struct ALG_stInputAttributes        
{
    const uint8/*BCTL_tenInputTypes*/ nInputType;   /*- Input Type. -*/ 
    uint8      * const pu8Addr;             /*- The address of uint8 input.-*/            
    uint16     * const pu16Addr;            /*- The address of uint16 input.-*/
    const uint16  nMinVal;            /*- Min value for this input. -*/
    const uint16  nMaxVal;            /*- Max value for this input. -*/
    const uint16  nInit;            /*- Default value for this input. -*/
    const uint16  nDefault;            /*- Error substitute value. -*/
    const uint16  nErrMask;
    const uint8   nErrWaitTime;            /*- If the time is reached, nDefault would be used.-*/
    uint8 u8ErrCounter;                 /*- Couter to record the error time. -*/
}ALG_tstInputAttributes;

/*this is for uint8 type variables*/
typedef enum ALG_enInputTypes
{   
	nUint8InputType = 0U,      /*- 0 -----> uint8 input type.-*/
	nUint16InputType,          /*- 1 -----> uint16 input type.-*/
	nUint32InputType           /*- 2 -----> uint32 input type.-*/
}ALG_tenInputTypes;

/* Attributes for uint8 type */
#define ALG_nDefineUint8Input(Addr,Min,Max,Default,ErrMask,ErrWaitTime) \
{ \
   nUint8InputType, \
   (Addr), \
   (uint16*) NULL, \
   (Min), \
   (Max), \
   0xFFU, \
   (Default), \
   (ErrMask), \
   (ErrWaitTime), \
   0U \
}

/* Attributes for uint16 type */
#define ALG_nDefineUint16Input(Addr,Min,Max,Default,ErrMask,ErrWaitTime) \
{ \
   nUint16InputType, \
   (uint8*) NULL, \
   (Addr), \
   (Min), \
   (Max), \
   0xFFFFU, \
   (Default), \
   (ErrMask), \
   (ErrWaitTime), \
   0U \
}


/*****************************************************************************
* EXPORT INTERFACE FUNCTION PROTOTYPES
*
* In this section declare
* - all system global function prototypes of your module. This is a copy of the function 
*   definitions without the header template.
******************************************************************************/
extern uint8    ALG_u8FirstOrderFilter        (uint16 pu16_1[], uint8 u8Input, uint8 u8K);
extern uint8    ALG_u8SecondOrderFilter       (uint16 pu16_1[], uint8 u8Input, uint8 u8K);
extern uint16   ALG_u16FirstOrderFilter       (uint32 pu32_1[], uint16 u16Input, uint8 u8K);
extern uint16   ALG_u16SecondOrderFilter      (uint32 pu32_1[], uint16 u16Input, uint8 u8K);
extern void     ALG_vHysteresis_8             (uint8 pu8_1[], const uint8 u8Input, const uint8 u8Hysteresis);
extern void    ALG_vHysteresis_16	      (uint16 pu16_1[], const uint16 u16Input, const uint16 u16Hysteresis);
extern uint8    ALG_u8CurveLookup_8_8_Limit   (uint8 pu8_1[], uint8 pu8_2[], const uint8 u8Input, const uint8 u8Size );
extern uint8    ALG_cu8CurveLookup_8_8_Limit   (const uint8 pu8_1[],const uint8 pu8_2[], const uint8 u8Input, const uint8 u8Size );
extern uint16 ALG_u16CurveLookup_16_16_Limit( uint16 pu16_1[], uint16 pu16_2[], const uint16 u16Input, const uint8 u8Size );
extern uint16 ALG_cu16CurveLookup_16_16_Limit( const uint16 pu16_1[], const uint16 pu16_2[], const uint16 u16Input, const uint8 u8Size );
extern uint8    ALG_u8GetClosestEntry        (uint8  pu8_1[], uint8 u8Size, uint8 u8Input);
extern uint8    ALG_cu8GetClosestEntry        (const uint8  pu8_1[], uint8 u8Size, uint8 u8Input);
extern uint16 ALG_u16GetClosestEntry(uint16 pu16_1[], uint8 u8Size, uint16 u16Input);
extern uint16 ALG_cu16GetClosestEntry(const uint16 pu16_1[],  uint8 u8Size, uint16 u16Input);
extern void ALG_vInputSigleChannelInit(ALG_tstInputAttributes *pAtr);
extern uint16 ALG_u16InputProcessChannel(ALG_tstInputAttributes *pAtr, uint16 u16In, uint8 *pu8InputUsable);


extern uint8 ALG_u8SensorFilter(const tstSensorFilterConstantType SensorPar[], tstSensorFilterVariableType SensorVar[]);
/* End of check if informations are already included
******************************************************************************/
#endif                                  /* ifndef ALG_H */

/*****************************************************************************
* EOF: Alg.h
******************************************************************************/

