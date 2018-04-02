#ifndef __USER_TIME_H
#define __USER_TIME_H

#include "stm32f1xx_hal.h"

extern void user_time_init(void);
extern void user_time_start(void);
extern void user_time_stop(void);

extern uint8_t get_timer2_isr_flag(void);
extern void clr_timer2_isr_flag(void);

#endif /* __USER_TIME_H */
