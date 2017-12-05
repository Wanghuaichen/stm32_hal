#ifndef __AF_DEFAULT_H
#define __AF_DEFAULT_H

#include "stm32f1xx_hal.h"

#define DEBUG_ENABLE         1

/*FAFTS---[取消SD_DRIVER const关键字]*/
#define FAFTS_PR		0   
#define I2C_PR			0	/*1=hard 2=soft*/
#define KEY_PR			0
#define KEYCAP_PR		0
#define LCD_PR			0
#define LED_PR			0
#define SD_PR	        0
#define SPI_PR	        0

#define DEBUG(fmt,arg...)          do{\
                                          if(DEBUG_ENABLE)\
                                          printf("<<-DEBUG->> [%d]"fmt"\n",__LINE__, ##arg);\
                                          }while(0)
#if FAFTS_PR
	#include "../Own/af_fafts.h" 
#endif

#if I2C_PR	
	#include  "../Own/af_i2c.h"
#elif I2C_PR	==	2
	#include  "../Own/af_i2c_sw.h"
#endif

#if KEY_PR
	#include  "../Own/af_key.h"
#endif

#if KEYCAP_PR
	#include  "../Own/af_key.h"
#endif

#if LCD_PR
	#include "../Own/af_lcd.h"
#endif

#if LED_PR
	#include  "../Own/af_led.h"
#endif
#if SD_PR
	#include  "../Own/af_sd.h"
#endif
#if SPI_PR
	#include  "../Own/af_spi.h"
#endif

#endif
