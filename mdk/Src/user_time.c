#include "stm32f1xx_hal.h"
#include "user_config.h"
#include "user_time.h"
#include "user_io.h"

void user_time_init(void)
{
	HAL_TIM_Base_Start(&htim3);
	HAL_TIM_Base_Start_IT(&htim2);
}

	static int frame = 0;
	static int second = 0;
	static int minute = 0;
	static int hour = 0;

static void ltc_run(unsigned char *buf)
{
	frame = (frame+1)%24;
	if (0 == frame)
	{
		second = (second+1)%60;
		if (0 == second)
		{
			minute = (minute+1)%60;
			if (0 == minute)
			{
				hour = (hour+1)%24;
			}
		}
	}
	buf[0] = frame%10;
	buf[1] = frame/10;
	buf[2] = second%10;
	buf[3] = second/10;
	buf[4] = minute%10;
	buf[5] = minute/10;
	buf[6] = hour%10;
	buf[7] = hour/10;
	buf[8] = 0xfc;
	buf[9] = 0xbf;
}

	static int index_byte = 0;
	static int index_bit = 0;
	static int odd_even_flag = 0;
	static unsigned char ltc_send_data[10] = {0};
	
	static int ltc_value = 0;
	static int ltc_count = 0;
	
static void ltc_send(void)
{
	ltc_send_data[8] = 0xfc;
	ltc_send_data[9] = 0xbf;
	if (0 == odd_even_flag)
	{
		odd_even_flag = 1;
	}
	else
	{
		odd_even_flag = 0;
	}

	if (1 == odd_even_flag)
	{
		HAL_GPIO_TogglePin(OUTPUT_LED0_GPIO_Port, OUTPUT_LED0_Pin);
		if (ltc_count == 0)
		{
			ltc_value = 0;
			//ltc_decode(520);
		}
		else
		{
			ltc_value = 1;
			//ltc_decode(260);
		}
		ltc_count = 0;
		index_bit = (index_bit+1)%8;
		if (0 == index_bit)
		{
			index_byte = (index_byte+1)%10;
			if (0 == index_byte)
			{
				ltc_run(ltc_send_data);
			}
		}
	}
	else
	{
		if (0 != (ltc_send_data[index_byte]&(0x01<<index_bit)))
		{
			HAL_GPIO_TogglePin(OUTPUT_LED0_GPIO_Port, OUTPUT_LED0_Pin);
			++ltc_count;
			//ltc_decode(260);
		}
	}
}

/**
  * @brief     Callback function of timer.
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM2) {
    ltc_send();
  }
}
