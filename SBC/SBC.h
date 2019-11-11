/**************************** .FILE_HEADER_BEGIN *****************************
  .TITLE: CSI for EEPROM driver for 96CX6 EEPROM serial
*-----------------------------------------------------------------------------
  .FILE:EEP_Drv.h
  .AUTHOR:Tan, fumin
*-----------------------------------------------------------------------------

 Date        Author                       Change
 -----------------------------------------------------------------------------
2013.02.06  Tan, fumin		   :create this module
2013.03.12  Tan, fumin		    create macro EP_CallBackFunction_Enable for driver call back for special flow
*****************************************************************************/


#ifndef SBC_H
#define SBC_H
#include "s_spi.h"
#include "general.h"

#define  SBC_Version 0x01
#define SBC_u16ErrCode			SBC_u16Array[SBC_nu16ErrCode]
#define SBC_u16SYS_Status		SBC_u16Array[SBC_nu16SYS_Status]
typedef enum  SBC_u16StatusNumber
{
	SBC_nu16CAN_Status=0,
	SBC_nu16LIN_Status,
	SBC_nu16SYS_Status,
	SBC_nu16ErrCode,
	SBC_nu16Max
} SBC_u16StatusVarNumber;

typedef enum  SBC_u16ErrCodeStatusNumber
{
	SBC_nu16InitModeConfigWDFail=0,
	SBC_nu16NormalModeConfigWDDisableInstopModeFail,
	SBC_nu16NormalModeConfigM_S_CTRLFail,
	SBC_nu16NormalModeConfigHW_CTRLFail,
	SBC_nu16NormalModeConfigBUS_CTRL_1Fail,
	SBC_nu16NormalModeConfigBUS_CTRL_2Fail,
	SBC_nu16NormalModeConfigWK_CTRL_1Fail,
	SBC_nu16NormalModeConfigWK_CTRL_2Fail,
	SBC_nu16NormalModeConfigSW_SD_CTRLFail,
	SBC_nu16NormalModeConfigHS_CTRL1_CTRLFail,
	SBC_nu16NormalModeConfigHS_CTRL2_CTRLFail,
	
	SBC_nu16ErrCodeMax
} SBC_u16ErrCodeStatusVarNumber;

typedef enum  SBC_u16SysStatusNumber
{
	SBC_u16SysStatusVarNumber_Init=0,
	SBC_u16SysStatusVarNumber_Init2Normal,
	SBC_u16SysStatusVarNumber_Normal,
	
	SBC_u16SysStatusVarNumber_Normal2Stop,
	SBC_u16SysStatusVarNumber_Stop,
	SBC_u16SysStatusVarNumber_Stop2Normal,
	
	SBC_u16SysStatusVarNumber_Normal2Sleep,
	SBC_u16SysStatusVarNumber_Sleep,

        SBC_u16SysStatusVarNumber_Standby,
	

	SBC_nu16SysStatusMax
} SBC_u16SysStatusVarNumber;
/**********************************************************************/

/*************Watch Dog Function List*************************************/

void SBC_vMain(void);
void SBC_vReset(void);/*11 01 reset,160921*/
void SBC_vInit();
void SBC_WDFeedDog();
void SBC_vStatusChange(SBC_u16SysStatusVarNumber enSysIndex);
Std_ReturnType SBC_u8ForceIoControl_Write (/*IN*/uint32 ForceIoControlWord);

#endif

