#ifndef __USER_CONFIG_H
#define __USER_CONFIG_H

#include "stm32f1xx_hal.h"

#define ABS(x) ((x)>0?(x):-(x)) 

/* atomic instructions */
#define SAFE(x) do{ \
	__set_PRIMASK(1); \
	x; \
	__set_PRIMASK(0); \
}while(0)

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern SPI_HandleTypeDef hspi1;
extern SPI_HandleTypeDef hspi2;

#endif /* __USER_CONFIG_H */
