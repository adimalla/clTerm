

/**
 ******************************************************************************
 * @file    main.c
 * @author  Aditya Mall,
 * @brief
 *
 *  Info    Test application for testing clTerm serial terminal utility
 *          tiva launchpad 123gxl using bare-metal code.
 *
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2020 Aditya Mall, MIT License </center></h2>
 *
 * MIT License
 *
 * Copyright (c) 2020 Aditya Mall
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
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




/*
 * Standard, board and API specific header files
 */
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"


/* API header file */
#include "cl_term.h"



/******************************************************************************/
/*                                                                            */
/*                  Data Structures and Defines                               */
/*                                                                            */
/******************************************************************************/


//Bit Banding defines for Port F Pins
#define PF1  (*((volatile uint32_t *)(0x42000000 + (0x400253FC-0x40000000)*32 + 1*4)))
#define PF2  (*((volatile uint32_t *)(0x42000000 + (0x400253FC-0x40000000)*32 + 2*4)))
#define PF3  (*((volatile uint32_t *)(0x42000000 + (0x400253FC-0x40000000)*32 + 3*4)))
#define PF4  (*((volatile uint32_t *)(0x42000000 + (0x400253FC-0x40000000)*32 + 4*4)))


//Board Modules Pins
#define ONBOARD_RED_LED      PF1
#define ONBOARD_BLUE_LED     PF2
#define ONBOARD_GREEN_LED    PF3
#define ONBOARD_PUSH_BUTTON  PF4

//UART0 defines
#define BAUDRATE 115200



/******************************************************************************/
/*                                                                            */
/*                   Bare-metal Function Implementations                      */
/*                                                                            */
/******************************************************************************/


//System clock and GPIO F for on-board led and button intilaization
void initHw(void)
{

    // Configure System clock as 40Mhz
    SYSCTL_RCC_R = SYSCTL_RCC_XTAL_16MHZ | SYSCTL_RCC_OSCSRC_MAIN | SYSCTL_RCC_USESYSDIV | (0x04 << SYSCTL_RCC_SYSDIV_S);

    // Enable GPIO port F peripherals
    SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOF;

    // Enable GPIO port A, and F peripherals
    SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOA | SYSCTL_RCGC2_GPIOF;

    //**************************************************** On Board Modules ******************************************************************//

    // Configure On boards RED, GREEN and BLUE led and Pushbutton Pins
    GPIO_PORTF_DEN_R |= (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4);  // Enable Digital
    GPIO_PORTF_DIR_R |= (1 << 1) | (1 << 2) | (1 << 3);             // Enable as Output
    GPIO_PORTF_DIR_R &= ~(0x10);                                    // Enable push button as Input
    GPIO_PORTF_PUR_R |= 0x10;                                       // Enable internal pull-up for push button


}


//UART0 initializations for serial COMM port on PA0 and PA1 (RX, TX)
void init_uart0(void)
{

    // Enable GPIO port F peripherals
    SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOA;

    // Configure UART0 pins
    SYSCTL_RCGCUART_R  |= SYSCTL_RCGCUART_R0;                       // Turn-on UART0, leave other uarts in same status
    GPIO_PORTA_DEN_R   |= 3;                                        // Turn on Digital Operations on PA0 and PA1
    GPIO_PORTA_AFSEL_R |= 3;                                        // Select Alternate Functionality on PA0 and PA1
    GPIO_PORTA_PCTL_R  |= GPIO_PCTL_PA1_U0TX | GPIO_PCTL_PA0_U0RX;  // Select UART0 Module

    // Configure UART0 to 115200 baud, 8N1 format (must be 3 clocks from clock enable and config writes)
    UART0_CTL_R   = 0;                                              // turn-off UART0 to allow safe programming
    UART0_CC_R   |= UART_CC_CS_SYSCLK;                              // use system clock (40 MHz)
    UART0_IBRD_R  = 21;                                             // r = 40 MHz / (Nx115.2kHz), set floor(r)=21, where N=16
    UART0_FBRD_R  = 45;                                             // round(fract(r)*64)=45
    UART0_LCRH_R |= UART_LCRH_WLEN_8 | UART_LCRH_FEN;               // configure for 8N1 w/ 16-level FIFO
    UART0_CTL_R  |= UART_CTL_TXE | UART_CTL_RXE | UART_CTL_UARTEN;  // enable TX, RX, and module

}



// Blocking function that writes a serial character when the UART buffer is not full
void putcUart0(const char c)
{
    (UART0_FR_R & UART_FR_TXFF);
    UART0_DR_R = c;

}


// Blocking function that returns with serial data once the buffer is not empty
char getcUart0(void)
{
    while (UART0_FR_R & UART_FR_RXFE);
    return UART0_DR_R & 0xFF;
}



/******************************************************************************/
/*                                                                            */
/*                  clTerm console handle configurations                      */
/*                                                                            */
/******************************************************************************/


/*******************************************************************************
 *
 * Info: API operations structure.
 *
 * typedef struct _console_operations
 * {
 *   // Initialize serial hardware, (must return 0 for error, 1 for success)
 *   uint8_t (*open)(uint32_t baudrate);
 *
 *   // Function to print character data through serial
 *   uint8_t (*print_char)(char data);
 *   char    (*read_char)(void);
 *
 *   // Optional, reserved for future APIs
 *   int8_t  (*write)(const char *buffer, int16_t length);
 *   int8_t  (*read)(char *read_buffer, int16_t length);
 *
 *  }console_ops_t;
 *
 *
 *  Initialization:-
 *
 *  API initializes with 'console_open(...)' call which uses,
 *  (*open)(uint32_t baudrate) as call back function. and API operations,
 *  handle/object (structure shows above) as parameter.
 *
 *  Additionally API Operations expects standard serial data write,
 *  writes a byte to serial data register and serial read byte,
 *  reads a byte from serial data register
 *
 *
 *  1) Create a simple wrapper function for open which expects,
 *     baud-rate as parameter and 'must return 1' for success.
 *
 *
 *  Example:
 *
 *  uint8_t simple_open(uint32_t baud_rate)
 *  {
 *
 *      // User;s own serial initialization function
 *      your_uart0_init(void);
 *
 *      return 1;
 *  }
 *
 *  or
 *
 *  uint8_t simple_open(uint32_t baud_rate)
 *  {
 *      // User's own serial initialization function
 *      your_uart0_init(baud_rate);
 *
 *      // if above function successful return 1
 *      return 1;
 *  }
 *
 *
 *  2) Link the wrapper function and read and write function to API,
 *     operations structure.
 *
 *
 *  Example:
 *
 *  console_ops_t your_serial_operations =
 *  {
 *      .open       = simple_open,
 *      .print_char = your_putchar,
 *      .read_char  = your_readchar,
 *  }
 *
 *
 *  3) Call console initialization function and pass reference to API,
 *     operations object created above. Choose static or dynamic allocation,
 *     (if heap region configured).
 *
 *
 *  Example: (choosing static allocation)
 *
 *  //Define baud-rate / serial speed
 *  #define BAUDRATE 115200
 *
 *  //Initialize serial buffer
 *  char *buffer[40] = {0};
 *
 *  //Initialize serial handle
 *  cl_term_t *console;  //pointer has handle function allocates object
 *
 *  console = console_open(&your_serial_operations, BAUDRATE, buffer, CONSOLE_STATIC);
 *
 *  if(!console)
 *  {
 *      //assert error
 *  }
 *
 ******************************************************************************/



//Create wrapper function

// Here in this test code baud-rate for serial is redundant and used as,
// dummy parameter because main, UART initialization functions configures,
// serial baud-rate internally.
uint8_t myUartOpen(uint32_t baud_rate)
{
     init_uart0();

     //return 1 for success, here
     return 1;
}

//Accordingly, creating wrapper function of serial read and write to match
//API operation function return types and parameters

uint8_t myPutChar(char data)
{
    putcUart0(data);

    return 0;
}


//Link API operations
console_ops_t myUartOperations =
{

 .open       = myUartOpen,
 .print_char = myPutChar,
 .read_char  = getcUart0,

};


//Console handle Instance,(Global declaration optional)
cl_term_t *myConsole;




/******************************************************************************/
/*                                                                            */
/*                  clTerm command table configurations                       */
/*                                                                            */
/******************************************************************************/




/**
 * main.c
 */
int main(void)
{

    //Initialize variables
    bool loop = false;

    char serial_buffer[MAX_INPUT_SIZE] = {0};

    //Initialize peripheral hardware (CLOCK and board led GPIO)
    initHw();

    //Create console handle, initializes UART/serial hardware
    myConsole = console_open(&myUartOperations, BAUDRATE, serial_buffer, CONSOLE_STATIC);


    loop = true;

    while(loop)
    {
        //Get input from user
        console_get_string(myConsole, MAX_INPUT_SIZE);

    }

    return 0;
}
