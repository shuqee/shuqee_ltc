/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2017 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_hal.h"

/* USER CODE BEGIN Includes */
#include "user_config.h"
#include "user_io.h"
#include "user_time.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
//int timer3_enable = 0;
//int io_ltc = 0;
//int io_ltc_update = 0;
//int ltc_update_time = 0;
//int rec_ltc_data[10] = {0};

//int max_timer3 = 0;
//int cur_timer3 = 0;
//int pre_timer3 = 0;
//int dif_timer3 = 0;

//int max_timer2 = 0;
//int cur_timer2 = 0;
//int pre_timer2 = 0;
//int dif_timer2 = 0;

//int display = 0;
//int count_flag = 0;

//int count1=0,count2=0;
//int count0=0;
//int ix = 0;
//int zishiying = 0;
//int shangci = 0;
//int shiying[10] = {0};
//int ooo_=0,	kkk_=0;
//int ERR_=0;

//int last_value=0,j=0,k=0;
//int time2_count = 0 ,time_count=0;
//int zhengok = 0;
//int zuizon[100];
//int zhengno=0;
//int jiaozheng[16]={0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,1};
//int i=0;
//int LED_Count = 0,LED_Flag = 0;
//int LED_Power=5000;
//int Pswd[20]={0x00};
//int UDPData_R[13]={0X00};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM3_Init(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();

  /* USER CODE BEGIN 2 */
	user_io_init();
	user_time_init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* TIM2 init function */
static void MX_TIM2_Init(void)
{

  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;

  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 71;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 259;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* TIM3 init function */
static void MX_TIM3_Init(void)
{

  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;

  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 71;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 50000;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(OUTPUT_LED1_GPIO_Port, OUTPUT_LED1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(OUTPUT_LED0_GPIO_Port, OUTPUT_LED0_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : OUTPUT_LED1_Pin */
  GPIO_InitStruct.Pin = OUTPUT_LED1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(OUTPUT_LED1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : EXTI_LTC_Pin */
  GPIO_InitStruct.Pin = EXTI_LTC_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(EXTI_LTC_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : OUTPUT_LED0_Pin */
  GPIO_InitStruct.Pin = OUTPUT_LED0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(OUTPUT_LED0_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI4_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI4_IRQn);

}

/* USER CODE BEGIN 4 */
//void ltc_run(unsigned char *data)
//{
//	static int frame = 0;
//	static int second = 0;
//	static int minute = 0;
//	static int hour = 0;
//	frame = (frame+1)%24;
//	if (0 == frame)
//	{
//		second = (second+1)%60;
//		if (0 == second)
//		{
//			minute = (minute+1)%60;
//			if (0 == minute)
//			{
//				hour = (hour+1)%24;
//			}
//		}
//	}
//	data[0] = frame%10;
//	data[1] = frame/10;
//	data[2] = second%10;
//	data[3] = second/10;
//	data[4] = minute%10;
//	data[5] = minute/10;
//	data[6] = hour%10;
//	data[7] = hour/10;
//	data[8] = 0xfc;
//	data[9] = 0xbf;
//}

//int jieduizhi(int a ,int b)
//{
//	if(a<b)
//		return (b-a);
//	else
//		return (a-b);

//}

//void ltc_send(void)
//{
//	static int index_byte = 0;
//	static int index_bit = 0;
//	static int odd_even_flag = 0;
//	static unsigned char data[10] = {0};
//	
//	data[8] = 0xfc;
//	data[9] = 0xbf;
//	  
//	if (0 == odd_even_flag)
//	{
//		odd_even_flag = 1;
//	}
//	else
//	{
//		odd_even_flag = 0;
//	}

//	if (1 == odd_even_flag)
//	{
//		HAL_GPIO_TogglePin(OUTPUT_LED0_GPIO_Port, OUTPUT_LED0_Pin);
//		io_ltc = !io_ltc;
//		io_ltc_update = 1;
//		index_bit = (index_bit+1)%8;
//		if (0 == index_bit)
//		{
//			index_byte = (index_byte+1)%10;
//			if (0 == index_byte)
//			{
//				//ltc_run(data);
//			}
//		}
//	}
//	else
//	{
//		if (0 == (data[index_byte]&(0x80>>index_bit)))
//		{
//			HAL_GPIO_TogglePin(OUTPUT_LED0_GPIO_Port, OUTPUT_LED0_Pin);
//			io_ltc = !io_ltc;
//			io_ltc_update = 1;
//		}
//	}
//	
//	if (io_ltc_update == 1)
//	{
//		io_ltc_update = 0;
//		
//	cur_timer2 = __HAL_TIM_GET_COUNTER(&htim3);
//	if (cur_timer2 > pre_timer2)
//	{
//	  dif_timer2 = cur_timer2 - pre_timer2;
//	}
//	else
//	{
//	  dif_timer2 = cur_timer2+50000-pre_timer2;
//	}
//	max_timer2 = (max_timer2<dif_timer2)?dif_timer2:max_timer2;
//	pre_timer2 = cur_timer2;
//	
//	ltc_update_time = dif_timer2;
//	  
//	  dif_timer3 = ltc_update_time;
//	  
//	  if (zishiying == 0)
//	  {
//		  ++ix;
//		  if (ix > 80)
//		  {
//			  if ((20 < ooo_) && (20 < kkk_))
//			  {
//				  zishiying = 1;
//				  return;
//			  }
//			  
//			  if (shangci == 0)
//			  {
//				  shangci = dif_timer3;
//				  return;
//			  }
//			  count2 = jieduizhi(shiying[0], dif_timer3);
//			  if (count2 < 10)
//			  {
//				  ++ooo_;
//				  shangci = dif_timer3;
//				  return;
//			  }
//			  count2 = jieduizhi(shiying[2], dif_timer3);
//			  if (count2 < 10)
//			  {
//				  ++kkk_;
//				  shangci = dif_timer3;
//				  return;
//			  }
//			  
//			  count2 = jieduizhi(dif_timer3, shangci);
//			  if (count2 < 20)
//			  {
//				  shangci = dif_timer3;
//				  return;
//			  }
//			  
//			  if (shangci < dif_timer3)
//			  {
//				  count2 = jieduizhi(shangci, count2);
//				  if (count2 < 10)
//				  {
//					  shiying[0] = shangci;
//					  shiying[2] = dif_timer3;
//				  }
//			  }
//			  else
//			  {
//				  count2 = jieduizhi(dif_timer3, count2);
//				  if (count2 < 10)
//				  {
//					  shiying[0] = dif_timer3;
//					  shiying[2] = shangci;
//				  }
//			  }
//			  
//			  ooo_ = 0;
//			  kkk_ = 0;
//		  }
//	  }
//	  else
//	  {
//		count_flag = 1;
//		if ((shiying[2]-80) < dif_timer3)
//		{
//			if (dif_timer3 < (shiying[2]+80))
//			{
//				count1 = 0;
//			}
//			else
//			{
//				count1 = 2;
//			}
//		}
//		else if ((shiying[0]-80) < dif_timer3)
//		{
//			if (dif_timer3 < (shiying[0]+80))
//			{
//				count1 = 1;
//			}
//			else 
//			{
//				count1 = 2;
//			}
//	
//		}
//		else
//		{
//			count1 = 2;
//		}

//		if(count1==2)
//		{
//			ERR_++;
//			if (ERR_ == 50)
//			{
//				ERR_ = 0;
//				zishiying = 0;

//			}
//		}
//	  }
//	  
//		if (count_flag == 1)
//		{
//			count_flag = 0;
//			time2_count = count1;		
//			if (time2_count == 0)
//			{
//				last_value = 0;
//				time_count = 0;
//			}
//			else if (time2_count == 1)
//			{
//				time_count++;
//				if (time_count == 2)
//				{
//				 	time_count = 0;
//					last_value = 1;
//				}
//				else
//				{
//					return;
//				}
//			}
//			else
//			{
//				; /* do nothing */
//			}

//			if (zhengok == 0)
//			{	
//				if (last_value == 1)
//				{
//					if (j != 12)
//					{
//						++j;
//					}
//					else
//					{
//						j = 0;
//					}
//					if (j == 14)
//					{					
//						j = 0;
//						zhengok = 1;
//					}
//				}
//				else
//				{
//					if (j == 12)
//					{
//						++j;
//					}
//					else
//					{
//						j = 0;
//					}
//				}
//			}
//			else
//			{
//			 	zuizon[zhengno]=last_value;
				
//				switch(zhengno)
//				{
//					case 3:
//						UDPData_R[10] = zuizon[0]+(zuizon[1]<<1);
//						UDPData_R[10] = UDPData_R[10]+(zuizon[2]<<2)+(zuizon[3]<<3);
//						break;
//					case 9:
//						UDPData_R[9] =  zuizon[8]+(zuizon[9]<<1);
//						break;
//					case 19:
//						UDPData_R[7] =  zuizon[16]+(zuizon[17]<<1)+(zuizon[18]<<2);
//						UDPData_R[7] = 	UDPData_R[7]+(zuizon[19]<<3);
//						break;
//					case 26:
//						UDPData_R[6] =  zuizon[24]+(zuizon[25]<<1)+(zuizon[26]<<2);
//						UDPData_R[6] =  UDPData_R[6] ;
//						break;
//					case 35:
//						UDPData_R[4] =  zuizon[32]+(zuizon[33]<<1)+(zuizon[34]<<2);
//						UDPData_R[4] = 	UDPData_R[4]+(zuizon[35]<<3);
//						break;
//					case 42:
//						UDPData_R[3] =  zuizon[40]+(zuizon[41]<<1)+(zuizon[42]<<2);
//						UDPData_R[3] = 	UDPData_R[3];
//						break;
//					case 51:
//						UDPData_R[1] =  zuizon[48]+(zuizon[49]<<1)+(zuizon[50]<<2);
//						UDPData_R[1] = 	UDPData_R[1]+(zuizon[51]<<3);
//						break;
//					case 57:
//						UDPData_R[0] =  zuizon[56]+(zuizon[57]<<1);
//						UDPData_R[0] = 	UDPData_R[0];
//						break;				
//					case 63:
//						break;							
//					case 64:
//						break;							
//				}

//				zhengno++;
//				if (zhengno == 80)
//				{
//					for (k=0; k<10; k++)
//					{
//						rec_ltc_data[k] = 0;
//						for (i=0; i<8; i++)
//						{
//							rec_ltc_data[k] += (zuizon[8*k+i]<<i);
//						}
//					}
//					zhengno = 0;
//					for (i=0; i<16; i++)
//					{
//						if (jiaozheng[i] != zuizon[64+i])
//						{
//							zhengok = 0;
//						}

//					}

//					if (zhengok == 1)
//					{
//						LED_Count ++ ;
//						if (10 < LED_Count)
//						{
//							LED_Count = 0;
//							if(LED_Flag == 0)
//							{
//								LED_Flag = 1;
//								HAL_GPIO_WritePin(OUTPUT_LED1_GPIO_Port, OUTPUT_LED1_Pin, GPIO_PIN_RESET);
//							}
//							else
//							{
//								LED_Flag = 0;
//								HAL_GPIO_WritePin(OUTPUT_LED1_GPIO_Port, OUTPUT_LED1_Pin, GPIO_PIN_SET);
//							}  
//						}
//					}
//				}			
//			}
//		}
//	}
//}

/**
  * @brief  EXTI line detection callbacks.
  * @param  GPIO_Pin: Specifies the pins connected EXTI line
  * @retval None
  */
//void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
//{
//  if(EXTI_LTC_Pin == GPIO_Pin)
//  {
//	  if (timer3_enable == 0)
//	  {
//		  max_timer3 = 0;
//		  cur_timer3 = 0;
//		  pre_timer3 = 0;
//		  return;
//	  }
//	  
//	  cur_timer3 = __HAL_TIM_GET_COUNTER(&htim3);
//	  dif_timer3 = cur_timer3 - pre_timer3;
//	  if (dif_timer3 < 0)
//	  {
//		  dif_timer3+=50000;
//	  }
//	  pre_timer3 = cur_timer3;
//	  
//	  if (zishiying == 0)
//	  {
//		  ++ix;
//		  if (ix > 80)
//		  {
//			  if ((20 < ooo_) && (20 < kkk_))
//			  {
//				  zishiying = 1;
//				  return;
//			  }
//			  
//			  if (shangci == 0)
//			  {
//				  shangci = dif_timer3;
//				  return;
//			  }
//			  count2 = jieduizhi(shiying[0], dif_timer3);
//			  if (count2 < 10)
//			  {
//				  ++ooo_;
//				  shangci = dif_timer3;
//				  return;
//			  }
//			  count2 = jieduizhi(shiying[2], dif_timer3);
//			  if (count2 < 10)
//			  {
//				  ++kkk_;
//				  shangci = dif_timer3;
//				  return;
//			  }
//			  
//			  count2 = jieduizhi(dif_timer3, shangci);
//			  if (count2 < 20)
//			  {
//				  shangci = dif_timer3;
//				  return;
//			  }
//			  
//			  if (shangci < dif_timer3)
//			  {
//				  count2 = jieduizhi(shangci, count2);
//				  if (count2 < 10)
//				  {
//					  shiying[0] = shangci;
//					  shiying[2] = dif_timer3;
//				  }
//			  }
//			  else
//			  {
//				  count2 = jieduizhi(dif_timer3, count2);
//				  if (count2 < 10)
//				  {
//					  shiying[0] = dif_timer3;
//					  shiying[2] = shangci;
//				  }
//			  }
//			  
//			  ooo_ = 0;
//			  kkk_ = 0;
//		  }
//	  }
//	  else
//	  {
//		count_flag = 1;
//		if ((shiying[2]-80) < dif_timer3)
//		{
//			if (dif_timer3 < (shiying[2]+80))
//			{
//				count1 = 0;
//			}
//			else
//			{
//				count1 = 2;
//			}
//		}
//		else if ((shiying[0]-80) < dif_timer3)
//		{
//			if (dif_timer3 < (shiying[0]+80))
//			{
//				count1 = 1;
//			}
//			else 
//			{
//				count1 = 2;
//			}
//	
//		}
//		else
//		{
//			count1 = 2;
//		}

//		if(count1==2)
//		{
//			ERR_++;
//			if (ERR_ == 50)
//			{
//				ERR_ = 0;
//				zishiying = 0;

//			}
//		}
//	  }
//	  
//		if (count_flag == 1)
//		{
//			count_flag = 0;
//			time2_count = count1;		
//			if (time2_count == 0)
//			{
//				last_value = 0;
//				time_count = 0;
//			}
//			else if (time2_count == 1)
//			{
//				time_count++;
//				if (time_count == 2)
//				{
//				 	time_count = 0;
//					last_value = 1;
//				}
//				else
//				{
//					return;
//				}
//			}
//			else
//			{
//				; /* do nothing */
//			}

//			if (zhengok == 0)
//			{	
//				if (last_value == 1)
//				{
//					if (j != 12)
//					{
//						++j;
//					}
//					else
//					{
//						j = 0;
//					}
//					if (j == 14)
//					{					
//						j = 0;
//						zhengok = 1;
//					}
//				}
//				else
//				{
//					if (j == 12)
//					{
//						++j;
//					}
//					else
//					{
//						j = 0;
//					}
//				}
//			}
//			else
//			{
//			 	zuizon[zhengno]=last_value;
//				
////				switch(zhengno)
////				{
////					case 3:
////						UDPData_R[10] = zuizon[0]+(zuizon[1]<<1);
////						UDPData_R[10] = UDPData_R[10]+(zuizon[2]<<2)+(zuizon[3]<<3);
////						break;
////					case 9:
////						UDPData_R[9] =  zuizon[8]+(zuizon[9]<<1);
////						break;
////					case 19:
////						UDPData_R[7] =  zuizon[16]+(zuizon[17]<<1)+(zuizon[18]<<2);
////						UDPData_R[7] = 	UDPData_R[7]+(zuizon[19]<<3);
////						break;
////					case 26:
////						UDPData_R[6] =  zuizon[24]+(zuizon[25]<<1)+(zuizon[26]<<2);
////						UDPData_R[6] =  UDPData_R[6] ;
////						break;
////					case 35:
////						UDPData_R[4] =  zuizon[32]+(zuizon[33]<<1)+(zuizon[34]<<2);
////						UDPData_R[4] = 	UDPData_R[4]+(zuizon[35]<<3);
////						break;
////					case 42:
////						UDPData_R[3] =  zuizon[40]+(zuizon[41]<<1)+(zuizon[42]<<2);
////						UDPData_R[3] = 	UDPData_R[3];
////						break;
////					case 51:
////						UDPData_R[1] =  zuizon[48]+(zuizon[49]<<1)+(zuizon[50]<<2);
////						UDPData_R[1] = 	UDPData_R[1]+(zuizon[51]<<3);
////						break;
////					case 57:
////						UDPData_R[0] =  zuizon[56]+(zuizon[57]<<1);
////						UDPData_R[0] = 	UDPData_R[0];
////						break;				
////					case 63:
////						break;							
////					case 64:
////						break;							
////				}

//				zhengno++;
//				if (zhengno == 80)
//				{
//					for (k=0; k<10; k++)
//					{
//						rec_ltc_data[k] = 0;
//						for (i=0; i<8; i++)
//						{
//							rec_ltc_data[k] += (zuizon[8*k+i]<<i);
//						}
//					}
//					zhengno = 0;
////					for (i=0; i<16; i++)
////					{
////						if (jiaozheng[i] != zuizon[64+i])
////						{
////							zhengok = 0;
////						}

////					}

//					if (zhengok == 1)
//					{
//						LED_Count ++ ;
//						if (10 < LED_Count)
//						{
//							LED_Count = 0;
//							if(LED_Flag == 0)
//							{
//								LED_Flag = 1;
//								HAL_GPIO_WritePin(OUTPUT_LED1_GPIO_Port, OUTPUT_LED1_Pin, GPIO_PIN_RESET);
//							}
//							else
//							{
//								LED_Flag = 0;
//								HAL_GPIO_WritePin(OUTPUT_LED1_GPIO_Port, OUTPUT_LED1_Pin, GPIO_PIN_SET);
//							}  
//						}
//					}
//				}			
//			}
//		}
//  }
//}

//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
//{
//  if (htim->Instance == TIM2) {
//    ltc_send();
//  }
//}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void _Error_Handler(char * file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler_Debug */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
