#ifndef __AF_LCD_H
#define __AF_LCD_H

#include "ascii.h"
#include "../Own/af_default.h"


/***************************************************************************************
2^26 =0X0400 0000 = 64MB,每个 BANK 有4*64MB = 256MB
64MB:FSMC_Bank1_NORSRAM1:0X6000 0000 ~ 0X63FF FFFF
64MB:FSMC_Bank1_NORSRAM2:0X6400 0000 ~ 0X67FF FFFF
64MB:FSMC_Bank1_NORSRAM3:0X6800 0000 ~ 0X6BFF FFFF
64MB:FSMC_Bank1_NORSRAM4:0X6C00 0000 ~ 0X6FFF FFFF

选择BANK1-BORSRAM4 连接 TFT，地址范围为0X6C00 0000 ~ 0X6FFF FFFF
FSMC_A23 接LCD的DC(寄存器/数据选择)脚
寄存器基地址 = 0X6C00 0000
RAM基地址 = 0X6D00 0000 = 0X6C00 0000+2^23*2 = 0X6C00 0000 + 0X100 0000 = 0X6D00 0000
当选择不同的地址线时，地址要重新计算  
****************************************************************************************/
#define FAFTS_SD        1
#define FAFTS_FLASH     (1-FAFTS_SD)
/*信息输出*/
#define DEBUG_STATE         1
#define GBK_1616_ADDR  10*4096

/******************************* LCD 显示屏的 FSMC 参数定义 ***************************/
#define      LCD_CMD         ( ( uint32_t ) 0x6C000000 )	     //FSMC_Bank1_NORSRAM1用于LCD命令操作的地址
#define      LCD_DATA        ( ( uint32_t ) 0x6D000000 )      //FSMC_Bank1_NORSRAM1用于LCD数据操作的地址      

/***************** ILI934 显示屏全屏默认（扫描方向为1时）最大宽度和最大高度 *********************/
#define      LCD_Column		240     
#define      LCD_Line		320     

/***************************** ILI934 显示区域的起始坐标和总行列数 ***************************/
#define      LCD_WindowX		    0     //起始点的X坐标
#define      LCD_WindowY		    0     //起始点的Y坐标

/***************************** 在 ILI934 显示屏上显示的字符的大小 ***************************/
#define      WIDTH_EN		            8	    //英文字符宽度 
#define      HEIGHT_EN		            16		  //英文字符高度 
#define      WIDTH_CH		            16	    //中文字符宽度 
#define      HEIGHT_CH		            16		  //中文字符高度 


/******************************* 定义 ILI934 显示屏常用颜色 ********************************/
#define      WHITE		 		           0xFFFF	   //白色
#define      BLACK                         0x0000	   //黑色 
#define      GREY                          0xF7DE	   //灰色 
#define      BLUE                          0x001F	   //蓝色 
#define      BLUE2                         0x051F	   //浅蓝色 
#define      RED                           0xF800	   //红色 
#define      MAGENTA                       0xF81F	   //红紫色，洋红色 
#define      GREEN                         0x07E0	   //绿色 
#define      CYAN                          0x7FFF	   //蓝绿色，青色 
#define      YELLOW                        0xFFE0	   //黄色 
#define      BRED                          0xF81F
#define      GRED                          0xFFE0
#define      GBLUE                         0x07FF



/******************************* 定义 ILI934 常用命令 ********************************/
#define      CMD_SetX		 		    0x2A	     //设置X坐标
#define      CMD_SetY		 		    0x2B	     //设置Y坐标
#define      CMD_SetPixel		 		0x2C	     //填充像素

/* R(8bit) G(8bit) B(8bit)  --> RGB565  */
#define RGB24TORGB16(R,G,B) ((R>>3)<<11)|((G>>2)<<5)|(B>>3)


/********************************** 声明 ILI934 函数 ***************************************/
__inline void                 LCD_Write_Cmd           ( uint16_t uscmd );
__inline void                 LCD_Write_Data          ( uint16_t data );
__inline uint16_t             LCD_Read_Data           ( void );
void                     LCD_Init                    ( uint16_t Bg_Colour=BLACK );
void                     LCD_Rst                     ( void );
void                     LCD_BL                      ( FunctionalState enumState );
void                     LCD_GramScan                ( uint8_t MODE );
void                     LCD_ClearWindow             ( uint16_t X, uint16_t Y, uint16_t WIDTH, uint16_t HEIGTH, uint16_t Colour );
void                     LCD_ClearScreen             (uint16_t Colour);
void                     LCD_SetPointPixel           ( uint16_t X, uint16_t Y, uint16_t Colour );
uint16_t                 LCD_GetPointPixel           ( uint16_t X , uint16_t Y );
void                     LCD_DrawLine                ( uint16_t X1, uint16_t Y1, uint16_t X2, uint16_t Y2, uint16_t Colour );
void                     LCD_DrawRectangle           ( uint16_t X, uint16_t Y, uint16_t WIDTH, uint16_t HEIGTH, uint16_t Colour, uint8_t Filled );
void                     LCD_DrawCircle              ( uint16_t X_Center, uint16_t Y_Center, uint16_t Radius, uint16_t Colour, uint8_t Filled );
void                     LCD_Show                    ( uint16_t X, uint16_t Y, const uint8_t * pStr, uint16_t Bg_Colour=BLACK, uint16_t Fg_Colour=WHITE);
void                     LCD_IMG                     ( uint16_t x, uint16_t y,char *pic_name);
extern void SPI_FLASH_BufferRead(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead);


#endif
