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
| 2016.7.1          A0      Luo Xindian        First created for base code.  
| 
| 
********************************************************************************/


/*****************************************************************************
* FILE DECLARATION
*****************************************************************************/
#define BCTL_Interface                          /* Name of the Module                */

/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
*****************************************************************************/
/* System-headerfiles */
#include "General.h"

/* Foreign headerfiles */
#include "ALG.h"
#include "CCS.h"  
#include "SUN.h"  
#include "VEL.h"  
#include "MMI.h"  
#include "EVAP.h"  
#include "OAT.h"  
#include "HCT.h" 
#include "Aird.h"
#include "RFA.h"
#include "POW.h"
#include "CTS_StdDef.h"
#include "VICT.h"

/* Own headerfiles */
#include "BCTL_Cfg.h"
#include "BCTL_Type.h"
#include "BCTL_Private.h"
#include "BCTL.h"      
#include "BCTL_interface.h"

/*****************************************************************************
* MODULE GLOBAL CONFIGURATION CONSTANTS
*
* In this section define
* - constants to configure your module. These constants are unknown for other
*   modules
*****************************************************************************/
/* Input comfiguration table. */
static BCTL_tstU8InputAttributes BCTL_stU8InputAttr[BCTL_nNumOfU8Inputs] =
{ 
    /*Min*****Max****Default***Terr****LastVar***Couter*/
    {	0x0U,	0x4U,	0x0U,	0x5U,	0x0U,	0x0U},	/*---	    BCTL_u8InputAirdDisplay	---*/
    {	0x0U,	0x1U,	0x0U,	0x5U,	0x0U,	0x0U},	/*---	    BCTL_u8InputAcDisplay	---*/
    {	0x0U,	0x1U,	0x0U,	0x5U,	0x0U,	0x0U},	/*---	    BCTL_u8InputIgnLimit	---*/
    {	0x0U,	0x1U,	0x0U,	0x5U,	0x0U,	0x0U},	/*---	    BCTL_u8InputIsStaus	---*/
    {	0x0U,	0xfeU,	44U,	       0x5U,	44U,	       0x0U},	/*---	    BCTL_u8InputMmiSetTempDr	---*/
    {	0x0U,	0xfeU,	44U,	       0x5U,	44U,	       0x0U},	/*---	    BCTL_u8InputMmiSetTempPs	---*/
    {	0x0U,	0x1U,	0x0U,	0x5U,	0x0U,	0x0U},	/*---	    BCTL_u8InputMmiBlwEvent	---*/
    {	0x0U,	0x6U,	0x0U,	0x5U,	0x0U,	0x0U},	/*---	    BCTL_u8InputMmiBlwMode	---*/
    {	0x0U,	0x7U,	0x0U,	0x5U,	0x0U,	0x0U},	/*---	    BCTL_u8InputMmiBlwCtrl	---*/
    {	0x0U,	0x1U,	0x0U,	0x5U,	0x0U,	0x0U},	/*---	    BCTL_u8InputPowFail	---*/
    {	0x0U,	0x1U,	0x0U,	0x5U,	0x0U,	0x0U} 	/*---	    BCTL_u8InputRfaDisplay	---*/

};

static BCTL_tstU16InputAttributes BCTL_stU16InputAttr[BCTL_nNumOfU16Inputs] =
{
    {	0U,	10000U,	5200U,	5U,	5200U,	0U},	/*---	    BCTL_u16InputCcsSetTempDr	---*/
    {	0U,	10000U,	5200U,	5U,	5200U,	0U},	/*---	    BCTL_u16InputCcsSetTempPs	---*/
    {	0U,	10000U,	5200U,	5U,	5200U,	0U},	/*---	    BCTL_u16InputCcsBlowoutAvg	---*/
    {	0U,	10000U,	5000U,	5U,	5000U,	0U},	/*---	    BCTL_u16InputCcsTempDiffDr	---*/
    {	0U,	10000U,	5000U,	5U,	5000U,	0U},	/*---	    BCTL_u16InputCcsTempDiffPs	---*/
    {	0U,	10000U,	5200U,	5U,	5200U,	0U},	/*---	    BCTL_u16InputEvapValue	---*/
    {	0U,	10000U,	5800U,	5U,	5800U,	0U},	/*---	    BCTL_u16InputHctValue	---*/
    {	0U,	10000U,	5200U,	5U,	5200U,	0U},	/*---	    BCTL_u16InputOatValue	---*/
    {	0U,	2000U,	0U,	       5U,	0U,	       0U},	/*---	    BCTL_u16InputSunValue	---*/
    {	0U,	2000U,	0U,	       5U,	0U,	       0U}  /*---	    BCTL_u16InputVelValue	---*/

};

BCTL_tenValueSts BCTL_enU16InputValueCalc(BCTL_tstU16InAttrType *Input, uint16 *Output);
BCTL_tenValueSts BCTL_enU8InputValueCalc(BCTL_tstU8InAttrType *Input, uint8 *Output);


/*============================================================================
*Function : BCTL_tenValueSts BCTL_enAirdDisInfoImport(uint8 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
BCTL_tenValueSts BCTL_enAirdDisInfoImport(uint8 *value)
{
    BCTL_tenValueSts enRet;
    BCTL_tstU8InAttrType stU8InAttr;
    
    stU8InAttr.pstU8Attr = &BCTL_stU8InputAttr[BCTL_u8InputAirdDisplay];
    stU8InAttr.u8Input = BCTL_u8AirdDisInfo();
    
    enRet = BCTL_enU8InputValueCalc(&stU8InAttr,value);
    return enRet;
}

/*============================================================================
*Function : BCTL_tenValueSts BCTL_enAcccDisInfoImport(uint8 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
BCTL_tenValueSts BCTL_enAcccDisInfoImport(uint8 *value)
{
    BCTL_tenValueSts enRet;
    BCTL_tstU8InAttrType stU8InAttr;
    
    stU8InAttr.pstU8Attr = &BCTL_stU8InputAttr[BCTL_u8InputAcDisplay];
    stU8InAttr.u8Input = BCTL_u8AcccDisInfo();
    
    enRet=BCTL_enU8InputValueCalc(&stU8InAttr,value);
    return enRet;
}

/*============================================================================
*Function : BCTL_tenValueSts BCTL_enIgnEnableSigImport(uint8 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
BCTL_tenValueSts BCTL_enIgnEnableSigImport(uint8 *value)
{
    BCTL_tenValueSts enRet;
    BCTL_tstU8InAttrType stU8InAttr;
    
    stU8InAttr.pstU8Attr = &BCTL_stU8InputAttr[BCTL_u8InputIgnLimit];
    stU8InAttr.u8Input = BCTL_u8IgnEnableSig();
    
    enRet=BCTL_enU8InputValueCalc(&stU8InAttr,value);
    return enRet;
}

/*============================================================================
*Function : BCTL_tenValueSts BCTL_enIsStatusImport(uint8 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
BCTL_tenValueSts BCTL_enIsStatusImport(uint8 *value)
{
    BCTL_tenValueSts enRet;
    BCTL_tstU8InAttrType stU8InAttr;
    
    stU8InAttr.pstU8Attr = &BCTL_stU8InputAttr[BCTL_u8InputIsStaus];
    stU8InAttr.u8Input = BCTL_u8IstpEngStatus();
    
    enRet=BCTL_enU8InputValueCalc(&stU8InAttr,value);
    return enRet;
}


/*============================================================================
*Function : BCTL_tenValueSts BCTL_enMmiSetTempDrImport(uint8 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
BCTL_tenValueSts BCTL_enMmiSetTempDrImport(uint8 *value)
{
    BCTL_tenValueSts enRet;
    BCTL_tstU8InAttrType stU8InAttr;
    
    stU8InAttr.pstU8Attr = &BCTL_stU8InputAttr[BCTL_u8InputMmiSetTempDr];
    stU8InAttr.u8Input = BCTL_u8MmiSetTempDr();
    if(stU8InAttr.u8Input == 0xFFU)
    {
        stU8InAttr.u8Input = 0xFEU;
    }
    else
    {

    }
    
    enRet=BCTL_enU8InputValueCalc(&stU8InAttr,value);
    return enRet;
}

/*============================================================================
*Function : BCTL_tenValueSts BCTL_enMmiSetTempPsImport(uint8 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
BCTL_tenValueSts BCTL_enMmiSetTempPsImport(uint8 *value)
{
    BCTL_tenValueSts enRet;
    BCTL_tstU8InAttrType stU8InAttr;
    
    stU8InAttr.pstU8Attr = &BCTL_stU8InputAttr[BCTL_u8InputMmiSetTempPs];
    stU8InAttr.u8Input = BCTL_u8MmiSetTempPs();
    
    enRet=BCTL_enU8InputValueCalc(&stU8InAttr,value);
    return enRet;
}

/*============================================================================
*Function : BCTL_tenValueSts BCTL_enMmiBlwCtrlImport(uint8 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
BCTL_tenValueSts BCTL_enMmiBlwEventImport(uint8 *value)
{
    BCTL_tenValueSts enRet;
    BCTL_tstU8InAttrType stU8InAttr;
    
    stU8InAttr.pstU8Attr = &BCTL_stU8InputAttr[BCTL_u8InputMmiBlwEvent];
    stU8InAttr.u8Input = BCTL_u8GetMmiBlwEvent();
    
    enRet=BCTL_enU8InputValueCalc(&stU8InAttr,value);
    return enRet;
}

/*============================================================================
*Function : BCTL_tenValueSts BCTL_enMmiBlwModeImport(uint8 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
BCTL_tenValueSts BCTL_enMmiBlwModeImport(uint8 *value)
{
    BCTL_tenValueSts enRet;
    BCTL_tstU8InAttrType stU8InAttr;
    
    stU8InAttr.pstU8Attr = &BCTL_stU8InputAttr[BCTL_u8InputMmiBlwMode];
    stU8InAttr.u8Input = BCTL_u8GetMmiMode();
    
    enRet=BCTL_enU8InputValueCalc(&stU8InAttr,value);
    return enRet;
}

/*============================================================================
*Function : BCTL_tenValueSts BCTL_enMmiBlwCtrlImport(uint8 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
BCTL_tenValueSts BCTL_enMmiBlwCtrlImport(uint8 *value)
{
    BCTL_tenValueSts enRet;
    BCTL_tstU8InAttrType stU8InAttr;
    
    stU8InAttr.pstU8Attr = &BCTL_stU8InputAttr[BCTL_u8InputMmiBlwCtrl];
    stU8InAttr.u8Input = BCTL_u8GetMmiCtrl();
    
    enRet=BCTL_enU8InputValueCalc(&stU8InAttr,value);
    return enRet;
}

/*============================================================================
*Function : BCTL_tenValueSts BCTL_enPowFailureImport(uint8 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
BCTL_tenValueSts BCTL_enPowFailureImport(uint8 *value)
{
    BCTL_tenValueSts enRet;
    BCTL_tstU8InAttrType stU8InAttr;
    
    stU8InAttr.pstU8Attr = &BCTL_stU8InputAttr[BCTL_u8InputPowFail];
    stU8InAttr.u8Input = BCTL_u8GetPowHighVolt()|BCTL_u8GetPowLowVolt();
    
    enRet=BCTL_enU8InputValueCalc(&stU8InAttr,value);
    return enRet;
}


/*============================================================================
*Function : BCTL_tenValueSts BCTL_enMmiBlwCtrlImport(uint8 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
BCTL_tenValueSts BCTL_enRfaDisInfoImport(uint8 *value)
{
    BCTL_tenValueSts enRet;
    BCTL_tstU8InAttrType stU8InAttr;
    
    stU8InAttr.pstU8Attr = &BCTL_stU8InputAttr[BCTL_u8InputRfaDisplay];
    stU8InAttr.u8Input = BCTL_u16GetRfaDisInfo();
    
    enRet=BCTL_enU8InputValueCalc(&stU8InAttr,value);
    return enRet;
}

/************************************* 16 bit inputs *****************************************/

/*============================================================================
*Function : BCTL_tenValueSts BCTL_enCcsSetTempDrImport(uint16 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
BCTL_tenValueSts BCTL_enCcsSetTempDrImport(uint16 *value)
{
    BCTL_tenValueSts enRet;
    BCTL_tstU16InAttrType stU16InAttr;
    
    stU16InAttr.pstU16Attr = &BCTL_stU16InputAttr[BCTL_u16InputCcsSetTempDr];
    stU16InAttr.u16Input = BCTL_u16GetCcsSetTempDr();
    if(stU16InAttr.u16Input != 0xFFFFU)
    {
        stU16InAttr.u16Input += 4600U;
    }
    enRet=BCTL_enU16InputValueCalc(&stU16InAttr,value);
    return enRet;
}

/*============================================================================
*Function : BCTL_tenValueSts BCTL_enCcsSetTempPsImport(uint16 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
BCTL_tenValueSts BCTL_enCcsSetTempPsImport(uint16 *value)
{
    BCTL_tenValueSts enRet;
    BCTL_tstU16InAttrType stU16InAttr;
    
    stU16InAttr.pstU16Attr = &BCTL_stU16InputAttr[BCTL_u16InputCcsSetTempPs];
    stU16InAttr.u16Input = BCTL_u16GetCcsSetTempPs();
    if(stU16InAttr.u16Input != 0xFFFFU)
    {
        stU16InAttr.u16Input += 4600U;
    }
    enRet=BCTL_enU16InputValueCalc(&stU16InAttr,value);
    return enRet;
}

/*============================================================================
*Function : BCTL_tenValueSts BCTL_enCcsBlowoutAvgImport(uint16 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
BCTL_tenValueSts BCTL_enCcsBlowoutAvgImport(uint16 *value)
{
    BCTL_tenValueSts enRet;
    BCTL_tstU16InAttrType stU16InAttr;
    
    stU16InAttr.pstU16Attr = &BCTL_stU16InputAttr[BCTL_u16InputCcsBlowoutAvg];
    stU16InAttr.u16Input = BCTL_u16GetCcsBlowoutTempAvg();//BCTL_u16GetCcsSetTempAvg();160108
    if(stU16InAttr.u16Input != 0xFFFFU)
    {
        stU16InAttr.u16Input += 4600U;
    }
    enRet=BCTL_enU16InputValueCalc(&stU16InAttr,value);
    return enRet;
}

/*============================================================================
*Function : BCTL_tenValueSts BCTL_enCcsSiDrImport(uint16 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
BCTL_tenValueSts BCTL_enCcsSiDrImport(uint16 *value)
{
    BCTL_tenValueSts enRet;
    BCTL_tstU16InAttrType stU16InAttr;
    
    stU16InAttr.pstU16Attr = &BCTL_stU16InputAttr[BCTL_u16InputCcsTempDiffDr];
    stU16InAttr.u16Input = BCTL_u16GetCcsSiDr();
    if(stU16InAttr.u16Input != 0xFFFFU)
    {
        stU16InAttr.u16Input += 4360U;
    }
    enRet=BCTL_enU16InputValueCalc(&stU16InAttr,value);
    return enRet;
}

/*============================================================================
*Function : BCTL_tenValueSts BCTL_enCcsSiPsImport(uint16 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
BCTL_tenValueSts BCTL_enCcsSiPsImport(uint16 *value)
{
    BCTL_tenValueSts enRet;
    BCTL_tstU16InAttrType stU16InAttr;
    
    stU16InAttr.pstU16Attr = &BCTL_stU16InputAttr[BCTL_u16InputCcsTempDiffPs];
    stU16InAttr.u16Input = BCTL_u16GetCcsSiPs();
    if(stU16InAttr.u16Input != 0xFFFFU)
    {
        stU16InAttr.u16Input += 4360U;
    }
    enRet=BCTL_enU16InputValueCalc(&stU16InAttr,value);
    return enRet;
}

/*============================================================================
*Function : BCTL_tenValueSts BCTL_enEvapVarImport(uint16 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
BCTL_tenValueSts BCTL_enEvapVarImport(uint16 *value)
{
    BCTL_tenValueSts enRet;
    BCTL_tstU16InAttrType stU16InAttr;
    
    stU16InAttr.pstU16Attr = &BCTL_stU16InputAttr[BCTL_u16InputEvapValue];
    stU16InAttr.u16Input = BCTL_u16GetEvaValue();
    if(stU16InAttr.u16Input != 0xFFFFU)
    {
        stU16InAttr.u16Input += 4600U;
    }
    enRet=BCTL_enU16InputValueCalc(&stU16InAttr,value);
    return enRet;
}

/*============================================================================
*Function : BCTL_tenValueSts BCTL_enHctVarImport(uint16 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
BCTL_tenValueSts BCTL_enHctVarImport(uint16 *value)
{
    BCTL_tenValueSts enRet;
    BCTL_tstU16InAttrType stU16InAttr;
    
    stU16InAttr.pstU16Attr = &BCTL_stU16InputAttr[BCTL_u16InputHctValue];
    stU16InAttr.u16Input = BCTL_u16GetHctValue();
    if(stU16InAttr.u16Input != 0xFFFFU)
    {
        stU16InAttr.u16Input += 4600U;
    }
    enRet=BCTL_enU16InputValueCalc(&stU16InAttr,value);
    return enRet;
}


/*============================================================================
*Function : BCTL_tenValueSts BCTL_enOatValImport(uint16 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
BCTL_tenValueSts BCTL_enOatValImport(uint16 *value)
{
    BCTL_tenValueSts enRet;
    BCTL_tstU16InAttrType stU16InAttr;
    
    stU16InAttr.pstU16Attr = &BCTL_stU16InputAttr[BCTL_u16InputOatValue];
    stU16InAttr.u16Input = BCTL_u16GetOatValue();
    if(stU16InAttr.u16Input != 0xFFFFU)
    {
        stU16InAttr.u16Input += 4600U;
    }
    enRet=BCTL_enU16InputValueCalc(&stU16InAttr,value);
    return enRet;
}

/*============================================================================
*Function : BCTL_tenValueSts BCTL_enIncomingHeatImport(uint16 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
BCTL_tenValueSts BCTL_enIncomingHeatImport(uint16 *value)
{
    uint8 u8IncomingHeatSta;
    BCTL_tstU16InAttrType stU16InAttr;

    u8IncomingHeatSta = (uint8)VICT_u16GetValidState(VICT_nu16IncomingHeat);
    stU16InAttr.u16Input = VICT_u16GetValue(VICT_nu16IncomingHeat);

    if(stU16InAttr.u16Input != 0xFFFFU)
    {
        stU16InAttr.u16Input += 4600U;
    }

    *value = stU16InAttr.u16Input;
    
    return (BCTL_tenValueSts)u8IncomingHeatSta;
}

/*============================================================================
*Function : BCTL_tenValueSts BCTL_enSunVarImport(uint16 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
BCTL_tenValueSts BCTL_enSunVarImport(uint16 *value)
{
    BCTL_tenValueSts enRet;
    BCTL_tstU16InAttrType stU16InAttr;
    
    stU16InAttr.pstU16Attr = &BCTL_stU16InputAttr[BCTL_u16InputSunValue];
#if(BCTL_nSunSensorNum == 1)
    stU16InAttr.u16Input = BCTL_u16GetSunValueDr();
#else
    stU16InAttr.u16Input = MAX(BCTL_u16GetSunValueDr(),BCTL_u16GetSunValuePs());
#endif
    
    enRet=BCTL_enU16InputValueCalc(&stU16InAttr,value);
    return enRet;
}

/*============================================================================
*Function : BCTL_tenValueSts BCTL_enVelVarImport(uint16 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
BCTL_tenValueSts BCTL_enVelVarImport(uint16 *value)
{
    BCTL_tenValueSts enRet;
    BCTL_tstU16InAttrType stU16InAttr;
    
    stU16InAttr.pstU16Attr = &BCTL_stU16InputAttr[BCTL_u16InputVelValue];
    stU16InAttr.u16Input = BCTL_u16GetVelValue();
    
    enRet=BCTL_enU16InputValueCalc(&stU16InAttr,value);
    return enRet;
}



#if(BCTL_nUseRTE == True)
/*============================================================================
*Function : void BCTL_vOutputUpdate(void)
*Description : Local value after caculation need to transmit to RTE
*takes : nothing
*return: Nothing
*/
void BCTL_vOutputUpdate(void)
{
 #if 0
    BCTL_tenValueSts enValueSts;
    BCTL_tstMainOut stMainOut;
    enValueSts=BCTL_enGetStMainOutExport(&stMainOut);

	Rte_IWrite_Bctl_vReset_BctlSwVersion_u8Version(0xA5U);
	Rte_IWrite_Bctl_vMain_BctlDisplay_u8DispInfo(stMainOut.DisplayInfo.Val);
	Rte_IWrite_Bctl_vMain_BctlBlwCcsTarget_u16BlwSpd(stMainOut.CcsTrgVlt.Val);
	Rte_IWrite_Bctl_vMain_BctlTargetVoltageLimit_u16BlwSpd(stMainOut.VolLmt.Val);
	Rte_IWrite_Bctl_vMain_BctlOatSetTempOffset_u16TempOffset(stMainOut.OatCcsSetTempVolOffsetDr.Val);
	Rte_IWrite_Bctl_vMain_BctlBlowoutTempOffset_u16TempOffset(0U);
	Rte_IWrite_Bctl_vMain_BctlSiOffset_u16BlwSpdOffset(stMainOut.SiVolOffsetDr.Val);
	Rte_IWrite_Bctl_vMain_BctlSunOffset_u16BlwSpdOffset(stMainOut.SunVolOffset.Val);
	Rte_IWrite_Bctl_vMain_BctlBlwTarget_u16BlwSpd(stMainOut.TrgVlt.Val);
	Rte_IWrite_Bctl_vMain_BctlVelOffset_u16BlwSpdOffset(stMainOut.VelVolOffset.Val);
	Rte_IWrite_Bctl_vMain_BctlErrorCode_u16BitMap(stMainOut.SwVer.Val);
	Rte_IWrite_Bctl_vMain_BctlAirdBaseVoltage_u16BlwSpd(0U);
	Rte_IWrite_Bctl_vMain_BctlHctEvaLimit_u16BlwSpd(stMainOut.WuCdVolLmt.Val);
	Rte_IWrite_Bctl_vMain_BctlOatLimit_u16BlwSpd(stMainOut.OatVolLmt.Val);

    if(stMainOut.TrgVlt.Sts != BCTL_nInvalid)
    {
	    Rte_IWrite_Bctl_vMain_BctlValid_u8Flag(1U);
    }
    else
    {
	    Rte_IWrite_Bctl_vMain_BctlValid_u8Flag(0U);
    }
#endif
}
#endif
/*============================================================================
*Function : BCTL_tenValueSts BCTL_enU16InputValueCalc(BCTL_tstU16InputAttributes *Input, uint16 *Output)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
BCTL_tenValueSts BCTL_enU16InputValueCalc(BCTL_tstU16InAttrType *Input, uint16 *Output)
{
    BCTL_tenValueSts enRet;
    if(Input->u16Input == 0xFFFF)
    {
        if(Input->pstU16Attr->u8ErrCounter < Input->pstU16Attr->n8ErrWaitTime)
        {
            enRet = BCTL_nInvalid;
        }
        else
        {
           enRet = BCTL_nDefault;
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
          enRet=BCTL_nLastValue;
        }
        else
        {
          *Output=Input->u16Input;
          enRet=BCTL_nValid;
        }
        Input->pstU16Attr->u16Last = *Output;
    }
    return enRet;
}

/*============================================================================
*Function : BCTL_tenValueSts BCTL_enU8InputValueCalc(BCTL_tstU8InputAttributes *Input, uint8 *Output)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
BCTL_tenValueSts BCTL_enU8InputValueCalc(BCTL_tstU8InAttrType *Input, uint8 *Output)
{
    BCTL_tenValueSts enRet;
    
    if(Input->u8Input == 0xFFU)
    {
        if(Input->pstU8Attr->u8ErrCounter < Input->pstU8Attr->n8ErrWaitTime)
        {
            enRet=BCTL_nInvalid;
        }
        else
        {
           enRet=BCTL_nDefault;
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
            enRet=BCTL_nLastValue;
        }
        else
        {
          *Output=Input->u8Input;
          enRet=BCTL_nValid;
        }
        Input->pstU8Attr->u8Last = *Output;
    }
    return enRet;
}

/*****************************************************************************
* EOF: DCM_Cfg.c
*****************************************************************************/

