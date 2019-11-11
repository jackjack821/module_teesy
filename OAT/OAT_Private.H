/*******************************************************************************
| Module Name: Calculate the ambient temperature
| File Name: OAT_Private.h
|
|-------------------------------------------------------------------------------
|               C O P Y R I G H T
|-------------------------------------------------------------------------------
| Copyright (c) 2016 Huizhou Desay SV Automotive Co., Ltd.    All rights reserved.
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
| Zou Riming                     Desay SV Automotive Co., Ltd
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date             Ver         Author               Description
| ----------  -------  -------------  -------------------------------------------------
| 2016-06-21   0100      Zou Riming            First Create  
| 2016-09-22   0200      Zou Riming          Delet condition 2 of cold start 
| 
********************************************************************************/
#ifndef OAT_PRIVATE_H
#define OAT_PRIVATE_H

 /* Define the current sortware version of this module  */
#define OAT_nSwVersion				(0x0400u)  


/* Configuration setting of the module */

#define OAT_UseInActiveMode      False         /* Calculate ambient temperature in active mode or not*/
#define OAT_UseNewCCP              True         /* OAT module Use NewCCP or not*/
#define OAT_FromSensor              True         /*  True: OAT from sensor;  False: OAT from bus   */
#define OAT_UseTemp500             False        /*   Max temp use: (True: 500deg;  False: 120deg) */
#define OAT_UseIgnDelay              False        /*  True: use IGN delay flag;  False: not use IGN delay flag */
#define OAT_InitValUseCurVal        True      /*   Cold start Init use: (True:current PTA;  False: the min between current PTA and current HCT)*/
#define OAT_MidErrorUseDefault    True        /*  Mid way error use: (True: Defalt value;  False: last value) */
#define OAT_PtaUseGeneralSensor True      /*PTA use General amb sensor or other amb sensor*/

/* System-headerfiles */
#include "General.h"

/* Foreign headerfiles */
#include "Alg.h" 

//#include "CANAPP.h"
#include "IGN.h" 
#include "HCT.h" 
#include "Rte_internal.h" 
#include "POW.h" 
//#include "VEL.h" 
#include "EED.h" 
#include "Frame_if.h"

/* Own headerfiles */
#include "OAT_Type.h"   
#include "OAT_Cfg.h"
#include "OAT.h"     
#include "OAT_interface.h"


/*Define the value for other module****************************************/
#define OAT_u16SwVersion		    (OAT_au16Array[OAT_nu16SwVersion])
#define OAT_u16Valid                        (OAT_au16Array[OAT_nu16Valid])
#define OAT_u16Display                     (OAT_au16Array[OAT_nu16Display])
#define OAT_u16EedOatValue             (OAT_au16Array[OAT_nu16EedOatValue])
#define OAT_u16EedHctValue             (OAT_au16Array[OAT_nu16EedHctValue])
#define OAT_u16SensorAdRawValue   (OAT_au16Array[OAT_nu16SensorAdRawValue])
#define OAT_u16BusRawValue            (OAT_au16Array[OAT_nu16BusRawValue])
#define OAT_u16PhyRawValue            (OAT_au16Array[OAT_nu16PhyRawValue])
#define OAT_u16Value		           (OAT_au16Array[OAT_nu16Value])
#define OAT_u16ValueHys		           (OAT_au16Array[OAT_nu16ValueHys])
#define OAT_u16DiagInfo                   (OAT_au16Array[OAT_nu16DiagInfo])
#define OAT_u16ErrorCode                  (OAT_au16Array[OAT_nu16ErrorCode])
   
/*Define read/write eeprom data stored */
#define OAT_u16EedOatData  (OAT_u16EedData[0])
#define OAT_u16EedHctData  (OAT_u16EedData[1])

 /*  Define const parameter */
#define OAT_nu16InitOutPutValue  (0xFFFFU)

 /*  Define const parameter */

#if(OAT_PtaUseGeneralSensor==True)
#define OAT_nSensorChanel            (9U)  /* The AD chanel of MCU in the circuit, start from 0  */
#else
#define OAT_nSensorChanel            (8U)  /* The AD chanel of MCU in the circuit, start from 0  */
#endif

#define OAT_nMaxInitTime           (10U)  /* The max init Delay time for OAT init calculate  */
#define OAT_nMaxErrorDelay           (5U)  /* The Max Value Error Delay of other module */
#define OAT_nChangePrarameter	  (8U)  /* Change prarameter, to inprove the resolution */
#define OAT_nUpdateTime                (1U) /*   unit: second  */
#define OAT_nVelSwitchFreeze        (10U)/*   unit: km/h  */
#define OAT_nVelSwitch                 (40U)/*   unit: km/h  */

#define OAT_u16FreezeRiseSpeed   (0U)	/*by zsc,140320, no update*/
#define OAT_u16SlowRiseSpeed         (uint16)(((uint16)OAT_nSlowRiseSpeed <<OAT_nChangePrarameter)/OAT_nSpeedDivTime) /*0.1 per min*/
#define OAT_u16FastRiseSpeed          (uint16)(((uint16)OAT_nFastRiseSpeed  <<OAT_nChangePrarameter)/OAT_nSpeedDivTime) /*1 per min*/
#define OAT_u16ConstFallSpeed         (uint16)(((uint16)OAT_nConstFallSpeed <<OAT_nChangePrarameter)/OAT_nSpeedDivTime) /*6 per min*/

#define OAT_nFreezeRiseSpeed       (0U)	
#define OAT_nSlowRiseSpeed         (1U)      /* 1/10 = 0.1deg per min  */
#define OAT_nFastRiseSpeed           (10U)   /* 10/10 = 1deg per min  */
#define OAT_nConstFallSpeed          (60U)  /* 60/10 = 6deg per min  */
#define OAT_nSpeedDivTime           (60U)   /* 60s = 1min  */

#define OAT_nHysteresis			(uint16)(2*10) /*change to 2degree by zsc,141121,ori 3 degree*/
#define OAT_nBusValueFactor		(4U)  /*resolution is 0.25*/
#define OAT_nBusValueOffset	       (128U)  /* 0 means -128¡æ */
#define OAT_nDefaultBusValue       (uint16)((15+OAT_nBusValueOffset)*OAT_nBusValueFactor)
#define OAT_nValueShortToGnd               (20U)     /* 0.098V, less than means short to ground   */
#define OAT_nValueShortToPow               (1005U)  /* 4.912V,more than means short to power  */ 
#define OAT_u16HctEedDiffThres     (uint16)(5*10)/* 5 deg,  difference between current Hct Value and EED Hct Value*/
#define OAT_u16HctKeyOnOffDiffThres	(uint16)(5*10)/* 5 deg,  difference between key on hct and key off hct*/
#define OAT_nDefaultValue                  OAT_nTemp(20)   
#define OAT_nDefaultHctValue             OAT_nTemp(15)
#define OAT_u16HctForColdStartLimit   OAT_nTemp(60)   


#if (OAT_UseTemp500==True)
#define OAT_nMaxTemp                      (uint16)((500+500)*10) /*500deg*/
#define OAT_nMinTemp                       (uint16)((-500+500)*10) /*-500deg*/
#define OAT_nTemp(Deg)                    (uint16)((Deg+500)*10) 
#define OAT_nTempValueFactor          (10U)  /*resolution is 0.1*/
#define OAT_nTempValueOffset	    (uint16)(500) /* value=(T+500)*10,  5000 means 0¡æ */
#else
#define OAT_nMaxTemp	                  (uint16)((120+40)*10)/*120deg*/
#define OAT_nMinTemp	                  (uint16)((-40+40)*10)/*-40deg*/
#define OAT_nTemp(Deg)                    (uint16)((Deg+40)*10) 
#define OAT_nTempValueFactor           (10U)  /*resolution is 0.1*/
#define OAT_nTempValueOffset           (uint16)(40) /* value=(T+40)*10, 400 means 0¡æ */
#endif

#if (OAT_UseIgnDelay==True)
#define OAT_u16GetIgnDelayFlag()     (IGN_u16GetValue(IGN_nu16Off2OnOrLeaveCrankDelayFlag))
#else
#define OAT_u16GetIgnDelayFlag()     True
#endif


/**************************Extern Module Interface Without RTE Start*****************************/
#define OAT_u16GetSysValue_SYS_nFlag1000MS_BG()                FRAME_u16GetValue(SYS_nu16Flag1000MS_BG)
#define OAT_u16GetVelValue_VEL_nu16ValueForOat()               (VEL_u16GetValue(VEL_nu16OatValue))
#define OAT_u16GetHctValue_HCT_nu16ValueForOat()               HCT_u16GetValue(HCT_nu16Value)
#define OAT_ReadEedGroupData(au8DataBuffer,u16Length)        Rte_Call_IoHwEep_IoHwEedProto_ReadEep_OatValue_EedRead(au8DataBuffer,u16Length)//*au8DataBuffer=u16Length 
#define OAT_WriteEedGroupData(au8DataBuffer,u16Length)       Rte_Call_IoHwEep_IoHwEedProto_WriteEep_OatValue_EedWrite(au8DataBuffer,u16Length)// *au8DataBuffer=u16Length 
#if(OAT_FromSensor==True)
#define OAT_u16GetPowValue_POW_nu16AdValid()                  True//(POW_u16GetValue(POW_nu16AdValid))//
#define OAT_u16GetHalValue_HAL_nu16OatAdValue(Value)              (Rte_Call_IoHwAd_IoHwAd_ReadAd_OatSensorValue_Read(Value))
#else
#define OAT_u16GetPowValue_POW_nu16ComLowVoltage()     (POW_u16GetValue(POW_nu16ComLowVoltage))
#define OAT_u16GetPowValue_POW_nu16ComHighVoltage()      (POW_u16GetValue(POW_nu16ComHighVoltage))
#define OAT_u16GetCanValue_CANAPP_nu16OatQuaFlag()   	  (uint16)(CANAPP_u8GetValue(CANAPP_nu8AirAmbTe_D_Qf))
#define OAT_u16GetCanValue_CANAPP_nu16OatValue()   	    (CANAPP_u16GetValue(CANAPP_nu16AirAmb_Te_Actl))
#endif

/**************************Extern Module Interface Without RTE End*****************************/

#endif                                  /* ifndef OAT_PRIVATE_H*/

/*****************************************************************************
* EOF: OAT_Private.h
******************************************************************************/

