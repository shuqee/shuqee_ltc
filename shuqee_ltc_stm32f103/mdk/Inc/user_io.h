#ifndef __USER_IO_H
#define __USER_IO_H

#define LTC_TOGGLE() HAL_GPIO_TogglePin(OUTPUT_LED0_GPIO_Port, OUTPUT_LED0_Pin)
#define LED_TOGGLE() HAL_GPIO_TogglePin(OUTPUT_LED1_GPIO_Port, OUTPUT_LED1_Pin)

#define SPI_FLASH_CS(x) HAL_GPIO_WritePin(SPI_FLASH_CS_GPIO_Port, SPI_FLASH_CS_Pin, (GPIO_PinState)(x))
#define SPI_SD_CS(x) HAL_GPIO_WritePin(SPI_SD_CS_GPIO_Port, SPI_SD_CS_Pin, (GPIO_PinState)(x))
#define SPI_NRF_CS(x) HAL_GPIO_WritePin(SPI_NRF_CS_GPIO_Port, SPI_NRF_CS_Pin, (GPIO_PinState)(x))

#define SPI_LCD_CS(x) HAL_GPIO_WritePin(SPI_LCD_CS_GPIO_Port, SPI_LCD_CS_Pin, (GPIO_PinState)(x))
#define OUTPUT_LCD_DC(x) HAL_GPIO_WritePin(OUTPUT_LCD_DC_GPIO_Port, OUTPUT_LCD_DC_Pin, (GPIO_PinState)(x))
#define OUTPUT_LCD_BL(x) HAL_GPIO_WritePin(OUTPUT_LCD_BL_GPIO_Port, OUTPUT_LCD_BL_Pin, (GPIO_PinState)(x))
#define OUTPUT_LCD_RES(x) HAL_GPIO_WritePin(OUTPUT_LCD_RES_GPIO_Port, OUTPUT_LCD_RES_Pin, (GPIO_PinState)(x))

#define LCD_CS_CLR() SPI_LCD_CS(0)
#define LCD_CS_SET() SPI_LCD_CS(1)

#define LCD_DC_CLR() OUTPUT_LCD_DC(0)
#define LCD_DC_SET() OUTPUT_LCD_DC(1)

#define LCD_RST_CLR() OUTPUT_LCD_RES(0)
#define LCD_RST_SET() OUTPUT_LCD_RES(1)

#define LCD_LED_CLR() OUTPUT_LCD_BL(0)
#define LCD_LED_SET() OUTPUT_LCD_BL(1)

#define GET_LTC() HAL_GPIO_ReadPin(EXTI_LTC_GPIO_Port, EXTI_LTC_Pin)

extern void user_io_init(void);
extern void ltc_decode(int interval);

#endif /* __USER_IO_H */
