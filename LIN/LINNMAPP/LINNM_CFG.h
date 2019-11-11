/**************************** .FILE_HEADER_BEGIN *****************************
 .FILE; [ LINNM_cfg.h]
 .Author; [ Liu Fuguang]
 .Date; 2016/12/30
 .Update Time; 11:43:29
 .Gen File Name: SX11P_LIN_V1.0_2016-12-29.xlsx
****************************** .FILE_HEADER_END ******************************/
#ifndef LINNM_CFG_H
#define LINNM_CFG_H
#ifndef LINNM
#define ext extern
#else
#define ext
#endif
/****************************************************************************/
/*****************           HARDWARE CONFIGURATION            *************************/
/*****************                                                            *************************/
/****************************************************************************/
#if 0
/* RLIN30RX is P0_3, RLIN30TX is P0_2     (2nd Alternative) */
#define LIN0_SET_PFC     do { PFC0    |= 0x000C; } while(0)
#define LIN0_SET_PFCE    do { PFCE0   &= 0xFFF3; } while(0)
#define LIN0_SET_PFCAE   do { PFCAE0  &= 0xFFF3; } while(0)
#define LIN0_SET_PMC     do { PMC0    |= 0x000C; } while(0)
#define LIN0_SET_PM      do { PM0     |= 0x0008; \
                          PM0     &= 0xFFFB; } while(0)
#define LIN0_SET_RX_PU   do { PU0     |= 0x0008; } while(0)
#endif
/* RLIN30RX is P0_3(GE-T IS P10_9), RLIN30TX is P0_2(FE-T IS P10_10)     (2nd Alternative) */
#define LIN0_SET_PFC     do { PFC10    |= 0x0600; } while(0)
#define LIN0_SET_PFCE    do { PFCE10   &= 0xF9FF; } while(0)
#define LIN0_SET_PFCAE   do { PFCAE10  &= 0xF9FF; } while(0)
#define LIN0_SET_PMC     do { PMC10    |= 0x0600; } while(0)
#define LIN0_SET_PM      do { PM10     |= 0x0200; \
                          PM10     &= 0xFBFF; } while(0)
#define LIN0_SET_RX_PU   do { PU10     |= 0x0200; } while(0)

/* Interrupt Priority of the Tx/Rx/Status interrupts -
*  must be an integer from 0-7, inclusive.
*  0=highest priority, 7=lowest priority */
#define LIN_COMM_INT_PRIO       7u
/* Interrupt Priority of the wake interrupt -
*  must be an integer from 0-7, inclusive.
*  0=highest priority, 7=lowest priority */
#define LIN_WAKE_INT_PRIO       1u

#define LIN_CLR_INT_PRIO     ((uint16)0xFFF8)
#define LIN_SET_INT_PRIO     ((uint16)LIN_COMM_INT_PRIO)
#define LIN_SET_WAKE_INT_PRIO ((uint16)LIN_WAKE_INT_PRIO)
#define LIN0_SET_INT_PRIO    do { ICRLIN30UR0 &= LIN_CLR_INT_PRIO; \
                          ICRLIN30UR0 |= LIN_SET_INT_PRIO; \
                          ICRLIN30UR1 &= LIN_CLR_INT_PRIO; \
                          ICRLIN30UR1 |= LIN_SET_INT_PRIO; \
                          ICRLIN30UR2 &= LIN_CLR_INT_PRIO; \
                          ICRLIN30UR2 |= LIN_SET_INT_PRIO; \
                          ICP10       &= LIN_CLR_INT_PRIO; \
                          ICP10       |= LIN_SET_WAKE_INT_PRIO;} while(0)

/****************************************************************************/
/*****************                 Input Interface                        *************************/
/*****************    Need to configurate when Integration       *************************/
/****************************************************************************/
#define LINNM_McuStopModeUse	Yes

//#define  LINNM_u16LocalWakeUpPinCfg     HAL_PinConfig(0,6,1)
//#define  LINNM_nIGN2PortPin (0x0006)
#define  LINNM_u16LocalWakeUp(u8temp)   True //MCU_u16PinRead((MUC_enPinID)LINNM_nIGN2PortPin,u8temp)//HAL_PinRead(0,6)
#define  LINNM_u16CanWakeUp    	        True// CANAPP_u16GetValue(CANAPP_nu16KeepAlive)

#define LINNM_u16VolLo 	POW_u16GetValue(POW_nu16ComLowVoltage)	
#define LINNM_u16VolHi 	POW_u16GetValue(POW_nu16ComHighVoltage)	

#define LINNM_ST_APP_ON		False //SchTb_FE5DB7DA_IgOn
#define LINNM_ST_APP_ACTIVE	False //SchTb_FE5DB7DA_IgOff /*FE-3ZA do not have schedule of ACTIVE state*/

#define LINNM_ST_DIAG_REQUEST	False //SchTb_FE5DB7DA_IgOn
#define LINNM_ST_DIAG_RESPONE	False //SchTb_FE5DB7DA_IgOn


#undef ext
#endif
