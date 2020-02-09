/**
 ******************************************************************************
 * @file    cl_term_config.h
 * @author  Aditya Mall,
 * @brief
 *
 *  Info    clTerm config file
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


#ifndef CL_TERM_CONFIG_H_
#define CL_TERM_CONFIG_H_




/******************************************************************************/
/*                                                                            */
/*                          Macros and Defines                                */
/*                                                                            */
/******************************************************************************/


/* clTerm Utility defines */
#define CLTERM_VERSION 1


/* Input buffer defines */
#define MAX_INPUT_SIZE  40
#define MAX_ARGUMENTS   10
#define MAX_ARG_LENGTH  20


/* Command list table defines */
#define MAX_TABLE_SIZE  20
#define CMD_NAME_SIZE   15


/* VT100 compatible terminal defines */

/* Attributes */
#define CONSOLE_CLEAR_SCREEN  "\033[2J\033[H"
#define CONSOLE_LOCAL_ECHO    "\033[12l"
#define CONSOLE_EOL           "\r\n"
#define BOLD_ON               "\033[;1m"
#define ATTRIBUTES_OFF        "\033[0m"

/* Text Colors */
#define TERM_RED "\033[31;1m"



#endif /* CL_TERM_CONFIG_H_ */
