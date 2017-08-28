#ifndef __USER_IO_H
#define __USER_IO_H

#define LTC_TOGGLE() HAL_GPIO_TogglePin(OUTPUT_LED0_GPIO_Port, OUTPUT_LED0_Pin)
#define LED_TOGGLE() HAL_GPIO_TogglePin(OUTPUT_LED1_GPIO_Port, OUTPUT_LED1_Pin)

#define GET_LTC() HAL_GPIO_ReadPin(EXTI_LTC_GPIO_Port, EXTI_LTC_Pin)

extern void user_io_init(void);
extern void ltc_decode(int interval);

#endif /* __USER_IO_H */
