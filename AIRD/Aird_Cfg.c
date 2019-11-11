/************************** DEFAULTS ************************************/
/********************** Automatically Generated File ************************/
/********************* Do not edit this file manually! **********************/
/** Generated On : 2017/10/20  11:36:48                                     */
/**           By : uidp4501                                                 */
/**        Using : AIRD_Cfg_v01.xls                                         */
/**         From : D:\HVACProject\Geely\FE-5DB&7DA\ProjectCode\01_APP\AIRD  */
/**               (D = )                                                    */
/****************************************************************************/

/*****************************************************************************
* FILE DECLARATION
*****************************************************************************/

#define AIRD_CFG

/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
*****************************************************************************/
#include "AIRD.h"


/*****************************************************************************
* MODULE GLOBAL CONFIGURATION CONSTANTS
*
* In this section define
* - constants and macros to configure your module. These constants are unknown for other
*   modules
*****************************************************************************/




const AIRD_tstRomLayout AIRD_stRomLayout = {

   {  /*----------------------- Group1 ---------------------------------------*/

      {  /* AirdInfo */
         0x1U,                                                    /* u8VariableConst */
         0x0U                                                     /* u8ChipType */
      },

      {  /* AirdData */
         { 0x033EU,0x02A3U,0x0200U,0x0160U,0x00D2U },             /* au16AirdManuPosition_Tbl */
         { 0x033EU,0x02E4U,0x02A3U,0x0253U,0x0200U,0x0160U,0x00D2U },  /* au16AirdWinterPosition_Tbl */
         { 0x033EU,0x02E4U,0x02A3U,0x0253U,0x0200U,0x0160U,0x00D2U },  /* au16AirdSummerPosition_Tbl */
         { 0x024EU,0x0276U,0x029EU,0x02C6U },                     /* au16BlowoutTempDown_Tbl */
         { 0x026CU,0x0294U,0x02B2U,0x02EEU },                     /* au16BlowoutTempUp_Tbl */
         { 0x0334U,0x0366U },                                     /* au16HeatercoreTempDown */
         { 0x0352U,0x0384U }                                      /* au16HeatercoreTempUp */
      },
      0xE3U,                                                      /* u8AddChkSum */
      0x6DU                                                       /* u8XorChkSum */
   }
};
