/**************************** .FILE_HEADER_BEGIN *****************************
  .TITLE:    driver for SBC serial
*-----------------------------------------------------------------------------
  .FILE:EEP_Drv.h
  .AUTHOR:Zhushengxin
*-----------------------------------------------------------------------------

 Date        Author                       Change
 -----------------------------------------------------------------------------
2018.03.27 Zhushengxin		   :create this module

*****************************************************************************/

#include "general.h"

#ifndef SBC_Private_H
#define SBC_Private_H

#include "s_spi.h"
#include "SBC_Type.h"
#include "SBC_Private.h"


#define TLE9262Drv_u16ErrcodeSetbit(bit)  SBC_u16ErrCode |= (0x01<<(bit))
#define TLE9262Drv_u16ErrcodeClcbit(bit)  SBC_u16ErrCode &= ~(0x01<<(bit))

#endif

