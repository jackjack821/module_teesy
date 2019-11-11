/**************************** .FILE_HEADER_BEGIN *****************************
  .TITLE  [Ict_Type, Type define for module ICT  ]
*-----------------------------------------------------------------------------
  .FILE   [ Ict_Type.h                                                         ]
*-----------------------------------------------------------------------------

 Version Date        		Author                       Change                      
 -----------------------------------------------------------------------------
 Rev 01.00.01  2014/04/13     OuyangBihuan       	    	The first version               

*****************************************************************************/

#ifndef ICT_TYPE_H
#define ICT_TYPE_H

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
    ICT_nInvalid=0u,
    ICT_nValid,
    ICT_nDefault,
    ICT_nLastValue
}ICT_tenValueSts;

typedef struct
{
    uint8 u8InitNeedFlag;
}ICT_tstCalc1000MsFlagIn;
typedef struct
{
    uint8 u81000MsFlag;
}ICT_tstCalc1000MsFlagOut;

typedef struct
{
    uint8 u8InitNeedFlag;
    uint16 u16SensorRawValue;
}ICT_tstCalSensorValueIn;
typedef struct
{
    uint16 u16SensorValue;
}ICT_tstCalSensorValueOut;

typedef struct
{
    uint8 u8OatValid;
    uint8 u8AirdValid;
    uint16 u16AmbientValue;
    uint16 u16AirdPos;    
}ICT_tstCalStaticOffsetIn;
typedef struct
{
    int16 i16StaticOffset;
}ICT_tstCalStaticOffsetOut;

typedef struct
{
    uint8 u8CcsValid;
    uint8 u8OatValid;
    uint8 u8InitNeedFlag;
    uint16 u16CcsSetTemp;
    uint16 u16OatValue;
    int16 i16IctStaticValue;
}ICT_tstCalDynamicOffsetIn;
typedef struct
{
    uint16 u16MaxDiff;
    uint16 u16DynMax;
    uint16 u16DynOffset;
    int16 i16DynOffset;
}ICT_tstCalDynamicOffsetOut;

typedef struct
{
    uint8 u8ResetNeedFlag;
    uint16 u16CcsSetTemp;
    uint16 u16UnDampingIctValue;
    
}ICT_tstDampingIn;
typedef struct
{
    uint16 u16IctValue;
}ICT_tstDampingOut;

typedef struct
{
    uint16 u16SensorAdValue;
    uint16 u16SensorValue;
    uint16 u16DynMax;
    uint16 u16MaxDiff;
    uint16 u16DynOffset;
    int16 i16DynOffset;
    uint16 u16StaticOffset;
    uint16 u16UndampedValue;
    uint16 u16IctValue;
    uint16 u16ErrorCode;
    uint8  u8ModuleValid;
}ICT_tstMainOut;/*Ccp control*/
typedef enum
{
	Ict_nReplaceIctValue,
	Ict_nCcpForceMax
}CcpControl_Ict;

/*****************************************************************************
* End of check if informations are already included
******************************************************************************/

#endif                                  /* ifndef ICT_TYPE_H */
/*****************************************************************************
* EOF: Ict_Type.h
******************************************************************************/
