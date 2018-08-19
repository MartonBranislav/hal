#include "hal/bsp.h"
#include "hal/gpio.h"
#include "hal/spi.h"

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

mikrobus_pin_t _spi_ss_pin[_MIKROBUS_COUNT];
const spi_channel_t _spi_channel[_MIKROBUS_COUNT] = { 3, 3 };

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

bsp_err_t bsp_mikrobus_spi_open(mikrobus_t bus, mikrobus_pin_t ss, spi_config_t config)
{
    _spi_ss_pin[bus] = ss;
    bsp_mikrobus_set(bus, ss);
    if (spi_open(_spi_channel[bus], config))
        return BSP_ERROR_HAL;
    return BSP_ERR_OK;
}

bsp_err_t bsp_mikrobus_spi_close(mikrobus_t bus)
{
    bsp_mikrobus_rst(bus, _spi_ss_pin[bus]);
    if (spi_close(_spi_channel[bus]))
        return BSP_ERROR_HAL;
    return BSP_ERR_OK;
}

bsp_err_t bsp_mikrobus_spi_transfer(mikrobus_t bus, spi_transfer_block_t tb)
{
    bsp_mikrobus_rst(bus, _spi_ss_pin[bus]);
    if (spi_transfer(_spi_channel[bus], tb))
        return BSP_ERROR_HAL;
    bsp_mikrobus_set(bus, _spi_ss_pin[bus]);
    return BSP_ERR_OK;
}

