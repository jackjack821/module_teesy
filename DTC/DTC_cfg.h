/*******************************************************************************
| Module Name: DTC process(prcess dianostic code)
| File Name: DTC_Cfg.h
|
| .Date; 2018-6-5
| .Update Time; 14:49:42
| .DTCDefineList; D:\HVACProject\Geely\FE-5DB&7DA\ProjectTools\CANTools\DTC\DTCGen\FE-5DB&7DA DTC list_20180605.xlsm
|-------------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-------------------------------------------------------------------------------
| Name                                  Company
| ---------------------     ---------------------------------------
| Sui Yanchun                        Desay SV Automotive Co., Ltd
| Zhang Shuncong                     Desay SV Automotive Co., Ltd
| Li Jiaye                           Desay SV Automotive Co., Ltd
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date             Ver         Author               Description
| ----------  -------  -------------  -------------------------------------------------
| 2014-11-24  1.00        Sui Yanchun       update the DTC module
| 2015-12-56  2.00        Lin Tao           update for the MISRA C
| 2017-07-21  3.00        Li Jiaye          interface update

********************************************************************************/
#ifndef DTC_CFG_H
#define DTC_CFG_H
/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
******************************************************************************/
/* System-headerfiles */
#include "General.h" 

/* Foreign headerfiles */
/* Own headerfiles */
#include "DTC_Type.h" 
#include "DTC_Private.h" 


/*DTC Table define*/
typedef enum DTC_enVarNumber
{
    /************************** DTC value Start *********************************/
     DTC_nBusOff, /*0*/
     DTC_nErrPEPS, /*1*/
     DTC_nErrEMS, /*2*/
     DTC_nErrESC, /*3*/
     DTC_nErrIPK, /*4*/
     DTC_nErrMMI, /*5*/
     DTC_nErrTBOX, /*6*/
     DTC_nLostEMS, /*7*/
     DTC_nLostESC, /*8*/
     DTC_nLostIPK, /*9*/
     DTC_nLostMMI, /*10*/
     DTC_nLostTBOX, /*11*/
     DTC_nLostPEPS, /*12*/
     DTC_nPowLow, /*13*/
     DTC_nPowHigh, /*14*/
     DTC_nBlowerErr, /*15*/
     DTC_nMix1Gnd, /*16*/
     DTC_nMix1Bat, /*17*/
     DTC_nMix1Block, /*18*/
     DTC_nMix2Gnd, /*19*/
     DTC_nMix2Bat, /*20*/
     DTC_nMix2Block, /*21*/
     DTC_nAirdGnd, /*22*/
     DTC_nAirdBat, /*23*/
     DTC_nAirdBlock, /*24*/
     DTC_nRfaGnd, /*25*/
     DTC_nRfaBat, /*26*/
     DTC_nRfaBlock, /*27*/
     DTC_nEvapGnd, /*28*/
     DTC_nEvapBat, /*29*/
     DTC_nOatGnd, /*30*/
     DTC_nOatBat, /*31*/
     DTC_nSunDrGnd, /*32*/
     DTC_nSunDrBat, /*33*/
     DTC_nLostPM25, /*34*/
     DTC_nPM25HWErr, /*35*/
     DTC_nAQSHWErr, /*36*/
     DTC_END
}DTC_tenVarNumber;

enum
{
  DTC_nCallForeGround = 0,
  DTC_nCallBackGround1,
  DTC_nCallBackGround2,
  DTC_nCallPowFailureDtc,
};
/***Start***/
typedef struct
{
    uint8                       DTCMSB;
    uint8                       DTCLSB;
    uint8                       DTC_Failure_Type;
}DTC_CODE_TYPE;
typedef struct
{
    DTC_tenVarNumber            DTC_Index;
    DTC_CODE_TYPE               DTC_Code;
    uint8                       Fault_INC;
    uint8                       Fault_DEC;
    uint8                       Fault_THRPass;
    uint8                       Fault_THRFail;
    uint8                       DTC_Priority;
    uint8                       CallSequence;

}DTC_PROPERTY_TYPE;
/*==================
define property struct type===
===================*/
typedef uint8 (*tfpDTCFailureStatus) (void);
typedef struct
{
    DTC_tenVarNumber                DTC_Index;
    const DTC_CODE_TYPE             DTC_Code;
    const uint8                                 Fault_INC;
    const uint8                                     Fault_DEC;
    const uint8                                 Fault_THRPass;
    const uint8                                 Fault_THRFail;
    const uint8                             DTC_Priority;
    const uint8                             CallSequence;
    const tfpDTCFailureStatus           fpDtcGetFailureStatus;
}DTC_tstProperty;
/*define the Pass and fail counter*/
#define DEFAULT_INC                         (1U)
#define DEFAULT_DEC                         (1U)

/*define the Threshold value*/
#define SIGNAL_FAULT_THR                     (1U)
#define DEFAULT_THR_Pass                     (118U)
#define DEFAULT_THR_Fail                     (138U)
#define DEFAULT_THR_Init                     (128U)

#define Pow_THR_Pass                         (127U)/*Call in 10ms,Modify by LT,20160806*/
#define POW_THR_Fail                         (129U)/*Call in 10ms,Modify by LT,20160806*/

#define Motor_THR_Pass                       (108U)
#define Motor_THR_Fail                       (148U)

#define MotorBlock_THR_Pass                  (127U)
#define MotorBlock_THR_Fail                  (129U)

#define Sensor_THR_Pass                      (108U)
#define Sensor_THR_Fail                      (148U)

#define BCTL_THR_Pass                        (127U)
#define BCTL_THR_Fail                        (129U)

#define CAN_THR_Pass                         (127U)
#define CAN_THR_Fail                         (129U)

#define LIN_THR_Pass                         (127U)
#define LIN_THR_Fail                         (129U)

#define PTC_THR_Pass                         (108U) /*148-108=4s*/
#define PTC_THR_Fail                         (148U) /*148-128=2s*/

#define ACCM_THR_Pass                        (108U) /*148-108=4s*/
#define ACCM_THR_Fail                        (148U) /*148-128=2s*/

#define BUMP_THR_Pass                        (108U) /*148-108=4s*/
#define BUMP_THR_Fail                        (148U) /*148-128=2s*/

/*Priority define*/
#define GneralPriority                      (1U)
#define BusoffPriority                      (4U)
#define SesnorPriority                      (4U)
#define BatteryPriority                     (3U)
#define MotorPriority                       (3U)
#define CanMessPriority                     (6U)
#define LinMessPriority                     (4U)
#define PM25Priority                        (4U)
#define IONPriority                         (4U)
#define PTCPriority                         (2U)
#define ACCMPriority                        (2U)
#define MotorPumpPriority                   (1U)
#define HeatingPumpPriority                 (2U)
#define ChillerPumpPriority                 (2U)

/*Define the supported service for $19*/
#define DTC_SnapshotSupported               (Yes)
#define DTC_ExtendDataSupported             (Yes)

#define DTC_SortFIFO                        (1U)
#define DTC_SortPriority                    (2U)

#define DTC_nSWVerSion                  (0xA3U)/*20160914*/

extern const DTC_tstProperty DTC_stPropertyTable[DTC_END];

#if (DTC_SnapshotSupported == Yes)
extern  const uint8 DTC_SnapshotNumTbl[1];
extern  const uint16 DTC_SnapshotDIDTbl[1][6];
#endif

#if (DTC_ExtendDataSupported == Yes)
extern const uint8 DTC_ExtendedRecordNumTbl[2];
#endif

#endif

/*****************************************************************************
* EOF: DTC_cfg.h
******************************************************************************/

