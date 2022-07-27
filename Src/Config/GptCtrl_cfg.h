#ifndef GPTCTRL_CFG
#define GPTCTRL_CFG

#include "GptCtrl.h"



/*_____________Please Pre-define The Timer Types____________________*/

       Gpt_Predef_TimerType Predef =                 /*ENABLE / DISABLE*/
       
   {  /* GPT_PREDEF_TIMER_1US_16BIT   */                    ENABLE, 
      /* GPT_PREDEF_TIMER_1US_24BIT   */                    ENABLE,
      /* GPT_PREDEF_TIMER_1US_32BIT   */                    ENABLE,
      /* GPT_PREDEF_TIMER_100US_32BIT */                    DISABE
   
   };


#define GPT_REQUEST                        2
  
#endif
 


