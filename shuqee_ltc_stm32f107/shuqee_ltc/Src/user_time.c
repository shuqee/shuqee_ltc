#include "stm32f1xx_hal.h"
#include "user_config.h"
#include "user_time.h"

static uint8_t timer2_isr_flag = 0;

static uint8_t timer2_enable_flag = 0;

void user_time_init(void)
{
	HAL_TIM_Base_Start(&htim3);
	HAL_TIM_Base_Start_IT(&htim2);
}

void user_time_start(void)
{
	if (timer2_enable_flag == 0)
	{
		HAL_TIM_Base_Start_IT(&htim2);
		timer2_enable_flag = 1;
	}
}

void user_time_stop(void)
{
	if (timer2_enable_flag != 0)
	{
		HAL_TIM_Base_Stop_IT(&htim2);
		timer2_enable_flag = 0;
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	timer2_isr_flag = 1;
}

uint8_t get_timer2_isr_flag(void)   //10 ms
{
	uint8_t timer2_isr = 0;
	SAFE(timer2_isr = timer2_isr_flag);
	return timer2_isr;
}

void clr_timer2_isr_flag(void)
{
	SAFE(timer2_isr_flag = 0);
}
