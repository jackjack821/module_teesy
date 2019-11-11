/*******************************************************************************
| Module Name: KEY capture and debouncing interface
| File Name: KEY_interface.c
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
| Li Jiaye                        Desay SV Automotive Co., Ltd
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date             Ver         Author               Description
| ----------  -------  -------------  ------------------------------------------
| 2016.8.3         0100      Li jiaye         module template update. 
| 
| 
****************************** .FILE_HEADER_END *********************************/


/*****************************************************************************
* FILE DECLARATION
*****************************************************************************/
#define KEY_Interface                          /* Name of the Module                */

/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
*****************************************************************************/
/* System-headerfiles */
#include "General.h"

/* Foreign headerfiles */
#include "Rte_internal.h"
#include "ALG.h"
#include "CanApp.h"

/* Own headerfiles */
#include "KEY_Cfg.h"
#include "KEY_Type.h"
#include "KEY_Private.h"
#include "KEY.h"      
#include "KEY_interface.h"
#include "TouchKey.h"
#include "Force.h"
/*****************************************************************************
* MODULE GLOBAL CONFIGURATION CONSTANTS
*
* In this section define
* - constants to configure your module. These constants are unknown for other
*   modules
*****************************************************************************/
/*Ccp control*/
typedef enum
{
	Key_nSetKeyPress,
    	Key_nGetKeyPress,
	Key_nCcpForceMax
}CcpControl_Key;

static uint16 Key_CcpKeyPress=0;
static uint8 Key_CcpForceFlag=0;
static uint32 Key_CcpControlData[Key_nCcpForceMax];
#define KeyGetCcpForceBit(index)	((Key_CcpForceFlag>>index)&0x01)
#define KeySetCcpForceBit(index)	(Key_CcpForceFlag=Key_CcpForceFlag|(0x01<<index))
#define KeyClrCcpForceBit(index)	(Key_CcpForceFlag=Key_CcpForceFlag&(~(0x01<<index)))
#define KeyClrCcpForceByte(void)	(Key_CcpForceFlag=0)

static uint32 Key_u32PhyKeyPressFlag;
static uint32 Key_u32ForceADValidFlag;
/*****************************************************************************
 Function      : KEY_ForceIoControl_Write                                 
 Description   : Ccp control function
 Takes         : Nothing
 Return Value  : None                                                *
*****************************************************************************/
Std_ReturnType KEY_u8ForceIoControl_Write(/*IN*/uint32 ForceIoControlWord)
{
	tstCcpContronType CcpControlWord;
	CcpControlWord.CcpContronData=(uint16)ForceIoControlWord;
	CcpControlWord.CcpCommand=(uint8)(ForceIoControlWord>>16);
	CcpControlWord.CcpCommandFlag=(uint8)(ForceIoControlWord>>24);
	if(CcpControlWord.CcpCommandFlag==True)
	{
		switch(CcpControlWord.CcpCommand)
		{
			case 0:
				KeyClrCcpForceByte();
				break;
			case 1:
				KeySetCcpForceBit(Key_nSetKeyPress);
				Key_CcpControlData[Key_nSetKeyPress]=CcpControlWord.CcpContronData;
				break;
			case 2:
				KeyClrCcpForceBit(Key_nSetKeyPress);
				Key_CcpControlData[Key_nSetKeyPress]=0;
				break;
            case 0x81:
                KeySetCcpForceBit(Key_nGetKeyPress);
                break;
			default:
				break;
		}
	}
	else
	{
		KeyClrCcpForceByte();
	}
    return 0;
}

/*============================================================================
*Function : void KEY_vClrForceFlagByteAction(void)
*Description : 
*takes : nothing
*return: nothing
*/
void KEY_vClrForceFlagByteAction(void)
{
    KeyClrCcpForceByte();
}
/*============================================================================
*Function : KEY_tenValueSts KEY_vForceKeyPressImport(uint8 IndexInput, uint8 *Output)
*Description : max 32 keys
*takes : nothing
*return: nothing
*/
KEY_tenValueSts KEY_vForceKeyPressImport(uint8 IndexInput, uint8 *Output)
{
    KEY_tenValueSts enReturn=KEY_nInvalid;
    if(KeyGetCcpForceBit(Key_nSetKeyPress)==True)
    {
        *Output=((uint8)(Key_CcpControlData[Key_nSetKeyPress]>>IndexInput)&0x01);
        enReturn=KEY_nValid;
    }
    else
    {
        *Output=0x00;
        enReturn=KEY_nInvalid;
    }
    return enReturn;
    
}

/*============================================================================
*Function : KEY_tenValueSts KEY_vPtsKeyPressImport(uint8 IndexInput, KEY_tenKeyAction 	enKeyCurrStatus;)
*Description : max 32 keys
*takes : nothing
*return: nothing
*/
KEY_tenValueSts KEY_vPtsKeyPressImport(uint8 IndexInput, KEY_tenKeyAction 	enKeyCurrStatus)
{
    KEY_tenValueSts enReturn=KEY_nValid;
    
    if(KeyGetCcpForceBit(Key_nGetKeyPress))
    {
        if(enKeyCurrStatus == 0u)
        {
            Key_CcpKeyPress |= (uint16)(1u << IndexInput);
        }
        else
        {
            Key_CcpKeyPress &= ~((uint16)(1u << IndexInput));
        }
    }
    else
    {
        Key_CcpKeyPress = 0u;
    }
    return enReturn;
    
}
/*============================================================================
*Function : void KEY_vMainExportAction(void)
*Description : Export local calculated value
*takes : nothing
*return: nothing
*/
void KEY_vMainExportAction(void)
{
    KEY_tstMainOut KEY_stMainOut;
    KEY_enGetMainOutputExport(&KEY_stMainOut);
    //Rte_IWrite_Key_vMain_KeyPutKeyPressed_KeyPressed((uint16)KEY_stMainOut.u32ActionTable);
}


/*============================================================================
*Function : uint16 KEY_u16PressedKey(void)
*Description : Export local calculated value
*takes : nothing
*return: nothing
*/
uint16 KEY_u16PressedKey(void)
{
    KEY_tstMainOut KEY_stMainOut;
    KEY_enGetMainOutputExport(&KEY_stMainOut);
    return (uint16)KEY_stMainOut.u32ActionTable;
}

/*============================================================================
*Function : uint32 KEY_u32PressedKey(void)
*Description : Export local calculated value
*takes : nothing
*return: nothing
*/
uint32 KEY_u32PressedKey(void)
{
    KEY_tstMainOut KEY_stMainOut;
    KEY_enGetMainOutputExport(&KEY_stMainOut);
    return (uint32)KEY_stMainOut.u32ActionTable;
}

uint32 KEY_u32KeyStatusIsPress(void)
{
    KEY_tstMainOut KEY_stMainOut;
    KEY_enGetMainOutputExport(&KEY_stMainOut);
    return (uint32)KEY_stMainOut.u32OperationTable;
}

/*============================================================================
*Function : uint16 KEY_u16PressedKeyForPts(void)
*Description : Export local calculated value
*takes : nothing
*return: nothing
*/
uint16 KEY_u16PressedKeyForPts(void)
{
    return Key_CcpKeyPress;
}

/*============================================================================
*Function : KEY_tenValueSts KEY_vKeyShrPressImport(uint16 *value)
*Description : max 32 keys
*takes : nothing
*return: nothing
*/
KEY_tenValueSts KEY_vKey1Import(uint16 *value)
{
    KEY_tenValueSts enReturn=KEY_nValid;
    uint16 u16ReadKeyPinLevel;
	 u16ReadKeyPinLevel=TOUCHKEY_u32GetValue((TOUCHKEY_tenu32CCModeVarNum)(TOUCHKEY_nCCMode_Button_L_1));
	    if( (u16ReadKeyPinLevel == 1u)&&(Key_u32ForceADValidFlag==1))
	    {
		    *value=0u;
	    }
	    else
	    {
	          *value=1u;
	    }
		if(u16ReadKeyPinLevel == 1u)
		{
			Key_u32PhyKeyPressFlag |= 1 <<0u;
		}
	    return enReturn;
}

/*============================================================================
*Function : KEY_tenValueSts KEY_vKeyShlPressImport(uint16 *value)
*Description : max 32 keys
*takes : nothing
*return: nothing
*/
KEY_tenValueSts KEY_vKey2Import(uint16 *value)
{
		KEY_tenValueSts enReturn=KEY_nValid;
		uint16 u16ReadKeyPinLevel;
		u16ReadKeyPinLevel=TOUCHKEY_u32GetValue((TOUCHKEY_tenu32CCModeVarNum)(TOUCHKEY_nCCMode_Button_L_2));
		if( (u16ReadKeyPinLevel == 1u)&&(Key_u32ForceADValidFlag==1))
		{
		    *value=0u;
		}
		else
		{
		      *value=1u;
		}
		if(u16ReadKeyPinLevel == 1u)
		{
			Key_u32PhyKeyPressFlag |= 1 <<1u;
		}
	    return enReturn;
}

/*============================================================================
*Function : KEY_tenValueSts KEY_vKeyOffPressImport(uint16 *value)
*Description : max 32 keys
*takes : nothing
*return: nothing
*/
KEY_tenValueSts KEY_vKey3Import(uint16 *value)
{
   		 KEY_tenValueSts enReturn=KEY_nValid;
		uint16 u16ReadKeyPinLevel;
		u16ReadKeyPinLevel=TOUCHKEY_u32GetValue((TOUCHKEY_tenu32CCModeVarNum)(TOUCHKEY_nCCMode_Button_L_3));
		if( (u16ReadKeyPinLevel == 1u)&&(Key_u32ForceADValidFlag==1))
		{
		    *value=0u;
		}
		else
		{
		      *value=1u;
		}

    if(u16ReadKeyPinLevel == 1u)
    {
        Key_u32PhyKeyPressFlag |= 1 << 2u;
    }
    return enReturn;
}

/*============================================================================
*Function : KEY_tenValueSts KEY_vKeyRecPressImport(uint16 *value)
*Description : max 32 keys
*takes : nothing
*return: nothing
*/
KEY_tenValueSts KEY_vKey4Import(uint16 *value)
{
	    KEY_tenValueSts enReturn=KEY_nValid;
	    uint16 u16ReadKeyPinLevel;

  		u16ReadKeyPinLevel=TOUCHKEY_u32GetValue((TOUCHKEY_tenu32CCModeVarNum)(TOUCHKEY_nCCMode_Button_L_4));
		if( (u16ReadKeyPinLevel == 1u)&&(Key_u32ForceADValidFlag==1))
		{
		    *value=0u;
		}
		else
		{
		      *value=1u;
		}

    if(u16ReadKeyPinLevel == 1u)
    {
        Key_u32PhyKeyPressFlag |= 1 << 3u;
    }
    return enReturn;
}

/*============================================================================
*Function : KEY_tenValueSts KEY_vKeyDefPressImport(uint16 *value)
*Description : max 32 keys
*takes : nothing
*return: nothing
*/
KEY_tenValueSts KEY_vKey5Import(uint16 *value)
{
   	    KEY_tenValueSts enReturn=KEY_nValid;
	    uint16 u16ReadKeyPinLevel;

  		u16ReadKeyPinLevel=TOUCHKEY_u32GetValue((TOUCHKEY_tenu32CCModeVarNum)(TOUCHKEY_nCCMode_Button_L_5));
		if( (u16ReadKeyPinLevel == 1u)&&(Key_u32ForceADValidFlag==1))
		{
		    *value=0u;
		}
		else
		{
		      *value=1u;
		}

    if(u16ReadKeyPinLevel == 1u)
    {
        Key_u32PhyKeyPressFlag |= 1 << 4u;
    }
    return enReturn;
}

/*============================================================================
*Function : KEY_tenValueSts KEY_vKeyRDefPressImport(uint16 *value)
*Description : max 32 keys
*takes : nothing
*return: nothing
*/
KEY_tenValueSts KEY_vKey6Import(uint16 *value)
{
     	    KEY_tenValueSts enReturn=KEY_nValid;
	    uint16 u16ReadKeyPinLevel;

  		u16ReadKeyPinLevel=TOUCHKEY_u32GetValue((TOUCHKEY_tenu32CCModeVarNum)(TOUCHKEY_nCCMode_Button_L_6));
		if( (u16ReadKeyPinLevel == 1u)&&(Key_u32ForceADValidFlag==1))
		{
		    *value=0u;
		}
		else
		{
		      *value=1u;
		}
	if(u16ReadKeyPinLevel == 1u)
    {
        Key_u32PhyKeyPressFlag |= 1 << 5u;
    }
    return enReturn;
}

/*============================================================================
*Function : KEY_tenValueSts KEY_vKeyModePressImport(uint16 *value)
*Description : max 32 keys
*takes : nothing
*return: nothing
*/
KEY_tenValueSts KEY_vKey7Import(uint16 *value)
{
          KEY_tenValueSts enReturn=KEY_nValid;
	    uint16 u16ReadKeyPinLevel;

  		u16ReadKeyPinLevel=TOUCHKEY_u32GetValue((TOUCHKEY_tenu32CCModeVarNum)(TOUCHKEY_nCCMode_Button_L_7));
		if( (u16ReadKeyPinLevel == 1u)&&(Key_u32ForceADValidFlag==1))
		{
		    *value=0u;
		}
		else
		{
		      *value=1u;
		}
	if(u16ReadKeyPinLevel == 1u)
    {
        Key_u32PhyKeyPressFlag |= 1 << 6u;
    }
    return enReturn;
}

/*============================================================================
*Function : KEY_tenValueSts KEY_vKeyFanDecPressImport(uint16 *value)
*Description : max 32 keys
*takes : nothing
*return: nothing
*/
KEY_tenValueSts KEY_vKey8Import(uint16 *value)
{
	KEY_tenValueSts enReturn=KEY_nValid;
	uint16 u16ReadKeyPinLevel;
	u16ReadKeyPinLevel=TOUCHKEY_u32GetValue((TOUCHKEY_tenu32CCModeVarNum)(TOUCHKEY_nCCMode_Button_L_8));
	if( (u16ReadKeyPinLevel == 1u)&&(Key_u32ForceADValidFlag==1))
	{
	    *value=0u;
	}
	else
	{
	      *value=1u;
	}
    if(u16ReadKeyPinLevel == 1u)
    {
        Key_u32PhyKeyPressFlag |= 1 << 7u;
    }
    return enReturn;
}

/*============================================================================
*Function : KEY_tenValueSts KEY_vKeyAutoPressImport(uint16 *value)
*Description : max 32 keys
*takes : nothing
*return: nothing
*/
KEY_tenValueSts KEY_vKey9Import(uint16 *value)
{
	KEY_tenValueSts enReturn=KEY_nValid;
	uint16 u16ReadKeyPinLevel;
	u16ReadKeyPinLevel=TOUCHKEY_u32GetValue((TOUCHKEY_tenu32CCModeVarNum)(TOUCHKEY_nCCMode_Button_L_9));
	if( (u16ReadKeyPinLevel == 1u)&&(Key_u32ForceADValidFlag==1))
	{
	    *value=0u;
	}
	else
	{
	      *value=1u;
	}

    if(u16ReadKeyPinLevel == 1u)
    {
        Key_u32PhyKeyPressFlag |= 1 << 8u;
    }
    return enReturn;
}

/*============================================================================
*Function : KEY_tenValueSts KEY_vKeyAcPressImport(uint16 *value)
*Description : max 32 keys
*takes : nothing
*return: nothing
*/
KEY_tenValueSts KEY_vKeyForce1Import(uint16 *value)
{
    KEY_tenValueSts enReturn=KEY_nValid;
    uint16 u16ReadKeyPinLevel;

    u16ReadKeyPinLevel=ForceSensor_u8GetValue((KEY_tenu8PadVarNum)KEY_nu8Pad1);
    if(u16ReadKeyPinLevel == 1u)
    {
	    *value=0u;
    }
    else
    {
        *value=1u;
    }

    if(u16ReadKeyPinLevel == 1u)
    {
        Key_u32PhyKeyPressFlag |= 1 << 9u;
    }
    return enReturn;
}

/*============================================================================
*Function : KEY_tenValueSts KEY_vKeyIonPressImport(uint16 *value)
*Description : max 32 keys
*takes : nothing
*return: nothing
*/
KEY_tenValueSts KEY_vKeyForce2Import(uint16 *value)
{
    KEY_tenValueSts enReturn=KEY_nValid;
    uint16 u16ReadKeyPinLevel;

    u16ReadKeyPinLevel=ForceSensor_u8GetValue((KEY_tenu8PadVarNum)KEY_nu8Pad2);
    if(u16ReadKeyPinLevel == 1u)
    {
	    *value=0u;
    }
    else
    {
        *value=1u;
    }

    if(u16ReadKeyPinLevel == 1u)
    {
        Key_u32PhyKeyPressFlag |= 1 << 10u;
    }
    return enReturn;
}

/*============================================================================
*Function : KEY_tenValueSts KEY_vKeyFanIncPressImport(uint16 *value)
*Description : max 32 keys
*takes : nothing
*return: nothing
*/
KEY_tenValueSts KEY_vKeyForce3Import(uint16 *value)
{
    KEY_tenValueSts enReturn=KEY_nValid;
    uint16 u16ReadKeyPinLevel;

    u16ReadKeyPinLevel=ForceSensor_u8GetValue((KEY_tenu8PadVarNum)KEY_nu8Pad3);
    if(u16ReadKeyPinLevel == 1u)
    {
	    *value=0u;
    }
    else
    {
        *value=1u;
    }

    if(u16ReadKeyPinLevel == 1u)
    {
        Key_u32PhyKeyPressFlag |= 1 << 11u;
    }
    return enReturn;
}

/*============================================================================
*Function : KEY_tenValueSts KEY_vKeyDualPressImport(uint16 *value)
*Description : max 32 keys
*takes : nothing
*return: nothing
*/
KEY_tenValueSts KEY_vKeyForce4Import(uint16 *value)
{
    KEY_tenValueSts enReturn=KEY_nValid;
    uint16 u16ReadKeyPinLevel;

    u16ReadKeyPinLevel=ForceSensor_u8GetValue((KEY_tenu8PadVarNum)KEY_nu8Pad4);
    if(u16ReadKeyPinLevel == 1u)
    {
	    *value=0u;
    }
    else
    {
        *value=1u;
    }

    if(u16ReadKeyPinLevel == 1u)
    {
        Key_u32PhyKeyPressFlag |= 1 << 12u;
    }
    return enReturn;
}

/*============================================================================
*Function : KEY_tenValueSts KEY_vKeyMaxAcPressImport(uint16 *value)
*Description : max 32 keys
*takes : nothing
*return: nothing
*/
KEY_tenValueSts KEY_vKeyForce5Import(uint16 *value)
{
    KEY_tenValueSts enReturn=KEY_nValid;
    uint16 u16ReadKeyPinLevel;

    u16ReadKeyPinLevel=ForceSensor_u8GetValue((KEY_tenu8PadVarNum)KEY_nu8Pad5);
    if(u16ReadKeyPinLevel == 1u)
    {
	    *value=0u;
    }
    else
    {
        *value=1u;
    }

    if(u16ReadKeyPinLevel == 1u)
    {
        Key_u32PhyKeyPressFlag |= 1 << 13u;
    }
    return enReturn;
}

/*============================================================================
*Function : KEY_tenValueSts KEY_vKeyAqsPressImport(uint16 *value)
*Description : max 32 keys
*takes : nothing
*return: nothing
*/
KEY_tenValueSts KEY_vKeyForce6Import(uint16 *value)
{
    KEY_tenValueSts enReturn=KEY_nValid;
    uint16 u16ReadKeyPinLevel;

    u16ReadKeyPinLevel=ForceSensor_u8GetValue((KEY_tenu8PadVarNum)KEY_nu8Pad6);
    if(u16ReadKeyPinLevel == 1u)
    {
	    *value=0u;
    }
    else
    {
        *value=1u;
    }

    if(u16ReadKeyPinLevel == 1u)
    {
        Key_u32PhyKeyPressFlag |= 1 << 14u;
    }
    return enReturn;
}

/*============================================================================
*Function : KEY_tenValueSts KEY_vKeyPM25PressImport(uint16 *value)
*Description : max 32 keys
*takes : nothing
*return: nothing
*/
KEY_tenValueSts KEY_vKeyForce7Import(uint16 *value)
{
    KEY_tenValueSts enReturn=KEY_nValid;
    uint16 u16ReadKeyPinLevel;

    u16ReadKeyPinLevel=ForceSensor_u8GetValue((KEY_tenu8PadVarNum)KEY_nu8Pad7);
    if(u16ReadKeyPinLevel == 1u)
    {
	    *value=0u;
    }
    else
    {
        *value=1u;
    }

    if(u16ReadKeyPinLevel == 1u)
    {
        Key_u32PhyKeyPressFlag |= 1 << 15u;
    }
    return enReturn;
}

/*============================================================================
*Function : KEY_tenValueSts KEY_vKeyPM25PressImport(uint16 *value)
*Description : max 32 keys
*takes : nothing
*return: nothing
*/
KEY_tenValueSts KEY_vKeyForce8Import(uint16 *value)
{
   KEY_tenValueSts enReturn=KEY_nValid;
    uint16 u16ReadKeyPinLevel;

    u16ReadKeyPinLevel=ForceSensor_u8GetValue((KEY_tenu8PadVarNum)KEY_nu8Pad8);
    if(u16ReadKeyPinLevel == 1u)
    {
	    *value=0u;
    }
    else
    {
        *value=1u;
    }

    if(u16ReadKeyPinLevel == 1u)
    {
        Key_u32PhyKeyPressFlag |= 1 << 16u;
    }
    return enReturn;
}

/*============================================================================
*Function : KEY_tenValueSts KEY_vKeyPM25PressImport(uint16 *value)
*Description : max 32 keys
*takes : nothing
*return: nothing
*/
KEY_tenValueSts KEY_vKeyForce9Import(uint16 *value)
{
  KEY_tenValueSts enReturn=KEY_nValid;
    uint16 u16ReadKeyPinLevel;

    u16ReadKeyPinLevel=ForceSensor_u8GetValue((KEY_tenu8PadVarNum)KEY_nu8Pad9);
    if(u16ReadKeyPinLevel == 1u)
    {
	    *value=0u;
    }
    else
    {
        *value=1u;
    }

    if(u16ReadKeyPinLevel == 1u)
    {
        Key_u32PhyKeyPressFlag |= 1 << 17u;
    }
    return enReturn;
}
/*============================================================================
*Function : void KEY_vKeyClearPhyKeyFalg(void)
*Description : max 32 keys
*takes : nothing
*return: nothing
*/
void KEY_vKeyClearPhyKeyFalg(void)
{
    Key_u32PhyKeyPressFlag = 0u;
}

/*============================================================================
*Function : uint32 KEY_vKeyGetPhyKeyPressAction(void)
*Description : max 32 keys
*takes : nothing
*return: nothing
*/
uint32 KEY_vKeyGetPhyKeyPressAction(void)
{
    //KEY_tstMainOut KEY_stMainOut;
    
    //KEY_enGetMainOutputExport(&KEY_stMainOut);

    //return (Key_u32PhyKeyPressFlag & KEY_stMainOut.u32ActionTable);
    return Key_u32PhyKeyPressFlag;
}

/*============================================================================
*Function : uint32 Key_u32ForceADProcess(void)
*Description : max 32 keys
*takes : nothing
*return: nothing
*/
uint32 Key_u32ForceSensorADProcess(void)
{
	uint16 u16ForceSensorADValue;
	u16ForceSensorADValue=21;
	//Rte_Call_IoHwAd_IoHwAd_ReadAd_FORCE_Read(&u16ForceSensorADValue);
	if(u16ForceSensorADValue>20)
	{
		Key_u32ForceADValidFlag=1;
	}
	else
	{
		Key_u32ForceADValidFlag=1;
	}
    return Key_u32ForceADValidFlag;
	
}
/*****************************************************************************
* EOF: KEY_interface.c
*****************************************************************************/
