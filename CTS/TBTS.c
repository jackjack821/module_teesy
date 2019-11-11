/***************************************************************************************************
                                TARGET BLOWOUT TEMPERATURE STRATEGY                                
                                        
  .File Name  : TBTS.c
  
  .Description: This file is used for the target blowout temperature calculation.
  
  --------------------------------------------------------------------------------------------------
    Version     Date        Author          Change
  --------------------------------------------------------------------------------------------------
    V001        2016-01-13  Chen Xiongzhi   - Creat this module.
    V002        2016-01-19  Chen Xiongzhi   - Add error processing status.
    V003        2016-01-20  Chen Xiongzhi   - Rename to TBTS.
***************************************************************************************************/

#define TBTS                             


/***************************************************************************************************
                                            HEADER FILES                                            
***************************************************************************************************/

/* System header files */
#include "CTS_StdDef.h"

/* Foreign header files */
#include "CTS_Alg.h"
#include "CTS_Cfg.h"

/* Own headerfiles */
#include "TBTS.h" 
#include "TBTS_Interface.h"
#include "TBTS_Private.h"  
#include "TBTS_Type.h"


/***************************************************************************************************
                                        FILE LOCAL VARIABLES            
                                        
  Note(s): Define all file local variables in this section. 
***************************************************************************************************/

static TBTS_tstU16Output TBTS_astU16Output[TBTS_nu16Max];
static TBTS_tstPreCtlBlowTemp TBTS_stPreCtlBlowTemp;
static TBTS_tstFbCtlOfs TBTS_stFbCtlOfs;
static TBTS_tstDblZoneOfs TBTS_stDblZoneOfs;
static TBTS_tstFrontRearOfs TBTS_stFrontRearOfs;
static cuint8 TBTS_u8TaskCtr;


/***************************************************************************************************
                                   FILE LOCAL FUNCTION PROTOTYES                                   

  Note(s): In this section declare all file local function prototypes needed for your module.
***************************************************************************************************/

static void TBTS_vTgtBlowTempOutput(void);
static void TBTS_vExControlOutput(void);
static void TBTS_vPreCtlBlowTempOutput(void);
static void TBTS_vFbCtlOfsOutput(void);
static void TBTS_vDblZoneOfsOutput(void);
static void TBTS_vFrontRearOfsOutput(void);
static void TBTS_vCalcSglPreCtlBlowTemp(TBTS_tstCalcSglPreCtlBlowTempIn *pstInput, TBTS_tstSglPreCtlBlowTemp *pstOutput);
static void TBTS_vCalcSglFbCtlOfs(TBTS_tstCalcSglFbCtlOfsIn *pstInput, TBTS_tstSglFbCtlOfs *pstOutput);
static void TBTS_vCalcSglDblZoneOfs(TBTS_tstCalcSglDblZoneOfsIn *pstInput, TBTS_tstSglDblZoneOfs *pstOutput);
static void TBTS_vCalcFrontRearOfs(TBTS_tstCalcFrontRearOfsIn *pstInput, TBTS_tstFrontRearOfs *pstOutput);


/***************************************************************************************************
  Function   : TBTS_vReset                                                      
                           
  Description: Reset function of virtual in car temperature process. This function is called in the  
               RESET container of the operating system.    
                                
  Arguments  : None
  
  Returns    : None 
***************************************************************************************************/

void TBTS_vReset(void)
{
    TBTS_vWriteEnTgtBlowTempStaL(CTS_nInvalid);
    TBTS_vWriteEnTgtBlowTempStaR(CTS_nInvalid);
    TBTS_vWriteEnTgtBlowTempStaRe(CTS_nInvalid);
}


/***************************************************************************************************
  Function   : TBTS_vInit                                                      
                           
  Description: Initialize function of virtual in car temperature process. This function is called in  
               the INIT container of the operating system.
                                
  Arguments  : None
  
  Returns    : None 
***************************************************************************************************/ 

void TBTS_vInit(void)
{
    TBTS_vWriteEnTgtBlowTempStaL(CTS_nInvalid);
    TBTS_vWriteEnTgtBlowTempStaR(CTS_nInvalid);
    TBTS_vWriteEnTgtBlowTempStaRe(CTS_nInvalid);
    TBTS_stPreCtlBlowTemp.enPreCtlBlowTempStaL = CTS_nInvalid;
    TBTS_stPreCtlBlowTemp.enPreCtlBlowTempStaR = CTS_nInvalid;
    TBTS_stPreCtlBlowTemp.enPreCtlBlowTempStaRe = CTS_nInvalid;
    TBTS_stFbCtlOfs.enFbCtlOfsStaL = CTS_nInvalid;
    TBTS_stFbCtlOfs.enFbCtlOfsStaR = CTS_nInvalid;
    TBTS_stFbCtlOfs.enFbCtlOfsStaRe = CTS_nInvalid;
    TBTS_stDblZoneOfs.enDblZoneOfsStaL = CTS_nInvalid;
    TBTS_stDblZoneOfs.enDblZoneOfsStaR = CTS_nInvalid;
    TBTS_stFrontRearOfs.enFrontRearOfsSta = CTS_nInvalid;
    TBTS_u8TaskCtr = 0U;
}


/***************************************************************************************************
  Function   : TBTS_vDeinit                                                     
                           
  Description: De-Init function of virtual in car temperature process. This function is called in  
               the DEINIT container of the operating system.
                                
  Arguments  : None
  
  Returns    : None 
***************************************************************************************************/

void TBTS_vDeinit(void)
{
    TBTS_vWriteEnTgtBlowTempStaL(CTS_nInvalid);
    TBTS_vWriteEnTgtBlowTempStaR(CTS_nInvalid);
    TBTS_vWriteEnTgtBlowTempStaRe(CTS_nInvalid);
}


/***************************************************************************************************
  Function   : TBTS_vMain                                                      
                           
  Description: Main function of virtual in car temperature process. This function is called in the  
               cyclic background task in the ON status. 
            
  Arguments  : None
  
  Returns    : None 
***************************************************************************************************/

void TBTS_vMain(void)
{
    if (TBTS_u8TaskCtr == 0U)
    {
        TBTS_vPreCtlBlowTempOutput();
        TBTS_u8TaskCtr = 1U;
    }
    if (TBTS_u8TaskCtr == 1U)
    {
        TBTS_vTgtBlowTempOutput();
        TBTS_vExControlOutput();
        TBTS_u8TaskCtr = 2U;
    }
    else if (TBTS_u8TaskCtr == 2U)
    {
        TBTS_vFbCtlOfsOutput();
        TBTS_u8TaskCtr = 3U;
    }
    else if (TBTS_u8TaskCtr == 3U)
    {
        TBTS_vDblZoneOfsOutput();
        TBTS_u8TaskCtr = 4U;
    } 
    else if (TBTS_u8TaskCtr == 4U)
    {   
        TBTS_vFrontRearOfsOutput();
        TBTS_u8TaskCtr = 5U;
    }
    else if (TBTS_u8TaskCtr == 5U) 
    {
        TBTS_u8TaskCtr = 6U;    
    }
    else if (TBTS_u8TaskCtr == 6U)
    {
        TBTS_u8TaskCtr = 7U;
    }
    else if (TBTS_u8TaskCtr == 7U)
    {
        TBTS_u8TaskCtr = 8U;
    }
    else if (TBTS_u8TaskCtr == 8U)
    { 
        TBTS_u8TaskCtr = 9U;
    }
    else 
    {   
        TBTS_u8TaskCtr = 0U;
    }
}


/***************************************************************************************************
  Function   : TBTS_vTgtBlowTempOutput                                                
                           
  Description: This function is used to process the target blowout temperature output.
            
  Arguments  : None
  
  Returns    : None
***************************************************************************************************/

static void TBTS_vTgtBlowTempOutput(void)
{
    CTS_tenValidSta enTgtBlowTempStaL, enTgtBlowTempStaR, enTgtBlowTempStaRe;
    cint32 i32TgtBlowTempL, i32TgtBlowTempR, i32TgtBlowTempRe;
    
    i32TgtBlowTempL = (cint32)TBTS_stPreCtlBlowTemp.u16PreCtlBlowTempL;
    i32TgtBlowTempR = (cint32)TBTS_stPreCtlBlowTemp.u16PreCtlBlowTempR;
    i32TgtBlowTempRe = (cint32)TBTS_stPreCtlBlowTemp.u16PreCtlBlowTempRe;

    if (TBTS_stFbCtlOfs.enFbCtlOfsStaL == CTS_nValid)
    {
        i32TgtBlowTempL += (cint32)TBTS_stFbCtlOfs.u16FbCtlOfsL;
        i32TgtBlowTempL -= (cint32)CTS_stThermalRelativeZero.u16Const;
    }

    if (TBTS_stFbCtlOfs.enFbCtlOfsStaR == CTS_nValid)
    {
        i32TgtBlowTempR += (cint32)TBTS_stFbCtlOfs.u16FbCtlOfsR;
        i32TgtBlowTempR -= (cint32)CTS_stThermalRelativeZero.u16Const;
    }

    if (TBTS_stFbCtlOfs.enFbCtlOfsStaRe == CTS_nValid)
    {
        i32TgtBlowTempRe += (cint32)TBTS_stFbCtlOfs.u16FbCtlOfsRe;
        i32TgtBlowTempRe -= (cint32)CTS_stThermalRelativeZero.u16Const;
    }

    if ((CTS_stZoneNum.u8Const>1U) && (TBTS_stDblZoneOfs.enDblZoneOfsStaL==CTS_nValid))
    {
        i32TgtBlowTempL += (cint32)TBTS_stDblZoneOfs.u16DblZoneOfsL;
        i32TgtBlowTempL -= (cint32)CTS_stThermalRelativeZero.u16Const;
    }

    if ((CTS_stZoneNum.u8Const>1U) && (TBTS_stDblZoneOfs.enDblZoneOfsStaR==CTS_nValid))
    {
        i32TgtBlowTempR += (cint32)TBTS_stDblZoneOfs.u16DblZoneOfsR;
        i32TgtBlowTempR -= (cint32)CTS_stThermalRelativeZero.u16Const;
    }

    if ((CTS_stZoneNum.u8Const==3U) && (TBTS_stFrontRearOfs.enFrontRearOfsSta==CTS_nValid))
    {
        i32TgtBlowTempL += (cint32)TBTS_stFrontRearOfs.u16FrontOfs;
        i32TgtBlowTempL -= (cint32)CTS_stThermalRelativeZero.u16Const;
        
        i32TgtBlowTempR += (cint32)TBTS_stFrontRearOfs.u16FrontOfs;
        i32TgtBlowTempR -= (cint32)CTS_stThermalRelativeZero.u16Const;

        i32TgtBlowTempRe += (cint32)TBTS_stFrontRearOfs.u16RearOfs;
        i32TgtBlowTempRe -= (cint32)CTS_stThermalRelativeZero.u16Const;
    }

    if (i32TgtBlowTempL > (cint32)CTS_stMaxTgtBlowTempLimit.u16Const)
    {
        i32TgtBlowTempL = (cint32)CTS_stMaxTgtBlowTempLimit.u16Const;
    }

    if (i32TgtBlowTempR > (cint32)CTS_stMaxTgtBlowTempLimit.u16Const)
    {
        i32TgtBlowTempR = (cint32)CTS_stMaxTgtBlowTempLimit.u16Const;
    }

    if (i32TgtBlowTempRe > (cint32)CTS_stMaxTgtBlowTempLimit.u16Const)
    {
        i32TgtBlowTempRe = (cint32)CTS_stMaxTgtBlowTempLimit.u16Const;
    }

    enTgtBlowTempStaL = TBTS_stPreCtlBlowTemp.enPreCtlBlowTempStaL; 
    enTgtBlowTempStaR = TBTS_stPreCtlBlowTemp.enPreCtlBlowTempStaR;
    enTgtBlowTempStaRe = TBTS_stPreCtlBlowTemp.enPreCtlBlowTempStaRe;
    i32TgtBlowTempL = (cint32)CTS_u16I32ToU16(i32TgtBlowTempL, 0);
    i32TgtBlowTempR = (cint32)CTS_u16I32ToU16(i32TgtBlowTempR, 0);
    i32TgtBlowTempRe = (cint32)CTS_u16I32ToU16(i32TgtBlowTempRe, 0);
        
    TBTS_vWriteEnTgtBlowTempStaL(enTgtBlowTempStaL); 
    TBTS_vWriteEnTgtBlowTempStaR(enTgtBlowTempStaR); 
    TBTS_vWriteEnTgtBlowTempStaRe(enTgtBlowTempStaRe); 
    TBTS_vWriteU16TgtBlowTempL((cuint16)i32TgtBlowTempL);
    TBTS_vWriteU16TgtBlowTempR((cuint16)i32TgtBlowTempR);
    TBTS_vWriteU16TgtBlowTempRe((cuint16)i32TgtBlowTempRe);
}


/***************************************************************************************************
  Function   : TBTS_vExControlOutput                                                
                           
  Description: This function is used to process external control output.
            
  Arguments  : None
  
  Returns    : None
***************************************************************************************************/

static void TBTS_vExControlOutput(void)
{
    CTS_tenValidSta enExTgtBlowTempStaL, enExTgtBlowTempStaR, enExTgtBlowTempStaRe;
    cuint16 u16ExTgtBlowTempL, u16ExTgtBlowTempR, u16ExTgtBlowTempRe;
    cbool boUseExTgtBlowTempL = TBTS_boUseExTgtBlowTempL();
    cbool boUseExTgtBlowTempR = TBTS_boUseExTgtBlowTempR();
    cbool boUseExTgtBlowTempRe = TBTS_boUseExTgtBlowTempR();

    enExTgtBlowTempStaL = TBTS_enExTgtBlowTempLImport(&u16ExTgtBlowTempL);
    enExTgtBlowTempStaR = TBTS_enExTgtBlowTempRImport(&u16ExTgtBlowTempR);
    enExTgtBlowTempStaRe = TBTS_enExTgtBlowTempReImport(&u16ExTgtBlowTempRe);
    
    if (boUseExTgtBlowTempL == CTS_True)
    {
        TBTS_vWriteEnTgtBlowTempStaL(enExTgtBlowTempStaL); 
        TBTS_vWriteU16TgtBlowTempL(u16ExTgtBlowTempL);
    }

    if (boUseExTgtBlowTempR == CTS_True)
    {
        TBTS_vWriteEnTgtBlowTempStaR(enExTgtBlowTempStaR); 
        TBTS_vWriteU16TgtBlowTempR(u16ExTgtBlowTempR);
    }

    if (boUseExTgtBlowTempRe == CTS_True)
    {
        TBTS_vWriteEnTgtBlowTempStaRe(enExTgtBlowTempStaRe); 
        TBTS_vWriteU16TgtBlowTempRe(u16ExTgtBlowTempRe);
    }
}


/***************************************************************************************************
  Function   : TBTS_vPreCtlBlowTempOutput                                                
                           
  Description: This function is used to process the pre-control blowout temperature output.
            
  Arguments  : None
  
  Returns    : None
***************************************************************************************************/

static void TBTS_vPreCtlBlowTempOutput(void)
{
    TBTS_tstCalcSglPreCtlBlowTempIn stCalcSglPreCtlBlowTempIn;
    TBTS_tstSglPreCtlBlowTemp stSglPreCtlBlowTempL, stSglPreCtlBlowTempR, stSglPreCtlBlowTempRe;

    stCalcSglPreCtlBlowTempIn.enSetTempSta = TBTS_enSetTempLImport(&stCalcSglPreCtlBlowTempIn.u16SetTemp);
    stCalcSglPreCtlBlowTempIn.enIncomingHeatSta = TBTS_enIncomingHeatImport(&stCalcSglPreCtlBlowTempIn.u16IncomingHeat);
    stCalcSglPreCtlBlowTempIn.enBlowSpdSta = TBTS_enBlowSpdImport(&stCalcSglPreCtlBlowTempIn.u16BlowSpd);
    TBTS_vCalcSglPreCtlBlowTemp(&stCalcSglPreCtlBlowTempIn, &stSglPreCtlBlowTempL);

    stCalcSglPreCtlBlowTempIn.enSetTempSta = TBTS_enSetTempRImport(&stCalcSglPreCtlBlowTempIn.u16SetTemp);
    TBTS_vCalcSglPreCtlBlowTemp(&stCalcSglPreCtlBlowTempIn, &stSglPreCtlBlowTempR);

    stCalcSglPreCtlBlowTempIn.enSetTempSta = TBTS_enSetTempReImport(&stCalcSglPreCtlBlowTempIn.u16SetTemp);
    TBTS_vCalcSglPreCtlBlowTemp(&stCalcSglPreCtlBlowTempIn, &stSglPreCtlBlowTempRe);

    TBTS_stPreCtlBlowTemp.enPreCtlBlowTempStaL = stSglPreCtlBlowTempL.enPreCtlBlowTempSta;
    TBTS_stPreCtlBlowTemp.u16PreCtlBlowTempL = stSglPreCtlBlowTempL.u16PreCtlBlowTemp;
    TBTS_stPreCtlBlowTemp.enPreCtlBlowTempStaR = stSglPreCtlBlowTempR.enPreCtlBlowTempSta;
    TBTS_stPreCtlBlowTemp.u16PreCtlBlowTempR = stSglPreCtlBlowTempR.u16PreCtlBlowTemp;
    TBTS_stPreCtlBlowTemp.enPreCtlBlowTempStaRe = stSglPreCtlBlowTempRe.enPreCtlBlowTempSta;
    TBTS_stPreCtlBlowTemp.u16PreCtlBlowTempRe = stSglPreCtlBlowTempRe.u16PreCtlBlowTemp;
}


/***************************************************************************************************
  Function   : TBTS_vFbCtlOfsOutputL                                                
                           
  Description: This function is used to process the feed-back control offset output.
            
  Arguments  : None
  
  Returns    : None
***************************************************************************************************/

static void TBTS_vFbCtlOfsOutput(void)
{
    TBTS_tstCalcSglFbCtlOfsIn stCalcSglFbCtlOfsIn;
    TBTS_tstSglFbCtlOfs stSglFbCtlOfsOutL, stSglFbCtlOfsOutR, stSglFbCtlOfsOutRe;

    stCalcSglFbCtlOfsIn.enSetTempSta = TBTS_enSetTempLImport(&stCalcSglFbCtlOfsIn.u16SetTemp);
    stCalcSglFbCtlOfsIn.enHeadZoneTempSta = TBTS_enHeadZoneTempLImport(&stCalcSglFbCtlOfsIn.u16HeadZoneTemp); 
    TBTS_vCalcSglFbCtlOfs(&stCalcSglFbCtlOfsIn, &stSglFbCtlOfsOutL);

    stCalcSglFbCtlOfsIn.enSetTempSta = TBTS_enSetTempRImport(&stCalcSglFbCtlOfsIn.u16SetTemp);
    stCalcSglFbCtlOfsIn.enHeadZoneTempSta = TBTS_enHeadZoneTempRImport(&stCalcSglFbCtlOfsIn.u16HeadZoneTemp);
    TBTS_vCalcSglFbCtlOfs(&stCalcSglFbCtlOfsIn, &stSglFbCtlOfsOutR);

    stCalcSglFbCtlOfsIn.enSetTempSta = TBTS_enSetTempReImport(&stCalcSglFbCtlOfsIn.u16SetTemp);
    stCalcSglFbCtlOfsIn.enHeadZoneTempSta = TBTS_enHeadZoneTempReImport(&stCalcSglFbCtlOfsIn.u16HeadZoneTemp);
    TBTS_vCalcSglFbCtlOfs(&stCalcSglFbCtlOfsIn, &stSglFbCtlOfsOutRe);

    TBTS_stFbCtlOfs.enFbCtlOfsStaL = stSglFbCtlOfsOutL.enFbCtlOfsSta;
    TBTS_stFbCtlOfs.u16FbCtlOfsL = stSglFbCtlOfsOutL.u16FbCtlOfs;
    TBTS_stFbCtlOfs.enFbCtlOfsStaR = stSglFbCtlOfsOutR.enFbCtlOfsSta;
    TBTS_stFbCtlOfs.u16FbCtlOfsR = stSglFbCtlOfsOutR.u16FbCtlOfs;
    TBTS_stFbCtlOfs.enFbCtlOfsStaRe = stSglFbCtlOfsOutRe.enFbCtlOfsSta;
    TBTS_stFbCtlOfs.u16FbCtlOfsRe = stSglFbCtlOfsOutRe.u16FbCtlOfs;
}


/***************************************************************************************************
  Function   : TBTS_vDblZoneOfsOutputL                                                
                           
  Description: This function is used to process the double zone offset output.
            
  Arguments  : None
  
  Returns    : None
***************************************************************************************************/

static void TBTS_vDblZoneOfsOutput(void)
{
    TBTS_tstCalcSglDblZoneOfsIn stCalcSglDblZoneOfsIn;
    TBTS_tstSglDblZoneOfs stSglDblZoneOfsL, stSglDblZoneOfsR;

    stCalcSglDblZoneOfsIn.enSetTempSta = TBTS_enSetTempLImport(&stCalcSglDblZoneOfsIn.u16SetTemp);
    stCalcSglDblZoneOfsIn.enSideSetTempSta = TBTS_enSetTempRImport(&stCalcSglDblZoneOfsIn.u16SideSetTemp);
    stCalcSglDblZoneOfsIn.enAirdModeSta = TBTS_enAirdModeImport(&stCalcSglDblZoneOfsIn.u8AirdMode);
    stCalcSglDblZoneOfsIn.enSideHeadZoneTempSta = TBTS_enHeadZoneTempRImport(&stCalcSglDblZoneOfsIn.u16SideHeadZoneTemp);
    TBTS_vCalcSglDblZoneOfs(&stCalcSglDblZoneOfsIn, &stSglDblZoneOfsL);

    stCalcSglDblZoneOfsIn.enSetTempSta = TBTS_enSetTempRImport(&stCalcSglDblZoneOfsIn.u16SetTemp);
    stCalcSglDblZoneOfsIn.enSideSetTempSta = TBTS_enSetTempLImport(&stCalcSglDblZoneOfsIn.u16SideSetTemp);
    stCalcSglDblZoneOfsIn.enSideHeadZoneTempSta = TBTS_enHeadZoneTempLImport(&stCalcSglDblZoneOfsIn.u16SideHeadZoneTemp);
    TBTS_vCalcSglDblZoneOfs(&stCalcSglDblZoneOfsIn, &stSglDblZoneOfsR);

    TBTS_stDblZoneOfs.enDblZoneOfsStaL = stSglDblZoneOfsL.enDblZoneOfsSta;
    TBTS_stDblZoneOfs.u16DblZoneOfsL = stSglDblZoneOfsL.u16DblZoneOfs;
    TBTS_stDblZoneOfs.enDblZoneOfsStaR = stSglDblZoneOfsR.enDblZoneOfsSta;
    TBTS_stDblZoneOfs.u16DblZoneOfsR = stSglDblZoneOfsR.u16DblZoneOfs;
}


/***************************************************************************************************
  Function   : TBTS_vFrontRearOfsOutput                                                
                           
  Description: This function is used to process the front/rear zone offset output.
            
  Arguments  : None
  
  Returns    : None
***************************************************************************************************/

static void TBTS_vFrontRearOfsOutput(void)
{
    TBTS_tstCalcFrontRearOfsIn stCalcFrontRearOfsIn; 

    stCalcFrontRearOfsIn.enSetTempStaL = TBTS_enSetTempLImport(&stCalcFrontRearOfsIn.u16SetTempL);
    stCalcFrontRearOfsIn.enSetTempStaR = TBTS_enSetTempRImport(&stCalcFrontRearOfsIn.u16SetTempR);
    stCalcFrontRearOfsIn.enSetTempStaRe = TBTS_enSetTempReImport(&stCalcFrontRearOfsIn.u16SetTempRe);
    stCalcFrontRearOfsIn.enAirdModeSta = TBTS_enAirdModeImport(&stCalcFrontRearOfsIn.u8AirdMode);
    stCalcFrontRearOfsIn.enHeadZoneTempStaL = TBTS_enHeadZoneTempLImport(&stCalcFrontRearOfsIn.u16HeadZoneTempL);
    stCalcFrontRearOfsIn.enHeadZoneTempStaR = TBTS_enHeadZoneTempRImport(&stCalcFrontRearOfsIn.u16HeadZoneTempR);
    stCalcFrontRearOfsIn.enHeadZoneTempStaRe = TBTS_enHeadZoneTempReImport(&stCalcFrontRearOfsIn.u16HeadZoneTempRe);
    TBTS_vCalcFrontRearOfs(&stCalcFrontRearOfsIn, &TBTS_stFrontRearOfs);
}


/***************************************************************************************************
  Function   : TBTS_vCalcSglPreCtlBlowTemp                                        
                           
  Description: This function is used to calculate the single side pre-control blowout temperature.
            
  Arguments  : pstInput         - is the address of input structure. 
                                    - enSetTempSta: The valid status of set temperature.
                                    - u16SetTemp: The set temperature.
                                    - enIncomingHeatSta: The valid status of incoming heat.
                                    - u16IncomingHeat: The incoming heat.
                                    - enBlowSpdSta: The valid status of blowout speed.
                                    - u16BlowSpd: The blowout speed.
                                    
               pstOutput        - is the address of output structure.
                                    - enPreCtlBlowTempSta: The valid status of pre-control blowout 
                                                           temperature.
                                    - u16PreCtlBlowTemp: The pre-control blowout temperature output.
  
  Returns    : None
***************************************************************************************************/

static void TBTS_vCalcSglPreCtlBlowTemp(TBTS_tstCalcSglPreCtlBlowTempIn *pstInput, TBTS_tstSglPreCtlBlowTemp *pstOutput)
{ 
    if ((pstInput->enSetTempSta==CTS_nValid) && (pstInput->enIncomingHeatSta==CTS_nValid) 
         && (pstInput->enBlowSpdSta==CTS_nValid))
    {   
        pstOutput->u16PreCtlBlowTemp = CTS_u16Lookup3D_Linear(pstInput->u16SetTemp,  
                                       pstInput->u16IncomingHeat, pstInput->u16BlowSpd, 
                                       CTS_stPreCtlBlowTemp.u8SizeX, CTS_stPreCtlBlowTemp.u8SizeY, 
                                       CTS_stPreCtlBlowTemp.u8SizeZ, 
                                       CTS_stPreCtlBlowTemp.pu16TableX, 
                                       CTS_stPreCtlBlowTemp.pu16TableY, 
                                       CTS_stPreCtlBlowTemp.pu16TableZ, 
                                       CTS_stPreCtlBlowTemp.pu16TableU);
        
        pstOutput->enPreCtlBlowTempSta = CTS_nValid;
    }
    else
    {
        pstOutput->enPreCtlBlowTempSta = CTS_nInvalid;
    }
}


/***************************************************************************************************
  Function   : TBTS_vCalcSglFbCtlOfs                                        
                           
  Description: This function is used to calculate the single side feed-back control offset.
            
  Arguments  : pstInput         - is the address of input structure. 
                                    - enSetTempSta: The valid status of set temperature.
                                    - u16SetTemp: The set temperature.
                                    - enHeadZoneTempSta: The valid status of head zone temperature.
                                    - u16HeadZoneTemp: The head zone temperatue.
                                    
               pstOutput        - is the address of output structure.
                                    - enFbCtlOfsSta: The valid status of feed-back control offset.
                                    - u16FbCtlOfs: The feed-back control offset output.
  
  Returns    : None
***************************************************************************************************/

static void TBTS_vCalcSglFbCtlOfs(TBTS_tstCalcSglFbCtlOfsIn *pstInput, TBTS_tstSglFbCtlOfs *pstOutput)
{
    cint32 i32Ofs;
    cint16 i16Err, i16PFactor;
    cuint16 u16Err, u16PFactor;

    if ((pstInput->enSetTempSta==CTS_nValid) && (pstInput->enHeadZoneTempSta==CTS_nValid))
    {       
        i32Ofs = (cint32)pstInput->u16SetTemp - (cint32)pstInput->u16HeadZoneTemp; 
        i32Ofs += (cint32)CTS_stThermalRelativeZero.u16Const;
        i16Err = CTS_i16I32ToI16(i32Ofs);
        u16Err = CTS_u16I16ToU16(i16Err, 0);

        u16PFactor = CTS_u16Lookup1D_Limit(u16Err, CTS_stFbCtlPFactor.u8SizeX, 
                     CTS_stFbCtlPFactor.pu16TableX, CTS_stFbCtlPFactor.pu16TableY);

        i16PFactor = CTS_i16I32ToI16((cint32)u16PFactor);
        
        i32Ofs -= (cint32)CTS_stThermalRelativeZero.u16Const;
        i16Err = CTS_i16I32ToI16(i32Ofs);

        i32Ofs = ((cint32)i16Err*(cint32)i16PFactor) / (cint32)CTS_stFbCtlPFactorBase.u16Const;
        i32Ofs += (cint32)CTS_stThermalRelativeZero.u16Const;

        pstOutput->u16FbCtlOfs = CTS_u16I32ToU16(i32Ofs, 0);
        pstOutput->enFbCtlOfsSta = CTS_nValid;
    }
    else
    {
        pstOutput->enFbCtlOfsSta = CTS_nInvalid;
    }
}


/***************************************************************************************************
  Function   : TBTS_vCalcSglDblZoneOfs                                        
                           
  Description: This function is used to calculate the single side double zone offset.
            
  Arguments  : pstInput         - is the address of input structure. 
                                    - enSetTempSta: The valid status of set temperature.
                                    - u16SetTemp: The set temperature.
                                    - enSideSetTempSta: The valid status of the other side set 
                                                        temperature.
                                    - u16SideSetTemp: The other side set temperature.
                                    - enAirdModeSta: The valid status of AIRD mode.
                                    - u8AirdMode: The AIRD mode.
                                    - enSideHeadZoneTempSta: The valid status of the other side head 
                                                             zone temperature.
                                    - u16SideHeadZoneTemp: The other side head zone temperatue.

               pstOutput        - is the address of output structure.
                                    - enDblZoneOfsSta: The valid status of double zone offset.
                                    - u16DblZoneOfs: The double zone offset output.
  
  Returns    : None
***************************************************************************************************/

static void TBTS_vCalcSglDblZoneOfs(TBTS_tstCalcSglDblZoneOfsIn *pstInput, TBTS_tstSglDblZoneOfs *pstOutput)
{
    cuint8 u8DblZoneOfsFactor;
    cint32 i32Ofs;
   
    if ((pstInput->enSetTempSta==CTS_nValid) && (pstInput->enSideSetTempSta==CTS_nValid))
    { 
        if (pstInput->u16SetTemp != pstInput->u16SideSetTemp)
        {
            if ((pstInput->enAirdModeSta==CTS_nValid) 
                && (pstInput->enSideHeadZoneTempSta==CTS_nValid))
            {
                u8DblZoneOfsFactor = CTS_u8ReadConstArray(CTS_stDblZoneOfsFactor.pu8Array, 
                                     CTS_stDblZoneOfsFactor.u8Size, pstInput->u8AirdMode);

                i32Ofs = (cint32)pstInput->u16SetTemp - (cint32)pstInput->u16SideHeadZoneTemp;
                i32Ofs *= (cint32)u8DblZoneOfsFactor;
                i32Ofs /= (cint32)CTS_stZoneOfsFactorBase.u8Const;
                i32Ofs += (cint32)CTS_stThermalRelativeZero.u16Const;

                pstOutput->u16DblZoneOfs = CTS_u16I32ToU16(i32Ofs, 0); 
                pstOutput->enDblZoneOfsSta = CTS_nValid;
            }
            else
            {
                pstOutput->enDblZoneOfsSta = CTS_nInvalid;
            }
        }
        else
        {
            pstOutput->u16DblZoneOfs = CTS_stThermalRelativeZero.u16Const;
            pstOutput->enDblZoneOfsSta = CTS_nValid;
        }
    }
    else
    {
        pstOutput->enDblZoneOfsSta = CTS_nInvalid;
    }
}


/***************************************************************************************************
  Function   : TBTS_vCalcFrontRearOfs                                        
                           
  Description: This function is used to calculate the front/rear zone offset.
            
  Arguments  : pstInput         - is the address of input structure. 
                                    - enSetTempStaL: The valid status of left side set temperature.
                                    - u16SetTempL: The left side set temperature.
                                    - enSetTempStaR: The valid status of right side set temperature.
                                    - u16SetTempR: The right side set temperature.
                                    - enSetTempStaRe: The valid status of rear side set temperature.
                                    - u16SetTempRe: The rear side set temperature.
                                    - enAirdModeSta: The valid status of AIRD mode.
                                    - u8AirdMode: The AIRD mode.
                                    - enHeadZoneTempStaL: The valid status of the left side head 
                                                          zone temperature.
                                    - u16HeadZoneTempL: The left side head zone temperatue.
                                    - enHeadZoneTempStaR: The valid status of the right side head 
                                                          zone temperature.
                                    - u16HeadZoneTempR: The right side head zone temperatue.
                                    - enHeadZoneTempStaRe: The valid status of the rear side head 
                                                           zone temperature.
                                    - u16HeadZoneTempRe: The rear side head zone temperatue.
                                    
               pstOutput        - is the address of output structure.
                                    - enFrontRearOfsSta: The valid status of front/rear zone offset.
                                    - u16FrontOfs: The front zone offset output.
                                    - u16RearOfs: The rear zone offset output.
  
  Returns    : None
***************************************************************************************************/

static void TBTS_vCalcFrontRearOfs(TBTS_tstCalcFrontRearOfsIn *pstInput, TBTS_tstFrontRearOfs *pstOutput)
{
    cuint32 u32FrontSetTemp;
    cuint8 u8FrontRearOfsFactor;
    cint32 i32FrontSetTemp, i32FrontHeadZoneTemp, i32FrontOfs, i32RearOfs;
        
    if ((pstInput->enSetTempStaL==CTS_nValid) && (pstInput->enSetTempStaR==CTS_nValid) 
        && (pstInput->enSetTempStaRe==CTS_nValid))
    {
        u32FrontSetTemp = ((cuint32)pstInput->u16SetTempL+(cuint32)pstInput->u16SetTempR) / 2U;

        if (u32FrontSetTemp != (cuint32)pstInput->u16SetTempRe) 
        {
            if ((pstInput->enAirdModeSta==CTS_nValid) && (pstInput->enHeadZoneTempStaL==CTS_nValid) 
                && (pstInput->enHeadZoneTempStaR==CTS_nValid) 
                && (pstInput->enHeadZoneTempStaRe==CTS_nValid))
            {
                u8FrontRearOfsFactor = CTS_u8ReadConstArray(CTS_stFrontRearOfsFactor.pu8Array, 
                                       CTS_stFrontRearOfsFactor.u8Size, pstInput->u8AirdMode);
                
                i32FrontSetTemp = CTS_i32U32ToI32(u32FrontSetTemp);
                
                i32FrontOfs = i32FrontSetTemp - (cint32)pstInput->u16HeadZoneTempRe;
                i32FrontOfs *= (cint32)u8FrontRearOfsFactor;
                i32FrontOfs /= (cint32)CTS_stZoneOfsFactorBase.u8Const;
                i32FrontOfs += (cint32)CTS_stThermalRelativeZero.u16Const;

                i32FrontHeadZoneTemp = (cint32)pstInput->u16HeadZoneTempL;
                i32FrontHeadZoneTemp += (cint32)pstInput->u16HeadZoneTempR;
                i32FrontHeadZoneTemp /= 2;
                
                i32RearOfs = (cint32)pstInput->u16SetTempRe - i32FrontHeadZoneTemp;
                i32RearOfs *= (cint32)u8FrontRearOfsFactor;
                i32RearOfs /= (cint32)CTS_stZoneOfsFactorBase.u8Const;
                i32RearOfs += (cint32)CTS_stThermalRelativeZero.u16Const;

                pstOutput->u16FrontOfs = CTS_u16I32ToU16(i32FrontOfs, 0);
                pstOutput->u16RearOfs = CTS_u16I32ToU16(i32RearOfs, 0);
                pstOutput->enFrontRearOfsSta = CTS_nValid;
            }
            else
            {
                pstOutput->enFrontRearOfsSta = CTS_nInvalid;
            }
        }
        else
        {
            pstOutput->u16FrontOfs = CTS_stThermalRelativeZero.u16Const;
            pstOutput->u16RearOfs = CTS_stThermalRelativeZero.u16Const;
            pstOutput->enFrontRearOfsSta = CTS_nValid;
        } 
    }
    else
    {
        pstOutput->enFrontRearOfsSta = CTS_nInvalid;
    }
}


/***************************************************************************************************
  Function   : TBTS_enGetU16Value                                                 
                           
  Description: This function is used to get the single 16-bit export value of TBTS module. 
                
  Arguments  : enIndex          - is the index of output value.  
               *pu16Output      - is the output value.
                                    
  Returns    : CTS_nValid       - The output value is ready.
               CTS_nInvalid     - The output value is not ready.
***************************************************************************************************/

CTS_tenValidSta TBTS_enGetU16Export(TBTS_tenu16VarIndex enIndex, cuint16 *pu16Output)
{
    CTS_tenValidSta enReturn;
    cuint16 u16Max = (cuint16)TBTS_nu16Max - 1U;
        
    if (enIndex < TBTS_nu16Max)
    {
        *pu16Output = TBTS_astU16Output[enIndex].u16Output;
        enReturn = TBTS_astU16Output[enIndex].enOutputValidSta;
    }
    else
    {
        *pu16Output = TBTS_astU16Output[u16Max].u16Output;
        enReturn = TBTS_astU16Output[u16Max].enOutputValidSta;
    }

    return enReturn;
}

cuint16 TBTS_u16GetValue(TBTS_tenu16VarIndex enIndex)
{
    cuint16 u16Return;
    cuint16 u16Max = (cuint16)TBTS_nu16Max - 1U;
        
    if (enIndex < TBTS_nu16Max)
    {
        u16Return = TBTS_astU16Output[enIndex].u16Output;
    }
    else
    {
        u16Return = TBTS_astU16Output[u16Max].u16Output;
    }

    return u16Return;
}

cuint8 TBTS_u16GetValidState( TBTS_tenu16VarIndex enIndex)
{
	CTS_tenValidSta enReturn;
    cuint16 u16Max = (cuint16)TBTS_nu16Max - 1U;
        
    if (enIndex < TBTS_nu16Max)
    {
        enReturn = TBTS_astU16Output[enIndex].enOutputValidSta;
    }
    else
    {
        enReturn = TBTS_astU16Output[u16Max].enOutputValidSta;
    }
	return enReturn;
}

/***************************************************************************************************
  EOF: TBTS.c
***************************************************************************************************/
