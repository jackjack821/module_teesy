/***************************************************************************************************
                                       KEY PROCESS
  .File Name: TouchKey_Type.h
  
  .Description: Thie file is used to define data type.

  --------------------------------------------------------------------------------------------------
  Version     Date            Author            Change

  --------------------------------------------------------------------------------------------------
  Rev 1.0     2017/11/06      Zhong Bin     	The first version            
***************************************************************************************************/
#ifndef TOUCHKEY_TYPE_H
#define TOUCHKEY_TYPE_H
#include "General.h"
/***************************************************************************************************
                                       HEADER FILES 
***************************************************************************************************/

/* System-headerfiles */

/* Foreign headerfiles */

/* Own headerfiles */

#define CAN_Mode	1
#define Manual_Mode		2

#define DemoConfiguration	CAN_Mode

/* the number of variables that will be used by other modules.*/

/*
add by wuyijun
data 2019- 6-10 
function 
*/
 typedef enum
 {
	TOUCHKEY_nCCMode_Button_L_1 = 0,
	TOUCHKEY_nCCMode_Button_L_2,
	TOUCHKEY_nCCMode_Button_L_3,
	TOUCHKEY_nCCMode_Button_L_4,
	TOUCHKEY_nCCMode_Button_L_5,	
	TOUCHKEY_nCCMode_Button_L_6,
	TOUCHKEY_nCCMode_Button_L_7,
	TOUCHKEY_nCCMode_Button_L_8,
	TOUCHKEY_nCCMode_Button_L_9,
	TOUCHKEY_nCCMode_Button_L_10,	
	
	TOUCHKEY_nCCMode_Button_R_1 ,
	TOUCHKEY_nCCMode_Button_R_2,
	TOUCHKEY_nCCMode_Button_R_3,
	TOUCHKEY_nCCMode_Button_R_4,
	TOUCHKEY_nCCMode_Button_R_5,	
	TOUCHKEY_nCCMode_Button_R_6,
	TOUCHKEY_nCCMode_Button_R_7,
	TOUCHKEY_nCCMode_Button_R_8,
	TOUCHKEY_nCCMode_Button_R_9,
	TOUCHKEY_nCCMode_Button_R_10,	

	TOUCHKEY_nu32CCModeMax
 }TOUCHKEY_tenu32CCModeVarNum;

 typedef enum
 {
	TOUCHKEY_nu16IicX_Value = 0,
	TOUCHKEY_nu16IicY_Value,
	TOUCHKEY_nu16Others,
	TOUCHKEY_nu16Max
 }TOUCHKEY_tenu16CCModeVarNum;
 
typedef enum
{
	TOUCHKEY_nRelease = 0,
	TOUCHKEY_nPress,
	TOUCHKEY_nMove
}TOUCHKEY_tenActType;




typedef enum
{	
	TOUCHKEY_nu32MainCCPage = 0,
	TOUCHKEY_nu32MainSeatPage,
	TOUCHKEY_nu32MainBodyPage,
	TOUCHKEY_nu32MainDrivePage,
	TOUCHKEY_nu32MainOutPage,
	TOUCHKEY_nMAINPAGE_Max
}TOUCHKEY_tenMainPageID;


typedef enum
{
	TOUCHKEY_nSeatPAGE_1 = 0,
	TOUCHKEY_nSeatPAGE_2,
	TOUCHKEY_nSeatPAGE_3,
	TOUCHKEY_nSeatPAGE_4,
	TOUCHKEY_nSeatPAGE_5,
	TOUCHKEY_nSeatPAGE_6,
	TOUCHKEY_nSeatPAGE_7,
	TOUCHKEY_nSeatPAGE_8,
	TOUCHKEY_nSeatPAGE_9,
	TOUCHKEY_nSeatPAGE_10,

	TOUCHKEY_nSeatModePAGE_Max
	
}TOUCHKEY_tenSeatModePageID;

typedef enum
{
	TOUCHKEY_nBodyPAGE_1 = 0,
	TOUCHKEY_nBodyPAGE_2,
	TOUCHKEY_nBodyPAGE_3,
	TOUCHKEY_nBodyPAGE_4,
	TOUCHKEY_nBodyPAGE_5,
	TOUCHKEY_nBodyPAGE_6,
	TOUCHKEY_nBodyPAGE_7,
	TOUCHKEY_nBodyPAGE_8,
	TOUCHKEY_nBodyPAGE_9,
	TOUCHKEY_nBodyPAGE_10,
	
	TOUCHKEY_nBodyModePAGE_Max
	
}TOUCHKEY_tenBodyModePageID;

typedef enum
{
	TOUCHKEY_nDrive_PAGE_1 = 0,
	TOUCHKEY_nDrive_PAGE_2,
	TOUCHKEY_nDrive_PAGE_3,
	TOUCHKEY_nDrive_PAGE_4,
	TOUCHKEY_nDrive_PAGE_5,
	TOUCHKEY_nDrive_PAGE_6,
	TOUCHKEY_nDrive_PAGE_7,
	TOUCHKEY_nDrive_PAGE_8,
	
	TOUCHKEY_nDriveModePAGE_Max
}TOUCHKEY_tenDriveModePageID;

typedef enum
{
	TOUCHKEY_nCCMode=0,
	TOUCHKEY_nSeatMode,
	TOUCHKEY_nBodyMode,
	TOUCHKEY_nDriveMode,
	TOUCHKEY_nMaxMode
}TOUCHKEY_tenMenuMode;


typedef enum
{
	TOUCHKEY_nAUTOPAGE_AirFlow = 0,
	TOUCHKEY_nAUTOPAGE_InnerLoop,
	TOUCHKEY_nAUTOPAGE_AutoOn,
	TOUCHKEY_nAUTOPAGE_AutoOff,
	TOUCHKEY_nAUTOPAGE_Blower,
	TOUCHKEY_nAUTOPAGE_TempMove,
	TOUCHKEY_nAUTOPAGE_Back,
	TOUCHKEY_nAUTOPAGE_Max
}TOUCHKEY_tenAutoPageID;

typedef enum
{
	TOUCHKEY_nBLOWERPAGE_AirFlow = 0,
	TOUCHKEY_nBLOWERPAGE_InnerLoop,
	TOUCHKEY_nBLOWERPAGE_Auto,
	TOUCHKEY_nBLOWERPAGE_BlowerLevel5,
	TOUCHKEY_nBLOWERPAGE_BlowerLevel4,
	TOUCHKEY_nBLOWERPAGE_BlowerLevel3,
	TOUCHKEY_nBLOWERPAGE_BlowerLevel2,
	TOUCHKEY_nBLOWERPAGE_BlowerLevel1,
	TOUCHKEY_nBLOWERPAGE_BlowerLevel0,
	TOUCHKEY_nBLOWERPAGE_TempMove,
	TOUCHKEY_nBLOWERPAGE_Back,
	TOUCHKEY_nBLOWERPAGE_Max
}TOUCHKEY_tenBlowerPageID;

typedef enum
{
	TOUCHKEY_nWELCOMEPAGE_OK = 0,
	TOUCHKEY_nWELCOMEPAGE_Next,

	TOUCHKEY_nWELCOMEPAGE_Max
}TOUCHKEY_tenWelcomePageID;

typedef enum
{
	//TOUCHKEY_nTRIED_DRIVEPAGE_OK = 0,
	TOUCHKEY_nTRIED_DRIVEPAGE_Next= 0,
	TOUCHKEY_nTRIED_DRIVEPAGE_Max
}TOUCHKEY_tenTiredDrivePageID;

typedef enum
{
	//TOUCHKEY_nSMOKEPAGE_OK = 0,
	TOUCHKEY_nSMOKEPAGE_Next= 0,
	TOUCHKEY_nSMOKEPAGE_Max
}TOUCHKEY_tenSmokePageID;

typedef enum
{
	//TOUCHKEY_nTEMPLOWPAGE_OK = 0,
	TOUCHKEY_nTEMPLOWPAGE_Next= 0,
	TOUCHKEY_nTEMPLOWPAGE_Max
}TOUCHKEY_tenTempLowPageID;

typedef enum
{
	TOUCHKEY_nMoveNull = 0,
	TOUCHKEY_nMoveUp,
	TOUCHKEY_nMoveDown,
	TOUCHKEY_nMoveLeft,
	TOUCHKEY_nMoveRight
}TOUCHKEY_tenMoveDirection;

typedef struct 
{
	uint8  KeyID;
	uint16 x_PosMin;
	uint16 x_PosMax;
	uint16 y_PosMin;
	uint16 y_PosMax;
	TOUCHKEY_tenActType 		enCurrStatus;
	TOUCHKEY_tenActType 		enLastStatus;
	TOUCHKEY_tenActType		enEffectAction;
	uint8                boKeyValid;
}TOUCHKEY_stPageAttribute;
#endif                            
/***************************************************************************************************
                                           END
***************************************************************************************************/
