#include "stm32f1xx_hal.h"
#include "user_config.h"
#include "user_io.h"
#include "spi_flash.h"
#include "delay.h"

#define W25Q80 	0XEF13 	
#define W25Q16 	0XEF14
#define W25Q32 	0XEF15
#define W25Q64 	0XEF16
				 
/* control command table */
#define W25X_WRITE_ENABLE		0x06 
#define W25X_WRITE_DISABLE		0x04 
#define W25X_READ_STATUS_REG	0x05 
#define W25X_WRITE_STATUS_REG	0x01 
#define W25X_READ_DATA			0x03 
#define W25X_FAST_READ_DATA		0x0B 
#define W25X_FAST_READ_DUAL		0x3B 
#define W25X_PAGE_PROGRAM		0x02 
#define W25X_BLOCK_ERASE		0xD8 
#define W25X_SECTOR_ERASE		0x20 
#define W25X_CHIP_ERASE			0xC7 
#define W25X_POWER_DOWN			0xB9 
#define W25X_RELEASE_POWER_DOWN	0xAB 
#define W25X_DEVICE_ID			0xAB 
#define W25X_MANUFACT_DEVICE_ID	0x90 
#define W25X_JEDEC_DEVICE_ID	0x9F

static uint16_t spi_flash_read_id(void);  	    //读取FLASH ID
static uint8_t spi_flash_read_sr(void);        //读取状态寄存器 
static void spi_flash_write_sr(uint8_t sr);  	//写状态寄存器
static void spi_flash_write_enable(void);  //写使能 
static void spi_flash_write_disable(void);	//写保护
static void spi_flash_write_nocheck(uint8_t* p_buffer,uint32_t write_addr,uint16_t num_byte_to_write);
static void spi_flash_wait_busy(void);           //等待空闲

uint16_t spi_flash_type = W25Q64;//默认就是25Q64

void spi_flash_init(void)
{	
	spi_flash_type = spi_flash_read_id();//读取FLASH ID.  
	while(spi_flash_read_id()!=W25Q64)							//检测不到W25Q64
	{
		delay_ms(100);
		LED_TOGGLE();
	}
} 

//读取SPI_FLASH的状态寄存器
//BIT7  6   5   4   3   2   1   0
//SPR   RV  TB BP2 BP1 BP0 WEL BUSY
//SPR:默认0,状态寄存器保护位,配合WP使用
//TB,BP2,BP1,BP0:FLASH区域写保护设置
//WEL:写使能锁定
//BUSY:忙标记位(1,忙;0,空闲)
//默认:0x00
uint8_t spi_flash_read_sr(void)   
{  
	uint8_t byte=0;   
	SPI_FLASH_CS(0);                            //使能器件   
	spi2_read_write_byte(W25X_READ_STATUS_REG);    //发送读取状态寄存器命令    
	byte=spi2_read_write_byte(0Xff);             //读取一个字节  
	SPI_FLASH_CS(1);                            //取消片选     
	return byte;   
} 
//写SPI_FLASH状态寄存器
//只有SPR,TB,BP2,BP1,BP0(bit 7,5,4,3,2)可以写!!!
void spi_flash_write_sr(uint8_t sr)   
{   
	SPI_FLASH_CS(0);                            //使能器件   
	spi2_read_write_byte(W25X_WRITE_STATUS_REG);   //发送写取状态寄存器命令    
	spi2_read_write_byte(sr);               //写入一个字节  
	SPI_FLASH_CS(1);                            //取消片选     	      
}   
//SPI_FLASH写使能	
//将WEL置位   
void spi_flash_write_enable(void)   
{
	SPI_FLASH_CS(0);                            //使能器件   
    spi2_read_write_byte(W25X_WRITE_ENABLE);      //发送写使能  
	SPI_FLASH_CS(1);                            //取消片选     	      
} 
//SPI_FLASH写禁止	
//将WEL清零  
void spi_flash_write_disable(void)   
{  
	SPI_FLASH_CS(0);                            //使能器件   
    spi2_read_write_byte(W25X_WRITE_DISABLE);     //发送写禁止指令    
	SPI_FLASH_CS(1);                            //取消片选     	      
} 			    
//读取芯片ID W25X16的ID:0XEF14
uint16_t spi_flash_read_id(void)
{
	uint16_t temp = 0;	  
	SPI_FLASH_CS(0);				    
	spi2_read_write_byte(0x90);//发送读取ID命令	    
	spi2_read_write_byte(0x00); 	    
	spi2_read_write_byte(0x00); 	    
	spi2_read_write_byte(0x00); 	 			   
	temp|=spi2_read_write_byte(0xFF)<<8;  
	temp|=spi2_read_write_byte(0xFF);	 
	SPI_FLASH_CS(1);				    
	return temp;
}   		    
//读取SPI FLASH  
//在指定地址开始读取指定长度的数据
//p_buffer:数据存储区
//read_addr:开始读取的地址(24bit)
//num_byte_to_read:要读取的字节数(最大65535)
void spi_flash_read(uint8_t* p_buffer,uint32_t read_addr,uint16_t num_byte_to_read)   
{ 
 	uint16_t i;    												    
	SPI_FLASH_CS(0);                            //使能器件   
    spi2_read_write_byte(W25X_READ_DATA);         //发送读取命令   
    spi2_read_write_byte((uint8_t)((read_addr)>>16));  //发送24bit地址    
    spi2_read_write_byte((uint8_t)((read_addr)>>8));   
    spi2_read_write_byte((uint8_t)read_addr);   
    for(i=0;i<num_byte_to_read;i++)
	{ 
        p_buffer[i]=spi2_read_write_byte(0XFF);   //循环读数  
    }
	SPI_FLASH_CS(1);                            //取消片选     	      
}  
//SPI在一页(0~65535)内写入少于256个字节的数据
//在指定地址开始写入最大256字节的数据
//p_buffer:数据存储区
//write_addr:开始写入的地址(24bit)
//num_byte_to_write:要写入的字节数(最大256),该数不应该超过该页的剩余字节数!!!	 
void spi_flash_write_Page(uint8_t* p_buffer,uint32_t write_addr,uint16_t num_byte_to_write)
{
 	uint16_t i;  
    spi_flash_write_enable();                  //SET WEL 
	SPI_FLASH_CS(0);                            //使能器件   
    spi2_read_write_byte(W25X_PAGE_PROGRAM);      //发送写页命令   
    spi2_read_write_byte((uint8_t)((write_addr)>>16)); //发送24bit地址    
    spi2_read_write_byte((uint8_t)((write_addr)>>8));   
    spi2_read_write_byte((uint8_t)write_addr);   
    for(i=0;i<num_byte_to_write;i++)spi2_read_write_byte(p_buffer[i]);//循环写数  
	SPI_FLASH_CS(1);                            //取消片选 
	spi_flash_wait_busy();					   //等待写入结束
} 
//无检验写SPI FLASH 
//必须确保所写的地址范围内的数据全部为0XFF,否则在非0XFF处写入的数据将失败!
//具有自动换页功能 
//在指定地址开始写入指定长度的数据,但是要确保地址不越界!
//p_buffer:数据存储区
//write_addr:开始写入的地址(24bit)
//num_byte_to_write:要写入的字节数(最大65535)
//CHECK OK
void spi_flash_write_nocheck(uint8_t* p_buffer,uint32_t write_addr,uint16_t num_byte_to_write)   
{ 			 		 
	uint16_t pageremain;	   
	pageremain=256-write_addr%256; //单页剩余的字节数		 	    
	if(num_byte_to_write<=pageremain)pageremain=num_byte_to_write;//不大于256个字节
	while(1)
	{	   
		spi_flash_write_Page(p_buffer,write_addr,pageremain);
		if(num_byte_to_write==pageremain)break;//写入结束了
	 	else //num_byte_to_write>pageremain
		{
			p_buffer+=pageremain;
			write_addr+=pageremain;	

			num_byte_to_write-=pageremain;			  //减去已经写入了的字节数
			if(num_byte_to_write>256)pageremain=256; //一次可以写入256个字节
			else pageremain=num_byte_to_write; 	  //不够256个字节了
		}
	};	    
} 
//写SPI FLASH  
//在指定地址开始写入指定长度的数据
//该函数带擦除操作!
//p_buffer:数据存储区
//write_addr:开始写入的地址(24bit)
//num_byte_to_write:要写入的字节数(最大65535)  		   
uint8_t spi_flash_buf[4096];
void spi_flash_write(uint8_t* p_buffer,uint32_t write_addr,uint16_t num_byte_to_write)   
{ 
	uint32_t secpos;
	uint16_t secoff;
	uint16_t secremain;	   
 	uint16_t i;    

	secpos=write_addr/4096;//扇区地址 0~511 for w25x16
	secoff=write_addr%4096;//在扇区内的偏移
	secremain=4096-secoff;//扇区剩余空间大小   

	if(num_byte_to_write<=secremain)secremain=num_byte_to_write;//不大于4096个字节
	while(1) 
	{	
		spi_flash_read(spi_flash_buf,secpos*4096,4096);//读出整个扇区的内容
		for(i=0;i<secremain;i++)//校验数据
		{
			if(spi_flash_buf[secoff+i]!=0XFF)break;//需要擦除  	  
		}
		if(i<secremain)//需要擦除
		{
			spi_flash_erase_sector(secpos);//擦除这个扇区
			for(i=0;i<secremain;i++)	   //复制
			{
				spi_flash_buf[i+secoff]=p_buffer[i];	  
			}
			spi_flash_write_nocheck(spi_flash_buf,secpos*4096,4096);//写入整个扇区  

		}else spi_flash_write_nocheck(p_buffer,write_addr,secremain);//写已经擦除了的,直接写入扇区剩余区间. 				   
		if(num_byte_to_write==secremain)break;//写入结束了
		else//写入未结束
		{
			secpos++;//扇区地址增1
			secoff=0;//偏移位置为0 	 

		   	p_buffer+=secremain;  //指针偏移
			write_addr+=secremain;//写地址偏移	   
		   	num_byte_to_write-=secremain;				//字节数递减
			if(num_byte_to_write>4096)secremain=4096;	//下一个扇区还是写不完
			else secremain=num_byte_to_write;			//下一个扇区可以写完了
		}	 
	};	 	 
}
//擦除整个芯片
//整片擦除时间:
//W25X16:25s 
//W25X32:40s 
//W25X64:40s 
//等待时间超长...
void spi_flash_erase_chip(void)   
{                                             
    spi_flash_write_enable();                  //SET WEL 
    spi_flash_wait_busy();   
  	SPI_FLASH_CS(0);                            //使能器件   
    spi2_read_write_byte(W25X_CHIP_ERASE);        //发送片擦除命令  
	SPI_FLASH_CS(1);                            //取消片选     	      
	spi_flash_wait_busy();   				   //等待芯片擦除结束
}   
//擦除一个扇区
//dst_addr:扇区地址 0~511 for w25x16
//擦除一个山区的最少时间:150ms
void spi_flash_erase_sector(uint32_t dst_addr)   
{   
	dst_addr*=4096;
    spi_flash_write_enable();                  //SET WEL 	 
    spi_flash_wait_busy();   
  	SPI_FLASH_CS(0);                            //使能器件   
    spi2_read_write_byte(W25X_SECTOR_ERASE);      //发送扇区擦除指令 
    spi2_read_write_byte((uint8_t)((dst_addr)>>16));  //发送24bit地址    
    spi2_read_write_byte((uint8_t)((dst_addr)>>8));   
    spi2_read_write_byte((uint8_t)dst_addr);  
	SPI_FLASH_CS(1);                            //取消片选     	      
    spi_flash_wait_busy();   				   //等待擦除完成
}  
//等待空闲
void spi_flash_wait_busy(void)   
{   
	while ((spi_flash_read_sr()&0x01)==0x01);   // 等待BUSY位清空
}  
//进入掉电模式
void spi_flash_powerdown(void)   
{ 
  	SPI_FLASH_CS(0);                            //使能器件   
    spi2_read_write_byte(W25X_POWER_DOWN);        //发送掉电命令  
	SPI_FLASH_CS(1);                            //取消片选     	      
    delay_us(3);                               //等待TPD  
}   
//唤醒
void spi_flash_wakeup(void)   
{  
  	SPI_FLASH_CS(0);                            //使能器件   
    spi2_read_write_byte(W25X_RELEASE_POWER_DOWN);   //  send W25X_POWER_DOWN command 0xAB    
	SPI_FLASH_CS(1);                            //取消片选     	      
    delay_us(3);                               //等待TRES1
}   
