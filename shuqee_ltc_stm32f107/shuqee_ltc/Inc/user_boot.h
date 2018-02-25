#ifndef __USER_BOOT_H
#define __USER_BOOT_H

#include "stm32f1xx_hal.h"

extern void boot_set_update_flag(void);
extern void boot_clean_update_flag(void);

#endif /* __USER_BOOT_H */
