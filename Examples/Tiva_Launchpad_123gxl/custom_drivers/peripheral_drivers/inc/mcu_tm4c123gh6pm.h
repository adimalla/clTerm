/**
 ******************************************************************************
 * @file    custom_tm4c123.hgh6pm, file name will change
 * @author  Aditya Mall.
 * @brief   TM4C123GH6PM Device Peripheral Access Layer Header File.
 *
 *          This file contains:
 *           - Data structures and the address mapping for all peripherals
 *           - peripherals registers declarations and bits definition
 *           - Macros to access peripheral’s registers hardware
 *
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2019 Aditya Mall, Hari Haran Krishnan </center></h2>
 *
 * TODO Add license.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */

#ifndef MAIN_TM4C123GH6PM_H_
#define MAIN_TM4C123GH6PM_H_


/*
 * @brief Standard C Headers
 */
#include <stdint.h>


/*
 * @brief Interrupt Number Definition, Idea taken from ARM header file
 */


typedef enum {

    /* -------------------  Cortex-M4 Processor Exceptions Numbers  ------------------- */

    Reset_IRQn                    = -15,              /*!<   1  Reset Vector, invoked on Power up and warm reset                 */
    HardFault_IRQn                = -13,              /*!<   3  Hard Fault, all classes of Fault                                 */
    SVCall_IRQn                   =  -5,              /*!<  11  System Service Call via SVC instruction                          */
    PendSV_IRQn                   =  -2,              /*!<  14  Pendable request for system service                              */
    SysTick_IRQn                  =  -1,              /*!<  15  System Tick Timer                                                */

    /* -------------------  TM4C123GH6PM Specific Interrupt Numbers  ------------------ */

    GPIOA_IRQn                    =   0,              /*!<   0  GPIOA                                                            */
    GPIOB_IRQn                    =   1,              /*!<   1  GPIOB                                                            */
    GPIOC_IRQn                    =   2,              /*!<   2  GPIOC                                                            */
    GPIOD_IRQn                    =   3,              /*!<   3  GPIOD                                                            */
    GPIOE_IRQn                    =   4,              /*!<   4  GPIOE                                                            */
    UART0_IRQn                    =   5,              /*!<   5  UART0                                                            */
    UART1_IRQn                    =   6,              /*!<   6  UART1                                                            */
    SSI0_IRQn                     =   7,              /*!<   7  SSI0                                                             */
    I2C0_IRQn                     =   8,              /*!<   8  I2C0                                                             */
    PWM0_FAULT_IRQn               =   9,              /*!<   9  PWM0_FAULT                                                       */
    PWM0_0_IRQn                   =  10,              /*!<  10  PWM0_0                                                           */
    PWM0_1_IRQn                   =  11,              /*!<  11  PWM0_1                                                           */
    PWM0_2_IRQn                   =  12,              /*!<  12  PWM0_2                                                           */
    QEI0_IRQn                     =  13,              /*!<  13  QEI0                                                             */
    ADC0SS0_IRQn                  =  14,              /*!<  14  ADC0SS0                                                          */
    ADC0SS1_IRQn                  =  15,              /*!<  15  ADC0SS1                                                          */
    ADC0SS2_IRQn                  =  16,              /*!<  16  ADC0SS2                                                          */
    ADC0SS3_IRQn                  =  17,              /*!<  17  ADC0SS3                                                          */
    WATCHDOG0_IRQn                =  18,              /*!<  18  WATCHDOG0                                                        */
    TIMER0A_IRQn                  =  19,              /*!<  19  TIMER0A                                                          */
    TIMER0B_IRQn                  =  20,              /*!<  20  TIMER0B                                                          */
    TIMER1A_IRQn                  =  21,              /*!<  21  TIMER1A                                                          */
    TIMER1B_IRQn                  =  22,              /*!<  22  TIMER1B                                                          */
    TIMER2A_IRQn                  =  23,              /*!<  23  TIMER2A                                                          */
    TIMER2B_IRQn                  =  24,              /*!<  24  TIMER2B                                                          */
    COMP0_IRQn                    =  25,              /*!<  25  COMP0                                                            */
    COMP1_IRQn                    =  26,              /*!<  26  COMP1                                                            */
    SYSCTL_IRQn                   =  28,              /*!<  28  SYSCTL                                                           */
    FLASH_CTRL_IRQn               =  29,              /*!<  29  FLASH_CTRL                                                       */
    GPIOF_IRQn                    =  30,              /*!<  30  GPIOF                                                            */
    UART2_IRQn                    =  33,              /*!<  33  UART2                                                            */
    SSI1_IRQn                     =  34,              /*!<  34  SSI1                                                             */
    TIMER3A_IRQn                  =  35,              /*!<  35  TIMER3A                                                          */
    TIMER3B_IRQn                  =  36,              /*!<  36  TIMER3B                                                          */
    I2C1_IRQn                     =  37,              /*!<  37  I2C1                                                             */
    QEI1_IRQn                     =  38,              /*!<  38  QEI1                                                             */
    CAN0_IRQn                     =  39,              /*!<  39  CAN0                                                             */
    CAN1_IRQn                     =  40,              /*!<  40  CAN1                                                             */
    HIB_IRQn                      =  43,              /*!<  43  HIB                                                              */
    USB0_IRQn                     =  44,              /*!<  44  USB0                                                             */
    PWM0_3_IRQn                   =  45,              /*!<  45  PWM0_3                                                           */
    UDMA_IRQn                     =  46,              /*!<  46  UDMA                                                             */
    UDMAERR_IRQn                  =  47,              /*!<  47  UDMAERR                                                          */
    ADC1SS0_IRQn                  =  48,              /*!<  48  ADC1SS0                                                          */
    ADC1SS1_IRQn                  =  49,              /*!<  49  ADC1SS1                                                          */
    ADC1SS2_IRQn                  =  50,              /*!<  50  ADC1SS2                                                          */
    ADC1SS3_IRQn                  =  51,              /*!<  51  ADC1SS3                                                          */
    SSI2_IRQn                     =  57,              /*!<  57  SSI2                                                             */
    SSI3_IRQn                     =  58,              /*!<  58  SSI3                                                             */
    UART3_IRQn                    =  59,              /*!<  59  UART3                                                            */
    UART4_IRQn                    =  60,              /*!<  60  UART4                                                            */
    UART5_IRQn                    =  61,              /*!<  61  UART5                                                            */
    UART6_IRQn                    =  62,              /*!<  62  UART6                                                            */
    UART7_IRQn                    =  63,              /*!<  63  UART7                                                            */
    I2C2_IRQn                     =  68,              /*!<  68  I2C2                                                             */
    I2C3_IRQn                     =  69,              /*!<  69  I2C3                                                             */
    TIMER4A_IRQn                  =  70,              /*!<  70  TIMER4A                                                          */
    TIMER4B_IRQn                  =  71,              /*!<  71  TIMER4B                                                          */
    TIMER5A_IRQn                  =  92,              /*!<  92  TIMER5A                                                          */
    TIMER5B_IRQn                  =  93,              /*!<  93  TIMER5B                                                          */
    WTIMER0A_IRQn                 =  94,              /*!<  94  WTIMER0A                                                         */
    WTIMER0B_IRQn                 =  95,              /*!<  95  WTIMER0B                                                         */
    WTIMER1A_IRQn                 =  96,              /*!<  96  WTIMER1A                                                         */
    WTIMER1B_IRQn                 =  97,              /*!<  97  WTIMER1B                                                         */
    WTIMER2A_IRQn                 =  98,              /*!<  98  WTIMER2A                                                         */
    WTIMER2B_IRQn                 =  99,              /*!<  99  WTIMER2B                                                         */
    WTIMER3A_IRQn                 = 100,              /*!< 100  WTIMER3A                                                         */
    WTIMER3B_IRQn                 = 101,              /*!< 101  WTIMER3B                                                         */
    WTIMER4A_IRQn                 = 102,              /*!< 102  WTIMER4A                                                         */
    WTIMER4B_IRQn                 = 103,              /*!< 103  WTIMER4B                                                         */
    WTIMER5A_IRQn                 = 104,              /*!< 104  WTIMER5A                                                         */
    WTIMER5B_IRQn                 = 105,              /*!< 105  WTIMER5B                                                         */
    SYSEXC_IRQn                   = 106,              /*!< 106  SYSEXC                                                           */
    PWM1_0_IRQn                   = 134,              /*!< 134  PWM1_0                                                           */
    PWM1_1_IRQn                   = 135,              /*!< 135  PWM1_1                                                           */
    PWM1_2_IRQn                   = 136,              /*!< 136  PWM1_2                                                           */
    PWM1_3_IRQn                   = 137,              /*!< 137  PWM1_3                                                           */
    PWM1_FAULT_IRQn               = 138               /*!< 138  PWM1_FAULT                                                       */

} IRQ_NUMBER_T;


/*
 * @brief IO definitions (access restrictions to peripheral registers), idea taken from ARM header file
 */
#define __I       volatile const       /*!< Defines 'read only' permissions    */
#define __O       volatile             /*!< Defines 'write only' permissions   */
#define __IO      volatile             /*!< Defines 'read / write' permissions */


/*
 * @brief Generic Bit Macro Definitions
 */
#define SET       1
#define RESET     0
#define ENABLE    SET
#define DISABLE   RESET
#define EN        ENABLE
#define DS        DISABLE



/***************************************************************************/
/*                                                                         */
/*                       Device Memory Map                                 */
/*                                                                         */
/***************************************************************************/



/*
 * @brief Base Addresses of Flash and SRAM memory
 */
#define FLASH_BASEADDR           0x00000000UL  /*!< FLASH (up to 256 KB) base address in the alias region */
#define SRAM_BASEADDR            0x20000000UL  /*!< SRAM (32 KB) base address in the alias region         */
#define SRAM_BB_BASEADDR         0x22000000UL  /*!< SRAM (32 KB) base address in the bit-band region      */


/*
 * @brief Peripheral Bus Base Addresses
 */
#define PERIPH_BASEADDR          0x40000000UL                      /*!< Peripheral base address in the alias region         */
#define PERIPH_BB_BASEADDR       (PERIPH_BASEADDR + 0x02000000UL)  /*!< Bit-banded alias of 0x4000.0000 through 0x400F.FFFF */
#define APBPERIPH_BASEADDR       PERIPH_BASEADDR                   /*!< Base address of Advanced Peripheral Bus             */
#define AHBPERIPH_BASEADDR       (PERIPH_BASEADDR + 0x00050000UL)  /*!< Base address of Advanced High Performance Bus       */


/*
 * @brief APB Peripherals Base Addresses
 * TODO add other peripherals
 */
#define WATCHDOG0_BASEADDR       (APBPERIPH_BASEADDR + 0x0000UL)      /*!< Base address of Watchdog timer 0        */
#define WATCHDOG1_BASEADDR       (APBPERIPH_BASEADDR + 0x1000UL)      /*!< Base address of Watchdog timer 1        */

#define GPIOA_BASEADDR           (APBPERIPH_BASEADDR + 0x4000UL)      /*!< Base address of GPIO Port A             */
#define GPIOB_BASEADDR           (APBPERIPH_BASEADDR + 0x5000UL)      /*!< Base address of GPIO Port B             */
#define GPIOC_BASEADDR           (APBPERIPH_BASEADDR + 0x6000UL)      /*!< Base address of GPIO Port C             */
#define GPIOD_BASEADDR           (APBPERIPH_BASEADDR + 0x7000UL)      /*!< Base address of GPIO Port D             */
#define GPIOE_BASEADDR           (APBPERIPH_BASEADDR + 0x00024000UL)  /*!< Base address of GPIO Port E             */
#define GPIOF_BASEADDR           (APBPERIPH_BASEADDR + 0x00025000UL)  /*!< Base address of GPIO Port F             */

#define SSI0_BASEADDR            (APBPERIPH_BASEADDR + 0x8000UL)      /*!< Base address of SSI0                    */
#define SSI1_BASEADDR            (APBPERIPH_BASEADDR + 0x9000UL)      /*!< Base address of SSI1                    */
#define SSI2_BASEADDR            (APBPERIPH_BASEADDR + 0xA000UL)      /*!< Base address of SSI2                    */
#define SSI3_BASEADDR            (APBPERIPH_BASEADDR + 0xB000UL)      /*!< Base address of SSI3                    */

#define UART0_BASEADDR           (APBPERIPH_BASEADDR + 0xC000UL)      /*!< Base address of UART0                   */
#define UART1_BASEADDR           (APBPERIPH_BASEADDR + 0xD000UL)      /*!< Base address of UART1                   */
#define UART2_BASEADDR           (APBPERIPH_BASEADDR + 0xE000UL)      /*!< Base address of UART2                   */
#define UART3_BASEADDR           (APBPERIPH_BASEADDR + 0xF000UL)      /*!< Base address of UART3                   */
#define UART4_BASEADDR           (APBPERIPH_BASEADDR + 0x00010000UL)  /*!< Base address of UART4                   */
#define UART5_BASEADDR           (APBPERIPH_BASEADDR + 0x00011000UL)  /*!< Base address of UART5                   */
#define UART6_BASEADDR           (APBPERIPH_BASEADDR + 0x00012000UL)  /*!< Base address of UART6                   */
#define UART7_BASEADDR           (APBPERIPH_BASEADDR + 0x00013000UL)  /*!< Base address of UART7                   */

#define I2C0_BASEADDR            (APBPERIPH_BASEADDR + 0x00020000UL)  /*!< Base address of I2C 0                   */
#define I2C1_BASEADDR            (APBPERIPH_BASEADDR + 0x00021000UL)  /*!< Base address of I2C 1                   */
#define I2C2_BASEADDR            (APBPERIPH_BASEADDR + 0x00022000UL)  /*!< Base address of I2C 2                   */
#define I2C3_BASEADDR            (APBPERIPH_BASEADDR + 0x00023000UL)  /*!< Base address of I2C 3                   */

#define SYSCTL_BASEADDR          (APBPERIPH_BASEADDR + 0x000FE000UL)  /*!< Base address of System Control Register */



/*
 * @brief AHB Peripherals Base Addresses
 */
#define USB_BASEADDR             (AHBPERIPH_BASEADDR + 0x0000UL)  /*!< Base address of USB                        */
#define GPIOA_AHB_BASEADDR       (AHBPERIPH_BASEADDR + 0x8000UL)  /*!< Base address of GPIO Port A (AHB aperture) */
#define GPIOB_AHB_BASEADDR       (AHBPERIPH_BASEADDR + 0x9000UL)  /*!< Base address of GPIO Port B (AHB aperture) */
#define GPIOC_AHB_BASEADDR       (AHBPERIPH_BASEADDR + 0xA000UL)  /*!< Base address of GPIO Port C (AHB aperture) */
#define GPIOD_AHB_BASEADDR       (AHBPERIPH_BASEADDR + 0xB000UL)  /*!< Base address of GPIO Port D (AHB aperture) */
#define GPIOE_AHB_BASEADDR       (AHBPERIPH_BASEADDR + 0xC000UL)  /*!< Base address of GPIO Port E (AHB aperture) */
#define GPIOF_AHB_BASEADDR       (AHBPERIPH_BASEADDR + 0xD000UL)  /*!< Base address of GPIO Port F (AHB aperture) */



/*
 * @brief Base Addresses of Core Peripherals
 */
#define COREPERIPH_BASEADDR      0xE000E000UL                      /*!< Processor Core Peripheral base address */
#define SYSTIC_BASEADDR          (COREPERIPH_BASEADDR + 0x0010UL)  /*!< SysTick Base Address                   */
#define NVIC_BASEADDR            (COREPERIPH_BASEADDR + 0x0100UL)  /*!< NVIC Base Address                      */




/***************************************************************************/
/*                                                                         */
/*                 Device Specific Data Structure Section                  */
/*                                                                         */
/***************************************************************************/


/*
 * @brief Cortex M-4 Processor Core Peripheral Register
 */

typedef struct
{
    __IO uint32_t EN0;             /*!< Interrupt 0-31 Set Enable,        Address offset: 0x100 */
    __IO uint32_t EN1;             /*!< Interrupt 32-63 Set Enable,       Address offset: 0x104 */
    __IO uint32_t EN2;             /*!< Interrupt 64-95 Set Enable,       Address offset: 0x108 */
    __IO uint32_t EN3;             /*!< Interrupt 96-127 Set Enable,      Address offset: 0x10C */
    __IO uint32_t EN4;             /*!< Interrupt 128-138 Set Enable,     Address offset: 0x110 */
    __IO uint32_t RESERVED[27];    /*!< RESERVED,                         Address offset: 0x17C */
    __IO uint32_t DISO;            /*!< Interrupt 0-31 Clear Enable,      Address offset: 0x180 */
    __IO uint32_t DIS1;            /*!< Interrupt 32-63 Clear Enable,     Address offset: 0x184 */
    __IO uint32_t DIS2;            /*!< Interrupt 64-95 Clear Enable,     Address offset: 0x188 */
    __IO uint32_t DIS3;            /*!< Interrupt 96-127 Clear Enable,    Address offset: 0x18C */
    __IO uint32_t DIS4;            /*!< Interrupt 128-138 Clear Enable,   Address offset: 0x190 */
    __IO uint32_t RESERVED1[27];   /*!< RESERVED,                         Address offset: 0x1FC */
    __IO uint32_t PENDO;           /*!< Interrupt 0-31 Set Pending,       Address offset: 0x200 */
    __IO uint32_t PEND1;           /*!< Interrupt 32-63 Set Pending,      Address offset: 0x204 */
    __IO uint32_t PEND2;           /*!< Interrupt 64-95 Set Pending,      Address offset: 0x208 */
    __IO uint32_t PEND3;           /*!< Interrupt 96-127 Set Pending,     Address offset: 0x20C */
    __IO uint32_t PEND4;           /*!< Interrupt 128-138 Set Pending,    Address offset: 0x210 */
    __IO uint32_t RESERVED2[27];   /*!< RESERVED,                         Address offset: 0x280 */
    __IO uint32_t UNPENDO;         /*!< Interrupt 0-31 Clear Pending,     Address offset: 0x280 */
    __IO uint32_t UNPEND1;         /*!< Interrupt 32-63 Clear Pending,    Address offset: 0x284 */
    __IO uint32_t UNPEND2;         /*!< Interrupt 64-95 Clear Pending,    Address offset: 0x288 */
    __IO uint32_t UNPEND3;         /*!< Interrupt 96-127 Clear Pending,   Address offset: 0x28C */
    __IO uint32_t UNPEND4;         /*!< Interrupt 128-138 Clear Pending,  Address offset: 0x290 */
    __IO uint32_t RESERVED3[27];   /*!< RESERVED,                         Address offset: 0x2FC */
    __IO uint32_t ACTIVE0;         /*!< Interrupt 0-31 Active Bit,        Address offset: 0x300 */
    __IO uint32_t ACTIVE1;         /*!< Interrupt 32-63 Active Bit,       Address offset: 0x304 */
    __IO uint32_t ACTIVE2;         /*!< Interrupt 64-95 Active Bit,       Address offset: 0x308 */
    __IO uint32_t ACTIVE3;         /*!< Interrupt 96-127 Active Bit,      Address offset: 0x30C */
    __IO uint32_t ACTIVE4;         /*!< Interrupt 128-138 Active Bit,     Address offset: 0x310 */
    __IO uint32_t RESERVED4[59];   /*!< RESERVED,                         Address offset: 0x3FC */
    __IO uint32_t PRIO;            /*!< Interrupt 0-3 Priority,           Address offset: 0x400 */
    __IO uint32_t PRI1;            /*!< Interrupt 4-7 Priority,           Address offset: 0x404 */
    __IO uint32_t PRI2;            /*!< Interrupt 8-11 Priority,          Address offset: 0x408 */
    __IO uint32_t PRI3;            /*!< Interrupt 12-15 Priority,         Address offset: 0x40C */
    __IO uint32_t PRI4;            /*!< Interrupt 16-19 Priority,         Address offset: 0x410 */
    __IO uint32_t PRI5;            /*!< Interrupt 20-23 Priority,         Address offset: 0x414 */
    __IO uint32_t PRI6;            /*!< Interrupt 24-27 Priority,         Address offset: 0x418 */
    __IO uint32_t PRI7;            /*!< Interrupt 28-31 Priority,         Address offset: 0x41C */
    __IO uint32_t PRI8;            /*!< Interrupt 32-35 Priority,         Address offset: 0x420 */
    __IO uint32_t PRI9;            /*!< Interrupt 36-39 Priority,         Address offset: 0x424 */
    __IO uint32_t PRI1O;           /*!< Interrupt 40-43 Priority,         Address offset: 0x428 */
    __IO uint32_t PRI11;           /*!< Interrupt 44-47 Priority,         Address offset: 0x42C */
    __IO uint32_t PRI12;           /*!< Interrupt 48-51 Priority,         Address offset: 0x430 */
    __IO uint32_t PRI13;           /*!< Interrupt 52-55 Priority,         Address offset: 0x434 */
    __IO uint32_t PRI14;           /*!< Interrupt 56-59 Priority,         Address offset: 0x438 */
    __IO uint32_t PRI15;           /*!< Interrupt 60-63 Priority,         Address offset: 0x43C */
    __IO uint32_t PRI16;           /*!< Interrupt 64-67 Priority,         Address offset: 0x440 */
    __IO uint32_t PRI17;           /*!< Interrupt 68-71 Priority,         Address offset: 0x444 */
    __IO uint32_t PRI18;           /*!< Interrupt 72-75 Priority,         Address offset: 0x448 */
    __IO uint32_t PRI19;           /*!< Interrupt 76-79 Priority,         Address offset: 0x44C */
    __IO uint32_t PRI20;           /*!< Interrupt 80-83 Priority,         Address offset: 0x450 */
    __IO uint32_t PRI21;           /*!< Interrupt 84-87 Priority,         Address offset: 0x454 */
    __IO uint32_t PRI22;           /*!< Interrupt 88-91 Priority,         Address offset: 0x458 */
    __IO uint32_t PRI23;           /*!< Interrupt 92-95 Priority,         Address offset: 0x45C */
    __IO uint32_t PRI24;           /*!< Interrupt 96-99 Priority,         Address offset: 0x460 */
    __IO uint32_t PRI25;           /*!< Interrupt 100-103 Priority,       Address offset: 0x464 */
    __IO uint32_t PRI26;           /*!< Interrupt 104-107 Priority,       Address offset: 0x468 */
    __IO uint32_t PRI27;           /*!< Interrupt 108-111 Priority,       Address offset: 0x46C */
    __IO uint32_t PRI28;           /*!< Interrupt 112-115 Priority,       Address offset: 0x470 */
    __IO uint32_t PRI29;           /*!< Interrupt 116-119 Priority,       Address offset: 0x474 */
    __IO uint32_t PRI30;           /*!< Interrupt 120-123 Priority,       Address offset: 0x478 */
    __IO uint32_t PRI31;           /*!< Interrupt 124-127 Priority,       Address offset: 0x47C */
    __IO uint32_t PRI32;           /*!< Interrupt 128-131 Priority,       Address offset: 0x480 */
    __IO uint32_t PRI33;           /*!< Interrupt 132-135 Priority,       Address offset: 0x484 */
    __IO uint32_t PRI34;           /*!< Interrupt 136-138 Priority,       Address offset: 0x488 */
    __IO uint32_t RESERVED5[669];  /*!< RESERVED,                         Address offset: 0xEFC */
    __IO uint32_t SWTRIG;          /*!< Software Trigger Interrupt,       Address offset: 0xF00 */

} NVIC_T;



/*
 * @brief Peripheral Register Structures
 */



/*
 * @brief System Control Register Structure
 */
typedef struct system_control
{
    __IO uint32_t DID0;             /*!< Device Identification 0,                                                           Address offset: 0x000          */
    __IO uint32_t DID1;             /*!< Device Identification 1,                                                           Address offset: 0x004          */
    __I  uint32_t LEGACY[10];       /*!< Legacy Registers,                                                                  Address offset: 0x008 to 0x02C */
    __IO uint32_t PBORCTL;          /*!< Brown-Out Reset Control,                                                           Address offset: 0x030          */
    __I  uint32_t LEGACY2[7];       /*!< Legacy Registers,                                                                  Address offset: 0x034 to 0x04C */
    __IO uint32_t RIS;              /*!< Raw Interrupt Status,                                                              Address offset: 0x050          */
    __IO uint32_t IMC;              /*!< Interrupt Mask Control,                                                            Address offset: 0x054          */
    __IO uint32_t MISC;             /*!< Masked Interrupt Status and Clear,                                                 Address offset: 0x058          */
    __IO uint32_t RESC;             /*!< Reset Cause,                                                                       Address offset: 0x05C          */
    __IO uint32_t RCC;              /*!< Run-Mode Clock Configuration,                                                      Address offset: 0x060          */
    __I  uint32_t RESERVED[2];      /*!< RESERVED,                                                                          Address offset: 0x064 to 0x068 */
    __IO uint32_t GPIOHBCTL;        /*!< GPIO High-Performance Bus Control,                                                 Address offset: 0x06C          */
    __IO uint32_t RCC2;             /*!< Run-Mode Clock Configuration 2,                                                    Address offset: 0x070          */
    __I  uint32_t RESERVED1[2];     /*!< RESERVED,                                                                          Address offset: 0x074 to 0x078 */
    __IO uint32_t MOSCCTL;          /*!< Main Oscillator Control,                                                           Address offset: 0x07C          */
    __I  uint32_t RESERVED2[32];    /*!< RESERVED,                                                                          Address offset: 0x080 to 0x0FC */
    __I  uint32_t LEGACY3[3];       /*!< Legacy Registers,                                                                  Address offset: 0x100 to 0x108 */
    __I  uint32_t RESERVED3;        /*!< RESERVED,                                                                          Address offset: 0x10C          */
    __I  uint32_t LEGACY4[3];       /*!< Legacy Registers,                                                                  Address offset: 0x110 to 0x118 */
    __I  uint32_t RESERVED4;        /*!< RESERVED,                                                                          Address offset: 0x11C          */
    __I  uint32_t LEGACY5[3];       /*!< Legacy Registers,                                                                  Address offset: 0x120 to 0x128 */
    __I  uint32_t RESERVED5[6];     /*!< RESERVED,                                                                          Address offset: 0x12C to 0x140 */
    __IO uint32_t DSLPCLKCFG;       /*!< Deep Sleep Clock Configuration,                                                    Address offset: 0x144          */
    __I  uint32_t RESERVED6;        /*!< RESERVED,                                                                          Address offset: 0x148          */
    __IO uint32_t SYSPROP;          /*!< System Properties,                                                                 Address offset: 0x14C          */
    __IO uint32_t PIOSCCAL;         /*!< Precision Internal Oscillator Calibration,                                         Address offset: 0x150          */
    __IO uint32_t PIOSCSTAT;        /*!< Precision Internal Oscillator Statistics,                                          Address offset: 0x154          */
    __I  uint32_t RESERVED7[2];     /*!< RESERVED,                                                                          Address offset: 0x158 to 0x15C */
    __IO uint32_t PLLFREQ0;         /*!< PLL Frequency 0,                                                                   Address offset: 0x160          */
    __IO uint32_t PLLFREQ1;         /*!< PLL Frequency 1,                                                                   Address offset: 0x164          */
    __IO uint32_t PLLSTAT;          /*!< PLL Status,                                                                        Address offset: 0x168          */
    __I  uint32_t RESERVED8[7];     /*!< RESERVED,                                                                          Address offset: 0x16C to 0x184 */
    __IO uint32_t SLPPWRCFG;        /*!< Sleep Power Configuration,                                                         Address offset: 0x188          */
    __IO uint32_t DSLPPWRCFG;       /*!< Deep-Sleep Power Configuration,                                                    Address offset: 0x18C          */
    __I  uint32_t LEGACY6;          /*!< Legacy Registers,                                                                  Address offset: 0x190          */
    __I  uint32_t RESERVED9[3];     /*!< RESERVED,                                                                          Address offset: 0x194 to 0x19C */
    __I  uint32_t LEGACY7;          /*!< Legacy Registers,                                                                  Address offset: 0x1A0          */
    __I  uint32_t RESERVED10[4];    /*!< RESERVED,                                                                          Address offset: 0x1A4 to 0x1B0 */
    __IO uint32_t LDOSPCTL;         /*!< LDO Sleep Power Control,                                                           Address offset: 0x1B4          */
    __I  uint32_t LDOSPCAL;         /*!< LDO Sleep Power Calibration,                                                       Address offset: 0x1B8          */
    __IO uint32_t LDODPCTL;         /*!< LDO Deep-Sleep Power Control,                                                      Address offset: 0x1BC          */
    __IO uint32_t LDODPCAL;         /*!< LDO Deep-Sleep Power Calibration,                                                  Address offset: 0x1C0          */
    __I  uint32_t RESERVED11[2];    /*!< RESERVED,                                                                          Address offset: 0x1C4 to 0x1C8 */
    __IO uint32_t SDPMST;           /*!< Sleep / Deep-Sleep Power Mode Status,                                              Address offset: 0x1CC          */
    __I  uint32_t RESERVED12[76];   /*!< RESERVED,                                                                          Address offset: 0x1D0 to 0x2FC */
    __IO uint32_t PPWD;             /*!< Watchdog Timer Peripheral Present,                                                 Address offset: 0x300          */
    __IO uint32_t PPTIMER;          /*!< 16/32-Bit General-Purpose Timer Peripheral Present,                                Address offset: 0x304          */
    __IO uint32_t PPGPIO;           /*!< General-Purpose Input/Output Peripheral Present,                                   Address offset: 0x308          */
    __IO uint32_t PPDMA;            /*!< Micro Direct Memory Access Peripheral Present,                                     Address offset: 0x30C          */
    __I  uint32_t RESERVED13;       /*!< RESERVED,                                                                          Address offset: 0x310          */
    __IO uint32_t PPHIB;            /*!< Hibernation Peripheral Present,                                                    Address offset: 0x314          */
    __IO uint32_t PPUART;           /*!< Universal Asynchronous Receiver/Transmitter Peripheral Present,                    Address offset: 0x318          */
    __IO uint32_t PPSSI;            /*!< Synchronous Serial Interface Peripheral Present,                                   Address offset: 0x31C          */
    __IO uint32_t PPI2C;            /*!< Inter-Integrated Circuit Peripheral Present,                                       Address offset: 0x320          */
    __I  uint32_t RESERVED14;       /*!< RESERVED,                                                                          Address offset: 0x324          */
    __IO uint32_t PPUSB;            /*!< Universal Serial Bus Peripheral Present,                                           Address offset: 0x328          */
    __I  uint32_t RESERVED15[2];    /*!< RESERVED,                                                                          Address offset: 0x32C to 0x330 */
    __IO uint32_t PPCAN;            /*!< Controller Area Network Peripheral Present,                                        Address offset: 0x334          */
    __IO uint32_t PPADC;            /*!< Analog-to-Digital Converter Peripheral Present,                                    Address offset: 0x338          */
    __IO uint32_t PPACMP;           /*!< Analog Comparator Peripheral Present,                                              Address offset: 0x33C          */
    __IO uint32_t PPPWM;            /*!< Pulse Width Modulator Peripheral Present,                                          Address offset: 0x340          */
    __IO uint32_t PPQEI;            /*!< Quadrature Encoder Interface Peripheral Present,                                   Address offset: 0x344          */
    __I  uint32_t RESERVED16[4];    /*!< RESERVED,                                                                          Address offset: 0x348 to 0x354 */
    __IO uint32_t PPEEPROM;         /*!< EEPROM Peripheral Present,                                                         Address offset: 0x358          */
    __IO uint32_t PPWTIMER;         /*!< 32/64-Bit Wide General-Purpose Timer Peripheral Present,                           Address offset: 0x35C          */
    __I  uint32_t RESERVED17[104];  /*!< RESERVED,                                                                          Address offset: 0x360 to 0x4FC */
    __IO uint32_t SRWD;             /*!< Watchdog Timer Software Reset,                                                     Address offset: 0x500          */
    __IO uint32_t SRTIMER;          /*!< 16/32-Bit General-Purpose Timer Software Reset,                                    Address offset: 0x504          */
    __IO uint32_t SRGPIO;           /*!< General-Purpose Input/Output Software Reset,                                       Address offset: 0x508          */
    __IO uint32_t SRDMA;            /*!< Micro Direct Memory Access Software Reset,                                         Address offset: 0x50C          */
    __I  uint32_t RESERVED18;       /*!< RESERVED,                                                                          Address offset: 0x510          */
    __IO uint32_t SRHIB;            /*!< Hibernation Software Reset,                                                        Address offset: 0x514          */
    __IO uint32_t SRUART;           /*!< Universal Asynchronous Receiver/Transmitter Software Reset,                        Address offset: 0x518          */
    __IO uint32_t SRSSI;            /*!< Synchronous Serial Interface Software Reset,                                       Address offset: 0x51C          */
    __IO uint32_t SRI2C;            /*!< Inter-Integrated Circuit Software Reset,                                           Address offset: 0x520          */
    __I  uint32_t RESERVED19;       /*!< RESERVED,                                                                          Address offset: 0x524          */
    __IO uint32_t SRUSB;            /*!< Universal Serial Bus Software Reset,                                               Address offset: 0x528          */
    __I  uint32_t RESERVED20[2];    /*!< RESERVED,                                                                          Address offset: 0x52C to 0x530 */
    __IO uint32_t SRCAN;            /*!< Controller Area Network Software Reset,                                            Address offset: 0x534          */
    __IO uint32_t SRADC;            /*!< Analog-to-Digital Converter Software Reset,                                        Address offset: 0x538          */
    __IO uint32_t SRACMP;           /*!< Analog Comparator Software Reset,                                                  Address offset: 0x53C          */
    __IO uint32_t SRPWM;            /*!< Pulse Width Modulator Software Reset,                                              Address offset: 0x540          */
    __IO uint32_t SRQEI;            /*!< Quadrature Encoder Interface Software Reset,                                       Address offset: 0x544          */
    __I  uint32_t RESERVED21[4];    /*!< RESERVED,                                                                          Address offset: 0x548 to 0x554 */
    __IO uint32_t SREEPROM;         /*!< EEPROM Software Reset,                                                             Address offset: 0x558          */
    __IO uint32_t SRWTIMER;         /*!< 32/64-Bit Wide General-Purpose Timer Software Reset,                               Address offset: 0x55C          */
    __I  uint32_t RESERVED22[40];   /*!< RESERVED,                                                                          Address offset: 0x560 to 0x5FC */
    __IO uint32_t RCGCWD;           /*!< Watchdog Timer Run Mode Clock Gating Control,                                      Address offset: 0x600          */
    __IO uint32_t RCGCTIMER;        /*!< 16/32-Bit General-Purpose Timer Run Mode Clock Gating Control,                     Address offset: 0x604          */
    __IO uint32_t RCGCGPIO;         /*!< General-Purpose Input/Output Run Mode Clock Gating Control,                        Address offset: 0x608          */
    __IO uint32_t RCGCDMA;          /*!< Micro Direct Memory Access Run Mode Clock Gating Control,                          Address offset: 0x60C          */
    __I  uint32_t RESERVED23;       /*!< RESERVED,                                                                          Address offset: 0x610          */
    __IO uint32_t RCGCHIB;          /*!< Hibernation Run Mode Clock Gating Control,                                         Address offset: 0x614          */
    __IO uint32_t RCGCUART;         /*!< Universal Asynchronous Receiver/Transmitter Run Mode Clock Gating Control,         Address offset: 0x618          */
    __IO uint32_t RCGCSSI;          /*!< Synchronous Serial Interface Run Mode Clock Gating Control,                        Address offset: 0x61C          */
    __IO uint32_t RCGCI2C;          /*!< Inter-Integrated Circuit Run Mode Clock Gating Control,                            Address offset: 0x620          */
    __I  uint32_t RESERVED24;       /*!< RESERVED,                                                                          Address offset: 0x624          */
    __IO uint32_t RCGCUSB;          /*!< Universal Serial Bus Run Mode Clock Gating Control,                                Address offset: 0x628          */
    __I  uint32_t RESERVED25[2];    /*!< RESERVED,                                                                          Address offset: 0x62C to 0x630 */
    __IO uint32_t RCGCCAN;          /*!< Controller Area Network Run Mode Clock Gating Control,                             Address offset: 0x634          */
    __IO uint32_t RCGCADC;          /*!< Analog-to-Digital Converter Run Mode Clock Gating Control,                         Address offset: 0x638          */
    __IO uint32_t RCGCACMP;         /*!< Analog Comparator Run Mode Clock Gating Control,                                   Address offset: 0x63C          */
    __IO uint32_t RCGCPWM;          /*!< Pulse Width Modulator Run Mode Clock Gating Control,                               Address offset: 0x640          */
    __IO uint32_t RCGCQEI;          /*!< Quadrature Encoder Interface Run Mode Clock Gating Control,                        Address offset: 0x644          */
    __I  uint32_t RESERVED26[4];    /*!< RESERVED,                                                                          Address offset: 0x648 to 0x654 */
    __IO uint32_t RCGCEEPROM;       /*!< EEPROM Run Mode Clock Gating Control,                                              Address offset: 0x658          */
    __IO uint32_t RCGCWTIMER;       /*!< 32/64-Bit Wide General-Purpose Timer Run Mode Clock Gating Control,                Address offset: 0x65C          */
    __I  uint32_t RESERVED27[40];   /*!< RESERVED,                                                                          Address offset: 0x660 to 0x6FC */
    __IO uint32_t SCGCWD;           /*!< Watchdog Timer Sleep Mode Clock Gating Control,                                    Address offset: 0x700          */
    __IO uint32_t SCGCTIMER;        /*!< 16/32-Bit General-Purpose Timer Sleep Mode Clock Gating Control,                   Address offset: 0x704          */
    __IO uint32_t SCGCGPIO;         /*!< General-Purpose Input/Output Sleep Mode Clock Gating Control,                      Address offset: 0x708          */
    __IO uint32_t SCGCDMA;          /*!< Micro Direct Memory Access Sleep Mode Clock Gating Control,                        Address offset: 0x70C          */
    __I  uint32_t RESERVED28;       /*!< RESERVED,                                                                          Address offset: 0x710          */
    __IO uint32_t SCGCHIB;          /*!< Hibernation Sleep Mode Clock Gating Control,                                       Address offset: 0x714          */
    __IO uint32_t SCGCUART;         /*!< Universal Asynchronous Receiver/Transmitter Sleep Mode Clock Gating Control,       Address offset: 0x718          */
    __IO uint32_t SCGCSSI;          /*!< Synchronous Serial Interface Sleep Mode Clock Gating Control,                      Address offset: 0x71C          */
    __IO uint32_t SCGCI2C;          /*!< Inter-Integrated Circuit Sleep Mode Clock Gating Control,                          Address offset: 0x720          */
    __I  uint32_t RESERVED29;       /*!< RESERVED,                                                                          Address offset: 0x724          */
    __IO uint32_t SCGCUSB;          /*!< Universal Serial Bus Sleep Mode Clock Gating Control,                              Address offset: 0x728          */
    __I  uint32_t RESERVED30[2];    /*!< RESERVED,                                                                          Address offset: 0x72C to 0x730 */
    __IO uint32_t SCGCCAN;          /*!< Controller Area Network Sleep Mode Clock Gating Control,                           Address offset: 0x734          */
    __IO uint32_t SCGCADC;          /*!< Analog-to-Digital Converter Sleep Mode Clock Gating Control,                       Address offset: 0x738          */
    __IO uint32_t SCGCACMP;         /*!< Analog Comparator Sleep Mode Clock Gating Control,                                 Address offset: 0x73C          */
    __IO uint32_t SCGCPWM;          /*!< Pulse Width Modulator Sleep Mode Clock Gating Control,                             Address offset: 0x740          */
    __IO uint32_t SCGCQEI;          /*!< Quadrature Encoder Interface Sleep Mode Clock Gating Control,                      Address offset: 0x744          */
    __I  uint32_t RESERVED31[4];    /*!< RESERVED,                                                                          Address offset: 0x748 to 0x754 */
    __IO uint32_t SCGCEEPROM;       /*!< EEPROM Sleep Mode Clock Gating Control,                                            Address offset: 0x758          */
    __IO uint32_t SCGCWTIMER;       /*!< 32/64-Bit Wide General-Purpose Timer Sleep Mode Clock Gating Control,              Address offset: 0x75C          */
    __I  uint32_t RESERVED32[40];   /*!< RESERVED,                                                                          Address offset: 0x760 to 0x7FC */
    __IO uint32_t DCGCWD;           /*!< Watchdog Timer Deep-Sleep Mode Clock Gating Control,                               Address offset: 0x800          */
    __IO uint32_t DCGCTIMER;        /*!< 16/32-Bit General-Purpose Timer Deep-Sleep Mode Clock Gating Control,              Address offset: 0x804          */
    __IO uint32_t DCGCGPIO;         /*!< General-Purpose Input/Output Deep-Sleep Mode Clock Gating Control,                 Address offset: 0x808          */
    __IO uint32_t DCGCDMA;          /*!< Micro Direct Memory Access Deep-Sleep Mode Clock Gating Control,                   Address offset: 0x80C          */
    __I  uint32_t RESERVED33;       /*!< RESERVED,                                                                          Address offset: 0x810          */
    __IO uint32_t DCGCHIB;          /*!< Hibernation Deep-Sleep Mode Clock Gating Control,                                  Address offset: 0x814          */
    __IO uint32_t DCGCUART;         /*!< Universal Asynchronous Receiver/Transmitter Deep-Sleep Mode Clock Gating Control,  Address offset: 0x818          */
    __IO uint32_t DCGCSSI;          /*!< Synchronous Serial Interface Deep-Sleep Mode Clock Gating Control,                 Address offset: 0x81C          */
    __IO uint32_t DCGCI2C;          /*!< Inter-Integrated Circuit Deep-Sleep Mode Clock Gating Control,                     Address offset: 0x820          */
    __I  uint32_t RESERVED34;       /*!< RESERVED,                                                                          Address offset: 0x824          */
    __IO uint32_t DCGCUSB;          /*!< Universal Serial Bus Deep-Sleep Mode Clock Gating Control,                         Address offset: 0x828          */
    __I  uint32_t RESERVED35[2];    /*!< RESERVED,                                                                          Address offset: 0x82C to 0x230 */
    __IO uint32_t DCGCCAN;          /*!< Controller Area Network Deep-Sleep Mode Clock Gating Control,                      Address offset: 0x834          */
    __IO uint32_t DCGCADC;          /*!< Analog-to-Digital Converter Deep-Sleep Mode Clock Gating Control,                  Address offset: 0x838          */
    __IO uint32_t DCGCACMP;         /*!< Analog Comparator Deep-Sleep Mode Clock Gating Control,                            Address offset: 0x83C          */
    __IO uint32_t DCGCPWM;          /*!< Pulse Width Modulator Deep-Sleep Mode Clock Gating Control,                        Address offset: 0x840          */
    __IO uint32_t DCGCQEI;          /*!< Quadrature Encoder Interface Deep-Sleep Mode Clock Gating Control,                 Address offset: 0x844          */
    __I  uint32_t RESERVED36[4];    /*!< RESERVED,                                                                          Address offset: 0x848 to 0x854 */
    __IO uint32_t DCGCEEPROM;       /*!< EEPROM Deep-Sleep Mode Clock Gating Control,                                       Address offset: 0x858          */
    __IO uint32_t DCGCWTIMER;       /*!< 32/64-Bit Wide General-Purpose Timer Deep-Sleep Mode Clock Gating Control          Address offset: 0x85C          */
    __I  uint32_t RESERVED37[104];  /*!< RESERVED,                                                                          Address offset: 0x860 to 0x9FC */
    __IO uint32_t PRWD;             /*!< Watchdog Timer Peripheral Ready,                                                   Address offset: 0xA00          */
    __IO uint32_t PRTIMER;          /*!< 16/32-Bit General-Purpose Timer Peripheral Ready,                                  Address offset: 0xA04          */
    __IO uint32_t PRGPIO;           /*!< General-Purpose Input/Output Peripheral Ready,                                     Address offset: 0xA08          */
    __IO uint32_t PRDMA;            /*!< Micro Direct Memory Access Peripheral Ready,                                       Address offset: 0xA0C          */
    __I  uint32_t RESERVED38;       /*!< RESERVED,                                                                          Address offset: 0xA10          */
    __IO uint32_t PRHIB;            /*!< Hibernation Peripheral Ready,                                                      Address offset: 0xA14          */
    __IO uint32_t PRUART;           /*!< Universal Asynchronous Receiver/Transmitter Peripheral Ready,                      Address offset: 0xA18          */
    __IO uint32_t PRSSI;            /*!< Synchronous Serial Interface Peripheral Ready,                                     Address offset: 0xA1C          */
    __IO uint32_t PRI2C;            /*!< Inter-Integrated Circuit Peripheral Ready,                                         Address offset: 0xA20          */
    __I  uint32_t RESERVED39;       /*!< RESERVED,                                                                          Address offset: 0xA24          */
    __IO uint32_t PRUSB;            /*!< Universal Serial Bus Peripheral Ready,                                             Address offset: 0xA28          */
    __I  uint32_t RESERVED40[2];    /*!< RESERVED,                                                                          Address offset: 0xA2C to 0x230 */
    __IO uint32_t PRCAN;            /*!< Controller Area Network Peripheral Ready,                                          Address offset: 0xA34          */
    __IO uint32_t PRADC;            /*!< Analog-to-Digital Converter Peripheral Ready,                                      Address offset: 0xA38          */
    __IO uint32_t PRACMP;           /*!< Analog Comparator Peripheral Ready,                                                Address offset: 0xA3C          */
    __IO uint32_t PRPWM;            /*!< Pulse Width Modulator Peripheral Ready,                                            Address offset: 0xA40          */
    __IO uint32_t PRQEI;            /*!< Quadrature Encoder Interface Peripheral Ready,                                     Address offset: 0xA44          */
    __I  uint32_t RESERVED41[4];    /*!< RESERVED,                                                                          Address offset: 0xA48 to 0xA54 */
    __IO uint32_t PREEPROM;         /*!< EEPROM Peripheral Ready,                                                           Address offset: 0xA58          */
    __IO uint32_t PRWTIMER;         /*!< 32/64-Bit Wide General-Purpose Timer Peripheral Ready,                             Address offset: 0xA5C          */

} sysctl_t;



/*
 * @brief System Control Legacy Register Structure
 */
typedef struct system_control_legacy
{
    __I  uint32_t RESERVED[2];    /*!< RESERVED,                                         Address offset: 0x000 to 0x004 */
    __IO uint32_t DC0;            /*!< Device Capabilities 0,                            Address offset: 0x008          */
    __I  uint32_t RESERVED1;      /*!< RESERVED,                                         Address offset: 0x00C          */
    __IO uint32_t DC1;            /*!< Device Capabilities 1,                            Address offset: 0x010          */
    __IO uint32_t DC2;            /*!< Device Capabilities 2,                            Address offset: 0x014          */
    __IO uint32_t DC3;            /*!< Device Capabilities 3,                            Address offset: 0x018          */
    __IO uint32_t DC4;            /*!< Device Capabilities 4,                            Address offset: 0x01C          */
    __IO uint32_t DC5;            /*!< Device Capabilities 5,                            Address offset: 0x020          */
    __IO uint32_t DC6;            /*!< Device Capabilities 6,                            Address offset: 0x024          */
    __IO uint32_t DC7;            /*!< Device Capabilities 7,                            Address offset: 0x028          */
    __IO uint32_t DC8;            /*!< Device Capabilities 8                             Address offset: 0x02C          */
    __I  uint32_t RESERVED2[4];   /*!< RESERVED,                                         Address offset: 0x030 to 0x03C */
    __IO uint32_t SRCR0;          /*!< Software Reset Control 0,                         Address offset: 0x040          */
    __IO uint32_t SRCR1;          /*!< Software Reset Control 1,                         Address offset: 0x044          */
    __IO uint32_t SRCR2;          /*!< Software Reset Control 2,                         Address offset: 0x048          */
    __I  uint32_t RESERVED3[45];  /*!< RESERVED,                                         Address offset: 0x04C to 0x0FC */
    __IO uint32_t RCGC0;          /*!< Run Mode Clock Gating Control Register 0,         Address offset: 0x100          */
    __IO uint32_t RCGC1;          /*!< Run Mode Clock Gating Control Register 1,         Address offset: 0x104          */
    __IO uint32_t RCGC2;          /*!< Run Mode Clock Gating Control Register 2,         Address offset: 0x108          */
    __I  uint32_t RESERVED4;      /*!< RESERVED,                                         Address offset: 0x10C          */
    __IO uint32_t SCGC0;          /*!< Sleep Mode Clock Gating Control Register 0,       Address offset: 0x110          */
    __IO uint32_t SCGC1;          /*!< Sleep Mode Clock Gating Control Register 1,       Address offset: 0x114          */
    __IO uint32_t SCGC2;          /*!< Sleep Mode Clock Gating Control Register 2,       Address offset: 0x118          */
    __I  uint32_t RESERVED5;      /*!< RESERVED,                                         Address offset: 0x11C          */
    __IO uint32_t DCGC0;          /*!< Deep Sleep Mode Clock Gating Control Register 0,  Address offset: 0x120          */
    __IO uint32_t DCGC1;          /*!< Deep-Sleep Mode Clock Gating Control Register 1,  Address offset: 0x124          */
    __IO uint32_t DCGC2;          /*!< Deep Sleep Mode Clock Gating Control Register 2,  Address offset: 0x128          */
    __I  uint32_t RESERVED6[25];  /*!< RESERVED,                                         Address offset: 0x12C to 0x18C */
    __IO uint32_t DC9;            /*!< Device Capabilities 9,                            Address offset: 0x190          */
    __I  uint32_t RESERVED7[3];   /*!< RESERVED,                                         Address offset: 0x194 to 0x19C */
    __IO uint32_t NVMSTAT;        /*!< Non-Volatile Memory Information,                  Address offset: 0x1A0          */

} sysctl_legacy_t;



/*
 * @brief General-Purpose Input/Outputs Register Structure
 * TODO complete Address offsets docs
 */
typedef struct gpio_port
{
    __I  uint32_t BITMASK[255];  /*!< GPIO [9:2] register mask space, see Data Sheet,  Address offset: 0x3FC */
    __IO uint32_t DATA;          /*!< GPIO Data,                                       Address offset: 0x400 */
    __IO uint32_t DIR;           /*!< GPIO Direction,                                  Address offset: 0x404 */
    __IO uint32_t IS;            /*!< GPIO Interrupt Sense,                            Address offset: 0x408 */
    __IO uint32_t IBE;           /*!< GPIO Interrupt Both Edges,                       Address offset: 0x40C */
    __IO uint32_t IEV;           /*!< GPIO Interrupt Event,                            Address offset: 0x410 */
    __IO uint32_t IM;            /*!< GPIO Interrupt Mask,                             Address offset: 0x414 */
    __IO uint32_t RIS;           /*!< GPIO Raw Interrupt Status,                       Address offset: 0x418 */
    __IO uint32_t MIS;           /*!< GPIO Masked Interrupt Status,                    Address offset: 0x41C */
    __O  uint32_t ICR;           /*!< GPIO Interrupt Clear,                            Address offset: 0x420 */
    __IO uint32_t AFSEL;         /*!< GPIO Alternate Function Select,                  Address offset: 0x400 */
    __I  uint32_t RESERVED[55];  /*!< RESERVED,                                        Address offset: 0x000 */
    __IO uint32_t DR2R;          /*!< GPIO 2-mA Drive Select,                          Address offset: 0x000 */
    __IO uint32_t DR4R;          /*!< GPIO 4-mA Drive Select,                          Address offset: 0x000 */
    __IO uint32_t DR8R;          /*!< GPIO 8-mA Drive Select,                          Address offset: 0x000 */
    __IO uint32_t ODR;           /*!< GPIO Open Drain Select,                          Address offset: 0x000 */
    __IO uint32_t PUR;           /*!< GPIO Pull-Up Select,                             Address offset: 0x000 */
    __IO uint32_t PDR;           /*!< GPIO Pull-Down Select,                           Address offset: 0x000 */
    __IO uint32_t SLR;           /*!< GPIO Slew Rate Control Select,                   Address offset: 0x000 */
    __IO uint32_t DEN;           /*!< GPIO Digital Enable,                             Address offset: 0x000 */
    __IO uint32_t LOCK;          /*!< GPIO Lock,                                       Address offset: 0x000 */
    __IO uint32_t CR;            /*!< GPIO Commit,                                     Address offset: 0x000 */
    __IO uint32_t AMSEL;         /*!< GPIO Analog Mode Select,                         Address offset: 0x000 */
    __IO uint32_t PCTL;          /*!< GPIO Port Control,                               Address offset: 0x000 */
    __IO uint32_t ADCCTL;        /*!< GPIO ADC Control,                                Address offset: 0x000 */
    __IO uint32_t DMACTL;        /*!< GPIO DMA Control,                                Address offset: 0x000 */

} gpio_port_t;


/**
  * @brief Synchronous Serial Interface peripheral (SSI) Register Structure
  */

typedef struct ssi_periheral
{
  __IO uint32_t  CR0;             /*!< SSI Control 0,                Address offset: 0x000          */
  __IO uint32_t  CR1;             /*!< SSI Control 1,                Address offset: 0x004          */
  __IO uint32_t  DR;              /*!< SSI Data,                     Address offset: 0x008          */
  __IO uint32_t  SR;              /*!< SSI Status,                   Address offset: 0x00C          */
  __IO uint32_t  CPSR;            /*!< SSI Clock Prescale,           Address offset: 0x010          */
  __IO uint32_t  IM;              /*!< SSI Interrupt Mask,           Address offset: 0x014          */
  __IO uint32_t  RIS;             /*!< SSI Raw Interrupt Status,     Address offset: 0x018          */
  __IO uint32_t  MIS;             /*!< SSI Masked Interrupt Status,  Address offset: 0x01C          */
  __O  uint32_t  ICR;             /*!< SSI Interrupt Clear,          Address offset: 0x020          */
  __IO uint32_t  DMACTL;          /*!< SSI DMA Control,              Address offset: 0x024          */
  __I  uint32_t  RESERVED[1000];  /*!< RESERVED,                     Address offset: 0x028 to 0xFC4 */
  __IO uint32_t  CC;              /*!< SSI Clock Configuration       Address offset: 0xFC8          */

} ssi_periph_t;



typedef union uart_rsr_ecr
{
    __I  uint32_t  RSR;            /*!< UART Receive Status/Error Clear                                       */
    __IO uint32_t  ECR_UART_ALT;   /*!< UART Receive Status/Error Clear                                       */

} uart_rsr_ecr_t;


typedef struct uart_peripheral
{
    __IO uint32_t  DR;              /*!< UART Data                                                             */
    uart_rsr_ecr_t RSR_ECR;         /*!< UART Receive and Error status clear                                   */
    __I  uint32_t  RESERVED[4];     /*!< RESERVED,                                       Address offset: 0x000 */
    __IO uint32_t  FR;              /*!< UART Flag                                                             */
    __I  uint32_t  RESERVED1;       /*!< RESERVED,                                       Address offset: 0x000 */
    __IO uint32_t  ILPR;            /*!< UART IrDA Low-Power Register                                          */
    __IO uint32_t  IBRD;            /*!< UART Integer Baud-Rate Divisor                                        */
    __IO uint32_t  FBRD;            /*!< UART Fractional Baud-Rate Divisor                                     */
    __IO uint32_t  LCRH;            /*!< UART Line Control                                                     */
    __IO uint32_t  CTL;             /*!< UART Control                                                          */
    __IO uint32_t  IFLS;            /*!< UART Interrupt FIFO Level Select                                      */
    __IO uint32_t  IM;              /*!< UART Interrupt Mask                                                   */
    __IO uint32_t  RIS;             /*!< UART Raw Interrupt Status                                             */
    __IO uint32_t  MIS;             /*!< UART Masked Interrupt Status                                          */
    __O  uint32_t  ICR;             /*!< UART Interrupt Clear                                                  */
    __IO uint32_t  DMACTL;          /*!< UART DMA Control                                                      */
    __I  uint32_t  RESERVED2[22];   /*!< RESERVED,                                       Address offset: 0x000 */
    __IO uint32_t  UART9BITADDR;    /*!< UART 9-Bit Self Address                                               */
    __IO uint32_t  UART9BITAMASK;   /*!< UART 9-Bit Self Address Mask                                          */
    __I  uint32_t  RESERVED3[965];  /*!< RESERVED,                                       Address offset: 0x000 */
    __IO uint32_t  PP;              /*!< UART Peripheral Properties                                            */
    __I  uint32_t  RESERVED4;       /*!< RESERVED,                                       Address offset: 0x000 */
    __IO uint32_t  CC;              /*!< UART Clock Configuration                                              */

} uart_periph_t;




/***************************************************************************/
/*                                                                         */
/*                       Device Peripheral Definitions                     */
/*                                                                         */
/***************************************************************************/


/*
 * @brief Peripheral Declarations
 */
#define GPIOA                    ((gpio_port_t *) GPIOA_BASEADDR)
#define GPIOB                    ((gpio_port_t *) GPIOB_BASEADDR)
#define GPIOC                    ((gpio_port_t *) GPIOC_BASEADDR)
#define GPIOD                    ((gpio_port_t *) GPIOD_BASEADDR)
#define GPIOE                    ((gpio_port_t *) GPIOE_BASEADDR)
#define GPIOF                    ((gpio_port_t *) GPIOF_BASEADDR)

#define GPIOA_AHB                ((gpio_port_t *) GPIOA_AHB_BASEADDR)
#define GPIOB_AHB                ((gpio_port_t *) GPIOB_AHB_BASEADDR)
#define GPIOC_AHB                ((gpio_port_t *) GPIOC_AHB_BASEADDR)
#define GPIOD_AHB                ((gpio_port_t *) GPIOD_AHB_BASEADDR)
#define GPIOE_AHB                ((gpio_port_t *) GPIOE_AHB_BASEADDR)
#define GPIOF_AHB                ((gpio_port_t *) GPIOF_AHB_BASEADDR)

#define SSI0                     ((ssi_periph_t *) SSI0_BASEADDR)
#define SSI1                     ((ssi_periph_t *) SSI1_BASEADDR)
#define SSI2                     ((ssi_periph_t *) SSI2_BASEADDR)
#define SSI3                     ((ssi_periph_t *) SSI3_BASEADDR)

#define UART0                    ((uart_periph_t *) UART0_BASEADDR)
#define UART1                    ((uart_periph_t *) UART1_BASEADDR)
#define UART2                    ((uart_periph_t *) UART2_BASEADDR)
#define UART3                    ((uart_periph_t *) UART3_BASEADDR)
#define UART4                    ((uart_periph_t *) UART4_BASEADDR)
#define UART5                    ((uart_periph_t *) UART5_BASEADDR)
#define UART6                    ((uart_periph_t *) UART6_BASEADDR)
#define UART7                    ((uart_periph_t *) UART7_BASEADDR)

#define SYSCTL                   ((sysctl_t        *) SYSCTL_BASEADDR)
#define SYSCTL_LEGACY            ((sysctl_legacy_t *) SYSCTL_BASEADDR)

#define NVIC                     ((NVIC_T          *) NVIC_BASEADDR)




#endif /* MAIN_TM4C123GH6PM_H_ */
