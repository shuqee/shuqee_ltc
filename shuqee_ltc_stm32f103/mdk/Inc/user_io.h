#ifndef __USER_IO_H
#define __USER_IO_H

#define LTC_TOGGLE() HAL_GPIO_TogglePin(OUTPUT_LED0_GPIO_Port, OUTPUT_LED0_Pin)
#define LED_TOGGLE() HAL_GPIO_TogglePin(OUTPUT_LED1_GPIO_Port, OUTPUT_LED1_Pin)

#define SPI_FLASH_CS(x) HAL_GPIO_WritePin(SPI_FLASH_CS_GPIO_Port, SPI_FLASH_CS_Pin, (GPIO_PinState)(x))
#define SPI_SD_CS(x) HAL_GPIO_WritePin(SPI_SD_CS_GPIO_Port, SPI_SD_CS_Pin, (GPIO_PinState)(x))
#define SPI_NRF_CS(x) HAL_GPIO_WritePin(SPI_NRF_CS_GPIO_Port, SPI_NRF_CS_Pin, (GPIO_PinState)(x))

#define GET_LTC() HAL_GPIO_ReadPin(EXTI_LTC_GPIO_Port, EXTI_LTC_Pin)

extern void user_io_init(void);
extern void ltc_decode(int interval);

#endif /* __USER_IO_H */
