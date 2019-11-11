/**************************** .FILE_HEADER_BEGIN *****************************
  .TITLE  [Bctl, Blower control  ]
*-----------------------------------------------------------------------------
  .FILE   [ Bctl.c                                                         ]
*-----------------------------------------------------------------------------

 Version 			Date        Author                       Change                      
 -----------------------------------------------------------------------------     
 Rev 01.00.01  2014/04/13     OuyangBihuan       	    	The first version                  

*****************************************************************************/

/*****************************************************************************
* FILE DECLARATION
*****************************************************************************/
#define BCTL                          /* Name of the Module                */

/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
*****************************************************************************/
/* System-headerfiles */
#include "General.h"
//#include "CCS.h"  
//#include "SUN.h"  
//#include "VEL.h"  
#include "MMI.h" 
//#include "OAT.h"  
#include "Rte_Internal.h" 
/* Foreign headerfiles */
#include "Alg.h "

/* Please put the headerfiles which related to foreign here! */

/* Own headerfiles */
#include "Bctl_Cfg.h" 
#include "Bctl_Type.h"
#include "Bctl_Private.h" 
#include "Bctl_Interface.h" 
#include "Bctl.h" 




/* Please put the headerfiles which related to own here! */


/*****************************************************************************
* GLOBAL DEFINITIONS
*
* In this section define
* - all global ROM-CONSTants of your module
* - all global variables of your module
*****************************************************************************/

/* example1: Global ROM-constants
   ----------------------------------------------------- */

/* example2: Global Variables
   ----------------------------------------------------- */


/*****************************************************************************
* FILE LOCAL DEFINITIONS
*
* In this section define
* - all file local define-CONSTants
* - all file local ROM-CONSTants (STATIC)
* - all file local variables (STATIC)
*****************************************************************************/
/* example1: Local Define-constants
   ----------------------------------------------------- */
uint8 BCTL_u8LastMmiBlwCtrl;
uint8 BCTL_u8Off2OnIncFlag;
uint8 BCTL_u8Off2OnBlwLvlSet;
uint16 BCTL_u16TrgVolLmt; 
uint16 BCTL_u16TrgVolLmtTimer;   
static BCTL_tenCalSlices BCTL_enDisInfoSlices;
static BCTL_tstTblAttr BCTL_stTblAttrDisInfo = 
{
    BCTL_au16RomTrgVolX,
    BCTL_au16RomDisInfoInc,   
    BCTL_au16RomDisInfoDec,
    &BCTL_enDisInfoSlices,
    BCTL_nDisInfo_Len,
};

static BCTL_tstTblAttr2D BCTL_stTblAttr2DSunOffset =
{
	BCTL_au16RomSunLoadX,
	BCTL_au16RomSunOffsetOatTbl,
	{
		BCTL_au16RomSunOffset0,
		BCTL_au16RomSunOffset1,
		BCTL_au16RomSunOffset2,
		BCTL_au16RomSunOffset3,
	},
	BCTL_nSunOffset_Len,
	BCTL_nSunOffsetOatTbl_Len,
};

static BCTL_tstTblAttr2D BCTL_stTblAttr2DVelOffset =
{
	BCTL_au16RomVelX,
	BCTL_au16RomVelVolOffsetOatTbl,
	{
		BCTL_au16RomVelVolOffset0,
		BCTL_au16RomVelVolOffset1,
		BCTL_au16RomVelVolOffset2,
		BCTL_au16RomVelVolOffset3,
	},
	BCTL_nVelVolOffset_Len,
	BCTL_nVelVolOffsetOatTbl_Len,
};

static BCTL_tstTblAttr2D BCTL_stTblAttr2DSiOffset =
{
	BCTL_au16RomSiOffsetX,
	BCTL_au16RomSiOffsetOatTbl,
	{
		BCTL_au16RomSiOffsetY0,
		BCTL_au16RomSiOffsetY1,
		BCTL_au16RomSiOffsetY2,
		BCTL_au16RomSiOffsetY3,
	},
	BCTL_nSiOffset_Len,
	BCTL_nSiOffsetOatTbl_Len,
};

static BCTL_tstMainOut BCTL_stMainOut;

/*****************************************************************************
* FILE LOCAL FUNCTION DECLARE
*
* In this section declare
* - all file functions used internal of this module 
*****************************************************************************/
static void BCTL_vCalManualTrgVolF(BCTL_tstCalManualTrgVolIn *stCalManualTrgVolIn, BCTL_tstCalManualTrgVolOut *stCalManualTrgVolOut);	
static void BCTL_vCalDefTrgVolF(BCTL_tstCalDefTrgVolIn *stCalDefTrgVolIn, BCTL_tstCalDefTrgVolOut *stCalDefTrgVolOut);
static void BCTL_vCalOffTrgVolF(BCTL_tstMainBankOut *stCalOffTrgVolOut);
static void BCTL_vHandleIncDecF(BCTL_tstHandleIncDecIn *stHandleIncDecIn, BCTL_tstHandleIncDecOut *stHandleIncDecOut);
static void BCTL_vCalTrgVoltF(BCTL_tstCalTrgVoltIn *stCalTrgVoltIn, BCTL_tstCalTrgVoltOut *stCalTrgVoltOut);		
static void BCTL_vCalDisInfoF(BCTL_tstCalDisInfoIn *stCalDisInfoIn, BCTL_tstCalDisInfoOut *stCalDisInfoOut);	
static void BCTL_vCalVolLimitF(BCTL_tstCalVolLimitIn *stCalVolLimitIn, BCTL_tstCalVolLimitOut *stCalVolLimitOut);
static void BCTL_vCalAutoTrgVolF(BCTL_tstCalAutoTrgVolIn *stCalAutoTrgVolIn, BCTL_tstCalAutoTrgVolOut *stCalAutoTrgVolOut);	
static uint16 BCTL_u16Lookup2D_Limit(uint16 u16InputX, uint16 u16InputY, BCTL_tstTblAttr2D stTblAttr2D);
static uint16 BCTL_u16CalOatSetTempVolOffset(uint16 u16CcsSetTemp,uint16 u16OatVal);
static uint16 BCTL_u16CalSiVolOffset(uint16 u16Si,uint16 u16OatVal);
static uint16 BCTL_u16CalSunloadVolOffset(uint16 u16Sunload,uint16 u16OatVal);
static uint16 BCTL_u16CalVelVolOffset(uint16 u16Vel,uint16 u16OatVal);
static uint16 BCTL_u16CalIncDecOffset(uint16 u16Input,uint16 u16LastOuput, BCTL_tstTblAttr stTblAttr);
static uint16 BCTL_u16LookupTblForTrgVolt(uint16 u16TrgLevel);
static void BCTL_vForceBctlControl(void);
/* ===========================================================================
* Function   : void BCTL_u16CalBlowoutTempOffset (void)
* Description: Need to add description
* Takes      : Nothing
* Returns    : Nothing
*/

static void BCTL_vSetDefualtVolF(BCTL_tstMainOut *pstMainOut);

#if( BCTL_nUseCCP == True)
typedef enum
{
	Bctl_nSetCcsBlwTarget,
	Bctl_nSetBlwTarget,
	Bctl_nCcpForceMax
}CcpControl_Bctl;

static uint8 Bctl_CcpForceFlag=0;
static uint16 Bctl_CcpControlData[Bctl_nCcpForceMax];
#define BctlGetCcpForceBit(index)	((Bctl_CcpForceFlag>>index)&0x01)
#define BctlSetCcpForceBit(index)	(Bctl_CcpForceFlag=Bctl_CcpForceFlag|(0x01<<index))
#define BctlClrCcpForceBit(index)	(Bctl_CcpForceFlag=Bctl_CcpForceFlag&(~(0x01<<index)))
#define BctlClrCcpForceByte(void)	(Bctl_CcpForceFlag=0)
/*****************************************************************************
 Function      : BCTL_ForceIoControl_Write                                 
 Description   : Ccp control function
 Takes         : Nothing
 Return Value  : None                                                *
*****************************************************************************/
uint8 BCTL_u8ForceIoControl_Write(/*IN*/uint32 ForceIoControlWord)
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
				BctlClrCcpForceByte();
				break;
			case 1:
				BctlSetCcpForceBit(Bctl_nSetCcsBlwTarget);
				Bctl_CcpControlData[Bctl_nSetCcsBlwTarget]=CcpControlWord.CcpContronData;
				break;
			case 2:
				BctlClrCcpForceBit(Bctl_nSetCcsBlwTarget);
				Bctl_CcpControlData[Bctl_nSetCcsBlwTarget]=0;
				break;
			case 3:
				//BctlSetCcpForceBit(Bctl_nSetBlwTarget);
				//Bctl_CcpControlData[Bctl_nSetBlwTarget]=CcpControlWord.CcpContronData;
				BctlSetCcpForceBit(Bctl_nSetBlwTarget);
                if(CcpControlWord.CcpContronData < BCTL_nBlwVol2VltTbl_Len)
                {
                    Bctl_CcpControlData[Bctl_nSetBlwTarget] = BCTL_au16RomBlwVol2VltTblNorFreY[CcpControlWord.CcpContronData];
                }
                else
                {
				    Bctl_CcpControlData[Bctl_nSetBlwTarget]= CcpControlWord.CcpContronData;
                }
				break;
			case 4:
				BctlClrCcpForceBit(Bctl_nSetBlwTarget);
				Bctl_CcpControlData[Bctl_nSetBlwTarget]=0;
				break;
            case 0x82:
				//BctlSetCcpForceBit(Bctl_nSetBlwTarget);
				//Bctl_CcpControlData[Bctl_nSetBlwTarget]=CcpControlWord.CcpContronData;
				BctlSetCcpForceBit(Bctl_nSetBlwTarget);
                if(CcpControlWord.CcpContronData < BCTL_nBlwVol2VltTbl_Len)
                {
                    Bctl_CcpControlData[Bctl_nSetBlwTarget] = BCTL_au16RomBlwVol2VltTblNorFreY[CcpControlWord.CcpContronData];
                }
                else
                {
				    Bctl_CcpControlData[Bctl_nSetBlwTarget]= CcpControlWord.CcpContronData;
                }
            break;    
            case 0xA1:
				//BctlSetCcpForceBit(Bctl_nSetBlwTarget);
				//Bctl_CcpControlData[Bctl_nSetBlwTarget]=CcpControlWord.CcpContronData;
				BctlSetCcpForceBit(Bctl_nSetBlwTarget);
                if(CcpControlWord.CcpContronData < BCTL_nBlwVol2VltTbl_Len)
                {
                    Bctl_CcpControlData[Bctl_nSetBlwTarget] = BCTL_au16RomBlwVol2VltTblNorFreY[CcpControlWord.CcpContronData];
                }
                else
                {
				    Bctl_CcpControlData[Bctl_nSetBlwTarget]= CcpControlWord.CcpContronData;
                }
            break;    
            case 0xA2:
				BctlClrCcpForceBit(Bctl_nSetBlwTarget);
				Bctl_CcpControlData[Bctl_nSetBlwTarget]=0;
            case 0xA3:
				BctlSetCcpForceBit(Bctl_nSetBlwTarget);
                if(CcpControlWord.CcpContronData < BCTL_nBlwVol2VltTbl_Len)
                {
                    Bctl_CcpControlData[Bctl_nSetBlwTarget] = BCTL_au16RomBlwVol2VltTblNorFreY[CcpControlWord.CcpContronData];
                }
                else
                {
				    Bctl_CcpControlData[Bctl_nSetBlwTarget]= CcpControlWord.CcpContronData;
                }
            break;    
            case 0xA4:
				BctlClrCcpForceBit(Bctl_nSetBlwTarget);
				Bctl_CcpControlData[Bctl_nSetBlwTarget]=0;
             break;    
			default:
                return RTE_E_INVALID;
				//break;
		}
	}
	else
	{
		BctlClrCcpForceByte();
	}
        return RTE_E_OK;
}
#endif
/*****************************************************************************************/
static uint16 BCTL_u16Lookup2D_Limit(uint16 u16InputX, uint16 u16InputY, BCTL_tstTblAttr2D stTblAttr2D)
{
    uint16 u16Return = 0u;
    uint16 au16Table[2];

    if (u16InputY <= stTblAttr2D.pu16TableY[0])
    {	
        u16Return = ALG_cu16CurveLookup_16_16_Limit(stTblAttr2D.pu16TableX,stTblAttr2D.pu16TableZ[0],u16InputX,stTblAttr2D.nu8SizeX);
    }
    else if (u16InputY >= stTblAttr2D.pu16TableY[stTblAttr2D.nu8SizeY-1U])
    {	
        u16Return = ALG_cu16CurveLookup_16_16_Limit(stTblAttr2D.pu16TableX,stTblAttr2D.pu16TableZ[stTblAttr2D.nu8SizeY-1U],u16InputX,stTblAttr2D.nu8SizeX);
    }	
    else
    {
        uint8 u8Index;

        for (u8Index=1U; u8Index<stTblAttr2D.nu8SizeY; u8Index++)
        {
            if (u16InputY <= stTblAttr2D.pu16TableY[u8Index])
            {
                if (u16InputY < stTblAttr2D.pu16TableY[u8Index])
                {
                    au16Table[0] = ALG_cu16CurveLookup_16_16_Limit(stTblAttr2D.pu16TableX,stTblAttr2D.pu16TableZ[u8Index-1U],u16InputX,stTblAttr2D.nu8SizeX);
                    
                    au16Table[1] = ALG_cu16CurveLookup_16_16_Limit(stTblAttr2D.pu16TableX,stTblAttr2D.pu16TableZ[u8Index],u16InputX,stTblAttr2D.nu8SizeX);
                    
                    u16Return = ALG_cu16CurveLookup_16_16_Limit(&stTblAttr2D.pu16TableY[u8Index-1U], &au16Table[0],u16InputY,2U); 
                }
                else
                {
                    u16Return = ALG_cu16CurveLookup_16_16_Limit(stTblAttr2D.pu16TableX,stTblAttr2D.pu16TableZ[u8Index],u16InputX,stTblAttr2D.nu8SizeX);
                }
                break;		
            }
        }
    }

    return u16Return;
}



/* ===========================================================================
* Function   : static uint16 BCTL_u16CalIncDecOffset(uint16 u16Input,uint16 u16LastOuput, BCTL_tstTblAttr stTblAttr)
* Description: Need to add description
* Takes      : Nothing
* Returns    : Nothing
*/
static uint16 BCTL_u16CalIncDecOffset(uint16 u16Input,uint16 u16LastOuput, BCTL_tstTblAttr stTblAttr)
{
    uint16 u16OffsetDec, u16OffsetInc;
    uint16 u16Ret;

    u16OffsetInc = 
        ALG_cu16CurveLookup_16_16_Limit\
        (\
            stTblAttr.pu16TblAddrX,\
            stTblAttr.pu16TblAddrIncY,\
            u16Input,\
            stTblAttr.u8TblLen\
         );

    u16OffsetDec = 
        ALG_cu16CurveLookup_16_16_Limit\
        (\
            stTblAttr.pu16TblAddrX,\
            stTblAttr.pu16TblAddrDecY,\
            u16Input,\
            stTblAttr.u8TblLen\
         );
    
    switch(*(stTblAttr.ptrSlices))
    {

        case BCTL_nCalInc:
            if(u16OffsetDec <= u16LastOuput)
            {
                u16Ret = u16OffsetDec;
                *(stTblAttr.ptrSlices) = BCTL_nCalDec;
            }
            else if(u16OffsetInc >= u16LastOuput)
            {
                u16Ret = u16OffsetInc;
            }
	     else
  	     {
                u16Ret = u16LastOuput; 			
  	     }
            break;

        case BCTL_nCalDec:
            if(u16OffsetInc >= u16LastOuput)
            {
                u16Ret = u16OffsetInc;
                *(stTblAttr.ptrSlices) = BCTL_nCalInc;
            }
            else if(u16OffsetDec <= u16LastOuput)
            {
                u16Ret = u16OffsetDec;
            }			
            else
            {
                u16Ret = u16LastOuput;
            }
            break;

        default:
            *(stTblAttr.ptrSlices) = BCTL_nCalInc;
   
            break;               
    }

    return(u16Ret);
}

/* ===========================================================================
* Function   : uint16 BCTL_u16CalOatSetTempVolOffset (uint16 u16CcsSetTemp,uint16 u16OatVal)
* Description: Need to add description
* Takes      : Nothing
* Returns    : Nothing
*/
static uint16 BCTL_u16CalOatSetTempVolOffset(uint16 u16CcsSetTemp,uint16 u16OatVal)
{
    uint16 u16CcsOatDiff;
    uint16 u16Ret;

	u16CcsOatDiff = (5000U + u16OatVal) - u16CcsSetTemp;

    u16Ret = 
        ALG_cu16CurveLookup_16_16_Limit\
        (\
            BCTL_au16RomOatSetTempOffsetX,\
            BCTL_au16RomOatSetTempOffsetY,\
            u16CcsOatDiff,\
            BCTL_nOatSetTempOffset_Len\
         );

    return(u16Ret);
}


/* ===========================================================================
* Function   : static uint16	BCTL_u16CalSunloadVolOffset(uint16 u16Sunload,uint16 u16OatVal)
* Description: Need to add description
* Takes      : -->CcsSetTemp, -->OatValue
* Returns    : -->SunLoadOffset
*/
static uint16	BCTL_u16CalSunloadVolOffset(uint16 u16Sunload,uint16 u16OatVal)
{
	return(BCTL_u16Lookup2D_Limit(u16Sunload,u16OatVal,BCTL_stTblAttr2DSunOffset));
}

/* ===========================================================================
* Function   : static uint16	BCTL_u16CalVelVolOffset(uint16 u16Sunload,uint16 u16OatVal)
* Description: Need to add description
* Takes      : -->CcsSetTemp, -->OatValue
* Returns    : -->SunLoadOffset
*/
static uint16	BCTL_u16CalVelVolOffset(uint16 u16Vel,uint16 u16OatVal)
{
	return(BCTL_u16Lookup2D_Limit(u16Vel,u16OatVal,BCTL_stTblAttr2DVelOffset));
}

/* ===========================================================================
* Function   : static uint16	BCTL_u16CalSiVolOffset(uint16 u16Si,uint16 u16OatVal)
* Description: Need to add description
* Takes      : -->CcsSetTemp, -->OatValue
* Returns    : -->SiOffset
*/
static uint16	BCTL_u16CalSiVolOffset(uint16 u16Si,uint16 u16OatVal)
{
	return(BCTL_u16Lookup2D_Limit(u16Si,u16OatVal,BCTL_stTblAttr2DSiOffset));
}

static void BCTL_vSetDefualtVolF(BCTL_tstMainOut *pstMainOut)
{
    pstMainOut->CcsTrgVlt.Sts = BCTL_nInvalid;
    pstMainOut->CcsTrgVlt.Val = 0U;

    pstMainOut->CcsTrgVol.Sts = BCTL_nInvalid;
    pstMainOut->CcsTrgVol.Val = 0U; 


    pstMainOut->TrgVol.Sts = BCTL_nInvalid;
    pstMainOut->TrgVol.Val = 0U; 

    pstMainOut->TrgVlt.Sts = BCTL_nInvalid;
    pstMainOut->TrgVlt.Val = 0U; 

    pstMainOut->DisplayInfo.Sts = BCTL_nInvalid;
    pstMainOut->DisplayInfo.Val = 0x0U;     

    pstMainOut->OatCcsSetTempVolOffsetDr.Sts = BCTL_nInvalid;
    pstMainOut->OatCcsSetTempVolOffsetDr.Val = 0xFFFFU; 

    pstMainOut->OatCcsSetTempVolOffsetPs.Sts = BCTL_nInvalid;
    pstMainOut->OatCcsSetTempVolOffsetPs.Val = 0xFFFFU; 

    pstMainOut->SiVolOffsetDr.Sts = BCTL_nInvalid;
    pstMainOut->SiVolOffsetDr.Val = 0xFFFFU; 

    pstMainOut->SiVolOffsetPs.Sts = BCTL_nInvalid;
    pstMainOut->SiVolOffsetPs.Val = 0xFFFFU; 

    pstMainOut->SunVolOffset.Sts = BCTL_nInvalid;
    pstMainOut->SunVolOffset.Val = 0xFFFFU; 

    pstMainOut->VelVolOffset.Sts = BCTL_nInvalid;
    pstMainOut->VelVolOffset.Val = 0xFFFFU; 

    pstMainOut->WuCdVolLmt.Sts = BCTL_nInvalid;
    pstMainOut->WuCdVolLmt.Val = 0xFFFFU; 

    pstMainOut->OatVolLmt.Sts = BCTL_nInvalid;
    pstMainOut->OatVolLmt.Val = 0xFFFFU; 

}

static void BCTL_vCalAutoTrgVolF(BCTL_tstCalAutoTrgVolIn *stCalAutoTrgVolIn, BCTL_tstCalAutoTrgVolOut *stCalAutoTrgVolOut)
{
        int32 i32CcsTrgVolDr,i32TrgVolDr; 
#if (SYC_ZONES == 2)           
        int32 i32CcsTrgVolPs,i32TrgVolPs; 
        if((stCalAutoTrgVolIn->InCcsSetTempDr.Sts == BCTL_nInvalid)||(stCalAutoTrgVolIn->InOatValue.Sts == BCTL_nInvalid)||(stCalAutoTrgVolIn->InCcsTempDiffDr.Sts == BCTL_nInvalid)||    
        (stCalAutoTrgVolIn->InCcsSetTempPs.Sts == BCTL_nInvalid)||(stCalAutoTrgVolIn->InCcsTempDiffPs.Sts == BCTL_nInvalid))
#else
        if((stCalAutoTrgVolIn->InCcsSetTempDr.Sts == BCTL_nInvalid)||(stCalAutoTrgVolIn->InOatValue.Sts == BCTL_nInvalid)||(stCalAutoTrgVolIn->InCcsTempDiffDr.Sts == BCTL_nInvalid))
#endif
    {
        stCalAutoTrgVolOut->CcsTrgVol.Sts = BCTL_nInvalid;
        stCalAutoTrgVolOut->CcsTrgVol.Val = 0U; 

        stCalAutoTrgVolOut->TrgVol.Sts = BCTL_nInvalid;
        stCalAutoTrgVolOut->TrgVol.Val = 0U; 

        stCalAutoTrgVolOut->OatCcsSetTempVolOffsetDr.Sts = BCTL_nInvalid;
        stCalAutoTrgVolOut->OatCcsSetTempVolOffsetDr.Val = 0xFFFFU; 
#if (SYC_ZONES == 2)   
        stCalAutoTrgVolOut->OatCcsSetTempVolOffsetPs.Sts = BCTL_nInvalid;
        stCalAutoTrgVolOut->OatCcsSetTempVolOffsetPs.Val = 0xFFFFU; 

        stCalAutoTrgVolOut->SiVolOffsetPs.Sts = BCTL_nInvalid;
        stCalAutoTrgVolOut->SiVolOffsetPs.Val = 0xFFFFU; 
#endif        
        stCalAutoTrgVolOut->SiVolOffsetDr.Sts = BCTL_nInvalid;
        stCalAutoTrgVolOut->SiVolOffsetDr.Val = 0xFFFFU; 

        stCalAutoTrgVolOut->SunVolOffset.Sts = BCTL_nInvalid;
        stCalAutoTrgVolOut->SunVolOffset.Val = 0xFFFFU; 

        stCalAutoTrgVolOut->VelVolOffset.Sts = BCTL_nInvalid;
        stCalAutoTrgVolOut->VelVolOffset.Val = 0xFFFFU; 

    }
    else
    {
/***************************************************************************************************/        
        /* Calculate base volume.*/
        stCalAutoTrgVolOut->OatCcsSetTempVolOffsetDr.Val = BCTL_u16CalOatSetTempVolOffset(stCalAutoTrgVolIn->InCcsSetTempDr.Val, stCalAutoTrgVolIn->InIncomingValue.Val);
        stCalAutoTrgVolOut->OatCcsSetTempVolOffsetDr.Sts = BCTL_nValid;
#if (SYC_ZONES == 2)    
        stCalAutoTrgVolOut->OatCcsSetTempVolOffsetPs.Val = BCTL_u16CalOatSetTempVolOffset(stCalAutoTrgVolIn->InCcsSetTempPs.Val, stCalAutoTrgVolIn->InIncomingValue.Val);
        stCalAutoTrgVolOut->OatCcsSetTempVolOffsetPs.Sts = BCTL_nValid;
#endif
/***************************************************************************************************/
        /* Calculate feedback offset volume.*/
        stCalAutoTrgVolOut->SiVolOffsetDr.Val = BCTL_u16CalSiVolOffset(stCalAutoTrgVolIn->InCcsTempDiffDr.Val,stCalAutoTrgVolIn->InOatValue.Val);
        stCalAutoTrgVolOut->SiVolOffsetDr.Sts = BCTL_nValid;
#if (SYC_ZONES == 2)
        stCalAutoTrgVolOut->SiVolOffsetPs.Val = BCTL_u16CalSiVolOffset(stCalAutoTrgVolIn->InCcsTempDiffPs.Val,stCalAutoTrgVolIn->InOatValue.Val);
        stCalAutoTrgVolOut->SiVolOffsetPs.Sts = BCTL_nValid;
#endif
/***************************************************************************************************/
        /* Calculate sunload offset volume.*/
        if(stCalAutoTrgVolIn->InSunValue.Sts == BCTL_nInvalid)
        {
            stCalAutoTrgVolOut->SunVolOffset.Val = 1000U/*0*/;
            stCalAutoTrgVolOut->SunVolOffset.Sts = BCTL_nInvalid;
        }
        else
        {
            stCalAutoTrgVolOut->SunVolOffset.Val = BCTL_u16CalSunloadVolOffset(stCalAutoTrgVolIn->InSunValue.Val,stCalAutoTrgVolIn->InOatValue.Val);
            stCalAutoTrgVolOut->SunVolOffset.Sts = BCTL_nValid;
        }
/***************************************************************************************************/
        /* Calculate vel offset volume.*/
        if(stCalAutoTrgVolIn->InVelValue.Sts == BCTL_nInvalid)
        {
            stCalAutoTrgVolOut->VelVolOffset.Val = 1000U/*0*/;
            stCalAutoTrgVolOut->VelVolOffset.Sts = BCTL_nInvalid;
        }
        else
        {
            stCalAutoTrgVolOut->VelVolOffset.Val = BCTL_u16CalVelVolOffset(stCalAutoTrgVolIn->InVelValue.Val,stCalAutoTrgVolIn->InOatValue.Val);
            stCalAutoTrgVolOut->VelVolOffset.Sts = BCTL_nValid;
        }
/***************************************************************************************************/
        i32CcsTrgVolDr = stCalAutoTrgVolOut->OatCcsSetTempVolOffsetDr.Val + stCalAutoTrgVolOut->SunVolOffset.Val + stCalAutoTrgVolOut->VelVolOffset.Val - 2000U;
        i32TrgVolDr = i32CcsTrgVolDr + stCalAutoTrgVolOut->SiVolOffsetDr.Val;
        
        stCalAutoTrgVolOut->CcsTrgVol.Val = (uint16)RangeCheck(i32CcsTrgVolDr,0U,BCTL_au16RomManualVolTbl[BCTL_nManualVolTbl_Len-1u]);
        stCalAutoTrgVolOut->TrgVol.Val = (uint16)RangeCheck(i32TrgVolDr,0U,BCTL_au16RomManualVolTbl[BCTL_nManualVolTbl_Len-1u]);

/***************************************************************************************************/    
#if (SYC_ZONES == 2)
        i32CcsTrgVolPs = stCalAutoTrgVolOut->OatCcsSetTempVolOffsetPs.Val + stCalAutoTrgVolOut->SunVolOffset.Val + stCalAutoTrgVolOut->VelVolOffset.Val - 2000U;
        i32TrgVolPs = i32CcsTrgVolPs + stCalAutoTrgVolOut->SiVolOffsetPs.Val;
        
        i32CcsTrgVolPs = RangeCheck(i32CcsTrgVolPs,0U,BCTL_au16RomManualVolTbl[BCTL_nManualVolTbl_Len-1u]);
        i32TrgVolPs = RangeCheck(i32TrgVolPs,0U,BCTL_au16RomManualVolTbl[BCTL_nManualVolTbl_Len-1u]);

        stCalAutoTrgVolOut->CcsTrgVol.Val = (uint16)BCTL_vCalMax(i32CcsTrgVolDr,i32CcsTrgVolPs);
        stCalAutoTrgVolOut->TrgVol.Val = (uint16)BCTL_vCalMax(i32TrgVolDr,i32TrgVolPs);
#endif        
        stCalAutoTrgVolOut->CcsTrgVol.Sts = BCTL_nValid;
        stCalAutoTrgVolOut->TrgVol.Sts = BCTL_nValid;
    }
    
}

static void BCTL_vCalManualTrgVolF(BCTL_tstCalManualTrgVolIn *stCalManualTrgVolIn, BCTL_tstCalManualTrgVolOut *stCalManualTrgVolOut)
{
    if(stCalManualTrgVolIn->InMmiBlwCtrl.Sts !=BCTL_nInvalid)
    {
        stCalManualTrgVolOut->CcsTrgVol.Val = BCTL_au16RomManualVolTbl[stCalManualTrgVolIn->InMmiBlwCtrl.Val];
        stCalManualTrgVolOut->CcsTrgVol.Sts = BCTL_nValid;
        stCalManualTrgVolOut->TrgVol = stCalManualTrgVolOut->CcsTrgVol;
    }
    else
    {
        stCalManualTrgVolOut->CcsTrgVol.Val = 0u;
        stCalManualTrgVolOut->CcsTrgVol.Sts = BCTL_nInvalid;
        stCalManualTrgVolOut->TrgVol = stCalManualTrgVolOut->CcsTrgVol;        
    }

}

static void BCTL_vCalDefTrgVolF(BCTL_tstCalDefTrgVolIn *stCalDefTrgVolIn, BCTL_tstCalDefTrgVolOut *stCalDefTrgVolOut)
{
    if(stCalDefTrgVolIn->InMmiBlwCtrl.Sts !=BCTL_nInvalid)
    {
        stCalDefTrgVolOut->CcsTrgVol.Val = BCTL_au16RomManualVolTbl[stCalDefTrgVolIn->InMmiBlwCtrl.Val];
        stCalDefTrgVolOut->CcsTrgVol.Sts = BCTL_nValid;
        stCalDefTrgVolOut->TrgVol = stCalDefTrgVolOut->CcsTrgVol;
    }
    else
    {
        stCalDefTrgVolOut->CcsTrgVol.Val = 0u;
        stCalDefTrgVolOut->CcsTrgVol.Sts = BCTL_nInvalid;
        stCalDefTrgVolOut->TrgVol = stCalDefTrgVolOut->CcsTrgVol;        
    }

}

static void BCTL_vCalOffTrgVolF(BCTL_tstMainBankOut *stCalOffTrgVolOut)
{
    stCalOffTrgVolOut->CcsTrgVlt.Sts = BCTL_nValid;
    stCalOffTrgVolOut->CcsTrgVlt.Val = 0U;

    stCalOffTrgVolOut->CcsTrgVol.Sts = BCTL_nValid;
    stCalOffTrgVolOut->CcsTrgVol.Val = 0U; 


    stCalOffTrgVolOut->TrgVol.Sts = BCTL_nValid;
    stCalOffTrgVolOut->TrgVol.Val = 0U; 

    stCalOffTrgVolOut->TrgVlt.Sts = BCTL_nValid;
    stCalOffTrgVolOut->TrgVlt.Val = 0U; 

    stCalOffTrgVolOut->DisplayInfo.Sts = BCTL_nValid;
    stCalOffTrgVolOut->DisplayInfo.Val = 0x0U;     

}

static void BCTL_vHandleIncDecF(BCTL_tstHandleIncDecIn *stHandleIncDecIn, BCTL_tstHandleIncDecOut *stHandleIncDecOut)
{
    uint8 u8Step = 20U;
    uint8 u8IncDecFlag = False;

    if((stHandleIncDecIn->u8MmiBlwMode == BCTL_nMmiModeDef)
        || (stHandleIncDecIn->u8MmiBlwMode == BCTL_nMmiModeMaxAc)
      )
    {
        u8Step = 80U;
        u8IncDecFlag = True;
    }
    else if(stHandleIncDecIn->u8MmiBlwMode == BCTL_nMmiModeAuto)
    {
        u8Step = 20U;
        u8IncDecFlag = True;
    }
    else
    {
        u8IncDecFlag = False;
    }

    if(stHandleIncDecIn->u8MmiBlwMode == BCTL_nMmiModeOff)
    {
        *(stHandleIncDecOut->pu8Off2OnIncFlag) = 1U;
        *(stHandleIncDecOut->pu8Off2OnBlwLvlSet) = 0U;
        *(stHandleIncDecOut->pu16TrgVolLmt) = 0u;
        *(stHandleIncDecOut->pu8LastMmiBlwCtrl) = 0u;
    }
   else if(
        (*(stHandleIncDecOut->pu8Off2OnIncFlag) == 1U)
#if (BCTL_nAUTO_BLOWER_CONTROL != 0)    
        ||(u8IncDecFlag == True)
#endif        
      )
    
   {
        if(*(stHandleIncDecOut->pu8Off2OnIncFlag) == 1U)
        {
            if(*(stHandleIncDecOut->pu8Off2OnBlwLvlSet) == 0U)
            {
                *(stHandleIncDecOut->pu8Off2OnBlwLvlSet) = 1U;
                *(stHandleIncDecOut->pu8LastMmiBlwCtrl) = stHandleIncDecIn->u8MmiBlwCtrl;
            }
            else if((*(stHandleIncDecOut->pu8LastMmiBlwCtrl)) != (stHandleIncDecIn->u8MmiBlwCtrl))
            {
                *(stHandleIncDecOut->pu8Off2OnIncFlag) = 0U;
            }
            else
            {
                /* Nothing to do.*/
            }
        }
        else
        {
            /* Nothing to do.*/
        }
        
        if((*(stHandleIncDecOut->pu16TrgVolLmt) + u8Step) <= stHandleIncDecIn->u16TrgVol)
        {
            *(stHandleIncDecOut->pu16TrgVolLmt) += u8Step;
        }
        else if((*(stHandleIncDecOut->pu16TrgVolLmt)) > (stHandleIncDecIn->u16TrgVol + u8Step))
        {
            *(stHandleIncDecOut->pu16TrgVolLmt) -= u8Step;
        }
        else
        {
            *(stHandleIncDecOut->pu16TrgVolLmt) = stHandleIncDecIn->u16TrgVol;
            *(stHandleIncDecOut->pu8Off2OnIncFlag) = 0U;
        }                      

   }
   else
   {
        *(stHandleIncDecOut->pu16TrgVolLmt) = stHandleIncDecIn->u16TrgVol;
   }

}


/* ===========================================================================
* Function   : static uint16   BCTL_u16LookupTblForTrgVolt(uint16 u16TrgLevel)
* Description: Need to add description
* Takes      : Nothing
* Returns    : Nothing
*/
static uint16   BCTL_u16LookupTblForTrgVolt(uint16 u16TrgLevel)
{
    uint16 u16Res=0;
	uint8 u8Rfa=0;
	uint8 u8SysMode=0;

	u8SysMode = MMI_u8GetValue(MMI_nu8SysState);
	BCTL_enRfaDisInfoImport(&u8Rfa);
	if(u8SysMode == MMI_nSysStateAuto)
	{
	    if(u8Rfa==BCTL_nRecircFresh)
		{
			u16Res=ALG_cu16CurveLookup_16_16_Limit\
	               	(\
	                    BCTL_au16RomBlwVol2VltTblX,\
	                    BCTL_au16RomBlwVol2VltTblNorFreY,\
	                    u16TrgLevel,\
	                    BCTL_nBlwVol2VltTbl_Len\
	                 );
		}
		else
		{
			u16Res=ALG_cu16CurveLookup_16_16_Limit\
	               	(\
	                    BCTL_au16RomBlwVol2VltTblX,\
	                    BCTL_au16RomBlwVol2VltTblNorRecY,\
	                    u16TrgLevel,\
	                    BCTL_nBlwVol2VltTbl_Len\
	                 );
		}
	}
	else
	{
		u16Res=ALG_cu16CurveLookup_16_16_Limit\
               	(\
                    BCTL_au16RomBlwVol2VltTblX,\
                    BCTL_au16RomBlwVol2VltTblNorFreY,\
                    u16TrgLevel,\
                    BCTL_nBlwVol2VltTbl_Len\
                 );
	}
    /*
    return(
                ALG_cu16CurveLookup_16_16_Limit\
                (\
                    BCTL_au16RomBlwVol2VltTblX,\
                    BCTL_au16RomBlwVol2VltTblNorFreY,\
                    u16TrgLevel,\
                    BCTL_nBlwVol2VltTbl_Len\
                 )
         );
         */
    return u16Res;
}

static void BCTL_vCalTrgVoltF(BCTL_tstCalTrgVoltIn *stCalTrgVoltIn, BCTL_tstCalTrgVoltOut *stCalTrgVoltOut)
{
    stCalTrgVoltOut->TrgVolt.Sts = BCTL_nValid;
    stCalTrgVoltOut->TrgVolt.Val = BCTL_u16LookupTblForTrgVolt(stCalTrgVoltIn->u16TrgVol);
    stCalTrgVoltOut->CcsTrgVolt.Sts = BCTL_nValid;
    stCalTrgVoltOut->CcsTrgVolt.Val = BCTL_u16LookupTblForTrgVolt(stCalTrgVoltIn->u16CcsTrgVol);
}

static void BCTL_vCalDisInfoF(BCTL_tstCalDisInfoIn *stCalDisInfoIn, BCTL_tstCalDisInfoOut *stCalDisInfoOut)
{
    stCalDisInfoOut->DisInfo.Sts = BCTL_nValid;
    stCalDisInfoOut->DisInfo.Val = 
        (uint8 )BCTL_u16CalIncDecOffset(stCalDisInfoIn->u16TrgVol,(uint16)stCalDisInfoOut->DisInfo.Val,BCTL_stTblAttrDisInfo);
    if(stCalDisInfoOut->DisInfo.Val < 1u)
    {
        if(stCalDisInfoIn->u8MmiBlwMode == BCTL_nMmiModeOff)
        {
            stCalDisInfoOut->DisInfo.Val= 0u;
        }
        else
        {/*Added by Yang Shengli,avoid off to on display zero*/
            stCalDisInfoOut->DisInfo.Val= 1u;
        }
    }
}

static void BCTL_vCalVolLimitF(BCTL_tstCalVolLimitIn *stCalVolLimitIn, BCTL_tstCalVolLimitOut *stCalVolLimitOut)
{
    uint16 u16BlotTarget;
    uint16 u16BlotActual;
    int16 i16TempDiff;

    if((stCalVolLimitIn->InCcsBlowoutAvg.Sts == BCTL_nInvalid)||(stCalVolLimitIn->InMmiSetTempDr.Sts == BCTL_nInvalid)
        ||(stCalVolLimitIn->InHctValue.Sts == BCTL_nInvalid)||(stCalVolLimitIn->InOatValue.Sts == BCTL_nInvalid)
        ||(stCalVolLimitIn->InEvapValue.Sts == BCTL_nInvalid)
#if (SYC_ZONES == 2)          
        ||(stCalVolLimitIn->InMmiSetTempPs.Sts == BCTL_nInvalid)
#endif	    
       )
    {
        stCalVolLimitOut->OatVolLmt.Sts = BCTL_nInvalid;
        stCalVolLimitOut->OatVolLmt.Val = 0xFFFFU;

        stCalVolLimitOut->WuCdVolLmt.Sts = BCTL_nInvalid;
        stCalVolLimitOut->WuCdVolLmt.Val = 0xFFFFU;

        stCalVolLimitOut->VolLmt.Sts = BCTL_nInvalid;
        stCalVolLimitOut->VolLmt.Val = 0xFFFFU;        
    }
    else
    {     
        stCalVolLimitOut->VolLmt.Sts = BCTL_nValid;
        stCalVolLimitOut->OatVolLmt.Sts = BCTL_nValid;
        stCalVolLimitOut->WuCdVolLmt.Sts = BCTL_nValid;
        
#if (SYC_ZONES == 2)            
        if(((stCalVolLimitIn->InMmiSetTempDr.Val == 0U)&&(stCalVolLimitIn->InMmiSetTempPs.Val  >= 255U))||\
          ((stCalVolLimitIn->InMmiSetTempDr.Val >= 255U)&&(stCalVolLimitIn->InMmiSetTempPs.Val == 0U)))
#else
        if((stCalVolLimitIn->InMmiSetTempDr.Val == 0U)||(stCalVolLimitIn->InMmiSetTempDr.Val  >= 255U))
#endif
        {
            stCalVolLimitOut->VolLmt.Val = BCTL_au16RomManualVolTbl[BCTL_nManualVolTbl_Len -1U];
            stCalVolLimitOut->WuCdVolLmt.Val = BCTL_au16RomManualVolTbl[BCTL_nManualVolTbl_Len -1U];
            stCalVolLimitOut->OatVolLmt.Val = BCTL_au16RomManualVolTbl[BCTL_nManualVolTbl_Len -1U];
        }
        else
        {
        	u16BlotTarget = stCalVolLimitIn->InCcsBlowoutAvg.Val;
            
            if(((int32)u16BlotTarget - stCalVolLimitIn->InEvapValue.Val) <0)
            {
                u16BlotActual = stCalVolLimitIn->InEvapValue.Val;
            }
            else if(((int32)u16BlotTarget - (int32)stCalVolLimitIn->InHctValue.Val) >0)
            {
                u16BlotActual = stCalVolLimitIn->InHctValue.Val;
            }
            else
            {
                u16BlotActual = u16BlotTarget;
            }
        	u16BlotTarget = RangeCheck(u16BlotTarget, BCTL_nLimitTempMin, BCTL_nLimitTempMax);
        	u16BlotActual = RangeCheck(u16BlotActual, BCTL_nLimitTempMin, BCTL_nLimitTempMax);
            
        	//i16TempDiff = (int16)u16BlotTarget - (int16)u16BlotActual + 640U;
        	i16TempDiff = (int16)u16BlotTarget - (int16)u16BlotActual + 5000U;/*170108*/
        	//i16TempDiff = RangeCheck(i16TempDiff, 0, 1280);
        	i16TempDiff = RangeCheck(i16TempDiff, BCTL_nLimitTempMin, BCTL_nLimitTempMax);/*170108*/

            if(BCTL_u16TrgVolLmtTimer < 50u)/*5 second limit,added by YSL at mohe,20180316*/
            {
                BCTL_u16TrgVolLmtTimer++;
                stCalVolLimitOut->WuCdVolLmt.Val = BCTL_au16RomWuCdVolLimit[BCTL_nWuCdVolLimit_Len - 1u];
            }
            else
            {
            	stCalVolLimitOut->WuCdVolLmt.Val = 
                   ALG_cu16CurveLookup_16_16_Limit\
                    (\
                        BCTL_au16RomBoTempTgAtDiff,\
                        BCTL_au16RomWuCdVolLimit,\
                        (uint16)i16TempDiff,\
                        BCTL_nWuCdVolLimit_Len\
                     );
            }
             stCalVolLimitOut->OatVolLmt.Val=  \
                ALG_cu16CurveLookup_16_16_Limit\
                (\
                    BCTL_au16RomAmbient,\
                    BCTL_au16RomOatBlwLimit,\
                    stCalVolLimitIn->InOatValue.Val,\
                    BCTL_nOatBlwLimit_Len\
                 );
            stCalVolLimitOut->VolLmt.Val = BCTL_vCalMin(stCalVolLimitOut->OatVolLmt.Val,stCalVolLimitOut->WuCdVolLmt.Val);
        }
    }

}


/* ===========================================================================
* Function   : void BCTL_vMain (void)
* Description: Main function of the mixed air temperature control. This
*              function is called in the cyclic background task in the ON
*              state.
* Takes      : Nothing
* Returns    : Nothing
*/
void BCTL_vMain (void)
{
    BCTL_tstU8InOutType stU8InIgnEn, stU8InPowerFail,stU8InMmiBlwMode,stU8InMmiBlwCtrl;

    BCTL_tstCalDefTrgVolIn stCalDefTrgVolIn;
    BCTL_tstCalDefTrgVolOut stCalDefTrgVolOut;

    BCTL_tstCalManualTrgVolIn stCalManualTrgVolIn;
    BCTL_tstCalManualTrgVolOut stCalManualTrgVolOut;

    BCTL_tstCalAutoTrgVolIn stCalAutoTrgVolIn;
    BCTL_tstCalAutoTrgVolOut stCalAutoTrgVolOut;

    BCTL_tstCalVolLimitIn stCalVolLimitIn;
    BCTL_tstCalVolLimitOut stCalVolLimitOut;

    BCTL_tstHandleIncDecIn stHandleIncDecIn;
    BCTL_tstHandleIncDecOut stHandleIncDecOut;

    BCTL_tstCalTrgVoltIn stCalTrgVoltIn;
    BCTL_tstCalTrgVoltOut stCalTrgVoltOut;

    BCTL_tstCalDisInfoIn stCalDisInfoIn;
    BCTL_tstCalDisInfoOut stCalDisInfoOut;


    stU8InMmiBlwCtrl.Sts = BCTL_enMmiBlwCtrlImport(&stU8InMmiBlwCtrl.Val);
    stU8InMmiBlwMode.Sts = BCTL_enMmiBlwModeImport(&stU8InMmiBlwMode.Val);
    stU8InIgnEn.Sts = BCTL_enIgnEnableSigImport(&stU8InIgnEn.Val);
    stU8InPowerFail.Sts = BCTL_enPowFailureImport(&stU8InPowerFail.Val);

    if((stU8InIgnEn.Sts == BCTL_nInvalid)||(stU8InPowerFail.Sts == BCTL_nInvalid)||
    (stU8InMmiBlwMode.Sts == BCTL_nInvalid)||(stU8InMmiBlwCtrl.Sts == BCTL_nInvalid)||
    (stU8InPowerFail.Val == True))
    {
        BCTL_vSetDefualtVolF(&BCTL_stMainOut);
        BCTL_u8Off2OnIncFlag= 1u;
        BCTL_u16TrgVolLmt = 0u;
        BCTL_u8LastMmiBlwCtrl = 0u;
        BCTL_u8Off2OnBlwLvlSet = 0u;
    }
    else
    {
        if( (stU8InIgnEn.Val== 1U)&&(stU8InPowerFail.Val == 0U) )
        {
            switch(stU8InMmiBlwMode.Val)
            {
                case BCTL_nMmiModeManual:  
#if (BCTL_nMAX_AC_CONTROL != 0)                
                case BCTL_nMmiModeMaxAc:     
#endif                  
                    stCalManualTrgVolIn.InMmiBlwCtrl = stU8InMmiBlwCtrl;
                    BCTL_vCalManualTrgVolF(&stCalManualTrgVolIn,&stCalManualTrgVolOut);
                    BCTL_stMainOut.CcsTrgVlt = stCalManualTrgVolOut.CcsTrgVol;
                    BCTL_stMainOut.TrgVol = stCalManualTrgVolOut.TrgVol; 
                break;

#if (BCTL_nAUTO_BLOWER_CONTROL != 0)
                case BCTL_nMmiModeAuto: 
                    stCalAutoTrgVolIn.InCcsSetTempDr.Sts = BCTL_enCcsSetTempDrImport(&stCalAutoTrgVolIn.InCcsSetTempDr.Val);
                    stCalAutoTrgVolIn.InCcsSetTempPs.Sts = BCTL_enCcsSetTempPsImport(&stCalAutoTrgVolIn.InCcsSetTempPs.Val);
                    stCalAutoTrgVolIn.InCcsTempDiffDr.Sts= BCTL_enCcsSiDrImport(&stCalAutoTrgVolIn.InCcsTempDiffDr.Val);
                    stCalAutoTrgVolIn.InCcsTempDiffPs.Sts= BCTL_enCcsSiPsImport(&stCalAutoTrgVolIn.InCcsTempDiffPs.Val);
                    stCalAutoTrgVolIn.InOatValue.Sts = BCTL_enOatValImport(&stCalAutoTrgVolIn.InOatValue.Val);
                    stCalAutoTrgVolIn.InIncomingValue.Sts = BCTL_enIncomingHeatImport(&stCalAutoTrgVolIn.InIncomingValue.Val);
                    stCalAutoTrgVolIn.InSunValue.Sts = BCTL_enSunVarImport(&stCalAutoTrgVolIn.InSunValue.Val);
                    stCalAutoTrgVolIn.InVelValue.Sts = BCTL_enVelVarImport(&stCalAutoTrgVolIn.InVelValue.Val);
                    BCTL_vCalAutoTrgVolF(&stCalAutoTrgVolIn,&stCalAutoTrgVolOut);      
                    BCTL_stMainOut.OatCcsSetTempVolOffsetDr = stCalAutoTrgVolOut.OatCcsSetTempVolOffsetDr;
                    BCTL_stMainOut.OatCcsSetTempVolOffsetPs = stCalAutoTrgVolOut.OatCcsSetTempVolOffsetPs;
                    BCTL_stMainOut.SiVolOffsetDr = stCalAutoTrgVolOut.SiVolOffsetDr;
                    BCTL_stMainOut.SiVolOffsetPs = stCalAutoTrgVolOut.SiVolOffsetPs;
                    BCTL_stMainOut.SunVolOffset = stCalAutoTrgVolOut.SunVolOffset;
                    BCTL_stMainOut.VelVolOffset = stCalAutoTrgVolOut.VelVolOffset;    
                    BCTL_stMainOut.CcsTrgVol = stCalAutoTrgVolOut.CcsTrgVol;
                    BCTL_stMainOut.TrgVol = stCalAutoTrgVolOut.TrgVol;                

                    stCalVolLimitIn.InCcsBlowoutAvg.Sts = BCTL_enCcsBlowoutAvgImport(&stCalVolLimitIn.InCcsBlowoutAvg.Val);
                    stCalVolLimitIn.InMmiSetTempDr.Sts = BCTL_enMmiSetTempDrImport(&stCalVolLimitIn.InMmiSetTempDr.Val);
                    stCalVolLimitIn.InMmiSetTempPs.Sts = BCTL_enMmiSetTempPsImport(&stCalVolLimitIn.InMmiSetTempPs.Val);
                    stCalVolLimitIn.InEvapValue.Sts = BCTL_enEvapVarImport(&stCalVolLimitIn.InEvapValue.Val);
                    stCalVolLimitIn.InHctValue.Sts = BCTL_enHctVarImport(&stCalVolLimitIn.InHctValue.Val);
                    stCalVolLimitIn.InOatValue = stCalAutoTrgVolIn.InOatValue;
                    BCTL_vCalVolLimitF(&stCalVolLimitIn, &stCalVolLimitOut);
                    BCTL_stMainOut.OatVolLmt = stCalVolLimitOut.OatVolLmt;
                    BCTL_stMainOut.WuCdVolLmt = stCalVolLimitOut.WuCdVolLmt;
                    BCTL_stMainOut.VolLmt = stCalVolLimitOut.VolLmt;
                    
                    if((BCTL_stMainOut.VolLmt.Val < BCTL_stMainOut.TrgVol.Val)&&(BCTL_stMainOut.VolLmt.Sts != BCTL_nInvalid))
                    {
                        BCTL_stMainOut.TrgVol.Val = BCTL_stMainOut.VolLmt.Val;
                    }
                    else
                    {

                    }
           
                break; 
#endif 
                case BCTL_nMmiModeDef:   
                    stCalDefTrgVolIn.InMmiBlwCtrl = stU8InMmiBlwCtrl;
                    BCTL_vCalDefTrgVolF(&stCalDefTrgVolIn,&stCalDefTrgVolOut);
                    BCTL_stMainOut.CcsTrgVlt = stCalDefTrgVolOut.CcsTrgVol;
                    BCTL_stMainOut.TrgVol = stCalDefTrgVolOut.TrgVol; 
                break;

                case BCTL_nMmiModeOff:
                    BCTL_vCalOffTrgVolF(&BCTL_stMainOut);
                    BCTL_u8Off2OnIncFlag= 1u;
                    BCTL_u16TrgVolLmt = 0u;
                    BCTL_u8LastMmiBlwCtrl = 0u;
                    BCTL_u8Off2OnBlwLvlSet = 0u;                    
                break;

                default:
                    BCTL_vCalOffTrgVolF(&BCTL_stMainOut);
                    BCTL_u8Off2OnIncFlag= 1u;
                    BCTL_u16TrgVolLmt = 0u;
                    BCTL_u8LastMmiBlwCtrl = 0u;
                    BCTL_u8Off2OnBlwLvlSet = 0u;
                break;
            }     
            stHandleIncDecIn.u16TrgVol = BCTL_stMainOut.TrgVol.Val;
            stHandleIncDecIn.u8MmiBlwCtrl = stU8InMmiBlwCtrl.Val;
            stHandleIncDecIn.u8MmiBlwMode = stU8InMmiBlwMode.Val;
            stHandleIncDecOut.pu16TrgVolLmt = &BCTL_u16TrgVolLmt;
            stHandleIncDecOut.pu8LastMmiBlwCtrl = &BCTL_u8LastMmiBlwCtrl;
            stHandleIncDecOut.pu8Off2OnBlwLvlSet = &BCTL_u8Off2OnBlwLvlSet;
            stHandleIncDecOut.pu8Off2OnIncFlag = &BCTL_u8Off2OnIncFlag;
            BCTL_vHandleIncDecF(&stHandleIncDecIn, &stHandleIncDecOut);
            BCTL_stMainOut.TrgVol.Val = BCTL_u16TrgVolLmt;

            stCalTrgVoltIn.u16TrgVol = BCTL_stMainOut.TrgVol.Val;
            stCalTrgVoltIn.u16CcsTrgVol = BCTL_stMainOut.CcsTrgVol.Val;
            BCTL_vCalTrgVoltF(&stCalTrgVoltIn, &stCalTrgVoltOut);
            BCTL_stMainOut.TrgVlt = stCalTrgVoltOut.TrgVolt;
            BCTL_stMainOut.CcsTrgVlt = stCalTrgVoltOut.CcsTrgVolt;
            
            //BCTL_vForceBctlControl();
            
            stCalDisInfoIn.u16TrgVol = BCTL_stMainOut.TrgVol.Val;
            stCalDisInfoIn.u8MmiBlwCtrl = stU8InMmiBlwCtrl.Val;
            stCalDisInfoIn.u8MmiBlwMode = stU8InMmiBlwMode.Val;
            stCalDisInfoOut.DisInfo.Val= BCTL_stMainOut.DisplayInfo.Val;
            BCTL_vCalDisInfoF(&stCalDisInfoIn, &stCalDisInfoOut);
            BCTL_stMainOut.DisplayInfo.Val = stCalDisInfoOut.DisInfo.Val;
            BCTL_stMainOut.DisplayInfo.Sts = stCalDisInfoOut.DisInfo.Sts;

            BCTL_vForceBctlControl();
        }
        else
        {
            BCTL_u8Off2OnIncFlag= 1u;
            BCTL_u16TrgVolLmt = 0u;
            BCTL_u8LastMmiBlwCtrl = 0u;
            BCTL_u8Off2OnBlwLvlSet = 0u;
        }
    } 
    BCTL_vOutputUpdate();

}

/* ===========================================================================
* Function   : void BCTL_vReset (void)
* Description: Reset function of the mixed air temperature control. This
*              function is called in the RESET container of the operating
*              system.
* Takes      : Nothing
* Returns    : Nothing
*/
void BCTL_vReset (void)
{
 
}

/* ===========================================================================
* Function   : void BCTL_vInit (void)
* Description: Init function of the mixed air temperature control. This
*              function is called in the INIT container of the operating
*              system.
* Takes      : Nothing
* Returns    : Nothing
*/
void BCTL_vInit (void)
{
    BCTL_u8Off2OnIncFlag= 1u;
    BCTL_u16TrgVolLmt = 0u;
    BCTL_u8LastMmiBlwCtrl = 0u;
    BCTL_u8Off2OnBlwLvlSet = 0u;
    BCTL_u16TrgVolLmtTimer = 0u;
    BCTL_vSetDefualtVolF(&BCTL_stMainOut);
}

/* ===========================================================================
* Function   : void BCTL_vDeinit (void)
* Description: De-Init function of the mixed air temperature control. This
*              function is called in the DEINIT container of the operating
*              system.
* Takes      : Nothing
* Returns    : Nothing
*/
void BCTL_vDeinit (void)
{
    BCTL_vSetDefualtVolF(&BCTL_stMainOut);
    BCTL_u16TrgVolLmtTimer = 0u;
}



/*****************************************************************************
 AUTHOR:		 : Li Jiaye											  *
 DATE: 		 : 2015/07/22										  *
 Function      : Bctl_vActive                                                   *
 Description   : 
 Return Value  : None                                                        *
*****************************************************************************/
void BCTL_vActive(void)
{
    
}


/*****************************************************************************
* Function      : uint8 BCTL_u8GetValue( BCTL_tenu8VarNumber enIndex )                                            
* Description   : The extern model get the uint8 type variable value from this
*				     model,                                                      
* Takes  :    enIndex   - the index number.                                          
* Returns   : uint8   - the wanted value                                                 
*****************************************************************************/
uint8 BCTL_u8GetValue( BCTL_tenu8VarNumber enIndex )
{
    uint8 u8Ret;
    
        switch(enIndex)
        {
            case BCTL_nu8DisplayInfo:
                if(BCTL_stMainOut.DisplayInfo.Sts == BCTL_nInvalid)
                {
                    u8Ret= 0U;
                }
                else
                {
                    u8Ret = BCTL_stMainOut.DisplayInfo.Val;
                }
                break;
                
            default:
                u8Ret = 0U;
                break;
        }   
  return u8Ret;
}


/*****************************************************************************
* Function      : uint16 BCTL_u16GetValue( BCTL_tenu16VarNumber enIndex )                                              
* Description   : The extern model get the uint8 type variable value from this
*				     model,                                                      
* Takes  :    enIndex   - the index number.                                          
* Returns   : uint8   - the wanted value   
*****************************************************************************/
uint16 BCTL_u16GetValue( BCTL_tenu16VarNumber enIndex )
{
    uint16 u16Ret;

    switch(enIndex)
    {
        case BCTL_nu16OatCcsSetTempVolOffsetDr: 
                if(BCTL_stMainOut.OatCcsSetTempVolOffsetDr.Sts == BCTL_nInvalid)
                {
                    u16Ret= 0xFFFFU;
                }
                else
                {
                    u16Ret = BCTL_stMainOut.OatCcsSetTempVolOffsetDr.Val;
                }
            break;
        case BCTL_nu16OatCcsSetTempVolOffsetPs: 
                if(BCTL_stMainOut.OatCcsSetTempVolOffsetPs.Sts == BCTL_nInvalid)
                {
                    u16Ret= 0xFFFFU;
                }
                else
                {
                    u16Ret = BCTL_stMainOut.OatCcsSetTempVolOffsetPs.Val;
                }
            break;
        case BCTL_nu16SiVolOffsetDr: 
                if(BCTL_stMainOut.SiVolOffsetDr.Sts == BCTL_nInvalid)
                {
                    u16Ret= 0xFFFFU;
                }
                else
                {
                    u16Ret = BCTL_stMainOut.SiVolOffsetDr.Val;
                }
            break;
        case BCTL_nu16SiVolOffsetPs: 
                if(BCTL_stMainOut.SiVolOffsetPs.Sts == BCTL_nInvalid)
                {
                    u16Ret= 0xFFFFU;
                }
                else
                {
                    u16Ret = BCTL_stMainOut.SiVolOffsetPs.Val;
                }
            break;
        case BCTL_nu16SunVolOffset: 
                if(BCTL_stMainOut.SunVolOffset.Sts == BCTL_nInvalid)
                {
                    u16Ret= 0xFFFFU;
                }
                else
                {
                    u16Ret = BCTL_stMainOut.SunVolOffset.Val;
                }
            break;
        case BCTL_nu16VelVolOffset: 
                if(BCTL_stMainOut.VelVolOffset.Sts == BCTL_nInvalid)
                {
                    u16Ret= 0xFFFFU;
                }
                else
                {
                    u16Ret = BCTL_stMainOut.VelVolOffset.Val;
                }
            break;
        case BCTL_nu16CcsTrgVol: 
                if(BCTL_stMainOut.CcsTrgVol.Sts == BCTL_nInvalid)
                {
                    u16Ret= 0U;
                }
                else
                {
                    u16Ret = BCTL_stMainOut.CcsTrgVol.Val;
                }
            break;
        case BCTL_nu16TrgVol: 
                if(BCTL_stMainOut.TrgVol.Sts == BCTL_nInvalid)
                {
                    u16Ret= 0U;
                }
                else
                {
                    u16Ret = BCTL_stMainOut.TrgVol.Val;
                }
            break;
        case BCTL_nu16WuCdVolLmt: 
                if(BCTL_stMainOut.WuCdVolLmt.Sts == BCTL_nInvalid)
                {
                    u16Ret= 0xFFFFU;
                }
                else
                {
                    u16Ret = BCTL_stMainOut.WuCdVolLmt.Val;
                }
            break;
        case BCTL_nu16OatVolLmt: 
                if(BCTL_stMainOut.OatVolLmt.Sts == BCTL_nInvalid)
                {
                    u16Ret= 0xFFFFU;
                }
                else
                {
                    u16Ret = BCTL_stMainOut.OatVolLmt.Val;
                }
            break;
        case BCTL_nu16VolLmt: 
                if(BCTL_stMainOut.VolLmt.Sts == BCTL_nInvalid)
                {
                    u16Ret= 0xFFFFU;
                }
                else
                {
                    u16Ret = BCTL_stMainOut.VolLmt.Val;
                }
            break;
        case BCTL_nu16CcsTrgVlt: 
                if(BCTL_stMainOut.CcsTrgVlt.Sts == BCTL_nInvalid)
                {
                    u16Ret= 0U;
                }
                else
                {
                    u16Ret = BCTL_stMainOut.CcsTrgVlt.Val;
                }
            break;
        case BCTL_nu16TrgVlt: 
                if(BCTL_stMainOut.TrgVlt.Sts == BCTL_nInvalid)
                {
                    u16Ret= 0U;
                }
                else
                {
                    u16Ret = BCTL_stMainOut.TrgVlt.Val;
                }
            break;
        case BCTL_nu16SwVer:
        /* Software version. */
                u16Ret= 0x0101U;
            break;

    }
    return u16Ret;
}


/*******************************************************************************
*Function : BCTL_tenValueSts BCTL_enGetStMainOutExport(BCTL_tstMainOut *value)
*Description : export the target position
*takes :  Motor index
*return: 0:invalid  1:valid 2:default   3:last valid
*/
BCTL_tenValueSts BCTL_enGetStMainOutExport(BCTL_tstMainOut *value)
{
  *value = BCTL_stMainOut;
  return BCTL_nInvalid;
}

/*******************************************************************************
*Function : static void BCTL_vForceBctlControl(void)
*Description : export the target position
*takes :  Motor index
*return: none
*/
static void BCTL_vForceBctlControl(void)
{
    uint8 u8i;
    
#if( BCTL_nUseCCP == True)
    if(BctlGetCcpForceBit(Bctl_nSetCcsBlwTarget))
    {
        BCTL_stMainOut.CcsTrgVlt.Val = Bctl_CcpControlData[Bctl_nSetCcsBlwTarget];
    }
    
    if(BctlGetCcpForceBit(Bctl_nSetBlwTarget))
    {
        BCTL_stMainOut.TrgVlt.Val = Bctl_CcpControlData[Bctl_nSetBlwTarget];
        for(u8i=1u;u8i<BCTL_nManualVolTbl_Len;u8i++)
        {
            if(Bctl_CcpControlData[Bctl_nSetBlwTarget] <= BCTL_au16RomBlwVol2VltTblNorFreY[u8i])
            {
                break;
            }
        }
        BCTL_stMainOut.DisplayInfo.Val=u8i;
    }
#endif  
}

/*****************************************************************************
* EOF:Bctl.c
******************************************************************************/


