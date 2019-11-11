/**************************** .FILE_HEADER_BEGIN *****************************
 .FILE; [ CANNMAPP_cfg.h]
 .Author; [ Liu Fuguang]
 .Date; 2016/12/30
 .Update Time; 11:43:29
 .Gen File Name: SX11P_LIN_V1.0_2016-12-29.xlsx
****************************** .FILE_HEADER_END ******************************/
#ifndef CANNMAPP_CFG_H
#define CANNMAPP_CFG_H
#ifndef CANNMAPP
#define ext extern
#else
#define ext
#endif


/****************************************************************************/
/*****************                 Input Interface                        *************************/
/*****************    Need to configurate when Integration       *************************/
/****************************************************************************/
#define CANNMAPP_nIGN2PortPin (True) //0x0006)
#define CANNMAPP_u16LocalWakeUp(u8temp)    	True //MCU_u16PinRead((MUC_enPinID)CANNMAPP_nIGN2PortPin,u8temp)//HAL_PinRead(0,6)
#define CANNMAPP_McuStopModeUse False

#define CANNMAPP_u16VolLo 	POW_u16GetValue(POW_nu16ComLowVoltage)	
#define CANNMAPP_u16VolHi 	POW_u16GetValue(POW_nu16ComHighVoltage)	

#define CANNMAPP_StayActiveTime 	500
#define CANNMAPP_BusoffRecoverSendMsgHandle 5


#undef ext
#endif
