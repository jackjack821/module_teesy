/***************************************************************************************************
                           CLIMATE THERMODYNAMICS SYSTEM IMPORT INTERFACE                     

  .File Name  : CTS_Import.c
  
  .Description: This file is used to provide the import interface of climate thermodynamics system.
 
  --------------------------------------------------------------------------------------------------
    Version     Date        Author          Change
  --------------------------------------------------------------------------------------------------
    V001        2015-10-12  Chen Xiongzhi   - Creat this module.
    V002        2016-01-13  Chen Xiongzhi   - Rename for VII to CTS for automatic temperature 
                                              control strategy.
    V003        2016-01-19  Chen Xiongzhi   - Add error processing status.
    V004        2016-01-20  Chen Xiongzhi   - Rename to CTS_Import.
***************************************************************************************************/

#define CTS_Import


/***************************************************************************************************
                                            HEADER FILES                                            
***************************************************************************************************/
#include "General.h"
/* System header files */
#include "CTS_StdDef.h"
//#include "Std_Types.h"

/* Foreign header file */
#include "Oat.h"
#include "dcm.h"
#include "ACCC.h"
#include "rfa.h"
#include "bctl.h"
#include "vel.h"
#include "sun.h"
#include "evap.h"
#include "hct.h"
//#include "HAL.h"
#include "ccs.h"
//#include "NAT.h"
//#include "ICT.h"
//#include "CCP.h"
//#include "DCM_interface.h"
#include "CCP_CFG.h"
#include "Rte_internal.h"

/* Own header files */
#include "CTS_Import.h"


/***************************************************************************************************
                                        FILE LOCAL VARIABLES            
                                        
  Note(s): Define all file local variables in this section. 
***************************************************************************************************/

/*Ccp control*/
typedef enum
{
	CTS_nSetBlowoutTempDr,
	CTS_nSetBlowoutTempPs,
	CTS_nSetVictValueDr,
	CTS_nSetVictValuePs,
	CTS_nCcpForceMax
}CcpControl_CTS;

static uint8 CTS_u8CcpForceFlag=0;
static uint16 CTS_u16CcpControlData[CTS_nCcpForceMax];
#define CTS_GetCcpForceBit(index)	((CTS_u8CcpForceFlag>>index)&0x01)
#define CTS_SetCcpForceBit(index)	(CTS_u8CcpForceFlag=CTS_u8CcpForceFlag|(0x01<<index))
#define CTS_ClrCcpForceBit(index)	(CTS_u8CcpForceFlag=CTS_u8CcpForceFlag&(~(0x01<<index)))
#define CTS_ClrCcpForceByte(void)	(CTS_u8CcpForceFlag=0)


/***************************************************************************************************
  Function   : CTS_enOatImport                                                     
                           
  Description: This function is used to get the OAT.
                                
  Arguments  : pu16Output       - is the address of OAT output variable.
  
  Returns    : CTS_nValid       - The OAT is ready.
               CTS_nInvalid     - The OAT is not ready.
***************************************************************************************************/

CTS_tenValidSta CTS_enOatImport(cuint16 *pu16Output)
{
    CTS_tenValidSta Sta;
    cuint8 ValidFlag = (cuint8)OAT_u16GetValue(OAT_nu16Valid);//(cuint8)Rte_IRead_Cts_vGetRteInput_CtsGetOatValid_OatValid();

    if (ValidFlag == True)
    {
        Sta = CTS_nValid;
    }
    else
    {
        Sta = CTS_nInvalid;
    }

    *pu16Output = OAT_u16GetValue(OAT_nu16Value);//Rte_IRead_Cts_vGetRteInput_CtsGetOatValue_OatValue();
    
    return Sta;
}


/***************************************************************************************************
  Function   : CTS_enPcbTempAdImport                                                      
                           
  Description: This function is used to get the PCB temperature AD value.
                                
  Arguments  : pu16Output       - is the address of PCB temperature AD value output variable.
  
  Returns    : CTS_nValid       - The PCB temperature AD value is ready.
               CTS_nInvalid     - The PCB temperature AD value is not ready.
***************************************************************************************************/ 

CTS_tenValidSta CTS_enPcbTempAdImport(cuint16 *pu16Output)
{
    CTS_tenValidSta Sta;
    uint16 Value=600;

    //(void)Rte_Call_Cts_ReadAd_PcbTempSensor_Read(&Value);
	//Value = HAL_u16AdcGet(5U); 
    Rte_Call_IoHwAd_IoHwAd_ReadAd_PcbNtcValue_Read(&Value);
	
    *pu16Output = (cuint16)Value;

    if ((Value>20) && (Value<1000))
    {
        Sta = CTS_nValid;
    }
    else
    {
        Sta = CTS_nInvalid;
    }
    
    return Sta;
}


/***************************************************************************************************
  Function   : CTS_enMacHiLoStaLImport                                                      
                           
  Description: This function is used to get the left side MAC Hi/Lo status.
                                
  Arguments  : penOutput        - is the address of left side MAC Hi/Lo status output variable.
  
  Returns    : CTS_nValid       - The left side MAC position is ready.
               CTS_nInvalid     - The left side MAC position is not ready.
***************************************************************************************************/ 

CTS_tenValidSta CTS_enMacHiLoStaLImport(CTS_tenMacHiLoSta *penOutput)
{
    CTS_tenValidSta Sta;
    cuint8 ValidFlag = 1;//(cuint8)Rte_IRead_Cts_vGetRteInput_CtsGetDcmValid_DcmValid();
    cuint16 Value;//=HAL_u16AdcGet(7);
    Rte_Call_IoHwAd_IoHwAd_ReadAd_DcmMixMotorDrFB_Read(&Value);
	//(void)DCM_enGetU16CurrentPositionExport(0,&Value);//(cuint16)Rte_IRead_Cts_vGetRteInput_CtsGetDcmMixMotorFbAdValueDr_DcmMotorAdValue();
    
    if (1)//((ValidFlag == True)
    {
        Sta = CTS_nValid;
    }
    else
    {
        Sta = CTS_nInvalid;
    }

    if (Value < 285U)/*Low position + 20ad*/
    {
        *penOutput = CTS_nMacLo;//CTS_nMacHi;
    }
    //else if (Value < 854U)
    else if (Value > 737U)  /* lo/hi,160909,High position -20ad*/
    {
        *penOutput = CTS_nMacHi;
    }
    else
    {
        *penOutput = CTS_nMacBetweenHiLo;
    }
    
    return Sta;
}   


/***************************************************************************************************
  Function   : CTS_enMacHiLoStaRImport                                                     
                           
  Description: This function is used to get the right side MAC Hi/Lo status.
                                
  Arguments  : penOutput        - is the address of right side MAC Hi/Lo status output variable.
  
  Returns    : CTS_nValid       - The right side MAC position is ready.
               CTS_nInvalid     - The right side MAC position is not ready.
***************************************************************************************************/ 

CTS_tenValidSta CTS_enMacHiLoStaRImport(CTS_tenMacHiLoSta *penOutput)
{
    CTS_tenValidSta Sta;
    cuint8 ValidFlag = 1;//(cuint8)Rte_IRead_Cts_vGetRteInput_CtsGetDcmValid_DcmValid();
    cuint16 Value=0; 

    Rte_Call_IoHwAd_IoHwAd_ReadAd_DcmMixMotorPsFB_Read(&Value);
	//(void)DCM_enGetU16CurrentPositionExport(0,&Value);//(cuint16)Rte_IRead_Cts_vGetRteInput_CtsGetDcmMixMotorFbAdValueDr_DcmMotorAdValue();
        
    if (1)//((ValidFlag == True)
    {
        Sta = CTS_nValid;
    }
    else
    {
        Sta = CTS_nInvalid;
    }

    if (Value < 285U)/*Low position + 20ad*/
    {
        *penOutput = CTS_nMacLo;//CTS_nMacHi;
    }
    //else if (Value < 854U)
    else if (Value > 737U)  /* lo/hi,160909,High position -20ad*/
    {
        *penOutput = CTS_nMacHi;
    }
    else
    {
        *penOutput = CTS_nMacBetweenHiLo;
    }
    
    return Sta;
}  


/***************************************************************************************************
  Function   : CTS_enMacHiLoStaReImport                                                     
                           
  Description: This function is used to get the rear side MAC Hi/Lo status.
                                
  Arguments  : penOutput        - is the address of rear side MAC Hi/Lo status output variable.
  
  Returns    : CTS_nValid       - The rear side MAC position is ready.
               CTS_nInvalid     - The rear side MAC position is not ready.
***************************************************************************************************/ 

CTS_tenValidSta CTS_enMacHiLoStaReImport(CTS_tenMacHiLoSta *penOutput)
{
    CTS_tenValidSta Sta;
    cuint8 ValidFlag = 1;//(cuint8)Rte_IRead_Cts_vGetRteInput_CtsGetDcmValid_DcmValid();
    cuint16 Value=0; 
	//(void)DCM_enGetU16CurrentPositionExport(0,&Value);//(cuint16)Rte_IRead_Cts_vGetRteInput_CtsGetDcmMixMotorFbAdValueDr_DcmMotorAdValue();
        
    if (1)//((ValidFlag == True)
    {
        Sta = CTS_nValid;
    }
    else
    {
        Sta = CTS_nInvalid;
    }

    if (Value < 285U)/*Low position + 20ad*/
    {
        *penOutput = CTS_nMacLo;//CTS_nMacHi;
    }
    //else if (Value < 854U)
    else if (Value > 737U)  /* lo/hi,160909,High position -20ad*/
    {
        *penOutput = CTS_nMacHi;
    }
    else
    {
        *penOutput = CTS_nMacBetweenHiLo;
    }
    
    return Sta;
}


/***************************************************************************************************
  Function   : CTS_enAirdPosImport                                                      
                           
  Description: This function is used to get the AIRD position.
                                
  Arguments  : pu16Output       - is the address of AIRD position output variable.
  
  Returns    : CTS_nValid       - The AIRD position is ready.
               CTS_nInvalid     - The AIRD position is not ready.
***************************************************************************************************/

CTS_tenValidSta CTS_enAirdPosImport(cuint16 *pu16Output)
{
    CTS_tenValidSta Sta;
    cuint8 ValidFlag = 1;//(cuint8)Rte_IRead_Cts_vGetRteInput_CtsGetDcmValid_DcmValid();
	uint16 Value;//=HAL_u16AdcGet(10);
	Rte_Call_IoHwAd_IoHwAd_ReadAd_DcmAirdMotorFB_Read(&Value);
    if (1)//((ValidFlag == True)
    {
        Sta = CTS_nValid;
    }
    else
    {
        Sta = CTS_nInvalid;
    }
    *pu16Output = Value;
    //(void)DCM_enGetU16CurrentPositionExport(1,pu16Output);//Rte_IRead_Cts_vGetRteInput_CtsGetDcmAirdMotorFbAdValue_DcmMotorAdValue();
    
    return Sta;
}      


/***************************************************************************************************
  Function   : CTS_enRfaPosImport                                                      
                           
  Description: This function is used to get the RFA position.
                                
  Arguments  : pu16Output       - is the address of RFA position output variable.
  
  Returns    : CTS_nValid       - The RFA position is ready.
               CTS_nInvalid     - The RFA position is not ready.
***************************************************************************************************/

CTS_tenValidSta CTS_enRfaPosImport(cuint16 *pu16Output)
{
    CTS_tenValidSta Sta;
    cuint8 ValidFlag = (cuint8)RFA_u8GetValue(RFA_nu8Valid);//Rte_IRead_Cts_vGetRteInput_CtsGetRfaValid_RfaValid();
    cuint16 RfaSetPos = (cuint16)RFA_u16GetValue(RFA_nu16SetPos);//Rte_IRead_Cts_vGetRteInput_CtsGetRfaSetPos_RfaSetPos();

    if (ValidFlag == True)
    {
        Sta = CTS_nValid;
    }
    else
    {
        Sta = CTS_nInvalid;
    }

    if (RfaSetPos == 0)
    {
        *pu16Output = 200U; /*100% is fresh */
    }
    else
    {
        *pu16Output = 0U;
    }
    
    return Sta;
}    


/***************************************************************************************************
  Function   : CTS_enBlwrVoltImport                                                      
                           
  Description: This function is used to get the blower voltage.
                                
  Arguments  : pu16Output       - is the address of blower voltage output variable.
  
  Returns    : CTS_nValid       - The blower voltage is ready.
               CTS_nInvalid     - The blower voltage is not ready.
***************************************************************************************************/

CTS_tenValidSta CTS_enBlwrVoltImport(cuint16 *pu16Output)
{
    CTS_tenValidSta Sta;
    cuint8 ValidFlag = 1;//BCTL_u8GetValue(BCTL_nu8Valid);

    if (ValidFlag == True)
    {
        Sta = CTS_nValid;
    }
    else
    {
        Sta = CTS_nInvalid;
    }
    
    *pu16Output = (cuint16)BCTL_u16GetValue(BCTL_nu16TrgVlt);//Rte_IRead_Cts_vGetRteInput_CtsGetBctlBlwTarget_BctlTarget();
    
    return Sta;
}    


/***************************************************************************************************
  Function   : CTS_enVelocityImport                                                     
                           
  Description: This function is used to get the velocity.
                                
  Arguments  : pu16Output       - is the address of velocity output variable.
  
  Returns    : CTS_nValid       - The velocity is ready.
               CTS_nInvalid     - The velocity is not ready.
***************************************************************************************************/

CTS_tenValidSta CTS_enVelocityImport(cuint16 *pu16Output)
{
    CTS_tenValidSta Sta;
    cuint8 ValidFlag = VEL_u8GetValue(VEL_nu8Valid);

    if (ValidFlag == True)
    {
        Sta = CTS_nValid;
    }
    else
    {
        Sta = CTS_nInvalid;
    }
    
    *pu16Output = (cuint16)VEL_u16GetValue(VEL_nu16Velocity);//Rte_IRead_Cts_vGetRteInput_CtsGetVelVelocity_Velocity();
    
    return Sta;
}   


/***************************************************************************************************
  Function   : CTS_enRawEvapTempImport                                                     
                           
  Description: This function is used to get the raw evaporator temperature.
                                
  Arguments  : pu16Output       - is the address of raw evaporator temperature output variable.
  
  Returns    : CTS_nValid       - The raw evaporator temperature is ready.
               CTS_nInvalid     - The raw evaporator temperature is not ready.
***************************************************************************************************/

CTS_tenValidSta CTS_enRawEvapTempImport(cuint16 *pu16Output)
{
    CTS_tenValidSta Sta;
    cuint8 ValidFlag = EVAP_u8GetValue(EVAP_nu8Valid);//(cuint8)Rte_IRead_Cts_vGetRteInput_CtsGetEvapValid_EvapValid();

    if (ValidFlag == True)
    {
        Sta = CTS_nValid;
    }
    else
    {
        Sta = CTS_nInvalid;
    }
    
    *pu16Output = (cuint16)EVAP_u16GetValue(EVAP_nu16AcValue);//Rte_IRead_Cts_vGetRteInput_CtsGetEvapMacValue_EvapMacValue();
    
    return Sta;
}       


/***************************************************************************************************
  Function   : CTS_enRawHctImport                                                      
                           
  Description: This function is used to get the raw heater core entrance coolant temperature.
                                
  Arguments  : pu16Output       - is the address of raw heater core entrance coolant temperature 
                                  output variable.
  
  Returns    : CTS_nValid       - The raw heater core entrance coolant temperature is ready.
               CTS_nInvalid     - The raw heater core entrance coolant temperature is not ready.
***************************************************************************************************/

CTS_tenValidSta CTS_enRawHctImport(cuint16 *pu16Output)
{
    CTS_tenValidSta Sta;
    cuint8 ValidFlag = (cuint8)HCT_u16GetValue(HCT_nu16Valid);//(cuint8)Rte_IRead_Cts_vGetRteInput_CtsGetHctValid_HctValid();

    if (ValidFlag == True)
    {
        Sta = CTS_nValid;
    }
    else
    {
        Sta = CTS_nInvalid;
    }

    *pu16Output = (cuint16)HCT_u16GetValue(HCT_nu16Value);//Rte_IRead_Cts_vGetRteInput_CtsGetHctValue_HctTemp();
    
    if (*pu16Output > 1300)
    {
        *pu16Output  = 1300;
    }
    
    return Sta;
}     


/***************************************************************************************************
  Function   : CTS_enCcsSetTempLImport                                                      
                           
  Description: This function is used to get the left side CCS set temperature.
                                
  Arguments  : pu16Output       - is the address of left side CCS set temperature output variable.
  
  Returns    : CTS_nValid       - The left side CCS set temperature is ready.
               CTS_nInvalid     - The left side CCS set temperature is not ready.
***************************************************************************************************/

CTS_tenValidSta CTS_enSetTempLImport(cuint16 *pu16Output)
{
    CTS_tenValidSta Sta;
    cuint8 ValidFlag = CCS_u8GetValue(CCS_nu8SetTempValid);//CCS_nu8Valid);//(cuint8)Rte_IRead_Cts_vGetRteInput_CtsGetCcsValid_CcsValid();

    if (ValidFlag == True)
    {
        Sta = CTS_nValid;
    }
    else
    {
        Sta = CTS_nInvalid;
    }
    
    *pu16Output = (cuint16)CCS_u16GetValue(CCS_nu16SetTempDr);//Rte_IRead_Cts_vGetRteInput_CtsGetCcsSetTemp_CcsSetTempLeft();
    
    return Sta;
}    


/***************************************************************************************************
  Function   : CTS_enCcsSetTempRImport                                                      
                           
  Description: This function is used to get the right side CCS set temperature.
                                
  Arguments  : pu16Output       - is the address of right side CCS set temperature output variable.
  
  Returns    : CTS_nValid       - The right side CCS set temperature is ready.
               CTS_nInvalid     - The right side CCS set temperature is not ready.
***************************************************************************************************/

CTS_tenValidSta CTS_enSetTempRImport(cuint16 *pu16Output)
{
    CTS_tenValidSta Sta;
    cuint8 ValidFlag = CCS_u8GetValue(CCS_nu8SetTempValid);//CCS_nu8Valid)//(cuint8)Rte_IRead_Cts_vGetRteInput_CtsGetCcsValid_CcsValid();

    if (ValidFlag == True)
    {
        Sta = CTS_nValid;
    }
    else
    {
        Sta = CTS_nInvalid;
    }
    
    *pu16Output = (cuint16)CCS_u16GetValue(CCS_nu16SetTempPs);//Rte_IRead_Cts_vGetRteInput_CtsGetCcsSetTemp_CcsSetTempLeft();
    
    return Sta;
}  


/***************************************************************************************************
  Function   : CTS_enCcsSetTempReImport                                                      
                           
  Description: This function is used to get the rear side CCS set temperature.
                                
  Arguments  : pu16Output       - is the address of rear side CCS set temperature output variable.
  
  Returns    : CTS_nValid       - The rear side CCS set temperature is ready.
               CTS_nInvalid     - The rear side CCS set temperature is not ready.
***************************************************************************************************/

CTS_tenValidSta CTS_enSetTempReImport(cuint16 *pu16Output)
{
    CTS_tenValidSta Sta;
    cuint8 ValidFlag = CCS_u8GetValue(CCS_nu8SetTempValid);//CCS_nu8Valid)//(cuint8)Rte_IRead_Cts_vGetRteInput_CtsGetCcsValid_CcsValid();

    if (ValidFlag == True)
    {
        Sta = CTS_nValid;
    }
    else
    {
        Sta = CTS_nInvalid;
    }
    
    *pu16Output = (cuint16)CCS_u16GetValue(CCS_nu16SetTempDr);//Rte_IRead_Cts_vGetRteInput_CtsGetCcsSetTemp_CcsSetTempLeft();
    
    return Sta;
}


/***************************************************************************************************
  Function   : CTS_enRawSunLImport                                                      
                           
  Description: This function is used to get the left side raw sun intensity value.
                                
  Arguments  : pu16Output       - is the address of left side raw sun intensity output variable.
  
  Returns    : CTS_nValid       - The left side raw sun intensity value is ready.
               CTS_nInvalid     - The left side raw sun intensity value is not ready.
***************************************************************************************************/

CTS_tenValidSta CTS_enRawSunLImport(cuint16 *pu16Output)
{
    CTS_tenValidSta Sta;
    cuint8 ValidFlag = SUN_u8GetValue(SUN_nu8Valid);//(cuint8)Rte_IRead_Cts_vGetRteInput_CtsGetSunValid_SunValid();

    if (ValidFlag == True)
    {
        Sta = CTS_nValid;
    }
    else
    {
        Sta = CTS_nInvalid;
    }
    
    *pu16Output = (cuint16)SUN_u16GetValue(SUN_nu16ValueDr);//Rte_IRead_Cts_vGetRteInput_CtsGetSunValueDr_SunValueDr();
    
    return Sta;
}  


/***************************************************************************************************
  Function   : CTS_enRawSunRImport                                                     
                           
  Description: This function is used to get the right side raw sun intensity value.
                                
  Arguments  : pu16Output       - is the address of right side raw sun intensity output variable.
  
  Returns    : CTS_nValid       - The right side raw sun intensity value is ready.
               CTS_nInvalid     - The right side raw sun intensity value is not ready.
***************************************************************************************************/

CTS_tenValidSta CTS_enRawSunRImport(cuint16 *pu16Output)
{
    CTS_tenValidSta Sta;
    cuint8 ValidFlag = SUN_u8GetValue(SUN_nu8Valid);//(cuint8)Rte_IRead_Cts_vGetRteInput_CtsGetSunValid_SunValid();

    if (ValidFlag == True)
    {
        Sta = CTS_nValid;
    }
    else
    {
        Sta = CTS_nInvalid;
    }
    
    *pu16Output = (cuint16)SUN_u16GetValue(SUN_nu16ValuePs);//Rte_IRead_Cts_vGetRteInput_CtsGetSunValueDr_SunValueDr();
    
    return Sta;
}  


/***************************************************************************************************
  Function   : CTS_enSensorIctAdImport                                                    
                           
  Description: This function is used to get the sensor ICT AD value.
                                
  Arguments  : pu16Output       - is the address of sensor ICT AD value output variable.
  
  Returns    : CTS_nValid       - The sensor ICT AD value is valid.
               CTS_nInvalid     - The sensor ICT AD value is not valid.
***************************************************************************************************/

CTS_tenValidSta CTS_enSensorIctAdImport(cuint16 *pu16Output)
{
    CTS_tenValidSta Sta;
    uint16 Value=0;

    //(void)Rte_Call_Ict_IctProto_IctGetPtaResultValue_IctSensor_Read(&Value);

    if ((Value>20) && (Value<1000))
    {
        Sta = CTS_nValid;
    }
    else
    {
        Sta = CTS_nInvalid;
    }
    
    *pu16Output = (cuint16)Value;

	//Sta = CTS_nInvalid;/*only for test,160909*/
	
    return Sta;
}


/***************************************************************************************************
  Function   : CTS_enNatsValueImport                                                    
                           
  Description: This function is used to get the sensor Nats value value.
                                
  Arguments  : pu16Output       - is the address of sensor Nats value value output variable.
  
  Returns    : CTS_nValid       - The sensor Nats value value is valid.
               CTS_nInvalid     - The sensor Nats value value is not valid.
***************************************************************************************************/

CTS_tenValidSta CTS_enNatsValueImport(cuint16 *pu16Output)
{
    CTS_tenValidSta enReturn;
    uint8 NatsSensorErrCode = 0u;//NAT_u16GetValue(NAT_nu16ErrorCode);
    uint8 NatsValid=0u;//NAT_u8GetValue(NAT_nu8Valid);
    uint16 Value=0u;//NAT_u16GetValue(NAT_nu16Value);
    
    *pu16Output = (cuint16)Value;

    if ((NatsSensorErrCode==0) && (NatsValid==True))
    {
        enReturn = CTS_nValid;
    }
    else
    {
        enReturn = CTS_nInvalid;
    }
	
    return enReturn;
}


/***************************************************************************************************
  Function   : CTS_enHeaterPumpOnOffStaImport                                                      
                           
  Description: This function is used to get the heater pump on/off status.
                                
  Arguments  : pboOutput        - is the address of heater pump on/off status output variable.
  
  Returns    : CTS_nValid       - The heater pump on/off status is ready.
               CTS_nInvalid     - The heater pump on/off status is not ready.
***************************************************************************************************/

CTS_tenValidSta CTS_enHeaterPumpOnOffStaImport(CTS_tenOnOffSta *penOutput)
{
    uint16 u16EngineSpeed = 0u,u16EngineSpeedValid = 0u;
    
    u16EngineSpeed = CANAPP_u16GetValue(CANAPP_nu16EMS_EngineSpeedRPM);
    u16EngineSpeedValid = CANAPP_u16GetValue(CANAPP_nu16EMS_EngineSpeedRPMInvalid);
    
    if((u16EngineSpeed > 2000u) && (u16EngineSpeedValid == 0u))
    {
        *penOutput = CTS_nOn;
    }
    else
    {
        *penOutput = CTS_nOff;
    }
    
    return CTS_nValid;
}


/***************************************************************************************************
  Function   : CTS_enCompOnOffStaImport                                                      
                           
  Description: This function is used to get the compressor on/off status.
                                
  Arguments  : pboOutput        - is the address of compressor on/off status output variable.
  
  Returns    : CTS_nValid       - The compressor on/off status is ready.
               CTS_nInvalid     - The compressor on/off status is not ready.
***************************************************************************************************/

CTS_tenValidSta CTS_enCompOnOffStaImport(CTS_tenOnOffSta *penOutput)
{
    CTS_tenValidSta Sta;
    cuint8 ValidFlag = 1;//ACCC_u8GetValue(ACCC_nu8Valid);
    cuint8 Value = (cuint8)ACCC_u8GetValue(ACCC_nu8AcActualRequest);//Rte_IRead_Cts_vGetRteInput_CtsGetAcccActualRequest_AcccActualRequest();

    if (ValidFlag == True)
    {
        Sta = CTS_nValid;
    }
    else
    {
        Sta = CTS_nInvalid;
    }

    if (Value == True)
    {
        *penOutput = CTS_nOn;
    }
    else
    {
        *penOutput = CTS_nOff;
    }
    
    return Sta;
}


/***************************************************************************************************
  Function   : CTS_enFuelModeStaImport                                                      
                           
  Description: This function is used to get the fuel driving mode status.
                                
  Arguments  : pboOutput        - is the address of fuel driving mode status output variable.
  
  Returns    : CTS_nValid       - The fuel driving mode status is ready.
               CTS_nInvalid     - The fuel driving mode status is not ready.
***************************************************************************************************/

CTS_tenValidSta CTS_enFuelModeStaImport(cbool *pboOutput)
{
    *pboOutput = CTS_True;
    return CTS_nValid;
}


/***************************************************************************************************
  Function   : CTS_enElecModeStaImport                                                      
                           
  Description: This function is used to get the electric driving mode status.
                                
  Arguments  : pboOutput        - is the address of electric driving mode status output variable.
  
  Returns    : CTS_nValid       - The electric driving mode status is ready.
               CTS_nInvalid     - The electric driving mode status is not ready.
***************************************************************************************************/

CTS_tenValidSta CTS_enElecModeStaImport(cbool *pboOutput)
{
    *pboOutput = CTS_False;
    return CTS_nValid;
}


/***************************************************************************************************
  Function   : CTS_boUseExTgtBlowTempL                                                   
                           
  Description: This function is used to configure whether use the left side external target blowout 
               temperature.
                                
  Arguments  : None
  
  Returns    : CTS_True         - Use the left side external target blowout temperature.
               CTS_False        - Do not use the left side external target blowout temperature.
***************************************************************************************************/

cbool CTS_boUseExTgtBlowTempL(void)
{
    return CTS_GetCcpForceBit(CTS_nSetBlowoutTempDr); /*CCP conreol,160830*/
} 


/***************************************************************************************************
  Function   : CTS_enExTgtBlowTempLImport                                                      
                           
  Description: This function is used to get the left side external target blowout temperature.
                                
  Arguments  : pu16Output       - is the address of left side external target blowout temperature 
                                  output variable.
  
  Returns    : CTS_nValid       - The left side external target blowout temperature is ready.
               CTS_nInvalid     - The left side external target blowout temperature is not ready.
***************************************************************************************************/

CTS_tenValidSta CTS_enExTgtBlowTempLImport(cuint16 *pu16Output)
{
    CTS_tenValidSta Sta;
    cuint8 ValidFlag = 1;//(cuint8)Rte_IRead_Cts_vGetRteInput_CtsGetCcsValid_CcsValid();

	ValidFlag = CTS_GetCcpForceBit(CTS_nSetBlowoutTempDr);
    if (ValidFlag == True)
    {
        Sta = CTS_nValid;
    }
    else
    {
        Sta = CTS_nInvalid;
    }

    #if 0
    *pu16Output = (cuint16)Rte_IRead_Cts_vGetRteInput_CtsGetCcsBlowoutTemp_CcsBlowoutTempDr();
    #endif
    *pu16Output = CTS_u16CcpControlData[CTS_nSetBlowoutTempDr];
    
    return Sta;
}    


/***************************************************************************************************
  Function   : CTS_boUseExTgtBlowTempR                                                   
                           
  Description: This function is used to configure whether use the right side external target blowout 
               temperature.
                                
  Arguments  : None
  
  Returns    : CTS_True         - Use the right side external target blowout temperature.
               CTS_False        - Do not use the right side external target blowout temperature.
***************************************************************************************************/

cbool CTS_boUseExTgtBlowTempR(void)
{
    return CTS_GetCcpForceBit(CTS_nSetBlowoutTempPs); /*CCP conreol,160830*/
} 


/***************************************************************************************************
  Function   : CTS_enExTgtBlowTempRImport                                                      
                           
  Description: This function is used to get the right side external target blowout temperature.
                                
  Arguments  : pu16Output       - is the address of right side external target blowout temperature 
                                  output variable.
  
  Returns    : CTS_nValid       - The right side external target blowout temperature is ready.
               CTS_nInvalid     - The right side external target blowout temperature is not ready.
***************************************************************************************************/

CTS_tenValidSta CTS_enExTgtBlowTempRImport(cuint16 *pu16Output)
{
    CTS_tenValidSta Sta;
    cuint8 ValidFlag = 1;//(cuint8)Rte_IRead_Cts_vGetRteInput_CtsGetCcsValid_CcsValid();

	ValidFlag = CTS_GetCcpForceBit(CTS_nSetBlowoutTempPs);
    if (ValidFlag == True)
    {
        Sta = CTS_nValid;
    }
    else
    {
        Sta = CTS_nInvalid;
    }

    #if 0
    *pu16Output = (cuint16)Rte_IRead_Cts_vGetRteInput_CtsGetCcsBlowoutTemp_CcsBlowoutTempDr();
    #endif
    *pu16Output = CTS_u16CcpControlData[CTS_nSetBlowoutTempPs];
    
    return Sta;
}  


/***************************************************************************************************
  Function   : CTS_boUseExTgtBlowTempRe                                                      
                           
  Description: This function is used to configure whether use the rear side external target blowout 
               temperature.
                                
  Arguments  : None
  
  Returns    : CTS_True         - Use the rear side external target blowout temperature.
               CTS_False        - Do not use the rear side external target blowout temperature.
***************************************************************************************************/

cbool CTS_boUseExTgtBlowTempRe(void)
{
    return CTS_False;
} 


/***************************************************************************************************
  Function   : CTS_enExTgtBlowTempReImport                                                      
                           
  Description: This function is used to get the rear side external target blowout temperature.
                                
  Arguments  : pu16Output       - is the address of rear side external target blowout temperature 
                                  output variable.
  
  Returns    : CTS_nValid       - The rear side external target blowout temperature is ready.
               CTS_nInvalid     - The rear side external target blowout temperature is not ready.
***************************************************************************************************/

CTS_tenValidSta CTS_enExTgtBlowTempReImport(cuint16 *pu16Output)
{
    CTS_tenValidSta Sta;
    cuint8 ValidFlag = 1;//(cuint8)Rte_IRead_Cts_vGetRteInput_CtsGetCcsValid_CcsValid();

	ValidFlag = CTS_GetCcpForceBit(CTS_nSetBlowoutTempDr);
    if (ValidFlag == True)
    {
        Sta = CTS_nValid;
    }
    else
    {
        Sta = CTS_nInvalid;
    }

    #if 0
    *pu16Output = (cuint16)Rte_IRead_Cts_vGetRteInput_CtsGetCcsBlowoutTemp_CcsBlowoutTempDr();
    #endif
    *pu16Output = CTS_u16CcpControlData[CTS_nSetBlowoutTempDr];
    
    return Sta;
}


/***************************************************************************************************
  Function   : CTS_boDisIncomingHeatFl                                                      
                           
  Description: This function is used to configure whether disable incoming heat filter.
                                
  Arguments  : None
  
  Returns    : CTS_True         - Disable incoming heat filter.
               CTS_False        - Do not disable incoming heat filter.
***************************************************************************************************/

cbool CTS_boDisIncomingHeatFl(void)
{
    return CTS_GetCcpForceBit(CTS_nSetVictValueDr);
} 


/***************************************************************************************************
  Function   : CTS_boUseExHeadZoneTempL                                                      
                           
  Description: This function is used to configure whether use external left side head zone 
               temperature.
                                
  Arguments  : None
  
  Returns    : CTS_True         - Use external left side head zone temperature.
               CTS_False        - Do not use external left side head zone temperature.
***************************************************************************************************/

cbool CTS_boUseExHeadZoneTempL(void)
{
    return CTS_GetCcpForceBit(CTS_nSetVictValueDr); /*CCP conreol,160830*/
} 


/***************************************************************************************************
  Function   : CTS_enExHeadZoneTempLImport                                                      
                           
  Description: This function is used to get the left side external head zone temperature.
                                
  Arguments  : pu16Output       - is the address of left side external head zone temperature output 
                                  variable.
  
  Returns    : CTS_nValid       - The left side external head zone temperature is ready.
               CTS_nInvalid     - The left side external head zone temperature is not ready.
***************************************************************************************************/

CTS_tenValidSta CTS_enExHeadZoneTempLImport(cuint16 *pu16Output)
{
    *pu16Output = CTS_u16CcpControlData[CTS_nSetVictValueDr]; /*CCP conreol,160830*/;
    //return CTS_nInvalid;
    return CTS_nValid; /*160920*/
}     


/***************************************************************************************************
  Function   : CTS_boUseExHeadZoneTempR                                                      
                           
  Description: This function is used to configure whether use external rignt side head zone 
               temperature.
                                
  Arguments  : None
  
  Returns    : CTS_True         - Use external right side head zone temperature.
               CTS_False        - Do not use external right side head zone temperature.
***************************************************************************************************/

cbool CTS_boUseExHeadZoneTempR(void)
{
    //return CTS_False;
     return CTS_GetCcpForceBit(CTS_nSetVictValuePs); /*CCP conreol,160830*/
}


/***************************************************************************************************
  Function   : CTS_enExHeadZoneTempRImport                                                     
                           
  Description: This function is used to get the right side external head zone temperature.
                                
  Arguments  : pu16Output       - is the address of right side external head zone temperature output 
                                  variable.
  
  Returns    : CTS_nValid       - The right side external head zone temperature is ready.
               CTS_nInvalid     - The right side external head zone temperature is not ready.
***************************************************************************************************/

CTS_tenValidSta CTS_enExHeadZoneTempRImport(cuint16 *pu16Output)
{
   // *pu16Output = 0U;
   // return CTS_nInvalid;
   *pu16Output = CTS_u16CcpControlData[CTS_nSetVictValuePs]; /*CCP conreol,160830*/
    //return CTS_nInvalid;
    return CTS_nValid; /*160920*/
}  


/***************************************************************************************************
  Function   : CTS_boUseExHeadZoneTempRe                                                      
                           
  Description: This function is used to configure whether use external rear side head zone 
               temperature.
                                
  Arguments  : None
  
  Returns    : CTS_True         - Use external rear side head zone temperature.
               CTS_False        - Do not use external rear side head zone temperature.
***************************************************************************************************/

cbool CTS_boUseExHeadZoneTempRe(void)
{
    //return CTS_False;
     return CTS_GetCcpForceBit(CTS_nSetVictValueDr); /*CCP conreol,160830*/
}


/***************************************************************************************************
  Function   : CTS_enExHeadZoneTempReImport                                                     
                           
  Description: This function is used to get the rear side external head zone temperature.
                                
  Arguments  : pu16Output       - is the address of rear side external head zone temperature 
                                  output variable.
  
  Returns    : CTS_nValid       - The rear side external head zone temperature is ready.
               CTS_nInvalid     - The rear side external head zone temperature is not ready.
***************************************************************************************************/

CTS_tenValidSta CTS_enExHeadZoneTempReImport(cuint16 *pu16Output)
{
   // *pu16Output = 0U;
   // return CTS_nInvalid;
   *pu16Output = CTS_u16CcpControlData[CTS_nSetVictValueDr]; /*CCP conreol,160830*/
    //return CTS_nInvalid;
    return CTS_nValid; /*160920*/
}


/***************************************************************************************************
  Function   : CTS_boUseExBodyShellTemp                                                      
                           
  Description: This function is used to configure whether use external body shell temperature.
                                
  Arguments  : None
  
  Returns    : CTS_True         - Use external body shell temperature.
               CTS_False        - Do not use external body shell temperature.
***************************************************************************************************/

cbool CTS_boUseExBodyShellTemp(void)
{
    return CTS_False;
} 


/***************************************************************************************************
  Function   : CTS_enExBodyShellTempImport                                                      
                           
  Description: This function is used to get the external body shell temperature.
                                
  Arguments  : pu16Output       - is the address of right side external body shell temperature 
                                  output variable.
  
  Returns    : CTS_nValid       - The external body shell temperature is ready.
               CTS_nInvalid     - The external body shell temperature is not ready.
***************************************************************************************************/

CTS_tenValidSta CTS_enExBodyShellTempImport(cuint16 *pu16Output)
{
    *pu16Output = 0U;
    return CTS_nInvalid;
}    


/***************************************************************************************************
  Function   : CTS_boUseExCabinTemp                                                      
                           
  Description: This function is used to configure whether use external cabin temperature.
                                
  Arguments  : None
  
  Returns    : CTS_True         - Use external cabin temperature.
               CTS_False        - Do not use external cabin temperature.
***************************************************************************************************/

cbool CTS_boUseExCabinTemp(void)
{
    return CTS_False;
} 


/***************************************************************************************************
  Function   : CTS_enExCabinTempImport                                                      
                           
  Description: This function is used to get the external cabin temperature.
                                
  Arguments  : pu16Output       - is the address of right side external cabin temperature output 
                                  variable.
  
  Returns    : CTS_nValid       - The external cabin temperature is ready.
               CTS_nInvalid     - The external cabin temperature is not ready.
***************************************************************************************************/

CTS_tenValidSta CTS_enExCabinTempImport(cuint16 *pu16Output)
{
    *pu16Output = 0U;
    return CTS_nInvalid;
}    


/***************************************************************************************************
  Function   : CTS_boUseExIgnOffTime                                                      
                           
  Description: This function is used to configure whether use external ignition off time.
                                
  Arguments  : None
  
  Returns    : CTS_True         - Use external ignition off time.
               CTS_False        - Do not use external ignition off time.
***************************************************************************************************/

cbool CTS_boUseExIgnOffTime(void)
{
    return CTS_False;
}


/***************************************************************************************************
  Function   : CTS_enExIgnOffTimeImport                                                     
                           
  Description: This function is used to get the external ignition off time.
                                
  Arguments  : pu16Output       - is the address of external ignition off time output variable.
  
  Returns    : CTS_nValid       - The external ignition off time is ready.
               CTS_nInvalid     - The external ignition off time is not ready.
***************************************************************************************************/

CTS_tenValidSta CTS_enExIgnOffTimeImport(cuint16 *pu16Output)
{
    *pu16Output = 1U;
    return CTS_nValid;
}


/***************************************************************************************************
  Function   : CTS_boUseExBlowTempL                                                      
                           
  Description: This function is used to configure whether use the left side external blowout 
               temperature.
                                
  Arguments  : None
  
  Returns    : CTS_True         - Use the left side external blowout temperature.
               CTS_False        - Do not use the left side external blowout temperature.
***************************************************************************************************/

cbool CTS_boUseExBlowTempL(void)
{
    return CTS_False;
} 


/***************************************************************************************************
  Function   : CTS_enExBlowTempLImport                                                      
                           
  Description: This function is used to get the left side external blowout temperature.
                                
  Arguments  : pu16Output       - is the address of left side external blowout temperature output 
                                  variable.
  
  Returns    : CTS_nValid       - The left side external blowout temperature is ready.
               CTS_nInvalid     - The left side external blowout temperature is not ready.
***************************************************************************************************/

CTS_tenValidSta CTS_enExBlowTempLImport(cuint16 *pu16Output)
{
    *pu16Output = 1U;
    return CTS_nValid;
}    


/***************************************************************************************************
  Function   : CTS_boUseExBlowTempR                                                      
                           
  Description: This function is used to configure whether use the right side external blowout 
               temperature.
                                
  Arguments  : None
  
  Returns    : CTS_True         - Use the right side external blowout temperature.
               CTS_False        - Do not use the right side external blowout temperature.
***************************************************************************************************/

cbool CTS_boUseExBlowTempR(void)
{
    return CTS_False;
} 


/***************************************************************************************************
  Function   : CTS_enExBlowTempRImport                                                      
                           
  Description: This function is used to get the right side external blowout temperature.
                                
  Arguments  : pu16Output       - is the address of right side external blowout temperature output 
                                  variable.
  
  Returns    : CTS_nValid       - The right side external blowout temperature is ready.
               CTS_nInvalid     - The right side external blowout temperature is not ready.
***************************************************************************************************/

CTS_tenValidSta CTS_enExBlowTempRImport(cuint16 *pu16Output)
{
    *pu16Output = 1U;
    return CTS_nValid;
} 


/***************************************************************************************************
  Function   : CTS_boUseExBlowTempRe                                                      
                           
  Description: This function is used to configure whether use the rear side external blowout 
               temperature.
                                
  Arguments  : None
  
  Returns    : CTS_True         - Use the rear side external blowout temperature.
               CTS_False        - Do not use the rear side external blowout temperature.
***************************************************************************************************/

cbool CTS_boUseExBlowTempRe(void)
{
    return CTS_False;
} 


/***************************************************************************************************
  Function   : CTS_enExTgtBlowTempReImport                                                      
                           
  Description: This function is used to get the rear side external blowout temperature.
                                
  Arguments  : pu16Output       - is the address of rear side external blowout temperature output 
                                  variable.
  
  Returns    : CTS_nValid       - The rear side external blowout temperature is ready.
               CTS_nInvalid     - The rear side external blowout temperature is not ready.
***************************************************************************************************/

CTS_tenValidSta CTS_enExBlowTempReImport(cuint16 *pu16Output)
{
    *pu16Output = 1U;
    return CTS_nValid;
}


/***************************************************************************************************
  Function	 : CTS_u8ForceIoControl_Write														
						   
  Description: This function is used to force IO control.
								
  Arguments  : ForceIoControlWord	- is the IO control word input.
  
  Returns	 : RTE_E_OK			    - IO control force is ready.
			   RTE_E_INVALID 		- IO control force is not ready.
***************************************************************************************************/

uint8 CTS_u8ForceIoControl_Write(uint32 ForceIoControlWord)
{
	uint8 u8Result=0;//RTE_E_OK;
	tstCcpContronType CcpControlWord;
	CcpControlWord.CcpContronData=(uint16)ForceIoControlWord;
	CcpControlWord.CcpCommand=(uint8)(ForceIoControlWord>>16);
	CcpControlWord.CcpCommandFlag=(uint8)(ForceIoControlWord>>24);
	if(CcpControlWord.CcpCommandFlag==True)
	{
		switch(CcpControlWord.CcpCommand)
		{
			case 0:
				CTS_ClrCcpForceByte();
				break;
			case 1:
				CTS_SetCcpForceBit(CTS_nSetBlowoutTempDr);
				CTS_u16CcpControlData[CTS_nSetBlowoutTempDr]=CcpControlWord.CcpContronData;
				break;
			case 2:
				CTS_ClrCcpForceBit(CTS_nSetBlowoutTempDr);
				CTS_u16CcpControlData[CTS_nSetBlowoutTempDr]=0;
				break;
			case 3:
				CTS_SetCcpForceBit(CTS_nSetVictValueDr);
				CTS_u16CcpControlData[CTS_nSetVictValueDr]=CcpControlWord.CcpContronData;
				break;
			case 4:
				CTS_ClrCcpForceBit(CTS_nSetVictValueDr);
				CTS_u16CcpControlData[CTS_nSetVictValueDr]=0;
			case 5:
				CTS_SetCcpForceBit(CTS_nSetBlowoutTempPs);
				CTS_u16CcpControlData[CTS_nSetBlowoutTempPs]=CcpControlWord.CcpContronData;
				break;
			case 6:
				CTS_ClrCcpForceBit(CTS_nSetBlowoutTempPs);
				CTS_u16CcpControlData[CTS_nSetBlowoutTempPs]=0;
				break;
			case 7:
				CTS_SetCcpForceBit(CTS_nSetVictValuePs);
				CTS_u16CcpControlData[CTS_nSetVictValuePs]=CcpControlWord.CcpContronData;
				break;
			case 8:
				CTS_ClrCcpForceBit(CTS_nSetVictValuePs);
				CTS_u16CcpControlData[CTS_nSetVictValuePs]=0;
				break;
			default:
                u8Result= 1;//RTE_E_INVALID;
				break;
		}
	}
	else
	{
		CTS_ClrCcpForceByte();
	}
    return u8Result;
}


/***************************************************************************************************
  EOF: CTS_Import.c
***************************************************************************************************/
