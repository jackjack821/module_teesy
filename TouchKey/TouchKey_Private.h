/***************************************************************************************************
                                       Touch KEY PROCESS
  .File Name: TouchKey_Private.h
  
  .Description: Thie file is used to include the macro used for key module only.

  --------------------------------------------------------------------------------------------------
  Version     Date            Author            Change

  --------------------------------------------------------------------------------------------------
  Rev 1.0     2017/11/06      Zhong Bin     	The first version            
***************************************************************************************************/
#ifndef TOUCHKEY_PRIVATE_H
#define TOUCHKEY_PRIVATE_H

/* System-headerfiles */

/* Foreign headerfiles */

/* Own headerfiles */
#include "TouchKey_Type.h"

/***************************************************************************************************
                                    EXTERNAL MODULE INTERFACE
***************************************************************************************************/

/***************************************************************************************************
                                    INTERNAL MODULE INTERFACE
***************************************************************************************************/

#define TOUCHKEY_nMainPageAttribute \
{\
    	/*KeyID*/ 					/*X_Min,X_Max,Y_Min,Y_Max, KeyCurrstatu	  KeyLastStatus, 		KeyEffectAction 	valid state */ \
    	{TOUCHKEY_nu32MainCCPage, 47u, 162u, 35u, 105u, TOUCHKEY_nRelease, TOUCHKEY_nRelease,TOUCHKEY_nPress,False},\
    	{TOUCHKEY_nu32MainSeatPage, 174u, 274u, 35u, 105u, TOUCHKEY_nRelease, TOUCHKEY_nRelease,TOUCHKEY_nPress,False},\
    	{TOUCHKEY_nu32MainBodyPage, 286u, 386u, 35u, 105u, TOUCHKEY_nRelease, TOUCHKEY_nRelease,TOUCHKEY_nPress,False},\
    	{TOUCHKEY_nu32MainDrivePage, 398u, 498, 35u, 105u, TOUCHKEY_nRelease, TOUCHKEY_nRelease,TOUCHKEY_nPress,False},\
	{TOUCHKEY_nu32MainOutPage,510u,560u,35u,105u,TOUCHKEY_nRelease, TOUCHKEY_nRelease,TOUCHKEY_nPress,False},\
}


#define TOUCHKEY_nSeatModePageAttribute \
{\
    	/*KeyID*/ 					/*X_Min,X_Max,Y_Min,Y_Max, KeyCurrstatu	  KeyLastStatus, 		KeyEffectAction 	valid state */ \
	{TOUCHKEY_nSeatPAGE_1, 203u, 1071u, 163u, 556u, TOUCHKEY_nRelease, TOUCHKEY_nRelease,TOUCHKEY_nRelease,False},\
	{TOUCHKEY_nSeatPAGE_2,290u,1012u,660u,710u,TOUCHKEY_nRelease, TOUCHKEY_nRelease,TOUCHKEY_nRelease,False},\
	{TOUCHKEY_nSeatPAGE_3, 203u, 1071u, 163u, 556u, TOUCHKEY_nRelease, TOUCHKEY_nRelease,TOUCHKEY_nRelease,False},\
	{TOUCHKEY_nSeatPAGE_4,290u,1012u,660u,710u,TOUCHKEY_nRelease, TOUCHKEY_nRelease,TOUCHKEY_nRelease,False},\
	{TOUCHKEY_nSeatPAGE_5, 203u, 1071u, 163u, 556u, TOUCHKEY_nRelease, TOUCHKEY_nRelease,TOUCHKEY_nRelease,False},\
	{TOUCHKEY_nSeatPAGE_6,290u,1012u,660u,710u,TOUCHKEY_nRelease, TOUCHKEY_nRelease,TOUCHKEY_nRelease,False},\
	{TOUCHKEY_nSeatPAGE_7, 203u, 1071u, 163u, 556u, TOUCHKEY_nRelease, TOUCHKEY_nRelease,TOUCHKEY_nRelease,False},\
	{TOUCHKEY_nSeatPAGE_8,290u,1012u,660u,710u,TOUCHKEY_nRelease, TOUCHKEY_nRelease,TOUCHKEY_nRelease,False},\
	{TOUCHKEY_nSeatPAGE_9, 203u, 1071u, 163u, 556u, TOUCHKEY_nRelease, TOUCHKEY_nRelease,TOUCHKEY_nRelease,False},\
	{TOUCHKEY_nSeatPAGE_10,290u,1012u,660u,710u,TOUCHKEY_nRelease, TOUCHKEY_nRelease,TOUCHKEY_nRelease,False},\
}

#define TOUCHKEY_nBodyModePageAttribute \
{\
    	/*KeyID*/ 				/*X_Min,X_Max,Y_Min,Y_Max, KeyCurrstatu	  KeyLastStatus, 		KeyEffectAction 	valid state */ \
    	{TOUCHKEY_nBodyPAGE_1, 49u,221u,163u,255u,TOUCHKEY_nRelease, TOUCHKEY_nRelease,TOUCHKEY_nPress,False},\
    	{TOUCHKEY_nBodyPAGE_2, 250u,400u,163u,255u,  TOUCHKEY_nRelease, TOUCHKEY_nRelease,TOUCHKEY_nPress,False},\
    	{TOUCHKEY_nBodyPAGE_3, 429u,601u,163u,255u, TOUCHKEY_nRelease, TOUCHKEY_nRelease,TOUCHKEY_nPress,False},\
    	{TOUCHKEY_nBodyPAGE_4, 49u,221u,303u,395u, TOUCHKEY_nRelease, TOUCHKEY_nRelease,TOUCHKEY_nPress,False},\
    	{TOUCHKEY_nBodyPAGE_5, 250u,400u,303u,395u, TOUCHKEY_nRelease, TOUCHKEY_nRelease,TOUCHKEY_nPress,False},\
    	{TOUCHKEY_nBodyPAGE_6, 1319u,1491u,163u,255u, TOUCHKEY_nRelease, TOUCHKEY_nRelease,TOUCHKEY_nPress,False},\
    	{TOUCHKEY_nBodyPAGE_7, 1509u,1681u,163u,255u, TOUCHKEY_nRelease, TOUCHKEY_nRelease,TOUCHKEY_nPress,False},\
    	{TOUCHKEY_nBodyPAGE_8, 1710u,1860u,163u,255u, TOUCHKEY_nRelease, TOUCHKEY_nRelease,TOUCHKEY_nPress,False},\
	{TOUCHKEY_nBodyPAGE_9, 1509u,1681u,304u,396u, TOUCHKEY_nRelease, TOUCHKEY_nRelease,TOUCHKEY_nPress,False},\
	{TOUCHKEY_nBodyPAGE_10, 1699u,1871u,304u,396u, TOUCHKEY_nRelease, TOUCHKEY_nRelease,TOUCHKEY_nPress,False},\
}

#define TOUCHKEY_nDriveModePageAttribute \
{\
    	/*KeyID*/ 				/*X_Min,X_Max,Y_Min,Y_Max, KeyCurrstatu	  KeyLastStatus, 		KeyEffectAction 	valid state */ \
    	{TOUCHKEY_nDrive_PAGE_1, 506u,726u,638u,720u,TOUCHKEY_nRelease, TOUCHKEY_nRelease,TOUCHKEY_nPress,False},\
    	{TOUCHKEY_nDrive_PAGE_2, 740u,953u,638u,720u,  TOUCHKEY_nRelease, TOUCHKEY_nRelease,TOUCHKEY_nPress,False},\
    	{TOUCHKEY_nDrive_PAGE_3, 967u,1180u,638u,720u, TOUCHKEY_nRelease, TOUCHKEY_nRelease,TOUCHKEY_nPress,False},\
    	{TOUCHKEY_nDrive_PAGE_4, 1194u,1414u,638u,720u, TOUCHKEY_nRelease, TOUCHKEY_nRelease,TOUCHKEY_nPress,False},\
    	{TOUCHKEY_nDrive_PAGE_5, 2000u,4000u,2000u,4000u, TOUCHKEY_nRelease, TOUCHKEY_nRelease,TOUCHKEY_nPress,False},\
    	{TOUCHKEY_nDrive_PAGE_6, 2000u,4000u,2000u,4000u, TOUCHKEY_nRelease, TOUCHKEY_nRelease,TOUCHKEY_nPress,False},\
    	{TOUCHKEY_nDrive_PAGE_7, 2000u,4000u,2000u,4000u, TOUCHKEY_nRelease, TOUCHKEY_nRelease,TOUCHKEY_nPress,False},\
    	{TOUCHKEY_nDrive_PAGE_8, 2000u,4000u,2000u,4000u, TOUCHKEY_nRelease, TOUCHKEY_nRelease,TOUCHKEY_nPress,False},\
}

#if 0
#define TOUCHKEY_nCCModePageAttribute_R \
{\
    	/*KeyID*/ 						/*X_Min,X_Max,Y_Min,Y_Max, KeyCurrstatu	  KeyLastStatus, 		KeyEffectAction 	valid state */ \
	{TOUCHKEY_nCCMode_Button_R_1, 55u,60u,0u,5u, TOUCHKEY_nRelease, TOUCHKEY_nRelease,TOUCHKEY_nPress,False},\
	{TOUCHKEY_nCCMode_Button_R_2, 65u,100u,10u,40u, TOUCHKEY_nRelease, TOUCHKEY_nRelease,TOUCHKEY_nPress,False},\
	{TOUCHKEY_nCCMode_Button_R_3, 85u,100u,75u,90u, TOUCHKEY_nRelease, TOUCHKEY_nRelease,TOUCHKEY_nPress,False},\
	{TOUCHKEY_nCCMode_Button_R_4, 55u,65u,95u,100u, TOUCHKEY_nRelease, TOUCHKEY_nRelease,TOUCHKEY_nPress,False},\
	{TOUCHKEY_nCCMode_Button_R_5, 23u,28u,15u,20u, TOUCHKEY_nRelease, TOUCHKEY_nRelease,TOUCHKEY_nPress,False},\
	{TOUCHKEY_nCCMode_Button_R_6, 23u,28u,25u,32u, TOUCHKEY_nRelease, TOUCHKEY_nRelease,TOUCHKEY_nPress,False},\
	{TOUCHKEY_nCCMode_Button_R_7, 38u,48u,68u,85u, TOUCHKEY_nRelease, TOUCHKEY_nRelease,TOUCHKEY_nPress,False},\
	{TOUCHKEY_nCCMode_Button_R_8, 6u,10u,20u,25u, TOUCHKEY_nRelease, TOUCHKEY_nRelease,TOUCHKEY_nPress,False},\
	{TOUCHKEY_nCCMode_Button_R_9, 10u,20u,95u,100u, TOUCHKEY_nRelease, TOUCHKEY_nRelease,TOUCHKEY_nPress,False},\
	{TOUCHKEY_nCCMode_Button_R_10, 989u,1782u,236u,370u, TOUCHKEY_nRelease, TOUCHKEY_nRelease,TOUCHKEY_nPress,False},\
	{TOUCHKEY_nCCMode_Button_R_11, 138u,931u,370u,504u, TOUCHKEY_nRelease, TOUCHKEY_nRelease,TOUCHKEY_nPress,False},\
	{TOUCHKEY_nCCMode_Button_R_12, 989u,1782u,370u,504u, TOUCHKEY_nRelease, TOUCHKEY_nRelease,TOUCHKEY_nPress,False},\
}
#endif


#define TOUCHKEY_nCCModePageAttribute \
{\
    	/*KeyID*/ 	/*X_Min,X_Max,Y_Min,Y_Max, KeyCurrstatu	  KeyLastStatus, 		KeyEffectAction 	valid state */ \
	{TOUCHKEY_nCCMode_Button_L_1, 43u,74,0u,10u, TOUCHKEY_nRelease, TOUCHKEY_nRelease,TOUCHKEY_nPress,False},\
	{TOUCHKEY_nCCMode_Button_L_2, 0u,22u,0u,11u, TOUCHKEY_nRelease, TOUCHKEY_nRelease,TOUCHKEY_nPress,False},\
       {TOUCHKEY_nCCMode_Button_L_3, 85u,100u,29u,42u, TOUCHKEY_nRelease, TOUCHKEY_nRelease,TOUCHKEY_nPress,False},\
	{TOUCHKEY_nCCMode_Button_L_4, 50u,85u,25u,45u, TOUCHKEY_nRelease, TOUCHKEY_nRelease,TOUCHKEY_nPress,False},\
	{TOUCHKEY_nCCMode_Button_L_5, 0u,45u,25u,50u, TOUCHKEY_nRelease, TOUCHKEY_nRelease,TOUCHKEY_nPress,False},\
	{TOUCHKEY_nCCMode_Button_L_6, 55u,75u,55u,75u, TOUCHKEY_nRelease, TOUCHKEY_nRelease,TOUCHKEY_nPress,False},\
	{TOUCHKEY_nCCMode_Button_L_7, 17u,40u,64u,90u, TOUCHKEY_nRelease, TOUCHKEY_nRelease,TOUCHKEY_nPress,False},\
	{TOUCHKEY_nCCMode_Button_L_8, 69u,100u,91u,100u, TOUCHKEY_nRelease, TOUCHKEY_nRelease,TOUCHKEY_nPress,False},\
	{TOUCHKEY_nCCMode_Button_L_9, 20u,61u,91u,100u, TOUCHKEY_nRelease, TOUCHKEY_nRelease,TOUCHKEY_nPress,False},\
	{TOUCHKEY_nCCMode_Button_L_10, 138u,138u,138u,138u, TOUCHKEY_nRelease, TOUCHKEY_nRelease,TOUCHKEY_nPress,False},\
	{TOUCHKEY_nCCMode_Button_R_1, 79u,100u,86u,100u, TOUCHKEY_nRelease, TOUCHKEY_nRelease,TOUCHKEY_nPress,False},\
	{TOUCHKEY_nCCMode_Button_R_2, 29u,65u,80u,100u, TOUCHKEY_nRelease, TOUCHKEY_nRelease,TOUCHKEY_nPress,False},\
	{TOUCHKEY_nCCMode_Button_R_3, 69u,100u,45u,70u, TOUCHKEY_nRelease, TOUCHKEY_nRelease,TOUCHKEY_nPress,False},\
	{TOUCHKEY_nCCMode_Button_R_4, 20u,60u,46u,68u, TOUCHKEY_nRelease, TOUCHKEY_nRelease,TOUCHKEY_nPress,False},\
	{TOUCHKEY_nCCMode_Button_R_5, 0u,15u,58u,75u, TOUCHKEY_nRelease, TOUCHKEY_nRelease,TOUCHKEY_nPress,False},\
	{TOUCHKEY_nCCMode_Button_R_6, 60u,80u,10u,30u, TOUCHKEY_nRelease, TOUCHKEY_nRelease,TOUCHKEY_nPress,False},\
	{TOUCHKEY_nCCMode_Button_R_7, 25u,50u,16u,35u, TOUCHKEY_nRelease, TOUCHKEY_nRelease,TOUCHKEY_nPress,False},\
	{TOUCHKEY_nCCMode_Button_R_8, 0u,20u,10u,40u, TOUCHKEY_nRelease, TOUCHKEY_nRelease,TOUCHKEY_nPress,False},\
	{TOUCHKEY_nCCMode_Button_R_9, 35u,80u,0u,10u, TOUCHKEY_nRelease, TOUCHKEY_nRelease,TOUCHKEY_nPress,False},\
	{TOUCHKEY_nCCMode_Button_R_10, 0u,35u,0u,10u, TOUCHKEY_nRelease, TOUCHKEY_nRelease,TOUCHKEY_nPress,False},\
}

#endif              
/***************************************************************************************************
                                            END
***************************************************************************************************/
