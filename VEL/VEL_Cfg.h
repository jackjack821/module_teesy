/********************* MODULE STRUCTURE DEFINITIONS *************************/
/********************** Automatically Generated File ************************/
/********************* Do not edit this file manually! **********************/
/** Generated On : 2015/9/17  20:17:08                                      */
/**           By : Client Service Account (hzh1_csa06)                      */
/**        Using : VEL_Cfg.xls                                              */
/**         From : D:\HVACproject\Geely\Geely FE-3Z\ATC\SourceCode\Appl\VEL */
/**               (D = )                                                    */
/****************************************************************************/
/*****************************************************************************
* FILE DECLARATION
******************************************************************************/
#ifndef VEL_CFG_H
#define VEL_CFG_H
/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
******************************************************************************/
/* System-headerfiles */
#include "General.h"


/*****************************************************************************
* MACROS and STRUCT
*
* In this section declare
* - all macros and structs used in the configuration head file and C file.
******************************************************************************/


#define  VEL_nTempOffsetTbl_Len    (6U)
#define  VEL_nTempAmbientTbl_Len    (4U)
#define  VEL_nBlowerOffsetTbl_Len    (6U)
#define  VEL_nBlowerAmbientTbl_Len    (4U)

/*************************** Define Structures Arrary length ************************/

typedef const struct VEL_stInfo1
{
   const uint8    u8VariableConst;
   const uint8    u8ChipType;
   const uint8    u8HeaderFillByte1;
   const uint8    u8HeaderFillByte2;
} VEL_tstInfo1;

typedef const struct VEL_stInfo2
{
   const uint8    u8VariableConst;
   const uint8    u8HeaderFillByte1;
} VEL_tstInfo2;

typedef const struct VEL_stData2
{
   const uint16   au16TempOffsetTbl_X [ VEL_nTempOffsetTbl_Len ];
   const uint16   au16TempOffsetTbl_Y0 [ VEL_nTempOffsetTbl_Len ];
   const uint16   au16TempOffsetTbl_Y1 [ VEL_nTempOffsetTbl_Len ];
   const uint16   au16TempOffsetTbl_Y2 [ VEL_nTempOffsetTbl_Len ];
   const uint16   au16TempOffsetTbl_Y3 [ VEL_nTempOffsetTbl_Len ];
   const uint16   au16TempOffsetAmbientTbl [ VEL_nTempAmbientTbl_Len ];
} VEL_tstData2;

typedef const struct VEL_stInfo3
{
   const uint8    u8VariableConst;
   const uint8    u8HeaderFillByte1;
} VEL_tstInfo3;

typedef const struct VEL_stData3
{
   const uint16   au16BlowerOffsetTbl_X [ VEL_nBlowerOffsetTbl_Len ];
   const uint16   au16BlowerOffsetTbl_Y0 [ VEL_nBlowerOffsetTbl_Len ];
   const uint16   au16BlowerOffsetTbl_Y1 [ VEL_nBlowerOffsetTbl_Len ];
   const uint16   au16BlowerOffsetTbl_Y2 [ VEL_nBlowerOffsetTbl_Len ];
   const uint16   au16BlowerOffsetTbl_Y3 [ VEL_nBlowerOffsetTbl_Len ];
   const uint16   au16BlowerOffsetAmbientTbl [ VEL_nBlowerAmbientTbl_Len ];
} VEL_tstData3;

/*************************** Group Structures ************************/
typedef const struct VEL_stGroup1
{
   VEL_tstInfo1  stInfo1;
   const uint8  u8AddChkSum;
   const uint8  u8XorChkSum;
} VEL_tstGroup1;

typedef const struct VEL_stGroup2
{
   VEL_tstInfo2  stInfo2;
   VEL_tstData2  stData2;
   const uint8  u8AddChkSum;
   const uint8  u8XorChkSum;
} VEL_tstGroup2;

typedef const struct VEL_stGroup3
{
   VEL_tstInfo3  stInfo3;
   VEL_tstData3  stData3;
   const uint8  u8AddChkSum;
   const uint8  u8XorChkSum;
} VEL_tstGroup3;

/********************** LAYOUT STRUCTURE ****************************/

typedef const struct 
{
   VEL_tstGroup1  stGroup1;
   VEL_tstGroup2  stGroup2;
   VEL_tstGroup3  stGroup3;
} VEL_tstRomLayout;

extern const VEL_tstRomLayout VEL_stRomLayout;

/********************* VARIABLE ACCESS MACROS ***************************/
#define   VEL_u8Group1VariableConst               (VEL_stRomLayout.stGroup1.stInfo1.u8VariableConst)
#define   VEL_u8Group1ChipType                    (VEL_stRomLayout.stGroup1.stInfo1.u8ChipType)
#define   VEL_u8Group1HeaderFillByte1             (VEL_stRomLayout.stGroup1.stInfo1.u8HeaderFillByte1)
#define   VEL_u8Group1HeaderFillByte2             (VEL_stRomLayout.stGroup1.stInfo1.u8HeaderFillByte2)
#define   VEL_u8Group2VariableConst               (VEL_stRomLayout.stGroup2.stInfo2.u8VariableConst)
#define   VEL_u8Group2HeaderFillByte1             (VEL_stRomLayout.stGroup2.stInfo2.u8HeaderFillByte1)
#define   VEL_au16Group2TempOffsetTbl_X           (VEL_stRomLayout.stGroup2.stData2.au16TempOffsetTbl_X)
#define   VEL_au16Group2TempOffsetTbl_Y0          (VEL_stRomLayout.stGroup2.stData2.au16TempOffsetTbl_Y0)
#define   VEL_au16Group2TempOffsetTbl_Y1          (VEL_stRomLayout.stGroup2.stData2.au16TempOffsetTbl_Y1)
#define   VEL_au16Group2TempOffsetTbl_Y2          (VEL_stRomLayout.stGroup2.stData2.au16TempOffsetTbl_Y2)
#define   VEL_au16Group2TempOffsetTbl_Y3          (VEL_stRomLayout.stGroup2.stData2.au16TempOffsetTbl_Y3)
#define   VEL_au16Group2TempOffsetAmbientTbl          (VEL_stRomLayout.stGroup2.stData2.au16TempOffsetAmbientTbl)
#define   VEL_u8Group3VariableConst               (VEL_stRomLayout.stGroup3.stInfo3.u8VariableConst)
#define   VEL_u8Group3HeaderFillByte1             (VEL_stRomLayout.stGroup3.stInfo3.u8HeaderFillByte1)
#define   VEL_au16Group3BlowerOffsetTbl_X          (VEL_stRomLayout.stGroup3.stData3.au16BlowerOffsetTbl_X)
#define   VEL_au16Group3BlowerOffsetTbl_Y0          (VEL_stRomLayout.stGroup3.stData3.au16BlowerOffsetTbl_Y0)
#define   VEL_au16Group3BlowerOffsetTbl_Y1          (VEL_stRomLayout.stGroup3.stData3.au16BlowerOffsetTbl_Y1)
#define   VEL_au16Group3BlowerOffsetTbl_Y2          (VEL_stRomLayout.stGroup3.stData3.au16BlowerOffsetTbl_Y2)
#define   VEL_au16Group3BlowerOffsetTbl_Y3          (VEL_stRomLayout.stGroup3.stData3.au16BlowerOffsetTbl_Y3)
#define   VEL_au16Group3BlowerOffsetAmbientTbl          (VEL_stRomLayout.stGroup3.stData3.au16BlowerOffsetAmbientTbl)
#define   VEL_nFastRiseSpeed                      (10U)    /**/
#define   VEL_nFastFallSpeed                      (10U)    /**/
#define   VEL_nSlowRiseSpeed                      (1U)    /**/
#define   VEL_nSlowFallSpeed                      (1U)    /**/
#define   VEL_nReserve1                           (0U)    /**/
/******************************** END *************************************/
 /*****************************************************************************
* End of check if informations are already included
******************************************************************************/
#endif                                  /* ifndef */

/*****************************************************************************
*VEL_Cfg.h
******************************************************************************/
