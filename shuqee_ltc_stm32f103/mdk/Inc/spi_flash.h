#ifndef __SPI_FLASH_H
#define __SPI_FLASH_H

#include "stm32f1xx_hal.h"
#include "user_config.h"
#include "user_spi.h"

extern void spi_flash_init(void);
extern void spi_flash_read(uint8_t* p_buffer,uint32_t read_addr,uint16_t num_byte_to_read);   //读取flash
extern void spi_flash_write(uint8_t* p_buffer,uint32_t write_addr,uint16_t num_byte_to_write);//写入flash
extern void spi_flash_erase_chip(void);    	  //整片擦除
extern void spi_flash_erase_sector(uint32_t dst_addr);//扇区擦除
extern void spi_flash_powerdown(void);           //进入掉电模式
extern void spi_flash_wakeup(void);			  //唤醒

#endif /* __SPI_FLASH_H */
