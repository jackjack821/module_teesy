/**************************** .FILE_HEADER_BEGIN *****************************
  .TITLE   DC Motor Driver for NCV77x9, 	                             ]
*-----------------------------------------------------------------------------
  .FILE   NCV77x9.c                                                      ]
   .AUTHOR [  tan fumin 				                                     ]
*-----------------------------------------------------------------------------
NOTE:
		This software package only for DC motor driver nvc771!
 	
 Version Date        Author                       Change
 -----------------------------------------------------------------------------
 Rev 1.0 2015-4-28   tan fumin         module template update. 
 
****************************** .FILE_HEADER_END ******************************/

#include "NCV77x9.h"
#include "DCM_Type.h"
#include "DCM_interface.h"
#include "RDC.h" 
#include "ACCC.h" 
MDVR_stManage MDVR_stInfo;

#define CSDisable 	1
#define CSEnable	0
/*Ccp control*/
typedef enum
{
	NCV77x9_nSetMixMotor,
	NCV77x9_nSetAirdMotor,
	NCV77x9_nSetRfaMotor,
	NCV77x9_nSetPsMixMotor,
	NCV77x9_nSetAllMotor,
	NCV77x9_nCcpForceMax
}CcpControl_NCV77x9;
static uint8 NCV77x9_CcpForceFlag=0;
static uint16 NCV77x9_CcpControlData[NCV77x9_nCcpForceMax];
#define NCV77x9GetCcpForceBit(index)	((NCV77x9_CcpForceFlag>>index)&0x01)
#define NCV77x9SetCcpForceBit(index)	(NCV77x9_CcpForceFlag=NCV77x9_CcpForceFlag|(0x01<<index))
#define NCV77x9ClrCcpForceBit(index)	(NCV77x9_CcpForceFlag=NCV77x9_CcpForceFlag&(~(0x01<<index)))
#define NCV77x9ClrCcpForceByte(void)	(NCV77x9_CcpForceFlag=0)
static void NCV77x9_vCcpOutputForce(void);

/*****************************************************************************
 Function      : NCV77x9_ForceIoControl_Write                                 
 Description   : Ccp control function
 Takes         : Nothing
 Return Value  : None                                                *
*****************************************************************************/
Std_ReturnType NCV77x9_u8ForceIoControl_Write(/*IN*/UInt32 ForceIoControlWord)
{
	tstCcpContronType CcpControlWord;
	CcpControlWord.CcpContronData=(uint16)ForceIoControlWord;
	CcpControlWord.CcpCommand=(uint8)(ForceIoControlWord>>16);
	CcpControlWord.CcpCommandFlag=(uint8)(ForceIoControlWord>>24);
	if(CcpControlWord.CcpCommandFlag==True)
	{
		switch(CcpControlWord.CcpCommand)
		{
			case 0:
				NCV77x9ClrCcpForceByte();
				break;
			case 0x81:
				NCV77x9SetCcpForceBit(NCV77x9_nSetMixMotor);
                NCV77x9ClrCcpForceBit(NCV77x9_nSetAllMotor);
				NCV77x9_CcpControlData[NCV77x9_nSetMixMotor]=CcpControlWord.CcpContronData;
				break;
			case 0x82:
				NCV77x9SetCcpForceBit(NCV77x9_nSetPsMixMotor);
                NCV77x9ClrCcpForceBit(NCV77x9_nSetAllMotor);
				NCV77x9_CcpControlData[NCV77x9_nSetPsMixMotor]=CcpControlWord.CcpContronData;
				break;
			case 0x83:
				NCV77x9SetCcpForceBit(NCV77x9_nSetAirdMotor);
                NCV77x9ClrCcpForceBit(NCV77x9_nSetAllMotor);
				NCV77x9_CcpControlData[NCV77x9_nSetAirdMotor]=CcpControlWord.CcpContronData;
				break;
			case 0x84:
				NCV77x9SetCcpForceBit(NCV77x9_nSetRfaMotor);
                NCV77x9ClrCcpForceBit(NCV77x9_nSetAllMotor);
				NCV77x9_CcpControlData[NCV77x9_nSetRfaMotor]=CcpControlWord.CcpContronData;
				break;
            case 0x86:
                NCV77x9ClrCcpForceBit(NCV77x9_nSetRfaMotor);
                NCV77x9SetCcpForceBit(NCV77x9_nSetAllMotor);
                NCV77x9_CcpControlData[NCV77x9_nSetAllMotor]=CcpControlWord.CcpContronData;
                break;
			default:
                return RTE_E_INVALID;
				//break;
		}
	}
	else
	{
		NCV77x9ClrCcpForceByte();
	}
        return RTE_E_OK;
}

/*****************************************************************************
 Function      : NCV77x9_vCcpOutputForce                                 
 Description   : force output value
 Takes         : Nothing
 Return Value  : None                                                *
*****************************************************************************/
static void NCV77x9_vCcpOutputForce(void)
{
	uint8 Motor0Direction=3u;//nStopped;
	uint8 Motor1Direction=3u;//nStopped;
	uint8 Motor2Direction=3u;//nStopped;
	uint8 Motor3Direction=3u;//nStopped;
    
	if(NCV77x9GetCcpForceBit(NCV77x9_nSetMixMotor))
	{
		Motor0Direction=NCV77x9_CcpControlData[NCV77x9_nSetMixMotor];
	}
	else
	{
	}
	if(NCV77x9GetCcpForceBit(NCV77x9_nSetAirdMotor))
	{
		Motor1Direction=NCV77x9_CcpControlData[NCV77x9_nSetAirdMotor];
	}
	else
	{
	}
	if(NCV77x9GetCcpForceBit(NCV77x9_nSetRfaMotor))
	{
		Motor2Direction=NCV77x9_CcpControlData[NCV77x9_nSetRfaMotor];
	}
	else
	{
	}
	if(NCV77x9GetCcpForceBit(NCV77x9_nSetPsMixMotor))
	{
		Motor3Direction=NCV77x9_CcpControlData[NCV77x9_nSetPsMixMotor];
	}
	else
	{
	}

	if(Motor0Direction==nStopped)
	{
		MDVR_u8ChannelCtrl(OutPutChannel1,MDVR_enOutputLow);
		MDVR_u8ChannelCtrl(OutPutChannel7,MDVR_enOutputLow);		
	}
	else
	{
		MDVR_u8ChannelCtrl(OutPutChannel7,(MDVR_enCtrlType)((Motor0Direction&0x01)+1));
		MDVR_u8ChannelCtrl(OutPutChannel1,(MDVR_enCtrlType)(((Motor0Direction>>1)&0x01)+1));
	}

	if(Motor1Direction==nStopped)
	{
		MDVR_u8ChannelCtrl(OutPutChannel3,MDVR_enOutputLow);
		MDVR_u8ChannelCtrl(OutPutChannel2,MDVR_enOutputLow);
	}
	else
	{
		MDVR_u8ChannelCtrl(OutPutChannel3,(MDVR_enCtrlType)((Motor1Direction&0x01)+1));
		MDVR_u8ChannelCtrl(OutPutChannel2,(MDVR_enCtrlType)(((Motor1Direction>>1)&0x01)+1));
	}
	if(Motor2Direction==nStopped)
	{
		MDVR_u8ChannelCtrl(OutPutChannel5,MDVR_enOutputLow);
		MDVR_u8ChannelCtrl(OutPutChannel6,MDVR_enOutputLow);		
	}
	else
	{
		MDVR_u8ChannelCtrl(OutPutChannel5,(MDVR_enCtrlType)((Motor2Direction&0x01)+1));
		MDVR_u8ChannelCtrl(OutPutChannel6,(MDVR_enCtrlType)(((Motor2Direction>>1)&0x01)+1));
	}
	if(Motor3Direction==nStopped)
	{
		MDVR_u8ChannelCtrl(OutPutChannel9,MDVR_enOutputLow);
		MDVR_u8ChannelCtrl(OutPutChannel10,MDVR_enOutputLow);		
	}
	else
	{
		MDVR_u8ChannelCtrl(OutPutChannel9,(MDVR_enCtrlType)((Motor2Direction&0x01)+1));
		MDVR_u8ChannelCtrl(OutPutChannel10,(MDVR_enCtrlType)(((Motor2Direction>>1)&0x01)+1));
	}
	MDVR_vDrvStatusUpdate();
}


void NCV77x9_vReset(void)
{
	MDVR_stInfo.u16ChannelCtrlStatus=1<<15;/*internal reset need*/
	MDVR_stInfo.u16ChannelFeedBackStatus=0;
	MDVR_stInfo.u16ChannelCtrlStatus2=1<<15;/*internal reset need*/
    MDVR_stInfo.u16ChannelCtrlStatus2 |=MDVR_HBSEL<<14;
	MDVR_stInfo.u16ChannelFeedBackStatus2=0;
	MDVR_stInfo.u8DrvReady=0;
	
	MDVR_EnPinEnable();
	SPI_vDrvInit_CH2();
	SPI_u16SlaveSelect_CH2(0,CSEnable);
	SPI_u16TransferData_CH2(&MDVR_stInfo.u16ChannelCtrlStatus, &MDVR_stInfo.u16ChannelFeedBackStatus,2);
	SPI_u16TransferData_CH2(&MDVR_stInfo.u16ChannelCtrlStatus2, &MDVR_stInfo.u16ChannelFeedBackStatus2,2);
	SPI_u16SlaveSelect_CH2(0,CSDisable);
	MDVR_stInfo.u8DrvReady=1;
	MDVR_stInfo.u16ChannelCtrlStatus=0;
	MDVR_stInfo.u16ChannelCtrlStatus2=0;
}

void MDVR_vShutdown(void)
{
	MDVR_stInfo.u16ChannelCtrlStatus=0;
	MDVR_stInfo.u16ChannelFeedBackStatus=0;
	MDVR_stInfo.u16ChannelCtrlStatus2=0;
    MDVR_stInfo.u16ChannelCtrlStatus2 |=MDVR_HBSEL<<14;
	MDVR_stInfo.u16ChannelFeedBackStatus2=0;
	MDVR_stInfo.u8DrvReady=0;

	MDVR_EnPinEnable();
	SPI_vDrvInit_CH2();
	
	SPI_u16SlaveSelect_CH2(0,CSEnable);
	SPI_u16TransferData_CH2(&MDVR_stInfo.u16ChannelCtrlStatus, &MDVR_stInfo.u16ChannelFeedBackStatus,2);
	SPI_u16TransferData_CH2(&MDVR_stInfo.u16ChannelCtrlStatus2, &MDVR_stInfo.u16ChannelFeedBackStatus2,2);
	SPI_u16SlaveSelect_CH2(0,CSDisable);
	MDVR_EnPinDisable();
}

void NCV77x9_vInit(void)
{
	MDVR_stInfo.u16ChannelCtrlStatus=1<<15;/*internal reset need*/
	MDVR_stInfo.u16ChannelFeedBackStatus=0;
	MDVR_stInfo.u16ChannelCtrlStatus2=1<<15;/*internal reset need*/
	MDVR_stInfo.u16ChannelCtrlStatus2 |=MDVR_HBSEL<<14;    
	MDVR_stInfo.u16ChannelFeedBackStatus2=0;
    MDVR_stInfo.u8DrvReady=0;

    MDVR_EnPinEnable();
	SPI_vDrvInit_CH2();
	SPI_u16SlaveSelect_CH2(0,CSEnable);
	SPI_u16TransferData_CH2(&MDVR_stInfo.u16ChannelCtrlStatus, &MDVR_stInfo.u16ChannelFeedBackStatus,2);
	SPI_u16TransferData_CH2(&MDVR_stInfo.u16ChannelCtrlStatus2, &MDVR_stInfo.u16ChannelFeedBackStatus2,2);
	SPI_u16SlaveSelect_CH2(0,CSDisable);
    MDVR_stInfo.u8DrvReady=1;
	MDVR_stInfo.u16ChannelCtrlStatus=0;/*internal reset clrean*/
	MDVR_stInfo.u16ChannelCtrlStatus2=0;

    NCV77x9ClrCcpForceByte();
}

void NCV77x9_vDeinit(void)
{
	
	/*may do nothing in init, it may be working in KL15=OFF*/
    MDVR_vShutdown();

    NCV77x9ClrCcpForceByte();
}

uint8 MDVR_u8ChannelCtrl(uint8 channel, MDVR_enCtrlType status)
{
#define MDVR_ClearChannelBit(ch)	MDVR_stInfo.u16ChannelCtrlStatus &=~((1<<(7+ch)) | (1<<(1+ch)))
#define MDVR_ClearChannel2Bit(ch)	MDVR_stInfo.u16ChannelCtrlStatus2 &=~((1<<(7+ch)) | (1<<(1+ch)))
	
	if(status>MDVR_enOutputHigh)
	{
		DET_vErrReport(MDVR_enErrParaOutOfRange);
		return MDVR_enErrParaOutOfRange;
	}

    #if 0
	if(((1<<channel) & MDVR_u8ChannlMaks)==0)
	{
		DET_vErrReport(MDVR_enErrChannleOutOfRange);
		return MDVR_enErrChannleOutOfRange;
	}
    #endif
		
	if(MDVR_stInfo.u8DrvReady==0)
	{
		DET_vErrReport(MDVR_enErrDrvNotReady);
		return MDVR_enErrDrvNotReady;
	}
	
	if(MDVR_stInfo.u8DrvReady==MDVR_enErrDrvFatalErr)
	{
		DET_vErrReport(MDVR_enErrDrvFatalErr);
		return MDVR_enErrDrvFatalErr;
	}
	if(channel<OutPutChannel7)
	{
    	/*clear bits for control*/
    	MDVR_ClearChannelBit(channel);
    	
    	MDVR_stInfo.u16ChannelCtrlStatus |=MDVR_OverVoltageLockOutEnable<<0;
    	MDVR_stInfo.u16ChannelCtrlStatus |=MDVR_UnderLoadDetEnable<<13;
    	
    	if(status == MDVR_enHighZ)
    	{
    		/*disable channel and set the output bits to 0*/
    		MDVR_ClearChannelBit(channel);
    	}
    	else if(status == MDVR_enOutputLow)
    	{
    		MDVR_stInfo.u16ChannelCtrlStatus |=(1<<(7+channel));
    		MDVR_stInfo.u16ChannelCtrlStatus &=~(1<<(1+channel));
    		
    	} 
    	else if(status == MDVR_enOutputHigh)
    	{
    		MDVR_stInfo.u16ChannelCtrlStatus |=(1<<(7+channel)) | (1<<(1+channel));
    	} 
	}
    else
    {
    	/*clear bits for control*/
    	MDVR_ClearChannel2Bit(channel-OutPutChannel7);
    	
    	MDVR_stInfo.u16ChannelCtrlStatus2 |=MDVR_OverVoltageLockOutEnable<<0;
    	MDVR_stInfo.u16ChannelCtrlStatus2 |=MDVR_UnderLoadDetEnable<<13;
        MDVR_stInfo.u16ChannelCtrlStatus2 |=MDVR_HBSEL<<14;
    	
    	if(status == MDVR_enHighZ)
    	{
    		/*disable channel and set the output bits to 0*/
    		MDVR_ClearChannel2Bit(channel-OutPutChannel7);
    	}
    	else if(status == MDVR_enOutputLow)
    	{
    		MDVR_stInfo.u16ChannelCtrlStatus2 |=(1<<(7+channel-OutPutChannel7));
    		MDVR_stInfo.u16ChannelCtrlStatus2 &=~(1<<(1+channel-OutPutChannel7));
    		
    	} 
    	else if(status == MDVR_enOutputHigh)
    	{
    		MDVR_stInfo.u16ChannelCtrlStatus2 |=(1<<(7+channel-OutPutChannel7)) | (1<<(1+channel-OutPutChannel7));
    	} 
	}
	
	return MDVR_enErrOK;
	
}

void MDVR_vDrvStatusUpdate(void)
{
	uint8 i;
	SPI_u16SlaveSelect_CH2(0,CSEnable);
	if(SPI_u16TransferData_CH2(&MDVR_stInfo.u16ChannelCtrlStatus, &MDVR_stInfo.u16ChannelFeedBackStatus,2)==1)
	{
		MDVR_vErrTSDProcess();
	}
	SPI_u16SlaveSelect_CH2(0,CSDisable);
	for(i=100;i>0;)
	{
		i--;
	}
	SPI_u16SlaveSelect_CH2(0,CSEnable);
	if(SPI_u16TransferData_CH2(&MDVR_stInfo.u16ChannelCtrlStatus2, &MDVR_stInfo.u16ChannelFeedBackStatus2,2)==1)
	{
		MDVR_vErrTSDProcess();
	}
	SPI_u16SlaveSelect_CH2(0,CSDisable);
	MDVR_vErrProcess(MDVR_stInfo.u16ChannelFeedBackStatus);
}
/*****************************************************************************
 AUTHOR:		 : Li Jiaye											  *
 DATE: 		 : 2015/07/22										  *
 Function      : NCV77x9_vActive                                                   *
 Description   : 
 Return Value  : None                                                        *
*****************************************************************************/
void NCV77x9_vActive(void)
{
}

void NCV77x9_vMain(void)
{
	DCM_tenPortState Motor0Direction;
	DCM_tenPortState Motor1Direction;
	DCM_tenPortState Motor2Direction;
	DCM_tenPortState Motor3Direction;
    uint8 RdcReq;
    uint8 AcccReq;

    DCM_enGetEnMotorDiretionExport(DCM_nMixDrMotor,&Motor0Direction);
    DCM_enGetEnMotorDiretionExport(DCM_nAirdMotor,&Motor1Direction);
    DCM_enGetEnMotorDiretionExport(DCM_nRFAMotor,&Motor2Direction);
    DCM_enGetEnMotorDiretionExport(DCM_nMixPsMotor,&Motor3Direction);

    RdcReq = RDC_u8GetValue(RDC_nu8Request);
    AcccReq = ACCC_u8GetValue(ACCC_nu8AcActualRequest);

    if(NCV77x9GetCcpForceBit(NCV77x9_nSetMixMotor))
	{
		Motor0Direction=NCV77x9_CcpControlData[NCV77x9_nSetMixMotor];
	}
	else
	{
	}
	if(NCV77x9GetCcpForceBit(NCV77x9_nSetAirdMotor))
	{
		Motor1Direction=NCV77x9_CcpControlData[NCV77x9_nSetAirdMotor];
	}
	else
	{
	}
	if(NCV77x9GetCcpForceBit(NCV77x9_nSetRfaMotor))
	{
		Motor2Direction=NCV77x9_CcpControlData[NCV77x9_nSetRfaMotor];
	}
	else
	{
	}
	if(NCV77x9GetCcpForceBit(NCV77x9_nSetPsMixMotor))
	{
		Motor3Direction=NCV77x9_CcpControlData[NCV77x9_nSetPsMixMotor];
	}
	else
	{
	}
    
    if(NCV77x9GetCcpForceBit(NCV77x9_nSetAllMotor))
    {
        switch(NCV77x9_CcpControlData[NCV77x9_nSetAllMotor])
        {
            case 0x00:
                MDVR_u8ChannelCtrl(OutPutChannel1,MDVR_enOutputLow);
                MDVR_u8ChannelCtrl(OutPutChannel2,MDVR_enOutputLow);
                MDVR_u8ChannelCtrl(OutPutChannel3,MDVR_enOutputLow);
                MDVR_u8ChannelCtrl(OutPutChannel4,MDVR_enOutputLow);
                MDVR_u8ChannelCtrl(OutPutChannel5,MDVR_enOutputLow);
                MDVR_u8ChannelCtrl(OutPutChannel6,MDVR_enOutputLow);
                MDVR_u8ChannelCtrl(OutPutChannel7,MDVR_enOutputLow);
                MDVR_u8ChannelCtrl(OutPutChannel8,MDVR_enOutputLow);
                MDVR_u8ChannelCtrl(OutPutChannel9,MDVR_enOutputLow);
                MDVR_u8ChannelCtrl(OutPutChannel10,MDVR_enOutputLow);
                break;
            case 0x05:
                MDVR_u8ChannelCtrl(OutPutChannel1,MDVR_enOutputHigh);
                MDVR_u8ChannelCtrl(OutPutChannel2,MDVR_enOutputLow);
                MDVR_u8ChannelCtrl(OutPutChannel3,MDVR_enOutputHigh);
                MDVR_u8ChannelCtrl(OutPutChannel4,MDVR_enOutputLow);
                MDVR_u8ChannelCtrl(OutPutChannel5,MDVR_enOutputHigh);
                MDVR_u8ChannelCtrl(OutPutChannel6,MDVR_enOutputLow);
                MDVR_u8ChannelCtrl(OutPutChannel7,MDVR_enOutputHigh);
                MDVR_u8ChannelCtrl(OutPutChannel8,MDVR_enOutputLow);
                MDVR_u8ChannelCtrl(OutPutChannel9,MDVR_enOutputHigh);
                MDVR_u8ChannelCtrl(OutPutChannel10,MDVR_enOutputLow);
                break;
            case 0x0A:
                MDVR_u8ChannelCtrl(OutPutChannel1,MDVR_enOutputLow);
                MDVR_u8ChannelCtrl(OutPutChannel2,MDVR_enOutputHigh);
                MDVR_u8ChannelCtrl(OutPutChannel3,MDVR_enOutputLow);
                MDVR_u8ChannelCtrl(OutPutChannel4,MDVR_enOutputHigh);
                MDVR_u8ChannelCtrl(OutPutChannel5,MDVR_enOutputLow);
                MDVR_u8ChannelCtrl(OutPutChannel6,MDVR_enOutputHigh);
                MDVR_u8ChannelCtrl(OutPutChannel7,MDVR_enOutputLow);
                MDVR_u8ChannelCtrl(OutPutChannel8,MDVR_enOutputHigh);
                MDVR_u8ChannelCtrl(OutPutChannel9,MDVR_enOutputLow);
                MDVR_u8ChannelCtrl(OutPutChannel10,MDVR_enOutputHigh);
                break;
            case 0xFF:
                MDVR_u8ChannelCtrl(OutPutChannel1,MDVR_enOutputHigh);
                MDVR_u8ChannelCtrl(OutPutChannel2,MDVR_enOutputHigh);
                MDVR_u8ChannelCtrl(OutPutChannel3,MDVR_enOutputHigh);
                MDVR_u8ChannelCtrl(OutPutChannel4,MDVR_enOutputHigh);
                MDVR_u8ChannelCtrl(OutPutChannel5,MDVR_enOutputHigh);
                MDVR_u8ChannelCtrl(OutPutChannel6,MDVR_enOutputHigh);
                MDVR_u8ChannelCtrl(OutPutChannel7,MDVR_enOutputHigh);
                MDVR_u8ChannelCtrl(OutPutChannel8,MDVR_enOutputHigh);
                MDVR_u8ChannelCtrl(OutPutChannel9,MDVR_enOutputHigh);
                MDVR_u8ChannelCtrl(OutPutChannel10,MDVR_enOutputHigh);
                break;
        }
    }
    else
    {
    	if((Motor0Direction==nStopped) || (Motor0Direction == nNoError))
    	{
    		MDVR_u8ChannelCtrl(OutPutChannel1,MDVR_enOutputLow);
    		MDVR_u8ChannelCtrl(OutPutChannel7,MDVR_enOutputLow);		
    	}
    	else
    	{
    		MDVR_u8ChannelCtrl(OutPutChannel7,(MDVR_enCtrlType)((Motor0Direction&0x01)+1));
    		MDVR_u8ChannelCtrl(OutPutChannel1,(MDVR_enCtrlType)(((Motor0Direction>>1)&0x01)+1));
    	}
        
    	if((Motor1Direction==nStopped) || (Motor1Direction == nNoError))
    	{
    		MDVR_u8ChannelCtrl(OutPutChannel3,MDVR_enOutputLow);
    		MDVR_u8ChannelCtrl(OutPutChannel2,MDVR_enOutputLow);
    	}
    	else
    	{
    		MDVR_u8ChannelCtrl(OutPutChannel3,(MDVR_enCtrlType)((Motor1Direction&0x01)+1));
    		MDVR_u8ChannelCtrl(OutPutChannel2,(MDVR_enCtrlType)(((Motor1Direction>>1)&0x01)+1));
    	}
    	if((Motor2Direction==nStopped) || (Motor2Direction == nNoError))
    	{
    		MDVR_u8ChannelCtrl(OutPutChannel5,MDVR_enOutputLow);
    		MDVR_u8ChannelCtrl(OutPutChannel6,MDVR_enOutputLow);		
    	}
    	else
    	{
    		MDVR_u8ChannelCtrl(OutPutChannel5,(MDVR_enCtrlType)((Motor2Direction&0x01)+1));
    		MDVR_u8ChannelCtrl(OutPutChannel6,(MDVR_enCtrlType)(((Motor2Direction>>1)&0x01)+1));
    	}
    	if((Motor3Direction==nStopped) || (Motor3Direction == nNoError))
    	{
    		MDVR_u8ChannelCtrl(OutPutChannel9,MDVR_enOutputLow);
    		MDVR_u8ChannelCtrl(OutPutChannel10,MDVR_enOutputLow);		
    	}
    	else
    	{
    		MDVR_u8ChannelCtrl(OutPutChannel9,(MDVR_enCtrlType)((Motor3Direction&0x01)+1));
    		MDVR_u8ChannelCtrl(OutPutChannel10,(MDVR_enCtrlType)(((Motor3Direction>>1)&0x01)+1));
    	}

    	if(RdcReq==False)
    	{
    		MDVR_u8ChannelCtrl(OutPutChannel4,MDVR_enHighZ);
    	}
    	else
    	{	
    		MDVR_u8ChannelCtrl(OutPutChannel4,MDVR_enOutputLow);
    	}

    	if(AcccReq==False)
    	{
    		MDVR_u8ChannelCtrl(OutPutChannel8,MDVR_enOutputLow);
    	}
    	else
    	{	
    		MDVR_u8ChannelCtrl(OutPutChannel8,MDVR_enOutputHigh);
    	}
    }

	MDVR_vDrvStatusUpdate();
}

/*******************************************************************************

function :void MDVR_vErrProcess(uint16 u16ErrFeedBack)

Driver status feedback data struct:

PRE_bit15 : Latched Thermal Shutdown
			0 = No Fault
			1 = Fault
			
bit15:Over Current Shutdown Global Notification
			0 = No Fault
			1 = Fault			
bit14:Power Supply Failure on VS1 and/or VS2 Under Voltage and Over Voltage Monitoring
			0 = No Fault
			1 = Fault			
bit13:Under Load Detection Global Notification
			0 = No Fault
			1 = Fault		
			
bit12-11:Half Bridge 6 Status			
bit10-9:Half Bridge 5 Status
bit8-7:Half Bridge 4 Status
bit6-5:Half Bridge 3 Status
bit4-3:Half Bridge 2 Status
bit2-1:Half Bridge 1 Status
		00b 每 Output Disable
		01b 每 Over Current Shutdown
		10b 每 Under Load Detection
		11b 每 Output Enabled 	
		
bit0:Thermal Warning Global Notification
			0 = No Fault
			1 = Fault

***********************************************************************************/

uint16 MDVR_u16GetFeedBackStatus(void)
{
	return MDVR_stInfo.u16ChannelFeedBackStatus;
}

