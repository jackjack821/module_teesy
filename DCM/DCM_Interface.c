/*******************************************************************************
| Module Name: directed current motor
| File Name: DCM_Interface.c
|
|-------------------------------------------------------------------------------
|               C O P Y R I G H T
|-------------------------------------------------------------------------------
| Copyright (c) 2015 Huizhou Desay SV Automotive Co., Ltd.    All rights reserved.
|
| This software is copyright protected and proprietary to Desay SV Automotive Co., Ltd.
| Desay SV Automotive Co., Ltd grants to you only those rights as set out in the
| license conditions. All other rights remain with Desay SV Automotive Co., Ltd.
|
| REMOVAL OF THESE COMMENTS IS A VIOLATION OF THE LICENSE AGREEMENT.
|-------------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-------------------------------------------------------------------------------
| Name                                  Company
| ---------------------     ---------------------------------------
| Li Jiaye                        Desay SV Automotive Co., Ltd
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date             Ver         Author               Description
| ----------  -------  -------------  ------------------------------------------
| 2014.7.17         A0      Li jiaye         module template update. 
| 2014.8.21         A1      Li jiaye         module code updated after coding reviewed.
| 2015.3.29	        A2      Li Jiaye	     add DCM property config
| 2016.2.17         A3      Li Jiaye         module upgraded
| 2016.4.19         A4      Li Jiaye         For base code creating
| 
| 
********************************************************************************/


/*****************************************************************************
* FILE DECLARATION
*****************************************************************************/
#define DCM_Interface                          /* Name of the Module                */

/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
*****************************************************************************/
/* System-headerfiles */
#include "General.h"

/* Foreign headerfiles */
#include "Rte.h"
#include "pow.h"
#include "MAC.h"
#include "Aird.h"
#include "Rfa.h"
/* Own headerfiles */
#include "DCM_Type.h"
#include "DCM_interface.h"
#include "DCM_Cfg.h"
#include "DCM_Private.h"

static uint16 Dcm_CcpForceFlag=0u;
static uint16 Dcm_CcpControlData[Dcm_nCcpForceMax];

/*****************************************************************************
* MODULE GLOBAL CONFIGURATION CONSTANTS
*
* In this section define
* - constants to configure your module. These constants are unknown for other
*   modules
*****************************************************************************/

#ifdef DCM_WithoutRTE
uint8 DCM_u16MixMotorDrFB_Read(uint16 * value)
{
    uint8 ch=4u;
    return (uint8)MCU_u16ADCgetResault(ch,value);
}
uint8 DCM_u16AirdMotorFB_Read(uint16 * value)
{
    uint8 ch=3u;
    return (uint8)MCU_u16ADCgetResault(ch,value);
}
uint8 DCM_u16RfaMotorFB_Read(uint16 * value)
{
    uint8 ch=6u;
    return (uint8)MCU_u16ADCgetResault(ch,value);
}

#endif
uint16 Mac_u16GetTargetPosDr(void)
{
    return MAC_u16GetValue(MAC_nu16MixedAirPosDr);
}
uint16 Aird_u16GetTargetPos(void)
{
    return AIRD_u16GetValue(AIRD_nu16SetPos);
}
uint16 Rfa_u16GetTargetPos(void)
{
    return RFA_u16GetValue(RFA_nu16SetPos);
}
uint16 Mac_u16GetTargetPosPs(void)
{
    return MAC_u16GetValue(MAC_nu16MixedAirPosPs);
}


#ifdef OpenLoadEnable
tfpDriverPinSts DCM_u8GetMotorOpenLoadPin1[]=
{
    DCMspi_vGetMixDrOpenLoadSts,
    DCMspi_vGetAirdOpenLoadSts,
    DCMspi_vGetRfaOpenLoadSts
};
tfpDriverPinSts DCM_u8GetMotorOpenLoadPin2[]=
{
    DCMspi_vGetMixDrOpenLoadSts,
    DCMspi_vGetAirdOpenLoadSts,
    DCMspi_vGetRfaOpenLoadSts
};
#endif
#ifdef OverCurrentEnable
tfpDriverPinSts DCM_u8GetMotorOverCurrentPin1[]=
{
    DCMspi_vGetMixDrOverCurrentSts,
    DCMspi_vGetAirdOverCurrentSts,
    DCMspi_vGetRfaOverCurrentSts
};
tfpDriverPinSts DCM_u8GetMotorOverCurrentPin2[]=
{
    DCMspi_vGetMixDrOverCurrentSts,
    DCMspi_vGetAirdOverCurrentSts,
    DCMspi_vGetRfaOverCurrentSts
};
#endif
#ifdef OverTempEnable
#define DCM_u8GetOverTempFlag()   FunctionSpiOverTemp  
#endif

/*****************************************************************************
 Function      : Dcm_ForceIoControl_Write                                 
 Description   : Ccp control function
 Takes         : Nothing
 Return Value  : None                                                *
*****************************************************************************/
Std_ReturnType DCM_u8ForceIoControl_Write (/*IN*/uint32 ForceIoControlWord)
{
    uint8 u8ReturnValue=RTE_E_OK;
	tstCcpContronType CcpControlWord;
	CcpControlWord.CcpContronData=(uint16)ForceIoControlWord;
	CcpControlWord.CcpCommand=(uint8)(ForceIoControlWord>>16);
	CcpControlWord.CcpCommandFlag=(uint8)(ForceIoControlWord>>24);
	if(CcpControlWord.CcpCommandFlag==True)
	{
		switch(CcpControlWord.CcpCommand)
		{
			case 0:
				DcmClrCcpForceByte(void);
				break;
			case 1:
				DcmSetCcpForceBit(Dcm_nSetMixDrMotorFb);
				Dcm_CcpControlData[Dcm_nSetMixDrMotorFb]=CcpControlWord.CcpContronData;
				break;
			case 2:
				DcmClrCcpForceBit(Dcm_nSetMixDrMotorFb);
				Dcm_CcpControlData[Dcm_nSetMixDrMotorFb]=0u;
				break;
			case 3:
				DcmSetCcpForceBit(Dcm_nSetAirdMotorFb);
				Dcm_CcpControlData[Dcm_nSetAirdMotorFb]=CcpControlWord.CcpContronData;
				break;
			case 4:
				DcmClrCcpForceBit(Dcm_nSetAirdMotorFb);
				Dcm_CcpControlData[Dcm_nSetAirdMotorFb]=0u;
                break;
			default:
		        u8ReturnValue=RTE_E_INVALID;
                break;
		}
	}
	else
	{
		DcmClrCcpForceByte(void);
	}
        return u8ReturnValue;
}
/*============================================================================
*Function : void DCM_vClrForceByteFlag(void)
*Description : clear the force byte
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
void DCM_vClrForceByteFlag(void)
{
  DcmClrCcpForceByte(void);  
}


/*============================================================================
*Function : void DCM_vPutRteValue(void)
*Description : 
*takes : nothing
*return: nothing
*/
void DCM_vPutRteValue(void)
{
    uint16 au16PtaRawPosFb[MotorNum],au16PtaPosFb[MotorNum];
    DCM_tenPortState enMotorDiretion[MotorNum];
    uint8 i,u8ErrorCode[MotorNum];
    //DCM_tstState stPort;/*Release Warning,161024*/
    for(i=0u;i<(uint8)MotorNum;i++)
	{
        DCM_enGetU16CurrentPositionExport(i,&au16PtaPosFb[i]);
        DCM_enGetU16CurrentRawPositionExport(i,&au16PtaRawPosFb[i]);
        DCM_enGetEnMotorDiretionExport(i,&enMotorDiretion[i]);
        DCM_enGetU8ErrorCodeExport(i,&u8ErrorCode[i]);
    }
#if 0
    Rte_IWrite_Dcm_vMain_DcmValid_u8Flag(True);
    Rte_IWrite_Dcm_vMain_DcmSetDirectionMotor0_u8DcmSetDirection(enMotorDiretion[DCM_nMixDrMotor]);
    Rte_IWrite_Dcm_vMain_DcmSetDirectionMotor1_u8DcmSetDirection(enMotorDiretion[DCM_nAirdMotor]);
    Rte_IWrite_Dcm_vMain_DcmSetDirectionMotor2_u8DcmSetDirection(enMotorDiretion[DCM_nRFAMotor]);
    Rte_IWrite_Dcm_vMain_DcmSetDirectionMotor3_u8DcmSetDirection(enMotorDiretion[DCM_nMixPsMotor]);
    
    Rte_IWrite_Dcm_vMain_DcmMixMotorFbAdValueDr_u16AdValue(au16PtaPosFb[DCM_nMixDrMotor]);
    Rte_IWrite_Dcm_vMain_DcmAirdMotorFbAdValue_u16AdValue(au16PtaPosFb[DCM_nAirdMotor]);
    Rte_IWrite_Dcm_vMain_DcmRfaMotorFbAdValue_u16AdValue(au16PtaPosFb[DCM_nRFAMotor]);
    Rte_IWrite_Dcm_vMain_DcmMixMotorFbAdValuePs_u16AdValue(au16PtaPosFb[DCM_nMixPsMotor]);

    Rte_IWrite_Dcm_vMain_DcmMixMotorFbRawAdValueDr_u16AdValue(au16PtaRawPosFb[DCM_nMixDrMotor]); /*modify by LT,20160713*/
    Rte_IWrite_Dcm_vMain_DcmAirdMotorFbRawAdValue_u16AdValue(au16PtaRawPosFb[DCM_nAirdMotor]);/*modify by LT,20160713*/
    Rte_IWrite_Dcm_vMain_DcmRfaMotorFbRawAdValue_u16AdValue(au16PtaRawPosFb[DCM_nRFAMotor]);/*modify by LT,20160713*/
    Rte_IWrite_Dcm_vMain_DcmMixMotorFbRawAdValuePs_u16AdValue(au16PtaRawPosFb[DCM_nMixPsMotor]);/*modify by LT,20160713*/
   
    Rte_IWrite_Dcm_vMain_DcmErrorCode_u32DcmErrorCode((u8ErrorCode[3]<<24)|(u8ErrorCode[2]<<16)|(u8ErrorCode[1]<<8)|(u8ErrorCode[0]));
#endif
}
#ifdef PINDRIVER
/******************************************************************************
* Function   : static void DCM_vActuatorOperation(void)
* Description: Provides the decoding from DCM_tunPortData structures to the
*                i/o port mapping. Also controls the DCM_biAirMixEnable.
* Takes      : Nothing
* Returns    : Nothing
*/
 void DCM_vActuatorOperation(void)
{
    DCM_tstState   stPorts; 
    uint8 i;
    for(i=0u;i<(uint8)MotorNum;i++)
	{
        DCM_enGetStMotorStatusExport(i,&stPorts);
        DCM_astMotorSetPIN[0].fpSetPinSts(stPorts);
    }
}

/*============================================================================
*Function : DCM_tenValueSts DCM_enSetMotor0PINExport(DCM_tstState *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
DCM_tenValueSts DCM_enSetMotor0PINExport(DCM_tstState *value)
{
    if (value->bi2OkToSleep == 0u )
    {/*mix air motor*/
        DCM_biMotor0_1(value->enRequired);
        DCM_biMotor0_2(value->enRequired>>1u);
    }
    else
    {
        DCM_biMotor0_1(0);
        DCM_biMotor0_2(0);
    }
}
#endif
/*============================================================================
*Function : DCM_tenValueSts DCM_enLowVoltageFlagImport(uint8 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
DCM_tenValueSts DCM_enLowVoltageFlagImport(uint8 *value)
{
    *value=POW_u16GetValue(POW_nu16AppLowVoltage);
    return DCM_nValid;
}
/*============================================================================
*Function : DCM_tenValueSts DCM_enHighVoltageFlagImport(uint8 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
DCM_tenValueSts DCM_enHighVoltageFlagImport(uint8 *value)
{
    *value=POW_u16GetValue(POW_nu16AppHighVoltage);
    return DCM_nValid;
}
/*============================================================================
*Function : DCM_tenValueSts DCM_enAdValidFlagImport(uint8 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
DCM_tenValueSts DCM_enAdValidFlagImport(uint8 *value)
{
    *value=True;
    return DCM_nValid;
}
/*============================================================================
*Function : DCM_tenValueSts DCM_enTargetPositionImport(uint8 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
DCM_tenValueSts DCM_enTargetPositionImport(uint8 index,uint16 *value)
{
    DCM_tenValueSts enReturn=DCM_nValid;
    *value=DCM_stMotorProperty[index].fpTargetPosition();
    if(*value==0xFFFFu)/*YSL modify, 20170318*/
    {
        enReturn=DCM_nInvalid;
    }
    return enReturn;
}
/*============================================================================
*Function : DCM_tenValueSts DCM_enCurrentPositionImport(uint8 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
DCM_tenValueSts DCM_enCurrentPositionImport(uint8 index,uint16 *value)
{
    DCM_tenValueSts enReturn=DCM_nValid;
    DCM_stMotorProperty[index].fpCurrentPosition(value);
    /*=================For Ad feedback force===================*/
    if(index==(uint8)DCM_nMixDrMotor)
    {
        if(DcmGetCcpForceBit(Dcm_nSetMixDrMotorFb))
    	{
    		*value=Dcm_CcpControlData[Dcm_nSetMixDrMotorFb];
    	}
    }
    else if(index==(uint8)DCM_nAirdMotor)
    {
        if(DcmGetCcpForceBit(Dcm_nSetAirdMotorFb))
    	{
    		*value=Dcm_CcpControlData[Dcm_nSetAirdMotorFb];
    	}
    }
    else if(index==(uint8)DCM_nRFAMotor)
    {
        if(DcmGetCcpForceBit(Dcm_nSetRfaMotorFb))
    	{
    		*value=Dcm_CcpControlData[Dcm_nSetRfaMotorFb];
    	}
    }
    else
    {
        enReturn=DCM_nInvalid;
    }
    /*=================Ad feed back force end======================*/
    return enReturn;
}


/*****************************************************************************
* EOF: DCM_Cfg.c
*****************************************************************************/
