#include"Std_Types.h"
#include"IntCtrl.h"
#include"GptCtrl.h"
#include"DIO.h"


int main(void)
{  
  	extern const Gpt_ConfigType *ConfigPtr ;
	
	  IntCtrl_Init();
	  Gpt_Init(ConfigPtr);
	  void (*p)(void);
	  p = &Gpt_Notification_Timer0;
	  Gpt_StartTimer(TIMER_0_32BIT,50000);
    while(1);
		
    return 0;
}

void Gpt_Notification_Timer0()
{
   Dio_Flipchannel(PORT_A,PIN_7);
}