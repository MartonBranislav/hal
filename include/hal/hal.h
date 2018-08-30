#ifndef _HAL_H
#define _HAL_H

#include <stdint.h>

typedef enum
{
    HAL_ERR_OK = 0,
    HAL_ERR_INVALID_INPUT_ARGUMENTS
} hal_err_t;

typedef uint8_t hal_port_t;
typedef uint8_t hal_pin_t;

typedef enum
{
    HAL_GPIO_IN = 0,
    HAL_GPIO_OUT = 1
} hal_gpio_direction_t;

typedef enum
{
    HAL_STATE_LOW = 0,
    HAL_STATE_HIGH
} hal_state_t;

#endif // _HAL_H