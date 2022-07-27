#include "IntCtrl.h"

const IntCtrl_CfgType intArray [INT_REQUEST] = 
{
/* Interrupt_Number	          Group_Priority          SubGroup_Priority */
 { NVIC_GPIO_PORT_B,               2,                       1                  },
 { NVIC_16_32_TIMER_5_B,           3,                       1                  }
 	
};
