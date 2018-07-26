#include "gpio.h"

void main()
{
     hal_gpio_init_digital(HAL_GPIO_OUT, PORTG, PIN0);
     hal_gpio_init_digital(HAL_GPIO_OUT, PORTG, PIN1);
     hal_gpio_init_digital(HAL_GPIO_OUT, PORTA, PIN9);
     
     hal_gpio_write(PORTG, PIN0, 0);
     hal_gpio_write(PORTG, PIN1, 1);
     hal_gpio_write(PORTA, PIN9, 1);

     while(1)
     {
         hal_gpio_toggle(PORTG, PIN0);
         hal_gpio_toggle(PORTG, PIN1);
         hal_gpio_toggle(PORTA, PIN9);
         Delay_ms(200);
     }
}