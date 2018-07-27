#include "gpio.h"

typedef struct
{
    uint32_t PORT;
    uint32_t CLR;
    uint32_t SET;
    uint32_t INV;
} REGS;

const void* TRISREGS[7] = {
    0xBF886000, // A
    0xBF886040, // B
    0xBF886080, // C
    0xBF8860C0, // D
    0xBF886100, // E
    0xBF886140, // F
    0xBF886180 // G
};

const void* PORTREGS[7] = {
    0xBF886010, // A
    0xBF886050, // B
    0xBF886090, // C
    0xBF8860D0, // D
    0xBF886110, // E
    0xBF886140, // F
    0xBF886180 // G
};

const void* LATREGS[7] = {
    0xBF886020, // A
    0xBF886060, // B
    0xBF8860A0, // C
    0xBF8860E0, // D
    0xBF886120, // E
    0xBF886160, // F
    0xBF8861A0 // G
};

// TRISREG* TRISREGS[7];
// TRISREGS[0] = (TRISREG*)0xBF886000; // A
// TRISREGS[1] = (TRISREG*)0xBF886000; // B
// TRISREGS[2] = (TRISREG*)0xBF886000; // C
// TRISREGS[3] = (TRISREG*)0xBF886000; // D
// TRISREGS[4] = (TRISREG*)0xBF886000; // E
// TRISREGS[5] = (TRISREG*)0xBF886140; // F
// TRISREGS[6] = (TRISREG*)0xBF886180; // G
//static TRISREG *TRISAREG;

void set_direction(REGS *regs, hal_gpio_direction_t direction, hal_pin_t pin)
{
    if (direction == HAL_GPIO_OUT)
        regs->CLR = 0x0001 << pin;
    else
        regs->SET = 0x0001 << pin;
}

void toggle(REGS *regs, hal_pin_t pin)
{
    asm nop;
    regs->INV = 0x0001 << pin;
}

hal_err_t hal_gpio_init_digital(hal_gpio_direction_t direction, hal_port_t port, hal_pin_t pin)
{
    if (port == PORTB)
        AD1PCFG |= (unsigned long)0x01 << pin;

    set_direction((REGS*)TRISREGS[port], direction, pin);
    return HAL_ERR_OK;
}

hal_err_t hal_gpio_toggle(hal_port_t port, hal_pin_t pin)
{
    toggle((REGS*)LATREGS[port], pin);
    return HAL_ERR_OK;
}

void write(REGS *reg, hal_pin_t pin, uint8_t state)
{
    if (state)
        reg->SET = 0x0001 << pin;
    else
        reg->CLR = 0x0001 << pin;
}

hal_err_t hal_gpio_write(hal_port_t port, hal_pin_t pin, uint8_t state)
{
    write((REGS*)LATREGS[port], pin, state);
    return HAL_ERR_OK;
}