/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Mem_Map.h
 *       Module:  
 *
 *  Description:  header file for memory map     
 *  
 *********************************************************************************************************************/
#ifndef MEM_MAP_H_
#define MEM_MAP_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/*______Nested Vectored Interrupt Controller (NVIC) Registers_______*/

#define EN0                    (*(volatile uint32*)(0xE000E000+0x100) )
#define EN1                    (*(volatile uint32*)(0xE000E000+0x104) )
#define EN2                    (*(volatile uint32*)(0xE000E000+0x108) )
#define EN3                    (*(volatile uint32*)(0xE000E000+0x10C) )
#define EN4                    (*(volatile uint32*)(0xE000E000+0x110) )

#define PRI0                   (*(volatile uint32*)(0xE000E000+0x400) )
#define PRI1                   (*(volatile uint32*)(0xE000E000+0x404) )
#define PRI2                   (*(volatile uint32*)(0xE000E000+0x408) )
#define PRI3                   (*(volatile uint32*)(0xE000E000+0x40C) )
#define PRI4                   (*(volatile uint32*)(0xE000E000+0x410) )
#define PRI5                   (*(volatile uint32*)(0xE000E000+0x414) )
#define PRI6                   (*(volatile uint32*)(0xE000E000+0x418) )
#define PRI7                   (*(volatile uint32*)(0xE000E000+0x41C) )
#define PRI8                   (*(volatile uint32*)(0xE000E000+0x420) )
#define PRI9                   (*(volatile uint32*)(0xE000E000+0x424) )
#define PRI10                  (*(volatile uint32*)(0xE000E000+0x428) )
#define PRI11                  (*(volatile uint32*)(0xE000E000+0x42C) )
#define PRI12                  (*(volatile uint32*)(0xE000E000+0x430) )
#define PRI13                  (*(volatile uint32*)(0xE000E000+0x434) )
#define PRI14                  (*(volatile uint32*)(0xE000E000+0x438) )
#define PRI15                  (*(volatile uint32*)(0xE000E000+0x43C) )
#define PRI16                  (*(volatile uint32*)(0xE000E000+0x440) )
#define PRI17                  (*(volatile uint32*)(0xE000E000+0x444) )
#define PRI18                  (*(volatile uint32*)(0xE000E000+0x448) )
#define PRI19                  (*(volatile uint32*)(0xE000E000+0x44C) )
#define PRI20                  (*(volatile uint32*)(0xE000E000+0x450) )
#define PRI21                  (*(volatile uint32*)(0xE000E000+0x454) )
#define PRI22                  (*(volatile uint32*)(0xE000E000+0x458) )
#define PRI23                  (*(volatile uint32*)(0xE000E000+0x45C) )
#define PRI24                  (*(volatile uint32*)(0xE000E000+0x460) )
#define PRI25                  (*(volatile uint32*)(0xE000E000+0x464) )
#define PRI26                  (*(volatile uint32*)(0xE000E000+0x468) )
#define PRI27                  (*(volatile uint32*)(0xE000E000+0x46C) )
#define PRI28                  (*(volatile uint32*)(0xE000E000+0x470) )
#define PRI29                  (*(volatile uint32*)(0xE000E000+0x474) )
#define PRI30                  (*(volatile uint32*)(0xE000E000+0x478) )
#define PRI31                  (*(volatile uint32*)(0xE000E000+0x47C) )
#define PRI32                  (*(volatile uint32*)(0xE000E000+0x480) )
#define PRI33                  (*(volatile uint32*)(0xE000E000+0x484) )
#define PRI34                  (*(volatile uint32*)(0xE000E000+0x488) )

#define SWTRIG                 (*(volatile uint32*)(0xE000E000+0xF00) )


/*________________System Control Block (SCB) Registers_______________*/

#define INTCTRL                (*(volatile uint32*)(0xE000E000+0xD04) )
#define VTABLE                 (*(volatile uint32*)(0xE000E000+0xD08) )
#define APINT                  (*(volatile uint32*)(0xE000E000+0xD0C) )

#define SYSPRI1                (*(volatile uint32*)(0xE000E000+0xD18) )
#define SYSPRI2                (*(volatile uint32*)(0xE000E000+0xD1C) )
#define SYSPRI3                (*(volatile uint32*)(0xE000E000+0xD20) )

#define SYSHNDCTRL             (*(volatile uint32*)(0xE000E000+0xD24) )
#define FAULTSTAT              (*(volatile uint32*)(0xE000E000+0xD28) )
#define HFAULTSTAT             (*(volatile uint32*)(0xE000E000+0xD2C) )


/*________________General Purpose IN/OUT (GPIO) Registers_______________*/

#define GPIO_PORT_A_APB                0x40004000
#define GPIO_PORT_A_AHB                0x40058000

#define GPIO_PORT_B_APB                0x40005000
#define GPIO_PORT_B_AHB                0x40059000

#define GPIO_PORT_C_APB                0x40006000
#define GPIO_PORT_C_AHB                0x4005A000

#define GPIO_PORT_D_APB                0x40007000
#define GPIO_PORT_D_AHB                0x4005B000

#define GPIO_PORT_E_APB                0x40024000
#define GPIO_PORT_E_AHB                0x4005C000

#define GPIO_PORT_F_APB                0x40025000
#define GPIO_PORT_F_AHB                0x4005D000

#define UNLOCK_KEY                     0x4C4F434B

/*The GPIODATA register is virtually mapped to 256 locations in the address space and the
data read from and written to the registers are masked by the eight address lines [9:2]*/

#define GPIODATA_MASK(mask)    (*(volatile uint32*)((PortBase +0x000)+(uint16)mask))
#define GPIODATA               (*(volatile uint32*)(PortBase +0x000) )
/****************************************************************************************/

#define GPIODIR                (*(volatile uint32*)(PortBase +0x400) )
#define GPIOIS                 (*(volatile uint32*)(PortBase +0x404) )
#define GPIOIBE                (*(volatile uint32*)(PortBase +0x408) )
#define GPIOIEV                (*(volatile uint32*)(PortBase +0x40C) )
#define GPIOIM                 (*(volatile uint32*)(PortBase +0x410) )
#define GPIOICR                (*(volatile uint32*)(PortBase +0x41C) )
#define GPIOAFSEL              (*(volatile uint32*)(PortBase +0x420) )
#define GPIODR2R               (*(volatile uint32*)(PortBase +0x500) )
#define GPIODR4R               (*(volatile uint32*)(PortBase +0x504) )
#define GPIODR8R               (*(volatile uint32*)(PortBase +0x508) )
#define GPIOODR                (*(volatile uint32*)(PortBase +0x50C) )
#define GPIOPUR                (*(volatile uint32*)(PortBase +0x510) )
#define GPIOPDR                (*(volatile uint32*)(PortBase +0x514) )
#define GPIODEN                (*(volatile uint32*)(PortBase +0x51C) )
#define GPIOLOCK               (*(volatile uint32*)(PortBase +0x520) )
#define GPIOCR                 (*(volatile uint32*)(PortBase +0x524) )
#define GPIOAMSEL              (*(volatile uint32*)(PortBase +0x528) )
#define GPIOPCTL               (*(volatile uint32*)(PortBase +0x52C) )
#define GPIOADCCTL             (*(volatile uint32*)(PortBase +0x530) )


/*________________General Purpose Timers (GPT) Registers_______________*/

#define TIMER0_BASE_ADDRESS                   0x40030000
#define TIMER1_BASE_ADDRESS                   0x40031000
#define TIMER2_BASE_ADDRESS                   0x40032000
#define TIMER3_BASE_ADDRESS                   0x40033000
#define TIMER4_BASE_ADDRESS                   0x40034000
#define TIMER5_BASE_ADDRESS                   0x40035000


#define GPTMCFG                (*(volatile uint32*)(TimerBase +0x000) )

#define GPTMTAMR               (*(volatile uint32*)(TimerBase +0x004) )
#define GPTMTBMR               (*(volatile uint32*)(TimerBase +0x008) )

#define GPTMCTL                (*(volatile uint32*)(TimerBase +0x00C) )

#define GPTMIMR                (*(volatile uint32*)(TimerBase +0x018) )
#define GPTMICR                (*(volatile uint32*)(TimerBase +0x024) )

#define GPTMTAILR              (*(volatile uint32*)(TimerBase +0x028) )
#define GPTMTBILR              (*(volatile uint32*)(TimerBase +0x02C) )

#define GPTMTAMATCHR           (*(volatile uint32*)(TimerBase +0x030) )
#define GPTMTBMATCHR           (*(volatile uint32*)(TimerBase +0x034) )

#define GPTMTAPR               (*(volatile uint32*)(TimerBase +0x038) )
#define GPTMTBPR               (*(volatile uint32*)(TimerBase +0x03C) )

#define GPTMTAPMR              (*(volatile uint32*)(TimerBase +0x040) )
#define GPTMTBPMR              (*(volatile uint32*)(TimerBase +0x044) )

#define GPTMTAV                (*(volatile uint32*)(TimerBase +0x050) )
#define GPTMTBV                (*(volatile uint32*)(TimerBase +0x054) )

#define GPTMTAPS               (*(volatile uint32*)(TimerBase +0x05C) )
#define GPTMTBPS               (*(volatile uint32*)(TimerBase +0x060) )


/*____________________SRAM Memory Bit-Banding Regions__________________________________________________________________________________________________________________*/

#define BITBAND_SRAM_REF 0x20000000
#define BITBAND_SRAM_BASE 0x22000000

#define BITBAND_PRPH_REF 0x40000000
#define BITBAND_PRPH_BASE 0x42000000


/* addr = address of target byte = (address of register + byteNumber which contain the target bit (0-3))
   bit = target bit number  */

#define SET_BITBAND_PRPH(addr,byte,bit)          (*(volatile uint32*)((BITBAND_SRAM_BASE + ((((uint32) addr) + byte)-BITBAND_SRAM_REF)*32 + (bit*4)))) = 0x1
#define CLR_BITBAND_PRPH(addr,byte,bit)          (*(volatile uint32*)((BITBAND_SRAM_BASE + ((((uint32) addr) + byte)-BITBAND_SRAM_REF)*32 + (bit*4)))) = 0x0
#define SET_BITBAND_SRAM(addr,byte,bit)          (*(volatile uint32*)((BITBAND_PRPH_BASE + ((((uint32) addr) + byte)-BITBAND_PRPH_REF)*32 + (bit*4)))) = 0x1
#define CLR_BITBAND_SRAM(addr,byte,bit)          (*(volatile uint32*)((BITBAND_PRPH_BASE + ((((uint32) addr) + byte)-BITBAND_PRPH_REF)*32 + (bit*4)))) = 0x0







/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/	

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
 
#endif /* MEM_MAP_H_ */

/**********************************************************************************************************************
 *  END OF FILE: Mem_Map.h
 *********************************************************************************************************************/