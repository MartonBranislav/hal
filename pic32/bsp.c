#include "bsp.h"
#include "gpio.h"
#define MIKROBUS_COUNT (2)

typedef struct
{
    hal_port_t port;
    hal_pin_t pin;
} bsp_gpio_t;

bsp_gpio_t _mikrobus_map[MIKROBUS_COUNT][MIKROBUS_PIN_COUNT] = {
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

void bsp_mikrobus_init_digital(mikrobus_dir_t dir, mikrobus_t bus, mikrobus_pin_t pin)
{
    bsp_gpio_t *pinout = &_mikrobus_map[bus][pin];
    if (bus > MIKROBUS_COUNT - 1)
        return;
    if (pin > MIKROBUS_PIN_COUNT - 1)
        return;
    hal_gpio_init_digital(dir, pinout->port, pinout->pin);
}

void bsp_mikrobus_set(mikrobus_t bus, mikrobus_pin_t pin)
{
    bsp_gpio_t *pinout = &_mikrobus_map[bus][pin];
    hal_gpio_write(pinout->port, pinout->pin, 1);
}

void bsp_mikrobus_rst(mikrobus_t bus, mikrobus_pin_t pin)
{
    bsp_gpio_t *pinout = &_mikrobus_map[bus][pin];
    hal_gpio_write(pinout->port, pinout->pin, 0);
}

void bsp_mikrobus_toggle(mikrobus_t bus, mikrobus_pin_t pin)
{
    bsp_gpio_t *pinout = &_mikrobus_map[bus][pin];
    hal_gpio_toggle(pinout->port, pinout->pin);
}
