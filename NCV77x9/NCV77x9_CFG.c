/**************************** .FILE_HEADER_BEGIN *****************************
  .TITLE   DC Motor Driver for NCV77x9, 	                             ]
*-----------------------------------------------------------------------------
  .FILE   NCV77x9_cfg.c                                                      ]
   .AUTHOR [  tan fumin 				                                     ]
*-----------------------------------------------------------------------------
NOTE:
		This software package only for DC motor driver nvc771!
 	
 Version Date        Author                       Change
 -----------------------------------------------------------------------------
 Rev 1.0 2015-4-28   tan fumin         module template update. 
 
****************************** .FILE_HEADER_END ******************************/
//#include "hal.h"
#include "Std_Types.h"

/*Latched Thermal Shutdown error process*/
void MDVR_vErrTSDProcess(void)
{
	
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
void MDVR_vErrProcess(uint16 u16ErrFeedBack)
{
	
}




