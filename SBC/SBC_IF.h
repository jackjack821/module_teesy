/**************************** .FILE_HEADER_BEGIN *****************************
  .TITLE:     SBC_If.h
*-----------------------------------------------------------------------------
  .FILE: SBC_If.h
  .AUTHOR:ZhengJianshi
*-----------------------------------------------------------------------------

 Date        Author                       Change
 -----------------------------------------------------------------------------
2018.04.13 ZhengJianshi		   :create this module

*****************************************************************************/
#ifndef SBC_IF_H
#define SBC_IF_H

#include "SBC_Type.h"

 uint8 TLE9262Drv_vGetHS1_ConfigStatus(void);
 uint8 TLE9262Drv_vGetHS2_ConfigStatus(void);
 uint8 TLE9262Drv_vGetHS3_ConfigStatus(void);
 uint8 TLE9262Drv_vGetHS4_ConfigStatus(void);

  uint8 SBC_vGetSysStatus(void);
  uint16 SBC_vImpIDIgnStatic(void);
#endif

