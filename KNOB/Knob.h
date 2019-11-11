/***************************************************************************************************
                                     KNOB PROCESS                                                                            
 
  .File Name  : KNOB.h

  .Description: This file is used to define the statement of extern function.

  --------------------------------------------------------------------------------------------------
    Version     Date            Author              Change
    
  --------------------------------------------------------------------------------------------------
    Rev 1.0     2014-11-09      Xu Xianglin         - module template update.
    Rev 2.0     2015-02-05      Xu xianglin	        - inquiry mode.
    Rev 3.0     2015-03-10      Xu xianglin		    - inquiry mode optimization.
***************************************************************************************************/

#ifndef	KNOB_H
#define	KNOB_H

/***************************************************************************************************
                                        HEADER FILES
***************************************************************************************************/
#include "Knob_Cfg.h"  
#include "Knob_type.h"


/***************************************************************************************************
                                    EXTERN FUNCTION PROTOPYTE
***************************************************************************************************/
typedef enum
{
    Knob_enTempLRotaryOperate=0,
    Knob_enTempRRotaryOperate,
    Knob_enTempLPlusCounter,
    Knob_enTempRPlusCounter,
    Knob_enTempLMinusCounter,
    Knob_enTempRMinusCounter,
}Knob_tenu8Output;

void KNOB_vReset	(void);	/* Reset Container */
void KNOB_vInit	(void);	/* StandbyActive  */
void KNOB_vDeinit	(void);	/* ActiveStandby Container */
void KNOB_vMain	(void);	/* On Container */
//uint8 KNOB_u8GetValue(KNOB_tenVarNum Num);
Std_ReturnType KNOB_vCcpControl_Write(uint32 ForceIoControlWord);
void KNOB_v1msProcess(void);
uint8 KNOB_u8Getvalue(Knob_tenu8Output index);
uint8 KNOB_u8GetvalueForPts(Knob_tenu8Output index);
#endif                   

