/*******************************************************************************
| Module Name: Recirculation Fresh Air control interface
| File Name: BCTL_Interface.c
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
| 2016.7.1          A0      Ouyang Bihuan        First created for base code.  
| 
| 
********************************************************************************/


/*****************************************************************************
* FILE DECLARATION
*****************************************************************************/
#define BCTLDRV_Interface                          /* Name of the Module                */

/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
*****************************************************************************/
/* System-headerfiles */
#include "General.h"

/* Foreign headerfiles */
#include "ALG.h"
#include "BCTL.h"   
#include "RTE_Internal.h" 
/* Own headerfiles */
#include "BCTLDRV.h"    
#include "BCTLDRV_Cfg.h"
#include "BCTLDRV_Type.h"
#include "BCTLDRV_Private.h"  
#include "BCTLDRV_interface.h"

/*****************************************************************************
* MODULE GLOBAL CONFIGURATION CONSTANTS
*
* In this section define
* - constants to configure your module. These constants are unknown for other
*   modules
*****************************************************************************/
/* Input comfiguration table. */
#if(BCTLDRV_nHW_RELAY_CTRL !=0U)    
static BCTLDRV_tstU8InputAttributes BCTLDRV_stU8InputAttr[BCTLDRV_nNumOfU8Inputs] =
{ 
    /*Min*****Max****Default***Terr****LastVar***Couter*/
    {	0x0U,	0x1U,	0x0U,	0x5U,	0x0U,	0x0U},	/*---	    BCTLDRV_u8InputBlwRelay	---*/

};
#endif

static BCTLDRV_tstU16InputAttributes BCTLDRV_stU16InputAttr[BCTLDRV_nNumOfU16Inputs] =
{
    {	0U,	1600U,	0U,	       5U,	0U,	0U},	/*---	    BCTLDRV_u16InputBlwVolt	---*/
#if(BCTLDRV_nWITH_FEED_BACK!=0U)           
    {	0U,	2000U,	0U,	       5U,	0U,	0U},	/*---	    BCTLDRV_u16InputPtaBlwFb	---*/
#endif
};

BCTLDRV_tenValueSts BCTLDRV_enU16InputValueCalc(BCTLDRV_tstU16InAttrType *Input, uint16 *Output);
BCTLDRV_tenValueSts BCTLDRV_enU8InputValueCalc(BCTLDRV_tstU8InAttrType *Input, uint8 *Output);

#if( BCTLDRV_nUseCCP == True)

/*Ccp control*/
typedef enum
{
	BCTLDRV_nSetBlwAdFb,
	BCTLDRV_nObdSetBlwTarget,        
	BCTLDRV_nCcpForceMax
}CcpControl_BctlDrv;
static uint8 BCTLDRV_CcpForceFlag=0;
static uint16 BCTLDRV_CcpControlData[BCTLDRV_nCcpForceMax];
#define BCTLDRVGetCcpForceBit(index)	((BCTLDRV_CcpForceFlag>>index)&0x01)
#define BCTLDRVSetCcpForceBit(index)	(BCTLDRV_CcpForceFlag=BCTLDRV_CcpForceFlag|(0x01<<index))
#define BCTLDRVClrCcpForceBit(index)	(BCTLDRV_CcpForceFlag=BCTLDRV_CcpForceFlag&(~(0x01<<index)))
#define BCTLDRVClrCcpForceByte(void)	(BCTLDRV_CcpForceFlag=0)
//static void BCTLDRV_vCcpInputForce(void);
static void BCTLDRV_vCcpOutputForce(void);


/*****************************************************************************
 Function      : BCTLDRV_ForceIoControl_Write                                 
 Description   : Ccp control function
 Takes         : Nothing
 Return Value  : None                                                *
*****************************************************************************/
Std_ReturnType BCTLDRV_u8ForceIoControl_Write(/*IN*/UInt32 ForceIoControlWord)
{
    uint8 u8ReturnValue=RTE_E_OK;
	tstCcpContronType CcpControlWord;
	CcpControlWord.CcpContronData=(uint16)ForceIoControlWord;
	CcpControlWord.CcpCommand=(uint8)(ForceIoControlWord>>16);
	CcpControlWord.CcpCommandFlag=(uint8)(ForceIoControlWord>>24);
	if(CcpControlWord.CcpCommandFlag==True)
	{
		switch(CcpControlWord.CcpCommand)
		{
			case 0:
				BCTLDRVClrCcpForceByte();
				break;
			case 1:
				BCTLDRVSetCcpForceBit(BCTLDRV_nSetBlwAdFb);
				BCTLDRV_CcpControlData[BCTLDRV_nSetBlwAdFb]=CcpControlWord.CcpContronData;
				break;
			case 2:
				BCTLDRVClrCcpForceBit(BCTLDRV_nSetBlwAdFb);
				BCTLDRV_CcpControlData[BCTLDRV_nSetBlwAdFb]=0;
				break;
			case 0x81:
				BCTLDRVSetCcpForceBit(BCTLDRV_nObdSetBlwTarget);
				BCTLDRV_CcpControlData[BCTLDRV_nObdSetBlwTarget]=CcpControlWord.CcpContronData;
				break;
			default:
                u8ReturnValue= RTE_E_INVALID;;
				break;
		}
	}
	else
	{
		BCTLDRVClrCcpForceByte();                    
	}
        return u8ReturnValue;
}


/*****************************************************************************
 Function      : BCTLDRV_vCcpOutputForce                                 
 Description   : force output value
 Takes         : Nothing
 Return Value  : None                                                *
*****************************************************************************/
static void BCTLDRV_vCcpOutputForce(void)
{

}

#endif

#if(BCTLDRV_nHW_RELAY_CTRL !=0U)   
/*============================================================================
*Function : BCTLDRV_tenValueSts BCTLDRV_enAirdDisInfoImport(uint8 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
BCTLDRV_tenValueSts BCTLDRV_enRelaySigImport(uint8 *value)
{
    BCTLDRV_tenValueSts enRet;
    BCTLDRV_tstU8InAttrType stU8InAttr;
    
    stU8InAttr.pstU8Attr = &BCTLDRV_stU8InputAttr[BCTLDRV_u8InputBlwRelay];
    stU8InAttr.u8Input = BCTLDRV_u8GetBlwCanRelay();
    
    enRet = BCTLDRV_enU8InputValueCalc(&stU8InAttr,value);
    return enRet;
}
#endif
/*============================================================================
*Function : BCTLDRV_tenValueSts BCTLDRV_enBlwVoltImport(uint16 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
BCTLDRV_tenValueSts BCTLDRV_enBlwVoltImport(uint16 *value)
{
    BCTLDRV_tenValueSts enRet;
    BCTLDRV_tstU16InAttrType stU16InAttr;
    
    stU16InAttr.pstU16Attr = &BCTLDRV_stU16InputAttr[BCTLDRV_u16InputBlwVolt];
    stU16InAttr.u16Input = BCTLDRV_u16GetBctlVolt();
    
    enRet=BCTLDRV_enU16InputValueCalc(&stU16InAttr,value);
    return enRet;
}
#if(BCTLDRV_nWITH_FEED_BACK!=0U) 
/*============================================================================
*Function : BCTLDRV_tenValueSts BCTLDRV_enVelVarImport(uint16 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
BCTLDRV_tenValueSts BCTLDRV_enPtaBlwVoltImport(uint16 *value)
{
    BCTLDRV_tenValueSts enRet;
    BCTLDRV_tstU16InAttrType stU16InAttr;
    
    stU16InAttr.pstU16Attr = &BCTLDRV_stU16InputAttr[BCTLDRV_u16InputPtaBlwFb];
    BCTLDRV_u16HalGetBlowerFb(&stU16InAttr.u16Input);
    
    enRet=BCTLDRV_enU16InputValueCalc(&stU16InAttr,value);
    return enRet;
}
#endif


#if(BCTLDRV_nUseRTE == True)
/*============================================================================
*Function : void BCTLDRV_vOutputUpdate(void)
*Description : Local value after caculation need to transmit to RTE
*takes : nothing
*return: Nothing
*/
void BCTLDRV_vOutputUpdate(void)
{
#if 0
    Rte_IWrite_BctlDrv_vReset_BctlDrvSwVersion_u8Version(BCTLDRV_u8GetValue(BCTLDRV_nu8SwVersion));
    Rte_IWrite_BctlDrv_vMain_BctlDrvErrorCode_u16BitMap(BCTLDRV_u16GetValue(BCTLDRV_nu16Error));
    Rte_IWrite_BctlDrv_vMain_BctlDrvFbRawValue_u16RawValue(BCTLDRV_u16GetValue(BCTLDRV_nu16VoltFeedback));
    Rte_IWrite_BctlDrv_vMain_BctlDrvPwmDuty_u16PwmDuty(BCTLDRV_u16GetValue(BCTLDRV_nu16PwmDuty));
#endif
}
#endif
/*============================================================================
*Function : BCTLDRV_tenValueSts BCTLDRV_enU16InputValueCalc(BCTLDRV_tstU16InputAttributes *Input, uint16 *Output)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
BCTLDRV_tenValueSts BCTLDRV_enU16InputValueCalc(BCTLDRV_tstU16InAttrType *Input, uint16 *Output)
{
    BCTLDRV_tenValueSts enRet;
    if(Input->u16Input == 0xFFFF)
    {
        if(Input->pstU16Attr->u8ErrCounter < Input->pstU16Attr->n8ErrWaitTime)
        {
            enRet = BCTLDRV_nInvalid;
        }
        else
        {
           enRet = BCTLDRV_nDefault;
           *Output=Input->pstU16Attr->n16Default;
        }
        Input->pstU16Attr->u16Last = Input->pstU16Attr->n16Default;
    }
    else
    {
        if((Input->u16Input < Input->pstU16Attr->n16MinVal)||(Input->u16Input > Input->pstU16Attr->n16MaxVal))
        {
          /*Keep last value. */
          *Output = Input->pstU16Attr->u16Last;
          enRet=BCTLDRV_nLastValue;
        }
        else
        {
          *Output=Input->u16Input;
          enRet=BCTLDRV_nValid;
        }
        Input->pstU16Attr->u16Last = *Output;
    }
    return enRet;
}

/*============================================================================
*Function : BCTLDRV_tenValueSts BCTLDRV_enU8InputValueCalc(BCTLDRV_tstU8InputAttributes *Input, uint8 *Output)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
BCTLDRV_tenValueSts BCTLDRV_enU8InputValueCalc(BCTLDRV_tstU8InAttrType *Input, uint8 *Output)
{
    BCTLDRV_tenValueSts enRet;
    
    if(Input->u8Input == 0xFFU)
    {
        if(Input->pstU8Attr->u8ErrCounter < Input->pstU8Attr->n8ErrWaitTime)
        {
            enRet=BCTLDRV_nInvalid;
        }
        else
        {
           enRet=BCTLDRV_nDefault;
           *Output=Input->pstU8Attr->n8Default;
        }
        Input->pstU8Attr->u8Last = Input->pstU8Attr->n8Default;
    }
    else
    {
        if((Input->u8Input < Input->pstU8Attr->n8MinVal)||(Input->u8Input > Input->pstU8Attr->n8MaxVal))
        {
            /* Out put last value.*/
            *Output=Input->pstU8Attr->u8Last;
            enRet=BCTLDRV_nLastValue;
        }
        else
        {
          *Output=Input->u8Input;
          enRet=BCTLDRV_nValid;
        }
        Input->pstU8Attr->u8Last = *Output;
    }
    return enRet;
}

/*****************************************************************************
* EOF: BCTLDRV_Interface.c
*****************************************************************************/

