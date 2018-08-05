#include "hal/bsp.h"
#include "hal/gpio.h"

#define _MIKROBUS_COUNT (2)

typedef struct
{
    hal_port_t port;
    hal_pin_t pin;
} bsp_gpio_t;

bsp_gpio_t _mikrobus_map[_MIKROBUS_COUNT][MIKROBUS_PIN_COUNT] = {
    /* MIKROBUS_1 */
    {
        {PORTB, PIN8}, /* MIKROBUS_AN */ 
        {PORTC, PIN1}, /* MIKROBUS_RST */ 
        {PORTC, PIN2}, /* MIKROBUS_CS */ 
        {PORTB, PIN8}, /* MIKROBUS_SCK */ 
        {PORTB, PIN8}, /* MIKROBUS_MISO */ 
        {PORTB, PIN8}, /* MIKROBUS_MOSI */ 
        {PORTD, PIN0}, /* MIKROBUS_PWM */ 
        {PORTB, PIN8}, /* MIKROBUS_INT */ 
        {PORTB, PIN8}, /* MIKROBUS_RX */ 
        {PORTB, PIN8}, /* MIKROBUS_TX */ 
        {PORTB, PIN8}, /* MIKROBUS_SCL */ 
        {PORTB, PIN8}  /* MIKROBUS_SDA */ 
    },
    /* MIKROBUS_2 */
    {
        {PORTB, PIN8}, /* MIKROBUS_AN */ 
        {PORTC, PIN1}, /* MIKROBUS_RST */ 
        {PORTC, PIN2}, /* MIKROBUS_CS */ 
        {PORTB, PIN8}, /* MIKROBUS_SCK */ 
        {PORTB, PIN8}, /* MIKROBUS_MISO */ 
        {PORTB, PIN8}, /* MIKROBUS_MOSI */ 
        {PORTD, PIN0}, /* MIKROBUS_PWM */ 
        {PORTB, PIN8}, /* MIKROBUS_INT */ 
        {PORTB, PIN8}, /* MIKROBUS_RX */ 
        {PORTB, PIN8}, /* MIKROBUS_TX */ 
        {PORTB, PIN8}, /* MIKROBUS_SCL */ 
        {PORTB, PIN8}  /* MIKROBUS_SDA */ 
    }
};

bsp_err_t bsp_mikrobus_init_digital(mikrobus_dir_t dir, mikrobus_t bus, mikrobus_pin_t pin)
{
    bsp_gpio_t *pinout = &_mikrobus_map[bus][pin];

    if (bus > _MIKROBUS_COUNT - 1)
        return BSP_ERROR_INVALID_PIN;
    if (pin > MIKROBUS_PIN_COUNT - 1)
        return BSP_ERROR_INVALID_PIN;

    if (hal_gpio_init_digital(dir, pinout->port, pinout->pin) != HAL_ERR_OK)
        return BSP_ERROR_HAL;

    return BSP_ERR_OK;
}

bsp_err_t bsp_mikrobus_set(mikrobus_t bus, mikrobus_pin_t pin)
{
    bsp_gpio_t *pinout = &_mikrobus_map[bus][pin];
    if (hal_gpio_write(pinout->port, pinout->pin, HAL_STATE_HIGH) != HAL_ERR_OK)
        return BSP_ERROR_HAL;
    return BSP_ERR_OK;
}

bsp_err_t bsp_mikrobus_rst(mikrobus_t bus, mikrobus_pin_t pin)
{
    bsp_gpio_t *pinout = &_mikrobus_map[bus][pin];
    if (hal_gpio_write(pinout->port, pinout->pin, HAL_STATE_LOW) != HAL_ERR_OK)
        return BSP_ERROR_HAL;
    return BSP_ERR_OK;
}

bsp_err_t bsp_mikrobus_toggle(mikrobus_t bus, mikrobus_pin_t pin)
{
    bsp_gpio_t *pinout = &_mikrobus_map[bus][pin];
    if (hal_gpio_toggle(pinout->port, pinout->pin) != HAL_ERR_OK)
        return BSP_ERROR_HAL;
}

// bsp_err_t bsp_uart_write(bsp_uart_channel_t channel, uint8_t data)
// {
//     // channel -> bus, pin.
//     bsp_gpio_t *pinout = &_mikrobus_map[bus][pin];
//     hal_uart_module_t module = hal_uart_get_module(pinout->port, pinout->pin);
//     hal_uart_write(module, data);
// }

// bsp_err_t bsp_uart_read(bsp_uart_channel_t channel, uint8_t *data)
// {

// }
