/***************************************************************************************************
                        ALGORITHM LIBRARY FOR CLIMATE THERMODYNAMICS SYSTEM                        
 
  .File Name  : CTS_Alg.c
  
  .Description: This file provides the algorithm for climate thermodynamics system.
  
  --------------------------------------------------------------------------------------------------
    Version     Date        Author          Change
  --------------------------------------------------------------------------------------------------
    V001        2015-08-10  Chen Xiongzhi   - Creat this module.
    V002        2015-11-10  Chen Xiongzhi   - Rename to VALG.
    V003        2016-01-13  Chen Xiongzhi   - Rename to ATCS_Alg.
    V004        2016-01-20  Chen Xiongzhi   - Rename to CTS_Alg.
***************************************************************************************************/

#define CTS_Alg 


/***************************************************************************************************
                                            HEADER FILES                                            
***************************************************************************************************/

/* System header files */
#include "CTS_StdDef.h"

/* Foreign header files */


/* Own header files */
#include "CTS_Alg.h" 


/***************************************************************************************************
                                   FILE LOCAL FUNCTION PROTOTYES                                   

  Note(s): In this section declare all file local function prototypes needed for your module.
***************************************************************************************************/

static cuint16 CTS_u16Lookup1D_Linear(cuint16 u16Input, cuint8 u8Size, const cuint16 au16TableX[], const cuint16 au16TableY[]);
static cuint16 CTS_u16Lookup2D_Linear(cuint16 u16InputX, cuint16 u16InputY, cuint8 u8SizeX,cuint8 u8SizeY, const cuint16 au16TableX[], const cuint16 au16TableY[], const cuint16 au16TableZ[]);


/*************************************************************************************************** 
  Function   : CTS_u8GetU16ClosestEntry                         
                       
  Description: This function takes a pointer to an array,along with the size of the array and finds 
               the entry that is closest to the input value. If there are two entries in the array 
               that are equidistant from the input, the higher index is returned.                                   
                                                                           
  Arguments  : au16Array[]      - An 16-bit unsigned const array.      
               u8Size           - size of the array                    
               u16Input         - value that will be compared   
               
  Returns    : As cuint8 the index pointing to the closest entry in the array   
***************************************************************************************************/

cuint8 CTS_u8GetU16ClosestEntry(const cuint16 au16Array[], cuint8 u8Size, cuint16 u16Input)
{
    cuint8 u8Index, u8Return;
    cuint16 u16Diff, u16MinimumDiff;

    u16MinimumDiff = (cuint16)0xFFFF;                      

    for (u8Index=0U; u8Index<u8Size; u8Index++) 
    {   
        if (u16Input > au16Array[u8Index])
        {
            u16Diff = u16Input - au16Array[u8Index];
        }
        else
        {
            u16Diff = au16Array[u8Index] - u16Input;
        }

        if (u16Diff < u16MinimumDiff)
        {                                  
            u16MinimumDiff = u16Diff;         
            u8Return = u8Index;
        }
    }

    return u8Return;
}


/*************************************************************************************************** 
  Function   : CTS_u8I16ToU8                         
                       
  Description: This function is used to convert the signed 16-bit value into unsigned 8-bit value.
                                                                           
  Arguments  : i16Input     - is the signed 16-bit value input.
               i16ZeroPoint - is the zero point after the conversion. For example,if the 
                              i16ZeroPoint is -128, after the conversion we use 0 to represent the 
                              value -128 before the conversion.
               
  Returns    : unsigned 8-bit value output  
***************************************************************************************************/

cuint8 CTS_u8I16ToU8(cint16 i16Input, cint16 i16ZeroPoint)
{
    cuint8 u8Return;
    cint16 i16Return;

    if (i16Input < i16ZeroPoint)
    {
        u8Return = 0U;
    }
    else if (i16Input > (i16ZeroPoint+(cint16)0xFF))
    {
        u8Return = (cuint8)0xFF;
    }
    else
    {
        i16Return = i16Input - i16ZeroPoint;
        u8Return = (cuint8)i16Return;
    }

    return u8Return;
}


/*************************************************************************************************** 
  Function   : CTS_u16I16ToU16                         
                       
  Description: This function is used to convert the signed 16-bit value into unsigned 16-bit value.
                                                                           
  Arguments  : i16Input     - is the signed 16-bit value input.
               i16ZeroPoint - is the zero point after the conversion. For example, if the 
                              i16ZeroPoint is -128, after the conversion we use 0 to represent the 
                              value -128 before the conversion.
               
  Returns    : unsigned 16-bit value output  
***************************************************************************************************/

cuint16 CTS_u16I16ToU16(cint16 i16Input, cint16 i16ZeroPoint)
{
    cuint16 u16Return;
    cint32 i32Return;

    if (i16Input < i16ZeroPoint)
    {
        u16Return = 0U;
    }
    else
    {
        i32Return = (cint32)i16Input - (cint32)i16ZeroPoint;
        
        if (i32Return > 0xFFFF)
        {
            i32Return = 0xFFFF;

        }
        
        u16Return = (cuint16)i32Return;
    }

    return u16Return;
}


/*************************************************************************************************** 
  Function   : CTS_u16I32ToU16                         
                       
  Description: This function is used to convert the signed 32-bit value into unsigned 16-bit value.
                                                                           
  Arguments  : i32Input     - is the signed 32-bit value input.
               i32ZeroPoint - is the zero point after the conversion. For example, if the 
                              i32ZeroPoint is -128, after the conversion we use 0 to represent the 
                              value -128 before the conversion.
               
  Returns    : unsigned 16-bit value output  
***************************************************************************************************/

cuint16 CTS_u16I32ToU16(cint32 i32Input, cint32 i32ZeroPoint)
{
    cuint16 u16Return;
    cint32 i32Return;

    if (i32Input < i32ZeroPoint)
    {
        u16Return = 0U;
    }
    else if (i32Input > (i32ZeroPoint+(cint32)0xFFFF))
    {
        u16Return = (cuint16)0xFFFF;
    }
    else
    {
        i32Return = i32Input - i32ZeroPoint;
        u16Return = (cuint16)i32Return;
    }

    return u16Return;
}


/*************************************************************************************************** 
  Function   : CTS_u8I32ToU8                         
                       
  Description: This function is used to convert the signed 32-bit value into unsigned 8-bit value.
                                                                           
  Arguments  : i32Input     - is the signed 32-bit value input.
               i32ZeroPoint - is the zero point after the conversion. For example, if the 
                              i32ZeroPoint is -128, after the conversion we use 0 to represent the 
                              value -128 before the conversion.
               
  Returns    : unsigned 8-bit value output  
***************************************************************************************************/

cuint8 CTS_u8I32ToU8(cint32 i32Input, cint32 i32ZeroPoint)
{
    cuint8 u8Return;
    cint32 i32Return;

    if (i32Input < i32ZeroPoint)
    {
        u8Return = 0U;
    }
    else if (i32Input > (i32ZeroPoint+(cint32)0xFF))
    {
        u8Return = (cuint8)0xFF;
    }
    else
    {
        i32Return = i32Input - i32ZeroPoint;
        u8Return = (cuint8)i32Return;
    }

    return u8Return;
}


/*************************************************************************************************** 
  Function   : CTS_u16U32ToU16                         
                       
  Description: This function is used to convert the unsigned 16-bit value into unsigned 16-bit 
               value.
                                                                           
  Arguments  : u32Input     - is the unsigned 32-bit value input.
               
  Returns    : unsigned 16-bit value output  
***************************************************************************************************/

cuint16 CTS_u16U32ToU16(cuint32 u32Input)
{
    cuint16 u16Return;

    if (u32Input > (cuint32)0xFFFF)
    {
        u16Return = (cuint16)0xFFFF;
    }
    else
    {
        u16Return = (cuint16)u32Input;
    }

    return u16Return;
}


/*************************************************************************************************** 
  Function   : CTS_i32U32ToI32                         
                       
  Description: This function is used to convert the unsigned 32-bit value into signed 32-bit value.
                                                                           
  Arguments  : u32Input     - is the unsigned 32-bit value input.
               
  Returns    : signed 32-bit value output  
***************************************************************************************************/

cint32 CTS_i32U32ToI32(cuint32 u32Input)
{
    cint32 i32Return;
    
    if (u32Input > (cuint32)2147483647)
    {
        i32Return = (cint32)2147483647;
    }
    else
    {
        i32Return = (cint32)u32Input;
    }

    return i32Return;
}


/*************************************************************************************************** 
  Function   : CTS_i32U32ToI32                         
                       
  Description: This function is used to convert the signed 32-bit value into unsigned 32-bit value.
                                                                           
  Arguments  : i32Input     - is the signed 32-bit value input.
               
  Returns    : unsigned 32-bit value output  
***************************************************************************************************/

cuint32 CTS_u32i32ToU32(cint32 i32Input)
{
    cuint32 u32Return;
    
    if (i32Input < 0)
    {
        u32Return = (cuint32)0;
    }
    else
    {
        u32Return = (cuint32)i32Input;
    }

    return u32Return;
}


/*************************************************************************************************** 
  Function   : CTS_i8I16ToI8                         
                       
  Description: This function is used to convert the signed 16-bit value into signed 8-bit value.
                                                                           
  Arguments  : i16Input     - is the signed 16-bit value input.
               
  Returns    : signed 8-bit value output  
***************************************************************************************************/

cint8 CTS_i8I16ToI8(cint16 i16Input)
{
    cint8 i8Return;

    if (i16Input < (cint16)-128)
    {
        i8Return = (cint8)-128;
    }
    else if (i16Input > (cint16)127)
    {
        i8Return = (cint8)127;
    }
    else
    {
        i8Return = (cint8)i16Input;
    }

    return i8Return;
}


/*************************************************************************************************** 
  Function   : CTS_i16I32ToI16                         
                       
  Description: This function is used to convert the signed 32-bit value into signed 16-bit value.
                                                                          
  Arguments  : i32Input     - is the signed 32-bit value input.
               
  Returns    : signed 16-bit value output  
***************************************************************************************************/

cint16 CTS_i16I32ToI16(cint32 i32Input)
{
    cint16 i16Return;

    if (i32Input < (cint32)-32768)
    {
        i16Return = (cint16)-32768;
    }
    else if (i32Input > (cint32)32767)
    {
        i16Return = (cint16)32767;
    }
    else
    {
        i16Return = (cint16)i32Input;
    }

    return i16Return;
}


/*************************************************************************************************** 
  Function   : CTS_u8U32ToU8                         
                       
  Description: This function is used to convert the unsigned 16-bit value into unsigned 8-bit value.
                                                                           
  Arguments  : u32Input     - is the unsigned 32-bit value input.
               
  Returns    : unsigned 8-bit value output  
***************************************************************************************************/

cuint8 CTS_u8U32ToU8(cuint32 u32Input)
{
    cuint8 u8Return;

    if (u32Input > (cuint32)0xFF)
    {
        u8Return = (cuint8)0xFF;
    }
    else
    {
        u8Return = (cuint8)u32Input;
    }

    return u8Return;
}


/*************************************************************************************************** 
  Function   : CTS_u8U16ToU8                         
                       
  Description: This function is used to convert the unsigned 16-bit value into unsigned 8-bit value.
                                                                           
  Arguments  : u16Input     - is the unsigned 16-bit value input.
               
  Returns    : unsigned 8-bit value output  
***************************************************************************************************/

cuint8 CTS_u8U16ToU8(cuint16 u16Input)
{
    cuint8 u8Return;

    if (u16Input > (cuint16)0xFF)
    {
        u8Return = (cuint8)0xFF;
    }
    else
    {
        u8Return = (cuint8)u16Input;
    }

    return u8Return;
}


/***************************************************************************************************
  Function   : CTS_u8Lookup1D_Limit  
  
  Description: This function impliments an 8-bit curve lookup. The input value is converted , 
               using the characteristic curve. If the input is outside the range of x-values the  
               last y-value is returned, hence the "limit". 
                 
  Inputs     : u8Input       - The 8 bit unsigned input value.  
               u8Size        - The amount of points in the curves.
               au8TableX[]   - An array of 8-bit unsigned const values. This array must be  
                               monotonically increasing.    
               au8TableY[]   - An array of 8-bit unsigned const values. This array can be any  
                               function whatsoever.                 
                    
                       Y                                                             
                       ^                                   X******                   
                       |                                  *                          
                       |                                 *                           
               returns<|           X*****X              *                            
                       |          *       *            *                             
                       |      X**X         *          *                              
                       |*****X              X********X                               
                       |                                                             
                       |                                                             
                       +------------------------------------------>X                 
                                      ^                                              
                                   u8Input                                        
                                                                           
  Returns    : The 8-bit output if the interpolation                     
***************************************************************************************************/

cuint8 CTS_u8Lookup1D_Limit(cuint8 u8Input, cuint8 u8Size, const cuint8 au8TableX[], const cuint8 au8TableY[])
{
   cuint8 u8Index, u8X1, u8Y1, u8Return;
   cint16 i16XDiff, i16YDiff, i16Return;

   u8Index = u8Size - 1U;
   
    if (u8Input <= au8TableX[0])      
    {
        u8Return = au8TableY[0];
    }
    else if (u8Input >= au8TableX[u8Size-1U])   
    {
        u8Return = au8TableY[u8Size-1U];     
    }
    else
    {
        for (u8Index=u8Size-1U; u8Index>0U; u8Index--)
        {
            if (u8Input > au8TableX[u8Index-1U])
            {
                u8X1 = au8TableX[u8Index-1U];
                u8Y1 = au8TableY[u8Index-1U];
                i16YDiff = (cint16)au8TableY[u8Index] - (cint16)u8Y1;
                i16XDiff = (cint16)au8TableX[u8Index] - (cint16)u8X1;
                break;
            }
        }

        if ((i16XDiff==0) || (i16YDiff==0) || (u8Input==u8X1)) 
        {
            u8Return = u8Y1;
        }
        else
        {
            i16Return = (cint16)u8Y1 + ((i16YDiff *((cint16)u8Input-(cint16)u8X1))/i16XDiff);
            u8Return = CTS_u8I16ToU8(i16Return, 0);
        }
    }

    return u8Return;
}


/***************************************************************************************************
  Function   : CTS_u8Lookup2D_Limit  
  
  Description: This function impliments an 8-bit 2D lookup. The input value is converted , using 
               the characteristic curve. If the input is outside the range of x-values the last 
               y-value is returned, hence the "limit".  
                  
  Inputs     : u8InputX          - The 8 bit unsigned input value.                  
               u8InputY          - The 8 bit unsigned input value. 
               u8SizeX, u8SizeY  - The amount of points in the curves. 
               au8TableX[]       - An array of 8-bit unsigned const values. This array must be  
                                   monotonically increasing.                  
               au8TableY[]       - An array of 8-bit unsigned const values. This array must be  
                                   monotonically increasing.    
               au8TableZ[]       - An array of 8-bit unsigned const values. This array can be any  
                                   function whatsoever.                  
                  
                           Y                                                      
                           ^                               			          
                           |                             			      
                           |                  				  
                           |                 			 	                  
               InputY> |---|------------+ >returnsZ                			 	      
                           |            |			              
                           |            |                               
                           |            |                                
                           |            |				                         
                           |            |                  				      
                           +------------------------>X                   
                                        ^                                    
                                     InputX                                  
                                                                             
  Returns    : The 8-bit output if the interpolation                    
***************************************************************************************************/

cuint8 CTS_u8Lookup2D_Limit(cuint8 u8InputX, cuint8 u8InputY, cuint8 u8SizeX, cuint8 u8SizeY, const cuint8 au8TableX[], const cuint8 au8TableY[], const cuint8 au8TableZ[])
{
    cuint8 u8Return;
    cuint8 au8Table[2];
	
    if (u8InputY <= au8TableY[0])
    {	
        u8Return = CTS_u8Lookup1D_Limit(u8InputX, u8SizeX, au8TableX, &au8TableZ[0]);
    }
    else if (u8InputY >= au8TableY[u8SizeY-1U])
    {	
        u8Return = CTS_u8Lookup1D_Limit(u8InputX, u8SizeX, au8TableX, 
                   &au8TableZ[((cuint16)u8SizeY-1U)*(cuint16)u8SizeX]);
    }	
    else
    {
        cuint8 u8Index;
        
        for (u8Index=1U; u8Index<u8SizeY; u8Index++)
        {
            if (u8InputY <= au8TableY[u8Index])
            {
                if (u8InputY < au8TableY[u8Index])
                {
                    au8Table[0] = CTS_u8Lookup1D_Limit(u8InputX, u8SizeX, au8TableX, 
                                  &au8TableZ[((cuint16)u8Index-1U)*(cuint16)u8SizeX]);
                    
                    au8Table[1] = CTS_u8Lookup1D_Limit(u8InputX, u8SizeX, au8TableX, 
                                  &au8TableZ[(cuint16)u8Index*(cuint16)u8SizeX]);
                    
                    u8Return = CTS_u8Lookup1D_Limit(u8InputY, 2U, &au8TableY[u8Index-1U], 
                               &au8Table[0]); 
                }
                else
                {
                    u8Return = CTS_u8Lookup1D_Limit(u8InputX, u8SizeX, au8TableX, 
                               &au8TableZ[(cuint16)u8Index*(cuint16)u8SizeX]);
                }

                break;		
            }
        }
    }

    return u8Return;
}


/***************************************************************************************************
  Function   : CTS_u8Lookup1D_Linear  
  
  Description: This function impliments an 8-bit curve lookup. The input value is converted , 
               using the characteristic curve. If the input is outside the range of x-values the  
               y-value is calculated according to the last two piont, hence the "linear".
                 
  Inputs     : u8Input       - The 8 bit unsigned input value.  
               u8Size        - The amount of points in the curves.
               au8TableX[]   - An array of 8-bit unsigned const values. This array must be  
                               monotonically increasing.    
               au8TableY[]   - An array of 8-bit unsigned const values. This array can be any  
                               function whatsoever.                 
                    
                       Y                                                             
                       ^                                   *                  
                       |                                  *                          
                       |                                 *                           
               returns<|           X*****X              X                           
                       |          *       *            *                             
                       |      X**X         *          *                              
                       |     X              X********X                               
                       |    *                                                        
                       |   *                                                         
                       +------------------------------------------>X                 
                                      ^                                              
                                   u8Input                                        
                                                                           
  Returns    : The 8-bit output if the interpolation                     
***************************************************************************************************/

cuint8 CTS_u8Lookup1D_Linear(cuint8 u8Input, cuint8 u8Size, const cuint8 au8TableX[], const cuint8 au8TableY[])
{
   cuint8 u8Index, u8X1, u8Y1, u8Return;
   cint16 i16XDiff, i16YDiff, i16Return;

    if (u8Input <= au8TableX[0])
    {
        u8X1 = au8TableX[0];
        u8Y1 = au8TableY[0];
        i16YDiff = (cint16)au8TableY[1] - (cint16)u8Y1;
        i16XDiff = (cint16)au8TableX[1] - (cint16)u8X1;  
    }
    else if (u8Input >= au8TableX[u8Size-1U])   
    {
        u8X1 = au8TableX[u8Size-2U];
        u8Y1 = au8TableY[u8Size-2U];
        i16YDiff = (cint16)au8TableY[u8Size-1U] - (cint16)u8Y1;
        i16XDiff = (cint16)au8TableX[u8Size-1U] - (cint16)u8X1;     
    }
    else                             
    {
        for (u8Index=u8Size-1U; u8Index>0U; u8Index--)
        {
            if (u8Input > au8TableX[u8Index-1U])
            {
                u8X1 = au8TableX[u8Index-1U];
                u8Y1 = au8TableY[u8Index-1U];
                i16YDiff = (cint16)au8TableY[u8Index] - (cint16)u8Y1;
                i16XDiff = (cint16)au8TableX[u8Index] - (cint16)u8X1;
                break;
            }
        }   
    }
    
    if ((i16XDiff==0) || (i16YDiff==0) || (u8Input==u8X1)) 
    {
        u8Return = u8Y1;
    }
    else
    {
        i16Return = (cint16)u8Y1 + ((i16YDiff *((cint16)u8Input-(cint16)u8X1))/i16XDiff);
        u8Return = CTS_u8I16ToU8(i16Return, 0);
    }
    
    return u8Return;
}


/***************************************************************************************************
  Function   : CTS_u8Lookup2D_Linear 
  
  Description: This function impliments an 8-bit 2D lookup. The input value is converted , using 
               the characteristic curve. If the input is outside the range of x-values the y-value 
               is calculated according to the last two piont, hence the "linear".  
                  
  Inputs     : u8InputX          - The 8 bit unsigned input value.                  
               u8InputY          - The 8 bit unsigned input value. 
               u8SizeX, u8SizeY  - The amount of points in the curves. 
               au8TableX[]       - An array of 8-bit unsigned const values. This array must be  
                                   monotonically increasing.                  
               au8TableY[]       - An array of 8-bit unsigned const values. This array must be  
                                   monotonically increasing.    
               au8TableZ[]       - An array of 8-bit unsigned const values. This array can be any  
                                   function whatsoever.                  
                   
                           Y                                                      
                           ^                               			          
                           |                             			      
                           |                  				  
                           |                 			 	                  
               InputY> |---|------------+ >returnsZ                			 	      
                           |            |			              
                           |            |                               
                           |            |                                
                           |            |				                         
                           |            |                  				      
                           +------------------------>X                   
                                        ^                                    
                                     InputX                                  
                                                                             
  Returns    : The 8-bit output if the interpolation                    
***************************************************************************************************/

cuint8 CTS_u8Lookup2D_Linear(cuint8 u8InputX, cuint8 u8InputY, cuint8 u8SizeX, cuint8 u8SizeY, const cuint8 au8TableX[], const cuint8 au8TableY[], const cuint8 au8TableZ[])
{
    cuint8 u8Return;
    cuint8 au8Table[2];
	
    if (u8InputY <= au8TableY[0])
    {	
        u8Return = CTS_u8Lookup1D_Linear(u8InputX, u8SizeX, au8TableX, &au8TableZ[0]);
    }
    else if (u8InputY >= au8TableY[u8SizeY-1U])
    {	
        u8Return = CTS_u8Lookup1D_Linear(u8InputX, u8SizeX, au8TableX, 
                   &au8TableZ[((cuint16)u8SizeY-1U)*(cuint16)u8SizeX]);
    }	
    else
    {
        cuint8 u8Index;
        
        for (u8Index=1U; u8Index<u8SizeY; u8Index++)
        {
            if (u8InputY <= au8TableY[u8Index])
            {
                if (u8InputY < au8TableY[u8Index])
                {
                    au8Table[0] = CTS_u8Lookup1D_Linear(u8InputX, u8SizeX, au8TableX, 
                                  &au8TableZ[((cuint16)u8Index-1U)*(cuint16)u8SizeX]);
                    
                    au8Table[1] = CTS_u8Lookup1D_Linear(u8InputX, u8SizeX, au8TableX, 
                                  &au8TableZ[(cuint16)u8Index*(cuint16)u8SizeX]);
                    
                    u8Return = CTS_u8Lookup1D_Linear(u8InputY, 2U, &au8TableY[u8Index-1U], 
                               &au8Table[0]); 
                }
                else
                {
                    u8Return = CTS_u8Lookup1D_Linear(u8InputX, u8SizeX, au8TableX, 
                               &au8TableZ[(cuint16)u8Index*(cuint16)u8SizeX]);
                }

                break;		
            }
        }
    }

    return u8Return;
}


/***************************************************************************************************
  Function   : CTS_u16Lookup1D_Limit  
  
  Description: This function impliments an 16-bit curve lookup. The input value is converted , 
               using the characteristic curve. If the input is outside the range of x-values the  
               last y-value is returned, hence the "limit". 
                 
  Inputs     : u16Input          - The 16 bit unsigned input value.      
               u8Size            - The amount of points in the curves. 
               au16TableX[]      - An array of 16-bit unsigned const values. This array must be  
                                   monotonically increasing.    
               au16TableY[]      - An array of 16-bit unsigned const values. This array can be   
                                   any function whatsoever.                  
                   
                       Y                                                             
                       ^                                   X******                   
                       |                                  *                          
                       |                                 *                           
               returns<|           X*****X              *                            
                       |          *       *            *                             
                       |      X**X         *          *                              
                       |*****X              X********X                               
                       |                                                             
                       |                                                             
                       +------------------------------------------>X                 
                                      ^                                              
                                  u16Input                                        
                                                                           
  Returns    : The 16-bit output if the interpolation                     
***************************************************************************************************/

cuint16 CTS_u16Lookup1D_Limit(cuint16 u16Input, cuint8 u8Size, const cuint16 au16TableX[], const cuint16 au16TableY[])
{
    cuint8 u8Index;
    cuint16 u16X1, u16Y1, u16Return;
    cint32 i32XDiff, i32YDiff, i32Return;

    if (u16Input <= au16TableX[0])
    {
        u16Return = au16TableY[0];
    }
    else if (u16Input >= au16TableX[u8Size-1U])
    {
        u16Return = au16TableY[u8Size-1U];        
    }
    else
    {
        for (u8Index=u8Size-1U; u8Index>0U; u8Index--)
        {
            if (u16Input > au16TableX[u8Index-1U])
            {
                u16X1 = au16TableX[u8Index-1U];
                u16Y1 = au16TableY[u8Index-1U];
                i32YDiff = (cint32)au16TableY[u8Index] - (cint32)u16Y1;
                i32XDiff = (cint32)au16TableX[u8Index] - (cint32)u16X1;
                break;
            }
        }

        if ((i32XDiff==0) || (i32YDiff==0) || (u16Input==u16X1)) 
        {
            u16Return = u16Y1;
        }
        else
        { 
            i32Return = (cint32)u16Y1 + ((i32YDiff*((cint32)u16Input-(cint32)u16X1))/i32XDiff);
            u16Return = CTS_u16I32ToU16(i32Return, 0);
        }
    }

    return u16Return;
}


/***************************************************************************************************
  Function   : CTS_u16Lookup2D_Limit  

  Description: This function impliments an 16-bit 2D lookup. The input value is converted , using 
               the characteristic curve. If the input is outside the range of x-values the last 
               y-value is returned, hence the "limit".  
                  
  Inputs     : u16InputX         - The 16 bit unsigned input value.                  
               u16InputY         - The 16 bit unsigned input value.   
               u8SizeX, u8SizeY  - The amount of points in the curves. 
               au16TableX[]      - An array of 16-bit unsigned const values. This array must be  
                                   monotonically increasing.                  
               au16TableY[]      - An array of 16-bit unsigned const values. This array must be  
                                   monotonically increasing.    
               au16TableZ[]      - An array of 16-bit unsigned const values. This array can be 
                                   any function whatsoever.                 
                  
                             Y                                                      
                           ^                               			          
                           |                             			      
                           |                  				  
                           |                 			 	                  
               InputY> |---|------------+ >returnsZ                			 	      
                           |            |			              
                           |            |                               
                           |            |                                
                           |            |				                         
                           |            |                  				      
                           +------------------------>X                   
                                        ^                                    
                                     InputX                                 
                                                                             
  Returns    : The 16-bit output if the interpolation                    
***************************************************************************************************/

cuint16 CTS_u16Lookup2D_Limit(cuint16 u16InputX, cuint16 u16InputY, cuint8 u8SizeX,cuint8 u8SizeY, const cuint16 au16TableX[], const cuint16 au16TableY[], const cuint16 au16TableZ[])
{
    cuint16 u16Return;
    cuint16 au16Table[2];

    if (u16InputY <= au16TableY[0])
    {	
        u16Return = CTS_u16Lookup1D_Limit(u16InputX, u8SizeX, au16TableX, au16TableZ);
    }
    else if (u16InputY >= au16TableY[u8SizeY-1U])
    {	
        u16Return = CTS_u16Lookup1D_Limit(u16InputX, u8SizeX, au16TableX, 
                    &au16TableZ[((cuint16)u8SizeY-1U)*(cuint16)u8SizeX]);
    }	
    else
    {
        cuint8 u8Index;

        for (u8Index=1U; u8Index<u8SizeY; u8Index++)
        {
            if (u16InputY <= au16TableY[u8Index])
            {
                if (u16InputY < au16TableY[u8Index])
                {
                    au16Table[0] = CTS_u16Lookup1D_Limit(u16InputX, u8SizeX, au16TableX, 
                                   &au16TableZ[((cuint16)u8Index-1U)*(cuint16)u8SizeX]);
                    
                    au16Table[1] = CTS_u16Lookup1D_Limit(u16InputX, u8SizeX, au16TableX, 
                                   &au16TableZ[(cuint16)u8Index*(cuint16)u8SizeX]);
                    
                    u16Return = CTS_u16Lookup1D_Limit(u16InputY, 2U, &au16TableY[u8Index-1U], 
                                &au16Table[0]); 
                }
                else
                {
                    u16Return = CTS_u16Lookup1D_Limit(u16InputX, u8SizeX, au16TableX, 
                                &au16TableZ[(cuint16)u8Index*(cuint16)u8SizeX]);
                }

                break;		
            }
        }
    }

    return u16Return;
}


/***************************************************************************************************
  Function   : CTS_u16Lookup3D_Limit  

  Description: This function is used for 3D look up.  
                  
  Inputs     : u16InputX         - The 16 bit unsigned input value.                  
               u16InputY         - The 16 bit unsigned input value.   
               u16InputZ         - The 16 bit unsigned input value.   
               u8SizeX           - The amount of points in the curves. 
               u8SizeY           - The amount of points in the curves. 
               u8SizeZ           - The amount of points in the curves. 
               au16TableX[]      - X input table.                  
               au16TableY[]      - Y input table.    
               au16TableZ[]      - Z input table. 
               au16TableU[]      - Output table.
                                
                           Y          ^  Z                                                   
                           ^    _ _ _/_ _ _ U(x,y,z)>ReturnsU                                  			          
                           |  /|    /      /|                              			      
                           | / |   /      / |                  				  
                           |/  |  /      /  |                  			 	                  
               InputY> |---|------------|   |                  			 	      
                           |   |/_ _ _ _|_ _|	<InputZ				              
                           |   /        |   /                                  
                           |  /         |  /                                   
                           | /          | /				                         
                           |/           |/                  				      
                           +------------------------>X                   
                                        ^                                    
                                     InputX                                  
                                                                             
  Returns    : The 16-bit output if the interpolation                    
***************************************************************************************************/

cuint16 CTS_u16Lookup3D_Limit(cuint16 u16InputX, cuint16 u16InputY, cuint16 u16InputZ, cuint8 u8SizeX, cuint8 u8SizeY, cuint8 u8SizeZ, const cuint16 au16TableX[], const cuint16 au16TableY[], const cuint16 au16TableZ[], const cuint16 au16TableU[])
{
    cuint16 u16Return;
    cuint16 au16Table[2];

    if (u16InputZ <= au16TableZ[0])
    {	
        u16Return = CTS_u16Lookup2D_Limit(u16InputX, u16InputY, u8SizeX, u8SizeY, au16TableX, 
                    au16TableY, au16TableU);
    }
    else if (u16InputZ >= au16TableZ[u8SizeZ-1U])
    {	
        u16Return = CTS_u16Lookup2D_Limit(u16InputX, u16InputY, u8SizeX, u8SizeY, au16TableX, 
                    au16TableY, &au16TableU[((cuint16)u8SizeZ-1U)*(cuint16)u8SizeX*(cuint16)u8SizeY]); 
    }	
    else
    {
        cuint8 u8Index;

        for (u8Index=1U; u8Index<u8SizeZ; u8Index++)
        {
            if (u16InputZ <= au16TableZ[u8Index])
            {
                if (u16InputZ < au16TableZ[u8Index])
                {
                    au16Table[0] =  CTS_u16Lookup2D_Limit(u16InputX, u16InputY, u8SizeX, u8SizeY,  
                                    au16TableX, au16TableY, 
                                    &au16TableU[((cuint16)u8Index-1U)*(cuint16)u8SizeX*(cuint16)u8SizeY]);
                    
                    au16Table[1] =  CTS_u16Lookup2D_Limit(u16InputX, u16InputY, u8SizeX, u8SizeY,  
                                    au16TableX, au16TableY, 
                                    &au16TableU[(cuint16)u8Index*(cuint16)u8SizeX*(cuint16)u8SizeY]);
                    
                    u16Return = CTS_u16Lookup1D_Limit(u16InputZ, 2U, &au16TableZ[u8Index-1U], 
                                &au16Table[0]); 
                }
                else
                {
                    u16Return = CTS_u16Lookup2D_Limit(u16InputX, u16InputY, u8SizeX, u8SizeY,  
                                au16TableX, au16TableY, 
                                &au16TableU[(cuint16)u8Index*(cuint16)u8SizeX*(cuint16)u8SizeY]);
                }

                break;		
            }
        }
    }

    return u16Return;
}


/***************************************************************************************************
  Function   : CTS_u16Lookup1D_Linear  
  
  Description: This function impliments an 16-bit curve lookup. The input value is converted , 
               using the characteristic curve. If the input is outside the range of x-values the  
               y-value is calculated according to the last two piont, hence the "linear". 
                 
  Inputs     : u16Input          - The 16 bit unsigned input value.      
               u8Size            - The amount of points in the curves. 
               au16TableX[]      - An array of 16-bit unsigned const values. This array must be  
                                   monotonically increasing.    
               au16TableY[]      - An array of 16-bit unsigned const values. This array can be   
                                   any function whatsoever.                  
                             
                       Y                                                             
                       ^                                   *                   
                       |                                  *                          
                       |                                 *                           
               returns<|           X*****X              X                            
                       |          *       *            *                             
                       |      X**X         *          *                              
                       |     X              X********X                               
                       |    *                                                        
                       |   *                                                          
                       +------------------------------------------>X                 
                                      ^                                              
                                  u16Input                                        
                                                                           
  Returns    : The 16-bit output if the interpolation                     
***************************************************************************************************/

static cuint16 CTS_u16Lookup1D_Linear(cuint16 u16Input, cuint8 u8Size, const cuint16 au16TableX[], const cuint16 au16TableY[])
{
    cuint8 u8Index;
    cuint16 u16X1, u16Y1, u16Return;
    cint32 i32XDiff, i32YDiff, i32Return;

    if (u16Input <= au16TableX[0]) 
    {
        u16X1 = au16TableX[0];
        u16Y1 = au16TableY[0];
        i32YDiff = (cint32)au16TableY[1] - (cint32)u16Y1;
        i32XDiff = (cint32)au16TableX[1] - (cint32)u16X1; 
    }
    else if (u16Input >= au16TableX[u8Size-1U])
    {
        u16X1 = au16TableX[u8Size-2U];
        u16Y1 = au16TableY[u8Size-2U];
        i32YDiff = (cint32)au16TableY[u8Size-1U] - (cint32)u16Y1;
        i32XDiff = (cint32)au16TableX[u8Size-1U] - (cint32)u16X1;       
    } 
    else
    {
        for (u8Index=u8Size-1U; u8Index>0U; u8Index--)
        {
            if (u16Input > au16TableX[u8Index-1U])
            {
                u16X1 = au16TableX[u8Index-1U];
                u16Y1 = au16TableY[u8Index-1U];
                i32YDiff = (cint32)au16TableY[u8Index] - (cint32)u16Y1;
                i32XDiff = (cint32)au16TableX[u8Index] - (cint32)u16X1;
                break;
            }
        }
    }

    if ((i32XDiff==0) || (i32YDiff==0) || (u16Input==u16X1)) 
    {
        u16Return = u16Y1;
    }
    else
    { 
        i32Return = (cint32)u16Y1 + ((i32YDiff*((cint32)u16Input-(cint32)u16X1))/i32XDiff);
        u16Return = CTS_u16I32ToU16(i32Return, 0);
    }

    return u16Return;
}


/***************************************************************************************************
  Function   : CTS_u16Lookup2D_Linear  

  Description: This function impliments an 16-bit 2D lookup. The input value is converted , using 
               the characteristic curve. If the input is outside the range of x-values the y-value  
               is calculated according to the last two piont, hence the "linear".  
                  
  Inputs     : u16InputX         - The 16 bit unsigned input value.                  
               u16InputY         - The 16 bit unsigned input value.   
               u8SizeX, u8SizeY  - The amount of points in the curves. 
               au16TableX[]      - An array of 16-bit unsigned const values. This array must be  
                                   monotonically increasing.                  
               au16TableY[]      - An array of 16-bit unsigned const values. This array must be  
                                   monotonically increasing.    
               au16TableZ[]      - An array of 16-bit unsigned const values. This array can be 
                                   any function whatsoever.                 
                  
                             Y                                                      
                           ^                               			          
                           |                             			      
                           |                  				  
                           |                 			 	                  
               InputY> |---|------------+ >returnsZ                			 	      
                           |            |			              
                           |            |                               
                           |            |                                
                           |            |				                         
                           |            |                  				      
                           +------------------------>X                   
                                        ^                                    
                                     InputX                                 
                                                                             
  Returns    : The 16-bit output if the interpolation                    
***************************************************************************************************/

static cuint16 CTS_u16Lookup2D_Linear(cuint16 u16InputX, cuint16 u16InputY, cuint8 u8SizeX,cuint8 u8SizeY, const cuint16 au16TableX[], const cuint16 au16TableY[], const cuint16 au16TableZ[])
{
    cuint8 u8Index;
    cuint16 u16Return;
    cuint16 au16Table[2];

    if (u16InputY <= au16TableY[0])
    {	
	if (u16InputY < au16TableY[0])
	{
		au16Table[0] = CTS_u16Lookup1D_Linear(u16InputX, u8SizeX, au16TableX, au16TableZ);

		au16Table[1] = CTS_u16Lookup1D_Linear(u16InputX, u8SizeX, au16TableX, 
	                                   &au16TableZ[((cuint16)1U)*(cuint16)u8SizeX]);

		u16Return = CTS_u16Lookup1D_Linear(u16InputY, 2U, &au16TableY[0], 
		            &au16Table[0]); 
	}
	else
	{
		u16Return = CTS_u16Lookup1D_Linear(u16InputX, u8SizeX, au16TableX, au16TableZ);
	}
    }
    else if (u16InputY >= au16TableY[u8SizeY-1U])
    {	
	 if (u16InputY > au16TableY[u8SizeY-1U])
	 {
	 	au16Table[0] = CTS_u16Lookup1D_Linear(u16InputX, u8SizeX, au16TableX, 
                    &au16TableZ[((cuint16)u8SizeY-2U)*(cuint16)u8SizeX]);

		au16Table[1] = CTS_u16Lookup1D_Linear(u16InputX, u8SizeX, au16TableX, 
                    &au16TableZ[((cuint16)u8SizeY-1U)*(cuint16)u8SizeX]);

		u16Return = CTS_u16Lookup1D_Linear(u16InputY, 2U, &au16TableY[u8SizeY-2U], 
		            &au16Table[0]); 
	 }
	 else
	 {
	 	u16Return = CTS_u16Lookup1D_Linear(u16InputX, u8SizeX, au16TableX, 
                    &au16TableZ[((cuint16)u8SizeY-1U)*(cuint16)u8SizeX]);
	 }
    }	
    else
    {
        for (u8Index=1U; u8Index<u8SizeY; u8Index++)
        {
            if (u16InputY <= au16TableY[u8Index])
            {
                if (u16InputY < au16TableY[u8Index])
                {
                    au16Table[0] = CTS_u16Lookup1D_Linear(u16InputX, u8SizeX, au16TableX, 
                                   &au16TableZ[((cuint16)u8Index-1U)*(cuint16)u8SizeX]);
                    
                    au16Table[1] = CTS_u16Lookup1D_Linear(u16InputX, u8SizeX, au16TableX, 
                                   &au16TableZ[(cuint16)u8Index*(cuint16)u8SizeX]);
                    
                    u16Return = CTS_u16Lookup1D_Linear(u16InputY, 2U, &au16TableY[u8Index-1U], 
                                &au16Table[0]); 
                }
                else
                {
                    u16Return = CTS_u16Lookup1D_Linear(u16InputX, u8SizeX, au16TableX, 
                                &au16TableZ[(cuint16)u8Index*(cuint16)u8SizeX]);
                }

                break;		
            }
        }
    }

    return u16Return;
}


/***************************************************************************************************
  Function   : CTS_u16Lookup3D_Linear  

  Description: This function is used for 3D look up. If the input is outside the range of x-values 
               the y-value is calculated according to the last two piont, hence the "linear".  
                  
  Inputs     : u16InputX         - The 16 bit unsigned input value.                  
               u16InputY         - The 16 bit unsigned input value.   
               u16InputZ         - The 16 bit unsigned input value.   
               u8SizeX           - The amount of points in the curves. 
               u8SizeY           - The amount of points in the curves. 
               u8SizeZ           - The amount of points in the curves. 
               au16TableX[]      - X input table.                  
               au16TableY[]      - Y input table.    
               au16TableZ[]      - Z input table. 
               au16TableU[]      - Output table.
                                
                           Y          ^  Z                                                   
                           ^    _ _ _/_ _ _ U(x,y,z)>ReturnsU                                  			          
                           |  /|    /      /|                              			      
                           | / |   /      / |                  				  
                           |/  |  /      /  |                  			 	                  
               InputY> |---|------------|   |                  			 	      
                           |   |/_ _ _ _|_ _|	<InputZ				              
                           |   /        |   /                                  
                           |  /         |  /                                   
                           | /          | /				                         
                           |/           |/                  				      
                           +------------------------>X                   
                                        ^                                    
                                     InputX                                  
                                                                             
  Returns    : The 16-bit output if the interpolation                    
***************************************************************************************************/

cuint16 CTS_u16Lookup3D_Linear(cuint16 u16InputX, cuint16 u16InputY, cuint16 u16InputZ, cuint8 u8SizeX, cuint8 u8SizeY, cuint8 u8SizeZ, const cuint16 au16TableX[], const cuint16 au16TableY[], const cuint16 au16TableZ[], const cuint16 au16TableU[])
{
    cuint8 u8Index;
    cuint16 u16Return;
    cuint16 au16Table[2];

    if (u16InputZ <= au16TableZ[0])
    {	
	  if (u16InputZ < au16TableZ[0])
            {
                au16Table[0] =  CTS_u16Lookup2D_Linear(u16InputX, u16InputY, u8SizeX, u8SizeY,  
                                au16TableX, au16TableY, au16TableU);
                
                au16Table[1] =  CTS_u16Lookup2D_Linear(u16InputX, u16InputY, u8SizeX, u8SizeY,  
                                au16TableX, au16TableY, 
                                &au16TableU[(cuint16)1*(cuint16)u8SizeX*(cuint16)u8SizeY]);
                
                u16Return = CTS_u16Lookup1D_Linear(u16InputZ, 2U, &au16TableZ[0], 
                            &au16Table[0]); 
            }
            else
            {
                u16Return = CTS_u16Lookup2D_Linear(u16InputX, u16InputY, u8SizeX, u8SizeY, au16TableX, 
                    			au16TableY, au16TableU);
            }
    }
    else if (u16InputZ >= au16TableZ[u8SizeZ-1U])
    {	
	     if (u16InputZ > au16TableZ[u8SizeZ-1U])
            {
                au16Table[0] =  CTS_u16Lookup2D_Linear(u16InputX, u16InputY, u8SizeX, u8SizeY, au16TableX, 
                    au16TableY, &au16TableU[((cuint16)u8SizeZ-2U)*(cuint16)u8SizeX*(cuint16)u8SizeY]); 
                
                au16Table[1] =  CTS_u16Lookup2D_Linear(u16InputX, u16InputY, u8SizeX, u8SizeY, au16TableX, 
                    au16TableY, &au16TableU[((cuint16)u8SizeZ-1U)*(cuint16)u8SizeX*(cuint16)u8SizeY]); 
                
                u16Return = CTS_u16Lookup1D_Linear(u16InputZ, 2U, &au16TableZ[u8SizeZ-2U], 
                            &au16Table[0]); 
            }
            else
            {
                u16Return = CTS_u16Lookup2D_Linear(u16InputX, u16InputY, u8SizeX, u8SizeY, au16TableX, 
                    au16TableY, &au16TableU[((cuint16)u8SizeZ-1U)*(cuint16)u8SizeX*(cuint16)u8SizeY]); 
            }
    }	
    else
    {
        for (u8Index=1U; u8Index<u8SizeZ; u8Index++)
        {
            if (u16InputZ <= au16TableZ[u8Index])
            {
                if (u16InputZ < au16TableZ[u8Index])
                {
                    au16Table[0] =  CTS_u16Lookup2D_Linear(u16InputX, u16InputY, u8SizeX, u8SizeY,  
                                    au16TableX, au16TableY, 
                                    &au16TableU[((cuint16)u8Index-1U)*(cuint16)u8SizeX*(cuint16)u8SizeY]);
                    
                    au16Table[1] =  CTS_u16Lookup2D_Linear(u16InputX, u16InputY, u8SizeX, u8SizeY,  
                                    au16TableX, au16TableY, 
                                    &au16TableU[(cuint16)u8Index*(cuint16)u8SizeX*(cuint16)u8SizeY]);
                    
                    u16Return = CTS_u16Lookup1D_Linear(u16InputZ, 2U, &au16TableZ[u8Index-1U], 
                                &au16Table[0]); 
                }
                else
                {
                    u16Return = CTS_u16Lookup2D_Linear(u16InputX, u16InputY, u8SizeX, u8SizeY,  
                                au16TableX, au16TableY, 
                                &au16TableU[(cuint16)u8Index*(cuint16)u8SizeX*(cuint16)u8SizeY]);
                }

                break;		
            }
        }
    }

    return u16Return;
}


/***************************************************************************************************
  Function   : CTS_u16Lookup4D_Linear  

  Description: This function is used for 4D look up. If the input is outside the range of x-values 
               the y-value is calculated according to the last two piont, hence the "linear".  
                  
  Inputs     : u16InputX         - The 16 bit unsigned input value.                  
               u16InputY         - The 16 bit unsigned input value.   
               u16InputZ         - The 16 bit unsigned input value.   
               u16InputU         - The 16 bit unsigned input value.     
               u8SizeX           - The amount of points in the curves. 
               u8SizeY           - The amount of points in the curves. 
               u8SizeZ           - The amount of points in the curves.
               u8SizeU           - The amount of points in the curves.
               au16TableX[]      - X input table.                  
               au16TableY[]      - Y input table.    
               au16TableZ[]      - Z input table. 
               au16TableU[]      - U input table.
               au16TableV[]      - Output table.                                
                                                                             
  Returns    : The 16-bit output if the interpolation                    
***************************************************************************************************/

cuint16 CTS_u16Lookup4D_Linear(cuint16 u16InputX, cuint16 u16InputY, cuint16 u16InputZ, cuint16 u16InputU, cuint8 u8SizeX, cuint8 u8SizeY, cuint8 u8SizeZ, cuint8 u8SizeU, const cuint16 au16TableX[], const cuint16 au16TableY[], const cuint16 au16TableZ[], const cuint16 au16TableU[], const cuint16 au16TableV[])
{
    cuint8 u8Index;
    cuint16 u16Return;
    cuint16 au16Table[2];

    if (u16InputU <= au16TableU[0])
    {	
        u16Return = CTS_u16Lookup3D_Linear(u16InputX, u16InputY, u16InputZ, u8SizeX, u8SizeY, 
                    u8SizeZ,au16TableX, au16TableY, au16TableZ, au16TableV);
    }
    else if (u16InputU >= au16TableU[u8SizeU-1U])
    {	
        u16Return = CTS_u16Lookup3D_Linear(u16InputX, u16InputY, u16InputZ, u8SizeX, u8SizeY, 
                    u8SizeZ,au16TableX, au16TableY, au16TableZ, 
                    &au16TableV[((cuint16)u8SizeU-1U)*(cuint16)u8SizeZ*(cuint16)u8SizeX*(cuint16)u8SizeY]); 
    }	
    else
    {
        for (u8Index=1U; u8Index<u8SizeU; u8Index++)
        {
            if (u16InputU <= au16TableU[u8Index])
            {
                if (u16InputU < au16TableU[u8Index])
                {
                    au16Table[0] =  CTS_u16Lookup3D_Linear(u16InputX, u16InputY, u16InputZ, u8SizeX, 
                                    u8SizeY, u8SizeZ,au16TableX, au16TableY, au16TableZ, 
                                    &au16TableV[((cuint16)u8Index-1U)*(cuint16)u8SizeZ*(cuint16)u8SizeX*(cuint16)u8SizeY]);
                    
                    au16Table[1] =  CTS_u16Lookup3D_Linear(u16InputX, u16InputY, u16InputZ, u8SizeX, 
                                    u8SizeY, u8SizeZ,au16TableX, au16TableY, au16TableZ, 
                                    &au16TableV[(cuint16)u8Index*(cuint16)u8SizeZ*(cuint16)u8SizeX*(cuint16)u8SizeY]);
                    
                    u16Return = CTS_u16Lookup1D_Linear(u16InputU, 2U, &au16TableU[u8Index-1U], 
                                &au16Table[0]); 
                }
                else
                {
                    u16Return = CTS_u16Lookup3D_Linear(u16InputX, u16InputY, u16InputZ, u8SizeX, 
                                u8SizeY, u8SizeZ,au16TableX, au16TableY, au16TableZ, 
                                &au16TableV[(cuint16)u8Index*(cuint16)u8SizeZ*(cuint16)u8SizeX*(cuint16)u8SizeY]);
                }

                break;		
            }
        }
    }

    return u16Return;
}


/***************************************************************************************************
  Function   : CTS_u32FirstOrderFilter

  Description: This function is used for slow first-order filter, its filter factor could be very 
               small.

  Arguments  : u32PreValue      - is the previous value.
               u16Input         - is the filter target. 
               u16FilterFactor  - is the filter factor, value = u16FilterFactor / (2^u8FilterShift).
               u8FilterShift    - is the filter value shift count, Value < 16.
  
  Returns    : The 32-bit output after the filter
***************************************************************************************************/

cuint32 CTS_u32FirstOrderFilter(cuint32 u32PreValue, cuint16 u16Input, cuint16 u16FilterFactor, cuint8 u8FilterShift)
{
    cuint32 u32Output;
    cuint32 u32Remainder;
    cuint32 u32FilterBase;

    u32FilterBase = ((cuint32)0x00000001)<<u8FilterShift;

    u32Remainder = u32PreValue % u32FilterBase;
    u32Output = (u32PreValue>>u8FilterShift) * u16FilterFactor;
    u32Output += (u32Remainder*u16FilterFactor)>>u8FilterShift;
    u32Output = (u32PreValue+((cuint32)u16Input*(cuint32)u16FilterFactor)) - u32Output;
    
    return u32Output;
}


/***************************************************************************************************
  Function   : CTS_u8ReadConstArray

  Description: This function is used to read the const array.

  Arguments  : au8Array     - is the 8-bit unsigned const array to read.
               u8Size       - is the size of the array.
               u8Index      - is the index of array which needed to be read. 
  
  Returns    : The value of the array.
***************************************************************************************************/

cuint8 CTS_u8ReadConstArray(const cuint8 au8Array[], cuint8 u8Size, cuint8 u8Index)
{
    cuint8 u8Return;
    
    if (u8Index < u8Size)
    {
        u8Return = au8Array[u8Index];  
    }
    else
    {
        u8Return = au8Array[u8Size-1U];
    }

    return u8Return;
}


/***************************************************************************************************
  Function   : CTS_u16ReadConstArray

  Description: This function is used to read the const array.

  Arguments  : au16Array    - is the 16-bit unsigned const array to read.
               u8Size       - is the size of the array.
               u8Index      - is the index of array which needed to be read. 
  
  Returns    : The value of the array.
***************************************************************************************************/

cuint16 CTS_u16ReadConstArray(const cuint16 au16Array[], cuint8 u8Size, cuint8 u8Index)
{
    cuint16 u16Return;
    
    if (u8Index < u8Size)
    {
        u16Return = au16Array[u8Index];
    }
    else
    {
        u16Return = au16Array[u8Size-1U];
    }

    return u16Return;
}


/***************************************************************************************************
  EOF: CTS_Alg.c
***************************************************************************************************/
