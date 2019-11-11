/***************************************************************************************************
                        ALGORITHM LIBRARY FOR CLIMATE THERMODYNAMICS SYSTEM                       
 
  .File Name  : CTS_Alg.h
  
  .Description: This file provides the algorithm for climate thermodynamics system.
  
  --------------------------------------------------------------------------------------------------
    Version     Date        Author          Change
  --------------------------------------------------------------------------------------------------
    V001        2015-08-10  Chen Xiongzhi   - Creat this module.
    V002        2015-11-10  Chen Xiongzhi   - Rename to VALG.
    V003        2016-01-13  Chen Xiongzhi   - Rename to ATCS_Alg.
    V004        2016-01-20  Chen Xiongzhi   - Rename to CTS_Alg.
***************************************************************************************************/

#ifndef CTS_Alg_H
#define CTS_Alg_H


/***************************************************************************************************
                                EXPORT INTERFACE FUNCTION PROTOTYPES                      

  Note(s): In this section declare all system global function prototypes of your module.
***************************************************************************************************/

cuint8 CTS_u8GetU16ClosestEntry(const cuint16 au16Array[], cuint8 u8Size, cuint16 u16Input);
cuint8 CTS_u8I16ToU8(cint16 i16Input, cint16 i16ZeroPoint);
cuint16 CTS_u16I16ToU16(cint16 i16Input, cint16 i16ZeroPoint);
cint8 CTS_i8I16ToI8(cint16 i16Input);
cuint8 CTS_u8U32ToU8(cuint32 u32Input);
cuint8 CTS_u8U16ToU8(cuint16 u16Input);
cint16 CTS_i16I32ToI16(cint32 i32Input);
cuint16 CTS_u16I32ToU16(cint32 i32Input, cint32 i32ZeroPoint);
cuint8 CTS_u8I32ToU8(cint32 i32Input, cint32 i32ZeroPoint);
cuint16 CTS_u16U32ToU16(cuint32 u32Input);
cint32 CTS_i32U32ToI32(cuint32 u32Input);
cuint32 CTS_u32i32ToU32(cint32 i32Input);
cuint8 CTS_u8Lookup1D_Limit(cuint8 u8Input, cuint8 u8Size, const cuint8 au8TableX[], const cuint8 au8TableY[]);
cuint8 CTS_u8Lookup2D_Limit(cuint8 u8InputX, cuint8 u8InputY, cuint8 u8SizeX, cuint8 u8SizeY, const cuint8 au8TableX[], const cuint8 au8TableY[], const cuint8 au8TableZ[]);
cuint8 CTS_u8Lookup1D_Linear(cuint8 u8Input, cuint8 u8Size, const cuint8 au8TableX[], const cuint8 au8TableY[]);
cuint8 CTS_u8Lookup2D_Linear(cuint8 u8InputX, cuint8 u8InputY, cuint8 u8SizeX, cuint8 u8SizeY, const cuint8 au8TableX[], const cuint8 au8TableY[], const cuint8 au8TableZ[]);
cuint16 CTS_u16Lookup1D_Limit(cuint16 u16Input, cuint8 u8Size, const cuint16 au16TableX[], const cuint16 au16TableY[]);
cuint16 CTS_u16Lookup2D_Limit(cuint16 u16InputX, cuint16 u16InputY, cuint8 u8SizeX,cuint8 u8SizeY, const cuint16 au16TableX[], const cuint16 au16TableY[], const cuint16 au16TableZ[]);
cuint16 CTS_u16Lookup3D_Limit(cuint16 u16InputX, cuint16 u16InputY, cuint16 u16InputZ, cuint8 u8SizeX, cuint8 u8SizeY, cuint8 u8SizeZ, const cuint16 au16TableX[], const cuint16 au16TableY[], const cuint16 au16TableZ[], const cuint16 au16TableU[]);
cuint16 CTS_u16Lookup3D_Linear(cuint16 u16InputX, cuint16 u16InputY, cuint16 u16InputZ, cuint8 u8SizeX, cuint8 u8SizeY, cuint8 u8SizeZ, const cuint16 au16TableX[], const cuint16 au16TableY[], const cuint16 au16TableZ[], const cuint16 au16TableU[]);
cuint16 CTS_u16Lookup4D_Linear(cuint16 u16InputX, cuint16 u16InputY, cuint16 u16InputZ, cuint16 u16InputU, cuint8 u8SizeX, cuint8 u8SizeY, cuint8 u8SizeZ, cuint8 u8SizeU, const cuint16 au16TableX[], const cuint16 au16TableY[], const cuint16 au16TableZ[], const cuint16 au16TableU[], const cuint16 au16TableV[]);
cuint32 CTS_u32FirstOrderFilter(cuint32 u32PreValue, cuint16 u16Input, cuint16 u16FilterFactor, cuint8 u8FilterShift);
cuint8 CTS_u8ReadConstArray(const cuint8 au8Array[], cuint8 u8Size, cuint8 u8Index);
cuint16 CTS_u16ReadConstArray(const cuint16 au16Array[], cuint8 u8Size, cuint8 u8Index);


#endif

/***************************************************************************************************
  EOF: CTS_Alg.h
***************************************************************************************************/
