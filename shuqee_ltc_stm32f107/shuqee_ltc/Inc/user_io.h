#ifndef __USER_IO_H
#define __USER_IO_H

#include "stm32f1xx_hal.h"

#define LED1_TOGGLE() HAL_GPIO_TogglePin(OUTPUT_LED1_GPIO_Port, OUTPUT_LED1_Pin)
#define LED2_TOGGLE() HAL_GPIO_TogglePin(OUTPUT_LED2_GPIO_Port, OUTPUT_LED2_Pin)
#define LED3_TOGGLE() HAL_GPIO_TogglePin(OUTPUT_LED3_GPIO_Port, OUTPUT_LED3_Pin)

#define LED1_ON() HAL_GPIO_WritePin(OUTPUT_LED1_GPIO_Port, OUTPUT_LED1_Pin, GPIO_PIN_RESET)
#define LED2_ON() HAL_GPIO_WritePin(OUTPUT_LED2_GPIO_Port, OUTPUT_LED2_Pin, GPIO_PIN_RESET)
#define LED3_ON() HAL_GPIO_WritePin(OUTPUT_LED3_GPIO_Port, OUTPUT_LED3_Pin, GPIO_PIN_RESET)

#define LED1_OFF() HAL_GPIO_WritePin(OUTPUT_LED1_GPIO_Port, OUTPUT_LED1_Pin, GPIO_PIN_SET)
#define LED2_OFF() HAL_GPIO_WritePin(OUTPUT_LED2_GPIO_Port, OUTPUT_LED2_Pin, GPIO_PIN_SET)
#define LED3_OFF() HAL_GPIO_WritePin(OUTPUT_LED3_GPIO_Port, OUTPUT_LED3_Pin, GPIO_PIN_SET)

#define SPCIAL_1_ON() HAL_GPIO_WritePin(SPCIAL_1_GPIO_Port, SPCIAL_1_Pin, GPIO_PIN_RESET)
#define SPCIAL_2_ON() HAL_GPIO_WritePin(SPCIAL_2_GPIO_Port, SPCIAL_2_Pin, GPIO_PIN_RESET)
#define SPCIAL_3_ON() HAL_GPIO_WritePin(SPCIAL_3_GPIO_Port, SPCIAL_3_Pin, GPIO_PIN_RESET)
#define SPCIAL_4_ON() HAL_GPIO_WritePin(SPCIAL_4_GPIO_Port, SPCIAL_4_Pin, GPIO_PIN_RESET)
#define SPCIAL_5_ON() HAL_GPIO_WritePin(SPCIAL_5_GPIO_Port, SPCIAL_5_Pin, GPIO_PIN_RESET)
#define SPCIAL_6_ON() HAL_GPIO_WritePin(SPCIAL_6_GPIO_Port, SPCIAL_6_Pin, GPIO_PIN_RESET)
#define SPCIAL_7_ON() HAL_GPIO_WritePin(SPCIAL_7_GPIO_Port, SPCIAL_7_Pin, GPIO_PIN_RESET)
#define SPCIAL_8_ON() HAL_GPIO_WritePin(SPCIAL_8_GPIO_Port, SPCIAL_8_Pin, GPIO_PIN_RESET)

#define SPCIAL_1_OFF() HAL_GPIO_WritePin(SPCIAL_1_GPIO_Port, SPCIAL_1_Pin, GPIO_PIN_SET)
#define SPCIAL_2_OFF() HAL_GPIO_WritePin(SPCIAL_2_GPIO_Port, SPCIAL_2_Pin, GPIO_PIN_SET)
#define SPCIAL_3_OFF() HAL_GPIO_WritePin(SPCIAL_3_GPIO_Port, SPCIAL_3_Pin, GPIO_PIN_SET)
#define SPCIAL_4_OFF() HAL_GPIO_WritePin(SPCIAL_4_GPIO_Port, SPCIAL_4_Pin, GPIO_PIN_SET)
#define SPCIAL_5_OFF() HAL_GPIO_WritePin(SPCIAL_5_GPIO_Port, SPCIAL_5_Pin, GPIO_PIN_SET)
#define SPCIAL_6_OFF() HAL_GPIO_WritePin(SPCIAL_6_GPIO_Port, SPCIAL_6_Pin, GPIO_PIN_SET)
#define SPCIAL_7_OFF() HAL_GPIO_WritePin(SPCIAL_7_GPIO_Port, SPCIAL_7_Pin, GPIO_PIN_SET)
#define SPCIAL_8_OFF() HAL_GPIO_WritePin(SPCIAL_8_GPIO_Port, SPCIAL_8_Pin, GPIO_PIN_SET)

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

extern void user_io_init(void);

uint8_t get_ltc_frame(void);
uint8_t get_ltc_second(void);
uint8_t get_ltc_minute(void);
uint8_t get_ltc_hour(void);
uint8_t get_ltc_frame_update_event(void);
void clr_ltc_frame_update_event(void);

#endif /* __USER_IO_H */
