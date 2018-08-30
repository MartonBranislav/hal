#include "hal/gpio.h"
#include "hal/bsp.h"

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
//      hal_gpio_init_digital(HAL_GPIO_OUT, PORTG, PIN0);
//      hal_gpio_init_digital(HAL_GPIO_OUT, PORTG, PIN1);
//      hal_gpio_init_digital(HAL_GPIO_OUT, PORTA, PIN9);

//      hal_gpio_write(PORTG, PIN0, 0);
//      hal_gpio_write(PORTG, PIN1, 1);
//      hal_gpio_write(PORTA, PIN9, 1);

//      while(1)
//      {
//          hal_gpio_toggle(PORTG, PIN0);
//          hal_gpio_toggle(PORTG, PIN1);
//          hal_gpio_toggle(PORTA, PIN9);
//          Delay_ms(1000);
//      }
// }
