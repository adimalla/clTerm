/**
 ******************************************************************************
 * @file    main.c
 * @author  Aditya Mall,
 * @brief
 *
 *  Info    Application for testing clTerm serial terminal utility,
 *          using custom peripheral drivers.
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
 * Standard header and api header files
 */
#include <string.h>

#include "gpio_tm4c123gh6pm.h"
#include "uart_tm4c123gh6pm.h"

#include "cl_term.h"



/******************************************************************************/
/*                                                                            */
/*                      Data Structures and Defines                           */
/*                                                                            */
/******************************************************************************/


#define BAUDARATE 115200




/******************************************************************************/
/*                                                                            */
/*                       User Peripheral Init Functions                       */
/*                                                                            */
/******************************************************************************/



/* Function to initialize system clock to 40 MHz */
void init_clock(void)
{
    sysctl_t *pSYSCTL = SYSCTL;

    pSYSCTL->RCC = 0x00000540 | 0x00400000 | (0x04 << 23);
}



/* Initialize on board LED */
void init_board_io(void)
{

    gpio_handle_t board_io;

    memset(&board_io, 0, sizeof(board_io));

    board_io.p_gpio_x                  = GPIOF;
    board_io.gpio_pin_config.pin_mode  = DIGITAL_ENABLE;
    board_io.gpio_pin_config.direction = DIRECTION_OUTPUT;

    board_io.gpio_pin_config.pin_number = 1;
    gpio_init(&board_io);

    board_io.gpio_pin_config.pin_number = 2;
    gpio_init(&board_io);

    board_io.gpio_pin_config.pin_number = 3;
    gpio_init(&board_io);

}



/* Initialize UART for terminal */
uint8_t init_uart(gpio_port_t *gpio_port_addr, uart_periph_t *port_address, uint32_t buad_rate)
{

    uint8_t func_retval = 1;

    gpio_handle_t console_io;
    uart_handle_t console_uart;

    memset(&console_io, 0, sizeof(console_io));

    console_io.p_gpio_x                           = gpio_port_addr;
    console_io.gpio_pin_config.pin_mode           = DIGITAL_ENABLE;
    console_io.gpio_pin_config.alternate_function = ALTERNATE_FUNCTION_ENABLE;

    console_io.gpio_pin_config.pin_number = 0;
    console_io.gpio_pin_config.pctl_val   = UART0RX_PA0;

    gpio_init(&console_io);

    console_io.gpio_pin_config.pin_number = 1;
    console_io.gpio_pin_config.pctl_val   = UART0TX_PA1;

    gpio_init(&console_io);

    memset(&console_uart, 0, sizeof(console_uart));

    console_uart.p_uart_x = port_address;
    console_uart.uart_config.uart_clock_source = CLOCK_SYSTEM;
    console_uart.uart_config.uart_baudrate     = buad_rate;
    console_uart.uart_config.stop_bits         = ONE_STOP_BIT;
    console_uart.uart_config.uart_fifo         = FIFO_ENABLE;
    console_uart.uart_config.word_length       = EIGHT_BITS;
    console_uart.uart_config.uart_direction    = UART_TRANSCEIVER;

    uart_init(&console_uart);

    return func_retval;
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
 *  uint8_t serial_open(uint32_t baud_rate)
 *  {
 *
 *      // User's own serial initialization function
 *      your_uart0_init(GPIOA, UART0, baud_rate);
 *
 *      return 1;
 *  }
 *
 *  or
 *
 *  uint8_t serial_open(uint32_t baud_rate)
 *  {
 *      // User's own serial initialization function
 *      your_uart0_init(UART0, baud_rate);
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
 *     Caution!: Static allocation only creates one instance per application.
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


/* Create wrapper function */

/* Wrapper function for open */
/* Must return 1 for success */
uint8_t serial_open(uint32_t baud_rate)
{
    int8_t func_retval = 0;

    func_retval = init_uart(GPIOA, UART0, baud_rate);

    return func_retval;
}


/* Wrapper function for print_char */
uint8_t write_char(char data)
{
    uart_putchar(UART0, data);

    return 0;
}


/* Wrapper function for read_char */
char read_char(void)
{
    return uart_getchar(UART0);
}



/* Link above functions to console operations */
console_ops_t serial_ops =
{

 .open       = serial_open,
 .print_char = write_char,
 .read_char  = read_char,

};



/* Initialize handle instance as pointer (Global declaration optional) */
cl_term_t *console;




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



/* Test command to print all arguments entered by user */
int test1(int argc, char **argv)
{

    int index = 0;
    int count = 0;

    count = argc;

    console_print(console, "test command \n");

    for(index = 1; index < count; index++)
    {
        console_print(console, argv[index]);

        console_print(console, "\n");
    }

    return 0;
}


/* Test command to switch on/off on board LEDs              */
/* Command: led red on/off, led blue on/off or green on/off */
/* Uses new console object                                  */
int led(int argc, char **argv)
{
    int argument_count = 0;
    int index          = 0;

    argument_count = argc;

    /* Check number of arguments */
    if(argument_count < 3)
    {
        console_print(console, "Error: Less arguments entered \n");
    }
    else if(argument_count > 3)
    {
        console_print(console, "Error: Extra arguments entered \n");
    }
    else
    {
        /* Shown for clarity but can be optimized */

        /* Handle RED LED operation */
        if(strcmp(argv[index + 1], "red") == 0)
        {

            if(strcmp(argv[index + 2], "on") == 0)
            {
                gpio_write_pin(GPIOF, 1, SET);

            }
            else if (strcmp(argv[index + 2], "off") == 0)
            {
                gpio_write_pin(GPIOF, 1, RESET);
            }
            else
            {
                console_print(console, "Error: Wrong arguments entered \n");
            }

        }
        /* Handle BLUE LED operation */
        else if(strcmp(argv[index + 1], "blue") == 0)
        {

            if(strcmp(argv[index + 2], "on") == 0)
            {
                gpio_write_pin(GPIOF, 2, SET);
            }
            else if (strcmp(argv[index + 2], "off") == 0)
            {
                gpio_write_pin(GPIOF, 2, RESET);
            }
            else
            {
                console_print(console, "Error: Wrong arguments entered \n");
            }

        }
        /* Handle GREEN LED operation */
        else if(strcmp(argv[index + 1], "green") == 0)
        {

            if(strcmp(argv[index + 2], "on") == 0)
            {
                gpio_write_pin(GPIOF, 3, SET);
            }
            else if (strcmp(argv[index + 2], "off") == 0)
            {
                gpio_write_pin(GPIOF, 3, RESET);
            }
            else
            {
                console_print(console, "Error: Wrong arguments entered \n");
            }

        }
        else
        {
            console_print(console, "Error: Wrong arguments entered \n");
        }


    }


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



/* Main function */
int main(void)
{

    uint8_t loop = 0;
    int8_t  ok   = 0;

    command_table_t *command_list;

    char text_buffer[100];

    /* Initialize clock */
    init_clock();

    /* Initialize peripheral IO*/
    init_board_io();


    /* Open Console */
    console = console_open(&serial_ops, BAUDARATE, text_buffer, CONSOLE_STATIC);

    /* Create Command List Table */
    command_list = create_command_list(console, MAX_TABLE_SIZE);

    /* Add Commands */
    ok  =  add_command(command_list, "test1", test1);
    ok |=  add_command(command_list, "led", led);


    /* optional throw exception for add command */
    throw_exception(console, (console_exceptions_t)ok);


    /* Start Console, dependent, needs command table*/
    console_begin(console, command_list);


    loop = 1;

    while(loop)
    {
        /* Get input from user, independent, blocking function */
        console_get_string(console, MAX_INPUT_SIZE);

        /* Execute command, dependent, needs console begin */
        console_exec_command(console, command_list, text_buffer);

        /* Catch Exception */
        catch_exception(console, EXCEPTION_HOLD_STATE);

    }

    return 0;
}





