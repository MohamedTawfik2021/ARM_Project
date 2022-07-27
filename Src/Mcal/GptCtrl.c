/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  GptCtrl.c
 *        \brief  General Purpose Timer Driver

 *      \details  The Driver Configure All 16-bit Gpt (From Gpt0 to Gpt5) 
                  which are divided into two 16-bit timer (A,B) inside each Gpt.
 *                 
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "GptCtrl.h"
#include "Mem_Map.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/
volatile uint32 TimerBase;

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
void GPT_GetTimerBase(Gpt_ChannelType channel);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/******************************************************************************
* \Syntax          : void GPT_GetTimerBase(Gpt_ChannelType channel)       
* \Description     : Get the Timer Base Address                                
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : channel  : Timer channel                     
* \Parameters (out): None                                                      
* \Return value:   : None
*                                                                     
*******************************************************************************/

void GPT_GetTimerBase(Gpt_ChannelType channel)
{
     if(channel == TIMER_A0_16BIT ||channel == TIMER_B0_16BIT ||channel == TIMER_0_32BIT )
                         {  TimerBase = TIMER0_BASE_ADDRESS ; }
       else if(channel ==  TIMER_A1_16BIT ||channel == TIMER_B1_16BIT ||channel == TIMER_1_32BIT)
                         {  TimerBase = TIMER1_BASE_ADDRESS ; }
       else if(channel ==  TIMER_A2_16BIT ||channel == TIMER_B2_16BIT ||channel == TIMER_2_32BIT)
                         {  TimerBase = TIMER2_BASE_ADDRESS ; }
       else if(channel ==  TIMER_A3_16BIT ||channel == TIMER_B3_16BIT ||channel == TIMER_3_32BIT)
                         {  TimerBase = TIMER3_BASE_ADDRESS ; }
       else if(channel ==  TIMER_A4_16BIT ||channel == TIMER_B4_16BIT ||channel == TIMER_4_32BIT)
                         {  TimerBase = TIMER4_BASE_ADDRESS ; }
       else if(channel ==  TIMER_A5_16BIT ||channel == TIMER_B5_16BIT ||channel == TIMER_5_32BIT)
                         {  TimerBase = TIMER5_BASE_ADDRESS ; }     

}
/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/


/******************************************************************************
* \Syntax          : Std_ReturnType Gpt_Init(const Gpt_ConfigType* ConfigPtr)        
* \Description     : GPT Initialization                                   
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : ConfigPtr  : Configuration Pointer                    
* \Parameters (out): None                                                      
* \Return value:   : Std_ReturnType E_OK , E_NOK                                
*******************************************************************************/
Std_ReturnType Gpt_Init(const Gpt_ConfigType* ConfigPtr)
{  uint8 channel,chMode;
   uint32 ticksfreq ,maxTicks;
   uint32*callPtr;

   for(uint8 i=0; i<GPT_REQUEST; i++ )
    {
       channel  = ConfigPtr[i].channelId;
       ticksfreq = ConfigPtr[i].ticksFreq;
       maxTicks  = ConfigPtr[i].maxTicksValue;
       chMode    = ConfigPtr[i].channelMode;
       callPtr   = ConfigPtr[i].CallFnPtr;

    
/*Set The Timer Base Address*/
    GPT_GetTimerBase(channel);                              
    
/*Pre-Configurate Timers*/
    GPTMCTL &= (0xFFFF9080);
    GPTMCFG =  (0x00000000);

    if( maxTicks<= 0xFFFFFF)
    {
/* Confiure 16-bit TimerA Mode*/
       if ((channel % 2) == 0 && channel <12)   
        {   if(chMode == ONESHOT)
               {GPTMTAMR |= (0x1);}
            else 
               {GPTMTAMR |= (0x2);}

            GPTMCFG =  (0x4);
            GPTMTAMR |= (1<<4); //CountUP 
            GPTMTAILR |= ticksfreq;
            GPTMIMR |=(1);     // Time-out interrupt 
        }

    
/* Confiure 16-bit TimerB Mode*/
        else if ((channel % 2) == 1 && channel <12)
        {     
            if(chMode == ONESHOT)
               {GPTMTBMR |= (0x1);}
            else 
               {GPTMTBMR |= (0x2);}

            GPTMCFG =  (0x4);
            GPTMTAMR |= (1<<4); //CountUP 
            GPTMTBILR |= ticksfreq; 
        }
        return E_OK;
    }   
/* Confiure 32-bit Timer Mode*/
    else if (maxTicks >0xFFFFFF && maxTicks <=0xFFFFFFFF)
    {       
            if(chMode == ONESHOT)
               {GPTMTAMR |= (0x1);}
            else 
               {GPTMTAMR |= (0x2);}

            GPTMCFG =  (0x0);
            GPTMTAMR |= (1<<4); //CountUP 
            GPTMTAILR |= ticksfreq;

        return E_OK;    
    }

    else return E_NOK;

 }


}

	
	
/******************************************************************************
* \Syntax          : void Gpt_StartTimer (Gpt_ChannelType channel ,Gpt_ValueType targetTime)        
* \Description     : Start the timer counts                                  
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : channel : Timer Channel , targetTime : Loaded Value                    
* \Parameters (out): None                                                      
* \Return value:   : None
*                                                                     
*******************************************************************************/

void Gpt_StartTimer (Gpt_ChannelType channel ,Gpt_ValueType targetTime) 
{

       GPT_GetTimerBase(channel);
       
       if( targetTime<= 0xFFFFFF)
       {   if ((channel % 2) == 0 && channel <12)
               { /*16-bit mode Timer A Enable*/

                   GPTMTAILR = targetTime;
                   SET_BITBAND_PRPH(&GPTMCTL,0,0);
               }
            else if ((channel % 2) == 1 && channel <12)
                 /*16-bit mode Timer B Enable*/
               {
                   GPTMTBILR = targetTime;
                   SET_BITBAND_PRPH(&GPTMCTL,1,0);
               }   
       }
                /* 32-bit mode Timer Enable*/
       else if (targetTime >0xFFFFFF && targetTime <=0xFFFFFFFF)
       {
                   GPTMTAILR = targetTime;
                   SET_BITBAND_PRPH(&GPTMCTL,0,0);

       }

}

/******************************************************************************
* \Syntax          : void Gpt_StopTimer (Gpt_ChannelType channel)       
* \Description     : Stop timers before complete the period count                                   
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : channel : Timer Channel                    
* \Parameters (out): None                                                      
* \Return value:   : None
*                                                                     
*******************************************************************************/
void Gpt_StopTimer (Gpt_ChannelType channel) 
{
      GPT_GetTimerBase(channel);
       
      if ((channel % 2) == 0 && channel <12)
            /*16-bit mode Timer A Enable*/
          {  CLR_BITBAND_PRPH(&GPTMCTL,0,0); }
               
      else if ((channel % 2) == 1 && channel <12)
            /*16-bit mode Timer B Enable*/
          {  CLR_BITBAND_PRPH(&GPTMCTL,1,0); }

      else 
            /*32-bit mode Timer Enable*/
          {  CLR_BITBAND_PRPH(&GPTMCTL,0,0); }   

}


/******************************************************************************
* \Syntax          : void Gpt_EnableNotification(Gpt_ChannelType channel)        
* \Description     : Enable Timer Interrupts                                
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : channel : Timer Channel                     
* \Parameters (out): None                                                      
* \Return value:   : None
*                                                                     
*******************************************************************************/

void Gpt_EnableNotification(Gpt_ChannelType channel)
{
      GPT_GetTimerBase(channel);
       
      if ((channel % 2) == 0 && channel <12)
        /*16-bit mode Timer A Interrupt Enable*/
          {  SET_BITBAND_PRPH(&GPTMIMR,0,0); }
               
      else if ((channel % 2) == 1 && channel <12)
        /*16-bit mode Timer B Interrupt Enable*/
          {  SET_BITBAND_PRPH(&GPTMIMR,1,0); }

      else 
        /*32-bit mode Timer Interrupt Enable*/
          {  SET_BITBAND_PRPH(&GPTMIMR,0,0); }  

}


/******************************************************************************
* \Syntax          : void Gpt_DisableNotification(Gpt_ChannelType channel)        
* \Description     : Disable Timer Interrupts                               
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : channel : Timer Channel                  
* \Parameters (out): None                                                      
* \Return value:   : None
*                                                                     
*******************************************************************************/

void Gpt_DisableNotification(Gpt_ChannelType channel)
{
      GPT_GetTimerBase(channel);
       
      if ((channel % 2) == 0 && channel <12)
        /*16-bit mode Timer A Interrupt Disable*/
          {  CLR_BITBAND_PRPH(&GPTMIMR,0,0); }
               
      else if ((channel % 2) == 1 && channel <12)
        /*16-bit mode Timer B Interrupt Disable*/
          {  CLR_BITBAND_PRPH(&GPTMIMR,1,0); }

      else 
        /*32-bit mode Timer Interrupt Disable*/
          {  CLR_BITBAND_PRPH(&GPTMIMR,0,0); }  

}



/**********************************************************************************************************************
 *  END OF FILE: GptCtrl.c
 *********************************************************************************************************************/
