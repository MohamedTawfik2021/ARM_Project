#include"GptCtrl.h"
#include"GptCtrl_cfg.h"

const Gpt_ConfigType GptconfigArray[GPT_REQUEST] =
{
/* Channel_Id             Ticks_Freq               MaxTicks_Value               Channel_Mode           CallFnPtr */

   { TIMER_0_32BIT,         50000,                     20000000,                 CONTINOUS                       }
// { TIMER_A1_16BIT,         150,                       300,                     ONESHOT                         },

 
};

const Gpt_ConfigType *ConfigPtr = GptconfigArray;

/*_____________Please Pre-define The Timer Types____________________*/

 //      Gpt_Predef_TimerType Predef[3] =                 /*ENABLE / DISABLE*/
       
 //  {  /* GPT_PREDEF_TIMER_1US_16BIT   */                    ENABLE, 
 //     /* GPT_PREDEF_TIMER_1US_24BIT   */                    ENABLE,
 //     /* GPT_PREDEF_TIMER_1US_32BIT   */                    ENABLE,
 //     /* GPT_PREDEF_TIMER_100US_32BIT */                    DISABE
   
 //   };
	 
	 
	 
