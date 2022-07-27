#include"GptCtrl.h"

const Gpt_ConfigType GptconfigArray [GPT_REQUEST] =
{
/* Channel_Id           Ticks_Freq           MaxTicks_Value           Channel_Mode           CallFnPtr */

 { TIMER_A0_16BIT,         100,                   500,                 CONTINOUS,                        },
 { TIMER_A1_16BIT,         150,                   300,                  ONESHOT,                         },

 

};

extern const uint32* ConfigPtr = GptconfigArray;