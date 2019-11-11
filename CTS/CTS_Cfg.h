/***************************************************************************************************
                            CLIMATE THERMODYNAMICS SYSTEM CONFIGURATION               
                        
  .File Name  : CTS_Cfg.h
  
  .Description: This file is used to provide the configuration data for climate thermodynamics  
                system.
  
  --------------------------------------------------------------------------------------------------
    Version     Date        Author          Change
  --------------------------------------------------------------------------------------------------
    V001        2015-02-25  Chen Xiongzhi   - Creat this module.
    V002        2015-11-03  Chen Xiongzhi   - Update the filter target calculation data.
    V003        2015-11-13  Chen Xiongzhi   - Move the configurations in VIVP_Cfg in to this file.
    V004        2016-01-04  Chen Xiongzhi   - Make it compatible with tranditional ICT.
    V005        2016-01-12  Chen Xiongzhi   - Add configuration data for double zone heat effect 
                                              process.
    V006        2016-01-13  Chen Xiongzhi   - Rename to ATCS_Cfg for automatic temperature control
                                              strategy.
    V007        2016-01-20  Chen Xiongzhi   - Rename to CTS_Cfg.
***************************************************************************************************/

#ifndef CTS_Cfg_H
#define	CTS_Cfg_H


/***************************************************************************************************
                                    GLOBAL VARIABLES DECLARATION                                    

  Note(s): Declare all the global variables in this section.
***************************************************************************************************/

#ifndef CTS_Cfg

extern const CTS_tstU16ConstType CTS_stThermalAbsoluteZero;

extern const CTS_tstU16ConstType CTS_stThermalRelativeZero;

extern const CTS_tstU16ConstType CTS_stBlowSpdRelativeZero;

extern const CTS_tstU8ConstType CTS_stZoneNum;

extern const CTS_tstU8ConstType CTS_stIctMode;

extern const CTS_tstU16ConstType CTS_stVictActiveTime;

extern const CTS_tstU16ConstType CTS_stSensorIctActiveTime;

extern const CTS_tstU16ConstType CTS_stIctInvalidWaitTime;

extern const CTS_tstU16ConstType CTS_stMaxTgtBlowTempLimit;

extern const CTS_tstU16ConstArrayType CTS_stAirdModePos;

extern const CTS_tstU16ConstType CTS_stDefRfaPos;

extern const CTS_tstU16ConstType CTS_stRfaFreshRtoBase;

extern const CTS_tstU16Table1DType CTS_stRfaFreshRto;

extern const CTS_tstU16Table2DType CTS_stEvapFreshOfs;

extern const CTS_tstU16Table2DType CTS_stEvapRecircOfs;

extern const CTS_tstU8ConstType CTS_stEvapTempChgBase;

extern const CTS_tstU16ConstType CTS_stEvapTempChg;

extern const CTS_tstU8ConstType CTS_stHctChgBase;

extern const CTS_tstU16Table1DType CTS_stPumpOnHctChg;

extern const CTS_tstU16Table1DType CTS_stPumpOffHctChg;

extern const CTS_tstU16ConstType CTS_stMacRtoBase;

extern const CTS_tstU16Table2DType CTS_stHiMacRtoL;

extern const CTS_tstU16Table2DType CTS_stLoMacRtoL;

extern const CTS_tstU16Table2DType CTS_stHiMacRtoR;

extern const CTS_tstU16Table2DType CTS_stLoMacRtoR;

extern const CTS_tstU16Table2DType CTS_stHiMacRtoRe;

extern const CTS_tstU16Table2DType CTS_stLoMacRtoRe;

extern const CTS_tstU8ConstType CTS_stBlowTempChgBase;

extern const CTS_tstU16ConstType CTS_stBlowTempChg;

extern const CTS_tstU16Table2DType CTS_stBlowSpd;

extern const CTS_tstU16Table2DType CTS_stVelBlowSpdOfs;

extern const CTS_tstU16ConstType CTS_stSensorIctStableWaitTime;

extern const CTS_tstU16Table1DType CTS_stSensorIct;

extern const CTS_tstU16ConstType CTS_stSensorIctTolerance;

extern const CTS_tstU8ConstType CTS_stSensorIctChgBase;

extern const CTS_tstU16ConstType CTS_stSensorIctChg;

extern const CTS_tstU16ConstType CTS_stPcbTempStableWaitTime;

extern const CTS_tstU16Table1DType CTS_stPcbTemp;

extern const CTS_tstU16Table1DType CTS_stPcbIctLimit;

extern const CTS_tstU16ConstType CTS_stPcbIctBase;

extern const CTS_tstU16Table2DType CTS_stPcbIctFactor;

extern const CTS_tstU16ConstType CTS_stReadBackBase;

extern const CTS_tstU16Table2DType CTS_stIgnOffReadBack;

extern const CTS_tstU16Table2DType CTS_stSunLoadHeat;

extern const CTS_tstU8ConstType CTS_stBodyShellHeatChgBase;

extern const CTS_tstU16ConstType CTS_stBodyShellHeatChg;

extern const CTS_tstU16Table2DType CTS_stVelEngineHeat;

extern const CTS_tstU16ConstType CTS_stFuelModeBaseHeat;

extern const CTS_tstU16ConstType CTS_stElecModeBaseHeat;

extern const CTS_tstU16ConstType CTS_stCalibrateBaseHeat;

extern const CTS_tstU16Table3DType CTS_stBalanceHeadZoneTemp;

extern const CTS_tstU16Table3DType CTS_stCabinTempStcOfs;

extern const CTS_tstU8ConstType CTS_stHeatItemChgBase;

extern const CTS_tstU16ConstArrayType CTS_stHeadZoneFlowItemChg;

extern const CTS_tstU16ConstArrayType CTS_stCabinFlowItemChg;

extern const CTS_tstU16ConstType CTS_stShellItemChg;

extern const CTS_tstU8ConstType CTS_stFlowItemRtoBase;

extern const CTS_tstU8ConstArrayType CTS_stHeadZoneFlowItemRto;

extern const CTS_tstU8ConstArrayType CTS_stCabinFlowItemRto;

extern const CTS_tstU8ConstType CTS_stFlowItemRtoChgBase;

extern const CTS_tstU16ConstType CTS_stFlowItemRtoChg;

extern const CTS_tstU8ConstType CTS_stZoneEffectBase;

extern const CTS_tstU8ConstArrayType CTS_stDblZoneEffectFactor;

extern const CTS_tstU8ConstArrayType CTS_stFrontToRearEffectFactor;

extern const CTS_tstU8ConstArrayType CTS_stRearToFrontEffectFactor;

extern const CTS_tstU16Table3DType CTS_stPreCtlBlowTemp;

extern const CTS_tstU16ConstType CTS_stFbCtlPFactorBase;

extern const CTS_tstU16Table1DType CTS_stFbCtlPFactor;

extern const CTS_tstU8ConstType CTS_stZoneOfsFactorBase;

extern const CTS_tstU8ConstArrayType CTS_stDblZoneOfsFactor;

extern const CTS_tstU8ConstArrayType CTS_stFrontRearOfsFactor;

#endif


#endif                                  

/***************************************************************************************************
  EOF: CTS_Cfg.h
***************************************************************************************************/
