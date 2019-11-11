/***************************************************************************************************
                                           TBTS INTERFACE
                                           
  .File Name  : TBTS_Interface.h
  
  .Description: This file is the interface of TBTS.

  --------------------------------------------------------------------------------------------------
    Version     Date        Author          Change
  --------------------------------------------------------------------------------------------------
    V001        2016-04-15  Chen Xiongzhi   - Creat this module.
***************************************************************************************************/

#define TBTS_Interface


/***************************************************************************************************
                                            HEADER FILES                                            
***************************************************************************************************/

/* System header files */
#include "CTS_StdDef.h"

/* Foreign header file */
#include "CTS_Import.h"
#include "IPL.h"
#include "VICT.h"

/* Own header files */
#include "TBTS_Interface.h"


/***************************************************************************************************
  Function   : TBTS_enSetTempLImport                                                      
                           
  Description: This function is used to get the left side set temperature.
                                
  Arguments  : pu16Output       - is the address of left side set temperature output variable.
  
  Returns    : CTS_nValid       - The left side set temperature is ready.
               CTS_nInvalid     - The left side set temperature is not ready.
***************************************************************************************************/

CTS_tenValidSta TBTS_enSetTempLImport(cuint16 *pu16Output)
{
    return CTS_enSetTempLImport(pu16Output);
}     


/***************************************************************************************************
  Function   : TBTS_enSetTempRImport                                                      
                           
  Description: This function is used to get the right side set temperature.
                                
  Arguments  : pu16Output       - is the address of right side set temperature output variable.
  
  Returns    : CTS_nValid       - The right side set temperature is ready.
               CTS_nInvalid     - The right side set temperature is not ready.
***************************************************************************************************/

CTS_tenValidSta TBTS_enSetTempRImport(cuint16 *pu16Output)
{
    return CTS_enSetTempRImport(pu16Output);
}


/***************************************************************************************************
  Function   : TBTS_enSetTempReImport                                                      
                           
  Description: This function is used to get the rear side set temperature.
                                
  Arguments  : pu16Output       - is the address of rear side set temperature output variable.
  
  Returns    : CTS_nValid       - The rear side set temperature is ready.
               CTS_nInvalid     - The rear side set temperature is not ready.
***************************************************************************************************/

CTS_tenValidSta TBTS_enSetTempReImport(cuint16 *pu16Output)
{
    return CTS_enSetTempReImport(pu16Output);
}


/***************************************************************************************************
  Function   : TBTS_enIncomingHeatImport                                                      
                           
  Description: This function is used to get the incoming heat.
                                
  Arguments  : pu16Output       - is the address of incoming heat output variable.
  
  Returns    : CTS_nValid       - The incoming heat is ready.
               CTS_nInvalid     - The incoming heat is not ready.
***************************************************************************************************/

CTS_tenValidSta TBTS_enIncomingHeatImport(cuint16 *pu16Output)
{
    return VICT_enGetU16Export(VICT_nu16IncomingHeat, pu16Output);
}


/***************************************************************************************************
  Function   : TBTS_enBlowSpdImport                                                 
                           
  Description: This function is used to get the blowout speed.
                                
  Arguments  : pu16Output       - is the address of blowout speed output variable.
  
  Returns    : CTS_nValid       - The blowout speed is ready.
               CTS_nInvalid     - The blowout speed is not ready.
***************************************************************************************************/ 

CTS_tenValidSta TBTS_enBlowSpdImport(cuint16 *pu16Output)
{
    return IPL_enGetU16Export(IPL_nu16BlowSpd, pu16Output);
}


/***************************************************************************************************
  Function   : TBTS_enHeadZoneTempLImport                                                      
                           
  Description: This function is used to get the left side head zone temperature.
                                
  Arguments  : pu16Output       - is the address of left side head zone temperature output variable.
  
  Returns    : CTS_nValid       - The left side head zone temperature is ready.
               CTS_nInvalid     - The left side head zone temperature is not ready.
***************************************************************************************************/

CTS_tenValidSta TBTS_enHeadZoneTempLImport(cuint16 *pu16Output)
{
    return VICT_enGetU16Export(VICT_nu16HeadZoneTempL, pu16Output);
}


/***************************************************************************************************
  Function   : TBTS_enHeadZoneTempRImport                                                      
                           
  Description: This function is used to get the right side head zone temperature.
                                
  Arguments  : pu16Output       - is the address of right side head zone temperature output 
                                  variable.
  
  Returns    : CTS_nValid       - The right side head zone temperature is ready.
               CTS_nInvalid     - The right side head zone temperature is not ready.
***************************************************************************************************/

CTS_tenValidSta TBTS_enHeadZoneTempRImport(cuint16 *pu16Output)
{
    return VICT_enGetU16Export(VICT_nu16HeadZoneTempR, pu16Output);
}


/***************************************************************************************************
  Function   : TBTS_enHeadZoneTempReImport                                                      
                           
  Description: This function is used to get the rear side head zone temperature.
                                
  Arguments  : pu16Output       - is the address of rear side head zone temperature output 
                                  variable.
  
  Returns    : CTS_nValid       - The rear side head zone temperature is ready.
               CTS_nInvalid     - The rear side head zone temperature is not ready.
***************************************************************************************************/

CTS_tenValidSta TBTS_enHeadZoneTempReImport(cuint16 *pu16Output)
{
    return VICT_enGetU16Export(VICT_nu16HeadZoneTempRe, pu16Output);
}


/***************************************************************************************************
  Function   : TBTS_enAirdModeImport                                                    
                           
  Description: This function is used to get the AIRD mode.
                                
  Arguments  : pu16Output       - is the address of AIRD mode output variable.
  
  Returns    : CTS_nValid       - The AIRD mode is ready.
               CTS_nInvalid     - The AIRD mode is not ready.
***************************************************************************************************/

CTS_tenValidSta TBTS_enAirdModeImport(cuint8 *pu8Output)
{
    return IPL_enGetU8Export(IPL_nu8AirdMode, pu8Output);
}


/***************************************************************************************************
  Function   : TBTS_boUseExTgtBlowTempL                                                      
                           
  Description: This function is used to configure whether use the left side external target blowout 
               temperature.
                                
  Arguments  : None
  
  Returns    : CTS_True         - Use the left side external target blowout temperature.
               CTS_False        - Do not use the left side external target blowout temperature.
***************************************************************************************************/

cbool TBTS_boUseExTgtBlowTempL(void)
{
    return CTS_boUseExTgtBlowTempL();
} 


/***************************************************************************************************
  Function   : TBTS_enExTgtBlowTempLImport                                                      
                           
  Description: This function is used to get the left side external target blowout temperature.
                                
  Arguments  : pu16Output       - is the address of left side external target blowout temperature 
                                  output variable.
  
  Returns    : CTS_nValid       - The left side external target blowout temperature is ready.
               CTS_nInvalid     - The left side external target blowout temperature is not ready.
***************************************************************************************************/

CTS_tenValidSta TBTS_enExTgtBlowTempLImport(cuint16 *pu16Output)
{
    return CTS_enExTgtBlowTempLImport(pu16Output);
}    


/***************************************************************************************************
  Function   : TBTS_boUseExTgtBlowTempR                                                      
                           
  Description: This function is used to configure whether use the right side external target blowout 
               temperature.
                                
  Arguments  : None
  
  Returns    : CTS_True         - Use the right side external target blowout temperature.
               CTS_False        - Do not use the right side external target blowout temperature.
***************************************************************************************************/

cbool TBTS_boUseExTgtBlowTempR(void)
{
    return CTS_boUseExTgtBlowTempR();
}


/***************************************************************************************************
  Function   : TBTS_enExTgtBlowTempRImport                                                      
                           
  Description: This function is used to get the right side external target blowout temperature.
                                
  Arguments  : pu16Output       - is the address of right side external target blowout temperature 
                                  output variable.
  
  Returns    : CTS_nValid       - The right side external target blowout temperature is ready.
               CTS_nInvalid     - The right side external target blowout temperature is not ready.
***************************************************************************************************/

CTS_tenValidSta TBTS_enExTgtBlowTempRImport(cuint16 *pu16Output)
{
    return CTS_enExTgtBlowTempRImport(pu16Output);
}  


/***************************************************************************************************
  Function   : TBTS_boUseExTgtBlowTempRe                                                      
                           
  Description: This function is used to configure whether use the rear side external target blowout 
               temperature.
                                
  Arguments  : None
  
  Returns    : CTS_True         - Use the rear side external target blowout temperature.
               CTS_False        - Do not use the rear side external target blowout temperature.
***************************************************************************************************/

cbool TBTS_boUseExTgtBlowTempRe(void)
{
    return CTS_boUseExTgtBlowTempRe();
}


/***************************************************************************************************
  Function   : TBTS_enExTgtBlowTempReImport                                                      
                           
  Description: This function is used to get the rear side external target blowout temperature.
                                
  Arguments  : pu16Output       - is the address of rear side external target blowout temperature 
                                  output variable.
  
  Returns    : CTS_nValid       - The rear side external target blowout temperature is ready.
               CTS_nInvalid     - The rear side external target blowout temperature is not ready.
***************************************************************************************************/

CTS_tenValidSta TBTS_enExTgtBlowTempReImport(cuint16 *pu16Output)
{
    return CTS_enExTgtBlowTempReImport(pu16Output);
} 


/***************************************************************************************************
  EOF: TBTS_Interface.c
***************************************************************************************************/
