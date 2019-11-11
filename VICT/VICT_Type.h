/***************************************************************************************************
                                     VIRTUAL IN CAR TEMPERATURE                                     

  .File Name  : VICT_Type.h
  
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

#ifndef VICT_Type
#define VICT_Type


/***************************************************************************************************
                                          TYPE DEFINITIONS                                          

  Note(s): In this section define the type definitions
***************************************************************************************************/

/* The status of heat effect items */
typedef enum 
{
    VICT_nHeatItemInvalid=0,
    VICT_nHeatItemValid,
    VICT_nHeatItemLastValue
}VICT_tenHeatItemSta;

/* The status of zone temperature */
typedef enum 
{
    VICT_nZoneTempInvalid=0,
    VICT_nZoneTempValid,
    VICT_nZoneTempLastValue
}VICT_tenZoneTempSta;

/* The status of incoming heat */
typedef enum 
{
    VICT_nIncomingHeatInvalid=0,
    VICT_nIncomingHeatValid,
    VICT_nIncomingHeatRawValue
}VICT_tenIncomingHeatSta;

/* 16-bit output structure */
typedef struct
{
    CTS_tenValidSta enOutputValidSta;
    cuint16 u16Output;
}VICT_tstU16Output;

/* Heat effect item filter variables */
typedef struct
{
    CTS_tenValidSta enFlInitValSta;
    VICT_tenHeatItemSta enHeatItemSta;
    cuint32 u32HeadZoneFlowItemL;
    cuint32 u32HeadZoneFlowItemR;
    cuint32 u32HeadZoneFlowItemRe;
    cuint32 u32HeadZoneShellItem;
    cuint32 u32CabinFlowItem;
    cuint32 u32CabinShellItem;
    cuint16 u16HeadZoneFlowItemL;
    cuint16 u16HeadZoneFlowItemR;
    cuint16 u16HeadZoneFlowItemRe;
    cuint16 u16HeadZoneShellItem; 
    cuint16 u16CabinFlowItem;
    cuint16 u16CabinShellItem;
}VICT_tstHeatItemFl;

/* Input variables for PCB ICT calculation */
typedef struct
{
    CTS_tenValidSta enPcbTempSta;
    cuint16 u16PcbTemp;
    CTS_tenValidSta enOatSta;
    cuint16 u16Oat;
}VICT_tstCalcPcbIctIn;

/* Initial ICT */
typedef struct
{
    CTS_tenValidSta enInitIctSta;
    cuint16 u16InitHeadZoneTemp;
    cuint16 u16InitCabinTemp;
    cuint16 u16InitIctConfirmCtr;
}VICT_tstInitIct;

/* Input variables for initial ICT calculation */
typedef struct
{
    CTS_tenValidSta enSensorIctSta;
    cuint16 u16SensorIct;
    VICT_tstCalcPcbIctIn *pstCalcPcbIctIn;
    VICT_tstInitIct *pstPreInitIct;
}VICT_tstCalcInitIctIn;

/* PCB ICT */
typedef struct
{
    CTS_tenValidSta enPcbIctSta;
    cuint16 u16PcbIct;
}VICT_tstPcbIct;

/* Heat effect item combine ratio filter variables */
typedef struct
{
    CTS_tenValidSta enFlInitValSta;
    CTS_tenValidSta enHeatItemRtoSta;
    cuint32 u32HeadZoneFlowItemRto;
    cuint32 u32CabinFlowItemRto;
    cuint8 u8HeadZoneFlowItemRto;
    cuint8 u8HeadZoneShellItemRto;
    cuint8 u8CabinFlowItemRto;
    cuint8 u8CabinShellItemRto;
}VICT_tstHeatItemRtoFl;

/* Head zone filter target */
typedef struct
{
    CTS_tenValidSta enHeadZoneFlTgtSta;
    cuint16 u16HeadZoneFlTgtL;
    cuint16 u16HeadZoneFlTgtR;
    cuint16 u16HeadZoneFlTgtRe;
    cuint16 u16HeadZoneFlTgtAvg;
}VICT_tstHeadZoneFlTgt;

/* Input variables for read back ratio calculation */
typedef struct
{
    CTS_tenValidSta enIgnOffTimeSta;
    cuint16 u16IgnOffTime;
    CTS_tenValidSta enOatSta;
    cuint16 u16Oat;
}VICT_tstCalcReadBackRtoIn;

/* Incoming heat filter variables */
typedef struct
{
    CTS_tenValidSta enFlInitValSta;
    VICT_tenIncomingHeatSta enIncomingHeatSta;
    cuint32 u32BodyShellHeat;
    cuint16 u16IncomingHeat;
}VICT_tstIncomingHeatFl;

/* Read back ratio */
typedef struct
{
    CTS_tenValidSta enReadBackRtoSta;
    cuint16 u16ReadBackRto;
    cuint16 u16ReadBackBase;
}VICT_tstReadBackRto;

/* Input variables for initial incoming heat calculation */
typedef struct
{
    VICT_tstIncomingHeatFl *pstIncomingHeatFl;
    VICT_tstInitIct *pstInitIct;
    VICT_tstReadBackRto *pstReadBackRto;
    cuint8 u8BodyShellHeatFlShift;
}VICT_tstInitIncomingHeatFlIn;

/* Input variables for incoming heat calculation */
typedef struct
{
    VICT_tstIncomingHeatFl *pstIncomingHeatFl;
    CTS_tenValidSta enOatSta;
    cuint16 u16Oat;
    CTS_tenValidSta enSunLoadHeatSta;
    cuint16 u16SunLoadHeat;
    CTS_tenValidSta enVelEngineHeatSta;
    cuint16 u16VelEngineHeat; 
    CTS_tenValidSta enIncomingHeatFlFactorSta;
    cuint16 u16BodyShellHeatFlFactor;
    cuint8 u8BodyShellHeatFlShift;
}VICT_tstIncomingHeatFlIn;

/* Input variablse for cabin temperature static offset calculation */
typedef struct
{
    CTS_tenValidSta enSunSta;
    cuint16 u16Sun;
    CTS_tenValidSta enOatSta;
    cuint16 u16Oat;
    CTS_tenValidSta enAirdPosSta;
    cuint16 u16AirdPos;
}VICT_tstCalcCabinTempStcOfsIn;

/* Cabin temperature static offset */
typedef struct
{
    CTS_tenValidSta enCabinTempStcOfsSta;
    cuint16 u16CabinTempStcOfs;
}VICT_tstCabinTempStcOfs;

/* Input variablse for cabin filter target calculation */
typedef struct
{
    VICT_tstHeadZoneFlTgt *pstHeadZoneFlTgt;
    CTS_tenValidSta enSunSta;
    cuint16 u16Sun;
    CTS_tenValidSta enOatSta;
    cuint16 u16Oat;
    CTS_tenValidSta enAirdPosSta;
    cuint16 u16AirdPos;
}VICT_tstCalcCabinFlTgtIn;

/* Cabin filter target */
typedef struct
{
    CTS_tenValidSta enCabinFlTgtSta;
    cuint16 u16CabinFlTgt;
}VICT_tstCabinFlTgt;

/* Input variables for heat effect item filter factor calculation */
typedef struct
{
    CTS_tenValidSta enBlowSpdSta;
    cuint16 u16BlowSpd;
    CTS_tenValidSta enAirdModeSta;
    cuint8 u8AirdMode; 
}VICT_tstCalcHeatItemFlFactorIn;

/* Heat effect item filter factor */
typedef struct
{
    CTS_tenValidSta enHeatItemFlFactorSta;
    cuint16 u16HeadZoneFlowItemFlFactorL;
    cuint16 u16HeadZoneFlowItemFlFactorR;
    cuint16 u16HeadZoneFlowItemFlFactorRe;
    cuint16 u16CabinFlowItemFlFactor;
    cuint16 u16ShellItemFlFactor;
}VICT_tstHeatItemFlFactor;

/* Input variables for initial heat effect item filter */
typedef struct
{
    VICT_tstHeatItemFl *pstHeatItemFl;
    VICT_tstInitIct *pstInitIct;
    VICT_tstReadBackRto *pstReadBackRto;
    cuint8 u8HeatItemFlShift;
}VICT_tstInitHeatItemFlIn;

/* Input variables for read back process */
typedef struct
{
    cuint16 u16PreValue;
    cuint16 u16CurValue;
    cuint16 u16ReadBackRto;
    cuint16 u16ReadBackBase;
}VICT_tstReadBackIn;

/* The output of read back process */
typedef struct
{
    cuint16 u16ReadBackOut;
}VICT_tstReadBackOut;

/* Input variables for heat effect item combine ratio filter */
typedef struct
{
    CTS_tenValidSta enAirdModeSta;
    cuint8 u8AirdMode;
    VICT_tstHeatItemRtoFl *pstHeatItemRtoFl;
    CTS_tenValidSta enFlowItemRtoFlFactorSta;
    cuint16 u16FlowItemRtoFlFactor;
    cuint8 u8FlowItemRtoFlShift;
}VICT_tstHeatItemRtoFlIn;

/* Input variables for zone temperature calculation */
typedef struct
{
    VICT_tstHeatItemFl *pstHeatItemFl;
    VICT_tstHeatItemRtoFl *pstHeatItemRtoFl;
}VICT_tstCalcZoneTempIn;

/* The zone temperature */
typedef struct
{
    VICT_tenZoneTempSta enZoneTempSta;
    cuint16 u16HeadZoneTempL;
    cuint16 u16HeadZoneTempR;
    cuint16 u16HeadZoneTempRe;
    cuint16 u16BodyShellTemp;
    cuint16 u16CabinTemp;
}VICT_tstZoneTemp;

/* Input variables for single zone temperature calculation */
typedef struct
{
    cuint16 u16FlowItem;
    cuint16 u16ShellItem; 
    cuint8 u8FlowItemRto;
    cuint8 u8ShellItemRto;
}VICT_tstCalcSglZoneTempIn;

/* The single zone temperature */
typedef struct
{
    cuint16 u16ZoneTemp;
}VICT_tstSglZoneTemp;

/* Input variables for head zone filter target correction */
typedef struct
{
    VICT_tstHeadZoneFlTgt *pstHeadZoneFlTgt;
    CTS_tenValidSta enAirdModeSta;
    cuint8 u8AirdMode;
}VICT_tstHeadZoneFlTgtCorIn;

/* Input variables for head zone filter target calculation */
typedef struct
{
    VICT_tenIncomingHeatSta enIncomingHeatSta;
    cuint16 u16IncomingHeat;
    CTS_tenValidSta enBlowTempStaL;
    cuint16 u16BlowTempL;
    CTS_tenValidSta enBlowTempStaR;
    cuint16 u16BlowTempR;
    CTS_tenValidSta enBlowTempStaRe;
    cuint16 u16BlowTempRe;
    CTS_tenValidSta enBlowSpdSta;
    cuint16 u16BlowSpd;
}VICT_tstCalcHeadZoneFlTgtIn;

/* Input variables for single side head zone filter target calculation */
typedef struct
{
    CTS_tenValidSta enBlowTempSta;
    cuint16 u16BlowTemp;
    VICT_tenIncomingHeatSta enIncomingHeatSta;
    cuint16 u16IncomingHeat;
    CTS_tenValidSta enBlowSpdSta;
    cuint16 u16BlowSpd;
}VICT_tstCalcSglHeadZoneFlTgtIn;

/* The single side head zone filter target */
typedef struct
{
    CTS_tenValidSta enHeadZoneFlTgtSta;
    cuint16 u16HeadZoneFlTgt;
}VICT_tstSglHeadZoneFlTgt;

/* Input variables for heat effect items filter */
typedef struct
{
    VICT_tstHeatItemFl *pstHeatItemFl;
    VICT_tstHeadZoneFlTgt *pstHeadZoneFlTgt;
    VICT_tstCabinFlTgt *pstCabinFlTgt;
    VICT_tstHeatItemFlFactor *pstHeatItemFlFactor; 
    cuint8 u8HeatItemFlShift;
    cbool boSensorIctValid;
}VICT_tstHeatItemFlIn;

/* Input variables for heat effect item filter variables correction */
typedef struct
{
    CTS_tenValidSta enCabinTempSta;
    cuint16 u16CabinTemp;
    CTS_tenValidSta enSensorIctSta;
    cuint16 u16SensorIct;
    VICT_tstHeatItemFl *pstHeatItemFl;
    VICT_tstHeatItemRtoFl *pstHeatItemRtoFl;
    VICT_tstHeatItemFlFactor *pstHeatItemFlFactor;
    cuint8 u8HeatItemFlShift;
}VICT_tstHeatItemFlCorIn;

/* Input variables for correction error calculation */
typedef struct
{
    CTS_tenValidSta enCabinTempSta;
    cuint16 u16CabinTemp;
    CTS_tenValidSta enSensorIctSta;
    cuint16 u16SensorIct;
}VICT_tstCalcCorErrIn;

/* Correction error */
typedef struct
{
    CTS_tenValidSta enCorErrSta;
    cint16 i16CorErr;
}VICT_tstCorErr;

/* Input variables for heat effect item filter vairables updating  */
typedef struct
{
    VICT_tstHeatItemFl *pstInputAddress;
    VICT_tstHeatItemFl *pstUpdateAddress;
}VICT_tstUpdateHeatItemFlIn;

/* Input variables for heat effect item combine ratio filter vairables updating  */
typedef struct
{
    VICT_tstHeatItemRtoFl *pstInputAddress;
    VICT_tstHeatItemRtoFl *pstUpdateAddress;
}VICT_tstUpdateHeatItemRtoFlIn;

/* Input variables for incoming heat filter vairables updating  */
typedef struct
{
    VICT_tstIncomingHeatFl *pstInputAddress;
    VICT_tstIncomingHeatFl *pstUpdateAddress;
}VICT_tstUpdateIncomingHeatFlIn;


#endif                              

/***************************************************************************************************
  EOF: VICT_Type.h
***************************************************************************************************/
