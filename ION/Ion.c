/*******************************************************************************
| Module Name: ION Control
| File Name: Ion.c
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
#define ION                        /* name of the module                */


/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
*****************************************************************************/

/* system-headerfiles */
#include "General.h"
/* foreign headerfiles */
//#include "Rte_ion.h"
#include "Rte_internal.h"

#include "Mmi.h" 
#include "Mmi_Type.h"
#include "Mmi_Private.h"
//#include "Frame_if.h"
//#include  "Alg.h"
/* own headerfiles */
#include "Ion.h"
#include "Ion_Cfg.h"
#include "Ion_Private.h"
#include "Ion_Type.h"

/*Local variable definition*/
static uint8 ION_au8Array[ION_nu8Max];
static uint16 ION_au16Array[ION_nu16Max];

static uint16 ION_u16NoteLostTime=0;
static uint16 ION_u16TBoxReqMaxTimer=0;
static uint16 ION_u16Pm25ExceedTime=0;
static uint16 ION_u16IonOnWaitTimer=0;
static uint8 ION_u8PM25RunFlag=0;

static uint16 ION_u16PopupTimer=0;
static uint16 ION_u16FirstPopupTimer=0;

static uint8 ION_u8Pm25IsFirstPopup=True;
static uint8 ION_u8Pm25PopComfirm=False;
/*Ccp control*/
typedef enum
{
	ION_nIONStsReq,
	ION_nIONPm25Output,
	ION_nIONPm25OutDen,
	ION_nIONPm25InDen,
	ION_nIONCleanMode,
	ION_nIONIonMode,
	ION_nCcpForceMax
}CcpControl_ION;
static uint8 ION_u8CcpForceFlag=0;
static uint16 ION_u16CcpControlData[ION_nCcpForceMax];
#define ION_GetCcpForceBit(index)	((ION_u8CcpForceFlag>>index)&0x01)
#define ION_SetCcpForceBit(index)	(ION_u8CcpForceFlag=ION_u8CcpForceFlag|(0x01<<index))
#define ION_ClrCcpForceBit(index)	(ION_u8CcpForceFlag=ION_u8CcpForceFlag&(~(0x01<<index)))
#define ION_ClrCcpForceByte(void)	(ION_u8CcpForceFlag=0)

static void ION_vCcpOutputForce(void);

static void ION_vUpdateIonInformation(void);
static void ION_u8CheckInPutRange(uint8 Input,uint8 Max,uint8 Min,ION_tu8enVarNumber Mask);
static void ION_u16CheckInPutRange(uint16 Input,uint16 Max,uint16 Min,ION_tu16enVarNumber Mask);
static void ION_vIonManuControl(void);
//static void ION_vIonAutoRunTime(void);
static void ION_vIonAutoControl(void);
static void ION_vIonControl(void);
static void ION_vSensorErrorHandle(void);
static uint8 ION_u8CheckPm25TboxCondition(void);
static uint8 ION_u8CheckPm25EngCondition(void);
static uint8 ION_u8CheckPm25BusCondition(void);
static void ION_vPM25UpdatePm25Information(void);
static void ION_vPM25UpdateInnerAirQuanlity(void);
static void ION_vIonControlByInnerAirQuanlity(void);
static void ION_vWorkModeControl(void);
static void ION_vControlPm25Pin(uint16 PinLevel);
static void ION_vControlCleanModePin(uint16 PinLevel);
static void ION_vControlIonModePin(uint16 PinLevel);

static void ION_vVehicleConfig(void);
static void ION_vPopupHandle(void); /*CR, 180202*/
/*****************************************************************************										  *
 Function      : ION_vReset                                                  *
 Description   : Initialises the global variable*
                 Initialises the Pin also                            *
 Return Value  : None                                                        *
*****************************************************************************/
void ION_vReset(void)
{
	uint8 u8i;
   	ION_u8SwVersion = ION_nSwVersion;
	
	for(u8i = 0;u8i < ION_nu8Max;u8i++)
	{
		ION_au8Array[u8i] = 0;
	}
    ION_u16ErrorCode = 0;
	ION_vControlPm25Pin(Low); /*160112*/
    ION_vControlIonModePin(0u);
    ION_vControlCleanModePin(0u);
    ION_u16NoteLostTime = 0;/*when pm 25 power is off, clear the error counter,171229*/
    
	ION_u8AirOutQLevel = 0x7U;/*170514*/
	ION_u8AirInQLevel = 0x7U;
	ION_u16PM25InDen = ION_PM25DenDefault;
	ION_u16PM25OutDen = ION_PM25DenDefault;
    

	ION_u8Pm25IsFirstPopup=True;
	ION_u8Pm25PopComfirm = False;
}

/*****************************************************************************										  *
 Function      : ION_vInit                                                  *
 Description   : Module change from Active to ON*
                 Switch off the telltales.                            *
 Return Value  : None                                                        *
*****************************************************************************/
void ION_vInit(void)
{
	uint8 u8i;
	
	for(u8i = 0;u8i < ION_nu8Max;u8i++)
	{
		ION_au8Array[u8i] = 0;
	}
    ION_u16ErrorCode = 0;
	ION_u8PM25StsReq = False;//170514, True;
	ION_u8PM25EnableCheckLostDtc = False;
	ION_u8AirOutQLevel = 0x7U;/*170602*/
	ION_u8AirInQLevel = 0x7U;
	ION_u16PM25InDen = 0xFFFU;
	ION_u16PM25OutDen = 0xFFFU;
	ION_u8AirInQuality = PM25_Initing;
	
	ION_u8PM25ErrSts=0;
	ION_u8IONErrSts=0;
	ION_u16NoteLostTime=0;
	ION_u16Pm25ExceedTime = 0;/*DEBUG< set to 0,180207*/
	ION_u16PopupTimer=0;
	ION_u16FirstPopupTimer=0;
	ION_u8Pm25IsFirstPopup=True;
	ION_u8Pm25PopComfirm = False;
    ION_ClrCcpForceByte();

    ION_vControlIonModePin(0u);
    ION_vControlCleanModePin(0u);
}

/*****************************************************************************										  *
 Function      : ION_vDeinit                                                  *
 Description   : Module change from ON to Active*
                 Switch off the telltales.                            *
 Return Value  : None                                                        *
*****************************************************************************/
void ION_vDeinit(void)
{
	ION_u8PM25StsReq= False;
	ION_u8PM25EnableCheckLostDtc = False;
 	ION_u8IONStsReq	=False;
	ION_u8IONIZEState =False;
    ION_u16NoteLostTime = 0;/*when pm 25 power is off, clear the error counter,171229*/
    ION_ClrCcpForceByte();
	ION_vControlPm25Pin(Low); /*160810*/
    ION_vControlIonModePin(0u);
    ION_vControlCleanModePin(0u);
}

/*****************************************************************************										  *
 Function      : ION_vActive                                                  *
 Description   : The active function of ION module*
                 .                            *
 Return Value  : None                                                        *
*****************************************************************************/
void ION_vActive(void)
{
	uint8 u8HighVoltageFlag = False;
	uint8 u8LowVoltageFlag = False;
	uint8 sbiStaticOn = IGN_u16GetValue(IGN_nu16IgnStable)&0x01;	
	uint8 u8IgHwSts = IGN_u16GetValue(IGN_nu16IGN2IoStatus)&0x01;	
	
	u8LowVoltageFlag = ION_u8GetPowLowValue();
	u8HighVoltageFlag = ION_u8GetPowHighValue();

	if ((u8IgHwSts == True)&&(sbiStaticOn == False)) /*IG ON, bu not stable, send default value,170730*/
	{
	 	ION_u8AirOutQLevel = 0x7U;/*170602*/
		ION_u8AirInQLevel = 0x7U;
		ION_u16PM25InDen = 0xFFFU;
		ION_u16PM25OutDen = 0xFFFU;
		ION_u8AirInQuality = PM25_Initing;
		
		ION_u8PM25Sts=0;/*LIN &CAN sleep, PM25sts will send memory value,180417*/
		ION_u8PM25StsReq= 0;
	}
	
	if((u8LowVoltageFlag == True) || (u8HighVoltageFlag == True))
	{
		ION_vControlPm25Pin(Low);
        ION_vControlIonModePin(0u);
        ION_vControlCleanModePin(0u);
        ION_u16NoteLostTime = 0;/*when pm 25 power is off, clear the error counter,171229*/
		ION_u8IONStsReq = False;
	}
	else
	{
		/*update ion and pm25 sts*/
		//ION_vUpdateIonInformation();/*170729*/ /*debug:IG ON->OFF,L_AC_IONdetectEnable 1->0->1,180206*/
		
		/*Running PM25 sensor*/
		if (ION_u8CheckPm25TboxCondition() == True)
		{
            ION_vUpdateIonInformation();
			ION_u8PM25EnableCheckLostDtc = True;

			if (ION_u8CheckPm25BusCondition() == True)
			{
				ION_vControlPm25Pin(High);
				ION_u8PM25StsReq = True;
			}
			else
			{
				ION_vControlPm25Pin(Low);
				ION_u8PM25StsReq = False;				
			}
		}
		else
		{
			ION_vControlPm25Pin(Low);
			ION_u16NoteLostTime = 0;/*when pm 25 power is off, clear the error counter,171229*/
			ION_u8PM25StsReq = False;
			ION_u8PM25EnableCheckLostDtc = False;
		}

        //ION_u8CheckPm25EngCondition();
        
		/***update PM25 Information**********/
		if (ION_u8PM25StsReq == True)
		{
			ION_vPM25UpdatePm25Information();

			ION_vPM25UpdateInnerAirQuanlity();
		}
		else
		{
			ION_u8PM25Exceed = False;
		}		
	}
	ION_vVehicleConfig();
}
/*****************************************************************************										  *
 Function      : ION_vMain                                                   *
 Description   : In the On state .                         *
               . *
 NOTE: This part of the main code is normally called from the 100mS container*
 Return Value  : None                                                        *
*****************************************************************************/
void ION_vMain(void)
{
	uint8 u8HighVoltageFlag = False;
	uint8 u8LowVoltageFlag = False;

	u8LowVoltageFlag = ION_u8GetPowLowValue();
	u8HighVoltageFlag = ION_u8GetPowHighValue();

	if((u8LowVoltageFlag == True) || (u8HighVoltageFlag == True))
	{
		ION_vControlPm25Pin(Low);
        ION_vControlIonModePin(0u);
        ION_vControlCleanModePin(0u);
		ION_u8PM25StsReq = False;/*170514*/
		ION_u8PM25EnableCheckLostDtc = False;
		ION_u8IONStsReq = False;
		ION_u16NoteLostTime = 0;/*when pm 25 power is off, clear the error counter,171229*/
	}
	else
	{	
		/*update ion and pm25 sts*/
		ION_vUpdateIonInformation();/*170729*/
		
		/*Running PM25 sensor*/
		if ((ION_u8CheckPm25TboxCondition() == True)||(ION_u8CheckPm25EngCondition() == True))
		{
            ION_vPM25UpdatePm25Information(); /*update info  only when pm25 req is true*/
			ION_u8PM25EnableCheckLostDtc = True;
			
			if (ION_u8CheckPm25BusCondition() == True)
			{
				ION_vControlPm25Pin(High);
				ION_u8PM25StsReq = True;
			}
			else
			{
				ION_vControlPm25Pin(Low);
				ION_u8PM25StsReq = False;				
			}
		}
		else
		{
			ION_vControlPm25Pin(Low);
			ION_u8PM25StsReq = False;
			ION_u8PM25EnableCheckLostDtc = False;
            ION_u16NoteLostTime = 0;/*when pm 25 power is off, clear the error counter,171229*/
		}
		if (MMI_u8GetValue(MMI_nPm25Enable) == True)   /*MMI Allow PM25 working,180202*/
		{
			/***update PM25 Information**********/
			if (ION_u8PM25StsReq == True)
			{
				ION_vPM25UpdatePm25Information();

				ION_vPM25UpdateInnerAirQuanlity();
			}
			else
			{
				ION_u8PM25Exceed = False;
			}
		}
		else
		{
			ION_u8PM25Sts = 3; /*OFF*/
			ION_u8PM25Exceed = False;
			
		 	ION_u8AirOutQLevel = 0x7U;
			ION_u8AirInQLevel = 0x7U;
			ION_u16PM25InDen = 0xFFFU;
			ION_u16PM25OutDen = 0xFFFU;
			ION_u8AirInQuality = PM25_Initing;	
			ION_u8Pm25IsFirstPopup=True; /*DEBUG, POWER off is first send,180402*/
			ION_vWritePm25PinLevel(Low);/*180402*/
			ION_u8PM25StsReq = False;
		}
		/** ion control ******************/
		ION_vIonControl();
        ION_vWorkModeControl();
	}
	ION_vPopupHandle();

	ION_vSensorErrorHandle();/*error detect*/

	ION_vVehicleConfig();
	
	ION_vCcpOutputForce();/*add ccp control,160716*/
	
}
/*****************************************************************************										  *
 Function      : ION_vIonManuControl                                                   *
 Description   : In the On state .                         *
               . *
 NOTE: This part of the main code is normally called from the ION_vIonControl*
 Return Value  : None                                                        *
*****************************************************************************/
static void ION_vIonManuControl(void)
{
	uint8 u8MmiIonReq = False;

	u8MmiIonReq = MMI_u8GetValue(MMI_nu8IonCtrl);
	
	if(u8MmiIonReq == ION_nMmiIonIonMode)
	{
		if(ION_u8IONStsReq != True)
		{
			ION_u8IONStsReq = True;
		}
	}
	else if(u8MmiIonReq == ION_nMmiIonCleanerOff)
	{
		if(ION_u8IONStsReq != False)
		{
			ION_u8IONStsReq = False;
		}
	}
	else 
	{
		/*nothing to do*/
	}
}

/*****************************************************************************										  *
 Function      : ION_vIonAutoControl                                                   *
 Description   : In the On state .                         *
               . *
 NOTE: This part of the main code is normally called from the ION_vIonControl*
 Return Value  : None                                                        *
*****************************************************************************/
static void ION_vIonAutoControl(void)
{	
	  if (ION_u16PM25InDen != ION_PM25DenDefault)  /*no the default value,170819*/
	  {
		if(ION_u16PM25InDen < IonReqIonizerOffPoint)
		{
			if(ION_u8IONStsReq != False)
			{
				ION_u8IONStsReq = False;
				MMI_vTurnOffByIonFinish();
			}
		}
		else if(ION_u16PM25InDen > IonReqOpenIonizerOnPoint)
		{
			if(ION_u8IONStsReq == True)
			{
				/*if running, then keep!*/
				ION_u8IONStsReq = True;
			}
			else
			{
				ION_u8IONStsReq = True;
			}
		}
		else
		{
			if(ION_u8IONStsReq == True)
			{
				/*if running, then keep!*/
				ION_u8IONStsReq = True;
			}
			else
			{
				ION_u8IONStsReq = False;
			}
		}
	}
	else
	{
		ION_u8IONStsReq = False;
	}
}
/*****************************************************************************										  *
 Function      : ION_vIonControl                                                   *
 Description   : In the On state .                         *
               . *
 NOTE: This part of the main code is normally called from the ION_vMain*
 Return Value  : None                                                        *
*****************************************************************************/
static void ION_vIonControl(void)
{
	uint8 u8MmiIonControlMode = MMI_u8GetValue(MMI_nu8IonMode);

	//ION_vUpdateIonInformation();
	if (ION_nUseIonCfg == True)  /*170730*/
	{
		if((u8MmiIonControlMode == ION_nMmiIonAuto) && (ION_u8PM25StsReq == True))
		{
			ION_vIonAutoControl();
		}
		else if (u8MmiIonControlMode == ION_nMmiIonManual) /*Manual control*/
		{
			ION_vIonManuControl();
		}
		else if (u8MmiIonControlMode == ION_nMmiIonOff) /*Off control*/
		{
			if(ION_u8IONStsReq != False)
			{
				ION_u8IONStsReq = False;
			}

			ION_vIonControlByInnerAirQuanlity();
		}
		else
		{
			/*Nothing to do*/
			if(ION_u8IONStsReq != False)
			{
				ION_u8IONStsReq = False;
			}
		}
	}
	else
	{
		ION_u8IONStsReq = False;
		ION_u8IONErrSts = False;
		ION_u8IONIZEState = False;
	}
}

/*****************************************************************************
 Function      : ION_u8CheckInPutRange                                   *
 Description   : Check the input value from     *
				 other model                                                   *
 Return Value  :                                                        *
*****************************************************************************/
static void ION_u8CheckInPutRange(uint8 Input,uint8 Max,uint8 Min,ION_tu8enVarNumber Mask)
{
	if((Input > Max) || (Input < Min))
	{
		if(Mask == ION_nu8IONStsReq)
		{
			ION_au8Array[Mask] = 0;
		}
		ION_au16Array[ION_nu16ErrorCode] |= 1;
	}
	else
	{
		ION_au8Array[Mask] = Input;
	}
}
/*****************************************************************************
 Function      : ION_u16CheckInPutRange                                   *
 Description   : Check the input value from     *
				 other model                                                   *
 Return Value  :                                                        *
*****************************************************************************/
static void ION_u16CheckInPutRange(uint16 Input,uint16 Max,uint16 Min,ION_tu16enVarNumber Mask)
{
	if((Input > Max) || (Input < Min))
	{
		ION_au16Array[ION_nu16ErrorCode] |= 1;
	}
	else
	{
		ION_au16Array[Mask] = Input;
	}
}
/*****************************************************************************
 Function      : ION_vGetInPutValue                                   *
 Description   : Get the input value from     *
				 other model                                                   *
 Return Value  :                                                        *
*****************************************************************************/
static void ION_vUpdateIonInformation(void)
{
	//uint8 u8ReqIon = 0;
	uint8 u8IonSts = 0;
	uint8 u8IonErrSts = 0;
	uint8 u8PM25Sts = 0;
	uint8 u8PM25ErrSts = 0;
	uint16 u16ION_DIG = 0;
	(void)ION_u8GetION_DIG(&u16ION_DIG);
	u8IonSts = (uint8)(u16ION_DIG>>2);
	if((u8IonSts>(IonDigMax>>2))||(u8IonSts<(IonDigMin>>2)))//add by CSL 20170604
	{
		u8IonErrSts = 1;
	}
	
	ION_u16CheckInPutRange(u16ION_DIG,IonDigMax,IonDigMin,ION_nu16DIG);
	//ION_u8CheckInPutRange(u8ReqIon,IonReqMax,IonReqMin,ION_nu8IONStsReq);/*debug, AUTO , ion is not on,170428*/
	ION_u8CheckInPutRange(u8IonErrSts,IonStsMax,IonStsMin,ION_nu8IONIZEState);
	ION_u8CheckInPutRange(u8IonErrSts,IonErrStsMax,IonErrStsMin,ION_nu8IONErrSts);

	u8PM25ErrSts = ION_u8GetPM25ErrSts();
	u8PM25Sts = ION_u8GetPM25Sts();

	ION_u8CheckInPutRange(u8PM25ErrSts,Pm25ErrStsMax,Pm25ErrStsMin,ION_nu8PM25ErrSts);
	ION_u8CheckInPutRange(u8PM25Sts,Pm25StsMax,Pm25StsMin,ION_nu8PM25Sts);

	if(u8PM25ErrSts !=0) /*error hapen,170718*/
	{
		ION_u8PM25Sts = PM25_nCanAcPm25Err;
	}
    
	if((u16ION_DIG < 614) && (ION_u8IONStsReq == True))
	{
		ION_u8IONErrSts = 1;
	}
	else
	{
		ION_u8IONErrSts = 0;
	}
}
static void ION_vSensorErrorHandle(void)
{
	if(ION_u8PM25ErrSts == 2)/*PM25 sensor short circuit*/
	{
		ION_u8ErrorCode1 = 1;/*160921*/
	}
	else if(ION_u8PM25ErrSts == 3)/*PM25 sensor open circuit*/
	{
		ION_u8ErrorCode1 = 2;
	}
    else if(ION_u8PM25ErrSts == 1)
    {
		ION_u8ErrorCode1 = 4;        
    }
	else
	{
		ION_u8ErrorCode1 = 0;
	}

	if(ION_u8IONErrSts == 2)/*ION short circuit*/
	{
		ION_u8ErrorCode2 = 1;
	}
	else if(ION_u8IONErrSts == 3)/*ION open circuit*/
	{
		ION_u8ErrorCode2 = 2;
	}
    else if(ION_u8IONErrSts == 1)
    {
        ION_u8ErrorCode2 = 4;
	}
	else
	{
		ION_u8ErrorCode2 = 0;
	}
    ION_u16ErrorCode = (ION_u8ErrorCode2<<8)|ION_u8ErrorCode1; /*modify by LT,20160713*/
}

static uint8 ION_u8CheckPm25TboxCondition(void)
{
	uint8 u8TboxPm25Req = CANAPP_u16GetValue(CANAPP_nu16TBOX_Inquire_PM25);/*160926*/
    if(u8TboxPm25Req == True)
    {
		ION_u8TboxRequest = True;
        ION_u16TBoxReqMaxTimer = 0u;
    }
	if (ION_u8TboxRequest == True) /*170730*/
    {
        if(ION_u16TBoxReqMaxTimer < PM25_nTboxMaxReqTime)
        {
			ION_u16TBoxReqMaxTimer++;
		}
		else
		{
			ION_u8TboxRequest = False;
		}
    }
	return ION_u8TboxRequest;
}

static uint8 ION_u8CheckPm25EngCondition(void)
{
	uint16 u8EngineSpeed = CANAPP_u16GetValue(CANAPP_nu16EMS_EngineSpeedRPM);/*160926*/
    uint16 sbiStaticOn = IGN_u16GetValue(IGN_nu16IgnStable)&0x01;

	if (sbiStaticOn != True)  /*IG OFF will not detect engine condition,180426*/
	{
		ION_u8PM25RunFlag = False;
	}
    else
    {
    	if((u8EngineSpeed >= 2000) && (u8EngineSpeed < 0xfffe))
    	{
    		ION_u8PM25RunFlag = True;
    	}
    	else if(u8EngineSpeed <1200)
    	{
    		ION_u8PM25RunFlag = False;
    	}
    }
	return ION_u8PM25RunFlag;
}

static uint8 ION_u8CheckPm25BusCondition(void)
{
	uint16 u16Pm25LinSts = (LINAPP_u32GetValue(LINAPP_nu32ErrorCode)&0x01);/*LIN loss PM25, bit1 */
	uint8 u8RetValue=True;
	
	if (u16Pm25LinSts == False) /*no error*/
	{
		ION_u16NoteLostTime = 0;
		u8RetValue = True;
	}
	else
	{
		if(ION_u16NoteLostTime < PM25_nPm25NoteLostWaitTime)
        {
            ION_u16NoteLostTime++;
        }
		else
		{
			u8RetValue = False;
		}
	}

	return u8RetValue;
}

static void ION_vPM25UpdatePm25Information(void)
{
	uint8 u8PM25InLevel = 0;
	uint8 u8PM25OutLevel = 0;
	uint16 u16PM25InDen = 0;
	uint16 u16PM25OutDen = 0;
	
	if(ION_u8PM25Sts == PM25_nCanAcPm25Complete)/*Complete*/
	{
		u16PM25InDen = ION_u16GetPM25InDen();
		u16PM25OutDen = ION_u16GetPM25OutDen();
		u8PM25InLevel = ION_u8GetAirInQLevel();
		u8PM25OutLevel = ION_u8GetAirOutQLevel();
		
		ION_u16CheckInPutRange(u16PM25InDen,Pm25InDenMax,Pm25InDenMin,ION_nu16PM25InDen);
		ION_u16CheckInPutRange(u16PM25OutDen,Pm25OutDenMax,Pm25OutDenMin,ION_nu16PM25OutDen);
		ION_u8CheckInPutRange(u8PM25InLevel,PmAirInQLevelMax,PmAirInQLevelMin,ION_nu8AirInQLevel);
		ION_u8CheckInPutRange(u8PM25OutLevel,PmAirOutQLevelMax,PmAirOutQLevelMin,ION_nu8AirOutQLevel);

		if((ION_u8TboxRequest == True)&&(ION_u16TBoxReqMaxTimer > 20)&&(ION_u8PM25RunFlag == False))/*at lease run 2s while Tbox req,170729*/
		{
			ION_u8TboxRequest = False;
			ION_vControlPm25Pin(Low); /*170524*/
			ION_u16NoteLostTime = 0;/*when pm 25 power is off, clear the error counter,171229*/
			ION_u8PM25StsReq = False;
			ION_u8PM25EnableCheckLostDtc = False;
		}
	}	
}

static void ION_vPM25UpdateInnerAirQuanlity(void)
{
	uint8 u8MMIPM25PopupOperationSts = MMI_u8GetValue(MMI_nPm25PopupOerationSts);
	uint8 u8MmiIonControlMode = MMI_u8GetValue(MMI_nu8SysState);//change to sys mode,170604,MMI_nu8IonMode);
	uint8 u8RemoteSts = CANAPP_u16GetValue(CANAPP_nu16TBOX_AirCleanerReq);/*CR:not allow ion auto on  if Tbox remote start,171127*/
	if ((u8MMIPM25PopupOperationSts == True)&&(u8MmiIonControlMode == ION_nMmiIonOff)&&(ION_u16PM25InDen != ION_PM25DenDefault)) /*add,invalid,allow exceed display, only in Off mode*/
	{
		if (ION_u16PM25InDen > PM25_nAirBadQaulity) /*delete '=', keep the same as auto control,180417*/
		{
			if (ION_u16Pm25ExceedTime <= PM25_nAirBadTime)
			{
				ION_u16Pm25ExceedTime++;
			}
		}
		else if (ION_u16PM25InDen <= PM25_nAirGoodQaulity)
		{
			if (ION_u16Pm25ExceedTime >0 )
			{
				ION_u16Pm25ExceedTime --;
			}
		}
		else
		{
			/*nothing to do*/
		}

		if (ION_u16Pm25ExceedTime >= PM25_nAirBadTime)
		{
			ION_u8PM25Exceed = True;
		}
		else if (ION_u16Pm25ExceedTime <= PM25_nAirGoodTime) 
		{
			ION_u8PM25Exceed = False;
		}
		else
		{
			/*nothing to do*/
		}
	}
	else
	{
		ION_u16Pm25ExceedTime = 0;
		ION_u8PM25Exceed = False;
		ION_u16IonOnWaitTimer = 0;
	}

	//if ((ION_u8AirInQuality == PM25_Initing)||(ION_u16PM25InDen == ION_PM25DenDefault))
	if (ION_u16PM25InDen == ION_PM25DenDefault) /*170916*/
	{
		/*KEEP,170819*/
	}
	else
	{
		/*good*/
		if(ION_u16PM25InDen < PM25_Pm25Inside_LittleBadLevel)/*150 ug/m3 */
		{
			ION_u8AirInQuality = PM25_AirCondition_Good;
		}
		/*bad*/
		else if(ION_u16PM25InDen < PM25_Pm25Inside_VeryBadLevel)/*200 ug/m3 */
		{
			ION_u8AirInQuality = PM25_AirCondition_LittleBad;
		}
		/*very bad*/
		else
		{
			ION_u8AirInQuality = PM25_AirCondition_VeryBad;
		}
	}
}

static void ION_vIonControlByInnerAirQuanlity(void)
{  
#if 0
	if((ION_u8PM25Exceed == True)&&(ION_u16Pm25ExceedTime >= PM25_nAirBadTime))
	{		
		if (ION_u16IonOnWaitTimer <= IonDelayRunTime)
		{
			ION_u16IonOnWaitTimer++;
		}
		else
		{
			ION_u16IonOnWaitTimer = 0;
			MMI_vTurnOnByPm25Exceed();
		}
	}
#endif
}

static void ION_vWorkModeControl(void)
{
    uint8 u8MmiIonControl = MMI_u8GetValue(MMI_nu8IonCtrl);

    if(u8MmiIonControl == ION_nMmiIonCleanerOff)
    {
        ION_vControlIonModePin(0u);
        ION_vControlCleanModePin(0u);
    }
    //else if(u8MmiIonControl == ION_nMmiIonCleanMode)
    //{
        //ION_vControlIonModePin(0u);
        //ION_vControlCleanModePin(1u);
    //}
    else if(u8MmiIonControl == ION_nMmiIonIonMode)
    {
        ION_vControlIonModePin(1u);
        ION_vControlCleanModePin(1u);
    }
    else
    {
    }
}
/*****************************************************************************
 Function      : ION_u8GetValue                                   *
 Description   : The extern model get the uint8 type variables value from     *
				 this model                                                   *
 Return Value  : uint8                                                       *
*****************************************************************************/
uint8 ION_u8GetValue( ION_tu8enVarNumber enIndex )
{
    uint8 u8ReturnValue;
	if ( enIndex < ION_nu8Max )
	{
		u8ReturnValue = ION_au8Array[enIndex];
	}
	else
	{
		u8ReturnValue = ION_au8Array[ION_nu8Max-1];
	}
    return u8ReturnValue;
}

/*****************************************************************************
 Function      : ION_u16GetValue                                   *
 Description   : The extern model get the uint8 type variables value from     *
				 this model                                                   *
 Return Value  : uint16                                                       *
*****************************************************************************/
uint16 ION_u16GetValue( ION_tu16enVarNumber enIndex )
{
    uint16 u16ReturnValue;
	if ( enIndex < ION_nu16Max )
	{
		u16ReturnValue = ION_au16Array[enIndex];
	}
	else
	{
		u16ReturnValue = ION_au16Array[ION_nu16Max-1];
	}
    return u16ReturnValue;
}
/*ITP10,160424*/
/*****************************************************************************
 Function      : ION_u8ForceIoControl_Write                                 
 Description   : Ccp control function
 Takes         : Nothing
 Return Value  : None                                                *
*****************************************************************************/
Std_ReturnType ION_u8ForceIoControl_Write(/*IN*/uint32 ForceIoControlWord)
{
	uint8 u8Result=0;
	tstCcpContronType CcpControlWord;
	CcpControlWord.CcpContronData=(uint16)ForceIoControlWord;
	CcpControlWord.CcpCommand=(uint8)(ForceIoControlWord>>16);
	CcpControlWord.CcpCommandFlag=(uint8)(ForceIoControlWord>>24);
	if(CcpControlWord.CcpCommandFlag==True)
	{
		switch(CcpControlWord.CcpCommand)
		{
			case 0:
				ION_ClrCcpForceByte();
				break;
			case 0x7:
			case 0xA1:
				ION_SetCcpForceBit(ION_nIONStsReq);
				ION_u16CcpControlData[ION_nIONStsReq]=CcpControlWord.CcpContronData;
				break;
			case 0x8:
			case 0xA2:
				ION_ClrCcpForceBit(ION_nIONStsReq);
				ION_u16CcpControlData[ION_nIONStsReq]=0;
				break;
			case 0x9:
			case 0xA3: /*pts*/
				ION_SetCcpForceBit(ION_nIONPm25Output);
				ION_u16CcpControlData[ION_nIONPm25Output]=CcpControlWord.CcpContronData;
				break;
			case 0xA:
			case 0xA4: /*pts*/
				ION_ClrCcpForceBit(ION_nIONPm25Output);
				ION_u16CcpControlData[ION_nIONPm25Output]=CcpControlWord.CcpContronData;
				break;
			case 0x81: /*pts*/
				ION_SetCcpForceBit(ION_nIONPm25Output);
				ION_u16CcpControlData[ION_nIONPm25Output]=CcpControlWord.CcpContronData;
				break;
			case 0x82: /*pts*/
				ION_SetCcpForceBit(ION_nIONCleanMode);
				ION_u16CcpControlData[ION_nIONCleanMode]=CcpControlWord.CcpContronData;
				break;
			case 0x83: /*pts*/
				ION_SetCcpForceBit(ION_nIONIonMode);
				ION_u16CcpControlData[ION_nIONIonMode]=CcpControlWord.CcpContronData;
				break;
			case 0xB:
				ION_SetCcpForceBit(ION_nIONPm25OutDen);
				ION_u16CcpControlData[ION_nIONPm25OutDen]=CcpControlWord.CcpContronData;
				break;
			case 0xC:
				ION_ClrCcpForceBit(ION_nIONPm25OutDen);
				ION_u16CcpControlData[ION_nIONPm25OutDen]=CcpControlWord.CcpContronData;
				break;
			case 0xD:
				ION_SetCcpForceBit(ION_nIONPm25InDen);
				ION_u16CcpControlData[ION_nIONPm25InDen]=CcpControlWord.CcpContronData;
				break;
			case 0xE:
				ION_ClrCcpForceBit(ION_nIONPm25InDen);
				ION_u16CcpControlData[ION_nIONPm25InDen]=CcpControlWord.CcpContronData;
				break;
			default:
                u8Result= RTE_E_INVALID;
				break;
		}
	}
	else
	{
		ION_ClrCcpForceByte();
	}
    return u8Result;
}	

/*****************************************************************************
 Function      :ION_vCcpInputForce                                 
 Description   : force Input value
 Takes         : Nothing
 Return Value  : None                                                *
*****************************************************************************/
static void ION_vCcpOutputForce(void)
{	
	if(ION_GetCcpForceBit(ION_nIONStsReq))
	{
		ION_u8IONStsReq=ION_u16CcpControlData[ION_nIONStsReq];
	}

	if(ION_GetCcpForceBit(ION_nIONPm25Output))
	{
		ION_u8PM25StsReq = ION_u16CcpControlData[ION_nIONPm25Output];
		if (ION_u16CcpControlData[ION_nIONPm25Output] == 0)
		{
			ION_vWritePm25PinLevel(Low);
			ION_u16NoteLostTime = 0;/*when pm 25 power is off, clear the error counter,180110*/
		}
		else
		{
			ION_vWritePm25PinLevel(High);
		}
	}

	if(ION_GetCcpForceBit(ION_nIONPm25OutDen))
	{
		ION_u16PM25OutDen=ION_u16CcpControlData[ION_nIONPm25OutDen];
	}

	if(ION_GetCcpForceBit(ION_nIONPm25InDen))
	{
		ION_u16PM25InDen=ION_u16CcpControlData[ION_nIONPm25InDen];
	}

	if(ION_GetCcpForceBit(ION_nIONCleanMode))
	{
		ION_vWriteCleanModePinLevel(ION_u16CcpControlData[ION_nIONCleanMode]);
	}

	if(ION_GetCcpForceBit(ION_nIONIonMode))
	{
		ION_vWriteIonModePinLevel(ION_u16CcpControlData[ION_nIONIonMode]);
	}
}

static void ION_vControlPm25Pin(uint16 PinLevel)
{
    if(ION_GetCcpForceBit(ION_nIONPm25Output) == 0u)
	{
        ION_vWritePm25PinLevel(PinLevel);
	}
    else
    {
    }
}

static void ION_vControlCleanModePin(uint16 PinLevel)
{
    if(ION_GetCcpForceBit(ION_nIONCleanMode) == 0u)
	{
        ION_vWriteCleanModePinLevel(PinLevel);
	}
    else
    {
    }
}

static void ION_vControlIonModePin(uint16 PinLevel)
{
    if(ION_GetCcpForceBit(ION_nIONIonMode) == 0u)
	{
        ION_vWriteIonModePinLevel(PinLevel);
	}
    else
    {
    }
}

void  ION_vClearErrorCode(void)
{
	ION_u8PM25ErrSts=0;
	ION_u8IONErrSts=0;
	ION_u16NoteLostTime = 0;/*180417*/
}

static void ION_vVehicleConfig(void)
{
	if (ION_nUsePm25Cfg == False)
	{
		ION_u8PM25StsReq =0;
		ION_u8PM25Sts = 0;
		ION_u8PM25ErrSts = 0;
		ION_u8TboxRequest = 0;
		ION_u8PM25Exceed = 0;
		ION_vWritePm25PinLevel(Low);
		ION_u16NoteLostTime = 0;/*when pm 25 power is off, clear the error counter,171229*/
	}

	if (ION_nUseIonCfg == False)
	{
		ION_u8IONStsReq =0;
		ION_u8IONErrSts = 0;
		ION_u8IONIZEState = 0;
	}

}

static void ION_vPopupHandle(void)
{
	uint8 u8MmiPm25PopSts = CANAPP_u16GetValue(CANAPP_nu16MMI_PM25PopupActive); /*MMI send conmand cycle is 20ms while operation*/
	uint8 u8MmiPm25PopActive = MMI_u8GetValue(MMI_nPm25PopActive);
	if (ION_u8PM25Exceed == True) /*send popup 3 frame o every 100ms*/
	{
		if (ION_u8Pm25IsFirstPopup==True)  /*the first time send popup*/
		{
			if ((u8MmiPm25PopSts == True)||(u8MmiPm25PopActive == True)) /*MMI Has pop up the pm25,*/
			{
				ION_u8Pm25PopComfirm = True;
				//ION_u8Pm25IsFirstPopup=False; /*wait 5s, 180402*/
				//MMI_vTurnOnByPm25Exceed();
			}
			
			if (ION_u8Pm25PopComfirm == True)
			{	
					if (ION_u16PopupTimer < PM25_PopupKeepTime) /*debug: Real mmi, ac only send 2 popup req,180425*/
					{
						ION_u16PopupTimer++;
						ION_u8PM25PopupReq = ION_nPM25PopFirst;
					}
					else
					{
						ION_u8PM25PopupReq = ION_nPM25PopNone;
						if (ION_u16IonOnWaitTimer <= IonDelayRunTime)
						{
							ION_u16IonOnWaitTimer++;
						}
						else
						{
							ION_u16IonOnWaitTimer = 0;
							ION_u8Pm25IsFirstPopup=False;
							MMI_vTurnOnByPm25Exceed();
						}
					}
			}
			else
			{
				if(ION_u16FirstPopupTimer < PM25_FirstPopupCycle)	 /*not receive the popup state, send popup request every 10 s*/
				{
					ION_u16FirstPopupTimer++;
					ION_u16PopupTimer =0;
				}
				else
				{
					if (ION_u16PopupTimer < PM25_PopupKeepTime) /*300ms*/
					{
						ION_u16PopupTimer++;
						ION_u8PM25PopupReq = ION_nPM25PopFirst;
					}
					else
					{
						ION_u8PM25PopupReq = ION_nPM25PopNone;
						ION_u16FirstPopupTimer =0;
					}
				}
			}

		}
		else
		{
			ION_u8Pm25PopComfirm = False;/*180402*/
			if (ION_u16PopupTimer < PM25_PopupKeepTime) /*300ms*/
			{
				ION_u16PopupTimer++;
				ION_u8PM25PopupReq = ION_nPM25PopSecond;
				
				if (ION_u16PopupTimer == PM25_PopupKeepTime) /*delete -1, debug:200->300ms,180425*/
				{
					MMI_vTurnOnByPm25Exceed();
				}
			}
			else
			{
				ION_u8PM25PopupReq = ION_nPM25PopNone;
			}
		}
	}
	else
	{
		ION_u8PM25PopupReq = ION_nPM25PopNone;
		ION_u16PopupTimer=0;
		ION_u16FirstPopupTimer=PM25_FirstPopupCycle;
		ION_u8Pm25PopComfirm = False;
		ION_u16IonOnWaitTimer = 0;
	}

}

