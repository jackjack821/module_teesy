
/**************************** .FILE_HEADER_BEGIN *****************************
  .TITLE  [ HCT MODULE ]
*-----------------------------------------------------------------------------
  .FILE   [ Hct_Private.h ]
  .AUTHOR [  Xu Xianglin ]
*-----------------------------------------------------------------------------

 Version Date        Author                       Change                      
 -----------------------------------------------------------------------------
  0x0100        2016/8/23     Lv Haoguang    Create BaseCode.
*****************************************************************************/

#ifndef HCT_PRIVATE_H
#define HCT_PRIVATE_H

#include "hct_type.h"
#include "Oat.h"

static const uint16 HCT_u16FilterFactor_X[6] = {0,200,400,500,600,800}; 
static const uint16 HCT_u16FilterFactor_Y[6] = {1,1,  1,  1,  1  ,1  }; 

#define HCT_u16DefaultValue (90*10+400)/*acoording to can matrix*/
#define HCT_u16DefaultOatValue (20*10+400)
#define HCT_u16MaxValue     (0xE9)
#define HCT_u16ValueErrorTime (30)/*3 second*/

/***********/
#define HCT_u16IgnOnDelayFinish 1
#define HCT_u16QualityFlag	CANAPP_u16GetValue(CANAPP_nu16EMS_EngineCoolantTempInvalid)//Rte_IRead_Hct_vMain_Hct_CanAppEngWaterTempVD_u8Flag()	
#define HCT_u16RawTempFromCan	CANAPP_u16GetValue(CANAPP_nu16EMS_EngineCoolantTemp)//Rte_IRead_Hct_vMain_Hct_CanAppEngWaterTemp_u8Temp()
#define HCT_u16OatValid	OAT_u16GetValue(OAT_nu16Valid)	
#define HCT_u16OatValue	OAT_u16GetValue(OAT_nu16Value)

#define HCT_u16QualityValid 0
#define HCT_u16QualityInValid 1


/*************************No Config Parameter End******************************/
#define HCT_vSetBit(Value,bit)				(Value |= (1 << bit))
#define HCT_vClrBit(Value,bit)				(Value &= (~(1 << bit)))
#define HCT_vGetBit(Value,bit)				((Value>>bit)&0x01)

/***************************************************************************************************
* End of check if informations are already included
***************************************************************************************************/
#endif                              

