#include "stm32f1xx_hal.h"
#include "user_config.h"
#include "user_spi.h"

void user_spi_init(void)
{
	uint8_t spi_tx_data = 0xff;
	/* TODO: can not without timeout */
	(void)HAL_SPI_Transmit(&hspi1, &spi_tx_data, 1, HAL_MAX_DELAY);
}

void spi1_write_byte(uint8_t tx_data)
{	
	uint8_t spi_tx_data = 0;
	
	spi_tx_data = tx_data;
	/* TODO: can not without timeout */
	(void)HAL_SPI_Transmit(&hspi1, &spi_tx_data, 1, HAL_MAX_DELAY);		    
}
