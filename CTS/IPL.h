/***************************************************************************************************
                                     IMPORT PREPROCESSING LAYER                                      
                                 
  .File Name  : IPL.h
  
  .Description: This file is used to preprocess the import value.
  
  --------------------------------------------------------------------------------------------------
    Version     Date        Author          Change
  --------------------------------------------------------------------------------------------------
    V001        2014-01-08  Chen Xiongzhi   - Creat this module.
    V002        2015-01-22  Chen Xiongzhi   - Change the structure of the code for input conditions 
                                              process.
    V003        2015-01-30  Chen Xiongzhi   - Change the function structure, add input and output 
                                              structure for parameter passing.
    V004        2015-02-26  Chen Xiongzhi   - Change the code to conform to the rules of MISRA_C.
    V005        2015-08-06  Chen Xiongzhi   - Rename.
    V006        2015-11-10  Chen Xiongzhi   - Rename from IVP to VIVP.
    V007        2016-01-04  Chen Xiongzhi   - Make it compatible with tranditional ICT.
    V008        2016-01-13  Chen Xiongzhi   - Rename to AIVP for ATCS.
    V009        2016-01-19  Chen Xiongzhi   - Add error processing status.
    V010        2016-01-20  Chen Xiongzhi   - Rename to IPL.
    V011        2016-01-30  Chen Xiongzhi   - Update the function structure in order to make it 
                                              correspond to the block diagram.
***************************************************************************************************/

#ifndef IPL_H
#define	IPL_H


/***************************************************************************************************
                                    EXPORT INTERFACE DEFINITIONS                                   

  Note(s): In this section define
           - all export macros
           - all export define-constants
           - all export type definitions
***************************************************************************************************/

/* 8-bit output variables */
typedef enum 
{
    IPL_nu8AirdMode=0,
    IPL_nu8Max
}IPL_tenu8VarIndex;

/* 16-bit output variables */
typedef enum 
{
    IPL_nu16SensorIct=0,
    IPL_nu16EvapTemp,
    IPL_nu16Hct,
    IPL_nu16BlowTempL,
    IPL_nu16BlowTempR,
    IPL_nu16BlowTempRe,
    IPL_nu16BlowSpd,
    IPL_nu16Sun,
    IPL_nu16SunLoadHeat,
    IPL_nu16VelEngineHeat,
    IPL_nu16PcbTemp,
    IPL_nu16Max 
}IPL_tenu16VarIndex;


/***************************************************************************************************
                                EXPORT INTERFACE FUNCTION PROTOTYPES                      

  Note(s): In this section declare all system global function prototypes of your module.
***************************************************************************************************/

void IPL_vReset(void);		    
void IPL_vInit(void);		        
void IPL_vDeinit(void);
void IPL_vMain(void);
CTS_tenValidSta IPL_enGetU8Export(IPL_tenu8VarIndex enIndex, cuint8 *pu8Output);
CTS_tenValidSta IPL_enGetU16Export(IPL_tenu16VarIndex enIndex, cuint16 *pu16Output);

cuint8 IPL_u8GetValue( IPL_tenu8VarIndex enIndex);
cuint16 IPL_u16GetValue( IPL_tenu16VarIndex enIndex);

cuint8 IPL_u8GetValidState( IPL_tenu8VarIndex enIndex);
cuint8 IPL_u16GetValidState( IPL_tenu16VarIndex enIndex);
#endif                                  

/***************************************************************************************************
  EOF: IPL.h
***************************************************************************************************/
