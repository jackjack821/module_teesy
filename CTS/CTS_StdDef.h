/***************************************************************************************************
                       STANDARD DEFINIITON FOR CLIMATE THERMODYNAMICS SYSTEM                        
                    
  .File Name  : CTS_StdDef.h
  
  .Description: This file provides the standard definition for climate thermodynamics system.
  
  --------------------------------------------------------------------------------------------------
    Version     Date        Author          Change
  --------------------------------------------------------------------------------------------------
    V001        2015-08-10  Chen Xiongzhi   - Creat this module.
    V002        2015-11-10  Chen Xiongzhi   - Rename.
    V003        2015-11-13  Chen Xiongzhi   - Rename.
    V004        2015-11-13  Chen Xiongzhi   - Rename to ATCS_StdDef.
    V005        2016-01-19  Chen Xiongzhi   - Add error processing status.
    V006        2016-01-20  Chen Xiongzhi   - Rename to CTS_StdDef.
***************************************************************************************************/

#ifndef CTS_StdDef_H
#define CTS_StdDef_H


#include "string.h"
#include "stddef.h"
#include "math.h"
//#include "limits.h"
#include "stdlib.h"

typedef unsigned char       cuint8;
typedef signed char         cint8;
typedef unsigned short      cuint16;
typedef signed short        cint16;
typedef unsigned long       cuint32;
typedef signed long         cint32;
typedef unsigned char       cbool;

#define CTS_True            1U
#define CTS_False           0U

typedef enum 
{
    CTS_nInvalid=0,
    CTS_nValid
}CTS_tenValidSta;

typedef enum 
{
    CTS_nMacLo=0,
    CTS_nMacBetweenHiLo,
    CTS_nMacHi
}CTS_tenMacHiLoSta;

typedef enum 
{
    CTS_nOff=0,
    CTS_nOn
}CTS_tenOnOffSta;

typedef struct
{
	const cuint16 *pu16TableX;
	cuint8 u8SizeX;
	const cuint16 *pu16TableY;
}CTS_tstU16Table1DType;

typedef struct
{
	const cuint16 *pu16TableX;
	cuint8 u8SizeX;
	const cuint16 *pu16TableY;
	cuint8 u8SizeY;
	const cuint16 *pu16TableZ;
}CTS_tstU16Table2DType;

typedef struct
{
	const cuint16 *pu16TableX;
	cuint8 u8SizeX;
	const cuint16 *pu16TableY;
	cuint8 u8SizeY;
	const cuint16 *pu16TableZ;
    cuint8 u8SizeZ;
    const cuint16 *pu16TableU;
}CTS_tstU16Table3DType;

typedef struct
{
	const cuint16 *pu16TableX;
	cuint8 u8SizeX;
	const cuint16 *pu16TableY;
	cuint8 u8SizeY;
	const cuint16 *pu16TableZ;
    cuint8 u8SizeZ;
    const cuint16 *pu16TableU;
    cuint8 u8SizeU;
    const cuint16 *pu16TableV;
}CTS_tstU16Table4DType;

typedef struct
{
	const cuint8 *pu8Array;
	cuint8 u8Size;
}CTS_tstU8ConstArrayType;

typedef struct
{
	const cuint16 *pu16Array;
	cuint8 u8Size;
}CTS_tstU16ConstArrayType;

typedef struct
{
    cuint16 u16Const;
}CTS_tstU16ConstType;

typedef struct
{
    cuint8 u8Const;
}CTS_tstU8ConstType;


#endif

/***************************************************************************************************
  EOF: CTS_StdDef.h
***************************************************************************************************/
