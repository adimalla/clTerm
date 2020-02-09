/**
 ******************************************************************************
 * @file    cl_term.h
 * @author  Aditya Mall,
 * @brief
 *
 *  Info   clTerm header file.
 *
 ******************************************************************************
 *
 *  Info:-
 *                        88888888888       8888888b.
 *                 888        888           888    888
 *         d8888b  888        888   .d88b.  888   d88P 88888b.d88b.
 *        d8p      888        888  d8P  Y8b 8888888P   888  888  88b
 *        888      888        888  88888888 888 T88b   888  888  888
 *        Y8b      888        888  Y8b.     888  T88b  888  888  888
 *         Y8888P  88888888   888   Y8888   888   T88b 888  888  888
 *
 *                  clTerm Portable Serial Terminal Utility.
 *
 *
 * clTerm is an easy to port API based serial terminal utility which allows,
 * users to add standard C like "command line arguments" based functions,
 * or commands to their application. This utility is implemented via callback,
 * which allows portability across any micro-controller that supports serial
 * protocols.
 *
 * Steps:-
 *
 *
 ******************************************************************************
 * * @attention
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
 *********************************************************************************
 */


#ifndef CL_TERM_H_
#define CL_TERM_H_



/*
 * Standard header and api header files
 */
#include <stdint.h>

#include "cl_term_config.h"



/******************************************************************************/
/*                                                                            */
/*                      Data Structures and Defines                           */
/*                                                                            */
/******************************************************************************/



/* Console Exception values */
typedef enum _console_exception_values
{
    CONSOLE_NO_EXCEPTION             =  0,   /*!< no Exception Value                               */
    CONSOLE_OPEN_CMD_ERROR           = -1,   /*!< console open function pointer NULL error         */
    CONSOLE_PRINTCHR_CMD_ERROR       = -2,   /*!< console printchar function pointer NULL error    */
    CONSOLE_READCHR_CMD_ERROR        = -3,   /*!< console readchar function pointer NULL error     */
    CONSOLE_OPEN_CALLBACK_ERROR      = -4,   /*!< Console open call back return error              */
    CONSOLE_PRINT_FUNC_ERROR         = -5,   /*!< console print function error                     */
    CONSOLE_BEGIN_ERROR              = -6,   /*!< console begin function error                     */
    CONSOLE_GET_STRING_FUNC_ERROR    = -7,   /*!< console get string function error                */
    CONSOLE_EXEC_CMD_FUNC_ERROR      = -8,   /*!< console execute command function error           */
    CONSOLE_CMD_LIST_FUNC_ERROR      = -9,   /*!< command list function error                      */
    CONSOLE_CMD_LIST_STA_ALLOC_ERROR = -10,  /*!< command list Static allocation error             */
    CONSOLE_ADD_CMD_ERROR            = -11,  /*!< console add command function error               */
    CONSOLE_CMD_LIST_DYN_ALLOC_ERROR = -12,  /*!< command list dynamic allocation error            */
    CONSOLE_OBJ_NULL_ERROR           = -13,  /*!< console object NULL error                        */
    CONSOLE_CMD_LIST_OBJ_ERROR       = -14,  /*!< command list object NULL error                   */
    CONSOLE_GET_STRING_NOT_CALLED    = -15,  /*!< get_string function not used before exec_command */

}console_exceptions_t;


/* Catch exception API states */
typedef enum _catch_exception_state
{
    EXCEPTION_HOLD_STATE  = 1,   /* Block when exception occurs, report exceptions to terminal */
    EXCEPTION_REPORT_ONLY = 2,   /* Report exceptions to terminal only, do not block           */

}exception_state_t;





/* Call back functions  */
typedef struct _console_operations
{
    uint8_t (*open)(uint32_t baudrate);                    /*!< Initialize serial hardware, (must return 0 for error, 1 for success) */
    uint8_t (*print_char)(char data);                      /*!< Function to print character data through serial                      */
    char    (*read_char)(void);                            /*!< Function to read character from serial input                         */
    int8_t  (*write)(const char *buffer, int16_t length);  /*!< (optional) not implemented                                           */
    int8_t  (*read)(char *read_buffer, int16_t length);    /*!< (optional) not implemented                                           */

}console_ops_t;



/* Console object allocation type values */
typedef enum _console_alloc_type
{
    CONSOLE_STATIC  = 1,  /*!< Static allocation type value  */
    CONSOLE_DYNAMIC = 2,  /*!< Dynamic allocation type value */

}console_alloc_type_t;


/* Console status fields */
typedef struct _console_status
{
    uint8_t begin       : 1;  /*!< Console Begin Status            */
    uint8_t get_input   : 1;  /*!< Get string function call status */
    uint8_t lock        : 1;  /*!< Function Lock (not implemented) */
    uint8_t reserved    : 6;  /*!< Reserved                        */

}console_status_t;


/* Console Handle Structure */
typedef struct _cl_term
{
    char                  *input_buffer;       /*!< Serial text input buffer     */
    console_ops_t         *console_commands;   /*!< Console operations structure */
    console_exceptions_t  exception;           /*!< Exception return values      */
    console_alloc_type_t  allocation_type;     /*!< Object allocation type       */
    console_status_t      status;              /*!< Console status               */
    uint8_t               version;             /*!< Utility Version              */

}cl_term_t;




/* Command List Table */
typedef struct _command_table
{
    uint8_t command_table_size;              /*!< Table Size              */
    char    command_name[CMD_NAME_SIZE];     /*!< Command Name            */
    int     (*func)(int argc, char **argv);  /*!< Linked function pointer */

}command_table_t;




/******************************************************************************/
/*                                                                            */
/*                   Console Function Prototypes                              */
/*                                                                            */
/******************************************************************************/



/**************************************************************************
 * @brief  Constructor function to create console handle
 *         (Testing only static allocation)
 * @param  *console_ops : reference to console callback functions
 * @param  baudrate     : baudrate / speed of serial terminal
 * @param  buffer       : data / text buffer for serial terminal
 * @param  alloc_type   : handle object allocation type, static/dynamic
 * @retval cl_term_t   : Error = NULL, Success = console object handle.
 *                        exception(return to handle)
 *                        Exceptions, -1, -2, -3, -4 (see exception values)
 ***************************************************************************/
cl_term_t* console_open(console_ops_t *console_ops, uint32_t baudrate, void *buffer, console_alloc_type_t alloc_type);




/*********************************************************************
 * @brief  Function to print to serial terminal through call-backs
 * @param  *console       : reference to console handle
 * @param  string_input[] : data / text buffer for serial terminal
 * @retval int8_t         : Error = -5 (exception), Success = 0
 *********************************************************************/
int8_t console_print(cl_term_t *console, char string_input[]);




/*******************************************************************
 * @brief  Function to start the console and print console info
 *         sets console begin status needed for exec commands to
 *         work.
 * @param  *console : reference to console handle
 * @retval int8_t   : Error = -6 (exception), Success = 0
 *******************************************************************/
int8_t console_begin(cl_term_t *console, command_table_t *command_table);




/*****************************************************************
 * @brief  Function to start the console and print console info
 * @param  *console      : reference to console handle
 * @param  *input_length : length of input buffer to be filled
 * @retval int8_t        : Error = -7 (exception), Success = 0
 *****************************************************************/
int8_t console_get_string(cl_term_t *console, uint16_t input_length);




/*********************************************************************
 * @brief  Function to search and execute command entered by user,
 *         through serial terminal.
 *         Expects console start_status set to 1 by console_begin
 * @param  *console        : reference to console handle
 * @param  *command_list   : length of input buffer to be filled
 * @param  command_input[] : input buffer from get_string function
 * @retval int8_t          : Error   = -8 (exception),
 *                           Success = 1  (No input, bypass function)
 *                           Success = 0
 *********************************************************************/
int8_t console_exec_command(cl_term_t *console, command_table_t *command_list ,char command_input[]);





/***************************************************************
 * @brief  Constructor function to create command list object
 * @param  *console   : reference to console handle
 * @param  table_size : max number of entries
 * @retval int8_t     : Error   = -9, -10 (exception),
 *                      Success = command_table object
 ***************************************************************/
command_table_t* create_command_list(cl_term_t *console, uint8_t table_size);




/***************************************************************
 * @brief  Function to add commands to the command list table)
 * @param  *command_table : reference to command list table
 * @param  command_name[] : name of the user command
 * @param  (*command)     : reference to the call back function
 * @retval int8_t         : Error = -11 (exception),
 *                          Success = 0 (new entry),
 *                                  = 1 (entry exists)
 ***************************************************************/
int8_t add_command(command_table_t *command_table, char command_name[], int (*command)(int argc, char **argv));




/*************************************************************
 * @brief  Function to update exception type.
 *         (Doesn't throw parent object exception)
 * @param  *console             : reference to console handle
 * @param  console_exceptions_t : exception type
 * @retval void                 : void
 *************************************************************/
void throw_exception(cl_term_t *console, console_exceptions_t exception);




/************************************************************************************
 * @brief  Exception Handling and reporting function.
 *         (Doesn't handle parent object exception)
 * @param  *console             : reference to console handle
 * @param  exception_state      : exception handle state (hold/block or report only)
 * @retval console_exceptions_t : returns exception value in non block/hold state
 ************************************************************************************/
console_exceptions_t catch_exception(cl_term_t *console, exception_state_t exception_state);



#endif /* CL_TERM_H_ */
