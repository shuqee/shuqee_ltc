#include "stm32f1xx_hal.h"
#include "user_uart.h"
#include "user_io.h"
#include "modbus_udp.h"

#include <string.h>

extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;

static uint8_t uart2_receive_data = 0U;
static uint8_t uart3_receive_data = 0U;

void user_uart_init(void)
{
	HAL_UART_Receive_IT(&huart2, (uint8_t *)&uart2_receive_data, 1);	//串口接收一个字节，并通过中断返回结果
  HAL_UART_Receive_IT(&huart3, (uint8_t *)&uart3_receive_data, 1);
}

extern void lcd_printf(const char *fmt /*format*/, ...);

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart == &huart2)
	{
		huart2.Instance->DR = uart2_receive_data;
		while(__HAL_UART_GET_FLAG(&huart2, UART_FLAG_TXE) == RESET);
		huart3.Instance->DR = uart2_receive_data;
		while(__HAL_UART_GET_FLAG(&huart3, UART_FLAG_TXE) == RESET);
		HAL_UART_Receive_IT(&huart2, (uint8_t *)&uart2_receive_data, 1);
	}
	if (huart == &huart3)
	{
		huart3.Instance->DR = uart3_receive_data;
		while(__HAL_UART_GET_FLAG(&huart3, UART_FLAG_TXE) == RESET);
		HAL_UART_Receive_IT(&huart3, (uint8_t *)&uart3_receive_data, 1);
	}
}

void uart_send(uint8_t *data, uint16_t len)
{
	HAL_UART_Transmit_DMA(&huart3, data, len);
}

void uart_send_huart2(uint32_t tens,uint32_t uint)
{
	printf("tens=%d   ,    uints=%d   ,can_send=%d\n "  ,tens ,uint,udp_test_can.can_count);
}	

#pragma pack(1)

typedef struct bus485_control_pack
{	
	uint8_t head;
	uint8_t funcode;
	uint8_t high[3];
	uint8_t sp_seat;
	uint8_t sp_env;
	uint8_t seat_id;
	uint8_t end;
} bus485_control_pack_t;

#pragma pack()

bus485_control_pack_t pack = {.head=0xff, .end=0xee};

void bus485_control(uint8_t *high, uint8_t sp_seat, uint8_t sp_env, uint8_t seat_id)
{
	pack.funcode = 0xc2;
	memcpy(pack.high, high, sizeof(pack.high));
	pack.sp_seat = sp_seat;
	pack.sp_env = sp_env;
	pack.seat_id = seat_id;
	HAL_UART_Transmit_DMA(&huart3, (uint8_t *)&pack, sizeof(pack));	
}

int fputc(int ch, FILE *f)
{
	huart2.Instance->DR = ch;
	while(__HAL_UART_GET_FLAG(&huart2, UART_FLAG_TXE) == RESET);
	return ch; 
}

/*处理特效灯的显示模块*/
void special_checkout(uint8_t spcial_data)
{
	uint8_t i,spcial_temp;
	for(i=0;i<8;i++)
	{
		spcial_temp=spcial_data&(0x01<<i);
		if(spcial_temp!=0)  //有特效；
		{
			switch(i)
			{
				case 0:
					SPCIAL_1_ON();
					break;
				case 1:
					SPCIAL_2_ON();
					break;
				case 2:
					SPCIAL_3_ON();
					break;
				case 3:
					SPCIAL_4_ON();
					break;	
				case 4:
					SPCIAL_5_ON();
					break;
				case 5:
					SPCIAL_6_ON();
					break;
				case 6:
					SPCIAL_7_ON();
					break;
				case 7:
					SPCIAL_8_ON();
					break;					
			}	
		}	
		else
		{
			switch(i)
			{	
				case 0:
					SPCIAL_1_OFF();
					break;
				case 1:
					SPCIAL_2_OFF();
					break;
				case 2:
					SPCIAL_3_OFF();
					break;
				case 3:
					SPCIAL_4_OFF();
					break;	
				case 4:
					SPCIAL_5_OFF();
					break;
				case 5:
					SPCIAL_6_OFF();
					break;
				case 6:
					SPCIAL_7_OFF();
					break;
				case 7:
					SPCIAL_8_OFF();
					break;	
			}		
		}	
	}
}


