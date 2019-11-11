/***************************************************************************************************
                                       HCT PROCESS
  .File Name: HCT.h
  
  .Description: Thie file is used to work out a valid heatcore temperature.
  
  --------------------------------------------------------------------------------------------------
  Version     Date            Author            Change

  --------------------------------------------------------------------------------------------------
  0x0100        2016/8/23     Lv Haoguang    Create BaseCode.
***************************************************************************************************/
#ifndef HCT_H
#define HCT_H

#include "Hct_Type.h" 

void HCT_vReset(void);
void HCT_vInit(void);
void HCT_vDeinit (void);
void HCT_vMain(void);
void HCT_vActive(void);
uint16 HCT_u16GetValue(HCT_tenu16VarNumber enIndex);
Std_ReturnType HCT_u8ForceIoControl_Write(/*IN*/uint32 ForceIoControlWord);
#endif  
/*****************************************************************************
* EOF:
******************************************************************************/


