#include"Port.h"


const Port_ConfigType Port_Config[ACTIVATE_CHANNELS]=
{
	/* pinId       portId     pinDir     pinMode     portMux    currentStrength     internalAttach */
	{  PIN_0      ,PORT_A      ,IN        ,UART       ,0x2         ,PIN_2mA           ,PULLUP     },
	{  PIN_5      ,PORT_B      ,OUT       ,SSI        ,0x5         ,PIN_2mA           ,PULLDOWN   }
	
};

const Port_ConfigType *PortConfigPtr = Port_Config;