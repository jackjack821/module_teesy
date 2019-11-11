/***************************************************************************************************
                                     IMPORT PREPROCESSING LAYER                                  
                                 
  .File Name  : IPL_Type.h
  
  .Description: This file is used to preprocess the import value.
  
  --------------------------------------------------------------------------------------------------
    Version     Date        Author          Change
  --------------------------------------------------------------------------------------------------
    V001        2014-01-08  Chen Xiongzhi   - Creat this module.
    V002        2015-01-22  Chen Xiongzhi   - Change the structure of the code for input conditions 
                                              process.
    V003        2015-01-30  Chen Xiongzhi   - Change the function structure, add input and output 
                                              structure for parameter passing.
    V004        2015-02-26  Chen Xiongzhi   - Change the code to conform to the rules of MISRA_C.
    V005        2015-08-06  Chen Xiongzhi   - Rename.
    V006        2015-11-10  Chen Xiongzhi   - Rename from IVP to VIVP.
    V007        2016-01-04  Chen Xiongzhi   - Make it compatible with tranditional ICT.
    V008        2016-01-13  Chen Xiongzhi   - Rename to AIVP for ATCS.
    V009        2016-01-19  Chen Xiongzhi   - Add error processing status.
    V010        2016-01-20  Chen Xiongzhi   - Rename to IPL.
    V011        2016-01-30  Chen Xiongzhi   - Update the function structure in order to make it 
                                              correspond to the block diagram.
***************************************************************************************************/

#ifndef IPL_Type
#define IPL_Type


/***************************************************************************************************
                                          TYPE DEFINITIONS                                          

  Note(s): In this section define the type definitions
***************************************************************************************************/

/* 8-bit output structure */
typedef struct
{
    CTS_tenValidSta enOutputValidSta;
    cuint8 u8Output;
}IPL_tstU8Output;

/* 16-bit output structure */
typedef struct
{
    CTS_tenValidSta enOutputValidSta;
    cuint16 u16Output;
}IPL_tstU16Output;

/* EVAP temperature filter variables */
typedef struct
{
    CTS_tenValidSta enFlInitValSta;
    CTS_tenValidSta enEvapTempSta;
    cuint32 u32EvapTemp;
    cuint16 u16EvapTemp;
}IPL_tstEvapTempFl;

/* Heater core temperature filter variables */
typedef struct
{
    CTS_tenValidSta enFlInitValSta;
    CTS_tenValidSta enHctSta;
    cuint32 u32Hct;
    cuint16 u16Hct;
}IPL_tstHctFl;

/* Sensor ICT filter variables */
typedef struct
{
    CTS_tenValidSta enFlInitValSta;
    CTS_tenValidSta enSensorIctSta;
    cuint32 u32SensorIct;
    cuint16 u16SensorIct;
}IPL_tstSensorIctFl;

/* Blowout temperature filter variables */
typedef struct
{
    CTS_tenValidSta enFlInitValSta;
    CTS_tenValidSta enBlowTempSta;
    cuint32 u32BlowTemp;
    cuint16 u16BlowTemp;
}IPL_tstBlowTempFl;

/* Input variables for sensor ICT calculation */
typedef struct
{
    CTS_tenValidSta enSensorIctAdSta;
    cuint16 u16SensorIctAd;
    cuint16 u16StableWaitTime;
}IPL_tstCalcSensorIctIn;

/* Sensor ICT */
typedef struct
{
    CTS_tenValidSta enSensorIctSta;
    cuint16 u16StableWaitTime;
    cuint16 u16SensorIct;
}IPL_tstSensorIct;

/* Input variables for sensor ICT filter */
typedef struct
{
    IPL_tstSensorIct *pstSensorIct;
    IPL_tstSensorIctFl *pstSensorIctFl;
    CTS_tenValidSta enSensorIctFlFactorSta;
    cuint16 u16SensorIctFlFactor;
    cuint8 u8SensorIctFlShift;
}IPL_tstSensorIctFlIn;

/* Input variables for AIRD mode calculation */
typedef struct
{
    CTS_tenValidSta enAirdPosSta;
    cuint16 u16AirdPos;
}IPL_tstCalcAirdModeIn;

/* AIRD mode */
typedef struct
{
    CTS_tenValidSta enAirdModeSta;
    cuint8 u8AirdMode;
}IPL_tstAirdMode;

/* Input variables for EVAP temperature offset calculation */
typedef struct
{
    CTS_tenValidSta enRfaPosSta;
    cuint16 u16RfaPos;
    CTS_tenValidSta enOatSta;
    cuint16 u16Oat;
    CTS_tenValidSta enCabinTempSta;
    cuint16 u16CabinTemp;
    CTS_tenValidSta enBlwrVoltSta;
    cuint16 u16BlwrVolt;
}IPL_tstCalcEvapTempOfsIn;

/* Input variables for compressor off EVAP temperature calculation */
typedef struct
{
    CTS_tenValidSta enRfaPosSta;
    cuint16 u16RfaPos;
    CTS_tenValidSta enOatSta;
    cuint16 u16Oat;
    CTS_tenValidSta enCabinTempSta;
    cuint16 u16CabinTemp;
}IPL_tstCalcCompOffEvapTempIn;

/* Input variables for EVAP temperature calculation */
typedef struct
{
    CTS_tenValidSta enRawEvapTempSta;
    cuint16 u16RawEvapTemp;
    CTS_tenValidSta enCompValidSta;
    CTS_tenOnOffSta enCompOnOffSta;
    IPL_tstCalcEvapTempOfsIn *pstCalcEvapTempOfsIn;
    IPL_tstCalcCompOffEvapTempIn *pstCalcCompOffEvapTempIn;
}IPL_tstCalcEvapTempIn;

/* EVAP temperature */
typedef struct
{
    CTS_tenValidSta enEvapTempSta;
    cuint16 u16EvapTemp;
}IPL_tstEvapTemp;

/* Input variables for EVAP temperature filter */
typedef struct
{
    IPL_tstEvapTemp *pstEvapTemp;
    IPL_tstEvapTempFl *pstEvapTempFl;
    CTS_tenValidSta enEvapTempFlFactorSta;
    cuint16 u16EvapTempFlFactor;
    cuint8 u8EvapTempFlShift;
}IPL_tstEvapTempFlIn;

/* EVAP temperature offset */
typedef struct
{
    CTS_tenValidSta enEvapTempOfsSta;
    cuint16 u16EvapTempOfs;
}IPL_tstEvapTempOfs;

/* Compressor off EVAP temperature */
typedef struct
{
    CTS_tenValidSta enCompOffEvapTempSta;
    cuint16 u16CompOffEvapTemp;
}IPL_tstCompOffEvapTemp;

/* Input variables for heater core temperature filter */
typedef struct
{
    CTS_tenValidSta enHeaterPumpValidSta;
    CTS_tenOnOffSta enHeaterPumpOnOffSta;
    CTS_tenValidSta enEvapTempSta;
    cuint16 u16EvapTemp;
    CTS_tenValidSta enRawHctSta;
    cuint16 u16RawHct;
    IPL_tstHctFl *pstHctFl;
    CTS_tenValidSta enPumpOnFlFactorSta;
    cuint16 u16PumpOnFlFactor;
    CTS_tenValidSta enPumpOffFlFactorSta;
    cuint16 u16PumpOffFlFactor;
    cuint8 u8HctFlShift;
}IPL_tstHctFlIn;

/* Input variables for limit MAC ratio calculation */
typedef struct
{
    CTS_tenValidSta enAirdModeSta;
    cuint8 u8AirdMode;
    CTS_tenValidSta enBlwrVoltSta;
    cuint16 u16BlwrVolt;
}IPL_tstCalcLimitMacRtoIn;

/* Limit MAC ratio */
typedef struct
{
    CTS_tenValidSta enLimitMacRtoSta;
    cuint16 u16HiMacRto;
    cuint16 u16LoMacRto;
    cuint16 u16MacRtoBase;
}IPL_tstLimitMacRto;

/* Input variables for raw blowout temperature calculation */
typedef struct
{
    CTS_tenValidSta enEvapTempSta;
    cuint16 u16EvapTemp;
    CTS_tenValidSta enHctSta;
    cuint16 u16Hct;
    CTS_tenValidSta enTgtBlowTempSta;
    cuint16 u16TgtBlowTemp;
    CTS_tenValidSta enHiLoValidSta;
    CTS_tenMacHiLoSta enHiLoSta;
    IPL_tstLimitMacRto *pstLimitMacRto; 
}IPL_tstCalcRawBlowTempIn;

/* Output variables of blowout temperature output */
typedef struct
{
    CTS_tenValidSta enRawBlowTempSta;
    cuint16 u16RawBlowTemp;
    cbool boLoFlag;
}IPL_tstRawBlowTemp;

/* Input variables for blowout temperature calculation */
typedef struct
{
    IPL_tstCalcRawBlowTempIn *pstCalcRawBlowTempIn;
    IPL_tstBlowTempFl *pstBlowTempFl;
    CTS_tenValidSta enBlowTempFlFactorSta;
    cuint16 u16BlowTempFlFactor;
    cuint8 u8BlowTempFlShift;
    IPL_tstBlowTempFl *pstBlowTempFlUpdateAdd;
}IPL_tstCalcBlowTempIn;

/* The blowout temperature */
typedef struct
{
    CTS_tenValidSta enBlowTempSta;
    cuint16 u16BlowTemp;
}IPL_tstBlowTemp;

/* Input variables for blowout temperature filter */
typedef struct
{
    IPL_tstRawBlowTemp *pstRawBlowTemp;
    IPL_tstBlowTempFl *pstBlowTempFl;
    CTS_tenValidSta enBlowTempFlFactorSta;
    cuint16 u16BlowTempFlFactor;
    cuint8 u8BlowTempFlShift;
}IPL_tstBlowTempFlIn;

/* Input variables for blowout speed calculation */
typedef struct
{
    CTS_tenValidSta enVelocitySta;
    cuint16 u16Velocity;
    CTS_tenValidSta enRfaPosSta;
    cuint16 u16RfaPos;
    CTS_tenValidSta enBlwrVoltSta;
    cuint16 u16BlwrVolt;
}IPL_tstCalcBlowSpdIn;

/* Blowout speed */
typedef struct
{
    CTS_tenValidSta enBlowSpdSta;
    cuint16 u16BlowSpd;
}IPL_tstBlowSpd;

/* Input variables for sun calculation */
typedef struct
{
    CTS_tenValidSta enRawSuntStaL;
    cuint16 u16RawSunL;
    CTS_tenValidSta enRawSuntStaR;
    cuint16 u16RawSunR;
}IPL_tstCalcSunIn;

/* Sun */
typedef struct
{
    CTS_tenValidSta enSunSta;
    cuint16 u16Sun;
}IPL_tstSun;

/* Input variables for sun load heat calculation */
typedef struct
{
    CTS_tenValidSta enSunSta;
    cuint16 u16Sun;
    CTS_tenValidSta enOatSta;
    cuint16 u16Oat;
}IPL_tstCalcSunLoadHeatIn;

/* Sun load heat */
typedef struct
{
    CTS_tenValidSta enSunLoadHeatSta;
    cuint16 u16SunLoadHeat;
}IPL_tstSunLoadHeat;

/* Input variables for velocity engine heat calculation */
typedef struct
{
    CTS_tenValidSta enVelocitySta;
    cuint16 u16Velocity;
    CTS_tenValidSta enOatSta;
    cuint16 u16Oat;
    CTS_tenValidSta enFuelModeValidSta;
    cbool boInFuelMode;
    CTS_tenValidSta enElecModeValidSta;
    cbool boInElecMode;
}IPL_tstCalcVelEngineHeatIn;

/* Velocity engine heat */
typedef struct
{
    CTS_tenValidSta enVelEngineHeatSta;
    cuint16 u16VelEngineHeat;
}IPL_tstVelEngineHeat;

/* Input variables for PCB temperature calculation */
typedef struct
{
    CTS_tenValidSta enPcbTempAdSta;
    cuint16 u16PcbTempAd;
    cuint16 u16StableWaitTime;
}IPL_tstCalcPcbTempIn;

/* PCB temperature */
typedef struct
{
    CTS_tenValidSta enPcbTempSta;
    cuint16 u16StableWaitTime;
    cuint16 u16PcbTemp;
}IPL_tstPcbTemp;

/* Input variables for sensor ICT filter vairables updating  */
typedef struct
{
    IPL_tstSensorIctFl *pstInputAddress;
    IPL_tstSensorIctFl *pstUpdateAddress;
}IPL_tstUpdateSensorIctFlIn;

/* Input variables for EVAP temperature filter vairables updating  */
typedef struct
{
    IPL_tstEvapTempFl *pstInputAddress;
    IPL_tstEvapTempFl *pstUpdateAddress;
}IPL_tstUpdateEvapTempFlIn;

/* Input variables for HCT filter vairables updating  */
typedef struct
{
    IPL_tstHctFl *pstInputAddress;
    IPL_tstHctFl *pstUpdateAddress;
}IPL_tstUpdateHctFlIn;

/* Input variables for blowout temperature filter vairables updating  */
typedef struct
{
    IPL_tstBlowTempFl *pstInputAddress;
    IPL_tstBlowTempFl *pstUpdateAddress;
}IPL_tstUpdateBlowTempFlIn;


#endif                              

/***************************************************************************************************
  EOF: IPL_Type.h
***************************************************************************************************/
