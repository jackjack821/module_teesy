/***************************************************************************************************
                                TARGET BLOWOUT TEMPERATURE STRATEGY                                    
                                        
  .File Name  : TBTS_Type.h
  
  .Description: This file is used for the target blowout temperature calculation.
  
  --------------------------------------------------------------------------------------------------
    Version     Date        Author          Change
  --------------------------------------------------------------------------------------------------
    V001        2016-01-13  Chen Xiongzhi   - Creat this module.
    V002        2016-01-19  Chen Xiongzhi   - Add error processing status.
    V003        2016-01-20  Chen Xiongzhi   - Rename to TBTS.
***************************************************************************************************/

#ifndef TBTS_Type
#define TBTS_Type


/***************************************************************************************************
                                          TYPE DEFINITIONS                                          

  Note(s): In this section define the type definitions
***************************************************************************************************/

/* 16-bit output structure */
typedef struct
{
    CTS_tenValidSta enOutputValidSta;
    cuint16 u16Output;
}TBTS_tstU16Output;

/* Pre-control blowout temperature */
typedef struct
{
    CTS_tenValidSta enPreCtlBlowTempStaL;
    cuint16 u16PreCtlBlowTempL;
    CTS_tenValidSta enPreCtlBlowTempStaR;
    cuint16 u16PreCtlBlowTempR;
    CTS_tenValidSta enPreCtlBlowTempStaRe;
    cuint16 u16PreCtlBlowTempRe;
}TBTS_tstPreCtlBlowTemp;

/* Feed-back control offset */
typedef struct
{
    CTS_tenValidSta enFbCtlOfsStaL;
    cuint16 u16FbCtlOfsL;
    CTS_tenValidSta enFbCtlOfsStaR;
    cuint16 u16FbCtlOfsR;
    CTS_tenValidSta enFbCtlOfsStaRe;
    cuint16 u16FbCtlOfsRe;
}TBTS_tstFbCtlOfs;

/* Double zone offset */
typedef struct
{
    CTS_tenValidSta enDblZoneOfsStaL;
    cuint16 u16DblZoneOfsL;
    CTS_tenValidSta enDblZoneOfsStaR;
    cuint16 u16DblZoneOfsR;
}TBTS_tstDblZoneOfs;

/* Front rear zone offset */
typedef struct
{
    CTS_tenValidSta enFrontRearOfsSta;
    cuint16 u16FrontOfs;
    cuint16 u16RearOfs;
}TBTS_tstFrontRearOfs;

/* Input variables for single side pre-control blowout temperature calculation */
typedef struct
{
    CTS_tenValidSta enSetTempSta;
    cuint16 u16SetTemp;
    CTS_tenValidSta enIncomingHeatSta;
    cuint16 u16IncomingHeat;
    CTS_tenValidSta enBlowSpdSta;
    cuint16 u16BlowSpd;
}TBTS_tstCalcSglPreCtlBlowTempIn;

/* Single side pre-control blowout temperature */
typedef struct
{
    CTS_tenValidSta enPreCtlBlowTempSta;
    cuint16 u16PreCtlBlowTemp;
}TBTS_tstSglPreCtlBlowTemp;

/* Input variables for single side feed-back control offset calculation */
typedef struct
{
    CTS_tenValidSta enSetTempSta;
    cuint16 u16SetTemp;
    CTS_tenValidSta enHeadZoneTempSta;
    cuint16 u16HeadZoneTemp;
}TBTS_tstCalcSglFbCtlOfsIn;

/* Single side feed-back control offset */
typedef struct
{
    CTS_tenValidSta enFbCtlOfsSta;
    cuint16 u16FbCtlOfs;
}TBTS_tstSglFbCtlOfs;

/* Input variables for single side double zone offset calculation */
typedef struct
{
    CTS_tenValidSta enSetTempSta;
    cuint16 u16SetTemp;
    CTS_tenValidSta enSideSetTempSta;
    cuint16 u16SideSetTemp;
    CTS_tenValidSta enAirdModeSta;
    cuint8 u8AirdMode;
    CTS_tenValidSta enSideHeadZoneTempSta;
    cuint16 u16SideHeadZoneTemp;
}TBTS_tstCalcSglDblZoneOfsIn;

/* Single side double zone offset */
typedef struct
{
    CTS_tenValidSta enDblZoneOfsSta;
    cuint16 u16DblZoneOfs;
}TBTS_tstSglDblZoneOfs;

/* Input variables for single side double zone offset calculation */
typedef struct
{
    CTS_tenValidSta enSetTempStaL;
    cuint16 u16SetTempL;
    CTS_tenValidSta enSetTempStaR;
    cuint16 u16SetTempR;
    CTS_tenValidSta enSetTempStaRe;
    cuint16 u16SetTempRe;
    CTS_tenValidSta enAirdModeSta;
    cuint8 u8AirdMode;
    CTS_tenValidSta enHeadZoneTempStaL;
    cuint16 u16HeadZoneTempL;
    CTS_tenValidSta enHeadZoneTempStaR;
    cuint16 u16HeadZoneTempR;
    CTS_tenValidSta enHeadZoneTempStaRe;
    cuint16 u16HeadZoneTempRe;
}TBTS_tstCalcFrontRearOfsIn;


#endif                              

/***************************************************************************************************
  EOF: TBTS_Type.h
***************************************************************************************************/
