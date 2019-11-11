/***************************************************************************************************
                           CLIMATE THERMODYNAMICS SYSTEM EXPORT INTERFACE                           
                           
  .File Name  : CTS_Export.c
  
  .Description: This file is used to provide the export interface of climate thermodynamics system.
  
  --------------------------------------------------------------------------------------------------
    Version     Date        Author          Change
  --------------------------------------------------------------------------------------------------
    V001        2016-01-13  Chen Xiongzhi   - Creat this module.
    V002        2016-01-19  Chen Xiongzhi   - Add error processing status.
    V003        2016-01-20  Chen Xiongzhi   - Rename to CTS_Export.
***************************************************************************************************/

#define CTS_Export


/***************************************************************************************************
                                            HEADER FILES                                            
***************************************************************************************************/

/* System header files */
#include "CTS_StdDef.h"

/* Foreign header files */
#include "IPL.h"
#include "VICT.h"
#include "TBTS.h"
#include "IPL_Interface.h"
/* Own headerfiles */
#include "CTS_Export.h"


/***************************************************************************************************
  Function   : CTS_vReset                                                      
                           
  Description: Reset function of CTS. This function is called in the RESET container of the 
               operating system.    
                                
  Arguments  : None
  
  Returns    : None 
***************************************************************************************************/

void CTS_vReset(void)
{
    IPL_vReset();
    VICT_vReset();
    TBTS_vReset();
}


/***************************************************************************************************
  Function   : CTS_vInit                                                      
                           
  Description: Initialize function of CTS. This function is called in the INIT container of the 
               operating system.
                                
  Arguments  : None
  
  Returns    : None 
***************************************************************************************************/ 

void CTS_vInit(void)
{
    IPL_vInit();
    VICT_vInit();
    TBTS_vInit();
}


/***************************************************************************************************
  Function   : CTS_vDeinit                                                     
                           
  Description: De-Init function of CTS. This function is called in the DEINIT container of the 
               operating system.
                                
  Arguments  : None
  
  Returns    : None 
***************************************************************************************************/

void CTS_vDeinit(void)
{
    IPL_vDeinit();
    VICT_vDeinit();
    TBTS_vDeinit();
}


/***************************************************************************************************
  Function   : CTS_v100msTask0                                                      
                           
  Description: Main task 0 of CTS. This function is called in the cyclic background task in the ON 
               status. 
            
  Arguments  : None
  
  Returns    : None 
***************************************************************************************************/

void CTS_v100msTask0(void)
{
    IPL_vMain();
}


/***************************************************************************************************
  Function   : CTS_v100msTask1                                                      
                           
  Description: Main task 1 of CTS. This function is called in the cyclic background task in the ON 
               status. 
            
  Arguments  : None
  
  Returns    : None 
***************************************************************************************************/

void CTS_v100msTask1(void)
{
    VICT_vMain();
}


/***************************************************************************************************
  Function   : CTS_v100msTask2                                                     
                           
  Description: Main task 2 of CTS. This function is called in the cyclic background task in the ON 
               status. 
            
  Arguments  : None
  
  Returns    : None 
***************************************************************************************************/

void CTS_v100msTask2(void)
{
    TBTS_vMain();
}


/***************************************************************************************************
  Function   : CTS_vActive                                                       
                           
  Description: Active function of CTS. This function is called in the cyclic background task in the 
               ACTIVE status. 
            
  Arguments  : None
  
  Returns    : None 
***************************************************************************************************/

void CTS_vActive(void)
{
    VICT_vActive();
}


/*************************************************************************************************** 
  Function   : CTS_boGetActiveFlag                         
                       
  Description: This function is used to get the active flag.
                                                                           
  Arguments  : None    
  
  Returns    : CTS_nTrue        - In active status.
               CTS_nFalse       - It is not necessary to be in active status.
***************************************************************************************************/

cbool CTS_boGetActiveFlag(void)
{
    cbool boReturn = VICT_boGetActiveFlag();
    
    return boReturn;
}


/*************************************************************************************************** 
  Function   : CTS_boGetSensorIctExport                         
                       
  Description: This function is used to get the sensor ICT.
                                                                           
  Arguments  : pu16Output       - is the address of sensor ICT output variable.     
  
  Returns    : CTS_nValid       - The sensor ICT is ready.
               CTS_nInvalid     - The sensor ICT is not ready.
***************************************************************************************************/

CTS_tenValidSta CTS_enGetSensorIctExport(cuint16 *pu16Output)
{
    return IPL_enGetU16Export(IPL_nu16SensorIct, pu16Output);
}


/*************************************************************************************************** 
  Function   : CTS_boGetPcbTempExport                         
                       
  Description: This function is used to get the PCB temperature.
                                                                           
  Arguments  : pu16Output       - is the address of PCB temperature output variable.     
  
  Returns    : CTS_nValid       - The PCB temperature is ready.
               CTS_nInvalid     - The PCB temperature is not ready.
***************************************************************************************************/

CTS_tenValidSta CTS_enGetPcbTempExport(cuint16 *pu16Output)
{
    return IPL_enGetU16Export(IPL_nu16PcbTemp, pu16Output);
}


/*************************************************************************************************** 
  Function   : CTS_boGetAirdModeExport                         
                       
  Description: This function is used to get AIRD mode.
                                                                           
  Arguments  : pu8Output        - is the address of AIRD mode output variable.     
  
  Returns    : CTS_nValid       - The AIRD mode is ready.
               CTS_nInvalid     - The AIRD mode is not ready.
***************************************************************************************************/

CTS_tenValidSta CTS_enGetAirdModeExport(cuint8 *pu8Output)
{
    return IPL_enGetU8Export(IPL_nu8AirdMode, pu8Output);
}


/*************************************************************************************************** 
  Function   : CTS_boGetEvapTempExport                  
                       
  Description: This function is used to get the EVAP temperature.
                                                                           
  Arguments  : pu16Output       - is the address of EVAP temperature output variable.     
  
  Returns    : CTS_nValid       - The EVAP temperature is ready.
               CTS_nInvalid     - The EVAP temperature is not ready.
***************************************************************************************************/

CTS_tenValidSta CTS_enGetEvapTempExport(cuint16 *pu16Output)
{
    return IPL_enGetU16Export(IPL_nu16EvapTemp, pu16Output);
}


/*************************************************************************************************** 
  Function   : CTS_boGetHctExport                  
                       
  Description: This function is used to get the heater core temperature.
                                                                           
  Arguments  : pu16Output       - is the address of heater core temperature output variable.     
  
  Returns    : CTS_nValid       - The heater core temperature is ready.
               CTS_nInvalid     - The heater core temperature is not ready.
***************************************************************************************************/

CTS_tenValidSta CTS_enGetHctExport(cuint16 *pu16Output)
{
    return IPL_enGetU16Export(IPL_nu16Hct, pu16Output);
}


/*************************************************************************************************** 
  Function   : CTS_enGetTgtBlowTempLExport                         
                       
  Description: This function is used to get the left side target blowout temperature.
                                                                           
  Arguments  : pu16Output       - is the address of left side target blowout temperature output 
                                  variable.     
  
  Returns    : CTS_nValid       - The left side target blowout temperature is ready.
               CTS_nInvalid     - The left side target blowout temperature is not ready.
***************************************************************************************************/

CTS_tenValidSta CTS_enGetTgtBlowTempLExport(cuint16 *pu16Output)
{
    return TBTS_enGetU16Export(TBTS_nu16TgtBlowTempL, pu16Output);
}


/*************************************************************************************************** 
  Function   : CTS_enGetTgtBlowTempRExport                        
                       
  Description: This function is used to get the right side target blowout temperature.
                                                                           
  Arguments  : pu16Output       - is the address of right side target blowout temperature output
                                  variable.     
  
  Returns    : CTS_nValid       - The right side target blowout temperature is ready.
               CTS_nInvalid     - The right side target blowout temperature is not ready.
***************************************************************************************************/

CTS_tenValidSta CTS_enGetTgtBlowTempRExport(cuint16 *pu16Output)
{
    return TBTS_enGetU16Export(TBTS_nu16TgtBlowTempR, pu16Output);
}


/*************************************************************************************************** 
  Function   : CTS_enGetTgtBlowTempReExport                        
                       
  Description: This function is used to get the rear side target blowout temperature.
                                                                           
  Arguments  : pu16Output       - is the address of rear side target blowout temperature output
                                  variable.     
  
  Returns    : CTS_nValid       - The rear side target blowout temperature is ready.
               CTS_nInvalid     - The rear side target blowout temperature is not ready.
***************************************************************************************************/

CTS_tenValidSta CTS_enGetTgtBlowTempReExport(cuint16 *pu16Output)
{
    return TBTS_enGetU16Export(TBTS_nu16TgtBlowTempRe, pu16Output);
}


/*************************************************************************************************** 
  Function   : CTS_boGetBlowTempLExport                        
                       
  Description: This function is used to get the left side blowout temperature.
                                                                           
  Arguments  : pu16Output       - is the address of left side blowout temperature output variable.     
  
  Returns    : CTS_nValid       - The left side blowout temperature is ready.
               CTS_nInvalid     - The left side blowout temperature is not ready.
***************************************************************************************************/

CTS_tenValidSta CTS_enGetBlowTempLExport(cuint16 *pu16Output)
{
    return IPL_enGetU16Export(IPL_nu16BlowTempL, pu16Output);
}


/*************************************************************************************************** 
  Function   : CTS_boGetBlowTempRExport                         
                       
  Description: This function is used to get the right side blowout temperature.
                                                                           
  Arguments  : pu16Output       - is the address of right side blowout temperature output variable.     
  
  Returns    : CTS_nValid       - The right side blowout temperature is ready.
               CTS_nInvalid     - The right side blowout temperature is not ready.
***************************************************************************************************/

CTS_tenValidSta CTS_enGetBlowTempRExport(cuint16 *pu16Output)
{
    return IPL_enGetU16Export(IPL_nu16BlowTempR, pu16Output);
}


/*************************************************************************************************** 
  Function   : CTS_boGetBlowTempReExport                         
                       
  Description: This function is used to get the rear side blowout temperature.
                                                                           
  Arguments  : pu16Output       - is the address of rear side blowout temperature output variable.     
  
  Returns    : CTS_nValid       - The rear side blowout temperature is ready.
               CTS_nInvalid     - The rear side blowout temperature is not ready.
***************************************************************************************************/

CTS_tenValidSta CTS_enGetBlowTempReExport(cuint16 *pu16Output)
{
    return IPL_enGetU16Export(IPL_nu16BlowTempRe, pu16Output);
}


/*************************************************************************************************** 
  Function   : CTS_boGetBlowSpdExport                         
                       
  Description: This function is used to get the blowout speed.
                                                                           
  Arguments  : pu16Output       - is the address of blowout speed output variable.     
  
  Returns    : CTS_nValid       - The blowout speed is ready.
               CTS_nInvalid     - The blowout speed is not ready.
***************************************************************************************************/

CTS_tenValidSta CTS_enGetBlowSpdExport(cuint16 *pu16Output)
{
    return IPL_enGetU16Export(IPL_nu16BlowSpd, pu16Output);
}


/*************************************************************************************************** 
  Function   : CTS_boGetSunExport                         
                       
  Description: This function is used to get sun.
                                                                           
  Arguments  : pu16Output       - is address of the sun output variable.     
  
  Returns    : CTS_nValid       - The sun is ready.
               CTS_nInvalid     - The sun is not ready.
***************************************************************************************************/

CTS_tenValidSta CTS_enGetSunExport(cuint16 *pu16Output)
{
    return IPL_enGetU16Export(IPL_nu16Sun, pu16Output);
}


/*************************************************************************************************** 
  Function   : CTS_boGetHeadZoneTempLExport                       
                       
  Description: This function is used to get the left side head zone temperature.
                                                                           
  Arguments  : pu16Output       - is the address of left side head zone temperature output variable.     
  
  Returns    : CTS_nValid       - The left side head zone temperature is ready.
               CTS_nInvalid     - The left side head zone temperature is not ready.
***************************************************************************************************/

CTS_tenValidSta CTS_enGetHeadZoneTempLExport(cuint16 *pu16Output)
{   
    return VICT_enGetU16Export(VICT_nu16HeadZoneTempL, pu16Output);
}


/*************************************************************************************************** 
  Function   : CTS_boGetHeadZoneTempRExport                       
                       
  Description: This function is used to get the right side head zone temperature.
                                                                           
  Arguments  : pu16Output       - is the address of right side head zone temperature output 
                                  variable.     
  
  Returns    : CTS_nValid       - The right side head zone temperature is ready.
               CTS_nInvalid     - The right side head zone temperature is not ready.
***************************************************************************************************/

CTS_tenValidSta CTS_enGetHeadZoneTempRExport(cuint16 *pu16Output)
{   
    return VICT_enGetU16Export(VICT_nu16HeadZoneTempR, pu16Output);
}


/*************************************************************************************************** 
  Function   : CTS_boGetHeadZoneTempReExport                       
                       
  Description: This function is used to get the rear side head zone temperature.
                                                                           
  Arguments  : pu16Output       - is the address of rear side head zone temperature output 
                                  variable.     
  
  Returns    : CTS_nValid       - The rear side head zone temperature is ready.
               CTS_nInvalid     - The rear side head zone temperature is not ready.
***************************************************************************************************/

CTS_tenValidSta CTS_enGetHeadZoneTempReExport(cuint16 *pu16Output)
{   
    return VICT_enGetU16Export(VICT_nu16HeadZoneTempRe, pu16Output);
}


/*************************************************************************************************** 
  Function   : CTS_boGetBodyShellTempExport                         
                       
  Description: This function is used to get the car body temperature.
                                                                           
  Arguments  : pu16Output       - is the address of car body temperature output variable.     
  
  Returns    : CTS_nValid       - The car body temperature is ready.
               CTS_nInvalid     - The car body temperature is not ready.
***************************************************************************************************/

CTS_tenValidSta CTS_enGetBodyShellTempExport(cuint16 *pu16Output)
{   
    return VICT_enGetU16Export(VICT_nu16BodyShellTemp, pu16Output);
}


/*************************************************************************************************** 
  Function   : CTS_boGetCabinTempExport                         
                       
  Description: This function is used to get the cabin temperature.
                                                                           
  Arguments  : pu16Output       - is the address of cabin temperature output variable.     
  
  Returns    : CTS_nValid       - The cabin temperature is ready.
               CTS_nInvalid     - The cabin temperature is not ready.
***************************************************************************************************/

CTS_tenValidSta CTS_enGetCabinTempExport(cuint16 *pu16Output)
{   
    return VICT_enGetU16Export(VICT_nu16CabinTemp, pu16Output);
}

CTS_tenValidSta CTS_enGetSunLoadHeatExport(cuint16 *pu16Output)
{
    return IPL_enGetU16Export(IPL_nu16SunLoadHeat, pu16Output);
}

CTS_tenValidSta CTS_enGetVelLoadHeatExport(cuint16 *pu16Output)
{
    return IPL_enGetU16Export(IPL_nu16VelEngineHeat, pu16Output);
}
/*************************************************************************************************** 
  Function   : CTS_boGetPcbTempadExport                         
                       
  Description: This function is used to get the PCB temperature.
                                                                           
  Arguments  : pu16Output       - is the address of PCB temperature output variable.     
  
  Returns    : CTS_nValid       - The PCB temperature is ready.
               CTS_nInvalid     - The PCB temperature is not ready.
***************************************************************************************************/

CTS_tenValidSta CTS_enGetPcbTempAdExport(cuint16 *pu16Output)
{
    return IPL_enPcbTempAdImport(pu16Output);
}
/***************************************************************************************************
  EOF: CTS_Export.c
***************************************************************************************************/
