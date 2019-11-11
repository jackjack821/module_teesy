/*******************************************************************************
| Module Name: KEY capture and debouncing  
| File Name: KEY_CFG.h
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
| 2016.8.3         0100      Li jiaye         module template update. 
| 
| 
****************************** .FILE_HEADER_END *********************************/
/*****************************************************************************
* FILE DECLARATION
******************************************************************************/
#ifndef TouchKey_CFG_H
#define TouchKey_CFG_H
/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
******************************************************************************/
/* System-headerfiles */
#include "General.h"
#include "TouchKey_type.h"
#define TouchKeyNum  (20)
#define MainPageNum  (4)
#define TouchType  SinglePointTouch
#define SinglePointTouch  1
#define MultiPointTouch    2
#define TouchNumbers      1
#define TouchIicDataLen  (29) /*Iic data length*/   

/**********************************
add by wuyijun 
Iic data length     20--->21

****************************************/


/******************************** END *************************************/
 /*****************************************************************************
* End of check if informations are already included
******************************************************************************/
#endif                                  /* ifndef */

/*****************************************************************************
*Touchkey_Cfg.h
******************************************************************************/
