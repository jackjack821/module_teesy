/**************************** .FILE_HEADER_BEGIN *****************************
  .TITLE  [EED                                      ]
*-----------------------------------------------------------------------------
  .FILE   [ EED.h                                                         ]
  .AUTHOR [  Tan Fumin				                                     ]
*-----------------------------------------------------------------------------
 Version Date        		Author                       
Change                      
 -----------------------------------------------------------------------------
 Rev 00.00.00 2014/12/12    Tan Fumin      			 The first version  
 Rev 02       2015/06/01    Zhang Shuncong            add groupID info,update flow                                                 update Telltales process
****************************** .FILE_HEADER_END ******************************/

#ifndef EED_H
#define EED_H

#include "General.h"
#include "EED_CFG.h"
#include "EED_TYPE.h"
#include "EED_PRIVATE.h"

#if EED_DataFlashType == FUJITSU_16BIT
#include "CFD.h"
#endif

#if EED_DataFlashType == NEC_32BIT
#include "FLS_Drv.h"
#endif
#define EED_UseFlowCheck
void EED_vReset(void);
void EED_vMain(void);
uint8 EED_u8GetValue( EED_tenu8VarNum enIndex );

uint8 EED_u8WriteGroupData(uint8 u8GroupID,uint8 au8DataBuffer[], uint16 u16Length);
uint8 EED_u8ReadGroupData(uint8 u8GroupID,uint8 au8DataBuffer[], uint16 u16Length);

uint8 EED_u8WriteGroupDataFlow(uint8 u8GroupID,uint8 au8DataBuffer[], uint16 u16Length);
//uint8 EED_u8ReadGroupDataFlow(uint8 u8GroupID,uint8 au8DataBuffer[], uint16 u16Length);

uint8 EED_u8WriteDataWait(uint32 u32EepAddress, uint8 au8DataBuffer[], uint16 u16Length);
uint8 EED_u8ReadDataWait(uint32 u32EepAddress, uint8 au8DataBuffer[], uint16 u16Length);

void EED_vWriteFlowCheck(void);
uint8 EED_u8WriteFlowFinish(void);


#endif

