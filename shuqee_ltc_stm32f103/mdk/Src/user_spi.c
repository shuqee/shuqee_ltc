#include "stm32f1xx_hal.h"
#include "user_config.h"
#include "user_spi.h"

void user_spi_init(void)
{
	uint8_t spi_tx_data = 0xff;
	uint8_t spi_rx_data = 0x00;
	/* TODO: can not without timeout */
	(void)HAL_SPI_Transmit(&hspi1, &spi_tx_data, 1, HAL_MAX_DELAY);
	(void)HAL_SPI_TransmitReceive(&hspi2, &spi_tx_data, &spi_rx_data, 1, HAL_MAX_DELAY);
}

void spi1_write_byte(uint8_t tx_data)
{	
	uint8_t spi_tx_data = 0;
	
	spi_tx_data = tx_data;
	/* TODO: can not without timeout */
	(void)HAL_SPI_Transmit(&hspi1, &spi_tx_data, 1, HAL_MAX_DELAY);		    
}

uint8_t spi2_read_write_byte(uint8_t tx_data)
{	
	uint8_t spi_tx_data = 0;
	uint8_t spi_rx_data = 0;
	
	spi_tx_data = tx_data;
	/* TODO: can not without timeout */
	(void)HAL_SPI_TransmitReceive(&hspi2, &spi_tx_data, &spi_rx_data, 1, HAL_MAX_DELAY);
	
	return spi_rx_data;				    
}
