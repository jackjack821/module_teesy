/*******************************************************************************
| Module Name: CAN CCL
| File Name: CANCCL.h
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
| Liu Fuguang                           Desay SV Automotive Co., Ltd
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date             Ver         Author               Description
| ----------  -------  -------------  -------------------------------------------------
| 2016-07-19  1.00        Liu Fuguang          First implementation

********************************************************************************/

#ifndef CANCCL_H
#define CANCCL_H

#ifndef CANCCL_C
  #define ext extern
#else
  #define ext
#endif

/*this is for uint8 type variables*/
typedef enum CANCCL_enu16VarNumber
{
	CANCCL_nu16EnableSleep = 0,
	CANCCL_nu16Max
}CANCCL_tenu16VarNumber;

typedef enum 
{
	CANCCL_enResetFlag = 0,
    CANCCL_enRunEnable,
    CANCCL_enRunDisable
}CANCCL_tenCanRunable;
/**************************** .BLOCK_COMMENT_BEGIN ***************************
* EXPORT INTERFACE FUNCTION PROTOTYPES
*
* In this section declare
* - all system global function prototypes of your module. This is a copy of
*   the function definitions without the header template.
***************************** .BLOCK_COMMENT_END *****************************/
ext void CANCCL_vReset(void);
ext void CANCCL_vMain(void);
ext uint16 CANCCL_u16GetValue(CANCCL_tenu16VarNumber enIndex);
void CANCCL_vTickCntCallBack(void);

#undef ext
#endif
