
/*******************************************************************************
| Module Name: DTC process(prcess dianostic code) 
| File Name: DTC.h
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
| Sui Yanchun                        Desay SV Automotive Co., Ltd
| Zhang Shuncong                     Desay SV Automotive Co., Ltd
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date             Ver         Author               Description
| ----------  -------  -------------  -------------------------------------------------
| 2014-11-24  1.00        Sui Yanchun       update the DTC module 
| 2015-12-56  2.00        Lin Tao           update for the MISRA C

********************************************************************************/

#ifndef DTC_H
#define  DTC_H
/* System-headerfiles */
#include "General.h"
#include "Rte_Type.h"
#include "DTC_Type.h"

/*----------------------------------------------------------------------------
-------------------------------	array define------------------------------------
------------------------------------------------------------------------------*/

/*this is for uint8 type variables*/
typedef enum DTC_enu8VarNumbers
{
	DTC_nu8Valid = 0,		/*The valid flag of DTC module output.*/
	DTC_nu8SwVersion,		/*The module SW version.*/
	DTC_nu8Max
}DTC_tenu8VarNumber;

/*this is for uint8 type variables*/
typedef enum DTC_enu16VarNumbers
{
	DTC_nu16ErrorCode = 0,		/*The valid flag of DTC module output.*/
	DTC_nu16Max
}DTC_tenu16VarNumber;


uint8 DTC_u8GetValue( DTC_tenu8VarNumber  enIndex );
uint16 DTC_u16GetValue( DTC_tenu16VarNumber  enIndex );
//uint8 DTC_u8GetNetWorkCfgValue(DTC_tenu8VarVechileCfg enIndex );
Std_ReturnType DTC_u8ReadStatusByte(/*INOUT*/UInt8 * Status, /*INOUT*/UInt8 * Index);

void DTC_vMain(void);
void DTC_vMain1(void);
void DTC_vMain2(void);
void DTC_vMain3(void);
void DTC_vMain10ms(void);
void DTC_vDeInit(void);
void DTC_vReset(void);
void DTC_vInit(void);
void DTC_vDeinit(void);
void DTC_vActive(void);

void DTC_vStandbyActive(void);
void DTC_vActiveStandby(void);


Std_ReturnType DTC_u8ClearAllDtc(void);
Std_ReturnType DTC_u8ForceIoControl_Write(UInt32 ForceIoControlWord);/*IN*/
Std_ReturnType DTC_u8ReadMaskFaultDtcNum(/*INOUT*/UInt8 * Req, /*INOUT*/UInt8 * Res, /*OUT*/UInt8 * Num);
Std_ReturnType DTC_u8ReadMaskFaultDtcList(/*INOUT*/UInt8 * Req, /*INOUT*/UInt8 * Res, /*OUT*/UInt8 * Num);

Std_ReturnType DTC_u8ReadSnapShotData(/*INOUT*/UInt8 * Req, /*INOUT*/UInt8 * Res, /*OUT*/UInt8 * Num);

#if (DTC_ExtendDataSupported == Yes)
Std_ReturnType DTC_u8ReadExtendData(/*INOUT*/UInt8 * Req, /*INOUT*/UInt8 * Res, /*OUT*/UInt8 * Num);
#endif
Std_ReturnType DTC_u8ReadSupportDtcList(/*INOUT*/UInt8 * Req, /*INOUT*/UInt8 * Res, /*OUT*/UInt16 * Num);

Std_ReturnType DTC_u8ForceIoControl_Write(/*IN*/uint32 ForceIoControlWord);



#endif

