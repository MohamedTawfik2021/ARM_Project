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

#include"GptCtrl.h"
#include"GptCtrl_cfg.h"
#include"Mem_Map.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/
volatile static uint32 TimerBase;

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
extern const Gpt_ConfigType *ConfigPtr;
extern void (*p)(void);
/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
void GPT_GetTimerBase(Gpt_ChannelType channel);
void TIMER0A_Handler(); 
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

/******************************************************************************
* \Syntax          : void TIMER0A_Handler()      
* \Description     : Timer0A_Hanler                                 
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None
*                                                                     
*******************************************************************************/
void TIMER0A_Handler()
{
    GPTMICR |=(0x1); 
	  (*p)();
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
{  
	 uint8 channel,chMode;
   uint32 ticksfreq ,maxTicks;
 //uint32*callPtr;

   for(uint8 i=0; i<GPT_REQUEST; i++ )
    {
       channel   = ConfigPtr[i].channelId;
       ticksfreq = ConfigPtr[i].ticksFreq;
       maxTicks  = ConfigPtr[i].maxTicksValue;
       chMode    = ConfigPtr[i].channelMode;
    // callPtr   = ConfigPtr[i].CallFnPtr;

    
/*Set The Timer Base Address*/
       GPT_GetTimerBase(channel);                              
    
/*Pre-Configurate Timers*/
       GPTMCTL &= (0xFFFF9080);
       GPTMCFG =  (0x00000000);

/* Confiure 16-bit TimerA Mode*/
       if ((channel % 2) == 0 && channel <12)   
        {   if(chMode == ONESHOT)
               {GPTMTAMR |= (0x1);}
            else 
               {GPTMTAMR |= (0x2);}

            GPTMCFG =  (0x4);
            GPTMTAMR &= ~(1<<4); //CountDown  
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
            GPTMTAMR &= ~(1<<4); //CountDown 
            GPTMTBILR |= ticksfreq; 
        }
        
       
/* Confiure 32-bit Timer Mode*/
    else 
        {       
            if(chMode == ONESHOT)
               {GPTMTAMR |= (0x1);}
            else 
               {GPTMTAMR |= (0x2);}

            GPTMCFG =  (0x0);
            GPTMTAMR &= ~(1<<4); //CountDown  
            GPTMTAILR |= ticksfreq;
	    	}
         
	   }

return E_OK;
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
           if ((channel % 2) == 0 && channel <12)
               { /*16-bit mode Timer A Enable*/

                   GPTMTAILR = targetTime;
                   GPTMCTL  |= 0x1;
               }
            else if ((channel % 2) == 1 && channel <12)
                 /*16-bit mode Timer B Enable*/
               {
                   GPTMTBILR = targetTime;
                   GPTMCTL  |= (1<<8);
               }   
       
                /* 32-bit mode Timer Enable*/
            else 
               {   GPTMTAILR = targetTime;
                   GPTMCTL  |= 0x1;
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
             {   GPTMCTL &=~(1);    }
               
      else if ((channel % 2) == 1 && channel <12)
            /*16-bit mode Timer B Enable*/
             {   GPTMCTL &=~(1<<8); }

      else 
            /*32-bit mode Timer Enable*/
             {   GPTMCTL &=~(1);    }   

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
          {  GPTMIMR |= (1); }
               
      else if ((channel % 2) == 1 && channel <12)
        /*16-bit mode Timer B Interrupt Enable*/
          {  GPTMIMR |= (1<<8); }

      else 
        /*32-bit mode Timer Interrupt Enable*/
          {  GPTMIMR |= (1); }  

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
          {  GPTMIMR &= ~(1); }
               
      else if ((channel % 2) == 1 && channel <12)
        /*16-bit mode Timer B Interrupt Disable*/
          {  GPTMIMR &= ~(1); }

      else 
        /*32-bit mode Timer Interrupt Disable*/
          {  GPTMIMR &= ~(1); }  

}



/**********************************************************************************************************************
 *  END OF FILE: GptCtrl.c
 *********************************************************************************************************************/
