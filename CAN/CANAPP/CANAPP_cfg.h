/**************************** .FILE_HEADER_BEGIN *****************************
 .FILE; [ CANAPP_cfg.h]
 .Author; [ Liu Fuguang]
 .Date; 2017/10/26
 .Update Time; 8:57:20
 .Gen File Name: Geely GE12_V1.3.11_CAN.xlsx
 .**************   Change History ********************************************* 
 .V2.0 (Release Date:2017-4-17)
 .1.Creation
 .V2.1 (Release Date:2017-4-18)
 .1.Add static uint16 CANAPP_u16SendMsgTimer_20ms
 .2.Add static uint16 CANAPP_u16SendMsgTimer_40ms
 .3.Add static uint16 CANAPP_u16SendMsgTimer_500ms
 .V2.2 (Release Date:2017-4-22)
 .1.Update *Update Content Of Send Message* Module 
 .***************************************************************************** 
****************************** .FILE_HEADER_END ******************************/

#ifndef CANAPP_CFG_H
#define CANAPP_CFG_H
/* Const code area...*/

/* Define the const */
#define U16_INIT_VALUE			0xFFFF
#define U16_MISS_VALUE			0xFFFE
#define U32_MISS_VALUE			0xFFFFFFFE

/* Define the CAN transmit signals from other modules */
#define CANNMAPP_BusOffStart     CANNMAPP_u16GetValue(CANNMAPP_nu16BusOffStart)
							

#endif

