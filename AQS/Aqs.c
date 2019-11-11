/*******************************************************************************
| Module Name: AQS Control
| File Name: Aqs.c
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
| Yang Shengli                        Desay SV Automotive Co., Ltd
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date             Ver         Author               Description
| ----------  -------  -------------  -------------------------------------------------
| 2016-02-25  1.00        Yang Shengli      First implementation
********************************************************************************/
#define AQS                        /* name of the module                */


/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
*****************************************************************************/

/* system-headerfiles */
#include "General.h"
/* foreign headerfiles */
#include "Rte_internal.h"
#include  "Alg.h"
#include  "Pow.h"
#include  "Vel.h"
#include  "Mcu_cfg.h"
#include  "Frame_if.h"
/* own headerfiles */
#include "Aqs.h"
#include "Aqs_Cfg.h"
#include "Aqs_Private.h"
#include "Aqs_Type.h"

/*Local variable definition*/
static uint8 AQS_au8Array[AQS_nu8Max];
static uint8 AQS_au8Record[30];
static uint8 AQS_u8RecordIndex;
static uint8 AQS_u8IndexClrEnable;
static uint8 AQS_u8CurStatus;
static uint8 AQS_u8ICTMissTmr;
static uint16 AQS_au16Array[AQS_nu16Max];
static uint32 AQS_u32InputPwmWidth;
static uint16 AQS_u16IgOnCnt;
#define AQS_CcpControlEnable

#ifdef AQS_CcpControlEnable
/*Ccp control*/
/**********************************Ccp control*****************************************/
typedef enum
{
    AQS_nAirBadTime=0u,	    /*Bad air time*/
    AQS_nState,	        /*Air state*/
	AQS_nCcpForceMax
}CcpControl_AQS;
static uint16 AQS_u16CcpForceFlag=0u;
static uint16 AQS_u16CcpControlData[AQS_nCcpForceMax];
#define AQSGetCcpForceBit(index)	((uint16)(AQS_u16CcpForceFlag>>(index))&0x01u)
#define AQSSetCcpForceBit(index)	(AQS_u16CcpForceFlag=AQS_u16CcpForceFlag|(0x01u<<(index)))
#define AQSClrCcpForceBit(index)	(AQS_u16CcpForceFlag=AQS_u16CcpForceFlag&(~(0x01u<<(index))))
#define AQSClrCcpForceByte(void)	(AQS_u16CcpForceFlag=0u)
/*************************************************************************************/

//static void AQS_vCcpInputForce(void);
#endif

static void AQS_vRecordAirBadTime(void);
static void AQS_vSensorDataProcess(void);
static void AQS_vAirStateJudgement(void);
static void AQS_vSensorInputPwmDetect(void);
/***************************************************
 Function         : void AQS_vReset (void)                                       *
 Description     : Reset container function of AQS                     *
 Takes            : Nothing
 Return Value  : Nothing                                                      *
***************************************************/
void AQS_vReset(void)
{
	AQS_u8State = AQS_Initing;
	AQS_u8SwVersion = AQS_nSwVersion;
	AQS_u8Valid = False;
	AQS_u8ErrorCode = 0;
	AQS_u8AirBadTime = 0;
	/*Write value to RTE*/
	
	AQS_u8IndexClrEnable=False;
	AQS_u8RecordIndex=0;
	AQS_u8CurStatus = AQS_Initing;
	
	memset(AQS_au8Record,0,sizeof(AQS_au8Record));
}

/*****************************************************************************
 Function         : void AQS_vInit( void)                                         *
 Description     : initialize function of AQS                      *
 Takes            : Nothing
 Return Value  : Nothing  
*****************************************************************************/
void AQS_vInit( void)
{
	AQS_u8State = AQS_Initing;
	AQS_u8SwVersion = AQS_nSwVersion;
	AQS_u8Valid = False;
	AQS_u8ErrorCode = 0u;
	AQS_u8AirBadTime = 0u;
    AQS_u8AirBadPercent = 0u;

	AQS_u8IndexClrEnable=False;
	AQS_u8RecordIndex=0;
	AQS_u8CurStatus = AQS_Initing;
    AQS_u16IgOnCnt = 0u;
	
	memset(AQS_au8Record,0,sizeof(AQS_au8Record));
    AQS_ControlGetAqsSensorPwm(On);
}


/*****************************************************************************
 Function         : void AQS_vDeinit( void)                                         *
 Description     : De-init function of AQS                      *
 Takes            : Nothing
 Return Value  : Nothing                                                      *
*****************************************************************************/
void AQS_vDeinit( void)
{
    AQS_ControlGetAqsSensorPwm(Off);
    AQS_u16IgOnCnt = 0u;
}

/*****************************************************************************										  *
 Function      : AQS_vRecordAirBadTime                                                   *
 Description   : Process Air bad time. *
 NOTE: This part of the main code is normally called from the AQS_vMain*
 Return Value  : None                                                        *
*****************************************************************************/
static void AQS_vRecordAirBadTime(void)
{
	/*more then 1 cycle time gone!*/
	if(AQS_u8IndexClrEnable == True)
	{
		if(AQS_LastCycRecord() == 1)/*Last record is Bad, then queue out this Bad count!*/
		{
			if(AQS_u8AirBadTime)
			{
				AQS_u8AirBadTime--;
			}
		}
	}
	
	if(AQS_u8CurStatus == AQS_AirBad)
	{
		AQS_SetCurRecordBad();
		AQS_u8AirBadTime++;
	}
	else
	{
		AQS_SetCurRecordGood();
	}
	
	if(++AQS_u8RecordIndex >= AQS_FilterTime)
	{
		AQS_u8RecordIndex = 0;
		AQS_u8IndexClrEnable=True;
	}
}
/*****************************************************************************										  *
 Function      : AQS_vSensorDataProcess                                                   *
 Description   : Process AQS data. *
 NOTE: This part of the main code is normally called from the AQS_vMain*
 Return Value  : None                                                        *
*****************************************************************************/
static void AQS_vSensorDataProcess(void)
{	
	uint16 AQS_u16SensorPwmValue;

    AQS_u16SensorPwmValue = AQS_u16PwmValue;

	AQS_u8ErrorCode = 0;
    if((AQS_u16SensorPwmValue <= 7u) && (AQS_u16SensorPwmValue >= 3u))
    {
		AQS_u8CurStatus = AQS_Error;
		AQS_vSetBit(AQS_u8ErrorCode,2);
    }
    else if((AQS_u16SensorPwmValue <= 20u) && (AQS_u16SensorPwmValue >= 10u))
    {
        AQS_u8CurStatus = AQS_AirGood;
    }
    else if((AQS_u16SensorPwmValue <= 35u) && (AQS_u16SensorPwmValue >= 25u))
    {
        AQS_u8CurStatus = AQS_AirGood;
    }
    else if((AQS_u16SensorPwmValue <= 45u) && (AQS_u16SensorPwmValue >= 35u))
    {
        AQS_u8CurStatus = AQS_AirBad;
    }
    else if((AQS_u16SensorPwmValue <= 55u) && (AQS_u16SensorPwmValue >= 45u))
    {
        AQS_u8CurStatus = AQS_AirBad;
    }
    else if((AQS_u16SensorPwmValue <= 65u) && (AQS_u16SensorPwmValue >= 55u))
    {
        AQS_u8CurStatus = AQS_AirBad;
    }
    else if((AQS_u16SensorPwmValue <= 75u) && (AQS_u16SensorPwmValue >= 65u))
    {
        AQS_u8CurStatus = AQS_AirBad;
    }
	else if(AQS_u16SensorPwmValue >= 95u)
	{
		AQS_u8CurStatus = AQS_ShutToPlus;
		AQS_vSetBit(AQS_u8ErrorCode,1);
	}
	else if(AQS_u16SensorPwmValue == 0u)
	{
		AQS_u8CurStatus = AQS_ShutToGnd;
		AQS_vSetBit(AQS_u8ErrorCode,0);
	}
	else
	{
		AQS_u8CurStatus = AQS_Initing;
	}

    if(AQS_u8State == AQS_Initing)
    {
        if((AQS_u8CurStatus == AQS_AirBad) || (AQS_u8CurStatus == AQS_AirGood))
        {   /*Init finish*/
            AQS_u8State = AQS_AirGood;
        }
        else
        {
        }
    }
    else
    {
    }
}

/*****************************************************************************										  *
 Function      : AQS_vAirStateJudgement                                                   *
 Description   : Process AQS data. *
 NOTE: This part of the main code is normally called from the AQS_vMain*
 Return Value  : None                                                        *
*****************************************************************************/
static void AQS_vAirStateJudgement(void)
{
	uint16 u16VelSpeed;
	uint8 u8BadAirPercentPiont;
	uint16 u16CurPercent;
    uint8 u8VelValid;
	uint16 *pu16_1 = NULL,*pu16_2 = NULL;

    u8VelValid = AQS_u8GetVelValid();
	u16VelSpeed = AQS_u16GetVelValue();
	/*calc this cycle bad air percentage!*/
	u16CurPercent = (uint16)AQS_u8AirBadTime;
    u16CurPercent *= 100;
    u16CurPercent /= AQS_FilterTime;

    if(u16CurPercent > 100u)
    {
        u16CurPercent = 100u;
    }
    AQS_u8AirBadPercent = u16CurPercent;
    if((u8VelValid == True) && (AQS_u8ErrorCode == 0u))
    {
    	/*find switch to Rec piont*/
    	if((AQS_u8State == AQS_AirGood) || (AQS_u8State == AQS_ShutToGnd) || (AQS_u8State == AQS_ShutToPlus)\
            || (AQS_u8State == AQS_Error))
    	{
    		pu16_1 = (uint16*)AQS_au16VelRecPercent_X;
    		pu16_2 = (uint16*)AQS_au16VelRecPercent_Y;
    		u8BadAirPercentPiont = ALG_u16CurveLookup_16_16_Limit(pu16_1,pu16_2,u16VelSpeed, AQS_au16VelRecPercentLen);

    		if(u16CurPercent >= u8BadAirPercentPiont)
    		{
    			AQS_u8State = AQS_AirBad;
    		}
            else
            {
                AQS_u8State = AQS_AirGood;
            }
    	}
    	/*find switch to Fresh piont*/
    	else if(AQS_u8State == AQS_AirBad)
    	{
    		pu16_1 = (uint16*)AQS_au16VelFreshPercent_X;
    		pu16_2 = (uint16*)AQS_au16VelFreshPercent_Y;
    		u8BadAirPercentPiont = ALG_u16CurveLookup_16_16_Limit(pu16_1,pu16_2,u16VelSpeed, AQS_au16VelFreshPercentLen);

    		if(u16CurPercent <= u8BadAirPercentPiont)
    		{
    			AQS_u8State = AQS_AirGood;
    		}
            else
            {
            }
    	}
    }
    else if(AQS_u8ErrorCode & 0x01u)
    {
        AQS_u8State = AQS_ShutToGnd;
    }
    else if(AQS_u8ErrorCode & 0x02u)
    {
        AQS_u8State = AQS_ShutToPlus;
    }
    else if(AQS_u8ErrorCode & 0x04u)
    {
        AQS_u8State = AQS_Error;
    }
}
/*****************************************************************************										  *
 Function      : AQS_vMain                                                   *
 Description   : Process AQS. *
 NOTE: This part of the main code is normally called from the 100mS container*
 Return Value  : None                                                        *
*****************************************************************************/
void AQS_vMain(void)
{
#if((CarConfiguration == High_End) || (CarConfiguration == Mid_End))
	uint8 u8Flag1000MS;
	uint8 u8PowBattLowVoltage;
	uint8 u8PowBattHighVoltage;

	u8PowBattHighVoltage = (uint8)POW_u16GetValue(POW_nu16AppHighVoltage);
	u8PowBattLowVoltage = (uint8)POW_u16GetValue(POW_nu16AppLowVoltage);
	u8Flag1000MS = (uint8)FRAME_u16GetValue(SYS_nu16Flag1000MS_BG);

    AQS_vSensorInputPwmDetect();
    if((u8Flag1000MS == True) && (AQS_u16IgOnCnt <= 20u))
    {
        AQS_u16IgOnCnt++;
    }
    
	if((u8PowBattHighVoltage == True) || (u8PowBattLowVoltage == True))
	{
        AQS_u16IgOnCnt=0u;
		return;
	}
	else if((AQS_u16IgOnCnt > 20u/*20s initial time*/) && (u8Flag1000MS == True))
	{
        //AQS_vSensorInputPwmDetect();
		AQS_vSensorDataProcess();
		AQS_vRecordAirBadTime();
		AQS_vAirStateJudgement();

		AQS_u8Valid = True;
		/*Write data to RTE*/
    #ifdef AQS_CcpControlEnable
        if(AQSGetCcpForceBit(AQS_nAirBadTime))
        {
            AQS_au8Array[AQS_nu8AirBadTime] = (uint8)AQS_u16CcpControlData[AQS_nAirBadTime];
        }
    #endif
    
    #ifdef AQS_CcpControlEnable
        if(AQSGetCcpForceBit(AQS_nState))
        {
            AQS_au8Array[AQS_nu8State] = (uint8)AQS_u16CcpControlData[AQS_nState];
        }
    #endif
	}
    else
    {
    }
#endif
}

#ifdef AQS_CcpControlEnable
/*****************************************************************************
 Function      : AQS_u8ForceIoControl_Write                                 
 Description   : Ccp control function
 Takes         : Nothing
 Return Value  : None                                                *
*****************************************************************************/

Std_ReturnType AQS_u8ForceIoControl_Write(/*IN*/UInt32 ForceIoControlWord)
{
	tstCcpContronType CcpControlWord;
	CcpControlWord.CcpContronData=(uint16)ForceIoControlWord;
	CcpControlWord.CcpCommand=(uint8)(ForceIoControlWord>>16);
	CcpControlWord.CcpCommandFlag=(uint8)(ForceIoControlWord>>24);
	if(CcpControlWord.CcpCommandFlag==True)
	{
		switch(CcpControlWord.CcpCommand)
		{
			case 0:
				AQSClrCcpForceByte();
				break;
            case 0xA1:
                AQSSetCcpForceBit(AQS_nAirBadTime);
                AQS_u16CcpControlData[AQS_nAirBadTime] = CcpControlWord.CcpContronData;
                break;
            case 0xA2:
                AQSClrCcpForceBit(AQS_nAirBadTime);
                AQS_u16CcpControlData[AQS_nAirBadTime] = 0u;
                break;
            case 0xA3:
                AQSSetCcpForceBit(AQS_nState);
                AQS_u16CcpControlData[AQS_nState] = CcpControlWord.CcpContronData;
                break;
            case 0xA4:
                AQSClrCcpForceBit(AQS_nState);
                AQS_u16CcpControlData[AQS_nState] = 0u;
                break;
			default:
				break;
		}
	}
	else
	{
		AQSClrCcpForceByte();
	}

    return 1u;
}
#endif
/*****************************************************************************										  *
 Function      : AQS_vActive                                                   *
 Description   : Process AQS. *
 NOTE: This part of the main code is normally called from the 100mS container*
 Return Value  : None                                                        *
*****************************************************************************/
void AQS_vActive(void)
{

}


/*****************************************************************************										  *
 Function      : AQS_vActiveStandby                                                   *
 Description   : Process AQS. *
 NOTE: This part of the main code is normally called from the 100mS container*
 Return Value  : None                                                        *
*****************************************************************************/
void AQS_vActiveStandby(void)
{

}
/*****************************************************************************
 Function      : AQS_u8GetValue                                   *
 Description   : The extern model get the uint8 type variables value from     *
				 this model                                                   *
 Return Value  : uint8                                                       *
*****************************************************************************/
uint8 AQS_u8GetValue( AQS_tu8enVarNumber enIndex )
{
    uint8 u8ReturnValue;
	if ( enIndex < AQS_nu8Max )
	{
		u8ReturnValue = AQS_au8Array[enIndex];
	}
	else
	{
		u8ReturnValue = AQS_au8Array[AQS_nu8Max-1];
	}
    return u8ReturnValue;
}


/*****************************************************************************
 Function      : AQS_u16GetValue                                   *
 Description   : The extern model get the uint8 type variables value from     *
				 this model                                                   *
 Return Value  : uint8                                                       *
*****************************************************************************/
uint16 AQS_u16GetValue( AQS_tu16enVarNumber enIndex )
{
    uint16 u16ReturnValue;
	if ( enIndex < AQS_nu16Max )
	{
		u16ReturnValue = AQS_au16Array[enIndex];
	}
	else
	{
		u16ReturnValue = AQS_au16Array[AQS_nu16Max-1];
	}
    return u16ReturnValue;
}


static void AQS_vSensorInputPwmDetect(void)
{
    uint16 u16DutyValue = 0u;
    uint16 u16PortValue = 0u;
    
    if(AQS_u8ICTMissTmr < 4u)
    {
        AQS_u8ICTMissTmr++;
        u16DutyValue=(uint16)AQS_u32InputPwmWidth;
    }
    else
    {
        AQS_ReadAqsOutsidePort(&u16PortValue);
        if(u16PortValue == 0u)
        {
            u16DutyValue= 0u;/*0%*/ 
        }
        else
        {
            u16DutyValue= 1000u;/*100%*/ 
        }
    }
    if(u16DutyValue > 1000u)
    {
        u16DutyValue = 1000u;/*100%*/
    }

    AQS_u16PwmValue = u16DutyValue/10u;
}

void Callback_MCU_ISR_TAUJ1_2(void)
{
    uint32 u32InputPwmDuty;
    
    u32InputPwmDuty = MCU_u32TAUxGetTime(MCU_mTAUJ1_2);

    u32InputPwmDuty = u32InputPwmDuty/10u;/*(AQS_u32InputPwmWidth(us)/10(ms)*1000)*1000,0~1000%*/
    if(u32InputPwmDuty > 1000u)
    {
        AQS_u32InputPwmWidth = 1000u;
    }
    else
    {
        AQS_u32InputPwmWidth = u32InputPwmDuty;
    }

    AQS_u8ICTMissTmr = 0u;
}

