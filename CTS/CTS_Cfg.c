/***************************************************************************************************
                            CLIMATE THERMODYNAMICS SYSTEM CONFIGURATION
                        
  .file Name    : CTS_Cfg.c
  
  .Description  : This file is used to provide the configuration data for climate thermodynamics
                  system.

  .Generate Time: 2018-7-9  18:12:29 
***************************************************************************************************/

#define CTS_Cfg


/***************************************************************************************************
                                            Header -Files
***************************************************************************************************/

/* System header files */
#include "CTS_StdDef.h"


/***************************************************************************************************
                                        Data CONFIGURATIONS

  Note(s): Configurate the data in this section.
***************************************************************************************************/

/* ICT mode: 0U-VICT, 1U-SensorIct */
#define CTS_u8IctMode                   0U

/* The number of zone */
#define CTS_u8ZoneNum                   2U

/* Maximal target blowout temperature limit */
#define CTS_u16MaxTgtBlowTempLimit      1600U

/* Zero point definitions */
#define CTS_u16ThermalAbsoluteZero      400U
#define CTS_u16ThermalRelativeZero      640U
#define CTS_u16BlowSpdRelativeZero      1000U

/* Active time after ignition off (1 minute per number) */
#define CTS_u16VictActiveTime           30U
#define CTS_u16SensorIctActiveTime      30U

/* The waiting time when the VICT output is invalid (1 second per number) */
#define CTS_u16IctInvalidWaitTime       60U

/* Time to wait sensor to become stable (1 second per number) */
#define CTS_u16SensorIctStableWaitTime  1U
#define CTS_u16PcbTempStableWaitTime    1U

/* The number of air distribution mode */
#define CTS_u8AirdModeNum               7U

/* The air distribution flap position of each AIRD mode */
static const cuint16 CTS_au16AirdModePos[CTS_u8AirdModeNum] = {830U,740U,675U,595U,512U,352U,210U};

/* Double zone heat effect factor, value = Factor / Base. */
#define CTS_u8ZoneEffectBase            100U
static const cuint8 CTS_au8DblZoneEffectFactor[CTS_u8AirdModeNum] = {0U,0U,0U,0U,45U,0U,0U};
static const cuint8 CTS_au8FrontToRearEffectFactor[CTS_u8AirdModeNum] = {0U,0U,0U,0U,0U,0U,0U};
static const cuint8 CTS_au8RearToFrontEffectFactor[CTS_u8AirdModeNum] = {0U,0U,0U,0U,0U,0U,0U};

/* The default position of R/F air flap for calculation when R/F air flap position is not valid. */
#define CTS_u16DefRfaPos                0U

/* R/F flap ratio */ 
#define CTS_u16RfaFreshRtoBase          100U
#define CTS_u8RfaFreshRto_Len           5U
static cuint16 CTS_au16RfaFreshRtoPos_X[CTS_u8RfaFreshRto_Len] = {0U,50U,100U,150U,200U};
static cuint16 CTS_au16RfaFreshRto_Y[CTS_u8RfaFreshRto_Len] = {0U,25U,50U,75U,100U};

/* EVAP offset when AC on */
#define CTS_u8EvapOfs_X_Len             5U
#define CTS_u8EvapOfs_Y_Len             3U
static cuint16 CTS_au16FreshOfsOat_X[CTS_u8EvapOfs_X_Len] = {400U,500U,600U,700U,800U};
static cuint16 CTS_au16RecircOfsCabinTemp_X[CTS_u8EvapOfs_X_Len] = {400U,480U,560U,640U,720U};
static cuint16 CTS_au16EvapOfsBlwrVlot_Y[CTS_u8EvapOfs_Y_Len] = {375U,611U,872U};
static cuint16 CTS_au16EvapFreshOfs_Z[CTS_u8EvapOfs_Y_Len][CTS_u8EvapOfs_X_Len] = 
{
    {640U,655U,690U,700U,720U},
    {640U,655U,690U,700U,720U},
    {640U,655U,690U,700U,720U}
};
static cuint16 CTS_au16EvapRecircOfs_Z[CTS_u8EvapOfs_Y_Len][CTS_u8EvapOfs_X_Len] = 
{
    {640U,655U,700U,720U,740U},
    {640U,655U,700U,720U,740U},
    {640U,655U,700U,720U,740U}
};

/* EVAP temperature changing rate, value = Chg / (2^ChgBase). */
#define CTS_u8EvapTempChgBase           11U
#define CTS_u16EvapTempChg              102U

/* Heater core temperature changing rate base */
#define CTS_u8HctChgBase                11U

/* HCT changing rate when heater pump on, value = Chg / (2^ChgBase). */
#define CTS_u8PumpOnChg_Len             5U
static const cuint16 CTS_au16PumpOnRawHct_X[CTS_u8PumpOnChg_Len] = {0U,300U,600U,900U,1200U};
static const cuint16 CTS_au16PumpOnHctChg_Y[CTS_u8PumpOnChg_Len] = {31U,51U,72U,92U,113U};

/* HCT changing rate when heater pump off, value = Chg / (2^ChgBase). */
#define CTS_u8PumpOffChg_Len            5U
static const cuint16 CTS_au16PumpOffBlwrVlot_X[CTS_u8PumpOffChg_Len] = {403U,490U,576U,663U,747U};
static const cuint16 CTS_au16PumpOffHctChg_Y[CTS_u8PumpOffChg_Len] = {102U,102U,102U,102U,102U};

/* Blowout temperature changing rate, value = Chg / (2^ChgBase). */
#define CTS_u8BlowTempChgBase           11U
#define CTS_u16BlowTempChg              51U

/* The mixing air flap ratio of HI and LO position, value = MacRto / MacRtoBase. */
#define CTS_u16MacRtoBase               1000U
#define CTS_u8MacRtoBlwrVolt_Y_Len      3U
static const cuint16 CTS_au16MacRtoAirdMode_X[CTS_u8AirdModeNum] = {0U,1U,2U,3U,4U,5U,6U};
static const cuint16 CTS_au16MacRtoBlwrVolt_Y[CTS_u8MacRtoBlwrVolt_Y_Len] = {403U,576U,747U};
static const cuint16 CTS_au16HiMacRtoL_Z[CTS_u8MacRtoBlwrVolt_Y_Len][CTS_u8AirdModeNum] = 
{
    {861U,848U,848U,848U,788U,815U,864U},
    {855U,843U,843U,843U,811U,815U,864U},
    {864U,830U,830U,830U,813U,815U,864U}
};
static const cuint16 CTS_au16LoMacRtoL_Z[CTS_u8MacRtoBlwrVolt_Y_Len][CTS_u8AirdModeNum] = 
{
    {0U,0U,0U,0U,0U,0U,0U},
    {0U,0U,0U,0U,0U,0U,0U},
    {0U,0U,0U,0U,0U,0U,0U}
};
static const cuint16 CTS_au16HiMacRtoR_Z[CTS_u8MacRtoBlwrVolt_Y_Len][CTS_u8AirdModeNum] = 
{
    {861U,848U,848U,848U,788U,815U,864U},
    {855U,843U,843U,843U,811U,815U,864U},
    {864U,830U,830U,830U,813U,815U,864U}
};
static const cuint16 CTS_au16LoMacRtoR_Z[CTS_u8MacRtoBlwrVolt_Y_Len][CTS_u8AirdModeNum] = 
{
    {0U,0U,0U,0U,0U,0U,0U},
    {0U,0U,0U,0U,0U,0U,0U},
    {0U,0U,0U,0U,0U,0U,0U}
};
static const cuint16 CTS_au16HiMacRtoRe_Z[CTS_u8MacRtoBlwrVolt_Y_Len][CTS_u8AirdModeNum] = 
{
    {834U,819U,819U,819U,814U,840U,840U},
    {859U,826U,826U,826U,840U,840U,840U},
    {860U,830U,830U,830U,841U,840U,840U}
};
static const cuint16 CTS_au16LoMacRtoRe_Z[CTS_u8MacRtoBlwrVolt_Y_Len][CTS_u8AirdModeNum] = 
{
    {0U,0U,0U,0U,0U,0U,0U},
    {0U,0U,0U,0U,0U,0U,0U},
    {0U,0U,0U,0U,0U,0U,0U}
};

/* PCB temperature sensor look-up table */
#define CTS_u8PcbTemp_Len               10U
static const cuint16 CTS_au16PcbTempAdValue_X[CTS_u8PcbTemp_Len] = {31U,81U,165U,301U,420U,561U,705U,829U,918U,973U};
static const cuint16 CTS_au16PcbTemp_Y[CTS_u8PcbTemp_Len] = {1900U,1450U,1150U,900U,750U,600U,450U,300U,150U,0U};

/* The PCB in-car temperature will be limited within OAT~(OAT+InitIctLimit). */
#define CTS_u8PcbIctLimit_Len           7U
static const cuint16 CTS_au16PcbIctLimitOat_X[CTS_u8PcbIctLimit_Len] = {0U,200U,300U,400U,500U,650U,800U};
static const cuint16 CTS_au16PcbIctLimit_Y[CTS_u8PcbIctLimit_Len] = {840U,840U,840U,840U,840U,840U,840U};

/* Factors for initial PCB in car temperature calculation, value = InitIctFactor / InitIctBase. */
#define CTS_u16PcbIctBase               100U
#define CTS_u8PcbIctFactorOat_X_Len     7U
#define CTS_u8PcbIctFactorErr_Y_Len     7U
static const cuint16 CTS_au16PcbIctFactorOat_X[CTS_u8PcbIctFactorOat_X_Len] = {200U,300U,400U,500U,600U,700U,800U};
static const cuint16 CTS_au16PcbIctFactorErr_Y[CTS_u8PcbIctFactorErr_Y_Len] = {0U,5U,15U,25U,35U,45U,55U};
static const cuint16 CTS_au16PcbIctFactor_Z[CTS_u8PcbIctFactorErr_Y_Len][CTS_u8PcbIctFactorOat_X_Len] =  
{
    {75U,75U,75U,75U,75U,70U,75U},
    {75U,75U,75U,75U,75U,70U,75U},
    {75U,75U,50U,30U,30U,30U,50U},
    {75U,75U,50U,30U,30U,30U,50U},
    {75U,75U,60U,35U,35U,35U,65U},
    {75U,75U,75U,75U,75U,75U,75U},
    {75U,75U,75U,75U,75U,75U,75U}
};

/* In-car temperature sensor look-up table */
#define CTS_u8SensorIct_Len             10U
static const cuint16 CTS_au16SensorIctAdValue_X[CTS_u8SensorIct_Len] = {90U,135U,168U,209U,319U,391U,791U,909U,973U,973U};
static const cuint16 CTS_au16SensorIct_Y[CTS_u8SensorIct_Len] = {1400U,1230U,1140U,1050U,870U,780U,350U,170U,0U,0U};

/* ICT Tolerance (0.1 Deg per number) */
#define CTS_u16SensorIctTolerance       50U

/* ICT sensor temperature changing rate, value = Chg / ChgBase. */
#define CTS_u8SensorIctChgBase          14U
#define CTS_u16SensorIctChg             164U

/* Sun intensity changing rate, value = Chg / ChgBase. */
#define CTS_u8BodyShellHeatChgBase      11U
#define CTS_u16BodyShellHeatChg         7U

/* Blower voltage to blowout speed lookup table. */
#define CTS_u8BlowSpdBlwrVolt_X_Len     7U
#define CTS_u8BlowSpdRfaPos_Y_Len       5U
static const cuint16 CTS_au16BlowSpdBlwrVolt_X[CTS_u8BlowSpdBlwrVolt_X_Len] = {0U,500U,1000U,1500U,2000U,2500U,3000U};
static const cuint16 CTS_au16BlowSpdRfaPos_Y[CTS_u8BlowSpdRfaPos_Y_Len] = {0U,50U,100U,150U,200U};
static const cuint16 CTS_au16BlowSpd_Z[CTS_u8BlowSpdRfaPos_Y_Len][CTS_u8BlowSpdBlwrVolt_X_Len] = 
{
    {0U,500U,1000U,1500U,2000U,2500U,3000U},
    {0U,500U,1000U,1500U,2000U,2500U,3000U},
    {0U,500U,1000U,1500U,2000U,2500U,3000U},
    {0U,500U,1000U,1500U,2000U,2500U,3000U},
    {0U,500U,1000U,1500U,2000U,2500U,3000U}
}; 

/* Velocity to blowout speed offset */
#define CTS_u8VelBlowSpdOfsVel_X_Len    7U
#define CTS_u8VelBlowSpdRfaPos_Y_Len    5U
static const cuint16 CTS_au16VelBlowSpdOfsVel_X[CTS_u8VelBlowSpdOfsVel_X_Len] = {0U,20U,40U,60U,80U,100U,120U};
static const cuint16 CTS_au16VelBlowSpdRfaPos_Y[CTS_u8VelBlowSpdRfaPos_Y_Len] = {0U, 60U, 120U, 180U, 240U};
static const cuint16 CTS_au16VelBlowSpdOfs_Z[CTS_u8VelBlowSpdRfaPos_Y_Len][CTS_u8VelBlowSpdOfsVel_X_Len] = 
{
    {1000U,1000U,1000U,1000U,1000U,1000U,1000U},
    {1000U,1000U,1000U,1000U,1000U,1000U,1000U},
    {1000U,1000U,1000U,1000U,1000U,1000U,1000U},
    {1000U,1000U,1000U,1000U,1000U,1000U,1000U},
    {1000U,1000U,1000U,1000U,1000U,1000U,1000U}
};

/* Balance head zone temperature in different OAT, blowout temperature and blowout speed */
#define CTS_u8BalanceBlowTemp_X_Len     14U
#define CTS_u8BalanceOat_Y_Len          11U
#define CTS_u8BalanceBlowSpd_Z_Len      5U
static const cuint16 CTS_au16BalanceBlowTemp_X[CTS_u8BalanceBlowTemp_X_Len] = {450U,500U,550U,600U,650U,700U,750U,800U,850U,900U,950U,1000U,1050U,1150U};
static const cuint16 CTS_au16BalanceOat_Y[CTS_u8BalanceOat_Y_Len] = {100U,200U,250U,300U,400U,450U,500U,550U,600U,700U,800U};
static const cuint16 CTS_au16BalanceBlowSpd_Z[CTS_u8BalanceBlowSpd_Z_Len] = {0U,350U,480U,660U,1200U};
static const cuint16 CTS_au16BalanceHeadZoneTemp_U[CTS_u8BalanceBlowSpd_Z_Len][CTS_u8BalanceOat_Y_Len][CTS_u8BalanceBlowTemp_X_Len] =
{
    /* Blower Off */
    {
        {180U,180U,180U,180U,180U,180U,180U,180U,180U,180U,180U,180U,180U,180U},
        {280U,280U,280U,280U,280U,280U,280U,280U,280U,280U,280U,280U,280U,280U},
        {330U,330U,330U,330U,330U,330U,330U,330U,330U,330U,330U,330U,330U,330U},
        {380U,380U,380U,380U,380U,380U,380U,380U,380U,380U,380U,380U,380U,380U},
        {480U,480U,480U,480U,480U,480U,480U,480U,480U,480U,480U,480U,480U,480U},
        {530U,530U,530U,530U,530U,530U,530U,530U,530U,530U,530U,530U,530U,530U},
        {580U,580U,580U,580U,580U,580U,580U,580U,580U,580U,580U,580U,580U,580U},
        {630U,630U,630U,630U,630U,630U,630U,630U,630U,630U,630U,630U,630U,630U},
        {680U,680U,680U,680U,680U,680U,680U,680U,680U,680U,680U,680U,680U,680U},
        {780U,780U,780U,780U,780U,780U,780U,780U,780U,780U,780U,780U,780U,780U},
        {880U,880U,880U,880U,880U,880U,880U,880U,880U,880U,880U,880U,880U,880U}
    },
    /* Low Blowout Speed */
    {
        {381U,407U,433U,459U,485U,502U,509U,517U,524U,532U,564U,572U,580U,588U},
        {422U,444U,465U,486U,508U,522U,531U,539U,548U,557U,584U,589U,594U,599U},
        {443U,462U,481U,500U,519U,533U,542U,551U,560U,569U,593U,597U,601U,605U},
        {463U,480U,497U,514U,531U,543U,553U,562U,572U,581U,603U,605U,608U,610U},
        {497U,516U,535U,554U,573U,586U,601U,617U,632U,648U,673U,677U,681U,685U},
        {514U,533U,553U,572U,591U,605U,621U,637U,654U,670U,697U,701U,705U,710U},
        {531U,551U,570U,590U,609U,624U,641U,658U,675U,692U,720U,725U,730U,734U},
        {548U,568U,588U,607U,627U,643U,661U,678U,696U,714U,744U,749U,754U,759U},
        {555U,576U,596U,617U,638U,648U,670U,693U,716U,738U,772U,776U,780U,784U},
        {592U,612U,633U,653U,673U,684U,709U,734U,760U,785U,812U,818U,824U,830U},
        {628U,649U,669U,689U,709U,721U,748U,776U,803U,831U,851U,860U,868U,877U}
    },
    /* Middle Blowout Speed 1 */
    {
        {395U,423U,450U,478U,505U,535U,551U,566U,582U,597U,641U,650U,658U,667U},
        {441U,464U,487U,511U,534U,559U,572U,585U,599U,612U,652U,661U,671U,681U},
        {463U,485U,506U,527U,549U,570U,583U,595U,607U,620U,657U,667U,678U,688U},
        {486U,505U,525U,544U,563U,582U,593U,605U,616U,627U,662U,673U,684U,695U},
        {505U,526U,546U,567U,588U,591U,608U,625U,643U,660U,715U,724U,733U,742U},
        {522U,542U,562U,582U,602U,613U,631U,648U,666U,684U,741U,748U,755U,762U},
        {538U,557U,577U,596U,616U,635U,653U,671U,690U,708U,766U,771U,777U,782U},
        {555U,573U,592U,611U,630U,656U,675U,694U,713U,732U,792U,795U,799U,802U},
        {564U,586U,608U,629U,651U,667U,693U,718U,744U,769U,801U,809U,816U,824U},
        {594U,613U,633U,652U,672U,702U,727U,751U,776U,801U,831U,839U,848U,856U},
        {624U,641U,658U,675U,693U,737U,761U,784U,808U,832U,861U,870U,879U,889U}
    },
    /* Middle Blowout Speed 2 */
    {
        {413U,439U,466U,493U,520U,585U,597U,609U,620U,632U,654U,678U,701U,725U},
        {462U,484U,505U,527U,548U,598U,610U,623U,636U,649U,690U,708U,726U,744U},
        {487U,506U,525U,543U,562U,604U,617U,630U,644U,657U,707U,722U,738U,753U},
        {512U,528U,544U,560U,576U,610U,624U,638U,651U,665U,725U,737U,750U,762U},
        {550U,563U,576U,589U,603U,627U,647U,668U,688U,709U,784U,799U,814U,829U},
        {551U,567U,583U,599U,615U,639U,662U,685U,709U,732U,802U,815U,827U,840U},
        {552U,571U,590U,609U,627U,651U,677U,703U,729U,755U,820U,830U,841U,851U},
        {554U,575U,597U,618U,640U,663U,692U,721U,750U,779U,838U,846U,854U,862U},
        {563U,588U,613U,639U,664U,692U,722U,753U,784U,815U,849U,859U,870U,881U},
        {586U,608U,629U,651U,673U,721U,751U,780U,810U,839U,872U,884U,896U,907U},
        {609U,627U,645U,664U,682U,751U,779U,807U,835U,864U,896U,909U,922U,934U}
    },
    /* High Blowout Speed */
    {
        {465U,490U,515U,540U,565U,735U,736U,736U,737U,737U,693U,762U,830U,899U},
        {528U,543U,559U,574U,590U,715U,725U,736U,747U,758U,804U,846U,889U,931U},
        {559U,570U,581U,592U,603U,704U,720U,736U,752U,769U,859U,888U,918U,947U},
        {590U,596U,603U,609U,615U,694U,715U,737U,758U,779U,914U,930U,947U,963U},
        {685U,675U,666U,656U,646U,735U,765U,795U,825U,855U,991U,1024U,1056U,1089U},
        {640U,644U,647U,651U,654U,718U,757U,797U,837U,876U,987U,1015U,1044U,1072U},
        {595U,612U,629U,645U,662U,700U,750U,799U,848U,897U,983U,1007U,1032U,1056U},
        {551U,580U,610U,640U,670U,683U,742U,801U,860U,919U,979U,999U,1019U,1039U},
        {560U,596U,631U,667U,702U,765U,812U,859U,906U,953U,992U,1011U,1030U,1049U},
        {562U,591U,619U,648U,676U,778U,823U,867U,912U,956U,997U,1018U,1039U,1060U},
        {564U,585U,607U,628U,650U,792U,834U,875U,917U,959U,1002U,1025U,1048U,1071U}
    }
};      

/* Cabin temperature static offset in different OAT, blowout temperature and AIRD mode */
#define CTS_u8CabinOfsSun_X_Len         11U
#define CTS_u8CabinOfsOat_Y_Len         11U
#define CTS_u8CabinOfsAirdPos_Z_Len     4U
static const cuint16 CTS_au16CabinOfsSun_X[CTS_u8CabinOfsSun_X_Len] = {0U,100U,200U,300U,400U,500U,600U,700U,800U,900U,1000U};
static const cuint16 CTS_au16CabinOfsOat_Y[CTS_u8CabinOfsOat_Y_Len] = {0U,200U,250U,300U,350U,400U,450U,500U,550U,600U,700U};
static const cuint16 CTS_au16CabinOfsAirdPos_Z[CTS_u8CabinOfsAirdPos_Z_Len] = {210U,512U,675U,830U};
static const cuint16 CTS_au16CabinTempStcOfs_U[CTS_u8CabinOfsAirdPos_Z_Len][CTS_u8CabinOfsOat_Y_Len][CTS_u8CabinOfsSun_X_Len] =
{
    {
        {620U,620U,620U,620U,620U,620U,620U,620U,620U,620U,620U},
        {620U,620U,620U,620U,620U,620U,620U,620U,620U,620U,620U},
        {620U,620U,620U,620U,620U,620U,620U,620U,620U,620U,620U},
        {620U,620U,620U,620U,620U,620U,620U,620U,620U,620U,620U},
        {620U,620U,620U,620U,620U,620U,620U,620U,620U,620U,620U},
        {580U,592U,605U,615U,625U,625U,625U,625U,625U,625U,625U},
        {620U,625U,630U,635U,635U,635U,635U,635U,635U,635U,635U},
        {610U,615U,620U,625U,635U,635U,635U,635U,635U,635U,635U},
        {610U,615U,620U,625U,635U,635U,635U,635U,620U,610U,610U},
        {610U,615U,620U,625U,635U,635U,635U,635U,620U,620U,610U},
        {610U,615U,620U,625U,635U,635U,635U,635U,620U,620U,620U}
    },
    {
        {620U,620U,620U,620U,620U,620U,620U,620U,620U,620U,620U},
        {620U,620U,620U,620U,620U,620U,620U,620U,620U,620U,620U},
        {620U,620U,620U,620U,620U,620U,620U,620U,620U,620U,620U},
        {620U,620U,620U,620U,620U,620U,620U,620U,620U,620U,620U},
        {620U,620U,620U,620U,620U,620U,620U,620U,620U,620U,620U},
        {620U,620U,620U,625U,625U,625U,625U,625U,625U,625U,625U},
        {620U,620U,620U,625U,635U,635U,635U,635U,635U,635U,635U},
        {620U,620U,620U,625U,635U,635U,635U,635U,635U,635U,635U},
        {615U,615U,615U,625U,635U,635U,635U,635U,635U,635U,635U},
        {620U,620U,620U,625U,635U,635U,635U,635U,635U,635U,635U},
        {620U,620U,620U,625U,635U,635U,635U,635U,635U,635U,635U}
    },
    {
        {545U,555U,577U,595U,600U,600U,600U,600U,600U,600U,600U},
        {555U,570U,587U,595U,600U,600U,600U,600U,600U,600U,600U},
        {560U,565U,582U,602U,605U,605U,605U,605U,605U,605U,605U},
        {572U,585U,595U,604U,610U,610U,610U,610U,610U,610U,610U},
        {572U,588U,598U,605U,612U,612U,612U,612U,612U,612U,612U},
        {590U,592U,605U,615U,625U,625U,625U,625U,625U,625U,625U},
        {592U,595U,610U,625U,635U,635U,635U,635U,635U,635U,635U},
        {605U,615U,620U,625U,635U,635U,635U,635U,635U,635U,635U},
        {610U,615U,620U,625U,635U,635U,635U,635U,635U,635U,635U},
        {600U,600U,600U,600U,600U,605U,605U,605U,605U,605U,605U},
        {595U,595U,595U,595U,590U,590U,590U,590U,590U,590U,590U}
    },
    {
        {565U,575U,587U,595U,600U,600U,600U,600U,600U,600U,600U},
        {565U,578U,590U,595U,600U,600U,600U,600U,600U,600U,600U},
        {570U,580U,592U,602U,605U,605U,605U,605U,605U,605U,605U},
        {572U,585U,595U,604U,610U,610U,610U,610U,610U,610U,610U},
        {572U,588U,598U,605U,612U,612U,612U,612U,612U,612U,612U},
        {580U,592U,605U,615U,625U,625U,625U,625U,625U,625U,625U},
        {585U,595U,610U,625U,635U,635U,635U,635U,635U,635U,635U},
        {585U,595U,610U,625U,635U,635U,635U,635U,635U,635U,635U},
        {620U,625U,630U,635U,635U,635U,635U,635U,635U,635U,635U},
        {620U,625U,630U,635U,635U,635U,635U,635U,635U,635U,635U},
        {600U,625U,630U,635U,635U,635U,635U,635U,635U,635U,635U}
    }
};

/* Heat caused by sun load */ 
#define CTS_u8SunLoadHeatSun_X_Len      6U
#define CTS_u8SunLoadHeatOat_Y_Len      7U
static const cuint16 CTS_au16SunLoadHeatSun_X[CTS_u8SunLoadHeatSun_X_Len] = {0U,150U,300U,500U,800U,1200U};
static const cuint16 CTS_au16SunLoadHeatOat_Y[CTS_u8SunLoadHeatOat_Y_Len] = {250U,350U,400U,450U,500U,600U,700U};
static const cuint16 CTS_au16SunLoadHeat_Z[CTS_u8SunLoadHeatOat_Y_Len][CTS_u8SunLoadHeatSun_X_Len] = 
{
    {640U,660U,710U,740U,800U,840U},
    {640U,655U,700U,740U,790U,830U},
    {640U,650U,690U,740U,790U,810U},
    {640U,650U,690U,740U,770U,790U},
    {640U,650U,690U,750U,770U,770U},
    {640U,655U,730U,750U,760U,790U},
    {640U,665U,740U,750U,760U,830U}
};

/* Engine heat in different and air leaking heat caused by velocity */ 
#define CTS_u8VelEngineHeatVel_X_Len    6U
#define CTS_u8VelEngineHeatOat_Y_Len    7U
static const cuint16 CTS_au16VelEngineHeatVel_X[CTS_u8VelEngineHeatVel_X_Len] = {0U,40U,60U,75U,100U,130U};
static const cuint16 CTS_au16VelEngineHeatOat_Y[CTS_u8VelEngineHeatOat_Y_Len] = {250U,350U,400U,450U,500U,600U,700U};
static const cuint16 CTS_au16VelEngineHeat_Z[CTS_u8VelEngineHeatOat_Y_Len][CTS_u8VelEngineHeatVel_X_Len] = 
{
    {710U,680U,650U,625U,620U,620U},
    {700U,670U,650U,625U,620U,620U},
    {700U,670U,650U,630U,625U,625U},
    {670U,640U,640U,640U,640U,640U},
    {660U,640U,640U,640U,640U,640U},
    {660U,640U,640U,640U,640U,640U},
    {640U,640U,640U,640U,640U,640U}
};

/* The base heat caused by the running of engine (In fuel mode or in electric mode) */
#define CTS_u16FuelModeBaseHeat         720U
#define CTS_u16ElecModeBaseHeat         660U

/* The base heat during calibration */ 
#define CTS_u16CalibrateBaseHeat        720U

/* Effect item changing rate, value = Chg / (2^ChgBase). */
#define CTS_u8HeatItemChgBase           14U
static const cuint16 CTS_au16HeadZoneFlowItemChg[CTS_u8AirdModeNum] = {328U,147U,131U,102U,102U,106U,70U};
static const cuint16 CTS_au16CabinFlowItemChg[CTS_u8AirdModeNum] = {106U,25U,25U,29U,102U,56U,39U};
#define CTS_u16ShellItemChg             8U

/* blowout temperature affecting item changing ratio , value = FlowItemRto / FlowItemRtoBase. */
#define CTS_u8FlowItemRtoBase           100U
static const cuint8 CTS_au8HeadZoneFlowItemRto[CTS_u8AirdModeNum] = {78U,65U,75U,65U,68U,60U,60U};
static const cuint8 CTS_au8CabinFlowItemRto[CTS_u8AirdModeNum] = {65U,45U,45U,45U,35U,30U,25U};

/* Flow item ratio changing rate, value = Chg / (2^ChgBase). */
#define CTS_u8FlowItemRtoChgBase        10U
#define CTS_u16FlowItemRtoChg           51U

/* Engine off read back ratio */
#define CTS_u16ReadBackBase             100U
#define CTS_u8IgnOffTime_X_Len          7U
#define CTS_u8IgnOffOat_Y_Len           5U
static const cuint16 CTS_au16IgnOffTime_X[CTS_u8IgnOffTime_X_Len] = {3U,10U,20U,30U,60U,90U,120U};
static const cuint16 CTS_au16IgnOffOat_Y[CTS_u8IgnOffOat_Y_Len] = {50U,200U,400U,600U,800U};
static const cuint16 CTS_au16IgnOffReadBack_Z[CTS_u8IgnOffOat_Y_Len][CTS_u8IgnOffTime_X_Len] =
{
    {100U,40U,20U,0U,0U,0U,0U},
    {100U,40U,20U,0U,0U,0U,0U},
    {100U,40U,20U,0U,0U,0U,0U},
    {100U,70U,40U,0U,0U,0U,0U},
    {100U,70U,40U,0U,0U,0U,0U}
};

/* Pre-control blowout temperature in different set temperature, OAT and blowout speed */
#define CTS_u8PreCtlSetTemp_X_Len       11U
#define CTS_u8PreCtlOat_Y_Len           11U
#define CTS_u8PreCtlBlowSpd_Z_Len       4U
static const cuint16 CTS_au16PreCtlSetTemp_X[CTS_u8PreCtlSetTemp_X_Len] = {400U,580U,600U,620U,640U,660U,680U,700U,730U,780U,1275U};
static const cuint16 CTS_au16PreCtlOat_Y[CTS_u8PreCtlOat_Y_Len] = {100U,200U,250U,300U,400U,450U,500U,550U,600U,700U,800U};
static const cuint16 CTS_au16PreCtlBlowSpd_Z[CTS_u8PreCtlBlowSpd_Z_Len] = {350U,480U,660U,1200U};
static const cuint16 CTS_au16PreCtlBlowTemp_U[CTS_u8PreCtlBlowSpd_Z_Len][CTS_u8PreCtlOat_Y_Len][CTS_u8PreCtlSetTemp_X_Len] =
{
    /* Low Blowout Speed */
    {
        {0U,1050U,1300U,1550U,1800U,2050U,2300U,2550U,2925U,3550U,1600U},
        {0U,944U,1169U,1556U,1944U,2331U,2718U,3105U,3685U,4653U,1600U},
        {0U,923U,1040U,1563U,2097U,2630U,3163U,3697U,4497U,5830U,1600U},
        {0U,895U,943U,1579U,2436U,3293U,4150U,5007U,6293U,8436U,1600U},
        {0U,678U,746U,811U,875U,924U,1036U,1531U,2294U,3565U,1600U},
        {0U,622U,683U,747U,808U,870U,919U,989U,1618U,2769U,1600U},
        {0U,575U,627U,687U,748U,806U,865U,914U,1059U,2110U,1600U},
        {0U,531U,581U,632U,691U,749U,805U,861U,927U,1556U,1600U},
        {0U,511U,559U,607U,662U,727U,771U,816U,882U,1051U,1600U},
        {0U,422U,471U,519U,568U,617U,680U,731U,791U,891U,1600U},
        {0U,331U,380U,429U,479U,528U,578U,627U,717U,807U,1600U}
    },
    /* Middle Blowout Speed 1 */
    {
        {0U,845U,903U,926U,949U,1069U,1300U,1531U,1877U,2454U,1600U},
        {0U,780U,855U,910U,935U,993U,1140U,1343U,1648U,2157U,1600U},
        {0U,740U,821U,901U,928U,966U,1073U,1265U,1553U,2033U,1600U},
        {0U,695U,780U,869U,919U,947U,1032U,1195U,1468U,1923U,1600U},
        {0U,631U,726U,784U,843U,900U,918U,936U,1033U,1567U,1600U},
        {0U,596U,645U,720U,777U,833U,889U,914U,941U,1395U,1600U},
        {0U,558U,609U,661U,715U,769U,824U,878U,919U,1108U,1600U},
        {0U,518U,571U,624U,669U,709U,762U,815U,894U,940U,1600U},
        {0U,487U,533U,579U,625U,678U,725U,764U,823U,917U,1600U},
        {0U,414U,465U,517U,568U,620U,664U,697U,757U,858U,1600U},
        {0U,322U,380U,438U,497U,555U,613U,658U,692U,791U,1600U}
    },
    /* Middle Blowout Speed 2 */
    {
        {0U,696U,764U,849U,918U,963U,1005U,1047U,1171U,1382U,1600U},
        {0U,682U,710U,788U,867U,914U,938U,979U,1075U,1353U,1600U},
        {0U,672U,696U,761U,837U,903U,923U,943U,1025U,1330U,1600U},
        {0U,656U,685U,736U,809U,882U,913U,929U,970U,1296U,1600U},
        {0U,564U,640U,686U,732U,781U,830U,879U,914U,947U,1600U},
        {0U,540U,603U,660U,702U,745U,788U,831U,896U,934U,1600U},
        {0U,524U,577U,630U,677U,717U,756U,794U,851U,919U,1600U},
        {0U,511U,558U,604U,650U,694U,729U,764U,816U,901U,1600U},
        {0U,484U,523U,563U,603U,642U,679U,714U,762U,843U,1600U},
        {0U,436U,482U,528U,574U,620U,657U,678U,715U,800U,1600U},
        {0U,370U,425U,480U,535U,590U,645U,663U,685U,752U,1600U}
    },
    /* High Blowout Speed */
    {
        {0U,654U,660U,666U,672U,678U,684U,690U,699U,1013U,1600U},
        {0U,618U,654U,662U,670U,678U,686U,694U,771U,924U,1600U},
        {0U,547U,639U,659U,668U,678U,688U,698U,780U,906U,1600U},
        {0U,370U,530U,653U,666U,678U,691U,714U,785U,900U,1600U},
        {0U,993U,889U,786U,683U,579U,476U,680U,697U,775U,1600U},
        {0U,-410U,-124U,162U,448U,655U,670U,686U,716U,779U,1600U},
        {0U,404U,464U,524U,584U,644U,674U,700U,730U,781U,1600U},
        {0U,499U,533U,566U,600U,633U,689U,715U,740U,782U,1600U},
        {0U,478U,506U,534U,563U,591U,619U,647U,672U,716U,1600U},
        {0U,482U,517U,552U,587U,622U,652U,662U,676U,702U,1600U},
        {0U,487U,534U,581U,627U,654U,661U,668U,678U,696U,1600U}
    }
};

/* Feed-back control proportional component in different error, value = Factor / FactorBase. */
#define CTS_u16FbCtlPFactorBase         10U
#define CTS_u8FbCtl_Len                 11U       
static cuint16 CTS_au16FbCtlErr_X[CTS_u8FbCtl_Len] = {580U,600U,610U,620U,630U,640U,650U,660U,670U,680U,700U};
static cuint16 CTS_au16FbCtlPFactor_Y[CTS_u8FbCtl_Len] = {42U,38U,33U,30U,20U,12U,21U,30U,33U,38U,42U};

/* The factor used for double zone offset calculation, value = OfsFactor / OfsBase. */
#define CTS_u8ZoneOfsFactorBase         10U
static cuint8 CTS_au8DblZoneOfsFactor[CTS_u8AirdModeNum] = {0U,0U,0U,0U,0U,0U,0U};
static cuint8 CTS_au8FrontRearOfsFactor[CTS_u8AirdModeNum] = {0U,0U,0U,0U,0U,0U,0U};

const CTS_tstU16ConstType CTS_stThermalAbsoluteZero =
{
    (cuint16)CTS_u16ThermalAbsoluteZero
};

const CTS_tstU16ConstType CTS_stThermalRelativeZero =
{
    (cuint16)CTS_u16ThermalRelativeZero
};

const CTS_tstU16ConstType CTS_stBlowSpdRelativeZero =
{
    (cuint16)CTS_u16BlowSpdRelativeZero
};

const CTS_tstU8ConstType CTS_stZoneNum =
{
    (cuint8)CTS_u8ZoneNum
};

const CTS_tstU8ConstType CTS_stIctMode =
{
    (cuint8)CTS_u8IctMode
};

const CTS_tstU16ConstType CTS_stVictActiveTime =
{
    (cuint16)CTS_u16VictActiveTime
};

const CTS_tstU16ConstType CTS_stSensorIctActiveTime =
{
    (cuint16)CTS_u16SensorIctActiveTime
};

const CTS_tstU16ConstType CTS_stIctInvalidWaitTime =
{
    (cuint16)CTS_u16IctInvalidWaitTime
};

const CTS_tstU16ConstType CTS_stMaxTgtBlowTempLimit =
{
    (cuint16)CTS_u16MaxTgtBlowTempLimit
};

const CTS_tstU16ConstArrayType CTS_stAirdModePos =
{
    CTS_au16AirdModePos,
    (cuint8)CTS_u8AirdModeNum
};

const CTS_tstU16ConstType CTS_stDefRfaPos =
{
    (cuint16)CTS_u16DefRfaPos
};

const CTS_tstU16ConstType CTS_stRfaFreshRtoBase =
{
    (cuint16)CTS_u16RfaFreshRtoBase
};

const CTS_tstU16Table1DType CTS_stRfaFreshRto =
{
    CTS_au16RfaFreshRtoPos_X,
    (cuint8)CTS_u8RfaFreshRto_Len,
    CTS_au16RfaFreshRto_Y,
};

const CTS_tstU16Table2DType CTS_stEvapFreshOfs =
{
    CTS_au16FreshOfsOat_X,
    (cuint8)CTS_u8EvapOfs_X_Len,
    CTS_au16EvapOfsBlwrVlot_Y,
    (cuint8)CTS_u8EvapOfs_Y_Len,
    &CTS_au16EvapFreshOfs_Z[0][0]
};

const CTS_tstU16Table2DType CTS_stEvapRecircOfs =
{
    CTS_au16RecircOfsCabinTemp_X,
    (cuint8)CTS_u8EvapOfs_X_Len,
    CTS_au16EvapOfsBlwrVlot_Y,
    (cuint8)CTS_u8EvapOfs_Y_Len,
    &CTS_au16EvapRecircOfs_Z[0][0]
};

const CTS_tstU8ConstType CTS_stEvapTempChgBase =
{
    (cuint8)CTS_u8EvapTempChgBase
};

const CTS_tstU16ConstType CTS_stEvapTempChg =
{
    (cuint16)CTS_u16EvapTempChg
};

const CTS_tstU8ConstType CTS_stHctChgBase =
{
    (cuint8)CTS_u8HctChgBase
};

const CTS_tstU16Table1DType CTS_stPumpOnHctChg =
{
    CTS_au16PumpOnRawHct_X,
    (cuint8)CTS_u8PumpOnChg_Len,
    CTS_au16PumpOnHctChg_Y
};

const CTS_tstU16Table1DType CTS_stPumpOffHctChg =
{
    CTS_au16PumpOffBlwrVlot_X,
    (cuint8)CTS_u8PumpOffChg_Len,
    CTS_au16PumpOffHctChg_Y
};

const CTS_tstU16ConstType CTS_stMacRtoBase =
{
    (cuint16)CTS_u16MacRtoBase
};

const CTS_tstU16Table2DType CTS_stHiMacRtoL =
{
    CTS_au16MacRtoAirdMode_X,
    (cuint8)CTS_u8AirdModeNum,
    CTS_au16MacRtoBlwrVolt_Y,
    (cuint8)CTS_u8MacRtoBlwrVolt_Y_Len,
    &CTS_au16HiMacRtoL_Z[0][0]
};

const CTS_tstU16Table2DType CTS_stLoMacRtoL =
{
    CTS_au16MacRtoAirdMode_X,
    (cuint8)CTS_u8AirdModeNum,
    CTS_au16MacRtoBlwrVolt_Y,
    (cuint8)CTS_u8MacRtoBlwrVolt_Y_Len,
    &CTS_au16LoMacRtoL_Z[0][0]
};

const CTS_tstU16Table2DType CTS_stHiMacRtoR =
{
    CTS_au16MacRtoAirdMode_X,
    (cuint8)CTS_u8AirdModeNum,
    CTS_au16MacRtoBlwrVolt_Y,
    (cuint8)CTS_u8MacRtoBlwrVolt_Y_Len,
    &CTS_au16HiMacRtoR_Z[0][0]
};

const CTS_tstU16Table2DType CTS_stLoMacRtoR =
{
    CTS_au16MacRtoAirdMode_X,
    (cuint8)CTS_u8AirdModeNum,
    CTS_au16MacRtoBlwrVolt_Y,
    (cuint8)CTS_u8MacRtoBlwrVolt_Y_Len,
    &CTS_au16LoMacRtoR_Z[0][0]
};

const CTS_tstU16Table2DType CTS_stHiMacRtoRe =
{
    CTS_au16MacRtoAirdMode_X,
    (cuint8)CTS_u8AirdModeNum,
    CTS_au16MacRtoBlwrVolt_Y,
    (cuint8)CTS_u8MacRtoBlwrVolt_Y_Len,
    &CTS_au16HiMacRtoRe_Z[0][0]
};

const CTS_tstU16Table2DType CTS_stLoMacRtoRe =
{
    CTS_au16MacRtoAirdMode_X,
    (cuint8)CTS_u8AirdModeNum,
    CTS_au16MacRtoBlwrVolt_Y,
    (cuint8)CTS_u8MacRtoBlwrVolt_Y_Len,
    &CTS_au16LoMacRtoRe_Z[0][0]
};

const CTS_tstU8ConstType CTS_stBlowTempChgBase =
{
    (cuint8)CTS_u8BlowTempChgBase
};

const CTS_tstU16ConstType CTS_stBlowTempChg =
{
    (cuint16)CTS_u16BlowTempChg
};

const CTS_tstU16Table2DType CTS_stBlowSpd =
{
    CTS_au16BlowSpdBlwrVolt_X,
    (cuint8)CTS_u8BlowSpdBlwrVolt_X_Len,
    CTS_au16BlowSpdRfaPos_Y,
    (cuint8)CTS_u8BlowSpdRfaPos_Y_Len,
    &CTS_au16BlowSpd_Z[0][0]
};

const CTS_tstU16Table2DType CTS_stVelBlowSpdOfs =
{
    CTS_au16VelBlowSpdOfsVel_X,
    (cuint8)CTS_u8VelBlowSpdOfsVel_X_Len,
    CTS_au16VelBlowSpdRfaPos_Y,
    (cuint8)CTS_u8VelBlowSpdRfaPos_Y_Len,
    &CTS_au16VelBlowSpdOfs_Z[0][0]
};

const CTS_tstU16ConstType CTS_stSensorIctStableWaitTime =
{
    (cuint16)CTS_u16SensorIctStableWaitTime
};

const CTS_tstU16Table1DType CTS_stSensorIct =
{
    CTS_au16SensorIctAdValue_X,
    (cuint8)CTS_u8SensorIct_Len,
    CTS_au16SensorIct_Y
};

const CTS_tstU16ConstType CTS_stSensorIctTolerance =
{
    (cuint16)CTS_u16SensorIctTolerance
};

const CTS_tstU8ConstType CTS_stSensorIctChgBase =
{
    (cuint8)CTS_u8SensorIctChgBase
};

const CTS_tstU16ConstType CTS_stSensorIctChg =
{
    (cuint16)CTS_u16SensorIctChg
};

const CTS_tstU16ConstType CTS_stPcbTempStableWaitTime =
{
    (cuint16)CTS_u16PcbTempStableWaitTime
};

const CTS_tstU16Table1DType CTS_stPcbTemp =
{
    CTS_au16PcbTempAdValue_X,
    (cuint8)CTS_u8PcbTemp_Len,
    CTS_au16PcbTemp_Y
};

const CTS_tstU16Table1DType CTS_stPcbIctLimit =
{
    CTS_au16PcbIctLimitOat_X,
    (cuint8)CTS_u8PcbIctLimit_Len,
    CTS_au16PcbIctLimit_Y
};

const CTS_tstU16ConstType CTS_stPcbIctBase =
{
    (cuint16)CTS_u16PcbIctBase
};

const CTS_tstU16Table2DType CTS_stPcbIctFactor =
{
    CTS_au16PcbIctFactorOat_X,
    (cuint8)CTS_u8PcbIctFactorOat_X_Len,
    CTS_au16PcbIctFactorErr_Y,
    (cuint8)CTS_u8PcbIctFactorErr_Y_Len,
    &CTS_au16PcbIctFactor_Z[0][0]
};

const CTS_tstU16ConstType CTS_stReadBackBase =
{
    (cuint16)CTS_u16ReadBackBase
};

const CTS_tstU16Table2DType CTS_stIgnOffReadBack =
{
    CTS_au16IgnOffTime_X,
    (cuint8)CTS_u8IgnOffTime_X_Len,
    CTS_au16IgnOffOat_Y,
    (cuint8)CTS_u8IgnOffOat_Y_Len,
    &CTS_au16IgnOffReadBack_Z[0][0]
};

const CTS_tstU16Table2DType CTS_stSunLoadHeat =
{
    CTS_au16SunLoadHeatSun_X,
    (cuint8)CTS_u8SunLoadHeatSun_X_Len,
    CTS_au16SunLoadHeatOat_Y,
    (cuint8)CTS_u8SunLoadHeatOat_Y_Len,
    &CTS_au16SunLoadHeat_Z[0][0]
};

const CTS_tstU8ConstType CTS_stBodyShellHeatChgBase =
{
    (cuint8)CTS_u8BodyShellHeatChgBase
};

const CTS_tstU16ConstType CTS_stBodyShellHeatChg =
{
    (cuint16)CTS_u16BodyShellHeatChg
};

const CTS_tstU16Table2DType CTS_stVelEngineHeat =
{
    CTS_au16VelEngineHeatVel_X,
    (cuint8)CTS_u8VelEngineHeatVel_X_Len,
    CTS_au16VelEngineHeatOat_Y,
    (cuint8)CTS_u8VelEngineHeatOat_Y_Len,
    &CTS_au16VelEngineHeat_Z[0][0]
};

const CTS_tstU16ConstType CTS_stFuelModeBaseHeat =
{
    (cuint16)CTS_u16FuelModeBaseHeat
};

const CTS_tstU16ConstType CTS_stElecModeBaseHeat =
{
    (cuint16)CTS_u16ElecModeBaseHeat
};

const CTS_tstU16ConstType CTS_stCalibrateBaseHeat =
{
    (cuint16)CTS_u16CalibrateBaseHeat
};

const CTS_tstU16Table3DType CTS_stBalanceHeadZoneTemp =
{
    CTS_au16BalanceBlowTemp_X,
    (cuint8)CTS_u8BalanceBlowTemp_X_Len,
    CTS_au16BalanceOat_Y,
    (cuint8)CTS_u8BalanceOat_Y_Len,
    CTS_au16BalanceBlowSpd_Z,
    (cuint8)CTS_u8BalanceBlowSpd_Z_Len,
    &CTS_au16BalanceHeadZoneTemp_U[0][0][0],
};

const CTS_tstU16Table3DType CTS_stCabinTempStcOfs =
{
    CTS_au16CabinOfsSun_X,
    (cuint8)CTS_u8CabinOfsSun_X_Len,
    CTS_au16CabinOfsOat_Y,
    (cuint8)CTS_u8CabinOfsOat_Y_Len,
    CTS_au16CabinOfsAirdPos_Z,
    (cuint8)CTS_u8CabinOfsAirdPos_Z_Len,
    &CTS_au16CabinTempStcOfs_U[0][0][0],
};

const CTS_tstU8ConstType CTS_stHeatItemChgBase =
{
    (cuint8)CTS_u8HeatItemChgBase
};

const CTS_tstU16ConstArrayType CTS_stHeadZoneFlowItemChg =
{
    CTS_au16HeadZoneFlowItemChg,
    (cuint8)CTS_u8AirdModeNum
};

const CTS_tstU16ConstArrayType CTS_stCabinFlowItemChg =
{
    CTS_au16CabinFlowItemChg,
    (cuint8)CTS_u8AirdModeNum
};

const CTS_tstU16ConstType CTS_stShellItemChg =
{
    (cuint16)CTS_u16ShellItemChg
};

const CTS_tstU8ConstType CTS_stFlowItemRtoBase =
{
    (cuint8)CTS_u8FlowItemRtoBase
};

const CTS_tstU8ConstArrayType CTS_stHeadZoneFlowItemRto =
{
    CTS_au8HeadZoneFlowItemRto,
    (cuint8)CTS_u8AirdModeNum
};

const CTS_tstU8ConstArrayType CTS_stCabinFlowItemRto =
{
    CTS_au8CabinFlowItemRto,
    (cuint8)CTS_u8AirdModeNum
};

const CTS_tstU8ConstType CTS_stFlowItemRtoChgBase =
{
    (cuint8)CTS_u8FlowItemRtoChgBase
};

const CTS_tstU16ConstType CTS_stFlowItemRtoChg =
{
    (cuint16)CTS_u16FlowItemRtoChg
};

const CTS_tstU8ConstType CTS_stZoneEffectBase =
{
    (cuint8)CTS_u8ZoneEffectBase
};

const CTS_tstU8ConstArrayType CTS_stDblZoneEffectFactor =
{
    CTS_au8DblZoneEffectFactor,
    (cuint8)CTS_u8AirdModeNum
};

const CTS_tstU8ConstArrayType CTS_stFrontToRearEffectFactor =
{
    CTS_au8FrontToRearEffectFactor,
    (cuint8)CTS_u8AirdModeNum
};

const CTS_tstU8ConstArrayType CTS_stRearToFrontEffectFactor =
{
    CTS_au8RearToFrontEffectFactor,
    (cuint8)CTS_u8AirdModeNum
};

const CTS_tstU16Table3DType CTS_stPreCtlBlowTemp =
{
    CTS_au16PreCtlSetTemp_X,
    (cuint8)CTS_u8PreCtlSetTemp_X_Len,
    CTS_au16PreCtlOat_Y,
    (cuint8)CTS_u8PreCtlOat_Y_Len,
    CTS_au16PreCtlBlowSpd_Z,
    (cuint8)CTS_u8PreCtlBlowSpd_Z_Len,
    &CTS_au16PreCtlBlowTemp_U[0][0][0],
};

const CTS_tstU16ConstType CTS_stFbCtlPFactorBase =
{
    (cuint16)CTS_u16FbCtlPFactorBase
};

const CTS_tstU16Table1DType CTS_stFbCtlPFactor =
{
    CTS_au16FbCtlErr_X,
    (cuint8)CTS_u8FbCtl_Len,
    CTS_au16FbCtlPFactor_Y
};

const CTS_tstU8ConstType CTS_stZoneOfsFactorBase =
{
    (cuint8)CTS_u8ZoneOfsFactorBase
};

const CTS_tstU8ConstArrayType CTS_stDblZoneOfsFactor =
{
    CTS_au8DblZoneOfsFactor,
    (cuint8)CTS_u8AirdModeNum
};

const CTS_tstU8ConstArrayType CTS_stFrontRearOfsFactor =
{
    CTS_au8FrontRearOfsFactor,
    (cuint8)CTS_u8AirdModeNum
};


/***************************************************************************************************
EOF:   CTS_Cfg.c
***************************************************************************************************/
