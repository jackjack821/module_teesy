/***************************************************************************************************
                                TARGET BLOWOUT TEMPERATURE STRATEGY                                    
                                        
  .File Name  : TBTS.h
  
  .Description: This file is used for the target blowout temperature calculation.
  
  --------------------------------------------------------------------------------------------------
    Version     Date        Author          Change
  --------------------------------------------------------------------------------------------------
    V001        2016-01-13  Chen Xiongzhi   - Creat this module.
    V002        2016-01-19  Chen Xiongzhi   - Add error processing status.
    V003        2016-01-20  Chen Xiongzhi   - Rename to TBTS.
***************************************************************************************************/

#ifndef TBTS_H
#define	TBTS_H


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
    TBTS_nu16TgtBlowTempL=0,
    TBTS_nu16TgtBlowTempR,
    TBTS_nu16TgtBlowTempRe,
    TBTS_nu16Max
}TBTS_tenu16VarIndex;


/***************************************************************************************************
                                EXPORT INTERFACE FUNCTION PROTOTYPES                      

  Note(s): In this section declare all system global function prototypes of your module.
***************************************************************************************************/

void TBTS_vReset(void);		    
void TBTS_vInit(void);		        
void TBTS_vDeinit(void);	
void TBTS_vMain(void);
CTS_tenValidSta TBTS_enGetU16Export(TBTS_tenu16VarIndex enIndex, cuint16 *pu16Output);
cuint16 TBTS_u16GetValue(TBTS_tenu16VarIndex enIndex);
cuint8 TBTS_u16GetValidState( TBTS_tenu16VarIndex enIndex);
#endif                                  

/***************************************************************************************************
  EOF: TBTS.h
***************************************************************************************************/
