/**
 ******************************************************************************
 * @file    gpio_tm4c123gh6pm.c, file name will change
 * @author  Aditya Mall,
 * @brief   TM4C123GH6PM Device Peripheral Access Layer Header File.
 *
 *  This file contains:
 *              - Helper functions for Driver exposed API functions
 *              - Driver APIs, for GPIO
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
 * @brief Standard and Driver header files
 */
#include "gpio_tm4c123gh6pm.h"
#include <string.h>


/* Macros specific to source file */
#define GPIOA_BIT_POS 0
#define GPIOB_BIT_POS 1
#define GPIOC_BIT_POS 2
#define GPIOD_BIT_POS 3
#define GPIOE_BIT_POS 4
#define GPIOF_BIT_POS 5


/******************************************************************************/
/*                                                                            */
/*                         Driver Functions                                   */
/*                                                                            */
/******************************************************************************/


/*
 * @brief   helper function to enable GPIO Peripheral Clock (Blocks till peripheral is ready)
 * @param   *p_gpio_x : pointer to the GPIO port structure (gpio_port_t).
 * @retval  int8_t    : error = -1, success = bit position corresponding to GPIO port
 */
static int8_t gpio_clock_enable(gpio_port_t *p_gpio_x)
{

    int8_t   return_value  = 0;       /*!< Return value  of the function                      */
    sysctl_t *sys_clock    = SYSCTL;  /*!< Pointer to the Address of System Control Structure */

    /* Check for correct function parameter value */
    if(p_gpio_x == NULL)
    {
        return_value = -1;
    }
    else
    {
        /* @brief Enable Clock for GPIO ports with re initialization check  */

        if(p_gpio_x == GPIOA && !(sys_clock->RCGCGPIO & 0x01UL))
        {
            sys_clock->RCGCGPIO |= (0x01UL);

            /* Check if peripheral is ready before accessed by software (Poll) */
            while( !(sys_clock->PRGPIO & (0x01UL)) );

            return_value = (0x01UL);
        }
        else if(p_gpio_x == GPIOB && !( sys_clock->RCGCGPIO & (1 << GPIOB_BIT_POS) ))
        {
            sys_clock->RCGCGPIO |= (1 << GPIOB_BIT_POS);

            /* Check if peripheral is ready before accessed by software (Poll) */
            while( !(sys_clock->PRGPIO & (1 << GPIOB_BIT_POS)) );

            return_value = (1 << GPIOB_BIT_POS);
        }
        else if(p_gpio_x == GPIOC && !( sys_clock->RCGCGPIO & (1 << GPIOC_BIT_POS) ))
        {
            sys_clock->RCGCGPIO |= (1 << GPIOC_BIT_POS);

            /* Check if peripheral is ready before accessed by software (Poll) */
            while( !(sys_clock->PRGPIO & (1 << GPIOC_BIT_POS)) );

            return_value = (1 << GPIOC_BIT_POS);
        }
        else if(p_gpio_x == GPIOD && !( sys_clock->RCGCGPIO & (1 << GPIOD_BIT_POS) ))
        {
            sys_clock->RCGCGPIO |= (1 << GPIOD_BIT_POS);

            /* Check if peripheral is ready before accessed by software (Poll) */
            while( !(sys_clock->PRGPIO & (1 << GPIOD_BIT_POS)) );

            return_value = (1 << GPIOD_BIT_POS);
        }
        else if(p_gpio_x == GPIOE && !( sys_clock->RCGCGPIO & (1 << GPIOE_BIT_POS) ))
        {
            sys_clock->RCGCGPIO |= (1 << GPIOE_BIT_POS);

            /* Check if peripheral is ready before accessed by software (Poll) */
            while( !(sys_clock->PRGPIO & (1 << GPIOE_BIT_POS)) );

            return_value = (1 << GPIOE_BIT_POS);
        }
        else if(p_gpio_x == GPIOF && !( sys_clock->RCGCGPIO & (1 << GPIOF_BIT_POS) ))
        {
            sys_clock->RCGCGPIO |= (1 << GPIOF_BIT_POS);

            /* Check if peripheral is ready before accessed by software (Poll) */
            while( !(sys_clock->PRGPIO & (1 << GPIOF_BIT_POS)) );

            return_value = (1 << GPIOF_BIT_POS);
        }
    }

    return return_value;
}



/*
 * @brief   Intializes GPIO pin.
 * @param   *p_gpio_hanlde : pointer to the GPIO Handle structure (gpio_handle_t).
 * @retval  success = 0, error = -1
 */
int8_t gpio_init(gpio_handle_t *p_gpio_hanlde)
{

    uint8_t  drive_select      = 0;  /*!< Variable for selecting drive current values                */
    uint8_t  pupd_select       = 0;  /*!< Variable for selecting Pull-Up or Pull-Down configurations */
    uint8_t  gpio_pin_mode     = 0;  /*!< Variable for selecting Digital or Analog configurations    */
    int8_t   func_return_value = 0;  /*!< Return value of the gpio init function                     */
    int8_t   gpio_clock_retval = 0;  /*!< Return value of gpio clock enable function                 */

    /* Enable Respective GPIO Port Clock*/
    gpio_clock_retval = gpio_clock_enable(p_gpio_hanlde->p_gpio_x);

    /* error check gpio clock function and pin number entered by the user */
    if(gpio_clock_retval == -1 || p_gpio_hanlde->gpio_pin_config.pin_number > 8)
    {
        func_return_value = gpio_clock_retval;
    }
    else
    {
        /*
         * @brief Configure GPIO Pin Direction
         * @note  All configurations are done by simply left shifting value set in the gpiopinConfig structure by PIN NUMBER (Set by User)
         * @note  See Value of Switch cases in header file gpio_tm4c123gh6pm.h
         */
        p_gpio_hanlde->p_gpio_x->DIR |= (p_gpio_hanlde->gpio_pin_config.direction << p_gpio_hanlde->gpio_pin_config.pin_number);


        /* @brief Configure GPIO Pin Open Drain Select */
        p_gpio_hanlde->p_gpio_x->ODR |= (p_gpio_hanlde->gpio_pin_config.opendrain << p_gpio_hanlde->gpio_pin_config.pin_number);


        /* @brief Configure GPIO Pin Drive Select */
        drive_select = p_gpio_hanlde->gpio_pin_config.drive;

        switch(drive_select)
        {

        case DRIVE_2MA:
            p_gpio_hanlde->p_gpio_x->DR2R |= (1 << p_gpio_hanlde->gpio_pin_config.pin_number);
            break;

        case DRIVE_4MA:
            p_gpio_hanlde->p_gpio_x->DR4R |= (1 << p_gpio_hanlde->gpio_pin_config.pin_number);
            break;

        case DRIVE_8MA:
            p_gpio_hanlde->p_gpio_x->DR8R |= (1 << p_gpio_hanlde->gpio_pin_config.pin_number);
            break;

        default:
            break;

        }


        /* @brief Configure GPIO Pin Pull-Up and Pull-Down Select */
        pupd_select = p_gpio_hanlde->gpio_pin_config.pull_up_down;

        switch(pupd_select)
        {

        case NO_PULL_UPDOWN:
            break;

        case PULLUP_ENABLE:
            p_gpio_hanlde->p_gpio_x->PUR |= (1 << p_gpio_hanlde->gpio_pin_config.pin_number);
            break;

        case PULLDOWN_ENABLE:
            p_gpio_hanlde->p_gpio_x->PDR |= (1 << p_gpio_hanlde->gpio_pin_config.pin_number);
            break;

        default:
            break;

        }


        /* @brief GPIO Digital or Analog Register Mode Select  */
        gpio_pin_mode = p_gpio_hanlde->gpio_pin_config.pin_mode;

        switch(gpio_pin_mode)
        {

        case DIGITAL_ENABLE:
            /* Clear analog mode if before setting up digital */
            p_gpio_hanlde->p_gpio_x->AMSEL &= ~(1 << p_gpio_hanlde->gpio_pin_config.pin_number);
            p_gpio_hanlde->p_gpio_x->DEN   |= (1 << p_gpio_hanlde->gpio_pin_config.pin_number);

            break;

        case ANALOG_ENABLE:
            /* Clear digital mode before setting up analog */
            p_gpio_hanlde->p_gpio_x->DEN   &= ~(1 << p_gpio_hanlde->gpio_pin_config.pin_number);
            p_gpio_hanlde->p_gpio_x->AMSEL |= (1 << p_gpio_hanlde->gpio_pin_config.pin_number);

            break;

        default:
            break;

        }


        /*
         * @brief GPIO Port Control Register and GPIO Pin Alternate Function
         * @note  Values of PCTLVAL, see header file gpio_tm4c123gh6pm.h
         */
        if(p_gpio_hanlde->gpio_pin_config.alternate_function == ALTERNATE_FUNCTION_ENABLE)
        {

            p_gpio_hanlde->p_gpio_x->AFSEL |= (p_gpio_hanlde->gpio_pin_config.alternate_function << p_gpio_hanlde->gpio_pin_config.pin_number);

            p_gpio_hanlde->p_gpio_x->PCTL  |= (p_gpio_hanlde->gpio_pin_config.pctl_val << (4 * p_gpio_hanlde->gpio_pin_config.pin_number));

        }
    }

    return func_return_value;
}



/*
 * @brief   Read from GPIO pin
 * @param   *p_gpio_x   : pointer to the GPIO port structure (gpio_port_t).
 * @param   pin_number : GPIO Pin Number.
 * @retval  uint8_t   : Return value from the pin.
 */
uint8_t gpio_read_pin(gpio_port_t *p_gpio_x, uint8_t pin_number)
{

    uint8_t retVal = 0;                        /*!< Variable to store the return value of the pin                       */

    retVal = (p_gpio_x->DATA >> pin_number);   /*!< Shift value from the pin to LSB and mask it with 0xFF (Masking bit) */

    return retVal;
}



/*
 * @brief   Write to GPIO pin
 * @param   *p_gpio_x   : pointer to the GPIO port structure (gpio_port_t).
 * @param   pin_number : GPIO Pin Number
 * @bool    value     : Value to be written, 1 or 0.
 * @retval  None.
 */
void gpio_write_pin(gpio_port_t *p_gpio_x, uint8_t pin_number, bool value)
{

    if (value == ENABLE)
    {
        //p_gpio_x->DATA &= ~(1 << pin_number); /*!< WARNING : Momentarily becomes zero >*/
        p_gpio_x->DATA |= (1 << pin_number);   /*!< Set bit of the corresponding Pin Number   */
    }
    else if (value == DISABLE)
        p_gpio_x->DATA &= ~(1 << pin_number);  /*!< Clear bit of the corresponding Pin Number */

}



/*
 * @brief   Read from GPIO port (Blocking function)
 * @param   *p_gpio_x  : pointer to the GPIO port structure (gpio_port_t).
 * @retval  uint8_t  : Data from the port
 */
uint8_t gpio_read_port(gpio_port_t *p_gpio_x)
{

    uint8_t return_value = 0;                /*!< Variable to store the return value of the port */

    return_value = (p_gpio_x->DATA) & 0xFF;  /*!< Return Masked value of the data register       */

    return return_value;
}



/*
 * @brief   Write to GPIO port
 * @param   *p_gpio_x  : pointer to the GPIO port structure (gpio_port_t).
 * @param   value  : Data to be written to the port
 * @retval  None.
 */
void gpio_write_port(gpio_port_t *p_gpio_x, uint8_t value)
{

    p_gpio_x->DATA = value;  /*!< Write value directly to the Data Register */

}



#if 0
/*
 * @brief   Deinitialize GPIO pin.
 * @param   *p_gpio_hanlde : pointer to the GPIO Handle structure (gpio_handle_t).
 * @retval  None.
 */
void gpio_deinit(gpio_handle_t *p_gpio_hanlde)
{



}

/*
 * @brief   Configure GPIO Interrupt
 * @param   IRQNumber   : Interrupt Number
 * @param   IRQPriority : Interrupt Priority
 * @param   state       : Enable or Disable Interrupt
 * @retval  None.
 */
void GPIO_InterruptConfig(uint8_t IRQNumber, uint8_t IRQPriority, bool state)
{



}

/*
 * @brief   Configure GPIO Interrupt
 * @param   pin_number: GPIO Pin Number triggering the interrupt
 * @retval  None.
 */
void GPIO_InterruptHandling(uint8_t pin_number)
{



}
#endif

