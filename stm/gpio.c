#include "hal/gpio.h"

#define GPIO_PORT_COUNT (5)

typedef struct
{
    uint32_t crl;
    uint32_t crh;
    uint32_t idr;
    uint32_t odr;
    uint32_t bsrr;
    uint32_t brr;
} gpio_reg_map_t;



const void* gpio_port_addr[GPIO_PORT_COUNT] = {
    0x40010800, /* Port A */
    0x40010C00, /* Port B */
    0x40011000, /* Port C */
    0x40011400, /* Port D */
    0x40011800  /* Port E */
};

hal_err_t _write(gpio_reg_map_t *base, hal_pin_t pin, uint8_t state)
{
    if (state)
        base->bsrr = (0x00000001 << pin);
    else
        base->bsrr = (0x00010000 << pin);
    return HAL_ERR_OK;
}

uint32_t _read(gpio_reg_map_t *base, hal_pin_t pin)
{
    return base->idr & (0x00000001 << pin);
}

/*
void GPIO_Clk_Enable(unsigned long *gpio_port){
  unsigned long prt, pos;
  prt = (unsigned long)gpio_port & 0xFFFFFC00;
  pos = 0;
  switch (prt){
    case _GPIOA_BASE_ADDR: pos = 0x4; break;
    case _GPIOB_BASE_ADDR: pos = 0x8; break;
    case _GPIOC_BASE_ADDR: pos = 0x10; break;
    case _GPIOD_BASE_ADDR: pos = 0x20; break;
    case _GPIOE_BASE_ADDR: pos = 0x40; break;
    case _GPIOF_BASE_ADDR: pos = 0x80; break;
    case _GPIOG_BASE_ADDR: pos = 0x100; break;
  }

  RCC_APB2ENR |= pos;
}
*/
hal_err_t hal_gpio_init_digital(hal_gpio_direction_t direction, hal_port_t port, hal_pin_t pin)
{

    uint32_t reg_mask = 0x0000000F;
    uint32_t val = 0;
    uint8_t shf = 0;
    uint32_t reg_val = 0;
    gpio_reg_map_t* base = (gpio_reg_map_t*)gpio_port_addr[port];
    reg_val = direction ? 0x00000003 : 0x00000004;
    GPIO_Clk_Enable((void*)base);
    if (pin > 7)
    {
        shf = ((pin % 8) * 4);
        reg_mask <<= shf;
        val = reg_val << shf;
        base->crh = (base->crh & ~reg_mask) | val;
    }
    else
    {
        reg_mask <<= pin * 4;
        val = reg_val << (pin * 4);
        base->crl = (base->crl & ~reg_mask) | val;
    }
}

hal_err_t hal_gpio_write(hal_port_t port, hal_pin_t pin, uint8_t state)
{
    _write((gpio_reg_map_t*)gpio_port_addr[port], pin, state);
    return HAL_ERR_OK;
}

hal_err_t hal_gpio_read(hal_port_t port, hal_pin_t pin, uint8_t *state)
{
    *state = _read((gpio_reg_map_t*)gpio_port_addr[port], pin);
}

hal_err_t hal_gpio_toggle(hal_port_t port, hal_pin_t pin)
{
    uint32_t state = _read((gpio_reg_map_t*)gpio_port_addr[port], pin);
    _write((gpio_reg_map_t*)gpio_port_addr[port], pin, state ? 0 : 1);
    return HAL_ERR_OK;
}

// void GPIO_Digital_Output(unsigned long *port, unsigned long pin_mask){
//   GPIO_Config(port, pin_mask, _GPIO_CFG_DIGITAL_OUTPUT);
// }

// void GPIO_Digital_Input(unsigned long *port, unsigned long pin_mask){
//   GPIO_Config(port, pin_mask, _GPIO_CFG_DIGITAL_INPUT);
// }

// void GPIO_Config(unsigned long *port, unsigned int pin_mask, unsigned long config){
//   unsigned long tmpreg, pinpos, pos, currentpin, pinmask, currentmode, local1, local2;

//   unsigned long mode, speed;

//   port = (unsigned long)port & 0xFFFFFC00;

//   GPIO_Clk_Enable(port);

//   // ubrza donjih 8 bita
//   if(pin_mask == _GPIO_PINMASK_LOW){
//     if(config == _GPIO_CFG_DIGITAL_OUTPUT){
//       *(port + _CRL_OFFSET) = 0x33333333;
//       return;
//     }
//     if(config == _GPIO_CFG_DIGITAL_INPUT){
//       *(port + _CRL_OFFSET) = 0x44444444;
//       return;
//     }
//   }

//   if(pin_mask == _GPIO_PINMASK_ALL){
//     if(config == _GPIO_CFG_DIGITAL_OUTPUT){
//       *(port + _CRL_OFFSET) = 0x33333333;
//       *(port + _CRH_OFFSET) = 0x33333333;
//       return;
//     }
//     if(config == _GPIO_CFG_DIGITAL_INPUT){
//       *(port + _CRL_OFFSET) = 0x44444444;
//       *(port + _CRH_OFFSET) = 0x44444444;
//       return;
//     }
//   }

//   currentmode = 0;
//   speed = 0;

//   if (config & (_GPIO_CFG_MODE_ANALOG))
//     currentmode = 0;
//   else if (config & _GPIO_CFG_MODE_INPUT){
//     if(config & (_GPIO_CFG_PULL_DOWN | _GPIO_CFG_PULL_UP))
//       currentmode = 0x8;
//     else
//       currentmode = 0x4;
//   }
//   else if(config & _GPIO_CFG_MODE_OUTPUT){
//     if (config & _GPIO_CFG_OTYPE_OD)
//       currentmode = 0x4;
//     else
//       currentmode = 0;
//   }
//   else if (config & _GPIO_CFG_MODE_ALT_FUNCTION){
//     if (config & _GPIO_CFG_OTYPE_OD)
//       currentmode = 0xC;
//     else
//       currentmode = 0x8;
//   }

//   if(config & (_GPIO_CFG_SPEED_MAX | _GPIO_CFG_SPEED_50MHZ))
//     speed = 3;
//   else if(config & _GPIO_CFG_SPEED_2MHZ)
//     speed = 2;
//   else if (config & _GPIO_CFG_SPEED_10MHZ)
//     speed = 1;

//   tmpreg = 0;
//   pinpos = 0;
//   pos = 0;
//   currentpin = 0;
//   pinmask = 0;

//   if(config & (_GPIO_CFG_MODE_OUTPUT | _GPIO_CFG_MODE_ALT_FUNCTION))
//   {
//     /* Output mode */
//     currentmode |= (unsigned long)speed;
//   }

//   if((pin_mask & 0xFF) != 0){
//     tmpreg = *port;      // CRL register

//     for (pinpos = 0x00; pinpos < 0x08; pinpos++)
//     {
//       pos = ((unsigned long)0x01) << pinpos;
//       /* Get the port pins position */
//       currentpin = (pin_mask) & pos;

//       if (currentpin == pos)
//       {
//         pos = pinpos << 2;
//         /* Clear the corresponding low control register bits */
//         pinmask = ((unsigned long)0x0F) << pos;
//         tmpreg &= ~pinmask;

//         /* Write the mode configuration in the corresponding bits */
//         tmpreg |= (currentmode << pos);

//         /* Reset the corresponding ODR bit */
//         if((config & (_GPIO_CFG_MODE_INPUT | _GPIO_CFG_PULL_DOWN)) == (_GPIO_CFG_MODE_INPUT | _GPIO_CFG_PULL_DOWN))
//         {
//           *(port + _BRR_OFFSET) = (((unsigned long)0x01) << pinpos);  // write to BRR register
//         }
//         /* Set the corresponding ODR bit */
//         if((config & (_GPIO_CFG_MODE_INPUT | _GPIO_CFG_PULL_UP)) == (_GPIO_CFG_MODE_INPUT | _GPIO_CFG_PULL_UP))
//         {
//           *(port + _BSRR_OFFSET) = (((unsigned long)0x01) << pinpos);
//         }
//       }
//     }
//     *port = tmpreg;          // write to CRL register

//   }

// /*---------------------------- GPIO CRH Configuration ------------------------*/
//   /* Configure the eight high port pins */
//   if (pin_mask > 0x00FF)
//   {
//     tmpreg = *(port + _CRH_OFFSET);//GPIOx->CRH;
//     for (pinpos = 0x00; pinpos < 0x08; pinpos++)
//     {
//       pos = (((unsigned long)0x01) << (pinpos + 0x08));
//       /* Get the port pins position */
//       currentpin = ((pin_mask) & pos);
//       if (currentpin == pos)
//       {
//         pos = pinpos << 2;
//         /* Clear the corresponding high control register bits */
//         pinmask = ((unsigned long)0x0F) << pos;
//         tmpreg &= ~pinmask;

//         /* Write the mode configuration in the corresponding bits */
//         tmpreg |= (currentmode << pos);

//         /* Reset the corresponding ODR bit */
//         if((config & (_GPIO_CFG_MODE_INPUT | _GPIO_CFG_PULL_DOWN)) == (_GPIO_CFG_MODE_INPUT | _GPIO_CFG_PULL_DOWN))
//         {
//           *(port + _BRR_OFFSET) = (((unsigned long)0x01) << (pinpos + 0x08));
//         }
//         /* Set the corresponding ODR bit */
//         if((config & (_GPIO_CFG_MODE_INPUT | _GPIO_CFG_PULL_UP)) == (_GPIO_CFG_MODE_INPUT | _GPIO_CFG_PULL_UP))
//         {
//           *(port + _BSRR_OFFSET) = (((unsigned long)0x01) << (pinpos + 0x08));
//         }
//       }
//     }
//     *(port + _CRH_OFFSET) = tmpreg;
//   }
// }
