/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  IntCtrl.c
 *        \brief  Nested Vector Interrupt Controller Driver
 *
 *      \details  The Driver Configure All MCU interrupts Priority into gorups and subgroups
 *                Enable and Disable Interrupt Gates for Peripherals
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "Std_Types.h"
#include "IntCtrl.h"
#include "Mem_Map.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

#define INT_GROUPING_SYSTEM_XXX    4
#define INT_GROUPING_SYSTEM_XXY    5
#define INT_GROUPING_SYSTEM_XYY    6
#define INT_GROUPING_SYSTEM_YYY    7	

#define APINT_VECTKEY        0x05FA
/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

IntCtrl_IntType intNum;

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/


/******************************************************************************
* \Syntax          : void IntCtrl_Init(void)                                      
* \Description     : initialize Nvic Module Configuration 
*                                                     
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void IntCtrl_Init(void)
{
	
	uint8 priRegNum ,intGroup ,intSubGroup ,intGroupingField ,bitField;
	uint8 enRegNum ,enBit;
	volatile uint32 *priRegOffset ;
	volatile uint32 *enRegOffset ;

	/*___Set Grouping System - SCB_APINT Register___*/
	     APINT =( (APINT_VECTKEY << 16)|(INT_GROUPING_SYSTEM << 8));
	       
	
 for(uint8 i=0; i< INT_REQUEST ;i++)
	{
		intNum = intArray[i].interruptNumber;
		intGroup = intArray[i].groupPriority;
		intSubGroup = intArray[i].subgroupPriority;
		
    /*___Group\Subgroup priority - PRIx Nvic Registers___*/
        priRegNum = (intNum / 4);
		intGroupingField = (intNum % 4);
		priRegOffset = (0xE000E000+0x400)+ priRegNum;

#if   (INT_GROUPING_SYSTEM == INT_GROUPING_SYSTEM_XXX)
	     bitField = intGroup;
#elif (INT_GROUPING_SYSTEM == INT_GROUPING_SYSTEM_XXY) 
         bitField = (intGroup<<1) | (intSubGroup);
#elif (INT_GROUPING_SYSTEM == INT_GROUPING_SYSTEM_XYY) 
         bitField = (locGroup<<2) | (intSubGroup);
#elif (INT_GROUPING_SYSTEM == INT_GROUPING_SYSTEM_YYY) 
         bitField = intSubGroup;
#else
         bitField = 0X0;
    #warning DEFAULT GROUPING SELECTED
#endif 	
		
		switch (intGroupingField)
		{  
			case 0:
			    *priRegOffset |= (bitField<<5); 
				break;
			case 1:
			    *priRegOffset |= (bitField<<13); 
				break;	
            case 2:
			    *priRegOffset |= (bitField<<21); 
				break;
            case 3:
			    *priRegOffset |= (bitField<<29); 
				break;
		}
		
	
    /*___Enable Interrupt - NVIC_ENx Register___*/
	   enRegNum = (intNum / 32);
	   enBit = (intNum % 32);
       enRegOffset = (0xE000E000+0x100)+ enRegNum;
	   *enRegOffset |= (1 << enBit);

	}	
}


/******************************************************************************
* \Syntax          : void IntCtrl_Trigger(intNum)                                      
* \Description     : Trigger any interrupt by software 
*                                                     
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : intNum                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/

void IntCtrl_Trigger(intNum)
{
  SWTRIG |= (intNum);
}

/**********************************************************************************************************************
 *  END OF FILE: IntCtrl.c
 *********************************************************************************************************************/
