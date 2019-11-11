/**************************** .FILE_HEADER_BEGIN *****************************
  .TITLE   DC Motor Driver for NCV77x9, 	                             ]
*-----------------------------------------------------------------------------
  .FILE   NCV77x9_type.h                                                      ]
   .AUTHOR [  tan fumin 				                                     ]
*-----------------------------------------------------------------------------
NOTE:
		This software package only for DC motor driver nvc771!
 	
 Version Date        Author                       Change
 -----------------------------------------------------------------------------
 Rev 1.0 2015-4-28   tan fumin         module template update. 
 
****************************** .FILE_HEADER_END ******************************/

#ifndef NCV77x9_TYPE_H
#define NCV77x9_TYPE_H



#define MDVR_ChannelID_1	0
#define MDVR_ChannelID_2	1
#define MDVR_ChannelID_3	2
#define MDVR_ChannelID_4	3
#define MDVR_ChannelID_5	4
#define MDVR_ChannelID_6	5


typedef enum
{
	MDVR_enHighZ=0,	/*driver out is High-Z status*/
	MDVR_enOutputLow,		/*driver out is Low level and lowside is shut cut to GND*/
	MDVR_enOutputHigh,		/*driver out is High level and highside is shut cut to VDD*/
}MDVR_enCtrlType;
#if 0
typedef enum
{
    OutputDisable=0,
    OverCurrent,
    UnderLoad,
    Normal
}MDVR_tenChannelErrorStatus;
typedef struct 
{
    uint8 OverCurrent: 1;
    uint8 PowerFailure:1;
    uint8 UnderLoad:1;
    MDVR_tenChannelErrorStatus Channel6:2;
    MDVR_tenChannelErrorStatus Channel5:2;
    MDVR_tenChannelErrorStatus Channel4:2;
    MDVR_tenChannelErrorStatus Channel3:2;
    MDVR_tenChannelErrorStatus Channel2:2;
    MDVR_tenChannelErrorStatus Channel1:2;
    uint8 OverTempWarn:1;
    
}MDVR_tstErrorStatus;
#endif
typedef struct
{
	uint16 u16ChannelCtrlStatus;
    uint16 u16ChannelCtrlStatus2;
	uint16 u16ChannelFeedBackStatus;
	uint16 u16ChannelFeedBackStatus2;
	uint8 u8DrvReady;
}MDVR_stManage;


enum
{
	MDVR_enErrOK,
	MDVR_enErrParaOutOfRange,
	MDVR_enErrChannleOutOfRange,
	MDVR_enErrDrvNotReady,
	MDVR_enErrDrvFatalErr,
};

#endif

