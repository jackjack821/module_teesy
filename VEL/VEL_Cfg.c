/************************** DEFAULTS ************************************/
/********************** Automatically Generated File ************************/
/********************* Do not edit this file manually! **********************/
/** Generated On : 2015/9/17  20:17:09                                      */
/**           By : Client Service Account (hzh1_csa06)                      */
/**        Using : VEL_Cfg.xls                                              */
/**         From : D:\HVACproject\Geely\Geely FE-3Z\ATC\SourceCode\Appl\VEL */
/**               (D = )                                                    */
/****************************************************************************/

/*****************************************************************************
* FILE DECLARATION
*****************************************************************************/

#define VEL_CFG

/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
*****************************************************************************/
#include "VEL.h"


/*****************************************************************************
* MODULE GLOBAL CONFIGURATION CONSTANTS
*
* In this section define
* - constants and macros to configure your module. These constants are unknown for other
*   modules
*****************************************************************************/




const VEL_tstRomLayout VEL_stRomLayout = {

   {  /*----------------------- Group1 ---------------------------------------*/

      {  /* Info1 */
         0x1U,                                                    /* u8VariableConst */
         0x0U,                                                    /* u8ChipType */
         0xFFU,                                                   /* u8HeaderFillByte1 */
         0xFFU                                                    /* u8HeaderFillByte2 */
      },
      0x0U,                                                       /* u8AddChkSum */
      0x2U                                                        /* u8XorChkSum */
   },

   {  /*----------------------- Group2 ---------------------------------------*/

      {  /* Info2 */
         0x1U,                                                    /* u8VariableConst */
         0xFFU                                                    /* u8HeaderFillByte1 */
      },

      {  /* Data2 */
         { 0x0000U,0x0014U,0x0028U,0x003CU,0x0050U,0x0078U },     /* au16TempOffsetTbl_X */
         { 0x0280U,0x0280U,0x0280U,0x0280U,0x0280U,0x0280U },     /* au16TempOffsetTbl_Y0 */
         { 0x0280U,0x0280U,0x0280U,0x0280U,0x0280U,0x0280U },     /* au16TempOffsetTbl_Y1 */
         { 0x027BU,0x027CU,0x0280U,0x0280U,0x0280U,0x0280U },     /* au16TempOffsetTbl_Y2 */
         { 0x027CU,0x027DU,0x0280U,0x0280U,0x0280U,0x0280U },     /* au16TempOffsetTbl_Y3 */
         { 0x00FAU,0x01C2U,0x028AU,0x0320U }                      /* au16TempOffsetAmbientTbl */
      },
      0x33U,                                                      /* u8AddChkSum */
      0x43U                                                       /* u8XorChkSum */
   },

   {  /*----------------------- Group3 ---------------------------------------*/

      {  /* Info3 */
         0x1U,                                                    /* u8VariableConst */
         0xFFU                                                    /* u8HeaderFillByte1 */
      },

      {  /* Data3 */
         { 0x0000U,0x0014U,0x0028U,0x003CU,0x0050U,0x0078U },     /* au16BlowerOffsetTbl_X */
         { 0x03E8U,0x03E8U,0x03E8U,0x03E8U,0x03E8U,0x03E8U },     /* au16BlowerOffsetTbl_Y0 */
         { 0x03E8U,0x03E8U,0x03E8U,0x03E8U,0x03E8U,0x03E8U },     /* au16BlowerOffsetTbl_Y1 */
         { 0x03E8U,0x03E8U,0x03E8U,0x03E8U,0x03E8U,0x03E8U },     /* au16BlowerOffsetTbl_Y2 */
         { 0x041AU,0x0406U,0x03E8U,0x03E8U,0x03E8U,0x03E8U },     /* au16BlowerOffsetTbl_Y3 */
         { 0x00FAU,0x01C2U,0x028AU,0x0320U }                      /* au16BlowerOffsetAmbientTbl */
      },
      0xF9U,                                                      /* u8AddChkSum */
      0x59U                                                       /* u8XorChkSum */
   }
};