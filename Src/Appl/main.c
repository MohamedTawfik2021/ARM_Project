#include "Std_Types.h"
#include "IntCtrl.h"
#include "SysTick.h"
#include "DIO.h"


#define PERIOD    0xFF 
void (*p)(void);


int main(void)
{  
	  IntCtrl_Init();
	  SysTick_Init(PERIOD);
	  p = SysTick_Notification;
    while(1);
		
    return 0;
}


void SysTick_Notification()
{   
   Dio_Flipchannel(PORT_A,PIN_0);		 
}   