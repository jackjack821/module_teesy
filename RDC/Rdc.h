/***************************************************************************************************
                                       RDC PROCESS
  .File Name: RDC.h
  
  .Description: Thie file is used to process rear defrost events.

  --------------------------------------------------------------------------------------------------
  Version     Date            Author            Change

  --------------------------------------------------------------------------------------------------
  Rev 1.0     2014/11/27      Xu Xianglin     	The first version            
***************************************************************************************************/

#ifndef RDC_H
#define RDC_H

/***************************************************************************************************
                                        HEADER FILES
***************************************************************************************************/

/* System-headerfiles */
#include "General.h"
/* Foreign headerfiles */

/* Own headerfiles */
#include "Rdc_Type.h"
#include "Rdc_Cfg.h"
#include "Rte_Type.h"

/***************************************************************************************************
                                    EXTERN FUNCTION PROTOPYTE
***************************************************************************************************/
void RDC_vReset(void);
void RDC_vInit (void);
void RDC_vDeinit (void);
void  RDC_vMain (void);
uint8 RDC_u8GetValue( RDC_tenu8VarNumber enIndex);
Std_ReturnType RDC_u8ForceIoControl_Write(UInt32 ForceIoControlWord);
#endif                     
/*****************************************************************************
* EOF: Rdc.h
******************************************************************************/

