/***************************************************************************************************
                                           HCT INTERFACE
                                           
  .File Name  : HCT_Interface.h
  
  .Description: This file is the interface of HCT.

  --------------------------------------------------------------------------------------------------
    Version     Date        Author          Change
  --------------------------------------------------------------------------------------------------
  0x0100        2016/8/23     Lv Haoguang    Create BaseCode.
***************************************************************************************************/

#ifndef HCT_Interface_H
#define HCT_Interface_H

#include "Hct_Type.h" 
/***************************************************************************************************
                                   INTERFACE FUNCTION PROTOTYPES                                    

  Note(s): In this section declare all interface function prototypes of your module.
***************************************************************************************************/
HCT_tenValueSts HCT_enImportRawTemp(uint16 *value);
HCT_tenValueSts HCT_enImportOatTemp(uint16 *value);
void HCT_enInitValue(void);
void HCT_enExportAll(void);


#endif

