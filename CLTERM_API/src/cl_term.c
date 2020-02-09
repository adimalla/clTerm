/**
 ******************************************************************************
 * @file    cl_term.c
 * @author  Aditya Mall,
 * @brief
 *
 *  Info   clTerm source file
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
 * @brief Standard Headers
 */
#include <string.h>
#include <stdlib.h>

#include "cl_term.h"
#include "cl_term_cmd.h"


/******************************************************************************/
/*                                                                            */
/*                     Console Structures and defines                         */
/*                                                                            */
/******************************************************************************/


/* ASCII values used by get_string function */
typedef enum console_command
{
    BACKSPACE         = 8,
    NEWLINE_CHARACTER = 10,
    CARRIAGE_RETURN   = 13,
    ASCII_ESCAPE      = 27,
    ASCII_DELETE      = 127

}console_command_t;




/******************************************************************************/
/*                                                                            */
/*                              Private Functions                             */
/*                                                                            */
/******************************************************************************/


/************************ Helper Functions********************************/

/* Implementation of glibc reentrant strtok Copyright (C) 1991-2019 GNU C Library */

static char *api_strtok_r (char *s, const char *delim, char **save_ptr)
{
    char *end;
    if (s == NULL)
        s = *save_ptr;
    if (*s == '\0')
    {
        *save_ptr = s;
        return NULL;
    }
    /* Scan leading delimiters.  */
    s += strspn (s, delim);
    if (*s == '\0')
    {
        *save_ptr = s;
        return NULL;
    }
    /* Find the end of the token.  */
    end = s + strcspn (s, delim);
    if (*end == '\0')
    {
        *save_ptr = end;
        return s;
    }
    /* Terminate the token and make *SAVE_PTR point past it.  */
    *end = '\0';
    *save_ptr = end + 1;
    return s;
}




/************************* Console private functions******************************/


/**************************************************************
 * @brief  Static function to search for default commands
 * @param  *console       : reference to console handle
 * @param  *command_table : reference to command list table
 * @retval int8_t         : Success = 0, command not found
 *                          Success = 1, command found
 ***************************************************************/
static int8_t search_command(command_table_t *command_table, char command_name[])
{
    int8_t func_retval = 0;

    uint8_t index = 0;

    uint8_t found = 0;


    for(index =0 ; index < command_table->command_table_size; index++)
    {
        if( (strncmp(command_table[index].command_name, command_name, sizeof(command_table[index].command_name) - 1) == 0 ) )
        {
            found = 1;
            func_retval = index;
        }

    }

    if(found == 0)
        func_retval = -1;

    return func_retval;
}




/***********************************************************
 * @brief  Static function to search for default commands
 * @param  *console       : reference to console handle
 * @param  *command_table : reference to command list table
 * @param  arg_count      : argument count
 * @param  **command_argv : argument variables
 * @retval uint8_t        : Success = 0, command not found
 *                                  = 1, command found
 ***********************************************************/
static uint8_t search_default_commands(cl_term_t *console, command_table_t *command_list, uint8_t arg_count, char **command_argv)
{

    uint8_t func_retval = 0;

    if( ( strcmp(command_argv[0], "term") ) == 0 )
    {
        terminal_commands(console, command_list, arg_count, command_argv);

        func_retval = 1;
    }
    else if( (strcmp(command_argv[0], "clear") ) == 0 )
    {

    }

    return func_retval;
}






/******************************************************************************/
/*                                                                            */
/*                         Console Functions                                  */
/*                                                                            */
/******************************************************************************/



/**************************************************************************
 * @brief  Constructor function to create console handle
 *         (Multiple Exit points)
 * @param  *console_ops : reference to console callback functions
 * @param  baudrate     : baudrate / speed of serial terminal
 * @param  buffer       : data / text buffer for serial terminal
 * @param  alloc_type   : handle object allocation type, static/dynamic
 * @retval cl_term_t   : Error = NULL, Success = console object handle.
 *                        exception(return to handle)
 *                        Exceptions, -1, -2, -3, -4 (see exception values)
 ***************************************************************************/
cl_term_t* console_open(console_ops_t *console_ops, uint32_t baudrate, void *buffer, console_alloc_type_t alloc_type)
{

    cl_term_t *console;

    uint8_t callback_retval = 0;

    if(buffer == NULL || alloc_type == 0 || alloc_type > 2 || console_ops == NULL)
    {
        return NULL;
    }
    else
    {
        /* configure Static allocation */
        if(alloc_type == CONSOLE_STATIC)
        {
            static cl_term_t static_console;

            console = &static_console;


            console->allocation_type = CONSOLE_STATIC;

        }
        else if(alloc_type == CONSOLE_DYNAMIC)
        {

            console = malloc(sizeof(cl_term_t));

            if(console == NULL)
                return NULL;

            memset(console, NULL, sizeof(cl_term_t));


            console->allocation_type = CONSOLE_DYNAMIC;

        }
        else
        {
            return NULL;
        }

        /* Configure input buffer */
        console->input_buffer = (void*)buffer;


        /* Configure Critical operations */
        console->console_commands = console_ops;


        /* Return exceptions in error condition */
        if(console->console_commands->open == NULL)
        {
            console->exception = CONSOLE_OPEN_CMD_ERROR;
        }
        else if(console->console_commands->print_char == NULL)
        {
            console->exception = CONSOLE_PRINTCHR_CMD_ERROR;
        }
        else if(console->console_commands->read_char == NULL)
        {
            console->exception = CONSOLE_READCHR_CMD_ERROR;
        }

        if(console->exception < 0)
            return NULL;

        /* Configure default operations */



        /* Call console open to start console, returns 0 as error */
        callback_retval = console->console_commands->open(baudrate);

        if(!callback_retval)
        {
            console->exception = CONSOLE_OPEN_CALLBACK_ERROR;

            return NULL;
        }
    }


    return console;
}




/******************************************************************
 * @brief  Function to print to serial terminal through call-backs
 * @param  *console       : reference to console handle
 * @param  string_input[] : data / text buffer for serial terminal
 * @retval int8_t         : Error = -5 (exception), Success = 0
 ******************************************************************/
int8_t console_print(cl_term_t *console, char string_input[])
{

    int8_t   func_retval   = 0;
    uint16_t string_length = 0;
    uint16_t index         = 0;

    if(console == NULL)
    {
        func_retval = CONSOLE_OBJ_NULL_ERROR;

    }
    else if(string_input == NULL)
    {
        console->exception = CONSOLE_PRINT_FUNC_ERROR;
    }
    else
    {
        string_length = strlen(string_input);

        /* Call callback function for print character */
        for(index = 0; index < string_length; index++)
        {
            if(string_input[index] == '\n')
            {
                console->console_commands->print_char('\r');
                console->console_commands->print_char(string_input[index]);
            }

            else
                console->console_commands->print_char(string_input[index]);
        }

        func_retval = 0;
    }

    return func_retval;

}




/*************************************************************
 * @brief  Constructor function to create command list object
 *         (Testing only static allocation)
 * @param  *console   : reference to console handle
 * @param  table_size : max number of entries
 * @retval int8_t     : Error   = -9, -10 (exception),
 *                      Success = command_table object
 *************************************************************/
command_table_t* create_command_list(cl_term_t *console, uint8_t table_size)
{

    command_table_t *command_list;

    static command_table_t command_table_static_alloc[MAX_TABLE_SIZE];

    if(console == NULL)
    {
        return NULL;
    }
    else if(table_size == 0)
    {
        throw_exception(console, CONSOLE_CMD_LIST_FUNC_ERROR);
    }
    else
    {
        if(console->allocation_type == CONSOLE_STATIC)
        {
            /* Allocate static memory */
            command_list = command_table_static_alloc;

            /* Set table size */
            command_list->command_table_size = table_size;

        }
        else if(console->allocation_type == CONSOLE_DYNAMIC)
        {

            /* Allocate dynamic memory */
            command_list = malloc( table_size * sizeof(command_table_t) );

            if(command_list == NULL)
            {
                console->exception = CONSOLE_CMD_LIST_DYN_ALLOC_ERROR;

                return NULL;
            }

            memset(command_list, NULL, ( sizeof(command_table_t) * table_size ) );

            /* Set table size */
            command_list->command_table_size = table_size;

        }
        else
        {
            throw_exception(console, CONSOLE_CMD_LIST_STA_ALLOC_ERROR);

            return NULL;

        }
    }

    return command_list;
}




/***************************************************************
 * @brief  Function to add commands to the command list table)
 * @param  *command_table : reference to command list table
 * @param  command_name[] : name of the user command
 * @param  (*command)     : reference to the call back function
 * @retval int8_t         : Error = -11 (exception),
 *                          Success = 0 (new entry),
 *                                  = 1 (entry exists)
 ***************************************************************/
int8_t add_command(command_table_t *command_table, char command_name[], int (*command)(int argc, char **argv))
{

    int8_t func_retval = 0;

    uint8_t index = 0;


    if(command_table == NULL)
    {
        func_retval = CONSOLE_CMD_LIST_OBJ_ERROR;
    }
    else if(command_name == NULL || command == NULL)
    {
        func_retval = CONSOLE_ADD_CMD_ERROR;
    }
    else
    {
        for(index=0; index < command_table->command_table_size; index++)
        {
            if( (strncmp(command_table[index].command_name, command_name, sizeof(command_table[index].command_name) - 1) == 0 ) )
            {
                func_retval = 1;

                break;
            }
            else if( (strncmp(command_table[index].command_name, "\0", sizeof(command_table[index].command_name)) == 0) )
            {
                /* Add entry */
                strncpy(command_table[index].command_name, command_name, strlen(command_name));

                command_table[index].func = command;

                func_retval = 0;

                break;
            }

        }
    }

    return func_retval;
}





/*******************************************************************
 * @brief  Function to start the console and print console info
 *         sets console begin status needed for exec commands to
 *         work.
 * @param  *console       : reference to console handle
 * @param  *command_table : reference to command list table
 * @retval int8_t         : Error = -6 (exception), Success = 0
 *******************************************************************/
int8_t console_begin(cl_term_t *console, command_table_t *command_table)
{

    int8_t func_retval = 0;

    if(console == NULL)
    {
        func_retval = CONSOLE_OBJ_NULL_ERROR;

    }
    else if(command_table == NULL)
    {
        /* Throw exception if command_list_create(...) is not called */
        throw_exception(console, CONSOLE_CMD_LIST_OBJ_ERROR);

    }
    else if(console->exception != CONSOLE_NO_EXCEPTION)
    {
        /* Throw exception if exception already exists */
        throw_exception(console, console->exception);

    }
    else
    {

        /* Set begin status */
        console->status.begin = 1;

        /* Set version status */
        console->version = CLTERM_VERSION;

        /* Clear Console Screen */
        console_print(console, CONSOLE_CLEAR_SCREEN);

        /* Enable Local Echo */
        console_print(console, CONSOLE_LOCAL_ECHO);

        /* Print Logo to console */
        console_logo(console);

        logo_header(console);

        console_print(console, "\n");

        func_retval = 0;
    }

    return func_retval;
}





/*****************************************************************
 * @brief  Function to start the console and print console info
 * @param  *console      : reference to console handle
 * @param  *input_length : length of input buffer to be filled
 * @retval int8_t        : Error = -7 (exception), Success = 0
 *****************************************************************/
int8_t console_get_string(cl_term_t *console, uint16_t input_length)
{

    int8_t func_retval = 0;

    char     char_input  = 0;
    char     next_1      = 0;
    char     next_2      = 0;
    uint16_t char_count  = 0;

    if(console == NULL)
    {
        func_retval = CONSOLE_OBJ_NULL_ERROR;
    }
    else if(input_length == 0)
    {
        throw_exception(console, CONSOLE_GET_STRING_FUNC_ERROR);
    }
    else
    {

        /* Set get_string call status as */
        console->status.get_input = 1;

        /* Clear input buffer before writing */
        memset(console->input_buffer, 0, input_length);

        /* Prompt sign */
        console_print(console, "\033[1;32m$>\033[0m");

        while(1)
        {
            char_input = console->console_commands->read_char();

            /* Carriage return and Backspace Processing */
            if(char_input == CARRIAGE_RETURN)
            {
                console->input_buffer[char_count] = '\0';

                /* Go to new line with carriage return after done entering the text */
                console->console_commands->print_char('\r');
                console->console_commands->print_char('\n');

                char_count = 0;

                break;
            }
            else if (char_input == BACKSPACE || char_input == ASCII_DELETE)
            {
                if(char_count <= 0)
                {
                    console_print(console, "\033[C");
                }
                else
                {
                    console->console_commands->print_char(' ');

                    console_print(console, "\033[D");

                    char_count--;
                }

            }
            else if (char_input == ASCII_ESCAPE)
            {
                next_1 = console->console_commands->read_char();
                next_2 = console->console_commands->read_char();

                /* Up, don't process UP key press */
                if(next_1 == 91 && next_2 == 65)
                {
                    console_print(console, "\033[B");
                    char_input = '\0';
                }
                /* Down, Don't process Down key press */
                else if(next_1 == 91 && next_2 == 66)
                {
                    console_print(console, "\033[A");
                    char_input = '\0';
                }

            }
            else
            {
                console->input_buffer[char_count++] = char_input;

                /* Buffer over flow check */
                if(char_count == input_length - 1)
                {
                    console->input_buffer[char_count] = '\0';

                    char_count = 0;

                    console_print(console, "\n");
                    console_print(console, "\n");

                    console_print(console, TERM_RED);
                    console_print(console, "Error: ");
                    console_print(console, ATTRIBUTES_OFF);
                    console_print(console, "Input Length Exceeded \n");

                    console_print(console, "\n");

                    break;
                }

            }

        }

    }

    return func_retval;
}





/*********************************************************************
 * @brief  Function to search and execute command entered by user,
 *         through serial terminal.
 *         Expects console begin_status set to 1 by console_begin(...)
 * @param  *console        : reference to console handle
 * @param  *command_list   : length of input buffer to be filled
 * @param  command_input[] : input buffer from get_string function
 * @retval int8_t          : Error   = -8 (exception),
 *                           Success = 1  (No input, bypass function)
 *                           Success = 0
 *********************************************************************/
int8_t console_exec_command(cl_term_t *console, command_table_t *command_list ,char command_input[])
{

    int8_t func_retval = 0;

    /* Command input string parsing */
    char   command_arguments[MAX_ARGUMENTS][MAX_ARG_LENGTH] = {0};
    char  *command_arguments_rows[MAX_ARGUMENTS]            = {0};
    char **command_argv;

    uint8_t index             = 0;

    uint8_t arg_count         = 0;  /*!< number of arguments entered by the user                */
    int8_t  search_retval     = 0;  /*!< return value of search command from command list table */
    uint8_t search_def_retval = 0;  /*!< return value of search from default terminal commands  */

    char *track_ptr;
    char *token;

    uint8_t token_length = 0;

    /* Check exception conditions */
    if(console == NULL)
    {
        func_retval = CONSOLE_OBJ_NULL_ERROR;
    }
    else if(console->exception != CONSOLE_NO_EXCEPTION)
    {

        /* throw exception if exception already exists */
        throw_exception(console, console->exception);

    }
    else if(console->status.begin == 0)
    {
        /* throw exception if control_begin(...) is not called */
        throw_exception(console, CONSOLE_BEGIN_ERROR);

    }
    else if(console->status.get_input == 0)
    {
        /* throw exception if console_get_string is not called */
        throw_exception(console, CONSOLE_GET_STRING_NOT_CALLED);

    }
    else if(command_input[0] == '\0' )
    {
        /* Bypass function */
        func_retval = 1;
    }
    else
    {

        /* Clear console get input status */
        console->status.get_input = 0;

        track_ptr = command_input;

        /* Tokenize command input */
        while( (token = api_strtok_r(track_ptr, " ", &track_ptr)) )
        {

            /* Check token length and truncate it for max token length */
            token_length = strlen(token);

            if(token_length > MAX_ARG_LENGTH)
                token_length = MAX_ARG_LENGTH - 1;

            /* Copy token */
            strncpy(command_arguments[index], token, token_length);

            index++;

            /*Check max arguments */
            if(index >= MAX_ARGUMENTS)
                break;

            token_length = 0;

        }

        /* Get argument count */
        arg_count = index;

        /* Map command argument buffer to command line friendly pointer to pointer variable */
        for(index = 0; index < arg_count; index++)
        {
            command_arguments_rows[index] = command_arguments[index];
        }

        command_argv = command_arguments_rows;


        /* Search for default commands */
        search_def_retval = search_default_commands(console, command_list, arg_count, command_argv);


        /* Search for commands in user command list if not default command */
        if(!search_def_retval)
        {

            /* Search command list for commands and execute command through call back */
            /* Command name = index 0 */
            search_retval = search_command(command_list, command_argv[0]);

            if(search_retval >= 0)
            {
                command_list[search_retval].func(arg_count, command_argv);
            }
            else
            {
                /* Print Command Not Found */
                console_print(console, "\n");

                console_print(console, TERM_RED);
                console_print(console, "Error: ");
                console_print(console, ATTRIBUTES_OFF);

                console_print(console, "Command Not Found \n");
                console_print(console, "\n");

                console_print(console, "Please check if command is added to the user command list \n");
                console_print(console, "\n");

                console_print(console, BOLD_ON);
                console_print(console, "Use 'term --list' to list user commands or,\n"
                                       "    'term --help' for help options.        \n");
                console_print(console, ATTRIBUTES_OFF);

                console_print(console, "\n");

            }
        }

    }

    return func_retval;
}





/*************************************************************
 * @brief  Function to update exception type.
 *         (Doesn't throw parent object exception)
 * @param  *console             : reference to console handle
 * @param  console_exceptions_t : exception type
 * @retval void                 : void
 *************************************************************/
void throw_exception(cl_term_t *console, console_exceptions_t exception)
{

    if(console->exception == CONSOLE_NO_EXCEPTION)
        console->exception = exception;

}




/************************************************************************************
 * @brief  Exception Handling and reporting function.
 *         (Doesn't handle parent object exception)
 * @param  *console             : reference to console handle
 * @param  exception_state      : exception handle state (hold/block or report only)
 * @retval console_exceptions_t : returns exception value in non block/hold state
 ************************************************************************************/
console_exceptions_t catch_exception(cl_term_t *console, exception_state_t exception_state)
{
    uint8_t hold = 0;

    console_exceptions_t exception = (console_exceptions_t) 0;

    if(console == NULL)
    {
        exception = CONSOLE_OBJ_NULL_ERROR;
    }
    else
    {
        exception = console->exception;

        /* Handle exception, print exception number and error message */
        switch(exception)
        {

        case CONSOLE_NO_EXCEPTION:


            break;

        case CONSOLE_BEGIN_ERROR:

            console_print(console, "ERROR: Console Begin \n");

            break;

        case CONSOLE_GET_STRING_FUNC_ERROR:

            console_print(console, "ERROR: Console Get String Function \n");

            break;

        case CONSOLE_EXEC_CMD_FUNC_ERROR:

            console_print(console, "ERROR: Console Execute Command Function \n");

            break;

        case CONSOLE_CMD_LIST_FUNC_ERROR:

            console_print(console, "ERROR: Command List Create \n");

            break;

        case  CONSOLE_CMD_LIST_STA_ALLOC_ERROR:

            console_print(console, "ERROR: Command List Static Allocation \n");

            break;

        case CONSOLE_CMD_LIST_DYN_ALLOC_ERROR:

            console_print(console, "ERROR: Command List Dynamic Allocation \n");

            break;


        case CONSOLE_CMD_LIST_OBJ_ERROR:

            console_print(console, "ERROR: Command List Object = NULL \n");

            break;


        case CONSOLE_GET_STRING_NOT_CALLED:

            console_print(console, "ERROR: console_get_string(...) not called before console_exec_command \n");

            break;


        default:

            console_print(console, "Error: Exception Unknown \n");

            break;

        }


        /* Get into blocking state after exception occurs */
        if(exception < 0)
        {
            hold = 1;
        }

        if(exception_state == EXCEPTION_HOLD_STATE)
            while(hold);

    }


    return exception;
}





