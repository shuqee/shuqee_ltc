#include "stm32f1xx_hal.h"
#include "user_config.h"
#include "delay.h"

void delay_us(uint16_t nus)
{		
	__HAL_TIM_SET_AUTORELOAD(&htim3, nus);
	HAL_TIM_Base_Start(&htim3);
	while(!__HAL_TIM_GET_FLAG(&htim3, TIM_FLAG_UPDATE));
	__HAL_TIM_CLEAR_FLAG(&htim3, TIM_FLAG_UPDATE);
	HAL_TIM_Base_Stop(&htim3);
}

void delay_ms(uint16_t nms)
{	 		
	while(nms--)
	{
		delay_us(1000);
	}	    
} 