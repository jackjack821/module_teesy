/***************************************************************************************************
                                           IPL INTERFACE                                           

  .File Name  : IPL_Interface.c
  
  .Description: This file is the interface of IPL.

  --------------------------------------------------------------------------------------------------
    Version     Date        Author          Change
  --------------------------------------------------------------------------------------------------
    V001        2016-04-15  Chen Xiongzhi   - Creat this module.
***************************************************************************************************/

#define IPL_Interface


/***************************************************************************************************
                                            HEADER FILES                                            
***************************************************************************************************/

/* System header files */
#include "CTS_StdDef.h"

/* Foreign header file */
#include "CTS_Import.h"
#include "TBTS.h"
#include "VICT.h"

/* Own header files */
#include "IPL_Interface.h"


/***************************************************************************************************
  Function   : IPL_enSensorIctAdImport                                                     
                           
  Description: This function is used to get the sensor ICT AD value.
                                
  Arguments  : pu16Output       - is the address of sensor ICT AD value output variable.
  
  Returns    : CTS_nValid       - The sensor ICT AD value is valid.
               CTS_nInvalid     - The sensor ICT AD value is not valid.
***************************************************************************************************/

CTS_tenValidSta IPL_enSensorIctAdImport(cuint16 *pu16Output)
{
    return CTS_enSensorIctAdImport(pu16Output);
}


/***************************************************************************************************
  Function   : IPL_enNatsValueImport                                                     
                           
  Description: This function is used to get the sensor ICT AD value.
                                
  Arguments  : pu16Output       - is the address of sensor ICT AD value output variable.
  
  Returns    : CTS_nValid       - The sensor ICT AD value is valid.
               CTS_nInvalid     - The sensor ICT AD value is not valid.
***************************************************************************************************/

CTS_tenValidSta IPL_enNatsValueImport(cuint16 *pu16Output)
{
    return CTS_enNatsValueImport(pu16Output);
}

/***************************************************************************************************
  Function   : IPL_enPcbTempAdImport                                                    
                           
  Description: This function is used to get the PCB temperature AD value.
                                
  Arguments  : pu16Output       - is the address of PCB temperature AD value output variable.
  
  Returns    : CTS_nValid       - The PCB temperature AD value is ready.
               CTS_nInvalid     - The PCB temperature AD value is not ready.
***************************************************************************************************/ 

CTS_tenValidSta IPL_enPcbTempAdImport(cuint16 *pu16Output)
{
    return CTS_enPcbTempAdImport(pu16Output);
}


/***************************************************************************************************
  Function   : IPL_enOatImport                                                     
                           
  Description: This function is used to get OAT.
                                
  Arguments  : pu16Output       - is the address of OAT output variable.
  
  Returns    : CTS_nValid       - The OAT is ready.
               CTS_nInvalid     - The OAT is not ready.
***************************************************************************************************/

CTS_tenValidSta IPL_enOatImport(cuint16 *pu16Output)
{
    return CTS_enOatImport(pu16Output);
}


/***************************************************************************************************
  Function   : IPL_enRawEvapTempImport                                                   
                           
  Description: This function is used to get the raw evaporator temperature.
                                
  Arguments  : pu16Output       - is the address of raw evaporator temperature output variable.
  
  Returns    : CTS_nValid       - The raw evaporator temperature is ready.
               CTS_nInvalid     - The raw evaporator temperature is not ready.
***************************************************************************************************/

CTS_tenValidSta IPL_enRawEvapTempImport(cuint16 *pu16Output)
{
    return CTS_enRawEvapTempImport(pu16Output);
}       


/***************************************************************************************************
  Function   : IPL_enRawHctImport                                                     
                           
  Description: This function is used to get the raw heater core entrance coolant temperature.
                                
  Arguments  : pu16Output       - is the address of raw heater core entrance coolant temperature 
                                  output variable.
  
  Returns    : CTS_nValid       - The raw heater core entrance coolant temperature is ready.
               CTS_nInvalid     - The raw heater core entrance coolant temperature is not ready.
***************************************************************************************************/

CTS_tenValidSta IPL_enRawHctImport(cuint16 *pu16Output)
{
    return CTS_enRawHctImport(pu16Output);
}     


/***************************************************************************************************
  Function   : IPL_enRawSunLImport                                                      
                           
  Description: This function is used to get the left side raw sun intensity value.
                                
  Arguments  : pu16Output       - is the address of left side raw sun intensity value output 
                                  variable.
  
  Returns    : CTS_nValid       - The left side raw sun intensity value is ready.
               CTS_nInvalid     - The left side raw sun intensity value is not ready.
***************************************************************************************************/

CTS_tenValidSta IPL_enRawSunLImport(cuint16 *pu16Output)
{
    return CTS_enRawSunLImport(pu16Output);
}  


/***************************************************************************************************
  Function   : IPL_enRawSunRImport                                                     
                           
  Description: This function is used to get the right side raw sun intensity value.
                                
  Arguments  : pu16Output       - is the address of right side raw sun intensity value output 
                                  variable.
  
  Returns    : CTS_nValid       - The right side raw sun intensity value is ready.
               CTS_nInvalid     - The right side raw sun intensity value is not ready.
***************************************************************************************************/

CTS_tenValidSta IPL_enRawSunRImport(cuint16 *pu16Output)
{
    return CTS_enRawSunRImport(pu16Output);
}  


/***************************************************************************************************
  Function   : IPL_enCompOnOffStaImport                                                      
                           
  Description: This function is used to get the compressor on/off status.
                                
  Arguments  : pboOutput        - is the address of compressor on/off status output variable.
  
  Returns    : CTS_nValid       - The compressor on/off status is ready.
               CTS_nInvalid     - The compressor on/off status is not ready.
***************************************************************************************************/

CTS_tenValidSta IPL_enCompOnOffStaImport(CTS_tenOnOffSta *penOutput)
{
    return CTS_enCompOnOffStaImport(penOutput);
}


/***************************************************************************************************
  Function   : IPL_enHeaterPumpOnOffStaImport                                                      
                           
  Description: This function is used to get the heater pump on/off status.
                                
  Arguments  : pboOutput        - is the address of heater pump on/off status output variable.
  
  Returns    : CTS_nValid       - The heater pump on/off status is ready.
               CTS_nInvalid     - The heater pump on/off status is not ready.
***************************************************************************************************/

CTS_tenValidSta IPL_enHeaterPumpOnOffStaImport(CTS_tenOnOffSta *penOutput)
{
    return CTS_enHeaterPumpOnOffStaImport(penOutput);
}


/***************************************************************************************************
  Function   : IPL_enFuelModeStaImport                                                      
                           
  Description: This function is used to get the fuel driving mode.
                                
  Arguments  : pboOutput        - is the address of fuel driving mode status output variable.
  
  Returns    : CTS_nValid       - The fuel driving mode status is ready.
               CTS_nInvalid     - The fuel driving mode status is not ready.
***************************************************************************************************/

CTS_tenValidSta IPL_enFuelModeStaImport(cbool *pboOutput)
{
    return CTS_enFuelModeStaImport(pboOutput);
}


/***************************************************************************************************
  Function   : IPL_enElecModeStaImport                                                      
                           
  Description: This function is used to get the electric driving mode.
                                
  Arguments  : pboOutput        - is the address of electric driving mode status output variable.
  
  Returns    : CTS_nValid       - The electric driving mode status is ready.
               CTS_nInvalid     - The electric driving mode status is not ready.
***************************************************************************************************/

CTS_tenValidSta IPL_enElecModeStaImport(cbool *pboOutput)
{
    return CTS_enElecModeStaImport(pboOutput);
}


/***************************************************************************************************
  Function   : IPL_enMacHiLoStaLImport                                                      
                           
  Description: This function is used to get the left side MAC Hi/Lo status.
                                
  Arguments  : penOutput        - is the address of left side MAC Hi/Lo status output variable.
  
  Returns    : CTS_nValid       - The left side MAC position is ready.
               CTS_nInvalid     - The left side MAC position is not ready.
***************************************************************************************************/ 

CTS_tenValidSta IPL_enMacHiLoStaLImport(CTS_tenMacHiLoSta *penOutput)
{
    return CTS_enMacHiLoStaLImport(penOutput);
}   


/***************************************************************************************************
  Function   : IPL_enMacHiLoStaRImport                                                      
                           
  Description: This function is used to get the right side MAC Hi/Lo status.
                                
  Arguments  : penOutput        - is the address of right side MAC Hi/Lo status output variable.
  
  Returns    : CTS_nValid       - The right side MAC position is ready.
               CTS_nInvalid     - The right side MAC position is not ready.
***************************************************************************************************/ 

CTS_tenValidSta IPL_enMacHiLoStaRImport(CTS_tenMacHiLoSta *penOutput)
{
    return CTS_enMacHiLoStaRImport(penOutput);
}  


/***************************************************************************************************
  Function   : IPL_enMacHiLoStaReImport                                                      
                           
  Description: This function is used to get the rear side MAC Hi/Lo status.
                                
  Arguments  : penOutput        - is the address of rear side MAC Hi/Lo status output variable.
  
  Returns    : CTS_nValid       - The rear side MAC position is ready.
               CTS_nInvalid     - The rear side MAC position is not ready.
***************************************************************************************************/ 

CTS_tenValidSta IPL_enMacHiLoStaReImport(CTS_tenMacHiLoSta *penOutput)
{
    return CTS_enMacHiLoStaReImport(penOutput);
}


/***************************************************************************************************
  Function   : IPL_enAirdPosImport                                                     
                           
  Description: This function is used to get the AIRD position.
                                
  Arguments  : pu16Output       - is the address of AIRD position output variable.
  
  Returns    : CTS_nValid       - The AIRD position is ready.
               CTS_nInvalid     - The AIRD position is not ready.
***************************************************************************************************/

CTS_tenValidSta IPL_enAirdPosImport(cuint16 *pu16Output)
{
    return CTS_enAirdPosImport(pu16Output);
}      


/***************************************************************************************************
  Function   : IPL_enRfaPosImport                                                     
                           
  Description: This function is used to get the RFA position.
                                
  Arguments  : pu16Output       - is the address of RFA position output variable.
  
  Returns    : CTS_nValid       - The RFA position is ready.
               CTS_nInvalid     - The RFA position is not ready.
***************************************************************************************************/

CTS_tenValidSta IPL_enRfaPosImport(cuint16 *pu16Output)
{
    return CTS_enRfaPosImport(pu16Output);
}    


/***************************************************************************************************
  Function   : IPL_enBlwrVoltImport                                                    
                           
  Description: This function is used to get the blower voltage.
                                
  Arguments  : pu16Output       - is the address of blower voltage output variable.
  
  Returns    : CTS_nValid       - The blower voltage is ready.
               CTS_nInvalid     - The blower voltage is not ready.
***************************************************************************************************/

CTS_tenValidSta IPL_enBlwrVoltImport(cuint16 *pu16Output)
{
    return CTS_enBlwrVoltImport(pu16Output);
}    


/***************************************************************************************************
  Function   : IPL_enVelocityImport                                                     
                           
  Description: This function is used to get the velocity.
                                
  Arguments  : pu16Output       - is the address of velocity output variable.
  
  Returns    : CTS_nValid       - The velocity is ready.
               CTS_nInvalid     - The velocity is not ready.
***************************************************************************************************/

CTS_tenValidSta IPL_enVelocityImport(cuint16 *pu16Output)
{
    return CTS_enVelocityImport(pu16Output);
}   









/***************************************************************************************************
  Function   : IPL_enTgtBlowTempL                                                      
                           
  Description: This function is used to get the left side target blowout temperature.
                                
  Arguments  : pu16Output       - is the address of left side target blowout temperature output 
                                  variable.
  
  Returns    : CTS_nValid       - The left side target blowout temperature is ready.
               CTS_nInvalid     - The left side target blowout temperature is not ready.
***************************************************************************************************/

CTS_tenValidSta IPL_enTgtBlowTempLImport(cuint16 *pu16Output)
{
    return TBTS_enGetU16Export(TBTS_nu16TgtBlowTempL, pu16Output);
}    


/***************************************************************************************************
  Function   : IPL_enTgtBlowTempR                                                     
                           
  Description: This function is used to get the right side target blowout temperature.
                                
  Arguments  : pu16Output       - is the address of right side target blowout temperature output 
                                  variable.
  
  Returns    : CTS_nValid       - The right side target blowout temperature is ready.
               CTS_nInvalid     - The right side target blowout temperature is not ready.
***************************************************************************************************/

CTS_tenValidSta IPL_enTgtBlowTempRImport(cuint16 *pu16Output)
{
    return TBTS_enGetU16Export(TBTS_nu16TgtBlowTempR, pu16Output);
}  


/***************************************************************************************************
  Function   : IPL_enTgtBlowTempRe                                                     
                           
  Description: This function is used to get the rear side target blowout temperature.
                                
  Arguments  : pu16Output       - is the address of rear side target blowout temperature output 
                                  variable.
  
  Returns    : CTS_nValid       - The rear side target blowout temperature is ready.
               CTS_nInvalid     - The rear side target blowout temperature is not ready.
***************************************************************************************************/

CTS_tenValidSta IPL_enTgtBlowTempReImport(cuint16 *pu16Output)
{
    return TBTS_enGetU16Export(TBTS_nu16TgtBlowTempRe, pu16Output);
} 


/***************************************************************************************************
  Function   : IPL_enCabinTemp                                                    
                           
  Description: This function is used to get the cabin temperature.
                                
  Arguments  : pu16Output       - is the address of cabin temperature output variable.
  
  Returns    : CTS_nValid       - The cabin temperature is ready.
               CTS_nInvalid     - The cabin temperature is not ready.
***************************************************************************************************/

CTS_tenValidSta IPL_enCabinTempImport(cuint16 *pu16Output)
{
    return VICT_enGetU16Export(VICT_nu16CabinTemp, pu16Output);
}  


/***************************************************************************************************
  Function   : IPL_boUseExBlowTempL                                                      
                           
  Description: This function is used to configure whether use the left side external blowout 
               temperature.
                                
  Arguments  : None
  
  Returns    : CTS_True         - Use the left side external blowout temperature.
               CTS_False        - Do not use the left side external blowout temperature.
***************************************************************************************************/

cbool IPL_boUseExBlowTempL(void)
{
    return CTS_boUseExBlowTempL();
} 


/***************************************************************************************************
  Function   : IPL_enExBlowTempLImport                                                      
                           
  Description: This function is used to get the left side external blowout temperature.
                                
  Arguments  : pu16Output       - is the address of left side external blowout temperature output 
                                  variable.
  
  Returns    : CTS_nValid       - The left side external blowout temperature is ready.
               CTS_nInvalid     - The left side external blowout temperature is not ready.
***************************************************************************************************/

CTS_tenValidSta IPL_enExBlowTempLImport(cuint16 *pu16Output)
{
    return CTS_enExBlowTempLImport(pu16Output);
}    


/***************************************************************************************************
  Function   : IPL_boUseExBlowTempR                                                      
                           
  Description: This function is used to configure whether use the right side external blowout 
               temperature.
                                
  Arguments  : None
  
  Returns    : CTS_True         - Use the right side external blowout temperature.
               CTS_False        - Do not use the right side external blowout temperature.
***************************************************************************************************/

cbool IPL_boUseExBlowTempR(void)
{
    return CTS_boUseExBlowTempR();
} 


/***************************************************************************************************
  Function   : IPL_enExBlowTempRImport                                                      
                           
  Description: This function is used to get the right side external blowout temperature.
                                
  Arguments  : pu16Output       - is the address of right side external blowout temperature output 
                                  variable.
  
  Returns    : CTS_nValid       - The right side external blowout temperature is ready.
               CTS_nInvalid     - The right side external blowout temperature is not ready.
***************************************************************************************************/

CTS_tenValidSta IPL_enExBlowTempRImport(cuint16 *pu16Output)
{
    return CTS_enExBlowTempRImport(pu16Output);
} 


/***************************************************************************************************
  Function   : IPL_boUseExBlowTempRe                                                      
                           
  Description: This function is used to configure whether use the rear side external blowout 
               temperature.
                                
  Arguments  : None
  
  Returns    : CTS_True         - Use the rear side external blowout temperature.
               CTS_False        - Do not use the rear side external blowout temperature.
***************************************************************************************************/

cbool IPL_boUseExBlowTempRe(void)
{
    return CTS_boUseExBlowTempRe();
} 


/***************************************************************************************************
  Function   : IPL_enExTgtBlowTempReImport                                                      
                           
  Description: This function is used to get the rear side external blowout temperature.
                                
  Arguments  : pu16Output       - is the address of rear side external blowout temperature output 
                                  variable.
  
  Returns    : CTS_nValid       - The rear side external blowout temperature is ready.
               CTS_nInvalid     - The rear side external blowout temperature is not ready.
***************************************************************************************************/

CTS_tenValidSta IPL_enExBlowTempReImport(cuint16 *pu16Output)
{
    return CTS_enExBlowTempReImport(pu16Output);
}


/***************************************************************************************************
  EOF: IPL_Interface.c
***************************************************************************************************/
