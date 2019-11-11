/***************************************************************************************************
                                           IPL INTERFACE                                           

  .File Name  : IPL_Interface.h
  
  .Description: This file is the interface of IPL.

  --------------------------------------------------------------------------------------------------
    Version     Date        Author          Change
  --------------------------------------------------------------------------------------------------
    V001        2016-04-15  Chen Xiongzhi   - Creat this module.
***************************************************************************************************/

#ifndef IPL_Interface_H
#define IPL_Interface_H


/***************************************************************************************************
                                   INTERFACE FUNCTION PROTOTYPES                                    

  Note(s): In this section declare all interface function prototypes of your module.
***************************************************************************************************/

/* In-car temperature sensor AD value */
CTS_tenValidSta IPL_enSensorIctAdImport(cuint16 *pu16Output);

/* In-car temperature nats value value */
CTS_tenValidSta IPL_enNatsValueImport(cuint16 *pu16Output);

/* PCB temperature AD value */
CTS_tenValidSta IPL_enPcbTempAdImport(cuint16 *pu16Output); 

/* Outside air temperature */
CTS_tenValidSta IPL_enOatImport(cuint16 *pu16Output);

/* Raw evaporator temperature */
CTS_tenValidSta IPL_enRawEvapTempImport(cuint16 *pu16Output);                        

/* Raw heater core entrance coolant temperature */
CTS_tenValidSta IPL_enRawHctImport(cuint16 *pu16Output);                        

/* Sun intansity */
CTS_tenValidSta IPL_enRawSunLImport(cuint16 *pu16Output);                   
CTS_tenValidSta IPL_enRawSunRImport(cuint16 *pu16Output); 

/* Compressor on/off status */
CTS_tenValidSta IPL_enCompOnOffStaImport(CTS_tenOnOffSta *penOutput);

/* Heater pump on/off status */
CTS_tenValidSta IPL_enHeaterPumpOnOffStaImport(CTS_tenOnOffSta *penOutput);

/* Fuel driving mode status */
CTS_tenValidSta IPL_enFuelModeStaImport(cbool *pboOutput);

/* Electric driving mode status */
CTS_tenValidSta IPL_enElecModeStaImport(cbool *pboOutput);

/* Mixing air flap Hi/Lo status */
CTS_tenValidSta IPL_enMacHiLoStaLImport(CTS_tenMacHiLoSta *penOutput);
CTS_tenValidSta IPL_enMacHiLoStaRImport(CTS_tenMacHiLoSta *penOutput);
CTS_tenValidSta IPL_enMacHiLoStaReImport(CTS_tenMacHiLoSta *penOutput);

/* Air distribution flap status */
CTS_tenValidSta IPL_enAirdPosImport(cuint16 *pu16Output);                   

/* R/F flap status */
CTS_tenValidSta IPL_enRfaPosImport(cuint16 *pu16Output);                     

/* Blower voltage */
CTS_tenValidSta IPL_enBlwrVoltImport(cuint16 *pu16Output);                  

/* Velocity */
CTS_tenValidSta IPL_enVelocityImport(cuint16 *pu16Output);                  

/* Target blowout temperature */
CTS_tenValidSta IPL_enTgtBlowTempLImport(cuint16 *pu16Output);    
CTS_tenValidSta IPL_enTgtBlowTempRImport(cuint16 *pu16Output);    
CTS_tenValidSta IPL_enTgtBlowTempReImport(cuint16 *pu16Output);  

/* Cabin temperature */
CTS_tenValidSta IPL_enCabinTempImport(cuint16 *pu16Output); 

/* External blowout temperature */
cbool IPL_boUseExBlowTempL(void); 
CTS_tenValidSta IPL_enExBlowTempLImport(cuint16 *pu16Output);    
cbool IPL_boUseExBlowTempR(void); 
CTS_tenValidSta IPL_enExBlowTempRImport(cuint16 *pu16Output);   
cbool IPL_boUseExBlowTempRe(void); 
CTS_tenValidSta IPL_enExBlowTempReImport(cuint16 *pu16Output);


#endif

/***************************************************************************************************
  EOF: IPL_Interface.h
***************************************************************************************************/
