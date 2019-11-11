/**************************** .FILE_HEADER_BEGIN *****************************
  .TITLE: TLE9262  Driver used on 32bit MCU RH850L by SPI 
*-----------------------------------------------------------------------------
  .FILE:TLE9262.c   
*-----------------------------------------------------------------------------

 Date        Author                       Change
 -----------------------------------------------------------------------------
2018.03.27  ZhuShengxin		   :create this module
2018.04.13  ZhengJianshi		   :update 
*****************************************************************************/

#include <Rte_Internal.h>
#include "S_SPI.h"
#include "general.h"
#include "SBC.h"
#include "SBC_Type.h"
#include "SBC_Private.h"
#include "SBC_IF.h"


static SBCdrv_tstControlRegisters SBCdrv_stControlRegisters;
static SBCdrv_tstStatusRegisters  SBCdrv_stStatusRegisters;

//static SBCdrv_tstControlRegisters SBCdrv_stControlRegistersOutData;
//static SBCdrv_tstControlRegisters SBCdrv_stControlRegistersRecData;
static uint8	CtrlRe1[2];
uint8 u8Rec[2];
static uint16 SBC_u16Array[SBC_nu16Max];
void TLE9262Drv_W_Ctl_Regs(void * OutDataHead,void * RecDataHead)		
{
	uint8 * ptemp=NULL;
	ptemp = (uint8 *)OutDataHead;
	*ptemp = (*ptemp)|(0x01<<7);
	SPI_u16SlaveSelect_CH1(0,0);
	SPI_u16TransferData_CH1(OutDataHead,RecDataHead,2);
	SPI_u16SlaveSelect_CH1(0,1);
	S_SPI_CH1_CSNDelay();
}
void TLE9262Drv_R_Ctl_Regs(void * OutDataHead,void * RecDataHead)		
{
	uint8 * ptemp=NULL;
	ptemp = (uint8 *)OutDataHead;
	*ptemp = (*ptemp)&(~(0x01<<7));
	SPI_u16SlaveSelect_CH1(0,0);
	SPI_u16TransferData_CH1(OutDataHead,RecDataHead,2);
	SPI_u16SlaveSelect_CH1(0,1);
	S_SPI_CH1_CSNDelay();
}
void TLE9262Drv_Clc_Sta_Regs(void * OutDataHead,void * RecDataHead)
{
	TLE9262Drv_W_Ctl_Regs(OutDataHead,RecDataHead);
}
void TLE9262Drv_R_Sta_Regs(void * OutDataHead,void * RecDataHead)
{
	TLE9262Drv_R_Ctl_Regs(OutDataHead,RecDataHead);
}
void  TLE9262Drv_vAddrInit(void)
{
	SBCdrv_stControlRegisters.M_S_CTRL.RegistersAddr = M_S_CTRLAddr;
	SBCdrv_stControlRegisters.HW_CTRL.RegistersAddr =HW_CTRLAddr;
	SBCdrv_stControlRegisters.WD_CTRL.RegistersAddr =WD_CTRLAddr;
	SBCdrv_stControlRegisters.BUS_CTRL_1.RegistersAddr =BUS_CTRL_1Addr;
	SBCdrv_stControlRegisters.BUS_CTRL_2.RegistersAddr =BUS_CTRL_2Addr;
	SBCdrv_stControlRegisters.WK_CTRL_1.RegistersAddr =WK_CTRL_1Addr;  
	SBCdrv_stControlRegisters.WK_CTRL_2.RegistersAddr =WK_CTRL_2Addr;
	SBCdrv_stControlRegisters.WK_PUPD_CTRL.RegistersAddr =WK_PUPD_CTRLAddr;
	SBCdrv_stControlRegisters.WK_FLT_CTRL.RegistersAddr =WK_FLT_CTRLAddr;
	SBCdrv_stControlRegisters.TIMER1_CTRL.RegistersAddr =TIMER1_CTRLAddr;
	SBCdrv_stControlRegisters.TIMER2_CTRL.RegistersAddr =TIMER2_CTRLAddr;   
	SBCdrv_stControlRegisters.SW_SD_CTRL.RegistersAddr =SW_SD_CTRLAddr;   
	SBCdrv_stControlRegisters.HS_CTRL_1.RegistersAddr =HS_CTRL_1Addr;
	SBCdrv_stControlRegisters.HS_CTRL_2.RegistersAddr =HS_CTRL_2Addr;
	SBCdrv_stControlRegisters.GPIO_CTRL.RegistersAddr =GPIO_CTRLAddr;
	SBCdrv_stControlRegisters.PWM1_CTRL.RegistersAddr =PWM1_CTRLAddr;
	SBCdrv_stControlRegisters.PWM2_CTRL.RegistersAddr =PWM2_CTRLAddr;   
	SBCdrv_stControlRegisters.PWM_FREQ_CTRL.RegistersAddr =PWM_FREQ_CTRLAddr;    
	SBCdrv_stControlRegisters.SYS_STAT_CTRL.RegistersAddr =SYS_STAT_CTRLAddr;
	
	SBCdrv_stStatusRegisters.BUS_STAT_1.RegistersAddr = BUS_STAT_1Addr;
	SBCdrv_stStatusRegisters.BUS_STAT_2.RegistersAddr = BUS_STAT_2Addr;
	SBCdrv_stStatusRegisters.DEV_STAT.RegistersAddr = DEV_STATAddr;
	SBCdrv_stStatusRegisters.FAM_PROD_STAT.RegistersAddr = FAM_PROD_STATAddr;
	SBCdrv_stStatusRegisters.HS_OC_OT_STAT.RegistersAddr = HS_OC_OT_STATAddr;
	SBCdrv_stStatusRegisters.HS_OL_STAT.RegistersAddr = HS_OL_STATAddr;
	SBCdrv_stStatusRegisters.SUP_STAT_1.RegistersAddr = SUP_STAT_1Addr;
	SBCdrv_stStatusRegisters.SUP_STAT_2.RegistersAddr = SUP_STAT_2Addr;
	SBCdrv_stStatusRegisters.THERM_STAT.RegistersAddr = THERM_STATAddr;
	SBCdrv_stStatusRegisters.WK_LVL_STAT.RegistersAddr = WK_LVL_STATAddr;
	SBCdrv_stStatusRegisters.WK_STAT_1.RegistersAddr = WK_STAT_1Addr;
	SBCdrv_stStatusRegisters.WK_STAT_2.RegistersAddr = WK_STAT_2Addr;
}
/********************************************************************************/

/*******************M_S_CTRL*****************************************************/

/******************************************************************************/
/*
*Function Name :  TLE9262Drv_M_S_CTRL_ModeControl(SBCdrv_tenModeControlType  mode);

* Description   :	SBC Mode Control
				00B , SBC Normal Mode
				01B , SBC Sleep Mode
				10B , SBC Stop Mode
				11B , SBC Reset: Soft Reset is executed
* Date          :	2018.03.28
*/
/******************************************************************************/
void  TLE9262Drv_M_S_CTRL_Mode_Cfg(SBCdrv_tenModeControlType  mode)
{

	SBCdrv_stControlRegisters.M_S_CTRL.RegistersData &=(uint8)~(0x07<<6u) ;
	SBCdrv_stControlRegisters.M_S_CTRL.RegistersData |=(uint8)((uint8)mode << 6U) ;

}
/******************************************************************************/
/*
*Function Name :  TLE9262Drv_M_S_CTRL_VCC3ModeControl(SBCdrv_tenVcc3ModeControlType  mode);

* Description   :	VCC3 Mode Control
				0B , VCC3 OFF
				1B , VCC3 is enabled (as independent voltage regulator)
* Date          :	2018.03.28
*/
/******************************************************************************/
void  TLE9262Drv_M_S_CTRL_VCC3Mode_Cfg(SBCdrv_tenVcc3ModeControlType  mode)
{
	SBCdrv_stControlRegisters.M_S_CTRL.RegistersData &=(uint8)~(0x1<<5) ;
	SBCdrv_stControlRegisters.M_S_CTRL.RegistersData |=(uint8)((uint8)(mode<<5)) ;
}

/******************************************************************************/
/*
*Function Name :TLE9262Drv_M_S_CTRL_VCC2ModeControl(SBCdrv_tenVcc2ModeControlType  mode);

* Description   :	VCC2 Mode Control
				00B , VCC2 off
				01B , VCC2 on in Normal Mode
				10B , VCC2 on in Normal and Stop Mode
				11B , VCC2 always on (except in SBC Fail-Safe Mode)
				
* Date          :	2018.03.28
*/
/******************************************************************************/
void  TLE9262Drv_M_S_CTRL_VCC2Mode_Cfg(SBCdrv_tenVcc2ModeControlType  mode)
{
	SBCdrv_stControlRegisters.M_S_CTRL.RegistersData &=(uint8)~0x18 ;
	SBCdrv_stControlRegisters.M_S_CTRL.RegistersData |=(uint8)((uint8)mode<<3) ;
}
/******************************************************************************/
/*
*Function Name :TLE9262Drv_VCC1_OV_Control(SBCdrv_tenVcc2ModeControlType  mode);

* Description   :	VCC1 Over Voltage leading to Restart / Fail-Safe Mode enable
				0B , VCC1_ OV is set in case of VCC1_OV; no SBC Restart or Fail-
					Safe is entered for VCC1_OV
				1B , VCC1_ OV is set in case of VCC1_OV; depending on the
					device configuration SBC Restart or SBC Fail-Safe Mode is
					entered (see Chapter 5.1.1);
* Date          :	2018.03.28
*/
/******************************************************************************/
void  TLE9262Drv_M_S_CTRL_VCC1_OV_Cfg(SBCdrv_tenVCC1_OV_RSTType  mode)
{
	SBCdrv_stControlRegisters.M_S_CTRL.RegistersData &=(uint8)~0x04 ;
	SBCdrv_stControlRegisters.M_S_CTRL.RegistersData |=(uint8)((uint8)(mode<<2));
}

/******************************************************************************/
/*
*Function Name :TLE9262Drv_M_S_CTRL_VCC1_OV_Control(SBCdrv_tenVcc2ModeControlType  mode);

* Description   :	VRT1,f 4.5 4.6 4.75 V VCC1 falling
				VRT1,r 4.6 4.7 4.85 V VCC1 rising

				VRT2,f 3.75 3.9 4.05 V VCC1 falling 
				VRT2,r 3.85 4.0 4.15 V VCC1 rising 

				VRT3,f 3.15 3.3 3.45 V VCC1 falling
				VRT3,r 3.25 3.4 3.55 V VCC1 rising

				VRT4,f 2.4 2.65 2.8 V VCC1 falling
				VRT4,r 2.5 2.75 2.9 V VCC1 rising
* Date          :	2018.03.28
*/
/******************************************************************************/
void  TLE9262Drv_M_S_CTRL_VCC1_RT_Cfg(SBCdrv_tenVCC1_RTType  mode)
{
	SBCdrv_stControlRegisters.M_S_CTRL.RegistersData &=(uint8)~0x03 ;
	SBCdrv_stControlRegisters.M_S_CTRL.RegistersData |=(uint8)((uint8)mode<<0);
}
/******************************************************************************/




/********************************************************************************/
/*******************HW_CTRL*****************************************************/
/********************************************************************************/







/******************************************************************************/
/*
*Function Name :TLE9262Drv_HW_CTRL_VCC1_RT_Cfg(SBCdrv_tenVcc2ModeControlType  mode);

* Description   :	VCC3 Output Voltage Configuration
				0B , VCC3 has same output voltage as VCC1
				1B , VCC3 is configured to either 3.3V or 1.8V (depending on VCC1 derivative)
* Date          :	2018.04.10
*/
/******************************************************************************/
static void  TLE9262Drv_HW_CTRL_VCC3_V_Cfg(SBCdrv_tenVCC3_V_CFGType  mode)
{
	SBCdrv_stControlRegisters.HW_CTRL.RegistersData &=(uint8)~0x80 ;
	SBCdrv_stControlRegisters.HW_CTRL.RegistersData |=(uint8)((uint8)mode<<7);
}






/******************************************************************************/
/*
*Function Name :TLE9262Drv_HW_CTRL_VCC1_OV_Control(SBCdrv_tenVcc2ModeControlType  mode);

* Description   :	Soft Reset Configuration
				0B , RO will be triggered (pulled low) during a Soft Reset
				1B , No RO triggering during a Soft Reset
* Date          :	2018.03.28
*/
/******************************************************************************/
static void  TLE9262Drv_HW_CTRL_Soft_Reset_RO_Cfg(SBCdrv_tenSoftResetRoType  mode)
{
	SBCdrv_stControlRegisters.HW_CTRL.RegistersData &=(uint8)~0x40 ;
	SBCdrv_stControlRegisters.HW_CTRL.RegistersData |=(uint8)((uint8)mode<<6);
}






/******************************************************************************/
/*
*Function Name :TLE9262Drv_HW_CTRL_FailureOutputActivation_Cfg(SBCdrv_tenFailureOutputActivation_CFGType  mode);

* Description   :	Failure Output Activation
				0B , activated by defined failures
				1B , activated by software
* Date          :	2018.04.10
*/
/******************************************************************************/
static void  TLE9262Drv_HW_CTRL_FailureOutputActivation_Cfg(SBCdrv_tenFailureOutputActivation_CFGType  mode)
{
	SBCdrv_stControlRegisters.HW_CTRL.RegistersData &=(uint8)~0x20 ;
	SBCdrv_stControlRegisters.HW_CTRL.RegistersData |=(uint8)((uint8)mode<<5);
}





/******************************************************************************/
/*
*Function Name :TLE9262Drv_HW_CTRL_VCC3_VS_UV_OFF_Cfg(SBCdrv_tenVCC3_VS_UV_OFF_CFGType  mode);

* Description   :	VCC3 VS_UV shutdown configuration
				0B , VCC3 will be disabled automatically at VS_UV
				1B , VCC3 will stay enabled even below VS_UV
* Date          :	2018.04.10
*/
/******************************************************************************/
static void  TLE9262Drv_HW_CTRL_VCC3_VS_UV_OFF_Cfg(SBCdrv_tenVCC3_VS_UV_OFF_CFGType  mode)
{
	SBCdrv_stControlRegisters.HW_CTRL.RegistersData &=(uint8)~0x10 ;
	SBCdrv_stControlRegisters.HW_CTRL.RegistersData |=(uint8)((uint8)mode<<4);
}





/******************************************************************************/
/*
*Function Name :TLE9262Drv_HW_CTRL_VCC3_LS_Cfg(SBCdrv_tenVCC3_LS_CFGType  mode);

* Description   :	VCC3 Configuration
				0B , VCC3 operating as a stand-alone regulator
				1B , VCC3 in load sharing operation with VCC1
* Date          :	2018.04.10
*/
/******************************************************************************/
static void  TLE9262Drv_HW_CTRL_VCC3_LS_Cfg(SBCdrv_tenVCC3_LS_CFGType  mode)
{
	SBCdrv_stControlRegisters.HW_CTRL.RegistersData &=(uint8)~0x08 ;
	SBCdrv_stControlRegisters.HW_CTRL.RegistersData |=(uint8)((uint8)mode<<3);
}






/******************************************************************************/
/*
*Function Name :TLE9262Drv_HW_CTRL_VCC3_LS_STP_ON_Cfg(SBCdrv_tenVCC3_LS_CFGType  mode);

* Description   :	VCC3 Configuration
				0B , VCC3 in LS configuration during SBC Stop Mode and highpower mode: disabled
				1B , VCC3 in LS configuration during SBC Stop Mode and highpower mode: enabled
* Date          :	2018.04.10
*/
/******************************************************************************/
static void  TLE9262Drv_HW_CTRL_VCC3_LS_STP_ON_Cfg(SBCdrv_tenVCC3_LS_STP_ON_CFGType  mode)
{
	SBCdrv_stControlRegisters.HW_CTRL.RegistersData &=(uint8)~0x02 ;
	SBCdrv_stControlRegisters.HW_CTRL.RegistersData |=(uint8)((uint8)mode<<1);
}





/******************************************************************************/
/*
*Function Name :TLE9262Drv_HW_CTRL_VCC1_OV_Control(SBCdrv_tenHW_CTRL_CFGModeType  mode);

* Description   :	Configuration Select (see also Table 5)
				0B , Depending on hardware configuration, SBC Restart or Fail-
				Safe Mode is reached after the 2. watchdog trigger failure
				(=default) - Config 3/4
				1B , Depending on hardware configuration, SBC Restart or Fail-
				Safe Mode is reached after the 1. watchdog trigger failure -
				Config
* Date          :	2018.03.28				
*/
/******************************************************************************/
static void  TLE9262Drv_HW_CTRL_CFG_Cfg(SBCdrv_tenHW_CTRL_CFGModeType  mode)
{
	SBCdrv_stControlRegisters.HW_CTRL.RegistersData &=(uint8)~0x01 ;
	SBCdrv_stControlRegisters.HW_CTRL.RegistersData |=(uint8)((uint8)mode<<0);
}




/*******************WD_CTRL*****************************************************/
/******************************************************************************/
/*
*Function Name :TLE9262Drv_WDCheckSum_Cfg(void)

* Description   :	A check sum bit is part of the SPI commend to trigger the watchdog and to set the watchdog setting.
				The sum of the 8 data bits in the register WWD_CTRL needs to have even parity (see Equation (3)). This is
				realized by either setting the bit CHECKSUM to 0 or 1. If the check sum is wrong, then the SPI command is
				ignored, i.e. the watchdog is not triggered or the settings are not changed and the bit SPI_FAIL is set.
				The checksum is calculated by taking all 8 data bits into account. The written value of the reserved bit 3 of the
				WWD_CTRL register is considered (even if read as ��0�� in the SPI output) for checksum calculation, i.e. if a 1 is
				written on the reserved bit position, then a 1 will be used in the checksum calculation.
* Date          :	2018.03.28				
*/
/******************************************************************************/
static void TLE9262Drv_WDCheckSum_Cfg(void)
{
	uint8 i=0,CheckSumBit=0;
	uint8 CheckSum=0;
	for(i=0;i<7;i++)	
	{
		CheckSum+=((SBCdrv_stControlRegisters.WD_CTRL.RegistersData>>i) & (uint8)0x01);
	}
	if(CheckSum%2==1)
	{
		CheckSumBit =1;
	}
	else
	{
		CheckSumBit =0;
	}
	SBCdrv_stControlRegisters.WD_CTRL.RegistersData &=(uint8)~0x80 ;
	SBCdrv_stControlRegisters.WD_CTRL.RegistersData |=(uint8)((uint8)CheckSumBit<<7);
		
}


/******************************************************************************/
/*******************BUS_CTRL_1************************************************/
/******************************************************************************/




/******************************************************************************/
/*
*Function Name :TLE9262Drv_BUS_CTRL_1_LinFlash_Cfg(SBCdrv_tenLINxFlashProgrammingModeType mode)

* Description   :	LINx Flash Programming Mode
				0B , Slope control mechanism active
				1B , Deactivation of slope control for baud rates up to 115kBaud

* Date          :	2018.04.10	
*/
/******************************************************************************/
static void TLE9262Drv_BUS_CTRL_1_LinFlash_Cfg(SBCdrv_tenLINxFlashProgrammingModeType  mode)
{
	SBCdrv_stControlRegisters.BUS_CTRL_1.RegistersData &=(uint8)~0x80 ;
	SBCdrv_stControlRegisters.BUS_CTRL_1.RegistersData |=(uint8)((uint8)mode<<7);
}




/******************************************************************************/
/*
*Function Name :TLE9262Drv_BUS_CTRL_1_LIN_LSM_Cfg(SBCdrv_tenLINxLSMType mode)

* Description   :	LINx Low-Slope Mode Selection
				0B , LIN Normal-Mode is activated
				1B , LIN Low-Slope Mode (10.4kBaud) activated

* Date          :	2018.04.10	
*/
/******************************************************************************/
static void TLE9262Drv_BUS_CTRL_1_LIN_LSM_Cfg(SBCdrv_tenLINxLSMType  mode)
{
	SBCdrv_stControlRegisters.BUS_CTRL_1.RegistersData &=(uint8)~0x40 ;
	SBCdrv_stControlRegisters.BUS_CTRL_1.RegistersData |=(uint8)((uint8)mode<<6);
}




/******************************************************************************/
/*
*Function Name :TLE9262Drv_BUS_CTRL_1_LIN_LSM_Cfg(SBCdrv_tenLINTXDTimeOutType mode)

* Description   :	LINx TXD Time-Out Control
				0B , TXD Time-Out feature disabled
				1B , TXD Time-Out feature enabled

* Date          :	2018.04.10	
*/
/******************************************************************************/
static void TLE9262Drv_BUS_CTRL_1_LIN_TXD_TO_Cfg(SBCdrv_tenLINTXDTimeOutType  mode)
{
	SBCdrv_stControlRegisters.BUS_CTRL_1.RegistersData &=(uint8)~0x20 ;
	SBCdrv_stControlRegisters.BUS_CTRL_1.RegistersData |=(uint8)((uint8)mode<<5);
}




/******************************************************************************/
/*
*Function Name :TLE9262Drv_BUS_CTRL_1_LIN1_Module_Cfg(SBCdrv_tenLINModuleModeType mode)

* Description   :	LIN1-Module Mode
				00B , LIN1 OFF
				01B , LIN1 is wake capable
				10B , LIN1 Receive Only Mode
				11B , LIN1 Normal Mode
* Date          :	2018.04.10	
*/
/******************************************************************************/
static void TLE9262Drv_BUS_CTRL_1_LIN1_Module_Cfg(SBCdrv_tenLINModuleModeType  mode)
{
	SBCdrv_stControlRegisters.BUS_CTRL_1.RegistersData &=(uint8)~0x18 ;
	SBCdrv_stControlRegisters.BUS_CTRL_1.RegistersData |=(uint8)((uint8)mode<<3);
}




/******************************************************************************/
/*
*Function Name :TLE9262Drv_BUS_CTRL_1_HSCAN_Module_Cfg(SBCdrv_tenHSCANModuleModeType mode)

* Description   :	CAN-Module Mode
				00B , CAN OFF
				01B , CAN is wake capable
				10B , CAN Receive Only Mode
				11B , CAN Normal Mode
* Date          :	2018.04.11	
*/
/******************************************************************************/
static void TLE9262Drv_BUS_CTRL_1_HSCAN_Module_Cfg(SBCdrv_tenHSCANModuleModeType  mode)
{
	SBCdrv_stControlRegisters.BUS_CTRL_1.RegistersData &=(uint8)~0x03 ;
	SBCdrv_stControlRegisters.BUS_CTRL_1.RegistersData |=(uint8)((uint8)mode<<0);
}




/******************************************************************************/
/*******************BUS_CTRL_2************************************************/
/******************************************************************************/




/******************************************************************************/
/*
*Function Name :TLE9262Drv_BUS_CTRL_2_I_PEAK_TH_Cfg(SBCdrv_tenHSCANModuleModeType mode)

* Description   :	CAN-Module Mode
				0B , low VCC1 active peak threshold selected
				1B , higher VCC1 active peak threshold selected
* Date          :	2018.04.11	
*/
/******************************************************************************/
static void TLE9262Drv_BUS_CTRL_2_I_PEAK_TH_Cfg(SBCdrv_tenPeakThresholdModeType  mode)
{
	SBCdrv_stControlRegisters.BUS_CTRL_2.RegistersData &=(uint8)~0x20 ;
	SBCdrv_stControlRegisters.BUS_CTRL_2.RegistersData |=(uint8)((uint8)mode<<5);
}



/******************************************************************************/
/*******************WK_CTRL_1************************************************/
/******************************************************************************/




/******************************************************************************/
/*
*Function Name :void TLE9262Drv_WK_CTRL_1_TIMER2_WK_EN_CFG(SBCdrv_tenTmer2WakeSourceEnModeType mode)

* Description   :Timer2 Wake Source Control (for cyclic wake)
			0B , Timer2 wake disabled
			1B , Timer2 is enabled as a wake source
* Date          :	2018.04.11	
*/
/******************************************************************************/
static void TLE9262Drv_WK_CTRL_1_TIMER2_WK_EN_CFG(SBCdrv_tenTmer2WakeSourceEnModeType mode)
{
	SBCdrv_stControlRegisters.WK_CTRL_1.RegistersData &=(uint8)~0x80 ;
	SBCdrv_stControlRegisters.WK_CTRL_1.RegistersData |=(uint8)((uint8)mode<<7);
}



/******************************************************************************/
/*
*Function Name :void TLE9262Drv_WK_CTRL_1_TIMER1_WK_EN_CFG(SBCdrv_tenTmer1WakeSourceEnModeType mode)

* Description   :Timer1 Wake Source Control (for cyclic wake)
			0B , Timer1 wake disabled
			1B , Timer1 is enabled as a wake source
* Date          :	2018.04.11	
*/
/******************************************************************************/
static void TLE9262Drv_WK_CTRL_1_TIMER1_WK_EN_CFG(SBCdrv_tenTmer1WakeSourceEnModeType mode)
{
	SBCdrv_stControlRegisters.WK_CTRL_1.RegistersData &=(uint8)~0x40 ;
	SBCdrv_stControlRegisters.WK_CTRL_1.RegistersData |=(uint8)((uint8)mode<<6);
}



/******************************************************************************/
/*
*Function Name :void TLE9262Drv_WK_CTRL_1_WD_STM_EN_1_CFG(SBCdrv_tenWatchdogSTM_EN1ModeType mode)

* Description   :Watchdog Deactivation during Stop Mode
			0B , Watchdog is active in Stop Mode
			1B , Watchdog is deactivated in Stop Mode
* Date          :	2018.04.11	
*/
/******************************************************************************/
static void TLE9262Drv_WK_CTRL_1_WD_STM_EN_1_CFG(SBCdrv_tenWatchdogSTM_EN1ModeType mode)
{
	SBCdrv_stControlRegisters.WK_CTRL_1.RegistersData &=(uint8)~0x04 ;
	SBCdrv_stControlRegisters.WK_CTRL_1.RegistersData |=(uint8)((uint8)mode<<2);
}



/******************************************************************************/
/*******************WK_CTRL_2************************************************/
/******************************************************************************/




/******************************************************************************/
/*
*Function Name :void TLE9262Drv_WK_CTRL_2_WD_STM_EN_1_CFG(SBCdrv_tenGlobalInterruptConfigurationModeType mode)

* Description   :Global Interrupt Configuration
			0B , Only wake sources trigger INT (default)
			1B , All status information register bits will trigger INT (including all wake sources)
* Date          :	2018.04.11	
*/
/******************************************************************************/
static void TLE9262Drv_WK_CTRL_2_INT_GLOBAL_CFG(SBCdrv_tenGlobalInterruptConfigurationModeType mode)
{
	SBCdrv_stControlRegisters.WK_CTRL_2.RegistersData &=(uint8)~0x80 ;
	SBCdrv_stControlRegisters.WK_CTRL_2.RegistersData |=(uint8)((uint8)mode<<7);
}



/******************************************************************************/
/*
*Function Name :void TLE9262Drv_WK_CTRL_2_WK_MEAS_CFG(SBCdrv_tenWK_MEASModeType mode)

* Description   :WK / Measurement selection
			0B , WK functionality enabled for WK1 and WK2
			1B , Measurement functionality enabled; WK1 & WK2 are disabled as wake sources, i.e. bits WK1/2_EN bits are ignored
* Date          :	2018.04.11	
*/
/******************************************************************************/
static void TLE9262Drv_WK_CTRL_2_WK_MEAS_CFG(SBCdrv_tenWK_MEASModeType mode)
{
	SBCdrv_stControlRegisters.WK_CTRL_2.RegistersData &=(uint8)~0x20 ;
	SBCdrv_stControlRegisters.WK_CTRL_2.RegistersData |=(uint8)((uint8)mode<<5);
}



/******************************************************************************/
/*
*Function Name :void TLE9262Drv_WK_CTRL_2_WK3_EN_CFG(SBCdrv_tenWK3_ENModeType mode)

* Description   :WK3 Wake Source Control
			0B , WK3 wake disabled
			1B , WK3 is enabled as a wake source
* Date          :	2018.04.11	
*/
/******************************************************************************/
static void TLE9262Drv_WK_CTRL_2_WK3_EN_CFG(SBCdrv_tenWK3_ENModeType mode)
{
	SBCdrv_stControlRegisters.WK_CTRL_2.RegistersData &=(uint8)~0x04 ;
	SBCdrv_stControlRegisters.WK_CTRL_2.RegistersData |=(uint8)((uint8)mode<<2);
}



/******************************************************************************/
/*
*Function Name :void TLE9262Drv_WK_CTRL_2_WK2_EN_CFG(SBCdrv_tenWK2_ENModeType mode)

* Description   :WK2 Wake Source Control
			0B , WK2 wake disabled
			1B , WK2 is enabled as a wake source
* Date          :	2018.04.11	
*/
/******************************************************************************/
static void TLE9262Drv_WK_CTRL_2_WK2_EN_CFG(SBCdrv_tenWK2_ENModeType mode)
{
	SBCdrv_stControlRegisters.WK_CTRL_2.RegistersData &=(uint8)~0x02 ;
	SBCdrv_stControlRegisters.WK_CTRL_2.RegistersData |=(uint8)((uint8)mode<<1);
}



/******************************************************************************/
/*
*Function Name :void TLE9262Drv_WK_CTRL_2_WK1_EN_CFG(SBCdrv_tenWK1_ENModeType mode)

* Description   :WK1 Wake Source Control
			0B , WK1 wake disabled
			1B , WK1 is enabled as a wake source
* Date          :	2018.04.11	
*/
/******************************************************************************/
static void TLE9262Drv_WK_CTRL_2_WK1_EN_CFG(SBCdrv_tenWK1_ENModeType mode)
{
	SBCdrv_stControlRegisters.WK_CTRL_2.RegistersData &=(uint8)~0x01 ;
	SBCdrv_stControlRegisters.WK_CTRL_2.RegistersData |=(uint8)((uint8)mode<<0);
}



/******************************************************************************/
/*******************WK_PUPD_CTRL************************************************/
/******************************************************************************/




/******************************************************************************/
/*
*Function Name :void TLE9262Drv_WK_PUPD_CTRL_WK3_PUPD_CFG(SBCdrv_tenWK3_PUPDModeType mode)

* Description   :WK3 Pull-Up / Pull-Down Configuration
			00B , No pull-up / pull-down selected
			01B , Pull-down resistor selected
			10B , Pull-up resistor selected
			11B , Automatic switching to pull-up or pull-down
* Date          :	2018.04.11	
*/
/******************************************************************************/
#if 0
static void TLE9262Drv_WK_PUPD_CTRL_WK3_PUPD_CFG(SBCdrv_tenWK3_PUPDModeType mode)
{
	SBCdrv_stControlRegisters.WK_PUPD_CTRL.RegistersData &=(uint8)~0x30 ;
	SBCdrv_stControlRegisters.WK_PUPD_CTRL.RegistersData |=(uint8)((uint8)mode<<4);
}
#endif

/******************************************************************************/
/*
*Function Name :void TLE9262Drv_WK_PUPD_CTRL_WK2_PUPD_CFG(SBCdrv_tenWK2_PUPDModeType mode)

* Description   :WK2 Pull-Up / Pull-Down Configuration
			00B , No pull-up / pull-down selected
			01B , Pull-down resistor selected
			10B , Pull-up resistor selected
			11B , Automatic switching to pull-up or pull-down
* Date          :	2018.04.11	
*/
/******************************************************************************/
#if 0
static void TLE9262Drv_WK_PUPD_CTRL_WK2_PUPD_CFG(SBCdrv_tenWK2_PUPDModeType mode)
{
	SBCdrv_stControlRegisters.WK_PUPD_CTRL.RegistersData &=(uint8)~0x0C ;
	SBCdrv_stControlRegisters.WK_PUPD_CTRL.RegistersData |=(uint8)((uint8)mode<<2);
}
#endif


/******************************************************************************/
/*
*Function Name :void TLE9262Drv_WK_PUPD_CTRL_WK1_PUPD_CFG(SBCdrv_tenWK1_PUPDModeType mode)

* Description   :WK1 Pull-Up / Pull-Down Configuration
			00B , No pull-up / pull-down selected
			01B , Pull-down resistor selected
			10B , Pull-up resistor selected
			11B , Automatic switching to pull-up or pull-down
* Date          :	2018.04.11	
*/
/******************************************************************************/
#if 0
static void TLE9262Drv_WK_PUPD_CTRL_WK1_PUPD_CFG(SBCdrv_tenWK1_PUPDModeType mode)
{
	SBCdrv_stControlRegisters.WK_PUPD_CTRL.RegistersData &=(uint8)~0x03 ;
	SBCdrv_stControlRegisters.WK_PUPD_CTRL.RegistersData |=(uint8)((uint8)mode<<0);
}
#endif
/******************************************************************************/
/*******************WK_FLT_CTRL************************************************/
/******************************************************************************/




/******************************************************************************/
/*
*Function Name :void TLE9262Drv_WK_FLT_CTRL_WK3_FLT_CFG(SBCdrv_tenWK_FLTModeType mode)

* Description   :WK3 Filter Time Configuration
			00B , Configuration A: Filter with 16��s filter time (static sensing)
			01B , Configuration B: Filter with 64��s filter time (static sensing)
			10B , Configuration C: Filtering at the end of the on-time; a filter time of 16��s (cyclic sensing) is selected, Timer1
			11B , Configuration D: Filtering at the end of the on-time; a filter time of 16��s (cyclic sensing) is selected, Timer2
* Date          :	2018.04.11	
*/
/******************************************************************************/
#if 0
static void TLE9262Drv_WK_FLT_CTRL_WK3_FLT_CFG(SBCdrv_tenWK_FLTModeType mode)
{
	SBCdrv_stControlRegisters.WK_FLT_CTRL.RegistersData &=(uint8)~0x30 ;
	SBCdrv_stControlRegisters.WK_FLT_CTRL.RegistersData |=(uint8)((uint8)mode<<4);
}
#endif


/******************************************************************************/
/*
*Function Name :void TLE9262Drv_WK_FLT_CTRL_WK2_FLT_CFG(SBCdrv_tenWK_FLTModeType mode)

* Description   :WK2 Filter Time Configuration
			00B , Configuration A: Filter with 16��s filter time (static sensing)
			01B , Configuration B: Filter with 64��s filter time (static sensing)
			10B , Configuration C: Filtering at the end of the on-time; a filter time of 16��s (cyclic sensing) is selected, Timer1
			11B , Configuration D: Filtering at the end of the on-time; a filter time of 16��s (cyclic sensing) is selected, Timer2
* Date          :	2018.04.11	
*/
/******************************************************************************/
#if 0
static void TLE9262Drv_WK_FLT_CTRL_WK2_FLT_CFG(SBCdrv_tenWK_FLTModeType mode)
{
	SBCdrv_stControlRegisters.WK_FLT_CTRL.RegistersData &=(uint8)~0x0C ;
	SBCdrv_stControlRegisters.WK_FLT_CTRL.RegistersData |=(uint8)((uint8)mode<<2);
}
#endif


/******************************************************************************/
/*
*Function Name :void TLE9262Drv_WK_FLT_CTRL_WK1_FLT_CFG(SBCdrv_tenWK_FLTModeType mode)

* Description   :WK1 Filter Time Configuration
			00B , Configuration A: Filter with 16��s filter time (static sensing)
			01B , Configuration B: Filter with 64��s filter time (static sensing)
			10B , Configuration C: Filtering at the end of the on-time; a filter time of 16��s (cyclic sensing) is selected, Timer1
			11B , Configuration D: Filtering at the end of the on-time; a filter time of 16��s (cyclic sensing) is selected, Timer2
* Date          :	2018.04.11	
*/
/******************************************************************************/
#if 0
static void TLE9262Drv_WK_FLT_CTRL_WK1_FLT_CFG(SBCdrv_tenWK_FLTModeType mode)
{
	SBCdrv_stControlRegisters.WK_FLT_CTRL.RegistersData &=(uint8)~0x03 ;
	SBCdrv_stControlRegisters.WK_FLT_CTRL.RegistersData |=(uint8)((uint8)mode<<0);
}
#endif



/******************************************************************************/
/*******************TIMER1_CTRL************************************************/
/******************************************************************************/




/******************************************************************************/
/*
*Function Name :void TLE9262Drv_TIMER1_CTRL_TIMER1_ON_CFG(SBCdrv_tenTIMER_ONModeType mode)

* Description   :Timer1 On-Time Configuration
			000B , OFF / Low (timer not running, HSx output is low)
			001B , 0.1ms on-time
			010B , 0.3ms on-time
			011B , 1.0ms on-time
			100B , 10ms on-time
			101B , 20ms on-time
			110B , OFF / HIGH (timer not running, HSx output is high)
			111B , reserved
* Date          :	2018.04.11	
*/
/******************************************************************************/
#if 0
static void TLE9262Drv_TIMER1_CTRL_TIMER1_ON_CFG(SBCdrv_tenTIMER_ONModeType mode)
{
	SBCdrv_stControlRegisters.TIMER1_CTRL.RegistersData &=(uint8)~(0x07<<4) ;
	SBCdrv_stControlRegisters.TIMER1_CTRL.RegistersData |=(uint8)((uint8)mode<<4);
}
#endif


/******************************************************************************/
/*
*Function Name :void TLE9262Drv_TIMER1_CTRL_TIMER1_PER_CFG(SBCdrv_tenTIMER_PERModeType mode)

* Description   :Timer1 Period Configuration
			000B , 10ms
			001B , 20ms
			010B , 50ms
			011B , 100ms
			100B , 200ms
			101B , 1s
			110B , 2s
			111B , reserved
* Date          :	2018.04.11	
*/
/******************************************************************************/
#if 0
static void TLE9262Drv_TIMER1_CTRL_TIMER1_PER_CFG(SBCdrv_tenTIMER_PERModeType mode)
{
	SBCdrv_stControlRegisters.TIMER1_CTRL.RegistersData &=(uint8)~(0x07) ;
	SBCdrv_stControlRegisters.TIMER1_CTRL.RegistersData |=(uint8)((uint8)mode<<0);
}
#endif


/******************************************************************************/
/*******************TIMER2_CTRL************************************************/
#if 0
static void  TLE9262Drv_TIMER2_CTRL_Data_Clc(void)
{
	SBCdrv_stControlRegisters.TIMER2_CTRL.RegistersData = 0;
}
#endif



/******************************************************************************/
/*
*Function Name :void TLE9262Drv_TIMER2_CTRL_TIMER2_ON_CFG(SBCdrv_tenTIMER_ONModeType mode)

* Description   :Timer2 On-Time Configuration
			000B , OFF / Low (timer not running, HSx output is low)
			001B , 0.1ms on-time
			010B , 0.3ms on-time
			011B , 1.0ms on-time
			100B , 10ms on-time
			101B , 20ms on-time
			110B , OFF / HIGH (timer not running, HSx output is high)
			111B , reserved
* Date          :	2018.04.11	
*/
/******************************************************************************/
#if 0
static void TLE9262Drv_TIMER2_CTRL_TIMER2_ON_CFG(SBCdrv_tenTIMER_ONModeType mode)
{
	SBCdrv_stControlRegisters.TIMER2_CTRL.RegistersData &=(uint8)~(0x07<<4) ;
	SBCdrv_stControlRegisters.TIMER2_CTRL.RegistersData |=(uint8)((uint8)mode<<4);
}
#endif


/******************************************************************************/
/*
*Function Name :void TLE9262Drv_TIMER2_CTRL_TIMER2_PER_CFG(SBCdrv_tenTIMER_PERModeType mode)

* Description   :Timer2 Period Configuration
			000B , 10ms
			001B , 20ms
			010B , 50ms
			011B , 100ms
			100B , 200ms
			101B , 1s
			110B , 2s
			111B , reserved
* Date          :	2018.04.11	
*/
/******************************************************************************/
#if 0
static void TLE9262Drv_TIMER2_CTRL_TIMER2_PER_CFG(SBCdrv_tenTIMER_PERModeType mode)
{
	SBCdrv_stControlRegisters.TIMER2_CTRL.RegistersData &=(uint8)~(0x07) ;
	SBCdrv_stControlRegisters.TIMER2_CTRL.RegistersData |=(uint8)((uint8)mode<<0);
}
#endif


/******************************************************************************/
/*******************SW_SD_CTRL************************************************/
/******************************************************************************/




/******************************************************************************/
/*
*Function Name :void TLE9262Drv_SW_SD_CTRL_HS_OV_SD_EN_CFG()

* Description   :Shutdown Disabling of HS1...4 in case of VSHS OV
			0B , shutdown enabled in case of VSHS OV
			1B , shutdown disabled in case of VSHS OV
* Date          :	2018.04.11	
*/
/******************************************************************************/
static void TLE9262Drv_SW_SD_CTRL_HS_OV_SD_EN_CFG(SBCdrv_tenHS_OV_UV_SD_ENModeType mode)
{
	SBCdrv_stControlRegisters.SW_SD_CTRL.RegistersData &=(uint8)~(0x01<<6) ;
	SBCdrv_stControlRegisters.SW_SD_CTRL.RegistersData |=(uint8)((uint8)(mode<<6));
}



/******************************************************************************/
/*
*Function Name :void TLE9262Drv_SW_SD_CTRL_HS_UV_SD_EN_CFG()

* Description   :Shutdown Disabling of HS1...4 in case of VSHS UV
			0B , shutdown enabled in case of VSHS UV
			1B , shutdown disabled in case of VSHS UV
* Date          :	2018.04.11	
*/
/******************************************************************************/
static void TLE9262Drv_SW_SD_CTRL_HS_UV_SD_EN_CFG(SBCdrv_tenHS_OV_UV_SD_ENModeType mode)
{
	SBCdrv_stControlRegisters.SW_SD_CTRL.RegistersData &=(uint8)~(0x01<<5) ;
	SBCdrv_stControlRegisters.SW_SD_CTRL.RegistersData |=(uint8)((uint8)mode<<5);
}



/******************************************************************************/
/*
*Function Name :void TLE9262Drv_SW_SD_CTRL_HS_UV_SD_REC_CFG()

* Description   :Switch Recovery after Removal of VSHS OV/UV for HS1...4
			0B , Switch recovery is disabled
			1B , Previous state before VSHS OV/UV is enabled after OV/UV condition is removed
* Date          :	2018.04.11	
*/
/******************************************************************************/
static void TLE9262Drv_SW_SD_CTRL_HS_OV_UV_REC_CFG(SBCdrv_tenHS_OV_UV_RECModeType mode)
{
	SBCdrv_stControlRegisters.SW_SD_CTRL.RegistersData &=(uint8)~(0x01<<4) ;
	SBCdrv_stControlRegisters.SW_SD_CTRL.RegistersData |=(uint8)((uint8)mode<<4);
}



/******************************************************************************/
/*******************HS_CTRL1************************************************/
/******************************************************************************/



/******************************************************************************/
/*
*Function Name :void TLE9262Drv_HS_CTRL1_HS2_CFG()

* Description   :HS2 Configuration
			000B , Off
			001B , On
			010B , Controlled by Timer1
			011B , Controlled by Timer2
			100B , Controlled by PWM1
			101B , Controlled by PWM2
			110B , Reserved
			111B , Reserved
* Date          :	2018.04.11	
*/
/******************************************************************************/
static void TLE9262Drv_HS_CTRL1_HS2_CFG(SBCdrv_tenHS_ConfigurationModeType mode)
{
	SBCdrv_stControlRegisters.HS_CTRL_1.RegistersData &=(uint8)~(0x07<<4) ;
	SBCdrv_stControlRegisters.HS_CTRL_1.RegistersData |=(uint8)((uint8)mode<<4);
}



/******************************************************************************/
/*
*Function Name :void TLE9262Drv_HS_CTRL1_HS1_CFG()

* Description   :HS1 Configuration
			000B , Off
			001B , On
			010B , Controlled by Timer1
			011B , Controlled by Timer2
			100B , Controlled by PWM1
			101B , Controlled by PWM2
			110B , Reserved
			111B , Reserved
* Date          :	2018.04.11	
*/
/******************************************************************************/
static void TLE9262Drv_HS_CTRL1_HS1_CFG(SBCdrv_tenHS_ConfigurationModeType mode)
{
	SBCdrv_stControlRegisters.HS_CTRL_1.RegistersData &=(uint8)~(0x07<<0) ;
	SBCdrv_stControlRegisters.HS_CTRL_1.RegistersData |=(uint8)((uint8)mode<<0);
}



/******************************************************************************/
/*******************HS_CTRL2************************************************/
/******************************************************************************/

/******************************************************************************/
/*
*Function Name :void TLE9262Drv_HS_CTRL2_HS4_CFG()

* Description   :HS4 Configuration
			000B , Off
			001B , On
			010B , Controlled by Timer1
			011B , Controlled by Timer2
			100B , Controlled by PWM1
			101B , Controlled by PWM2
			110B , Reserved
			111B , Reserved
* Date          :	2018.04.11	
*/
/******************************************************************************/
static void TLE9262Drv_HS_CTRL2_HS4_CFG(SBCdrv_tenHS_ConfigurationModeType mode)
{
	SBCdrv_stControlRegisters.HS_CTRL_2.RegistersData &=(uint8)~(0x07<<4) ;
	SBCdrv_stControlRegisters.HS_CTRL_2.RegistersData |=(uint8)((uint8)mode<<4);
}



/******************************************************************************/
/*
*Function Name :void TLE9262Drv_HS_CTRL2_HS3_CFG()

* Description   :HS3 Configuration
			000B , Off
			001B , On
			010B , Controlled by Timer1
			011B , Controlled by Timer2
			100B , Controlled by PWM1
			101B , Controlled by PWM2
			110B , Reserved
			111B , Reserved
* Date          :	2018.04.11	
*/
/******************************************************************************/
static void TLE9262Drv_HS_CTRL2_HS3_CFG(SBCdrv_tenHS_ConfigurationModeType mode)
{
	SBCdrv_stControlRegisters.HS_CTRL_2.RegistersData &=(uint8)~(0x07<<0) ;
	SBCdrv_stControlRegisters.HS_CTRL_2.RegistersData |=(uint8)((uint8)mode<<0);
}




/******************************************************************************/
/*******************SUP_STAT_2************************************************/
/******************************************************************************/
#if 0
static void  TLE9262Drv_SUP_STAT_2_Clc(void)
{
	SBCdrv_stStatusRegisters.SUP_STAT_2.RegistersData = 0;
	CtrlRe1[0] = SBCdrv_stStatusRegisters.SUP_STAT_2.RegistersAddr;
	CtrlRe1[1] = SBCdrv_stStatusRegisters.SUP_STAT_2.RegistersData;
	TLE9262Drv_Clc_Sta_Regs(CtrlRe1,u8Rec);
}
#endif
static void  TLE9262Drv_SUP_STAT_2_Get(void)
{
	SBCdrv_stStatusRegisters.SUP_STAT_2.RegistersData = 0;
	CtrlRe1[0] = SBCdrv_stStatusRegisters.SUP_STAT_2.RegistersAddr;
	CtrlRe1[1] = SBCdrv_stStatusRegisters.SUP_STAT_2.RegistersData;
	TLE9262Drv_R_Sta_Regs(CtrlRe1,u8Rec);
	 SBCdrv_stStatusRegisters.SUP_STAT_2.RegistersData = u8Rec[1];
}
/******************************************************************************/
/*******************THERM_STAT************************************************/
/******************************************************************************/
#if 0
static void  TLE9262Drv_THERM_STAT_Clc(void)
{
	SBCdrv_stStatusRegisters.THERM_STAT.RegistersData = 0;
	CtrlRe1[0] = SBCdrv_stStatusRegisters.THERM_STAT.RegistersAddr;
	CtrlRe1[1] = SBCdrv_stStatusRegisters.THERM_STAT.RegistersData;
	TLE9262Drv_Clc_Sta_Regs(CtrlRe1,u8Rec);
}
#endif
static void  TLE9262Drv_THERM_STAT_Get(void)
{
	SBCdrv_stStatusRegisters.THERM_STAT.RegistersData = 0;
	CtrlRe1[0] = SBCdrv_stStatusRegisters.THERM_STAT.RegistersAddr;
	CtrlRe1[1] = SBCdrv_stStatusRegisters.THERM_STAT.RegistersData;
	TLE9262Drv_R_Sta_Regs(CtrlRe1,u8Rec);
	 SBCdrv_stStatusRegisters.THERM_STAT.RegistersData = u8Rec[1];
}

/******************************************************************************/
/*******************SUP_STAT_1************************************************/
/******************************************************************************/
static void  TLE9262Drv_SUP_STAT_1_Clc(void)
{
	SBCdrv_stStatusRegisters.SUP_STAT_2.RegistersData = 0;
	CtrlRe1[0] = SBCdrv_stStatusRegisters.SUP_STAT_1.RegistersAddr;
	CtrlRe1[1] = SBCdrv_stStatusRegisters.SUP_STAT_1.RegistersData;
	TLE9262Drv_Clc_Sta_Regs(CtrlRe1,u8Rec);
}
#if 0
static void  TLE9262Drv_SUP_STAT_1_Get(void)
{
	SBCdrv_stStatusRegisters.SUP_STAT_1.RegistersData = 0;
	CtrlRe1[0] = SBCdrv_stStatusRegisters.SUP_STAT_1.RegistersAddr;
	CtrlRe1[1] = SBCdrv_stStatusRegisters.SUP_STAT_1.RegistersData;
	TLE9262Drv_R_Sta_Regs(CtrlRe1,u8Rec);
	 SBCdrv_stStatusRegisters.SUP_STAT_1.RegistersData = u8Rec[1];
}
#endif
/******************************************************************************/
/*******************DEV_STAT************************************************/
/******************************************************************************/
#if 0
static void  TLE9262Drv_DEV_STAT_Clc(void)
{
	SBCdrv_stStatusRegisters.DEV_STAT.RegistersData = 0;
	CtrlRe1[0] = SBCdrv_stStatusRegisters.DEV_STAT.RegistersAddr;
	CtrlRe1[1] = SBCdrv_stStatusRegisters.DEV_STAT.RegistersData;
	TLE9262Drv_Clc_Sta_Regs(CtrlRe1,u8Rec);
}
#endif
static void  TLE9262Drv_DEV_STAT_Get(void)
{
	SBCdrv_stStatusRegisters.DEV_STAT.RegistersData = 0;
	CtrlRe1[0] = SBCdrv_stStatusRegisters.DEV_STAT.RegistersAddr;
	CtrlRe1[1] = SBCdrv_stStatusRegisters.DEV_STAT.RegistersData;
	TLE9262Drv_R_Sta_Regs(CtrlRe1,u8Rec);
	 SBCdrv_stStatusRegisters.DEV_STAT.RegistersData = u8Rec[1];
}

/******************************************************************************/
/*******************BUS_STAT_1************************************************/
/******************************************************************************/
static void  TLE9262Drv_BUS_STAT_1_Clc(void)
{
	SBCdrv_stStatusRegisters.BUS_STAT_1.RegistersData = 0;
	CtrlRe1[0] = SBCdrv_stStatusRegisters.BUS_STAT_1.RegistersAddr;
	CtrlRe1[1] = SBCdrv_stStatusRegisters.BUS_STAT_1.RegistersData;
	TLE9262Drv_Clc_Sta_Regs(CtrlRe1,u8Rec);
}
static void  TLE9262Drv_BUS_STAT_1_Get(void)
{
	SBCdrv_stStatusRegisters.BUS_STAT_1.RegistersData = 0;
	CtrlRe1[0] = SBCdrv_stStatusRegisters.BUS_STAT_1.RegistersAddr;
	CtrlRe1[1] = SBCdrv_stStatusRegisters.BUS_STAT_1.RegistersData;
	TLE9262Drv_R_Sta_Regs(CtrlRe1,u8Rec);
	 SBCdrv_stStatusRegisters.BUS_STAT_1.RegistersData = u8Rec[1];
}
/******************************************************************************/
/*******************BUS_STAT_2************************************************/
/******************************************************************************/
#if 0
static void  TLE9262Drv_BUS_STAT_2_Clc(void)
{
	SBCdrv_stStatusRegisters.BUS_STAT_2.RegistersData = 0;
	CtrlRe1[0] = SBCdrv_stStatusRegisters.BUS_STAT_2.RegistersAddr;
	CtrlRe1[1] = SBCdrv_stStatusRegisters.BUS_STAT_2.RegistersData;
	TLE9262Drv_Clc_Sta_Regs(CtrlRe1,u8Rec);
}
#endif
#if 0
static void  TLE9262Drv_BUS_STAT_2_Get(void)
{
	SBCdrv_stStatusRegisters.BUS_STAT_2.RegistersData = 0;
	CtrlRe1[0] = SBCdrv_stStatusRegisters.BUS_STAT_2.RegistersAddr;
	CtrlRe1[1] = SBCdrv_stStatusRegisters.BUS_STAT_2.RegistersData;
	TLE9262Drv_R_Sta_Regs(CtrlRe1,u8Rec);
	 SBCdrv_stStatusRegisters.BUS_STAT_2.RegistersData = u8Rec[1];
}
#endif
/******************************************************************************/
/*******************WK_STAT_1************************************************/
/******************************************************************************/
static void  TLE9262Drv_WK_STAT_1_Clc(void)
{
	SBCdrv_stStatusRegisters.WK_STAT_1.RegistersData = 0;
	CtrlRe1[0] = SBCdrv_stStatusRegisters.WK_STAT_1.RegistersAddr;
	CtrlRe1[1] = SBCdrv_stStatusRegisters.WK_STAT_1.RegistersData;
	TLE9262Drv_Clc_Sta_Regs(CtrlRe1,u8Rec);
}
static void  TLE9262Drv_WK_STAT_1_Get(void)
{
	SBCdrv_stStatusRegisters.WK_STAT_1.RegistersData = 0;
	CtrlRe1[0] = SBCdrv_stStatusRegisters.WK_STAT_1.RegistersAddr;
	CtrlRe1[1] = SBCdrv_stStatusRegisters.WK_STAT_1.RegistersData;
	TLE9262Drv_R_Sta_Regs(CtrlRe1,u8Rec);
	 SBCdrv_stStatusRegisters.WK_STAT_1.RegistersData = u8Rec[1];
}
/******************************************************************************/
/*******************WK_STAT_2************************************************/
/******************************************************************************/
static void  TLE9262Drv_WK_STAT_2_Clc(void)
{
	SBCdrv_stStatusRegisters.WK_STAT_2.RegistersData = 0;
	CtrlRe1[0] = SBCdrv_stStatusRegisters.WK_STAT_2.RegistersAddr;
	CtrlRe1[1] = SBCdrv_stStatusRegisters.WK_STAT_2.RegistersData;
	TLE9262Drv_Clc_Sta_Regs(CtrlRe1,u8Rec);
}
static void  TLE9262Drv_WK_STAT_2_Get(void)
{
	SBCdrv_stStatusRegisters.WK_STAT_2.RegistersData = 0;
	CtrlRe1[0] = SBCdrv_stStatusRegisters.WK_STAT_2.RegistersAddr;
	CtrlRe1[1] = SBCdrv_stStatusRegisters.WK_STAT_2.RegistersData;
	TLE9262Drv_R_Sta_Regs(CtrlRe1,u8Rec);
	 SBCdrv_stStatusRegisters.WK_STAT_2.RegistersData = u8Rec[1];
}
/******************************************************************************/
/*******************WK_LVL_STAT************************************************/
/******************************************************************************/
#if 0
static void  TLE9262Drv_WK_LVL_STAT_Clc(void)
{
	SBCdrv_stStatusRegisters.WK_LVL_STAT.RegistersData = 0;
	CtrlRe1[0] = SBCdrv_stStatusRegisters.WK_LVL_STAT.RegistersAddr;
	CtrlRe1[1] = SBCdrv_stStatusRegisters.WK_LVL_STAT.RegistersData;
	TLE9262Drv_Clc_Sta_Regs(CtrlRe1,u8Rec);
}
#endif
#if 0
static void  TLE9262Drv_WK_LVL_STAT_Get(void)
{
	SBCdrv_stStatusRegisters.WK_LVL_STAT.RegistersData = 0;
	CtrlRe1[0] = SBCdrv_stStatusRegisters.WK_LVL_STAT.RegistersAddr;
	CtrlRe1[1] = SBCdrv_stStatusRegisters.WK_LVL_STAT.RegistersData;
	TLE9262Drv_R_Sta_Regs(CtrlRe1,u8Rec);
	 SBCdrv_stStatusRegisters.WK_LVL_STAT.RegistersData = u8Rec[1];
}
#endif
/******************************************************************************/
/*******************WK_LVL_STAT************************************************/
/******************************************************************************/
#if 0
static void  TLE9262Drv_HS_OC_OT_STAT_Clc(void)
{
	SBCdrv_stStatusRegisters.HS_OC_OT_STAT.RegistersData = 0;
	CtrlRe1[0] = SBCdrv_stStatusRegisters.HS_OC_OT_STAT.RegistersAddr;
	CtrlRe1[1] = SBCdrv_stStatusRegisters.HS_OC_OT_STAT.RegistersData;
	TLE9262Drv_Clc_Sta_Regs(CtrlRe1,u8Rec);
}
#endif
static void  TLE9262Drv_HS_OC_OT_STAT_Get(void)
{
	SBCdrv_stStatusRegisters.HS_OC_OT_STAT.RegistersData = 0;
	CtrlRe1[0] = SBCdrv_stStatusRegisters.HS_OC_OT_STAT.RegistersAddr;
	CtrlRe1[1] = SBCdrv_stStatusRegisters.HS_OC_OT_STAT.RegistersData;
	TLE9262Drv_R_Sta_Regs(CtrlRe1,u8Rec);
	 SBCdrv_stStatusRegisters.HS_OC_OT_STAT.RegistersData = u8Rec[1];
}
/******************************************************************************/
/*******************HS_OL_STAT************************************************/
/******************************************************************************/
#if 0
static void  TLE9262Drv_HS_OL_STAT_Clc(void)
{
	SBCdrv_stStatusRegisters.HS_OL_STAT.RegistersData = 0;
	CtrlRe1[0] = SBCdrv_stStatusRegisters.HS_OL_STAT.RegistersAddr;
	CtrlRe1[1] = SBCdrv_stStatusRegisters.HS_OL_STAT.RegistersData;
	TLE9262Drv_Clc_Sta_Regs(CtrlRe1,u8Rec);
}
#endif
static void  TLE9262Drv_HS_OL_STAT_Get(void)
{
	SBCdrv_stStatusRegisters.HS_OL_STAT.RegistersData = 0;
	CtrlRe1[0] = SBCdrv_stStatusRegisters.HS_OL_STAT.RegistersAddr;
	CtrlRe1[1] = SBCdrv_stStatusRegisters.HS_OL_STAT.RegistersData;
	TLE9262Drv_R_Sta_Regs(CtrlRe1,u8Rec);
	 SBCdrv_stStatusRegisters.HS_OL_STAT.RegistersData = u8Rec[1];
}
/******************************************************************************/
/*
*Function Name :void TLE9262Drv_WD_DisableInStopMode_Control()

* Description   :call in normal,and next change to stop
* Date          :	2018.04.11	
*/
/******************************************************************************/
static void TLE9262Drv_WD_DisableInStopMode_Control(void)
{	
	//Step1 Set bit WD_STM_EN_1 =1
	TLE9262Drv_WK_CTRL_1_WD_STM_EN_1_CFG(SBCdrv_tenWatchdogSTM_EN1ModeType_Deactive);
	CtrlRe1[0] = SBCdrv_stControlRegisters.WK_CTRL_1.RegistersAddr;
	CtrlRe1[1] = SBCdrv_stControlRegisters.WK_CTRL_1.RegistersData;
	TLE9262Drv_W_Ctl_Regs(CtrlRe1,u8Rec);
	
	//Step 2 Set bit WD_STM_EN_0 =1 and Trigger
	SBCdrv_stControlRegisters.WD_CTRL.RegistersData |=(0X01<<6);//write 1
	TLE9262Drv_WDCheckSum_Cfg();
	CtrlRe1[0] = SBCdrv_stControlRegisters.WD_CTRL.RegistersAddr;
	CtrlRe1[1] = SBCdrv_stControlRegisters.WD_CTRL.RegistersData;
	TLE9262Drv_W_Ctl_Regs(CtrlRe1,u8Rec);

/*	
	//step 3 Set bit WD_STM_EN_0 =1 and Trigger
	SBCdrv_stControlRegisters.WD_CTRL.RegistersData |=(0X01<<6);
	TLE9262Drv_WDCheckSum_Cfg();
	CtrlRe1[0] = SBCdrv_stControlRegisters.WD_CTRL.RegistersAddr;
	CtrlRe1[1] = SBCdrv_stControlRegisters.WD_CTRL.RegistersData;
	TLE9262Drv_W_Ctl_Regs(CtrlRe1,u8Rec);
*/	
}




/******************************************************************************/
/*
*Function Name :void TLE9262Drv_WD_Init2Normal_Control()

* Description   :
* Date          :	2018.04.11	
*/
/******************************************************************************/
static void TLE9262Drv_WD_Init2Normal_Control(void)
{
	/*WatchDog is active in stop mode
	Time-out watchdog
	watchdog start with long open window after CAN/LIN Wake
	Watch timer 200ms
	*/
	SBCdrv_stControlRegisters.WD_CTRL.RegistersData &=(uint8)~(0x01<<6) ;//only config in normal mode and go to stop
	
	SBCdrv_stControlRegisters.WD_CTRL.RegistersData &=(uint8)~(0x01<<5)  ;
	SBCdrv_stControlRegisters.WD_CTRL.RegistersData |=(uint8)((uint8)TimeoutMode<<5);
	//Watchdog works as a Time-Out watchdog
	
	SBCdrv_stControlRegisters.WD_CTRL.RegistersData &=(uint8)~(0x01<<4)  ;
	SBCdrv_stControlRegisters.WD_CTRL.RegistersData |=(uint8)((uint8)LongOpenwindowWake<<4);
	//Watchdog starts with a long open window after CAN/LINx Wake

	SBCdrv_stControlRegisters.WD_CTRL.RegistersData &=(uint8)~(0x07 <<0);
	SBCdrv_stControlRegisters.WD_CTRL.RegistersData |=(uint8)((uint8)TimerPeriod_1000ms<<0);
	//Watchdog starts with a long open window after CAN/LINx Wake
	TLE9262Drv_WDCheckSum_Cfg();

	/**********************writing into register************** */
	CtrlRe1[0] = SBCdrv_stControlRegisters.WD_CTRL.RegistersAddr;
	CtrlRe1[1] = SBCdrv_stControlRegisters.WD_CTRL.RegistersData;

	TLE9262Drv_W_Ctl_Regs(CtrlRe1,u8Rec);

	/*read back to check if okay*/
	TLE9262Drv_R_Ctl_Regs(CtrlRe1,u8Rec);
	if(u8Rec[1]!=CtrlRe1[1])
	{
		TLE9262Drv_u16ErrcodeSetbit(SBC_nu16NormalModeConfigWDDisableInstopModeFail);
	}
	else
	{
		TLE9262Drv_u16ErrcodeClcbit(SBC_nu16NormalModeConfigWDDisableInstopModeFail);
	}

}



/******************************************************************************/
/*
*Function Name :void TLE9262Drv_M_S_CTRL_Init2Normal_Control()

* Description   :
* Date          :	2018.04.11	
*/
/******************************************************************************/
static void TLE9262Drv_M_S_CTRL_Init2Normal_Control(void)
{
	/*
	7-6.SBC Normal Mode
	5.VCC3 OFF
	4-3.VCC2 always on (except in SBC Fail-Safe Mode)
	2.unchanged with VCC1 OV
		INT Pin			HW_CTRL_CFG	VCC1_OV_RST	SBC Mode Entry
		any value 		x 				0 				unchanged
		External pull-up 	1 				1 				SBC Restart Mode
		No ext. pull-up 	1 				1 				SBC Fail-Safe Mode
		External pull-up 	0 				1 				SBC Restart Mode
		No ext. pull-up 	0 				1 				SBC Fail-Safe Mode
	1.VCC1 Reset Threshold Control  Vrt2
	*/
	TLE9262Drv_M_S_CTRL_Mode_Cfg(SBCdrv_Normal_Mode);
	TLE9262Drv_M_S_CTRL_VCC3Mode_Cfg(Vcc3Off );
	TLE9262Drv_M_S_CTRL_VCC2Mode_Cfg(Vcc2AlwaysOn); //power for can
	TLE9262Drv_M_S_CTRL_VCC1_OV_Cfg(Vcc1OvNoResrt);
	TLE9262Drv_M_S_CTRL_VCC1_RT_Cfg(Vrt2Selected);  

	/**********************writing into register************** */
	CtrlRe1[0] = SBCdrv_stControlRegisters.M_S_CTRL.RegistersAddr;
	CtrlRe1[1] = SBCdrv_stControlRegisters.M_S_CTRL.RegistersData;
	TLE9262Drv_W_Ctl_Regs(CtrlRe1,u8Rec);

	/*read back to check if okay*/
	TLE9262Drv_R_Ctl_Regs(CtrlRe1,u8Rec);
	if(u8Rec[1]!=CtrlRe1[1])
	{
		TLE9262Drv_u16ErrcodeSetbit(SBC_nu16NormalModeConfigM_S_CTRLFail);
	}
	else
	{
		TLE9262Drv_u16ErrcodeClcbit(SBC_nu16NormalModeConfigM_S_CTRLFail);
	}
}



/******************************************************************************/
/*
*Function Name :void TLE9262Drv_HW_CTRL_Init2Normal_Control()

* Description   :
* Date          :	2018.04.11	
*/
/******************************************************************************/
static void TLE9262Drv_HW_CTRL_Init2Normal_Control(void)
{
	/*
	7.VCC3 OUT Same with VCC1  
	6.RO will be triggered (pulled low) during a Soft Reset on SBC
	5.FOx not activated by software an be activated by defined failures
	4.VCC3 will stay enabled even below VS_UV
	3.VCC3 in load sharing operation with VCC1
	1.
	0.Depending on hardware configuration, SBC Restart or Fail-Safe Mode is reached after the 2. watchdog trigger failure
	-----Restart Mode(External pull-up  On INT PIN)
	-----Fail-Safe Mode Mode(No External pull-up  On INT PIN)
	*/
	TLE9262Drv_HW_CTRL_VCC3_V_Cfg(SameWithVCC1);
	TLE9262Drv_HW_CTRL_Soft_Reset_RO_Cfg(RoTrigeer);
	TLE9262Drv_HW_CTRL_FailureOutputActivation_Cfg(ActivatedByDefinedFailures);
	TLE9262Drv_HW_CTRL_VCC3_VS_UV_OFF_Cfg(SBCdrv_tenVCC3_VS_UV_OFF_CFGType_Stay_Enabled);
	TLE9262Drv_HW_CTRL_VCC3_LS_Cfg(SBCdrv_tenVCC3_LS_CFGType_ShareingOperationWithVCC1);
	TLE9262Drv_HW_CTRL_VCC3_LS_STP_ON_Cfg(SBCdrv_tenVCC3_LS_STP_ON_CFGType_Disable);
	TLE9262Drv_HW_CTRL_CFG_Cfg(SBCdrv_tenHW_CTRL_CFGModeType_ReserAfter2WatchDogFail);

	/**********************writing into register************** */
	CtrlRe1[0] = SBCdrv_stControlRegisters.HW_CTRL.RegistersAddr;
	CtrlRe1[1] = SBCdrv_stControlRegisters.HW_CTRL.RegistersData;
	TLE9262Drv_W_Ctl_Regs(CtrlRe1,u8Rec);

	/*read back to check if okay*/
	TLE9262Drv_R_Ctl_Regs(CtrlRe1,u8Rec);
	if(u8Rec[1]!=CtrlRe1[1])
	{
		TLE9262Drv_u16ErrcodeSetbit(SBC_nu16NormalModeConfigHW_CTRLFail);
	}
	else
	{
		TLE9262Drv_u16ErrcodeClcbit(SBC_nu16NormalModeConfigHW_CTRLFail);
	}
	
}



/******************************************************************************/
/*
*Function Name :void TLE9262Drv_BUS_CTRL_1_Init2Normal_Control()

* Description   :
* Date          :	2018.04.11	
*/
/******************************************************************************/
static void TLE9262Drv_BUS_CTRL_1_Init2Normal_Control(void)
{
	/*
	7.Slope control mechanism active
	6.LIN Normal-Mode is activated
	5.TXD Time-Out feature disabled
	4-3.LIN1-Module Mode:-------LIN1 Normal Mode
		00B , LIN1 OFF
		01B , LIN1 is wake capable
		10B , LIN1 Receive Only Mode
		11B , LIN1 Normal Mode
	1-0.HS-CAN Module Modes-----CAN Normal Mode
		00B , CAN OFF
		01B , CAN is wake capable
		10B , CAN Receive Only Mode
		11B , CAN Normal Mode
	*/
	TLE9262Drv_BUS_CTRL_1_LinFlash_Cfg(SBCdrv_tenLINxFlashProgrammingModeType_Active);
	TLE9262Drv_BUS_CTRL_1_LIN_LSM_Cfg(SBCdrv_tenLINxLSMType_Normal);
	TLE9262Drv_BUS_CTRL_1_LIN_TXD_TO_Cfg(SBCdrv_tenLINTXDTimeOutType_Disable);
	TLE9262Drv_BUS_CTRL_1_LIN1_Module_Cfg(SBCdrv_tenLINModuleModeType_Normal);
	TLE9262Drv_BUS_CTRL_1_HSCAN_Module_Cfg(SBCdrv_tenHSCANModuleModeType_Normal);
	
	
	/**********************writing into register************** */
	CtrlRe1[0] = SBCdrv_stControlRegisters.BUS_CTRL_1.RegistersAddr;
	CtrlRe1[1] = SBCdrv_stControlRegisters.BUS_CTRL_1.RegistersData;
	TLE9262Drv_W_Ctl_Regs(CtrlRe1,u8Rec);
	
	/*read back to check if okay*/
	TLE9262Drv_R_Ctl_Regs(CtrlRe1,u8Rec);
	if(u8Rec[1]!=CtrlRe1[1])
	{
		TLE9262Drv_u16ErrcodeSetbit(SBC_nu16NormalModeConfigBUS_CTRL_1Fail);
	}
	else
	{
		TLE9262Drv_u16ErrcodeClcbit(SBC_nu16NormalModeConfigBUS_CTRL_1Fail);
	}
	
}



/******************************************************************************/
/*
*Function Name :void TLE9262Drv_BUS_CTRL_2_Init2Normal_Control()

* Description   :
* Date          :	2018.04.11	
*/
/******************************************************************************/
static void TLE9262Drv_BUS_CTRL_2_Init2Normal_Control(void)
{
	/*
	I_PEAK_TH VCC1 Active Peak Threshold Selection
	*/
	TLE9262Drv_BUS_CTRL_2_I_PEAK_TH_Cfg(SBCdrv_tenPeakThresholdModeType_Higher);
	
	
	/**********************writing into register************** */
	CtrlRe1[0] = SBCdrv_stControlRegisters.BUS_CTRL_2.RegistersAddr;
	CtrlRe1[1] = SBCdrv_stControlRegisters.BUS_CTRL_2.RegistersData;
	TLE9262Drv_W_Ctl_Regs(CtrlRe1,u8Rec);
	
	/*read back to check if okay*/
	TLE9262Drv_R_Ctl_Regs(CtrlRe1,u8Rec);
	if(u8Rec[1]!=CtrlRe1[1])
	{
		TLE9262Drv_u16ErrcodeSetbit(SBC_nu16NormalModeConfigBUS_CTRL_2Fail);
	}
	else
	{
		TLE9262Drv_u16ErrcodeClcbit(SBC_nu16NormalModeConfigBUS_CTRL_2Fail);
	}
	
}




/******************************************************************************/
/*
*Function Name :void TLE9262Drv_HS_CTRL1_Init2Normal_Control()

* Description   :
* Date          :	2018.04.11	
*/
/******************************************************************************/
static void TLE9262Drv_HS_CTRL1_NormalMode_Control(void)
{

	uint8 u8HS1=0,u8HS2=0;
	u8HS1 = TLE9262Drv_vGetHS1_ConfigStatus();
	u8HS2 = TLE9262Drv_vGetHS2_ConfigStatus();
	
	TLE9262Drv_HS_CTRL1_HS1_CFG((SBCdrv_tenHS_ConfigurationModeType)u8HS1);
	TLE9262Drv_HS_CTRL1_HS2_CFG((SBCdrv_tenHS_ConfigurationModeType)u8HS2);
	
	
	/**********************writing into register************** */
	CtrlRe1[0] = SBCdrv_stControlRegisters.HS_CTRL_1.RegistersAddr;
	CtrlRe1[1] = SBCdrv_stControlRegisters.HS_CTRL_1.RegistersData;
	TLE9262Drv_W_Ctl_Regs(CtrlRe1,u8Rec);
	
	/*read back to check if okay*/
	TLE9262Drv_R_Ctl_Regs(CtrlRe1,u8Rec);
	if(u8Rec[1]!=CtrlRe1[1])
	{
		TLE9262Drv_u16ErrcodeSetbit(SBC_nu16NormalModeConfigHS_CTRL1_CTRLFail);
	}
	else
	{
		TLE9262Drv_u16ErrcodeClcbit(SBC_nu16NormalModeConfigHS_CTRL1_CTRLFail);
	}
	
}


/******************************************************************************/
/*
*Function Name :void TLE9262Drv_HS_CTRL1_Init2Normal_Control()

* Description   :
* Date          :	2018.04.11	
*/
/******************************************************************************/
static void TLE9262Drv_HS_CTRL1_OFF(void)
{

	TLE9262Drv_HS_CTRL1_HS1_CFG(SBCdrv_tenHS_ConfigurationModeType_OFF);
	TLE9262Drv_HS_CTRL1_HS2_CFG(SBCdrv_tenHS_ConfigurationModeType_OFF);
	
	
	/**********************writing into register************** */
	CtrlRe1[0] = SBCdrv_stControlRegisters.HS_CTRL_1.RegistersAddr;
	CtrlRe1[1] = SBCdrv_stControlRegisters.HS_CTRL_1.RegistersData;
	TLE9262Drv_W_Ctl_Regs(CtrlRe1,u8Rec);
	
	/*read back to check if okay*/
	TLE9262Drv_R_Ctl_Regs(CtrlRe1,u8Rec);
	if(u8Rec[1]!=CtrlRe1[1])
	{
		TLE9262Drv_u16ErrcodeSetbit(SBC_nu16NormalModeConfigHS_CTRL1_CTRLFail);
	}
	else
	{
		TLE9262Drv_u16ErrcodeClcbit(SBC_nu16NormalModeConfigHS_CTRL1_CTRLFail);
	}
	
}



/******************************************************************************/
/*
*Function Name :void TLE9262Drv_HS_CTRL2_OFF()

* Description   :
* Date          :	2018.04.11	
*/
/******************************************************************************/
static void TLE9262Drv_HS_CTRL2_OFF(void)
{

	TLE9262Drv_HS_CTRL2_HS3_CFG(SBCdrv_tenHS_ConfigurationModeType_OFF);
	TLE9262Drv_HS_CTRL2_HS4_CFG(SBCdrv_tenHS_ConfigurationModeType_OFF);
	
	
	/**********************writing into register************** */
	CtrlRe1[0] = SBCdrv_stControlRegisters.HS_CTRL_2.RegistersAddr;
	CtrlRe1[1] = SBCdrv_stControlRegisters.HS_CTRL_2.RegistersData;
	TLE9262Drv_W_Ctl_Regs(CtrlRe1,u8Rec);
	
	/*read back to check if okay*/
	TLE9262Drv_R_Ctl_Regs(CtrlRe1,u8Rec);
	if(u8Rec[1]!=CtrlRe1[1])
	{
		TLE9262Drv_u16ErrcodeSetbit(SBC_nu16NormalModeConfigHS_CTRL2_CTRLFail);
	}
	else
	{
		TLE9262Drv_u16ErrcodeClcbit(SBC_nu16NormalModeConfigHS_CTRL2_CTRLFail);
	}
	
}
/******************************************************************************/
/*
*Function Name :void TLE9262Drv_HS_CTRL1_Init2Normal_Control()

* Description   :
* Date          :	2018.04.11	
*/
/******************************************************************************/
#if 0
static void TLE9262Drv_HS_CTRL2_NormalMode_Control(void)
{

	uint8 u8HS3=0,u8HS4=0;
	u8HS3 = TLE9262Drv_vGetHS3_ConfigStatus();
	u8HS4 = TLE9262Drv_vGetHS4_ConfigStatus();
	
	TLE9262Drv_HS_CTRL2_HS3_CFG((SBCdrv_tenHS_ConfigurationModeType)u8HS3);
	TLE9262Drv_HS_CTRL2_HS4_CFG((SBCdrv_tenHS_ConfigurationModeType)u8HS4);
	
	
	/**********************writing into register************** */
	CtrlRe1[0] = SBCdrv_stControlRegisters.HS_CTRL_2.RegistersAddr;
	CtrlRe1[1] = SBCdrv_stControlRegisters.HS_CTRL_2.RegistersData;
	TLE9262Drv_W_Ctl_Regs(CtrlRe1,u8Rec);
	
	/*read back to check if okay*/
	TLE9262Drv_R_Ctl_Regs(CtrlRe1,u8Rec);
	if(u8Rec[1]!=CtrlRe1[1])
	{
		TLE9262Drv_u16ErrcodeSetbit(SBC_nu16NormalModeConfigHS_CTRL2_CTRLFail);
	}
	else
	{
		TLE9262Drv_u16ErrcodeClcbit(SBC_nu16NormalModeConfigHS_CTRL2_CTRLFail);
	}
}	
#endif




/******************************************************************************/
/*
*Function Name :void TLE9262Drv_SW_SD_Init2Normal_Control()

* Description   :
* Date          :	2018.04.11	
*/
/******************************************************************************/
static void TLE9262Drv_SW_SD_Init2Normal_Control(void)
{
	/*
	6.shutdown disabled in case of VSHS OV
	5.shutdown disabled in case of VSHS UV
	4.Switch recovery is disabled
	*/
	
	TLE9262Drv_SW_SD_CTRL_HS_OV_SD_EN_CFG(SBCdrv_tenHS_OV_UV_SD_ENModeType_Disable);
	TLE9262Drv_SW_SD_CTRL_HS_UV_SD_EN_CFG(SBCdrv_tenHS_OV_UV_SD_ENModeType_Disable);
	TLE9262Drv_SW_SD_CTRL_HS_OV_UV_REC_CFG(SBCdrv_tenHS_OV_UV_RECModeType_Disable);

	/**********************writing into register************** */
	CtrlRe1[0] = SBCdrv_stControlRegisters.SW_SD_CTRL.RegistersAddr;
	CtrlRe1[1] = SBCdrv_stControlRegisters.SW_SD_CTRL.RegistersData;
	TLE9262Drv_W_Ctl_Regs(CtrlRe1,u8Rec);
	
	/*read back to check if okay*/
	TLE9262Drv_R_Ctl_Regs(CtrlRe1,u8Rec);
	if(u8Rec[1]!=CtrlRe1[1])
	{
		TLE9262Drv_u16ErrcodeSetbit(SBC_nu16NormalModeConfigSW_SD_CTRLFail);
	}
	else
	{
		TLE9262Drv_u16ErrcodeClcbit(SBC_nu16NormalModeConfigSW_SD_CTRLFail);
	}
	
}



/******************************************************************************/
/*
*Function Name :void TLE9262Drv_HW_CTRL_Normal2Stop_Control()

* Description   :
* Date          :	2018.04.11	
*/
/******************************************************************************/
static void TLE9262Drv_HW_CTRL_Normal2Stop_Control(void)
{
	TLE9262Drv_HW_CTRL_Init2Normal_Control();
}



/******************************************************************************/
/*
*Function Name :void TLE9262Drv_HW_CTRL_Normal2Sleep_Control()

* Description   :
* Date          :	2018.04.11	
*/
/******************************************************************************/
static void TLE9262Drv_HW_CTRL_Normal2Sleep_Control(void)
{
	TLE9262Drv_HW_CTRL_Init2Normal_Control();
}
/******************************************************************************/
/*
*Function Name :void TLE9262Drv_BUS_CTRL_1_Normal2Stop_Control()

* Description   :
* Date          :	2018.04.11	
*/
/******************************************************************************/
static void TLE9262Drv_BUS_CTRL_1_Normal2Stop_Control(void)
{
	/*
	7.Slope control mechanism active
	6.LIN Normal-Mode is activated
	5.TXD Time-Out feature disabled
	4-3.LIN1-Module Mode:-------LIN1 is wake capable
		00B , LIN1 OFF
		01B , LIN1 is wake capable
		10B , LIN1 Receive Only Mode
		11B , LIN1 Normal Mode
	1-0.HS-CAN Module Modes-----CAN is wake capable
		00B , CAN OFF
		01B , CAN is wake capable
		10B , CAN Receive Only Mode
		11B , CAN Normal Mode
	*/
	TLE9262Drv_BUS_CTRL_1_LinFlash_Cfg(SBCdrv_tenLINxFlashProgrammingModeType_Active);
	TLE9262Drv_BUS_CTRL_1_LIN_LSM_Cfg(SBCdrv_tenLINxLSMType_Normal);
	TLE9262Drv_BUS_CTRL_1_LIN_TXD_TO_Cfg(SBCdrv_tenLINTXDTimeOutType_Disable);
	TLE9262Drv_BUS_CTRL_1_LIN1_Module_Cfg(SBCdrv_tenLINModuleModeType_WakeCapable);
	TLE9262Drv_BUS_CTRL_1_HSCAN_Module_Cfg(SBCdrv_tenHSCANModuleModeType_WakeCapable);
	
	
	/**********************writing into register************** */
	CtrlRe1[0] = SBCdrv_stControlRegisters.BUS_CTRL_1.RegistersAddr;
	CtrlRe1[1] = SBCdrv_stControlRegisters.BUS_CTRL_1.RegistersData;
	TLE9262Drv_W_Ctl_Regs(CtrlRe1,u8Rec);
	
	/*read back to check if okay*/
	TLE9262Drv_R_Ctl_Regs(CtrlRe1,u8Rec);
	if(u8Rec[1]!=CtrlRe1[1])
	{
		TLE9262Drv_u16ErrcodeSetbit(SBC_nu16NormalModeConfigBUS_CTRL_1Fail);
	}
	else
	{
		TLE9262Drv_u16ErrcodeClcbit(SBC_nu16NormalModeConfigBUS_CTRL_1Fail);
	}
	
}

/******************************************************************************/
/*
*Function Name :void TLE9262Drv_BUS_CTRL_1_Normal2Stop_Control()

* Description   :
* Date          :	2018.04.11	
*/
/******************************************************************************/
static void TLE9262Drv_BUS_CTRL_1_OFF_Control(void)
{
	/*
	7.Slope control mechanism active
	6.LIN Normal-Mode is activated
	5.TXD Time-Out feature disabled
	4-3.LIN1-Module Mode:-------LIN1 is wake capable
		00B , LIN1 OFF
		01B , LIN1 is wake capable
		10B , LIN1 Receive Only Mode
		11B , LIN1 Normal Mode
	1-0.HS-CAN Module Modes-----CAN is wake capable
		00B , CAN OFF
		01B , CAN is wake capable
		10B , CAN Receive Only Mode
		11B , CAN Normal Mode
	*/
	TLE9262Drv_BUS_CTRL_1_LinFlash_Cfg(SBCdrv_tenLINxFlashProgrammingModeType_Active);
	TLE9262Drv_BUS_CTRL_1_LIN_LSM_Cfg(SBCdrv_tenLINxLSMType_Normal);
	TLE9262Drv_BUS_CTRL_1_LIN_TXD_TO_Cfg(SBCdrv_tenLINTXDTimeOutType_Disable);
	TLE9262Drv_BUS_CTRL_1_LIN1_Module_Cfg(SBCdrv_tenLINModuleModeType_OFF);
	TLE9262Drv_BUS_CTRL_1_HSCAN_Module_Cfg(SBCdrv_tenHSCANModuleModeType_OFF);
	
	
	/**********************writing into register************** */
	CtrlRe1[0] = SBCdrv_stControlRegisters.BUS_CTRL_1.RegistersAddr;
	CtrlRe1[1] = SBCdrv_stControlRegisters.BUS_CTRL_1.RegistersData;
	TLE9262Drv_W_Ctl_Regs(CtrlRe1,u8Rec);
	
	/*read back to check if okay*/
	TLE9262Drv_R_Ctl_Regs(CtrlRe1,u8Rec);
	if(u8Rec[1]!=CtrlRe1[1])
	{
		TLE9262Drv_u16ErrcodeSetbit(SBC_nu16NormalModeConfigBUS_CTRL_1Fail);
	}
	else
	{
		TLE9262Drv_u16ErrcodeClcbit(SBC_nu16NormalModeConfigBUS_CTRL_1Fail);
	}
	
}

/******************************************************************************/
/*
*Function Name :void TLE9262Drv_BUS_CTRL_1_Standby_Control()

* Description   :
* Date          :	2018.04.11	
*/
/******************************************************************************/
static void TLE9262Drv_BUS_CTRL_1_Standby_Control(void)
{
	/*
	7.Slope control mechanism active
	6.LIN Normal-Mode is activated
	5.TXD Time-Out feature disabled
	4-3.LIN1-Module Mode:-------LIN1 is wake capable
		00B , LIN1 OFF
		01B , LIN1 is wake capable
		10B , LIN1 Receive Only Mode
		11B , LIN1 Normal Mode
	1-0.HS-CAN Module Modes-----CAN is wake capable
		00B , CAN OFF
		01B , CAN is wake capable
		10B , CAN Receive Only Mode
		11B , CAN Normal Mode
	*/
	TLE9262Drv_BUS_CTRL_1_LinFlash_Cfg(SBCdrv_tenLINxFlashProgrammingModeType_Active);
	TLE9262Drv_BUS_CTRL_1_LIN_LSM_Cfg(SBCdrv_tenLINxLSMType_Normal);
	TLE9262Drv_BUS_CTRL_1_LIN_TXD_TO_Cfg(SBCdrv_tenLINTXDTimeOutType_Disable);
	TLE9262Drv_BUS_CTRL_1_LIN1_Module_Cfg(SBCdrv_tenLINModuleModeType_OFF);
	TLE9262Drv_BUS_CTRL_1_HSCAN_Module_Cfg(SBCdrv_tenLINModuleModeType_OFF);
	
	
	/**********************writing into register************** */
	CtrlRe1[0] = SBCdrv_stControlRegisters.BUS_CTRL_1.RegistersAddr;
	CtrlRe1[1] = SBCdrv_stControlRegisters.BUS_CTRL_1.RegistersData;
	TLE9262Drv_W_Ctl_Regs(CtrlRe1,u8Rec);
	
	/*read back to check if okay*/
	TLE9262Drv_R_Ctl_Regs(CtrlRe1,u8Rec);
	if(u8Rec[1]!=CtrlRe1[1])
	{
		TLE9262Drv_u16ErrcodeSetbit(SBC_nu16NormalModeConfigBUS_CTRL_1Fail);
	}
	else
	{
		TLE9262Drv_u16ErrcodeClcbit(SBC_nu16NormalModeConfigBUS_CTRL_1Fail);
	}
	
}


/******************************************************************************/
/*
*Function Name :void TLE9262Drv_BUS_CTRL_1_Normal2Sleep_Control()

* Description   :
* Date          :	2018.04.11	
*/
/******************************************************************************/
static void TLE9262Drv_BUS_CTRL_1_Normal2Sleep_Control(void)
{
	TLE9262Drv_BUS_CTRL_1_Normal2Stop_Control();
}



/******************************************************************************/
/*
*Function Name :void TLE9262Drv_WK_CTRL_1_Normal2Stop_Control()

* Description   :
* Date          :	2018.04.11	
*/
/******************************************************************************/
static void TLE9262Drv_WK_CTRL_1_Normal2Stop_Control(void)
{
	/*
	7.Timer2 Wake Source Control  ----Timer2 wake disabled
	6.Timer1 Wake Source Control-----Timer1 wake disabled
	2.Watchdog Deactivation during Stop Mode----0B , Watchdog is active in Stop Mode   ///set to 1 need speical sqe
	*/
	TLE9262Drv_WK_CTRL_1_TIMER2_WK_EN_CFG(SBCdrv_tenTmer2WakeSourceEnModeType_Disable);
	TLE9262Drv_WK_CTRL_1_TIMER1_WK_EN_CFG(SBCdrv_tenTmer1WakeSourceEnModeType_Disable);
	
	TLE9262Drv_WK_CTRL_1_WD_STM_EN_1_CFG(SBCdrv_tenWatchdogSTM_EN1ModeType_Active);
	
	/**********************writing into register************** */
	CtrlRe1[0] = SBCdrv_stControlRegisters.WK_CTRL_1.RegistersAddr;
	CtrlRe1[1] = SBCdrv_stControlRegisters.WK_CTRL_1.RegistersData;
	TLE9262Drv_W_Ctl_Regs(CtrlRe1,u8Rec);
	
	/*read back to check if okay*/
	TLE9262Drv_R_Ctl_Regs(CtrlRe1,u8Rec);
	if(u8Rec[1]!=CtrlRe1[1])
	{
		TLE9262Drv_u16ErrcodeSetbit(SBC_nu16NormalModeConfigWK_CTRL_1Fail);
	}
	else
	{
		TLE9262Drv_u16ErrcodeClcbit(SBC_nu16NormalModeConfigWK_CTRL_1Fail);
	}
	
}



/******************************************************************************/
/*
*Function Name :void TLE9262Drv_WK_CTRL_1_Normal2Sleep_Control()

* Description   :
* Date          :	2018.04.11	
*/
/******************************************************************************/
static void TLE9262Drv_WK_CTRL_1_Normal2Sleep_Control(void)
{
	TLE9262Drv_WK_CTRL_1_Normal2Stop_Control();
}

/******************************************************************************/
/*
*Function Name :void TLE9262Drv_WK_CTRL_2_Normal2Stop_Control()

* Description   :
* Date          :	2018.04.11	
*/
/******************************************************************************/
static void TLE9262Drv_WK_CTRL_2_Normal2Stop_Control(void)
{
	/*
	7.INT_GLOBAL---Only wake sources trigger INT (default)
	5.WK / Measurement selection ---WK functionality enabled for WK1 and WK2
	2.WK3 Wake Source Control-----WK3 wake disabled
	1.WK2 Wake Source Control-----WK2 wake disabled
	0.WK1 Wake Source Control-----WK1 is enabled as a wake source
	*/
	TLE9262Drv_WK_CTRL_2_INT_GLOBAL_CFG(SBCdrv_tenGlobalInterruptConfigurationModeType_INT);
	TLE9262Drv_WK_CTRL_2_WK_MEAS_CFG(SBCdrv_tenWK_MEASModeType_EnabledWK_Function);
	TLE9262Drv_WK_CTRL_2_WK3_EN_CFG(SBCdrv_tenWK3_ENModeType_Enabled);
	TLE9262Drv_WK_CTRL_2_WK2_EN_CFG(SBCdrv_tenWK2_ENModeType_Disabled);
	TLE9262Drv_WK_CTRL_2_WK1_EN_CFG(SBCdrv_tenWK1_ENModeType_Disabled);
	
	
	/**********************writing into register************** */
	CtrlRe1[0] = SBCdrv_stControlRegisters.WK_CTRL_2.RegistersAddr;
	CtrlRe1[1] = SBCdrv_stControlRegisters.WK_CTRL_2.RegistersData;
	TLE9262Drv_W_Ctl_Regs(CtrlRe1,u8Rec);
	
	/*read back to check if okay*/
	TLE9262Drv_R_Ctl_Regs(CtrlRe1,u8Rec);
	if(u8Rec[1]!=CtrlRe1[1])
	{
		TLE9262Drv_u16ErrcodeSetbit(SBC_nu16NormalModeConfigWK_CTRL_1Fail);
	}
	else
	{
		TLE9262Drv_u16ErrcodeClcbit(SBC_nu16NormalModeConfigWK_CTRL_1Fail);
	}
	
}



/******************************************************************************/
/*
*Function Name :void TLE9262Drv_WK_CTRL_2_Normal2Sleep_Control()

* Description   :
* Date          :	2018.04.11	
*/
/******************************************************************************/
static void TLE9262Drv_WK_CTRL_2_Normal2Sleep_Control(void)
{
	TLE9262Drv_WK_CTRL_2_Normal2Stop_Control();
}
/******************************************************************************/
/*
*Function Name :void TLE9262Drv_M_S_CTRL_Normal2Stop_Control()

* Description   :
* Date          :	2018.04.11	
*/
/******************************************************************************/
static void TLE9262Drv_M_S_CTRL_Normal2Stop_Control(void)
{
	TLE9262Drv_M_S_CTRL_Mode_Cfg(SBCdrv_Stop_Mode);
	TLE9262Drv_M_S_CTRL_VCC1_OV_Cfg(Vcc1OvNoResrt);
	TLE9262Drv_M_S_CTRL_VCC1_RT_Cfg(Vrt2Selected);   
	TLE9262Drv_M_S_CTRL_VCC2Mode_Cfg(Vcc2AlwaysOn); //power for can
	TLE9262Drv_M_S_CTRL_VCC3Mode_Cfg(Vcc3Off );

	/**********************writing into register************** */
	CtrlRe1[0] = SBCdrv_stControlRegisters.M_S_CTRL.RegistersAddr;
	CtrlRe1[1] = SBCdrv_stControlRegisters.M_S_CTRL.RegistersData;
	TLE9262Drv_W_Ctl_Regs(CtrlRe1,u8Rec);
	
	/*read back to check if okay*/
	TLE9262Drv_R_Ctl_Regs(CtrlRe1,u8Rec);
	if(u8Rec[1]!=CtrlRe1[1])
	{
		TLE9262Drv_u16ErrcodeSetbit(SBC_nu16NormalModeConfigM_S_CTRLFail);
	}
	else
	{
		TLE9262Drv_u16ErrcodeClcbit(SBC_nu16NormalModeConfigM_S_CTRLFail);
	}
}



/******************************************************************************/
/*
*Function Name :void TLE9262Drv_M_S_CTRL_Normal2Stop_Control()

* Description   :
* Date          :	2018.04.11	
*/
/******************************************************************************/
static void TLE9262Drv_M_S_CTRL_Normal2SLeep_Control(void)
{
	TLE9262Drv_M_S_CTRL_Mode_Cfg(SBCdrv_Sleep_Mode);
	TLE9262Drv_M_S_CTRL_VCC1_OV_Cfg(Vcc1OvNoResrt);
	TLE9262Drv_M_S_CTRL_VCC1_RT_Cfg(Vrt2Selected);   
	TLE9262Drv_M_S_CTRL_VCC2Mode_Cfg(Vcc2AlwaysOn); //power for can
	TLE9262Drv_M_S_CTRL_VCC3Mode_Cfg(Vcc3Off );

	/**********************writing into register************** */
	CtrlRe1[0] = SBCdrv_stControlRegisters.M_S_CTRL.RegistersAddr;
	CtrlRe1[1] = SBCdrv_stControlRegisters.M_S_CTRL.RegistersData;
	TLE9262Drv_W_Ctl_Regs(CtrlRe1,u8Rec);
	
	/*read back to check if okay*/
	TLE9262Drv_R_Ctl_Regs(CtrlRe1,u8Rec);
	if(u8Rec[1]!=CtrlRe1[1])
	{
		TLE9262Drv_u16ErrcodeSetbit(SBC_nu16NormalModeConfigM_S_CTRLFail);
	}
	else
	{
		TLE9262Drv_u16ErrcodeClcbit(SBC_nu16NormalModeConfigM_S_CTRLFail);
	}
}
/******************************************************************************/
/*
*Function Name :void TLE9262Drv_M_S_CTRL_ResetMode()

* Description   :
* Date          :	2018.04.11	
*/
/******************************************************************************/
static void TLE9262Drv_M_S_CTRL_ResetMode(void)
{
	TLE9262Drv_M_S_CTRL_Mode_Cfg(SBCdrv_Reset);
	TLE9262Drv_M_S_CTRL_VCC1_OV_Cfg(Vcc1OvNoResrt);
	TLE9262Drv_M_S_CTRL_VCC1_RT_Cfg(Vrt2Selected);   
	TLE9262Drv_M_S_CTRL_VCC2Mode_Cfg(Vcc2AlwaysOn); //power for can
	TLE9262Drv_M_S_CTRL_VCC3Mode_Cfg(Vcc3Off );

	/**********************writing into register************** */
	CtrlRe1[0] = SBCdrv_stControlRegisters.M_S_CTRL.RegistersAddr;
	CtrlRe1[1] = SBCdrv_stControlRegisters.M_S_CTRL.RegistersData;
	TLE9262Drv_W_Ctl_Regs(CtrlRe1,u8Rec);
	
	/*read back to check if okay*/
	TLE9262Drv_R_Ctl_Regs(CtrlRe1,u8Rec);
	if(u8Rec[1]!=CtrlRe1[1])
	{
		TLE9262Drv_u16ErrcodeSetbit(SBC_nu16NormalModeConfigM_S_CTRLFail);
	}
	else
	{
		TLE9262Drv_u16ErrcodeClcbit(SBC_nu16NormalModeConfigM_S_CTRLFail);
	}
}
/******************************************************************************/
/*
*Function Name :void TLE9262Drv_vInit2NormalMode()

* Description   :
* Date          :	2018.04.11	
*/
/******************************************************************************/
void  TLE9262Drv_vInitMode(void)
{
	TLE9262Drv_WD_Init2Normal_Control();
}




/******************************************************************************/
/*
*Function Name :void TLE9262Drv_vInit2NormalMode()

* Description   :
* Date          :	2018.04.11	
*/
/******************************************************************************/
void  TLE9262Drv_vInit2NormalMode(void)
{
	TLE9262Drv_M_S_CTRL_Init2Normal_Control();
	TLE9262Drv_HW_CTRL_Init2Normal_Control();
	TLE9262Drv_WD_Init2Normal_Control();
	TLE9262Drv_BUS_CTRL_1_Init2Normal_Control();
	TLE9262Drv_BUS_CTRL_2_Init2Normal_Control();
	TLE9262Drv_SW_SD_Init2Normal_Control();
}


/******************************************************************************/
/*
*Function Name :void TLE9262Drv_vNormal2StopMode()

* Description   :
* Date          :	2018.04.11	
*/
/******************************************************************************/
void  TLE9262Drv_vStop2NormalMode(void)
{
	TLE9262Drv_vInit2NormalMode();
}


/******************************************************************************/
/*
*Function Name :void TLE9262Drv_vGetStatRegister()

* Description   :
* Date          :	2018.04.11	
*/
/******************************************************************************/
void  TLE9262Drv_vGetStatRegister(void)
{	
	if(u8Rec[0]!=0)
	{
		if(u8Rec[0]&0x01)
		{
			TLE9262Drv_SUP_STAT_2_Get();
		}
		if(u8Rec[0]&(0x01<<1))
		{
			TLE9262Drv_THERM_STAT_Get();
		}
		if(u8Rec[0]&(0x01<<2))
		{
			TLE9262Drv_DEV_STAT_Get();
		}
		if(u8Rec[0]&(0x01<<3))
		{
			TLE9262Drv_BUS_STAT_1_Get();
		}
		if(u8Rec[0]&(0x01<<4))
		{
			TLE9262Drv_WK_STAT_1_Get();
			TLE9262Drv_WK_STAT_2_Get();
		}
		if(u8Rec[0]&(0x01<<5))
		{
			TLE9262Drv_SUP_STAT_2_Get();
			
		}
		if(u8Rec[0]&(0x01<<6))
		{
			TLE9262Drv_HS_OC_OT_STAT_Get();
		}
		if(u8Rec[0]&(0x01<<7))
		{
			TLE9262Drv_HS_OL_STAT_Get();
		}
	}
}

/******************************************************************************/
/*
*Function Name :void TLE9262Drv_vNormal2StopMode()

* Description   :
* Date          :	2018.04.11	
*/
/******************************************************************************/
void  TLE9262Drv_vNormal2SleepMode(void)
{
	TLE9262Drv_HW_CTRL_Normal2Sleep_Control();

	TLE9262Drv_WK_CTRL_1_Normal2Sleep_Control();
	TLE9262Drv_WK_CTRL_2_Normal2Sleep_Control();

	TLE9262Drv_BUS_CTRL_1_Normal2Sleep_Control();
	TLE9262Drv_HS_CTRL1_OFF();
	TLE9262Drv_HS_CTRL2_OFF();

	/*Config mode and Supply*/  
	//this step must be doing And nor SBC can not Sleep
	TLE9262Drv_WK_STAT_1_Clc();
	TLE9262Drv_WK_STAT_2_Clc();
	TLE9262Drv_vGetStatRegister();
	//this step must be doing at last
	TLE9262Drv_M_S_CTRL_Normal2SLeep_Control();
	//this step must be doing at last
}


/******************************************************************************/
/*
*Function Name :void TLE9262Drv_vNormalMode()

* Description   :
* Date          :	2018.04.11	
*/
/******************************************************************************/
void  TLE9262Drv_vNormalMode(void)
{	//write register
	TLE9262Drv_WD_Init2Normal_Control();
	TLE9262Drv_HS_CTRL1_NormalMode_Control();
	//get STAT register
	//TLE9262Drv_vGetStatRegister();
}



/******************************************************************************/
/*
*Function Name :void TLE9262Drv_vNormalMode()

* Description   :
* Date          :	2018.04.11	
*/
/******************************************************************************/
void  TLE9262Drv_vNormal2StopMode(void)
{
	TLE9262Drv_HW_CTRL_Normal2Stop_Control();
	TLE9262Drv_WK_CTRL_1_Normal2Stop_Control();
	TLE9262Drv_WK_CTRL_2_Normal2Stop_Control();
	TLE9262Drv_BUS_CTRL_1_Normal2Stop_Control();
	TLE9262Drv_HS_CTRL1_OFF();
	TLE9262Drv_HS_CTRL2_OFF();


	/*before go to stop mode ,must clear WK_STAT_1 and WK_STAT_2*/
	TLE9262Drv_WK_STAT_1_Clc();
	TLE9262Drv_WK_STAT_2_Clc();
	TLE9262Drv_vGetStatRegister();
	/*Config mode and Supply*/ 

	TLE9262Drv_WD_DisableInStopMode_Control();
        /*The watchdog can be disabled for SBC Stop Mode in SBC Normal Mode.*/
	
	//this step must be doing at last
	TLE9262Drv_M_S_CTRL_Normal2Stop_Control();
	//this step must be doing at last
}


/******************************************************************************/
/*
*Function Name :void TLE9262Drv_vNormalMode()

* Description   :
* Date          :	2018.04.11	
*/
/******************************************************************************/
void  TLE9262Drv_StandbyMode(void)
{
	
	TLE9262Drv_HW_CTRL_Normal2Stop_Control();

	TLE9262Drv_WK_CTRL_1_Normal2Stop_Control();
	TLE9262Drv_WK_CTRL_2_Normal2Stop_Control();
	//TLE9262Drv_WD_DisableInStopMode_Control();
	TLE9262Drv_BUS_CTRL_1_OFF_Control();
	TLE9262Drv_HS_CTRL1_OFF();
	TLE9262Drv_HS_CTRL2_OFF();
}

/******************************************************************************/
/*
*Function Name :void TLE9262Drv_vMain()

* Description   :
* Date          :	2018.04.11	
*/
/******************************************************************************/
void  TLE9262Drv_vMain(void)
{
    uint8 u8Readvalue;
    //TLE9262Drv_BUS_STAT_1_Clc();
    //TLE9262Drv_SUP_STAT_1_Clc();
    //TLE9262Drv_vInit2NormalMode();
    TLE9262Drv_vNormalMode();
    //Rte_Read_PIM_PIM_IgnState_Value(&u8Readvalue);
    if(!u8Readvalue&0x01)
    {
        //SBC_u8ForceIoControl_Write(0);
    }
	
}
/******************************************************************************/
/*
*Function Name void SBC_vStatusChange(SBC_u16SysStatusVarNumber enSysIndex)
* Description   : sbc status change manangment
* Date          :	2018.04.11	
*/
/******************************************************************************/

void SBC_vStatusChange(SBC_u16SysStatusVarNumber enSysIndex)
{
	SBC_u16SYS_Status=enSysIndex;
	switch(SBC_u16SYS_Status)
	{
		case SBC_u16SysStatusVarNumber_Init:
			TLE9262Drv_vInitMode();
			SBC_u16SYS_Status=SBC_u16SysStatusVarNumber_Init2Normal;
		break;
			
		case SBC_u16SysStatusVarNumber_Init2Normal:
			
			TLE9262Drv_vInit2NormalMode();
			
			SBC_u16SYS_Status=SBC_u16SysStatusVarNumber_Normal;
		break;
			
		case SBC_u16SysStatusVarNumber_Normal:
			
			TLE9262Drv_vNormalMode();
		
		break;

			
		case SBC_u16SysStatusVarNumber_Normal2Stop:
			
			TLE9262Drv_vNormal2StopMode();
			
			SBC_u16SYS_Status=SBC_u16SysStatusVarNumber_Stop;
		break;

			
		case SBC_u16SysStatusVarNumber_Stop:
		break;

			
		case SBC_u16SysStatusVarNumber_Stop2Normal:		
			TLE9262Drv_M_S_CTRL_Init2Normal_Control();
			SBC_u16SYS_Status=SBC_u16SysStatusVarNumber_Normal;
		break;

		case SBC_u16SysStatusVarNumber_Normal2Sleep:
			TLE9262Drv_vNormal2SleepMode();
		break;

		case SBC_u16SysStatusVarNumber_Sleep:
            break;

            case SBC_u16SysStatusVarNumber_Standby:
                    TLE9262Drv_StandbyMode();
             break;
			
		default:
			break;
		
	}

}



/******************************************************************************/
/*
*Function Name :void vReset()

* Description   :
* Date          :	2018.04.11	
*/
/******************************************************************************/
void  TLE9262Drv_vReset(void)
{	
	SPI_vDrvInit_CH1();
	TLE9262Drv_vAddrInit();
	
	TLE9262Drv_vInitMode();

	
	TLE9262Drv_vInit2NormalMode();
	//TLE9262Drv_vInitMode();

	
	TLE9262Drv_BUS_STAT_1_Clc();
	TLE9262Drv_SUP_STAT_1_Clc();

	
}



/******************************************************************************/
/*
*Function Name :void SBC_vMain()

* Description   :
* Date          :	2018.04.11	
*/
/******************************************************************************/
//extern uint8  OS_FirstSleepFlag;
//uint8 OS_FirstSleepFlagLast;
void SBC_vMain(void)
{
#if 0
       if(OS_FirstSleepFlag==1)
	{

	}
       else if((OS_FirstSleepFlagLast==1)&&(OS_FirstSleepFlag==0))
       {
            SBC_vReset();
        }
	else
	{
		TLE9262Drv_vMain();
	}
	OS_FirstSleepFlagLast = OS_FirstSleepFlag;
#endif
    

	TLE9262Drv_vMain();/*GE-T*/
    
}
void SBC_vReset(void)
{
	TLE9262Drv_vReset();
}

void SBC_vInit()
{
	
}

void SBC_WDFeedDog()
{

	TLE9262Drv_WD_Init2Normal_Control();

}





