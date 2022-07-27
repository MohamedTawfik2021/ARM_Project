/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  FileName.c
 *        \brief  
 *
 *      \details  
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "Mem_Map.h"
#include "Port.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/
volatile uint32 PortBase;

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
void GetPortBase(Port_Type Port);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/******************************************************************************
* \Syntax          : void GetPortBase(Port_Type Port)      
* \Description     : Get the Port Base Address                                
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : port :  MCU Port                   
* \Parameters (out): None                                                      
* \Return value:   : None                                 
*******************************************************************************/
void GetPortBase(Port_Type Port)
{
    if(Port == PORT_A )
        {  PortBase = GPIO_PORT_A_APB ; }
    else if(Port == PORT_B )
        {  PortBase = GPIO_PORT_B_APB ; }
    else if(Port == PORT_C )
        {  PortBase = GPIO_PORT_C_APB ; }
    else if(Port == PORT_D )
        {  PortBase = GPIO_PORT_D_APB ; } 
    else if(Port == PORT_E )
        {  PortBase = GPIO_PORT_E_APB ; }  
    else if(Port == PORT_F )
        {  PortBase = GPIO_PORT_F_APB ; }  
      
}
/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/


/******************************************************************************
* \Syntax          : void Port_Init ( const Port_ConfigType* ConfigPtr )        
* \Description     : Initializes the Port Driver module.                                   
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : ConfigPtr  :  Pointer to configuration set.                     
* \Parameters (out): None                                                      
* \Return value:   : None  
*                                                                      
*******************************************************************************/
void Port_Init ( const Port_ConfigType* ConfigPtr )
{
	Port_PinType                Pin;
	Port_Type                   Port;
	Port_PinDirectionType       PinDir;
	Port_PinModeType            PinMode;
	uint8                       PortMux;
	Port_PinOutputCurrentType   CurrentStrength;
	Port_PinInternalAttachType  InternalAttach;
	
	
	for(uint8 i=0;i< ACTIVATE_CHANNELS;i++)
	{
		Pin               = ConfigPtr[i].pinId;
		Port              = ConfigPtr[i].portId;
		PinDir            = ConfigPtr[i].pinDir;
		PinMode           = ConfigPtr[i].pinMode;
		PortMux           = ConfigPtr[i].portMux;
		CurrentStrength   = ConfigPtr[i].currentStrength;
		InternalAttach    = ConfigPtr[i].internalAttach;

		GetPortBase(Port);
		GPIOLOCK  = UNLOCK_KEY;
        GPIOCR   |= (1<<Pin);
		GPIOAFSEL|= (1<<Pin);
		GPIOPCTL |= (PortMux<<(Pin*4));

        switch (PinDir)
		{
		case IN:
			GPIODIR &= (0<<Pin); 
			break;
		case OUT:
			GPIODIR |= (1<<Pin); 
			break;
		}
         
		 switch (CurrentStrength)
		{
		case PIN_2mA:
		    GPIODR2R |= (1<<Pin); 
			break;
		case PIN_4mA:
			GPIODR4R |= (1<<Pin); 
			break;
		case PIN_8mA:
			GPIODR4R |= (1<<Pin); 
			break;	
		}

		switch (InternalAttach)
		{
		case PULLUP:
			GPIOPUR |= (1<<Pin);
			break;
		case PULLDOWN:
			GPIOPDR |= (1<<Pin);
			break;
		case OPENDRAIN:
			GPIOODR |= (1<<Pin);
			break;	
		default:
			break;
		}
		
		
	}
	
	
}

/**********************************************************************************************************************
 *  END OF FILE: Port.c
 *********************************************************************************************************************/
