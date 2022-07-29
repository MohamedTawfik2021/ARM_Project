/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  DIO.c
 *        \brief  General Purpose DIGITAL in/out Driver
 *
 *      \details  The Driver Configure GPIO as a Digital function only
                  
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include"Std_Types.h"
#include"Mem_Map.h"
#include"DIO.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/
#define MASK_ADDR_PIN0      0x004
#define MASK_ADDR_PIN1      0x008
#define MASK_ADDR_PIN2      0x010
#define MASK_ADDR_PIN3      0x020
#define MASK_ADDR_PIN4      0x040
#define MASK_ADDR_PIN5      0x080
#define MASK_ADDR_PIN6      0x100
#define MASK_ADDR_PIN7      0x200

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/
volatile static uint32 PortBase;
/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
void Dio_GetPortBase(Dio_PortType port);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/
/******************************************************************************
* \Syntax          : void Dio_GetPortBase(Dio_PortType port)       
* \Description     : Get the Port Base Address                                
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : port :  MCU Port                   
* \Parameters (out): None                                                      
* \Return value:   : None                                 
*******************************************************************************/
void Dio_GetPortBase(Dio_PortType port)
{
    if(port == PORT_A )
        {  PortBase = GPIO_PORT_A_APB ; }
    else if(port == PORT_B )
        {  PortBase = GPIO_PORT_B_APB ; }
    else if(port == PORT_C )
        {  PortBase = GPIO_PORT_C_APB ; }
    else if(port == PORT_D )
        {  PortBase = GPIO_PORT_D_APB ; } 
    else if(port == PORT_E )
        {  PortBase = GPIO_PORT_E_APB ; }  
    else if(port == PORT_F )
        {  PortBase = GPIO_PORT_F_APB ; }  
      
}
/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/


/******************************************************************************
* \Syntax          : Dio_LevelType Dio_ReadPin (Dio_PinType pin)       
* \Description     : Read MCU Pin Value                                   
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : pin :  Pin Number                     
* \Parameters (out): None                                                      
* \Return value:   : Dio_LevelType : High/Low
*                                                                     
*******************************************************************************/
Dio_LevelType Dio_ReadPin (Dio_PortType port , Dio_PinType pin)
{
    uint8  pinRead  = 0x0;
    uint16 maskAddr = 0x0;

    Dio_GetPortBase(port);
    GPIOLOCK  = UNLOCK_KEY;
    GPIOCR   |= (1<<pin);
    GPIODEN  |= (1<<pin);
    GPIODIR  &= (0<<pin); 
    maskAddr |= (1<<(pin+2)); 

   return pinRead = GPIODATA_MASK(maskAddr);
    
}

/******************************************************************************
* \Syntax          : void Dio_WritePin (Dio_PinType pin , Dio_LevelType level)      
* \Description     : Write a level to MCU Pin                                  
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : pin :  Pin Number  , level : High/Low                   
* \Parameters (out): None                                                      
* \Return value:   : None
*                                                                     
*******************************************************************************/
void Dio_WritePin (Dio_PortType port ,Dio_PinType pin , Dio_LevelType level)
{
    uint16 maskAddr = 0x0;

    Dio_GetPortBase(port);
    GPIOLOCK  = UNLOCK_KEY;
    GPIOCR   |= (1<<pin);
    GPIODEN  |= (1<<pin);
    GPIODIR  |= (1<<pin); 
    maskAddr |= (1<<(pin+2)); 
    GPIODATA_MASK(maskAddr) = level;

}

/******************************************************************************
* \Syntax          : Dio_LevelType Dio_Flipchannel (Dio_PinType pin)      
* \Description     : Flip MCU Pin Value                                   
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : pin :  Pin Number                     
* \Parameters (out): None                                                      
* \Return value:   : Dio_LevelType : High/Low
*                                                                     
*******************************************************************************/
Dio_LevelType Dio_Flipchannel (Dio_PortType port ,Dio_PinType pin)
{
    uint16 maskAddr = 0x0;
    uint8 level;
    Dio_GetPortBase(port);
    GPIOLOCK  = UNLOCK_KEY;
    GPIOCR   |= (1<<pin);
    GPIODEN  |= (1<<pin);
    GPIODIR  |= (1<<pin); 
    maskAddr |= (1<<(pin+2)); 
    GPIODATA_MASK(maskAddr) = ~ GPIODATA_MASK(maskAddr);
    level  = GPIODATA_MASK(maskAddr);
    level  = ((level>>pin) & (0x1));
    return level;
}

/******************************************************************************
* \Syntax          : Dio_PortLevelType Dio_ReadPort (Dio_PortType port)      
* \Description     : Read MCU Port Value                                   
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : port :  MCU Port                     
* \Parameters (out): None                                                      
* \Return value:   : Dio_PortLevelType : Port Value
*                                                                     
*******************************************************************************/
Dio_PortLevelType Dio_ReadPort (Dio_PortType port)
{
    uint8  portRead  = 0x0;
    
    Dio_GetPortBase(port);
    GPIOLOCK  = UNLOCK_KEY;
    GPIOCR   |= (0xF);
    GPIODEN  |= (0xF);
    GPIODIR  &= (0x0); 
    
   return portRead = GPIODATA ;
}

/******************************************************************************
* \Syntax          : void Dio_WritePort(Dio_PortType port , Dio_PortLevelType level)     
* \Description     : Write a vlue to MCU Port                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : port :  MCU Port                     
* \Parameters (out): None                                                      
* \Return value:   : None
*                                                                     
*******************************************************************************/
void Dio_WritePort(Dio_PortType port , Dio_PortLevelType level)
{
    Dio_GetPortBase(port);
    GPIOLOCK  = UNLOCK_KEY;
    GPIOCR   |= (0xF);
    GPIODEN  |= (0xF);
    GPIODIR  |= (0xF); 
    GPIODATA = level;

}

/**********************************************************************************************************************
 *  END OF FILE: DIO.c
 *********************************************************************************************************************/
