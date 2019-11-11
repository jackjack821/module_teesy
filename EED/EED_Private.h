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
  Rev 02       2015/06/01    Zhang Shuncong            add groupID info,update flow                                                  update Telltales process
****************************** .FILE_HEADER_END ******************************/

#ifndef EED_PRIVATE_H
#define EED_PRIVATE_H


/*****************************************************************************
* LOCATION-DEFINES -only when the location assignment is needed.
******************************************************************************/

/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
******************************************************************************/
/* System-headerfiles */

/* Please put the headerfiles which related to system here! */

/* Foreign headerfiles */

/* Please put the headerfiles which related to foreign here! */


/* Own headerfiles */
#include "EEDA1_ee_defines.h"
#include "EEDA1_ee_struct.h"
#include "EEDA1_ee_defaults.h"

//3***************************************************************************************************************************************
/*Change the define if neccesary*/

#define EED_EEPstartAddr			0x0000
#define EED_FLSstartAddr			0x0000
#define EED_TotalGroupNum		TOTAL_GROUP_USING
#define EED_EEPROMGroupNum	EXT_GROUP_USING
//#define EED_EEPFlowWaitMax		4
//#define EED_FlsFlowWaitMax		8

#define EED_nu8GroupMMI		EED_enGroupID_2
#define EED_nu8GroupOAT		EED_enGroupID_3
#define EED_nu8GroupDIAG	EED_enGroupID_4
#define EED_nu8GroupDTC		EED_enGroupID_5
#define EED_nu8GroupFP		EED_enGroupID_6 //J72
#define EED_nu8GroupPTS		EED_enGroupID_7 //J72
//3***************************************************************************************************************************************

#define EED_GetEEPGrpNum()	EED_EEPROMGroupNum
#define EED_RAMmirrorHead	&EED_stLayout
#define EED_ROMmirrorHead	&EED__stROMLayout
#define EED_enGroupID_NUM	EED_TotalGroupNum
#define EED_nu8GroupMax EED_TotalGroupNum

#define EED_EepromOccupySize()		EED_u32UsingEepSize
#define EED_FlashOccupySize()			EED_u32UsigFlsSize

#define EED_AllFlowFinish()	(EED_stFlowFLS.Out&&EED_stFlowEEP.Out&&EED_stFlowFLS.In&&EED_stFlowEEP.In)

#define EED_IsFlsFinish()		(EED_stFlowFLS.Out<EED_stFlowFLS.In)
#define EED_SetFlsFinish()		EED_stFlowFLS.In=0;EED_stFlowFLS.Out=0
#define EED_FlsNextFlow()		EED_stFlowFLS.Out++

#define EED_FlsFrom()			EED_stFlowFLS.From[MOD]
#define EED_FlsTo()			EED_stFlowFLS.To[MOD]
#define EED_FlsWriteSize()		EED_stFlowFLS.DataLen[MOD]
#define EED_FlsEraseSize()		EED_stFlowFLS.EraseSize[MOD]

#define EED_FlsFlowInsert(FromRam,ToFls,u16Size,u16EraseSize)	\
							EED_stFlowFLS.From[MOD]=(void *)FromRam;\
							EED_stFlowFLS.To[MOD]=(void *)ToFls;\
							EED_stFlowFLS.DataLen[MOD]=u16Size;\
							EED_stFlowFLS.EraseSize[MOD]=u16EraseSize;\
							EED_stFlowFLS.In++
							
#define EED_GroupInf(group)			{(void *)&EED_stLayout.stGROUP##group,(void *)&EED__stROMLayout.stGROUP##group,sizeof(EED_stLayout.stGROUP##group)}

#define EED_GroupInfoHead(group) 			(&EED_axBlockTable[group])
#define EED_GroupRamHead(group) 	(EED_axBlockTable[group].pvGroupRAMHead)
#define EED_GroupROMHead(group) 	(EED_axBlockTable[group].pvGroupROMHead)
#define EED_GroupSize(group) 			(EED_axBlockTable[group].u16GroupSize)
/*******************************************************************************
* End of check if informations are already included
*******************************************************************************/
#endif                                  /* ifndef EED_PRIVATE_H*/

/*******************************************************************************
* EOF: EED.h
*******************************************************************************/


