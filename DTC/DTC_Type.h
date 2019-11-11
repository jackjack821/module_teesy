/*******************************************************************************
| Module Name: DTC process(prcess dianostic code) 
| File Name: DTC_Type.h
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
| Sui Yanchun                 Desay SV Automotive Co., Ltd
| Lin Tao                     Desay SV Automotive Co., Ltd
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date             Ver         Author               Description
| ----------  -------  -------------  -------------------------------------------------
| 2014-11-24  1.00        Sui Yanchun       update the DTC module 
| 2015-12-56  2.00        Lin Tao           update for the MISRA C

********************************************************************************/


#ifndef DTC_TYPE_H
#define DTC_TYPE_H


#include "DTC_Cfg.h"
#include "DTC_Private.h"
/* System-headerfiles */
#include "General.h"



/*----------------------------------------------------------------------------
-------------------------------	structure define------------------------------------
------------------------------------------------------------------------------*/



/*DTC information which save in the EEPROM,one dtc--->length= 10*/
/***Start***/
#pragma pack(1)
typedef struct
{
	uint8       SysBattery;
    uint8       CoolantTemp;
	uint16      VelSpeed;
    uint32      u32FirstOdometer;
    uint32      u32LastOdometer;

}DTC_SNAPSHOT;

typedef struct
{
	uint8 	Fault_Frequency;	/* 0-255,Fault occurrence counter*/
	uint8 	Fault_Count;		/* upto 1 frequency add 1 =FC*/
	uint8	MonitorCycleCnt;
	uint8 	AgeingCnt;		    /* need to update*/
	
}DTC_EXTENDED_DATA;

typedef struct
{
    uint8 					DTCIndex;
    uint8 					Status_Byte;	
    DTC_SNAPSHOT            Snapshot_Data;
    DTC_EXTENDED_DATA 		Extended_Data;	
    uint8					Aged_Check;		
}DTC_EEP_STORE;
#pragma pack()
/***End***/


/*DTC information which save in the RAM*/
/***Start***/
typedef struct
{
	uint8 						Status_Byte;
	DTC_SNAPSHOT                Snapshot_Data;
	DTC_EXTENDED_DATA 			Extended_Data;	
	uint8						DTC_Aged ;
	
}DTC_DATA_TYPE;
/***End***/

#if 0
/*-----------------var declare----------------------------------------------------*/
typedef struct
{
	DTC_EEP_STORE Dtc_content[DTC_MIN_NUMBER_TO_STORE];
	uint8 		Checksum;
	
}DTC_EEP_Format;
#endif


typedef enum DTC_enu8VarVechileCfg
{
	DTC_nu8EMSNodeCfg,
	DTC_nu8PEPSNodeCfg,
    DTC_nu8BCMNodeCfg, 
    DTC_nu8ESCNodeCfg, 
    DTC_nu8TBOXNodeCfg,   
    DTC_nu8MMINodeCfg,   
    DTC_nu8IPKNodeCfg, 
    DTC_nu8IPUNodeCfg,
    DTC_nu8BMSHNodeCfg,
    DTC_nu8VCUNodeCfg,
    DTC_nu8OBCNodeCfg,    
    DTC_nu8PM25NodeCfg,   
    DTC_nu8IONNodeCfg, 
    DTC_nu8RCPNodeCfg,    
    DTC_nu8AQSSensorCfg,      
	DTC_nu8VechileCfgMax
}DTC_tenu8VarVechileCfg;



#endif                                  /* ifndef */

