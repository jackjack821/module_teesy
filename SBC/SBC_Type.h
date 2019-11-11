/**************************** .FILE_HEADER_BEGIN *****************************
  .TITLE:    driver for SBC serial
*-----------------------------------------------------------------------------
  .FILE:EEP_Drv.h
  .AUTHOR:Zhushengxin
*-----------------------------------------------------------------------------

 Date        Author                       Change
 -----------------------------------------------------------------------------
2018.03.27 Zhushengxin		   :create this module

*****************************************************************************/

#include "general.h"

#ifndef SBC_Type_H
#define SBC_Type_H

/********************Control Registers Addr**************/
#define   M_S_CTRLAddr  0x01;
#define   HW_CTRLAddr   0x02;
#define   WD_CTRLAddr   0x03;
#define   BUS_CTRL_1Addr   0x04;
#define   BUS_CTRL_2Addr   0x05;
#define   WK_CTRL_1Addr   0x06;  
#define   WK_CTRL_2Addr   0x07;
#define   WK_PUPD_CTRLAddr  0x08;
#define   WK_FLT_CTRLAddr  0x09;
#define   TIMER1_CTRLAddr   0x0C;
#define   TIMER2_CTRLAddr   0x0D;   
#define   SW_SD_CTRLAddr   0x10;   
#define   HS_CTRL_1Addr   0x14;
#define   HS_CTRL_2Addr   0x15;
#define   GPIO_CTRLAddr  0x17;
#define   PWM1_CTRLAddr  0x18;
#define   PWM2_CTRLAddr  0x19;   
#define   PWM_FREQ_CTRLAddr  0x1C;    
#define   SYS_STAT_CTRLAddr   0x1E;
/*******************************************************/

/**********************Status Registers Addr***************/
#define  SUP_STAT_2Addr   0x40
#define  SUP_STAT_1Addr   0x41
#define  THERM_STATAddr   0x42
#define  DEV_STATAddr 	  0x43
#define  BUS_STAT_1Addr    0x44
#define  BUS_STAT_2Addr    0x45
#define  WK_STAT_1Addr    0x46
#define  WK_STAT_2Addr    0x47
#define  WK_LVL_STATAddr    0x48
#define  HS_OC_OT_STATAddr    0x54
#define  HS_OL_STATAddr    0x55
#define  FAM_PROD_STATAddr    0x7e

/******************************************************/
typedef enum
{
    SBCdrv_Normal_Mode, 
    SBCdrv_Sleep_Mode, 
    SBCdrv_Stop_Mode, 	
    SBCdrv_Reset		
} SBCdrv_tenModeControlType;

typedef enum
{
    Vcc3Off, 
    Vcc3Enable, 	
} SBCdrv_tenVcc3ModeControlType;

typedef enum
{
    Vcc2Off, 
    Vcc2Normal, 
    Vcc2NormalAndStop, 	
    Vcc2AlwaysOn, 	
} SBCdrv_tenVcc2ModeControlType;

typedef enum
{
    Vcc1OvNoResrt, 
    Vcc1OvResrtdependCfg, 	
} SBCdrv_tenVCC1_OV_RSTType;


/***********************************
VRT1,f 4.5 4.6 4.75 V VCC1 falling
VRT1,r 4.6 4.7 4.85 V VCC1 rising

VRT2,f 3.75 3.9 4.05 V VCC1 falling 
VRT2,r 3.85 4.0 4.15 V VCC1 rising 

VRT3,f 3.15 3.3 3.45 V VCC1 falling
VRT3,r 3.25 3.4 3.55 V VCC1 rising

VRT4,f 2.4 2.65 2.8 V VCC1 falling
VRT4,r 2.5 2.75 2.9 V VCC1 rising
***********************************/
typedef enum
{
	Vrt1Selected, 
	Vrt2Selected,
	Vrt3Selected,
	Vrt4Selected,
	
} SBCdrv_tenVCC1_RTType;

typedef enum
{
    SameWithVCC1, 
    DependingOnVCC1Derivative, 	
} SBCdrv_tenVCC3_V_CFGType;

typedef enum
{
    RoTrigeer, 
    RoNoTrigeer, 	
} SBCdrv_tenSoftResetRoType;

typedef enum
{
    ActivatedByDefinedFailures, 
    ActivatedBySoftware, 	
} SBCdrv_tenFailureOutputActivation_CFGType;

typedef enum
{
    SBCdrv_tenVCC3_VS_UV_OFF_CFGType_Disabled, 
    SBCdrv_tenVCC3_VS_UV_OFF_CFGType_Stay_Enabled, 	
} SBCdrv_tenVCC3_VS_UV_OFF_CFGType;

typedef enum
{
    SBCdrv_tenVCC3_LS_CFGType_StandAlone, 
    SBCdrv_tenVCC3_LS_CFGType_ShareingOperationWithVCC1, 	
} SBCdrv_tenVCC3_LS_CFGType;

typedef enum
{
    SBCdrv_tenVCC3_LS_STP_ON_CFGType_Disable, 
    SBCdrv_tenVCC3_LS_STP_ON_CFGType_Enable, 	
} SBCdrv_tenVCC3_LS_STP_ON_CFGType;

typedef enum
{
    SBCdrv_tenHW_CTRL_CFGModeType_ReserAfter2WatchDogFail, 
    SBCdrv_tenHW_CTRL_CFGModeType_ReserAfter1WatchDogFail, 
} SBCdrv_tenHW_CTRL_CFGModeType;

typedef enum
{
    SBCdrv_tenCHECKSUM_Type_NoCheckSum, 
    SBCdrv_tenCHECKSUM_Type_CheckSum,
} SBCdrv_tenCHECKSUM_Type;

typedef enum
{
    ActiveInStopMode, 
    DeactivatedInStopMod,
} SBCdrv_tenWD_STM_EN_0Type;







typedef enum
{
    TimeoutMode,
    WindowMode,
} SBCdrv_tenWatchdogType ;


typedef enum
{
	NotstartAfterclWake,
	LongOpenwindowWake,
} SBCdrv_tenWatchdogWK_BUSType ;

typedef enum
{
	TimerPeriod_10ms,
	TimerPeriod_20ms,
	TimerPeriod_50ms,	
	TimerPeriod_100ms,		
	TimerPeriod_200ms,	
	TimerPeriod_500ms,	
	TimerPeriod_1000ms,	
	reserved,				
} SBCdrv_tenWatchdogTimerPeriodType ;

typedef enum
{
	SBCdrv_tenLINxFlashProgrammingModeType_Active,
	SBCdrv_tenLINxFlashProgrammingModeType_Deactivation,
		
} SBCdrv_tenLINxFlashProgrammingModeType ;

typedef enum
{
	SBCdrv_tenLINxLSMType_Normal,
	SBCdrv_tenLINxLSMType_LowSlopeMode,	
} SBCdrv_tenLINxLSMType ;

typedef enum
{
	SBCdrv_tenLINTXDTimeOutType_Disable,
	SBCdrv_tenLINTXDTimeOutType_Enable,	
} SBCdrv_tenLINTXDTimeOutType ;

typedef enum
{
	SBCdrv_tenLINModuleModeType_OFF,
	SBCdrv_tenLINModuleModeType_WakeCapable,	
	SBCdrv_tenLINModuleModeType_ReceiveOnly,
	SBCdrv_tenLINModuleModeType_Normal,
} SBCdrv_tenLINModuleModeType ;

typedef enum
{
	SBCdrv_tenHSCANModuleModeType_OFF,
	SBCdrv_tenHSCANModuleModeType_WakeCapable,	
	SBCdrv_tenHSCANModuleModeType_ReceiveOnly,
	SBCdrv_tenHSCANModuleModeType_Normal,
} SBCdrv_tenHSCANModuleModeType ;

typedef enum
{
	SBCdrv_tenPeakThresholdModeType_Low,
	SBCdrv_tenPeakThresholdModeType_Higher,
} SBCdrv_tenPeakThresholdModeType ;

typedef enum
{
	SBCdrv_tenTmer2WakeSourceEnModeType_Disable,
	SBCdrv_tenTmer2WakeSourceEnModeType_Enable,
} SBCdrv_tenTmer2WakeSourceEnModeType ;

typedef enum
{
	SBCdrv_tenTmer1WakeSourceEnModeType_Disable,
	SBCdrv_tenTmer1WakeSourceEnModeType_Enable,
} SBCdrv_tenTmer1WakeSourceEnModeType ;
typedef enum
{
	SBCdrv_tenWatchdogSTM_EN1ModeType_Active,
	SBCdrv_tenWatchdogSTM_EN1ModeType_Deactive,
} SBCdrv_tenWatchdogSTM_EN1ModeType ;
typedef enum
{
	SBCdrv_tenGlobalInterruptConfigurationModeType_INT,
	SBCdrv_tenGlobalInterruptConfigurationModeType_AllStatus,
} SBCdrv_tenGlobalInterruptConfigurationModeType ;
typedef enum
{
	SBCdrv_tenWK_MEASModeType_EnabledWK_Function,
	SBCdrv_tenWK_MEASModeType_WK1_WK2_Disable,
} SBCdrv_tenWK_MEASModeType ;
typedef enum
{
	SBCdrv_tenWK3_ENModeType_Disabled,
	SBCdrv_tenWK3_ENModeType_Enabled,
} SBCdrv_tenWK3_ENModeType ;
typedef enum
{
	SBCdrv_tenWK2_ENModeType_Disabled,
	SBCdrv_tenWK2_ENModeType_Enabled,
} SBCdrv_tenWK2_ENModeType ;
typedef enum
{
	SBCdrv_tenWK1_ENModeType_Disabled,
	SBCdrv_tenWK1_ENModeType_Enabled,
} SBCdrv_tenWK1_ENModeType ;
typedef enum
{
	SBCdrv_tenWK3_PUPDModeType_NO,
	SBCdrv_tenWK3_PUPDModeType_PullDown,
	SBCdrv_tenWK3_PUPDModeType_Up,
	SBCdrv_tenWK3_PUPDModeType_Automatic,
} SBCdrv_tenWK3_PUPDModeType ;
typedef enum
{
	SBCdrv_tenWK2_PUPDModeType_NO,
	SBCdrv_tenWK2_PUPDModeType_PullDown,
	SBCdrv_tenWK2_PUPDModeType_Up,
	SBCdrv_tenWK2_PUPDModeType_Automatic,
} SBCdrv_tenWK2_PUPDModeType ;
typedef enum
{
	SBCdrv_tenWK1_PUPDModeType_NO,
	SBCdrv_tenWK1_PUPDModeType_PullDown,
	SBCdrv_tenWK1_PUPDModeType_Up,
	SBCdrv_tenWK1_PUPDModeType_Automatic,
} SBCdrv_tenWK1_PUPDModeType ;
typedef enum
{
	SBCdrv_tenWK_FLTModeType_16us,
	SBCdrv_tenWK_FLTModeType_64us,
	SBCdrv_tenWK_FLTModeType_SecondOn16us,
	SBCdrv_tenWK_FLTModeType_SecondOn64us,
} SBCdrv_tenWK_FLTModeType ;
typedef enum
{
	SBCdrv_tenTIMER1_ONModeType_OFF_Low,
	SBCdrv_tenTIMER1_ONModeType_100usOn,
	SBCdrv_tenTIMER1_ONModeType_300usOn,
	SBCdrv_tenTIMER1_ONModeType_1msOn,
	SBCdrv_tenTIMER1_ONModeType_10msOn,
	SBCdrv_tenTIMER1_ONModeType_20msOn,
	SBCdrv_tenTIMER1_ONModeType_OFF_High,
	SBCdrv_tenTIMER_ONModeType_reserved,
} SBCdrv_tenTIMER_ONModeType ;
typedef enum
{
	SBCdrv_tenTIMER1_PERModeType_10ms,
	SBCdrv_tenTIMER1_PERModeType_20ms,
	SBCdrv_tenTIMER1_PERModeType_50ms,
	SBCdrv_tenTIMER1_PERModeType_100ms,
	SBCdrv_tenTIMER1_PERModeType_200ms,
	SBCdrv_tenTIMER1_PERModeType_1s,
	SBCdrv_tenTIMER1_PERModeType_2s,
	SBCdrv_tenTIMER1_PERModeType_reserved,
} SBCdrv_tenTIMER_PERModeType ;
typedef enum
{
	SBCdrv_tenHS_OV_UV_SD_ENModeType_Enable,
	SBCdrv_tenHS_OV_UV_SD_ENModeType_Disable,
}SBCdrv_tenHS_OV_UV_SD_ENModeType;

typedef enum
{
	SBCdrv_tenHS_OV_UV_RECModeType_Disable,
	SBCdrv_tenHS_OV_UV_RECModeType_Enable,
}SBCdrv_tenHS_OV_UV_RECModeType;

typedef enum
{
	SBCdrv_tenHS_ConfigurationModeType_OFF,
	SBCdrv_tenHS_ConfigurationModeType_ON,
	SBCdrv_tenHS_ConfigurationModeType_CtlByTimer1,
	SBCdrv_tenHS_ConfigurationModeType_CtlByTimer2,
	SBCdrv_tenHS_ConfigurationModeType_CtlByPWM1,
	SBCdrv_tenHS_ConfigurationModeType_CtlByPWM2,
	SBCdrv_tenHS_ConfigurationModeType_Reserved,
}SBCdrv_tenHS_ConfigurationModeType;
typedef struct
{
	uint8 RegistersAddr;
	uint8 RegistersData;	
}RegDataAddr;

typedef struct
{
	 RegDataAddr  M_S_CTRL;
	 RegDataAddr  HW_CTRL;
	 RegDataAddr  WD_CTRL;
	 RegDataAddr  BUS_CTRL_1;
	 RegDataAddr  BUS_CTRL_2;
	 RegDataAddr  WK_CTRL_1;  
	 RegDataAddr  WK_CTRL_2;
	 RegDataAddr  WK_PUPD_CTRL;
	 RegDataAddr  WK_FLT_CTRL;
	 RegDataAddr  TIMER1_CTRL;
	 RegDataAddr  TIMER2_CTRL;   
	 RegDataAddr  SW_SD_CTRL;   
	 RegDataAddr  HS_CTRL_1;
	 RegDataAddr  HS_CTRL_2;
	 RegDataAddr  GPIO_CTRL;
	 RegDataAddr  PWM1_CTRL;
	 RegDataAddr  PWM2_CTRL;   
	 RegDataAddr  PWM_FREQ_CTRL;    
	 RegDataAddr  SYS_STAT_CTRL;
}SBCdrv_tstControlRegisters;
typedef struct
{
	RegDataAddr  SUP_STAT_2;
	RegDataAddr  SUP_STAT_1;
	RegDataAddr  THERM_STAT;
	RegDataAddr  DEV_STAT;
	RegDataAddr  BUS_STAT_1;
	RegDataAddr  BUS_STAT_2;  
	RegDataAddr WK_STAT_1;
	RegDataAddr  WK_STAT_2;
	RegDataAddr  WK_LVL_STAT;
	RegDataAddr  HS_OC_OT_STAT;
	RegDataAddr  HS_OL_STAT;   
	RegDataAddr  FAM_PROD_STAT;   
}SBCdrv_tstStatusRegisters;

typedef enum
{
	 SBCdrv_nu8M_S_CTRL,
	 SBCdrv_nu8HW_CTRL,
	 SBCdrv_nu8WD_CTRL,
	 SBCdrv_nu8BUS_CTRL_1,
	 SBCdrv_nu8BUS_CTRL_2,
	 SBCdrv_nu8WK_CTRL_1,  
	 SBCdrv_nu8WK_CTRL_2,
	 SBCdrv_nu8WK_PUPD_CTRL,
	 SBCdrv_nu8WK_FLT_CTRL,
	 SBCdrv_nu8TIMER1_CTRL,
	 SBCdrv_nu8TIMER2_CTRL,  
	 SBCdrv_nu8SW_SD_CTRL,   
	 SBCdrv_nu8HS_CTRL_1,
	 SBCdrv_nu8HS_CTRL_2,
	 SBCdrv_nu8GPIO_CTRL,
	 SBCdrv_nu8PWM1_CTRL,
	 SBCdrv_nu8PWM2_CTRL,  
	 SBCdrv_nu8PWM_FREQ_CTRL,  
	 SBCdrv_nu8SYS_STAT_CTRL
}SBCdrv_enumControlRegisters;

typedef enum
{
	SBCdrv_nu8SUP_STAT_2,
	SBCdrv_nu8SUP_STAT_1,
	SBCdrv_nu8THERM_STAT,
	SBCdrv_nu8DEV_STAT,
	SBCdrv_nu8BUS_STAT_1,
	SBCdrv_nu8BUS_STAT_2, 
	SBCdrv_nu8WK_STAT_1,
	SBCdrv_nu8WK_STAT_2,
	SBCdrv_nu8WK_LVL_STAT,
	SBCdrv_nu8HS_OC_OT_STAT,
	SBCdrv_nu8HS_OL_STAT,
	SBCdrv_nu8FAM_PROD_STAT
}SBCdrv_enumStatusRegisters;


#endif
