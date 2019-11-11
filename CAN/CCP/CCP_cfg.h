/*******************************************************************************
| Module Name: Climate Calibration Processing Module. 
| File Name: CCP.c
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
| Zhong bin                       Desay SV Automotive Co., Ltd
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date            Ver         Author               Description
| ----------  -------  -------------  ------------------------------------------
 13/8/2012        V1.1            Zhong Bin           Creation.
 16/12/2015       V1.2            Lin Tao             First release for J72L  

*****************************************************************************/

#ifndef CCP_CFG_H
#define CCP_CFG_H

#include  "Rte_internal.h"
//#include "istp.H"
#include "EVAP.H"
#include "OAT.H"
#include "EED.h"
#include "DTC.h"
#include "Dcm.h"
#include "Sun.h"
#include "CCS.h"
//#include "Aqs.h"
#include "KEY.h"
#include "ACCC.h" 
#include "ACCC_interface.h"
#include "Hct.h"
#include "Mac.h"
#include "Aird.h"
#include "Bctl.h"
#include "BCTLDRV.h" 
#include "Pow.h"
#include "Mmi.h"
#include "CanApp.h"  
#include "LinApp.H"
//#include "Ion.h"
#include "RFA.H"
#include "IGN.H" 
#include "dim.h"
#include "DIM_interface.h"
#include "VEL.h" 
#include "Diag_Cfg.h"
#include "NCV77X9.h"
//#include "ICT.h"
#include "RDC.h"
#include "EVAP.h"
#include "CTS_Export.h"
#include "IPL.h"
#include "TBTS.h"
#include "VICT.h"
#include "KNOB.h"
#include "LCD.h"
#include "MAC.h"
#include "SHC.h"
#include "Ion.h"
#include "Frame.h"
#include "TOUCHKEY.h"
#include "force.h"

#define CCP_u8GetLowByte(value) 	(uint8)(value)
#define CCP_u8GetHighByte(value) 	(uint8)(value>>8)

#define GetDwordToByte0(value)		(uint8)(value)
#define GetDwordToByte1(value)		(uint8)(value>>8)
#define GetDwordToByte2(value)		(uint8)(value>>16)
#define GetDwordToByte3(value)		(uint8)(value>>24)

/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
******************************************************************************/
/* system-headerfiles*/


/* foreign headerfiles*/

/* Own headerfiles */

/* Define the const */
#define NO_USE						0

#define CCP_u8DataArray00_Byte1		TOUCHKEY_u8GetIicValue_L(0)
#define CCP_u8DataArray00_Byte2		TOUCHKEY_u8GetIicValue_L(1)
#define CCP_u8DataArray00_Byte3		TOUCHKEY_u8GetIicValue_L(2)
#define CCP_u8DataArray00_Byte4		TOUCHKEY_u8GetIicValue_L(3)
#define CCP_u8DataArray00_Byte5		TOUCHKEY_u8GetIicValue_L(4)
#define CCP_u8DataArray00_Byte6		TOUCHKEY_u8GetIicValue_L(5)
#define CCP_u8DataArray00_Byte7		TOUCHKEY_u8GetIicValue_L(6)

#define CCP_u8DataArray01_Byte1		TOUCHKEY_u8GetIicValue_L(7)
#define CCP_u8DataArray01_Byte2		TOUCHKEY_u8GetIicValue_L(8)
#define CCP_u8DataArray01_Byte3		TOUCHKEY_u8GetIicValue_L(9)
#define CCP_u8DataArray01_Byte4		TOUCHKEY_u8GetIicValue_L(10)
#define CCP_u8DataArray01_Byte5		TOUCHKEY_u8GetIicValue_L(11)
#define CCP_u8DataArray01_Byte6		TOUCHKEY_u8GetIicValue_L(12)
#define CCP_u8DataArray01_Byte7		TOUCHKEY_u8GetIicValue_L(13)

#define CCP_u8DataArray02_Byte1		TOUCHKEY_u8GetIicValue_L(14)
#define CCP_u8DataArray02_Byte2		TOUCHKEY_u8GetIicValue_L(15)
#define CCP_u8DataArray02_Byte3		TOUCHKEY_u8GetIicValue_L(16)
#define CCP_u8DataArray02_Byte4		TOUCHKEY_u8GetIicValue_L(17)
#define CCP_u8DataArray02_Byte5		TOUCHKEY_u8GetIicValue_L(18)
#define CCP_u8DataArray02_Byte6		TOUCHKEY_u8GetIicValue_L(19)
#define CCP_u8DataArray02_Byte7		TOUCHKEY_u8GetIicValue_L(20)

#define CCP_u8DataArray03_Byte1		TOUCHKEY_u8GetIicValue_L(21)
#define CCP_u8DataArray03_Byte2		TOUCHKEY_u8GetIicValue_L(22)
#define CCP_u8DataArray03_Byte3		CCP_u8GetHighByte(Force_u16ForceSensorADProcess())             //TOUCHKEY_u8GetIicValue_L(23)
#define CCP_u8DataArray03_Byte4		TOUCHKEY_u8GetIicValue_L(24)
#define CCP_u8DataArray03_Byte5		TOUCHKEY_u8GetIicValue_L(25)
#define CCP_u8DataArray03_Byte6		TOUCHKEY_u8GetIicValue_L(26)
#define CCP_u8DataArray03_Byte7		TOUCHKEY_u8GetIicValue_L(27)

#define CCP_u8DataArray04_Byte1		TOUCHKEY_u8GetIicValue_L(28)     //aboutLeft  Button_u8key()   //
#define CCP_u8DataArray04_Byte2		TOUCHKEY_u8GetIicValue_L(29)    //Button_u8key()    //aboutLeft
#define CCP_u8DataArray04_Byte3		NO_USE
#define CCP_u8DataArray04_Byte4		NO_USE
#define CCP_u8DataArray04_Byte5		NO_USE
#define CCP_u8DataArray04_Byte6		NO_USE
#define CCP_u8DataArray04_Byte7		NO_USE

#define CCP_u8DataArray05_Byte1		NO_USE  //about left comand 1
#define CCP_u8DataArray05_Byte2		NO_USE//about left comand 2
#define CCP_u8DataArray05_Byte3		NO_USE
#define CCP_u8DataArray05_Byte4		NO_USE
#define CCP_u8DataArray05_Byte5		NO_USE
#define CCP_u8DataArray05_Byte6		NO_USE
#define CCP_u8DataArray05_Byte7		NO_USE

#define CCP_u8DataArray06_Byte1		NO_USE//about right comand 1
#define CCP_u8DataArray06_Byte2		NO_USE//about right comand 2
#define CCP_u8DataArray06_Byte3		NO_USE
#define CCP_u8DataArray06_Byte4		NO_USE
#define CCP_u8DataArray06_Byte5		NO_USE
#define CCP_u8DataArray06_Byte6		NO_USE
#define CCP_u8DataArray06_Byte7		NO_USE

#define CCP_u8DataArray07_Byte1		NO_USE
#define CCP_u8DataArray07_Byte2		NO_USE
#define CCP_u8DataArray07_Byte3		NO_USE
#define CCP_u8DataArray07_Byte4		NO_USE
#define CCP_u8DataArray07_Byte5		NO_USE
#define CCP_u8DataArray07_Byte6		NO_USE
#define CCP_u8DataArray07_Byte7		NO_USE

#define CCP_u8DataArray08_Byte1		NO_USE
#define CCP_u8DataArray08_Byte2		NO_USE
#define CCP_u8DataArray08_Byte3		NO_USE
#define CCP_u8DataArray08_Byte4		NO_USE
#define CCP_u8DataArray08_Byte5		NO_USE
#define CCP_u8DataArray08_Byte6		NO_USE
#define CCP_u8DataArray08_Byte7		NO_USE

#define CCP_u8DataArray09_Byte1		NO_USE
#define CCP_u8DataArray09_Byte2		NO_USE
#define CCP_u8DataArray09_Byte3		NO_USE
#define CCP_u8DataArray09_Byte4		NO_USE
#define CCP_u8DataArray09_Byte5		NO_USE
#define CCP_u8DataArray09_Byte6		NO_USE
#define CCP_u8DataArray09_Byte7		NO_USE

#define CCP_u8DataArray0A_Byte1		NO_USE
#define CCP_u8DataArray0A_Byte2		NO_USE
#define CCP_u8DataArray0A_Byte3		NO_USE
#define CCP_u8DataArray0A_Byte4		NO_USE
#define CCP_u8DataArray0A_Byte5		NO_USE
#define CCP_u8DataArray0A_Byte6		NO_USE
#define CCP_u8DataArray0A_Byte7		NO_USE

#define CCP_u8DataArray0B_Byte1		NO_USE
#define CCP_u8DataArray0B_Byte2		NO_USE
#define CCP_u8DataArray0B_Byte3		NO_USE
#define CCP_u8DataArray0B_Byte4		NO_USE
#define CCP_u8DataArray0B_Byte5		NO_USE
#define CCP_u8DataArray0B_Byte6		NO_USE
#define CCP_u8DataArray0B_Byte7		NO_USE

#define CCP_u8DataArray0C_Byte1		NO_USE
#define CCP_u8DataArray0C_Byte2		NO_USE
#define CCP_u8DataArray0C_Byte3		NO_USE
#define CCP_u8DataArray0C_Byte4		NO_USE
#define CCP_u8DataArray0C_Byte5		NO_USE
#define CCP_u8DataArray0C_Byte6		NO_USE
#define CCP_u8DataArray0C_Byte7		NO_USE

#define CCP_u8DataArray0D_Byte1		NO_USE
#define CCP_u8DataArray0D_Byte2		NO_USE
#define CCP_u8DataArray0D_Byte3		NO_USE
#define CCP_u8DataArray0D_Byte4		NO_USE
#define CCP_u8DataArray0D_Byte5		NO_USE
#define CCP_u8DataArray0D_Byte6		NO_USE
#define CCP_u8DataArray0D_Byte7		NO_USE

#define CCP_u8DataArray0E_Byte1		NO_USE
#define CCP_u8DataArray0E_Byte2		NO_USE
#define CCP_u8DataArray0E_Byte3		NO_USE
#define CCP_u8DataArray0E_Byte4		NO_USE
#define CCP_u8DataArray0E_Byte5		NO_USE
#define CCP_u8DataArray0E_Byte6		NO_USE
#define CCP_u8DataArray0E_Byte7		NO_USE

#define CCP_u8DataArray0F_Byte1		NO_USE
#define CCP_u8DataArray0F_Byte2		NO_USE
#define CCP_u8DataArray0F_Byte3		NO_USE
#define CCP_u8DataArray0F_Byte4		NO_USE
#define CCP_u8DataArray0F_Byte5		NO_USE
#define CCP_u8DataArray0F_Byte6		NO_USE
#define CCP_u8DataArray0F_Byte7		NO_USE

#define CCP_u8DataArray10_Byte1		NO_USE
#define CCP_u8DataArray10_Byte2		NO_USE
#define CCP_u8DataArray10_Byte3		NO_USE
#define CCP_u8DataArray10_Byte4		NO_USE
#define CCP_u8DataArray10_Byte5		NO_USE
#define CCP_u8DataArray10_Byte6		NO_USE
#define CCP_u8DataArray10_Byte7		NO_USE

#define CCP_u8DataArray11_Byte1		NO_USE
#define CCP_u8DataArray11_Byte2		NO_USE
#define CCP_u8DataArray11_Byte3		NO_USE
#define CCP_u8DataArray11_Byte4		NO_USE
#define CCP_u8DataArray11_Byte5		NO_USE
#define CCP_u8DataArray11_Byte6		NO_USE
#define CCP_u8DataArray11_Byte7		NO_USE

#define CCP_u8DataArray12_Byte1		NO_USE
#define CCP_u8DataArray12_Byte2		NO_USE
#define CCP_u8DataArray12_Byte3		NO_USE
#define CCP_u8DataArray12_Byte4		NO_USE
#define CCP_u8DataArray12_Byte5		NO_USE
#define CCP_u8DataArray12_Byte6		NO_USE
#define CCP_u8DataArray12_Byte7		NO_USE

#define CCP_u8DataArray13_Byte1		NO_USE
#define CCP_u8DataArray13_Byte2		NO_USE
#define CCP_u8DataArray13_Byte3		NO_USE
#define CCP_u8DataArray13_Byte4		NO_USE
#define CCP_u8DataArray13_Byte5		NO_USE
#define CCP_u8DataArray13_Byte6		NO_USE
#define CCP_u8DataArray13_Byte7		NO_USE

#define CCP_u8DataArray14_Byte1		NO_USE
#define CCP_u8DataArray14_Byte2		NO_USE
#define CCP_u8DataArray14_Byte3		NO_USE
#define CCP_u8DataArray14_Byte4		NO_USE
#define CCP_u8DataArray14_Byte5		NO_USE
#define CCP_u8DataArray14_Byte6		NO_USE
#define CCP_u8DataArray14_Byte7		NO_USE

#define CCP_u8DataArray15_Byte1		NO_USE
#define CCP_u8DataArray15_Byte2		NO_USE
#define CCP_u8DataArray15_Byte3		NO_USE
#define CCP_u8DataArray15_Byte4		NO_USE
#define CCP_u8DataArray15_Byte5		NO_USE
#define CCP_u8DataArray15_Byte6		NO_USE
#define CCP_u8DataArray15_Byte7		NO_USE

#define CCP_u8DataArray16_Byte1		NO_USE
#define CCP_u8DataArray16_Byte2		NO_USE
#define CCP_u8DataArray16_Byte3		NO_USE
#define CCP_u8DataArray16_Byte4		NO_USE
#define CCP_u8DataArray16_Byte5		NO_USE
#define CCP_u8DataArray16_Byte6		NO_USE
#define CCP_u8DataArray16_Byte7		NO_USE

#define CCP_u8DataArray17_Byte1		NO_USE
#define CCP_u8DataArray17_Byte2		NO_USE
#define CCP_u8DataArray17_Byte3		NO_USE
#define CCP_u8DataArray17_Byte4		NO_USE
#define CCP_u8DataArray17_Byte5		NO_USE
#define CCP_u8DataArray17_Byte6		NO_USE
#define CCP_u8DataArray17_Byte7		NO_USE

#define CCP_u8DataArray18_Byte1		NO_USE
#define CCP_u8DataArray18_Byte2		NO_USE
#define CCP_u8DataArray18_Byte3		NO_USE
#define CCP_u8DataArray18_Byte4		NO_USE
#define CCP_u8DataArray18_Byte5		NO_USE
#define CCP_u8DataArray18_Byte6		NO_USE
#define CCP_u8DataArray18_Byte7		NO_USE

#define CCP_u8DataArray19_Byte1		NO_USE
#define CCP_u8DataArray19_Byte2		NO_USE
#define CCP_u8DataArray19_Byte3		NO_USE
#define CCP_u8DataArray19_Byte4		NO_USE
#define CCP_u8DataArray19_Byte5		NO_USE
#define CCP_u8DataArray19_Byte6		NO_USE
#define CCP_u8DataArray19_Byte7		NO_USE

#define CCP_u8DataArray1A_Byte1		NO_USE
#define CCP_u8DataArray1A_Byte2		NO_USE
#define CCP_u8DataArray1A_Byte3		NO_USE
#define CCP_u8DataArray1A_Byte4		NO_USE
#define CCP_u8DataArray1A_Byte5		NO_USE
#define CCP_u8DataArray1A_Byte6		NO_USE
#define CCP_u8DataArray1A_Byte7		NO_USE

#define CCP_u8DataArray1B_Byte1		NO_USE
#define CCP_u8DataArray1B_Byte2		NO_USE
#define CCP_u8DataArray1B_Byte3		NO_USE
#define CCP_u8DataArray1B_Byte4		NO_USE
#define CCP_u8DataArray1B_Byte5		NO_USE
#define CCP_u8DataArray1B_Byte6		NO_USE
#define CCP_u8DataArray1B_Byte7		NO_USE

#define CCP_u8DataArray1C_Byte1		NO_USE
#define CCP_u8DataArray1C_Byte2		NO_USE
#define CCP_u8DataArray1C_Byte3		NO_USE
#define CCP_u8DataArray1C_Byte4		NO_USE
#define CCP_u8DataArray1C_Byte5		NO_USE
#define CCP_u8DataArray1C_Byte6		NO_USE
#define CCP_u8DataArray1C_Byte7		NO_USE

#define CCP_u8DataArray1D_Byte1		NO_USE
#define CCP_u8DataArray1D_Byte2		NO_USE
#define CCP_u8DataArray1D_Byte3		NO_USE
#define CCP_u8DataArray1D_Byte4		NO_USE
#define CCP_u8DataArray1D_Byte5		NO_USE
#define CCP_u8DataArray1D_Byte6		NO_USE
#define CCP_u8DataArray1D_Byte7		NO_USE

#define CCP_u8DataArray1E_Byte1		NO_USE
#define CCP_u8DataArray1E_Byte2		NO_USE
#define CCP_u8DataArray1E_Byte3		NO_USE
#define CCP_u8DataArray1E_Byte4		NO_USE
#define CCP_u8DataArray1E_Byte5		NO_USE
#define CCP_u8DataArray1E_Byte6		NO_USE
#define CCP_u8DataArray1E_Byte7		NO_USE

#define CCP_u8DataArray1F_Byte1		NO_USE
#define CCP_u8DataArray1F_Byte2		NO_USE
#define CCP_u8DataArray1F_Byte3		NO_USE
#define CCP_u8DataArray1F_Byte4		NO_USE
#define CCP_u8DataArray1F_Byte5		NO_USE
#define CCP_u8DataArray1F_Byte6		NO_USE
#define CCP_u8DataArray1F_Byte7		NO_USE

#define CCP_u8DataArray20_Byte1		NO_USE
#define CCP_u8DataArray20_Byte2		NO_USE
#define CCP_u8DataArray20_Byte3		NO_USE
#define CCP_u8DataArray20_Byte4		NO_USE
#define CCP_u8DataArray20_Byte5		NO_USE
#define CCP_u8DataArray20_Byte6		NO_USE
#define CCP_u8DataArray20_Byte7		NO_USE

#define CCP_u8DataArray21_Byte1		NO_USE
#define CCP_u8DataArray21_Byte2		NO_USE
#define CCP_u8DataArray21_Byte3		NO_USE
#define CCP_u8DataArray21_Byte4		NO_USE
#define CCP_u8DataArray21_Byte5		NO_USE
#define CCP_u8DataArray21_Byte6		NO_USE
#define CCP_u8DataArray21_Byte7		NO_USE

#define CCP_u8DataArray22_Byte1		NO_USE
#define CCP_u8DataArray22_Byte2		NO_USE
#define CCP_u8DataArray22_Byte3		NO_USE
#define CCP_u8DataArray22_Byte4		NO_USE
#define CCP_u8DataArray22_Byte5		NO_USE
#define CCP_u8DataArray22_Byte6		NO_USE
#define CCP_u8DataArray22_Byte7		NO_USE

#define CCP_u8DataArray23_Byte1		NO_USE
#define CCP_u8DataArray23_Byte2		NO_USE
#define CCP_u8DataArray23_Byte3		NO_USE
#define CCP_u8DataArray23_Byte4		NO_USE
#define CCP_u8DataArray23_Byte5		NO_USE
#define CCP_u8DataArray23_Byte6		NO_USE
#define CCP_u8DataArray23_Byte7		NO_USE

#define CCP_u8DataArray24_Byte1		NO_USE
#define CCP_u8DataArray24_Byte2		NO_USE
#define CCP_u8DataArray24_Byte3		NO_USE
#define CCP_u8DataArray24_Byte4		NO_USE
#define CCP_u8DataArray24_Byte5		NO_USE
#define CCP_u8DataArray24_Byte6		NO_USE
#define CCP_u8DataArray24_Byte7		NO_USE

#define CCP_u8DataArray25_Byte1		NO_USE
#define CCP_u8DataArray25_Byte2		NO_USE
#define CCP_u8DataArray25_Byte3		NO_USE
#define CCP_u8DataArray25_Byte4		NO_USE
#define CCP_u8DataArray25_Byte5		NO_USE
#define CCP_u8DataArray25_Byte6		NO_USE
#define CCP_u8DataArray25_Byte7		NO_USE

#define CCP_u8DataArray26_Byte1		NO_USE
#define CCP_u8DataArray26_Byte2		NO_USE
#define CCP_u8DataArray26_Byte3		NO_USE
#define CCP_u8DataArray26_Byte4		NO_USE
#define CCP_u8DataArray26_Byte5		NO_USE
#define CCP_u8DataArray26_Byte6		NO_USE
#define CCP_u8DataArray26_Byte7		NO_USE

#define CCP_u8DataArray27_Byte1		NO_USE
#define CCP_u8DataArray27_Byte2		NO_USE
#define CCP_u8DataArray27_Byte3		NO_USE
#define CCP_u8DataArray27_Byte4		NO_USE
#define CCP_u8DataArray27_Byte5		NO_USE
#define CCP_u8DataArray27_Byte6		NO_USE
#define CCP_u8DataArray27_Byte7		NO_USE

#define CCP_u8DataArray28_Byte1		NO_USE
#define CCP_u8DataArray28_Byte2		NO_USE
#define CCP_u8DataArray28_Byte3		NO_USE
#define CCP_u8DataArray28_Byte4		NO_USE
#define CCP_u8DataArray28_Byte5		NO_USE
#define CCP_u8DataArray28_Byte6		NO_USE
#define CCP_u8DataArray28_Byte7		NO_USE

#define CCP_u8DataArray29_Byte1		NO_USE
#define CCP_u8DataArray29_Byte2		NO_USE
#define CCP_u8DataArray29_Byte3		NO_USE
#define CCP_u8DataArray29_Byte4		NO_USE
#define CCP_u8DataArray29_Byte5		NO_USE
#define CCP_u8DataArray29_Byte6		NO_USE
#define CCP_u8DataArray29_Byte7		NO_USE

#define CCP_u8DataArray2A_Byte1		NO_USE
#define CCP_u8DataArray2A_Byte2		NO_USE
#define CCP_u8DataArray2A_Byte3		NO_USE
#define CCP_u8DataArray2A_Byte4		NO_USE
#define CCP_u8DataArray2A_Byte5		NO_USE
#define CCP_u8DataArray2A_Byte6		NO_USE
#define CCP_u8DataArray2A_Byte7		NO_USE

#define CCP_u8DataArray2B_Byte1		NO_USE
#define CCP_u8DataArray2B_Byte2		NO_USE
#define CCP_u8DataArray2B_Byte3		NO_USE
#define CCP_u8DataArray2B_Byte4		NO_USE
#define CCP_u8DataArray2B_Byte5		NO_USE
#define CCP_u8DataArray2B_Byte6		NO_USE
#define CCP_u8DataArray2B_Byte7		NO_USE

#define CCP_u8DataArray2C_Byte1		NO_USE
#define CCP_u8DataArray2C_Byte2		NO_USE
#define CCP_u8DataArray2C_Byte3		NO_USE
#define CCP_u8DataArray2C_Byte4		NO_USE
#define CCP_u8DataArray2C_Byte5		NO_USE
#define CCP_u8DataArray2C_Byte6		NO_USE
#define CCP_u8DataArray2C_Byte7		NO_USE

#define CCP_u8DataArray2D_Byte1		NO_USE
#define CCP_u8DataArray2D_Byte2		NO_USE
#define CCP_u8DataArray2D_Byte3		NO_USE
#define CCP_u8DataArray2D_Byte4		NO_USE
#define CCP_u8DataArray2D_Byte5		NO_USE
#define CCP_u8DataArray2D_Byte6		NO_USE
#define CCP_u8DataArray2D_Byte7		NO_USE

#define CCP_u8DataArray2E_Byte1		NO_USE
#define CCP_u8DataArray2E_Byte2		NO_USE
#define CCP_u8DataArray2E_Byte3		NO_USE
#define CCP_u8DataArray2E_Byte4		NO_USE
#define CCP_u8DataArray2E_Byte5		NO_USE
#define CCP_u8DataArray2E_Byte6		NO_USE
#define CCP_u8DataArray2E_Byte7		NO_USE

#define CCP_u8DataArray2F_Byte1		NO_USE
#define CCP_u8DataArray2F_Byte2		NO_USE
#define CCP_u8DataArray2F_Byte3		NO_USE
#define CCP_u8DataArray2F_Byte4		NO_USE
#define CCP_u8DataArray2F_Byte5		NO_USE
#define CCP_u8DataArray2F_Byte6		NO_USE
#define CCP_u8DataArray2F_Byte7		NO_USE

#define CCP_u8DataArray30_Byte1		NO_USE
#define CCP_u8DataArray30_Byte2		NO_USE
#define CCP_u8DataArray30_Byte3		NO_USE
#define CCP_u8DataArray30_Byte4		NO_USE
#define CCP_u8DataArray30_Byte5		NO_USE
#define CCP_u8DataArray30_Byte6		NO_USE
#define CCP_u8DataArray30_Byte7		NO_USE

#define CCP_u8DataArray31_Byte1		NO_USE
#define CCP_u8DataArray31_Byte2		NO_USE
#define CCP_u8DataArray31_Byte3		NO_USE
#define CCP_u8DataArray31_Byte4		NO_USE
#define CCP_u8DataArray31_Byte5		NO_USE
#define CCP_u8DataArray31_Byte6		NO_USE
#define CCP_u8DataArray31_Byte7		NO_USE

#define CCP_u8DataArray32_Byte1		NO_USE
#define CCP_u8DataArray32_Byte2		NO_USE
#define CCP_u8DataArray32_Byte3		NO_USE
#define CCP_u8DataArray32_Byte4		NO_USE
#define CCP_u8DataArray32_Byte5		NO_USE
#define CCP_u8DataArray32_Byte6		NO_USE
#define CCP_u8DataArray32_Byte7		NO_USE

#define CCP_u8DataArray33_Byte1		NO_USE
#define CCP_u8DataArray33_Byte2		NO_USE
#define CCP_u8DataArray33_Byte3		NO_USE
#define CCP_u8DataArray33_Byte4		NO_USE
#define CCP_u8DataArray33_Byte5		NO_USE
#define CCP_u8DataArray33_Byte6		NO_USE
#define CCP_u8DataArray33_Byte7		NO_USE

#define CCP_u8DataArray34_Byte1		NO_USE
#define CCP_u8DataArray34_Byte2		NO_USE
#define CCP_u8DataArray34_Byte3		NO_USE
#define CCP_u8DataArray34_Byte4		NO_USE
#define CCP_u8DataArray34_Byte5		NO_USE
#define CCP_u8DataArray34_Byte6		NO_USE
#define CCP_u8DataArray34_Byte7		NO_USE

#define CCP_u8DataArray35_Byte1		NO_USE
#define CCP_u8DataArray35_Byte2		NO_USE
#define CCP_u8DataArray35_Byte3		NO_USE
#define CCP_u8DataArray35_Byte4		NO_USE
#define CCP_u8DataArray35_Byte5		NO_USE
#define CCP_u8DataArray35_Byte6		NO_USE
#define CCP_u8DataArray35_Byte7		NO_USE

#define CCP_u8DataArray36_Byte1		NO_USE
#define CCP_u8DataArray36_Byte2		NO_USE
#define CCP_u8DataArray36_Byte3		NO_USE
#define CCP_u8DataArray36_Byte4		NO_USE
#define CCP_u8DataArray36_Byte5		NO_USE
#define CCP_u8DataArray36_Byte6		NO_USE
#define CCP_u8DataArray36_Byte7		NO_USE

#define CCP_u8DataArray37_Byte1		NO_USE
#define CCP_u8DataArray37_Byte2		NO_USE
#define CCP_u8DataArray37_Byte3		NO_USE
#define CCP_u8DataArray37_Byte4		NO_USE
#define CCP_u8DataArray37_Byte5		NO_USE
#define CCP_u8DataArray37_Byte6		NO_USE
#define CCP_u8DataArray37_Byte7		NO_USE

#define CCP_u8DataArray38_Byte1		NO_USE
#define CCP_u8DataArray38_Byte2		NO_USE
#define CCP_u8DataArray38_Byte3		NO_USE
#define CCP_u8DataArray38_Byte4		NO_USE
#define CCP_u8DataArray38_Byte5		NO_USE
#define CCP_u8DataArray38_Byte6		NO_USE
#define CCP_u8DataArray38_Byte7		NO_USE

#define CCP_u8DataArray39_Byte1		NO_USE
#define CCP_u8DataArray39_Byte2		NO_USE
#define CCP_u8DataArray39_Byte3		NO_USE
#define CCP_u8DataArray39_Byte4		NO_USE
#define CCP_u8DataArray39_Byte5		NO_USE
#define CCP_u8DataArray39_Byte6		NO_USE
#define CCP_u8DataArray39_Byte7		NO_USE

#define CCP_u8DataArray3A_Byte1		NO_USE
#define CCP_u8DataArray3A_Byte2		NO_USE
#define CCP_u8DataArray3A_Byte3		NO_USE
#define CCP_u8DataArray3A_Byte4		NO_USE
#define CCP_u8DataArray3A_Byte5		NO_USE
#define CCP_u8DataArray3A_Byte6		NO_USE
#define CCP_u8DataArray3A_Byte7		NO_USE

#define CCP_u8DataArray3B_Byte1		NO_USE
#define CCP_u8DataArray3B_Byte2		NO_USE
#define CCP_u8DataArray3B_Byte3		NO_USE
#define CCP_u8DataArray3B_Byte4		NO_USE
#define CCP_u8DataArray3B_Byte5		NO_USE
#define CCP_u8DataArray3B_Byte6		NO_USE
#define CCP_u8DataArray3B_Byte7		NO_USE

#define CCP_u8DataArray3C_Byte1		NO_USE
#define CCP_u8DataArray3C_Byte2		NO_USE
#define CCP_u8DataArray3C_Byte3		NO_USE
#define CCP_u8DataArray3C_Byte4		NO_USE
#define CCP_u8DataArray3C_Byte5		NO_USE
#define CCP_u8DataArray3C_Byte6		NO_USE
#define CCP_u8DataArray3C_Byte7		NO_USE

#define CCP_u8DataArray3D_Byte1		NO_USE
#define CCP_u8DataArray3D_Byte2		NO_USE
#define CCP_u8DataArray3D_Byte3		NO_USE
#define CCP_u8DataArray3D_Byte4		NO_USE
#define CCP_u8DataArray3D_Byte5		NO_USE
#define CCP_u8DataArray3D_Byte6		NO_USE
#define CCP_u8DataArray3D_Byte7		NO_USE

#define CCP_u8DataArray3E_Byte1		NO_USE
#define CCP_u8DataArray3E_Byte2		NO_USE
#define CCP_u8DataArray3E_Byte3		NO_USE
#define CCP_u8DataArray3E_Byte4		NO_USE
#define CCP_u8DataArray3E_Byte5		NO_USE
#define CCP_u8DataArray3E_Byte6		NO_USE
#define CCP_u8DataArray3E_Byte7		NO_USE

#define CCP_u8DataArray3F_Byte1		NO_USE
#define CCP_u8DataArray3F_Byte2		NO_USE
#define CCP_u8DataArray3F_Byte3		NO_USE
#define CCP_u8DataArray3F_Byte4		NO_USE
#define CCP_u8DataArray3F_Byte5		NO_USE
#define CCP_u8DataArray3F_Byte6		NO_USE
#define CCP_u8DataArray3F_Byte7		NO_USE

#define CCP_u8DataArray40_Byte1		NO_USE
#define CCP_u8DataArray40_Byte2		NO_USE
#define CCP_u8DataArray40_Byte3		NO_USE
#define CCP_u8DataArray40_Byte4		NO_USE
#define CCP_u8DataArray40_Byte5		NO_USE
#define CCP_u8DataArray40_Byte6		NO_USE
#define CCP_u8DataArray40_Byte7		NO_USE

#define CCP_u8DataArray41_Byte1		NO_USE
#define CCP_u8DataArray41_Byte2		NO_USE
#define CCP_u8DataArray41_Byte3		NO_USE
#define CCP_u8DataArray41_Byte4		NO_USE
#define CCP_u8DataArray41_Byte5		NO_USE
#define CCP_u8DataArray41_Byte6		NO_USE
#define CCP_u8DataArray41_Byte7		NO_USE

#define CCP_u8DataArray42_Byte1		NO_USE
#define CCP_u8DataArray42_Byte2		NO_USE
#define CCP_u8DataArray42_Byte3		NO_USE
#define CCP_u8DataArray42_Byte4		NO_USE
#define CCP_u8DataArray42_Byte5		NO_USE
#define CCP_u8DataArray42_Byte6		NO_USE
#define CCP_u8DataArray42_Byte7		NO_USE

#define CCP_u8DataArray43_Byte1		NO_USE
#define CCP_u8DataArray43_Byte2		NO_USE
#define CCP_u8DataArray43_Byte3		NO_USE
#define CCP_u8DataArray43_Byte4		NO_USE
#define CCP_u8DataArray43_Byte5		NO_USE
#define CCP_u8DataArray43_Byte6		NO_USE
#define CCP_u8DataArray43_Byte7		NO_USE

#define CCP_u8DataArray44_Byte1		NO_USE
#define CCP_u8DataArray44_Byte2		NO_USE
#define CCP_u8DataArray44_Byte3		NO_USE
#define CCP_u8DataArray44_Byte4		NO_USE
#define CCP_u8DataArray44_Byte5		NO_USE
#define CCP_u8DataArray44_Byte6		NO_USE
#define CCP_u8DataArray44_Byte7		NO_USE

#define CCP_u8DataArray45_Byte1		NO_USE
#define CCP_u8DataArray45_Byte2		NO_USE
#define CCP_u8DataArray45_Byte3		NO_USE
#define CCP_u8DataArray45_Byte4		NO_USE
#define CCP_u8DataArray45_Byte5		NO_USE
#define CCP_u8DataArray45_Byte6		NO_USE
#define CCP_u8DataArray45_Byte7		NO_USE

#define CCP_u8DataArray46_Byte1		NO_USE
#define CCP_u8DataArray46_Byte2		NO_USE
#define CCP_u8DataArray46_Byte3		NO_USE
#define CCP_u8DataArray46_Byte4		NO_USE
#define CCP_u8DataArray46_Byte5		NO_USE
#define CCP_u8DataArray46_Byte6		NO_USE
#define CCP_u8DataArray46_Byte7		NO_USE

#define CCP_u8DataArray47_Byte1		NO_USE
#define CCP_u8DataArray47_Byte2		NO_USE
#define CCP_u8DataArray47_Byte3		NO_USE
#define CCP_u8DataArray47_Byte4		NO_USE
#define CCP_u8DataArray47_Byte5		NO_USE
#define CCP_u8DataArray47_Byte6		NO_USE
#define CCP_u8DataArray47_Byte7		NO_USE

#define CCP_u8DataArray48_Byte1		NO_USE
#define CCP_u8DataArray48_Byte2		NO_USE
#define CCP_u8DataArray48_Byte3		NO_USE
#define CCP_u8DataArray48_Byte4		NO_USE
#define CCP_u8DataArray48_Byte5		NO_USE
#define CCP_u8DataArray48_Byte6		NO_USE
#define CCP_u8DataArray48_Byte7		NO_USE

#define CCP_u8DataArray49_Byte1		NO_USE
#define CCP_u8DataArray49_Byte2		NO_USE
#define CCP_u8DataArray49_Byte3		NO_USE
#define CCP_u8DataArray49_Byte4		NO_USE
#define CCP_u8DataArray49_Byte5		NO_USE
#define CCP_u8DataArray49_Byte6		NO_USE
#define CCP_u8DataArray49_Byte7		NO_USE

#define CCP_u8DataArray4A_Byte1		NO_USE
#define CCP_u8DataArray4A_Byte2		NO_USE
#define CCP_u8DataArray4A_Byte3		NO_USE
#define CCP_u8DataArray4A_Byte4		NO_USE
#define CCP_u8DataArray4A_Byte5		NO_USE
#define CCP_u8DataArray4A_Byte6		NO_USE
#define CCP_u8DataArray4A_Byte7		NO_USE

#define CCP_u8DataArray4B_Byte1		NO_USE
#define CCP_u8DataArray4B_Byte2		NO_USE
#define CCP_u8DataArray4B_Byte3		NO_USE
#define CCP_u8DataArray4B_Byte4		NO_USE
#define CCP_u8DataArray4B_Byte5		NO_USE
#define CCP_u8DataArray4B_Byte6		NO_USE
#define CCP_u8DataArray4B_Byte7		NO_USE

#define CCP_u8DataArray4C_Byte1		NO_USE
#define CCP_u8DataArray4C_Byte2		NO_USE
#define CCP_u8DataArray4C_Byte3		NO_USE
#define CCP_u8DataArray4C_Byte4		NO_USE
#define CCP_u8DataArray4C_Byte5		NO_USE
#define CCP_u8DataArray4C_Byte6		NO_USE
#define CCP_u8DataArray4C_Byte7		NO_USE

#define CCP_u8DataArray4D_Byte1		NO_USE
#define CCP_u8DataArray4D_Byte2		NO_USE
#define CCP_u8DataArray4D_Byte3		NO_USE
#define CCP_u8DataArray4D_Byte4		NO_USE
#define CCP_u8DataArray4D_Byte5		NO_USE
#define CCP_u8DataArray4D_Byte6		NO_USE
#define CCP_u8DataArray4D_Byte7		NO_USE

#define CCP_u8DataArray4E_Byte1		NO_USE
#define CCP_u8DataArray4E_Byte2		NO_USE
#define CCP_u8DataArray4E_Byte3		NO_USE
#define CCP_u8DataArray4E_Byte4		NO_USE
#define CCP_u8DataArray4E_Byte5		NO_USE
#define CCP_u8DataArray4E_Byte6		NO_USE
#define CCP_u8DataArray4E_Byte7		NO_USE

#define CCP_u8DataArray4F_Byte1		NO_USE
#define CCP_u8DataArray4F_Byte2		NO_USE
#define CCP_u8DataArray4F_Byte3		NO_USE
#define CCP_u8DataArray4F_Byte4		NO_USE
#define CCP_u8DataArray4F_Byte5		NO_USE
#define CCP_u8DataArray4F_Byte6		NO_USE
#define CCP_u8DataArray4F_Byte7		NO_USE

#define CCP_u8DataArray50_Byte1		NO_USE
#define CCP_u8DataArray50_Byte2		NO_USE
#define CCP_u8DataArray50_Byte3		NO_USE
#define CCP_u8DataArray50_Byte4		NO_USE
#define CCP_u8DataArray50_Byte5		NO_USE
#define CCP_u8DataArray50_Byte6		NO_USE
#define CCP_u8DataArray50_Byte7		NO_USE

#define CCP_u8DataArray51_Byte1		NO_USE
#define CCP_u8DataArray51_Byte2		NO_USE
#define CCP_u8DataArray51_Byte3		NO_USE
#define CCP_u8DataArray51_Byte4		NO_USE
#define CCP_u8DataArray51_Byte5		NO_USE
#define CCP_u8DataArray51_Byte6		NO_USE
#define CCP_u8DataArray51_Byte7		NO_USE

#define CCP_u8DataArray52_Byte1		NO_USE
#define CCP_u8DataArray52_Byte2		NO_USE
#define CCP_u8DataArray52_Byte3		NO_USE
#define CCP_u8DataArray52_Byte4		NO_USE
#define CCP_u8DataArray52_Byte5		NO_USE
#define CCP_u8DataArray52_Byte6		NO_USE
#define CCP_u8DataArray52_Byte7		NO_USE

#define CCP_u8DataArray53_Byte1		NO_USE
#define CCP_u8DataArray53_Byte2		NO_USE
#define CCP_u8DataArray53_Byte3		NO_USE
#define CCP_u8DataArray53_Byte4		NO_USE
#define CCP_u8DataArray53_Byte5		NO_USE
#define CCP_u8DataArray53_Byte6		NO_USE
#define CCP_u8DataArray53_Byte7		NO_USE

#define CCP_u8DataArray54_Byte1		NO_USE
#define CCP_u8DataArray54_Byte2		NO_USE
#define CCP_u8DataArray54_Byte3		NO_USE
#define CCP_u8DataArray54_Byte4		NO_USE
#define CCP_u8DataArray54_Byte5		NO_USE
#define CCP_u8DataArray54_Byte6		NO_USE
#define CCP_u8DataArray54_Byte7		NO_USE

#define CCP_u8DataArray55_Byte1		NO_USE
#define CCP_u8DataArray55_Byte2		NO_USE
#define CCP_u8DataArray55_Byte3		NO_USE
#define CCP_u8DataArray55_Byte4		NO_USE
#define CCP_u8DataArray55_Byte5		NO_USE
#define CCP_u8DataArray55_Byte6		NO_USE
#define CCP_u8DataArray55_Byte7		NO_USE

#define CCP_u8DataArray56_Byte1		NO_USE
#define CCP_u8DataArray56_Byte2		NO_USE
#define CCP_u8DataArray56_Byte3		NO_USE
#define CCP_u8DataArray56_Byte4		NO_USE
#define CCP_u8DataArray56_Byte5		NO_USE
#define CCP_u8DataArray56_Byte6		NO_USE
#define CCP_u8DataArray56_Byte7		NO_USE

#define CCP_u8DataArray57_Byte1		NO_USE
#define CCP_u8DataArray57_Byte2		NO_USE
#define CCP_u8DataArray57_Byte3		NO_USE
#define CCP_u8DataArray57_Byte4		NO_USE
#define CCP_u8DataArray57_Byte5		NO_USE
#define CCP_u8DataArray57_Byte6		NO_USE
#define CCP_u8DataArray57_Byte7		NO_USE

#define CCP_u8DataArray58_Byte1		NO_USE
#define CCP_u8DataArray58_Byte2		NO_USE
#define CCP_u8DataArray58_Byte3		NO_USE
#define CCP_u8DataArray58_Byte4		NO_USE
#define CCP_u8DataArray58_Byte5		NO_USE
#define CCP_u8DataArray58_Byte6		NO_USE
#define CCP_u8DataArray58_Byte7		NO_USE

#define CCP_u8DataArray59_Byte1		NO_USE
#define CCP_u8DataArray59_Byte2		NO_USE
#define CCP_u8DataArray59_Byte3		NO_USE
#define CCP_u8DataArray59_Byte4		NO_USE
#define CCP_u8DataArray59_Byte5		NO_USE
#define CCP_u8DataArray59_Byte6		NO_USE
#define CCP_u8DataArray59_Byte7		NO_USE

#define CCP_u8DataArray5A_Byte1		NO_USE
#define CCP_u8DataArray5A_Byte2		NO_USE
#define CCP_u8DataArray5A_Byte3		NO_USE
#define CCP_u8DataArray5A_Byte4		NO_USE
#define CCP_u8DataArray5A_Byte5		NO_USE
#define CCP_u8DataArray5A_Byte6		NO_USE
#define CCP_u8DataArray5A_Byte7		NO_USE

#define CCP_u8DataArray5B_Byte1		NO_USE
#define CCP_u8DataArray5B_Byte2		NO_USE
#define CCP_u8DataArray5B_Byte3		NO_USE
#define CCP_u8DataArray5B_Byte4		NO_USE
#define CCP_u8DataArray5B_Byte5		NO_USE
#define CCP_u8DataArray5B_Byte6		NO_USE
#define CCP_u8DataArray5B_Byte7		NO_USE

#define CCP_u8DataArray5C_Byte1		NO_USE
#define CCP_u8DataArray5C_Byte2		NO_USE
#define CCP_u8DataArray5C_Byte3		NO_USE
#define CCP_u8DataArray5C_Byte4		NO_USE
#define CCP_u8DataArray5C_Byte5		NO_USE
#define CCP_u8DataArray5C_Byte6		NO_USE
#define CCP_u8DataArray5C_Byte7		NO_USE

#define CCP_u8DataArray5D_Byte1		NO_USE
#define CCP_u8DataArray5D_Byte2		NO_USE
#define CCP_u8DataArray5D_Byte3		NO_USE
#define CCP_u8DataArray5D_Byte4		NO_USE
#define CCP_u8DataArray5D_Byte5		NO_USE
#define CCP_u8DataArray5D_Byte6		NO_USE
#define CCP_u8DataArray5D_Byte7		NO_USE

#define CCP_u8DataArray5E_Byte1		NO_USE
#define CCP_u8DataArray5E_Byte2		NO_USE
#define CCP_u8DataArray5E_Byte3		NO_USE
#define CCP_u8DataArray5E_Byte4		NO_USE
#define CCP_u8DataArray5E_Byte5		NO_USE
#define CCP_u8DataArray5E_Byte6		NO_USE
#define CCP_u8DataArray5E_Byte7		NO_USE

#define CCP_u8DataArray5F_Byte1		NO_USE
#define CCP_u8DataArray5F_Byte2		NO_USE
#define CCP_u8DataArray5F_Byte3		NO_USE
#define CCP_u8DataArray5F_Byte4		NO_USE
#define CCP_u8DataArray5F_Byte5		NO_USE
#define CCP_u8DataArray5F_Byte6		NO_USE
#define CCP_u8DataArray5F_Byte7		NO_USE

#define CCP_u8DataArray60_Byte1		NO_USE
#define CCP_u8DataArray60_Byte2		NO_USE
#define CCP_u8DataArray60_Byte3		NO_USE
#define CCP_u8DataArray60_Byte4		NO_USE
#define CCP_u8DataArray60_Byte5		NO_USE
#define CCP_u8DataArray60_Byte6		NO_USE
#define CCP_u8DataArray60_Byte7		NO_USE

#define CCP_u8DataArray61_Byte1		NO_USE
#define CCP_u8DataArray61_Byte2		NO_USE
#define CCP_u8DataArray61_Byte3		NO_USE
#define CCP_u8DataArray61_Byte4		NO_USE
#define CCP_u8DataArray61_Byte5		NO_USE
#define CCP_u8DataArray61_Byte6		NO_USE
#define CCP_u8DataArray61_Byte7		NO_USE

#define CCP_u8DataArray62_Byte1		NO_USE
#define CCP_u8DataArray62_Byte2		NO_USE
#define CCP_u8DataArray62_Byte3		NO_USE
#define CCP_u8DataArray62_Byte4		NO_USE
#define CCP_u8DataArray62_Byte5		NO_USE
#define CCP_u8DataArray62_Byte6		NO_USE
#define CCP_u8DataArray62_Byte7		NO_USE

#define CCP_u8DataArray63_Byte1		NO_USE
#define CCP_u8DataArray63_Byte2		NO_USE
#define CCP_u8DataArray63_Byte3		NO_USE
#define CCP_u8DataArray63_Byte4		NO_USE
#define CCP_u8DataArray63_Byte5		NO_USE
#define CCP_u8DataArray63_Byte6		NO_USE
#define CCP_u8DataArray63_Byte7		NO_USE

#define CCP_u8DataArray64_Byte1		NO_USE
#define CCP_u8DataArray64_Byte2		NO_USE
#define CCP_u8DataArray64_Byte3		NO_USE
#define CCP_u8DataArray64_Byte4		NO_USE
#define CCP_u8DataArray64_Byte5		NO_USE
#define CCP_u8DataArray64_Byte6		NO_USE
#define CCP_u8DataArray64_Byte7		NO_USE

#define CCP_u8DataArray65_Byte1		NO_USE
#define CCP_u8DataArray65_Byte2		NO_USE
#define CCP_u8DataArray65_Byte3		NO_USE
#define CCP_u8DataArray65_Byte4		NO_USE
#define CCP_u8DataArray65_Byte5		NO_USE
#define CCP_u8DataArray65_Byte6		NO_USE
#define CCP_u8DataArray65_Byte7		NO_USE

#define CCP_u8DataArray66_Byte1		NO_USE
#define CCP_u8DataArray66_Byte2		NO_USE
#define CCP_u8DataArray66_Byte3		NO_USE
#define CCP_u8DataArray66_Byte4		NO_USE
#define CCP_u8DataArray66_Byte5		NO_USE
#define CCP_u8DataArray66_Byte6		NO_USE
#define CCP_u8DataArray66_Byte7		NO_USE

#define CCP_u8DataArray67_Byte1		NO_USE
#define CCP_u8DataArray67_Byte2		NO_USE
#define CCP_u8DataArray67_Byte3		NO_USE
#define CCP_u8DataArray67_Byte4		NO_USE
#define CCP_u8DataArray67_Byte5		NO_USE
#define CCP_u8DataArray67_Byte6		NO_USE
#define CCP_u8DataArray67_Byte7		NO_USE

#define CCP_u8DataArray68_Byte1		NO_USE
#define CCP_u8DataArray68_Byte2		NO_USE
#define CCP_u8DataArray68_Byte3		NO_USE
#define CCP_u8DataArray68_Byte4		NO_USE
#define CCP_u8DataArray68_Byte5		NO_USE
#define CCP_u8DataArray68_Byte6		NO_USE
#define CCP_u8DataArray68_Byte7		NO_USE

#define CCP_u8DataArray69_Byte1		NO_USE
#define CCP_u8DataArray69_Byte2		NO_USE
#define CCP_u8DataArray69_Byte3		NO_USE
#define CCP_u8DataArray69_Byte4		NO_USE
#define CCP_u8DataArray69_Byte5		NO_USE
#define CCP_u8DataArray69_Byte6		NO_USE
#define CCP_u8DataArray69_Byte7		NO_USE

#define CCP_u8DataArray6A_Byte1		NO_USE
#define CCP_u8DataArray6A_Byte2		NO_USE
#define CCP_u8DataArray6A_Byte3		NO_USE
#define CCP_u8DataArray6A_Byte4		NO_USE
#define CCP_u8DataArray6A_Byte5		NO_USE
#define CCP_u8DataArray6A_Byte6		NO_USE
#define CCP_u8DataArray6A_Byte7		NO_USE

#define CCP_u8DataArray6B_Byte1		NO_USE
#define CCP_u8DataArray6B_Byte2		NO_USE
#define CCP_u8DataArray6B_Byte3		NO_USE
#define CCP_u8DataArray6B_Byte4		NO_USE
#define CCP_u8DataArray6B_Byte5		NO_USE
#define CCP_u8DataArray6B_Byte6		NO_USE
#define CCP_u8DataArray6B_Byte7		NO_USE

#define CCP_u8DataArray6C_Byte1		NO_USE
#define CCP_u8DataArray6C_Byte2		NO_USE
#define CCP_u8DataArray6C_Byte3		NO_USE
#define CCP_u8DataArray6C_Byte4		NO_USE
#define CCP_u8DataArray6C_Byte5		NO_USE
#define CCP_u8DataArray6C_Byte6		NO_USE
#define CCP_u8DataArray6C_Byte7		NO_USE

#define CCP_u8DataArray6D_Byte1		NO_USE
#define CCP_u8DataArray6D_Byte2		NO_USE
#define CCP_u8DataArray6D_Byte3		NO_USE
#define CCP_u8DataArray6D_Byte4		NO_USE
#define CCP_u8DataArray6D_Byte5		NO_USE
#define CCP_u8DataArray6D_Byte6		NO_USE
#define CCP_u8DataArray6D_Byte7		NO_USE

#define CCP_u8DataArray6E_Byte1		NO_USE
#define CCP_u8DataArray6E_Byte2		NO_USE
#define CCP_u8DataArray6E_Byte3		NO_USE
#define CCP_u8DataArray6E_Byte4		NO_USE
#define CCP_u8DataArray6E_Byte5		NO_USE
#define CCP_u8DataArray6E_Byte6		NO_USE
#define CCP_u8DataArray6E_Byte7		NO_USE

#define CCP_u8DataArray6F_Byte1		NO_USE
#define CCP_u8DataArray6F_Byte2		NO_USE
#define CCP_u8DataArray6F_Byte3		NO_USE
#define CCP_u8DataArray6F_Byte4		NO_USE
#define CCP_u8DataArray6F_Byte5		NO_USE
#define CCP_u8DataArray6F_Byte6		NO_USE
#define CCP_u8DataArray6F_Byte7		NO_USE

#define CCP_u8DataArray70_Byte1		NO_USE
#define CCP_u8DataArray70_Byte2		NO_USE
#define CCP_u8DataArray70_Byte3		NO_USE
#define CCP_u8DataArray70_Byte4		NO_USE
#define CCP_u8DataArray70_Byte5		NO_USE
#define CCP_u8DataArray70_Byte6		NO_USE
#define CCP_u8DataArray70_Byte7		NO_USE

#define CCP_u8DataArray71_Byte1		NO_USE
#define CCP_u8DataArray71_Byte2		NO_USE
#define CCP_u8DataArray71_Byte3		NO_USE
#define CCP_u8DataArray71_Byte4		NO_USE
#define CCP_u8DataArray71_Byte5		NO_USE
#define CCP_u8DataArray71_Byte6		NO_USE
#define CCP_u8DataArray71_Byte7		NO_USE

#define CCP_u8DataArray72_Byte1		NO_USE
#define CCP_u8DataArray72_Byte2		NO_USE
#define CCP_u8DataArray72_Byte3		NO_USE
#define CCP_u8DataArray72_Byte4		NO_USE
#define CCP_u8DataArray72_Byte5		NO_USE
#define CCP_u8DataArray72_Byte6		NO_USE
#define CCP_u8DataArray72_Byte7		NO_USE

#define CCP_u8DataArray73_Byte1		NO_USE
#define CCP_u8DataArray73_Byte2		NO_USE
#define CCP_u8DataArray73_Byte3		NO_USE
#define CCP_u8DataArray73_Byte4		NO_USE
#define CCP_u8DataArray73_Byte5		NO_USE
#define CCP_u8DataArray73_Byte6		NO_USE
#define CCP_u8DataArray73_Byte7		NO_USE

#define CCP_u8DataArray74_Byte1		NO_USE
#define CCP_u8DataArray74_Byte2		NO_USE
#define CCP_u8DataArray74_Byte3		NO_USE
#define CCP_u8DataArray74_Byte4		NO_USE
#define CCP_u8DataArray74_Byte5		NO_USE
#define CCP_u8DataArray74_Byte6		NO_USE
#define CCP_u8DataArray74_Byte7		NO_USE

#define CCP_u8DataArray75_Byte1		NO_USE
#define CCP_u8DataArray75_Byte2		NO_USE
#define CCP_u8DataArray75_Byte3		NO_USE
#define CCP_u8DataArray75_Byte4		NO_USE
#define CCP_u8DataArray75_Byte5		NO_USE
#define CCP_u8DataArray75_Byte6		NO_USE
#define CCP_u8DataArray75_Byte7		NO_USE

#define CCP_u8DataArray76_Byte1		NO_USE
#define CCP_u8DataArray76_Byte2		NO_USE
#define CCP_u8DataArray76_Byte3		NO_USE
#define CCP_u8DataArray76_Byte4		NO_USE
#define CCP_u8DataArray76_Byte5		NO_USE
#define CCP_u8DataArray76_Byte6		NO_USE
#define CCP_u8DataArray76_Byte7		NO_USE

#define CCP_u8DataArray77_Byte1		NO_USE
#define CCP_u8DataArray77_Byte2		NO_USE
#define CCP_u8DataArray77_Byte3		NO_USE
#define CCP_u8DataArray77_Byte4		NO_USE
#define CCP_u8DataArray77_Byte5		NO_USE
#define CCP_u8DataArray77_Byte6		NO_USE
#define CCP_u8DataArray77_Byte7		NO_USE

#define CCP_u8DataArray78_Byte1		NO_USE
#define CCP_u8DataArray78_Byte2		NO_USE
#define CCP_u8DataArray78_Byte3		NO_USE
#define CCP_u8DataArray78_Byte4		NO_USE
#define CCP_u8DataArray78_Byte5		NO_USE
#define CCP_u8DataArray78_Byte6		NO_USE
#define CCP_u8DataArray78_Byte7		NO_USE

#define CCP_u8DataArray79_Byte1		NO_USE
#define CCP_u8DataArray79_Byte2		NO_USE
#define CCP_u8DataArray79_Byte3		NO_USE
#define CCP_u8DataArray79_Byte4		NO_USE
#define CCP_u8DataArray79_Byte5		NO_USE
#define CCP_u8DataArray79_Byte6		NO_USE
#define CCP_u8DataArray79_Byte7		NO_USE

#define CCP_u8DataArray7A_Byte1		NO_USE
#define CCP_u8DataArray7A_Byte2		NO_USE
#define CCP_u8DataArray7A_Byte3		NO_USE
#define CCP_u8DataArray7A_Byte4		NO_USE
#define CCP_u8DataArray7A_Byte5		NO_USE
#define CCP_u8DataArray7A_Byte6		NO_USE
#define CCP_u8DataArray7A_Byte7		NO_USE

#define CCP_u8DataArray7B_Byte1		NO_USE
#define CCP_u8DataArray7B_Byte2		NO_USE
#define CCP_u8DataArray7B_Byte3		NO_USE
#define CCP_u8DataArray7B_Byte4		NO_USE
#define CCP_u8DataArray7B_Byte5		NO_USE
#define CCP_u8DataArray7B_Byte6		NO_USE
#define CCP_u8DataArray7B_Byte7		NO_USE

#define CCP_u8DataArray7C_Byte1		NO_USE
#define CCP_u8DataArray7C_Byte2		NO_USE
#define CCP_u8DataArray7C_Byte3		NO_USE
#define CCP_u8DataArray7C_Byte4		NO_USE
#define CCP_u8DataArray7C_Byte5		NO_USE
#define CCP_u8DataArray7C_Byte6		NO_USE
#define CCP_u8DataArray7C_Byte7		NO_USE

#define CCP_u8DataArray7D_Byte1		NO_USE
#define CCP_u8DataArray7D_Byte2		NO_USE
#define CCP_u8DataArray7D_Byte3		NO_USE
#define CCP_u8DataArray7D_Byte4		NO_USE
#define CCP_u8DataArray7D_Byte5		NO_USE
#define CCP_u8DataArray7D_Byte6		NO_USE
#define CCP_u8DataArray7D_Byte7		NO_USE

#define CCP_u8DataArray7E_Byte1		NO_USE
#define CCP_u8DataArray7E_Byte2		NO_USE
#define CCP_u8DataArray7E_Byte3		NO_USE
#define CCP_u8DataArray7E_Byte4		NO_USE
#define CCP_u8DataArray7E_Byte5		NO_USE
#define CCP_u8DataArray7E_Byte6		NO_USE
#define CCP_u8DataArray7E_Byte7		NO_USE

#define CCP_u8DataArray7F_Byte1		NO_USE
#define CCP_u8DataArray7F_Byte2		NO_USE
#define CCP_u8DataArray7F_Byte3		NO_USE
#define CCP_u8DataArray7F_Byte4		NO_USE
#define CCP_u8DataArray7F_Byte5		NO_USE
#define CCP_u8DataArray7F_Byte6		NO_USE
#define CCP_u8DataArray7F_Byte7		NO_USE

#define CCP_u8DataArray80_Byte1		NO_USE
#define CCP_u8DataArray80_Byte2		NO_USE
#define CCP_u8DataArray80_Byte3		NO_USE
#define CCP_u8DataArray80_Byte4		NO_USE
#define CCP_u8DataArray80_Byte5		NO_USE
#define CCP_u8DataArray80_Byte6		NO_USE
#define CCP_u8DataArray80_Byte7		NO_USE

/* Define the datasheet from other modules */
#define CCP_u8DataArray81_Byte1		CCS_u8GetValue(CCS_nu8SwVersion)
#define CCP_u8DataArray81_Byte2		CCP_u8GetLowByte(CCS_u16GetValue(CCS_nu16TempDiffAvg))
#define CCP_u8DataArray81_Byte3		CCP_u8GetHighByte(CCS_u16GetValue(CCS_nu16TempDiffAvg))
#define CCP_u8DataArray81_Byte4		CCP_u8GetLowByte(CCS_u16GetValue(CCS_nu16SetTempDr))
#define CCP_u8DataArray81_Byte5		CCP_u8GetHighByte(CCS_u16GetValue(CCS_nu16SetTempDr))
#define CCP_u8DataArray81_Byte6		CCP_u8GetLowByte(CCS_u16GetValue(CCS_nu16SetTempPs))
#define CCP_u8DataArray81_Byte7		CCP_u8GetHighByte(CCS_u16GetValue(CCS_nu16SetTempPs))

#define CCP_u8DataArray82_Byte1		CCS_u8GetValue(CCS_nu8Valid)//Rte_IRead_Ccp_vMain_Get_82_1_CcsValid_u8Flag()
#define CCP_u8DataArray82_Byte2		CCP_u8GetLowByte(CCS_u16GetValue(CCS_nu16BlowoutTempDr)/*Rte_IRead_Ccp_vMain_Get_82_23_CcsBlowoutTempDr_u16Temp()*/)
#define CCP_u8DataArray82_Byte3		CCP_u8GetHighByte(CCS_u16GetValue(CCS_nu16BlowoutTempDr)/*Rte_IRead_Ccp_vMain_Get_82_23_CcsBlowoutTempDr_u16Temp()*/)
#define CCP_u8DataArray82_Byte4		CCP_u8GetLowByte(CCS_u16GetValue(CCS_nu16BlowoutTempPs)/*Rte_IRead_Ccp_vMain_Get_82_45_CcsBlowoutTempPs_u16Temp()*/)
#define CCP_u8DataArray82_Byte5		CCP_u8GetHighByte(CCS_u16GetValue(CCS_nu16BlowoutTempPs)/*Rte_IRead_Ccp_vMain_Get_82_45_CcsBlowoutTempPs_u16Temp()*/)
#define CCP_u8DataArray82_Byte6		CCP_u8GetLowByte(CCS_u16GetValue(CCS_nu16BlowoutTempAvg)/*Rte_IRead_Ccp_vMain_Get_83_45_CcsSiBlwoutTempOffsetDr_u16TempOffset()*/)
#define CCP_u8DataArray82_Byte7		CCP_u8GetHighByte(CCS_u16GetValue(CCS_nu16BlowoutTempAvg)/*Rte_IRead_Ccp_vMain_Get_83_45_CcsSiBlwoutTempOffsetDr_u16TempOffset()*/)

#define CCP_u8DataArray83_Byte1		NO_USE
#define CCP_u8DataArray83_Byte2		CCP_u8GetLowByte(CCS_u16GetValue(CCS_nu16OatBlwoutTempOffsetDr)/*Rte_IRead_Ccp_vMain_Get_83_23_CcsOatBlwoutTempOffsetDr_u16TempOffset()*/)
#define CCP_u8DataArray83_Byte3		CCP_u8GetHighByte(CCS_u16GetValue(CCS_nu16OatBlwoutTempOffsetDr)/*Rte_IRead_Ccp_vMain_Get_83_23_CcsOatBlwoutTempOffsetDr_u16TempOffset()*/)
#define CCP_u8DataArray83_Byte4		CCP_u8GetLowByte(CCS_u16GetValue(CCS_nu16SiBlwoutTempOffsetDr))
#define CCP_u8DataArray83_Byte5		CCP_u8GetHighByte(CCS_u16GetValue(CCS_nu16SiBlwoutTempOffsetDr))
#define CCP_u8DataArray83_Byte6		CCP_u8GetLowByte(CCS_u16GetValue(CCS_nu16OatSetTempOffsetPs))//CCP_u8GetLowByte(Rte_IRead_Ccp_vMain_Get_83_67_CcsOatSetTempOffsetPs_u16TempOffset())
#define CCP_u8DataArray83_Byte7		CCP_u8GetHighByte(CCS_u16GetValue(CCS_nu16OatSetTempOffsetPs))//CCP_u8GetHighByte(Rte_IRead_Ccp_vMain_Get_83_67_CcsOatSetTempOffsetPs_u16TempOffset())

#define CCP_u8DataArray84_Byte1		NO_USE
#define CCP_u8DataArray84_Byte2		CCP_u8GetLowByte(CCS_u16GetValue(CCS_nu16OatSetTempOffsetDr)/*Rte_IRead_Ccp_vMain_Get_84_23_CcsOatSetTempOffsetDr_u16TempOffset()*/)
#define CCP_u8DataArray84_Byte3		CCP_u8GetHighByte(CCS_u16GetValue(CCS_nu16OatSetTempOffsetDr)/*Rte_IRead_Ccp_vMain_Get_84_23_CcsOatSetTempOffsetDr_u16TempOffset()*/)
#define CCP_u8DataArray84_Byte4		CCP_u8GetLowByte(CCS_u16GetValue(CCS_nu16TsetBlwoutTempOffsetDr)/*Rte_IRead_Ccp_vMain_Get_84_45_CcsTsetBlwoutTempOffsetDr_u16TempOffset()*/)
#define CCP_u8DataArray84_Byte5		CCP_u8GetHighByte(CCS_u16GetValue(CCS_nu16TsetBlwoutTempOffsetDr)/*Rte_IRead_Ccp_vMain_Get_84_45_CcsTsetBlwoutTempOffsetDr_u16TempOffset()*/)
#define CCP_u8DataArray84_Byte6		CCP_u8GetLowByte(CCS_u16GetValue(CCS_nu16TsetBlwoutTempOffsetPs)/*Rte_IRead_Ccp_vMain_Get_84_67_CcsTsetBlwoutTempOffsetPs_u16TempOffset()*/)
#define CCP_u8DataArray84_Byte7		CCP_u8GetHighByte(CCS_u16GetValue(CCS_nu16TsetBlwoutTempOffsetPs)/*Rte_IRead_Ccp_vMain_Get_84_67_CcsTsetBlwoutTempOffsetPs_u16TempOffset()*/)

#define CCP_u8DataArray85_Byte1		NO_USE
#define CCP_u8DataArray85_Byte2		CCP_u8GetLowByte(CCS_u16GetValue(CCS_nu16TempDiffDr)/*Rte_IRead_Ccp_vMain_Get_85_23_CcsTempDiffDr_u16TempDiff()*/)
#define CCP_u8DataArray85_Byte3	    CCP_u8GetHighByte(CCS_u16GetValue(CCS_nu16TempDiffDr)/*Rte_IRead_Ccp_vMain_Get_85_23_CcsTempDiffDr_u16TempDiff()*/)
#define CCP_u8DataArray85_Byte4		CCP_u8GetLowByte(CCS_u16GetValue(CCS_nu16TempDiffPs)/*Rte_IRead_Ccp_vMain_Get_85_45_CcsTempDiffPs_u16TempDiff()*/)
#define CCP_u8DataArray85_Byte5		CCP_u8GetHighByte(CCS_u16GetValue(CCS_nu16TempDiffPs)/*Rte_IRead_Ccp_vMain_Get_85_45_CcsTempDiffPs_u16TempDiff()*/)
#define CCP_u8DataArray85_Byte6		CCP_u8GetLowByte(CCS_u16GetValue(CCS_nu16OatBlwoutTempOffsetPs)/*Rte_IRead_Ccp_vMain_Get_85_67_CcsOatBlwoutTempOffsetPs_u16TempOffset()*/)
#define CCP_u8DataArray85_Byte7		CCP_u8GetHighByte(CCS_u16GetValue(CCS_nu16OatBlwoutTempOffsetPs)/*Rte_IRead_Ccp_vMain_Get_85_67_CcsOatBlwoutTempOffsetPs_u16TempOffset()*/)

#define CCP_u8DataArray86_Byte1		CCP_u8GetLowByte(CCS_u16GetValue(CCS_nu16SiBlwoutTempOffsetPs))
#define CCP_u8DataArray86_Byte2		CCP_u8GetHighByte(CCS_u16GetValue(CCS_nu16SiBlwoutTempOffsetPs))
#define CCP_u8DataArray86_Byte3		CCP_u8GetLowByte(CCS_u16GetValue(CCS_nu16ErrorCode)/*Rte_IRead_Ccp_vMain_Get_86_34_CcsErrorCode_u16BitMap()*/)
#define CCP_u8DataArray86_Byte4		CCP_u8GetHighByte(CCS_u16GetValue(CCS_nu16ErrorCode)/*Rte_IRead_Ccp_vMain_Get_86_34_CcsErrorCode_u16BitMap()*/)
#define CCP_u8DataArray86_Byte5		CCP_u8GetLowByte(CCS_u16GetValue(CCS_nu16SetTempAvg)/*Rte_IRead_Ccp_vMain_Get_86_56_CcsSetTempAvg_u16Temp()*/)
#define CCP_u8DataArray86_Byte6		CCP_u8GetHighByte(CCS_u16GetValue(CCS_nu16SetTempAvg)/*Rte_IRead_Ccp_vMain_Get_86_56_CcsSetTempAvg_u16Temp()*/)
#define CCP_u8DataArray86_Byte7		NO_USE

#define CCP_u8DataArray87_Byte1		MAC_u8GetValue(MAC_nu8SwVersion)//Rte_IRead_Ccp_vMain_Get_87_1_MacSwVersion_u8Version()   //MAC_u8GetValue(MAC_nu8SwVersion)
#define CCP_u8DataArray87_Byte2		CCP_u8GetLowByte(MAC_u16GetValue(MAC_nu16MixedAirPosDr)/* Rte_IRead_Ccp_vMain_Get_87_23_MacMixedAirPosDr_u16MotorPos()*/)//CCP_u8GetLowByte(MAC_u16GetValue(MAC_nu16MixedAirPosDr))
#define CCP_u8DataArray87_Byte3		CCP_u8GetHighByte(MAC_u16GetValue(MAC_nu16MixedAirPosDr)/*Rte_IRead_Ccp_vMain_Get_87_23_MacMixedAirPosDr_u16MotorPos()*/)//CCP_u8GetHighByte(MAC_u16GetValue(MAC_nu16MixedAirPosDr))
#define CCP_u8DataArray87_Byte4		CCP_u8GetLowByte(MAC_u16GetValue(MAC_nu16MixedAirPosPs)/*Rte_IRead_Ccp_vMain_Get_87_45_MacMixedAirPosPs_u16MotorPos()*/)//CCP_u8GetLowByte(MAC_u16GetValue(MAC_nu16MixedAirPosPs))
#define CCP_u8DataArray87_Byte5		CCP_u8GetHighByte(MAC_u16GetValue(MAC_nu16MixedAirPosPs)/*Rte_IRead_Ccp_vMain_Get_87_45_MacMixedAirPosPs_u16MotorPos()*/)//CCP_u8GetHighByte(MAC_u16GetValue(MAC_nu16MixedAirPosPs))
#define CCP_u8DataArray87_Byte6		CCP_u8GetLowByte(MAC_u16GetValue(MAC_nu16BlowoutTempAvg)/*Rte_IRead_Ccp_vMain_Get_87_67_MacBlowoutTempAvg_u16Temp()*/)
#define CCP_u8DataArray87_Byte7		CCP_u8GetHighByte(MAC_u16GetValue(MAC_nu16BlowoutTempAvg)/*Rte_IRead_Ccp_vMain_Get_87_67_MacBlowoutTempAvg_u16Temp()*/)

#define CCP_u8DataArray88_Byte1		MAC_u8GetValue(MAC_nu8Valid)//Rte_IRead_Ccp_vMain_Get_88_1_MacValid_u8Flag()//MAC_u8GetValue(MAC_nu8Valid)
#define CCP_u8DataArray88_Byte2		CCP_u8GetLowByte(MAC_u16GetValue(MAC_nu16BlowoutTempDr)/*Rte_IRead_Ccp_vMain_Get_88_23_MacBlowoutTempDr_u16Temp()*/)
#define CCP_u8DataArray88_Byte3		CCP_u8GetHighByte(MAC_u16GetValue(MAC_nu16BlowoutTempDr)/*Rte_IRead_Ccp_vMain_Get_88_23_MacBlowoutTempDr_u16Temp()*/)
#define CCP_u8DataArray88_Byte4		CCP_u8GetLowByte(MAC_u16GetValue(MAC_nu16BlowoutTempPs)/*Rte_IRead_Ccp_vMain_Get_88_45_MacBlowoutTempPs_u16Temp()*/)
#define CCP_u8DataArray88_Byte5		CCP_u8GetHighByte(MAC_u16GetValue(MAC_nu16BlowoutTempPs)/*Rte_IRead_Ccp_vMain_Get_88_45_MacBlowoutTempPs_u16Temp()*/)
#define CCP_u8DataArray88_Byte6		NO_USE
#define CCP_u8DataArray88_Byte7		NO_USE

#define CCP_u8DataArray89_Byte1		NO_USE
#define CCP_u8DataArray89_Byte2		NO_USE
#define CCP_u8DataArray89_Byte3		NO_USE
#define CCP_u8DataArray89_Byte4		NO_USE
#define CCP_u8DataArray89_Byte5		NO_USE
#define CCP_u8DataArray89_Byte6		NO_USE
#define CCP_u8DataArray89_Byte7		NO_USE

#define CCP_u8DataArray8A_Byte1		NO_USE
#define CCP_u8DataArray8A_Byte2		NO_USE//CCP_u8GetLowByte(MAC_u16GetValue(MAC_nu16BlowoutTempDr))
#define CCP_u8DataArray8A_Byte3		NO_USE//CCP_u8GetHighByte(MAC_u16GetValue(MAC_nu16BlowoutTempDr))
#define CCP_u8DataArray8A_Byte4		NO_USE//CCP_u8GetLowByte(MAC_u16GetValue(MAC_nu16BlowoutTempDr))
#define CCP_u8DataArray8A_Byte5		NO_USE//CCP_u8GetHighByte(MAC_u16GetValue(MAC_nu16BlowoutTempDr))
#define CCP_u8DataArray8A_Byte6		CCP_u8GetLowByte(MAC_u16GetValue(MAC_nu16BlowSpeedHys))
#define CCP_u8DataArray8A_Byte7		CCP_u8GetHighByte(MAC_u16GetValue(MAC_nu16BlowSpeedHys))

#define CCP_u8DataArray8B_Byte1		NO_USE//AIRD_u8GetValue(AIRD_nu8SwVersion)//Rte_IRead_Ccp_vMain_CcpGetAirdSwvesion_Version()
#define CCP_u8DataArray8B_Byte2		CCP_u8GetLowByte(MAC_u16GetValue(MAC_nu16EvapTempHys)/*Rte_IRead_Ccp_vMain_Get_8B_23_MacEvapTempHys_u16Temp()*/)//Rte_IRead_Ccp_vMain_CcpGetAirdDisplayInfo_AirdDisplay()
#define CCP_u8DataArray8B_Byte3		CCP_u8GetHighByte(MAC_u16GetValue(MAC_nu16EvapTempHys)/*Rte_IRead_Ccp_vMain_Get_8B_23_MacEvapTempHys_u16Temp()*/)
#define CCP_u8DataArray8B_Byte4		CCP_u8GetLowByte(MAC_u16GetValue(MAC_nu16HctHys)/*Rte_IRead_Ccp_vMain_Get_8B_45_MacHctHys_u16Temp()*/)//GetWordToByteLow(Rte_IRead_Ccp_vMain_CcpGetAirdSetPos_AirdSetPos())
#define CCP_u8DataArray8B_Byte5		CCP_u8GetHighByte(MAC_u16GetValue(MAC_nu16HctHys)/*Rte_IRead_Ccp_vMain_Get_8B_45_MacHctHys_u16Temp()*/)//CCP_u8GetHighByte(Rte_IRead_Ccp_vMain_CcpGetAirdSetPos_AirdSetPos())
#define CCP_u8DataArray8B_Byte6		CCP_u8GetLowByte(MAC_u16GetValue(MAC_nu16FlapRatioAvg)/*Rte_IRead_Ccp_vMain_Get_8B_67_MacFlapRatioAvg_u16Percent()*/)
#define CCP_u8DataArray8B_Byte7		CCP_u8GetHighByte(MAC_u16GetValue(MAC_nu16FlapRatioAvg)/*Rte_IRead_Ccp_vMain_Get_8B_67_MacFlapRatioAvg_u16Percent()*/)

#define CCP_u8DataArray8C_Byte1		CCP_u8GetLowByte(MAC_u16GetValue(MAC_nu16ErrorCode)/*Rte_IRead_Ccp_vMain_Get_8C_12_MacErrorCode_u16BitMap()*/)//CCP_u8GetLowByte(MAC_u16GetValue(MAC_nu16ErrCode))
#define CCP_u8DataArray8C_Byte2		CCP_u8GetHighByte(MAC_u16GetValue(MAC_nu16ErrorCode)/*Rte_IRead_Ccp_vMain_Get_8C_12_MacErrorCode_u16BitMap()*/)//CCP_u8GetHighByte(MAC_u16GetValue(MAC_nu16ErrCode))
#define CCP_u8DataArray8C_Byte3		CCP_u8GetLowByte(MAC_u16GetValue(MAC_nu16FlapRatioDr)/*Rte_IRead_Ccp_vMain_Get_8C_34_MacFlapRatioDr_u16Percent()*/)
#define CCP_u8DataArray8C_Byte4		CCP_u8GetHighByte(MAC_u16GetValue(MAC_nu16FlapRatioDr)/*Rte_IRead_Ccp_vMain_Get_8C_34_MacFlapRatioDr_u16Percent()*/)
#define CCP_u8DataArray8C_Byte5		CCP_u8GetLowByte(MAC_u16GetValue(MAC_nu16FlapRatioPs)/*Rte_IRead_Ccp_vMain_Get_8C_56_MacFlapRatioPs_u16Percent()*/)
#define CCP_u8DataArray8C_Byte6		CCP_u8GetHighByte(MAC_u16GetValue(MAC_nu16FlapRatioPs)/*Rte_IRead_Ccp_vMain_Get_8C_56_MacFlapRatioPs_u16Percent()*/)
#define CCP_u8DataArray8C_Byte7		NO_USE

#define CCP_u8DataArray8D_Byte1		AIRD_u8GetValue(AIRD_nu8SwVersion)//Rte_IRead_Ccp_vMain_Get_8D_1_AirdSwVersion_u8Version()//AIRD_u8GetValue(AIRD_nu8SwVersion)
#define CCP_u8DataArray8D_Byte2		CCP_u8GetLowByte(AIRD_u16GetValue(AIRD_nu16SetPos)/*Rte_IRead_Ccp_vMain_Get_8D_23_AirdSetPos_u16MotorPos()*/)//CCP_u8GetLowByte(AIRD_u16GetValue(AIRD_nu16SetPos))
#define CCP_u8DataArray8D_Byte3		CCP_u8GetHighByte(AIRD_u16GetValue(AIRD_nu16SetPos)/*Rte_IRead_Ccp_vMain_Get_8D_23_AirdSetPos_u16MotorPos()*/)//CCP_u8GetHighByte(AIRD_u16GetValue(AIRD_nu16SetPos))
#define CCP_u8DataArray8D_Byte4		NO_USE//CCP_u8GetLowByte(AIRD_u16GetValue(AIRD_nu16MaxPos))
#define CCP_u8DataArray8D_Byte5		NO_USE//CCP_u8GetHighByte(AIRD_u16GetValue(AIRD_nu16MaxPos))
#define CCP_u8DataArray8D_Byte6		NO_USE//CCP_u8GetLowByte(AIRD_u16GetValue(AIRD_nu16MinPos))
#define CCP_u8DataArray8D_Byte7		NO_USE//CCP_u8GetHighByte(AIRD_u16GetValue(AIRD_nu16MinPos))

#define CCP_u8DataArray8E_Byte1		AIRD_u8GetValue(AIRD_nu8Valid)
#define CCP_u8DataArray8E_Byte2		AIRD_u8GetValue(AIRD_nu8AirdAutoControl)
#define CCP_u8DataArray8E_Byte3		NO_USE
#define CCP_u8DataArray8E_Byte4		NO_USE
#define CCP_u8DataArray8E_Byte5		NO_USE
#define CCP_u8DataArray8E_Byte6		NO_USE
#define CCP_u8DataArray8E_Byte7		NO_USE

#define CCP_u8DataArray8F_Byte1		AIRD_u8GetValue(AIRD_nu8Display)
#define CCP_u8DataArray8F_Byte2		CCP_u8GetLowByte(AIRD_u16GetValue(AIRD_nu16ErrCode))
#define CCP_u8DataArray8F_Byte3		CCP_u8GetHighByte(AIRD_u16GetValue(AIRD_nu16ErrCode))
#define CCP_u8DataArray8F_Byte4		NO_USE
#define CCP_u8DataArray8F_Byte5		NO_USE
#define CCP_u8DataArray8F_Byte6		NO_USE
#define CCP_u8DataArray8F_Byte7		NO_USE

#define CCP_u8DataArray90_Byte1		RFA_u8GetValue(RFA_nu8SwVersion)
#define CCP_u8DataArray90_Byte2		CCP_u8GetLowByte(RFA_u16GetValue(RFA_nu16SetPos))
#define CCP_u8DataArray90_Byte3		CCP_u8GetHighByte(RFA_u16GetValue(RFA_nu16SetPos))
#define CCP_u8DataArray90_Byte4		CCP_u8GetLowByte(RFA_u16GetValue(RFA_nu16MaxPos))
#define CCP_u8DataArray90_Byte5		CCP_u8GetHighByte(RFA_u16GetValue(RFA_nu16MaxPos))
#define CCP_u8DataArray90_Byte6		CCP_u8GetLowByte(RFA_u16GetValue(RFA_nu16MinPos))
#define CCP_u8DataArray90_Byte7		CCP_u8GetHighByte(RFA_u16GetValue(RFA_nu16MinPos))

#define CCP_u8DataArray91_Byte1		RFA_u8GetValue(RFA_nu8Valid)
#define CCP_u8DataArray91_Byte2		CCP_u8GetLowByte(RFA_u16GetValue(RFA_nu16RecircTime))
#define CCP_u8DataArray91_Byte3		CCP_u8GetHighByte(RFA_u16GetValue(RFA_nu16RecircTime))
#define CCP_u8DataArray91_Byte4		NO_USE//CCP_u8GetLowByte(RFA_u16GetValue(RFA_nu16RecircSwitchPoint))
#define CCP_u8DataArray91_Byte5		NO_USE//CCP_u8GetHighByte(RFA_u16GetValue(RFA_nu16RecircSwitchPoint))
#define CCP_u8DataArray91_Byte6		RFA_u8GetValue(RFA_nu8Display)
#define CCP_u8DataArray91_Byte7		RFA_u8GetValue(RFA_nu8AutoPercent)

#define CCP_u8DataArray92_Byte1		CCP_u8GetLowByte(RFA_u16GetValue(RFA_nu16ErrorCode))
#define CCP_u8DataArray92_Byte2		CCP_u8GetHighByte(RFA_u16GetValue(RFA_nu16ErrorCode))
#define CCP_u8DataArray92_Byte3		RFA_u8GetValue(RFA_nu8SetPercent)
#define CCP_u8DataArray92_Byte4		CCP_u8GetLowByte(RFA_u16GetValue(RFA_nu16Priority))
#define CCP_u8DataArray92_Byte5		CCP_u8GetHighByte(RFA_u16GetValue(RFA_nu16Priority))
#define CCP_u8DataArray92_Byte6		NO_USE
#define CCP_u8DataArray92_Byte7		NO_USE

#define CCP_u8DataArray93_Byte1		NO_USE//BCTL_u8GetValue(BCTL_nu8SwVersion)
#define CCP_u8DataArray93_Byte2		CCP_u8GetLowByte(BCTL_u16GetValue(BCTL_nu16TrgVlt))
#define CCP_u8DataArray93_Byte3		CCP_u8GetHighByte(BCTL_u16GetValue(BCTL_nu16TrgVlt))//CCP_u8GetHighByte(Rte_IRead_Ccp_vMain_Get_93_23_BctlBlwTarget_u16BlwSpd())//CCP_u8GetHighByte(BCTL1_u16GetValue(BCTL_nu16BlowerTarget))
#define CCP_u8DataArray93_Byte4		CCP_u8GetLowByte(BCTL_u16GetValue(BCTL_nu16CcsTrgVlt))  //CCP_u8GetLowByte(Rte_IRead_Ccp_vMain_Get_93_45_BctlBlwCcsTarget_u16BlwSpd())//CCP_u8GetLowByte(BCTL1_u16GetValue(BCTL_nu16BlowerCcsTarget))
#define CCP_u8DataArray93_Byte5		CCP_u8GetHighByte(BCTL_u16GetValue(BCTL_nu16CcsTrgVlt))//CCP_u8GetHighByte(Rte_IRead_Ccp_vMain_Get_93_45_BctlBlwCcsTarget_u16BlwSpd())//CCP_u8GetHighByte(BCTL1_u16GetValue(BCTL_nu16BlowerCcsTarget))
#define CCP_u8DataArray93_Byte6		CCP_u8GetLowByte(BCTL_u16GetValue(BCTL_nu16OatCcsSetTempVolOffsetDr))//CCP_u8GetLowByte(Rte_IRead_Ccp_vMain_Get_93_67_BctlOatSetTempOffset_u16TempOffset())//CCP_u8GetLowByte(BCTL1_u16GetValue(BCTL_nu16BlowerOatSetTempOffset))
#define CCP_u8DataArray93_Byte7		CCP_u8GetHighByte(BCTL_u16GetValue(BCTL_nu16OatCcsSetTempVolOffsetDr))//CCP_u8GetHighByte(Rte_IRead_Ccp_vMain_Get_93_67_BctlOatSetTempOffset_u16TempOffset())//CCP_u8GetHighByte(BCTL1_u16GetValue(BCTL_nu16BlowerOatSetTempOffset))

#define CCP_u8DataArray94_Byte1		NO_USE//BCTL_u8GetValue(BCTL_nu8Valid)
#define CCP_u8DataArray94_Byte2		CCP_u8GetLowByte(BCTL_u16GetValue(BCTL_nu16SiVolOffsetDr))
#define CCP_u8DataArray94_Byte3		CCP_u8GetHighByte(BCTL_u16GetValue(BCTL_nu16SiVolOffsetDr))
#define CCP_u8DataArray94_Byte4		CCP_u8GetLowByte(BCTL_u16GetValue(BCTL_nu16VolLmt))
#define CCP_u8DataArray94_Byte5		CCP_u8GetHighByte(BCTL_u16GetValue(BCTL_nu16VolLmt))
#define CCP_u8DataArray94_Byte6		NO_USE//CCP_u8GetLowByte(BCTL_u16GetValue(BCTL_nu16AirdBaseVoltage))
#define CCP_u8DataArray94_Byte7		NO_USE//CCP_u8GetHighByte(BCTL_u16GetValue(BCTL_nu16AirdBaseVoltage))

#define CCP_u8DataArray95_Byte1		BCTL_u8GetValue(BCTL_nu8DisplayInfo)
#define CCP_u8DataArray95_Byte2		NO_USE//CCP_u8GetLowByte(BCTL_u16GetValue(BCTL_nu16BlowoutOffset))
#define CCP_u8DataArray95_Byte3		NO_USE//CCP_u8GetHighByte(BCTL_u16GetValue(BCTL_nu16BlowoutOffset))
#define CCP_u8DataArray95_Byte4		CCP_u8GetLowByte(BCTL_u16GetValue(BCTL_nu16VelVolOffset))
#define CCP_u8DataArray95_Byte5		CCP_u8GetHighByte(BCTL_u16GetValue(BCTL_nu16VelVolOffset))
#define CCP_u8DataArray95_Byte6		CCP_u8GetLowByte(BCTL_u16GetValue(BCTL_nu16SunVolOffset))
#define CCP_u8DataArray95_Byte7		CCP_u8GetHighByte(BCTL_u16GetValue(BCTL_nu16SunVolOffset))

#define CCP_u8DataArray96_Byte1		NO_USE//CCP_u8GetLowByte(BCTL_u16GetValue(BCTL_nu16Error))
#define CCP_u8DataArray96_Byte2		NO_USE//CCP_u8GetHighByte(BCTL_u16GetValue(BCTL_nu16Error))
#define CCP_u8DataArray96_Byte3		NO_USE//BCTL_FanOnOff
#define CCP_u8DataArray96_Byte4		NO_USE//BCTL_u8GetValue(Bctl_u88TargetLevel)
#define CCP_u8DataArray96_Byte5		NO_USE
#define CCP_u8DataArray96_Byte6		NO_USE
#define CCP_u8DataArray96_Byte7		NO_USE

#define CCP_u8DataArray97_Byte1		MMI_u8GetValue(MMI_nu8SwVersion) //Rte_IRead_Ccp_vMain_Get_97_1_MmiSwVersion_u8Version()//MMI_u8GetValue(MMI_nu8SwVersion)
#define CCP_u8DataArray97_Byte2		MMI_u8GetValue(MMI_nu8SetTempDr)
#define CCP_u8DataArray97_Byte3		MMI_u8GetValue(MMI_nu8SetTempPs)
#define CCP_u8DataArray97_Byte4		MMI_u8GetValue(MMI_nu8ModeControl)
#define CCP_u8DataArray97_Byte5		MMI_u8GetValue(MMI_nu8DefrostControl)
#define CCP_u8DataArray97_Byte6		MMI_u8GetValue(MMI_nu8DualControl)
#define CCP_u8DataArray97_Byte7		MMI_u8GetValue(MMI_nu8MaxAcControl)

#define CCP_u8DataArray98_Byte1		MMI_u8GetValue(MMI_nu8RecirMode)
#define CCP_u8DataArray98_Byte2		MMI_u8GetValue(MMI_nu8ACMode)
#define CCP_u8DataArray98_Byte3		MMI_u8GetValue(MMI_nu8BlwModeControl)
#define CCP_u8DataArray98_Byte4		NO_USE//MMI_u8GetValue(MMI_nu8Valid)
#define CCP_u8DataArray98_Byte5		MMI_u8GetValue(MMI_nu8BlwControl)
#define CCP_u8DataArray98_Byte6		MMI_u8GetValue(MMI_nu8AirdModeControl)
#define CCP_u8DataArray98_Byte7		MMI_u8GetValue(MMI_nu8AirdControl)

#define CCP_u8DataArray99_Byte1		MMI_u8GetValue(MMI_nu8RecirControl)
#define CCP_u8DataArray99_Byte2		MMI_u8GetValue(MMI_nu8ACControl)
#define CCP_u8DataArray99_Byte3		CCP_u8GetLowByte(MMI_u16GetValue(MMI_nu16ErrorCode)/*Rte_IRead_Ccp_vMain_Get_99_34_MmiErrorCode_u16BitMap()*/)
#define CCP_u8DataArray99_Byte4		CCP_u8GetHighByte(MMI_u16GetValue(MMI_nu16ErrorCode)/*Rte_IRead_Ccp_vMain_Get_99_34_MmiErrorCode_u16BitMap()*/)
#define CCP_u8DataArray99_Byte5		CCP_u8GetLowByte(MMI_u16GetValue(MMI_nu16IndicatorInfo1)/*Rte_IRead_Ccp_vMain_Get_99_56_MmiLedIndicatorInfo1_u16BitMap()*/)
#define CCP_u8DataArray99_Byte6		CCP_u8GetHighByte(MMI_u16GetValue(MMI_nu16IndicatorInfo1)/*Rte_IRead_Ccp_vMain_Get_99_56_MmiLedIndicatorInfo1_u16BitMap()*/)
#define CCP_u8DataArray99_Byte7		NO_USE

#define CCP_u8DataArray9A_Byte1		DCM_u8GetValue(DCM_nu8SwVersion)/*this value is error*/
#define CCP_u8DataArray9A_Byte2		NO_USE/*this value is error*/
#define CCP_u8DataArray9A_Byte3		DCM_u8GetValue(DCM_nu8MixDrDirection)
#define CCP_u8DataArray9A_Byte4		DCM_u8GetValue(DCM_nu8AirdDirection)
#define CCP_u8DataArray9A_Byte5		DCM_u8GetValue(DCM_nu8RfaDirection)
#define CCP_u8DataArray9A_Byte6		DCM_u8GetValue(DCM_nu8MixPsDirection)
#define CCP_u8DataArray9A_Byte7		NO_USE

#define CCP_u8DataArray9B_Byte1		DCM_u8GetValue(DCM_nu8MixDrErrorCode)
#define CCP_u8DataArray9B_Byte2		DCM_u8GetValue(DCM_nu8AirdErrorCode)
#define CCP_u8DataArray9B_Byte3		DCM_u8GetValue(DCM_nu8RfaErrorCode)
#define CCP_u8DataArray9B_Byte4		DCM_u8GetValue(DCM_nu8MixPsErrorCode)
#define CCP_u8DataArray9B_Byte5		NO_USE
#define CCP_u8DataArray9B_Byte6		NO_USE
#define CCP_u8DataArray9B_Byte7		NO_USE

#define CCP_u8DataArray9C_Byte1		CCP_u8GetLowByte(HCT_u16GetValue(HCT_nu16SwVer))//Rte_IRead_Ccp_vMain_Get_9C_1_HctSwVersion_u8Version()//HCT_u8GetValue(HCT_nu8SwVersion)
#define CCP_u8DataArray9C_Byte2		CCP_u8GetLowByte(HCT_u16GetValue(HCT_nu16Value))
#define CCP_u8DataArray9C_Byte3		CCP_u8GetHighByte(HCT_u16GetValue(HCT_nu16Value))
#define CCP_u8DataArray9C_Byte4		NO_USE//CCP_u8GetLowByte(HCT_u16GetValue(HCT_nu16DampedValue))
#define CCP_u8DataArray9C_Byte5		NO_USE//CCP_u8GetHighByte(Rte_IRead_Ccp_vMain_Get_9C_45_HctDampedValue_u16Temp())//CCP_u8GetHighByte(HCT_u16GetValue(HCT_nu16DampedValue))
#define CCP_u8DataArray9C_Byte6		NO_USE//CCP_u8GetLowByte(Rte_IRead_Ccp_vMain_Get_9C_67_HctOatOffset_u16TempOffset())//CCP_u8GetLowByte(HCT_u16GetValue(HCT_nu16OatOffset))
#define CCP_u8DataArray9C_Byte7		NO_USE//CCP_u8GetHighByte(Rte_IRead_Ccp_vMain_Get_9C_67_HctOatOffset_u16TempOffset())//CCP_u8GetHighByte(HCT_u16GetValue(HCT_nu16OatOffset))

#define CCP_u8DataArray9D_Byte1		NO_USE//HCT_u8GetValue(HCT_nu8WaterBumpSpeed)
#define CCP_u8DataArray9D_Byte2		NO_USE//CCP_u8GetLowByte(Rte_IRead_Ccp_vMain_Get_9D_23_HctDynOffset_u16TempOffset())//CCP_u8GetLowByte(HCT_u16GetValue(HCT_nu16DynOffset))
#define CCP_u8DataArray9D_Byte3		NO_USE//CCP_u8GetHighByte(Rte_IRead_Ccp_vMain_Get_9D_23_HctDynOffset_u16TempOffset())//CCP_u8GetHighByte(HCT_u16GetValue(HCT_nu16DynOffset))
#define CCP_u8DataArray9D_Byte4		NO_USE//CCP_u8GetLowByte(HCT_u16GetValue(HCT_nu16TgtCoolantTemp))
#define CCP_u8DataArray9D_Byte5		NO_USE//CCP_u8GetHighByte(HCT_u16GetValue(HCT_nu16TgtCoolantTemp))
#define CCP_u8DataArray9D_Byte6		NO_USE//CCP_u8GetLowByte(HCT_u16GetValue(HCT_nu16TgtHeatcoreTemp))
#define CCP_u8DataArray9D_Byte7		NO_USE//CCP_u8GetHighByte(HCT_u16GetValue(HCT_nu16TgtHeatcoreTemp))

#define CCP_u8DataArray9E_Byte1		NO_USE//HCT_u8GetValue(HCT_nu8WaterBumpSwitch)
#define CCP_u8DataArray9E_Byte2		NO_USE//CCP_u8GetLowByte(HCT_u16GetValue(HCT_nu16HeatcoreTemp))
#define CCP_u8DataArray9E_Byte3		NO_USE//CCP_u8GetHighByte(HCT_u16GetValue(HCT_nu16HeatcoreTemp))
#define CCP_u8DataArray9E_Byte4		NO_USE//CCP_u8GetLowByte(HCT_u16GetValue(HCT_nu16HeatcoreTemp))
#define CCP_u8DataArray9E_Byte5		NO_USE//CCP_u8GetHighByte(HCT_u16GetValue(HCT_nu16HeatcoreTemp))
#define CCP_u8DataArray9E_Byte6		NO_USE//CCP_u8GetLowByte(HCT_u16GetValue(HCT_nu16PITemp))
#define CCP_u8DataArray9E_Byte7		NO_USE//CCP_u8GetHighByte(HCT_u16GetValue(HCT_nu16PITemp))

#define CCP_u8DataArray9F_Byte1		NO_USE//HCT_u8GetValue(HCT_nu8PtcSwitch2Hvh)
#define CCP_u8DataArray9F_Byte2		NO_USE//CCP_u8GetLowByte(HCT_u16GetValue(HCT_nu16ReqPowerLimitForCan))
#define CCP_u8DataArray9F_Byte3		NO_USE//CCP_u8GetHighByte(HCT_u16GetValue(HCT_nu16ReqPowerLimitForCan))
#define CCP_u8DataArray9F_Byte4		NO_USE//CCP_u8GetLowByte(HCT_u16GetValue(HCT_nu16CurrHotAirRatio))
#define CCP_u8DataArray9F_Byte5		NO_USE//CCP_u8GetHighByte(VEL_u16GetValue(HCT_nu16CurrHotAirRatio))
#define CCP_u8DataArray9F_Byte6		NO_USE//CCP_u8GetLowByte(HCT_u16GetValue(HCT_nu16HvacNeedPtcTemp))
#define CCP_u8DataArray9F_Byte7		NO_USE//CCP_u8GetHighByte(HCT_u16GetValue(HCT_nu16HvacNeedPtcTemp))

#define CCP_u8DataArrayA0_Byte1		CCP_u8GetLowByte(HCT_u16GetValue(HCT_nu16ErrorCode))//HCT_u8GetValue(HCT_nu8ErrCode)//CCP_u8GetLowByte(HCT_u16GetValue(HCT_nu8ErrCode))
#define CCP_u8DataArrayA0_Byte2		CCP_u8GetHighByte(HCT_u16GetValue(HCT_nu16ErrorCode))//CCP_u8GetHighByte(HCT_u16GetValue(HCT_nu8ErrCode))
#define CCP_u8DataArrayA0_Byte3		NO_USE//HCT_u8GetValue(HCT_nu8PtcEnable2VCU)
#define CCP_u8DataArrayA0_Byte4		NO_USE//HCT_u8GetValue(HCT_nu8HvacNeedHeatFlag)
#define CCP_u8DataArrayA0_Byte5		NO_USE//HCT_u8GetValue(HCT_nu8BatteryNeedHeatFlag)
#define CCP_u8DataArrayA0_Byte6		NO_USE//HCT_u8GetValue(HCT_nu8WaterCycleValveForLin)
#define CCP_u8DataArrayA0_Byte7		NO_USE

#define CCP_u8DataArrayA1_Byte1		NO_USE//VEL_u8GetValue(VEL_nu8SwVersion)
#define CCP_u8DataArrayA1_Byte2		CCP_u8GetLowByte(VEL_u16GetValue(VEL_nu16Velocity))
#define CCP_u8DataArrayA1_Byte3		CCP_u8GetHighByte(VEL_u16GetValue(VEL_nu16Velocity))
#define CCP_u8DataArrayA1_Byte4		CCP_u8GetLowByte(VEL_u16GetValue(VEL_nu16RfaValue))
#define CCP_u8DataArrayA1_Byte5		CCP_u8GetHighByte(VEL_u16GetValue(VEL_nu16RfaValue))
#define CCP_u8DataArrayA1_Byte6		CCP_u8GetLowByte(VEL_u16GetValue(VEL_nu16OatValue))
#define CCP_u8DataArrayA1_Byte7		CCP_u8GetHighByte(VEL_u16GetValue(VEL_nu16OatValue))

#define CCP_u8DataArrayA2_Byte1		CCP_u8GetLowByte(VEL_u16GetValue(VEL_nu16TempOffset))
#define CCP_u8DataArrayA2_Byte2		CCP_u8GetHighByte(VEL_u16GetValue(VEL_nu16TempOffset))
#define CCP_u8DataArrayA2_Byte3		CCP_u8GetLowByte(VEL_u16GetValue(VEL_nu16BlowerOffset))
#define CCP_u8DataArrayA2_Byte4		CCP_u8GetHighByte(VEL_u16GetValue(VEL_nu16BlowerOffset))
#define CCP_u8DataArrayA2_Byte5		CCP_u8GetLowByte(VEL_u16GetValue(VEL_nu16ErrCode))
#define CCP_u8DataArrayA2_Byte6		CCP_u8GetHighByte(VEL_u16GetValue(VEL_nu16ErrCode))
#define CCP_u8DataArrayA2_Byte7		NO_USE

#define CCP_u8DataArrayA3_Byte1		NO_USE//SUN_u8GetValue(SUN_nu8SwVersion)
#define CCP_u8DataArrayA3_Byte2		CCP_u8GetLowByte(SUN_u16GetValue(SUN_nu16ValueDr))
#define CCP_u8DataArrayA3_Byte3		CCP_u8GetHighByte(SUN_u16GetValue(SUN_nu16ValueDr))
#define CCP_u8DataArrayA3_Byte4		CCP_u8GetLowByte(SUN_u16GetValue(SUN_nu16ValuePs))
#define CCP_u8DataArrayA3_Byte5		CCP_u8GetHighByte(SUN_u16GetValue(SUN_nu16ValuePs))
#define CCP_u8DataArrayA3_Byte6		CCP_u8GetLowByte(SUN_u16GetValue(SUN_nu16FilterSolar))
#define CCP_u8DataArrayA3_Byte7		CCP_u8GetHighByte(SUN_u16GetValue(SUN_nu16FilterSolar))

#define CCP_u8DataArrayA4_Byte1		NO_USE
#define CCP_u8DataArrayA4_Byte2		CCP_u8GetLowByte(SUN_u16GetValue(SUN_nu16TempOffsetDr))
#define CCP_u8DataArrayA4_Byte3		CCP_u8GetHighByte(SUN_u16GetValue(SUN_nu16TempOffsetDr))
#define CCP_u8DataArrayA4_Byte4		CCP_u8GetLowByte(SUN_u16GetValue(SUN_nu16TempOffsetPs))
#define CCP_u8DataArrayA4_Byte5		CCP_u8GetHighByte(SUN_u16GetValue(SUN_nu16TempOffsetPs))
#define CCP_u8DataArrayA4_Byte6		CCP_u8GetLowByte(SUN_u16GetValue(SUN_nu16BlowerOffset))
#define CCP_u8DataArrayA4_Byte7		CCP_u8GetHighByte(SUN_u16GetValue(SUN_nu16BlowerOffset))

#define CCP_u8DataArrayA5_Byte1		CCP_u8GetLowByte(SUN_u16GetValue(SUN_nu16ErrCode))
#define CCP_u8DataArrayA5_Byte2		CCP_u8GetHighByte(SUN_u16GetValue(SUN_nu16ErrCode))
#define CCP_u8DataArrayA5_Byte3		CCP_u8GetLowByte(SUN_u16GetValue(SUN_nu16SensorRawValueLeft))
#define CCP_u8DataArrayA5_Byte4		CCP_u8GetHighByte(SUN_u16GetValue(SUN_nu16SensorRawValueLeft))
#define CCP_u8DataArrayA5_Byte5		CCP_u8GetLowByte(SUN_u16GetValue(SUN_nu16SensorRawValueRight))
#define CCP_u8DataArrayA5_Byte6		CCP_u8GetHighByte(SUN_u16GetValue(SUN_nu16SensorRawValueRight))
#define CCP_u8DataArrayA5_Byte7		NO_USE

#define CCP_u8DataArrayA6_Byte1		NO_USE//OAT_u8GetValue(OAT_nu8SwVersion)
#define CCP_u8DataArrayA6_Byte2		CCP_u8GetLowByte(OAT_u16GetValue(OAT_nu16Value))
#define CCP_u8DataArrayA6_Byte3		CCP_u8GetHighByte(OAT_u16GetValue(OAT_nu16Value))
#define CCP_u8DataArrayA6_Byte4		CCP_u8GetLowByte(OAT_u16GetValue(OAT_nu16ValueHys))
#define CCP_u8DataArrayA6_Byte5		CCP_u8GetHighByte(OAT_u16GetValue(OAT_nu16ValueHys))
#define CCP_u8DataArrayA6_Byte6		CCP_u8GetLowByte(OAT_u16GetValue(OAT_nu16PhyRawValue))
#define CCP_u8DataArrayA6_Byte7		CCP_u8GetHighByte(OAT_u16GetValue(OAT_nu16PhyRawValue))

#define CCP_u8DataArrayA7_Byte1		CCP_u8GetLowByte(OAT_u16GetValue(OAT_nu16ErrorCode))
#define CCP_u8DataArrayA7_Byte2		CCP_u8GetHighByte(OAT_u16GetValue(OAT_nu16ErrorCode))
#define CCP_u8DataArrayA7_Byte3		CCP_u8GetLowByte(OAT_u16GetValue(OAT_nu16EedOatValue))
#define CCP_u8DataArrayA7_Byte4		CCP_u8GetHighByte(OAT_u16GetValue(OAT_nu16EedOatValue))
#define CCP_u8DataArrayA7_Byte5		CCP_u8GetLowByte(OAT_u16GetValue(OAT_nu16EedHctValue))
#define CCP_u8DataArrayA7_Byte6		CCP_u8GetHighByte(OAT_u16GetValue(OAT_nu16EedHctValue))
#define CCP_u8DataArrayA7_Byte7		NO_USE

#define CCP_u8DataArrayA8_Byte1		NO_USE //Rte_IRead_Ccp_vMain_Get_A8_1_CtsSwVersion_u8Version()//ICT_u8GetValue(ICT_nu8SwVersion) /*ITP4,160423*/
#define CCP_u8DataArrayA8_Byte2		NO_USE //CCP_u8GetLowByte(ICT_u16GetValue(ICT_nu16Value))
#define CCP_u8DataArrayA8_Byte3		NO_USE //CCP_u8GetHighByte(ICT_u16GetValue(ICT_nu16Value))
#define CCP_u8DataArrayA8_Byte4		NO_USE //CCP_u8GetLowByte(ICT_u16GetValue(ICT_nu16UndampedValue))
#define CCP_u8DataArrayA8_Byte5		NO_USE //CCP_u8GetHighByte(ICT_u16GetValue(ICT_nu16UndampedValue))
#define CCP_u8DataArrayA8_Byte6		NO_USE //CCP_u8GetLowByte(ICT_u16GetValue(ICT_nu16LinearLimitValue))
#define CCP_u8DataArrayA8_Byte7		NO_USE //CCP_u8GetHighByte(ICT_u16GetValue(ICT_nu16LinearLimitValue))

#define CCP_u8DataArrayA9_Byte1		NO_USE//ICT_u8GetValue(ICT_nu8SwVersion)
#define CCP_u8DataArrayA9_Byte2		NO_USE //CCP_u8GetLowByte(ICT_u16GetValue(ICT_nu16DynOffset))
#define CCP_u8DataArrayA9_Byte3		NO_USE //CCP_u8GetHighByte(ICT_u16GetValue(ICT_nu16DynOffset))
#define CCP_u8DataArrayA9_Byte4		NO_USE //CCP_u8GetLowByte(ICT_u16GetValue(ICT_nu16DynMax))
#define CCP_u8DataArrayA9_Byte5		NO_USE //CCP_u8GetHighByte(ICT_u16GetValue(ICT_nu16DynMax))
#define CCP_u8DataArrayA9_Byte6		NO_USE //CCP_u8GetLowByte(ICT_u16GetValue(ICT_nu16MaxDiff))
#define CCP_u8DataArrayA9_Byte7		NO_USE //CCP_u8GetHighByte(ICT_u16GetValue(ICT_nu16MaxDiff))

#define CCP_u8DataArrayAA_Byte1		NO_USE //CCP_u8GetLowByte(ICT_u16GetValue(ICT_nu16StaticOffset))
#define CCP_u8DataArrayAA_Byte2		NO_USE //CCP_u8GetHighByte(ICT_u16GetValue(ICT_nu16StaticOffset))
#define CCP_u8DataArrayAA_Byte3		NO_USE //CCP_u8GetLowByte(ICT_u16GetValue(ICT_nu16ErrorState))
#define CCP_u8DataArrayAA_Byte4		NO_USE //CCP_u8GetHighByte(ICT_u16GetValue(ICT_nu16ErrorState))
#define CCP_u8DataArrayAA_Byte5		NO_USE //CCP_u8GetLowByte(ICT_u16GetValue(ICT_nu16SensorValue))
#define CCP_u8DataArrayAA_Byte6		NO_USE //CCP_u8GetHighByte(ICT_u16GetValue(ICT_nu16SensorValue))
#define CCP_u8DataArrayAA_Byte7		NO_USE

#define CCP_u8DataArrayAB_Byte1		NO_USE//REV_u8GetValue(REV_nu8SwVersion)
#define CCP_u8DataArrayAB_Byte2		CCP_u8GetLowByte(CANAPP_u16GetValue(CANAPP_nu16EMS_EngineSpeedRPM))
#define CCP_u8DataArrayAB_Byte3		CCP_u8GetHighByte(CANAPP_u16GetValue(CANAPP_nu16EMS_EngineSpeedRPM))
#define CCP_u8DataArrayAB_Byte4		NO_USE
#define CCP_u8DataArrayAB_Byte5		NO_USE
#define CCP_u8DataArrayAB_Byte6		NO_USE
#define CCP_u8DataArrayAB_Byte7		NO_USE

#define CCP_u8DataArrayAC_Byte1		NO_USE//REV_u8GetValue(REV_nu8EngineRun)
#define CCP_u8DataArrayAC_Byte2		NO_USE//CCP_u8GetLowByte(REV_u16GetValue(REV_nu16ErrCode))
#define CCP_u8DataArrayAC_Byte3		NO_USE//CCP_u8GetHighByte(REV_u16GetValue(REV_nu16ErrCode))
#define CCP_u8DataArrayAC_Byte4		NO_USE
#define CCP_u8DataArrayAC_Byte5		NO_USE
#define CCP_u8DataArrayAC_Byte6		NO_USE
#define CCP_u8DataArrayAC_Byte7		NO_USE

#define CCP_u8DataArrayAD_Byte1	    RDC_u8GetValue(RDC_nu8SwVersion)
#define CCP_u8DataArrayAD_Byte2		NO_USE//CCP_u8GetLowByte(RDC_u16GetValue(RDC_nu16RunTime))
#define CCP_u8DataArrayAD_Byte3		NO_USE//CCP_u8GetHighByte(RDC_u16GetValue(RDC_nu16RunTime))
#define CCP_u8DataArrayAD_Byte4		NO_USE
#define CCP_u8DataArrayAD_Byte5		NO_USE
#define CCP_u8DataArrayAD_Byte6		NO_USE
#define CCP_u8DataArrayAD_Byte7		NO_USE

#define CCP_u8DataArrayAE_Byte1		NO_USE//RDC_u8GetValue(RDC_nu8OutputRequest)
#define CCP_u8DataArrayAE_Byte2		NO_USE//RDC_u8GetValue(RDC_nu8ErrCode)
#define CCP_u8DataArrayAE_Byte3		NO_USE//CCP_u8GetHighByte(RDC_u16GetValue(RDC_nu16ErrCode))
#define CCP_u8DataArrayAE_Byte4		RDC_u8GetValue(RDC_nu8Display)
#define CCP_u8DataArrayAE_Byte5		RDC_u8GetValue(RDC_nu8Feedback)
#define CCP_u8DataArrayAE_Byte6		RDC_u8GetValue(RDC_nu8Request)
#define CCP_u8DataArrayAE_Byte7		NO_USE

#define CCP_u8DataArrayAF_Byte1		NO_USE//STM_u8GetValue(STM_nu8SwVersion) 
#define CCP_u8DataArrayAF_Byte2		NO_USE
#define CCP_u8DataArrayAF_Byte3		NO_USE
#define CCP_u8DataArrayAF_Byte4		NO_USE
#define CCP_u8DataArrayAF_Byte5		NO_USE
#define CCP_u8DataArrayAF_Byte6		NO_USE
#define CCP_u8DataArrayAF_Byte7		NO_USE

#define CCP_u8DataArrayB0_Byte1		NO_USE//STM_u16GetValue(STM_nu8MacErrorInfDr)
#define CCP_u8DataArrayB0_Byte2		NO_USE//CCP_u8GetLowByte(STM_u16GetValue(STM_nu16MacCurrPosDr))
#define CCP_u8DataArrayB0_Byte3		NO_USE//CCP_u8GetHighByte(STM_u16GetValue(STM_nu16MacCurrPosDr))
#define CCP_u8DataArrayB0_Byte4		NO_USE//CCP_u8GetLowByte(STM_u16GetValue(STM_nu16MacTargetPosDr))
#define CCP_u8DataArrayB0_Byte5		NO_USE//CCP_u8GetHighByte(STM_u16GetValue(STM_nu16MacTargetPosDr))
#define CCP_u8DataArrayB0_Byte6		NO_USE//CCP_u8GetLowByte(STM_u16GetValue(STM_nu16MacMaxPosDr))
#define CCP_u8DataArrayB0_Byte7		NO_USE//CCP_u8GetHighByte(STM_u16GetValue(STM_nu16MacMaxPosDr))

#define CCP_u8DataArrayB1_Byte1		NO_USE//STM_u16GetValue(STM_nu8MacErrorInfPs)
#define CCP_u8DataArrayB1_Byte2		NO_USE//CCP_u8GetLowByte(STM_u16GetValue(STM_nu16MacCurrPosPs))
#define CCP_u8DataArrayB1_Byte3		NO_USE//CCP_u8GetHighByte(STM_u16GetValue(STM_nu16MacCurrPosPs))
#define CCP_u8DataArrayB1_Byte4		NO_USE//CCP_u8GetLowByte(STM_u16GetValue(STM_nu16MacTargetPosPs))
#define CCP_u8DataArrayB1_Byte5		NO_USE//CCP_u8GetHighByte(STM_u16GetValue(STM_nu16MacTargetPosPs))
#define CCP_u8DataArrayB1_Byte6		NO_USE//CCP_u8GetLowByte(STM_u16GetValue(STM_nu16MacMaxPosPs))
#define CCP_u8DataArrayB1_Byte7		NO_USE//CCP_u8GetHighByte(STM_u16GetValue(STM_nu16MacMaxPosPs))

#define CCP_u8DataArrayB2_Byte1		NO_USE//STM_u16GetValue(STM_nu8AirdErrorInf)
#define CCP_u8DataArrayB2_Byte2		NO_USE//CCP_u8GetLowByte(STM_u16GetValue(STM_nu16AirdCurrPos))
#define CCP_u8DataArrayB2_Byte3		NO_USE//CCP_u8GetHighByte(STM_u16GetValue(STM_nu16AirdCurrPos))
#define CCP_u8DataArrayB2_Byte4		NO_USE//CCP_u8GetLowByte(STM_u16GetValue(STM_nu16AirdTargetPos))
#define CCP_u8DataArrayB2_Byte5		NO_USE//CCP_u8GetHighByte(STM_u16GetValue(STM_nu16AirdTargetPos))
#define CCP_u8DataArrayB2_Byte6		NO_USE//CCP_u8GetLowByte(STM_u16GetValue(STM_nu16AirdMaxPos))
#define CCP_u8DataArrayB2_Byte7		NO_USE//CCP_u8GetHighByte(STM_u16GetValue(STM_nu16AirdMaxPos))

#define CCP_u8DataArrayB3_Byte1		NO_USE//STM_u16GetValue(STM_nu8RfaErrorInf)
#define CCP_u8DataArrayB3_Byte2		NO_USE//CCP_u8GetLowByte(STM_u16GetValue(STM_nu16RfaCurrPos))
#define CCP_u8DataArrayB3_Byte3		NO_USE//CCP_u8GetHighByte(STM_u16GetValue(STM_nu16RfaCurrPos))
#define CCP_u8DataArrayB3_Byte4		NO_USE//CCP_u8GetLowByte(STM_u16GetValue(STM_nu16RfaTargetPos))
#define CCP_u8DataArrayB3_Byte5		NO_USE//CCP_u8GetHighByte(STM_u16GetValue(STM_nu16RfaTargetPos))
#define CCP_u8DataArrayB3_Byte6		NO_USE//CCP_u8GetLowByte(STM_u16GetValue(STM_nu16RfaMaxPos))
#define CCP_u8DataArrayB3_Byte7		NO_USE//CCP_u8GetHighByte(STM_u16GetValue(STM_nu16RfaMaxPos))

#define CCP_u8DataArrayB4_Byte1		NO_USE//LCD_u8GetValue(LCD_nu8SwVersion)
#define CCP_u8DataArrayB4_Byte2		NO_USE//LCD_u8GetValue(LCD_nu8DisplayInfo_0)
#define CCP_u8DataArrayB4_Byte3		NO_USE//LCD_u8GetValue(LCD_nu8DisplayInfo_1)
#define CCP_u8DataArrayB4_Byte4		NO_USE//LCD_u8GetValue(LCD_nu8DisplayInfo_2)
#define CCP_u8DataArrayB4_Byte5		NO_USE//LCD_u8GetValue(LCD_nu8DisplayInfo_3)
#define CCP_u8DataArrayB4_Byte6		NO_USE//LCD_u8GetValue(LCD_nu8DisplayInfo_4)
#define CCP_u8DataArrayB4_Byte7		NO_USE//LCD_u8GetValue(LCD_nu8DisplayInfo_5)

#define CCP_u8DataArrayB5_Byte1		NO_USE//LCD_u8GetValue(LCD_nu8DisplayInfo_6)
#define CCP_u8DataArrayB5_Byte2		NO_USE//LCD_u8GetValue(LCD_nu8DisplayInfo_7)
#define CCP_u8DataArrayB5_Byte3		NO_USE//LCD_u8GetValue(LCD_nu8DisplayInfo_8)
#define CCP_u8DataArrayB5_Byte4		NO_USE//LCD_u8GetValue(LCD_nu8DisplayInfo_9)
#define CCP_u8DataArrayB5_Byte5		NO_USE//LCD_u8GetValue(LCD_nu8DisplayInfo_10)
#define CCP_u8DataArrayB5_Byte6		NO_USE//LCD_u8GetValue(LCD_nu8DisplayInfo_11)
#define CCP_u8DataArrayB5_Byte7		NO_USE//LCD_u8GetValue(LCD_nu8DisplayInfo_12)

#define CCP_u8DataArrayB6_Byte1		NO_USE//LCD_u8GetValue(LCD_nu8DisplayInfo_13)
#define CCP_u8DataArrayB6_Byte2		NO_USE//LCD_u8GetValue(LCD_nu8DisplayInfo_14)
#define CCP_u8DataArrayB6_Byte3		NO_USE//LCD_u8GetValue(LCD_nu8DisplayInfo_15)
#define CCP_u8DataArrayB6_Byte4		NO_USE
#define CCP_u8DataArrayB6_Byte5		NO_USE
#define CCP_u8DataArrayB6_Byte6		NO_USE
#define CCP_u8DataArrayB6_Byte7		NO_USE

#define CCP_u8DataArrayB7_Byte1		NO_USE//CCP_u8GetLowByte(Rte_IRead_Ccp_vMain_Get_B7_12_LcdErrorCode_u16BitMap())
#define CCP_u8DataArrayB7_Byte2		NO_USE//CCP_u8GetHighByte(Rte_IRead_Ccp_vMain_Get_B7_12_LcdErrorCode_u16BitMap())
#define CCP_u8DataArrayB7_Byte3		NO_USE
#define CCP_u8DataArrayB7_Byte4		NO_USE
#define CCP_u8DataArrayB7_Byte5		NO_USE
#define CCP_u8DataArrayB7_Byte6		NO_USE
#define CCP_u8DataArrayB7_Byte7		NO_USE

#define CCP_u8DataArrayB8_Byte1		ACCC_u8GetValue(ACCC_nu8SwVersion)//Rte_IRead_Ccp_vMain_Get_B8_1_AcccSwVersion_u8Version()//ACCC_u8GetValue(ACCC_nu8SwVersion)
#define CCP_u8DataArrayB8_Byte2		ACCC_u8GetValue(ACCC_nu8AcActualRequest)
#define CCP_u8DataArrayB8_Byte3		ACCC_u8GetValue(ACCC_nu8AcDisplay)
#define CCP_u8DataArrayB8_Byte4		ACCC_u8GetValue(ACCC_nu8MmiAcReq)
#define CCP_u8DataArrayB8_Byte5		CCP_u8GetLowByte(ACCC_u16GetValue(ACCC_nu16AcOffCode)/*Rte_IRead_Ccp_vMain_Get_B8_56_AcccOffCode_u16BitMap()*/)
#define CCP_u8DataArrayB8_Byte6		CCP_u8GetHighByte(ACCC_u16GetValue(ACCC_nu16AcOffCode)/*Rte_IRead_Ccp_vMain_Get_B8_56_AcccOffCode_u16BitMap()*/)
#define CCP_u8DataArrayB8_Byte7		NO_USE//ACCCDRV_u8GetValue(ACCCDRV_nu8EvapValveReq)//ACCC_u8GetValue(ACCC_nu8FuelCutState)

#define CCP_u8DataArrayB9_Byte1		NO_USE//CCP_u8GetLowByte(ACCCDRV_u16GetValue(ACCCDRV_nu16TargetPower))//AC_CompPowerLimit
#define CCP_u8DataArrayB9_Byte2		NO_USE//CCP_u8GetHighByte(ACCCDRV_u16GetValue(ACCCDRV_nu16TargetPower))//AC_CompPowerReq
#define CCP_u8DataArrayB9_Byte3		NO_USE//CCP_u8GetLowByte(ACCCDRV_u16GetValue(ACCCDRV_nu16TargetPower))//AC_CompTargetSpeed
#define CCP_u8DataArrayB9_Byte4		NO_USE//CCP_u8GetHighByte(ACCCDRV_u16GetValue(ACCCDRV_nu16TargetPower))//AcccEvapTargetTemp
#define CCP_u8DataArrayB9_Byte5		NO_USE//AcccHighSpdFan
#define CCP_u8DataArrayB9_Byte6		NO_USE//CCP_u8GetLowByte(ACCC_u16GetValue(ACCC_nu16EvapToff))
#define CCP_u8DataArrayB9_Byte7		NO_USE//CCP_u8GetHighByte(ACCC_u16GetValue(ACCC_nu16EvapToff))

#define CCP_u8DataArrayBA_Byte1		NO_USE//CCP_u8GetLowByte((uint16)(ACCC_u32GetValue(ACCC_nu32AcOffCode)>>16))
#define CCP_u8DataArrayBA_Byte2		NO_USE//CCP_u8GetHighByte((uint16)(ACCC_u32GetValue(ACCC_nu32AcOffCode)>>16))
#define CCP_u8DataArrayBA_Byte3		NO_USE//CCP_u8GetLowByte(ACCC_u16GetValue(ACCC_nu16TgtEvapTemp))
#define CCP_u8DataArrayBA_Byte4		NO_USE//CCP_u8GetHighByte(ACCC_u16GetValue(ACCC_nu16TgtEvapTemp))
#define CCP_u8DataArrayBA_Byte5		NO_USE//CCP_u8GetLowByte(ACCCDRV_u16GetValue(ACCCDRV_nu16ActualSpeedReq))
#define CCP_u8DataArrayBA_Byte6		NO_USE//CCP_u8GetHighByte(ACCCDRV_u16GetValue(ACCCDRV_nu16ActualSpeedReq))
#define CCP_u8DataArrayBA_Byte7		NO_USE//ACCCDRV_u8GetValue(ACCCDRV_nu8ChillerValveReq)

#define CCP_u8DataArrayBB_Byte1		EVAP_u8GetValue(EVAP_nu8SwVersion)
#define CCP_u8DataArrayBB_Byte2		CCP_u8GetLowByte(EVAP_u16GetValue(EVAP_nu16MacValue))
#define CCP_u8DataArrayBB_Byte3		CCP_u8GetHighByte(EVAP_u16GetValue(EVAP_nu16MacValue))
#define CCP_u8DataArrayBB_Byte4		CCP_u8GetLowByte(EVAP_u16GetValue(EVAP_nu16AcValue))
#define CCP_u8DataArrayBB_Byte5		CCP_u8GetHighByte(EVAP_u16GetValue(EVAP_nu16AcValue))
#define CCP_u8DataArrayBB_Byte6		NO_USE//CCP_u8GetLowByte(EVAP_u16GetValue(EVAP_nu16DynOffset))
#define CCP_u8DataArrayBB_Byte7		NO_USE//CCP_u8GetHighByte(EVAP_u16GetValue(EVAP_nu16DynOffset))

#define CCP_u8DataArrayBC_Byte1		CCP_u8GetLowByte(EVAP_u16GetValue(EVAP_nu16ErrorCode))
#define CCP_u8DataArrayBC_Byte2		CCP_u8GetHighByte(EVAP_u16GetValue(EVAP_nu16ErrorCode))
#define CCP_u8DataArrayBC_Byte3		CCP_u8GetLowByte(EVAP_u16GetValue(EVAP_nu16RawValue))
#define CCP_u8DataArrayBC_Byte4		CCP_u8GetHighByte(EVAP_u16GetValue(EVAP_nu16RawValue))
#define CCP_u8DataArrayBC_Byte5		NO_USE
#define CCP_u8DataArrayBC_Byte6		NO_USE
#define CCP_u8DataArrayBC_Byte7		NO_USE

#define CCP_u8DataArrayBD_Byte1		NO_USE//IGN_u8GetValue(IGN_nu8SwVersion)/*this value is error for J72L*/
#define CCP_u8DataArrayBD_Byte2		NO_USE//IGN_u8GetValue(IGN_nu8KeyPos)
#define CCP_u8DataArrayBD_Byte3		NO_USE//CCP_u8GetLowByte(IGN_u16GetValue(IGN_nu16ErrorCode))
#define CCP_u8DataArrayBD_Byte4		NO_USE//CCP_u8GetHighByte(IGN_u16GetValue(IGN_nu16ErrorCode))
#define CCP_u8DataArrayBD_Byte5		NO_USE
#define CCP_u8DataArrayBD_Byte6		NO_USE
#define CCP_u8DataArrayBD_Byte7		NO_USE

#define CCP_u8DataArrayBE_Byte1		((uint8)POW_u16GetValue(POW_nu16SwVersion))
#define CCP_u8DataArrayBE_Byte2		((uint8)POW_u16GetValue(POW_nu16AppLowVoltage))
#define CCP_u8DataArrayBE_Byte3		((uint8)POW_u16GetValue(POW_nu16AppHighVoltage))
#define CCP_u8DataArrayBE_Byte4		((uint8)POW_u16GetValue(POW_nu16ComLowVoltage))
#define CCP_u8DataArrayBE_Byte5		((uint8)POW_u16GetValue(POW_nu16ComHighVoltage))
#define CCP_u8DataArrayBE_Byte6		((uint8)POW_u16GetValue(POW_nu16DiagLowVoltage))
#define CCP_u8DataArrayBE_Byte7		((uint8)POW_u16GetValue(POW_nu16DiagHighVoltage))

#define CCP_u8DataArrayBF_Byte1		CCP_u8GetLowByte(POW_u16GetValue(POW_nu16ErrorCode))
#define CCP_u8DataArrayBF_Byte2		CCP_u8GetHighByte(POW_u16GetValue(POW_nu16ErrorCode))
#define CCP_u8DataArrayBF_Byte3		CCP_u8GetLowByte(POW_u16GetValue(POW_nu16RawK30VoltFb))
#define CCP_u8DataArrayBF_Byte4		CCP_u8GetHighByte(POW_u16GetValue(POW_nu16RawK30VoltFb))
#define CCP_u8DataArrayBF_Byte5		NO_USE
#define CCP_u8DataArrayBF_Byte6		NO_USE
#define CCP_u8DataArrayBF_Byte7		NO_USE

#define CCP_u8DataArrayC0_Byte1		NO_USE//PTA_u8GetValue(PTA_nu8SwVersion)
#define CCP_u8DataArrayC0_Byte2		CCP_u8GetLowByte(CCP_u16GetAdValue(12))//5V_DET
#define CCP_u8DataArrayC0_Byte3		CCP_u8GetHighByte(CCP_u16GetAdValue(12))//5V-DET
#define CCP_u8DataArrayC0_Byte4		CCP_u8GetLowByte(CCP_u16GetAdValue(13))//K30
#define CCP_u8DataArrayC0_Byte5		CCP_u8GetHighByte(CCP_u16GetAdValue(13))//K30
#define CCP_u8DataArrayC0_Byte6		NO_USE//CCP_u8GetLowByte(IGN_u16GetValue(IGN_nu16IGN2Fb))//K15
#define CCP_u8DataArrayC0_Byte7		NO_USE//CCP_u8GetHighByte(IGN_u16GetValue(IGN_nu16IGN2Fb))//K15

#define CCP_u8DataArrayC1_Byte1		NO_USE//PTA_u8GetValue(PTA_nu8Valid)
#define CCP_u8DataArrayC1_Byte2		CCP_u8GetLowByte(CCP_u16GetAdValue(6))//CCP_u8GetLowByte(HAL_u16AdcGet(2U))//EVAP
#define CCP_u8DataArrayC1_Byte3		CCP_u8GetHighByte(CCP_u16GetAdValue(6))//CCP_u8GetHighByte(HAL_u16AdcGet(2U))//EVAP
#define CCP_u8DataArrayC1_Byte4		CCP_u8GetLowByte(CCP_u16GetAdValue(3))//CCP_u8GetLowByte(PTA_u16GetValue(PTA_nRawIncarTemp))
#define CCP_u8DataArrayC1_Byte5		CCP_u8GetHighByte(CCP_u16GetAdValue(3))//CCP_u8GetHighByte(PTA_u16GetValue(PTA_nRawIncarTemp))
#define CCP_u8DataArrayC1_Byte6		CCP_u8GetLowByte(CCP_u16GetAdValue(9))//CCP_u8GetLowByte(PTA_u16GetValue(PTA_nRawAmbTemp))
#define CCP_u8DataArrayC1_Byte7		CCP_u8GetHighByte(CCP_u16GetAdValue(9))//CCP_u8GetHighByte(PTA_u16GetValue(PTA_nRawAmbTemp))

#define CCP_u8DataArrayC2_Byte1		NO_USE
#define CCP_u8DataArrayC2_Byte2		CCP_u8GetLowByte(CCP_u16GetAdValue(7))
#define CCP_u8DataArrayC2_Byte3		CCP_u8GetHighByte(CCP_u16GetAdValue(7))
#define CCP_u8DataArrayC2_Byte4		CCP_u8GetLowByte(CCP_u16GetAdValue(8))
#define CCP_u8DataArrayC2_Byte5		CCP_u8GetHighByte(CCP_u16GetAdValue(8))
#define CCP_u8DataArrayC2_Byte6		CCP_u8GetLowByte(CCP_u16GetAdValue(11))//Mac_Dr_FB
#define CCP_u8DataArrayC2_Byte7		CCP_u8GetHighByte(CCP_u16GetAdValue(11))//Mac_Dr_FB

#define CCP_u8DataArrayC3_Byte1		NO_USE
#define CCP_u8DataArrayC3_Byte2		CCP_u8GetLowByte(CCP_u16GetAdValue(15))//Mac_Ps_FB
#define CCP_u8DataArrayC3_Byte3		CCP_u8GetHighByte(CCP_u16GetAdValue(15))//Mac_Ps_FB
#define CCP_u8DataArrayC3_Byte4		CCP_u8GetLowByte(CCP_u16GetAdValue(10))//AIRD_FB
#define CCP_u8DataArrayC3_Byte5		CCP_u8GetHighByte(CCP_u16GetAdValue(10))//AIRD_FB
#define CCP_u8DataArrayC3_Byte6		CCP_u8GetLowByte(CCP_u16GetAdValue(4))//FR_FB
#define CCP_u8DataArrayC3_Byte7		CCP_u8GetHighByte(CCP_u16GetAdValue(4))//FR_FB

#define CCP_u8DataArrayC4_Byte1		CCP_u8GetLowByte(CCP_u16GetAdValue(2))
#define CCP_u8DataArrayC4_Byte2		CCP_u8GetHighByte(CCP_u16GetAdValue(2)) // Raw blower Fb
#define CCP_u8DataArrayC4_Byte3		NO_USE//CCP_u8GetHighByte(HAL_u16AdcGet(2U))
#define CCP_u8DataArrayC4_Byte4	    CCP_u8GetLowByte(AQS_u16GetValue(AQS_nu16PwmValue))//CCP_u8GetHighByte(PTA_u16GetValue(PTA_nRawAqsFb))
#define CCP_u8DataArrayC4_Byte5		CCP_u8GetHighByte(AQS_u16GetValue(AQS_nu16PwmValue))
#define CCP_u8DataArrayC4_Byte6		NO_USE//CCP_u8GetLowByte(HAL_u16AdcGet(7U))//TEMP_KNOB
#define CCP_u8DataArrayC4_Byte7		NO_USE//CCP_u8GetHighByte(HAL_u16AdcGet(7U))//TEMP_KNOB

#define CCP_u8DataArrayC5_Byte1		NO_USE//CCP_u8GetLowByte(PTA_u16GetValue(PTA_nu16ErrCode))
#define CCP_u8DataArrayC5_Byte2		NO_USE//CCP_u8GetHighByte(PTA_u16GetValue(PTA_nu16ErrCode))
#define CCP_u8DataArrayC5_Byte3		NO_USE//CCP_u8GetLowByte(HAL_u16AdcGet(8U))//MODE KNOB
#define CCP_u8DataArrayC5_Byte4		NO_USE//CCP_u8GetHighByte(HAL_u16AdcGet(8U))//MODE_KNOB
#define CCP_u8DataArrayC5_Byte5		NO_USE//CCP_u8GetLowByte(HAL_u16AdcGet(16U))//BLOWER_KNOB
#define CCP_u8DataArrayC5_Byte6		NO_USE//CCP_u8GetHighByte(HAL_u16AdcGet(16U))//BLOWER_KNOB
#define CCP_u8DataArrayC5_Byte7		NO_USE

#define CCP_u8DataArrayC6_Byte1		NO_USE
#define CCP_u8DataArrayC6_Byte2		NO_USE//CCP_u8GetLowByte(PTA_u16GetValue(PTA_nResult5vVtgFb))
#define CCP_u8DataArrayC6_Byte3		NO_USE//CCP_u8GetHighByte(PTA_u16GetValue(PTA_nResult5vVtgFb))
#define CCP_u8DataArrayC6_Byte4		NO_USE//CCP_u8GetLowByte(PTA_u16GetValue(PTA_nResultKL30VtgFb))
#define CCP_u8DataArrayC6_Byte5		NO_USE//CCP_u8GetHighByte(PTA_u16GetValue(PTA_nResultKL30VtgFb))
#define CCP_u8DataArrayC6_Byte6		NO_USE//CCP_u8GetLowByte(PTA_u16GetValue(PTA_nResultKL15VtgFb))
#define CCP_u8DataArrayC6_Byte7		NO_USE//CCP_u8GetHighByte(PTA_u16GetValue(PTA_nResultKL15VtgFb))

#define CCP_u8DataArrayC7_Byte1		NO_USE
#define CCP_u8DataArrayC7_Byte2		NO_USE//CCP_u8GetLowByte(PTA_u16GetValue(PTA_nResultEvapTemp))
#define CCP_u8DataArrayC7_Byte3		NO_USE//CCP_u8GetHighByte(PTA_u16GetValue(PTA_nResultEvapTemp))
#define CCP_u8DataArrayC7_Byte4		NO_USE//CCP_u8GetLowByte(PTA_u16GetValue(PTA_nResultIncarTemp))
#define CCP_u8DataArrayC7_Byte5		NO_USE//CCP_u8GetHighByte(PTA_u16GetValue(PTA_nResultIncarTemp))
#define CCP_u8DataArrayC7_Byte6		NO_USE//CCP_u8GetLowByte(PTA_u16GetValue(PTA_nResultAmbTemp))
#define CCP_u8DataArrayC7_Byte7		NO_USE//CCP_u8GetHighByte(PTA_u16GetValue(PTA_nResultAmbTemp))

#define CCP_u8DataArrayC8_Byte1		NO_USE
#define CCP_u8DataArrayC8_Byte2		NO_USE//CCP_u8GetLowByte(PTA_u16GetValue(PTA_nResultSunDr))
#define CCP_u8DataArrayC8_Byte3		NO_USE//CCP_u8GetHighByte(PTA_u16GetValue(PTA_nResultSunDr))
#define CCP_u8DataArrayC8_Byte4		NO_USE//CCP_u8GetLowByte(PTA_u16GetValue(PTA_nResultSunPs))
#define CCP_u8DataArrayC8_Byte5		NO_USE//CCP_u8GetHighByte(PTA_u16GetValue(PTA_nResultSunPs))
#define CCP_u8DataArrayC8_Byte6		NO_USE
#define CCP_u8DataArrayC8_Byte7		NO_USE

#define CCP_u8DataArrayC9_Byte1		NO_USE
#define CCP_u8DataArrayC9_Byte2		NO_USE
#define CCP_u8DataArrayC9_Byte3		NO_USE
#define CCP_u8DataArrayC9_Byte4		NO_USE//CCP_u8GetLowByte(PSV_u16GetValue(PSV_nu16Value))
#define CCP_u8DataArrayC9_Byte5		NO_USE//CCP_u8GetHighByte(PSV_u16GetValue(PSV_nu16Value))
#define CCP_u8DataArrayC9_Byte6		NO_USE//CCP_u8GetLowByte(HAL_u16AdcGet(18U)) //CCP_u8GetLowByte(ACCC_u16GetValue(ACCC_nu16RawPreSensorAd))
#define CCP_u8DataArrayC9_Byte7		NO_USE//CCP_u8GetHighByte(HAL_u16AdcGet(18U)) //CCP_u8GetHighByte(ACCC_u16GetValue(ACCC_nu16RawPreSensorAd))

#define CCP_u8DataArrayCA_Byte1		NO_USE//CCP_u8GetLowByte(PTA_u16GetValue(PTA_nResultBlowerFb))
#define CCP_u8DataArrayCA_Byte2		NO_USE//CCP_u8GetLowByte(KEY_u16GetValue(KEY_nu16RawKeyAd1))
#define CCP_u8DataArrayCA_Byte3		NO_USE//CCP_u8GetHighByte(KEY_u16GetValue(KEY_nu16RawKeyAd1))
#define CCP_u8DataArrayCA_Byte4		NO_USE//CCP_u8GetLowByte(KEY_u16GetValue(KEY_nu16RawKeyAd2))
#define CCP_u8DataArrayCA_Byte5		NO_USE//CCP_u8GetHighByte(KEY_u16GetValue(KEY_nu16RawKeyAd2))
#define CCP_u8DataArrayCA_Byte6		NO_USE//CCP_u8GetLowByte(KEY_u16GetValue(KEY_nu16RawKeyAd3))
#define CCP_u8DataArrayCA_Byte7		NO_USE//CCP_u8GetHighByte(KEY_u16GetValue(KEY_nu16RawKeyAd3))

#define CCP_u8DataArrayCB_Byte1		NO_USE//KEY_u8GetValue(KEY_nu8SwVersion)
#define CCP_u8DataArrayCB_Byte2		NO_USE//KNOB_u8ValidFlag
#define CCP_u8DataArrayCB_Byte3		NO_USE//CCP_u8GetLowByte(KEY_u16GetValue(KEY_nu16PressedKey))
#define CCP_u8DataArrayCB_Byte4		NO_USE//CCP_u8GetHighByte(KEY_u16GetValue(KEY_nu16PressedKey))
#define CCP_u8DataArrayCB_Byte5		NO_USE//KEY_u8GetValue(KEY_enu8KeyPressed3)
#define CCP_u8DataArrayCB_Byte6		NO_USE//KEY_u8GetValue(KEY_enu8KeyPressed4)
#define CCP_u8DataArrayCB_Byte7		NO_USE

#define CCP_u8DataArrayCC_Byte1		NO_USE//CCP_u8GetLowByte(KEY_u16GetValue(KEY_nu16BlockedKey))//CCP_u8GetLowByte(KEY_u16BlockedKey)//KEY_u8GetValue(KEY_nu8ErrCode1)
#define CCP_u8DataArrayCC_Byte2		NO_USE//CCP_u8GetHighByte(KEY_u16GetValue(KEY_nu16BlockedKey))//CCP_u8GetHighByte(KEY_u16BlockedKey)//KEY_u8GetValue(KEY_nu8ErrCode2)
#define CCP_u8DataArrayCC_Byte3		NO_USE//KEY_u8GetValue(KEY_nu8ErrCode3)
#define CCP_u8DataArrayCC_Byte4		NO_USE//KEY_u8GetValue(KEY_nu8ErrCode4)
#define CCP_u8DataArrayCC_Byte5		NO_USE//CCP_u8GetLowByte(KEY_u16GetValue(KEY_nu16RawKey))
#define CCP_u8DataArrayCC_Byte6		NO_USE//CCP_u8GetHighByte(KEY_u16GetValue(KEY_nu16RawKey))
#define CCP_u8DataArrayCC_Byte7		NO_USE

#define CCP_u8DataArrayCD_Byte1		NO_USE//AQS_u8GetValue(AQS_nu8SwVersion)
#define CCP_u8DataArrayCD_Byte2		NO_USE//CCP_u8GetLowByte(AQS_u8GetValue(AQS_nu8AirBadTime))
#define CCP_u8DataArrayCD_Byte3		NO_USE//CCP_u8GetHighByte(AQS_u8GetValue(AQS_nu8AirBadTime))
#define CCP_u8DataArrayCD_Byte4		NO_USE
#define CCP_u8DataArrayCD_Byte5		NO_USE
#define CCP_u8DataArrayCD_Byte6		NO_USE
#define CCP_u8DataArrayCD_Byte7		NO_USE

#define CCP_u8DataArrayCE_Byte1		NO_USE//AQS_u8GetValue(AQS_nu8State)
#define CCP_u8DataArrayCE_Byte2		NO_USE//CCP_u8GetLowByte(AQS_u8GetValue(AQS_nu8ErrorCode))
#define CCP_u8DataArrayCE_Byte3		NO_USE//CCP_u8GetHighByte(AQS_u8GetValue(AQS_nu8ErrorCode))
#define CCP_u8DataArrayCE_Byte4		NO_USE
#define CCP_u8DataArrayCE_Byte5		NO_USE
#define CCP_u8DataArrayCE_Byte6		NO_USE
#define CCP_u8DataArrayCE_Byte7		NO_USE

#define CCP_u8DataArrayCF_Byte1		NO_USE//ION_u8GetValue(ION_nu8SwVersion)
#define CCP_u8DataArrayCF_Byte2		NO_USE//CCP_u8GetLowByte(ION_u16GetValue(ION_enu16BigDirtyLevel))
#define CCP_u8DataArrayCF_Byte3		NO_USE//CCP_u8GetHighByte(ION_u16GetValue(ION_enu16BigDirtyLevel))
#define CCP_u8DataArrayCF_Byte4		NO_USE//CCP_u8GetLowByte(ION_u16GetValue(ION_enu16SmallDirtyLevel))
#define CCP_u8DataArrayCF_Byte5		NO_USE//CCP_u8GetHighByte(ION_u16GetValue(ION_enu16SmallDirtyLevel))
#define CCP_u8DataArrayCF_Byte6		NO_USE//CCP_u8GetLowByte(ION_u16GetValue(ION_enu16BigDirtyCnt))
#define CCP_u8DataArrayCF_Byte7		NO_USE//CCP_u8GetHighByte(ION_u16GetValue(ION_enu16BigDirtyCnt))

#define CCP_u8DataArrayD0_Byte1		NO_USE//ION_u8GetValue(ION_nu8AirSatus)
#define CCP_u8DataArrayD0_Byte2		NO_USE//CCP_u8GetLowByte(ION_u16GetValue(ION_enu16SmallDirtyCnt))
#define CCP_u8DataArrayD0_Byte3		NO_USE//CCP_u8GetHighByte(ION_u16GetValue(ION_enu16SmallDirtyCnt))
#define CCP_u8DataArrayD0_Byte4		NO_USE//ION_u8GetValue(ION_nu8IONIZEState)
#define CCP_u8DataArrayD0_Byte5		NO_USE//ION_u8GetValue(ION_nu8PM25StsReq)
#define CCP_u8DataArrayD0_Byte6		NO_USE//ION_u8GetValue(ION_nu8PM25Sts)
#define CCP_u8DataArrayD0_Byte7		NO_USE//ION_u8GetValue(ION_nu8IONStsReq)

#define CCP_u8DataArrayD1_Byte1		NO_USE//CCP_u8GetLowByte(ION_u16GetValue(ION_nu16ErrorCode))
#define CCP_u8DataArrayD1_Byte2		NO_USE//CCP_u8GetHighByte(ION_u16GetValue(ION_nu16ErrorCode))
#define CCP_u8DataArrayD1_Byte3		NO_USE//CCP_u8GetLowByte(ION_u16GetValue(ION_nu16PM25OutDen))
#define CCP_u8DataArrayD1_Byte4		NO_USE//CCP_u8GetHighByte(ION_u16GetValue(ION_nu16PM25OutDen))
#define CCP_u8DataArrayD1_Byte5		NO_USE//CCP_u8GetLowByte(ION_u16GetValue(ION_nu16PM25InDen))
#define CCP_u8DataArrayD1_Byte6		NO_USE//CCP_u8GetHighByte(ION_u16GetValue(ION_nu16PM25InDen))
#define CCP_u8DataArrayD1_Byte7		NO_USE//ION_u8GetValue(ION_nu8IONIZEState)


#define CCP_u8DataArrayD2_Byte1		NO_USE
#define CCP_u8DataArrayD2_Byte2		NO_USE//KNOB_u8GetValue(KNOB_nu8ErrCode)
#define CCP_u8DataArrayD2_Byte3		NO_USE
#define CCP_u8DataArrayD2_Byte4		NO_USE//KNOB_u8GetValue(KNOB_nu8SwVersion)
#define CCP_u8DataArrayD2_Byte5		NO_USE
#define CCP_u8DataArrayD2_Byte6		NO_USE
#define CCP_u8DataArrayD2_Byte7		NO_USE

#define CCP_u8DataArrayD3_Byte1		NO_USE
#define CCP_u8DataArrayD3_Byte2		NO_USE
#define CCP_u8DataArrayD3_Byte3		NO_USE
#define CCP_u8DataArrayD3_Byte4		NO_USE
#define CCP_u8DataArrayD3_Byte5		NO_USE
#define CCP_u8DataArrayD3_Byte6		NO_USE
#define CCP_u8DataArrayD3_Byte7		NO_USE

#define CCP_u8DataArrayD4_Byte1		NO_USE//MODULE Name
#define CCP_u8DataArrayD4_Byte2		NO_USE
#define CCP_u8DataArrayD4_Byte3		NO_USE
#define CCP_u8DataArrayD4_Byte4		NO_USE
#define CCP_u8DataArrayD4_Byte5		NO_USE
#define CCP_u8DataArrayD4_Byte6		NO_USE
#define CCP_u8DataArrayD4_Byte7		NO_USE

#define CCP_u8DataArrayD5_Byte1		NO_USE//SW Version
#define CCP_u8DataArrayD5_Byte2		NO_USE
#define CCP_u8DataArrayD5_Byte3		NO_USE
#define CCP_u8DataArrayD5_Byte4		NO_USE
#define CCP_u8DataArrayD5_Byte5		NO_USE
#define CCP_u8DataArrayD5_Byte6		NO_USE
#define CCP_u8DataArrayD5_Byte7		NO_USE

#define CCP_u8DataArrayD6_Byte1		NO_USE//BctlDrv_u8GetValue(BctlDrv_nu8Valid)
#define CCP_u8DataArrayD6_Byte2		BCTLDRV_u8GetValue(BCTLDRV_nu8SwVersion)//BctlDrv_u8GetValue(BctlDrv_nu8SwVersion)
#define CCP_u8DataArrayD6_Byte3		CCP_u8GetLowByte(BCTLDRV_u16GetValue(BCTLDRV_nu16Error))
#define CCP_u8DataArrayD6_Byte4		CCP_u8GetHighByte(BCTLDRV_u16GetValue(BCTLDRV_nu16Error))
#define CCP_u8DataArrayD6_Byte5		CCP_u8GetLowByte(BCTLDRV_u16GetValue(BCTLDRV_nu16VoltFeedback))
#define CCP_u8DataArrayD6_Byte6		CCP_u8GetHighByte(BCTLDRV_u16GetValue(BCTLDRV_nu16VoltFeedback))
#define CCP_u8DataArrayD6_Byte7		NO_USE


#define CCP_u8DataArrayD7_Byte1		CCP_u8GetLowByte(BCTLDRV_u16GetValue(BCTLDRV_nu16PwmDuty))
#define CCP_u8DataArrayD7_Byte2		CCP_u8GetHighByte(BCTLDRV_u16GetValue(BCTLDRV_nu16PwmDuty))
#define CCP_u8DataArrayD7_Byte3		NO_USE
#define CCP_u8DataArrayD7_Byte4		NO_USE
#define CCP_u8DataArrayD7_Byte5		NO_USE
#define CCP_u8DataArrayD7_Byte6		NO_USE
#define CCP_u8DataArrayD7_Byte7		NO_USE

#define CCP_u8DataArrayD8_Byte1		((uint8)IGN_u16GetValue(IGN_nu16IGN2IoStatus))
#define CCP_u8DataArrayD8_Byte2		((uint8)IGN_u16GetValue(IGN_nu16IgnStable))
#define CCP_u8DataArrayD8_Byte3		((uint8)IGN_u16GetValue(IGN_nu16IgnStaticOn))
#define CCP_u8DataArrayD8_Byte4		NO_USE
#define CCP_u8DataArrayD8_Byte5		NO_USE
#define CCP_u8DataArrayD8_Byte6		NO_USE
#define CCP_u8DataArrayD8_Byte7		NO_USE

#define CCP_u8DataArrayD9_Byte1		NO_USE
#define CCP_u8DataArrayD9_Byte2		NO_USE
#define CCP_u8DataArrayD9_Byte3		NO_USE
#define CCP_u8DataArrayD9_Byte4		NO_USE
#define CCP_u8DataArrayD9_Byte5		NO_USE
#define CCP_u8DataArrayD9_Byte6		NO_USE
#define CCP_u8DataArrayD9_Byte7		NO_USE


#define CCP_u8DataArrayDA_Byte1	    NO_USE//DIM_u8GetValue(DIM_nu8Valid)
#define CCP_u8DataArrayDA_Byte2		NO_USE//DIM_u8GetValue(DIM_nu8SwVersion)
#define CCP_u8DataArrayDA_Byte3		NO_USE
#define CCP_u8DataArrayDA_Byte4		NO_USE//DIM_u8GetValue(DIM_nu8AcDuty)
#define CCP_u8DataArrayDA_Byte5		NO_USE//DIM_u8GetValue(DIM_nu8RecDuty)
#define CCP_u8DataArrayDA_Byte6		NO_USE//DIM_u8GetValue(DIM_nu8RdefDuty)
#define CCP_u8DataArrayDA_Byte7		NO_USE

#define CCP_u8DataArrayDB_Byte1		NO_USE//DIM_u8GetValue(DIM_nu8TempKnobSymbolDuty)
#define CCP_u8DataArrayDB_Byte2		NO_USE//DIM_u8GetValue(DIM_nu8BlowerKnobSymbolDuty)
#define CCP_u8DataArrayDB_Byte3		NO_USE//DIM_u8GetValue(DIM_nu8ModeKnobSymbolDuty)
#define CCP_u8DataArrayDB_Byte4		NO_USE
#define CCP_u8DataArrayDB_Byte5		NO_USE
#define CCP_u8DataArrayDB_Byte6		NO_USE
#define CCP_u8DataArrayDB_Byte7		NO_USE

#define CCP_u8DataArrayDC_Byte1		NO_USE//CCP_u8GetLowByte(RFA_u16GetValue(RFA_nu16FogDegTimer))
#define CCP_u8DataArrayDC_Byte2		NO_USE//CCP_u8GetHighByte(RFA_u16GetValue(RFA_nu16FogDegTimer))
#define CCP_u8DataArrayDC_Byte3		NO_USE//RFA_u8GetValue(RFA_nu8InitFogCtrlFlg)
#define CCP_u8DataArrayDC_Byte4		NO_USE//RFA_u8GetValue(RFA_nu8FogConfirmFlg)
#define CCP_u8DataArrayDC_Byte5		NO_USE//RFA_u8GetValue(RFA_nu8AtcAImodeTrg)
#define CCP_u8DataArrayDC_Byte6		NO_USE//RFA_u8GetValue(RFA_nu8AIModeTimeFlg)
#define CCP_u8DataArrayDC_Byte7		NO_USE

#define CCP_u8DataArrayDD_Byte1		NO_USE
#define CCP_u8DataArrayDD_Byte2		NO_USE
#define CCP_u8DataArrayDD_Byte3		NO_USE
#define CCP_u8DataArrayDD_Byte4		NO_USE
#define CCP_u8DataArrayDD_Byte5		NO_USE
#define CCP_u8DataArrayDD_Byte6		NO_USE
#define CCP_u8DataArrayDD_Byte7		NO_USE

#define CCP_u8DataArrayDE_Byte1		NO_USE
#define CCP_u8DataArrayDE_Byte2		NO_USE//PTC_u8GetValue(PTC_nu8SwVersion)
#define CCP_u8DataArrayDE_Byte3		NO_USE//PTC_u8GetValue(PTC_nu8AmbientTempValid)
#define CCP_u8DataArrayDE_Byte4		NO_USE//PTC_u8GetValue(PTC_nu8CoolantTempValid)
#define CCP_u8DataArrayDE_Byte5		NO_USE//PTC_u8GetValue(PTC_nu8PtcSwitch)
#define CCP_u8DataArrayDE_Byte6		NO_USE
#define CCP_u8DataArrayDE_Byte7		NO_USE

#define CCP_u8DataArrayDF_Byte1		NO_USE//vPTC_u8GetValue(PTC_nu8ErrCode0)
#define CCP_u8DataArrayDF_Byte2		NO_USE//PTC_u8GetValue(PTC_nu8ErrCode1)
#define CCP_u8DataArrayDF_Byte3		NO_USE
#define CCP_u8DataArrayDF_Byte4		NO_USE
#define CCP_u8DataArrayDF_Byte5		NO_USE
#define CCP_u8DataArrayDF_Byte6		NO_USE
#define CCP_u8DataArrayDF_Byte7		NO_USE

#define CCP_u8DataArrayE0_Byte1			NO_USE
#define CCP_u8DataArrayE0_Byte2			NO_USE
#define CCP_u8DataArrayE0_Byte3			NO_USE
#define CCP_u8DataArrayE0_Byte4			NO_USE
#define CCP_u8DataArrayE0_Byte5			NO_USE
#define CCP_u8DataArrayE0_Byte6			NO_USE
#define CCP_u8DataArrayE0_Byte7			NO_USE

#define CCP_u8DataArrayE1_Byte1			NO_USE//ISTP_u8GetValue(ISTP_nu8Valid)
#define CCP_u8DataArrayE1_Byte2			NO_USE//ISTP_u8GetValue(ISTP_nu8Version)
#define CCP_u8DataArrayE1_Byte3			NO_USE//CCP_u8GetLowByte(ISTP_u16GetValue(ISTP_nu16ThTemp))
#define CCP_u8DataArrayE1_Byte4			NO_USE//CCP_u8GetHighByte(ISTP_u16GetValue(ISTP_nu16ThTemp))
#define CCP_u8DataArrayE1_Byte5			NO_USE//CCP_u8GetLowByte(ISTP_u16GetValue(ISTP_nu16ThCTemp))
#define CCP_u8DataArrayE1_Byte6			NO_USE//CCP_u8GetHighByte(ISTP_u16GetValue(ISTP_nu16ThCTemp))
#define CCP_u8DataArrayE1_Byte7			NO_USE//ISTP_u8GetValue(ISTP_nu8ISState)

#define CCP_u8DataArrayE2_Byte1			NO_USE//CCP_u8GetLowByte(ISTP_u16GetValue(ISTP_nu16IStimer))
#define CCP_u8DataArrayE2_Byte2			NO_USE//CCP_u8GetHighByte(ISTP_u16GetValue(ISTP_nu16IStimer))
#define CCP_u8DataArrayE2_Byte3			NO_USE//CCP_u8GetLowByte(ISTP_u16GetValue(ISTP_nu16IRtimer))
#define CCP_u8DataArrayE2_Byte4			NO_USE//CCP_u8GetHighByte(ISTP_u16GetValue(ISTP_nu16IRtimer))
#define CCP_u8DataArrayE2_Byte5			NO_USE//CCP_u8GetLowByte(ISTP_u16GetValue(ISTP_nu16TimerA))
#define CCP_u8DataArrayE2_Byte6			NO_USE//CCP_u8GetHighByte(ISTP_u16GetValue(ISTP_nu16TimerA))
#define CCP_u8DataArrayE2_Byte7			NO_USE//ISTP_u8GetValue(ISTP_nu8ISFalt)

#define CCP_u8DataArrayE3_Byte1			NO_USE//CCP_u8GetLowByte(ISTP_u16GetValue(ISTP_nu16TimerB))
#define CCP_u8DataArrayE3_Byte2			NO_USE//CCP_u8GetHighByte(ISTP_u16GetValue(ISTP_nu16TimerB))
#define CCP_u8DataArrayE3_Byte3			NO_USE//CCP_u8GetLowByte(ISTP_u16GetValue(ISTP_nu16Thir))
#define CCP_u8DataArrayE3_Byte4			NO_USE//CCP_u8GetHighByte(ISTP_u16GetValue(ISTP_nu16Thir))
#define CCP_u8DataArrayE3_Byte5			NO_USE//CCP_u8GetLowByte(ISTP_u16GetValue(ISTP_nu16Twir))
#define CCP_u8DataArrayE3_Byte6			NO_USE//CCP_u8GetHighByte(ISTP_u16GetValue(ISTP_nu16Twir))
#define CCP_u8DataArrayE3_Byte7			NO_USE//ISTP_u8GetValue(ISTP_nu8EngineState)

#define CCP_u8DataArrayE4_Byte1			NO_USE//CCP_u8GetLowByte(ISTP_u16GetValue(ISTP_nu16This))
#define CCP_u8DataArrayE4_Byte2			NO_USE//CCP_u8GetHighByte(ISTP_u16GetValue(ISTP_nu16This))
#define CCP_u8DataArrayE4_Byte3			NO_USE//CCP_u8GetLowByte(ISTP_u16GetValue(ISTP_nu16ThD1))
#define CCP_u8DataArrayE4_Byte4			NO_USE//CCP_u8GetHighByte(ISTP_u16GetValue(ISTP_nu16ThD1))
#define CCP_u8DataArrayE4_Byte5			NO_USE//CCP_u8GetLowByte(ISTP_u16GetValue(ISTP_nu16ThD2))
#define CCP_u8DataArrayE4_Byte6			NO_USE//CCP_u8GetHighByte(ISTP_u16GetValue(ISTP_nu16ThD2))
#define CCP_u8DataArrayE4_Byte7			NO_USE//ISTP_u8GetValue(ISTP_nu8InitializeFlg)

#define CCP_u8DataArrayE5_Byte1			NO_USE//ISTP_u8GetValue(ISTP_nu8IsStepinFlg)
#define CCP_u8DataArrayE5_Byte2			NO_USE
#define CCP_u8DataArrayE5_Byte3			NO_USE
#define CCP_u8DataArrayE5_Byte4			NO_USE
#define CCP_u8DataArrayE5_Byte5			NO_USE
#define CCP_u8DataArrayE5_Byte6			NO_USE
#define CCP_u8DataArrayE5_Byte7			NO_USE

#define CCP_u8DataArrayE6_Byte1			NO_USE
#define CCP_u8DataArrayE6_Byte2			NO_USE
#define CCP_u8DataArrayE6_Byte3			NO_USE
#define CCP_u8DataArrayE6_Byte4			NO_USE
#define CCP_u8DataArrayE6_Byte5			NO_USE
#define CCP_u8DataArrayE6_Byte6			NO_USE
#define CCP_u8DataArrayE6_Byte7			NO_USE

#define CCP_u8DataArrayE7_Byte1			NO_USE//FP_u8GetValue(FP_nu8Valid)
#define CCP_u8DataArrayE7_Byte2			NO_USE//FP_u8GetValue(FP_nu8SwVersion)
#define CCP_u8DataArrayE7_Byte3			NO_USE//CCP_u8GetLowByte(FP_u16GetValue(FP_nu16atcTFogFlg))
#define CCP_u8DataArrayE7_Byte4			NO_USE//CCP_u8GetHighByte(FP_u16GetValue(FP_nu16atcTFogFlg))
#define CCP_u8DataArrayE7_Byte5			NO_USE//CCP_u8GetLowByte(FP_u16GetValue(FP_nu16atcPSteamSat))
#define CCP_u8DataArrayE7_Byte6			NO_USE//CCP_u8GetHighByte(FP_u16GetValue(FP_nu16atcPSteamSat))
#define CCP_u8DataArrayE7_Byte7			NO_USE

#define CCP_u8DataArrayE8_Byte1			NO_USE//CCP_u8GetLowByte(FP_u16GetValue(FP_nu16ErrorCode1))
#define CCP_u8DataArrayE8_Byte2			NO_USE//CCP_u8GetHighByte(FP_u16GetValue(FP_nu16ErrorCode1))
#define CCP_u8DataArrayE8_Byte3			NO_USE//CCP_u8GetLowByte(FP_u16GetValue(FP_nu16ErrorCode2))
#define CCP_u8DataArrayE8_Byte4			NO_USE//CCP_u8GetHighByte(FP_u16GetValue(FP_nu16ErrorCode2))
#define CCP_u8DataArrayE8_Byte5			NO_USE//NO_USE//CCP_u8GetLowByte(FP_u16GetValue(FP_nu16atcTDewPointOffset))
#define CCP_u8DataArrayE8_Byte6			NO_USE//CCP_u8GetHighByte(FP_u16GetValue(FP_nu16atcTDewPointOffset))
#define CCP_u8DataArrayE8_Byte7			NO_USE

#define CCP_u8DataArrayE9_Byte1			NO_USE//CCP_u8GetLowByte(FP_u16GetValue(FP_nu16atcPSteam))
#define CCP_u8DataArrayE9_Byte2			NO_USE//CCP_u8GetHighByte(FP_u16GetValue(FP_nu16atcPSteam))
#define CCP_u8DataArrayE9_Byte3			NO_USE//CCP_u8GetLowByte(FP_u16GetValue(FP_nu16atcTDewPoint))
#define CCP_u8DataArrayE9_Byte4			NO_USE//CCP_u8GetHighByte(FP_u16GetValue(FP_nu16atcTDewPoint))
#define CCP_u8DataArrayE9_Byte5			NO_USE//CCP_u8GetLowByte(FP_u16GetValue(FP_nu16atcTDewPointOffsetCnstA))
#define CCP_u8DataArrayE9_Byte6			NO_USE//CCP_u8GetHighByte(FP_u16GetValue(FP_nu16atcTDewPointOffsetCnstA))
#define CCP_u8DataArrayE9_Byte7			NO_USE

#define CCP_u8DataArrayEA_Byte1		NO_USE//CCP_u8GetLowByte(FP_u16GetValue(FP_nuatcTDewOffsetA1))
#define CCP_u8DataArrayEA_Byte2		NO_USE//CCP_u8GetHighByte(FP_u16GetValue(FP_nuatcTDewOffsetA1))
#define CCP_u8DataArrayEA_Byte3		NO_USE//CCP_u8GetLowByte(FP_u16GetValue(FP_nuatcTDewOffsetA2))
#define CCP_u8DataArrayEA_Byte4		NO_USE//CCP_u8GetHighByte(FP_u16GetValue(FP_nuatcTDewOffsetA2))
#define CCP_u8DataArrayEA_Byte5		NO_USE//CCP_u8GetLowByte(FP_u16GetValue(FP_nuatcTDewOffsetA3))
#define CCP_u8DataArrayEA_Byte6		NO_USE//CCP_u8GetHighByte(FP_u16GetValue(FP_nuatcTDewOffsetA3))
#define CCP_u8DataArrayEA_Byte7		NO_USE

#define CCP_u8DataArrayEB_Byte1		NO_USE
#define CCP_u8DataArrayEB_Byte2		NO_USE
#define CCP_u8DataArrayEB_Byte3		NO_USE
#define CCP_u8DataArrayEB_Byte4		NO_USE
#define CCP_u8DataArrayEB_Byte5		NO_USE
#define CCP_u8DataArrayEB_Byte6		NO_USE
#define CCP_u8DataArrayEB_Byte7		NO_USE

#define CCP_u8DataArrayEC_Byte1     ((uint8)IPL_u16GetValidState(IPL_nu16PcbTemp))
#define CCP_u8DataArrayEC_Byte2     CCP_u8GetLowByte(IPL_u16GetValue(IPL_nu16PcbTemp))
#define CCP_u8DataArrayEC_Byte3     CCP_u8GetHighByte(IPL_u16GetValue(IPL_nu16PcbTemp))
#define CCP_u8DataArrayEC_Byte4     ((uint8)IPL_u16GetValidState(IPL_nu16Hct))
#define CCP_u8DataArrayEC_Byte5     CCP_u8GetLowByte(IPL_u16GetValue(IPL_nu16Hct))
#define CCP_u8DataArrayEC_Byte6     CCP_u8GetHighByte(IPL_u16GetValue(IPL_nu16Hct))
#define CCP_u8DataArrayEC_Byte7     NO_USE

#define CCP_u8DataArrayED_Byte1     ((uint8)IPL_u16GetValidState(IPL_nu16EvapTemp))
#define CCP_u8DataArrayED_Byte2     CCP_u8GetLowByte(IPL_u16GetValue(IPL_nu16EvapTemp))
#define CCP_u8DataArrayED_Byte3     CCP_u8GetHighByte(IPL_u16GetValue(IPL_nu16EvapTemp))
#define CCP_u8DataArrayED_Byte4     ((uint8)IPL_u16GetValidState(IPL_nu16BlowSpd))
#define CCP_u8DataArrayED_Byte5     CCP_u8GetLowByte(IPL_u16GetValue(IPL_nu16BlowSpd))
#define CCP_u8DataArrayED_Byte6     CCP_u8GetHighByte(IPL_u16GetValue(IPL_nu16BlowSpd))
#define CCP_u8DataArrayED_Byte7     VICT_boGetActiveFlag()

#define CCP_u8DataArrayEE_Byte1     ((uint8)IPL_u16GetValidState(IPL_nu16BlowTempL))
#define CCP_u8DataArrayEE_Byte2     CCP_u8GetLowByte(IPL_u16GetValue(IPL_nu16BlowTempL))
#define CCP_u8DataArrayEE_Byte3     CCP_u8GetHighByte(IPL_u16GetValue(IPL_nu16BlowTempL))
#define CCP_u8DataArrayEE_Byte4     ((uint8)TBTS_u16GetValidState(TBTS_nu16TgtBlowTempL))
#define CCP_u8DataArrayEE_Byte5     CCP_u8GetLowByte(TBTS_u16GetValue(TBTS_nu16TgtBlowTempL))
#define CCP_u8DataArrayEE_Byte6     CCP_u8GetHighByte(TBTS_u16GetValue(TBTS_nu16TgtBlowTempL))
#define CCP_u8DataArrayEE_Byte7     NO_USE

#define CCP_u8DataArrayEF_Byte1     ((uint8)IPL_u16GetValidState(IPL_nu16BlowTempR))
#define CCP_u8DataArrayEF_Byte2     CCP_u8GetLowByte(IPL_u16GetValue(IPL_nu16BlowTempR))
#define CCP_u8DataArrayEF_Byte3     CCP_u8GetHighByte(IPL_u16GetValue(IPL_nu16BlowTempR))
#define CCP_u8DataArrayEF_Byte4     ((uint8)TBTS_u16GetValidState(TBTS_nu16TgtBlowTempR))
#define CCP_u8DataArrayEF_Byte5     CCP_u8GetLowByte(TBTS_u16GetValue(TBTS_nu16TgtBlowTempR))
#define CCP_u8DataArrayEF_Byte6     CCP_u8GetHighByte(TBTS_u16GetValue(TBTS_nu16TgtBlowTempR))
#define CCP_u8DataArrayEF_Byte7     NO_USE

#define CCP_u8DataArrayF0_Byte1     ((uint8)VICT_u16GetValidState(VICT_nu16HeadZoneTempL))
#define CCP_u8DataArrayF0_Byte2     CCP_u8GetLowByte(VICT_u16GetValue(VICT_nu16HeadZoneTempL))
#define CCP_u8DataArrayF0_Byte3     CCP_u8GetHighByte(VICT_u16GetValue(VICT_nu16HeadZoneTempL))
#define CCP_u8DataArrayF0_Byte4     ((uint8)VICT_u16GetValidState(VICT_nu16HeadZoneTempR))
#define CCP_u8DataArrayF0_Byte5     CCP_u8GetLowByte(VICT_u16GetValue(VICT_nu16HeadZoneTempR))
#define CCP_u8DataArrayF0_Byte6     CCP_u8GetHighByte(VICT_u16GetValue(VICT_nu16HeadZoneTempR))
#define CCP_u8DataArrayF0_Byte7     NO_USE

#define CCP_u8DataArrayF1_Byte1     ((uint8)VICT_u16GetValidState(VICT_nu16CabinTemp))
#define CCP_u8DataArrayF1_Byte2     CCP_u8GetLowByte(VICT_u16GetValue(VICT_nu16CabinTemp))
#define CCP_u8DataArrayF1_Byte3     CCP_u8GetHighByte(VICT_u16GetValue(VICT_nu16CabinTemp))
#define CCP_u8DataArrayF1_Byte4     ((uint8)VICT_u16GetValidState(VICT_nu16BodyShellTemp))
#define CCP_u8DataArrayF1_Byte5     CCP_u8GetLowByte(VICT_u16GetValue(VICT_nu16BodyShellTemp))
#define CCP_u8DataArrayF1_Byte6     CCP_u8GetHighByte(VICT_u16GetValue(VICT_nu16BodyShellTemp))
#define CCP_u8DataArrayF1_Byte7     NO_USE

#define CCP_u8DataArrayF2_Byte1     ((uint8)IPL_u16GetValidState(IPL_nu16Sun))
#define CCP_u8DataArrayF2_Byte2     CCP_u8GetLowByte(IPL_u16GetValue(IPL_nu16Sun))
#define CCP_u8DataArrayF2_Byte3     CCP_u8GetHighByte(IPL_u16GetValue(IPL_nu16Sun))
#define CCP_u8DataArrayF2_Byte4     ((uint8)IPL_u8GetValidState(IPL_nu8AirdMode))
#define CCP_u8DataArrayF2_Byte5     IPL_u8GetValue(IPL_nu8AirdMode)
#define CCP_u8DataArrayF2_Byte6     CCP_u8GetLowByte(VICT_u16GetValue(VICT_nu16IncomingHeat))
#define CCP_u8DataArrayF2_Byte7     CCP_u8GetHighByte(VICT_u16GetValue(VICT_nu16IncomingHeat))

#define CCP_u8DataArrayF3_Byte1     ((uint8)IPL_u16GetValidState(IPL_nu16SensorIct))
#define CCP_u8DataArrayF3_Byte2     CCP_u8GetLowByte(IPL_u16GetValue(IPL_nu16SensorIct))
#define CCP_u8DataArrayF3_Byte3     CCP_u8GetHighByte(IPL_u16GetValue(IPL_nu16SensorIct))
#define CCP_u8DataArrayF3_Byte4     CCP_u8GetLowByte(IPL_u16GetValue(IPL_nu16SunLoadHeat))
#define CCP_u8DataArrayF3_Byte5     CCP_u8GetHighByte(IPL_u16GetValue(IPL_nu16SunLoadHeat))
#define CCP_u8DataArrayF3_Byte6     CCP_u8GetLowByte(IPL_u16GetValue(IPL_nu16VelEngineHeat))
#define CCP_u8DataArrayF3_Byte7     CCP_u8GetHighByte(IPL_u16GetValue(IPL_nu16VelEngineHeat))

#define CCP_u8DataArrayF4_Byte1		NO_USE//LINAPP_u16GetValue(LIN_nu16L_WV1_AC_RunState)
#define CCP_u8DataArrayF4_Byte2		NO_USE//LINAPP_u16GetValue(LIN_nu16L_WV1_AC_Position)
#define CCP_u8DataArrayF4_Byte3		NO_USE//LINAPP_u16GetValue(LIN_nu16L_WV1_AC_SpeedLevel)
#define CCP_u8DataArrayF4_Byte4		NO_USE
#define CCP_u8DataArrayF4_Byte5		NO_USE
#define CCP_u8DataArrayF4_Byte6		NO_USE
#define CCP_u8DataArrayF4_Byte7		NO_USE

#define CCP_u8DataArrayF5_Byte1		NO_USE//LINAPP_u16GetValue(LIN_nu16L_WV3_AC_RunState)
#define CCP_u8DataArrayF5_Byte2		NO_USE//LINAPP_u16GetValue(LIN_nu16L_WV3_AC_Position)
#define CCP_u8DataArrayF5_Byte3		NO_USE//LINAPP_u16GetValue(LIN_nu16L_WV3_AC_SpeedLevel)
#define CCP_u8DataArrayF5_Byte4		NO_USE
#define CCP_u8DataArrayF5_Byte5		NO_USE
#define CCP_u8DataArrayF5_Byte6		NO_USE
#define CCP_u8DataArrayF5_Byte7		NO_USE

#define CCP_u8DataArrayF6_Byte1		NO_USE//LINAPP_u16GetValue(LIN_nu16L_ACCM_CompElecCurrV)
#define CCP_u8DataArrayF6_Byte2		NO_USE//LINAPP_u16GetValue(LIN_nu16L_ACCM_CompStat)
#define CCP_u8DataArrayF6_Byte3		NO_USE//LINAPP_u16GetValue(LIN_nu16L_ACCM_CompElecVoltV)
#define CCP_u8DataArrayF6_Byte4		NO_USE//LINAPP_u16GetValue(LIN_nu16L_ACCM_CompSpdIncrReq)
#define CCP_u8DataArrayF6_Byte5		NO_USE//LINAPP_u16GetValue(LIN_nu16L_ACCM_CompSpdV)
#define CCP_u8DataArrayF6_Byte6		NO_USE//LINAPP_u16GetValue(LIN_nu16L_ACCM_CompElecPwr)
#define CCP_u8DataArrayF6_Byte7		NO_USE//LINAPP_u16GetValue(LIN_nu16L_ACCM_CompSpd)

#define CCP_u8DataArrayF7_Byte1		NO_USE//LINAPP_u16GetValue(LIN_nu16L_ACCM_CompElecCurr)
#define CCP_u8DataArrayF7_Byte2		NO_USE//LINAPP_u16GetValue(LIN_nu16L_ACCM_CompFltStat)
#define CCP_u8DataArrayF7_Byte3		NO_USE//LINAPP_u16GetValue(LIN_nu16L_ACCM_CompIGBTTempV)
#define CCP_u8DataArrayF7_Byte4		NO_USE//LINAPP_u16GetValue(LIN_nu16L_ACCM_CompHVInputV)
#define CCP_u8DataArrayF7_Byte5		NO_USE//LINAPP_u16GetValue(LIN_nu16L_ACCM_CompBoardTempV)
#define CCP_u8DataArrayF7_Byte6		NO_USE//LINAPP_u16GetValue(LIN_nu16L_ACCM_CompBoardTemp)
#define CCP_u8DataArrayF7_Byte7		NO_USE//LINAPP_u16GetValue(LIN_nu16L_ACCM_CompHVInput)

#define CCP_u8DataArrayF8_Byte1		NO_USE//LINAPP_u16GetValue(LIN_nu16L_ACCM_CompIGBTTemp)
#define CCP_u8DataArrayF8_Byte2		NO_USE//LINAPP_u16GetValue(LIN_nu16L_ACCM_HVoltCircuitFault)
#define CCP_u8DataArrayF8_Byte3		NO_USE//LINAPP_u16GetValue(LIN_nu16L_ACCM_InCurrCircuitFault)
#define CCP_u8DataArrayF8_Byte4		NO_USE//LINAPP_u16GetValue(LIN_nu16L_ACCM_MotorCurrCircuitFault)
#define CCP_u8DataArrayF8_Byte5		NO_USE//LINAPP_u16GetValue(LIN_nu16L_ACCM_CircuitBoardTempSensorFault)
#define CCP_u8DataArrayF8_Byte6		NO_USE//LINAPP_u16GetValue(LIN_nu16L_ACCM_IGBTTempSensorFault)
#define CCP_u8DataArrayF8_Byte7		NO_USE//LINAPP_u16GetValue(LIN_nu16L_ACCM_MotorDriveCircuitFault)

#define CCP_u8DataArrayF9_Byte1		NO_USE       //CCP_u8GetLowByte(Force_u16GetValue(Force_nu16RawAd))
#define CCP_u8DataArrayF9_Byte2		NO_USE       //CCP_u8GetHighByte(Force_u16GetValue(Force_nu16RawAd))
#define CCP_u8DataArrayF9_Byte3		CCP_u8GetLowByte(Force_u16GetValue(Force_nu16RefAd))
#define CCP_u8DataArrayF9_Byte4		CCP_u8GetHighByte(Force_u16GetValue(Force_nu16RefAd))
#define CCP_u8DataArrayF9_Byte5		NO_USE//LINAPP_u16GetValue(LIN_nu16L_ACCM_HVoltStat)
#define CCP_u8DataArrayF9_Byte6		NO_USE//LINAPP_u16GetValue(LIN_nu16L_ACCM_In15VoltStat)
#define CCP_u8DataArrayF9_Byte7		NO_USE//LINAPP_u16GetValue(LIN_nu16L_ACCM_MotorCurrOverCurrStat)

#define CCP_u8DataArrayFA_Byte1	TOUCHKEY_u8GetIicValue_R(0)
#define CCP_u8DataArrayFA_Byte2	TOUCHKEY_u8GetIicValue_R(1)
#define CCP_u8DataArrayFA_Byte3	TOUCHKEY_u8GetIicValue_R(2)
#define CCP_u8DataArrayFA_Byte4	TOUCHKEY_u8GetIicValue_R(3)
#define CCP_u8DataArrayFA_Byte5	TOUCHKEY_u8GetIicValue_R(4)
#define CCP_u8DataArrayFA_Byte6	TOUCHKEY_u8GetIicValue_R(5)
#define CCP_u8DataArrayFA_Byte7	TOUCHKEY_u8GetIicValue_R(6)

#define CCP_u8DataArrayFB_Byte1		TOUCHKEY_u8GetIicValue_R(7)
#define CCP_u8DataArrayFB_Byte2		TOUCHKEY_u8GetIicValue_R(8)
#define CCP_u8DataArrayFB_Byte3		TOUCHKEY_u8GetIicValue_R(9)
#define CCP_u8DataArrayFB_Byte4		TOUCHKEY_u8GetIicValue_R(10)
#define CCP_u8DataArrayFB_Byte5		TOUCHKEY_u8GetIicValue_R(11)
#define CCP_u8DataArrayFB_Byte6		TOUCHKEY_u8GetIicValue_R(12)
#define CCP_u8DataArrayFB_Byte7		TOUCHKEY_u8GetIicValue_R(13)

#define CCP_u8DataArrayFC_Byte1		TOUCHKEY_u8GetIicValue_R(14)
#define CCP_u8DataArrayFC_Byte2		TOUCHKEY_u8GetIicValue_R(15)
#define CCP_u8DataArrayFC_Byte3		TOUCHKEY_u8GetIicValue_R(16)
#define CCP_u8DataArrayFC_Byte4		TOUCHKEY_u8GetIicValue_R(17)
#define CCP_u8DataArrayFC_Byte5		TOUCHKEY_u8GetIicValue_R(18)
#define CCP_u8DataArrayFC_Byte6		TOUCHKEY_u8GetIicValue_R(19)
#define CCP_u8DataArrayFC_Byte7		TOUCHKEY_u8GetIicValue_R(20)

/**********************************************
add by wuyijun
date 2019 5 24
user CCP_u8DataArrayFC_Byte6
***********************************************/

#define CCP_u8DataArrayFD_Byte1		TOUCHKEY_u8GetIicValue_R(21)
#define CCP_u8DataArrayFD_Byte2		TOUCHKEY_u8GetIicValue_R(22)          //TOUCHKEY_u16GetValue(22)
#define CCP_u8DataArrayFD_Byte3		TOUCHKEY_u8GetIicValue_R(23) 
#define CCP_u8DataArrayFD_Byte4		TOUCHKEY_u8GetIicValue_R(24) 	    //TOUCHKEY_u32GetValue(24)
#define CCP_u8DataArrayFD_Byte5		TOUCHKEY_u8GetIicValue_R(25) 
#define CCP_u8DataArrayFD_Byte6		TOUCHKEY_u8GetIicValue_R(26)
#define CCP_u8DataArrayFD_Byte7		TOUCHKEY_u8GetIicValue_R(27) 

#define CCP_u8DataArrayFE_Byte1		TOUCHKEY_u8GetIicValue_R(28)   //Button_u8key() 
#define CCP_u8DataArrayFE_Byte2		NO_USE
#define CCP_u8DataArrayFE_Byte3		NO_USE    //CCP_u8GetLowByte(uint8 Button_u8key(void))
#define CCP_u8DataArrayFE_Byte4		NO_USE//CCP_u8GetHighByte(DCM_u16GetValue(DCM_nu16ForcePress))
#define CCP_u8DataArrayFE_Byte5		NO_USE//DCM_u8GetValue(DCM_nu8MotorDriver)
#define CCP_u8DataArrayFE_Byte6		NO_USE
#define CCP_u8DataArrayFE_Byte7		NO_USE

//#define CCP_WriteSysForceData(Value)    (Ign_u8ForceIoControl_Write(Value))/*NO_USE*/
#define CCP_WriteSysForceData(Value)    (SYS_u8ForceIoControl_Write(Value))/*NO_USE*/
#define CCP_WriteKnobForceData(Value)   (KNOB_vCcpControl_Write(Value))/*NO_USE*/
#define CCP_WriteDcmForceData(Value)    (NCV77x9_u8ForceIoControl_Write(Value))//(DCM_u8ForceIoControl_Write(Value))
#define CCP_WriteLcdForceData(Value)    0//(LCD_u8ForceIoControl_Write(Value))/*NO_USE*/
#define CCP_WriteDimForceData(Value)    (DIM_u8ForceIoControl_Write(Value))/*NO_USE*///DIM_u8ForceIoControl_Write(Value)//DIM_u8ForceIoControl_Write(Value)
#define CCP_WriteBctlForceData(Value)   (BCTL_u8ForceIoControl_Write(Value))/*NO_USE*///BCTL_u8ForceIoControl_Write(Value)
#define CCP_WriteAcccForceData(Value)   (ACCC_u8ForceIoControl_Write(Value))/*NO_USE*///ACCC_u8ForceIoControl_Write(Value)
#define CCP_WritePowForceData(Value)    (POW_u8ForceIoControl_Write(Value))
#define CCP_WriteRdcForceData(Value)    (RDC_u8ForceIoControl_Write(Value))/*NO_USE*///RDC_u8ForceIoControl_Write(Value)
#define CCP_WriteMmiForceData(Value)    (MMI_u8ForceIoControl_Write(Value))/*NO_USE*///MMI_u8ForceIoControl_Write(Value)  
#define CCP_WriteAirdForceData(Value)   (AIRD_u8ForceIoControl_Write(Value))/*NO_USE*///AIRD_u8ForceIoControl_Write(Value)
#define CCP_WriteMacForceData(Value)    (MAC_u8ForceIoControl_Write(Value))/*NO_USE*///MAC_u8ForceIoControl_Write(Value)
#define CCP_WriteAqsForceData(Value)    (AQS_u8ForceIoControl_Write(Value))
#define CCP_WriteIonForceData(Value)    (ION_u8ForceIoControl_Write(Value))
#define CCP_WriteKeyForceData(Value)    (KEY_u8ForceIoControl_Write(Value))


#define CCP_WriteDtcForceData(Value)    (DTC_u8ForceIoControl_Write(Value)) 
#define CCP_WriteShcForceData(Value)    (SHC_u8ForceIoControl_Write(Value))/*NO_USE*/

#define CCP_DTCChecking            1//DTC_u8ClearChecking             


/*****************************************************************************
 AUTHOR:		: Lin Tao											  *
 DATE: 		   : 2016/8/23											  *                                         
 Description   : PTS Read Analogue Part 						     *                                                     
*****************************************************************************/
/*Group1-8bitAD*/
#define CCP_GetBatteryAD                (CCP_u16GetAdValue(13)>>2u)   
#define CCP_GetMixAirDrFbAD             (CCP_u16GetAdValue(11U)>>2u)
#define CCP_GetMixAirPsFbAD             (CCP_u16GetAdValue(15U)>>2u)
#define CCP_GetAirdFbAD                 (CCP_u16GetAdValue(10U)>>2u)
#define CCP_GetRfaFbAD                  (CCP_u16GetAdValue(4U)>>2u)
/*Group2-8bitAD*/
#define CCP_GetEvapSensorAd             (CCP_u16GetAdValue(6U)>>2u)
#define CCP_GetSolarSensorDrAd          (CCP_u16GetAdValue(7U)>>2u)
#define CCP_GetSolarSensorPsAd          (CCP_u16GetAdValue(8U)>>2u)
#define CCP_GetOatTempSensorAd          (CCP_u16GetAdValue(9U)>>2u)    
#define CCP_GetIctTempSensorAd          (CCP_u16GetAdValue(3U)>>2u)
/*Group3-8bitAD*/
#define CCP_GetHctTempSensorAd          NO_USE
#define CCP_GetAQSSensorAd              NO_USE//(AQS_u16GetValue(AQS_nu16SensorAdValue)>>2u)//(HAL_u16AdcGet(5U)>>2u)
#define CCP_GetPressureSensorAd         NO_USE//(PSV_u16GetValue(PSV_nu16AdValue)>>2u)//(HAL_u16AdcGet(5U)>>2u)
#define CCP_GetIG1FbAd                  NO_USE//(HAL_u16AdcGet(4U)>>2u)
#define CCP_GetIG2FbAd                  NO_USE
/*Group4-8bitAD*/
#define CCP_GetBlowerFbAd               (BCTLDRV_u16GetValue(BCTLDRV_nu16VoltFeedbackRaw)>>2u)
#define CCP_Get5VFbAd                   (CCP_u16GetAdValue(12U)>>2u)
#define CCP_GetRearDefFbAd              (CCP_u16GetAdValue(17U)>>2u)
#define CCP_GetSeatHeatDrFbAd           (CCP_u16GetAdValue(0U)>>2u)
#define CCP_GetSeatHeatPsFbAd           (CCP_u16GetAdValue(1U)>>2u)
/*Group5-8bitAD*/
#define CCP_GetDimmingDetAd             NO_USE
#define CCP_GetFaceBlwSensorDrAd        NO_USE
#define CCP_GetFaceBlwSensorPsAd        NO_USE
#define CCP_GetFootBlwSensorDrAd        NO_USE
#define CCP_GetFootBlwSensorPsAd        NO_USE
/*Group6-8bitAD*/
#define CCP_GetNATSFaceTempSensorAd     NO_USE//(CCP_u16GetAdValue(3U)>>2u)
#define CCP_GetNATSPCBTempSensorAd      (CCP_u16GetAdValue(14U)>>2u)
#define CCP_GetNATSIRTempSensorAd       NO_USE//(CCP_u16GetAdValue(5U)>>2u)
#define CCP_GetUserDefine1              NO_USE
#define CCP_GetUserDefine2              NO_USE
/*Group7-8bitAD*/
#define CCP_GetIonDiagnosis             (CCP_u16GetAdValue(16U)>>2u)
#define CCP_GetUserDefine4              NO_USE//(KEY_u16GetValue(KEY_nu16RawKeyAd2)>>2u)/*for KC-2, is the AD KeyIn2*/
#define CCP_GetUserDefine5              NO_USE//(KEY_u16GetValue(KEY_nu16RawKeyAd3)>>2u)/*for KC-2, is the AD KeyIn3*/
#define CCP_GetUserDefine6              NO_USE
#define CCP_GetUserDefine7              NO_USE
/*Group8-8bitAD*/
#define CCP_GetUserDefine8              NO_USE/*for KC-2 HB, Chiller Coolant Pump*/
#define CCP_GetUserDefine9              NO_USE/*for KC-2 HB, Motor Cooling Pump*/
#define CCP_GetUserDefine10             NO_USE/*for KC-2 HB, Heating Pump*/
#define CCP_GetUserDefine11             NO_USE
#define CCP_GetUserDefine12             NO_USE
/*****************************************************************************
 AUTHOR:		: Lin Tao											  *
 DATE: 		   : 2016/8/23											  *                                         
 Description   : PTS Read  digital port  						     *                                                     
*****************************************************************************/
#define CCP_GetDigtalPort0              NO_USE /*RearDefFbPort*/
#define CCP_GetDigtalPort1              NO_USE /*IStopFbPort*/
#define CCP_GetDigtalPort2              NO_USE /*BlowerRelayPort */
#define CCP_GetDigtalPort3              NO_USE /*BacklightSignalPort */
#define CCP_GetDigtalPort4              NO_USE
#define CCP_GetDigtalPort5              NO_USE
#define CCP_GetDigtalPort6              NO_USE
#define CCP_GetDigtalPort7              NO_USE
#define CCP_GetDigtalPort8              NO_USE
#define CCP_GetDigtalPort9              NO_USE
#define CCP_GetDigtalPort10             NO_USE
#define CCP_GetDigtalPort11             NO_USE
#define CCP_GetDigtalPort12             NO_USE
#define CCP_GetDigtalPort13             NO_USE
#define CCP_GetDigtalPort14             NO_USE
#define CCP_GetDigtalPort15             NO_USE

/*****************************************************************************
 AUTHOR:		: Lin Tao											  *
 DATE: 		   : 2016/8/23											  *                                         
 Description   : PTS Read  PWM 					     *                                                     
*****************************************************************************/
#define CCP_GetOatTmpInputPWM           NO_USE
#define CCP_GetOatTmpInputFreq          NO_USE
#define CCP_GetAccInputPWM              NO_USE
#define CCP_GetAccInputFreq             NO_USE
#define CCP_GetPTCInputPWM              NO_USE
#define CCP_GetPTCInputFreq             NO_USE
#define CCP_GetPressureInputPWM         NO_USE
#define CCP_GetPressureInputFreq        NO_USE
#define CCP_GetDimInputPWM              (DIM_u16GetValue(DIM_nu16InputPwmDuty)/10)
#define CCP_GetDimInputFreq             NO_USE
#define CCP_GetHCTInputPWM              NO_USE
#define CCP_GetHCTInputFreq             NO_USE
#define CCP_GetVelInputPWM              NO_USE
#define CCP_GetVelInputFreq             NO_USE
#define CCP_GetAqsInputPWM              (AQS_u16GetValue(AQS_nu16PwmValue))

/*****************************************************************************
 AUTHOR:		: Lin Tao											  *
 DATE: 		   : 2016/8/23											  *                                         
 Description   : PTS NAT System Test                                                 
*****************************************************************************/
#define CCP_GetNATSSurfaceTemp       (CCP_u16GetAdValue(3U)>>2u)
#define CCP_GetNATSPcbTemp           (CCP_u16GetAdValue(14U)>>2u)   
#define CCP_GetNATSAbsTemp           ABS((CCP_u16GetAdValue(3U)>>2u) - (CCP_u16GetAdValue(14U)>>2u))
#define CCP_GetNATValue              (NAT_u16GetValue(NAT_nu16Value))
/*****************************************************************************
 AUTHOR:		: Lin Tao											  *
 DATE: 		   : 2016/8/23											  *                                         
 Description   : PTS Read Key status and Knob                                                
*****************************************************************************/
#define CCP_GetKeyValue1           KEY_u16PressedKeyForPts()               
#define CCP_GetKeyValue2           NO_USE//KEY_u16GetValue(KEY_nu16PressedKey1)

#define CCP_GetKnob1ValueCW        KNOB_u8GetvalueForPts(Knob_enTempLPlusCounter)   
#define CCP_GetKnob1ValueCCW       KNOB_u8GetvalueForPts(Knob_enTempLMinusCounter)   
#define CCP_GetKnob2ValueCW        KNOB_u8GetvalueForPts(Knob_enTempRPlusCounter)   
#define CCP_GetKnob2ValueCCW       KNOB_u8GetvalueForPts(Knob_enTempRMinusCounter) 
#define CCP_GetKnob3ValueCW        NO_USE  
#define CCP_GetKnob3ValueCCW       NO_USE 

/*PTS define*/
#define CCP_HWVER_INTERNAL        HW_VERSION_INTERNAL
#define CCP_SWVER_INTERNAL        SW_VERSION_INTERNAL
#define CCP_SWVER_DATE            SW_VERSION_DATE  


/*****************************************************************************
 AUTHOR:		: Lin Tao											  *
 DATE: 		   : 2016/8/23											  *                                         
 Description   : PTS Product Information 						     *                                                     
*****************************************************************************/


#ifdef WriteLogDataUseDiretAddr

#define CCP_nu8SerialNumAddr      0xFF207480u
#define CCP_nu8SerialLen          0x10u
#define CCP_nu8FactoryNumAddr     0xFF207480u
#define CCP_nu8FactoryNumLen      0x10u
#define CCP_nu8DateAddr           0xFF207480u
#define CCP_nu8DateLen            0x10u
#define CCP_nu8ProductLineAddr    0xFF207480u
#define CCP_nu8ProductLineLen     0x10u
#define CCP_nu8SerialNumDayAddr   0xFF207480u
#define CCP_nu8SerialNumDayLen    0x10u
#define CCP_nu8InterHWVerAddr     0xFF207480u
#define CCP_nu8InterHWVerLen      0x10u
#define CCP_nu8ExterHWVerAddr     0xFF207480u
#define CCP_nu8ExterHWVerLen      0x10u

#else

#define CCP_nu8SerialNumBuffer      Diag_au8Group1ECUSerialNumber
#define CCP_nu8SerialLen            Diag_nECUSerialNumber_Len

#define CCP_nu8FactoryBuffer      

#define CCP_nu8DateBuffer           Diag_au8Group1ECUManufacturingDate
#define CCP_nu8DateLen              Diag_nECUManufacturingDate_Len

#define CCP_nu8ProductLineBuffer    
#define CCP_nu8SerialNumDayBuffer  

#define CCP_nu8InterHWVerBuffer     Diag_au8Group1HardWareVersion
#define CCP_nu8InterHWVerLen        Diag_nHardWareVersion_Len
#define CCP_nu8InterHWVerAddr       (0xFF207100UL) /*For Geely, APP and Bootloader use the common addr*/


#define CCP_nu8ExterHWVerBuffer     

#define CCP_LogicDataID                            EED_nu8GroupDIAG//EED_nu8GroupDTC,modify 20161121
#define CCP_WriteLogicDataGroup(ID,Buffer,Len)     EED_u8WriteGroupData(ID,Buffer,Len)
#define CCP_ReadLogicDataGroup(ID,Buffer,Len)      EED_u8ReadGroupData(ID,Buffer,Len)


#endif


#define CcpCaliDataFlashStart          (SECTOR_SA1_Start) 
#define CcpPTSResDelayForDTC           (50u)
#define CcpGetEEPPTSStartAddr          (0x03C0)/**Relative address**/
#define CcpGetEEPPTSMaxSize            (0x0040)/**Relative address**/
#define CcpDataFlashUse                
#define CcpPTSDataFalshStart           (SECTOR_SA16_Start) /*160829*/

#define CcpGetEEPSelfTestAddr          (SECTOR_SA15_End-63U)
#define CcpPTSEEPSelfTestData          (0x99U)

#define CCP_ReadEEPData(Addr,Buffer,Len)           EED_u8ReadDataWait(Addr,Buffer,Len)
#define CCP_WriteEEPData(Addr,Buffer,Len)          EED_u8WriteDataWait(Addr,Buffer,Len)



#endif
