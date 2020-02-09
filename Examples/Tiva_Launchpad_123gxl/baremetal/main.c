

/**
 ******************************************************************************
 * @file    main.c
 * @author  Aditya Mall,
 * @brief
 *
 *  Info    Application for testing clTerm serial terminal utility on,
 *          tiva launchpad 123gxl using bare-metal code.
 *
 *  Note
 *          Bare-metal functions provide by Dr.Jason Losh, The University of,
 *          Texas at Arlington as a part of project assignments in his courses,
 *          which is used here to demonstrate the portability of the API,
 *          to link with external functions.
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



/*******************************************************************************
 * Note:-
 *  Bare-metal functions provide by Dr.Jason Losh, The University of Texas at,
 *  Arlington as a part of project assignments in his courses, which is used here,
 *  to demonstrate the portability of the API to link with external functions.
 ******************************************************************************/



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
    while(UART0_FR_R & UART_FR_TXFF);
    UART0_DR_R = c;

}


// Blocking function that returns with serial data once the buffer is not empty
char getcUart0(void)
{
    while (UART0_FR_R & UART_FR_RXFE);
    return UART0_DR_R & 0xFF;
}



// Blocking function that writes a string when the UART buffer is not full
void putsUart0(const char* str)
{
    uint8_t i;

    for (i = 0; i < strlen(str); i++)
        putcUart0(str[i]);
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
 *  typedef struct _console_operations
 *  {
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
 * Initialization:-
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
 *     if static allocation is selected then input buffer (serial buffer),
 *     size is taken from cl_term_config.h
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
/*                         and adding commands.                               */
/*                                                                            */
/******************************************************************************/


/******************************************************************************
 *
 * Info:-
 *  clTerm utility provides user to add custom commands which are maintained in,
 *  console command table structure.
 *
 *  typedef struct _command_table
 *  {
 *   uint8_t command_table_size;
 *   char    command_name[CMD_NAME_SIZE];
 *   int     (*func)(int argc, char **argv);
 *
 *  } command_table_t;
 *
 * Initialization:-
 *
 *  1) Create command_table object though create_commad_list(...) API,
 *     it takes console handle object as parameter and table size.
 *     if console object is statically allocated then table size value,
 *     is redundant and will use size value from cl_term_config.h.
 *
 *  Example:
 *
 *  command_table_t *command_list;
 *
 *  command_list = create_command_list(console, MAX_TABLE_SIZE);
 *
 *  if(!command_list)
 *  {
 *    //assert error
 *  }
 *
 *
 *  2) Adding user defined commands to command table through add_command(...),
 *     with C command line arguments. Takes command_table object as parameter,
 *     and command name and address of the command function to be called.
 *
 *  Example:
 *
 *  int yourCommand1(int agrc, char **argv)
 *  {
 *      //do something useful.
 *
 *      return 0;
 *  }
 *
 *  int yourCommand2(int agrc, char **argv)
 *  {
 *      //do something useful again.
 *
 *      return 0;
 *  }
 *
 *  add_command(command_list, "command1", yourCommand1);
 *
 *  add_command(command_list, "command2", yourCommand2);
 *
 *  User input:-
 *
 *  command2 arg1 agr2
 *
 *
 ******************************************************************************/



/******************************************************************************/
/*                                                                            */
/*                       User defined commands                                */
/*                                                                            */
/******************************************************************************/

/*
 * Turns the on board RED LED on and off and prints operation,
 * to serial terminal. when "red on/off" is entered by the user.
 * Uses bare metal functions.
 */
int myCommand1(int argc, char **argv)
{
    int count = 0;
    int index = 0;

    count = argc;

    /*Check argument count, 1st argument is the command,
     *name itself.
     */
    if(count < 2)
    {
        putsUart0("Error: Less number of args entered \r\n");
    }
    else if(count > 2)
    {
        putsUart0("Error: Greater number of args entered \r\n");
    }
    else
    {
        putsUart0("\r\n");

        /*index = 0, first arg on index 0 is the command name,
         *index = 1, command argument.
         */
        if( strcmp(argv[index + 1], "on") == 0 )
        {
            ONBOARD_RED_LED = 1;

            putsUart0("RED LED is ON \r\n");

        }
        else if( strcmp(argv[index + 1], "off") == 0 )
        {
            ONBOARD_RED_LED = 0;

            putsUart0("RED LED is OFF \r\n");
        }
        else
        {
            putsUart0("Wrong argument entered \r\n");
        }

        putsUart0("\r\n");

        /*User can also add checks for correct command name by,
         *checking argv[index] where index = 0.
         */
    }

    return 0;
}

/*
 * Print the list of all arguments added by the user.
 * Uses print API provided by clTerm utility.
 * API only works for external function if console,
 * object is global.
 */
int myCommand2(int argc, char **argv)
{
    int index = 0;

    console_print(myConsole, "\n");

    for(index = 1; index < argc; index++)
    {
        console_print(myConsole, argv[index]);
        console_print(myConsole, "\n");
    }

    console_print(myConsole, "\n");

    return 0;
}



/******************************************************************************/
/*                                                                            */
/*                 Starting the console and executing commands.               */
/*                                                                            */
/******************************************************************************/


/*****************************************************************************
 *
 * Info:-
 *  The commands are executed by calling the console_begin(...) followed by,
 *  calling the console_get_string(...) to get user input and finally,
 *  calling the console_exec_command(...) to execute the correct entered by,
 *  the user.
 *
 * Initialization.
 *
 *  1) Start console by calling the console_begin(..) function.
 *     it takes console handle object and command table object as parameters.
 *     if there are no previous exceptions with command table API functions,
 *     console_begin executes successfully, or returns exception to console,
 *     handle which can be handle by catch_exception(...) function.
 *
 *  Example:
 *
 *     console_begin(console, command_list);
 *
 *  2) Call console_get_string(...), takes two parameters, object to console,
 *     handle and max input buffer size.
 *
 *  Example:
 *
 *     console_get_string(console, MAX_INPUT_SIZE);
 *
 *
 *  3) Call console_exec_command(...), takes console object, command table object,
 *     and user input buffer as parameters. This call is dependent upon successful,
 *     execution of console_begin(..) function otherwise exception is generated.
 *
 *
 *  Example:
 *
 *     console_exec_command(console, command_list, buffer);
 *
 ******************************************************************************/




/******************************************************************************/
/*                                                                            */
/*                        Exception handling                                  */
/*                                                                            */
/******************************************************************************/

/*****************************************************************************
 *
 *  Info:-
 *      Exception handling functions are provided to throw and catch,
 *      exceptions produced by the console APIs, Exception handling,
 *      functions are dependent on console handle.
 *
 *      Console APIs throw exceptions internally to the console handle,
 *      which can be caught by the catch_exception(...) function or viewed as,
 *      symbols in a live debug view.
 *
 *      > throw_exception(...), console handle object and exception type as,
 *        parameters.
 *
 *      List of exceptions values can be viewed in cl_term.h file.
 *
 *      > catch_exception(...), console handle object and exception state as,
 *        parameters.
 *
 *        if exception state = EXCEPTION_HOLD_STATE, then catch exception,
 *        function will block the state of the program and report the,
 *        exception to the terminal.  *
 *
 *  Example:-
 *
 *      int8_t exception;
 *
 *      exception = add_command(...)
 *
 *      throw_exception(console, (console_exception_t)exception);
 *
 *      catch_exception(console, EXCEPTION_HOLD_STATE);
 *
 *****************************************************************************/




/**
 * main.c
 */
int main(void)
{

    /*Initialize variables*/
    bool loop = false;

    char serial_buffer[MAX_INPUT_SIZE] = {0};

    command_table_t *command_list;
    int8_t           exception;

    /*Initialize peripheral hardware (CLOCK and board led GPIO)*/
    initHw();


    /*Create console handle, initializes UART/serial hardware*/
    myConsole = console_open(&myUartOperations, BAUDRATE, serial_buffer, CONSOLE_STATIC);


    /*Create table object*/
    command_list = create_command_list(myConsole, MAX_TABLE_SIZE);


    /*Add user commands*/
    exception  = add_command(command_list, "red", myCommand1);

    exception |= add_command(command_list, "print", myCommand2);


    throw_exception(myConsole, (console_exceptions_t)exception);


    /*Start console*/
    console_begin(myConsole, command_list);


    loop = true;

    while(loop)
    {
        /* Get input from user */
        console_get_string(myConsole, MAX_INPUT_SIZE);

        /* Execute user commands */
        console_exec_command(myConsole, command_list, serial_buffer);

        /* catch exception */
        catch_exception(myConsole, EXCEPTION_HOLD_STATE);

    }

    return 0;
}
