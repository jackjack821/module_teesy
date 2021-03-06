/***************************************************************************************************
                                     VIRTUAL IN CAR TEMPERATURE                                     

  .File Name  : VICT_Private.h
  
  .Description: This file is used to generate the virtual in car tempreture according to the  
                conditions which including initial PCB temperature, blowout temperature, blowout
                speed, OAT and sun intensity.
  
  --------------------------------------------------------------------------------------------------
    Version     Date        Author          Change
  --------------------------------------------------------------------------------------------------
    V001        2014-09-15  Chen Xiongzhi   - Creat this module.
    V002        2015-01-05  Chen Xiongzhi   - Opimize the dual zone process logic, add off mode  
                                              process filter factors, add engine off process logic,  
                                              opimize blowout speed look up curve and update to  
                                              unsigned 16-bit VICT output.
    V003        2015-01-08  Chen Xiongzhi   - Move some input process function to IPL module, 
                                              including PCB temperature process, blowout temperature 
                                              process, blowout speed process, sunload process and  
                                              AIRD mode process.
    V004        2015-01-22  Chen Xiongzhi   - Change the structure of the code for input conditions 
                                              process.
    V005        2015-01-30  Chen Xiongzhi   - Change the function structure, add input and output 
                                              structure for parameter passing.
    V006        2015-02-26  Chen Xiongzhi   - Change the code to conform to the rules of MISRA_C.
    V007        2015-11-03  Chen Xiongzhi   - Update the filter target calculating method.
    V008        2016-01-04  Chen Xiongzhi   - Make it compatible with tranditional ICT.
    V009        2016-01-12  Chen Xiongzhi   - Add double zone heat effect process.
    V010        2016-01-19  Chen Xiongzhi   - Add error processing status.
    V011        2016-01-30  Chen Xiongzhi   - Update the function structure in order to make it 
                                              correspond to the block diagram.
    V012        2016-03-04  Chen Xiongzhi   - Amend the accuracy of heat effect item correction
                                              function.
    V013        2016-05-26  Chen Xiongzhi   - Add body shell heat filter algorithm.
***************************************************************************************************/

#ifndef VICT_Private
#define VICT_Private


/***************************************************************************************************
                                  FILE LOCAL INTERFACE DEFINITIONS                                  

  Note(s): In this section define all file local macros interface.
***************************************************************************************************/

/* Writing interface */ 
#define VICT_vWriteEnHeadZoneTempStaL(Value)    (VICT_astU16Output[VICT_nu16HeadZoneTempL].enOutputValidSta = (Value))
#define VICT_vWriteU16HeadZoneTempL(Value)      (VICT_astU16Output[VICT_nu16HeadZoneTempL].u16Output = (Value))
#define VICT_vWriteEnHeadZoneTempStaR(Value)    (VICT_astU16Output[VICT_nu16HeadZoneTempR].enOutputValidSta = (Value))
#define VICT_vWriteU16HeadZoneTempR(Value)      (VICT_astU16Output[VICT_nu16HeadZoneTempR].u16Output = (Value))
#define VICT_vWriteEnHeadZoneTempStaRe(Value)   (VICT_astU16Output[VICT_nu16HeadZoneTempRe].enOutputValidSta = (Value))
#define VICT_vWriteU16HeadZoneTempRe(Value)     (VICT_astU16Output[VICT_nu16HeadZoneTempRe].u16Output = (Value))
#define VICT_vWriteEnBodyShellTempSta(Value)    (VICT_astU16Output[VICT_nu16BodyShellTemp].enOutputValidSta = (Value))
#define VICT_vWriteU16BodyShellTemp(Value)      (VICT_astU16Output[VICT_nu16BodyShellTemp].u16Output = (Value))
#define VICT_vWriteEnCabinTempSta(Value)        (VICT_astU16Output[VICT_nu16CabinTemp].enOutputValidSta = (Value))
#define VICT_vWriteU16CabinTemp(Value)          (VICT_astU16Output[VICT_nu16CabinTemp].u16Output = (Value))
#define VICT_vWriteEnIncomingHeatSta(Value)     (VICT_astU16Output[VICT_nu16IncomingHeat].enOutputValidSta = (Value))
#define VICT_vWriteU16IncomingHeat(Value)       (VICT_astU16Output[VICT_nu16IncomingHeat].u16Output = (Value))

/* Reading interface */
#define VICT_enReadHeadZoneTempStaL()           (VICT_astU16Output[VICT_nu16HeadZoneTempL].enOutputValidSta)
#define VICT_u16ReadHeadZoneTempL()             (VICT_astU16Output[VICT_nu16HeadZoneTempL].u16Output)
#define VICT_enReadHeadZoneTempStaR()           (VICT_astU16Output[VICT_nu16HeadZoneTempR].enOutputValidSta)
#define VICT_u16ReadHeadZoneTempR()             (VICT_astU16Output[VICT_nu16HeadZoneTempR].u16Output)
#define VICT_enReadHeadZoneTempStaRe()          (VICT_astU16Output[VICT_nu16HeadZoneTempRe].enOutputValidSta)
#define VICT_u16ReadHeadZoneTempRe()            (VICT_astU16Output[VICT_nu16HeadZoneTempRe].u16Output)
#define VICT_enReadBodyShellTempSta()           (VICT_astU16Output[VICT_nu16BodyShellTemp].enOutputValidSta)
#define VICT_u16ReadBodyShellTemp()             (VICT_astU16Output[VICT_nu16BodyShellTemp].u16Output)
#define VICT_enReadCabinTempSta()               (VICT_astU16Output[VICT_nu16CabinTemp].enOutputValidSta)
#define VICT_u16ReadCabinTemp()                 (VICT_astU16Output[VICT_nu16CabinTemp].u16Output)
#define VICT_enReadIncomingHeatSta()            (VICT_astU16Output[VICT_nu16IncomingHeat].enOutputValidSta)
#define VICT_u16ReadIncomingHeat()              (VICT_astU16Output[VICT_nu16IncomingHeat].u16Output)


#endif                              

/***************************************************************************************************
  EOF: VICT_Private.h
***************************************************************************************************/
