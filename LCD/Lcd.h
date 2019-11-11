/*******************************************************************************
| Module Name: Lcd Control
| File Name: Lcd.h
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
| Yang Shengli                        Desay SV Automotive Co., Ltd
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date             Ver         Author               Description
| ----------  -------  -------------  -------------------------------------------------
| 2016-02-27  1.00        Yang Shengli      First implementation
| 2016-03-15  2.00        Yang Shengli      update LCD code
********************************************************************************/

/*****************************************************************************
* FILE DECLARATION
******************************************************************************/
#ifndef LCD_H
#define LCD_H


/*****************************************************************************
* LOCATION-DEFINES -only when the location assignment is needed.
******************************************************************************/


/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
******************************************************************************/
/* System-headerfiles */
#include "General.h"
/* Please put the headerfiles which related to system here! */

/* Foreign headerfiles */

/* Please put the headerfiles which related to foreign here! */

#include "Rte_Type.h"
/* Own headerfiles */

#include "Lcd_Cfg.h"                 /* Configuration head file */
#include "Lcd_Type.h"                 /* General definitions and datatypes */


/*****************************************************************************
*EXPORT INTERFACE FUNCTION DEFINE
******************************************************************************/
extern void LCD_vReset(void);               /* called from reset comtainer      */
extern void LCD_vInit( void);
extern void LCD_vDeinit( void);
extern void LCD_vActive(void);              /* active container (10mS)         */
extern void LCD_vMain(void);                /* on container (10mS)             */
void LCD_vMainCommand(void);
void LCD_vMainCom0(void);
void LCD_vMainCom1(void);
void LCD_vMainCom2(void);
void LCD_vMainCom3(void);
extern uint16 LCD_vu16TouchInfGetValue( LCD_tenu16VarNumber enIndex );
#ifndef USE_INTIIC
extern void LCD_MasterSendEndCallback(void);
void LCD_MasterReceiveEndCallback(void);
void LCD_IicErr(uint8 Index);
#endif

extern Std_ReturnType LCD_u8ForceIoControl_Write(/*IN*/UInt32 ForceIoControlWord);
/*****************************************************************************
* End of check if informations are already included
******************************************************************************/
#endif                                  /* ifndef */

/*****************************************************************************
* EOF: LCD.h
******************************************************************************/
