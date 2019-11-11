
/**************************** .FILE_HEADER_BEGIN *****************************
  .TITLE  [ air distribution                                                 ]
*-----------------------------------------------------------------------------
  .FILE   [ aird1c1.h                                                        ]
  .AUTHOR [  duzj 				                                     ]
*-----------------------------------------------------------------------------

 Version Date        Author                       Change                      
 -----------------------------------------------------------------------------   
 Rev 1.0 2013-9-26    duzj        update the module.

*****************************************************************************
****************************** .FILE_HEADER_END ******************************/

#ifndef AIRD_H
#define AIRD_H

/* System-headerfiles */
#include "General.h"
#include "Rte_Internal.h"
/* Own headerfiles */
#include "AIRD_Type.h"
#include "Aird_Cfg.h"

void AIRD_vReset(void);      /* Reset Container */
void AIRD_vInit(void);         /* StandbyActive Container */
void AIRD_vDeinit(void);      /* ActiveStandby Container */
void AIRD_vMain(void);       /* On Container */
void AIRD_vActive(void);     /* Active Container */
Std_ReturnType AIRD_u8ForceIoControl_Write(/*IN*/UInt32 ForceIoControlWord);
uint8 AIRD_u8GetValue( AIRD_tenu8VarNumber enIndex );

uint16 AIRD_u16GetValue( AIRD_tenu16VarNumber enIndex );

#endif                                

