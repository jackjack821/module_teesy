/*******************************************************************************
| Module Name: directed current motor
| File Name: DCM.c
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

#define DCM                         /* Name of the Module                */

/********************************************************************************

                               _(\_/)
                             ,((((^`\
                            ((((  (6 \
                          ,((((( ,    \
      ,,,_              ,(((((  /"._  ,`,
     ((((\\ ,...       ,((((   /    `-.-'
     )))  ;'    `"'"'""((((   (
    (((  /            (((      \
     )) |                      |
    ((  |        .       '     |
    ))  \     _ '      `t   ,.')
    (   |   y;- -,-""'"-.\   \/
    )   / ./  ) /         `\  \
       |./   ( (           / /'
       ||     \\          //'|
       ||      \\       _//'||
       ||       ))     |_/  ||
       \_\     |_/          ||
       `'"                  \_\
                            `'"
****************************** .FILE_HEADER_END ******************************/

/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
*****************************************************************************/
/* System-headerfiles */
#include "General.h"

/* Foreign headerfiles */

/* Own headerfiles */
#include "DCM_Type.h"
#include "DCM.h"
#include "DCM_Cfg.h"
#include "DCM_interface.h"
#include "DCM_Private.h"
#include "KEY_Interface.h"
#include "KEY.h"  
#include "Force.h"  

#include "TouchKey.h"  


static uint16	DCM_au16PtaPosFb[MotorNum];
static uint16	DCM_au16PtaRawPosFb[MotorNum];
static uint8	DCM_au8ErrorCode[MotorNum];
static DCM_tenValueSts	DCM_enSetTargetValid[MotorNum];
static uint16	DCM_au16SetPosition[MotorNum];

static uint8 	DCM_au8Array[DCM_nu8OutputMax];
static uint16 	DCM_au16Array[DCM_nu16OutputMax];
static uint16   DCM_au16OatValue;
static uint8   DCM_u8VibrationFlag=False;
static uint8 DCM_u8VibrateTimes=0;
static uint8 DCM_u8VibrateCycles=0;
/*********************************************************************/


uint8 MotorVibrateType=1;                   
uint8 DCM_MotorVibrateTimer=10;
uint8 DCM_MotorVibrateCycle=10;
uint16 	DCM_motor_duty=600;
uint16  u8Touch_duty=600;
uint16  u8GSID_duty=300;


extern uint8 u8Gsid_flag;
static uint8 u8Gsid_count=0;
extern uint8 u8Button_Status_Flag;
	
/*********************************************************************/


#ifdef Mazda
static DCM_tenCorretFBState DCM_CorrectDirect[MotorNum];
#endif
static uint8    DCM_ResumeDelayTime;

#ifdef ENABLERESTDRIVING
static uint16	DCM_u16RestDutyCounter[MotorNum];
#endif
#ifdef ENABLECORRECTPTAFB
static uint32	DCM_au32PTAFBSave[MotorNum];
static uint8	DCM_u8PTAFBSaveValid[MotorNum];
#endif

DCM_tstState DCM_axPorts[MotorNum];
static DCM_tstBlockErrStatus DCM_axPortsBlockErr[MotorNum];
#ifdef OpenLoadEnable
static DCM_tstOpenLoadErrStatus DCM_axPortsOpenLoadErr[MotorNum];
#endif
#ifdef OverCurrentEnable
static DCM_tstOverCurrentErrStatus DCM_axPortsOverCurrentErr[MotorNum];
#endif
#ifdef OverTempEnable
static DCM_tstOverTempErrStatus DCM_axPortsOverTempErr[MotorNum];
#endif

void DCM_vCcpOutputForce(void);
void DCM_vGetInputValue(void);
void DCM_vADErrorDetect(uint8 enPort);
static DCM_tenDirectionState DCM_enDecideOperatingDirection(uint8 enPort);

void DCM_vOutputWrite(void);
 #ifdef ENABLECORRECTPTAFB
void DCM_enSavePTAFB(uint8 enPort);
DCM_tenCorretFBState DCM_vCorrectFB(uint8 enPort);
#endif
void DCM_vSetDirectionStopStatus(uint8 enPort);
void DCM_vSetDirectionMovingStatus(uint8 enPort);
void DCM_vSetDirectionMovingStatusWithoutFB(uint8 enPort);
void DCM_vDirectionDriveCalc(uint8 enPort);
#ifdef ENABLERESTDRIVING
void DCM_vRestDrivingCalc(uint8 enPort, DCM_tenPortState enDirection);
void DCM_vResetRestDriving(uint8 enPort);
#endif
void DCM_vExceptionHandler(uint8 enPort);
#ifdef ENABLEBLOCKCHECKDRIVING
void DCM_vCheckBlockPreviousDetection(uint8 enPort);
void DCM_vCheckBlockStatus(uint8 enPort);
void DCM_vResetBlockCheck(uint8 enPort);
void DCM_vBlockPreDrving(uint8 enPort);
void DCM_vBlockConfirm(uint8 enPort);
#ifdef Mazda
DCM_tenCorretFBState DCM_vCorrectDirect(uint8 enPort);
#endif
#endif
void DCM_vSetDrivingDirection(uint8 enPort);
#ifdef OpenLoadEnable
void DCM_vCheckOpenLoadStatus(uint8 enPort);
void DCM_vCheckOpenLoadPreviousDetection(uint8 enPort);
void DCM_vOpenLoadPreDrving(uint8 enPort);
void DCM_vOpenLoadConfirm(uint8 enPort);
DCM_tenSPIRead DCM_u8GetOpenLoadStatus(uint8 enPort);
void DCM_vResetOpenLoad(uint8 enPort, uint8 u8PreDrvTimes);
#endif
#ifdef OverCurrentEnable
void DCM_vCheckOverCurrentStatus(uint8 enPort);
void DCM_vCheckOverCurrentPreviousDetection(uint8 enPort);
void DCM_vOverCurrentPreDrving(uint8 enPort);
void DCM_vOverCurrentConfirm(uint8 enPort);
DCM_tenSPIRead DCM_u8GetOverCurrentStatus(uint8 enPort);
void DCM_vResetOverCurrent(uint8 enPort, uint8 u8PreDrvTimes);
#endif

#ifdef OverTempEnable
void DCM_vCheckOverTempStatus(uint8 enPort);
void DCM_vCheckOverTempPreviousDetection(uint8 enPort);
void DCM_vOverTempPreDrving(uint8 enPort);
void DCM_vOverTempConfirm(uint8 enPort);
DCM_tenSPIRead DCM_u8GetOverTempStatus(uint8 enPort);
void DCM_vResetOverTemp(uint8 enPort, uint8 u8PreDrvTimes);
#endif
DCM_tenSPIRead DCM_u8SPIStatusRead(uint8 enPort, DCM_tenSPIErrType enErrType);
void DCM_vSetMotorVibrateStatus_PWM(void);
void DCM_vSetMotorVibrateStatus_Timer(void);

/* ===========================================================================
* Function   : void DCM_vReset (void)
* Description: Reset function of DCM
* Takes      : Nothing
* Returns    : Nothing
*/
void DCM_vReset(void)
{

	
	uint8 i;

//	PMC0 |= 0x0001; /* Alternative Functions */                                                 
    //	PFC0 |= (0x0000); /* Alternative 2 */                                                     
    //	PM0 &= ~(1<<0);    /* P0_0 CANTX     Output */ 
	//P0 |= 0x0001; /* set Tx/Rx port high level*/
	
	for(i=0u;i<(uint8)MotorNum;i++)
	{
        #ifdef ENABLECORRECTPTAFB
		DCM_u8PTAFBSaveValid[i]=False;
        #endif
		#ifdef ENABLERESTDRIVING
		DCM_u16RestDutyCounter[i]=0u;
		#endif
		DCM_axPortsBlockErr[i].stBlockStatus=nBlockNotDetect;
        #ifdef OpenLoadEnable
		DCM_vResetOpenLoad(i, DCM_stMotorProperty[i].u8OpenloadPreviousDrvCount);
        #endif           
        #ifdef OverCurrentEnable
		DCM_vResetOverCurrent(i, DCM_stMotorProperty[i].u8OverCurrentPreviousDrvCount);
        #endif
        #ifdef OverTempEnable
		DCM_vResetOverTemp(i, DCM_stMotorProperty[i].u8OverTempPreviousDrvCount);
        #endif
        DCM_au16PtaPosFb[i]=0xFFFFu;
        DCM_au16PtaRawPosFb[i]=0xFFFFu;

	}
    DCM_au8Array[DCM_nu8SwVersion]=0xA3u;
}

/* ===========================================================================
* Function   : void DCM_vInit (void)
* Description: Init function of DCM
*              Called in Active->On container.
               Calls DCM_vReset also.
* Takes      : Nothing
* Returns    : Nothing
*/
void DCM_vInit(void)
{
	uint8 i;
	for(i=0u;i<(uint8)MotorNum;i++)
	{
      	#ifdef ENABLECORRECTPTAFB
		DCM_u8PTAFBSaveValid[i]=False;
      	#endif
		#ifdef ENABLERESTDRIVING
		DCM_u16RestDutyCounter[i]=0u;
		#endif
		DCM_axPortsBlockErr[i].stBlockStatus=nBlockNotDetect;

		DCM_axPorts[i].u16ActiveTime_Tmr=0u;
		DCM_vResetBlockCheck(i);
        #ifdef OpenLoadEnable
		DCM_vResetOpenLoad(i, DCM_stMotorProperty[i].u8OpenloadPreviousDrvCount);
        #endif
        #ifdef OverCurrentEnable
		DCM_vResetOverCurrent(i, DCM_stMotorProperty[i].u8OverCurrentPreviousDrvCount);
        #endif
        #ifdef OverTempEnable
		DCM_vResetOverTemp(i, DCM_stMotorProperty[i].u8OverTempPreviousDrvCount);
        #endif
		DCM_au8ErrorCode[i]=0u;
	}
	DCM_vClrForceByteFlag();
    DCM_ResumeDelayTime=150u;
    #ifdef Mazda
    DCM_CorrectDirect[DCM_nMixDrMotor]=nCorrectCCW;
    DCM_CorrectDirect[DCM_nAirdMotor]=nCorrectCW;
    #endif
        
}
/* ===========================================================================
* Function   : void DCM_vDeinit (void)
* Description: De-init function of DCM
*              Called in On->Active container.
               Calls DCM_vReset also.
* Takes      : Nothing
* Returns    : Nothing
*/
void DCM_vDeinit (void)
{
	uint8 i;	
	for(i=0u;i<(uint8)MotorNum;i++)
	{
		DCM_axPorts[i].bi2OkToSleep=True;
		DCM_au8ErrorCode[i]=0u;
	}
}


/*****************************************************************************
 Function      : DCM_enGetU8Value                                            *
 Description   : The extern model get the uint8 type variable value from this*
				 model                                                       *
 Return Value  : uint8 value                                                 *
*/
//DCM_tenValueSts DCM_enGetU8Value( DCM_nu8OutputVarNumber enIndex,uint8 *value )
uint8 DCM_u8GetValue(DCM_nu8OutputVarNumber enIndex)
{
    uint8 u8ReturnValue;
	if ( enIndex < DCM_nu8OutputMax )
	{
        u8ReturnValue=DCM_au8Array[enIndex];
	}
	else
	{
		u8ReturnValue=DCM_au8Array[(uint8)DCM_nu8OutputMax-1u];
	}
        return u8ReturnValue;
}
/*****************************************************************************
 Function      : DCM_enGetU16Value                                           *
 Description   : The extern model get the uint16 type variable value from this*
				 model                                                       *
 Return Value  : uint8 value                                                 *
*/

//DCM_tenValueSts DCM_enGetU16Value( DCM_nu16OutputVarNumber enIndex, uint16 *value )
uint16 DCM_u16GetValue(DCM_nu16OutputVarNumber enIndex)
{
    uint16 u16ReturnValue;
	if ( enIndex < DCM_nu16OutputMax )
	{
		u16ReturnValue=DCM_au16Array[enIndex];
	}
	else
	{
		u16ReturnValue=0u;
	}
      return u16ReturnValue;
}
/*****************************************************************************
 AUTHOR:		 : Li Jiaye											  *
 DATE: 		 : 2015/07/22										  *
 Function      : Dcm_vActive                                                 *
 Description   : 
 Return Value  : None                                                        *
*/

 
void DCM_vActive(void)
{
}

void MotorGSID_duty_set(uint32 parameter)
{	
	parameter=parameter*10;
	if(parameter>1000)
		parameter=1000;	
	u8GSID_duty=parameter;
}
void DCM_MCU_u8motortime_set(uint32 parameter)
{	
	DCM_MotorVibrateTimer=parameter;
	
}

void DCM_MotorVibrateCycle_set(uint32 parameter)
{
DCM_MotorVibrateCycle=parameter;
}
void DCM_motor_duty_set(uint32 parameter)
{
	parameter=parameter*10;
	if(parameter>1000)
		parameter=1000;	
	 u8Touch_duty=parameter;
}

/*******************************************************************************
* Function   : void DCM_vMain (void)
* Description: The main container function for DCM module.
*              This function is usually called every 10mS in On state.
* Takes      : Nothing
* Returns    : Nothing
*/
void DCM_vMain(void)
{
	uint8 enPort;
       uint8 u8LowVoltage,u8HighVoltage,u8ADvalid;

	uint16 u16KeyPressed,u16KeyPressed2;
	uint16 u16ForceKeyPressed2;
	uint32 u32KeyPress,u32KeyPress2;
   	uint32 u32PhyKeyPressFlag=0;
	static uint8 u8KeyStateLast=0;  		 //上一次的按键值
	static uint8 u8KeyState_flag=0;    	  //表示按键状态的更改
       
	u32KeyPress=DCM_u32GetKeyKeyPressed;
	u32KeyPress2=KEY_u32KeyStatusIsPress();
	u16KeyPressed2=((uint16)(u32KeyPress2&0x000001FF)); /*only 9 key, bit 0~8*/
	u16ForceKeyPressed2=(uint16)((u32KeyPress2>>9)&0x000001FF); /*change 16 to 9,190423*/
	DCM_au16Array[DCM_nu16KeyRawPress] = u16KeyPressed2;

/*
按键按下和松开电机运动
1.压力标志有 ，按键标志有 flag 有
2.压力标志无按键标志无flag无 替代下面的电机flag标志
3.有压力有滑动事件同意触发一次震动
加一个状态判断标准滑动事件邋
*/

	if(u8KeyStateLast!=u8Button_Status_Flag)          //实现按下和双开 需删除
	{
		u8KeyState_flag=1;     //变
	}
	else
	{
		u8KeyState_flag=0;
	}                                      //不必变
	
	u8KeyStateLast=u8Button_Status_Flag;

	
       u32PhyKeyPressFlag = (uint32)KEY_vKeyGetPhyKeyPressAction();

	if((DCM_sbiLowVoltage == True)||(DCM_sbiHighVoltage == True))
	{
		DCM_vReset(); 
	}
	else
	{
		if((u8KeyState_flag!=0)&&(u8Gsid_flag!=1))    /*u8Force_Pressed_Flag是否按下的标准压力*/	
		{
			DCM_u8VibrationFlag=True;   //电机震动标志	
			DCM_motor_duty=u8Touch_duty;
			//DCM_motor_duty=700;
		}
		else
		{
	
		}
		 if(u8Gsid_flag==1)          //  滑动事件开始震动	
		//if(u8Gsid_flag !=5)         //for test
		{	
			u8Gsid_count++;
				if(u8Gsid_count>100)  //100ms
				{	u8Gsid_count=0;				
				DCM_u8VibrationFlag=True;   //电机震动标志
				DCM_motor_duty=u8GSID_duty;
					}			
		}
		
		DCM_au8Array[DCM_nu8MotorDriver] = DCM_u8VibrationFlag;
		if(DCM_u8VibrationFlag==True)
		{
			MCU_u16PinWrite(MCU_mPinID_P10_4, 1);
			if (MotorVibrateType==MotorVibrate_Timer)
			 DCM_vSetMotorVibrateStatus_Timer();
			else if(MotorVibrateType==MotorVibrate_PWM)
			DCM_vSetMotorVibrateStatus_PWM();                       //start the motor
			
		}
		else
		{
			MCU_u16PinWrite(MCU_mPinID_P10_4, 0);
			MCU_u16PWGASetDuty(MCU_mPWGA10, 0);
		                  //start the motor

		}


	}

	
}
  


/*******************************************************************************
*Function : void DCM_vOutputWrite(void)
*Description :write the output value 
*takes : nothing
*return: nothing
*/
void DCM_vOutputWrite(void)
{
      DCM_au8Array[DCM_nu8Valid]=True;

      DCM_au8Array[DCM_nu8MixDrDirection]=(uint8)DCM_axPorts[0].enRequired;
      DCM_au8Array[DCM_nu8MixDrErrorCode]=DCM_au8ErrorCode[0];
      DCM_au16Array[DCM_nu16AdValueMixDr]=DCM_au16PtaPosFb[0];
      DCM_au16Array[DCM_nu16AdRawValueMixDr]=DCM_au16PtaRawPosFb[0];

      DCM_au8Array[DCM_nu8AirdDirection]=(uint8)DCM_axPorts[1].enRequired;
      DCM_au8Array[DCM_nu8AirdErrorCode]=DCM_au8ErrorCode[1];
      DCM_au16Array[DCM_nu16AdValueAird]=DCM_au16PtaPosFb[1];
      DCM_au16Array[DCM_nu16AdRawValueAird]=DCM_au16PtaRawPosFb[1];

      DCM_au8Array[DCM_nu8RfaDirection]=(uint8)DCM_axPorts[2].enRequired;
      DCM_au8Array[DCM_nu8RfaErrorCode]=DCM_au8ErrorCode[2];
      DCM_au16Array[DCM_nu16AdValueRfa]=DCM_au16PtaPosFb[2];
      DCM_au16Array[DCM_nu16AdRawValueRfa]=DCM_au16PtaRawPosFb[2];
#if (SYC_ZONES==2)
      DCM_au8Array[DCM_nu8MixPsDirection]=(uint8)DCM_axPorts[3].enRequired;
      DCM_au8Array[DCM_nu8MixPsErrorCode]=DCM_au8ErrorCode[3];
      DCM_au16Array[DCM_nu16AdValueMixPs]=DCM_au16PtaPosFb[3];
      DCM_au16Array[DCM_nu16AdRawValueMixPs]=DCM_au16PtaRawPosFb[3];
   #endif
}

/*******************************************************************************
*Function : void DCM_vADErrorDetect(uint8 enPort)
*Description : the function to handle the input AD value 
*takes : DCM_enMotorNumber enPort : The port number
*return: nothing
*/
void DCM_vADErrorDetect(uint8 enPort)
{    
    
    if(DCM_stMotorProperty[enPort].nFeedback==WithFeedback)
    {
        if(DCM_au16PtaRawPosFb[enPort]>1003u)
        {
          DCM_u8Shot2VccErrCodeSet(enPort);
          DCM_u8Shot2GndErrCodeClr(enPort);                     
        }
        else if(DCM_au16PtaRawPosFb[enPort]<20u)
        {
          DCM_u8Shot2GndErrCodeSet(enPort);
          DCM_u8Shot2VccErrCodeClr(enPort);
        }
        else
        {
          DCM_u8Shot2VccErrCodeClr(enPort);
          DCM_u8Shot2GndErrCodeClr(enPort);
        }              
    }
    else
    {
        DCM_u8Shot2VccErrCodeClr(enPort);
        DCM_u8Shot2GndErrCodeClr(enPort);
                
    }

}
/*******************************************************************************
*Function : void DCM_vGetInputValue(void)
*Description : the function to get the input value from foreign modul
*takes : nothing
*return: nothing
*/
void DCM_vGetInputValue(void)
{
	uint8 i;    

    for(i=0u;i<(uint8)MotorNum;i++)
    {
        DCM_enSetTargetValid[i]=DCM_enTargetPositionImport(i,&DCM_au16SetPosition[i]);
        if(DCM_stMotorProperty[i].nFeedback==WithFeedback)
        {
            DCM_enCurrentPositionImport(i,&DCM_au16PtaPosFb[i]);
        }
        else
        {
            DCM_au16PtaPosFb[i]=500u;
        }
        DCM_au16PtaRawPosFb[i]=DCM_au16PtaPosFb[i];
    }
}


/*******************************************************************************
* Function   : static DCM_tenDirectionState DCM_enDecideOperatingDirection(const DCM_enMotorNumber enPort)
* Description: Determines the movement direction required for the u8Port.
*              Called from DCM_vMain for each motor port.
* Takes      : DCM_enMotorNumber enPort : The port number ( 0->(DCM_nPortss - 1))
* Returns    : enPortState : The required direction.
*/
static DCM_tenDirectionState DCM_enDecideOperatingDirection(uint8 enPort)
{
	int16 deltaSetPosFB;
#ifdef ENABLECORRECTPTAFB
	DCM_tenCorretFBState nCorrectFBStatus;
#endif
	DCM_tenDirectionState en8DirectionReturn;
         en8DirectionReturn=nDirectionStop;
#ifdef ENABLECORRECTPTAFB
	nCorrectFBStatus=nCorrectSuccess;
	if(DCM_boGetFeedbackError(enPort)==1)
	{
		/*correct the fb according to driving time*/
		nCorrectFBStatus=DCM_vCorrectFB(enPort);
	}
	else
	{
		DCM_u8PTAFBSaveValid[enPort]=True;
		DCM_enSavePTAFB(enPort);
	}
	
	if(nCorrectFBStatus==nCorrectCW)
	{
		en8DirectionReturn= nDirectionCW;
	}
	else if(nCorrectFBStatus==nCorrectCCW)
	{
		en8DirectionReturn= nDirectionCCW;
	}
	else if(nCorrectFBStatus==nCorrectStop)
	{
        en8DirectionReturn= nDirectionStop;
	}
	else
	{/*correct FB success*/

#endif
        if(DCM_stMotorProperty[enPort].nFeedback==WithFeedback)
        {            
    		deltaSetPosFB=(int16)DCM_au16SetPosition[enPort]-(int16)DCM_au16PtaPosFb[enPort];
    		if(DCM_axPorts[enPort].enDirectionState==nDirectionStop)
    		{
    			if(deltaSetPosFB>DCM_stMotorProperty[enPort].i16Startvalue)
    			{
    				en8DirectionReturn= nDirectionCW;
    			}
    			else if(deltaSetPosFB<-DCM_stMotorProperty[enPort].i16Startvalue)
    			{
    				en8DirectionReturn= nDirectionCCW;
    			}
                else
                {
                }
    		}
    		else
    		{
    			#ifdef ENABLERESTDRIVING
    			if((deltaSetPosFB>DCM_stMotorProperty[enPort].i16Stopvalue)&&(deltaSetPosFB<nRest_Config))
    			{
    				en8DirectionReturn= nDirectionRestCW;
    			}
    			else
    			#endif
    			if(deltaSetPosFB>DCM_stMotorProperty[enPort].i16Stopvalue)
    			{
    				en8DirectionReturn= nDirectionCW;
    			}
                else
                {
                }
    			#ifdef ENABLERESTDRIVING
    			if((deltaSetPosFB<-DCM_stMotorProperty[enPort].i16Stopvalue)&&(deltaSetPosFB>-nRest_Config))
    			{
    				en8DirectionReturn= nDirectionRestCCW;
    			}
    			else
    			#endif
    			if(deltaSetPosFB<-DCM_stMotorProperty[enPort].i16Stopvalue)
    			{
    				en8DirectionReturn= nDirectionCCW;
    			}
                else
                {
                }
    		}	
        }
        else
        {
            if(DCM_au16SetPosition[enPort]>500u)
            {
                en8DirectionReturn= nDirectionCW;
            }
            else
            {
                en8DirectionReturn= nDirectionCCW;
            }
        }
	#ifdef ENABLECORRECTPTAFB
	}
	#endif
	
	return en8DirectionReturn;
}

#ifdef ENABLECORRECTPTAFB
/*******************************************************************************
*Function : uint8 DCM_vCorrectFB(const DCM_enMotorNumber enPort)
*Description: used to correct the FB of motor according to driving time when FB shot to GND or Vcc heppening
*takes: none
*return: correct fb success---0, driving CW return 2, driving CCW return 3
*/
DCM_tenCorretFBState DCM_vCorrectFB(uint8 enPort)
{
	DCM_tenCorretFBState enReturnValue; 
	if(DCM_stMotorProperty[enPort].nFeedback==WithFeedback)
	{
		if(DCM_u8PTAFBSaveValid[enPort]==True)
		{
            #ifdef Mazda
            if((DCM_au16SetPosition[enPort]<=DCM_stMotorProperty[enPort].u16Minposition+20)||\
                (DCM_au16SetPosition[enPort]>=DCM_stMotorProperty[enPort].u16Maxposition-20))
            {
             #endif
    			if(DCM_axPorts[enPort].enRequired==nActiveCW)
    			{
    				DCM_au32PTAFBSave[enPort]=DCM_au32PTAFBSave[enPort]+(uint32)DCM_stMotorProperty[enPort].u16MovingSpeed;
    				DCM_au16PtaPosFb[enPort]=(uint16)((DCM_au32PTAFBSave[enPort])>>DCM_DeltaADFactor_Config);/*calibration value*/
    			}
    			else if(DCM_axPorts[enPort].enRequired==nActiveCCW)
    			{
    				DCM_au32PTAFBSave[enPort]=DCM_au32PTAFBSave[enPort]-(uint32)DCM_stMotorProperty[enPort].u16MovingSpeed;
    				DCM_au16PtaPosFb[enPort]=(uint16)((DCM_au32PTAFBSave[enPort])>>DCM_DeltaADFactor_Config);/*calibration value*/
    			}
    			else
    			{
    				DCM_au16PtaPosFb[enPort]=(uint16)(DCM_au32PTAFBSave[enPort]>>DCM_DeltaADFactor_Config);
    			}
    			enReturnValue= nCorrectSuccess;
            #ifdef Mazda
            }
            else
            {
    			enReturnValue= nCorrectStop;
            }
            #endif
		}
		else
		{
			if(DCM_axPorts[enPort].u16ActiveTime_Tmr>=800u/*8second*/)
			{
				if(DCM_axPorts[enPort].enRequired==nActiveCW)
				{
					DCM_au32PTAFBSave[enPort]=(uint32)(DCM_stMotorProperty[enPort].u16Maxposition)<<DCM_DeltaADFactor_Config;
				}
				else if(DCM_axPorts[enPort].enRequired==nActiveCCW)
				{
					DCM_au32PTAFBSave[enPort]=(uint32)(DCM_stMotorProperty[enPort].u16Minposition)<<DCM_DeltaADFactor_Config;
				}
                else
                {
                }
				DCM_axPorts[enPort].u16ActiveTime_Tmr=0u;
				DCM_u8PTAFBSaveValid[enPort]=True;	
                #ifdef Mazda
                enReturnValue= nCorrectStop;
                #else
				enReturnValue= nCorrectSuccess;
                #endif
			}
			else
			{
                #ifdef Mazda
                enReturnValue=DCM_vCorrectDirect(enPort);/*For Mazda*/
                #else
				if(DCM_au16SetPosition[enPort]<DCM_stMotorProperty[enPort].u16Threshold)
				{
					/*put driving direction CCW*/
					enReturnValue= nCorrectCCW;
				}
				else
				{
					/*put driving direction CW*/
					enReturnValue= nCorrectCW;
				}
                #endif
                            
			}
		}
	}
	else
	{
		enReturnValue= nCorrectSuccess;
	}
    return enReturnValue;
}
#endif

#ifdef Mazda
/*******************************************************************************
*Function : uint8 DCM_vCorrectDirect(const DCM_enMotorNumber enPort)
*Description: just for Mazda
*takes: none
*return: correct fb success---0, driving CW return 2, driving CCW return 3
*/
DCM_tenCorretFBState DCM_vCorrectDirect(uint8 enPort)
{
    switch(enPort)
    {
        case DCM_nMixDrMotor:
            if(DCM_au16OatValue<400+130/*13deg*/)
            {
                DCM_CorrectDirect[DCM_nMixDrMotor]=nCorrectCCW;
            }
            else if(DCM_au16OatValue>400+170/*17deg*/)
            {
                DCM_CorrectDirect[DCM_nMixDrMotor]=nCorrectCW;
            }
            break;
        case DCM_nAirdMotor:
            if(DCM_au16OatValue<400+130/*13deg*/)
            {
                DCM_CorrectDirect[DCM_nAirdMotor]=nCorrectCW;
            }
            else if(DCM_au16OatValue>400+170/*17deg*/)
            {
                DCM_CorrectDirect[DCM_nAirdMotor]=nCorrectCCW;
            }
            break;
        default:
            break;
    }
    return DCM_CorrectDirect[enPort];
}

#endif
/*******************************************************************************
*Function : void DCM_vSetDirectionStopStatus(const DCM_enMotorNumber enPort)
*Description: set status for stop driving status
*takes: the motor number
*return:None
*/
void DCM_vSetDirectionStopStatus(uint8 enPort)
{
	/*set driving finish flag*/	
	DCM_axPorts[enPort].u16ActiveTime_Tmr=0u;
      	#ifdef ENABLEBLOCKCHECKDRIVING
	DCM_vResetBlockCheck(enPort);
      	#endif
	DCM_axPorts[enPort].enRequired=nStopped;
	#ifdef ENABLERESTDRIVING
	DCM_vResetRestDriving(enPort);
	#endif

}

/*******************************************************************************
*Function : void DCM_vSetDirectionMovingStatus(const DCM_enMotorNumber enPort)
*Description: set status for moving status
*takes: the motor number
*return:None
*/
void DCM_vSetDirectionMovingStatus(uint8 enPort)
{
		DCM_axPorts[enPort].bi2OkToSleep=False;
		#ifdef ENABLERESTDRIVING
		if(DCM_axPorts[enPort].enDirectionState==nDirectionRestCW)
		{
			DCM_vRestDrivingCalc(enPort,nActiveCW);
			if(DCM_axPorts[enPort].enDirectionPrevious!=DCM_axPorts[enPort].enDirectionState)
			{
				DCM_axPorts[enPort].u16ActiveTime_Tmr=DCM_stMotorProperty[enPort].u16DrivingActionTm-DCM_u16RestActiveTime_Config;
				#ifdef ENABLEBLOCKCHECKDRIVING
                DCM_vResetBlockCheck(enPort);
                #endif
			}
		}
		else if(DCM_axPorts[enPort].enDirectionState==nDirectionRestCCW)
		{
			DCM_vRestDrivingCalc(enPort,nActiveCCW);
			if(DCM_axPorts[enPort].enDirectionPrevious!=DCM_axPorts[enPort].enDirectionState)
			{
				DCM_axPorts[enPort].u16ActiveTime_Tmr=DCM_stMotorProperty[enPort].u16DrivingActionTm-DCM_u16RestActiveTime_Config;
				#ifdef ENABLEBLOCKCHECKDRIVING
                DCM_vResetBlockCheck(enPort);
                #endif
			}

		}
		else
		#endif
		{
			if(DCM_axPorts[enPort].enDirectionState==nDirectionCW)
			{				
				DCM_axPorts[enPort].enRequired=nActiveCW;
			}
			else if(DCM_axPorts[enPort].enDirectionState==nDirectionCCW)
			{				
				DCM_axPorts[enPort].enRequired=nActiveCCW;
			}
            else
            {
            }
			
			if(DCM_axPorts[enPort].enDirectionPrevious!=DCM_axPorts[enPort].enDirectionState)
			{
				DCM_axPorts[enPort].u16ActiveTime_Tmr=0u;
				#ifdef ENABLEBLOCKCHECKDRIVING
                DCM_vResetBlockCheck(enPort);
                #endif
			}
			#ifdef ENABLERESTDRIVING
			DCM_vResetRestDriving(enPort);
			#endif
		}
		
		/*timeout?*/
		if(DCM_axPorts[enPort].u16ActiveTime_Tmr<DCM_stMotorProperty[enPort].u16DrivingActionTm)
		{
			DCM_axPorts[enPort].u16ActiveTime_Tmr++;
		}
		else
		{
			DCM_axPorts[enPort].enRequired=nStopped;
			DCM_axPorts[enPort].bi2OkToSleep=True;
		}

	}


/*******************************************************************************
*Function : void DCM_vSetDirectionMovingStatusWithoutFB(const DCM_enMotorNumber enPort)
*Description: set status for moving status(without feed back) 
*takes: the motor number
*return:None
*/
void DCM_vSetDirectionMovingStatusWithoutFB(uint8 enPort)
{
    if(DCM_axPorts[enPort].enDirectionPrevious!=DCM_axPorts[enPort].enDirectionState)
    {
        DCM_axPorts[enPort].u16ActiveTime_Tmr=0u;
    }
    if(DCM_axPorts[enPort].u16ActiveTime_Tmr<700u/*7sec*/)
    {
    	if(DCM_axPorts[enPort].enDirectionState==nDirectionCW)
    	{				
    		DCM_axPorts[enPort].enRequired=nActiveCW;
    	}
    	else if(DCM_axPorts[enPort].enDirectionState==nDirectionCCW)
    	{				
    		DCM_axPorts[enPort].enRequired=nActiveCCW;
    	}
        else
        {
        }
    }
    else if(DCM_axPorts[enPort].u16ActiveTime_Tmr<(700u/*7sec*/+50u/*0.5sec*/))
    {
        DCM_axPorts[enPort].enRequired=nStopped;
    }
    #ifdef WithoutFBRunBackWhenStop
    else if(DCM_axPorts[enPort].u16ActiveTime_Tmr<(700u/*7sec*/+50u/*0.5sec*/+10u/*0.1sec*/))
    {
    	if(DCM_axPorts[enPort].enDirectionState==nDirectionCW)
    	{				
    		DCM_axPorts[enPort].enRequired=nActiveCCW;
    	}
    	else if(DCM_axPorts[enPort].enDirectionState==nDirectionCCW)
    	{				
    		DCM_axPorts[enPort].enRequired=nActiveCW;
    	}
        else
        {
        }
    }
    #endif
    else
    {
        DCM_axPorts[enPort].enRequired=nStopped;
    }

    if(DCM_axPorts[enPort].u16ActiveTime_Tmr<DCM_stMotorProperty[enPort].u16DrivingActionTm)
    {
        DCM_axPorts[enPort].u16ActiveTime_Tmr++;
    }

}


/*******************************************************************************
*Function : void DCM_vDirectionDriveCalc(const DCM_enMotorNumber enPort)
*Description: making calculation for driving status
*takes: the motor number
*return:None
*/
void DCM_vDirectionDriveCalc(uint8 enPort)
{
	DCM_axPorts[enPort].enPrevious=DCM_axPorts[enPort].enRequired;
	if(DCM_axPorts[enPort].enDirectionState==nDirectionStop)
	{
		DCM_vSetDirectionStopStatus(enPort);
	}
	else
	{
        if(DCM_stMotorProperty[enPort].nFeedback==WithFeedback)
        {
            DCM_vSetDirectionMovingStatus(enPort);
        }
        else
        {
            DCM_vSetDirectionMovingStatusWithoutFB(enPort);
        }
	}
	
	DCM_axPorts[enPort].enDirectionPrevious=DCM_axPorts[enPort].enDirectionState;
}

#ifdef ENABLERESTDRIVING
/*******************************************************************************
*Function : void  DCM_vRestDrivingCalc(const DCM_enMotorNumber enPort, DCM_enPortState enDirection)
*Description: making calculation for rest driving status
*takes: the motor number
*return:None
*/
void DCM_vRestDrivingCalc(uint8 enPort, DCM_tenPortState enDirection)
{
	if(DCM_u16RestDutyCounter[enPort]<DCM_RestDuty_Config)
	{
		DCM_u16RestDutyCounter[enPort]++;
		DCM_axPorts[enPort].enRequired=nStopped;
	}
	else
	{
		DCM_u16RestDutyCounter[enPort]=0u;
		DCM_axPorts[enPort].enRequired=enDirection;
	}
}
#endif
#ifdef ENABLERESTDRIVING
/*******************************************************************************
*Function : void  DCM_vResetRestDriving(const DCM_enMotorNumber enPort)
*Description: reset setting for rest driving status
*takes: the motor number
*return:None
*/
void DCM_vResetRestDriving(uint8 enPort)
{
	DCM_u16RestDutyCounter[enPort]=0u;
}
#endif
/*******************************************************************************
*Function : void  DCM_vExceptionHandler(const DCM_enMotorNumber enPort)
*Description: reset setting for rest driving status
*takes: the motor number
*return:None
*/
void  DCM_vExceptionHandler(uint8 enPort)
{
	#ifdef ENABLEBLOCKCHECKDRIVING
	if((DCM_boGetFeedbackError(enPort)==0)&&(DCM_stMotorProperty[enPort].nFeedback==WithFeedback))
	{
		DCM_vCheckBlockStatus(enPort);
	}
	else
	{
	}
	#endif
    #ifdef OpenLoadEnable
	DCM_vCheckOpenLoadStatus(enPort);
    #endif
    #ifdef OverCurrentEnable
	DCM_vCheckOverCurrentStatus(enPort);
    #endif
    #ifdef OverTempEnable
	DCM_vCheckOverTempStatus(enPort);	
    #endif
}

#ifdef ENABLEBLOCKCHECKDRIVING
/*******************************************************************************
*Function : void  DCM_vCheckBlockPreviousDetection(const DCM_enMotorNumber enPort)
*Description: function for detecting the previous block status
*takes: the motor number
*return:None
*/
void  DCM_vCheckBlockPreviousDetection(uint8 enPort)
{
	DCM_u8BlockErrCodeClr(enPort);
	DCM_axPortsBlockErr[enPort].stBlockPreDringCounter=0u;
    DCM_axPortsBlockErr[enPort].u32BlockRetryTmr=0u;
	if((DCM_axPortsBlockErr[enPort].stDetectTimer)<DCM_DetectTime_Config/*0.5second*/)
	{
		DCM_axPortsBlockErr[enPort].stDetectTimer++;
	}
	else
	{
		DCM_axPortsBlockErr[enPort].stDetectTimer=0u;
		if(abs((int16)(DCM_axPortsBlockErr[enPort].stBlockPTAFBSave)-(int16)DCM_au16PtaPosFb[enPort])\
            >(int16)DCM_stMotorProperty[enPort].u8MinADChange)
		{
			DCM_axPortsBlockErr[enPort].stBlockStatus=nBlockNotDetect;
		}
		else
		{
			DCM_axPortsBlockErr[enPort].stBlockStatus=nBlockPrevious;
		}
		DCM_axPortsBlockErr[enPort].stBlockPTAFBSave=DCM_au16PtaPosFb[enPort];
	}
}
/*******************************************************************************
*Function : void  DCM_vCheckBlockStatus(const DCM_enMotorNumber enPort)
*Description: reset setting for rest driving status
*takes: the motor number
*return:None
*/
void  DCM_vCheckBlockStatus(uint8 enPort)
{
	if(DCM_axPortsBlockErr[enPort].stBlockStatus==nBlockNotDetect)
	{
		DCM_vCheckBlockPreviousDetection(enPort);
	}
	else if(DCM_axPortsBlockErr[enPort].stBlockStatus==nBlockPrevious)
	{
		DCM_vBlockPreDrving(enPort);
	}
	else/*nBlockConfirm*/
	{
		DCM_axPortsBlockErr[enPort].stBlockPreDringCounter=0u;
		DCM_vBlockConfirm(enPort);
	}
}

/*******************************************************************************
*Function : void  DCM_vSetDrivingDirection(const DCM_enMotorNumber enPort)
*Description: setting driving direction for previous status
*takes: the motor number
*return:None
*/
void DCM_vSetDrivingDirection(uint8 enPort)
{
	if(DCM_axPorts[enPort].enDirectionState==nDirectionCW)
	{				
		DCM_axPorts[enPort].enRequired=nActiveCW;
	}
	else if(DCM_axPorts[enPort].enDirectionState==nDirectionCCW)
	{				
		DCM_axPorts[enPort].enRequired=nActiveCCW;
	}
	else if(DCM_axPorts[enPort].enDirectionState==nDirectionRestCW)
	{				
		DCM_axPorts[enPort].enRequired=nActiveCW;
	}
	else if(DCM_axPorts[enPort].enDirectionState==nDirectionRestCCW)
	{				
		DCM_axPorts[enPort].enRequired=nActiveCCW;
	}
    else
    {
    }
}

/*******************************************************************************
*Function : void  DCM_vBlockPreDrving(const DCM_enMotorNumber enPort)
*Description: reset setting for rest driving status
*takes: the motor number
*return:None
*/
void  DCM_vBlockPreDrving(uint8 enPort)
{
	DCM_axPortsBlockErr[enPort].stBlockPreTimer++;
	DCM_axPorts[enPort].u16ActiveTime_Tmr=0u;
	if(DCM_axPortsBlockErr[enPort].stBlockPreTimer>DCM_BlockPreTrime1_Config/*2.5seconds*/)
	{
		DCM_axPortsBlockErr[enPort].stBlockPreTimer=0u;		
		if(DCM_axPortsBlockErr[enPort].stBlockPreDringCounter<DCM_stMotorProperty[enPort].u8BlockPreviousDrvCount-1u/*8*/)
		{
			DCM_axPortsBlockErr[enPort].stBlockPreDringCounter++;
		}
		else
		{
			DCM_axPortsBlockErr[enPort].stBlockStatus=nBlockConfirm;
		}
	}
	else if(DCM_axPortsBlockErr[enPort].stBlockPreTimer==DCM_BlockPreTrime1_Config/*2.5seconds*/)
	{
		int16 i6ErrSavePosFB=abs((int16)(DCM_axPortsBlockErr[enPort].stBlockPTAFBSave)-(int16)(DCM_au16PtaPosFb[enPort]));
		if(i6ErrSavePosFB>(int16)DCM_stMotorProperty[enPort].u8MinADChange)
		{
			DCM_axPortsBlockErr[enPort].stBlockStatus=nBlockNotDetect;
		}
		DCM_axPortsBlockErr[enPort].stBlockPTAFBSave=DCM_au16PtaPosFb[enPort];
	}
	else if(DCM_axPortsBlockErr[enPort].stBlockPreTimer>=DCM_BlockPreTrime2_Config/*2seconds*/)
	{
		DCM_vSetDrivingDirection(enPort);			
	}
	else
	{
		DCM_axPorts[enPort].enRequired=nStopped;		
	}
}

/*******************************************************************************
*Function : void  DCM_vBlockConfirm(const DCM_enMotorNumber enPort)
*Description: reset setting for rest driving status
*takes: the motor number
*return:None
*/
void  DCM_vBlockConfirm(uint8 enPort)
{	
	DCM_u8BlockErrCodeSet(enPort);
	if(DCM_axPorts[enPort].enError==nNoError)
	{
		DCM_axPorts[enPort].enError=DCM_axPorts[enPort].enRequired;
	}
    DCM_axPorts[enPort].enRequired=nStopped;
    if(DCM_axPortsBlockErr[enPort].u32BlockRetryTmr>=(100u*(uint16)DCM_BlockRetryTmr))
    {   
        #ifdef Mazda
        DCM_vResetBlockCheck(enPort);
        #else
        DCM_axPortsBlockErr[enPort].stBlockStatus=nBlockPrevious;
        if(DCM_stMotorProperty[enPort].u8BlockPreviousDrvCount>(uint8)DCM_BlockRetryCounter)
        {            
            DCM_axPortsBlockErr[enPort].stBlockPreDringCounter=\
                DCM_stMotorProperty[enPort].u8BlockPreviousDrvCount-(uint8)DCM_BlockRetryCounter;
        }
        else
        {
           DCM_axPortsBlockErr[enPort].stBlockPreDringCounter=0u;
        }
        #endif
        
        DCM_axPortsBlockErr[enPort].u32BlockRetryTmr=0u;
    }
    else
    {
        DCM_axPortsBlockErr[enPort].u32BlockRetryTmr++;
    }
}

/*******************************************************************************
*Function : void  DCM_vResetBlockCheck(const DCM_enMotorNumber enPort)
*Description: reset setting for rest driving status
*takes: the motor number
*return:None
*/
void  DCM_vResetBlockCheck(uint8 enPort)
{
	DCM_axPorts[enPort].enError=nNoError;
	DCM_axPortsBlockErr[enPort].stBlockStatus=nBlockNotDetect;
	DCM_axPortsBlockErr[enPort].stBlockPreDringCounter=0u;
	DCM_axPortsBlockErr[enPort].stBlockPreTimer=0u;	
	DCM_axPortsBlockErr[enPort].stDetectTimer=0u;
	DCM_axPortsBlockErr[enPort].stBlockPTAFBSave=DCM_au16PtaPosFb[enPort];
	/*clr block flag for ouputing*/
}

#endif

#ifdef ENABLECORRECTPTAFB
/*******************************************************************************
* Function   :  void DCM_enSavePTAFB(const DCM_enMotorNumber enPort)
*
* Description: update the pta fb save; for FB correcting
* Takes      : Nothing
* Returns    : Nothing
*/
void DCM_enSavePTAFB(uint8 enPort)
{		

	if(DCM_axPorts[enPort].enRequired==nNoError)
	{
		/*Nothing*/
	}
	else if(DCM_axPorts[enPort].enRequired==nStopped)
	{
		if(DCM_au32PTAFBSave[enPort]==((uint32)DCM_au16PtaPosFb[enPort]<<DCM_DeltaADFactor_Config))
		{
			DCM_axPortsBlockErr[enPort].stPTAFBSaveDelay=82u;/*Delay820ms*/
			/*DCM_au16PtaPosFb[enPort]=DCM_au32PTAFBSave[enPort]/DCM_DeltaADFactor_Config;*/
		}
		else
		{
			if(DCM_axPortsBlockErr[enPort].stPTAFBSaveDelay>0u)
			{
				DCM_axPortsBlockErr[enPort].stPTAFBSaveDelay--;
				DCM_au16PtaPosFb[enPort]=(uint16)(DCM_au32PTAFBSave[enPort]>>DCM_DeltaADFactor_Config);
			}
			else
			{
                /*update the pta fb save; for FB correcting*/
				DCM_au32PTAFBSave[enPort]=(uint32)DCM_au16PtaPosFb[enPort]<<DCM_DeltaADFactor_Config;  
			}
		}
	}
	else/*motor Moving*/
	{
		uint16 u16ErrSavePosFB;
		uint16 u16PTAFBCalc=(uint16)(DCM_au32PTAFBSave[enPort]>>DCM_DeltaADFactor_Config);
        if(DCM_au16PtaRawPosFb[enPort]>u16PTAFBCalc)
        {
            u16ErrSavePosFB=DCM_au16PtaRawPosFb[enPort]-u16PTAFBCalc;
        }
        else
        {
            u16ErrSavePosFB=u16PTAFBCalc-DCM_au16PtaRawPosFb[enPort];
        }
		
		if(u16ErrSavePosFB<((uint16)(DCM_stMotorProperty[enPort].i16Stopvalue)*2u))
		{ 
            /*update the pta fb save; for FB correcting*/
			DCM_au32PTAFBSave[enPort]=(uint32)DCM_au16PtaPosFb[enPort]<<DCM_DeltaADFactor_Config; 
			DCM_axPortsBlockErr[enPort].stPTAFBSaveDelay=0u;
		}
		else
		{
			if(DCM_axPorts[enPort].enRequired==nActiveCW)
			{
				if(DCM_axPortsBlockErr[enPort].stPTAFBSaveDelay<3u/*30ms*/)
				{
					DCM_axPortsBlockErr[enPort].stPTAFBSaveDelay++;
					DCM_au32PTAFBSave[enPort]=DCM_au32PTAFBSave[enPort]+(uint32)DCM_stMotorProperty[enPort].u16MovingSpeed;
					DCM_au16PtaPosFb[enPort]=(uint16)(DCM_au32PTAFBSave[enPort]>>DCM_DeltaADFactor_Config);/*calibration value*/
				}
				else
				{
					DCM_axPortsBlockErr[enPort].stPTAFBSaveDelay=0u;
                    /*update the pta fb save; for FB correcting*/
					DCM_au32PTAFBSave[enPort]=(uint32)DCM_au16PtaPosFb[enPort]<<DCM_DeltaADFactor_Config;  
				}
			}
			else if(DCM_axPorts[enPort].enRequired==nActiveCCW)
			{
				if(DCM_axPortsBlockErr[enPort].stPTAFBSaveDelay<3u/*30ms*/)
				{
					DCM_axPortsBlockErr[enPort].stPTAFBSaveDelay++;
					DCM_au32PTAFBSave[enPort]=DCM_au32PTAFBSave[enPort]-(uint32)DCM_stMotorProperty[enPort].u16MovingSpeed;
					DCM_au16PtaPosFb[enPort]=(uint16)((DCM_au32PTAFBSave[enPort])>>DCM_DeltaADFactor_Config);/*calibration value*/
				}
				else
				{
					DCM_axPortsBlockErr[enPort].stPTAFBSaveDelay=0u;
                    /*update the pta fb save; for FB correcting*/
					DCM_au32PTAFBSave[enPort]=(uint32)DCM_au16PtaPosFb[enPort]<<DCM_DeltaADFactor_Config;  
				}
			}
            else
            {
            }
		}
	}
}
#endif

#ifdef OpenLoadEnable
/*******************************************************************************
*Function : void  DCM_vCheckOpenLoadStatus(const DCM_enMotorNumber enPort)
*Description: Check the OpenLoad Status
*takes: the motor number
*return:None        
*/
void  DCM_vCheckOpenLoadStatus(uint8 enPort)
{
	if(DCM_axPortsOpenLoadErr[enPort].stOpenLoadStatus==nOpenLoadNotDetect)
	{
		DCM_vCheckOpenLoadPreviousDetection(enPort);
	}
	else if(DCM_axPortsOpenLoadErr[enPort].stOpenLoadStatus==nOpenLoadPrevious)
	{
		DCM_vOpenLoadPreDrving(enPort);
	}
	else/*nOpenLoadConfirm*/
	{
		DCM_axPortsOpenLoadErr[enPort].u8OpenLoadPreDringCounter=0u;
		DCM_vOpenLoadConfirm(enPort);
	}
	DCM_u8OpenLoadErrCodeClr(enPort);
}
	

/*******************************************************************************
*Function : void  DCM_vCheckOpenLoadPreviousDetection(const DCM_enMotorNumber enPort)
*Description: Check the OpenLoad Status
*takes: the motor number
*return:None
*/
void  DCM_vCheckOpenLoadPreviousDetection(uint8 enPort)
{
	DCM_tenSPIRead enOpenLoadStatusRead;
	enOpenLoadStatusRead=DCM_u8SPIStatusRead(enPort,nOpenLoad);
	if(enOpenLoadStatusRead==nSPIReadError)
	{
		DCM_axPortsOpenLoadErr[enPort].stOpenLoadStatus= nOpenLoadPrevious;
	}
	else
	{
		DCM_axPortsOpenLoadErr[enPort].stOpenLoadStatus= nOpenLoadNotDetect;
	}
}

/*******************************************************************************
*Function : void  DCM_vOpenLoadPreDrving(const DCM_enMotorNumber enPort)
*Description: driving to confirm the OpenLoad
*takes: the motor number
*return:None
*/
void  DCM_vOpenLoadPreDrving(uint8 enPort)
{
	DCM_axPortsOpenLoadErr[enPort].u8OpenLoadPreTimer++;
	if(DCM_axPortsOpenLoadErr[enPort].u8OpenLoadPreTimer>DCM_PreTrime1_Config/*2.5seconds*/)
	{
		DCM_axPortsOpenLoadErr[enPort].u8OpenLoadPreTimer=0u;		
		if(DCM_axPortsOpenLoadErr[enPort].u8OpenLoadPreDringCounter<DCM_stMotorProperty[enPort].u8OpenloadPreviousDrvCount/*8*/)
		{
			DCM_axPortsOpenLoadErr[enPort].u8OpenLoadPreDringCounter++;
		}
		else
		{
			DCM_axPortsOpenLoadErr[enPort].stOpenLoadStatus=nOpenLoadConfirm;
		}
	}
	else if(DCM_axPortsOpenLoadErr[enPort].u8OpenLoadPreTimer==DCM_PreTrime1_Config/*2.5seconds*/)
	{
		DCM_vCheckOpenLoadPreviousDetection(enPort);
	}
	else if(DCM_axPortsBlockErr[enPort].stBlockPreTimer>=DCM_PreTrime2_Config/*2seconds*/)
	{
		DCM_vSetDrivingDirection(enPort);			
	}
	else
	{
		DCM_axPorts[enPort].enRequired=nStopped;		
	}
}

/*******************************************************************************
*Function : void  DCM_vOpenLoadConfirm(const DCM_enMotorNumber enPort)
*Description: set confirm status of OpenLoad
*takes: the motor number
*return:None
*/
void  DCM_vOpenLoadConfirm(uint8 enPort)
{
	DCM_axPorts[enPort].enRequired=nStopped;
	DCM_u8OpenLoadErrCodeSet(enPort);
}
/*******************************************************************************
*Function : void  DCM_u8GetOpenLoadStatus(const DCM_enMotorNumber enPort)
*Description: read SPI status
*takes: the motor number
*return:None
*/
DCM_tenSPIRead  DCM_u8GetOpenLoadStatus(uint8 enPort)
{
	DCM_tenSPIRead u8ReturnValue=nSPIReadNoError;

	if(DCM_u8GetMotorOpenLoadPin1[enPort]||DCM_u8GetMotorOpenLoadPin2[enPort])
	{
		u8ReturnValue=nSPIReadError;
	}
	else
	{
		u8ReturnValue=nSPIReadNoError;
	}
    
	return u8ReturnValue;
}

/*******************************************************************************
*Function : void  DCM_vResetOpenLoad(const DCM_tenMotorNumber enPort, uint8 u8PreDrvTimes)
*Description: reset the Openload status
*takes: the motor number
*return:None
*/
void  DCM_vResetOpenLoad(uint8 enPort, uint8 u8PreDrvTimes)
{
	DCM_axPortsOpenLoadErr[enPort].stOpenLoadStatus=nOpenLoadNotDetect;
	if(DCM_stMotorProperty[enPort].u8OpenloadPreviousDrvCount>=u8PreDrvTimes)
	{
		DCM_axPortsOpenLoadErr[enPort].u8OpenLoadPreDringCounter=\
            DCM_stMotorProperty[enPort].u8OpenloadPreviousDrvCount-u8PreDrvTimes;
	}
	else
	{
		DCM_axPortsOpenLoadErr[enPort].u8OpenLoadPreDringCounter=0;	
	}
}

#endif
#ifdef OverCurrentEnable
/******************************************************************************
*Function : void  DCM_vCheckOverCurrentStatus(const DCM_enMotorNumber enPort)
*Description: Check the OverCurrent Status
*takes: the motor number
*return:None
*/
void  DCM_vCheckOverCurrentStatus(uint8 enPort)
{
	if(DCM_axPortsOverCurrentErr[enPort].stOverCurrentStatus==nOverCurrentNotDetect)
	{
		DCM_vCheckOverCurrentPreviousDetection(enPort);
	}
	else if(DCM_axPortsOverCurrentErr[enPort].stOverCurrentStatus==nOverCurrentPrevious)
	{
		DCM_vOverCurrentPreDrving(enPort);
	}
	else/*nOverCurrentConfirm*/
	{
		DCM_axPortsOverCurrentErr[enPort].u8OverCurrentPreDringCounter=0u;
		DCM_vOverCurrentConfirm(enPort);
	}
}

/*******************************************************************************
*Function : void  DCM_vCheckOverCurrentPreviousDetection(const DCM_enMotorNumber enPort)
*Description: Check the OverCurrent Status
*takes: the motor number
*return:None
*/
void  DCM_vCheckOverCurrentPreviousDetection(uint8 enPort)
{
	uint8 u8OverCurrentStatusRead;
	u8OverCurrentStatusRead=DCM_u8SPIStatusRead(enPort,nOverCurrent);
	if(u8OverCurrentStatusRead==nSPIReadError)
	{
		DCM_axPortsOverCurrentErr[enPort].stOverCurrentStatus= nOverCurrentPrevious;
	}
	else
	{
		DCM_axPortsOverCurrentErr[enPort].stOverCurrentStatus= nOverCurrentNotDetect;
	}
	DCM_u8OverCurrentErrCodeClr(enPort);
}

/*******************************************************************************
*Function : void  DCM_vOverCurrentPreDrving(const DCM_enMotorNumber enPort)
*Description: driving to confirm the OverCurrent
*takes: the motor number
*return:None
*/
void  DCM_vOverCurrentPreDrving(uint8 enPort)
{
	DCM_axPortsOverCurrentErr[enPort].u8OverCurrentPreTimer++;
	if(DCM_axPortsOverCurrentErr[enPort].u8OverCurrentPreTimer>DCM_PreTrime1_Config/*2.5seconds*/)
	{
		DCM_axPortsOverCurrentErr[enPort].u8OverCurrentPreTimer=0u;		
		if(DCM_axPortsOverCurrentErr[enPort].u8OverCurrentPreDringCounter<\
            DCM_stMotorProperty[enPort].u8OverCurrentPreviousDrvCount/*8*/)
		{
			DCM_axPortsOverCurrentErr[enPort].u8OverCurrentPreDringCounter++;
		}
		else
		{
			DCM_axPortsOverCurrentErr[enPort].stOverCurrentStatus=nOverCurrentConfirm;
		}
	}
	else if(DCM_axPortsOverCurrentErr[enPort].u8OverCurrentPreTimer==DCM_PreTrime1_Config/*2.5seconds*/)
	{
		DCM_vCheckOverCurrentPreviousDetection(enPort);
	}
	else if(DCM_axPortsBlockErr[enPort].stBlockPreTimer>=DCM_PreTrime2_Config/*2seconds*/)
	{
		DCM_vSetDrivingDirection(enPort);			
	}
	else
	{
		DCM_axPorts[enPort].enRequired=nStopped;		
	}
}

/*******************************************************************************
*Function : void  DCM_vOverCurrentConfirm(const DCM_enMotorNumber enPort)
*Description: set confirm status of OverCurrent
*takes: the motor number
*return:None
*/
void  DCM_vOverCurrentConfirm(uint8 enPort)
{
	DCM_axPorts[enPort].enRequired=nStopped;
	DCM_u8OverCurrentErrCodeSet(enPort);
}
/*******************************************************************************
*Function : void  DCM_u8GetOverCurrentStatus(const DCM_enMotorNumber enPort)
*Description: read SPI status
*takes: the motor number
*return:None
*/
DCM_tenSPIRead  DCM_u8GetOverCurrentStatus(uint8 enPort)
{
	DCM_tenSPIRead u8ReturnValue=nSPIReadNoError;
	
	if(DCM_u8GetMotorOverCurrentPin1[enPort]||DCM_u8GetMotorOverCurrentPin2[enPort])
	{
		u8ReturnValue=nSPIReadError;
	}
	else
	{
		u8ReturnValue=nSPIReadNoError;
	}
    
	return u8ReturnValue;
}
/*******************************************************************************
*Function : void  DCM_vResetOverCurrent(const DCM_tenMotorNumber enPort, uint8 u8PreDrvTimes)
*Description: reset the OverCurrent status
*takes: the motor number
*return:None
*/
void  DCM_vResetOverCurrent(uint8 enPort, uint8 u8PreDrvTimes)
{
	DCM_axPortsOverCurrentErr[enPort].stOverCurrentStatus=nOverCurrentNotDetect;
	if(DCM_stMotorProperty[enPort].u8OverCurrentPreviousDrvCount>=u8PreDrvTimes)
	{
		DCM_axPortsOverCurrentErr[enPort].u8OverCurrentPreDringCounter=\
            DCM_stMotorProperty[enPort].u8OverCurrentPreviousDrvCount-u8PreDrvTimes;
	}
	else
	{
		DCM_axPortsOverCurrentErr[enPort].u8OverCurrentPreDringCounter=0;	
	}
}

#endif
#ifdef OverTempEnable
/*******************************************************************************
*Function : void  DCM_vCheckOverTempStatus(const DCM_enMotorNumber enPort)
*Description: Check the OverTemp Status
*takes: the motor number
*return:None
*/
void  DCM_vCheckOverTempStatus(uint8 enPort)
{
	if(DCM_axPortsOverTempErr[enPort].stOverTempStatus==nOverTempNotDetect)
	{
		DCM_vCheckOverTempPreviousDetection(enPort);
	}
	else if(DCM_axPortsOverTempErr[enPort].stOverTempStatus==nOverTempPrevious)
	{
		DCM_vOverTempPreDrving(enPort);
	}
	else/*nOverTempConfirm*/
	{
		DCM_axPortsOverTempErr[enPort].u8OverTempPreDringCounter=0u;
		DCM_vOverTempConfirm(enPort);
	}
}

/*******************************************************************************
*Function : void  DCM_vCheckOverTempPreviousDetection(const DCM_enMotorNumber enPort)
*Description: Check the OverTemp Status
*takes: the motor number
*return:None
*/
void  DCM_vCheckOverTempPreviousDetection(uint8 enPort)
{
	uint8 u8OverTempStatusRead;
	u8OverTempStatusRead=DCM_u8SPIStatusRead(enPort,nOverTemp);
	if(u8OverTempStatusRead==nSPIReadError)
	{
		DCM_axPortsOverTempErr[enPort].stOverTempStatus= nOverTempPrevious;
	}
	else
	{
		DCM_axPortsOverTempErr[enPort].stOverTempStatus= nOverTempNotDetect;
	}
	DCM_u8OverTempErrCodeClr(enPort);
}

/*******************************************************************************
*Function : void  DCM_vOverTempPreDrving(const DCM_enMotorNumber enPort)
*Description: driving to confirm the OverTemp
*takes: the motor number
*return:None
*/
void  DCM_vOverTempPreDrving(uint8 enPort)
{
	DCM_axPortsOverTempErr[enPort].u8OverTempPreTimer++;
	if(DCM_axPortsOverTempErr[enPort].u8OverTempPreTimer>DCM_PreTrime1_Config/*2.5seconds*/)
	{
		DCM_axPortsOverTempErr[enPort].u8OverTempPreTimer=0u;		
		if(DCM_axPortsOverTempErr[enPort].u8OverTempPreDringCounter<\
            DCM_stMotorProperty[enPort].u8OverTempPreviousDrvCount/*2*/)
		{
			DCM_axPortsOverTempErr[enPort].u8OverTempPreDringCounter++;
		}
		else
		{
			DCM_axPortsOverTempErr[enPort].stOverTempStatus=nOverTempConfirm;
		}
	}
	else if(DCM_axPortsOverTempErr[enPort].u8OverTempPreTimer==DCM_PreTrime1_Config/*2.5seconds*/)
	{
		DCM_vCheckOverTempPreviousDetection(enPort);
	}
	else if(DCM_axPortsOverTempErr[enPort].u8OverTempPreTimer>=DCM_PreTrime2_Config/*2seconds*/)
	{
		DCM_vSetDrivingDirection(enPort);			
	}
	else
	{
		DCM_axPorts[enPort].enRequired=nStopped;		
	}
}

/*******************************************************************************
*Function : void  DCM_vOverTempConfirm(const DCM_enMotorNumber enPort)
*Description: set confirm status of OverTemp
*takes: the motor number
*return:None
*/
void  DCM_vOverTempConfirm(uint8 enPort)
{
	DCM_axPorts[enPort].enRequired=nStopped;
	DCM_u8OverTempErrCodeSet(enPort);
}
/*******************************************************************************
*Function : void  DCM_u8GetOverTempStatus(const DCM_enMotorNumber enPort)
*Description: read SPI status
*takes: the motor number
*return:None
*/
DCM_tenSPIRead  DCM_u8GetOverTempStatus(uint8 enPort)
{
	DCM_tenSPIRead u8ReturnValue=nSPIReadNoError;

	if(DCM_u8GetOverTempFlag())
	{
		u8ReturnValue=nSPIReadError;
	}
	else
	{
		u8ReturnValue=nSPIReadNoError;
	}
	
	return u8ReturnValue;
}

/*******************************************************************************
*Function : void  DCM_vResetOverTemp(const DCM_tenMotorNumber enPort, uint8 u8PreDrvTimes)
*Description: reset the OverTemp status
*takes: the motor number
*return:None
*/
void  DCM_vResetOverTemp(uint8 enPort, uint8 u8PreDrvTimes)
{
	DCM_axPortsOverTempErr[enPort].stOverTempStatus=nOverTempNotDetect;
	if(DCM_stMotorProperty[enPort].u8OverTempPreviousDrvCount>=u8PreDrvTimes)
	{
		DCM_axPortsOverTempErr[enPort].u8OverTempPreDringCounter=\
            DCM_stMotorProperty[enPort].u8OverTempPreviousDrvCount-u8PreDrvTimes;
	}
	else
	{
		DCM_axPortsOverTempErr[enPort].u8OverTempPreDringCounter=0;	
	}
}

#endif
/*******************************************************************************
*Function : void  DCM_u8SPIStatusRead(const DCM_enMotorNumber enPort, DCM_tenSPIErrType enErrType)
*Description: read SPI status
*takes: the motor number
*return:None
*/
DCM_tenSPIRead  DCM_u8SPIStatusRead(uint8 enPort, DCM_tenSPIErrType enErrType)
{
	DCM_tenSPIRead u8ReturnValue=nSPIReadNoError;
    #ifdef OpenLoadEnable
	if(enErrType==nOpenLoad)
	{
		u8ReturnValue=DCM_u8GetOpenLoadStatus(enPort);
	}
    #endif
    #ifdef OverCurrentEnable
	if(enErrType==nOverCurrent)
	{
		u8ReturnValue=DCM_u8GetOverCurrentStatus(enPort);
	}
    #endif
    #ifdef OverTempEnable
	if(enErrType==nOverTemp)
	{
		u8ReturnValue=DCM_u8GetOverTempStatus(enPort);
	}
    #endif
	return u8ReturnValue;
}

/*******************************************************************************
*Function : DCM_tenValueSts DCM_u8TargetPositionExport(uint8 *value)
*Description : export the target position
*takes :  Motor index
*return: 0:invalid  1:valid 2:default   3:last valid
*/
DCM_tenValueSts DCM_enGetU16TargetPositionExport(uint8 index,uint16 *value)
{
    DCM_tenValueSts enReturn=DCM_nValid;
    if(index<(uint8)MotorNum)
    {
        *value=DCM_au16SetPosition[index];
        if(DCM_au16SetPosition[index]==0xFFFFu)
        {
            enReturn=DCM_nInvalid;
        }
    }
    else
    {
        enReturn=DCM_nInvalid;
    }
    return enReturn;

}
/*******************************************************************************
*Function : DCM_tenValueSts DCM_u8CurrentPositionExport(uint8 *value)
*Description : export the current AD value
*takes : Motor index
*return: 0:invalid  1:valid 2:default   3:last valid
*/
DCM_tenValueSts DCM_enGetU16CurrentPositionExport(uint8 index,uint16 *value)
{
    DCM_tenValueSts enReturn=DCM_nValid;
    if(index<(uint8)MotorNum)
    {
        *value=DCM_au16PtaPosFb[index];
    }
    else
    {
        enReturn=DCM_nInvalid;
    }
    return enReturn;
}
/*******************************************************************************
*Function : DCM_tenValueSts DCM_u8CurrentRawPositionExport(uint8 *value)
*Description : export the Raw AD value
*takes : Motor index
*return: 0:invalid  1:valid 2:default   3:last valid
*/
DCM_tenValueSts DCM_enGetU16CurrentRawPositionExport(uint8 index,uint16 *value)
{
    DCM_tenValueSts enReturn=DCM_nValid;
    if(index<(uint8)MotorNum)
    {
        *value=DCM_au16PtaRawPosFb[index];
    }
    else
    {
        enReturn=DCM_nInvalid;
    }
    return enReturn;
}
/*******************************************************************************
*Function : DCM_tenValueSts DCM_enGetEnMotorDiretionExport(uint8 index,DCM_tenPortState *value)
*Description : Export the motor diretion
*takes : Motor index
*return: 0:invalid  1:valid 2:default   3:last valid
*/
DCM_tenValueSts DCM_enGetEnMotorDiretionExport(uint8 index,DCM_tenPortState *value)
{
    DCM_tenValueSts enReturn=DCM_nValid;
    if(index<(uint8)MotorNum)
    {
        *value=DCM_axPorts[index].enRequired;
    }
    else
    {
        enReturn=DCM_nInvalid;
    }
    return enReturn;
}
/*******************************************************************************
*Function : DCM_tenValueSts DCM_enGetU8ErrorCodeExport(uint8 *value)
*Description : export Error code.
*takes : Motor index
*return: 0:invalid  1:valid 2:default   3:last valid
*/
DCM_tenValueSts DCM_enGetU8ErrorCodeExport(uint8 index,uint8 *value)
{
    DCM_tenValueSts enReturn=DCM_nValid;
    if(index<(uint8)MotorNum)
    {
        *value=DCM_au8ErrorCode[index];
    }
    else
    {
        enReturn=DCM_nInvalid;
    }
    return enReturn;
}
/*******************************************************************************
*Function : DCM_tenValueSts DCM_enGetStMotorStatusExport(uint8 index,DCM_tstState *value)
*Description : export motor struct
*takes : Motor index
*return: 0:invalid  1:valid 2:default   3:last valid
*/
DCM_tenValueSts DCM_enGetStMotorStatusExport(uint8 index,DCM_tstState *value)
{
    DCM_tenValueSts enReturn=DCM_nValid;
    if(index<(uint8)MotorNum)
    {
        memcpy(value, &DCM_axPorts[index], sizeof(DCM_tstState));
    }
    else
    {
        enReturn=DCM_nInvalid;
    }
    return enReturn;
}
/*******************************************************************************
*Function : DCM_tenValueSts DCM_enGetStMotorBlockStatusExport(uint8 index,DCM_tstBlockErrStatus *value)
*Description : export motor block struct
*takes : Motor index
*return: 0:invalid  1:valid 2:default   3:last valid
*/
DCM_tenValueSts DCM_enGetStMotorBlockStatusExport(uint8 index,DCM_tstBlockErrStatus *value)
{
    DCM_tenValueSts enReturn=DCM_nValid;
    if(index<(uint8)MotorNum)
    {
        memcpy(value, &DCM_axPortsBlockErr[index], sizeof(DCM_tstBlockErrStatus));
    }
    else
    {
        enReturn=DCM_nInvalid;
    }
    return enReturn;
}

/*******************************************************************************
*Function : void  DCM_vSetMotorVibrateStatus_PWM(void)
*Description: set status for moving status
*takes: the motor number
*return:None
*/
void  DCM_vSetMotorVibrateStatus_PWM(void)
{
	DCM_u8VibrateCycles++;
	if(DCM_u8VibrateCycles>DCM_MotorVibrateCycle)
	{
		DCM_u8VibrateCycles=0;
		DCM_u8VibrationFlag=False;
		MCU_u16PWGASetDuty(MCU_mPWGA10, 0);
		MCU_u16PinWrite(MCU_mPinID_P10_4, 0);
		
	}
	else 
	{
		MCU_u16PWGASetDuty(MCU_mPWGA10, DCM_motor_duty);
	}

}

/*******************************************************************************
*Function : void DCM_vSetMotorVibrateStatus_Timer(void)
*Description: set status for moving status
*takes: the motor number
*return:None
*/
void DCM_vSetMotorVibrateStatus_Timer(void)
{

		/*****do nothing***/
	DCM_u8VibrateTimes++;
	if(DCM_u8VibrateTimes>DCM_MotorVibrateTimer)
	{
		DCM_u8VibrateTimes=0;
		DCM_u8VibrationFlag=False;
		MCU_u16PWGASetDuty(MCU_mPWGA10, 0);
		MCU_u16PinWrite(MCU_mPinID_P10_4, 0);
		
		
	}
	else 
	{
		MCU_u16PWGASetDuty(MCU_mPWGA10, DCM_motor_duty);
	}

}


/*****************************************************************************
* EOF: DCM.c
*****************************************************************************/


