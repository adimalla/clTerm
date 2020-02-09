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



/*
 * @brief Standard Headers
 */
#include "mcu_tm4c123gh6pm.h"
#include "uart_tm4c123gh6pm.h"
#include <string.h>



/*
 * @brief UART Peripheral Clock Enable Macros
 */
#define UART0_ENABLE  ((uint8_t)0x01UL)
#define UART1_ENABLE  ((uint8_t)0x02UL)
#define UART2_ENABLE  ((uint8_t)0x04UL)
#define UART3_ENABLE  ((uint8_t)0x08UL)
#define UART4_ENABLE  ((uint8_t)0x10UL)
#define UART5_ENABLE  ((uint8_t)0x20UL)
#define UART6_ENABLE  ((uint8_t)0x40UL)
#define UART7_ENABLE  ((uint8_t)0x80UL)


/* UART Control register Bit position macros */





/******************************************************************************/
/*                                                                            */
/*                         Driver Functions                                   */
/*                                                                            */
/******************************************************************************/


/*
 * @brief   helper function to check UART port address
 * @param   *p_uart_x : pointer to the UART structure (uart_periph_t).
 * @retval  int8_t    : error = 1, success = 0
 */
static uint8_t uart_check_port_address(uart_periph_t *p_uart_x)
{
    uint8_t func_retval = 0;

    if( p_uart_x == UART0 || p_uart_x == UART1 || p_uart_x == UART2 || p_uart_x == UART4 || p_uart_x == UART4 || p_uart_x == UART5 || p_uart_x == UART6 || p_uart_x == UART7 )
    {
        func_retval = 0;
    }
    else
    {
        func_retval = 1;
    }

    return func_retval;
}

/*
 * @brief   helper function to enable UART Peripheral Clock (Blocks till peripheral is ready)
 * @param   *p_uart_x : pointer to the UART structure (uart_periph_t).
 * @retval  int8_t    : error = -1, success = 0
 */
static int8_t uart_clock_enable(uart_periph_t *p_uart_x)
{
    sysctl_t *p_sys_clock = SYSCTL;  /*!< Pointer to System Control Peripheral Structure */
    int8_t   func_retval = 0;        /*!< Return value of the function                   */

    /* Check for correct function parameter value */
    if(p_uart_x == NULL || uart_check_port_address(p_uart_x))
    {
        func_retval = -1;
    }
    else
    {
        /* Enable Clock for UART peripheral with re initialization check  */
        if( (p_uart_x == UART0) && !(p_sys_clock->RCGCUART & UART0_ENABLE) )
        {
            p_sys_clock->RCGCUART |= UART0_ENABLE;

            /* @brief check if UART peripheral is ready */
            while( !(p_sys_clock->PRUART & UART0_ENABLE) );
        }
        else if( (p_uart_x == UART1) && !(p_sys_clock->RCGCUART & UART1_ENABLE) )
        {
            p_sys_clock->RCGCUART |= UART1_ENABLE;

            /* @brief check if UART peripheral is ready */
            while( !(p_sys_clock->PRUART & UART1_ENABLE) );
        }
        else if( (p_uart_x == UART2) && !(p_sys_clock->RCGCUART & UART2_ENABLE) )
        {
            p_sys_clock->RCGCUART |= UART2_ENABLE;

            /* @brief check if UART peripheral is ready */
            while( !(p_sys_clock->PRUART & UART2_ENABLE) );
        }
        else if( (p_uart_x == UART3) && !( p_sys_clock->RCGCUART & UART3_ENABLE) )
        {
            p_sys_clock->RCGCUART |= UART3_ENABLE;

            /* @brief check if UART peripheral is ready */
            while( !(p_sys_clock->PRUART & UART3_ENABLE) );
        }
        else if( (p_uart_x == UART4) && !(p_sys_clock->RCGCUART & UART4_ENABLE) )
        {
            p_sys_clock->RCGCUART |= UART4_ENABLE;

            /* @brief check if UART peripheral is ready */
            while( !(p_sys_clock->PRUART & UART4_ENABLE) );
        }
        else if( (p_uart_x == UART5) && !(p_sys_clock->RCGCUART & UART5_ENABLE) )
        {
            p_sys_clock->RCGCUART |= UART5_ENABLE;

            /* @brief check if UART peripheral is ready */
            while( !(p_sys_clock->PRUART & UART1_ENABLE) );
        }
        else if( (p_uart_x == UART6) && !(p_sys_clock->RCGCUART & UART6_ENABLE) )
        {
            p_sys_clock->RCGCUART |= UART6_ENABLE;

            /* @brief check if UART peripheral is ready */
            while( !(p_sys_clock->PRUART & UART6_ENABLE) );
        }
        else if( (p_uart_x == UART7) && !(p_sys_clock->RCGCUART & UART7_ENABLE) )
        {
            p_sys_clock->RCGCUART |= UART7_ENABLE;

            /* @brief check if UART peripheral is ready */
            while( !(p_sys_clock->PRUART & UART7_ENABLE) );
        }

    }

    return func_retval;
}



static uint16_t get_system_clock_frequency()
{
    uint32_t rcc_value   = 0;
    uint16_t func_retval = 0;

    /* Left shift to LSB and get the starting 4 bits of LSB */
    rcc_value = (SYSCTL->RCC >> 23) & 0x0F;

    switch(rcc_value)
    {

    case 0x02:
        func_retval = 6667;
        break;

    case 0x03:
        func_retval = 5000;
        break;

    case 0x04:
        func_retval = 4000;
        break;

    case 0x0F:
        func_retval = 1250;
        break;

    }

    return func_retval;
}



/*
 * @brief   Initializes UART
 * @param   *p_uart_hanlde : pointer to the uart handle structure
 * @retval  int8_t         : -1 = error, 0 = success
 */
int8_t uart_init(uart_handle_t *p_uart_handle)
{
    int8_t func_retval       = 0;  /*!< Return value of uart init function         */
    int8_t uart_clock_retval = 0;  /*!< Return value of uart clock enable function */

    uint32_t  clock_frequency    = 0;
    uint16_t baudrate_calc       = 0;
    uint16_t baudrate_integer    = 0;
    uint16_t baudrate_fractional = 0;

    /* Enable UART peripheral clock */
    uart_clock_retval = uart_clock_enable(p_uart_handle->p_uart_x);

    /* Check for gpio clock enable error */
    if(uart_clock_retval == -1)
    {
        func_retval = uart_clock_retval;
    }
    else
    {
        /* Clear control register for safe programming */
        p_uart_handle->p_uart_x->CTL = 0;


        /* Configure UART Baudrate */
        clock_frequency = get_system_clock_frequency();

        baudrate_calc       = ( (clock_frequency * 10000 * 100) / (p_uart_handle->uart_config.uart_baudrate * 16) );
        baudrate_integer    = baudrate_calc / 100;
        baudrate_fractional = ( baudrate_calc % 100 ) * 64;
        baudrate_fractional = baudrate_fractional / 100;

        p_uart_handle->p_uart_x->IBRD = baudrate_integer;
        p_uart_handle->p_uart_x->FBRD = baudrate_fractional;


        /* Configure UART line control register */
        switch(p_uart_handle->uart_config.uart_fifo)
        {

        case FIFO_ENABLE:
            p_uart_handle->p_uart_x->LCRH |= (FIFO_ENABLE << 4);
            break;

        case FIFO_DISABLE:
            p_uart_handle->p_uart_x->LCRH &= ~(FIFO_ENABLE << 4);
            break;

        default:
            break;
        }


        /* Configure uart word length */
        switch(p_uart_handle->uart_config.word_length)
        {
        case FIVE_BITS:
            p_uart_handle->p_uart_x->LCRH &= ~(EIGHT_BITS << 5);
            break;

        case SIX_BITS:
            p_uart_handle->p_uart_x->LCRH |= (SIX_BITS << 5);
            break;

        case SEVEN_BITS:
            p_uart_handle->p_uart_x->LCRH |= (SEVEN_BITS << 5);
            break;

        case EIGHT_BITS:
            p_uart_handle->p_uart_x->LCRH |= (EIGHT_BITS << 5);
            break;
        }


        /* Select UART clock Source register */
        p_uart_handle->p_uart_x->CC |= p_uart_handle->uart_config.uart_clock_source;


        /* Configure UART control register TX, RX and LoopBack options */
        switch(p_uart_handle->uart_config.uart_direction)
        {
        case UART_TRANSCEIVER:
            p_uart_handle->p_uart_x->CTL |= (3 << 8);
            break;

        case UART_TRANSMIT:
            p_uart_handle->p_uart_x->CTL |= (1 << 8);
            break;

        case UART_RECEIVE:
            p_uart_handle->p_uart_x->CTL |= (1 << 9);
            break;

        case UART_LOOPBACK:
            p_uart_handle->p_uart_x->CTL |= (7 << 7);
            break;
        }

        /* Enable UART */
        p_uart_handle->p_uart_x->CTL |= 0x01;

    }

    return func_retval;
}



/*
 * @brief   Write char data to UART
 * @param   *p_uart_x : UART port address
 * @param   data      : data to be written
 * @retval  None.
 */
void uart_putchar(uart_periph_t *p_uart_x, char data)
{
    /* Put data in Transmit buffer/FIFO only when its empty, otherwise block */
    while(p_uart_x->FR & UART_TX_FIFO_FULL);

    p_uart_x->DR = data;

}



/*
 * @brief   Read char data from UART (Blocking Function)
 * @param   *p_uart_x : UART port address
 * @retval  char      : data read from UART
 */
char uart_getchar(uart_periph_t *p_uart_x)
{
    /* Block till the time there is no Data in Receive Buffer/FIFO */
    while(p_uart_x->FR & UART_RX_FIFO_EMPTY);

    /* Wrap data to 8 Bits */
    return p_uart_x->DR & 0xFF;

}


/*
 * @brief   Write data stream to UART
 * @param   *p_uart_x  : UART port address
 * @param   const char : write buffer
 * @param   length     : length of data to be written
 * @retval  error = -1, success = 0
 */
int8_t uart_write(uart_periph_t *p_uart_x, const char *buffer, int16_t length)
{
    int buffer_index = 0;
    int func_retval  = 0;

    /* error check function parameters */
    if(length < 0 || buffer == NULL)
    {
        func_retval = length;
    }
    else
    {
        for(buffer_index = 0; buffer_index < length; buffer_index++)
        {
            uart_putchar(p_uart_x, buffer[buffer_index]);
        }
    }

    return func_retval;
}



int8_t uart_read(uart_periph_t *p_uart_x, char *buffer, int16_t length)
{
    int buffer_index = 0;
    int func_retval  = 0;

    /* error check function parameters */
    if(length == -1 || buffer == NULL)
    {
        func_retval = length;
    }
    else
    {
        for(buffer_index = 0; buffer_index < length; buffer_index++)
        {
            while( (p_uart_x->FR & UART_RX_FIFO_EMPTY) && buffer_index < length);
            buffer[buffer_index] = p_uart_x->DR;
        }
    }

    return func_retval;

}

