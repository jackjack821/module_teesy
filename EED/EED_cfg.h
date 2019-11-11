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
#ifndef EED_CFG_H
#define EED_CFG_H


#define FUJITSU_16BIT	1
#define NEC_16BIT 		2
#define NEC_32BIT		3

#define EED_DataFlashType	NEC_32BIT 

#define EED_CheckLength_Enable	True
#define EED_ApplLength_Enable	True/**/

#if EED_DataFlashType == FUJITSU_16BIT
#include "CFD.h"
#endif

#if EED_DataFlashType == NEC_32BIT
#include "FLS_Drv.h"
#endif

/*config the max try counter*/
#define EED_u8MaxTryCnt       (uint8)4U

/*config the length for each goup*/
#if 0
#define EED_u8GroupSizeMMI       (uint8)20U /*total len = 18+2=20*/
#define EED_u8GroupSizeOAT       (uint8)16U /*total len = 14+2=16*/
#define EED_u8GroupSizeDIAG      (uint8)116U /*total len = 114+2=116*/
#define EED_u8GroupSizeDTC       (uint8)200U /*total len =202*/
#define EED_u8GroupSizePTS       (uint8)32U /*total len =32*/
#define EED_u8BufferSize         (uint8)(EED_u8GroupSizeMMI + EED_u8GroupSizeDTC)

#ifdef KC2_EED
/*config the length for each goup, change u8 to u16,160521*/
#define EED_u16GroupSizeMMI       32U /*total len = 32*/
#define EED_u16GroupSizeOAT       16U /*total len = 64*/
#define EED_u16GroupSizeDIAG      192U /*total len =256,change to 256, by zsc,160521*/
#define EED_u16GroupSizeDTC       640U /*total len =640*/
#define EED_u16GroupSizePTS       64U /*total len =32*/
#define EED_u16BufferSize        (EED_u16GroupSizeMMI + EED_u16GroupSizeDTC)
#endif

/*config the length for each goup, change u8 to u16,160521*/
#define EED_u16GroupSizeMMI       32U /*total len = 32*/
#define EED_u16GroupSizeOAT       16U /*total len = 64*/
#define EED_u16GroupSizeDIAG      192U /*total len =256,change to 256, by zsc,160521*/
#define EED_u16GroupSizeDTC       640U /*total len =640*/
#define EED_u16GroupSizePTS       64U /*total len =32*/
#define EED_u16BufferSize        (EED_u16GroupSizeMMI + EED_u16GroupSizeDTC)
/*config the length for each goup, change u8 to u16,160521*/

#endif

#define EED_nu8MMIBuffer_Tbl_Len    32U
#define EED_nu8OATBuffer_Tbl_Len    32U /*total len = 32*/
#define EED_nu8DIAGBuffer_Tbl_Len   192U /*total len =256,change to 256, by zsc,160521*/
#define EED_nu8DTCBuffer_Tbl_Len    640U /*total len =640*/
#define EED_nu8PTSBuffer_Tbl_Len    64U /*total len =32*/

#define EED_u16GroupSizeMMI       ((EED_nu8MMIBuffer_Tbl_Len/FLS_Block_Size+1)*FLS_Block_Size)  /*add more 1 block size*/
#define EED_u16GroupSizeOAT       ((EED_nu8OATBuffer_Tbl_Len/FLS_Block_Size+1)*FLS_Block_Size) 
#define EED_u16GroupSizeDIAG      ((EED_nu8DIAGBuffer_Tbl_Len/FLS_Block_Size+1)*FLS_Block_Size)
#define EED_u16GroupSizeDTC       ((EED_nu8DTCBuffer_Tbl_Len/FLS_Block_Size+1)*FLS_Block_Size)
//#define EED_u16GroupSizePTS       ((EED_nPTSBuffer_Tbl_Len/FLS_Block_Size+1)*FLS_Block_Size)/*PTS BUG,161108*/
#define EED_u16GroupSizePTS       ((EED_nu8PTSBuffer_Tbl_Len/FLS_Block_Size)*FLS_Block_Size)
#define EED_u16BufferSize        (EED_u16GroupSizeMMI + EED_u16GroupSizeDTC) /* must more than the largest buffer*/

#if EED_DataFlashType == FUJITSU_16BIT
/*For 673 and 693, flashA= SA1+SA2+SA3+SA4 = 32KB*/
#define SECTOR_SA1_Start       0x00DF2000U
#define SECTOR_SA1_End         0x00DF3FFFU

#define SECTOR_SA2_Start       0x00DF4000U
#define SECTOR_SA2_End         0x00DF5FFFU

#define SECTOR_SA3_Start       0x00DF6000U
#define SECTOR_SA3_End         0x00DF7FFFU

#define SECTOR_SA4_Start       0x00DF8000U
#define SECTOR_SA4_End         0x00DF9FFFU

#define SECTOR_All_Start       SECTOR_SA1_Start
#define SECTOR_All_End         SECTOR_SA4_End
/*this config data MUST relation to the link options,!!!!!!!!!!*/
#define EED_CFBlockSize	    (8*1024)

/*define function*/
#define EED_u8WriteData CFD_u8WriteData
#define EED_u8ReadData  CFD_u8ReadData
#define EED_u8Init CFD_u8Init

#endif

#if EED_DataFlashType == NEC_32BIT
/*For 32bit RH850, data flash= 512*64B = 32KB : 16*2K*/
#define SECTOR_SA1_Start       0xFF200000U
#define SECTOR_SA1_End         0xFF2007FFU

#define SECTOR_SA2_Start       0xFF200800U
#define SECTOR_SA2_End         0xFF200FFFU

#define SECTOR_SA3_Start       0xFF201000U
#define SECTOR_SA3_End         0xFF2017FFU

#define SECTOR_SA4_Start       0xFF201800U
#define SECTOR_SA4_End         0xFF201FFFU

#define SECTOR_SA5_Start       0xFF202000U
#define SECTOR_SA5_End         0xFF2027FFU

#define SECTOR_SA6_Start       0xFF202800U
#define SECTOR_SA6_End         0xFF202FFFU

#define SECTOR_SA7_Start       0xFF203000U
#define SECTOR_SA7_End         0xFF2037FFU

#define SECTOR_SA8_Start       0xFF203800U
#define SECTOR_SA8_End         0xFF203FFFU

#define SECTOR_SA9_Start       0xFF204000U
#define SECTOR_SA9_End         0xFF2047FFU

#define SECTOR_SA10_Start      0xFF204800U
#define SECTOR_SA10_End        0xFF204FFFU

#define SECTOR_SA11_Start      0xFF205000U
#define SECTOR_SA11_End        0xFF2057FFU

#define SECTOR_SA12_Start      0xFF205800U
#define SECTOR_SA12_End        0xFF205FFFU

#define SECTOR_SA13_Start      0xFF206000U
#define SECTOR_SA13_End        0xFF2067FFU

#define SECTOR_SA14_Start      0xFF206800U
#define SECTOR_SA14_End        0xFF206FFFU

#define SECTOR_SA15_Start       0xFF207000U
#define SECTOR_SA15_End         0xFF2077FFU

#define SECTOR_SA16_Start       0xFF207800U
#define SECTOR_SA16_End         0xFF207FFFU

#define SECTOR_All_Start       SECTOR_SA1_Start
#define SECTOR_All_End         SECTOR_SA16_End
/*this config data MUST relation to the link options,!!!!!!!!!!*/
#define EED_CFBlockSize	    (64)

/*define function*/
#define EED_u8WriteData FLS_u8WriteDataWait //CFD_u8WriteData
#define EED_u8ReadData  FLS_u8ReadDataWait //CFD_u8ReadData
#define EED_u8Init FLS_vDrvInit //CFD_u8Init
#define EED_u8WriteDataFlow FLS_u8WriteData //CFD_u8WriteData

#endif

#endif

