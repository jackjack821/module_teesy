/**************************** .FILE_HEADER_BEGIN *****************************
  .TITLE  [EED                                      ]
*-----------------------------------------------------------------------------
  .FILE   [ EED.c                                                         ]
  .AUTHOR [  Tan Fumin				                                     ]
*-----------------------------------------------------------------------------
 Version Date        		Author                       
Change                      
 -----------------------------------------------------------------------------
 Rev 00.00.00 2014/12/12    Tan Fumin      			 The first version  
 Rev 02       2015/06/01    Zhang Shuncong            add groupID info,update flow                                               update Telltales process
*****************************************************************************/

#define EED                         /* name of the module                */

/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
*****************************************************************************/
/* System-headerfiles */
#include "General.h"
/* foreign headerfiles */
#include "Rte_Iohweep.h"


/*Local variable definition*/
#include "EED_Cfg.h"
#include "EED_Type.h"
#include "EED_Private.h"
#include "EED.h"

EED_tstLayout EED_stLayout;
static uint8    EED_au8Array[EED_nu8Max];
//static uint8    EED_au8TempBuffer[EED_u16BufferSize];
static uint32   EED_au32ValidAddr[EED_nu8GroupMax];
static uint32 EED_u32FlsErasedAddr;
static uint32 EED_u32UsingEepSize,EED_u32UsigFlsSize;
static EED_stEEPFLOW EED_stFlowEEP;
static EED_stFLSFLOW EED_stFlowFLS;

#pragma alignvar(4)
static uint8    EED_au8TempBuffer[EED_u16BufferSize]; /*must be 32 bit aligned,160809*/

#if EED_DataFlashType == FUJITSU_16BIT
EED_tstGroup EED_axGroup[EED_nu8GroupMax] =
{
	/*  Group ID, Group Length, Group Start Addr,Group End Addr   */
    {EED_nu8GroupMMI,True,EED_u16GroupSizeMMI,SECTOR_SA1_Start,SECTOR_SA2_End},
    {EED_nu8GroupPTS,False,EED_u16GroupSizePTS,SECTOR_SA3_Start,SECTOR_SA3_End},
};
#endif

#if EED_DataFlashType == NEC_32BIT
EED_tstGroup EED_axGroup[EED_nu8GroupMax] =
{
	/*  Group ID, Group Length, Group Start Addr,Group End Addr   */
	{EED_enGroupID_1,True,EED_u16GroupSizeMMI,SECTOR_SA8_Start,SECTOR_SA8_End},
    {EED_nu8GroupMMI,True,EED_u16GroupSizeMMI,SECTOR_SA1_Start,SECTOR_SA2_End},
    {EED_nu8GroupOAT,True,EED_u16GroupSizeOAT,SECTOR_SA9_Start,SECTOR_SA9_End},
    {EED_nu8GroupDIAG,True,EED_u16GroupSizeDIAG,SECTOR_SA10_Start,SECTOR_SA10_End},
    {EED_nu8GroupDTC,True,EED_u16GroupSizeDTC,SECTOR_SA11_Start,SECTOR_SA11_End},
    {EED_nu8GroupFP,False,EED_u16GroupSizePTS,SECTOR_SA12_Start,SECTOR_SA12_End},
	{EED_nu8GroupPTS,False,EED_u16GroupSizePTS,SECTOR_SA16_Start,SECTOR_SA16_End},
	{EED_enGroupID_8,True,EED_u16GroupSizeMMI,SECTOR_SA14_Start,SECTOR_SA14_End},
};
#endif

static   EED_tstBlockInfo  EED_axBlockTable[EED_TotalGroupNum]=
{
#if EED_TotalGroupNum>=1
	EED_GroupInf(1),
#endif
#if EED_TotalGroupNum>=2
	EED_GroupInf(2),
#endif
#if EED_TotalGroupNum>=3
	EED_GroupInf(3),
#endif
#if EED_TotalGroupNum>=4
	EED_GroupInf(4),
#endif
#if EED_TotalGroupNum>=5
	EED_GroupInf(5),
#endif
#if EED_TotalGroupNum>=6
	EED_GroupInf(6),
#endif
#if EED_TotalGroupNum>=7
	EED_GroupInf(7),
#endif
#if EED_TotalGroupNum>=8
	EED_GroupInf(8),
#endif
#if EED_TotalGroupNum>=9
	EED_GroupInf(9),
#endif
#if EED_TotalGroupNum>=10
	EED_GroupInf(10),
#endif
#if EED_TotalGroupNum>=11
	EED_GroupInf(11),
#endif
#if EED_TotalGroupNum>=12
	EED_GroupInf(12),
#endif
#if EED_TotalGroupNum>=13
	EED_GroupInf(13),
#endif
#if EED_TotalGroupNum>=14
	EED_GroupInf(14),
#endif
#if EED_TotalGroupNum>=15
	EED_GroupInf(15),
#endif
#if EED_TotalGroupNum>=16
	EED_GroupInf(16),
#endif
#if EED_TotalGroupNum>=17
	EED_GroupInf(17),
#endif
#if EED_TotalGroupNum>=18
	EED_GroupInf(18),
#endif
#if EED_TotalGroupNum>=19
	EED_GroupInf(19),
#endif
#if EED_TotalGroupNum>=20
	EED_GroupInf(20),
#endif
#if EED_TotalGroupNum>=21
	EED_GroupInf(21),
#endif
#if EED_TotalGroupNum>=22
	EED_GroupInf(22),
#endif
#if EED_TotalGroupNum>=23
	EED_GroupInf(23),
#endif
#if EED_TotalGroupNum>=24
	EED_GroupInf(24),
#endif
#if EED_TotalGroupNum>=25
	EED_GroupInf(25),
#endif
#if EED_TotalGroupNum>=26
	EED_GroupInf(26),
#endif
#if EED_TotalGroupNum>=27
	EED_GroupInf(27),
#endif
#if EED_TotalGroupNum>=28
	EED_GroupInf(28),
#endif
#if EED_TotalGroupNum>=29
	EED_GroupInf(29),
#endif
#if EED_TotalGroupNum>=30
	EED_GroupInf(30),
#endif
#if EED_TotalGroupNum>=31
	EED_GroupInf(31),
#endif
#if EED_TotalGroupNum>=32
	EED_GroupInf(32),
#endif
#if EED_TotalGroupNum>=33
	#error "Can Not suport so many group data!!!"
#endif

};

static uint8 EED_u8CheckGroupLen (uint8 u8GroupID, uint16 u16Length);
static uint8 EED_u8CalAddCS (uint8 au8Buffer[], uint16 u16Length);
static uint8 EED_u8CalXorCS (uint8 au8Buffer[], uint16 u16Length);
static uint8 EED_u8CheckFinalData(uint8 au8BufferX[],uint16 u16Length);
static uint8 EED_u8CheckChecksum(uint8 au8BufferX[],uint16 u16Length);
static void  EED_vLimitValidAddr(uint8 u8GroupID,uint16 u16Length);
static void  EED_vErrorStateSetBit(uint8 u8Number); 
static void  EED_vErrorStateClrBit(uint8 u8Number);
static void  EED_vFlsHardWareUpdate(uint8 u8GroupID);
static void EED_vFlsEraseFlow(void);
static void EED_vSetFLSFlow(void *FromRam, void *ToFls,uint16 u16Size,uint16 u16EraseSize);
static void EED_vCalcCS(void const *vpDataHead, uint16 u16DataLegth,uint8 *AddRes, uint8 *XorRes);


/*****************************************************************************
 Function      : EED_u8GetValue                                              
 Description   : The extern model get the uint8 type variable value from this model   
 Return Value  : uint8 value                                                 
*****************************************************************************/
uint8 EED_u8GetValue( EED_tenu8VarNum enIndex )
{
    uint8 u8Value;
	if ( enIndex < EED_nu8Max )
	{
		u8Value = EED_au8Array[enIndex];
	}
	else
	{
		u8Value = EED_au8Array[EED_nu8Max-1U];
	}
    return u8Value;
}

/*****************************************************************************
 Function      : EED_u8GetValue                                              
 Description   : The extern model get the uint8 type variable value from this model   
 Return Value  : uint8 value                                                 
*****************************************************************************/
void EED_vReset(void)
{   
 	uint8 u8i=0U;
    uint8 u8TryCnt=0U;
    uint8 u8Result=0U;
  
    EED_au8Array[EED_nu8ErrorCode] = 0x00U; /*Clear error code*/
    EED_au8Array[EED_nu8SwVersion] = 0xA6U; /*change according to Version header ,160812*/

	for (u8i=0U;u8i<EED_nu8GroupMax;u8i++)
	{
	    EED_au32ValidAddr[u8i] = 0U;
    }
#if EED_DataFlashType == NEC_32BIT

     EED_u8Init();
#endif

#if EED_DataFlashType == FUJITSU_16BIT
    for (u8TryCnt=0U;u8TryCnt<=EED_u8MaxTryCnt;u8TryCnt++)
    {
        u8Result = EED_u8Init();

        if (u8Result == EED_ERR_NULL)
        {
            EED_vErrorStateClrBit(EED_nBit0);
            u8TryCnt = EED_u8MaxTryCnt;
        }
        else
        {
            EED_vErrorStateSetBit(EED_nBit0);
        }
    }
#endif
}

/*****************************************************************************
 Function      : EED_u8GetValue                                              
 Description   : The extern model get the uint8 type variable value from this model   
 Return Value  : uint8 value                                                 
*****************************************************************************/
//#if 0
void EED_vMain(void)
{
    /*nothing to do*/
}
//#endif

/*****************************************************************************
 Function      : EED_u8ReadGroupData                                              
 Description   : The extern interface:Read group data  
 Return Value  : uint8 value 
                 0----Write OK and driver working on
                 1----Write Fail
                 10----invalid Group ID
                 11----invalid Group Length
                 12----invalid Group Checksum
*****************************************************************************/
uint8 EED_u8ReadGroupData(uint8 u8GroupID,uint8 au8DataBuffer[], uint16 u16Length)
{
	uint8 u8ReadResult,u8Temp,u8TryCnt,u8Result,u8i;
	uint16 u16GroupSize;
    uint32 u32ReadingAddr,u32ValidAddr;

	if (u8GroupID < EED_nu8GroupMax)
    {
        u8Temp = EED_u8CheckGroupLen(u8GroupID,u16Length);

        if (u8Temp == True)
        {
            if (EED_axGroup[u8GroupID].u8CheckSumCfg == True)
            {
                #if EED_ApplLength_Enable == False
                u16GroupSize = u16Length+2U;/*If cs cal,add 2 bytes*/
                #else
                u16GroupSize = EED_axGroup[u8GroupID].u16Length;
                #endif
            }
            else
            {
                #if EED_ApplLength_Enable == False
                u16GroupSize = u16Length;
                #else
                u16GroupSize = EED_axGroup[u8GroupID].u16Length;
                #endif
            }
            
        	for(u32ReadingAddr = EED_axGroup[u8GroupID].u32StartAddr;u32ReadingAddr<EED_axGroup[u8GroupID].u32EndAddr;u32ReadingAddr+=u16GroupSize)
        	{
    	        for (u8TryCnt=0U;u8TryCnt<=EED_u8MaxTryCnt;u8TryCnt++)
    	        {
                    u8Result = EED_u8ReadData(u32ReadingAddr,EED_au8TempBuffer,u16GroupSize);
                    
      	            //#if EED_DataFlashType == NEC_32BIT  
                    /*If no data writed, return ECC error,150617*/
                    if ((u8Result == EED_FDL_ERR_BLANKCHECK)\
                        ||(u8Result == EED_FDL_ERR_ECC_SED)\
                        ||(u8Result == EED_FDL_ERR_ECC_DED))
                    {
                        u8TryCnt = EED_u8MaxTryCnt;
                        #if EED_ApplLength_Enable == False
                        u8Result = EED_u8CheckFinalData(EED_au8TempBuffer,u16Length);
                        #else
                        u8Result = EED_u8CheckFinalData(EED_au8TempBuffer,u16GroupSize-2);
                        #endif
                        
                        #if EED_DataFlashType == NEC_32BIT
                        u8Result = True; /*no need to check FinalData,150617*/
                        #endif
                        
                        if (u8Result == True)
                        {  
							EED_au32ValidAddr[u8GroupID] = u32ReadingAddr;/*for mext group,160524*/
                            u32ValidAddr = u32ReadingAddr - u16GroupSize;/*Read the forward group*/
                            if (u32ValidAddr < EED_axGroup[u8GroupID].u32StartAddr)/*Lower than start addr */
                            {
                                u32ValidAddr = EED_axGroup[u8GroupID].u32StartAddr;
                            }
                            else if (u32ValidAddr > EED_axGroup[u8GroupID].u32EndAddr)/*higher than start addr */
                            {
                                u32ValidAddr = EED_axGroup[u8GroupID].u32EndAddr;
                            }
                            else
                            {
                                /*nothing to do*/
                            }
                            
                            u8Result = EED_u8ReadData(u32ValidAddr,EED_au8TempBuffer,u16GroupSize);
                            
                            if (EED_axGroup[u8GroupID].u8CheckSumCfg == True)
                            {
                                u8Result = EED_u8CheckChecksum(EED_au8TempBuffer,u16GroupSize);
                                if (u8Result == True)
                                {
                                    u8TryCnt = EED_u8MaxTryCnt;
                                    //EED_au32ValidAddr[u8GroupID] = u32ReadingAddr;
                                    u8ReadResult = EED_ERR_NULL;
                                    
                                    /*copy the array,with out checksum*/
									#if 0
                                    for (u8i=0U;u8i<u16Length;u8i++)
                                    {
                                        au8DataBuffer[u8i] = EED_au8TempBuffer[u8i];
                                    } 
									#endif
									memcpy(au8DataBuffer,EED_au8TempBuffer,u16Length);/*USE mencoy.160523*/
                                    u32ReadingAddr = EED_axGroup[u8GroupID].u32EndAddr;/*jump out the for cycle*/
                                }
                                else
                                {
                                    u8ReadResult = EED_ErrorInvalidChecksum;
                                    u8TryCnt = EED_u8MaxTryCnt;
                                    u32ReadingAddr = EED_axGroup[u8GroupID].u32EndAddr;/*jump out the for cycle*/
                                }
                            }
                            else    
                            {   /*No need to check checksum*/                                  
                                /*copy the array,with out checksum*/
								#if 0
                                for (u8i=0U;u8i<u16Length;u8i++)
                                {
                                    au8DataBuffer[u8i] = EED_au8TempBuffer[u8i];
                                }  
								#endif
								memcpy(au8DataBuffer,EED_au8TempBuffer,u16Length);/*USE mencoy.160523*/
                                u8ReadResult = EED_ERR_NULL;
                                u32ReadingAddr = EED_axGroup[u8GroupID].u32EndAddr;/*jump out the for cycle*/                         
                            }
                        }
                        else
                        {   /*Not the final data,keep checking next group*/   
                            u8ReadResult = EED_Error;
							EED_au32ValidAddr[u8GroupID] = EED_axGroup[u8GroupID].u32EndAddr;/*for next write,160524*/
                        }
                    }
                    else
                    {   /*Read data error*/
                        u8ReadResult = EED_Error;
                    }
                }
    	        
            }            
            
        }
        else
        {   /*Group length  error*/
            u8ReadResult = EED_ErrorInvalidGroupLen;    
        }
    }
    else
    {   /*Group ID error*/
        u8ReadResult = EED_ErrorInvalidGroupID;
    }
    
	return u8ReadResult;

}

/*****************************************************************************
 Function      : EED_u8WriteGroupData                                              
 Description   : The extern interface:write group data    
 Return Value  : uint8 value
                 0----Write OK and driver working on
                 1----Write Fail
                 10----invalid Group ID
                 11----invalid Group Length
                 12----invalid Group Checksum
*****************************************************************************/
uint8 EED_u8WriteGroupData(uint8 u8GroupID,uint8 au8DataBuffer[], uint16 u16Length)
{
	uint8 u8WriteResult,u8Temp,u8TryCnt,u8Result,u8i;
	uint16 u16GroupSize=0U; 
	if (u8GroupID < EED_nu8GroupMax)
    {
        u8Temp = EED_u8CheckGroupLen(u8GroupID,u16Length);

        if (u8Temp == True)
        {
            /*copy the array*/
			memcpy(EED_au8TempBuffer,au8DataBuffer,u16Length);/*USE mencoy.160523*/
			#if 0
            for (u8i=0U;u8i<u16Length;u8i++)
            {
               EED_au8TempBuffer[u8i] = au8DataBuffer[u8i];
            }
            #if EED_ApplLength_Enable == True
            /*fill the rest data with 00,150618*/
            if (u16Length < EED_axGroup[u8GroupID].u16Length)
            {
                for (u8i=u16Length;u8i<EED_axGroup[u8GroupID].u16Length;u8i++)
                {
                    EED_au8TempBuffer[u8i] = 0U;
                }
            }
            #endif
            #endif
            if (EED_axGroup[u8GroupID].u8CheckSumCfg == True)
            {
                #if EED_ApplLength_Enable == False
                u16GroupSize = u16Length+2U;/*If cs cal,add 2 bytes*/
                #else
                u16GroupSize = EED_axGroup[u8GroupID].u16Length;
                #endif

                EED_au8TempBuffer[u16GroupSize-2U] = EED_u8CalAddCS(EED_au8TempBuffer,u16GroupSize-2);
                EED_au8TempBuffer[u16GroupSize-1U] = EED_u8CalXorCS(EED_au8TempBuffer,u16GroupSize-2);
            }
            else
            {
                #if EED_ApplLength_Enable == False
                u16GroupSize = u16Length;
                #else
                u16GroupSize = EED_axGroup[u8GroupID].u16Length;
                #endif
            }
            
            #if EED_ApplLength_Enable == False
            EED_vLimitValidAddr(u8GroupID,u16Length);
            #else
            EED_vLimitValidAddr(u8GroupID,u16GroupSize);
            #endif 
            
            for (u8TryCnt=0U;u8TryCnt<=EED_u8MaxTryCnt;u8TryCnt++)
            {
                u8Result = EED_u8WriteData(EED_au32ValidAddr[u8GroupID],EED_au8TempBuffer,u16GroupSize);

                if (u8Result == EED_ERR_NULL)
                {
                    u8Result = EED_u8ReadData(EED_au32ValidAddr[u8GroupID],EED_au8TempBuffer,u16GroupSize);
                    
                    if (u8Result == EED_ERR_NULL)
                    {
                        if (EED_axGroup[u8GroupID].u8CheckSumCfg == True)
                        {
                            u8Result = EED_u8CheckChecksum(EED_au8TempBuffer,u16GroupSize);
                            if (u8Result == True)   /*checksum right*/
                            {
                                u8TryCnt = EED_u8MaxTryCnt;
                                EED_au32ValidAddr[u8GroupID] += u16GroupSize;
                                u8WriteResult = EED_ERR_NULL;                               
                            }
                            else
                            {
                                /*write next data*/
                                u8WriteResult = EED_ErrorInvalidChecksum;
                                EED_au32ValidAddr[u8GroupID] += u16GroupSize;
                            }
                        }
                        else
                        {
                            u8TryCnt = EED_u8MaxTryCnt;
                            EED_au32ValidAddr[u8GroupID] += u16GroupSize;
                            u8WriteResult = EED_ERR_NULL;
                        }
                    }
                    else
                    {
                        u8WriteResult = EED_Error;
                    }
                }
                else
                {
                    u8WriteResult = EED_Error;
                }
            }
            
        }
        else
        {   /*Group length error*/
            u8WriteResult = EED_ErrorInvalidGroupLen;    
        }
    }
    else
    {   /*Group ID error*/
        u8WriteResult = EED_ErrorInvalidGroupID;
    }
	return u8WriteResult;

}


/*****************************************************************************
 Function      : EED_u8CheckGroupLen                                              
 Description   : The internal interface: check group length valid or not  
 Return Value  : uint8 value                                                 
*****************************************************************************/
static uint8 EED_u8CheckGroupLen (uint8 u8GroupID, uint16 u16Length)
{
  	uint8 u8Resault=0U;
	uint16 u16GroupLen=0u;
	if (u8GroupID < EED_nu8GroupMax)
    {
		if (EED_axGroup[u8GroupID].u8CheckSumCfg == True)
		{
			u16GroupLen = EED_axGroup[u8GroupID].u16Length-2u; /*add CheckSumCfg,160809*/
		}
		else
		{
			u16GroupLen = EED_axGroup[u8GroupID].u16Length;
		}
		
        #if EED_ApplLength_Enable == False
        if (u16GroupLen == u16Length)
        #else
        if (u16GroupLen >= u16Length) /*allow less than length,150618*/
        #endif
        {
            u8Resault = True; 
        }
        else
        {
            u8Resault = False;
        }
    }
    else
    {
        u8Resault = False;
    }  

    #if (EED_CheckLength_Enable == False)
    {
       u8Resault = True; 
    }
    #endif
    
    return u8Resault;
}

/*****************************************************************************
 Function      : EED_u8CalAddCS                                              
 Description   : The internal interface:calculate add checksum  
 Return Value  : uint8 value                                                 
*****************************************************************************/
static uint8 EED_u8CalAddCS (uint8 au8Buffer[], uint16 u16Length)
{
    uint8 u8CheckSum =0U;
  	uint16 u16i=0U;
	
	for(u16i=0U;u16i<u16Length;u16i++)
	{
        u8CheckSum += au8Buffer[u16i];
    }

    u8CheckSum = ~u8CheckSum; /* ADD chksum = inverted ADD chksum */

    return u8CheckSum;
}

/*****************************************************************************
 Function      : EED_u8CalXorCS                                              
 Description   : The internal interface:calculate xor checksum    
 Return Value  : uint8 value                                                 
*****************************************************************************/
static uint8 EED_u8CalXorCS (uint8 au8Buffer[], uint16 u16Length)
{
    uint8 u8CheckSum =0U;
  	uint16 u16i=0U;
	
	for(u16i=0U;u16i<u16Length;u16i++)
	{
        u8CheckSum ^= au8Buffer[u16i];
    }

    u8CheckSum = u8CheckSum+1U; /* XOR chksum = XOR chksum + 1*/

    return u8CheckSum;
}

/*****************************************************************************
 Function      : EED_u8CheckFinalData                                              
 Description   : The internal interface:check if final data or not 
 Return Value  : uint8 value                                                 
*****************************************************************************/
static uint8 EED_u8CheckFinalData(uint8 au8BufferX[],uint16 u16Length)
{
    uint8 u8Result=0U;
	uint16 u16Sum=0U,u16i=0U;

	for(u16i=0U;u16i<u16Length;u16i++)
	{
		u16Sum += au8BufferX[u16i];
	}

	if(u16Sum == (((uint32)u16Length << 8)- u16Length))
	{
		u8Result = True;
	}
    else
    {   /*au8BufferX is not all 0xFF*/
        u8Result = False;
    }
	return u8Result;
}


/*****************************************************************************
 Function      : EED_u8CheckChecksum                                              
 Description   : The internal interface:check check sum  
 Return Value  : uint8 value                                                 
*****************************************************************************/
static uint8 EED_u8CheckChecksum(uint8 au8BufferX[],uint16 u16Length)
{
    uint8 u8Result=0U;
    uint8 u8XorChkSum,u8AddChkSum;
    
    u8XorChkSum = EED_u8CalXorCS(au8BufferX,u16Length-2U);
    u8AddChkSum = EED_u8CalAddCS(au8BufferX,u16Length-2U);

    if ((au8BufferX[u16Length-2U] == u8AddChkSum)\
        &&(au8BufferX[u16Length-1U] == u8XorChkSum))
    {
        u8Result = True;
    }
    else
    {
        u8Result = False;
    }
    return u8Result;
}

/*****************************************************************************
 Function      : EED_vLimitValidAddr                                              
 Description   : The internal interface:check valid address   
 Return Value  : void                                                 
*****************************************************************************/
static void  EED_vLimitValidAddr(uint8 u8GroupID,uint16 u16Length)
{
    uint8 u8TryCnt,u8Temp;
    uint32 u32CodeFlashAddr,u32EndFlashAddr;
	//if (u8GroupID == EED_nu8GroupDTC) //160719
	//{
		EED_au32ValidAddr[u8GroupID] = 	EED_axGroup[u8GroupID].u32StartAddr - u16Length;//160308
	//}
    /*Lower than start addr  or higher than end addr*/
    if ((EED_au32ValidAddr[u8GroupID] < EED_axGroup[u8GroupID].u32StartAddr) /*add =,0224*/
        ||((EED_au32ValidAddr[u8GroupID]+ u16Length) > EED_axGroup[u8GroupID].u32EndAddr)) 
    {        
    	//for(u32CodeFlashAddr = EED_axGroup[u8GroupID].u32StartAddr;u32CodeFlashAddr <= EED_axGroup[u8GroupID].u32EndAddr; u32CodeFlashAddr+=EED_CFBlockSize)
		u32EndFlashAddr = EED_axGroup[u8GroupID].u32StartAddr+EED_axGroup[u8GroupID].u16Length;
		for(u32CodeFlashAddr = EED_axGroup[u8GroupID].u32StartAddr;u32CodeFlashAddr <= u32EndFlashAddr; u32CodeFlashAddr+=EED_CFBlockSize)//160719
		{
    	   for (u8TryCnt=0U;u8TryCnt< EED_u8MaxTryCnt;u8TryCnt++)
           {
                #if EED_DataFlashType == FUJITSU_16BIT
                u8Temp = CFD_u8SectorErase(u32CodeFlashAddr);
                #endif

                #if EED_DataFlashType == NEC_32BIT
                u8Temp = FLS_u8EraseWait(u32CodeFlashAddr,EED_CFBlockSize);
                #endif
                if (u8Temp == EED_ERR_NULL)
                {
                    u8TryCnt = EED_u8MaxTryCnt;
                }
                else
                {
                    /*nothing to do*/
                }
           
           }
        }          
         EED_au32ValidAddr[u8GroupID] = EED_axGroup[u8GroupID].u32StartAddr;/*re-start from start addr*/
    }
    else
    {
        /*nothing to do*/
    }  
}

/*****************************************************************************
 Function      : EED_vErrorStateSetBit                                              
 Description   : The internal interface:set error code bit  
 Return Value  : uint8 value                                                 
*****************************************************************************/
static void  EED_vErrorStateSetBit(uint8 u8Number)
{
    uint8 u8Value = 1U;
    EED_au8Array[EED_nu8ErrorCode] |= (u8Value << u8Number);
}

/*****************************************************************************
 Function      : EED_vErrorStateClrBit                                              
 Description   : The internal interface:set error code bit 
 Return Value  : uint8 value                                                 
*****************************************************************************/
static void  EED_vErrorStateClrBit(uint8 u8Number)
{
    uint8 u8Value = 1U;
    EED_au8Array[EED_nu8ErrorCode] &= ~(u8Value << u8Number);
}

/*****************************************************************************
 Function  : EED_u8WriteDataWait												 
 Description   : write data into EEPROM, para list:
 
 			 u32EepAddress: the EEPROM absolute address
 			 au8DataBuffer: head of the data store in the RAM which will be write into EEPROM
 			 u16Length: how many bytes write to EEPROM
 			 
 NOTE: NULL
 Return Value  : 0 is OK and driver working on
                 1----Write Fail
                 4----Invalid para
*****************************************************************************/
uint8 EED_u8WriteDataWait(uint32 u32EepAddress, uint8 au8DataBuffer[], uint16 u16Length)
{
    uint8 u8WriteResult,u8TryCnt,u8Result;
    uint8 u8Temp,u8Index;
    uint32 u32CodeFlashAddr=SECTOR_All_Start; 
	uint32 u32EndFlashAddr=SECTOR_All_Start;
    uint16 u16Offset;
    /*check address and length limit*/  
    if ((u32EepAddress < SECTOR_All_Start)||((u32EepAddress+u16Length) > SECTOR_All_End)
        ||(u16Length > (uint16)EED_u16BufferSize))
    {
        u8WriteResult = EED_ErrorInvalidParameter;
    }
    else
    {
        /*write for PTS*/
        if ((u32EepAddress >= EED_axGroup[EED_nu8GroupPTS].u32StartAddr)
            &&((u32EepAddress+u16Length) <= EED_axGroup[EED_nu8GroupPTS].u32EndAddr)
            &&(u16Length <= EED_u16GroupSizePTS))
        {
            u32CodeFlashAddr = EED_axGroup[EED_nu8GroupPTS].u32StartAddr;
            for (u8TryCnt=0U;u8TryCnt < EED_u8MaxTryCnt;u8TryCnt++)
            {
                /*step 1: read out 64Byte Pts flash data*/
                u8Result = EED_u8ReadData(u32CodeFlashAddr,EED_au8TempBuffer,EED_u16GroupSizePTS);

                //if (u8Result == EED_ERR_NULL) 160720
                //{                   
                    /*step 2: erase the pts block */
                    #if EED_DataFlashType == FUJITSU_16BIT
                    u8Temp = CFD_u8SectorErase(u32CodeFlashAddr);
                    #endif

                    #if EED_DataFlashType == NEC_32BIT
                    u8Temp = FLS_u8EraseWait(u32CodeFlashAddr,EED_CFBlockSize);
                    #endif

                    /*step 3: update the written data */
                    u16Offset = u32EepAddress - u32CodeFlashAddr;

                    for (u8Index=0u;u8Index<u16Length;u8Index++)
                    {
                       EED_au8TempBuffer[u16Offset+u8Index] = au8DataBuffer[u8Index];
                    }
                    
                    /*step 3: write data into data flash*/
                    for (u8TryCnt=0U;u8TryCnt < EED_u8MaxTryCnt;u8TryCnt++)
                    {
                        u8Result = EED_u8WriteData(u32CodeFlashAddr,EED_au8TempBuffer,EED_u16GroupSizePTS);

                        if (u8Result == EED_ERR_NULL)
                        {
                            u8TryCnt = EED_u8MaxTryCnt;
                            u8WriteResult = EED_ERR_NULL;
                        }
                        else
                        {
                            u8WriteResult = EED_Error;
                        }
                    }
                /*}
                else
                {
                    u8WriteResult = EED_Error;
                }*/
            }
        }
		else
		{
			/*step 1: erase the pts block */
			u32EndFlashAddr = ((uint32)(u16Length/EED_CFBlockSize+1))*EED_CFBlockSize+u32EepAddress;/*160809,160830*/
			for(u32CodeFlashAddr = u32EepAddress;u32CodeFlashAddr <= u32EndFlashAddr; u32CodeFlashAddr+=EED_CFBlockSize)
			{
	    	   for (u8TryCnt=0U;u8TryCnt< EED_u8MaxTryCnt;u8TryCnt++)
	           {
	                #if EED_DataFlashType == FUJITSU_16BIT
	                u8Temp = CFD_u8SectorErase(u32CodeFlashAddr);
	                #endif

	                #if EED_DataFlashType == NEC_32BIT
	                u8Temp = FLS_u8EraseWait(u32CodeFlashAddr,EED_CFBlockSize);
	                #endif
	                if (u8Temp == EED_ERR_NULL)
	                {
	                    u8TryCnt = EED_u8MaxTryCnt;
	                }
	                else
	                {
	                    /*nothing to do*/
	                }
	           
	           }
	        } 	

			/*step 2: write data into data flash*/
            for (u8TryCnt=0U;u8TryCnt < EED_u8MaxTryCnt;u8TryCnt++)
            {
                u8Result = EED_u8WriteData(u32EepAddress,au8DataBuffer,u16Length); /*use u32EepAddress,160809*/

                if (u8Result == EED_ERR_NULL)
                {
                    u8TryCnt = EED_u8MaxTryCnt;
                    u8WriteResult = EED_ERR_NULL;
                }
                else
                {
                    u8WriteResult = EED_Error;
                }
            }
		}
        
    }
    return u8WriteResult;
}

/*****************************************************************************
 Function  : EED_u8ReadDataWait												 
 Description   : write data into EEPROM, para list:
 
 			 u32EepAddress: the EEPROM absolute address
 			 au8DataBuffer: head of the data store in the RAM which will be read from EEPROM
 			 u16Length: how many bytes read from  EEPROM
 			 
 NOTE: NULL
 Return Value  : 0 is OK and driver working on
                 1----Read Fail
                 4----Invalid para
*****************************************************************************/
uint8 EED_u8ReadDataWait(uint32 u32EepAddress, uint8 au8DataBuffer[], uint16 u16Length)
{
    uint8 u8ReadResult,u8TryCnt,u8Result,u8Index;
     uint32 u32CodeFlashAddr=SECTOR_All_Start;
	  uint16 u16Offset;
    /*check address and length limit*/ 
    if ((u32EepAddress < SECTOR_All_Start)||((u32EepAddress+u16Length) > SECTOR_All_End)
        ||(u16Length > (uint16)EED_u16BufferSize))
    {
        u8ReadResult = EED_ErrorInvalidParameter;
    }
    else
    {
		/*read for PTS,160812*/
        if ((u32EepAddress >= EED_axGroup[EED_nu8GroupPTS].u32StartAddr)
            &&((u32EepAddress+u16Length) <= EED_axGroup[EED_nu8GroupPTS].u32EndAddr)
            &&(u16Length <= EED_u16GroupSizePTS))
        {
            u32CodeFlashAddr = EED_axGroup[EED_nu8GroupPTS].u32StartAddr;
            for (u8TryCnt=0U;u8TryCnt < EED_u8MaxTryCnt;u8TryCnt++)
            {
                /*step 1: read out 64Byte Pts flash data*/
                u8Result = EED_u8ReadData(u32CodeFlashAddr,EED_au8TempBuffer,EED_u16GroupSizePTS);

				if (u8Result == EED_ERR_NULL)
	            {
	                u8TryCnt = EED_u8MaxTryCnt;
	                u8ReadResult = EED_ERR_NULL;
	            }
	            else
	            {
	                u8ReadResult = EED_Error;
	            }
				
                /*step 3: update the written data */
                u16Offset = u32EepAddress - u32CodeFlashAddr;
				
				memcpy(au8DataBuffer,&EED_au8TempBuffer[u16Offset],u16Length);/*USE mencoy.160812*/
            }
        }
		else
		{
	        for (u8TryCnt=0U;u8TryCnt < EED_u8MaxTryCnt;u8TryCnt++)
	        {
	            //u8Result = EED_u8ReadData(u32EepAddress,au8DataBuffer,u16Length);/*read buff must be 32bit aligh,160806*/
	            u8Result = EED_u8ReadData(u32EepAddress,EED_au8TempBuffer,u16Length);
				memcpy(au8DataBuffer,EED_au8TempBuffer,u16Length);/*USE mencoy.160805*/
				
	            if (u8Result == EED_ERR_NULL)
	            {
	                u8TryCnt = EED_u8MaxTryCnt;
	                u8ReadResult = EED_ERR_NULL;
	            }
	            else
	            {
	                u8ReadResult = EED_Error;
	            }
	        }
		}
    }
    return u8ReadResult;
}


Std_ReturnType Eed_u8ReadGroupData(/*IN*/EedData portDefArg1, /*OUT*/EedData * EedData, /*IN*/EedDataLen EedDataLen)
{
    //return EED_u8ReadGroupData(portDefArg1-1, EedData, EedDataLen);
	#ifdef EED_UseFlowCheck
	return EED_u8ReadGroupData(portDefArg1, EedData, EedDataLen);
	#else
	return EED_u8ReadGroupData(portDefArg1-1, EedData, EedDataLen);
	#endif
}


Std_ReturnType Eed_u8WriteGroupData(/*IN*/EedData portDefArg1, /*OUT*/EedData * EedData, /*IN*/EedDataLen EepDataLen)
{
    //return EED_u8WriteGroupData(portDefArg1-1, EedData, EepDataLen);
	#ifdef EED_UseFlowCheck
	return EED_u8WriteGroupDataFlow(portDefArg1, EedData, EepDataLen);
	#else
	return EED_u8WriteGroupData(portDefArg1-1, EedData, EepDataLen);
	#endif
}


uint8 EED_u8WriteGroupDataFlow(uint8 u8GroupID,uint8 au8DataBuffer[], uint16 u16Length)
{
	uint8 u8WriteResult,u8Temp;
	uint16 u16WriteSize=0U,u16EraseSize=0U; 
	EED_tstBlockInfo * pBlockInf=EED_GroupInfoHead(0);
	void *From=NULL,*To=NULL;
	uint8 *XORcs=NULL,*ADDcs=NULL;
	
	if (u8GroupID < EED_TotalGroupNum)
    {
        u8Temp = EED_u8CheckGroupLen(u8GroupID,u16Length);
		
        if (u8Temp == True)
        {
            /*load group data head*/
			pBlockInf=EED_GroupInfoHead(u8GroupID);

			/*handle the ram and fls address*/
			From=pBlockInf->pvGroupRAMHead;
			To=(void *)EED_axGroup[u8GroupID].u32StartAddr;
			u16WriteSize=pBlockInf->u16GroupSize;
			
			/*copy the data to eed ram address*/
			memcpy(From,au8DataBuffer,u16Length);/*USE mencoy.160523*/

			/*checksum update*/
			XORcs=(uint8 *)From+u16WriteSize-1;
			ADDcs=(uint8 *)From+u16WriteSize-2;
			EED_vCalcCS(From,u16WriteSize-2,ADDcs,XORcs);

			/*set the erase flash size*/
			u16EraseSize = EED_axGroup[u8GroupID].u16Length;
			
			/*add to the write data flow*/
            EED_vSetFLSFlow(From,To,u16WriteSize,u16EraseSize);
			
            u8WriteResult = EED_ERR_NULL;
        }
        else
        {   /*Group length error*/
            u8WriteResult = EED_ErrorInvalidGroupLen;    
        }
    }
    else
    {   /*Group ID error*/
        u8WriteResult = EED_ErrorInvalidGroupID;
    }
	return u8WriteResult;

}

static void  EED_vFlsHardWareUpdate(uint8 u8GroupID)
{
    uint8 u8TryCnt,u8Temp;
    //uint32 u32CodeFlashAddr;
   EED_u32FlsErasedAddr = EED_axGroup[u8GroupID].u32StartAddr; 
   for (u8TryCnt=0U;u8TryCnt< EED_u8MaxTryCnt;u8TryCnt++)
   {
        #if EED_DataFlashType == FUJITSU_16BIT
        u8Temp = CFD_u8SectorErase(u32CodeFlashAddr);
        #endif

        #if EED_DataFlashType == NEC_32BIT
        //u8Temp = FLS_u8EraseWait(u32CodeFlashAddr,EED_CFBlockSize);
        /*erase the flash for new writting*/
		EED_FlashOccupySize() = EED_axGroup[u8GroupID].u32StartAddr+EED_axGroup[u8GroupID].u16Length;
		FLS_u8SetCallBackFun(EED_vFlsEraseFlow);
		//u8Temp = FLS_u8Erase(EED_u32FlsErasedAddr,EED_CFBlockSize);/*withg callback fun*/
		u8Temp = FLS_u8Erase(EED_u32FlsErasedAddr,EED_axGroup[u8GroupID].u16Length);
        #endif
        if (u8Temp == EED_ERR_NULL)
        {
            u8TryCnt = EED_u8MaxTryCnt;
        }
        else
        {
            /*nothing to do*/
        }
   
   }       
   EED_au32ValidAddr[u8GroupID] = EED_axGroup[u8GroupID].u32StartAddr;/*re-start from start addr*/

}

/*****************************************************************************
 Function  : EED_vFlsEraseFlow												
 Description   : Check the need erased blocks had done or not, this function ONLY call by
 			 EED_vFlsHardWareUpdate(call back)
 NOTE: NULL
 Return Value  : NULL
*****************************************************************************/
static void EED_vFlsEraseFlow(void)
{
	
	uint8 MOD;
	if(EED_IsFlsFinish()&&(FLS_u8GetSatus()==FLS_enCMD_Ready))
	{
		MOD=EED_stFlowFLS.Out%EED_FlsFlowWaitMax;
		FLS_u8WriteData((uint32)EED_FlsTo(),EED_FlsFrom(), EED_FlsWriteSize());
		
		/*clear flow*/
		EED_FlsFrom()=NULL;
		EED_FlsTo()=NULL;
		EED_FlsWriteSize()=0;

		/*set the flow */
		EED_FlsNextFlow();
		if(EED_IsFlsFinish())
		{
		}
		else
		{
			EED_SetFlsFinish();
		}
	}
	#if 0
	uint8 u8Result=0;
	EED_u32FlsErasedAddr+=FLS_Block_Size;
	
	if(EED_u32FlsErasedAddr<EED_FlashOccupySize())
	{
		FLS_u8SetCallBackFun(EED_vFlsEraseFlow);
		//FLS_u8Erase(FlsErasedSize/FLS_Address_Size);
		u8Result=FLS_u8Erase(EED_u32FlsErasedAddr,EED_CFBlockSize);
		u8Result=0;
	}
	else
	{
		EED_u32FlsErasedAddr=0;
	}
	#endif
}

/*****************************************************************************
 Function  : EED_vSetFLSFlow												
 Description   : set Flash write request flow, the data will automitic write into EEPROM ONLY when
 			you call the function EED_vFlsHardWareUpdate!!!!
 			
			 para list:
			
			 FromRam: data head address in RAM for write
			 ToFls: ToFls LOGIC address for write in [1 LOGIC address = 4 Bytes data]
			 u16Size: write data size
 NOTE: NULL
 Return Value  : NULL
*****************************************************************************/
static void EED_vSetFLSFlow(void *FromRam, void *ToFls,uint16 u16Size,uint16 u16EraseSize)
{
	uint8 Index,MOD=EED_stFlowFLS.In%EED_FlsFlowWaitMax;
	
	if(u16Size==0 ||(EED_stFlowFLS.In-EED_stFlowFLS.Out)>=EED_FlsFlowWaitMax)return;

	/*all request must only once!!*/
	for(Index=0;Index<EED_FlsFlowWaitMax;Index++)
	{
		if(EED_stFlowFLS.From[Index]==FromRam && EED_stFlowFLS.DataLen[Index]==u16Size)
			return;
	}
	
	EED_FlsFlowInsert(FromRam,ToFls,u16Size,u16EraseSize);
}



/*****************************************************************************
 Function  : EED_vFlowCheck												
 Description   : EED write flow check, if write flow is not finish all, it will write continuely!!!
 NOTE: CALL this function 10ms OR
 	    while(1)
 	    {
 	    	EED_vFlowCheck();
 	    	//your task containor
 	    }
 Return Value  : 	NULL
*****************************************************************************/
void EED_vWriteFlowCheck(void)
{
	
	uint8 MOD;
	#ifdef UseEEPROM
	if(EED_IsEepFinish()&&(EEP_u8GetSatus()==EP_enCMD_Ready))
	{
		MOD=EED_stFlowEEP.Out%EED_EEPFlowWaitMax;
		EEP_u8WriteData((uint16)EED_EepTo(), EED_EepFrom(), EED_EepWriteSize());
		/*clear flow*/
		EED_EepFrom()=NULL;
		EED_EepTo()=NULL;
		EED_EepWriteSize()=0;
		
		EED_EepNextFlow();
		if(EED_IsEepFinish())
		{
		
		}
		else
		{
			EED_SetEepFinish();
		}
	}
	#endif
	if(EED_IsFlsFinish()&&(FLS_u8GetSatus()==FLS_enCMD_Ready))
	{
		MOD=EED_stFlowFLS.Out%EED_FlsFlowWaitMax;
		/*set callback fun for write*/
		FLS_u8SetCallBackFun(EED_vFlsEraseFlow);
		
		/*erase block*/
		FLS_u8Erase((uint32)EED_FlsTo(),EED_FlsEraseSize());
	}
#if 0	
	if(EED_IsFlsFinish()&&(FLS_u8GetSatus()==FLS_enCMD_Ready))
	{
		MOD=EED_stFlowFLS.Out%EED_FlsFlowWaitMax;
		/*STEP1*/
		//FLS_u8WriteData((uint16)EED_FlsTo(),EED_FlsFrom(), EED_FlsWriteSize());
		FLS_u8WriteData((uint32)EED_FlsTo(),EED_FlsFrom(), EED_FlsWriteSize());
		/*clear flow*/
		EED_FlsFrom()=NULL;
		EED_FlsTo()=NULL;
		EED_FlsWriteSize()=0;
		
		EED_FlsNextFlow();
		if(EED_IsFlsFinish())
		{
		}
		else
		{
			EED_SetFlsFinish();
		}
	}
#endif
}

/*****************************************************************************
 Function  : EED_u8WriteFlowFinish												
 Description   : check all the Non-avoid data write finish or not, including EEPROM data and Flash data!!
 			Call this function before power off!!
 NOTE: NULL
 Return Value  : 	0: data write is not finish
 				else: data write finish
*****************************************************************************/
uint8 EED_u8WriteFlowFinish(void)
{
	return !EED_AllFlowFinish();
}

void EED_vCalcCS(void const *vpDataHead, uint16 u16DataLegth,uint8 *AddRes, uint8 *XorRes)
{
	uint8 u8XorChkSum = 0,u8AddChkSum = 0;
	const uint8 * pu8Data=(uint8 *)vpDataHead;
	uint16 u16i;
	
	for(u16i=0;u16i<u16DataLegth;u16i++,pu8Data++)
	{
		u8XorChkSum ^= *pu8Data;	/* calculate XOR checksum	*/
		u8AddChkSum += *pu8Data;/* calculate ADD checksum*/
	}
	
	*XorRes=u8XorChkSum+1;         /* XOR chksum = XOR chksum + 1*/
	*AddRes=~u8AddChkSum;	       /* ADD chksum = inverted ADD chksum */
}

