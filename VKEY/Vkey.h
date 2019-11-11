/***************************************************************************************************
                                       VKEY PROCESS
  .File Name: VKEY.h
  
  .Description: Thie file is used to process key events.

  --------------------------------------------------------------------------------------------------
  Version     Date            Author            Change

  --------------------------------------------------------------------------------------------------
  Rev 1.0     2016/02/03      Xu Xianglin     	The first version            
***************************************************************************************************/

#ifndef VKEY_H
#define VKEY_H

#include "vkey_type.h"

/***************************************************************************************************
                                        HEADER FILES
***************************************************************************************************/
/* Own headerfiles */

/***************************************************************************************************
                                    EXTERN VARIABLE INTERFACE
***************************************************************************************************/

/***************************************************************************************************
                                    EXTERN FUNCTION PROTOTYTE
***************************************************************************************************/

void VKEY_vReset (void); /*  Reset Container */
void VKEY_vInit  (void);  /* StandbyActive Container */
void VKEY_vDeinit (void);  /* ActiveStandby Container */
void VKEY_vMain  (void);  /* On Container */
void VKEY_vActiveStandby( void);
void VKEY_vStandbyActive( void);
void VKEY_vActive(void);
uint8 VKEY_u8GetValue(VKEY_tenu8VarNum Num);
void VKEY_vCcpControl_Write(uint32 ForceIoControlWord);
uint16 VKEY_u16GetValue(VKEY_tenu16VarNum Num);
#endif                                  /* ifndef */
