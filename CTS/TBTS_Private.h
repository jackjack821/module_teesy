/***************************************************************************************************
                                TARGET BLOWOUT TEMPERATURE STRATEGY                                    
                                        
  .File Name  : TBTS_Private.h
  
  .Description: This file is used for the target blowout temperature calculation.
  
  --------------------------------------------------------------------------------------------------
    Version     Date        Author          Change
  --------------------------------------------------------------------------------------------------
    V001        2016-01-13  Chen Xiongzhi   - Creat this module.
    V002        2016-01-19  Chen Xiongzhi   - Add error processing status.
    V003        2016-01-20  Chen Xiongzhi   - Rename to TBTS.
***************************************************************************************************/

#ifndef TBTS_Private
#define TBTS_Private


/***************************************************************************************************
                                  FILE LOCAL INTERFACE DEFINITIONS                                  

  Note(s): In this section define all file local macros interface.
***************************************************************************************************/

/* Writing interface */ 
#define TBTS_vWriteEnTgtBlowTempStaL(Value)     (TBTS_astU16Output[TBTS_nu16TgtBlowTempL].enOutputValidSta = (Value))
#define TBTS_vWriteU16TgtBlowTempL(Value)       (TBTS_astU16Output[TBTS_nu16TgtBlowTempL].u16Output = (Value))
#define TBTS_vWriteEnTgtBlowTempStaR(Value)     (TBTS_astU16Output[TBTS_nu16TgtBlowTempR].enOutputValidSta = (Value))
#define TBTS_vWriteU16TgtBlowTempR(Value)       (TBTS_astU16Output[TBTS_nu16TgtBlowTempR].u16Output = (Value))
#define TBTS_vWriteEnTgtBlowTempStaRe(Value)    (TBTS_astU16Output[TBTS_nu16TgtBlowTempRe].enOutputValidSta = (Value))
#define TBTS_vWriteU16TgtBlowTempRe(Value)      (TBTS_astU16Output[TBTS_nu16TgtBlowTempRe].u16Output = (Value))

/* Reading interface */
#define TBTS_enReadTgtBlowTempStaL()            (TBTS_astU16Output[TBTS_nu16TgtBlowTempL].enOutputValidSta)
#define TBTS_u16ReadTgtBlowTempL()              (TBTS_astU16Output[TBTS_nu16TgtBlowTempL].u16Output)
#define TBTS_enReadTgtBlowTempStaR()            (TBTS_astU16Output[TBTS_nu16TgtBlowTempR].enOutputValidSta)
#define TBTS_u16ReadTgtBlowTempR()              (TBTS_astU16Output[TBTS_nu16TgtBlowTempR].u16Output)
#define TBTS_enReadTgtBlowTempStaRe()           (TBTS_astU16Output[TBTS_nu16TgtBlowTempRe].enOutputValidSta)
#define TBTS_u16ReadTgtBlowTempRe()             (TBTS_astU16Output[TBTS_nu16TgtBlowTempRe].u16Output)


#endif                              

/***************************************************************************************************
  EOF: TBTS_Private.h
***************************************************************************************************/
