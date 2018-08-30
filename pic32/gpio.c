#include "hal/gpio.h"

typedef struct
{
    uint32_t reg;
    uint32_t clr;
    uint32_t set;
    uint32_t inv;
} gpio_reg_map_t;

const void* TRISREGS[7] = {
    0xBF886000, // Port A
    0xBF886040, // Port B
    0xBF886080, // Port C
    0xBF8860C0, // Port D
    0xBF886100, // Port E
    0xBF886140, // Port F
    0xBF886180  // Port G
};

const void* PORTREGS[7] = {
    0xBF886010, // Port A
    0xBF886050, // Port B
    0xBF886090, // Port C
    0xBF8860D0, // Port D
    0xBF886110, // Port E
    0xBF886140, // Port F
    0xBF886180  // Port G
};

const void* LATREGS[7] = {
    0xBF886020, // Port A
    0xBF886060, // Port B
    0xBF8860A0, // Port C
    0xBF8860E0, // Port D
    0xBF886120, // Port E
    0xBF886160, // Port F
    0xBF8861A0  // Port G
};

static void _set_direction(gpio_reg_map_t *regs, hal_gpio_direction_t direction, hal_pin_t pin)
{
    if (direction == HAL_GPIO_OUT)
        regs->CLR = 0x0001 << pin;
    else
        regs->SET = 0x0001 << pin;
}

static void _toggle(gpio_reg_map_t *regs, hal_pin_t pin)
{
    // asm nop;
    regs->INV = 0x0001 << pin;
}

hal_err_t hal_gpio_init_digital(hal_gpio_direction_t direction, hal_port_t port, hal_pin_t pin)
{
    if (port == PORTB)
        AD1PCFG |= (unsigned long)0x01 << pin;

    _set_direction((gpio_reg_map_t*)TRISREGS[port], direction, pin);
    return HAL_ERR_OK;
}

hal_err_t hal_gpio_toggle(hal_port_t port, hal_pin_t pin)
{
    _toggle((gpio_reg_map_t*)LATREGS[port], pin);
    return HAL_ERR_OK;
}

static void _write(gpio_reg_map_t *reg, hal_pin_t pin, uint8_t state)
{
    if (state)
        reg->SET = 0x0001 << pin;
    else
        reg->CLR = 0x0001 << pin;
}

hal_err_t hal_gpio_write(hal_port_t port, hal_pin_t pin, uint8_t state)
{
    _write((gpio_reg_map_t*)LATREGS[port], pin, state);
    return HAL_ERR_OK;
}

typedef struct
{
    uint32_t Direction;
    uint32_t Clear;
    uint32_t Out;
    uint32_t In;
} volatile * const Gpio_MapPtr;