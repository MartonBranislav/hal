#ifndef _GPIO_H
#define _GPIO_H

#define PORTA 0
#define PORTB 1
#define PORTC 2
#define PORTD 3
#define PORTE 4
#define PORTF 5
#define PORTG 6

#define PIN0 0
#define PIN1 1
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN6 6
#define PIN7 7
#define PIN8 8
#define PIN9 9
#define PIN10 10
#define PIN11 11
#define PIN12 12
#define PIN13 13
#define PIN14 14
#define PIN15 15

#include "hal.h"

typedef void(*hal_gpio_callback_t)();


/**
 * GPIO initialization function.
 */
hal_err_t hal_gpio_init_digital(hal_gpio_direction_t direction, hal_port_t port, hal_pin_t pin);

/**
 * Read GPIO pin.
 * @param[in] port Port.
 * @param[in] pin Pin.
 * @param[out] state Variable to store state on input pin.
 * @returns Error code.
 */
hal_err_t hal_gpio_read(hal_port_t port, hal_pin_t pin, uint8_t *state);

/**
 * Write GPIO pin.
 * @param[in] port Port.
 * @param[in] pin Pin.
 * @param[in] state Value to set output pin.
 * @returns Error code.
 */
hal_err_t hal_gpio_write(hal_port_t port, hal_pin_t pin, uint8_t state);

hal_err_t hal_gpio_register_write(uint32_t address, uint32_t value);
hal_err_t hal_gpio_register_read(uint32_t address, uint32_t *value);

hal_err_t hal_gpio_register_callback(hal_gpio_callback_t *callback);

hal_err_t hal_gpio_toggle(hal_port_t port, hal_pin_t pin);

#endif // _GPIO_H
