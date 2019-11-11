/***************************************************************************************************
                                           TBTS INTERFACE
                                           
  .File Name  : TBTS_Interface.h
  
  .Description: This file is the interface of TBTS.

  --------------------------------------------------------------------------------------------------
    Version     Date        Author          Change
  --------------------------------------------------------------------------------------------------
    V001        2016-04-15  Chen Xiongzhi   - Creat this module.
***************************************************************************************************/

#ifndef TBTS_Interface_H
#define TBTS_Interface_H

 
/***************************************************************************************************
                                   INTERFACE FUNCTION PROTOTYPES                                    

  Note(s): In this section declare all interface function prototypes of your module.
***************************************************************************************************/

/* Set temperature */
CTS_tenValidSta TBTS_enSetTempLImport(cuint16 *pu16Output);           
CTS_tenValidSta TBTS_enSetTempRImport(cuint16 *pu16Output);   
CTS_tenValidSta TBTS_enSetTempReImport(cuint16 *pu16Output);

/* Incoming heat */
CTS_tenValidSta TBTS_enIncomingHeatImport(cuint16 *pu16Output);
    
/* Blowout speed */
CTS_tenValidSta TBTS_enBlowSpdImport(cuint16 *pu16Output);                

/* Head zone temperature */
CTS_tenValidSta TBTS_enHeadZoneTempLImport(cuint16 *pu16Output);                
CTS_tenValidSta TBTS_enHeadZoneTempRImport(cuint16 *pu16Output);   
CTS_tenValidSta TBTS_enHeadZoneTempReImport(cuint16 *pu16Output);  

/* AIRD mode */
CTS_tenValidSta TBTS_enAirdModeImport(cuint8 *pu8Output);   

/* External target blowout temperature */
cbool TBTS_boUseExTgtBlowTempL(void); 
CTS_tenValidSta TBTS_enExTgtBlowTempLImport(cuint16 *pu16Output);  
cbool TBTS_boUseExTgtBlowTempR(void); 
CTS_tenValidSta TBTS_enExTgtBlowTempRImport(cuint16 *pu16Output);  
cbool TBTS_boUseExTgtBlowTempRe(void); 
CTS_tenValidSta TBTS_enExTgtBlowTempReImport(cuint16 *pu16Output);  


#endif

/***************************************************************************************************
  EOF: TBTS_Interface.h
***************************************************************************************************/
