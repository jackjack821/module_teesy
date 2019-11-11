/**************************** .FILE_HEADER_BEGIN *****************************
 .FILE; [ CANNMAPP.h]
 .Author; [ Liu Fuguang]
 .Date; 2016/12/30
 .Update Time; 11:43:29
 .Gen File Name: SX11P_LIN_V1.0_2016-12-29.xlsx
****************************** .FILE_HEADER_END ******************************/

#ifndef CANNMAPP_H
#define CANNMAPP_H
#ifndef CANNMAPP
#define ext extern
#else
#define ext
#endif

typedef enum
{/* All receive signals...*/
     CANNMAPP_nu16NmMode = 0,
     CANNMAPP_nu16NmPrevState ,
     CANNMAPP_nu16NmCurrState ,     
     CAMNMAPP_nu16CanSleep,
     //CANNMAPP_nu16CommunicationEnable, /*Reserve For the Project without AutosarNm*/
     CANNMAPP_nu16BusOffStart,
     CANNMAPP_nu16BusOffConf,
     CANNMAPP_u16BusIdle,
     CANNMAPP_u16MsgDlcErr,
     CANNMAPP_u16MsgValid,
     CANNMAPP_nu16Max
} CANNMAPP_tenu16VarNum;

enum
{
	CANNMAPP_nWake,
	CANNMAPP_nSleep,
	CANNMAPP_nSleepFail,
};

typedef struct
{
	/* Byte0 */
	uint8 WakeSource:8;
	/* Byte1 */
	uint8 NetWorkState:1; /*Only For Test*/
	uint8 NotUse0:1;
	uint8 NotUse1:1;
	uint8 NotUse2:1;
	uint8 NotUse3:1;
	uint8 NotUse4:1;
	uint8 NotUse5:1;
	uint8 NotUse6:1;
	/* Byte2 */
	uint8 NotUse7:1;
	uint8 StayWakeByK15:1; 
	uint8 NotUse8:1;
	uint8 NotUse9:1;
	uint8 NotUse10:1;
	uint8 NotUse11:1;
	uint8 StayWakeByDiag:1; 
	uint8 NotUse12:1;
	/* Byte3 */
	uint8 NotUse13:8;	
	/* Byte4 */
	uint8 NotUse14:8;	
	/* Byte5 */
	uint8 NotUse15:8;
}CANNMAPP_tstNmUserData;

enum
{
  //CANNMAPP_nDiagFun = 0/* ID: 0x000007df, Handle: 0, Func_DiagReq [BC] */, 
  //CANNMAPP_nDiagReq /* ID: 0x000007c6, Handle: 1, AC_DiagReq [BC] */, 
  //CANNMAPP_nCalibration /* ID: 0x000006b1, Handle: 2, CCP_Calibration_Write [BC] */, 
  CANNMAPP_nEmsRPM /* ID: 0x00000085, Handle: 3, EMS_EngineRPM [BC] */, 
  CANNMAPP_nIpk /* ID: 0x000003f1, Handle: 4, IPK_TotalOdometer [FC] */, 
  CANNMAPP_nMmiAc /* ID: 0x000002a5, Handle: 5, MMI_AC_Command [FC] */, 
  CANNMAPP_nMmiHvsm /* ID: 0x000002a3, Handle: 6, MMI_HVSM_Command [FC] */, 
  CANNMAPP_nTbox /* ID: 0x00000292, Handle: 7, TBOX_RemCon [FC] */, 
  CANNMAPP_nEmsDrv /* ID: 0x00000288, Handle: 8, EMS_EngineDriverInfo [FC] */, 
  CANNMAPP_nPeps /* ID: 0x000001e2, Handle: 9, PEPS_Message_Sts [FC] */, 
  CANNMAPP_nEsc /* ID: 0x00000125, Handle: 10, ESC_Status [FC] */, 
  CANNMAPP_nEmsEng /* ID: 0x00000086, Handle: 11, EMS_EngineStatus [FC] */,
  CANNMAPP_nMax
};
/* Main export function...*/
ext void CANNMAPP_vReset(void);
ext void CANNMAPP_vMain_10ms(void);
ext uint16 CANNMAPP_u16GetValue(CANNMAPP_tenu16VarNum enIndex);
ext void CANNMAPP_vClearBusoffError(void);
ext void CANNMAPP_vSetWakeupReasonByDiag(void);
ext void CANNMAPP_vClrWakeupReasonByDiag(void);
void CANNMAPP_vClearStayWakeByDiag(void);

//ext void Ccl_Nm_EnableTxPath( uint8 a );
//ext void ApplRepeatMsgInd( uint8 a );

/* End of the file...*/
#undef ext
#endif


