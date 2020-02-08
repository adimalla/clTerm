/**
 ******************************************************************************
 * @file    cl_term_cmd.c
 * @author  Aditya Mall,
 * @brief
 *
 *  Info   clTerm inbuilt/default commands source file
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

#include <stdint.h>
#include <string.h>
#include "cl_term_cmd.h"







/******************************************************************************/
/*                                                                            */
/*                              Private Functions                             */
/*                                                                            */
/******************************************************************************/





/*********************************************************
 * @brief  Static function to print terminal help details
 * @param  *console : reference to console handle
 * @retval void     : void
 *********************************************************/
static void term_help(cl_term_t *console)
{
    console_print(console,"clTerm: Portable Serial Terminal Utility \n");
    console_print(console,"clTerm version 1.0 (c)2020, Aditya Mall. \n");
    console_print(console,"License: MIT.                            \n");
    console_print(console,"\n");
    console_print(console,"\n");

    console_print(console,"Usage: term [options] \n");
    console_print(console,"\n");
    console_print(console,"\n");

    console_print(console,"options:- \n");
    console_print(console,"\n");

    console_print(console,"-i,--info : show details about using the utility API.  \n");
    console_print(console,"-l,--list : list the available commands added by user. \n");
    console_print(console,"-h,--help : show utility help.                         \n");
    console_print(console,"\n");

    console_print(console,"Visit: github.com/adimalla/clTerm for more details.\n");

}



/*********************************************************
 * @brief  Static function to print terminal info details
 * @param  *console : reference to console handle
 * @retval void     : void
 *********************************************************/
static void term_info(cl_term_t *console)
{

    console_logo(console);

    console_print(console, "Info:- \n");
    console_print(console,"\n");

    console_print(console,"clTerm is a minimal implementation of a portable serial,    \n"
                  "terminal utility, which allows users to add custom,         \n"
                  "'command line argument' based commands to their application.\n");

    console_print(console,"\n");

    console_print(console,"clTerm can be ported to any hardware that supports serial,\n"
                  "communication protocols, it is implemented as an API,     \n"
                  "this allows user to link user defined serial peripheral,  \n"
                  "read and write functions and add custom commands which,   \n"
                  "can have C command line arguments like functionalities.   \n");

    console_print(console,"\n");

    console_print(console,"For more details please visit: github.com/adimalla/clTerm \n");
    console_print(console,"\n");
    console_print(console,"email: aditya.mall1990@gmail.com,\n"
                          "       aditya.mall@mavs.uta.edu. \n");

    console_print(console,"\n");

    console_print(console,"clTerm version 1.0 (c)2020, Aditya Mall. \n");
    console_print(console,"License: MIT.                            \n");
    console_print(console,"\n");

}




/*************************************************
 * @brief  Static function to print command list
 * @param  *console : reference to console handle
 * @param  *table   : reference to console handle
 * @retval void     : void
 *************************************************/
static void term_list(cl_term_t *console, command_table_t *table)
{
    uint8_t index = 0;

    console_print(console, "Command \n");

    for(index = 0; index < table->command_table_size; index++)
    {

        console_print(console, table[index].command_name);
        console_print(console, "\n");

        if(strncmp(table[index].command_name, "\0", sizeof(table[index].command_name)) == 0)
            break;

    }

}





/******************************************************************************/
/*                                                                            */
/*                        Terminal Default Functions                          */
/*                                                                            */
/******************************************************************************/



/*********************************************************
 * @brief  Function to print clTerm logo on terminal
 * @param  *console : reference to console handle
 * @retval int8_t   : Error = 1 (exception), Success = 0
 ********************************************************/
int8_t console_logo(cl_term_t *console)
{

    int8_t func_retval = 0;

    if(console == NULL)
    {
        func_retval = 1;
    }
    else
    {
        console_print(console,"\n");

        console_print(console, "               88888888888       8888888b.                \n");
        console_print(console, "  d8888p  888      888   .d88b.  888   d88  88888b.d88b.  \n");
        console_print(console, " d8p      888      888  d8P  Y8b 8888888P   888  888  88b \n");
        console_print(console, " 888      888      888  88888888 888 T88b   888  888  888 \n");
        console_print(console, " Y8b.     888      888  Y8b.     888  T88b  888  888  888 \n");
        console_print(console, "  Y8888b  88888888 888   Y8888b  888   T88b 888  888  888 \n");

        console_print(console,"\n");
        console_print(console,"           clTerm, Portable Serial Terminal Utility        \n");
        console_print(console,"\n");

    }

    return func_retval;
}





/***********************************************************
 * @brief  Function to print clTerm info header on terminal
 * @param  *console : reference to console handle
 * @retval int8_t   : Error = 1 (exception), Success = 0
 **********************************************************/
int8_t logo_header(cl_term_t *console)
{


    int8_t func_retval = 0;

    if(console == NULL)
    {
        func_retval = 1;
    }
    else
    {

        console_print(console,"---------------------------------------------------------  \n");

        console_print(console,"clTerm, version: 1.0 (c)2020, Aditya Mall. \n");
        console_print(console,"License: MIT.                              \n");
        console_print(console,"\n");

        console_print(console,"Use 'term --help' to see usage. \n");
        console_print(console,"\n");

        console_print(console,"Visit: github.com/adimalla/clTerm for more details.\n");

        console_print(console,"---------------------------------------------------------  \n");
        console_print(console,"\n");
    }

    return func_retval;
}





/**********************************************************
 * @brief  Function to execute terminal default commands
 * @param  *console      : reference to console handle
 * @param  *command_list : reference to command list table
 * @param  argc          : argument count
 * @param  **argv        : reference to variable array
 * @retval uint8_t       : Error = 1, Success = 0
 *********************************************************/
uint8_t terminal_commands(cl_term_t *console, command_table_t *command_list, int argc, char **argv)
{

    uint8_t index = 0;
    uint8_t count = 0;

    uint8_t func_retval = 0;

    if(console == NULL)
    {
        func_retval = 1;
    }
    else
    {

        count = argc;

        console_print(console,"\n");

        /* Check for number of arguments */
        if(count < 2)
        {
            console_print(console,"Error: No argument given.\n");

            console_print(console,"\n");

            console_print(console,"Use 'term --help' to see usage.\n");
        }
        else if(count > 2)
        {
            console_print(console,"Error: Commands expects only 1 argument.\n");

            console_print(console,"\n");

            console_print(console,"Use 'term --help' to see usage.\n");
        }
        else
        {
            /* Check for help command and execute it */
            if( (strcmp(argv[index + 1], "--help") == 0) || (strcmp(argv[index + 1], "-h") == 0) )
            {

                term_help(console);

            }
            /* Check for info command and execute it */
            else if( strcmp(argv[index + 1], "--info") == 0 || (strcmp(argv[index + 1], "-i") == 0) )
            {

                term_info(console);

            }
            /* Check for list command and execute it */
            else if( strcmp(argv[index + 1], "--list") == 0 || (strcmp(argv[index + 1], "-l") == 0) )
            {

                term_list(console, command_list);

            }
            else
            {
                /* Report wrong argument entered to terminal */

                console_print(console,"Wrong argument entered.\n");

                console_print(console,"\n");

                console_print(console,"Use 'term --help' to see usage.\n");

            }

        }

        console_print(console,"\n");

    }

    return func_retval;
}








