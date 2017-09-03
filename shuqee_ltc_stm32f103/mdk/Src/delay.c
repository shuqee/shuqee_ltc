#include "stm32f1xx_hal.h"
#include "user_config.h"
#include "delay.h"

void delay_us(uint16_t nus)
{		
	__HAL_TIM_SET_AUTORELOAD(&htim4, nus);
	HAL_TIM_Base_Start(&htim4);
	while(!__HAL_TIM_GET_FLAG(&htim4, TIM_FLAG_UPDATE));
	__HAL_TIM_CLEAR_FLAG(&htim4, TIM_FLAG_UPDATE);
	HAL_TIM_Base_Stop(&htim4);
}

void delay_ms(uint16_t nms)
{	 		
	while(nms--)
	{
		delay_us(1000);
	}	    
} 