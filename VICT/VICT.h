/***************************************************************************************************
                                     VIRTUAL IN CAR TEMPERATURE                                     

  .File Name  : VICT.h
  
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
    V003        2015-01-08  Chen Xiongzhi   - Move some input process function to VICTIP module, 
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

#ifndef VICT_H
#define	VICT_H


/***************************************************************************************************
                                    EXPORT INTERFACE DEFINITIONS                                   

  Note(s): In this section define
           - all export macros
           - all export define-constants
           - all export type definitions
***************************************************************************************************/

/* 16-bit output variables */
typedef enum 
{
    VICT_nu16HeadZoneTempL=0,
    VICT_nu16HeadZoneTempR,
    VICT_nu16HeadZoneTempRe,
    VICT_nu16BodyShellTemp,
    VICT_nu16CabinTemp,
    VICT_nu16IncomingHeat,
    VICT_nu16Max
}VICT_tenu16VarIndex;


/***************************************************************************************************
                                EXPORT INTERFACE FUNCTION PROTOTYPES                      

  Note(s): In this section declare all system global function prototypes of your module.
***************************************************************************************************/

void VICT_vReset(void);		    
void VICT_vInit(void);		        
void VICT_vDeinit(void);	
void VICT_vMain(void);
void VICT_vActive(void);
cbool VICT_boGetActiveFlag(void);
CTS_tenValidSta VICT_enGetU16Export(VICT_tenu16VarIndex enIndex, cuint16 *pu16Output);
cuint16 VICT_u16GetValue(VICT_tenu16VarIndex enIndex);
cuint16 VICT_u16GetValidState( VICT_tenu16VarIndex enIndex);

#endif                                  

/***************************************************************************************************
  EOF: VICT.h
***************************************************************************************************/
