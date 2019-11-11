/***************************************************************************************************
                                           VICT INTERFACE         

  .File Name  : VICT_Interface.c
  
  .Description: This file is the interface of VICT.

  --------------------------------------------------------------------------------------------------
    Version     Date        Author          Change
  --------------------------------------------------------------------------------------------------
    V001        2016-04-15  Chen Xiongzhi   - Creat this module.
***************************************************************************************************/

#define VICT_Interface


/***************************************************************************************************
                                            HEADER FILES                                            
***************************************************************************************************/

/* System header files */
#include "CTS_StdDef.h"

/* Foreign header file */
#include "CTS_Import.h"
#include "IPL.h"

/* Own header files */
#include "VICT_Interface.h"


/***************************************************************************************************
  Function   : VICT_enSensorIctImport                                                    
                           
  Description: This function is used to get the sensor ICT.
                                
  Arguments  : pu16Output       - is the address of sensor ICT output variable.
  
  Returns    : CTS_nValid       - The sensor ICT is ready.
               CTS_nInvalid     - The sensor ICT is not ready.
***************************************************************************************************/

CTS_tenValidSta VICT_enSensorIctImport(cuint16 *pu16Output)
{
    return IPL_enGetU16Export(IPL_nu16SensorIct, pu16Output);
}


/***************************************************************************************************
  Function   : VICT_enPcbTempImport                                                   
                           
  Description: This function is used to get the PCB temperature.
                                
  Arguments  : pu16Output       - is the address of PCB temperature output variable.
  
  Returns    : CTS_nValid       - The PCB temperature is ready.
               CTS_nInvalid     - The PCB temperature is not ready.
***************************************************************************************************/ 

CTS_tenValidSta VICT_enPcbTempImport(cuint16 *pu16Output)
{
    return IPL_enGetU16Export(IPL_nu16PcbTemp, pu16Output);
}


/***************************************************************************************************
  Function   : VICT_enOatImport                                                   
                           
  Description: This function is used to get the OAT.
                                
  Arguments  : pu16Output       - is the address of OAT output variable. 
  
  Returns    : CTS_nValid       - The OAT is ready.
               CTS_nInvalid     - The OAT is not ready.
***************************************************************************************************/

CTS_tenValidSta VICT_enOatImport(cuint16 *pu16Output)
{
    return CTS_enOatImport(pu16Output);
}


/***************************************************************************************************
  Function   : VICT_enSunImport                                                      
                           
  Description: This function is used to get the sun intensity.
                                
  Arguments  : pu16Output       - is the address of sun intensity output variable.
  
  Returns    : CTS_nValid       - The sun intensity is ready.
               CTS_nInvalid     - The sun intensity is not ready.
***************************************************************************************************/

CTS_tenValidSta VICT_enSunImport(cuint16 *pu16Output)
{
    return IPL_enGetU16Export(IPL_nu16Sun, pu16Output);
}


/***************************************************************************************************
  Function   : VICT_enSunLoadHeatImport                                                      
                           
  Description: This function is used to get the sun load heat.
                                
  Arguments  : pu16Output       - is the address of sun load heat output variable.
  
  Returns    : CTS_nValid       - The sun load heat is ready.
               CTS_nInvalid     - The sun load heat is not ready.
***************************************************************************************************/

CTS_tenValidSta VICT_enSunLoadHeatImport(cuint16 *pu16Output)
{
    return IPL_enGetU16Export(IPL_nu16SunLoadHeat, pu16Output);
}


/***************************************************************************************************
  Function   : VICT_enVelEngineHeatImport                                                    
                           
  Description: This function is used to get the velocity engine heat.
                                
  Arguments  : pu16Output       - is the address of velocity engine heat output variable.
  
  Returns    : CTS_nValid       - The velocity engine heat is ready.
               CTS_nInvalid     - The velocity engine heat is not ready.
***************************************************************************************************/

CTS_tenValidSta VICT_enVelEngineHeatImport(cuint16 *pu16Output)
{
    return IPL_enGetU16Export(IPL_nu16VelEngineHeat, pu16Output);
}     


/***************************************************************************************************
  Function   : VICT_enBlowTempLImport                                                      
                           
  Description: This function is used to get the left side blowout temperature.
                                
  Arguments  : pu16Output       - is the address of left side blowout temperature output variable.
  
  Returns    : CTS_nValid       - The left side blowout temperature is ready.
               CTS_nInvalid     - The left side blowout temperature is not ready.
***************************************************************************************************/ 

CTS_tenValidSta VICT_enBlowTempLImport(cuint16 *pu16Output)
{
    return IPL_enGetU16Export(IPL_nu16BlowTempL, pu16Output);
}


/***************************************************************************************************
  Function   : VICT_enBlowTempRImport                                                     
                           
  Description: This function is used to get the right side blowout temperature.
                                
  Arguments  : pu16Output       - is the address of right side blowout temperature output variable.
  
  Returns    : CTS_nValid       - The right side blowout temperature is ready.
               CTS_nInvalid     - The right side blowout temperature is not ready.
***************************************************************************************************/ 

CTS_tenValidSta VICT_enBlowTempRImport(cuint16 *pu16Output)
{
    return IPL_enGetU16Export(IPL_nu16BlowTempR, pu16Output);
}


/***************************************************************************************************
  Function   : VICT_enBlowTempReImport                                                     
                           
  Description: This function is used to get the rear side blowout temperature.
                                
  Arguments  : pu16Output       - is the address of rear side blowout temperature output variable.
  
  Returns    : CTS_nValid       - The rear side blowout temperature is ready.
               CTS_nInvalid     - The rear side blowout temperature is not ready.
***************************************************************************************************/ 

CTS_tenValidSta VICT_enBlowTempReImport(cuint16 *pu16Output)
{
    return IPL_enGetU16Export(IPL_nu16BlowTempRe, pu16Output);
}

 
/***************************************************************************************************
  Function   : VICT_enBlowSpdImport                                                      
                           
  Description: This function is used to get the blowout speed.
                                
  Arguments  : pu16Output       - is the address of blowout speed output variable.
  
  Returns    : CTS_nValid       - The blowout speed is ready.
               CTS_nInvalid     - The blowout speed is not ready.
***************************************************************************************************/ 

CTS_tenValidSta VICT_enBlowSpdImport(cuint16 *pu16Output)
{
    return IPL_enGetU16Export(IPL_nu16BlowSpd, pu16Output);
}

 
/***************************************************************************************************
  Function   : VICT_enAirdModeImport                                                     
                           
  Description: This function is used to get the AIRD mode.
                                
  Arguments  : pu16Output       - is the address of AIRD mode output variable.
  
  Returns    : CTS_nValid       - The AIRD mode is ready.
               CTS_nInvalid     - The AIRD mode is not ready.
***************************************************************************************************/

CTS_tenValidSta VICT_enAirdModeImport(cuint8 *pu8Output)
{
    return IPL_enGetU8Export(IPL_nu8AirdMode, pu8Output);
}


/***************************************************************************************************
  Function   : VICT_enAirdPosImport                                                     
                           
  Description: This function is used to get the AIRD position.
                                
  Arguments  : pu16Output       - is the address of AIRD position output variable.
  
  Returns    : CTS_nValid       - The AIRD position is ready.
               CTS_nInvalid     - The AIRD position is not ready.
***************************************************************************************************/

CTS_tenValidSta VICT_enAirdPosImport(cuint16 *pu16Output)
{
    return CTS_enAirdPosImport(pu16Output);
} 


/***************************************************************************************************
  Function   : VICT_boUseExIgnOffTime                                                      
                           
  Description: This function is used to configure whether use external ignition off time.
                                
  Arguments  : None
  
  Returns    : CTS_True         - Use external ignition off time.
               CTS_False        - Do not use external ignition off time.
***************************************************************************************************/

cbool VICT_boUseExIgnOffTime(void)
{
    return CTS_boUseExIgnOffTime();
}


/***************************************************************************************************
  Function   : VICT_enExIgnOffTimeImport                                                     
                           
  Description: This function is used to get the external ignition off time.
                                
  Arguments  : pu16Output       - is the address of external ignition off time output variable.
  
  Returns    : CTS_nValid       - The external ignition off time is ready.
               CTS_nInvalid     - The external ignition off time is not ready.
***************************************************************************************************/

CTS_tenValidSta VICT_enExIgnOffTimeImport(cuint16 *pu16Output)
{
    return CTS_enExIgnOffTimeImport(pu16Output);
}


/***************************************************************************************************
  Function   : VICT_boDisIncomingHeatFl                                                      
                           
  Description: This function is used to configure whether disable incoming heat filter.
                                
  Arguments  : None
  
  Returns    : CTS_True         - Disable incoming heat filter.
               CTS_False        - Do not disable incoming heat filter.
***************************************************************************************************/

cbool VICT_boDisIncomingHeatFl(void)
{
    return CTS_boDisIncomingHeatFl();
} 


/***************************************************************************************************
  Function   : VICT_boUseExHeadZoneTempL                                                      
                           
  Description: This function is used to configure whether use external left side head zone 
               temperature.
                                
  Arguments  : None
  
  Returns    : CTS_True         - Use external left side head zone temperature.
               CTS_False        - Do not use external left side head zone temperature.
***************************************************************************************************/

cbool VICT_boUseExHeadZoneTempL(void)
{
    return CTS_boUseExHeadZoneTempL();
} 


/***************************************************************************************************
  Function   : VICT_enExHeadZoneTempLImport                                                      
                           
  Description: This function is used to get the left side external head zone temperature.
                                
  Arguments  : pu16Output       - is the address of left side external head zone temperature output 
                                  variable.
  
  Returns    : CTS_nValid       - The left side external head zone temperature is ready.
               CTS_nInvalid     - The left side external head zone temperature is not ready.
***************************************************************************************************/

CTS_tenValidSta VICT_enExHeadZoneTempLImport(cuint16 *pu16Output)
{
    return CTS_enExHeadZoneTempLImport(pu16Output);
}     


/***************************************************************************************************
  Function   : VICT_boUseExHeadZoneTempR                                                      
                           
  Description: This function is used to configure whether use external rignt side head zone 
               temperature.
                                
  Arguments  : None
  
  Returns    : CTS_True         - Use external right side head zone temperature.
               CTS_False        - Do not use external right side head zone temperature.
***************************************************************************************************/

cbool VICT_boUseExHeadZoneTempR(void)
{
    return CTS_boUseExHeadZoneTempR();
}


/***************************************************************************************************
  Function   : VICT_enExHeadZoneTempRImport                                                     
                           
  Description: This function is used to get the right side external head zone temperature.
                                
  Arguments  : pu16Output       - is the address of right side external head zone temperature output 
                                  variable.
  
  Returns    : CTS_nValid       - The right side external head zone temperature is ready.
               CTS_nInvalid     - The right side external head zone temperature is not ready.
***************************************************************************************************/

CTS_tenValidSta VICT_enExHeadZoneTempRImport(cuint16 *pu16Output)
{
    return CTS_enExHeadZoneTempRImport(pu16Output);
}  


/***************************************************************************************************
  Function   : VICT_boUseExHeadZoneTempRe                                                      
                           
  Description: This function is used to configure whether use external rear side head zone 
               temperature.
                                
  Arguments  : None
  
  Returns    : CTS_True         - Use external rear side head zone temperature.
               CTS_False        - Do not use external rear side head zone temperature.
***************************************************************************************************/

cbool VICT_boUseExHeadZoneTempRe(void)
{
    return CTS_boUseExHeadZoneTempRe();
}


/***************************************************************************************************
  Function   : VICT_enExHeadZoneTempReImport                                                     
                           
  Description: This function is used to get the rear side external head zone temperature.
                                
  Arguments  : pu16Output       - is the address of rear side external head zone temperature 
                                  output variable.
  
  Returns    : CTS_nValid       - The rear side external head zone temperature is ready.
               CTS_nInvalid     - The rear side external head zone temperature is not ready.
***************************************************************************************************/

CTS_tenValidSta VICT_enExHeadZoneTempReImport(cuint16 *pu16Output)
{
    return CTS_enExHeadZoneTempReImport(pu16Output);
}


/***************************************************************************************************
  EOF: VICT_Interface.c
***************************************************************************************************/
