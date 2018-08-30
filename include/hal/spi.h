#ifndef _SPI_H
#define _SPI_H

#include "hal/hal.h"

typedef void (*spi_callback_t)();

typedef uint8_t spi_channel_t;

typedef enum
{
    SPI_ERR_OK = 0,
    SPI_INVALID_CHANNEL
} spi_err_t;

/**
 * SPI master/slave architecture mode selection.
 */
typedef enum
{
    SPI_MASTER = 0,
    SPI_SLAVE
} spi_mode_t;

/**
 * Transfer frame format selection.
 */
typedef enum
{
    SPI_8BIT = 0,
    SPI_16BIT,
    SPI_32BIT
} spi_frame_t;

/**
 * CPOL determines the polarity of the clock.
 */
typedef enum
{
    SPI_IDLE_LOW = 0, /**< A clock which idles at 0. */
    SPI_IDLE_HIGH     /**< A clock which idles at 1. */
} spi_cpol_t;

/**
 * CPHA determines the timing of the data bits relative to the clock pulses.
 */
typedef enum {
    SPI_FIRST_EDGE = 0, /**< The data are sampled on the leading (first) clock edge */
    SPI_SECOND_EDGE     /**< The data are sampled on the trailing (second) clock edge. */
} spi_cpha_t;

/**
 * SPI init configuration structure.
 */
typedef struct
{
    uint32_t clock;
    spi_mode_t mode;
    spi_frame_t frame;
    spi_cpol_t cpol;
    spi_cpha_t cpha;
} spi_config_t;

/**
 * 
 */
typedef struct
{
    uint32_t *rx;
    uint32_t *tx;
    uint16_t size;
} spi_transfer_block_t;

/**
 * Initialization function.
 */
spi_err_t spi_init();

/**
 * Enabling SPI module with specified configuration \config.
 * @channel SPI module.
 * @config Configuration structure. 
 */
spi_err_t spi_open(spi_channel_t channel, spi_config_t config);

/**
 * Disabling SPI module.
 * @channel SPI module.
 */
spi_err_t spi_close(spi_channel_t channel);


/**
 * Transfer data function.
 * @channel SPI module.
 * @tb Transfer block structure.
 */
spi_err_t spi_transfer(spi_channel_t channel, spi_transfer_block_t tb);

#endif // _SPI_H