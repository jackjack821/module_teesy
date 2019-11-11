/*******************************************************************************
| Module Name: Power manage model
| File Name: pow_cfg.h
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
| Du Zejia                             Desay SV Automotive Co., Ltd
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date             Ver        	Author               Description
| ----------  -------  -------------  -------------------------------------------------
| 
|2015/08/10 Rev 01.10.00      Li Ning       			 The second version  
********************************************************************************/

/*****************************************************************************
* FILE DECLARATION
******************************************************************************/
#ifndef POW_CFG_H
#define POW_CFG_H

/* Foreign headerfiles */
#include "General.h"

/*refference voltage definition*/	

#define 	POW_Ref_K30	0
#define 	POW_Ref_IGN2	1
#define 	POW_Ref_IGN1	2



#define POW_AppRef		POW_Ref_K30		/*k30 as ref*/

#define POW_ComRef		POW_Ref_K30	/*k15 as ref*/

#define POW_DiagRef		POW_Ref_K30	/*k15 as ref*/

#define POW_Ref4		POW_Ref_K30	/*k15 as ref*/


/*-----------------------------------micro switch define---------------------------------------*/
#define Com_CheckVoltage	1
#define Diag_CheckVoltage	1
#define Ref4_CheckVoltage	0


#define POW_K30Abnormal		1		/* use the k15 if the k30 is abnormal such as less then k15 .if there is no K30 line so this swithc must be set 0*/	

#define POW_5vOutputStableUsed		1	/*use 5v output stable or not*/



#define POW_RteUsed		0	/*use rte or not*/

#define POW_SensorSupplyFbUsed		0	/*use sensorfb or not*/

#define POW_5vOutputFbUsed		1	/*use 5v output feedback or not*/

#define POW_K30FbUsed		1	/*use  k30 voltage for over or under voltage check */

#if (POW_K30FbUsed==1)
	#define POW_Ign2FbUsed		0	/*use ign2 instead k30 voltage for abnormal */
#endif


/*control*/
#define POW_SensorSupplyCtrlUsed		1	/*use sensor ctrl or not*/

#define POW_5vOutPutCtrlUsed		1	/*use 5v output ctrl or not*/

#define POW_VccCutOffUsed	0		/*if cut off vcc when the system goes into sleep*/


#define POW_5VOutputCfgIfIgnOff	0		/*5v output switch control if k15 is off:0=off,1=on when k15 is off*/

/*Power (KL30) input to AD detect HW configuration
BattDet = KL30_DET * POW_Volt_Rdiv_to_AD/(R1+R2+R3+POW_Volt_Rdiv_to_AD)*/

#define POW_Volt_R1	100U				/*K*/
#define POW_Volt_R2	100U				/*K*/
#define POW_Volt_R3	100U				/*K*/
#define POW_Volt_Rdiv_to_AD	100UL	/*K*/
#define POW_DiodeVolt	0.5                 /*Vol*/ /*change by ln matched the real shematic*/
#define POW_HysteresisVol	0.5		/*normal hysteresis voltage£º0.5v*/
#define POW_AD_Offset	0U			/*AD value*/

#define POW_Volt_R1_Ign	100U				/*K*/

#define POW_Volt_Rdiv_to_AD_Ign 	33UL	/*K*/

/*5v output resistor config*/
#define POW_5vOutput_R1	56U				/*K*/
#define POW_5vOutput_Rdiv	100U				/*K*/



/* volatage delay time definition*/

#define POW_u16AppEnterLowVoltageTimerCfg   		120U	    /*  low voltage hysteresis time of application module£º120ms= mirco start time>320ms*/ 	
#define POW_u16AppEnterHighVoltageTimerCfg   		120U	    /*  high voltage hysteresis time of application module£º10ms*/
#define POW_u16AppEnterSuperHighVoltageTimerCfg   	1U	    /*  high voltage hysteresis time of application module£º10ms*/
#define POW_u16AppLeaveLowVoltageTimerCfg   		0U	    /*  high voltage hysteresis time of application module£º0ms*/
#define POW_u16AppLeaveHighVoltageTimerCfg   		0U	    /*high voltage hysteresis time of application module£º0ms*/

#if (Com_CheckVoltage==1)
#define POW_u16CanEnterLowVoltageTimerCfg   		10U	    /* voltage hysteresis time of network manangement£º100ms*/
#define POW_u16CanEnterHighVoltageTimerCfg   		10U	    /* voltage hysteresis time of network manangement£º100ms*/
#define POW_u16CanLeaveLowVoltageTimerCfg   		0U	    /* voltage hysteresis time of network manangement£º0ms*/
#define POW_u16CanLeaveHighVoltageTimerCfg   		0U	    /* voltage hysteresis time of network manangement£º0ms*/
#endif

/*diag delay timer be process by DTC module so here set it as 0*/
#if  (Diag_CheckVoltage==1)
#define POW_u16DiagEnterLowVoltageTimerCfg   		0U	 /*  voltage hysteresis time of diagnostic£º0ms*/
#define POW_u16DiagEnterHighVoltageTimerCfg   		0U	 /*  voltage hysteresis time of diagnostic£º0ms*/
#define POW_u16DiagLeaveLowVoltageTimerCfg   		0U	 /*  voltage hysteresis time of diagnostic£º0ms*/
#define POW_u16DiagLeaveHighVoltageTimerCfg   		0U	 /*  voltage hysteresis time of diagnostic£º0ms*/
#endif

/*ref4 delay timer be process  here set it as 0*/
#if  (Ref4_CheckVoltage==1)
#define POW_u16Ref4EnterLowVoltageTimerCfg   		0U	 /*  voltage hysteresis time of diagnostic£º0ms*/
#define POW_u16Ref4EnterHighVoltageTimerCfg   		0U	 /*  voltage hysteresis time of diagnostic£º0ms*/
#define POW_u16Ref4LeaveLowVoltageTimerCfg   		0U	 /*  voltage hysteresis time of diagnostic£º0ms*/
#define POW_u16Ref4LeaveHighVoltageTimerCfg   		0U	 /*  voltage hysteresis time of diagnostic£º0ms*/
#endif

#define POW_u165vSensorMin							5U		/*min value of 5v sensor feeaback ad value: 0.0049v*/
#define POW_u85vSensorLimitTimeCfg					4U		/*5v sensor supply fail time: 40ms*/
#define POW_u8AdValidTimeCfg						20U		/*ad valid hysteresis time : 200ms*/
#define POW_u85vStableTimeCfg						20U		/*5v stable  time : 200ms*/




/*GPIO ID list for HAL and APP layer*/







/*k30 as ref voltage: (batvol-0.5)*51.2=ad*/
#define POW_VoltToADK30(vol)		((uint16)((uint32)(( (vol))*1024UL) * POW_Volt_Rdiv_to_AD/(5U*(POW_Volt_R1+POW_Volt_R2+POW_Volt_R3+POW_Volt_Rdiv_to_AD))) )
#define POW_SupplyVoltToADK30(vol)	((POW_VoltToADK30(vol)-POW_VoltToADK30(POW_DiodeVolt)))	
#define POW_SupplyVoltK30Coefficient	(1000*(5U*(POW_Volt_R1+POW_Volt_R2+POW_Volt_R3+POW_Volt_Rdiv_to_AD))/(1024*POW_Volt_Rdiv_to_AD))	/*1000 time and does not consider diode voltage cause of the same value*/

/*k15 as ref voltage*/
#define POW_VoltToADIgn(vol)		((uint16)((uint32)(( (vol))*1024UL) * POW_Volt_Rdiv_to_AD_Ign/(5U*(POW_Volt_R1_Ign+POW_Volt_Rdiv_to_AD_Ign))) )
#define POW_SupplyVoltToADIgn(vol)	((POW_VoltToADIgn(vol)-POW_VoltToADIgn(POW_DiodeVolt)))	
#define POW_SupplyVoltIgnCoefficient	(1000*(5U*(POW_Volt_R1_Ign+POW_Volt_Rdiv_to_AD_Ign))/(1024*POW_Volt_Rdiv_to_AD_Ign))			/*1000 time and does not consider diode voltage cause of the same value*/

/*5v output voltage*/
#define POW_5vOutputToAD(vol)		((uint16)((uint32)(( (vol))*1024UL) * POW_5vOutput_Rdiv/(5U*(POW_5vOutput_R1+POW_5vOutput_Rdiv))) )
#define POW_5vOutputToValue(ad)		((uint16)(((( (uint32)(ad))*5UL*10UL) * (POW_5vOutput_R1+POW_5vOutput_Rdiv)/POW_5vOutput_Rdiv)>>10 ))


#if (POW_K30Abnormal ==  1)
/*#define POW_u16BatShortGndVoltageThreshold  		(uint16)(POW_SupplyVoltToADK30(0.5)-POW_AD_Offset)	
#define POW_u16BatShortGndVoltageRecoverValue 		(uint16)(POW_SupplyVoltToADK30(6.5)-POW_AD_Offset)	
#define POW_u16BatShortGndVoltageEnterTimeCfg  		(10)
#define POW_u16BatShortGndVoltageRecoverTimeCfg  	(10)
#define POW_u16BatShortGndLowIgnHystCfg       		(uint16)(POW_VoltToADIgn(0.5)) 
#define POW_u16BatShortGndIgnHighHystCfg      		(uint16)(POW_VoltToADIgn(0.5))*/
#define POW_u16BatShortGndHystCfg      			(2u*1000)/*  1000 time .voltage hysteresis value :2v*/
#endif


/*app*/
#if (POW_AppRef==POW_Ref_K30)
/*k30 as ref voltage*/
#define POW_u16AppSuperHighVoltageThreshold  		(uint16)(POW_SupplyVoltToADK30(19)-POW_AD_Offset)/*(uint16)(19.0U Volt) */    /* 16v   100k(battery)/400k(total)*/ 
#define POW_u16AppHighVoltageThreshold  			(uint16)(POW_SupplyVoltToADK30(16)-POW_AD_Offset)/*(uint16)(16.0U Volt) */    /* 16v   100k(battery)/400k(total)*/ 
#define POW_u16AppLowVoltageThreshold   			(uint16)(POW_SupplyVoltToADK30(9)-POW_AD_Offset)/*(uint16)(8.7U Volt) */    /* 8.7v */
#define POW_u16AppLowVoltageHystCfg       			(uint16)(POW_VoltToADK30(0.4)) /*low voltage hysteresis value of application module:0.7v*/
#define POW_u16AppHighVoltageHystCfg      			(uint16)(POW_VoltToADK30(0.4))/* high voltage hysteresis value of application module:0.7v*/
#endif
/*k15 as ref voltage*/
#define POW_u16AppSuperHighVoltageThresholdIgn  	(uint16)(POW_SupplyVoltToADIgn(19)-POW_AD_Offset)/*(uint16)(19.0U Volt) */    /* 16v   100k(battery)/400k(total)*/ 
#define POW_u16AppHighVoltageThresholdIgn  			(uint16)(POW_SupplyVoltToADIgn(16)-POW_AD_Offset)/*(uint16)(16.0U Volt) */    /* 16v   100k(battery)/400k(total)*/ 
#define POW_u16AppLowVoltageThresholdIgn   			(uint16)(POW_SupplyVoltToADIgn(9)-POW_AD_Offset)/*(uint16)(8.7U Volt) */    /* 8.7v */
#define POW_u16AppLowVoltageIgnHystCfg       		(uint16)(POW_VoltToADIgn(0.4)) /*low voltage hysteresis value of application module:0.7v*/
#define POW_u16AppHighVoltageIgnHystCfg      		(uint16)(POW_VoltToADIgn(0.4))/* high voltage hysteresis value of application module:0.7v*/


/*com*/
#if (POW_ComRef==POW_Ref_K30)
/* k30 as ref voltage */
#define POW_u16CanHighVoltageThreshold				(uint16)(POW_SupplyVoltToADK30(18)-POW_AD_Offset)/*(uint16)(18.0U Volt)*/		/*- 18V -*/
#define POW_u16CanLowVoltageThreshold				(uint16)(POW_SupplyVoltToADK30(7)-POW_AD_Offset)/*(uint16)(6.5 Volt)*/ /*- 6.5V  -*/
#define POW_u16CanHighVoltageHystCfg          			(uint16)(POW_VoltToADK30(0.5))       	/*voltage hysteresis value of the can net management:0.9*/  
#define POW_u16CanLowVoltageHystCfg          			(uint16)(POW_VoltToADK30(0.5))       	/*voltage hysteresis value of the can net management:0.9*/  
#endif
/* k15 as ref voltage */
#define POW_u16CanHighVoltageThresholdIgn			(uint16)(POW_SupplyVoltToADIgn(18)-POW_AD_Offset)/*(uint16)(18.0U Volt)*/		/*- 18V -*/
#define POW_u16CanLowVoltageThresholdIgn			(uint16)(POW_SupplyVoltToADIgn(7)-POW_AD_Offset)/*(uint16)(6.5 Volt)*/ /*- 6.5V  -*/
#define POW_u16CanHighVoltageIgnHystCfg          		(uint16)(POW_VoltToADIgn(0.5))       	/*voltage hysteresis value of the can net management:0.9*/  
#define POW_u16CanLowVoltageIgnHystCfg          		(uint16)(POW_VoltToADIgn(0.5))       	/*voltage hysteresis value of the can net management:0.9*/  


/*diag*/
#if (POW_DiagRef==POW_Ref_K30)
/* k30 as ref voltage */
#define POW_u16DiagHighVoltageThreshold			(uint16)(POW_SupplyVoltToADK30(15)-POW_AD_Offset)/*(uint16)(16.0U Volt) */
#define POW_u16DiagLowVoltageThreshold				(uint16)(POW_SupplyVoltToADK30(10)-POW_AD_Offset)/*(uint16)(9.0U Volt)*/
#define POW_u16DiagLowVoltageHystCfg         			(uint16)(POW_VoltToADK30(1))   /* low voltage hysteresis value of diagnostic module:0.5v(0-20v,x/1025*5*4) */
#define POW_u16DiagHighVoltageHystCfg        			(uint16)(POW_VoltToADK30(1))  /*high voltage hysteresis value of diagnostic module:0.5v*/	
#endif
/* k15 as ref voltage */
#define POW_u16DiagHighVoltageThresholdIgn			(uint16)(POW_SupplyVoltToADIgn(15)-POW_AD_Offset)/*(uint16)(16.0U Volt) */
#define POW_u16DiagLowVoltageThresholdIgn			(uint16)(POW_SupplyVoltToADIgn(10)-POW_AD_Offset)/*(uint16)(9.0U Volt)*/
#define POW_u16DiagLowVoltageIgnHystCfg         		(uint16)(POW_VoltToADIgn(0.5))   /* low voltage hysteresis value of diagnostic module:0.5v(0-20v,x/1025*5*4) */
#define POW_u16DiagHighVoltageIgnHystCfg        		(uint16)(POW_VoltToADIgn(1))  /*high voltage hysteresis value of diagnostic */


/*ref4*/
#if (POW_Ref4==POW_Ref_K30)
/* k30 as ref voltage */
#define POW_u16Ref4HighVoltageThreshold			(uint16)(POW_SupplyVoltToADK30(16)-POW_AD_Offset)/*(uint16)(16.0U Volt) */
#define POW_u16Ref4LowVoltageThreshold				(uint16)(POW_SupplyVoltToADK30(9.5)-POW_AD_Offset)/*(uint16)(9.0U Volt)*/
#define POW_u16Ref4LowVoltageHystCfg         			(uint16)(POW_VoltToADK30(0.5))   /* low voltage hysteresis value of diagnostic module:0.5v(0-20v,x/1025*5*4) */
#define POW_u16Ref4HighVoltageHystCfg        			(uint16)(POW_VoltToADK30(1))  /*high voltage hysteresis value of diagnostic module:0.5v*/	
#endif
/* k15 as ref voltage */
#define POW_u16Ref4HighVoltageThresholdIgn			(uint16)(POW_SupplyVoltToADIgn(16)-POW_AD_Offset)/*(uint16)(16.0U Volt) */
#define POW_u16Ref4LowVoltageThresholdIgn			(uint16)(POW_SupplyVoltToADIgn(9.5)-POW_AD_Offset)/*(uint16)(9.0U Volt)*/
#define POW_u16Ref4LowVoltageIgnHystCfg         		(uint16)(POW_VoltToADIgn(0.5))   /* low voltage hysteresis value of diagnostic module:0.5v(0-20v,x/1025*5*4) */
#define POW_u16Ref4HighVoltageIgnHystCfg        		(uint16)(POW_VoltToADIgn(1))  /*high voltage hysteresis value of diagnostic */






#define POW_u165vStableVolCfg          		(uint16)(POW_5vOutputToAD(4.5))       	/*voltage 4.5v*/  

#define POW_SupplyVot_10Times(vol)			(((uint32)(vol))*100/512	)	


/*---------------------adc channel definition--------------------------*/
#if (POW_RteUsed ==1)
/*define by rte*/
#else
#if (POW_K30FbUsed==1)
	#define POW_nRawKL30VtgFb				MCU_mADCID_ADCA0I13
	#if (POW_Ign2FbUsed==1)
		#define POW_nRawIGN2VtgFb				MCU_mADCID_ADCA0I0
	#endif
#endif

#if (POW_SensorSupplyFbUsed==1)	
	#define POW_nRaw5vSensorSupplyFb		MCU_mADCID_ADCA0I6	// 5v det
#endif

#if (POW_5vOutputFbUsed==1)
	#define POW_nRaw5vOutputFb				MCU_mADCID_ADCA0I8
#endif
#endif


/*-------------------------------------------------io  and significant bit config----------------------------------------*/
/*Power control for mcu supply*/
#if (POW_VccCutOffUsed ==1)
	#if (POW_RteUsed ==1)
	#else
		#define POW_McuSupply_PortPin		0 //0x0004
	
		#define POW_McuSupply_ValidLevel		1/*what level will turn on the power*/
	#endif
#endif


//4Power control for ALL sensor supply
#if (POW_SensorSupplyCtrlUsed==1)
#define POW_SensorSupply_PortPin	0x0005

#define POW_SensorSupply_ValidLevel		0/*what level will turn on the power*/
#endif

//4Power control for 5V output to the connector
#if (POW_5vOutPutCtrlUsed==1)
	#define POW_5vOutput_PortPin		0x000a
	#define POW_5vOutput_ValidLevel		1/*what level will turn on the power*/
#endif

#if POW_McuSupply_ValidLevel==1
#define POW_McuSupply_OnLevel	1
#define POW_McuSupply_OffLevel	0
#else
#define POW_McuSupply_OnLevel	0
#define POW_McuSupply_OffLevel	1
#endif

#if POW_SensorSupply_ValidLevel==1
#define POW_SensorSupply_OnLevel	1
#define POW_SensorSupply_OffLevel	0
#else
#define POW_SensorSupply_OnLevel	0
#define POW_SensorSupply_OffLevel	1
#endif

#if POW_5vOutput_ValidLevel==1
#define POW_5vOutput_OnLevel	1
#define POW_5vOutput_OffLevel	0
#else
#define POW_5vOutput_OnLevel	0
#define POW_5vOutput_OffLevel	1
#endif

				


/*****************************************************************************
* End of check if informations are already included
******************************************************************************/
#endif                                  /* ifndef POW_CFG_H */

/*****************************************************************************
* EOF: Pow_Cfg.h
******************************************************************************/

