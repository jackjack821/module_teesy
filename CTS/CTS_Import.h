/***************************************************************************************************
                           CLIMATE THERMODYNAMICS SYSTEM IMPORT INTERFACE                     

  .File Name  : CTS_Import.h
  
  .Description: This file is used to provide the import interface of climate thermodynamics system.
  
  --------------------------------------------------------------------------------------------------
    Version     Date        Author          Change
  --------------------------------------------------------------------------------------------------
    V001        2015-10-12  Chen Xiongzhi   - Creat this module.
    V002        2016-01-13  Chen Xiongzhi   - Rename for VII to CTS for automatic temperature 
                                              control strategy.
    V003        2016-01-19  Chen Xiongzhi   - Add error processing status.
    V004        2016-01-20  Chen Xiongzhi   - Rename to CTS_Import.
***************************************************************************************************/

#ifndef CTS_Import_H
#define CTS_Import_H
#include "General.h"
 
/***************************************************************************************************
                                IMPORT INTERFACE FUNCTION PROTOTYPES                      

  Note(s): In this section declare all import interface function prototypes of your module.
***************************************************************************************************/

/* Outside Air Temperature */
CTS_tenValidSta CTS_enOatImport(cuint16 *pu16Output);

/* PCB Temperature AD Value */
CTS_tenValidSta CTS_enPcbTempAdImport(cuint16 *pu16Output);                

/* Mixing Air Flap Hi/Lo Status */
CTS_tenValidSta CTS_enMacHiLoStaLImport(CTS_tenMacHiLoSta *penOutput);
CTS_tenValidSta CTS_enMacHiLoStaRImport(CTS_tenMacHiLoSta *penOutput);
CTS_tenValidSta CTS_enMacHiLoStaReImport(CTS_tenMacHiLoSta *penOutput);

/* Air Distribution Flap Status */
CTS_tenValidSta CTS_enAirdPosImport(cuint16 *pu16Output);                   

/* R/F Flap Status */
CTS_tenValidSta CTS_enRfaPosImport(cuint16 *pu16Output);                     

/* Blower Voltage */
CTS_tenValidSta CTS_enBlwrVoltImport(cuint16 *pu16Output);                  

/* Velocity */
CTS_tenValidSta CTS_enVelocityImport(cuint16 *pu16Output);                  

/* Raw Evaporator Temperature */
CTS_tenValidSta CTS_enRawEvapTempImport(cuint16 *pu16Output);                        

/* Raw Heater Core Entrance Coolant Temperature */
CTS_tenValidSta CTS_enRawHctImport(cuint16 *pu16Output);                        

/* CCS Set Temperature */
CTS_tenValidSta CTS_enSetTempLImport(cuint16 *pu16Output);           
CTS_tenValidSta CTS_enSetTempRImport(cuint16 *pu16Output);        
CTS_tenValidSta CTS_enSetTempReImport(cuint16 *pu16Output); 

/* Sun Intansity */
CTS_tenValidSta CTS_enRawSunLImport(cuint16 *pu16Output);                   
CTS_tenValidSta CTS_enRawSunRImport(cuint16 *pu16Output);                      

/* In-Car Temperature Sensor AD Value */
CTS_tenValidSta CTS_enSensorIctAdImport(cuint16 *pu16Output);

/* In-Car Temperature nats value Value */
CTS_tenValidSta CTS_enNatsValueImport(cuint16 *pu16Output);

/* Heater Pump On/Off Status */
CTS_tenValidSta CTS_enHeaterPumpOnOffStaImport(CTS_tenOnOffSta *penOutput);

/* Compressor On/Off Status */
CTS_tenValidSta CTS_enCompOnOffStaImport(CTS_tenOnOffSta *penOutput);

/* Fuel Driving Mode Status */
CTS_tenValidSta CTS_enFuelModeStaImport(cbool *pboOutput);

/* Electric Driving Mode Status */
CTS_tenValidSta CTS_enElecModeStaImport(cbool *pboOutput);

/* External Target Blowout Temperature */
cbool CTS_boUseExTgtBlowTempL(void); 
CTS_tenValidSta CTS_enExTgtBlowTempLImport(cuint16 *pu16Output);    
cbool CTS_boUseExTgtBlowTempR(void); 
CTS_tenValidSta CTS_enExTgtBlowTempRImport(cuint16 *pu16Output);   
cbool CTS_boUseExTgtBlowTempRe(void); 
CTS_tenValidSta CTS_enExTgtBlowTempReImport(cuint16 *pu16Output);

/* Disable Incoming Heat Filter */
cbool CTS_boDisIncomingHeatFl(void);

/* External Head Zone Temperature */
cbool CTS_boUseExHeadZoneTempL(void); 
CTS_tenValidSta CTS_enExHeadZoneTempLImport(cuint16 *pu16Output);    
cbool CTS_boUseExHeadZoneTempR(void); 
CTS_tenValidSta CTS_enExHeadZoneTempRImport(cuint16 *pu16Output);  
cbool CTS_boUseExHeadZoneTempRe(void); 
CTS_tenValidSta CTS_enExHeadZoneTempReImport(cuint16 *pu16Output);  

/* External Body Shell Temperature */
cbool CTS_boUseExBodyShellTemp(void); 
CTS_tenValidSta CTS_enExBodyShellTempImport(cuint16 *pu16Output);    

/* External Cabin Temperature */
cbool CTS_boUseExCabinTemp(void); 
CTS_tenValidSta CTS_enExCabinTempImport(cuint16 *pu16Output);    

/* External Ignition Off Time */
cbool CTS_boUseExIgnOffTime(void);
CTS_tenValidSta CTS_enExIgnOffTimeImport(cuint16 *pu16Output);

/* External blowout temperature */
cbool CTS_boUseExBlowTempL(void); 
CTS_tenValidSta CTS_enExBlowTempLImport(cuint16 *pu16Output);    
cbool CTS_boUseExBlowTempR(void); 
CTS_tenValidSta CTS_enExBlowTempRImport(cuint16 *pu16Output);   
cbool CTS_boUseExBlowTempRe(void); 
CTS_tenValidSta CTS_enExBlowTempReImport(cuint16 *pu16Output);

uint8 CTS_u8ForceIoControl_Write(/*IN*/uint32 ForceIoControlWord);
#endif

/***************************************************************************************************
  EOF: CTS_Import.h
***************************************************************************************************/
