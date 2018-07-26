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

#include <stdint.h>

typedef enum
{
    HAL_ERR_OK = 0,
    HAL_ERR_INVALID_INPUT_ARGUMENTS,
} hal_err_t;

typedef uint8_t hal_port_t;
typedef uint8_t hal_pin_t;

typedef enum
{
    HAL_GPIO_IN = 0,
    HAL_GPIO_OUT = 1
} hal_gpio_direction_t;


// hal_err_t hal_gpio_init_analog(hal_port_t port, hal_pin_t pin);
hal_err_t hal_gpio_init_digital(hal_gpio_direction_t direction, hal_port_t port, hal_pin_t pin);
hal_err_t hal_gpio_read(hal_port_t port, hal_pin_t pin, uint8_t *state);
hal_err_t hal_gpio_write(hal_port_t port, hal_pin_t pin, uint8_t state);
hal_err_t hal_gpio_toggle(hal_port_t port, hal_pin_t pin);

// hal_err_t hal_gpio_set(hal_port_t port, hal_pin_t pin);
// hal_err_t hal_gpio_rst(hal_port_t port, hal_pin_t pin);
