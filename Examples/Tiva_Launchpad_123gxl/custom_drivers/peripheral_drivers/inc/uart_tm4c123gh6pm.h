/**
 ******************************************************************************
 * @file    uart_tm4c123gh6pm.h, file name will change
 * @author  Aditya Mall,
 * @brief   TM4C123GH6PM Device Peripheral Access Layer Header File.
 *
 *  This file contains:
 *
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2019 Aditya Mall, Hari Haran Krishnan </center></h2>
 *
 * TODO Add license, add your name as you make changes
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



#ifndef UART_TM4C123GH6PM_H_
#define UART_TM4C123GH6PM_H_


/*
 * @brief Standard Headers
 */
#include "mcu_tm4c123gh6pm.h"


/******************************************************************************/
/*                                                                            */
/*                Macros and constants for UART Initialization                */
/*                                                                            */
/******************************************************************************/


/* Word Length */
typedef enum uart_word_length
{
    FIVE_BITS,   /*!< UART Word length 5 bits (UARTLCRH) */
    SIX_BITS,    /*!< UART Word length 6 bits (UARTLCRH) */
    SEVEN_BITS,  /*!< UART Word length 7 bits (UARTLCRH) */
    EIGHT_BITS   /*!< UART Word length 8 bits (UARTLCRH) */

}uart_word_length_t;


/* UART FIFO Select */
typedef enum uart_fifo
{
    FIFO_DISABLE,  /*!< UART FIFO Disable (UARTLCRH) */
    FIFO_ENABLE    /*!< UART FIFO Enable  (UARTLCRH) */

}uart_fifo_t;


/* UART stop bits */
typedef enum uart_stop_bits
{
    ONE_STOP_BIT,  /*!< UART 1 stop bit  (UARTLCRH) */
    TWO_STOP_BIT,  /*!< UART 2 stop bits (UARTLCRH) */

}uart_stop_bits_t;


/* UART Parity Select */
typedef enum uart_parity
{
    PARITY_DISABLE,  /*!< UART parity disabled    (UARTLCRH) */
    PARITY_ODD,      /*!< UART Select Odd parity  (UARTLCRH) */
    PARITY_EVEN,     /*!< UART Select Even parity (UARTLCRH) */

}uart_parity_t;


/* UART clock source */
typedef enum uart_clock_source
{
    CLOCK_SYSTEM = 0,  /*!< Main Oscillator as clock source (UARTCC) */
    CLOCK_PIOSC  = 5,  /*!< Precision Internal Oscillator   (UARTCC) */

}uart_clock_source_t;


/* UART direction */
typedef enum uart_direction
{
    UART_TRANSCEIVER,  /*!< UART TX and RX both enabled (UARTCTL) */
    UART_TRANSMIT,     /*!< UART TX enabled             (UARTCTL) */
    UART_RECEIVE,      /*!< UART RX enabled             (UARTCTL) */
    UART_LOOPBACK      /*!< UART in Loopback mode       (UARTCTL) */

}uart_direction_t;


/* uart flow control */
typedef enum uart_flow_control
{
    UART_RTS = 1,  /*!< UART enable Request to clear (UARTCTL) */
    UART_CTS = 2   /*!< UART enable clear to send (UARTCTL)    */

}uart_flow_control_t;


/* UART FLags */
typedef enum uart_flags
{
    UART_CTS_FLAG      = 0x01,  /*!< UART CTS is set (UARTFF)         */
    UART_PERIPH_BUSY   = 0x08,  /*!< UART Peripheral is busy (UARTFF) */
    UART_RX_FIFO_EMPTY = 0x10,  /*!< UART RX FIFO is empty (UARTFF)   */
    UART_TX_FIFO_FULL  = 0x20,  /*!< UART TX FIFO is full (UARTFF)    */
    UART_RX_FIFO_FULL  = 0x40,  /*!< UART RX FIFO is full (UARTFF)    */
    UART_TX_FIFO_EMPTY = 0x80   /*!< UART TX FIFO is empty (UARTFF)   */

}uart_flags_t;



/******************************************************************************/
/*                                                                            */
/*                  Data Structures for UART COnfiguration                    */
/*                                                                            */
/******************************************************************************/


typedef struct uart_periph_config
{
   uint32_t            uart_baudrate;      /*!< UART set data Baudrate                                    */
   uart_word_length_t  word_length;        /*!< UART set data word length                                 */
   uart_fifo_t         uart_fifo;          /*!< UART FIFO selection, enable or disable FIFO               */
   uart_stop_bits_t    stop_bits;          /*!< UART set stop bits, 1 Stop or 2 Stop bits                 */
   uart_parity_t       uart_parity;        /*!< UART set parity bits                                      */
   uart_clock_source_t uart_clock_source;  /*!< UART set clock source, CLOCK_SYSTEM (Main) or CLOCK_PISOC */
   uart_direction_t    uart_direction;     /*!< UART direction, TXRX, TX, RX or Loopback                  */

   uart_flow_control_t flow_control;       /*!< Currently doesn't support */

}uart_periph_config_t;


typedef struct uart_handle
{
    uart_periph_t        *p_uart_x;    /*!< UART peripheral address                 */
    uart_periph_config_t uart_config;  /*!< UART peripheral configuration structure */

}uart_handle_t;



/******************************************************************************/
/*                                                                            */
/*                      Driver Function Prototypes                            */
/*                                                                            */
/******************************************************************************/


/*
 * @brief   Initializes UART
 * @param   *p_uart_hanlde : pointer to the uart handle structure
 * @retval  int8_t         : -1 = error, 0 = success
 */
int8_t uart_init(uart_handle_t *p_uart_handle);



/*
 * @brief   Write char data to UART
 * @param   *p_uart_x : UART port address
 * @param   data      : data to be written
 * @retval  None.
 */
void uart_putchar(uart_periph_t *p_uart_x, char data);



/*
 * @brief   Read char data from UART (Blocking Function)
 * @param   *p_uart_x : UART port address
 * @retval  char      : data read from UART
 */
char uart_getchar(uart_periph_t *p_uart_x);



/*
 * @brief   Write data stream to UART
 * @param   *p_uart_x  : UART port address
 * @param   const char : write buffer
 * @param   length     : length of data to be written
 * @retval  error = -1, success = 0
 */
int8_t uart_write(uart_periph_t *p_uart_x, const char *buffer, int16_t length);


int8_t uart_read(uart_periph_t *p_uart_x, char *buffer, int16_t length);


#endif
