/***************************************************************************************************
                                     IMPORT PREPROCESSING LAYER                                  
                                 
  .File Name  : IPL_Private.h
  
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

#ifndef IPL_Private
#define IPL_Private


/***************************************************************************************************
                                  FILE LOCAL INTERFACE DEFINITIONS                                  

  Note(s): In this section define all file local macros interface.
***************************************************************************************************/

/* Writing interface */
#define IPL_vWriteEnSensorIctSta(Value)         (IPL_astU16Output[IPL_nu16SensorIct].enOutputValidSta = (Value))
#define IPL_vWriteU16SensorIct(Value)           (IPL_astU16Output[IPL_nu16SensorIct].u16Output = (Value))
#define IPL_vWriteEnAirdModeSta(Value)          (IPL_astU8Output[IPL_nu8AirdMode].enOutputValidSta = (Value))
#define IPL_vWriteU8AirdMode(Value)             (IPL_astU8Output[IPL_nu8AirdMode].u8Output = (Value))
#define IPL_vWriteEnEvapTempSta(Value)          (IPL_astU16Output[IPL_nu16EvapTemp].enOutputValidSta = (Value))
#define IPL_vWriteU16EvapTemp(Value)            (IPL_astU16Output[IPL_nu16EvapTemp].u16Output = (Value))
#define IPL_vWriteEnHctSta(Value)               (IPL_astU16Output[IPL_nu16Hct].enOutputValidSta = (Value))
#define IPL_vWriteU16Hct(Value)                 (IPL_astU16Output[IPL_nu16Hct].u16Output = (Value))
#define IPL_vWriteEnBlowTempStaL(Value)         (IPL_astU16Output[IPL_nu16BlowTempL].enOutputValidSta = (Value))
#define IPL_vWriteU16BlowTempL(Value)           (IPL_astU16Output[IPL_nu16BlowTempL].u16Output = (Value))
#define IPL_vWriteEnBlowTempStaR(Value)         (IPL_astU16Output[IPL_nu16BlowTempR].enOutputValidSta = (Value))
#define IPL_vWriteU16BlowTempR(Value)           (IPL_astU16Output[IPL_nu16BlowTempR].u16Output = (Value))
#define IPL_vWriteEnBlowTempStaRe(Value)        (IPL_astU16Output[IPL_nu16BlowTempRe].enOutputValidSta = (Value))
#define IPL_vWriteU16BlowTempRe(Value)          (IPL_astU16Output[IPL_nu16BlowTempRe].u16Output = (Value))
#define IPL_vWriteEnBlowSpdSta(Value)           (IPL_astU16Output[IPL_nu16BlowSpd].enOutputValidSta = (Value))
#define IPL_vWriteU16BlowSpd(Value)             (IPL_astU16Output[IPL_nu16BlowSpd].u16Output = (Value))
#define IPL_vWriteEnSunSta(Value)               (IPL_astU16Output[IPL_nu16Sun].enOutputValidSta = (Value))
#define IPL_vWriteU16Sun(Value)                 (IPL_astU16Output[IPL_nu16Sun].u16Output = (Value))
#define IPL_vWriteEnSunLoadHeatSta(Value)       (IPL_astU16Output[IPL_nu16SunLoadHeat].enOutputValidSta = (Value))
#define IPL_vWriteU16SunLoadHeat(Value)         (IPL_astU16Output[IPL_nu16SunLoadHeat].u16Output = (Value))
#define IPL_vWriteEnVelEngineHeatSta(Value)     (IPL_astU16Output[IPL_nu16VelEngineHeat].enOutputValidSta = (Value))
#define IPL_vWriteU16VelEngineHeat(Value)       (IPL_astU16Output[IPL_nu16VelEngineHeat].u16Output = (Value))
#define IPL_vWriteEnPcbTempSta(Value)           (IPL_astU16Output[IPL_nu16PcbTemp].enOutputValidSta = (Value))
#define IPL_vWriteU16PcbTemp(Value)             (IPL_astU16Output[IPL_nu16PcbTemp].u16Output = (Value))

/* Reading interface */
#define IPL_enReadSensorIctSta()                (IPL_astU16Output[IPL_nu16SensorIct].enOutputValidSta)
#define IPL_u16ReadSensorIct()                  (IPL_astU16Output[IPL_nu16SensorIct].u16Output)
#define IPL_enReadAirdModeSta()                 (IPL_astU8Output[IPL_nu8AirdMode].enOutputValidSta)
#define IPL_u8ReadAirdMode()                    (IPL_astU8Output[IPL_nu8AirdMode].u8Output)
#define IPL_enReadEvapTempSta()                 (IPL_astU16Output[IPL_nu16EvapTemp].enOutputValidSta)
#define IPL_u16ReadEvapTemp()                   (IPL_astU16Output[IPL_nu16EvapTemp].u16Output)
#define IPL_enReadHctSta()                      (IPL_astU16Output[IPL_nu16Hct].enOutputValidSta)
#define IPL_u16ReadHct()                        (IPL_astU16Output[IPL_nu16Hct].u16Output)
#define IPL_enReadBlowTempStaL()                (IPL_astU16Output[IPL_nu16BlowTempL].enOutputValidSta)
#define IPL_u16ReadBlowTempL()                  (IPL_astU16Output[IPL_nu16BlowTempL].u16Output)
#define IPL_enReadBlowTempStaR()                (IPL_astU16Output[IPL_nu16BlowTempR].enOutputValidSta)
#define IPL_u16ReadBlowTempR()                  (IPL_astU16Output[IPL_nu16BlowTempR].u16Output)
#define IPL_enReadBlowTempStaRe()               (IPL_astU16Output[IPL_nu16BlowTempRe].enOutputValidSta)
#define IPL_u16ReadBlowTempRe()                 (IPL_astU16Output[IPL_nu16BlowTempRe].u16Output)
#define IPL_enReadBlowSpdSta()                  (IPL_astU16Output[IPL_nu16BlowSpd].enOutputValidSta)
#define IPL_u16ReadBlowSpd()                    (IPL_astU16Output[IPL_nu16BlowSpd].u16Output)
#define IPL_enReadSunSta()                      (IPL_astU16Output[IPL_nu16Sun].enOutputValidSta)
#define IPL_u16ReadSun()                        (IPL_astU16Output[IPL_nu16Sun].u16Output)
#define IPL_enReadSunLoadHeatSta()              (IPL_astU16Output[IPL_nu16SunLoadHeat].enOutputValidSta)
#define IPL_u16ReadSunLoadHeat()                (IPL_astU16Output[IPL_nu16SunLoadHeat].u16Output)
#define IPL_enReadVelEngineHeatSta()            (IPL_astU16Output[IPL_nu16VelEngineHeat].enOutputValidSta)
#define IPL_u16ReadVelEngineHeat()              (IPL_astU16Output[IPL_nu16VelEngineHeat].u16Output)
#define IPL_enReadPcbTempSta()                  (IPL_astU16Output[IPL_nu16PcbTemp].enOutputValidSta)
#define IPL_u16ReadPcbTemp()                    (IPL_astU16Output[IPL_nu16PcbTemp].u16Output)


#endif                              

/***************************************************************************************************
  EOF: IPL_Private.h
***************************************************************************************************/
