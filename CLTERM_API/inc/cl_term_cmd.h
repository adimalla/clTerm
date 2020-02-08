/**
 ******************************************************************************
 * @file    cl_term_cmd.h
 * @author  Aditya Mall,
 * @brief
 *
 *  Info    clTerm inbuilt/default commands header file
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


#ifndef CL_TERM_CMD_H_
#define CL_TERM_CMD_H_



/*
 * @brief Standard Headers
 */
#include "cl_term.h"



/******************************************************************************/
/*                                                                            */
/*                     Terminal Default Function Prototypes                   */
/*                                                                            */
/******************************************************************************/



/*********************************************************
 * @brief  Function to print clTerm logo on terminal
 * @param  *console : reference to console handle
 * @retval int8_t   : Error = 1 (exception), Success = 0
 ********************************************************/
int8_t console_logo(cl_term_t *console);



/***********************************************************
 * @brief  Function to print clTerm info header on terminal
 * @param  *console : reference to console handle
 * @retval int8_t   : Error = 1 (exception), Success = 0
 **********************************************************/
int8_t logo_header(cl_term_t *console);



/**********************************************************
 * @brief  Function to execute terminal default commands
 * @param  *console      : reference to console handle
 * @param  *command_list : reference to command list table
 * @param  argc          : argument count
 * @param  **argv        : reference to variable array
 * @retval uint8_t       : Error = 1, Success = 0
 *********************************************************/
uint8_t terminal_commands(cl_term_t *console, command_table_t *command_list, int argc, char **argv);




#endif /* CL_TERM_CMD_H_ */
