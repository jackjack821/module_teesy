/***************************************************************************************************
                                     VIRTUAL IN CAR TEMPERATURE                                     
                                        
  .File Name  : VICT.c
  
  .Description: This file is used to generate the virtual in car tempreture according to the  
                conditions which including initial PCB temperature, blowout temperature, blowout
                speed, OAT and sun intensity.
  
  --------------------------------------------------------------------------------------------------
    Version     Date        Author          Change
  --------------------------------------------------------------------------------------------------
    V001        2014-09-15  Chen Xiongzhi   - Creat this module.
    V002        2015-01-05  Chen Xiongzhi   - Opimize the dual zone process logic, add off mode  
                                              process filter factors, add engine off process logic,  
                                              opimize blowout speed look up curve and update to  
                                              unsigned 16-bit VICT output.
    V003        2015-01-08  Chen Xiongzhi   - Move some input process function to VICTIP module, 
                                              including PCB temperature process, blowout temperature 
                                              process, blowout speed process, sunload process and  
                                              AIRD mode process.
    V004        2015-01-22  Chen Xiongzhi   - Change the structure of the code for input conditions 
                                              process.
    V005        2015-01-30  Chen Xiongzhi   - Change the function structure, add input and output 
                                              structure for parameter passing.
    V006        2015-02-26  Chen Xiongzhi   - Change the code to conform to the rules of MISRA_C.
    V007        2015-11-03  Chen Xiongzhi   - Update the filter target calculating method.
    V008        2016-01-04  Chen Xiongzhi   - Make it compatible with tranditional ICT.
    V009        2016-01-12  Chen Xiongzhi   - Add double zone heat effect process.
    V010        2016-01-19  Chen Xiongzhi   - Add error processing status.
    V011        2016-01-30  Chen Xiongzhi   - Update the function structure in order to make it 
                                              correspond to the block diagram.
    V012        2016-03-04  Chen Xiongzhi   - Amend the accuracy of heat effect item correction
                                              function.
    V013        2016-05-26  Chen Xiongzhi   - Add body shell heat filter algorithm.
***************************************************************************************************/

#define VICT                             


/***************************************************************************************************
                                            HEADER FILES                                            
***************************************************************************************************/

/* System header files */
#include "CTS_StdDef.h"

/* Foreign header files */
#include "CTS_Alg.h"
#include "CTS_Cfg.h"

/* Own headerfiles */
#include "VICT.h" 
#include "VICT_Interface.h"
#include "VICT_Private.h"  
#include "VICT_Type.h"


/***************************************************************************************************
                                        FILE LOCAL VARIABLES            
                                        
  Note(s): Define all file local variables in this section. 
***************************************************************************************************/

static VICT_tstU16Output VICT_astU16Output[VICT_nu16Max];
static cbool VICT_boActiveFlag;
static VICT_tstHeatItemFl VICT_stHeatItemFl;
static VICT_tstHeatItemRtoFl VICT_stHeatItemRtoFl;
static VICT_tstIncomingHeatFl VICT_stIncomingHeatFl;
static VICT_tstHeadZoneFlTgt VICT_stHeadZoneFlTgt;
static VICT_tstCabinFlTgt VICT_stCabinFlTgt;
static VICT_tstHeatItemFlFactor VICT_stHeatItemFlFator;
static cuint16 VICT_u16IgnOffTime;
static cbool VICT_boSensorIctValid;
static cuint16 VICT_u16ZoneTempInvalidCtr; 
static cuint8 VICT_u8TaskCtr;
static VICT_tstInitIct VICT_stInitIct;
static VICT_tstReadBackRto VICT_stReadBackRto;


/***************************************************************************************************
                                   FILE LOCAL FUNCTION PROTOTYES                                   

  Note(s): In this section declare all file local function prototypes needed for your module.
***************************************************************************************************/

static void VICT_vInitCondOutput(void);
static void VICT_vHeatItemOutput(void);
static void VICT_vHeatItemRtoOutput(void);
static void VICT_vHeatItemFlCorOutput(void);
static void VICT_vZoneTempOutput(void);
static void VICT_vExHeadZoneTempCtl(void);
static void VICT_vFlFactorOutput(void);
static void VICT_vIncomingHeatOutput(void);
static void VICT_vHeadZoneFlTgtOutput(void);
static void VICT_vHeadZoneFlTgtCorOutput(void);
static void VICT_vCabinFlTgtOutput(void);
static void VICT_vSensorIctStaOutput(void);
static void VICT_vInitHeatItemFl(VICT_tstInitHeatItemFlIn *pstInput, VICT_tstHeatItemFl *pstOutput);
static void VICT_vCalcInitIct(VICT_tstCalcInitIctIn *pstInput, VICT_tstInitIct *pstOutput);
static void VICT_vCalcPcbIct(VICT_tstCalcPcbIctIn *pstInput, VICT_tstPcbIct *pstOutput);
static void VITC_vCalcReadBackRto(VICT_tstCalcReadBackRtoIn *pstInput, VICT_tstReadBackRto *pstOutput);
static void VICT_vReadBack(VICT_tstReadBackIn *pstInput, VICT_tstReadBackOut *pstOutput);
static void VICT_vHeatItemFl(VICT_tstHeatItemFlIn *pstInput, VICT_tstHeatItemFl *pstOutput);
static void VICT_vHeatItemRtoFl(VICT_tstHeatItemRtoFlIn *pstInput, VICT_tstHeatItemRtoFl *pstOutput);
static void VICT_vHeatItemFlCor(VICT_tstHeatItemFlCorIn *pstInput, VICT_tstHeatItemFl *pstOutput);
static void VICT_vCalcCorErr(VICT_tstCalcCorErrIn *pstInput, VICT_tstCorErr *pstOutput);
static void VICT_vCalcZoneTemp(VICT_tstCalcZoneTempIn *pstInput, VICT_tstZoneTemp *pstOutput);
static void VICT_vCalcSglZoneTemp(VICT_tstCalcSglZoneTempIn *pstInput, VICT_tstSglZoneTemp *pstOutput);
static void VICT_vCalcHeatItemFlFactor(VICT_tstCalcHeatItemFlFactorIn *pstInput, VICT_tstHeatItemFlFactor *pstOutput);
static void VICT_vInitIncomingHeatFl(VICT_tstInitIncomingHeatFlIn *pstInput, VICT_tstIncomingHeatFl *pstOutput);
static void VICT_vIncomingHeatFl(VICT_tstIncomingHeatFlIn *pstInput, VICT_tstIncomingHeatFl *pstOutput);
static void VICT_vCalcHeadZoneFlTgt(VICT_tstCalcHeadZoneFlTgtIn *pstInput, VICT_tstHeadZoneFlTgt *pstOutput);
static void VICT_vCalcSglHeadZoneFlTgt(VICT_tstCalcSglHeadZoneFlTgtIn *pstInput, VICT_tstSglHeadZoneFlTgt *pstOutput);
static void VICT_vHeadZoneFlTgtCor(VICT_tstHeadZoneFlTgtCorIn *pstInput, VICT_tstHeadZoneFlTgt *pstOutput);
static void VICT_vCalcCabinFlTgt(VICT_tstCalcCabinFlTgtIn *pstInput, VICT_tstCabinFlTgt *pstOutput);
static void VICT_vCalcCabinTempStcOfs(VICT_tstCalcCabinTempStcOfsIn *pstInput, VICT_tstCabinTempStcOfs *pstOutput);
static void VICT_vUpdateHeatItemRtoFl(VICT_tstUpdateHeatItemRtoFlIn *pstInput);
static void VICT_vUpdateHeatItemFl(VICT_tstUpdateHeatItemFlIn *pstInput);
static void VICT_vUpdateIncomingHeatFl(VICT_tstUpdateIncomingHeatFlIn *pstInput);


/***************************************************************************************************
  Function   : VICT_vReset                                                      
                           
  Description: Reset function of virtual in car temperature process. This function is called in the  
               RESET container of the operating system.    
                                
  Arguments  : None
  
  Returns    : None 
***************************************************************************************************/

void VICT_vReset(void)
{
    VICT_vWriteEnHeadZoneTempStaL(CTS_nInvalid);
    VICT_vWriteEnHeadZoneTempStaR(CTS_nInvalid);
    VICT_vWriteEnHeadZoneTempStaRe(CTS_nInvalid);
    VICT_vWriteEnBodyShellTempSta(CTS_nInvalid);
    VICT_vWriteEnCabinTempSta(CTS_nInvalid);
    VICT_vWriteEnIncomingHeatSta(CTS_nInvalid);
    VICT_boActiveFlag = CTS_False;
    VICT_u16IgnOffTime = 0xFFFFU;
}


/***************************************************************************************************
  Function   : VICT_vInit                                                      
                           
  Description: Initialize function of virtual in car temperature process. This function is called in  
               the INIT container of the operating system.
                                
  Arguments  : None
  
  Returns    : None 
***************************************************************************************************/ 

void VICT_vInit(void)
{
    VICT_vWriteEnHeadZoneTempStaL(CTS_nInvalid);
    VICT_vWriteEnHeadZoneTempStaR(CTS_nInvalid);
    VICT_vWriteEnHeadZoneTempStaRe(CTS_nInvalid);
    VICT_vWriteEnBodyShellTempSta(CTS_nInvalid);
    VICT_vWriteEnCabinTempSta(CTS_nInvalid);
    VICT_vWriteEnIncomingHeatSta(CTS_nInvalid);
    VICT_stHeatItemFl.enFlInitValSta = CTS_nInvalid;
    VICT_stHeatItemFl.enHeatItemSta = VICT_nHeatItemInvalid;
    VICT_stHeatItemRtoFl.enFlInitValSta = CTS_nInvalid;
    VICT_stHeatItemRtoFl.enHeatItemRtoSta = CTS_nInvalid;
    VICT_stIncomingHeatFl.enFlInitValSta = CTS_nInvalid;
    VICT_stIncomingHeatFl.enIncomingHeatSta = VICT_nIncomingHeatInvalid;
    VICT_stHeadZoneFlTgt.enHeadZoneFlTgtSta = CTS_nInvalid;
    VICT_stCabinFlTgt.enCabinFlTgtSta = CTS_nInvalid;
    VICT_stHeatItemFlFator.enHeatItemFlFactorSta = CTS_nInvalid;
    VICT_u16ZoneTempInvalidCtr = 0U;
    VICT_u8TaskCtr = 0U;
    VICT_stInitIct.enInitIctSta = CTS_nInvalid;
    VICT_stInitIct.u16InitIctConfirmCtr = 0U;
    VICT_stReadBackRto.enReadBackRtoSta = CTS_nInvalid;

    if (CTS_stIctMode.u8Const == 0U)
    {
        VICT_boSensorIctValid = CTS_False;
    }
    else
    {
        VICT_boSensorIctValid = CTS_True;
    }
}


/***************************************************************************************************
  Function   : VICT_vDeinit                                                     
                           
  Description: De-Init function of virtual in car temperature process. This function is called in  
               the DEINIT container of the operating system.
                                
  Arguments  : None
  
  Returns    : None 
***************************************************************************************************/

void VICT_vDeinit(void)
{
    if (VICT_stHeatItemFl.enHeatItemSta != VICT_nHeatItemInvalid)
    {
        VICT_boActiveFlag = CTS_True;
        VICT_u16IgnOffTime = 0U;
    }
    
    VICT_vWriteEnHeadZoneTempStaL(CTS_nInvalid);
    VICT_vWriteEnHeadZoneTempStaR(CTS_nInvalid);
    VICT_vWriteEnHeadZoneTempStaRe(CTS_nInvalid);
    VICT_vWriteEnBodyShellTempSta(CTS_nInvalid);
    VICT_vWriteEnCabinTempSta(CTS_nInvalid);
    VICT_vWriteEnIncomingHeatSta(CTS_nInvalid);
}


/***************************************************************************************************
  Function   : VICT_vMain                                                      
                           
  Description: Main function of virtual in car temperature process. This function is called in the  
               cyclic background task in the ON status. 
            
  Arguments  : None
  
  Returns    : None 
***************************************************************************************************/

void VICT_vMain(void)
{
    VICT_vInitCondOutput();
    
    if (VICT_u8TaskCtr == 0U)
    {
        VICT_vHeatItemOutput();
        VICT_u8TaskCtr = 1U;
    }
    if (VICT_u8TaskCtr == 1U)
    {
        VICT_vHeatItemRtoOutput();
        VICT_u8TaskCtr = 2U;
    }
    else if (VICT_u8TaskCtr == 2U)
    {
        VICT_vHeatItemFlCorOutput();
        VICT_u8TaskCtr = 3U;
    }
    else if (VICT_u8TaskCtr == 3U)
    {
        VICT_vZoneTempOutput();
        VICT_vExHeadZoneTempCtl();
        VICT_u8TaskCtr = 4U;
    } 
    else if (VICT_u8TaskCtr == 4U)
    { 
        VICT_vFlFactorOutput(); 
        VICT_u8TaskCtr = 5U;
    }
    else if (VICT_u8TaskCtr == 5U) 
    {
        VICT_u8TaskCtr = 6U;    
    }
    else if (VICT_u8TaskCtr == 6U)
    {
        VICT_vIncomingHeatOutput();
        VICT_u8TaskCtr = 7U;
    }
    else if (VICT_u8TaskCtr == 7U)
    {
        VICT_vHeadZoneFlTgtOutput();
        VICT_u8TaskCtr = 8U;
    }
    else if (VICT_u8TaskCtr == 8U)
    { 
        VICT_vHeadZoneFlTgtCorOutput();
        VICT_u8TaskCtr = 9U;
    }
    else 
    {   
        VICT_vCabinFlTgtOutput();
        VICT_u8TaskCtr = 0U;
    }

    VICT_vSensorIctStaOutput();
}


/***************************************************************************************************
  Function   : VICT_vActive                                                       
                           
  Description: Active function of virtual in car temperature process. This function is called in the 
               cyclic background task in the ACTIVE status. 
            
  Arguments  : None
  
  Returns    : None 
***************************************************************************************************/

void VICT_vActive(void)
{
    if (VICT_boSensorIctValid == CTS_False)
    {
        if (VICT_u16IgnOffTime < CTS_stVictActiveTime.u16Const)                                         
        {
            VICT_u16IgnOffTime++;
        }
        else
        {
            VICT_u16IgnOffTime = 0xFFFFU;
            VICT_boActiveFlag = CTS_False;
        }
    }
    else
    {
        if (VICT_u16IgnOffTime < CTS_stSensorIctActiveTime.u16Const)                                         
        {
            VICT_u16IgnOffTime++;
        }
        else
        {
            VICT_u16IgnOffTime = 0xFFFFU;
            VICT_boActiveFlag = CTS_False;
        }
    }
}


/***************************************************************************************************
  Function   : VICT_vInitCondOutput                                                
                           
  Description: This function is used to process the intial condition output.
            
  Arguments  : None
  
  Returns    : None
***************************************************************************************************/
 
static void VICT_vInitCondOutput(void)
{
    VICT_tstCalcInitIctIn stCalcInitIctIn;
    VICT_tstCalcPcbIctIn stCalcPcbIctIn;
    VICT_tstCalcReadBackRtoIn stCalcReadBackRtoIn;
    cbool boUseExIgnOffTime = VICT_boUseExIgnOffTime();
    
    stCalcPcbIctIn.enPcbTempSta = VICT_enPcbTempImport(&stCalcPcbIctIn.u16PcbTemp);
    stCalcPcbIctIn.enOatSta = VICT_enOatImport(&stCalcPcbIctIn.u16Oat);
    
    stCalcInitIctIn.enSensorIctSta = VICT_enSensorIctImport(&stCalcInitIctIn.u16SensorIct);
    stCalcInitIctIn.pstCalcPcbIctIn = &stCalcPcbIctIn;
    stCalcInitIctIn.pstPreInitIct = &VICT_stInitIct;

    VICT_vCalcInitIct(&stCalcInitIctIn, &VICT_stInitIct);

    if (boUseExIgnOffTime == CTS_False)
    {
        stCalcReadBackRtoIn.enIgnOffTimeSta = CTS_nValid;
        stCalcReadBackRtoIn.u16IgnOffTime = VICT_u16IgnOffTime;
        stCalcReadBackRtoIn.enOatSta = VICT_enOatImport(&stCalcReadBackRtoIn.u16Oat);
    }
    else
    {
        stCalcReadBackRtoIn.enIgnOffTimeSta = VICT_enExIgnOffTimeImport(&stCalcReadBackRtoIn.u16IgnOffTime);
        stCalcReadBackRtoIn.enOatSta = VICT_enOatImport(&stCalcReadBackRtoIn.u16Oat);
    }

    VITC_vCalcReadBackRto(&stCalcReadBackRtoIn, &VICT_stReadBackRto);
}


/***************************************************************************************************
  Function   : VICT_vHeatItemOutput                                                
                           
  Description: This function is used to process the intial heat effect items output.
            
  Arguments  : None
  
  Returns    : None
***************************************************************************************************/
 
static void VICT_vHeatItemOutput(void)
{
    VICT_tstInitHeatItemFlIn stInitHeatItemFlIn;
    VICT_tstHeatItemFl stInitHeatItemFlOut;
    VICT_tstHeatItemFlIn stHeatItemFlIn;
    VICT_tstHeatItemFl stHeatItemFlOut;
    VICT_tstUpdateHeatItemFlIn stUpdateHeatItemFlIn;

    stInitHeatItemFlIn.pstHeatItemFl = &VICT_stHeatItemFl;
    stInitHeatItemFlIn.pstInitIct = &VICT_stInitIct;
    stInitHeatItemFlIn.pstReadBackRto = &VICT_stReadBackRto;
    stInitHeatItemFlIn.u8HeatItemFlShift = CTS_stHeatItemChgBase.u8Const;       
    VICT_vInitHeatItemFl(&stInitHeatItemFlIn, &stInitHeatItemFlOut);  

    stHeatItemFlIn.pstHeatItemFl = &stInitHeatItemFlOut;   
    stHeatItemFlIn.pstHeadZoneFlTgt = &VICT_stHeadZoneFlTgt;
    stHeatItemFlIn.pstCabinFlTgt = &VICT_stCabinFlTgt;
    stHeatItemFlIn.pstHeatItemFlFactor = &VICT_stHeatItemFlFator;  
    stHeatItemFlIn.u8HeatItemFlShift = CTS_stHeatItemChgBase.u8Const;
    stHeatItemFlIn.boSensorIctValid = VICT_boSensorIctValid;
    VICT_vHeatItemFl(&stHeatItemFlIn, &stHeatItemFlOut);

    stUpdateHeatItemFlIn.pstInputAddress = &stHeatItemFlOut;
    stUpdateHeatItemFlIn.pstUpdateAddress = &VICT_stHeatItemFl;
    VICT_vUpdateHeatItemFl(&stUpdateHeatItemFlIn);
}


/***************************************************************************************************
  Function   : VICT_vHeatItemRtoOutput                                                
                           
  Description: This function is used to process the heat effect item ratio output.
            
  Arguments  : None
  
  Returns    : None
***************************************************************************************************/

static void VICT_vHeatItemRtoOutput(void)
{
    VICT_tstHeatItemRtoFlIn stHeatItemRtoFlIn;
    VICT_tstHeatItemRtoFl stHeatItemRtoFlOut;
    VICT_tstUpdateHeatItemRtoFlIn stUpdateHeatItemRtoFlIn;

    stHeatItemRtoFlIn.enAirdModeSta = VICT_enAirdModeImport(&stHeatItemRtoFlIn.u8AirdMode);
    stHeatItemRtoFlIn.pstHeatItemRtoFl = &VICT_stHeatItemRtoFl;
    stHeatItemRtoFlIn.enFlowItemRtoFlFactorSta = CTS_nValid;
    stHeatItemRtoFlIn.u16FlowItemRtoFlFactor = CTS_stFlowItemRtoChg.u16Const;
    stHeatItemRtoFlIn.u8FlowItemRtoFlShift = CTS_stFlowItemRtoChgBase.u8Const;
    VICT_vHeatItemRtoFl(&stHeatItemRtoFlIn, &stHeatItemRtoFlOut);

    stUpdateHeatItemRtoFlIn.pstInputAddress = &stHeatItemRtoFlOut;
    stUpdateHeatItemRtoFlIn.pstUpdateAddress = &VICT_stHeatItemRtoFl;
    VICT_vUpdateHeatItemRtoFl(&stUpdateHeatItemRtoFlIn);
}


/***************************************************************************************************
  Function   : VICT_vHeatItemFlCorOutput                                                
                           
  Description: This function is used to process the output of heat effect item correction.
            
  Arguments  : None
  
  Returns    : None
***************************************************************************************************/

static void VICT_vHeatItemFlCorOutput(void)
{
    VICT_tstHeatItemFlCorIn stHeatItemFlCorIn;
    VICT_tstHeatItemFl stHeatItemFlCorOut;
    VICT_tstUpdateHeatItemFlIn stUpdateHeatItemFlIn;

    stHeatItemFlCorIn.enCabinTempSta = VICT_enReadCabinTempSta();
    stHeatItemFlCorIn.u16CabinTemp = VICT_u16ReadCabinTemp();
    stHeatItemFlCorIn.enSensorIctSta = VICT_enSensorIctImport(&stHeatItemFlCorIn.u16SensorIct);
    stHeatItemFlCorIn.pstHeatItemFl = &VICT_stHeatItemFl;
    stHeatItemFlCorIn.pstHeatItemRtoFl = &VICT_stHeatItemRtoFl;
    stHeatItemFlCorIn.pstHeatItemFlFactor = &VICT_stHeatItemFlFator; 
    stHeatItemFlCorIn.u8HeatItemFlShift = CTS_stHeatItemChgBase.u8Const; 
    VICT_vHeatItemFlCor(&stHeatItemFlCorIn, &stHeatItemFlCorOut);

    stUpdateHeatItemFlIn.pstInputAddress = &stHeatItemFlCorOut;
    stUpdateHeatItemFlIn.pstUpdateAddress = &VICT_stHeatItemFl;
    VICT_vUpdateHeatItemFl(&stUpdateHeatItemFlIn);
}


/***************************************************************************************************
  Function   : VICT_vZoneTempOutput                                                
                           
  Description: This function is used to process the zone temperature output.
            
  Arguments  : None
  
  Returns    : None
***************************************************************************************************/

static void VICT_vZoneTempOutput(void)
{
    VICT_tstCalcZoneTempIn stCalcZoneTempIn;
    VICT_tstZoneTemp stZoneTemp;
    
    stCalcZoneTempIn.pstHeatItemFl = &VICT_stHeatItemFl;
    stCalcZoneTempIn.pstHeatItemRtoFl = &VICT_stHeatItemRtoFl; 
    VICT_vCalcZoneTemp(&stCalcZoneTempIn, &stZoneTemp);

    if (stZoneTemp.enZoneTempSta != VICT_nZoneTempInvalid) 
    {
        if (stZoneTemp.enZoneTempSta == VICT_nZoneTempValid)
        {
            VICT_u16ZoneTempInvalidCtr = 0U; 
        }
        else
        {
            if (VICT_u16ZoneTempInvalidCtr < CTS_stIctInvalidWaitTime.u16Const)
            {
                VICT_u16ZoneTempInvalidCtr++;
            }
        }

        if (VICT_u16ZoneTempInvalidCtr < CTS_stIctInvalidWaitTime.u16Const)
        {
            VICT_vWriteEnHeadZoneTempStaL(CTS_nValid);
            VICT_vWriteEnHeadZoneTempStaR(CTS_nValid);
            VICT_vWriteEnHeadZoneTempStaRe(CTS_nValid);
            VICT_vWriteEnBodyShellTempSta(CTS_nValid);
            VICT_vWriteEnCabinTempSta(CTS_nValid);
            VICT_vWriteU16HeadZoneTempL(stZoneTemp.u16HeadZoneTempL);
            VICT_vWriteU16HeadZoneTempR(stZoneTemp.u16HeadZoneTempR);
            VICT_vWriteU16HeadZoneTempRe(stZoneTemp.u16HeadZoneTempRe);
            VICT_vWriteU16BodyShellTemp(stZoneTemp.u16BodyShellTemp);
            VICT_vWriteU16CabinTemp(stZoneTemp.u16CabinTemp);
        }
        else
        {
            VICT_vWriteEnHeadZoneTempStaL(CTS_nInvalid);
            VICT_vWriteEnHeadZoneTempStaR(CTS_nInvalid);
            VICT_vWriteEnHeadZoneTempStaRe(CTS_nInvalid);
            VICT_vWriteEnBodyShellTempSta(CTS_nInvalid);
            VICT_vWriteEnCabinTempSta(CTS_nInvalid);
        }
    }
    else
    {
        VICT_vWriteEnHeadZoneTempStaL(CTS_nInvalid);
        VICT_vWriteEnHeadZoneTempStaR(CTS_nInvalid);
        VICT_vWriteEnHeadZoneTempStaRe(CTS_nInvalid);
        VICT_vWriteEnBodyShellTempSta(CTS_nInvalid);
        VICT_vWriteEnCabinTempSta(CTS_nInvalid);
    }
}


/***************************************************************************************************
  Function   : VICT_vExHeadZoneTempCtl                                               
                           
  Description: This function is used to process the external head zone temperature control.
            
  Arguments  : None
  
  Returns    : None
***************************************************************************************************/

static void VICT_vExHeadZoneTempCtl(void)
{
    CTS_tenValidSta enHeadZonTempStaL, enHeadZonTempStaR, enHeadZonTempStaRe;
    cuint16 u16HeadZoneTempL, u16HeadZoneTempR, u16HeadZoneTempRe;
    cbool boUesExHeadZoneTempL = VICT_boUseExHeadZoneTempL();
    cbool boUesExHeadZoneTempR = VICT_boUseExHeadZoneTempR();
    cbool boUesExHeadZoneTempRe = VICT_boUseExHeadZoneTempRe();

    enHeadZonTempStaL = VICT_enExHeadZoneTempLImport(&u16HeadZoneTempL);
    enHeadZonTempStaR = VICT_enExHeadZoneTempRImport(&u16HeadZoneTempR);
    enHeadZonTempStaRe = VICT_enExHeadZoneTempReImport(&u16HeadZoneTempRe);

    if (boUesExHeadZoneTempL == CTS_True)
    {
        VICT_vWriteEnHeadZoneTempStaL(enHeadZonTempStaL);
        VICT_vWriteU16HeadZoneTempL(u16HeadZoneTempL);
    }

    if (boUesExHeadZoneTempR == CTS_True)
    {
        VICT_vWriteEnHeadZoneTempStaR(enHeadZonTempStaR);
        VICT_vWriteU16HeadZoneTempR(u16HeadZoneTempR);
    }

    if (boUesExHeadZoneTempRe == CTS_True)
    {
        VICT_vWriteEnHeadZoneTempStaRe(enHeadZonTempStaRe);
        VICT_vWriteU16HeadZoneTempRe(u16HeadZoneTempRe);
    }
}


/***************************************************************************************************
  Function   : VICT_vFlFactorOutput                                                
                           
  Description: This function is used to process the filter factors output.
            
  Arguments  : None
  
  Returns    : None
***************************************************************************************************/

static void VICT_vFlFactorOutput(void)
{
    VICT_tstCalcHeatItemFlFactorIn stCalcHeatItemFlFactorIn;

    stCalcHeatItemFlFactorIn.enBlowSpdSta = VICT_enBlowSpdImport(&stCalcHeatItemFlFactorIn.u16BlowSpd);
    stCalcHeatItemFlFactorIn.enAirdModeSta = VICT_enAirdModeImport(&stCalcHeatItemFlFactorIn.u8AirdMode);
    VICT_vCalcHeatItemFlFactor(&stCalcHeatItemFlFactorIn, &VICT_stHeatItemFlFator);
}


/***************************************************************************************************
  Function   : VICT_vIncomingHeatOutput                                                
                           
  Description: This function is used to process the incoming heat output.
            
  Arguments  : None
  
  Returns    : None
***************************************************************************************************/

static void VICT_vIncomingHeatOutput(void)
{ 
    VICT_tstInitIncomingHeatFlIn stInitIncomingHeatFlIn;
    VICT_tstIncomingHeatFl stInitIncomingHeatFlOut;
    VICT_tstIncomingHeatFlIn stIncomingHeatFlIn;

    stInitIncomingHeatFlIn.pstIncomingHeatFl = &VICT_stIncomingHeatFl;
    stInitIncomingHeatFlIn.pstInitIct = &VICT_stInitIct;
    stInitIncomingHeatFlIn.pstReadBackRto = &VICT_stReadBackRto;
    stInitIncomingHeatFlIn.u8BodyShellHeatFlShift = CTS_stBodyShellHeatChgBase.u8Const;   
    VICT_vInitIncomingHeatFl(&stInitIncomingHeatFlIn, &stInitIncomingHeatFlOut);
        
    stIncomingHeatFlIn.pstIncomingHeatFl = &stInitIncomingHeatFlOut;
    stIncomingHeatFlIn.enOatSta = VICT_enOatImport(&stIncomingHeatFlIn.u16Oat);
    stIncomingHeatFlIn.enSunLoadHeatSta = VICT_enSunLoadHeatImport(&stIncomingHeatFlIn.u16SunLoadHeat);
    stIncomingHeatFlIn.enVelEngineHeatSta = VICT_enVelEngineHeatImport(&stIncomingHeatFlIn.u16VelEngineHeat);
    
    if (VICT_boDisIncomingHeatFl() == CTS_True)
    {
        stIncomingHeatFlIn.enIncomingHeatFlFactorSta = CTS_nInvalid;
    }
    else
    {
        stIncomingHeatFlIn.enIncomingHeatFlFactorSta = CTS_nValid;
    }
    
    stIncomingHeatFlIn.u16BodyShellHeatFlFactor = CTS_stBodyShellHeatChg.u16Const;
    stIncomingHeatFlIn.u8BodyShellHeatFlShift = CTS_stBodyShellHeatChgBase.u8Const;
    VICT_vIncomingHeatFl(&stIncomingHeatFlIn, &VICT_stIncomingHeatFl);

    if (VICT_stIncomingHeatFl.enIncomingHeatSta != VICT_nIncomingHeatInvalid)
    {
        VICT_vWriteEnIncomingHeatSta(CTS_nValid);
        VICT_vWriteU16IncomingHeat(VICT_stIncomingHeatFl.u16IncomingHeat);
    }
    else
    {
        VICT_vWriteEnIncomingHeatSta(CTS_nInvalid);
    }
}


/***************************************************************************************************
  Function   : VICT_vHeadZoneFlTgtOutput                                                
                           
  Description: This function is used to process the head zone temperature filter target output.
            
  Arguments  : None
  
  Returns    : None
***************************************************************************************************/

static void VICT_vHeadZoneFlTgtOutput(void)
{ 
    VICT_tstCalcHeadZoneFlTgtIn stCalcHeadZoneFlTgtIn;

    stCalcHeadZoneFlTgtIn.enBlowTempStaL = VICT_enBlowTempLImport(&stCalcHeadZoneFlTgtIn.u16BlowTempL);
    stCalcHeadZoneFlTgtIn.enBlowTempStaR = VICT_enBlowTempRImport(&stCalcHeadZoneFlTgtIn.u16BlowTempR);
    stCalcHeadZoneFlTgtIn.enBlowTempStaRe = VICT_enBlowTempReImport(&stCalcHeadZoneFlTgtIn.u16BlowTempRe);
    stCalcHeadZoneFlTgtIn.enIncomingHeatSta = VICT_stIncomingHeatFl.enIncomingHeatSta;
    stCalcHeadZoneFlTgtIn.u16IncomingHeat = VICT_stIncomingHeatFl.u16IncomingHeat;
    stCalcHeadZoneFlTgtIn.enBlowSpdSta = VICT_enBlowSpdImport(&stCalcHeadZoneFlTgtIn.u16BlowSpd);
    VICT_vCalcHeadZoneFlTgt(&stCalcHeadZoneFlTgtIn, &VICT_stHeadZoneFlTgt);
}


/***************************************************************************************************
  Function   : VICT_vHeadZoneFlTgtCorOutput                                                
                           
  Description: This function is used to process the head zone temperature filter target correction 
               output.
            
  Arguments  : None
  
  Returns    : None
***************************************************************************************************/

static void VICT_vHeadZoneFlTgtCorOutput(void)
{
    VICT_tstHeadZoneFlTgtCorIn stHeadZoneFlTgtCorIn;

    stHeadZoneFlTgtCorIn.pstHeadZoneFlTgt = &VICT_stHeadZoneFlTgt;
    stHeadZoneFlTgtCorIn.enAirdModeSta = VICT_enAirdModeImport(&stHeadZoneFlTgtCorIn.u8AirdMode); 
    VICT_vHeadZoneFlTgtCor(&stHeadZoneFlTgtCorIn, &VICT_stHeadZoneFlTgt);
}


/***************************************************************************************************
  Function   : VICT_vCabinFlTgtOutput                                                
                           
  Description: This function is used to process the cabin zone filter target output.
            
  Arguments  : None
  
  Returns    : None
***************************************************************************************************/

static void VICT_vCabinFlTgtOutput(void)
{
    VICT_tstCalcCabinFlTgtIn stCalcCabinFlTgtIn;

    stCalcCabinFlTgtIn.pstHeadZoneFlTgt = &VICT_stHeadZoneFlTgt;
    stCalcCabinFlTgtIn.enSunSta = VICT_enSunImport(&stCalcCabinFlTgtIn.u16Sun);
    stCalcCabinFlTgtIn.enOatSta = VICT_enOatImport(&stCalcCabinFlTgtIn.u16Oat);
    stCalcCabinFlTgtIn.enAirdPosSta = VICT_enAirdPosImport(&stCalcCabinFlTgtIn.u16AirdPos);   
    VICT_vCalcCabinFlTgt(&stCalcCabinFlTgtIn, &VICT_stCabinFlTgt);
}


/***************************************************************************************************
  Function   : VICT_vSensorIctStaOutput                                                
                           
  Description: This function is used to process the failure status of sensor ICT output.
            
  Arguments  : None
  
  Returns    : None
***************************************************************************************************/

static void VICT_vSensorIctStaOutput(void)
{
    cuint16 u16SensorIct;
    
    CTS_tenValidSta enSensorIctSta = VICT_enSensorIctImport(&u16SensorIct);
    
    if (enSensorIctSta == CTS_nInvalid)
    {
        VICT_boSensorIctValid = CTS_False;
    }
    else
    {
        VICT_boSensorIctValid = CTS_True;
    }
}


/***************************************************************************************************
  Function   : VICT_vInitHeatItemFl                                                
                           
  Description: This function is used to process the initial heat effect item filter.
            
  Arguments  : pstInput         - is the address of input structure.
                                    - pstHeatItemFl: The address of heat effect item filter 
                                                     structure.
                                    - pstCalcInitIctIn: The address of initial ICT calculation input 
                                                        structure.       
                                    - pstCalcReadBackRtoIn: The address of read back ratio 
                                                            calculation input structure.
                                    - u8HeatItemFlShift: The heat effect item filter shift.
                                
               pstOutput        - is the address of output structure.
                                    - enFlInitValSta: The initial filter value valid status.
                                    - enHeatItemSta: The valid status of heat effect item.
                                    - u32HeadZoneFlowItemL: The 32-bit left side head zone flow 
                                                            field heat effect item.
                                    - u32HeadZoneFlowItemR: The 32-bit right side head zone flow 
                                                            field heat effect item.
                                    - u32HeadZoneFlowItemRe: The 32-bit rear side head zone flow 
                                                             field heat effect item.
                                    - u32HeadZoneShellItem: The 32-bit head zone body shell heat 
                                                            effect item.
                                    - u32CabinFlowItem: The 32-bit cabin flow field heat effect 
                                                        item.
                                    - u32CabinShellItem: The 32-bit cabin body shell heat effect
                                                         item.
                                    - u16HeadZoneFlowItemL: The 16-bit left side head zone flow 
                                                            field heat effect item.
                                    - u16HeadZoneFlowItemR: The 16-bit right side head zone flow 
                                                            field heat effect item.
                                    - u16HeadZoneFlowItemRe: The 16-bit rear side head zone flow 
                                                             field heat effect item.
                                    - u16HeadZoneShellItem: The 16-bit head zone body shell heat 
                                                            effect item.
                                    - u16CabinFlowItem: The 16-bit cabin flow field heat effect 
                                                        item.
                                    - u16CabinShellItem: The 16-bit cabin body shell heat effect
                                                         item.
  
  Returns    : None
***************************************************************************************************/

static void VICT_vInitHeatItemFl(VICT_tstInitHeatItemFlIn *pstInput, VICT_tstHeatItemFl *pstOutput)
{
    VICT_tstUpdateHeatItemFlIn stUpdateHeatItemFlIn;
    VICT_tstHeatItemFl stHeatItemFl;
    VICT_tstReadBackIn stReadBackIn;
    VICT_tstReadBackOut stHeadZoneFlowItemL, stHeadZoneFlowItemR, stHeadZoneFlowItemRe;
    VICT_tstReadBackOut stHeadZoneShellItem, stCabinFlowItem, stCabinShellItem;

    stUpdateHeatItemFlIn.pstInputAddress = pstInput->pstHeatItemFl;
    stUpdateHeatItemFlIn.pstUpdateAddress = &stHeatItemFl;
    VICT_vUpdateHeatItemFl(&stUpdateHeatItemFlIn);

    if ((*pstInput->pstHeatItemFl).enFlInitValSta == CTS_nInvalid)
    {
        if (((*pstInput->pstInitIct).enInitIctSta==CTS_nValid) 
            && ((*pstInput->pstReadBackRto).enReadBackRtoSta==CTS_nValid))
        {
            stReadBackIn.u16CurValue = (*pstInput->pstInitIct).u16InitHeadZoneTemp;
            stReadBackIn.u16ReadBackRto = (*pstInput->pstReadBackRto).u16ReadBackRto;
            stReadBackIn.u16ReadBackBase = (*pstInput->pstReadBackRto).u16ReadBackBase;  
            stReadBackIn.u16PreValue = (*pstInput->pstHeatItemFl).u16HeadZoneFlowItemL;
            VICT_vReadBack(&stReadBackIn, &stHeadZoneFlowItemL);

            stReadBackIn.u16PreValue = (*pstInput->pstHeatItemFl).u16HeadZoneFlowItemR;
            VICT_vReadBack(&stReadBackIn, &stHeadZoneFlowItemR);

            stReadBackIn.u16PreValue = (*pstInput->pstHeatItemFl).u16HeadZoneFlowItemRe;
            VICT_vReadBack(&stReadBackIn, &stHeadZoneFlowItemRe);

            stReadBackIn.u16PreValue = (*pstInput->pstHeatItemFl).u16HeadZoneShellItem;
            VICT_vReadBack(&stReadBackIn, &stHeadZoneShellItem);

            stReadBackIn.u16CurValue = (*pstInput->pstInitIct).u16InitCabinTemp;
            stReadBackIn.u16PreValue = (*pstInput->pstHeatItemFl).u16CabinFlowItem;
            VICT_vReadBack(&stReadBackIn, &stCabinFlowItem);

            stReadBackIn.u16PreValue = (*pstInput->pstHeatItemFl).u16CabinShellItem;
            VICT_vReadBack(&stReadBackIn, &stCabinShellItem);

            stHeatItemFl.u32HeadZoneFlowItemL = (cuint32)stHeadZoneFlowItemL.u16ReadBackOut 
                                                << pstInput->u8HeatItemFlShift;   
            
            stHeatItemFl.u32HeadZoneFlowItemR = (cuint32)stHeadZoneFlowItemR.u16ReadBackOut 
                                                << pstInput->u8HeatItemFlShift;   

            stHeatItemFl.u32HeadZoneFlowItemRe = (cuint32)stHeadZoneFlowItemRe.u16ReadBackOut 
                                                 << pstInput->u8HeatItemFlShift;
            
            stHeatItemFl.u32HeadZoneShellItem = (cuint32)stHeadZoneShellItem.u16ReadBackOut 
                                                << pstInput->u8HeatItemFlShift;  
            
            stHeatItemFl.u32CabinFlowItem = (cuint32)stCabinFlowItem.u16ReadBackOut 
                                            << pstInput->u8HeatItemFlShift;   
            
            stHeatItemFl.u32CabinShellItem = (cuint32)stCabinShellItem.u16ReadBackOut 
                                             << pstInput->u8HeatItemFlShift;  
            
            stHeatItemFl.u16HeadZoneFlowItemL = stHeadZoneFlowItemL.u16ReadBackOut;
            stHeatItemFl.u16HeadZoneFlowItemR = stHeadZoneFlowItemR.u16ReadBackOut;
            stHeatItemFl.u16HeadZoneFlowItemRe = stHeadZoneFlowItemRe.u16ReadBackOut;
            stHeatItemFl.u16HeadZoneShellItem = stHeadZoneShellItem.u16ReadBackOut; 
            stHeatItemFl.u16CabinFlowItem = stCabinFlowItem.u16ReadBackOut;
            stHeatItemFl.u16CabinShellItem = stCabinShellItem.u16ReadBackOut;
            stHeatItemFl.enFlInitValSta = CTS_nValid;
            stHeatItemFl.enHeatItemSta = VICT_nHeatItemValid;
        }
        else
        {
            stHeatItemFl.enHeatItemSta = VICT_nHeatItemInvalid;
        }
    }

    stUpdateHeatItemFlIn.pstInputAddress = &stHeatItemFl;
    stUpdateHeatItemFlIn.pstUpdateAddress = pstOutput;
    VICT_vUpdateHeatItemFl(&stUpdateHeatItemFlIn);
}


/***************************************************************************************************
  Function   : VICT_vCalcInitIct                                               
                           
  Description: This function is used to calculate the initial in car temperature.
            
  Arguments  : pstInput         - is the address of input structure.
                                    - enSensorIctSta: The valid status of sensor ICT.
                                    - u16SensorIct: The sensor ICT
                                    - pstCalcPcbIctIn: The address of PCB ICT calculation input 
                                                       structure.
                                
               pstOutput        - is the address of output structure.
                                    - enInitIctSta: The status of initial ICT.
                                    - u16InitIct: The initial ICT output
  
  Returns    : None
***************************************************************************************************/

static void VICT_vCalcInitIct(VICT_tstCalcInitIctIn *pstInput, VICT_tstInitIct *pstOutput)
{
    VICT_tstPcbIct stPcbIct;
    VICT_tstInitIct stInitIct;

    VICT_vCalcPcbIct(pstInput->pstCalcPcbIctIn, &stPcbIct);

    stInitIct.u16InitHeadZoneTemp = stPcbIct.u16PcbIct;
    
    if (stPcbIct.enPcbIctSta == CTS_nValid)
    {
        if (pstInput->enSensorIctSta == CTS_nValid)
        {
            stInitIct.u16InitCabinTemp = pstInput->u16SensorIct;
        }
        else
        {
            stInitIct.u16InitCabinTemp = stPcbIct.u16PcbIct;    
        }

        if ((*pstInput->pstPreInitIct).u16InitIctConfirmCtr < 10U)
        {
            stInitIct.enInitIctSta = CTS_nInvalid;
            
            if ((((cint32)(*pstInput->pstPreInitIct).u16InitHeadZoneTemp - (cint32)stInitIct.u16InitHeadZoneTemp) > 30)
                || (((cint32)(*pstInput->pstPreInitIct).u16InitHeadZoneTemp - (cint32)stInitIct.u16InitHeadZoneTemp) < -30)
                || (((cint32)(*pstInput->pstPreInitIct).u16InitCabinTemp - (cint32)stInitIct.u16InitCabinTemp) > 30)
                || (((cint32)(*pstInput->pstPreInitIct).u16InitCabinTemp - (cint32)stInitIct.u16InitCabinTemp) < -30))
            {
                stInitIct.u16InitIctConfirmCtr = 0U;
            }
            else
            {
                stInitIct.u16InitIctConfirmCtr = (*pstInput->pstPreInitIct).u16InitIctConfirmCtr + 1U;
            }
        }
        else
        {
            stInitIct.u16InitIctConfirmCtr = 10U;
            stInitIct.enInitIctSta = CTS_nValid;
        }
    }
    else
    {
        stInitIct.u16InitIctConfirmCtr =  0U;
        stInitIct.enInitIctSta = CTS_nInvalid;
    } 

    pstOutput->enInitIctSta = stInitIct.enInitIctSta;
    pstOutput->u16InitHeadZoneTemp = stInitIct.u16InitHeadZoneTemp;
    pstOutput->u16InitCabinTemp = stInitIct.u16InitCabinTemp;
    pstOutput->u16InitIctConfirmCtr = stInitIct.u16InitIctConfirmCtr;
}


/***************************************************************************************************
  Function   : VICT_vCalcPcbIct                                               
                           
  Description: This function is used to calculate in car temperature according to the PCB 
               temperature and OAT.
            
  Arguments  : pstInput         - is the address of input structure.
                                    - enPcbTempSta: The valid status of PCB temperature.
                                    - u16PcbTemp: The PCB temperature.
                                    - enOatSta: The valid status of OAT.
                                    - u16Oat: The OAT.
                                
               pstOutput        - is the address of output structure.
                                    - enPcbIctSta: The valid status of PCB ICT.
                                    - u16PcbIct: The PCB ICT output
  
  Returns    : None
***************************************************************************************************/

static void VICT_vCalcPcbIct(VICT_tstCalcPcbIctIn *pstInput, VICT_tstPcbIct *pstOutput)
{
    cint32 i32PcbIct, i32PcbIctLimit, i32Err;
    cuint16 u16PcbIctFactor;
    
    if ((pstInput->enPcbTempSta==CTS_nValid) && (pstInput->enOatSta==CTS_nValid))
    {
        if (pstInput->u16PcbTemp > pstInput->u16Oat)
        {
            i32PcbIct = (cint32)pstInput->u16PcbTemp - (cint32)pstInput->u16Oat;

            i32PcbIctLimit = (cint32)CTS_u16Lookup1D_Limit(pstInput->u16Oat, 
                             CTS_stPcbIctLimit.u8SizeX, CTS_stPcbIctLimit.pu16TableX, 
                             CTS_stPcbIctLimit.pu16TableY);

            i32PcbIctLimit -= (cint32)CTS_stThermalRelativeZero.u16Const;

            if (i32PcbIct > i32PcbIctLimit)
            {
                i32PcbIct = i32PcbIctLimit;
            }

            i32Err = i32PcbIct + (cint32)CTS_stThermalRelativeZero.u16Const;
            i32Err = (cint32)CTS_u16I32ToU16(i32Err, 0);

            u16PcbIctFactor = CTS_u16Lookup2D_Limit(pstInput->u16Oat, (cuint16)i32Err, 
                              CTS_stPcbIctFactor.u8SizeX, CTS_stPcbIctFactor.u8SizeY,
                              CTS_stPcbIctFactor.pu16TableX, CTS_stPcbIctFactor.pu16TableY,
                              CTS_stPcbIctFactor.pu16TableZ);
                
            i32PcbIct *= (cint32)u16PcbIctFactor;           
            i32PcbIct /= (cint32)CTS_stPcbIctBase.u16Const; 
            i32PcbIct += (cint32)pstInput->u16Oat;  
        }
        else
        {
            i32PcbIct = (cint32)pstInput->u16Oat;  
        }
        
        pstOutput->u16PcbIct = CTS_u16I32ToU16(i32PcbIct, 0);
        pstOutput->enPcbIctSta = CTS_nValid;
    }
    else
    {
        pstOutput->enPcbIctSta = CTS_nInvalid;
    }
}


/***************************************************************************************************
  Function   : VITC_vCalcReadBackRto                                                
                           
  Description: This function is used to calculate the read back ratio.
            
  Arguments  : pstInput         - is the address of input structure.
                                    - enIgnOffTimeSta: The valid status of ignition off time.
                                    - u16IgnOffTime: The ignition off time.
                                    - enOatSta: The valid status of OAT.
                                    - u16Oat: The OAT.
                                    
               pstOutput        - is the address of output structure.
                                    - enReadBackRtosta: The valid status of read back ratio.
                                    - u16ReadBackRto: The read back ratio.
                                    - u16ReadBackBase: The base of read back ratio.
  
  Returns    : None
***************************************************************************************************/

static void VITC_vCalcReadBackRto(VICT_tstCalcReadBackRtoIn *pstInput, VICT_tstReadBackRto *pstOutput)
{
    if ((pstInput->enIgnOffTimeSta==CTS_nValid) && (pstInput->enOatSta==CTS_nValid))
    {
        pstOutput->u16ReadBackRto = CTS_u16Lookup2D_Limit(pstInput->u16IgnOffTime, pstInput->u16Oat, 
                                    CTS_stIgnOffReadBack.u8SizeX, CTS_stIgnOffReadBack.u8SizeY, 
                                    CTS_stIgnOffReadBack.pu16TableX, 
                                    CTS_stIgnOffReadBack.pu16TableY,
                                    CTS_stIgnOffReadBack.pu16TableZ);

        pstOutput->u16ReadBackBase = CTS_stReadBackBase.u16Const;

        pstOutput->enReadBackRtoSta = CTS_nValid;
    }
    else
    {
        pstOutput->enReadBackRtoSta = CTS_nInvalid;
    }
}


/***************************************************************************************************
  Function   : VICT_vReadBack                                               
                           
  Description: This function is used to process the read back calculation.
            
  Arguments  : pstInput         - is the address of input structure.
                                    - u16PreValue: The previous value.
                                    - u16CurValue: The current value.
                                    - u16ReadBackRto: The read back ratio.
                                    - u16ReadBackBase: The read back base input.

               pstOutput        - is the address of output structure.
                                    - u16ReadBackOut: The output of read back process.
               
  Returns    : None
***************************************************************************************************/

static void VICT_vReadBack(VICT_tstReadBackIn *pstInput, VICT_tstReadBackOut *pstOutput)
{
    cuint32 u32ReadBackOut;

    if (pstInput->u16ReadBackRto < pstInput->u16ReadBackBase)
    {
        u32ReadBackOut = (cuint32)pstInput->u16ReadBackBase - (cuint32)pstInput->u16ReadBackRto;
        u32ReadBackOut *= (cuint32)pstInput->u16CurValue;
        u32ReadBackOut += (cuint32)pstInput->u16PreValue * (cuint32)pstInput->u16ReadBackRto;
        u32ReadBackOut /= pstInput->u16ReadBackBase;
        
        pstOutput->u16ReadBackOut = CTS_u16U32ToU16(u32ReadBackOut);
    }
    else
    {
        pstOutput->u16ReadBackOut = pstInput->u16PreValue;
    }
}


/***************************************************************************************************
  Function   : VICT_vHeatItemFl                                               
  
  Description: This function is used to filter the flow field heat effect item and vehicle body      
               shell heat effect item.
            
  Arguments  : pstInput         - is the address of input structure.
                                    - pstHeatItemFl: The address of heat effect item filter 
                                                     structure.
                                    - pstHeadZoneFlTgt: The address of head zone filter target 
                                                        structure.
                                    - pstCabinFlTgt: The address of cabin filter target structure.
                                    - pstHeatItemFlFactor: The address of filter factor structure.
                                    - u8HeatItemFlShift: The heat effect item filter shift.
                                    - boSensorIctValid: The sensor ICT valid status.
                                
               pstOutput        - is the address of output structure.
                                    - enFlInitValSta: The initial filter value valid status.
                                    - enHeatItemSta: The valid status of heat effect item.
                                    - u32HeadZoneFlowItemL: The 32-bit left side head zone flow 
                                                            field heat effect item.
                                    - u32HeadZoneFlowItemR: The 32-bit right side head zone flow 
                                                            field heat effect item.
                                    - u32HeadZoneFlowItemRe: The 32-bit rear side head zone flow 
                                                             field heat effect item.
                                    - u32HeadZoneShellItem: The 32-bit head zone body shell heat 
                                                            effect item.
                                    - u32CabinFlowItem: The 32-bit cabin flow field heat effect 
                                                        item.
                                    - u32CabinShellItem: The 32-bit cabin body shell heat effect
                                                         item.
                                    - u16HeadZoneFlowItemL: The 16-bit left side head zone flow 
                                                            field heat effect item.
                                    - u16HeadZoneFlowItemR: The 16-bit right side head zone flow 
                                                            field heat effect item.
                                    - u16HeadZoneFlowItemRe: The 16-bit rear side head zone flow 
                                                             field heat effect item.
                                    - u16HeadZoneShellItem: The 16-bit head zone body shell heat 
                                                            effect item.
                                    - u16CabinFlowItem: The 16-bit cabin flow field heat effect 
                                                        item.
                                    - u16CabinShellItem: The 16-bit cabin body shell heat effect
                                                         item.
                                    
  Returns    : None
***************************************************************************************************/

static void VICT_vHeatItemFl(VICT_tstHeatItemFlIn *pstInput, VICT_tstHeatItemFl *pstOutput)
{
    VICT_tstUpdateHeatItemFlIn stUpdateHeatItemFlIn;
    VICT_tstHeatItemFl stHeatItemFl;
    cbool boEnableFl;

    stUpdateHeatItemFlIn.pstInputAddress = pstInput->pstHeatItemFl;
    stUpdateHeatItemFlIn.pstUpdateAddress = &stHeatItemFl;
    VICT_vUpdateHeatItemFl(&stUpdateHeatItemFlIn);

    if ((*pstInput->pstHeatItemFl).enFlInitValSta == CTS_nValid)
    {
        if (((*pstInput->pstHeadZoneFlTgt).enHeadZoneFlTgtSta==CTS_nValid) 
            && ((*pstInput->pstCabinFlTgt).enCabinFlTgtSta==CTS_nValid) 
            && ((*pstInput->pstHeatItemFlFactor).enHeatItemFlFactorSta==CTS_nValid))
        {
            boEnableFl = CTS_True;
        }
        else if ((pstInput->boSensorIctValid == CTS_True) 
                 && ((*pstInput->pstHeatItemFlFactor).enHeatItemFlFactorSta==CTS_nValid))
        {
            boEnableFl = CTS_True;
        }
        else
        {
            boEnableFl = CTS_False;
        }
        
        if (boEnableFl == CTS_True)
        {
            stHeatItemFl.u32HeadZoneFlowItemL = CTS_u32FirstOrderFilter(
                                                (*pstInput->pstHeatItemFl).u32HeadZoneFlowItemL, 
                                                (*pstInput->pstHeadZoneFlTgt).u16HeadZoneFlTgtL, 
                                                (*pstInput->pstHeatItemFlFactor).u16HeadZoneFlowItemFlFactorL, 
                                                pstInput->u8HeatItemFlShift);

            stHeatItemFl.u32HeadZoneFlowItemR = CTS_u32FirstOrderFilter(
                                                (*pstInput->pstHeatItemFl).u32HeadZoneFlowItemR, 
                                                (*pstInput->pstHeadZoneFlTgt).u16HeadZoneFlTgtR, 
                                                (*pstInput->pstHeatItemFlFactor).u16HeadZoneFlowItemFlFactorR, 
                                                pstInput->u8HeatItemFlShift);

            stHeatItemFl.u32HeadZoneFlowItemRe = CTS_u32FirstOrderFilter(
                                                 (*pstInput->pstHeatItemFl).u32HeadZoneFlowItemRe, 
                                                 (*pstInput->pstHeadZoneFlTgt).u16HeadZoneFlTgtRe, 
                                                 (*pstInput->pstHeatItemFlFactor).u16HeadZoneFlowItemFlFactorRe, 
                                                 pstInput->u8HeatItemFlShift);

            stHeatItemFl.u32HeadZoneShellItem = CTS_u32FirstOrderFilter(
                                                (*pstInput->pstHeatItemFl).u32HeadZoneShellItem, 
                                                (*pstInput->pstHeadZoneFlTgt).u16HeadZoneFlTgtAvg, 
                                                (*pstInput->pstHeatItemFlFactor).u16ShellItemFlFactor, 
                                                pstInput->u8HeatItemFlShift);

            stHeatItemFl.u32CabinFlowItem = CTS_u32FirstOrderFilter(
                                            (*pstInput->pstHeatItemFl).u32CabinFlowItem, 
                                            (*pstInput->pstCabinFlTgt).u16CabinFlTgt, 
                                            (*pstInput->pstHeatItemFlFactor).u16CabinFlowItemFlFactor, 
                                            pstInput->u8HeatItemFlShift);

            stHeatItemFl.u32CabinShellItem = CTS_u32FirstOrderFilter(
                                             (*pstInput->pstHeatItemFl).u32CabinShellItem, 
                                             (*pstInput->pstCabinFlTgt).u16CabinFlTgt, 
                                             (*pstInput->pstHeatItemFlFactor).u16ShellItemFlFactor, 
                                             pstInput->u8HeatItemFlShift);

            stHeatItemFl.u16HeadZoneFlowItemL = CTS_u16U32ToU16(stHeatItemFl.u32HeadZoneFlowItemL 
                                                >> pstInput->u8HeatItemFlShift);
            
            stHeatItemFl.u16HeadZoneFlowItemR = CTS_u16U32ToU16(stHeatItemFl.u32HeadZoneFlowItemR 
                                                >> pstInput->u8HeatItemFlShift);

            stHeatItemFl.u16HeadZoneFlowItemRe = CTS_u16U32ToU16(stHeatItemFl.u32HeadZoneFlowItemRe 
                                                 >> pstInput->u8HeatItemFlShift);
            
            stHeatItemFl.u16HeadZoneShellItem = CTS_u16U32ToU16(stHeatItemFl.u32HeadZoneShellItem 
                                                >> pstInput->u8HeatItemFlShift);
            
            stHeatItemFl.u16CabinFlowItem = CTS_u16U32ToU16(stHeatItemFl.u32CabinFlowItem 
                                            >> pstInput->u8HeatItemFlShift);
            
            stHeatItemFl.u16CabinShellItem = CTS_u16U32ToU16(stHeatItemFl.u32CabinShellItem 
                                             >> pstInput->u8HeatItemFlShift);

            stHeatItemFl.enHeatItemSta = VICT_nHeatItemValid;
        }
        else
        {
            stHeatItemFl.enHeatItemSta = VICT_nHeatItemLastValue;
        }
    }

    stUpdateHeatItemFlIn.pstInputAddress = &stHeatItemFl;
    stUpdateHeatItemFlIn.pstUpdateAddress = pstOutput;
    VICT_vUpdateHeatItemFl(&stUpdateHeatItemFlIn);
}


/***************************************************************************************************
  Function   : VICT_vHeatItemRtoFl                                               
                           
  Description: This function is used to process the heat effect item combine ratio filter.
            
  Arguments  : pstInput         - is the address of input structure.
                                    - enAirdModeSta: The valid status of AIRD mode.
                                    - u8AirdMode: The AIRD mode.
                                    - pstHeatItemRtoFl: The address of heat effect item ratio 
                                                        filter structure.
                                    - enFlowItemRtoFlFactorSta: The valid status of flow field heat 
                                                                effect item filter factor.
                                    - u16FlowItemRtoFlFactor: The flow field heat effect item ratio
                                                              filter factor.
                                    - u8FlowItemRtoFlShift: The flow field heat effect item ratio  
                                                            filter shift.
                                
               pstOutput        - is the address of output structure.
                                    - enFlInitValSta: The initial filter value status.
                                    - enHeatItemRtoSta: The valid status of heat effect item combine
                                                        ratio.
                                    - u32HeadZoneFlowItemRto: The 32-bit head zone flow field heat 
                                                              effect item combine ratio.
                                    - u32CabinFlowItemRto: The 32-bit cabin flow field heat effect
                                                           item combine ratio.
                                    - u8HeadZoneFlowItemRto: The 8-bit head zone flow field heat 
                                                             effect item combine ratio.  
                                    - u8HeadZoneShellItemRto: The 8-bit head zone body shell heat  
                                                              effect item combine ratio.
                                    - u8CabinFlowItemRto: The 8-bit cabin flow field heat effect 
                                                          item combine ratio.  
                                    - u8CabinShellItemRto: The 8-bit cabin body shell heat effect 
                                                           item combine ratio.

  Returns    : None
***************************************************************************************************/

static void VICT_vHeatItemRtoFl(VICT_tstHeatItemRtoFlIn *pstInput, VICT_tstHeatItemRtoFl *pstOutput)
{
    VICT_tstUpdateHeatItemRtoFlIn stUpdateHeatItemRtoFlIn;
    VICT_tstHeatItemRtoFl stHeatItemRtoFl;
    cuint8 u8HeadZoneFlowItemRto, u8HeadZoneShellItemRto, u8CabinFlowItemRto, u8CabinShellItemRto;
    cint16 i16ShellItemRto;

    stUpdateHeatItemRtoFlIn.pstInputAddress = pstInput->pstHeatItemRtoFl;
    stUpdateHeatItemRtoFlIn.pstUpdateAddress = &stHeatItemRtoFl;
    VICT_vUpdateHeatItemRtoFl(&stUpdateHeatItemRtoFlIn);
    
    if (pstInput->enAirdModeSta == CTS_nValid)
    {
        u8HeadZoneFlowItemRto = CTS_u8ReadConstArray(CTS_stHeadZoneFlowItemRto.pu8Array, 
                                CTS_stHeadZoneFlowItemRto.u8Size, pstInput->u8AirdMode);
        
        u8CabinFlowItemRto = CTS_u8ReadConstArray(CTS_stCabinFlowItemRto.pu8Array, 
                             CTS_stCabinFlowItemRto.u8Size, pstInput->u8AirdMode);

        if ((*pstInput->pstHeatItemRtoFl).enFlInitValSta == CTS_nInvalid)
        {    
            stHeatItemRtoFl.enFlInitValSta = CTS_nValid;    
            stHeatItemRtoFl.enHeatItemRtoSta = CTS_nValid;
            
            stHeatItemRtoFl.u32HeadZoneFlowItemRto = (cuint32)u8HeadZoneFlowItemRto 
                                                     << pstInput->u8FlowItemRtoFlShift;  
            
            stHeatItemRtoFl.u32CabinFlowItemRto = (cuint32)u8CabinFlowItemRto 
                                                  << pstInput->u8FlowItemRtoFlShift;
        }
        else
        {
            if (pstInput->enFlowItemRtoFlFactorSta == CTS_nValid)
            {
                stHeatItemRtoFl.enHeatItemRtoSta = CTS_nValid; 
                
                stHeatItemRtoFl.u32HeadZoneFlowItemRto = CTS_u32FirstOrderFilter(
                                                         (*pstInput->pstHeatItemRtoFl).u32HeadZoneFlowItemRto, 
                                                         (cuint16)u8HeadZoneFlowItemRto, 
                                                         pstInput->u16FlowItemRtoFlFactor, 
                                                         pstInput->u8FlowItemRtoFlShift);
                
                stHeatItemRtoFl.u32CabinFlowItemRto = CTS_u32FirstOrderFilter(
                                                      (*pstInput->pstHeatItemRtoFl).u32CabinFlowItemRto, 
                                                      (cuint16)u8CabinFlowItemRto, 
                                                      pstInput->u16FlowItemRtoFlFactor, 
                                                      pstInput->u8FlowItemRtoFlShift);
            }
            else
            {
                stHeatItemRtoFl.enHeatItemRtoSta = CTS_nInvalid; 
            }
        }

        u8HeadZoneFlowItemRto = CTS_u8U32ToU8(stHeatItemRtoFl.u32HeadZoneFlowItemRto 
                                >> pstInput->u8FlowItemRtoFlShift);
        
        i16ShellItemRto = (cint16)CTS_stFlowItemRtoBase.u8Const - (cint16)u8HeadZoneFlowItemRto;
        u8HeadZoneShellItemRto = CTS_u8I16ToU8(i16ShellItemRto, 0);

        u8CabinFlowItemRto = CTS_u8U32ToU8(stHeatItemRtoFl.u32CabinFlowItemRto 
                             >> pstInput->u8FlowItemRtoFlShift);
        
        i16ShellItemRto = (cint16)CTS_stFlowItemRtoBase.u8Const - (cint16)u8CabinFlowItemRto;
        u8CabinShellItemRto = CTS_u8I16ToU8(i16ShellItemRto, 0);
        
        stHeatItemRtoFl.u8HeadZoneFlowItemRto = u8HeadZoneFlowItemRto;
        stHeatItemRtoFl.u8HeadZoneShellItemRto = u8HeadZoneShellItemRto;
        stHeatItemRtoFl.u8CabinFlowItemRto = u8CabinFlowItemRto;
        stHeatItemRtoFl.u8CabinShellItemRto = u8CabinShellItemRto;
    }
    else
    {
        stHeatItemRtoFl.enHeatItemRtoSta = CTS_nInvalid;
    }

    stUpdateHeatItemRtoFlIn.pstInputAddress = &stHeatItemRtoFl;
    stUpdateHeatItemRtoFlIn.pstUpdateAddress = pstOutput;
    VICT_vUpdateHeatItemRtoFl(&stUpdateHeatItemRtoFlIn);
}


/***************************************************************************************************
  Function   : VICT_vHeatItemFlCor                                               
  
  Description: This function is used to correct the heat effect item filter variables according to 
               the sensor ICT.
            
  Arguments  : pstInput         - is the address of input structure.
                                    - enCabinTempSta: The valid status of cabin temperature.
                                    - u16CabinTemp: The cabin temperature.
                                    - enSensorIctSta: The valid status of sensor ICT.
                                    - u16SensorIct: The sensor ICT.
                                    - pstHeatItemFl: The address of heat effect item filter 
                                                     structure.
                                    - pstHeatItemRtoFl: The address of heat effect item ratio 
                                                      structure.
                                    - pstHeatItemFlFactor: The address of filter factor structure.
                                    - u8HeatItemFlShift: The heat effect item filter shift.
                                                        
               pstOutput        - is the address of output structure.
                                    - enFlInitValSta: The initial filter value valid status.
                                    - enHeatItemSta: The valid status of heat effect item.
                                    - u32HeadZoneFlowItemL: The 32-bit left side head zone flow 
                                                            field heat effect item.
                                    - u32HeadZoneFlowItemR: The 32-bit right side head zone flow 
                                                            field heat effect item.
                                    - u32HeadZoneFlowItemRe: The 32-bit rear side head zone flow 
                                                             field heat effect item.
                                    - u32HeadZoneShellItem: The 32-bit head zone body shell heat 
                                                            effect item.
                                    - u32CabinFlowItem: The 32-bit cabin flow field heat effect 
                                                        item.
                                    - u32CabinShellItem: The 32-bit cabin body shell heat effect
                                                         item.
                                    - u16HeadZoneFlowItemL: The 16-bit left side head zone flow 
                                                            field heat effect item.
                                    - u16HeadZoneFlowItemR: The 16-bit right side head zone flow 
                                                            field heat effect item.
                                    - u16HeadZoneFlowItemRe: The 16-bit rear side head zone flow 
                                                             field heat effect item.
                                    - u16HeadZoneShellItem: The 16-bit head zone body shell heat 
                                                            effect item.
                                    - u16CabinFlowItem: The 16-bit cabin flow field heat effect 
                                                        item.
                                    - u16CabinShellItem: The 16-bit cabin body shell heat effect
                                                         item.

  Returns    : None
***************************************************************************************************/

static void VICT_vHeatItemFlCor(VICT_tstHeatItemFlCorIn *pstInput, VICT_tstHeatItemFl *pstOutput)
{
    VICT_tstUpdateHeatItemFlIn stUpdateHeatItemFlIn;
    VICT_tstHeatItemFl stHeatItemFl;
    VICT_tstCalcCorErrIn stCalcCorErrIn;
    VICT_tstCorErr stCorErr;
    cint32 i32Buffer, i32CabinZoneBase, i32CabinHeatItemRtoBase; 
    cint32 i32HeadZoneFlowItemOfsL, i32HeadZoneFlowItemOfsR, i32HeadZoneFlowItemOfsRe;
    cint32 i32CabinFlowItemOfs, i32ShellItemOfs;
    cint32 i32HeadZoneFlowItemL, i32HeadZoneFlowItemR, i32HeadZoneFlowItemRe, i32HeadZoneShellItem;
    cint32 i32CabinFlowItem, i32CabinShellItem;
    /* cint32 i32FilterBase = CTS_i32U32ToI32(((cuint32)0x00000001)<<pstInput->u8HeatItemFlShift); */
    cint32 i32FilterBase = CTS_i32U32ToI32(((cuint32)0x00000001)<<9);/*160907*/

    stUpdateHeatItemFlIn.pstInputAddress = pstInput->pstHeatItemFl;
    stUpdateHeatItemFlIn.pstUpdateAddress = &stHeatItemFl;
    VICT_vUpdateHeatItemFl(&stUpdateHeatItemFlIn);

    stCalcCorErrIn.enCabinTempSta = pstInput->enCabinTempSta;
    stCalcCorErrIn.u16CabinTemp = pstInput->u16CabinTemp;
    stCalcCorErrIn.enSensorIctSta = pstInput->enSensorIctSta;
    stCalcCorErrIn.u16SensorIct = pstInput->u16SensorIct;
    VICT_vCalcCorErr(&stCalcCorErrIn, &stCorErr);

    if ((stCorErr.enCorErrSta==CTS_nValid) 
        && ((*pstInput->pstHeatItemFl).enHeatItemSta!=VICT_nHeatItemInvalid) 
        && ((*pstInput->pstHeatItemRtoFl).enHeatItemRtoSta==CTS_nValid)
        && ((*pstInput->pstHeatItemFlFactor).enHeatItemFlFactorSta==CTS_nValid))
    {
        i32CabinZoneBase = (cint32)(*pstInput->pstHeatItemRtoFl).u8CabinFlowItemRto;
        i32CabinZoneBase *= (cint32)(*pstInput->pstHeatItemFlFactor).u16CabinFlowItemFlFactor;
        
        i32Buffer = (cint32)(*pstInput->pstHeatItemRtoFl).u8CabinShellItemRto;
        i32Buffer *= (cint32)(*pstInput->pstHeatItemFlFactor).u16ShellItemFlFactor;
        
        i32CabinZoneBase += i32Buffer;

        i32CabinHeatItemRtoBase = (cint32)(*pstInput->pstHeatItemRtoFl).u8CabinFlowItemRto;
        i32CabinHeatItemRtoBase += (cint32)(*pstInput->pstHeatItemRtoFl).u8CabinShellItemRto;

        i32Buffer = (cint32)stCorErr.i16CorErr * i32CabinHeatItemRtoBase * i32FilterBase;
            
        i32HeadZoneFlowItemOfsL = (cint32)(*pstInput->pstHeatItemFlFactor).u16HeadZoneFlowItemFlFactorL;
        i32HeadZoneFlowItemOfsL = (i32Buffer*i32HeadZoneFlowItemOfsL) / i32CabinZoneBase;/*160907*/
                   
        i32HeadZoneFlowItemOfsR = (cint32)(*pstInput->pstHeatItemFlFactor).u16HeadZoneFlowItemFlFactorR;
        i32HeadZoneFlowItemOfsR = (i32Buffer*i32HeadZoneFlowItemOfsR) / i32CabinZoneBase;  /*160907*/

        i32HeadZoneFlowItemOfsRe = (cint32)(*pstInput->pstHeatItemFlFactor).u16HeadZoneFlowItemFlFactorRe;
        i32HeadZoneFlowItemOfsRe = (i32Buffer*i32HeadZoneFlowItemOfsRe) / i32CabinZoneBase; /*160907*/ 

        i32CabinFlowItemOfs = (cint32)(*pstInput->pstHeatItemFlFactor).u16CabinFlowItemFlFactor;
        i32CabinFlowItemOfs = (i32Buffer*i32CabinFlowItemOfs) / i32CabinZoneBase;/*160907*/

        i32ShellItemOfs = (cint32)(*pstInput->pstHeatItemFlFactor).u16ShellItemFlFactor;
        i32ShellItemOfs = (i32Buffer*i32ShellItemOfs) / i32CabinZoneBase;/*160907*/

        i32HeadZoneFlowItemL = CTS_i32U32ToI32((*pstInput->pstHeatItemFl).u32HeadZoneFlowItemL);
        i32HeadZoneFlowItemR = CTS_i32U32ToI32((*pstInput->pstHeatItemFl).u32HeadZoneFlowItemR);
        i32HeadZoneFlowItemRe = CTS_i32U32ToI32((*pstInput->pstHeatItemFl).u32HeadZoneFlowItemRe);
        i32HeadZoneShellItem = CTS_i32U32ToI32((*pstInput->pstHeatItemFl).u32HeadZoneShellItem);
        i32CabinFlowItem = CTS_i32U32ToI32((*pstInput->pstHeatItemFl).u32CabinFlowItem);
        i32CabinShellItem = CTS_i32U32ToI32((*pstInput->pstHeatItemFl).u32CabinShellItem);

        stHeatItemFl.enFlInitValSta = (*pstInput->pstHeatItemFl).enFlInitValSta;
        stHeatItemFl.enHeatItemSta = VICT_nHeatItemValid;
        stHeatItemFl.u32HeadZoneFlowItemL = CTS_u32i32ToU32(i32HeadZoneFlowItemL+(i32HeadZoneFlowItemOfsL*32)); /*160907*/  
        stHeatItemFl.u32HeadZoneFlowItemR = CTS_u32i32ToU32(i32HeadZoneFlowItemR+(i32HeadZoneFlowItemOfsR*32)); /*160907*/
        stHeatItemFl.u32HeadZoneFlowItemRe = CTS_u32i32ToU32(i32HeadZoneFlowItemRe+(i32HeadZoneFlowItemOfsRe*32)); /*160907*/
        stHeatItemFl.u32HeadZoneShellItem = CTS_u32i32ToU32(i32HeadZoneShellItem+(i32ShellItemOfs*32));  /*160907*/           
        stHeatItemFl.u32CabinFlowItem = CTS_u32i32ToU32(i32CabinFlowItem+(i32CabinFlowItemOfs*32));  /*160907*/          
        stHeatItemFl.u32CabinShellItem = CTS_u32i32ToU32(i32CabinShellItem+(i32ShellItemOfs*32));    /*160907*/        
        stHeatItemFl.u16HeadZoneFlowItemL = CTS_u16U32ToU16(stHeatItemFl.u32HeadZoneFlowItemL >> pstInput->u8HeatItemFlShift);
        stHeatItemFl.u16HeadZoneFlowItemR = CTS_u16U32ToU16(stHeatItemFl.u32HeadZoneFlowItemR >> pstInput->u8HeatItemFlShift);
        stHeatItemFl.u16HeadZoneFlowItemRe = CTS_u16U32ToU16(stHeatItemFl.u32HeadZoneFlowItemRe >> pstInput->u8HeatItemFlShift);
        stHeatItemFl.u16HeadZoneShellItem = CTS_u16U32ToU16(stHeatItemFl.u32HeadZoneShellItem >> pstInput->u8HeatItemFlShift);
        stHeatItemFl.u16CabinFlowItem = CTS_u16U32ToU16(stHeatItemFl.u32CabinFlowItem >> pstInput->u8HeatItemFlShift);
        stHeatItemFl.u16CabinShellItem = CTS_u16U32ToU16(stHeatItemFl.u32CabinShellItem >> pstInput->u8HeatItemFlShift); 
    }

    stUpdateHeatItemFlIn.pstInputAddress = &stHeatItemFl;
    stUpdateHeatItemFlIn.pstUpdateAddress = pstOutput;
    VICT_vUpdateHeatItemFl(&stUpdateHeatItemFlIn);
}


/***************************************************************************************************
  Function   : VICT_vCalcCorErr                                                  
                           
  Description: This function is used to calculate the corection error. 
                
  Arguments  : pstInput         - is the address of input structure.
                                    - enCabinTempSta: The valid status of cabin temperature.
                                    - u16CabinTemp: The cabin temperature.
                                    - enSensorIctSta: The valid status of sensor ICT.
                                    - u16SensorIct: The sensor ICT.
                                                        
               pstOutput        - is the address of output structure.
                                    - enCorErrSta: The valid status of correction error.
                                    - i16CorErr: The correction error output.
                                    
  Returns    : None
***************************************************************************************************/

static void VICT_vCalcCorErr(VICT_tstCalcCorErrIn *pstInput, VICT_tstCorErr *pstOutput)
{
    cint32 i32CorErr;

    if ((pstInput->enCabinTempSta==CTS_nValid) && (pstInput->enSensorIctSta==CTS_nValid))
    {
        i32CorErr = (cint32)pstInput->u16SensorIct - (cint32)pstInput->u16CabinTemp;
        
        if (i32CorErr > (cint32)CTS_stSensorIctTolerance.u16Const)
        {
            i32CorErr -= (cint32)CTS_stSensorIctTolerance.u16Const;
        }
        else if (i32CorErr < (0-(cint32)CTS_stSensorIctTolerance.u16Const))
        {
            i32CorErr += (cint32)CTS_stSensorIctTolerance.u16Const;
        }
        else
        {
            i32CorErr = 0;
        }

        pstOutput->i16CorErr = CTS_i16I32ToI16(i32CorErr);
        pstOutput->enCorErrSta = CTS_nValid;
    }
    else
    {
        pstOutput->i16CorErr = 0;
        pstOutput->enCorErrSta = CTS_nInvalid;
    }
}


/***************************************************************************************************
  Function   : VICT_vCalcZoneTemp                                               
                           
  Description: This function is used to combine the flow field heat effect item and vehicle body  
               shell heat effect item affecting element to calculate zone temperature.
            
  Arguments  : pstInput         - is the address of input structure.
                                    - pstHeatItemFl: The address of heat effect item filter 
                                                     variable.    
                                    - pstHeatItemRtoFl: The address of heat effect item combine 
                                                        ratio filter variable.
                                    - enAirdModeSta: The valid status of AIRD mode.
                                    - u8AirdMode: The AIRD mode.                   
                                
               pstOutput        - is the address of output structure.
                                    - enZoneTempSta: The valid status of zone temperature.
                                    - u16HeadZoneTempL: The left side head zone temperature.
                                    - u16HeadZoneTempR: The right side head zone temperature.
                                    - u16HeadZoneTempRe: The rear side head zone temperature.
                                    - u16BodyShellTemp: The vehicle body shell temperature.
                                    - u16CabinTemp: The cabin temperature.
  
  Returns    : None
***************************************************************************************************/

static void VICT_vCalcZoneTemp(VICT_tstCalcZoneTempIn *pstInput, VICT_tstZoneTemp *pstOutput)
{
    VICT_tstCalcSglZoneTempIn stCalcSglZoneTempIn;
    VICT_tstSglZoneTemp stHeadZoneTempL, stHeadZoneTempR, stHeadZoneTempRe, stCabinTemp;
    
    if (((*pstInput->pstHeatItemFl).enHeatItemSta!=VICT_nHeatItemInvalid)  
        && ((*pstInput->pstHeatItemRtoFl).enHeatItemRtoSta==CTS_nValid))
    {
        stCalcSglZoneTempIn.u16ShellItem = (*pstInput->pstHeatItemFl).u16HeadZoneShellItem;
        stCalcSglZoneTempIn.u8FlowItemRto = (*pstInput->pstHeatItemRtoFl).u8HeadZoneFlowItemRto;
        stCalcSglZoneTempIn.u8ShellItemRto = (*pstInput->pstHeatItemRtoFl).u8HeadZoneShellItemRto;
        
        stCalcSglZoneTempIn.u16FlowItem = (*pstInput->pstHeatItemFl).u16HeadZoneFlowItemL;   
        VICT_vCalcSglZoneTemp(&stCalcSglZoneTempIn, &stHeadZoneTempL);

        stCalcSglZoneTempIn.u16FlowItem = (*pstInput->pstHeatItemFl).u16HeadZoneFlowItemR;    
        VICT_vCalcSglZoneTemp(&stCalcSglZoneTempIn, &stHeadZoneTempR);

        stCalcSglZoneTempIn.u16FlowItem = (*pstInput->pstHeatItemFl).u16HeadZoneFlowItemRe;    
        VICT_vCalcSglZoneTemp(&stCalcSglZoneTempIn, &stHeadZoneTempRe);

        stCalcSglZoneTempIn.u16FlowItem = (*pstInput->pstHeatItemFl).u16CabinFlowItem;
        stCalcSglZoneTempIn.u16ShellItem = (*pstInput->pstHeatItemFl).u16CabinShellItem;
        stCalcSglZoneTempIn.u8FlowItemRto = (*pstInput->pstHeatItemRtoFl).u8CabinFlowItemRto;
        stCalcSglZoneTempIn.u8ShellItemRto = (*pstInput->pstHeatItemRtoFl).u8CabinShellItemRto;
        VICT_vCalcSglZoneTemp(&stCalcSglZoneTempIn, &stCabinTemp);

        pstOutput->u16HeadZoneTempL = stHeadZoneTempL.u16ZoneTemp;
        pstOutput->u16HeadZoneTempR = stHeadZoneTempR.u16ZoneTemp;
        pstOutput->u16HeadZoneTempRe = stHeadZoneTempRe.u16ZoneTemp;
        pstOutput->u16BodyShellTemp =(*pstInput->pstHeatItemFl).u16HeadZoneShellItem;
        pstOutput->u16CabinTemp = stCabinTemp.u16ZoneTemp;

        if ((*pstInput->pstHeatItemFl).enHeatItemSta == VICT_nHeatItemValid)
        {
            pstOutput->enZoneTempSta = VICT_nZoneTempValid;
        }
        else
        {
            pstOutput->enZoneTempSta = VICT_nZoneTempLastValue;
        }
    }
    else
    {
        pstOutput->enZoneTempSta = VICT_nZoneTempInvalid;
    }
}


/***************************************************************************************************
  Function   : VICT_vCalcSglZoneTemp                                               
                           
  Description: This function is used to combine the flow field heat effect item and vehicle body  
               shell heat effect item affecting element to calculate single zone temperature.
            
  Arguments  : pstInput         - is the address of input structure.
                                    - u16FlowItem: The flow field heat effect item.
                                    - u16ShellItem: The vehicle body shell heat effect item.
                                    - u8FlowItemRto: The flow field heat effect item combine ratio.
                                    - u8ShellItemRto: The vehicle body shell heat effect item  
                                                      combine ratio.
                                
               pstOutput        - is the address of output structure.
                                    - u16ZoneTemp: The zone temperature output.
  
  Returns    : None
***************************************************************************************************/

static void VICT_vCalcSglZoneTemp(VICT_tstCalcSglZoneTempIn *pstInput, VICT_tstSglZoneTemp *pstOutput)
{
    cuint32 u32ResultTemp;
    
    u32ResultTemp = (cuint32)pstInput->u16FlowItem * (cuint32)pstInput->u8FlowItemRto; 
    u32ResultTemp += (cuint32)pstInput->u16ShellItem * (cuint32)pstInput->u8ShellItemRto;
    u32ResultTemp /=  (cuint32)pstInput->u8FlowItemRto + (cuint32)pstInput->u8ShellItemRto;
    
    pstOutput->u16ZoneTemp = CTS_u16U32ToU16(u32ResultTemp);
}


/***************************************************************************************************
  Function   : VICT_vCalcHeatItemFlFactor                                       
                           
  Description: This function is used to calculate the heat effect item filter factor.
            
  Arguments  : pstInput         - is the address of input structure.
                                    - enBlowSpdSta: The valid status of blowout speed.
                                    - u16BlowSpd: The blowout speed.
                                    - enAirdModeSta: The valid status of AIRD mode.
                                    - u8AirdMode: The AIRD mode.
                                
               pstOutput        - is the address of output structure.
                                   - enHeatItemFlFactorSta: The valid status of heat effect item  
                                                            filter factors.
                                   - u16HeadZoneFlowItemFlFactorL: The left side head zone flow    
                                                                   field heat effect item filter 
                                                                   factor.
                                   - u16HeadZoneFlowItemFlFactorR: The right side head zone flow    
                                                                   field heat effect item filter 
                                                                   factor.
                                   - u16HeadZoneFlowItemFlFactorRe: The rear side head zone flow    
                                                                    field heat effect item filter 
                                                                    factor.
                                   - u16CabinFlowItemFlFactor: The cabin flow field heat effect item 
                                                               filter factor.
                                   - u16ShellItemFlFactor: The vehicle body shell heat effect item  
                                                           filter factor.
  
  Returns    : None
***************************************************************************************************/

static void VICT_vCalcHeatItemFlFactor(VICT_tstCalcHeatItemFlFactorIn *pstInput, VICT_tstHeatItemFlFactor *pstOutput)
{
    cuint16 u16HeadZoneFlFactor, u16CabinFlFactor;
    
    if (pstInput->enBlowSpdSta == CTS_nValid)
    {
        if (pstInput->u16BlowSpd != 0U)
        {
            if (pstInput->enAirdModeSta==CTS_nValid)
            {
                u16HeadZoneFlFactor = CTS_u16ReadConstArray(CTS_stHeadZoneFlowItemChg.pu16Array, 
                                      CTS_stHeadZoneFlowItemChg.u8Size, pstInput->u8AirdMode);

                u16CabinFlFactor = CTS_u16ReadConstArray(CTS_stCabinFlowItemChg.pu16Array, 
                                   CTS_stCabinFlowItemChg.u8Size, pstInput->u8AirdMode);

                pstOutput->enHeatItemFlFactorSta = CTS_nValid;
                pstOutput->u16HeadZoneFlowItemFlFactorL = u16HeadZoneFlFactor;
                pstOutput->u16HeadZoneFlowItemFlFactorR = u16HeadZoneFlFactor;
                pstOutput->u16HeadZoneFlowItemFlFactorRe = u16HeadZoneFlFactor;
                pstOutput->u16CabinFlowItemFlFactor = u16CabinFlFactor;
                pstOutput->u16ShellItemFlFactor = CTS_stShellItemChg.u16Const;
            }
            else
            {
                pstOutput->enHeatItemFlFactorSta = CTS_nInvalid;
            }
        }
        else
        {
            pstOutput->enHeatItemFlFactorSta = CTS_nValid;
            pstOutput->u16HeadZoneFlowItemFlFactorL = CTS_stShellItemChg.u16Const;
            pstOutput->u16HeadZoneFlowItemFlFactorR = CTS_stShellItemChg.u16Const;
            pstOutput->u16HeadZoneFlowItemFlFactorRe = CTS_stShellItemChg.u16Const;
            pstOutput->u16CabinFlowItemFlFactor = CTS_stShellItemChg.u16Const;
            pstOutput->u16ShellItemFlFactor = CTS_stShellItemChg.u16Const;
        }
    }
    else
    {
        pstOutput->enHeatItemFlFactorSta = CTS_nInvalid;
    }
}


/***************************************************************************************************
  Function   : VICT_vInitIncomingHeatFl                                               
                           
  Description: This function is used to process the initial incoming heat filter.
            
  Arguments  : pstInput         - is the address of input structure.
                                    - pstIncomingHeatFl: The adderss of incoming heat filter 
                                                         variables.
                                    - pstCalcInitIctIn: The address of initial ICT calculation input 
                                                        structure.
                                    - pstCalcReadBackRtoIn: The address of read back ratio 
                                                            calculation input structure.
                                    - u8BodyShellHeatFlShift: The filter shift of body shell heat.
  
               pstOutput        - is the address of output structure.
                                    - enFlInitValSta: The initial filter value valid status.
                                    - enIncomingHeatSta: The valid status of incoming heat.
                                    - u32BodyShellHeat: The body shell heat.
                                    - u16IncomingHeat: The incoming heat.
  
  Returns    : None
***************************************************************************************************/

static void VICT_vInitIncomingHeatFl(VICT_tstInitIncomingHeatFlIn *pstInput, VICT_tstIncomingHeatFl *pstOutput)
{
    VICT_tstUpdateIncomingHeatFlIn stUpdateIncomingHeatFlIn;
    VICT_tstIncomingHeatFl stIncomingHeatFl;
    VICT_tstReadBackIn stReadBackIn;
    VICT_tstReadBackOut stReadBackOut;

    stUpdateIncomingHeatFlIn.pstInputAddress = pstInput->pstIncomingHeatFl;
    stUpdateIncomingHeatFlIn.pstUpdateAddress = &stIncomingHeatFl;
    VICT_vUpdateIncomingHeatFl(&stUpdateIncomingHeatFlIn);
    
    if ((*pstInput->pstIncomingHeatFl).enFlInitValSta == CTS_nInvalid)
    {
        if (((*pstInput->pstInitIct).enInitIctSta==CTS_nValid) 
            && ((*pstInput->pstReadBackRto).enReadBackRtoSta==CTS_nValid))
        {
            stReadBackIn.u16PreValue = CTS_u16U32ToU16((*pstInput->pstIncomingHeatFl).u32BodyShellHeat 
                                       >> pstInput->u8BodyShellHeatFlShift);
            
            stReadBackIn.u16CurValue = (*pstInput->pstInitIct).u16InitHeadZoneTemp;
            stReadBackIn.u16ReadBackRto = (*pstInput->pstReadBackRto).u16ReadBackRto;
            stReadBackIn.u16ReadBackBase = (*pstInput->pstReadBackRto).u16ReadBackBase;

            VICT_vReadBack(&stReadBackIn, &stReadBackOut);

            stIncomingHeatFl.enFlInitValSta = CTS_nValid;
            stIncomingHeatFl.enIncomingHeatSta = VICT_nIncomingHeatValid;
            
            stIncomingHeatFl.u32BodyShellHeat = (cuint32)stReadBackOut.u16ReadBackOut 
                                                << pstInput->u8BodyShellHeatFlShift;

            stIncomingHeatFl.u16IncomingHeat = stReadBackOut.u16ReadBackOut;
        }
    }

    stUpdateIncomingHeatFlIn.pstInputAddress = &stIncomingHeatFl;
    stUpdateIncomingHeatFlIn.pstUpdateAddress = pstOutput;
    VICT_vUpdateIncomingHeatFl(&stUpdateIncomingHeatFlIn);
}


/***************************************************************************************************
  Function   : VICT_vIncomingHeatFl                                               
                           
  Description: This function is used to process the incoming heat filter.
            
  Arguments  : pstInput         - is the address of input structure.
                                    - pstIncomingHeatFl: The adderss of incoming heat filter 
                                                         variables.
                                    - enOatSta: The valid status of OAT.
                                    - u16Oat: The OAT.
                                    - enSunLoadHeatSta: The valid status of sun load heat.
                                    - u16SunLoadHeat: The sun load heat.
                                    - enVelEngineHeatSta: The valid status of velocity engine heat.
                                    - u16VelEngineHeat: The velocity engine heat.
                                    - enIncomingHeatFlFactorSta: The valid status of incoming heat 
                                                                 filter factor.
                                    - u16BodyShellHeatFlFactor: The filter factor of body shell 
                                                                heat.
                                    - u8BodyShellHeatFlShift: The filter shift of body shell heat.
  
               pstOutput        - is the address of output structure.
                                    - enFlInitValSta: The initial filter value valid status.
                                    - enIncomingHeatSta: The valid status of incoming heat.
                                    - u32BodyShellHeat: The body shell heat.
                                    - u16IncomingHeat: The incoming heat.
  
  Returns    : None
***************************************************************************************************/

static void VICT_vIncomingHeatFl(VICT_tstIncomingHeatFlIn *pstInput, VICT_tstIncomingHeatFl *pstOutput)
{
    VICT_tstUpdateIncomingHeatFlIn stUpdateIncomingHeatFlIn;
    VICT_tstIncomingHeatFl stIncomingHeatFl; 
    cint32 i32IncomingHeat;

    stUpdateIncomingHeatFlIn.pstInputAddress = pstInput->pstIncomingHeatFl;
    stUpdateIncomingHeatFlIn.pstUpdateAddress = &stIncomingHeatFl;
    VICT_vUpdateIncomingHeatFl(&stUpdateIncomingHeatFlIn);

    if (pstInput->enOatSta == CTS_nValid)
    {
        i32IncomingHeat = (cint32)pstInput->u16Oat;
            
        if (pstInput->enSunLoadHeatSta == CTS_nValid)
        {
            i32IncomingHeat += (cint32)pstInput->u16SunLoadHeat;
            i32IncomingHeat -= (cint32)CTS_stThermalRelativeZero.u16Const;
        }
            
        if (((*pstInput->pstIncomingHeatFl).enFlInitValSta==CTS_nValid) 
            && (pstInput->enIncomingHeatFlFactorSta==CTS_nValid))
        {
            i32IncomingHeat = (cint32)CTS_u16I32ToU16(i32IncomingHeat, 0);

            stIncomingHeatFl.u32BodyShellHeat = CTS_u32FirstOrderFilter(
                                                (*pstInput->pstIncomingHeatFl).u32BodyShellHeat, 
                                                (cuint16)i32IncomingHeat, 
                                                pstInput->u16BodyShellHeatFlFactor, 
                                                pstInput->u8BodyShellHeatFlShift);

            i32IncomingHeat = (cint32)CTS_u16U32ToU16(stIncomingHeatFl.u32BodyShellHeat 
                              >> pstInput->u8BodyShellHeatFlShift);

            stIncomingHeatFl.enIncomingHeatSta = VICT_nIncomingHeatValid;
        }
        else
        {
            stIncomingHeatFl.enIncomingHeatSta = VICT_nIncomingHeatRawValue;
        }

        if (pstInput->enVelEngineHeatSta == CTS_nValid)
        {
            i32IncomingHeat += (cint32)pstInput->u16VelEngineHeat;
            i32IncomingHeat -= (cint32)CTS_stThermalRelativeZero.u16Const;
        }

        stIncomingHeatFl.u16IncomingHeat = CTS_u16I32ToU16(i32IncomingHeat, 0);
    }
    else
    {
        stIncomingHeatFl.enIncomingHeatSta = VICT_nIncomingHeatInvalid;
    }

    stUpdateIncomingHeatFlIn.pstInputAddress = &stIncomingHeatFl;
    stUpdateIncomingHeatFlIn.pstUpdateAddress = pstOutput;
    VICT_vUpdateIncomingHeatFl(&stUpdateIncomingHeatFlIn);
}


/***************************************************************************************************
  Function   : VICT_vCalcHeadZoneFlTgt                                               
                           
  Description: This function is used to calculate head zone filter target.
            
  Arguments  : pstInput         - is the address of input structure.
                                    - enIncomingHeatSta: The valid status of incoming heat.
                                    - u16IncomingHeat: The incoming heat.
                                    - enBlowTempStaL: The valid status of left side blowout 
                                                      temperature.
                                    - u16BlowTempL: The left side blowout temperature.
                                    - enBlowTempStaR: The valid status of right side blowout 
                                                      temperature.
                                    - u16BlowTempR: The right side blowout temperature.
                                    - enBlowTempStaRe: The valid status of rear side blowout 
                                                       temperature.
                                    - u16BlowTempRe: The rear side blowout temperature.
                                    - enBlowSpdSta: The valid status of blowout speed.
                                    - u16BlowSpd: The blowout speed.
  
               pstOutput        - is the address of output structure.
                                    - enHeadZonFlTgtSta: The head zone filter target valid status.
                                    - u16HeadZoneFlTgtL: The left side head zone filter target.
                                    - u16HeadZoneFlTgtR: The right side head zone filter target.
                                    - u16HeadZoneFlTgtRe: The rear side head zone filter target.
                                    - u16HeadZoneFlTgtAvg: The average head zone filter target.
  
  Returns    : None
***************************************************************************************************/

static void VICT_vCalcHeadZoneFlTgt(VICT_tstCalcHeadZoneFlTgtIn *pstInput, VICT_tstHeadZoneFlTgt *pstOutput)
{
    CTS_tenValidSta enHeadZoneFlTgtSta;
    VICT_tstCalcSglHeadZoneFlTgtIn stCalcSglHeadZoneFlTgtIn;
    VICT_tstSglHeadZoneFlTgt stHeadZoneFlTgtL, stHeadZoneFlTgtR, stHeadZoneFlTgtRe;
    cuint32 u32HeadZoneFlTgtAvg;

    stCalcSglHeadZoneFlTgtIn.enIncomingHeatSta = pstInput->enIncomingHeatSta;
    stCalcSglHeadZoneFlTgtIn.u16IncomingHeat = pstInput->u16IncomingHeat;
    stCalcSglHeadZoneFlTgtIn.enBlowSpdSta = pstInput->enBlowSpdSta;
    stCalcSglHeadZoneFlTgtIn.u16BlowSpd = pstInput->u16BlowSpd;

    stCalcSglHeadZoneFlTgtIn.enBlowTempSta = pstInput->enBlowTempStaL;
    stCalcSglHeadZoneFlTgtIn.u16BlowTemp = pstInput->u16BlowTempL;
    VICT_vCalcSglHeadZoneFlTgt(&stCalcSglHeadZoneFlTgtIn, &stHeadZoneFlTgtL);
    
    stCalcSglHeadZoneFlTgtIn.enBlowTempSta = pstInput->enBlowTempStaR;
    stCalcSglHeadZoneFlTgtIn.u16BlowTemp = pstInput->u16BlowTempR;
    VICT_vCalcSglHeadZoneFlTgt(&stCalcSglHeadZoneFlTgtIn, &stHeadZoneFlTgtR);

    stCalcSglHeadZoneFlTgtIn.enBlowTempSta = pstInput->enBlowTempStaRe;
    stCalcSglHeadZoneFlTgtIn.u16BlowTemp = pstInput->u16BlowTempRe;
    VICT_vCalcSglHeadZoneFlTgt(&stCalcSglHeadZoneFlTgtIn, &stHeadZoneFlTgtRe);

    if ((CTS_stZoneNum.u8Const==3U) && (stHeadZoneFlTgtL.enHeadZoneFlTgtSta==CTS_nValid) 
        && (stHeadZoneFlTgtR.enHeadZoneFlTgtSta==CTS_nValid)
        && (stHeadZoneFlTgtRe.enHeadZoneFlTgtSta==CTS_nValid))
    {
        u32HeadZoneFlTgtAvg = (cuint32)stHeadZoneFlTgtL.u16HeadZoneFlTgt;
        u32HeadZoneFlTgtAvg += (cuint32)stHeadZoneFlTgtR.u16HeadZoneFlTgt;
        u32HeadZoneFlTgtAvg += (cuint32)stHeadZoneFlTgtRe.u16HeadZoneFlTgt;
        u32HeadZoneFlTgtAvg /= 3U;
        enHeadZoneFlTgtSta = CTS_nValid;
    }
    else if ((CTS_stZoneNum.u8Const==2U) && (stHeadZoneFlTgtL.enHeadZoneFlTgtSta==CTS_nValid) 
             && (stHeadZoneFlTgtR.enHeadZoneFlTgtSta==CTS_nValid))
    {
        u32HeadZoneFlTgtAvg = (cuint32)stHeadZoneFlTgtL.u16HeadZoneFlTgt;
        u32HeadZoneFlTgtAvg += (cuint32)stHeadZoneFlTgtR.u16HeadZoneFlTgt;
        u32HeadZoneFlTgtAvg /= 2U;
        stHeadZoneFlTgtRe.u16HeadZoneFlTgt = CTS_u16U32ToU16(u32HeadZoneFlTgtAvg);
        enHeadZoneFlTgtSta = CTS_nValid;
    }
    else if ((CTS_stZoneNum.u8Const==1U) && (stHeadZoneFlTgtL.enHeadZoneFlTgtSta==CTS_nValid)) 
    {
        u32HeadZoneFlTgtAvg = (cuint32)stHeadZoneFlTgtL.u16HeadZoneFlTgt;
        stHeadZoneFlTgtR.u16HeadZoneFlTgt = stHeadZoneFlTgtL.u16HeadZoneFlTgt;
        stHeadZoneFlTgtRe.u16HeadZoneFlTgt = stHeadZoneFlTgtL.u16HeadZoneFlTgt;
        enHeadZoneFlTgtSta = CTS_nValid;
    }
    else
    {
        enHeadZoneFlTgtSta = CTS_nInvalid;
    }

    pstOutput->u16HeadZoneFlTgtL = stHeadZoneFlTgtL.u16HeadZoneFlTgt;
    pstOutput->u16HeadZoneFlTgtR = stHeadZoneFlTgtR.u16HeadZoneFlTgt;
    pstOutput->u16HeadZoneFlTgtRe = stHeadZoneFlTgtRe.u16HeadZoneFlTgt;
    pstOutput->u16HeadZoneFlTgtAvg = CTS_u16U32ToU16(u32HeadZoneFlTgtAvg);
    pstOutput->enHeadZoneFlTgtSta = enHeadZoneFlTgtSta;
}


/***************************************************************************************************
  Function   : VICT_vCalcSglHeadZoneFlTgt                                         
                           
  Description: This function is used to calculate the single side head zone filter target.
            
  Arguments  : pstInput         - is the address of input structure.
                                    - enBlowTempSta: The valid status of blowout temperature.
                                    - u16BlowTemp: The blowout temperature.
                                    - enIncomingHeatSta: The valid status of incoming heat.
                                    - u16IncomingHeat: The incoming heat.
                                    - enBlowSpdSta: The valid status of blowout speed.
                                    - u16BlowSpd: The blowout speed.
                                
               pstOutput        - is the address of output structure.
                                    - enHeadZoneFlTgtSta: The valid status of single side head zone 
                                                          filter target.
                                    - u16HeadZoneFlTgt: The single side head zone filter target.
  
  Returns    : None
***************************************************************************************************/

static void VICT_vCalcSglHeadZoneFlTgt(VICT_tstCalcSglHeadZoneFlTgtIn *pstInput, VICT_tstSglHeadZoneFlTgt *pstOutput)
{
    if ((pstInput->enBlowTempSta==CTS_nValid) 
        && (pstInput->enIncomingHeatSta!=VICT_nIncomingHeatInvalid)  
        && (pstInput->enBlowSpdSta==CTS_nValid))
    { 
        pstOutput->u16HeadZoneFlTgt = CTS_u16Lookup3D_Linear(pstInput->u16BlowTemp,  
                                      pstInput->u16IncomingHeat, pstInput->u16BlowSpd, 
                                      CTS_stBalanceHeadZoneTemp.u8SizeX, 
                                      CTS_stBalanceHeadZoneTemp.u8SizeY, 
                                      CTS_stBalanceHeadZoneTemp.u8SizeZ, 
                                      CTS_stBalanceHeadZoneTemp.pu16TableX, 
                                      CTS_stBalanceHeadZoneTemp.pu16TableY, 
                                      CTS_stBalanceHeadZoneTemp.pu16TableZ, 
                                      CTS_stBalanceHeadZoneTemp.pu16TableU);
        
        pstOutput->enHeadZoneFlTgtSta = CTS_nValid;
    }
    else
    {
        pstOutput->enHeadZoneFlTgtSta = CTS_nInvalid;
    }
}


/***************************************************************************************************
  Function   : VICT_vHeadZoneFlTgtCor                                               
                           
  Description: This function is used to process the head zone filter target correction.
            
  Arguments  : pstInput         - is the address of input structure.
                                    - pstHeadZoneFlTgt: The address of head zone filter target 
                                                        variables.
                                    - enAirdModeSta: The valid status of AIRD mode.
                                    - u8AirdMode: The AIRD mode.
                                
               pstOutput        - is the address of output structure.
                                    - enHeadZonFlTgtSta: The head zone filter target valid status.
                                    - u16HeadZoneFlTgtL: The left side head zone filter target.
                                    - u16HeadZoneFlTgtR: The right side head zone filter target.
                                    - u16HeadZoneFlTgtRe: The rear side head zone filter target.
                                    - u16HeadZoneFlTgtAvg: The average head zone filter target.
  
  Returns    : None
***************************************************************************************************/

static void VICT_vHeadZoneFlTgtCor(VICT_tstHeadZoneFlTgtCorIn *pstInput, VICT_tstHeadZoneFlTgt *pstOutput)
{
    cint32 i32HeadZoneFlTgtL, i32HeadZoneFlTgtR, i32HeadZoneFlTgtRe;
    cint32 i32HeadZoneFlTgtAvg, i32ZoneEffect;
    cuint8 u8DblZoneEffectFactor, u8FrontToRearEffectFactor, u8RearToFrontEffectFactor;

    i32HeadZoneFlTgtL = (cint32)(*pstInput->pstHeadZoneFlTgt).u16HeadZoneFlTgtL;
    i32HeadZoneFlTgtR = (cint32)(*pstInput->pstHeadZoneFlTgt).u16HeadZoneFlTgtR;
    i32HeadZoneFlTgtRe = (cint32)(*pstInput->pstHeadZoneFlTgt).u16HeadZoneFlTgtRe;
    i32HeadZoneFlTgtAvg = (cint32)(*pstInput->pstHeadZoneFlTgt).u16HeadZoneFlTgtAvg;

    if (pstInput->enAirdModeSta == CTS_nValid)
    {
        u8DblZoneEffectFactor = CTS_u8ReadConstArray(CTS_stDblZoneEffectFactor.pu8Array, 
                                CTS_stDblZoneEffectFactor.u8Size, pstInput->u8AirdMode);

        u8FrontToRearEffectFactor = CTS_u8ReadConstArray(CTS_stFrontToRearEffectFactor.pu8Array, 
                                    CTS_stFrontToRearEffectFactor.u8Size, pstInput->u8AirdMode);

        u8RearToFrontEffectFactor = CTS_u8ReadConstArray(CTS_stRearToFrontEffectFactor.pu8Array, 
                                    CTS_stRearToFrontEffectFactor.u8Size, pstInput->u8AirdMode);
        
        if (CTS_stZoneNum.u8Const == 3U)   
        {
            i32ZoneEffect = (i32HeadZoneFlTgtL+i32HeadZoneFlTgtR) / 2;
            i32ZoneEffect = i32ZoneEffect * (cint32)u8DblZoneEffectFactor;
            
            i32HeadZoneFlTgtL *= (cint32)CTS_stZoneEffectBase.u8Const - (cint32)u8DblZoneEffectFactor;
            i32HeadZoneFlTgtL += i32ZoneEffect;
            i32HeadZoneFlTgtL /= (cint32)CTS_stZoneEffectBase.u8Const;
            
            i32HeadZoneFlTgtR *= (cint32)CTS_stZoneEffectBase.u8Const - (cint32)u8DblZoneEffectFactor; 
            i32HeadZoneFlTgtR += i32ZoneEffect;
            i32HeadZoneFlTgtR /= (cint32)CTS_stZoneEffectBase.u8Const;

            i32ZoneEffect = (i32HeadZoneFlTgtL+i32HeadZoneFlTgtR+i32HeadZoneFlTgtRe) / 3;
            i32ZoneEffect = i32ZoneEffect * (cint32)u8RearToFrontEffectFactor;

            i32HeadZoneFlTgtL *= (cint32)CTS_stZoneEffectBase.u8Const - (cint32)u8RearToFrontEffectFactor;
            i32HeadZoneFlTgtL += i32ZoneEffect;
            i32HeadZoneFlTgtL /= (cint32)CTS_stZoneEffectBase.u8Const;
            
            i32HeadZoneFlTgtR *= (cint32)CTS_stZoneEffectBase.u8Const - (cint32)u8RearToFrontEffectFactor; 
            i32HeadZoneFlTgtR += i32ZoneEffect;
            i32HeadZoneFlTgtR /= (cint32)CTS_stZoneEffectBase.u8Const;

            i32ZoneEffect = (i32HeadZoneFlTgtL+i32HeadZoneFlTgtR) / 2;
            i32ZoneEffect = i32ZoneEffect * (cint32)u8FrontToRearEffectFactor;
            
            i32HeadZoneFlTgtRe *= (cint32)CTS_stZoneEffectBase.u8Const - (cint32)u8FrontToRearEffectFactor; 
            i32HeadZoneFlTgtRe += i32ZoneEffect;
            i32HeadZoneFlTgtRe /= (cint32)CTS_stZoneEffectBase.u8Const;
        }
        else if (CTS_stZoneNum.u8Const == 2U)
        {
            i32ZoneEffect = (i32HeadZoneFlTgtL+i32HeadZoneFlTgtR) / 2;
            i32ZoneEffect = i32ZoneEffect * (cint32)u8DblZoneEffectFactor;
            
            i32HeadZoneFlTgtL *= (cint32)CTS_stZoneEffectBase.u8Const - (cint32)u8DblZoneEffectFactor;
            i32HeadZoneFlTgtL += i32ZoneEffect;
            i32HeadZoneFlTgtL /= (cint32)CTS_stZoneEffectBase.u8Const;
            
            i32HeadZoneFlTgtR *= (cint32)CTS_stZoneEffectBase.u8Const - (cint32)u8DblZoneEffectFactor; 
            i32HeadZoneFlTgtR += i32ZoneEffect;
            i32HeadZoneFlTgtR /= (cint32)CTS_stZoneEffectBase.u8Const;

            i32HeadZoneFlTgtRe = (i32HeadZoneFlTgtL+i32HeadZoneFlTgtR) / 2;
        }
        else
        {
            i32HeadZoneFlTgtR = i32HeadZoneFlTgtL;
            i32HeadZoneFlTgtRe = i32HeadZoneFlTgtL;
        }

        i32HeadZoneFlTgtAvg = (i32HeadZoneFlTgtL+i32HeadZoneFlTgtR+i32HeadZoneFlTgtRe) / 3;
    }

    pstOutput->enHeadZoneFlTgtSta = (*pstInput->pstHeadZoneFlTgt).enHeadZoneFlTgtSta;
    pstOutput->u16HeadZoneFlTgtL = CTS_u16I32ToU16(i32HeadZoneFlTgtL, 0);
    pstOutput->u16HeadZoneFlTgtR = CTS_u16I32ToU16(i32HeadZoneFlTgtR, 0);
    pstOutput->u16HeadZoneFlTgtRe = CTS_u16I32ToU16(i32HeadZoneFlTgtRe, 0);
    pstOutput->u16HeadZoneFlTgtAvg = CTS_u16I32ToU16(i32HeadZoneFlTgtAvg, 0);
}


/***************************************************************************************************
  Function   : VICT_vCalcCabinFlTgt                                               
                           
  Description: This function is used to calculate cabin filter target.
            
  Arguments  : pstInput         - is the address of input structure.
                                    - pstHeadZoneFlTgt: The address of head zone filter target 
                                                        structure.
                                    - enSunSta: The valid status of sun.
                                    - u16Sun: The sun.
                                    - enOatSta: The valid status os OAT.
                                    - u16Oat: The OAT.
                                    - enAirdPosSta: The valid status of AIRD position.
                                    - u16AirdPos: The AIRD position.
                                
               pstOutput        - is the address of output structure.
                                    - enCabinFlTgtSta: The cabin filter target valid status.
                                    - u16CabinFlTgt: The cabin filter target.
  
  Returns    : None
***************************************************************************************************/

static void VICT_vCalcCabinFlTgt(VICT_tstCalcCabinFlTgtIn *pstInput, VICT_tstCabinFlTgt *pstOutput)
{
    VICT_tstCalcCabinTempStcOfsIn stCalcCabinTempStcOfsIn;
    VICT_tstCabinTempStcOfs stCabineTempStcOfs;
    cint32 i32CabineFlTgt;

    if ((*pstInput->pstHeadZoneFlTgt).enHeadZoneFlTgtSta == CTS_nValid)
    {
        stCalcCabinTempStcOfsIn.enSunSta = pstInput->enSunSta;
        stCalcCabinTempStcOfsIn.u16Sun = pstInput->u16Sun;
        stCalcCabinTempStcOfsIn.enOatSta = pstInput->enOatSta;
        stCalcCabinTempStcOfsIn.u16Oat = pstInput->u16Oat;
        stCalcCabinTempStcOfsIn.enAirdPosSta = pstInput->enAirdPosSta;
        stCalcCabinTempStcOfsIn.u16AirdPos = pstInput->u16AirdPos;
        VICT_vCalcCabinTempStcOfs(&stCalcCabinTempStcOfsIn, &stCabineTempStcOfs);

        pstOutput->enCabinFlTgtSta = stCabineTempStcOfs.enCabinTempStcOfsSta;
        
        i32CabineFlTgt = (cint32)(*pstInput->pstHeadZoneFlTgt).u16HeadZoneFlTgtAvg;
        i32CabineFlTgt -= (cint32)stCabineTempStcOfs.u16CabinTempStcOfs; 
        i32CabineFlTgt += (cint32)CTS_stThermalRelativeZero.u16Const;

        pstOutput->u16CabinFlTgt = CTS_u16I32ToU16(i32CabineFlTgt, 0);
    }
    else
    {
        pstOutput->enCabinFlTgtSta = CTS_nInvalid;
    }
}


/***************************************************************************************************
  Function   : VICT_vCalcCabinTempStcOfs                                         
                           
  Description: This function is used to calculate the cabin temperature static offset.
            
  Arguments  : pstInput         - is the address of input structure.
                                    - enSunSta: The valid status of sun.
                                    - u16Sun: The sun.
                                    - enOatSta: The valid status os OAT.
                                    - u16Oat: The OAT.
                                    - enAirdPosSta: The valid status of AIRD position.
                                    - u16AirdPos: The AIRD position.
                                
               pstOutput        - is the address of output structure.
                                    - enCabinTempStcOfsSta: The valid status of cabin temperature
                                                            static offset.
                                    - u16CabinTempStcOfs: The cabin temperature static offset 
                                                          output.
  
  Returns    : None
***************************************************************************************************/

static void VICT_vCalcCabinTempStcOfs(VICT_tstCalcCabinTempStcOfsIn *pstInput, VICT_tstCabinTempStcOfs *pstOutput)
{
    if ((pstInput->enSunSta==CTS_nValid) && (pstInput->enOatSta==CTS_nValid) 
        && (pstInput->enAirdPosSta==CTS_nValid))
    {   
        pstOutput->u16CabinTempStcOfs = CTS_u16Lookup3D_Limit(pstInput->u16Sun, pstInput->u16Oat, 
                                        pstInput->u16AirdPos, CTS_stCabinTempStcOfs.u8SizeX, 
                                        CTS_stCabinTempStcOfs.u8SizeY, 
                                        CTS_stCabinTempStcOfs.u8SizeZ, 
                                        CTS_stCabinTempStcOfs.pu16TableX, 
                                        CTS_stCabinTempStcOfs.pu16TableY, 
                                        CTS_stCabinTempStcOfs.pu16TableZ, 
                                        CTS_stCabinTempStcOfs.pu16TableU);

        pstOutput->enCabinTempStcOfsSta = CTS_nValid;
    }
    else
    {
        pstOutput->enCabinTempStcOfsSta = CTS_nInvalid;
    }
}


/***************************************************************************************************
  Function   : VICT_vUpdateHeatItemRtoFl                                               
  
  Description: This function is used to updete the heat effect item combine ratio filter variables.
            
  Arguments  : pstInput         - is the address of input structure.
                                    - pstInputAddress: The address of input variable.
                                    - pstUpdateAddress: The address needed to be updated.

  Returns    : None
***************************************************************************************************/

static void VICT_vUpdateHeatItemRtoFl(VICT_tstUpdateHeatItemRtoFlIn *pstInput)
{
    (*pstInput->pstUpdateAddress).enFlInitValSta = (*pstInput->pstInputAddress).enFlInitValSta;
    (*pstInput->pstUpdateAddress).enHeatItemRtoSta = (*pstInput->pstInputAddress).enHeatItemRtoSta;
    (*pstInput->pstUpdateAddress).u32HeadZoneFlowItemRto = (*pstInput->pstInputAddress).u32HeadZoneFlowItemRto;
    (*pstInput->pstUpdateAddress).u32CabinFlowItemRto = (*pstInput->pstInputAddress).u32CabinFlowItemRto;
    (*pstInput->pstUpdateAddress).u8HeadZoneFlowItemRto = (*pstInput->pstInputAddress).u8HeadZoneFlowItemRto;  
    (*pstInput->pstUpdateAddress).u8HeadZoneShellItemRto = (*pstInput->pstInputAddress).u8HeadZoneShellItemRto;            
    (*pstInput->pstUpdateAddress).u8CabinFlowItemRto = (*pstInput->pstInputAddress).u8CabinFlowItemRto;            
    (*pstInput->pstUpdateAddress).u8CabinShellItemRto = (*pstInput->pstInputAddress).u8CabinShellItemRto;           
}


/***************************************************************************************************
  Function   : VICT_vUpdateHeatItemFl                                               
  
  Description: This function is used to updete the heat effect item filter variables.
            
  Arguments  : pstInput         - is the address of input structure.
                                    - pstInputAddress: The address of input variable.
                                    - pstUpdateAddress: The address needed to be updated.

  Returns    : None
***************************************************************************************************/

static void VICT_vUpdateHeatItemFl(VICT_tstUpdateHeatItemFlIn *pstInput)
{
    (*pstInput->pstUpdateAddress).enFlInitValSta = (*pstInput->pstInputAddress).enFlInitValSta;
    (*pstInput->pstUpdateAddress).enHeatItemSta = (*pstInput->pstInputAddress).enHeatItemSta;
    (*pstInput->pstUpdateAddress).u32HeadZoneFlowItemL = (*pstInput->pstInputAddress).u32HeadZoneFlowItemL;  
    (*pstInput->pstUpdateAddress).u32HeadZoneFlowItemR = (*pstInput->pstInputAddress).u32HeadZoneFlowItemR;  
    (*pstInput->pstUpdateAddress).u32HeadZoneFlowItemRe = (*pstInput->pstInputAddress).u32HeadZoneFlowItemRe;  
    (*pstInput->pstUpdateAddress).u32HeadZoneShellItem = (*pstInput->pstInputAddress).u32HeadZoneShellItem;            
    (*pstInput->pstUpdateAddress).u32CabinFlowItem = (*pstInput->pstInputAddress).u32CabinFlowItem;           
    (*pstInput->pstUpdateAddress).u32CabinShellItem = (*pstInput->pstInputAddress).u32CabinShellItem;           
    (*pstInput->pstUpdateAddress).u16HeadZoneFlowItemL = (*pstInput->pstInputAddress).u16HeadZoneFlowItemL;
    (*pstInput->pstUpdateAddress).u16HeadZoneFlowItemR = (*pstInput->pstInputAddress).u16HeadZoneFlowItemR;
    (*pstInput->pstUpdateAddress).u16HeadZoneFlowItemRe = (*pstInput->pstInputAddress).u16HeadZoneFlowItemRe;
    (*pstInput->pstUpdateAddress).u16HeadZoneShellItem = (*pstInput->pstInputAddress).u16HeadZoneShellItem;
    (*pstInput->pstUpdateAddress).u16CabinFlowItem = (*pstInput->pstInputAddress).u16CabinFlowItem;
    (*pstInput->pstUpdateAddress).u16CabinShellItem = (*pstInput->pstInputAddress).u16CabinShellItem; 
}


/***************************************************************************************************
  Function   : VICT_vUpdateIncomingHeatFl                                               
  
  Description: This function is used to updete the incoming heat filter variables.
            
  Arguments  : pstInput         - is the address of input structure.
                                    - pstInputAddress: The address of input variable.
                                    - pstUpdateAddress: The address needed to be updated.

  Returns    : None
***************************************************************************************************/

static void VICT_vUpdateIncomingHeatFl(VICT_tstUpdateIncomingHeatFlIn *pstInput)
{
    (*pstInput->pstUpdateAddress).enFlInitValSta = (*pstInput->pstInputAddress).enFlInitValSta;
    (*pstInput->pstUpdateAddress).enIncomingHeatSta = (*pstInput->pstInputAddress).enIncomingHeatSta;
    (*pstInput->pstUpdateAddress).u32BodyShellHeat = (*pstInput->pstInputAddress).u32BodyShellHeat;
    (*pstInput->pstUpdateAddress).u16IncomingHeat = (*pstInput->pstInputAddress).u16IncomingHeat;
}


/*************************************************************************************************** 
  Function   : VICT_boGetActiveFlag                         
                       
  Description: This function is used to get the active flag.
                                                                           
  Arguments  : None    
  
  Returns    : CTS_nTrue        - In active status.
               CTS_nFalse       - It is not necessary to be in active status.
***************************************************************************************************/

cbool VICT_boGetActiveFlag(void)
{  
    return VICT_boActiveFlag;
}


/***************************************************************************************************
  Function   : VICT_enGetU16Export                                                 
                           
  Description: This function is used to get the single 16-bit export value of VICT module. 
                
  Arguments  : enIndex          - is the index of output value.  
               *pu16Output      - is the output value.
                                    
  Returns    : CTS_nValid       - The output value is ready.
               CTS_nInvalid     - The output value is not ready.
***************************************************************************************************/

CTS_tenValidSta VICT_enGetU16Export(VICT_tenu16VarIndex enIndex, cuint16 *pu16Output)
{
    CTS_tenValidSta enReturn;
    cuint16 u16Max = (cuint16)VICT_nu16Max - 1U;
        
    if (enIndex < VICT_nu16Max)
    {
        *pu16Output = VICT_astU16Output[enIndex].u16Output;
        enReturn = VICT_astU16Output[enIndex].enOutputValidSta;
    }
    else
    {
        *pu16Output = VICT_astU16Output[u16Max].u16Output;
        enReturn = VICT_astU16Output[u16Max].enOutputValidSta;
    }

    return enReturn;
}

cuint16 VICT_u16GetValue(VICT_tenu16VarIndex enIndex)
{
	cuint16 ReturnValue;
    cuint16 u16Max = (cuint16)VICT_nu16Max - 1U;
        
    if (enIndex < VICT_nu16Max)
    {
        ReturnValue = VICT_astU16Output[enIndex].u16Output;
    }
    else
    {
        ReturnValue = VICT_astU16Output[u16Max].u16Output;
    }
	return ReturnValue;
}

cuint16 VICT_u16GetValidState( VICT_tenu16VarIndex enIndex)
{
	CTS_tenValidSta ReturnValue;
    cuint16 u16Max = (cuint16)VICT_nu16Max - 1U;
        
    if (enIndex < VICT_nu16Max)
    {
        ReturnValue = VICT_astU16Output[enIndex].enOutputValidSta;
    }
    else
    {
        ReturnValue = VICT_astU16Output[u16Max].enOutputValidSta;
    }
	return (cuint8)ReturnValue;
}


/***************************************************************************************************
  EOF: VICT.c
***************************************************************************************************/
