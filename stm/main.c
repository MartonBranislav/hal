#include "gpio.h"
#include "bsp.h"

void main()
{
    bsp_mikrobus_init_digital(MIKROBUS_OUT, MIKROBUS_1, MIKROBUS_AN);
    bsp_mikrobus_init_digital(MIKROBUS_OUT, MIKROBUS_1, MIKROBUS_PWM);

    bsp_mikrobus_set(MIKROBUS_1, MIKROBUS_AN);
    bsp_mikrobus_rst(MIKROBUS_1, MIKROBUS_PWM);

    while(1)
    {
        bsp_mikrobus_toggle(MIKROBUS_1, MIKROBUS_AN);
        bsp_mikrobus_toggle(MIKROBUS_1, MIKROBUS_PWM);
        Delay_ms(200);
    }
}

// void main()
// {
// //  GPIO_Digital_Output(&GPIOD_BASE, _GPIO_PINMASK_0);
// //  GPIO_Digital_Output(&GPIOD_BASE, _GPIO_PINMASK_1);
// //  GPIO_Digital_Output(&GPIOD_BASE, _GPIO_PINMASK_2);
//      hal_gpio_init_digital(HAL_GPIO_OUT, PORTA, PIN0);
//      hal_gpio_init_digital(HAL_GPIO_OUT, PORTA, PIN9);
//      hal_gpio_init_digital(HAL_GPIO_OUT, PORTB, PIN0);
//      hal_gpio_init_digital(HAL_GPIO_OUT, PORTC, PIN0);
//      hal_gpio_init_digital(HAL_GPIO_OUT, PORTD, PIN9);
//      hal_gpio_init_digital(HAL_GPIO_OUT, PORTD, PIN0);
//      hal_gpio_init_digital(HAL_GPIO_OUT, PORTD, PIN1);
//      hal_gpio_init_digital(HAL_GPIO_OUT, PORTD, PIN2);

//      hal_gpio_write(PORTA, PIN0, 1);
//      hal_gpio_write(PORTA, PIN9, 1);
//      hal_gpio_write(PORTB, PIN0, 1);
//      hal_gpio_write(PORTC, PIN0, 1);
//      hal_gpio_write(PORTD, PIN9, 1);
//      hal_gpio_write(PORTD, PIN0, 1);
//      hal_gpio_write(PORTD, PIN1, 1);
//      hal_gpio_write(PORTD, PIN2, 1);

//      while(1)
//      {
//          hal_gpio_toggle(PORTA, PIN0);
//          hal_gpio_toggle(PORTA, PIN9);
//          hal_gpio_toggle(PORTB, PIN0);
//          hal_gpio_toggle(PORTC, PIN0);
//          hal_gpio_toggle(PORTD, PIN9);
//          hal_gpio_toggle(PORTD, PIN0);
//          hal_gpio_toggle(PORTD, PIN1);
//          hal_gpio_toggle(PORTD, PIN2);
//          Delay_ms(200);
//      }
// }

// st
// void SPIx_Init_Advanced(char clock_divider, long config, const Module_Struct *module);

// pic32
// void SPIx_Init_Advanced(unsigned master_mode, unsigned data_mode, unsigned clock_divider, unsigned slave_select, unsigned data_sample, unsigned clock_idle, unsigned edge);

