/***************************************************************************************************
                                           VICT INTERFACE         

  .File Name  : VICT_Interface.h
  
  .Description: This file is the interface of VICT.

  --------------------------------------------------------------------------------------------------
    Version     Date        Author          Change
  --------------------------------------------------------------------------------------------------
    V001        2016-04-15  Chen Xiongzhi   - Creat this module.
***************************************************************************************************/

#ifndef VICT_Interface_H
#define VICT_Interface_H

 
/***************************************************************************************************
                                   INTERFACE FUNCTION PROTOTYPES                                    

  Note(s): In this section declare all interface function prototypes of your module.
***************************************************************************************************/

/* Sensor in-car temperature */
CTS_tenValidSta VICT_enSensorIctImport(cuint16 *pu16Output);   

/* PCB temperature */
CTS_tenValidSta VICT_enPcbTempImport(cuint16 *pu16Output);   

/* Outside air temperature */
CTS_tenValidSta VICT_enOatImport(cuint16 *pu16Output);

/* Sun intensity */
CTS_tenValidSta VICT_enSunImport(cuint16 *pu16Output);                

/* Sun load heat */
CTS_tenValidSta VICT_enSunLoadHeatImport(cuint16 *pu16Output);                

/* Velocity engine heat */
CTS_tenValidSta VICT_enVelEngineHeatImport(cuint16 *pu16Output);               

/* Blowout temperature */
CTS_tenValidSta VICT_enBlowTempLImport(cuint16 *pu16Output);                
CTS_tenValidSta VICT_enBlowTempRImport(cuint16 *pu16Output);  
CTS_tenValidSta VICT_enBlowTempReImport(cuint16 *pu16Output);

/* Blowout speed */
CTS_tenValidSta VICT_enBlowSpdImport(cuint16 *pu16Output);     

/* AIRD mode */
CTS_tenValidSta VICT_enAirdModeImport(cuint8 *pu8Output);       

/* AIRD position */
CTS_tenValidSta VICT_enAirdPosImport(cuint16 *pu16Output);     

/* External ignition off time */
cbool VICT_boUseExIgnOffTime(void);
CTS_tenValidSta VICT_enExIgnOffTimeImport(cuint16 *pu16Output);

/* Disable Incoming Heat Filter */
cbool VICT_boDisIncomingHeatFl(void);

/* External Head Zone Temperature */
cbool VICT_boUseExHeadZoneTempL(void); 
CTS_tenValidSta VICT_enExHeadZoneTempLImport(cuint16 *pu16Output);    
cbool VICT_boUseExHeadZoneTempR(void); 
CTS_tenValidSta VICT_enExHeadZoneTempRImport(cuint16 *pu16Output);  
cbool VICT_boUseExHeadZoneTempRe(void); 
CTS_tenValidSta VICT_enExHeadZoneTempReImport(cuint16 *pu16Output); 


#endif

/***************************************************************************************************
  EOF: VICT_Interface.h
***************************************************************************************************/
