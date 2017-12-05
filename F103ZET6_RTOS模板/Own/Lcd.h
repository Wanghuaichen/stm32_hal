#ifndef __AF_LCD_H
#define __AF_LCD_H

#include "ascii.h"
#include "../Own/af_default.h"


/***************************************************************************************
2^26 =0X0400 0000 = 64MB,ÿ�� BANK ��4*64MB = 256MB
64MB:FSMC_Bank1_NORSRAM1:0X6000 0000 ~ 0X63FF FFFF
64MB:FSMC_Bank1_NORSRAM2:0X6400 0000 ~ 0X67FF FFFF
64MB:FSMC_Bank1_NORSRAM3:0X6800 0000 ~ 0X6BFF FFFF
64MB:FSMC_Bank1_NORSRAM4:0X6C00 0000 ~ 0X6FFF FFFF

ѡ��BANK1-BORSRAM4 ���� TFT����ַ��ΧΪ0X6C00 0000 ~ 0X6FFF FFFF
FSMC_A23 ��LCD��DC(�Ĵ���/����ѡ��)��
�Ĵ�������ַ = 0X6C00 0000
RAM����ַ = 0X6D00 0000 = 0X6C00 0000+2^23*2 = 0X6C00 0000 + 0X100 0000 = 0X6D00 0000
��ѡ��ͬ�ĵ�ַ��ʱ����ַҪ���¼���  
****************************************************************************************/
#define FAFTS_SD        1
#define FAFTS_FLASH     (1-FAFTS_SD)
/*��Ϣ���*/
#define DEBUG_STATE         1
#define GBK_1616_ADDR  10*4096

/******************************* LCD ��ʾ���� FSMC �������� ***************************/
#define      LCD_CMD         ( ( uint32_t ) 0x6C000000 )	     //FSMC_Bank1_NORSRAM1����LCD��������ĵ�ַ
#define      LCD_DATA        ( ( uint32_t ) 0x6D000000 )      //FSMC_Bank1_NORSRAM1����LCD���ݲ����ĵ�ַ      

/***************** ILI934 ��ʾ��ȫ��Ĭ�ϣ�ɨ�跽��Ϊ1ʱ������Ⱥ����߶� *********************/
#define      LCD_Column		240     
#define      LCD_Line		320     

/***************************** ILI934 ��ʾ�������ʼ������������� ***************************/
#define      LCD_WindowX		    0     //��ʼ���X����
#define      LCD_WindowY		    0     //��ʼ���Y����

/***************************** �� ILI934 ��ʾ������ʾ���ַ��Ĵ�С ***************************/
#define      WIDTH_EN		            8	    //Ӣ���ַ���� 
#define      HEIGHT_EN		            16		  //Ӣ���ַ��߶� 
#define      WIDTH_CH		            16	    //�����ַ���� 
#define      HEIGHT_CH		            16		  //�����ַ��߶� 


/******************************* ���� ILI934 ��ʾ��������ɫ ********************************/
#define      WHITE		 		           0xFFFF	   //��ɫ
#define      BLACK                         0x0000	   //��ɫ 
#define      GREY                          0xF7DE	   //��ɫ 
#define      BLUE                          0x001F	   //��ɫ 
#define      BLUE2                         0x051F	   //ǳ��ɫ 
#define      RED                           0xF800	   //��ɫ 
#define      MAGENTA                       0xF81F	   //����ɫ�����ɫ 
#define      GREEN                         0x07E0	   //��ɫ 
#define      CYAN                          0x7FFF	   //����ɫ����ɫ 
#define      YELLOW                        0xFFE0	   //��ɫ 
#define      BRED                          0xF81F
#define      GRED                          0xFFE0
#define      GBLUE                         0x07FF



/******************************* ���� ILI934 �������� ********************************/
#define      CMD_SetX		 		    0x2A	     //����X����
#define      CMD_SetY		 		    0x2B	     //����Y����
#define      CMD_SetPixel		 		0x2C	     //�������

/* R(8bit) G(8bit) B(8bit)  --> RGB565  */
#define RGB24TORGB16(R,G,B) ((R>>3)<<11)|((G>>2)<<5)|(B>>3)


/********************************** ���� ILI934 ���� ***************************************/
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
