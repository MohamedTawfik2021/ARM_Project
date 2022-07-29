/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  GptCtrl.h
 *       Module:  GptCtrl
 *
 *  Description:  Configuration of General Purpose Timer   
 *  
 *********************************************************************************************************************/
#ifndef GPTCTRL_H
#define GPTCTRL_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include"Std_Types.h"


/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

typedef struct  Gpt_Predef_Timer
{
     uint8 GPT_PREDEF_TIMER_1US_16BIT   :1;
     uint8 GPT_PREDEF_TIMER_1US_24BIT   :1;
     uint8 GPT_PREDEF_TIMER_1US_32BIT   :1;
     uint8 GPT_PREDEF_TIMER_100US_32BIT :1;

}Gpt_Predef_TimerType;


typedef enum Gpt_Channel
{
    TIMER_A0_16BIT,
    TIMER_B0_16BIT,
    TIMER_A1_16BIT,
    TIMER_B1_16BIT,
    TIMER_A2_16BIT,
    TIMER_B2_16BIT,
    TIMER_A3_16BIT,
    TIMER_B3_16BIT,
    TIMER_A4_16BIT,
    TIMER_B4_16BIT,
    TIMER_A5_16BIT,
    TIMER_B5_16BIT,
    TIMER_0_32BIT,
    TIMER_1_32BIT,
    TIMER_2_32BIT,
    TIMER_3_32BIT,
    TIMER_4_32BIT,
    TIMER_5_32BIT,
   
} Gpt_ChannelType;



typedef enum Gpt_Mode
{ 
    ONESHOT,
    CONTINOUS

} Gpt_ModeType;

typedef enum Gpt_Enable
{ 
    DISABE,
    ENABLE

} Gpt_EnableType;

typedef enum Std_Return
{
    E_NOK,
    E_OK

}Std_ReturnType;

typedef uint32 Gpt_ValueType;

typedef struct Gpt_Config
{ 
    Gpt_ChannelType channelId ;
    Gpt_ValueType ticksFreq ;
    Gpt_ValueType maxTicksValue ;
    Gpt_ModeType channelMode;
   // uint32* CallFnPtr;

} Gpt_ConfigType;


/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/


 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

Std_ReturnType Gpt_Init(const Gpt_ConfigType* ConfigPtr);
void Gpt_StartTimer(Gpt_ChannelType channel ,Gpt_ValueType target_Time);
void Gpt_StopTimer(Gpt_ChannelType channel );


void Gpt_Notification_Timer0();
void Gpt_Notification_Timer1();
void Gpt_Notification_Timer2();
void Gpt_Notification_Timer3();
void Gpt_Notification_Timer4();
void Gpt_Notification_Timer5();

void Gpt_EnableNotification(Gpt_ChannelType channel);
void Gpt_DisableNotification(Gpt_ChannelType channel);


Gpt_ValueType Gpt_GetTimeElapsed(Gpt_ChannelType channel);
Gpt_ValueType Gpt_GetTimeRemainig(Gpt_ChannelType channel);

#endif  /* GPTCTRL_H */

/**********************************************************************************************************************
 *  END OF FILE: GptCtrl.h
 *********************************************************************************************************************/
