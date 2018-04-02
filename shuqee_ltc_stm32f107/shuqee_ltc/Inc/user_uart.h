#ifndef __USER_UART_H
#define __USER_UART_H

#include "user_config.h"

extern void user_uart_init(void);

extern void bus485_control(uint8_t *high, uint8_t sp_seat, uint8_t sp_env, uint8_t seat_id);
extern void special_checkout(uint8_t spcial_data);

#endif /* __USER_UART_H */
