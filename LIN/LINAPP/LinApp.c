/**************************** .FILE_HEADER_BEGIN *****************************
 .FILE; [ LINAPP1c1.c]
 .Author; [ Chen Yudong]
 .Date; 2017/10/12
 .Update Time; 13:37:47
 .**************   Change History ********************************************* 
 .V2.0 (Release Date:2017-4-3)
 .1.Creation
 .V2.1 (Release Date:2017-4-6)
 .1.Add u32GetValue Interface in LINAPP.C.
 .2.Add u32GetValue Interface in LINAPP.h.
 .V2.2 (Release Date:2017-4-8)
 .1.Add vClearMessCnt Interface in LINAPP.C.
 .***************************************************************************** 
 .Gen File Name: Geely GE12_LIN_V1.31_20170624.xlsx
****************************** .FILE_HEADER_END ******************************/

#define LINAPP                          /* Name of the Module                */

/* HEADER-FILES (Only those that are needed in this file) */
#include "SHC.h"
#include "RDC.h"
#include "stdio.H"
#include "POW.h"
#include "Frame_if.H"
#include "LINNM.h"
#include "Mmi.h"
#include "Oat.h"
#include "Vel.h"
#include "Ion.h"
#include "Bctl.h"
#include "Accc.h"
#include "DCM.h"
#include "force.h"
#include "touchkey.h"
#include "key.h"
/* System-headerfiles */
#include "General.H"
//#include "Iodefine.H"

/* Lin Driver headfiles */
#include "lin_api.H"
#include "dtl_api.H"
#include "Lin_Drv.h"
#include "LinDiag.h"

/* Own headerfiles */
#include "LINAPP.H"
#include "LINAPP_cfg.H"

/********
add by wuyijun 
data 2019 05 27

fundction 

****/

#include "Ccp_cfg.h"


#include "ccp_def.h"

/* internal variable...*/
static uint16 LINAPP_au16Array[LINAPP_nu16Max];
static uint32 LINAPP_au32Array[LINAPP_nu32Max];
static uint16 LINAPP_u16MsgLostCounter[LINAPP_nMsgMax];
static uint8 LinCycleTick1000ms;

#define LINAPP_ErrCodeSet(Index)             (LINAPP_au32Array[LINAPP_nu32ErrorCode] |= (0x00000001 << Index))
#define LINAPP_ErrCodeClr(Index)             (LINAPP_au32Array[LINAPP_nu32ErrorCode] &= (~(0x00000001 << Index)))
#define LINAPP_ErrCodeGet(Index)             ((LINAPP_au32Array[LINAPP_nu32ErrorCode]>>Index) & 0x00000001)
#define LINAPP_AllErrCodeClr(Index)          (LINAPP_au32Array[LINAPP_nu32ErrorCode] = 0U)
#define LINAPP_Msg1stRecSucFlgSet(Index)             (LINAPP_au32Array[LINAPP_nu32Msg1stRecSucFlg] |= (0x00000001 << Index))
#define LINAPP_Msg1stRecSucFlgClr(Index)             (LINAPP_au32Array[LINAPP_nu32Msg1stRecSucFlg] &= (~(0x00000001 << Index)))
#define LINAPP_Msg1stRecSucFlgGet(Index)             ((LINAPP_au32Array[LINAPP_nu32Msg1stRecSucFlg]>>Index) & 0x00000001)
#define LINAPP_AllErrFlagClr(Index)                  (LINAPP_au32Array[LINAPP_nu32Msg1stRecSucFlg] = 0U)


/* All frame lost communication flag definition...*/
#define PM25_1_LOST_COUNT_MAX      100 

/* Transmit frame definition...*/
void LINAPPSend_AC_1_0x01(void);
void LINAPPSend_AC_2_0x05(void);
static void LinAppSend_FCP_01_02h(void);

/* Receive frame definition...*/
void LINAPPReceive_PM25_1_0x04(void);

/* Frame update cycle...*/
void LINAPPSendFrameUpdate(void);
void LINAPPReceiveFrameUpdate(void);

/* */
void LINAPPSend_AC_1_0x01(void)
{

}

void LINAPPSend_AC_2_0x05(void)
{
    // l_bool_wr_L_AC_PM25StsReq(5);/*TEST*/
    // l_u8_wr_L_AC_CarSpeed(LINAPP_au16Array[LIN_nu16L_PM25_InDen]);/*TEST*/
}


/* */
void LINAPPReceive_PM25_1_0x04(void)
{
	if(l_flg_tst_AC_1())
	{
		l_flg_clr_AC_1();
		LINAPP_au16Array[LIN_nu16L_PM25_InDen] = l_u8_rd_L_AC_LeftSetTemperature();
	}
}


/* Send frame update cycle call...*/
void LINAPPSendFrameUpdate(void)
{/**/
     //LINAPPSend_AC_1_0x01();
     //LINAPPSend_AC_2_0x05();
}

/* Receive frame update cycle call...*/
void LINAPPReceiveFrameUpdate(void)
{/**/
     LINAPPReceive_PM25_1_0x04();
}
/* const code...*/


void LINAPP_vReset(void)
{
	uint8 u8i;	
	for(u8i=0;u8i<LINAPP_nMsgMax;u8i++)
	{
	      LINAPP_u16MsgLostCounter[u8i]=0;
	}
	for(u8i=0;u8i<LINAPP_nu16Max;u8i++)
	{
	      LINAPP_au16Array[u8i]=0;
	}
	for(u8i=0;u8i<LINAPP_nu32Max;u8i++)
	{
	      LINAPP_au32Array[u8i]=0;
	}
}

// this function must be call in 10ms container
void LINAPP_vMain_10ms(void)
{	
	LINAPPSendFrameUpdate();
	LINAPPReceiveFrameUpdate();
}

uint16 LINAPP_u16GetValue(LIN_tenu16VarNum enIndex)
{
	if(enIndex < LINAPP_nu16Max)
	{
		return (LINAPP_au16Array[enIndex]);
	}
	else
	{
		return (LINAPP_au16Array[LINAPP_nu16Max-1]);
	}
}
void LINAPP_vClrValue(LIN_tenu16VarNum enIndex)
{
	if(enIndex < LINAPP_nu16Max)
	{
		LINAPP_au16Array[enIndex]=0;
	}
	else
	{
	}
}

uint32 LINAPP_u32GetValue(LIN_tenu32VarNum enIndex)
{
	if(enIndex < LINAPP_nu32Max)
	{
		return (LINAPP_au32Array[enIndex]);
	}
	else
	{
		return (LINAPP_au32Array[LINAPP_nu32Max-1]);
	}
}

/*When Dtc clear happen, all ErrorCounter and ErrorCode need to be clear, this function will be called by DTC Function.*/
uint16 LINAPP_vClearMessCnt(void)
{
	uint8 u8i;	
	for(u8i=0;u8i<LINAPP_nMsgMax;u8i++)
	{
	      LINAPP_u16MsgLostCounter[u8i]=0;
	}
	LINAPP_AllErrCodeClr();
    LINAPP_AllErrFlagClr();
}

 vuint8 Panel_info_FCP_1(vuint8* txBuffer) /*PRETRANSIT 161119*/
 {
     LinAppSend_FCP_01_02h();
    return 1;
 }

 vuint8 Panel_info_FCP_2(vuint8* txBuffer) /*PRETRANSIT 161119*/
 {
     //LinAppSend_FCP_01_02h();
    return 1;
 }
/**************************** .BLOCK_COMMENT_BEGIN ***************************
* GLOBAL DEFINITIONS
*
* In this section define
* - all global ROM-constants of your module
* - all global variables of your module
***************************** .BLOCK_COMMENT_END *****************************/

/**************************** .BLOCK_COMMENT_BEGIN ***************************
* FILE LOCAL DEFINITIONS
*
* In this section define
* - all file local macros
* - all file local define-constants
* - all file local type definitions
* - all file local ROM-constants
* - all file local variables
***************************** .BLOCK_COMMENT_END *****************************/

static void LinAppSend_FCP_01_02h(void)
{
	uint32 u32Ad=0;
  	uint16 u16Ad=Force_u16GetValue(Force_nu16RawAd);

/***********************
add by wuyijun 
data 2019 05 27
fundction : tell us which key is us presss.

*******************************/
extern uint8 TOUCHKEY_u8DataArrayFE_Byte6;
//	l_u8_wr_L_FCP_LeftTempUp((uint8)CCP_u8DataArrayFE_Byte6);

	l_u8_wr_L_FCP_LeftTempUp(TOUCHKEY_u8DataArrayFE_Byte6);

/********
two way

*****/
 //   data_u8DataArrayFE_Byte6=     CCP_stDatastrct.u8Data6;


		#if 0	
//	 _s_L_FCP_LeftTempUp=0x01;
//	 _s_L_FCP_LeftTempDown=0x01;

	//_s_L_FCP_NoUsed4 = LINAPP_au16Array[LIN_nu16L_PM25_InDen];
	if(u16Ad < 255)
	{
	_s_L_FCP_NoUsed4 = u16Ad;
	}
	else
	{
		_s_L_FCP_NoUsed4 = 255;
	}

	u32Ad = KEY_u32KeyStatusIsPress();
	_s_L_FCP_NoUsed3 = (uint8)(u32Ad&0x000001FF);
	_s_L_FCP_NoUsed2 = (uint8)((u32Ad>>9)&0x000001FF);
	//_s_L_FCP_NoUsed3 = TOUCHKEY_u8GetValue(TOUCHKEY_nu8IicX_Value);
	//_s_L_FCP_NoUsed2 = TOUCHKEY_u8GetValue(TOUCHKEY_nu8IicY_Value);

	u16Ad=Force_u16GetValue(Force_nu16RefAd);
	if(u16Ad < 255)
	{
	_s_L_FCP_NoUsed1 = u16Ad;
	}
	else
	{
		_s_L_FCP_NoUsed1 = 255;
	}

	l_bool_wr_L_FCP_DefrostReq(0);
	l_bool_wr_L_FCP_AUTOreq(1);
	l_bool_wr_L_FCP_CycleReq(0);
	l_bool_wr_L_FCP_RearDefReq(1);
	l_bool_wr_L_FCP_MaxAcReq(0); /*no maxac in 3za,161117*/
	l_bool_wr_L_FCP_LeftSeatHeatReq(1);
	l_bool_wr_L_FCP_RightSeatHeatReq(0);
	l_bool_wr_L_FCP_IONreq(0);
   	 l_bool_wr_L_FCP_ModeDown(0);
	l_bool_wr_L_FCP_ModeUp(0);
	l_bool_wr_L_FCP_Heatreq(0);

	l_bool_wr_L_FCP_OffModereq(0);
	
	l_bool_wr_L_FCP_MaxAcReq(0); 

	#endif
	
}
 

/*****************************************************************************
* EOF:
******************************************************************************/

