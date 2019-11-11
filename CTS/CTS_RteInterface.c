/***************************************************************************************************
                            CLIMATE THERMODYNAMICS SYSTEM RTE INTERFACE                             
                           
  .File Name  : CTS_RetInterface.c
  
  .Description: This file is the climate thermodynamics system interface for RTE.
  
  --------------------------------------------------------------------------------------------------
    Version     Date        Author          Change
  --------------------------------------------------------------------------------------------------
    V001        2016-03-18  Chen Xiongzhi   - Creat this module.
***************************************************************************************************/

#define CTS_RteInterface


/***************************************************************************************************
                                            HEADER-FILES                                            
***************************************************************************************************/

/* System header files */
#include "CTS_StdDef.h"
#include "Std_Types.h"

/* Foreign header files */
#include "CTS_Export.h"
//#include "Rte_Cts.h"

/* Own headerfiles */
#include "CTS_RteInterface.h"


/***************************************************************************************************
  Function   : CTS_vRteReset                                                      
                           
  Description: Reset function of CTS. This function is called in the RESET container of the 
               operating system.    
                                
  Arguments  : None
  
  Returns    : None 
***************************************************************************************************/

void CTS_vRteReset(void)
{
    CTS_vReset();
}


/***************************************************************************************************
  Function   : CTS_vRteInit                                                      
                           
  Description: Initialize function of CTS. This function is called in the INIT container of the 
               operating system.
                                
  Arguments  : None
  
  Returns    : None 
***************************************************************************************************/ 

void CTS_vRteInit(void)
{
    CTS_vInit();
}


/***************************************************************************************************
  Function   : CTS_vRteDeinit                                                     
                           
  Description: De-Init function of CTS. This function is called in the DEINIT container of the 
               operating system.
                                
  Arguments  : None
  
  Returns    : None 
***************************************************************************************************/

void CTS_vRteDeinit(void)
{
    CTS_vDeinit();
}


/***************************************************************************************************
  Function   : CTS_vRte100msTask0                                                      
                           
  Description: Main task 0 of CTS. This function is called in the cyclic background task in the ON 
               status. 
            
  Arguments  : None
  
  Returns    : None 
***************************************************************************************************/

void CTS_vRte100msTask0(void)
{
    CTS_v100msTask0();
}


/***************************************************************************************************
  Function   : CTS_vRte100msTask1                                                      
                           
  Description: Main task 1 of CTS. This function is called in the cyclic background task in the ON 
               status. 
            
  Arguments  : None
  
  Returns    : None 
***************************************************************************************************/

void CTS_vRte100msTask1(void)
{
    CTS_v100msTask1();
}


/***************************************************************************************************
  Function   : CTS_vRte100msTask2                                                     
                           
  Description: Main task 2 of CTS. This function is called in the cyclic background task in the ON 
               status. 
            
  Arguments  : None
  
  Returns    : None 
***************************************************************************************************/

void CTS_vRte100msTask2(void)
{
    CTS_v100msTask2();
}


/***************************************************************************************************
  Function   : CTS_vRteActive                                                       
                           
  Description: Active function of CTS. This function is called in the cyclic background task in the 
               ACTIVE status. 
            
  Arguments  : None
  
  Returns    : None 
***************************************************************************************************/

void CTS_vRteActive(void)
{
	#if 0
    CTS_vActive();
	#endif
}


/***************************************************************************************************
  Function   : CTS_vGetRteInput                                                       
                           
  Description: This function is RTE input process function, no need to add code into this 
               function.
            
  Arguments  : None
  
  Returns    : None 
***************************************************************************************************/

void CTS_vGetRteInput(void)
{
    /* No needed to add code here. */    
}


/***************************************************************************************************
  Function   : CTS_vWriteRteOutput                                                       
                           
  Description: This function is used to write the CTS output into RTE.
            
  Arguments  : None
  
  Returns    : None 
***************************************************************************************************/

void CTS_vWriteRteOutput(void)
{
	#if 0
    cbool boActiveFlag;
    CTS_tenValidSta enSensorIctSta, enAirdModeSta, enEvapTempSta, enHctSta;
    CTS_tenValidSta enTgtBlowTempStaL, enTgtBlowTempStaR, enBlowTempStaL, enBlowTempStaR;
    CTS_tenValidSta enBlowSpdSta, enSunSta, enPcbTempSta,u8SunloadheatSta,u8VelloadheatSta;
    CTS_tenValidSta enHeadZoneTempStaL, enHeadZoneTempStaR, enBodyShellTempSta, enCabinTempSta;
    cuint8 u8AirdMode;
    cuint16 u16SensorIct, u16EvapTemp, u16Hct, u16TgtBlowTempL, u16TgtBlowTempR;
    cuint16 u16BlowTempL, u16BlowTempR, u16BlowSpd, u16Sun, u16PcbTemp;
    cuint16 u16HeadZoneTempL, u16HeadZoneTempR, u16BodyShellTemp, u16CabinTemp,u16Sunloadheat,u16Velloadheat;

    boActiveFlag = CTS_boGetActiveFlag();
    Rte_IWrite_Cts_vWriteRteOutput_CtsPutActiveFlag_CtsActiveFlag((uint8)boActiveFlag);
    
    enSensorIctSta = CTS_enGetSensorIctExport(&u16SensorIct);
    Rte_IWrite_Cts_vWriteRteOutput_CtsSensorIctValid_CtsSensorIctValid((uint8)enSensorIctSta);
    Rte_IWrite_Cts_vWriteRteOutput_CtsSensorIct_CtsSensorIct((uint16)u16SensorIct);
        
    enAirdModeSta = CTS_enGetAirdModeExport(&u8AirdMode);
    Rte_IWrite_Cts_vWriteRteOutput_CtsPutAirdModeValid_CtsAirdModeValid((uint8)enAirdModeSta);
    Rte_IWrite_Cts_vWriteRteOutput_CtsPutAirdMode_CtsAirdMode((uint8)u8AirdMode);
    
    enEvapTempSta = CTS_enGetEvapTempExport(&u16EvapTemp);
    Rte_IWrite_Cts_vWriteRteOutput_CtsEvapTempValid_CtsEvapTempValid((uint8)enEvapTempSta);
    Rte_IWrite_Cts_vWriteRteOutput_CtsEvapTemp_CtsEvapTemp((uint16)u16EvapTemp);
        
    enHctSta = CTS_enGetHctExport(&u16Hct);
    Rte_IWrite_Cts_vWriteRteOutput_CtsPutHctValid_CtsHctValid((uint8)enHctSta);
    Rte_IWrite_Cts_vWriteRteOutput_CtsPutHct_CtsHct((uint16)u16Hct);
        
    enTgtBlowTempStaL = CTS_enGetTgtBlowTempLExport(&u16TgtBlowTempL);
    Rte_IWrite_Cts_vWriteRteOutput_CtsPutTgtBlowTempLeftValid_CtsTgtBlowTempValid((uint8)enTgtBlowTempStaL);
    Rte_IWrite_Cts_vWriteRteOutput_CtsPutTgtBlowTempLeft_CtsTgtBlowTemp((uint16)u16TgtBlowTempL);
    
    enTgtBlowTempStaR = CTS_enGetTgtBlowTempRExport(&u16TgtBlowTempR);
    Rte_IWrite_Cts_vWriteRteOutput_CtsPutTgtBlowTempRightValid_CtsTgtBlowTempValid((uint8)enTgtBlowTempStaR);
    Rte_IWrite_Cts_vWriteRteOutput_CtsPutTgtBlowTempRight_CtsTgtBlowTemp((uint16)u16TgtBlowTempR);
    
    enBlowTempStaL = CTS_enGetBlowTempLExport(&u16BlowTempL);
    Rte_IWrite_Cts_vWriteRteOutput_CtsPutBlowTempLeftValid_CtsBlowTempValid((uint8)enBlowTempStaL);
    Rte_IWrite_Cts_vWriteRteOutput_CtsPutBlowTempLeft_CtsBlowTemp((uint16)u16BlowTempL);
    
    enBlowTempStaR = CTS_enGetBlowTempRExport(&u16BlowTempR);
    Rte_IWrite_Cts_vWriteRteOutput_CtsPutBlowTempRightValid_CtsBlowTempValid((uint8)enBlowTempStaR);
    Rte_IWrite_Cts_vWriteRteOutput_CtsPutBlowTempRight_CtsBlowTemp((uint16)u16BlowTempR);
    
    enBlowSpdSta = CTS_enGetBlowSpdExport(&u16BlowSpd);
    Rte_IWrite_Cts_vWriteRteOutput_CtsPutBlowSpdValid_CtsBlowSpdValid((uint8)enBlowSpdSta);
    Rte_IWrite_Cts_vWriteRteOutput_CtsPutBlowSpd_CtsBlowSpd((uint16)u16BlowSpd);
    
    enSunSta = CTS_enGetSunExport(&u16Sun);
    Rte_IWrite_Cts_vWriteRteOutput_CtsPutSunValid_CtsSunValid((uint8)enSunSta);
    Rte_IWrite_Cts_vWriteRteOutput_CtsPutSun_CtsSunValue((uint16)u16Sun);
    
    enPcbTempSta = CTS_enGetPcbTempExport(&u16PcbTemp);
    Rte_IWrite_Cts_vWriteRteOutput_CtsPutPcbTempValid_CtsPcbTempValid((uint8)enPcbTempSta);
    Rte_IWrite_Cts_vWriteRteOutput_CtsPutPcbTemp_CtsPcbTemp((uint16)u16PcbTemp);

	enPcbTempSta = CTS_enGetPcbTempAdExport(&u16PcbTemp);
	Rte_IWrite_Cts_vWriteRteOutput_CtsPutPcbSensorAdValid_CtsPcbSensorAdValid((uint8)enPcbTempSta);
	Rte_IWrite_Cts_vWriteRteOutput_CtsPutPcbSensorAd_CtsPcbSensorAd((uint16)u16PcbTemp);
	
    enHeadZoneTempStaL = CTS_enGetHeadZoneTempLExport(&u16HeadZoneTempL);
    Rte_IWrite_Cts_vWriteRteOutput_CtsPutHeadTempLeftValid_CtsHeadTempValid((uint8)enHeadZoneTempStaL);
    Rte_IWrite_Cts_vWriteRteOutput_CtsPutHeadTempLeft_CtsHeadTemp((uint16)u16HeadZoneTempL);
    
    enHeadZoneTempStaR = CTS_enGetHeadZoneTempRExport(&u16HeadZoneTempR);
    Rte_IWrite_Cts_vWriteRteOutput_CtsPutHeadTempRightValid_CtsHeadTempValid((uint8)enHeadZoneTempStaR);
    Rte_IWrite_Cts_vWriteRteOutput_CtsPutHeadTempRight_CtsHeadTemp((uint16)u16HeadZoneTempR);
    
    enBodyShellTempSta = CTS_enGetBodyShellTempExport(&u16BodyShellTemp);
    Rte_IWrite_Cts_vWriteRteOutput_CtsPutCarTempValid_CtsCarTempValid((uint8)enBodyShellTempSta);
    Rte_IWrite_Cts_vWriteRteOutput_CtsPutCarTemp_CtsCarTemp((uint16)u16BodyShellTemp);
    
    enCabinTempSta = CTS_enGetCabinTempExport(&u16CabinTemp);
    Rte_IWrite_Cts_vWriteRteOutput_CtsCabinTempValid_CtsCabinTempValid((uint8)enCabinTempSta);
    Rte_IWrite_Cts_vWriteRteOutput_CtsCabinTemp_CtsCabinTemp((uint16)u16CabinTemp);

	u8SunloadheatSta = CTS_enGetSunLoadHeatExport(&u16Sunloadheat);/*160926*/
    Rte_IWrite_Cts_vWriteRteOutput_CtsPutSunLoadHeatValid_CtsSunLoadHeatValid((uint8)u8SunloadheatSta);
    Rte_IWrite_Cts_vWriteRteOutput_CtsPutSunLoadHeat_CtsSunLoadHeat((uint16)u16Sunloadheat);

	u8VelloadheatSta = CTS_enGetVelLoadHeatExport(&u16Velloadheat);/*160926*/
    Rte_IWrite_Cts_vWriteRteOutput_CtsPutVelEngineHeattValid_CtsVelEngineHeattValid((uint8)u8VelloadheatSta);
    Rte_IWrite_Cts_vWriteRteOutput_CtsPutVelEngineHeatt_CtsVelEngineHeat((uint16)u16Velloadheat);
	#endif
}


/***************************************************************************************************
  EOF: CTS_RteInterface.c
***************************************************************************************************/
