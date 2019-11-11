
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

#ifndef HCT_TYPE_H
#define HCT_TYPE_H


/*this is for uint16 type variables*/
typedef enum HCT_enu16VarNumbers
{
	HCT_nu16Value,
	HCT_nu16Valid,
	HCT_nu16ErrorCode,
	HCT_nu16SwVer,
	HCT_nu16Max                     
}HCT_tenu16VarNumber;

 typedef enum HCT_enValueSts
 {
    HCT_nInvalid=0u,
    HCT_nValid,
    HCT_nDefault,
    HCT_nLastValue
 }HCT_tenValueSts;


/****************************************/
typedef struct
{
	uint16 u16OatValue;
}HCT_tstCalcFilterFactorIn;
typedef struct
{
	uint16 u16FilterFactor;
}HCT_tstCalcFilterFactorOut;
/****************************************/
typedef struct
{
	uint16 u16HctValueRaw;
	uint16 u16FilterFactor;
}HCT_tstFilterProcessIn;
typedef struct
{
	uint16 u16HctValue;
}HCT_tstFilterProcessOut;
/****************************************/

#endif                           
/*****************************************************************************
******************************************************************************/
