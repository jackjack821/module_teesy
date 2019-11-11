/***************************************************************************************************
                                       Touch KEY PROCESS
  .File Name: TouchKey.h
  
  .Description: Thie file is used to process touch key events.

  --------------------------------------------------------------------------------------------------
  Version     Date            Author            Change

  --------------------------------------------------------------------------------------------------
  Rev 1.0     2017/11/06      Zhong Bin     	The first version            
***************************************************************************************************/

#ifndef TOUCHKEY_H
#define TOUCHKEY_H
/***************************************************************************************************
                                        HEADER FILES
***************************************************************************************************/
/* Own headerfiles */
#include "TouchKey_Type.h"

/***************************************************************************************************
                                    EXTERN VARIABLE INTERFACE
***************************************************************************************************/
extern TOUCHKEY_tenMoveDirection ActionMode;


//extern uint16 FRAME_u16InternalDataForegroudTick;

/***************************************************************************************************
                                    EXTERN FUNCTION PROTOTYTE
***************************************************************************************************/
void TOUCHKEY_vReset (void); 
extern void TOUCHKEY_vInit  (void);  
void TOUCHKEY_vDeinit (void);  
extern void TOUCHKEY_vMain  (void);  
uint32 TOUCHKEY_u32GetValue(TOUCHKEY_tenu32CCModeVarNum Num);
uint16  Get16BitValue(uint8 ucHighByte, uint8 ucLowByte);
uint16 TOUCHKEY_u16GetValue(TOUCHKEY_tenu16CCModeVarNum Num);
uint8 TOUCHKEY_u8GetIicValue_R(uint8 u8Num);
uint8 TOUCHKEY_u8GetIicValue_L(uint8 u8Num);
//void Button_u8key(void);
#endif                                  /* ifndef */

