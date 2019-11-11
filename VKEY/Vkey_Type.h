/***************************************************************************************************
                                       VKEY PROCESS
  .File Name: VKEY_Type.h
  
  .Description: Thie file is used to define data type.

  --------------------------------------------------------------------------------------------------
  Version     Date            Author            Change

  --------------------------------------------------------------------------------------------------
  Rev 1.0     2015/03/26      Xu Xianglin     	The first version            
***************************************************************************************************/
#ifndef VKEY_TYPE_H
#define VKEY_TYPE_H

/***************************************************************************************************
                                       HEADER FILES 
***************************************************************************************************/

/* System-headerfiles */

/* Foreign headerfiles */

/* Own headerfiles */


/* the number of variables that will be used by other modules.*/
 typedef enum
 {
	 VKEY_nu16PressedKey,
	 VKEY_nu16ErrorCode,
	 VKEY_nu16RawKey,
	 VKEY_nu16Max
 }VKEY_tenu16VarNum;

 
typedef enum
{
    VKEY_nu8FLeftSetTemp,
    VKEY_nu8FRightSetTemp,
    //VKEY_nu8AutoKey,
    VKEY_nu8BlowerSpd,
    VKEY_nu8Mode,
	//VKEY_nu8RfaKey,
	//VKEY_nu8AqsKey,
	//VKEY_nu8AcKey,
	//VKEY_nu8OffKey,
	//VKEY_nu8DefKey,
	//VKEY_nu8IonKey,
	VKEY_nu8PM25PopupOerationSts,

    VKEY_nu8DrvHeaReq,
    VKEY_nu8PassHeaReq,

    //VKEY_nu8DualKey,
    //VKEY_nu8PM25Key,
    VKEY_nu8PM25PopupActive,
    VKEY_nu8AirCleanerReq,
    VKEY_nu8TempReq,
    VKEY_nu8AirConditionerReq,
    
    VKEY_nu8SwVersion,
    VKEY_nu8Max
}VKEY_tenu8VarNum;



typedef enum
{
    VKEY_nFLeftSetTemp,
    VKEY_nFRightSetTemp,
    //VKEY_nAutoKey,
    VKEY_nBlowerSpd,
    VKEY_nMode,
	//VKEY_nRfaKey,
	//VKEY_nAqsKey,
	//VKEY_nAcKey,
	//VKEY_nOffKey,
	//VKEY_nDefKey,
	//VKEY_nIonKey,
	VKEY_nPM25PopupOperationSts,

    VKEY_nDrvHeaReq,
    VKEY_nPassHeaReq,

    //VKEY_nDualKey,
    //VKEY_nPM25Key,
    VKEY_nPM25PopupActive,
    VKEY_nAirCleanerReq,
    VKEY_nTempReq,
    VKEY_nAirConditionerReq,

	VKEY_nInvalid
}VKEY_tenID;


typedef struct {
const VKEY_tenID 	enKeyID;
const uint8     	u8MinValidValue;
const uint8     	u8MaxValidValue;
uint8               u8CurrStatus;
uint8               u8LastStatus;
uint8 				u8PressTimer;
const uint8         u8ResponseTime;
uint8               boKeyValib;
const uint8	        u8Group;
const uint8         u8Priority;
const uint8         u8Attr;/*0:key  1:Not key*/
}VKEY_stATTRIBUTE;

typedef enum
{
	VKey_nSetKeyPress,
	VKey_nCcpForceMax
}CcpControl_VKEY;


typedef struct
{
	uint8 CcpCommandFlag;
	uint8 CcpCommand;
	uint16 CcpContronData;
}VKEY_tstCcpControlInput;
#endif                            
/***************************************************************************************************
                                           END
***************************************************************************************************/
