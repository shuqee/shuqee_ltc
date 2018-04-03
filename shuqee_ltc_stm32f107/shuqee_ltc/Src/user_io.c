#include "stm32f1xx_hal.h"
#include "user_config.h"
#include "user_io.h"

void user_io_init(void)
{

}


	static int interval_last = 0;
	static int self_adaption_flag = 0;
	static int adaption_short_interval = 0;
	static int adaption_long_interval = 0;
	static int bit_index = 0;
	static int short_interval_count = 0;
	static int long_interval_count = 0;
	static int interval_state = 0;
	static int interval_count = 0;
	static int error_count = 0;
	static int ltc_update_event = 0;
	static int ltc_bit_value = 0;
	static int ltc_frame_flag = 0;
	static int ltc_frame_check_index = 0;
	
    static int ltc_bit_buf[80] = {0};
	static int ltc_bit_index = 0;
	
	static unsigned char ltc_receive_data[10] = {0};
	
	static int led_count = 0;
	
	static uint8_t frame = 0;
	static uint8_t second = 0;
	static uint8_t minute = 0;
	static uint8_t hour = 0;
	
	static uint8_t ltc_frame_update_event = 0;
	
uint8_t get_ltc_frame(void)
{
	uint8_t ret_frame = 0;
	SAFE(ret_frame = frame);
	return ret_frame;
}

uint8_t get_ltc_second(void)
{
	uint8_t ret_second = 0;
	SAFE(ret_second = second);
	return ret_second;
}

uint8_t get_ltc_minute(void)
{
	uint8_t ret_minute = 0;
	SAFE(ret_minute = minute);
	return ret_minute;
}

uint8_t get_ltc_hour(void)
{
	uint8_t ret_hour = 0;
	SAFE(ret_hour = hour);
	return ret_hour;
}

uint8_t get_ltc_frame_update_event(void)
{
	uint8_t update_event = 0;
	SAFE(update_event = ltc_frame_update_event);
	return update_event;
}

void clr_ltc_frame_update_event(void)
{
	SAFE(ltc_frame_update_event = 0);
}

void ltc_decode(int interval)
{	
	int i,j;
	
	if (self_adaption_flag == 0)
	{
		++bit_index;
		if (bit_index > 80)
		{
			if ((20 < short_interval_count) && (20 < long_interval_count))
			{
				self_adaption_flag = 1;
				return;
			}

			if (interval_last == 0)
			{
				interval_last = interval;
				return;
			}

			if (ABS(adaption_short_interval-interval) < 20)
			{
				++short_interval_count;
				interval_last = interval;
				error_count = 0;
				return;
			}
			else
			{
				error_count++;
			}

			if (ABS(adaption_long_interval-interval) < 20)
			{
				++long_interval_count;
				interval_last = interval;
				error_count = 0;
				return;
			}
			else
			{
				error_count++;
			}
			
			if (error_count > 100)
			{
				error_count = 0;
				interval_last = 0;
				return;
				
			}

			if (ABS(interval-interval_last) < 20)
			{
				interval_last = interval;
				return;
			}

			if (interval_last < interval)
			{
				if (ABS(interval_last-ABS(interval-interval_last)) < 10)
				{
					adaption_short_interval = interval_last;
					adaption_long_interval = interval;
				}
			}
			else
			{
				if (ABS(interval-ABS(interval-interval_last)) < 10)
				{
					adaption_short_interval = interval;
					adaption_long_interval = interval_last;
				}
			}

			short_interval_count = 0;
			long_interval_count = 0;
		}
	}
	else
	{
		ltc_update_event = 1;
		if ((adaption_long_interval-80) < interval)
		{
			if (interval < (adaption_long_interval+80))
			{
				interval_state = 0;
			}
			else
			{
				interval_state = 2;
			}
		}
		else if ((adaption_short_interval-80) < interval)
		{
			if (interval < (adaption_short_interval+80))
			{
				interval_state = 1;
			}
			else 
			{
				interval_state = 2;
			}
		}
		else
		{
			interval_state = 2;
		}

		if (interval_state == 2)
		{
			++error_count;
			if (error_count == 50)
			{
				error_count = 0;
				self_adaption_flag = 0;
			}
		}
	}
	  
	if (ltc_update_event == 1)
	{
		ltc_update_event = 0;		
		if (interval_state == 0)
		{
			ltc_bit_value = 0;
			interval_count = 0;
		}
		else if (interval_state == 1)
		{
			interval_count++;
			if (interval_count == 2)
			{
				interval_count = 0;
				ltc_bit_value = 1;
			}
			else
			{
				return;
			}
		}
		else
		{
			; /* do nothing */
		}

		if (ltc_frame_flag == 0)
		{	
			if (ltc_bit_value == 1)
			{
				if (ltc_frame_check_index != 12)
				{
					++ltc_frame_check_index;
				}
				else
				{
					ltc_frame_check_index = 0;
				}
				if (ltc_frame_check_index == 14)
				{					
					ltc_frame_check_index = 0;
					ltc_frame_flag = 1;
				}
			}
			else
			{
				if (ltc_frame_check_index == 12)
				{
					++ltc_frame_check_index;
				}
				else
				{
					ltc_frame_check_index = 0;
				}
			}
		}
		else
		{
			ltc_bit_buf[ltc_bit_index]=ltc_bit_value;
			
			ltc_bit_index = (ltc_bit_index+1)%80;
			if (ltc_bit_index == 0)
			{
				for (j=0; j<10; j++)
				{
					ltc_receive_data[j] = 0;
					for (i=0; i<8; i++)
					{
						ltc_receive_data[j] += (ltc_bit_buf[8*j+i]<<i);
					}
				}
				
				frame = ((ltc_receive_data[1]&0x03)*10)+(ltc_receive_data[0]&0x0f);
				second = ((ltc_receive_data[3]&0x07)*10)+(ltc_receive_data[2]&0x0f);
				minute = ((ltc_receive_data[5]&0x07)*10)+(ltc_receive_data[4]&0x0f);
				hour = ((ltc_receive_data[7]&0x03)*10)+(ltc_receive_data[6]&0x0f);
				
				if ((ltc_receive_data[8] != 0xfc) ||
					(ltc_receive_data[9] != 0xbf))
				{
					ltc_frame_flag = 0;
				}
				else
				{
					ltc_frame_update_event = 1;
				}		

				if (ltc_frame_flag == 1)
				{
					led_count ++ ;
					if (10 < led_count)
					{
						led_count = 0;
						LED2_TOGGLE();
					}
				}
			}			
		}
	}
}

/**
  * @brief  EXTI line detection callbacks.
  * @param  GPIO_Pin: Specifies the pins connected EXTI line
  * @retval None
  */
	static int cur_timer3 = 0;
	static int pre_timer3 = 0;
	static int dif_timer3 = 0;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(EXTI_LTC_Pin == GPIO_Pin)
	{
		cur_timer3 = __HAL_TIM_GET_COUNTER(&htim3);
		dif_timer3 = cur_timer3 - pre_timer3;
		if (dif_timer3 < 0)
		{
			dif_timer3+=50000;
		}
		pre_timer3 = cur_timer3;
		ltc_decode(dif_timer3);
	}
}
