#include <stdint.h>

#define MIKROBUS_PIN_COUNT (12)

typedef enum {
    MIKROBUS_AN = 0,
    MIKROBUS_RST = 1,
    MIKROBUS_CS = 2,
    MIKROBUS_SCK = 3,
    MIKROBUS_MISO = 4,
    MIKROBUS_MOSI = 5,
    MIKROBUS_PWM = 6,
    MIKROBUS_INT = 7,
    MIKROBUS_RX = 8,
    MIKROBUS_TX = 9,
    MIKROBUS_SCL = 10,
    MIKROBUS_SDA = 11
} mikrobus_pin_t;


 typedef enum {
    MIKROBUS_1 = 0,
    MIKROBUS_2 = 2,
    MIKROBUS_3 = 3,
    MIKROBUS_4 = 4,
    MIKROBUS_5 = 5,
    MIKROBUS_6 = 6,
    MIKROBUS_7 = 7,
    MIKROBUS_8 = 8,
    MIKROBUS_9 = 9,
    MIKROBUS_10 = 10,
    MIKROBUS_11 = 11,
    MIKROBUS_12 = 12,
    MIKROBUS_13 = 13,
    MIKROBUS_14 = 14,
    MIKROBUS_15 = 15,
    MIKROBUS_16 = 16
} mikrobus_t;

typedef enum 
{
    MIKROBUS_OUT = 1,
    MIKROBUS_IN = 0,
} mikrobus_dir_t;

void bsp_mikrobus_init_digital(mikrobus_dir_t dir, mikrobus_t bus, mikrobus_pin_t pin);
void bsp_mikrobus_set(mikrobus_t bus, mikrobus_pin_t pin);
void bsp_mikrobus_rst(mikrobus_t bus, mikrobus_pin_t pin);
void bsp_mikrobus_toggle(mikrobus_t bus, mikrobus_pin_t pin);