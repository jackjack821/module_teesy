/***************************************************************************************************
                                     IMPORT PREPROCESSING LAYER                                     
                                 
  .File Name  : IPL.c
  
  .Description: This file is used to preprocess the import value.
  
  --------------------------------------------------------------------------------------------------
    Version     Date        Author          Change
  --------------------------------------------------------------------------------------------------
    V001        2014-01-08  Chen Xiongzhi   - Creat this module.
    V002        2015-01-22  Chen Xiongzhi   - Change the structure of the code for input conditions 
                                              process.
    V003        2015-01-30  Chen Xiongzhi   - Change the function structure, add input and output 
                                              structure for parameter passing.
    V004        2015-02-26  Chen Xiongzhi   - Change the code to conform to the rules of MISRA_C.
    V005        2015-08-06  Chen Xiongzhi   - Rename.
    V006        2015-11-10  Chen Xiongzhi   - Rename from IVP to VIVP.
    V007        2016-01-04  Chen Xiongzhi   - Make it compatible with tranditional ICT.
    V008        2016-01-13  Chen Xiongzhi   - Rename to AIVP for ATCS.
    V009        2016-01-19  Chen Xiongzhi   - Add error processing status.
    V010        2016-01-20  Chen Xiongzhi   - Rename to IPL.
    V011        2016-01-30  Chen Xiongzhi   - Update the function structure in order to make it 
                                              correspond to the block diagram.
***************************************************************************************************/

#define IPL                           


/***************************************************************************************************
                                            HEADER FILES
***************************************************************************************************/

/* System header files */
#include "CTS_StdDef.h"

/* Foreign header files */
#include "CTS_Alg.h"
#include "CTS_Cfg.h"

/* Own header files */
#include "IPL.h"  
#include "IPL_Interface.h"
#include "IPL_Private.h" 
#include "IPL_Type.h"    


/***************************************************************************************************
                                        FILE LOCAL VARIABLES                                        
                                        
  Note(s): Define all file local variables in this section.
***************************************************************************************************/

static IPL_tstU8Output IPL_astU8Output[IPL_nu8Max];
static IPL_tstU16Output IPL_astU16Output[IPL_nu16Max];
static IPL_tstSensorIctFl IPL_stSensorIctFl;
static IPL_tstEvapTempFl IPL_stEvapTempFl;
static IPL_tstHctFl IPL_stHctFl;
static IPL_tstBlowTempFl IPL_stBlowTempFlL;
static IPL_tstBlowTempFl IPL_stBlowTempFlR;
static IPL_tstBlowTempFl IPL_stBlowTempFlRe;
static cuint16 IPL_u16IctStableWaitTime;
static cuint16 IPL_u16PcbTempStableWaitTime;
static cuint8 IPL_u8TaskCtr;


/***************************************************************************************************
                                   FILE LOCAL FUNCTION PROTOTYES                                   

  Note(s): In this section declare all file local function prototypes needed for your module.
***************************************************************************************************/

static void IPL_vSensorIctOutput(void);
static void IPL_vAirdModeOutput(void);
static void IPL_vEvapTempOutput(void);
static void IPL_vHctOutput(void);
static void IPL_vBlowTempOutput(void);
static void IPL_vBlowSpdOutput(void);
static void IPL_vSunOutput(void);
static void IPL_vSunLoadHeatOutput(void);
static void IPL_vVelEngineHeatOutput(void);
static void IPL_vPcbTempOutput(void);
static void IPL_vCalcSensorIct(IPL_tstCalcSensorIctIn *pstInput, IPL_tstSensorIct *pstOutput);
static void IPL_vSensorIctFl(IPL_tstSensorIctFlIn *pstInput, IPL_tstSensorIctFl *pstOutput);
static void IPL_vCalcAirdMode(IPL_tstCalcAirdModeIn *pstInput, IPL_tstAirdMode *pstOutput);
static void IPL_vCalcEvapTemp(IPL_tstCalcEvapTempIn *pstInput, IPL_tstEvapTemp *pstOutput);
static void IPL_vCalcEvapTempOfs(IPL_tstCalcEvapTempOfsIn *pstInput, IPL_tstEvapTempOfs *pstOutput);
static void IPL_vCalcCompOffEvapTemp(IPL_tstCalcCompOffEvapTempIn *pstInput, IPL_tstCompOffEvapTemp *pstOutput);
static void IPL_vEvapTempFl(IPL_tstEvapTempFlIn *pstInput, IPL_tstEvapTempFl *pstOutput);
static void IPL_vHctFl(IPL_tstHctFlIn *pstInput, IPL_tstHctFl *pstOutput);
static void IPL_vCalcBlowTemp(IPL_tstCalcBlowTempIn *pstInput, IPL_tstBlowTemp *pstOutput);
static void IPL_vCalcLimitMacRtoL(IPL_tstCalcLimitMacRtoIn *pstInput, IPL_tstLimitMacRto *pstOutput);
static void IPL_vCalcLimitMacRtoR(IPL_tstCalcLimitMacRtoIn *pstInput, IPL_tstLimitMacRto *pstOutput);
static void IPL_vCalcLimitMacRtoRe(IPL_tstCalcLimitMacRtoIn *pstInput, IPL_tstLimitMacRto *pstOutput);
static void IPL_vBlowTempFl(IPL_tstBlowTempFlIn *pstInput, IPL_tstBlowTempFl *pstOutput);
static void IPL_vCalcRawBlowTemp(IPL_tstCalcRawBlowTempIn *pstInput, IPL_tstRawBlowTemp *pstOutput);
static void IPL_vCalcBlowSpd(IPL_tstCalcBlowSpdIn *pstInput, IPL_tstBlowSpd *pstOutput);
static void IPL_vCalcSun(IPL_tstCalcSunIn *pstInput, IPL_tstSun *pstOutput);
static void IPL_vCalcSunLoadHeat(IPL_tstCalcSunLoadHeatIn *pstInput, IPL_tstSunLoadHeat *pstOutput);
static void IPL_vCalcVelEngineHeat(IPL_tstCalcVelEngineHeatIn *pstInput, IPL_tstVelEngineHeat *pstOutput);
static void IPL_vCalcPcbTemp(IPL_tstCalcPcbTempIn *pstInput, IPL_tstPcbTemp *pstOutput);
static void IPL_vUpdateSensorIctFl(IPL_tstUpdateSensorIctFlIn *pstInput);
static void IPL_vUpdateEvapTempFl(IPL_tstUpdateEvapTempFlIn *pstInput);
static void IPL_vUpdateHctFl(IPL_tstUpdateHctFlIn *pstInput);
static void IPL_vUpdateBlowTempFl(IPL_tstUpdateBlowTempFlIn *pstInput);


/***************************************************************************************************
  Function   : IPL_vReset                                                      
                           
  Description: Reset function of virtual in car temperature input process module. This function is 
               called in the RESET container of the operating system.    
                                
  Arguments  : None
  
  Returns    : None 
***************************************************************************************************/

void IPL_vReset(void)
{
    IPL_vWriteEnSensorIctSta(CTS_nInvalid);
    IPL_vWriteEnAirdModeSta(CTS_nInvalid); 
    IPL_vWriteEnEvapTempSta(CTS_nInvalid);
    IPL_vWriteEnHctSta(CTS_nInvalid);
    IPL_vWriteEnBlowTempStaL(CTS_nInvalid);
    IPL_vWriteEnBlowTempStaR(CTS_nInvalid);
    IPL_vWriteEnBlowTempStaRe(CTS_nInvalid);
    IPL_vWriteEnBlowSpdSta(CTS_nInvalid);
    IPL_vWriteEnSunSta(CTS_nInvalid);
    IPL_vWriteEnSunLoadHeatSta(CTS_nInvalid);
    IPL_vWriteEnVelEngineHeatSta(CTS_nInvalid);
    IPL_vWriteEnPcbTempSta(CTS_nInvalid); 
}


/***************************************************************************************************
  Function   : IPL_vInit                                                      
                           
  Description: Initialize function of virtual in car temperature input process module. This function 
               is called in the INIT container of the operating system.
                                
  Arguments  : None
  
  Returns    : None 
***************************************************************************************************/ 

void IPL_vInit(void)
{
    IPL_vWriteEnSensorIctSta(CTS_nInvalid);
    IPL_vWriteEnAirdModeSta(CTS_nInvalid); 
    IPL_vWriteEnEvapTempSta(CTS_nInvalid);
    IPL_vWriteEnHctSta(CTS_nInvalid);
    IPL_vWriteEnBlowTempStaL(CTS_nInvalid);
    IPL_vWriteEnBlowTempStaR(CTS_nInvalid);
    IPL_vWriteEnBlowTempStaRe(CTS_nInvalid);
    IPL_vWriteEnBlowSpdSta(CTS_nInvalid);
    IPL_vWriteEnSunSta(CTS_nInvalid);
    IPL_vWriteEnSunLoadHeatSta(CTS_nInvalid);
    IPL_vWriteEnVelEngineHeatSta(CTS_nInvalid);
    IPL_vWriteEnPcbTempSta(CTS_nInvalid); 
    IPL_stSensorIctFl.enFlInitValSta = CTS_nInvalid;
    IPL_stSensorIctFl.enSensorIctSta = CTS_nInvalid;
    IPL_stEvapTempFl.enFlInitValSta = CTS_nInvalid;
    IPL_stEvapTempFl.enEvapTempSta = CTS_nInvalid;
    IPL_stHctFl.enFlInitValSta = CTS_nInvalid;
    IPL_stHctFl.enHctSta = CTS_nInvalid;
    IPL_stBlowTempFlL.enFlInitValSta = CTS_nInvalid;
    IPL_stBlowTempFlL.enBlowTempSta = CTS_nInvalid;
    IPL_stBlowTempFlR.enFlInitValSta = CTS_nInvalid;
    IPL_stBlowTempFlR.enBlowTempSta = CTS_nInvalid;
    IPL_stBlowTempFlRe.enFlInitValSta = CTS_nInvalid;
    IPL_stBlowTempFlRe.enBlowTempSta = CTS_nInvalid;
    IPL_u16IctStableWaitTime = 0U;
    IPL_u16PcbTempStableWaitTime = 0U;
    IPL_u8TaskCtr = 0U;
}


/***************************************************************************************************
  Function   : IPL_vDeinit                                                     
                           
  Description: De-Init function of virtual in car temperature input process module. This function is 
               called in the DEINIT container of the operating system.
                                
  Arguments  : None
  
  Returns    : None 
***************************************************************************************************/

void IPL_vDeinit(void)
{
    IPL_vWriteEnSensorIctSta(CTS_nInvalid);
    IPL_vWriteEnAirdModeSta(CTS_nInvalid); 
    IPL_vWriteEnEvapTempSta(CTS_nInvalid);
    IPL_vWriteEnHctSta(CTS_nInvalid);
    IPL_vWriteEnBlowTempStaL(CTS_nInvalid);
    IPL_vWriteEnBlowTempStaR(CTS_nInvalid);
    IPL_vWriteEnBlowTempStaRe(CTS_nInvalid);
    IPL_vWriteEnBlowSpdSta(CTS_nInvalid);
    IPL_vWriteEnSunSta(CTS_nInvalid);
    IPL_vWriteEnSunLoadHeatSta(CTS_nInvalid);
    IPL_vWriteEnVelEngineHeatSta(CTS_nInvalid);
    IPL_vWriteEnPcbTempSta(CTS_nInvalid); 
}


/***************************************************************************************************
  Function   : IPL_vMain                                                      
                           
  Description: Main function of IPL. This function is called in the cyclic background task in the 
               ON status. 
            
  Arguments  : None
  
  Returns    : None 
***************************************************************************************************/

void IPL_vMain(void)
{
    if (IPL_u8TaskCtr == 0U)
    {
        IPL_vSensorIctOutput();
        IPL_u8TaskCtr = 1U;
    }
    if (IPL_u8TaskCtr == 1U)
    {
        IPL_vAirdModeOutput();
        IPL_u8TaskCtr = 2U;
    }
    else if (IPL_u8TaskCtr == 2U)
    {
        IPL_vEvapTempOutput();
        IPL_u8TaskCtr = 3U;
    }
    else if (IPL_u8TaskCtr == 3U)
    {
        IPL_vHctOutput();
        IPL_u8TaskCtr = 4U;
    } 
    else if (IPL_u8TaskCtr == 4U)
    {   
        IPL_vBlowTempOutput();
        IPL_u8TaskCtr = 5U;
    }
    else if (IPL_u8TaskCtr == 5U) 
    {
        IPL_vBlowSpdOutput();
        IPL_u8TaskCtr = 6U;    
    }
    else if (IPL_u8TaskCtr == 6U)
    {
        IPL_vSunOutput();
        IPL_u8TaskCtr = 7U;
    }
    else if (IPL_u8TaskCtr == 7U)
    {
        IPL_vSunLoadHeatOutput();
        IPL_u8TaskCtr = 8U;
    }
    else if (IPL_u8TaskCtr == 8U)
    { 
        IPL_vVelEngineHeatOutput();
        IPL_u8TaskCtr = 9U;
    }
    else 
    {   
        IPL_vPcbTempOutput();
        IPL_u8TaskCtr = 0U;
    }
}


/***************************************************************************************************
  Function   : IPL_vSensorIctOutput       
                           
  Description: This function is used to process sensor ICT output.
                                
  Arguments  : None
  
  Returns    : None
***************************************************************************************************/

static void IPL_vSensorIctOutput(void)
{
    IPL_tstCalcSensorIctIn stCalcSensorIctIn;
    IPL_tstSensorIct stSensorIct;
    IPL_tstSensorIctFlIn stSensorIctFlIn;
    IPL_tstSensorIctFl stSensorIctFlOut;
    IPL_tstUpdateSensorIctFlIn stUpdateSensorIctFlIn; 
    CTS_tenValidSta enNatsIctSta;
    cuint16 u16NatsIct;

    stCalcSensorIctIn.enSensorIctAdSta = IPL_enSensorIctAdImport(&stCalcSensorIctIn.u16SensorIctAd);
    stCalcSensorIctIn.u16StableWaitTime = IPL_u16IctStableWaitTime;
    IPL_vCalcSensorIct(&stCalcSensorIctIn, &stSensorIct);

    IPL_u16IctStableWaitTime = stSensorIct.u16StableWaitTime;

    enNatsIctSta = IPL_enNatsValueImport(&u16NatsIct);

    if (enNatsIctSta == CTS_nValid)
    {
        stSensorIct.enSensorIctSta = enNatsIctSta;
        stSensorIct.u16SensorIct = u16NatsIct;
    }

    stSensorIctFlIn.pstSensorIct = &stSensorIct;
    stSensorIctFlIn.pstSensorIctFl = &IPL_stSensorIctFl;
    stSensorIctFlIn.enSensorIctFlFactorSta = CTS_nValid;
    stSensorIctFlIn.u16SensorIctFlFactor = CTS_stSensorIctChg.u16Const;
    stSensorIctFlIn.u8SensorIctFlShift = CTS_stSensorIctChgBase.u8Const;
    IPL_vSensorIctFl(&stSensorIctFlIn, &stSensorIctFlOut);

    stUpdateSensorIctFlIn.pstInputAddress = &stSensorIctFlOut;
    stUpdateSensorIctFlIn.pstUpdateAddress = &IPL_stSensorIctFl;
    IPL_vUpdateSensorIctFl(&stUpdateSensorIctFlIn);
         
    IPL_vWriteEnSensorIctSta(stSensorIctFlOut.enSensorIctSta);
    IPL_vWriteU16SensorIct(stSensorIctFlOut.u16SensorIct);
}


/***************************************************************************************************
  Function   : IPL_vAirdModeOutput       
                           
  Description: This function is used to process AIRD mode output.
                                
  Arguments  : None
  
  Returns    : None
***************************************************************************************************/

static void IPL_vAirdModeOutput(void)
{
    IPL_tstCalcAirdModeIn stCalcAirdModeIn;
    IPL_tstAirdMode stAirdMode;
    
    stCalcAirdModeIn.enAirdPosSta = IPL_enAirdPosImport(&stCalcAirdModeIn.u16AirdPos);
    IPL_vCalcAirdMode(&stCalcAirdModeIn, &stAirdMode);

    IPL_vWriteU8AirdMode(stAirdMode.u8AirdMode);
    IPL_vWriteEnAirdModeSta(stAirdMode.enAirdModeSta);
}


/***************************************************************************************************
  Function   : IPL_vEvapTempOutput       
                           
  Description: This function is used to process EVAP temperature output.
                                
  Arguments  : None
  
  Returns    : None
***************************************************************************************************/

static void IPL_vEvapTempOutput(void)
{
    IPL_tstCalcEvapTempIn stCalcEvapTempIn;
    IPL_tstCalcEvapTempOfsIn stCalcEvapTempOfsIn;
    IPL_tstCalcCompOffEvapTempIn stCalcCompOffEvapTempIn;
    IPL_tstEvapTemp stEvapTemp;
    IPL_tstEvapTempFlIn stEvapTempFlIn;
    IPL_tstEvapTempFl stEvapTempFlOut;
    IPL_tstUpdateEvapTempFlIn stUpdateEvapTempFlIn; 

    stCalcEvapTempOfsIn.enRfaPosSta = IPL_enRfaPosImport(&stCalcEvapTempOfsIn.u16RfaPos);
    stCalcEvapTempOfsIn.enOatSta = IPL_enOatImport(&stCalcEvapTempOfsIn.u16Oat);
    stCalcEvapTempOfsIn.enCabinTempSta = IPL_enCabinTempImport(&stCalcEvapTempOfsIn.u16CabinTemp);
    stCalcEvapTempOfsIn.enBlwrVoltSta = IPL_enBlwrVoltImport(&stCalcEvapTempOfsIn.u16BlwrVolt);

    stCalcCompOffEvapTempIn.enRfaPosSta = IPL_enRfaPosImport(&stCalcCompOffEvapTempIn.u16RfaPos);
    stCalcCompOffEvapTempIn.enOatSta = IPL_enOatImport(&stCalcCompOffEvapTempIn.u16Oat);
    stCalcCompOffEvapTempIn.enCabinTempSta = IPL_enCabinTempImport(&stCalcCompOffEvapTempIn.u16CabinTemp);

    stCalcEvapTempIn.enRawEvapTempSta = IPL_enRawEvapTempImport(&stCalcEvapTempIn.u16RawEvapTemp);
    stCalcEvapTempIn.enCompValidSta = IPL_enCompOnOffStaImport(&stCalcEvapTempIn.enCompOnOffSta);
    stCalcEvapTempIn.pstCalcEvapTempOfsIn = &stCalcEvapTempOfsIn;
    stCalcEvapTempIn.pstCalcCompOffEvapTempIn = &stCalcCompOffEvapTempIn;
    IPL_vCalcEvapTemp(&stCalcEvapTempIn, &stEvapTemp);

    stEvapTempFlIn.pstEvapTemp = &stEvapTemp;
    stEvapTempFlIn.pstEvapTempFl = &IPL_stEvapTempFl;
    stEvapTempFlIn.enEvapTempFlFactorSta = CTS_nValid;
    stEvapTempFlIn.u16EvapTempFlFactor = CTS_stEvapTempChg.u16Const;
    stEvapTempFlIn.u8EvapTempFlShift = CTS_stEvapTempChgBase.u8Const;   
    IPL_vEvapTempFl(&stEvapTempFlIn, &stEvapTempFlOut);

    stUpdateEvapTempFlIn.pstInputAddress = &stEvapTempFlOut;
    stUpdateEvapTempFlIn.pstUpdateAddress = &IPL_stEvapTempFl;
    IPL_vUpdateEvapTempFl(&stUpdateEvapTempFlIn);
        
    IPL_vWriteEnEvapTempSta(stEvapTempFlOut.enEvapTempSta);
    IPL_vWriteU16EvapTemp(stEvapTempFlOut.u16EvapTemp);
}


/***************************************************************************************************
  Function   : IPL_vHctOutput       
                           
  Description: This function is used to process HCT output.
                                
  Arguments  : None
  
  Returns    : None
***************************************************************************************************/

static void IPL_vHctOutput(void)
{
    CTS_tenValidSta enRawHctSta, enBlwrVoltSta;
    cuint16 u16RawHct, u16BlwrVolt, u16PumpOnFlFactor, u16PumpOffFlFactor;
    IPL_tstHctFlIn stHctFlIn;
    IPL_tstHctFl stHctFlOut;
    IPL_tstUpdateHctFlIn stUpdateHctFlIn;

    enRawHctSta = IPL_enRawHctImport(&u16RawHct);
    enBlwrVoltSta = IPL_enBlwrVoltImport(&u16BlwrVolt);

    u16PumpOnFlFactor = CTS_u16Lookup1D_Limit(u16RawHct, CTS_stPumpOnHctChg.u8SizeX, 
                        CTS_stPumpOnHctChg.pu16TableX, CTS_stPumpOnHctChg.pu16TableY);

    u16PumpOffFlFactor = CTS_u16Lookup1D_Limit(u16BlwrVolt, CTS_stPumpOffHctChg.u8SizeX, 
                         CTS_stPumpOffHctChg.pu16TableX, CTS_stPumpOffHctChg.pu16TableY);

    stHctFlIn.enHeaterPumpValidSta = IPL_enHeaterPumpOnOffStaImport(&stHctFlIn.enHeaterPumpOnOffSta);
    stHctFlIn.enEvapTempSta = IPL_enReadEvapTempSta();
    stHctFlIn.u16EvapTemp = IPL_u16ReadEvapTemp();
    stHctFlIn.enRawHctSta = IPL_enRawHctImport(&stHctFlIn.u16RawHct);
    stHctFlIn.pstHctFl = &IPL_stHctFl;
    stHctFlIn.enPumpOnFlFactorSta = enRawHctSta;
    stHctFlIn.u16PumpOnFlFactor = u16PumpOnFlFactor;
    stHctFlIn.enPumpOffFlFactorSta = enBlwrVoltSta;
    stHctFlIn.u16PumpOffFlFactor = u16PumpOffFlFactor;
    stHctFlIn.u8HctFlShift = CTS_stHctChgBase.u8Const;
    IPL_vHctFl(&stHctFlIn, &stHctFlOut);

    stUpdateHctFlIn.pstInputAddress = &stHctFlOut;
    stUpdateHctFlIn.pstUpdateAddress = &IPL_stHctFl;
    IPL_vUpdateHctFl(&stUpdateHctFlIn);

    IPL_vWriteU16Hct(stHctFlOut.u16Hct);
    IPL_vWriteEnHctSta(stHctFlOut.enHctSta);   
}


/***************************************************************************************************
  Function   : IPL_vBlowTempOutput       
                           
  Description: This function is used to process blowout temperature output.
                                
  Arguments  : None
  
  Returns    : None
***************************************************************************************************/

static void IPL_vBlowTempOutput(void)
{
    IPL_tstCalcLimitMacRtoIn stCalcLimitMacRtoIn;
    IPL_tstLimitMacRto stLimitMacRtoL, stLimitMacRtoR, stLimitMacRtoRe;
    IPL_tstCalcRawBlowTempIn stCalcRawBlowTempInL, stCalcRawBlowTempInR, stCalcRawBlowTempInRe;
    IPL_tstCalcBlowTempIn stCalcBlowTempIn;
    IPL_tstBlowTemp stBlowTempL, stBlowTempR, stBlowTempRe;
    CTS_tenValidSta enExBlowTempStaL, enExBlowTempStaR, enExBlowTempStaRe;
    cuint16 u16ExBlowTempL, u16ExBlowTempR, u16ExBlowTempRe;
    cbool boUseExBlowTempL = IPL_boUseExBlowTempL();
    cbool boUseExBlowTempR = IPL_boUseExBlowTempR();
    cbool boUseExBlowTempRe = IPL_boUseExBlowTempRe();
    
    stCalcLimitMacRtoIn.enAirdModeSta = IPL_enReadAirdModeSta();
    stCalcLimitMacRtoIn.u8AirdMode = IPL_u8ReadAirdMode();
    stCalcLimitMacRtoIn.enBlwrVoltSta = IPL_enBlwrVoltImport(&stCalcLimitMacRtoIn.u16BlwrVolt);
    IPL_vCalcLimitMacRtoL(&stCalcLimitMacRtoIn, &stLimitMacRtoL);
    IPL_vCalcLimitMacRtoR(&stCalcLimitMacRtoIn, &stLimitMacRtoR);
    IPL_vCalcLimitMacRtoRe(&stCalcLimitMacRtoIn, &stLimitMacRtoRe);

    stCalcRawBlowTempInL.enEvapTempSta = IPL_enReadEvapTempSta();
    stCalcRawBlowTempInL.u16EvapTemp = IPL_u16ReadEvapTemp();
    stCalcRawBlowTempInL.enHctSta = IPL_enReadHctSta();
    stCalcRawBlowTempInL.u16Hct = IPL_u16ReadHct(); 
    stCalcRawBlowTempInL.enTgtBlowTempSta = IPL_enTgtBlowTempLImport(&stCalcRawBlowTempInL.u16TgtBlowTemp);
    stCalcRawBlowTempInL.enHiLoValidSta = IPL_enMacHiLoStaLImport(&stCalcRawBlowTempInL.enHiLoSta); 
    stCalcRawBlowTempInL.pstLimitMacRto = &stLimitMacRtoL; 

    stCalcRawBlowTempInR.enEvapTempSta = IPL_enReadEvapTempSta();
    stCalcRawBlowTempInR.u16EvapTemp = IPL_u16ReadEvapTemp();
    stCalcRawBlowTempInR.enHctSta = IPL_enReadHctSta();
    stCalcRawBlowTempInR.u16Hct = IPL_u16ReadHct(); 
    stCalcRawBlowTempInR.enTgtBlowTempSta = IPL_enTgtBlowTempRImport(&stCalcRawBlowTempInR.u16TgtBlowTemp);
    stCalcRawBlowTempInR.enHiLoValidSta = IPL_enMacHiLoStaRImport(&stCalcRawBlowTempInR.enHiLoSta);
    stCalcRawBlowTempInR.pstLimitMacRto = &stLimitMacRtoR;

    stCalcRawBlowTempInRe.enEvapTempSta = IPL_enReadEvapTempSta();
    stCalcRawBlowTempInRe.u16EvapTemp = IPL_u16ReadEvapTemp();
    stCalcRawBlowTempInRe.enHctSta = IPL_enReadHctSta();
    stCalcRawBlowTempInRe.u16Hct = IPL_u16ReadHct(); 
    stCalcRawBlowTempInRe.enTgtBlowTempSta = IPL_enTgtBlowTempReImport(&stCalcRawBlowTempInRe.u16TgtBlowTemp);
    stCalcRawBlowTempInRe.enHiLoValidSta = IPL_enMacHiLoStaReImport(&stCalcRawBlowTempInRe.enHiLoSta);
    stCalcRawBlowTempInRe.pstLimitMacRto = &stLimitMacRtoRe;

    stCalcBlowTempIn.pstCalcRawBlowTempIn = &stCalcRawBlowTempInL;
    stCalcBlowTempIn.pstBlowTempFl = &IPL_stBlowTempFlL;
    stCalcBlowTempIn.enBlowTempFlFactorSta = CTS_nValid;
    stCalcBlowTempIn.u16BlowTempFlFactor = CTS_stBlowTempChg.u16Const;
    stCalcBlowTempIn.u8BlowTempFlShift = CTS_stBlowTempChgBase.u8Const;
    stCalcBlowTempIn.pstBlowTempFlUpdateAdd = &IPL_stBlowTempFlL;
    IPL_vCalcBlowTemp(&stCalcBlowTempIn, &stBlowTempL);

    stCalcBlowTempIn.pstCalcRawBlowTempIn = &stCalcRawBlowTempInR;
    stCalcBlowTempIn.pstBlowTempFl = &IPL_stBlowTempFlR;
    stCalcBlowTempIn.pstBlowTempFlUpdateAdd = &IPL_stBlowTempFlR;
    IPL_vCalcBlowTemp(&stCalcBlowTempIn, &stBlowTempR);

    stCalcBlowTempIn.pstCalcRawBlowTempIn = &stCalcRawBlowTempInRe;
    stCalcBlowTempIn.pstBlowTempFl = &IPL_stBlowTempFlRe;
    stCalcBlowTempIn.pstBlowTempFlUpdateAdd = &IPL_stBlowTempFlRe;
    IPL_vCalcBlowTemp(&stCalcBlowTempIn, &stBlowTempRe);
    
    IPL_vWriteEnBlowTempStaL(stBlowTempL.enBlowTempSta);
    IPL_vWriteU16BlowTempL(stBlowTempL.u16BlowTemp);
    IPL_vWriteEnBlowTempStaR(stBlowTempR.enBlowTempSta);
    IPL_vWriteU16BlowTempR(stBlowTempR.u16BlowTemp);
    IPL_vWriteEnBlowTempStaRe(stBlowTempRe.enBlowTempSta);
    IPL_vWriteU16BlowTempRe(stBlowTempRe.u16BlowTemp);

    enExBlowTempStaL = IPL_enExBlowTempLImport(&u16ExBlowTempL);
    enExBlowTempStaR = IPL_enExBlowTempRImport(&u16ExBlowTempR);
    enExBlowTempStaRe = IPL_enExBlowTempReImport(&u16ExBlowTempRe);

    if ((boUseExBlowTempL==CTS_True) && (enExBlowTempStaL==CTS_nValid))
    {
        IPL_vWriteEnBlowTempStaL(CTS_nValid);
        IPL_vWriteU16BlowTempL(u16ExBlowTempL);
    }

    if ((boUseExBlowTempR==CTS_True) && (enExBlowTempStaR==CTS_nValid))
    {
        IPL_vWriteEnBlowTempStaR(CTS_nValid);
        IPL_vWriteU16BlowTempR(u16ExBlowTempR);
    }

    if ((boUseExBlowTempRe==CTS_True) && (enExBlowTempStaRe==CTS_nValid))
    {
        IPL_vWriteEnBlowTempStaRe(CTS_nValid);
        IPL_vWriteU16BlowTempRe(u16ExBlowTempRe);
    }
}


/***************************************************************************************************
  Function   : IPL_vBlowSpdOutput       
                           
  Description: This function is used to process blowout speed output.
                                
  Arguments  : None
  
  Returns    : None
***************************************************************************************************/

static void IPL_vBlowSpdOutput(void)
{
    IPL_tstCalcBlowSpdIn stCalcBlowSpdIn;
    IPL_tstBlowSpd stBlowSpd;

    stCalcBlowSpdIn.enVelocitySta = IPL_enVelocityImport(&stCalcBlowSpdIn.u16Velocity);
    stCalcBlowSpdIn.enRfaPosSta = IPL_enRfaPosImport(&stCalcBlowSpdIn.u16RfaPos);
    stCalcBlowSpdIn.enBlwrVoltSta = IPL_enBlwrVoltImport(&stCalcBlowSpdIn.u16BlwrVolt);
    
    IPL_vCalcBlowSpd(&stCalcBlowSpdIn, &stBlowSpd);
    
    if (stBlowSpd.enBlowSpdSta == CTS_nValid)
    {
        IPL_vWriteU16BlowSpd(stBlowSpd.u16BlowSpd);
        IPL_vWriteEnBlowSpdSta(CTS_nValid);
    }
    else
    {
        IPL_vWriteU16BlowSpd(0U);
        IPL_vWriteEnBlowSpdSta(CTS_nInvalid);
    }
}


/***************************************************************************************************
  Function   : IPL_vSunOutput       
                           
  Description: This function is used to process sun output.
                                
  Arguments  : None
  
  Returns    : None
***************************************************************************************************/

static void IPL_vSunOutput(void)
{
    IPL_tstCalcSunIn stCalcSunIn;
    IPL_tstSun stSun;

    stCalcSunIn.enRawSuntStaL = IPL_enRawSunLImport(&stCalcSunIn.u16RawSunL);
    stCalcSunIn.enRawSuntStaR = IPL_enRawSunRImport(&stCalcSunIn.u16RawSunR);
    IPL_vCalcSun(&stCalcSunIn, &stSun);
    
    IPL_vWriteEnSunSta(stSun.enSunSta);
    IPL_vWriteU16Sun(stSun.u16Sun);
}


/***************************************************************************************************
  Function   : IPL_vSunLoadHeatOutput       
                           
  Description: This function is used to process sun load heat output.
                                
  Arguments  : None
  
  Returns    : None
***************************************************************************************************/

static void IPL_vSunLoadHeatOutput(void)
{
    IPL_tstCalcSunLoadHeatIn stCalcSunLoadHeatIn;
    IPL_tstSunLoadHeat stSunLoadHeat;

    stCalcSunLoadHeatIn.enSunSta = IPL_enReadSunSta();
    stCalcSunLoadHeatIn.u16Sun = IPL_u16ReadSun();
    stCalcSunLoadHeatIn.enOatSta = IPL_enOatImport(&stCalcSunLoadHeatIn.u16Oat);
    IPL_vCalcSunLoadHeat(&stCalcSunLoadHeatIn, &stSunLoadHeat);

    if (stSunLoadHeat.enSunLoadHeatSta == CTS_nValid)
    {
        IPL_vWriteU16SunLoadHeat(stSunLoadHeat.u16SunLoadHeat);
        IPL_vWriteEnSunLoadHeatSta(CTS_nValid);
    }
    else
    {
        IPL_vWriteU16SunLoadHeat(CTS_stThermalRelativeZero.u16Const);
        IPL_vWriteEnSunLoadHeatSta(CTS_nInvalid);
    }
}


/***************************************************************************************************
  Function   : IPL_vVelEngineHeatOutput       
                           
  Description: This function is used to process the engine heat in different velocity and air  
               leaking heat caused by velocity output.
                                
  Arguments  : None
  
  Returns    : None
***************************************************************************************************/

static void IPL_vVelEngineHeatOutput(void)
{
    IPL_tstCalcVelEngineHeatIn stCalcVelEngineHeatIn;
    IPL_tstVelEngineHeat stVelEngineHeat;

    stCalcVelEngineHeatIn.enVelocitySta = IPL_enVelocityImport(&stCalcVelEngineHeatIn.u16Velocity);
    stCalcVelEngineHeatIn.enOatSta = IPL_enOatImport(&stCalcVelEngineHeatIn.u16Oat);
    stCalcVelEngineHeatIn.enFuelModeValidSta = IPL_enFuelModeStaImport(&stCalcVelEngineHeatIn.boInFuelMode);
    stCalcVelEngineHeatIn.enElecModeValidSta = IPL_enElecModeStaImport(&stCalcVelEngineHeatIn.boInElecMode);
    IPL_vCalcVelEngineHeat(&stCalcVelEngineHeatIn, &stVelEngineHeat);

    if (stVelEngineHeat.enVelEngineHeatSta == CTS_nValid)
    {
        IPL_vWriteU16VelEngineHeat(stVelEngineHeat.u16VelEngineHeat);
        IPL_vWriteEnVelEngineHeatSta(CTS_nValid);
    }
    else
    {
        IPL_vWriteU16VelEngineHeat(CTS_stThermalRelativeZero.u16Const);
        IPL_vWriteEnVelEngineHeatSta(CTS_nInvalid);
    }
}


/***************************************************************************************************
  Function   : IPL_vPcbTempOutput       
                           
  Description: This function is used to process PCB temperature output.
                                
  Arguments  : None
  
  Returns    : None
***************************************************************************************************/

static void IPL_vPcbTempOutput(void)
{
    IPL_tstCalcPcbTempIn stCalcPcbTempIn;
    IPL_tstPcbTemp stPcbTemp;

    stCalcPcbTempIn.enPcbTempAdSta = IPL_enPcbTempAdImport(&stCalcPcbTempIn.u16PcbTempAd);
    stCalcPcbTempIn.u16StableWaitTime = IPL_u16PcbTempStableWaitTime;    
    IPL_vCalcPcbTemp(&stCalcPcbTempIn, &stPcbTemp);

    IPL_u16PcbTempStableWaitTime = stPcbTemp.u16StableWaitTime;

    IPL_vWriteU16PcbTemp(stPcbTemp.u16PcbTemp);
    IPL_vWriteEnPcbTempSta(stPcbTemp.enPcbTempSta);
}


/***************************************************************************************************
  Function   : IPL_vCalcSensorIct                                               
                           
  Description: This function is used to calculate the sensor in-car temperature.
            
  Arguments  : pstInput         - is the address of input structure. 
                                    - enSensorIctAdSta: The valid status of sensor ICT AD value.
                                    - u16SensorIctAd: The sensor ICT AD value.
                                    - u16StableWaitTime: Time to wait sensor to become stable.   
                                    
               pstOutput        - is the address of output structure.
                                    - enSensorIctSta: The valid status of sensor ICT.
                                    - u16StableWaitTime: Time to wait sensor to become stable.
                                    - u16SensorIct: The sensor ICT output.
  
  Returns    : None
***************************************************************************************************/

static void IPL_vCalcSensorIct(IPL_tstCalcSensorIctIn *pstInput, IPL_tstSensorIct *pstOutput)
{
    if (pstInput->enSensorIctAdSta == CTS_nValid) 
    {
        if (pstInput->u16StableWaitTime < CTS_stSensorIctStableWaitTime.u16Const)
        {
            pstOutput->u16StableWaitTime = pstInput->u16StableWaitTime + 1U;
            pstOutput->enSensorIctSta = CTS_nInvalid;
        }
        else
        {
            pstOutput->u16SensorIct = CTS_u16Lookup1D_Limit(pstInput->u16SensorIctAd, 
                                      CTS_stSensorIct.u8SizeX, CTS_stSensorIct.pu16TableX, 
                                      CTS_stSensorIct.pu16TableY);

            pstOutput->u16StableWaitTime = CTS_stSensorIctStableWaitTime.u16Const;
            pstOutput->enSensorIctSta = CTS_nValid;
        }
    }
    else
    {
        pstOutput->u16StableWaitTime = 0U;
        pstOutput->enSensorIctSta = CTS_nInvalid;
    }
}


/***************************************************************************************************
  Function   : IPL_vCalcSensorIct                                               
                           
  Description: This function is used to filter the sensor in-car temperature.
            
  Arguments  : pstInput         - is the address of input structure. 
                                    - pstSensorIct: The address of sensor ICT variable.
                                    - pstSensorIctFl: The address of sensor ICT filter variable.
                                    - enSensorIctFlFactorSta: The valid status of sensor ICT filter 
                                                              factor.
                                    - u16SensorIctFlFactor: The filter factor of sensor ICT.
                                    - u8SensorIctFlShift: The filter shift of sensor ICT.
                                    
               pstOutput        - is the address of output structure.
                                    - enFlInitValSta: The initial filter value status.
                                    - enSensorIctSta: The valid status of sensor ICT.
                                    - u32SensorIct: The 32-bit sensor ICT.
                                    - u16SensorIct: The 16-bit sensor ICT.
  
  Returns    : None
***************************************************************************************************/

static void IPL_vSensorIctFl(IPL_tstSensorIctFlIn *pstInput, IPL_tstSensorIctFl *pstOutput)
{
    IPL_tstUpdateSensorIctFlIn stUpdateSensorIctFlIn;  
    IPL_tstSensorIctFl stSensorIctFl;

    stUpdateSensorIctFlIn.pstInputAddress = pstInput->pstSensorIctFl;
    stUpdateSensorIctFlIn.pstUpdateAddress = &stSensorIctFl;
    IPL_vUpdateSensorIctFl(&stUpdateSensorIctFlIn);
        
    if ((*pstInput->pstSensorIct).enSensorIctSta == CTS_nValid) 
    {
        if ((*pstInput->pstSensorIctFl).enFlInitValSta == CTS_nInvalid)
        {
            stSensorIctFl.enFlInitValSta = CTS_nValid;
            stSensorIctFl.enSensorIctSta = CTS_nValid;
            
            stSensorIctFl.u32SensorIct = (cuint32)(*pstInput->pstSensorIct).u16SensorIct
                                         << pstInput->u8SensorIctFlShift;

            stSensorIctFl.u16SensorIct = (*pstInput->pstSensorIct).u16SensorIct;
        }
        else
        {
            if (pstInput->enSensorIctFlFactorSta == CTS_nValid)
            {
                stSensorIctFl.enSensorIctSta = CTS_nValid;
                
                stSensorIctFl.u32SensorIct = CTS_u32FirstOrderFilter(
                                             (*pstInput->pstSensorIctFl).u32SensorIct,  
                                             (*pstInput->pstSensorIct).u16SensorIct, 
                                             pstInput->u16SensorIctFlFactor, 
                                             pstInput->u8SensorIctFlShift);

                stSensorIctFl.u16SensorIct = CTS_u16U32ToU16(stSensorIctFl.u32SensorIct
                                             >> pstInput->u8SensorIctFlShift);
            }
            else
            {
                stSensorIctFl.enSensorIctSta = CTS_nInvalid;
            }
        }
    }
    else
    {
        stSensorIctFl.enSensorIctSta = CTS_nInvalid;
    }

    stUpdateSensorIctFlIn.pstInputAddress = &stSensorIctFl;
    stUpdateSensorIctFlIn.pstUpdateAddress = pstOutput;    
    IPL_vUpdateSensorIctFl(&stUpdateSensorIctFlIn);
}


/*************************************************************************************************** 
  Function   : IPL_vCalcAirdMode                         
                       
  Description: This function is used to calculate the AIRD mode.
                                                                           
  Arguments  : pstInput         - is the address of input structure. 
                                    - enAirdPosSta: The valid status of AIRD position.
                                    - u16AirdPos: The AIRD position.
                                    
               pstOutput        - is the address of output structure.
                                    - enAirdModeSta: The valid status of AIRD mode.
                                    - u8AirdMode: The AIRD mode output.   
  
  Returns    : None
***************************************************************************************************/

static void IPL_vCalcAirdMode(IPL_tstCalcAirdModeIn *pstInput, IPL_tstAirdMode *pstOutput)
{
    if (pstInput->enAirdPosSta == CTS_nValid)
    { 
        pstOutput->u8AirdMode = CTS_u8GetU16ClosestEntry(CTS_stAirdModePos.pu16Array, 
                                CTS_stAirdModePos.u8Size, pstInput->u16AirdPos);
        
        pstOutput->enAirdModeSta = CTS_nValid;
    }
    else
    {
        pstOutput->enAirdModeSta = CTS_nInvalid;
    }
}


/***************************************************************************************************
  Function   : IPL_vCalcEvapTemp                                               
                           
  Description: This function is used to calculate the EVAP temperature.
            
  Arguments  : pstInput         - is the address of input structure. 
                                    - enRawEvapTempSta: The valid status of raw EVAP temperature.
                                    - u16RawEvapTemp: The raw EVAP temperature.
                                    - enCompValidSta: The valid status of compressor status.
                                    - enCompOnOffSta: The compressor on/off status.
                                    - pstCalcEvapTempOfsIn: The address of EVAP temperature offset
                                                            calculation input structure.
                                    - pstCalcCompOffEvapTempIn: The address of compressor off EVAP 
                                                                temperature calculation input 
                                                                structure.
                                    
               pstOutput        - is the address of output structure.
                                    - enEvapTempSta: The valid status of EVAP temperature.
                                    - u16EvapTemp: The EVAP temperature output.   
  
  Returns    : None
***************************************************************************************************/

static void IPL_vCalcEvapTemp(IPL_tstCalcEvapTempIn *pstInput, IPL_tstEvapTemp *pstOutput)
{
    IPL_tstEvapTempOfs stEvapTempOfs;
    cint32 i32EvapTemp;
    IPL_tstCompOffEvapTemp stCompOffEvapTemp;
    
    if (pstInput->enRawEvapTempSta == CTS_nValid)
    {
        IPL_vCalcEvapTempOfs(pstInput->pstCalcEvapTempOfsIn, &stEvapTempOfs);
        
        if ((pstInput->enCompValidSta==CTS_nValid) && (pstInput->enCompOnOffSta==CTS_nOn) 
             && (stEvapTempOfs.enEvapTempOfsSta==CTS_nValid))
        {
            i32EvapTemp = (cint32)pstInput->u16RawEvapTemp;
            i32EvapTemp += (cint32)stEvapTempOfs.u16EvapTempOfs;
            i32EvapTemp -= (cint32)CTS_stThermalRelativeZero.u16Const;
            
            pstOutput->u16EvapTemp = CTS_u16I32ToU16(i32EvapTemp, 0);
        }
        else
        {
            pstOutput->u16EvapTemp = pstInput->u16RawEvapTemp;
        }

        pstOutput->enEvapTempSta = CTS_nValid;
    }
    else
    {
        if ((pstInput->enCompValidSta==CTS_nValid) && (pstInput->enCompOnOffSta==CTS_nOff))
        {
            IPL_vCalcCompOffEvapTemp(pstInput->pstCalcCompOffEvapTempIn, &stCompOffEvapTemp);
            
            pstOutput->u16EvapTemp = stCompOffEvapTemp.u16CompOffEvapTemp;
            pstOutput->enEvapTempSta = stCompOffEvapTemp.enCompOffEvapTempSta;
        }
        else
        {
            pstOutput->enEvapTempSta = CTS_nInvalid;
        }
    }
}


/***************************************************************************************************
  Function   : IPL_vCalcEvapTempOfs                                               
                           
  Description: This function is used to calculate the EVAP temperature offset.
            
  Arguments  : pstInput         - is the address of input structure. 
                                    - enRfaPosSta: The valid status of R/F air flap position.
                                    - u16RfaPos: The R/F air flap position.
                                    - enOatSta: The valid status of OAT.
                                    - u16Oat: The OAT.
                                    - enCabinTempSta: The valid status of cabin temperature.
                                    - u16CabinTemp: The cabin temperature.
                                    - enBlwrVoltSta: The valid status of blower voltage.
                                    - u16BlwrVolt: The blower voltage.
                                    
               pstOutput        - is the address of output structure.
                                    - enEvapTempOfsSta: The valid status of EVAP temperature.
                                    - u16EvapTempOfs: The EVAP temperature offset.
  
  Returns    : None
***************************************************************************************************/

static void IPL_vCalcEvapTempOfs(IPL_tstCalcEvapTempOfsIn *pstInput, IPL_tstEvapTempOfs *pstOutput)
{
    cuint16 u16RfaPos, u16RfaFreshRto, u16EvapFreshOfs, u16EvapRecircOfs;
    cint32 i32RfaRecircRatio;
    cuint32 u32EvapTempOfs;

    if (pstInput->enRfaPosSta == CTS_nValid)
    {
        u16RfaPos = pstInput->u16RfaPos;
    }
    else
    {
        u16RfaPos = CTS_stDefRfaPos.u16Const;
    }
        
    u16RfaFreshRto = CTS_u16Lookup1D_Limit(u16RfaPos, CTS_stRfaFreshRto.u8SizeX, 
                     CTS_stRfaFreshRto.pu16TableX, CTS_stRfaFreshRto.pu16TableY);

    i32RfaRecircRatio = (cint32)CTS_stRfaFreshRtoBase.u16Const - (cint32)u16RfaFreshRto;
    i32RfaRecircRatio = (cint32)CTS_u16I32ToU16(i32RfaRecircRatio, 0);

    if ((pstInput->enOatSta==CTS_nValid) && (pstInput->enCabinTempSta==CTS_nValid) 
        && (pstInput->enBlwrVoltSta==CTS_nValid))
    {
        u16EvapFreshOfs = CTS_u16Lookup2D_Limit(pstInput->u16Oat, pstInput->u16BlwrVolt, 
                          CTS_stEvapFreshOfs.u8SizeX, CTS_stEvapFreshOfs.u8SizeY, 
                          CTS_stEvapFreshOfs.pu16TableX, CTS_stEvapFreshOfs.pu16TableY, 
                          CTS_stEvapFreshOfs.pu16TableZ);

        u16EvapRecircOfs = CTS_u16Lookup2D_Limit(pstInput->u16CabinTemp, pstInput->u16BlwrVolt, 
                           CTS_stEvapRecircOfs.u8SizeX, CTS_stEvapRecircOfs.u8SizeY, 
                           CTS_stEvapRecircOfs.pu16TableX, CTS_stEvapRecircOfs.pu16TableY, 
                           CTS_stEvapRecircOfs.pu16TableZ);
 
        u32EvapTempOfs = (cuint32)u16EvapFreshOfs * (cuint32)u16RfaFreshRto;
        u32EvapTempOfs += (cuint32)u16EvapRecircOfs * (cuint32)i32RfaRecircRatio;
        u32EvapTempOfs /= (cuint32)CTS_stRfaFreshRtoBase.u16Const;

        pstOutput->u16EvapTempOfs = CTS_u16U32ToU16(u32EvapTempOfs); 
        pstOutput->enEvapTempOfsSta = CTS_nValid;
    }
    else
    {
        pstOutput->enEvapTempOfsSta = CTS_nInvalid;
    }
}


/***************************************************************************************************
  Function   : IPL_vCalcCompOffEvapTemp                                               
                           
  Description: This function is used to calculate the evaporator temperature when the compressor 
               off.
            
  Arguments  : pstInput         - is the address of input structure. 
                                    - enRfaPosSta: The valid status of R/F air flap position.
                                    - u16RfaPos: The R/F air flap position.
                                    - enOatSta: The valid status of OAT.
                                    - u16Oat: The OAT.
                                    - enCabinTempSta: The valid status of cabin temperature.
                                    - u16CabinTemp: The cabin temperature.
                                    
               pstOutput        - is the address of output structure.
                                    - enCompOffEvapTempSta: The valid status of compressor off EVAP
                                                            temperature.
                                    - u16CompOffEvapTemp: The compressor off EVAP temperature.
  
  Returns    : None
***************************************************************************************************/

static void IPL_vCalcCompOffEvapTemp(IPL_tstCalcCompOffEvapTempIn *pstInput, IPL_tstCompOffEvapTemp *pstOutput)
{
    cuint16 u16RfaPos, u16RfaFreshRto;
    cint32 i32RfaRecircRatio;
    cuint32 u32EvapTemp;

    if (pstInput->enRfaPosSta == CTS_nValid)
    {
        u16RfaPos = pstInput->u16RfaPos; 
    }
    else
    {
        u16RfaPos = CTS_stDefRfaPos.u16Const;
    }
        
    u16RfaFreshRto = CTS_u16Lookup1D_Limit(u16RfaPos, CTS_stRfaFreshRto.u8SizeX, 
                     CTS_stRfaFreshRto.pu16TableX, CTS_stRfaFreshRto.pu16TableY);

    i32RfaRecircRatio = (cint32)CTS_stRfaFreshRtoBase.u16Const - (cint32)u16RfaFreshRto;
    i32RfaRecircRatio = (cint32)CTS_u16I32ToU16(i32RfaRecircRatio, 0);
    
    if ((pstInput->enOatSta==CTS_nValid) && (pstInput->enCabinTempSta==CTS_nValid))
    {
        u32EvapTemp = (cuint32)pstInput->u16Oat * (cuint32)u16RfaFreshRto;
        u32EvapTemp += (cuint32)pstInput->u16CabinTemp * (cuint32)i32RfaRecircRatio;
        u32EvapTemp /= (cuint32)CTS_stRfaFreshRtoBase.u16Const;

        pstOutput->u16CompOffEvapTemp = CTS_u16U32ToU16(u32EvapTemp);  
        pstOutput->enCompOffEvapTempSta = CTS_nValid;
    }
    else
    {
        pstOutput->enCompOffEvapTempSta = CTS_nInvalid;
    }
}


/***************************************************************************************************
  Function   : IPL_vEvapTempFl                                               
                           
  Description: This function is used to filter the EVAP temperature.
            
  Arguments  : pstInput         - is the address of input structure. 
                                    - pstEvapTemp: The address of EVAP temperature variable.
                                    - pstEvapTempFl: The address of EVAP temperature filter 
                                                     variable.
                                    - enEvapTempFlFactorSta: The valid status of EVAP temperature
                                                             filter factor.
                                    - u16EvapTempFlFactor: The filter factor of EVAP temperature.
                                    - u8EvapTempFlShift: The filter shift of EVAP temperature.
                                    
               pstOutput        - is the address of output structure.
                                    - enFlInitValSta: The initial filter value status.
                                    - enEvapTempSta: The valid status of EVAP temperature.
                                    - u32EvapTemp: The 32-bit EVAP temperature.
                                    - u16EvapTemp: The 16-bit EVAP temperature.
  
  Returns    : None
***************************************************************************************************/

static void IPL_vEvapTempFl(IPL_tstEvapTempFlIn *pstInput, IPL_tstEvapTempFl *pstOutput)
{
    IPL_tstUpdateEvapTempFlIn stUpdateEvapTempFlIn;  
    IPL_tstEvapTempFl stEvapTempFl;

    stUpdateEvapTempFlIn.pstInputAddress = pstInput->pstEvapTempFl;
    stUpdateEvapTempFlIn.pstUpdateAddress = &stEvapTempFl;
    IPL_vUpdateEvapTempFl(&stUpdateEvapTempFlIn);
        
    if ((*pstInput->pstEvapTemp).enEvapTempSta == CTS_nValid) 
    {
        if ((*pstInput->pstEvapTempFl).enFlInitValSta == CTS_nInvalid)
        {
            stEvapTempFl.enFlInitValSta = CTS_nValid;
            stEvapTempFl.enEvapTempSta = CTS_nValid;
            
            stEvapTempFl.u32EvapTemp = (cuint32)(*pstInput->pstEvapTemp).u16EvapTemp
                                       << pstInput->u8EvapTempFlShift;

            stEvapTempFl.u16EvapTemp = (*pstInput->pstEvapTemp).u16EvapTemp;
        }
        else
        {
            if (pstInput->enEvapTempFlFactorSta == CTS_nValid)
            {
                stEvapTempFl.enEvapTempSta = CTS_nValid;
                
                stEvapTempFl.u32EvapTemp = CTS_u32FirstOrderFilter(
                                           (*pstInput->pstEvapTempFl).u32EvapTemp,  
                                           (*pstInput->pstEvapTemp).u16EvapTemp, 
                                           pstInput->u16EvapTempFlFactor, 
                                           pstInput->u8EvapTempFlShift);

                stEvapTempFl.u16EvapTemp = CTS_u16U32ToU16(stEvapTempFl.u32EvapTemp
                                           >> pstInput->u8EvapTempFlShift);
            }
            else
            {
                stEvapTempFl.enEvapTempSta = CTS_nInvalid;
            }
        }
    }
    else
    {
        stEvapTempFl.enEvapTempSta = CTS_nInvalid;
    }

    stUpdateEvapTempFlIn.pstInputAddress = &stEvapTempFl;
    stUpdateEvapTempFlIn.pstUpdateAddress = pstOutput;
    IPL_vUpdateEvapTempFl(&stUpdateEvapTempFlIn);
}


/***************************************************************************************************
  Function   : IPL_vHctFl          
                           
  Description: This functio is used to filter the heater core temperature.       
            
  Arguments  : pstInput         - is the address of input structure.   
                                    - enHeaterPumpValidSta: The valid status of heater pump status.
                                    - enHeaterPumpOnOffSta: The heater pump on/off status.
                                    - enEvapTempSta: The valid status of EVAP temperature.
                                    - u16EvapTemp: The EVAP temperature.
                                    - enRawHctSta: The valid status of raw HCT.
                                    - u16RawHct: The raw HCT.
                                    - pstHctFl: The address of HCT filter structure.
                                    - enPumpOnFlFactorSta: The valid status of pump on filter 
                                                           factor.
                                    - u16PumpOnFlFactor: The filter factor when heater core pump on.
                                    - enPumpOffFlFactorSta: The valid status of pump off filter
                                                            factor.
                                    - u16PumpOffFlFactor: The filter factor when heater core pump 
                                                          off.
                                    - u8HctFlShift: The filter shift of heater core temperature.
                                  
               pstOutput        - is the address of output structure.
                                    - enFlInitValSta: The initial filter value status.
                                    - enHctSta: The valid status of HCT.
                                    - u32Hct: The 32-bit heater core temperature.
                                    - u16Hct: The 16-bit heater core temperature.
  
  Returns    : None
***************************************************************************************************/

static void IPL_vHctFl(IPL_tstHctFlIn *pstInput, IPL_tstHctFl *pstOutput)
{
    IPL_tstUpdateHctFlIn stUpdateHctFlIn;
    IPL_tstHctFl stHctFl;

    stUpdateHctFlIn.pstInputAddress = pstInput->pstHctFl;
    stUpdateHctFlIn.pstUpdateAddress = &stHctFl;
    IPL_vUpdateHctFl(&stUpdateHctFlIn);
        
    stHctFl.enHctSta = CTS_nInvalid;
        
    if (pstInput->enHeaterPumpValidSta == CTS_nValid) 
    {
        if ((*pstInput->pstHctFl).enFlInitValSta == CTS_nInvalid) 
        {
            if (pstInput->enHeaterPumpOnOffSta == CTS_nOff) 
            {
                if (pstInput->enEvapTempSta == CTS_nValid) 
                {
                    stHctFl.enHctSta = CTS_nValid;
                    stHctFl.enFlInitValSta = CTS_nValid;
                    stHctFl.u32Hct = (cuint32)pstInput->u16EvapTemp << pstInput->u8HctFlShift;
                    stHctFl.u16Hct = pstInput->u16EvapTemp;   
                }
            }
            else
            {
                if (pstInput->enRawHctSta == CTS_nValid)
                {
                    stHctFl.enHctSta = CTS_nValid;
                    stHctFl.enFlInitValSta = CTS_nValid;
                    stHctFl.u32Hct = (cuint32)pstInput->u16RawHct << pstInput->u8HctFlShift;
                    stHctFl.u16Hct = pstInput->u16RawHct;   
                }
            }
        }
        else
        {
            if (pstInput->enHeaterPumpOnOffSta == CTS_nOff)
            {
                if ((pstInput->enEvapTempSta==CTS_nValid) 
                     && (pstInput->enPumpOffFlFactorSta==CTS_nValid))
                {
                    stHctFl.enHctSta = CTS_nValid;
                    
                    stHctFl.u32Hct = CTS_u32FirstOrderFilter((*pstInput->pstHctFl).u32Hct, 
                                     pstInput->u16EvapTemp, pstInput->u16PumpOffFlFactor, 
                                     pstInput->u8HctFlShift);

                    stHctFl.u16Hct = CTS_u16U32ToU16(stHctFl.u32Hct >> pstInput->u8HctFlShift);
                }
            }
            else
            {
                if ((pstInput->enRawHctSta==CTS_nValid) 
                     && (pstInput->enPumpOnFlFactorSta==CTS_nValid))
                {
                    stHctFl.enHctSta = CTS_nValid;
                    
                    stHctFl.u32Hct = CTS_u32FirstOrderFilter((*pstInput->pstHctFl).u32Hct,  
                                     pstInput->u16RawHct, pstInput->u16PumpOnFlFactor, 
                                     pstInput->u8HctFlShift);

                    stHctFl.u16Hct = CTS_u16U32ToU16(stHctFl.u32Hct >> pstInput->u8HctFlShift);
                }
            }
        }
    }

    stUpdateHctFlIn.pstInputAddress = &stHctFl;
    stUpdateHctFlIn.pstUpdateAddress = pstOutput;
    IPL_vUpdateHctFl(&stUpdateHctFlIn);
}


/***************************************************************************************************
  Function   : IPL_vCalcBlowTemp                                               
                           
  Description: This function is used to calculate the blowout temperature.
            
  Arguments  : pstInput         - is the address of input structure.   
                                    - pstCalcRawBlowTempIn: The address of raw blowout temperature
                                                            calculation input structure.
                                    - pstBlowTempFl: The address of blowout temperature filter 
                                                     sturcture.
                                    - enBlowTempFlFactorSta: The valid status of blowout temperature
                                                             filter factor.
                                    - u16BlowTempFlFactor: The filter factor of blowout temperature.
                                    - u8BlowTempFlShift: The filter shift of blowout temperature.
                                    - pstBlowTempFlUpdateAdd: The address of blowout temperatrue
                                                              filter structure needed to be 
                                                              updeated.
                                  
               pstOutput        - is the address of output structure.
                                    - enBlowTempSta: The valid status of blowout temperature.
                                    - u16BlowTemp: The blowout temperature.
  
  Returns    : None
***************************************************************************************************/

static void IPL_vCalcBlowTemp(IPL_tstCalcBlowTempIn *pstInput, IPL_tstBlowTemp *pstOutput)
{
    IPL_tstRawBlowTemp stRawBlowTemp;
    IPL_tstBlowTempFlIn stBlowTempFlIn;
    IPL_tstBlowTempFl stBlowTempFlOut;
    IPL_tstUpdateBlowTempFlIn stUpdateBlowTempFlIn;

    IPL_vCalcRawBlowTemp(pstInput->pstCalcRawBlowTempIn, &stRawBlowTemp);

    stBlowTempFlIn.pstRawBlowTemp = &stRawBlowTemp;
    stBlowTempFlIn.pstBlowTempFl = pstInput->pstBlowTempFl;
    stBlowTempFlIn.enBlowTempFlFactorSta = pstInput->enBlowTempFlFactorSta;
    stBlowTempFlIn.u16BlowTempFlFactor = pstInput->u16BlowTempFlFactor;
    stBlowTempFlIn.u8BlowTempFlShift = pstInput->u8BlowTempFlShift;
    IPL_vBlowTempFl(&stBlowTempFlIn, &stBlowTempFlOut);

    stUpdateBlowTempFlIn.pstInputAddress = &stBlowTempFlOut;
    stUpdateBlowTempFlIn.pstUpdateAddress = pstInput->pstBlowTempFlUpdateAdd;      
    IPL_vUpdateBlowTempFl(&stUpdateBlowTempFlIn);

    pstOutput->u16BlowTemp = stBlowTempFlOut.u16BlowTemp;
    pstOutput->enBlowTempSta = stBlowTempFlOut.enBlowTempSta;
}


/***************************************************************************************************
  Function   : IPL_vCalcLimitMacRtoL                                               
                           
  Description: This function is used to calculate left side MAC ratio when the air mixing flap 
               reaches the limit position.
            
  Arguments  : pstInput         - is the address of input structure. 
                                    - enAirdModeSta: The valid status of AIRD mode.
                                    - u8AirdMode: The AIRD mode.
                                    - enBlwrVoltSta: The valid status of blower voltage.
                                    - u16BlwrVolt: The blower voltage.
  
               pstOutput        - is the address of output structure.
                                    - enLimitMacRtoSta: The valid status of limit MAC ratio.
                                    - u16HiMacRto: The MAC ratio of HI position.
                                    - u16LoMacRto: The MAC ratio of LO position.
                                    - u16MacRtoBase: The MAC ratio base.
  
  Returns    : None
***************************************************************************************************/

static void IPL_vCalcLimitMacRtoL(IPL_tstCalcLimitMacRtoIn *pstInput, IPL_tstLimitMacRto *pstOutput)
{
    if ((pstInput->enAirdModeSta==CTS_nValid) && (pstInput->enBlwrVoltSta==CTS_nValid))
    {
        pstOutput->u16HiMacRto = CTS_u16Lookup2D_Limit((cuint16)pstInput->u8AirdMode, 
                                 pstInput->u16BlwrVolt, CTS_stHiMacRtoL.u8SizeX, 
                                 CTS_stHiMacRtoL.u8SizeY, CTS_stHiMacRtoL.pu16TableX, 
                                 CTS_stHiMacRtoL.pu16TableY, CTS_stHiMacRtoL.pu16TableZ);

        pstOutput->u16LoMacRto = CTS_u16Lookup2D_Limit((cuint16)pstInput->u8AirdMode, 
                                 pstInput->u16BlwrVolt, CTS_stLoMacRtoL.u8SizeX, 
                                 CTS_stLoMacRtoL.u8SizeY, CTS_stLoMacRtoL.pu16TableX, 
                                 CTS_stLoMacRtoL.pu16TableY, CTS_stLoMacRtoL.pu16TableZ);
            
        pstOutput->u16MacRtoBase = CTS_stMacRtoBase.u16Const; 
        
        pstOutput->enLimitMacRtoSta = CTS_nValid;
    }
    else
    {
        pstOutput->enLimitMacRtoSta = CTS_nInvalid;
    }
}


/***************************************************************************************************
  Function   : IPL_vCalcLimitMacRtoR                                               
                           
  Description: This function is used to calculate right side MAC ratio when the air mixing flap 
               reaches the limit position.
            
  Arguments  : pstInput         - is the address of input structure. 
                                    - enAirdModeSta: The valid status of AIRD mode.
                                    - u8AirdMode: The AIRD mode.
                                    - enBlwrVoltSta: The valid status of blower voltage.
                                    - u16BlwrVolt: The blower voltage.
  
               pstOutput        - is the address of output structure.
                                    - enLimitMacRtoSta: The valid status of limit MAC ratio.
                                    - u16HiMacRto: The MAC ratio of HI position.
                                    - u16LoMacRto: The MAC ratio of LO position.
                                    - u16MacRtoBase: The MAC ratio base.
  
  Returns    : None
***************************************************************************************************/

static void IPL_vCalcLimitMacRtoR(IPL_tstCalcLimitMacRtoIn *pstInput, IPL_tstLimitMacRto *pstOutput)
{
    if ((pstInput->enAirdModeSta==CTS_nValid) && (pstInput->enBlwrVoltSta==CTS_nValid))
    {
        pstOutput->u16HiMacRto = CTS_u16Lookup2D_Limit((cuint16)pstInput->u8AirdMode, 
                                 pstInput->u16BlwrVolt, CTS_stHiMacRtoR.u8SizeX, 
                                 CTS_stHiMacRtoR.u8SizeY, CTS_stHiMacRtoR.pu16TableX, 
                                 CTS_stHiMacRtoR.pu16TableY, CTS_stHiMacRtoR.pu16TableZ);

        pstOutput->u16LoMacRto = CTS_u16Lookup2D_Limit((cuint16)pstInput->u8AirdMode, 
                                 pstInput->u16BlwrVolt, CTS_stLoMacRtoR.u8SizeX, 
                                 CTS_stLoMacRtoR.u8SizeY, CTS_stLoMacRtoR.pu16TableX, 
                                 CTS_stLoMacRtoR.pu16TableY, CTS_stLoMacRtoR.pu16TableZ);
            
        pstOutput->u16MacRtoBase = CTS_stMacRtoBase.u16Const; 
        
        pstOutput->enLimitMacRtoSta = CTS_nValid;
    }
    else
    {
        pstOutput->enLimitMacRtoSta = CTS_nInvalid;
    }
}


/***************************************************************************************************
  Function   : IPL_vCalcLimitMacRtoRe                                               
                           
  Description: This function is used to calculate rear side MAC ratio when the air mixing flap 
               reaches the limit position.
            
  Arguments  : pstInput         - is the address of input structure. 
                                    - enAirdModeSta: The valid status of AIRD mode.
                                    - u8AirdMode: The AIRD mode.
                                    - enBlwrVoltSta: The valid status of blower voltage.
                                    - u16BlwrVolt: The blower voltage.
  
               pstOutput        - is the address of output structure.
                                    - enLimitMacRtoSta: The valid status of limit MAC ratio.
                                    - u16HiMacRto: The MAC ratio of HI position.
                                    - u16LoMacRto: The MAC ratio of LO position.
                                    - u16MacRtoBase: The MAC ratio base.
  
  Returns    : None
***************************************************************************************************/

static void IPL_vCalcLimitMacRtoRe(IPL_tstCalcLimitMacRtoIn *pstInput, IPL_tstLimitMacRto *pstOutput)
{
    if ((pstInput->enAirdModeSta==CTS_nValid) && (pstInput->enBlwrVoltSta==CTS_nValid))
    {
        pstOutput->u16HiMacRto = CTS_u16Lookup2D_Limit((cuint16)pstInput->u8AirdMode, 
                                 pstInput->u16BlwrVolt, CTS_stHiMacRtoRe.u8SizeX, 
                                 CTS_stHiMacRtoRe.u8SizeY, CTS_stHiMacRtoRe.pu16TableX, 
                                 CTS_stHiMacRtoRe.pu16TableY, CTS_stHiMacRtoRe.pu16TableZ);

        pstOutput->u16LoMacRto = CTS_u16Lookup2D_Limit((cuint16)pstInput->u8AirdMode, 
                                 pstInput->u16BlwrVolt, CTS_stLoMacRtoRe.u8SizeX, 
                                 CTS_stLoMacRtoRe.u8SizeY, CTS_stLoMacRtoRe.pu16TableX, 
                                 CTS_stLoMacRtoRe.pu16TableY, CTS_stLoMacRtoRe.pu16TableZ);
            
        pstOutput->u16MacRtoBase = CTS_stMacRtoBase.u16Const; 
        
        pstOutput->enLimitMacRtoSta = CTS_nValid;
    }
    else
    {
        pstOutput->enLimitMacRtoSta = CTS_nInvalid;
    }
}


/***************************************************************************************************
  Function   : IPL_vBlowTempFl          
                           
  Description: This functio is used to perform the filter of the blowout temperature.       
            
  Arguments  : pstInput         - is the address of input structure.
                                    - pstRawBlowTemp: The address of raw blowout temperature 
                                                      structure.
                                    - pstBlowTempFl: The address of previous blowout temperature
                                                      structure.
                                    - enBlowTempFlFactorSta: The valid status of blowout temperature
                                                             filter factor.
                                    - u16BlowTempFlFactor: The filter factor of blowout temperature.
                                    - u8BlowTempFlShift: The filter shift of blowout temperature.
                                  
               pstOutput        - is the address of output structure.
                                    - enFlInitValSta: The valid status of initial filter value.
                                    - enBlowTempSta: The valid status of blowout temperature.
                                    - u32BlowTemp: The 32-bit blowout temperature.
                                    - u16BlowTemp: The 16-bit blowout temperature.
  
  Returns    : None
***************************************************************************************************/

static void IPL_vBlowTempFl(IPL_tstBlowTempFlIn *pstInput, IPL_tstBlowTempFl *pstOutput)
{
    IPL_tstUpdateBlowTempFlIn stUpdateBlowTempFlIn;
    IPL_tstBlowTempFl stBlowTempFl;

    stUpdateBlowTempFlIn.pstInputAddress = pstInput->pstBlowTempFl;
    stUpdateBlowTempFlIn.pstUpdateAddress = &stBlowTempFl;    
    IPL_vUpdateBlowTempFl(&stUpdateBlowTempFlIn);
            
    if ((*pstInput->pstRawBlowTemp).enRawBlowTempSta == CTS_nValid) 
    {
        if ((*pstInput->pstBlowTempFl).enFlInitValSta == CTS_nInvalid)
        {
            stBlowTempFl.enFlInitValSta = CTS_nValid;
            stBlowTempFl.enBlowTempSta = CTS_nValid;
            
            stBlowTempFl.u32BlowTemp = (cuint32)(*pstInput->pstRawBlowTemp).u16RawBlowTemp 
                                       << pstInput->u8BlowTempFlShift;
            
            stBlowTempFl.u16BlowTemp = (*pstInput->pstRawBlowTemp).u16RawBlowTemp;
        }
        else
        {
            if ((*pstInput->pstRawBlowTemp).boLoFlag != CTS_True)
            {
                if (pstInput->enBlowTempFlFactorSta == CTS_nValid)
                {
                    stBlowTempFl.enBlowTempSta = CTS_nValid;
                
                    stBlowTempFl.u32BlowTemp = CTS_u32FirstOrderFilter(
                                               (*pstInput->pstBlowTempFl).u32BlowTemp, 
                                               (*pstInput->pstRawBlowTemp).u16RawBlowTemp, 
                                               pstInput->u16BlowTempFlFactor, 
                                               pstInput->u8BlowTempFlShift);

                    stBlowTempFl.u16BlowTemp = CTS_u16U32ToU16(stBlowTempFl.u32BlowTemp 
                                               >> pstInput->u8BlowTempFlShift);
                }
                else
                {
                    stBlowTempFl.enBlowTempSta = CTS_nInvalid;
                }
            }
            else
            {
		stBlowTempFl.u32BlowTemp = (cuint32)(*pstInput->pstRawBlowTemp).u16RawBlowTemp 
                                           << pstInput->u8BlowTempFlShift;
            
            	stBlowTempFl.u16BlowTemp = (*pstInput->pstRawBlowTemp).u16RawBlowTemp;
            }
        }
    }
    else
    {
        stBlowTempFl.enBlowTempSta = CTS_nInvalid;
    }

    stUpdateBlowTempFlIn.pstInputAddress = &stBlowTempFl;
    stUpdateBlowTempFlIn.pstUpdateAddress = pstOutput;   
    IPL_vUpdateBlowTempFl(&stUpdateBlowTempFlIn);
}


/***************************************************************************************************
  Function   : IPL_vCalcRawBlowTemp         
                           
  Description: This functio is used to calculate the raw blowout temperature.
            
  Arguments  : pstInput         - is the address of input structure.
                                    - enEvapTempSta: The valid status of EVAP temperature.
                                    - u16EvapTemp: The EVAP temperature.
                                    - enHctSta: The valid status of HCT.
                                    - u16Hct: The HCT.
                                    - enTgtBlowTempSta: The valid status of target blowout 
                                                        temperature.
                                    - u16TgtBlowTemp: The target blowout temperature.
                                    - enHiLoValidSta: The valid status of HI/LO.
                                    - boReachHi: MAC flap reachs Hi or not.
                                    - boReachLo: Mac flap reachs Lo or not.
                                    - pstLimitMacRto: The address of MAC ratio structure.
                                
               pstOutput        - is the address of output structure.
                                    - enRawBlowTempSta: The status of raw blowout temperature.
                                    - u16RawBlowTemp: The raw blowout temperature.
                                    - boLoFlag: The low flag.
  
  Returns    : None
***************************************************************************************************/

static void IPL_vCalcRawBlowTemp(IPL_tstCalcRawBlowTempIn *pstInput, IPL_tstRawBlowTemp *pstOutput)
{
    cint32 i32BlowTemp;
    cbool boLoFlag;
        
    if ((pstInput->enTgtBlowTempSta==CTS_nValid) && (pstInput->enHctSta==CTS_nValid) 
        && (pstInput->enEvapTempSta==CTS_nValid))
    {
        if ((pstInput->enHiLoValidSta==CTS_nValid) 
            && ((*pstInput->pstLimitMacRto).enLimitMacRtoSta==CTS_nValid))
        {
            if ((pstInput->u16TgtBlowTemp >= pstInput->u16Hct) || (pstInput->enHiLoSta==CTS_nMacHi))
            {
                i32BlowTemp = (cint32)pstInput->u16Hct - (cint32)pstInput->u16EvapTemp;
                i32BlowTemp = (cint32)CTS_u16I32ToU16(i32BlowTemp, 0);
                i32BlowTemp *= (cint32)(*pstInput->pstLimitMacRto).u16HiMacRto;
                i32BlowTemp /= (cint32)(*pstInput->pstLimitMacRto).u16MacRtoBase;
                i32BlowTemp += (cint32)pstInput->u16EvapTemp;
            }
            else if ((pstInput->u16TgtBlowTemp <= pstInput->u16EvapTemp) 
                     || (pstInput->enHiLoSta==CTS_nMacLo))
            {
                i32BlowTemp = (cint32)pstInput->u16Hct - (cint32)pstInput->u16EvapTemp;
                i32BlowTemp = (cint32)CTS_u16I32ToU16(i32BlowTemp, 0);
                i32BlowTemp *= (cint32)(*pstInput->pstLimitMacRto).u16LoMacRto;
                i32BlowTemp /= (cint32)(*pstInput->pstLimitMacRto).u16MacRtoBase;
                i32BlowTemp += (cint32)pstInput->u16EvapTemp;
            }
            else
            {
                i32BlowTemp = (cint32)pstInput->u16TgtBlowTemp;
            }

	    if (pstInput->enHiLoSta == CTS_nMacLo)
            {
                boLoFlag = CTS_True;
            }
            else
            {
                boLoFlag = CTS_False;
            }
        }
        else
        {
            if (pstInput->u16TgtBlowTemp >= pstInput->u16Hct)
            {
                i32BlowTemp = (cint32)pstInput->u16Hct;
                boLoFlag = CTS_False;
            }
            else if (pstInput->u16TgtBlowTemp <= pstInput->u16EvapTemp)
            {
                i32BlowTemp = (cint32)pstInput->u16EvapTemp;
                boLoFlag = CTS_True;
            }
            else
            {
                i32BlowTemp = (cint32)pstInput->u16TgtBlowTemp;
                boLoFlag = CTS_False;
            }
        }
        
        pstOutput->u16RawBlowTemp = CTS_u16I32ToU16(i32BlowTemp, 0);
        pstOutput->enRawBlowTempSta = CTS_nValid;
        pstOutput->boLoFlag = boLoFlag;
    }
    else
    {
        pstOutput->enRawBlowTempSta = CTS_nInvalid;
    }
}


/***************************************************************************************************
  Function   : IPL_vCalcBlowSpd          
                           
  Description: This functio is used to calculate blowout speed according to the blower target, RFA 
               position and vihicle velocity.
            
  Arguments  : pstInput         - is the address of input structure.
                                    - enVelocitySta: The valid status of velocity.
                                    - u16Velocity: The velocity.
                                    - enRfaPosSta: The valid status of R/F air flap position.
                                    - u16RfaPos: The R/F air flap position.
                                    - enBlwrVoltSta: The valid status of blower voltage.
                                    - u16BlwrVolt: The blower voltage.
                                
               pstOutput        - is the address of output structure. 
                                    - enBlowSpdSta: The valid status of blowout speed.
                                    - u16BlowSpd: The blowout speed output.
  
  Returns    : None
***************************************************************************************************/

static void IPL_vCalcBlowSpd(IPL_tstCalcBlowSpdIn *pstInput, IPL_tstBlowSpd *pstOutput)
{
    cuint16 u16RfaPos;
    cint32 i32BlowSpd, i32VelOfs;

    if (pstInput->enRfaPosSta == CTS_nValid)
    {
        u16RfaPos = pstInput->u16RfaPos;    
    }
    else
    {
        u16RfaPos = CTS_stDefRfaPos.u16Const;
    }

    if (pstInput->enBlwrVoltSta == CTS_nValid)
    {
        i32BlowSpd = (cint32)CTS_u16Lookup2D_Limit(pstInput->u16BlwrVolt, u16RfaPos, 
                     CTS_stBlowSpd.u8SizeX, CTS_stBlowSpd.u8SizeY, CTS_stBlowSpd.pu16TableX, 
                     CTS_stBlowSpd.pu16TableY, CTS_stBlowSpd.pu16TableZ);

        i32VelOfs = (cint32)CTS_stBlowSpdRelativeZero.u16Const;
        
        if (pstInput->enVelocitySta == CTS_nValid)
        {
            i32VelOfs = (cint32)CTS_u16Lookup2D_Limit(pstInput->u16Velocity, u16RfaPos, 
                        CTS_stVelBlowSpdOfs.u8SizeX, CTS_stVelBlowSpdOfs.u8SizeY, 
                        CTS_stVelBlowSpdOfs.pu16TableX, CTS_stVelBlowSpdOfs.pu16TableY, 
                        CTS_stVelBlowSpdOfs.pu16TableZ);
        }
        
        i32BlowSpd += i32VelOfs - (cint32)CTS_stBlowSpdRelativeZero.u16Const;
        
        pstOutput->u16BlowSpd = CTS_u16I32ToU16(i32BlowSpd, 0);
        pstOutput->enBlowSpdSta = CTS_nValid;
    }
    else
    {
        pstOutput->u16BlowSpd = 0U;
        pstOutput->enBlowSpdSta = CTS_nInvalid;
    }
}


/***************************************************************************************************
  Function   : IPL_vCalcSun          
                           
  Description: This functio is used to calculate sun value.
            
  Arguments  : pstInput         - is the address of input structure.
                                    - enRawSunStaL: The valid status of left side raw sun.
                                    - u16RawSunL: The left side raw sun.
                                    - enRawSunStaR: The valid status of right side raw sun.
                                    - u16RawSunR: The right side raw sun.
                                
               pstOutput        - is the address of output structure.
                                    - enSunSta: The valid status of sun.
                                    - u16Sun: The sun output.
  
  Returns    : None
***************************************************************************************************/

static void IPL_vCalcSun(IPL_tstCalcSunIn *pstInput, IPL_tstSun *pstOutput)
{
    cuint16 u16RawSunL = pstInput->u16RawSunL;
    cuint16 u16RawSunR = pstInput->u16RawSunR;

    if (pstInput->enRawSuntStaL == CTS_nInvalid)
    {
        u16RawSunL = 0U;
    }

    if (pstInput->enRawSuntStaR == CTS_nInvalid)
    {
        u16RawSunR = 0U;
    }

    if (u16RawSunL > u16RawSunR)
    {
        pstOutput->u16Sun = u16RawSunL;
    }
    else
    {
        pstOutput->u16Sun = u16RawSunR;
    }

    if ((pstInput->enRawSuntStaL==CTS_nValid) || (pstInput->enRawSuntStaR==CTS_nValid))
    {
        pstOutput->enSunSta = CTS_nValid;
    }
    else
    {
        pstOutput->enSunSta = CTS_nInvalid;
    }
}


/***************************************************************************************************
  Function   : IPL_vCalcSunLoadHeat                                         
                           
  Description: This function is used to calculate the heat cause by sun load.
  
  Arguments  : pstInput         - is the address of input structure.
                                    - enSunSta: The valid status of sun.
                                    - u16Sun: The sun.
                                    - enOatSta: The valid status of OAT.
                                    - u16Oat: The OAT.
                                
               pstOutput        - is the address of output structure.
                                    - enSunLoadHeatSta: The valid status of sun load heat.
                                    - u16SunLoadHeat: The sun load heat output.
  
  Returns    : None
***************************************************************************************************/

static void IPL_vCalcSunLoadHeat(IPL_tstCalcSunLoadHeatIn *pstInput, IPL_tstSunLoadHeat *pstOutput)
{  
    if ((pstInput->enSunSta==CTS_nValid) && (pstInput->enOatSta==CTS_nValid))
    {
        pstOutput->u16SunLoadHeat = CTS_u16Lookup2D_Limit(pstInput->u16Sun, pstInput->u16Oat, 
                                    CTS_stSunLoadHeat.u8SizeX, CTS_stSunLoadHeat.u8SizeY, 
                                    CTS_stSunLoadHeat.pu16TableX, CTS_stSunLoadHeat.pu16TableY, 
                                    CTS_stSunLoadHeat.pu16TableZ);
        
        pstOutput->enSunLoadHeatSta = CTS_nValid;
    }
    else
    {
        pstOutput->u16SunLoadHeat = CTS_stThermalRelativeZero.u16Const;
        pstOutput->enSunLoadHeatSta = CTS_nInvalid;
    }
}


/***************************************************************************************************
  Function   : IPL_vCalcVelEngineHeat                                         
                           
  Description: This function is used to calculate the engine heat in different velocity and air  
               leaking heat caused by velocity.
  
  Arguments  : pstInput         - is the address of input structure.
                                    - enVelocitySta: The valid status of velocity.
                                    - u16Velocity: The velocity.
                                    - enOatSta: The valid status of OAT.
                                    - u16Oat: The OAT.
                                    - enFuelModeValidSta: The valid status of fuel mode status.
                                    - boInFuelMode: In fuel mode status.
                                    - enElecModeValidSta: The valid status of electric mode status.
                                    - boInElecMode: In electric mode status.
                                
               pstOutput        - is the address of output structure.
                                    - enVelEngineHeatSta: The valid status of velocity engine heat.
                                    - u16VelEngineHeat: The velocity engine heat output.
  
  Returns    : None
***************************************************************************************************/

static void IPL_vCalcVelEngineHeat(IPL_tstCalcVelEngineHeatIn *pstInput, IPL_tstVelEngineHeat *pstOutput)
{
    cint32 i32VelEngineHeat;

    if ((pstInput->enVelocitySta==CTS_nValid) && (pstInput->enOatSta==CTS_nValid))
    {
        i32VelEngineHeat = (cint32)CTS_u16Lookup2D_Limit(pstInput->u16Velocity, pstInput->u16Oat, 
                           CTS_stVelEngineHeat.u8SizeX, CTS_stVelEngineHeat.u8SizeY, 
                           CTS_stVelEngineHeat.pu16TableX, CTS_stVelEngineHeat.pu16TableY, 
                           CTS_stVelEngineHeat.pu16TableZ);

        if ((pstInput->enFuelModeValidSta==CTS_nValid) 
             && (pstInput->enElecModeValidSta==CTS_nValid))
        {
            if ((pstInput->boInFuelMode==CTS_True) && (pstInput->boInElecMode==CTS_False))
            {
                i32VelEngineHeat -= (cint32)CTS_stCalibrateBaseHeat.u16Const;
                i32VelEngineHeat += (cint32)CTS_stFuelModeBaseHeat.u16Const; 
            }
            else if ((pstInput->boInFuelMode==CTS_False) && (pstInput->boInElecMode==CTS_True))
            {
                i32VelEngineHeat -= (cint32)CTS_stCalibrateBaseHeat.u16Const;
                i32VelEngineHeat += (cint32)CTS_stElecModeBaseHeat.u16Const; 
            }
            else if ((pstInput->boInFuelMode==CTS_True) && (pstInput->boInElecMode==CTS_True))
            {
                i32VelEngineHeat -= (cint32)CTS_stCalibrateBaseHeat.u16Const;
                i32VelEngineHeat += (cint32)CTS_stFuelModeBaseHeat.u16Const; 
                i32VelEngineHeat += (cint32)CTS_stElecModeBaseHeat.u16Const; 
                i32VelEngineHeat -= (cint32)CTS_stThermalRelativeZero.u16Const;
            }
            else
            {
                i32VelEngineHeat = (cint32)CTS_stThermalRelativeZero.u16Const - i32VelEngineHeat;
                i32VelEngineHeat += (cint32)CTS_stThermalRelativeZero.u16Const;
                i32VelEngineHeat -= (cint32)CTS_stCalibrateBaseHeat.u16Const;
                i32VelEngineHeat += (cint32)CTS_stThermalRelativeZero.u16Const;
            }
        }

        pstOutput->u16VelEngineHeat = CTS_u16I32ToU16(i32VelEngineHeat, 0); 
        pstOutput->enVelEngineHeatSta = CTS_nValid;
    }
    else
    {
        pstOutput->u16VelEngineHeat = CTS_stThermalRelativeZero.u16Const;
        pstOutput->enVelEngineHeatSta = CTS_nInvalid;
    }
}


/***************************************************************************************************
  Function   : IPL_vCalcPcbTemp                                               
                           
  Description: This function is used to calculate the PCB temperature.
            
  Arguments  : pstInput         - is the address of input structure. 
                                    - enPcbTempAdSta: The valid status of PCB temperature AD value.
                                    - u16PcbTempAd: The PCB temperature AD value.
                                    - u16StableWaitTime: Time to wait sensor to become stable.
                                    
               pstOutput        - is the address of output structure.
                                    - enPcbTempSta: The valid status of PCB temperature.
                                    - u16StableWaitTime: Time to wait sensor to become stable.
                                    - u16PcbTemp: The PCB temperature output.
  
  Returns    : None
***************************************************************************************************/

static void IPL_vCalcPcbTemp(IPL_tstCalcPcbTempIn *pstInput, IPL_tstPcbTemp *pstOutput)
{  
    if (pstInput->enPcbTempAdSta == CTS_nValid) 
    {
        if (pstInput->u16StableWaitTime < CTS_stPcbTempStableWaitTime.u16Const)
        {
            pstOutput->u16StableWaitTime = pstInput->u16StableWaitTime + 1U;
            pstOutput->enPcbTempSta = CTS_nInvalid;
        }
        else
        {
            pstOutput->u16PcbTemp = CTS_u16Lookup1D_Limit(pstInput->u16PcbTempAd, 
                                    CTS_stPcbTemp.u8SizeX, CTS_stPcbTemp.pu16TableX, 
                                    CTS_stPcbTemp.pu16TableY);

            pstOutput->u16StableWaitTime = CTS_stPcbTempStableWaitTime.u16Const;
            pstOutput->enPcbTempSta = CTS_nValid;
        }
    }
    else
    {
        pstOutput->u16StableWaitTime = 0U;
        pstOutput->enPcbTempSta = CTS_nInvalid;
    }
}


/***************************************************************************************************
  Function   : IPL_vUpdateSensorIctFl                                               
  
  Description: This function is used to updete the sensor ICT filter variables.
            
  Arguments  : pstInput         - is the address of input structure.
                                    - pstInputAddress: The address of input variable.
                                    - pstUpdateAddress: The address needed to be updated.

  Returns    : None
***************************************************************************************************/

static void IPL_vUpdateSensorIctFl(IPL_tstUpdateSensorIctFlIn *pstInput)
{
    (*pstInput->pstUpdateAddress).enFlInitValSta = (*pstInput->pstInputAddress).enFlInitValSta;
    (*pstInput->pstUpdateAddress).enSensorIctSta = (*pstInput->pstInputAddress).enSensorIctSta;
    (*pstInput->pstUpdateAddress).u32SensorIct = (*pstInput->pstInputAddress).u32SensorIct;
    (*pstInput->pstUpdateAddress).u16SensorIct = (*pstInput->pstInputAddress).u16SensorIct;
}


/***************************************************************************************************
  Function   : IPL_vUpdateSensorIctFl                                               
  
  Description: This function is used to updete the EVAP temperature filter variables.
            
  Arguments  : pstInput         - is the address of input structure.
                                    - pstInputAddress: The address of input variable.
                                    - pstUpdateAddress: The address needed to be updated.

  Returns    : None
***************************************************************************************************/

static void IPL_vUpdateEvapTempFl(IPL_tstUpdateEvapTempFlIn *pstInput)
{
    (*pstInput->pstUpdateAddress).enFlInitValSta = (*pstInput->pstInputAddress).enFlInitValSta;
    (*pstInput->pstUpdateAddress).enEvapTempSta = (*pstInput->pstInputAddress).enEvapTempSta;
    (*pstInput->pstUpdateAddress).u32EvapTemp = (*pstInput->pstInputAddress).u32EvapTemp;
    (*pstInput->pstUpdateAddress).u16EvapTemp = (*pstInput->pstInputAddress).u16EvapTemp;
}


/***************************************************************************************************
  Function   : IPL_vUpdateHctFl                                               
  
  Description: This function is used to updete the HCT filter variables.
            
  Arguments  : pstInput         - is the address of input structure.
                                    - pstInputAddress: The address of input variable.
                                    - pstUpdateAddress: The address needed to be updated.

  Returns    : None
***************************************************************************************************/

static void IPL_vUpdateHctFl(IPL_tstUpdateHctFlIn *pstInput)
{
    (*pstInput->pstUpdateAddress).enFlInitValSta = (*pstInput->pstInputAddress).enFlInitValSta;
    (*pstInput->pstUpdateAddress).enHctSta = (*pstInput->pstInputAddress).enHctSta;
    (*pstInput->pstUpdateAddress).u32Hct = (*pstInput->pstInputAddress).u32Hct;
    (*pstInput->pstUpdateAddress).u16Hct = (*pstInput->pstInputAddress).u16Hct;
}


/***************************************************************************************************
  Function   : IPL_vUpdateBlowTempFl                                               
  
  Description: This function is used to updete the blowout temperature filter variables.
            
  Arguments  : pstInput         - is the address of input structure.
                                    - pstInputAddress: The address of input variable.
                                    - pstUpdateAddress: The address needed to be updated.

  Returns    : None
***************************************************************************************************/

static void IPL_vUpdateBlowTempFl(IPL_tstUpdateBlowTempFlIn *pstInput)
{
    (*pstInput->pstUpdateAddress).enFlInitValSta = (*pstInput->pstInputAddress).enFlInitValSta;
    (*pstInput->pstUpdateAddress).enBlowTempSta = (*pstInput->pstInputAddress).enBlowTempSta;
    (*pstInput->pstUpdateAddress).u32BlowTemp = (*pstInput->pstInputAddress).u32BlowTemp;
    (*pstInput->pstUpdateAddress).u16BlowTemp = (*pstInput->pstInputAddress).u16BlowTemp;
}

    
/***************************************************************************************************
  Function   : IPL_enGetU8Value                                                 
                           
  Description: This function is used to get the single 8-bit export value of IPL module. 
                
  Arguments  : enIndex          - is the index of output value.  
               *pu8Output       - is the output value.
                                    
  Returns    : CTS_nValid       - The output value is ready.
               CTS_nInvalid     - The output value is not ready.
***************************************************************************************************/

CTS_tenValidSta IPL_enGetU8Export(IPL_tenu8VarIndex enIndex, cuint8 *pu8Output)
{
    CTS_tenValidSta enReturn;
    cuint16 u16Max = (cuint16)IPL_nu8Max - 1U;
    
    if (enIndex < IPL_nu8Max)
    {
        *pu8Output = IPL_astU8Output[enIndex].u8Output;
        enReturn = IPL_astU8Output[enIndex].enOutputValidSta;
    }
    else
    {
        *pu8Output = IPL_astU8Output[u16Max].u8Output;
        enReturn = IPL_astU8Output[u16Max].enOutputValidSta;
    }

    return enReturn;
}


/***************************************************************************************************
  Function   : IPL_enGetU16Value                                                 
                           
  Description: This function is used to get the single 16-bit export value of IPL module. 
                
  Arguments  : enIndex          - is the index of output value.  
               *pu16Output      - is the output value.
                                    
  Returns    : CTS_nValid       - The output value is ready.
               CTS_nInvalid     - The output value is not ready.
***************************************************************************************************/

CTS_tenValidSta IPL_enGetU16Export(IPL_tenu16VarIndex enIndex, cuint16 *pu16Output)
{
    CTS_tenValidSta enReturn;
    cuint16 u16Max = (cuint16)IPL_nu16Max - 1U;
        
    if (enIndex < IPL_nu16Max)
    {
        *pu16Output = IPL_astU16Output[enIndex].u16Output;
        enReturn = IPL_astU16Output[enIndex].enOutputValidSta;
    }
    else
    {
        *pu16Output = IPL_astU16Output[u16Max].u16Output;
        enReturn = IPL_astU16Output[u16Max].enOutputValidSta;
    }

    return enReturn;
}

/*****************************************************************************
 Function      : IPL_u8GetValue                                              
 Description   : The extern model get the uint16 type variable value from this model                                                       
 Return Value  : uint16 value                                                 
*****************************************************************************/
cuint8 IPL_u8GetValue( IPL_tenu8VarIndex enIndex)
{
	cuint8 ReturnValue;
    cuint16 u16Max = (cuint16)IPL_nu8Max - 1U;
        
    if (enIndex < IPL_nu8Max)
    {
        ReturnValue = IPL_astU8Output[enIndex].u8Output;
    }
    else
    {
        ReturnValue = IPL_astU8Output[u16Max].u8Output;
    }
	return ReturnValue;
}

/*****************************************************************************
 Function      : IPL_u16GetValue                                              
 Description   : The extern model get the uint16 type variable value from this model                                                       
 Return Value  : uint16 value                                                 
*****************************************************************************/
cuint16 IPL_u16GetValue( IPL_tenu16VarIndex enIndex)
{
	cuint16 ReturnValue;
    cuint16 u16Max = (cuint16)IPL_nu16Max - 1U;
        
    if (enIndex < IPL_nu16Max)
    {
        ReturnValue = IPL_astU16Output[enIndex].u16Output;
    }
    else
    {
        ReturnValue = IPL_astU16Output[u16Max].u16Output;
    }
	return ReturnValue;
}


/*****************************************************************************
 Function      : IPL_u8GetValue                                              
 Description   : The extern model get the uint16 type variable value from this model                                                       
 Return Value  : uint16 value                                                 
*****************************************************************************/
cuint8 IPL_u8GetValidState( IPL_tenu8VarIndex enIndex)
{
	CTS_tenValidSta enReturn;
    cuint16 u16Max = (cuint16)IPL_nu8Max - 1U;
        
    if (enIndex < IPL_nu8Max)
    {
        enReturn = IPL_astU8Output[enIndex].enOutputValidSta;
    }
    else
    {
        enReturn = IPL_astU8Output[u16Max].enOutputValidSta;
    }
	return enReturn;
}

/*****************************************************************************
 Function      : IPL_u16GetValue                                              
 Description   : The extern model get the uint16 type variable value from this model                                                       
 Return Value  : uint16 value                                                 
*****************************************************************************/
cuint8 IPL_u16GetValidState( IPL_tenu16VarIndex enIndex)
{
	CTS_tenValidSta enReturn;
    cuint16 u16Max = (cuint16)IPL_nu16Max - 1U;
        
    if (enIndex < IPL_nu16Max)
    {
        enReturn = IPL_astU16Output[enIndex].enOutputValidSta;
    }
    else
    {
        enReturn = IPL_astU16Output[u16Max].enOutputValidSta;
    }
	return enReturn;
}
/***************************************************************************************************
  EOF: IPL.c
***************************************************************************************************/
