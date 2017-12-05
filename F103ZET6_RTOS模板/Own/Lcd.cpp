#include "../Own/af_lcd.h"




static void                   LCD_Delay               ( __IO uint32_t nCount );
static void                   LCD_REG_Config          ( void );
static void                   LCD_SetCursor           ( uint16_t X, uint16_t Y );
static __inline void          LCD_FillColor           ( uint32_t ulAmout_Point, uint16_t Colour );
static uint16_t               LCD_Read_PixelData      ( void );
static void                   LCD_OpenWindow          ( uint16_t X, uint16_t Y, uint16_t WIDTH, uint16_t HEIGTH );


/**
  * @brief  ��LCDд������
  * @param  usCmd :Ҫд��������Ĵ�����ַ��
  * @retval ��
  */	
__inline void LCD_Write_Cmd ( uint16_t cmd )
{
	* ( __IO uint16_t * ) ( LCD_CMD ) = cmd;
	
}


/**
  * @brief  ��LCDд������
  * @param  data :Ҫд�������
  * @retval ��
  */	
__inline void LCD_Write_Data ( uint16_t data )
{
	* ( __IO uint16_t * ) ( LCD_DATA ) = data;
	
}


/**
  * @brief  ��LCD��ȡ����
  * @param  ��
  * @retval ��ȡ��������
  */	
__inline uint16_t LCD_Read_Data ( void )
{
	return ( * ( __IO uint16_t * ) ( LCD_DATA ) );
	
}


/**
  * @brief  ���� LCD ����ʱ����
  * @param  nCount ����ʱ����ֵ
  * @retval ��
  */	
static void LCD_Delay ( __IO uint32_t nCount )
{
  for ( ; nCount != 0; nCount -- );
	
}


/**
 * @brief  ��ʼ��LCD�Ĵ���
 * @param  ��
 * @retval ��
 */
static void LCD_REG_Config ( void )
{
	/*  Power control B (CFh)  */

	LCD_Write_Cmd ( 0xCF  );
	LCD_Write_Data ( 0x00  );
	LCD_Write_Data ( 0x81  );
	LCD_Write_Data ( 0x30  );
	
	/*  Power on sequence control (EDh) */
	
	LCD_Write_Cmd ( 0xED );
	LCD_Write_Data ( 0x64 );
	LCD_Write_Data ( 0x03 );
	LCD_Write_Data ( 0x12 );
	LCD_Write_Data ( 0x81 );
	
	/*  Driver timing control A (E8h) */
	
	LCD_Write_Cmd ( 0xE8 );
	LCD_Write_Data ( 0x85 );
	LCD_Write_Data ( 0x10 );
	LCD_Write_Data ( 0x78 );
	
	/*  Power control A (CBh) */
	
	LCD_Write_Cmd ( 0xCB );
	LCD_Write_Data ( 0x39 );
	LCD_Write_Data ( 0x2C );
	LCD_Write_Data ( 0x00 );
	LCD_Write_Data ( 0x34 );
	LCD_Write_Data ( 0x02 );
	
	/* Pump ratio control (F7h) */
	
	LCD_Write_Cmd ( 0xF7 );
	LCD_Write_Data ( 0x20 );
	
	/* Driver timing control B */
	
	LCD_Write_Cmd ( 0xEA );
	LCD_Write_Data ( 0x00 );
	LCD_Write_Data ( 0x00 );
	
	/* Frame Rate Control (In Normal Mode/Full Colors) (B1h) */
	
	LCD_Write_Cmd ( 0xB1 );
	LCD_Write_Data ( 0x00 );
	LCD_Write_Data ( 0x1B );
	
	/*  Display Function Control (B6h) */
	
	LCD_Write_Cmd ( 0xB6 );
	LCD_Write_Data ( 0x0A );
	LCD_Write_Data ( 0xA2 );
	
	/* Power Control 1 (C0h) */
	
	LCD_Write_Cmd ( 0xC0 );
	LCD_Write_Data ( 0x35 );
	
	/* Power Control 2 (C1h) */
	
	LCD_Write_Cmd ( 0xC1 );
	LCD_Write_Data ( 0x11 );
	
	/* VCOM Control 1 (C5h) */
	LCD_Write_Cmd ( 0xC5 );
	LCD_Write_Data ( 0x45 );
	LCD_Write_Data ( 0x45 );
	
	/*  VCOM Control 2 (C7h)  */
	LCD_Write_Cmd ( 0xC7 );
	LCD_Write_Data ( 0xA2 );
	
	/* Enable 3G (F2h) */
	LCD_Write_Cmd ( 0xF2 );
	LCD_Write_Data ( 0x00 );
	
	/* Gamma Set (26h) */
	LCD_Write_Cmd ( 0x26 );
	LCD_Write_Data ( 0x01 );
	
	
	/* Positive Gamma Correction */
	LCD_Write_Cmd ( 0xE0 ); //Set Gamma
	LCD_Write_Data ( 0x0F );
	LCD_Write_Data ( 0x26 );
	LCD_Write_Data ( 0x24 );
	LCD_Write_Data ( 0x0B );
	LCD_Write_Data ( 0x0E );
	LCD_Write_Data ( 0x09 );
	LCD_Write_Data ( 0x54 );
	LCD_Write_Data ( 0xA8 );
	LCD_Write_Data ( 0x46 );
	LCD_Write_Data ( 0x0C );
	LCD_Write_Data ( 0x17 );
	LCD_Write_Data ( 0x09 );
	LCD_Write_Data ( 0x0F );
	LCD_Write_Data ( 0x07 );
	LCD_Write_Data ( 0x00 );
	
	/* Negative Gamma Correction (E1h) */
	LCD_Write_Cmd ( 0XE1 ); //Set Gamma
	LCD_Write_Data ( 0x00 );
	LCD_Write_Data ( 0x19 );
	LCD_Write_Data ( 0x1B );
	LCD_Write_Data ( 0x04 );
	LCD_Write_Data ( 0x10 );
	LCD_Write_Data ( 0x07 );
	LCD_Write_Data ( 0x2A );
	LCD_Write_Data ( 0x47 );
	LCD_Write_Data ( 0x39 );
	LCD_Write_Data ( 0x03 );
	LCD_Write_Data ( 0x06 );
	LCD_Write_Data ( 0x06 );
	LCD_Write_Data ( 0x30 );
	LCD_Write_Data ( 0x38 );
	LCD_Write_Data ( 0x0F );
	
	/* memory access control set */
	
	LCD_Write_Cmd ( 0x36 ); 	
	LCD_Write_Data ( 0xC8 );    /*����  ���Ͻǵ� (���)�����½� (�յ�)ɨ�跽ʽ*/
	
	
	/* column address control set */
	LCD_Write_Cmd ( CMD_SetX ); 
	LCD_Write_Data ( 0x00 );
	LCD_Write_Data ( 0x00 );
	LCD_Write_Data ( 0x00 );
	LCD_Write_Data ( 0xEF );
	
	/* page address control set */
	
	LCD_Write_Cmd ( CMD_SetY ); 
	LCD_Write_Data ( 0x00 );
	LCD_Write_Data ( 0x00 );
	LCD_Write_Data ( 0x01 );
	LCD_Write_Data ( 0x3F );
	
	/*  Pixel Format Set (3Ah)  */
	
	LCD_Write_Cmd ( 0x3a ); 
	LCD_Write_Data ( 0x55 );
	
	/* Sleep Out (11h)  */
	LCD_Write_Cmd ( 0x11 );	
	LCD_Delay ( 0xAFFf<<2 );
	
	
	/* Display ON (29h) */
	LCD_Write_Cmd ( 0x29 ); 
	
	
}


/**
 * @brief  LCD����LED����
 * @param  enumState �������Ƿ�ʹ�ܱ���LED
  *   �ò���Ϊ����ֵ֮һ��
  *     @arg ENABLE :ʹ�ܱ���LED
  *     @arg DISABLE :���ñ���LED
 * @retval ��
 */
void LCD_BL( FunctionalState enumState )
{
	if ( enumState )
		HAL_GPIO_WritePin ( GPIOG, GPIO_PIN_6,GPIO_PIN_RESET );
	else
		HAL_GPIO_WritePin ( GPIOG, GPIO_PIN_6,GPIO_PIN_SET );	
}



/**
 * @brief  LCD �����λ
 * @param  ��
 * @retval ��
 */
 void LCD_Rst ( void )
{			
	HAL_GPIO_WritePin ( GPIOG, GPIO_PIN_11,GPIO_PIN_RESET );	 //�͵�ƽ��λ
	LCD_Delay ( 0xAFFf<<2 ); 					   
	HAL_GPIO_WritePin ( GPIOG, GPIO_PIN_11,GPIO_PIN_SET );		 	 
	LCD_Delay ( 0xAFFf<<2 ); 		
}

/**
 * @brief  LCD��ʼ�����������Ҫ�õ�lcd��һ��Ҫ�����������
 * @param  ��
 * @retval ��
 */
void LCD_Init ( uint16_t Bg_Colour)
{
	LCD_BL ( ENABLE );      //����LCD�����
	LCD_Rst ();
	LCD_REG_Config ();
    LCD_ClearScreen(Bg_Colour);
    
}


/**
 * @brief  ����LCD��GRAM��ɨ�跽�� 
 * @param  ucOption ��ѡ��GRAM��ɨ�跽�� 
  *   �ò���Ϊ����ֵ֮һ��
  *     @arg 1 :���Ͻ�->���½�
  *     @arg 2 :���½�->���Ͻ�
  *     @arg 3 :���½�->���Ͻ�
  *     @arg 4 :���Ͻ�->���½�
 * @retval ��
 */
void LCD_GramScan ( uint8_t MODE )
{	
	switch ( MODE )
	{
		case 1:
//   ���Ͻ�->���½�      ��ʾ��Ӣ��ʱ�õ�������ģʽ 
//		____ x(240)       //Һ������Ϊ�ο���
//	 |  
//	 |	y(320)        
		  
			LCD_Write_Cmd ( 0x36 ); 
			LCD_Write_Data ( 0xC8 );   
			LCD_Write_Cmd ( CMD_SetX ); 
			LCD_Write_Data ( 0x00 );	/* x start */	
			LCD_Write_Data ( 0x00 );
			LCD_Write_Data ( 0x00 );  /* x end */	
			LCD_Write_Data ( 0xEF );

			LCD_Write_Cmd ( CMD_SetY ); 
			LCD_Write_Data ( 0x00 );	/* y start */  
			LCD_Write_Data ( 0x00 );
			LCD_Write_Data ( 0x01 );	/* y end */   
			LCD_Write_Data ( 0x3F );
					
		  break;
		
		case 2:
//		���½�->���Ͻ�      ��ʾ����ͷͼ��ʱ�õ�������ģʽ 
//		|x(320)            //Һ������Ϊ�ο���
//		|
//		|___ y(240)
		  
			LCD_Write_Cmd ( 0x36 ); 
			LCD_Write_Data ( 0x68 );	
			LCD_Write_Cmd ( CMD_SetX ); 
			LCD_Write_Data ( 0x00 );
			LCD_Write_Data ( 0x00 );
			LCD_Write_Data ( 0x01 );
			LCD_Write_Data ( 0x3F );	

			LCD_Write_Cmd ( CMD_SetY ); 
			LCD_Write_Data ( 0x00 );
			LCD_Write_Data ( 0x00 );
			LCD_Write_Data ( 0x00 );
			LCD_Write_Data ( 0xEF );		
		
		  break;
		
		case 3:
//		���½�->���Ͻ�        ��ʾBMPͼƬʱ�õ�������ģʽ 
//		           |x(320)   //Һ������Ϊ�ο���
//		           |           
//		y(240) ____|
		
			LCD_Write_Cmd ( 0x36 ); 
			LCD_Write_Data ( 0x28 );	
			LCD_Write_Cmd ( CMD_SetX ); 
			LCD_Write_Data ( 0x00 );
			LCD_Write_Data ( 0x00 );
			LCD_Write_Data ( 0x01 );
			LCD_Write_Data ( 0x3F );	

			LCD_Write_Cmd ( CMD_SetY ); 
			LCD_Write_Data ( 0x00 );
			LCD_Write_Data ( 0x00 );
			LCD_Write_Data ( 0x00 );
			LCD_Write_Data ( 0xEF );			
		  
		  break;

		case 4:
//		���½ǽ�->���Ͻ�
//		|y(320)              //Һ������Ϊ�ο���
//		|
//		|___ x(240)			
		  
			LCD_Write_Cmd ( 0x36 ); 
			LCD_Write_Data ( 0x48 );	
			LCD_Write_Cmd ( CMD_SetX ); 
			LCD_Write_Data ( 0x00 );
			LCD_Write_Data ( 0x00 );
			LCD_Write_Data ( 0x00 );
			LCD_Write_Data ( 0xEF );	

			LCD_Write_Cmd ( CMD_SetY ); 
			LCD_Write_Data ( 0x00 );
			LCD_Write_Data ( 0x00 );
			LCD_Write_Data ( 0x01 );
			LCD_Write_Data ( 0x3F );				
	    break;		
	}	
	/* write gram start */
	LCD_Write_Cmd ( CMD_SetPixel );	
}


/**
 * @brief  ��LCD��ʾ���Ͽ���һ������
 * @param  X �����ض�ɨ�跽���´��ڵ����X����
 * @param  Y �����ض�ɨ�跽���´��ڵ����Y����
 * @param  WIDTH �����ڵĿ��
 * @param  HEIGTH �����ڵĸ߶�
 * @retval ��
 */
static void LCD_OpenWindow ( uint16_t X, uint16_t Y, uint16_t WIDTH, uint16_t HEIGTH )
{	
	LCD_Write_Cmd ( CMD_SetX ); 				 /* ����X���� */
	LCD_Write_Data ( X >> 8  );	 /* �ȸ�8λ��Ȼ���8λ */
	LCD_Write_Data ( X & 0xff  );	 /* ������ʼ��ͽ�����*/
	LCD_Write_Data ( ( X + WIDTH - 1 ) >> 8  );
	LCD_Write_Data ( ( X + WIDTH - 1 ) & 0xff  );

	LCD_Write_Cmd ( CMD_SetY ); 			     /* ����Y����*/
	LCD_Write_Data ( Y >> 8  );
	LCD_Write_Data ( Y & 0xff  );
	LCD_Write_Data ( ( Y + HEIGTH - 1 ) >> 8 );
	LCD_Write_Data ( ( Y + HEIGTH - 1) & 0xff );	
}


/**
 * @brief  �趨LCD�Ĺ������
 * @param  X �����ض�ɨ�跽���¹���X����
 * @param  Y �����ض�ɨ�跽���¹���Y����
 * @retval ��
 */
static void LCD_SetCursor ( uint16_t X, uint16_t Y )	
{
	LCD_OpenWindow ( X, Y, 1, 1 );
}


/**
 * @brief  ��LCD��ʾ������ĳһ��ɫ������ص�
 * @param  ulAmout_Point ��Ҫ�����ɫ�����ص������Ŀ
 * @param  Colour ����ɫ
 * @retval ��
 */
static __inline void LCD_FillColor ( uint32_t ulAmout_Point, uint16_t Colour )
{
	uint32_t i = 0;
	
	
	/* memory write */
	LCD_Write_Cmd ( CMD_SetPixel );	
		
	for ( i = 0; i < ulAmout_Point; i ++ )
		LCD_Write_Data ( Colour );
		
	
}


/**
 * @brief  ��LCD��ʾ����ĳһ������ĳ����ɫ��������
 * @param  X �����ض�ɨ�跽���´��ڵ����X����
 * @param  Y �����ض�ɨ�跽���´��ڵ����Y����
 * @param  WIDTH �����ڵĿ��
 * @param  HEIGTH �����ڵĸ߶�
 * @param  Colour ����ɫ
 * @retval ��
 */
void LCD_ClearWindow ( uint16_t X, uint16_t Y, uint16_t WIDTH, uint16_t HEIGTH, uint16_t Colour )
{
	LCD_OpenWindow ( X, Y, WIDTH, HEIGTH );
	LCD_FillColor ( WIDTH * HEIGTH, Colour );			
}


void LCD_ClearScreen(uint16_t Colour)
{
  	LCD_OpenWindow ( 0, 0, LCD_Column, LCD_Line );
	LCD_FillColor ( LCD_Column * LCD_Line, Colour );  
}


/**
 * @brief  ��LCD��ʾ����ĳһ����ĳ����ɫ�������
 * @param  X �����ض�ɨ�跽���¸õ��X����
 * @param  Y �����ض�ɨ�跽���¸õ��Y����
 * @param  Colour ������������ɫ
 * @retval ��
 */
void LCD_SetPointPixel ( uint16_t X, uint16_t Y, uint16_t Colour )	
{	
	if ( ( X < LCD_Column ) && ( Y < LCD_Line ) )
  {
		LCD_SetCursor ( X, Y );		
		LCD_FillColor ( 1, Colour );
	}	
}


/**
 * @brief  ��ȡLCD GRAN ��һ����������
 * @param  ��
 * @retval ��������
 */
static uint16_t LCD_Read_PixelData ( void )	
{	
	uint16_t usR=0, usG=0, usB=0 ;	
	LCD_Write_Cmd ( 0x2E );   /* ������ */	
	usR = LCD_Read_Data (); 	/*FIRST READ OUT DUMMY DATA*/	
	usR = LCD_Read_Data ();  	/*READ OUT RED DATA  */
	usB = LCD_Read_Data ();  	/*READ OUT BLUE DATA*/
	usG = LCD_Read_Data ();  	/*READ OUT GREEN DATA*/		
  return ( ( ( usR >> 11 ) << 11 ) | ( ( usG >> 10 ) << 5 ) | ( usB >> 11 ) );
	
}


/**
 * @brief  ��ȡ LCD ��ʾ����ĳһ����������������
 * @param  X �����ض�ɨ�跽���¸õ��X����
 * @param  Y �����ض�ɨ�跽���¸õ��Y����
 * @retval ��������
 */
uint16_t LCD_GetPointPixel ( uint16_t X, uint16_t Y )
{ 
	uint16_t PixelData;
	LCD_SetCursor ( X, Y );	
	PixelData = LCD_Read_PixelData ();	
	return PixelData;	
}


/**
 * @brief  �� LCD ��ʾ����ʹ�� Bresenham �㷨���߶� 
 * @param  X1 �����ض�ɨ�跽�����߶ε�һ���˵�X����
 * @param  Y1 �����ض�ɨ�跽�����߶ε�һ���˵�Y����
 * @param  X2 �����ض�ɨ�跽�����߶ε���һ���˵�X����
 * @param  Y2 �����ض�ɨ�跽�����߶ε���һ���˵�Y����
 * @param  Colour ���߶ε���ɫ
 * @retval ��
 */
void LCD_DrawLine ( uint16_t X1, uint16_t Y1, uint16_t X2, uint16_t Y2, uint16_t Colour )
{
	uint16_t us; 
	uint16_t X_Current, Y_Current;
	
	int32_t lError_X = 0, lError_Y = 0, lDelta_X, lDelta_Y, lDistance; 
	int32_t lIncrease_X, lIncrease_Y; 	
	
	
	lDelta_X = X2 - X1; //������������ 
	lDelta_Y = Y2 - Y1; 
	
	X_Current = X1; 
	Y_Current = Y1; 
	
	
	if ( lDelta_X > 0 ) 
		lIncrease_X = 1; //���õ������� 
	
	else if ( lDelta_X == 0 ) 
		lIncrease_X = 0;//��ֱ�� 
	
	else 
  { 
    lIncrease_X = -1;
    lDelta_X = - lDelta_X;
  } 

	
	if ( lDelta_Y > 0 )
		lIncrease_Y = 1; 
	
	else if ( lDelta_Y == 0 )
		lIncrease_Y = 0;//ˮƽ�� 
	
	else 
  {
    lIncrease_Y = -1;
    lDelta_Y = - lDelta_Y;
  } 

	
	if (  lDelta_X > lDelta_Y )
		lDistance = lDelta_X; //ѡȡ�������������� 
	
	else 
		lDistance = lDelta_Y; 

	
	for ( us = 0; us <= lDistance + 1; us ++ )//������� 
	{  
		LCD_SetPointPixel ( X_Current, Y_Current, Colour );//���� 
		
		lError_X += lDelta_X ; 
		lError_Y += lDelta_Y ; 
		
		if ( lError_X > lDistance ) 
		{ 
			lError_X -= lDistance; 
			X_Current += lIncrease_X; 
		}  
		
		if ( lError_Y > lDistance ) 
		{ 
			lError_Y -= lDistance; 
			Y_Current += lIncrease_Y; 
		} 
		
	}  
	
	
}   


/**
 * @brief  �� LCD ��ʾ���ϻ�һ������
 * @param  X �����ض�ɨ�跽���¾��ε���ʼ��X����
 * @param  Y �����ض�ɨ�跽���¾��ε���ʼ��Y����
 * @param  WIDTH�����εĿ�ȣ���λ�����أ�
 * @param  HEIGTH�����εĸ߶ȣ���λ�����أ�
 * @param  Colour �����ε���ɫ
 * @param  Filled ��ѡ���Ƿ����þ���
  *   �ò���Ϊ����ֵ֮һ��
  *     @arg 0 :���ľ���
  *     @arg 1 :ʵ�ľ���
 * @retval ��
 */
void LCD_DrawRectangle ( uint16_t X, uint16_t Y, uint16_t WIDTH, uint16_t HEIGTH, uint16_t Colour, uint8_t Filled )
{
	if ( Filled )
	  LCD_ClearWindow ( X, Y, WIDTH, HEIGTH, Colour);
	else
	{
		LCD_DrawLine ( X, Y, X + WIDTH - 1, Y, Colour );
		LCD_DrawLine ( X, Y + HEIGTH - 1, X + WIDTH - 1, Y + HEIGTH - 1, Colour );
		LCD_DrawLine ( X, Y, X, Y + HEIGTH - 1, Colour );
		LCD_DrawLine ( X + WIDTH - 1, Y, X + WIDTH - 1, Y + HEIGTH - 1, Colour );		
	}

}


/**
 * @brief  �� LCD ��ʾ����ʹ�� Bresenham �㷨��Բ
 * @param  X_Center �����ض�ɨ�跽����Բ�ĵ�X����
 * @param  Y_Center �����ض�ɨ�跽����Բ�ĵ�Y����
 * @param  Radius��Բ�İ뾶����λ�����أ�
 * @param  Colour ��Բ����ɫ
 * @param  Filled ��ѡ���Ƿ�����Բ
  *   �ò���Ϊ����ֵ֮һ��
  *     @arg 0 :����Բ
  *     @arg 1 :ʵ��Բ
 * @retval ��
 */
void LCD_DrawCircle ( uint16_t X_Center, uint16_t Y_Center, uint16_t Radius, uint16_t Colour, uint8_t Filled )
{
	int16_t sCurrentX, sCurrentY;
	int16_t sError;
	sCurrentX = 0; sCurrentY = Radius;	  	
	sError = 3 - ( Radius << 1 );     //�ж��¸���λ�õı�־	
	while ( sCurrentX <= sCurrentY )
	{
		int16_t sCountY;	
		if ( Filled ) 			
			for ( sCountY = sCurrentX; sCountY <= sCurrentY; sCountY ++ ) 
			{                      
				LCD_SetPointPixel ( X_Center + sCurrentX, Y_Center + sCountY,   Colour );           //1���о����� 
				LCD_SetPointPixel ( X_Center - sCurrentX, Y_Center + sCountY,   Colour );           //2       
				LCD_SetPointPixel ( X_Center - sCountY,   Y_Center + sCurrentX, Colour );           //3
				LCD_SetPointPixel ( X_Center - sCountY,   Y_Center - sCurrentX, Colour );           //4
				LCD_SetPointPixel ( X_Center - sCurrentX, Y_Center - sCountY,   Colour );           //5    
        LCD_SetPointPixel ( X_Center + sCurrentX, Y_Center - sCountY,   Colour );           //6
				LCD_SetPointPixel ( X_Center + sCountY,   Y_Center - sCurrentX, Colour );           //7 	
        LCD_SetPointPixel ( X_Center + sCountY,   Y_Center + sCurrentX, Colour );           //0				
			}		
		else
		{          
			LCD_SetPointPixel ( X_Center + sCurrentX, Y_Center + sCurrentY, Colour );             //1���о�����
			LCD_SetPointPixel ( X_Center - sCurrentX, Y_Center + sCurrentY, Colour );             //2      
			LCD_SetPointPixel ( X_Center - sCurrentY, Y_Center + sCurrentX, Colour );             //3
			LCD_SetPointPixel ( X_Center - sCurrentY, Y_Center - sCurrentX, Colour );             //4
			LCD_SetPointPixel ( X_Center - sCurrentX, Y_Center - sCurrentY, Colour );             //5       
			LCD_SetPointPixel ( X_Center + sCurrentX, Y_Center - sCurrentY, Colour );             //6
			LCD_SetPointPixel ( X_Center + sCurrentY, Y_Center - sCurrentX, Colour );             //7 
			LCD_SetPointPixel ( X_Center + sCurrentY, Y_Center + sCurrentX, Colour );             //0
        }				
		sCurrentX ++;	
		if ( sError < 0 ) 
			sError += 4 * sCurrentX + 6;	  	
		else
		{
			sError += 10 + 4 * ( sCurrentX - sCurrentY );   
			sCurrentY --;
		} 					
	}	
}



/**
  * ��������: ��SD����ȡGBK��
  * �������: pBuffer�����ݱ����ַ
  *           gbk �������ַ����ֽ���
  *           font������ѡ��
  *           ��ѡֵ��USE_FONT_16 ��16������
  *                   USE_FONT_24 ��24������ 
  * �� �� ֵ: uint8_t: 0:��ȡʧ�ܣ�1����ȡ�ɹ�
  * ˵    ����ʹ�øú���֮ǰȷ����������f_mount(&fs,"0:",1);����
  */
static uint8_t GetGBKCode_SD(uint8_t * pBuffer,const uint16_t Char)
{
  uint32_t pos;
  uint8_t high8bit,low8bit;
  static uint8_t everRead = 0;
  high8bit=Char>> 8;
  low8bit=Char& 0x00FF;
    if(everRead==0)
    {
        if(FATFS_GetAttachedDriversNbr()!=0)
        {
            if(f_mount (&fs, "0:", 1)!=FR_OK)
            {
                LCD_Show(160,20,"FAILED MOUNT\n");
                DEBUG("FATFS MOUNT WRONG");
                while(1);
            }
            else
            {
                everRead=1;
            }
            
        }
        else
            LCD_Show(160,20,"NO ATTACHERDRIVERS\n");
    }

    // 16*16��С�ĺ��� ����ģ ռ��16*16/8���ֽ�
    pos=((high8bit-0xa1)*94+low8bit-0xa1)*16*16/8;
    fres=f_open(&file,"0:/GBK_1616.FON",FA_OPEN_EXISTING|FA_READ);
  if(fres == FR_OK ) 
  {
    f_lseek (&file, pos);		//ָ��ƫ��
    fres=f_read(&file,pBuffer,32,&fnum); 
    f_close(&file);      
    return 1;  
  }    
  else
    return 0;    
}

/**
  * ��������: ��FLASH��ȡGBK��
  * �������: pBuffer�����ݱ����ַ
  *           gbk �������ַ����ֽ���
  *           font������ѡ��
  *           ��ѡֵ��USE_FONT_16 ��16������
  *                   USE_FONT_24 ��24������ 
  * �� �� ֵ: uint8_t: 0:��ȡʧ�ܣ�1����ȡ�ɹ�
  * ˵    ����ʹ�øú���֮ǰȷ����������f_mount(&fs,"0:",1);����
  */
static uint8_t GetGBKCode_FLASH(uint8_t * pBuffer,const uint16_t Char,uint8_t font=16)
{
  uint32_t pos;
  uint8_t high8bit,low8bit;

  high8bit=Char>> 8;
  low8bit=Char& 0x00FF;

    // 16*16��С�ĺ��� ����ģ ռ��16*16/8���ֽ�
    pos=((high8bit-0xa1)*94+low8bit-0xa1)*16*16/8;
		SPI_FLASH_BufferRead(pBuffer,GBK_1616_ADDR+pos,32);
	return 1;
}



/**
 * @brief  �� LCD ��ʾ������ʾһ��Ӣ���ַ�
 * @param  X �����ض�ɨ�跽�����ַ�����ʼX����
 * @param  Y �����ض�ɨ�跽���¸õ����ʼY����
 * @param  Char ��Ҫ��ʾ��Ӣ���ַ�
 * @param  Bg_Colour ��ѡ��Ӣ���ַ��ı���ɫ
 * @param  Bg_Colour ��ѡ��Ӣ���ַ���ǰ��ɫ
 * @retval ��
 */
static void LCD_Show_EN ( uint16_t X, uint16_t Y, const char Char, uint16_t Bg_Colour, uint16_t Fg_Colour )
{
	uint8_t temp, ch, line, column;	
	ch = Char - ' ';	
	LCD_OpenWindow ( X, Y, WIDTH_EN, HEIGHT_EN );	
	LCD_Write_Cmd ( CMD_SetPixel );		
	for ( line = 0; line < HEIGHT_EN; line ++ )
	{
		temp = ASCII_1608 [ ch ] [ line ];		
		for ( column = 0; column < WIDTH_EN; column ++ )
		{
			if ( temp & 0x01 )
				LCD_Write_Data ( Fg_Colour );			
			else
				LCD_Write_Data ( Bg_Colour );											
			temp >>= 1;					
		}/* д��һ�� */		
	}/* ȫ��д�� */	
}

/**
 * @brief  �� LCD ��ʾ������ʾһ�������ַ�
 * @param  X �����ض�ɨ�跽�����ַ�����ʼX����
 * @param  Y �����ض�ɨ�跽�����ַ�����ʼY����
 * @param  Char ��Ҫ��ʾ�������ַ��������룩
 * @param  Bg_Colour ��ѡ�������ַ��ı���ɫ
 * @param  Bg_Colour ��ѡ�������ַ���ǰ��ɫ
 * @retval ��
 */ 
static void LCD_Show_CH ( uint16_t X, uint16_t Y, uint16_t Char, uint16_t Bg_Colour, uint16_t Fg_Colour )
{
	uint8_t line, column;
	uint8_t buff [ 32 ];	
    uint16_t temp; 		
	LCD_OpenWindow ( X, Y, WIDTH_CH, HEIGHT_CH );	
	LCD_Write_Cmd ( CMD_SetPixel );
		if(FAFTS_SD) 
			GetGBKCode_SD ( buff, Char );	//ȡ��ģ����	
		else if(FAFTS_FLASH)
			GetGBKCode_FLASH ( buff, Char );		
	for ( line = 0; line < HEIGHT_CH; line ++ )
	{
    /* ȡ�������ֽڵ����ݣ���lcd�ϼ���һ�����ֵ�һ�� */
		temp = buff [ line * 2 ];
		temp = ( temp << 8 );
		temp |= buff [ line * 2 + 1 ];		
		for ( column = 0; column < WIDTH_CH; column ++ )
		{			
			if ( temp & ( 0x01 << 15 ) )  //��λ��ǰ 
                LCD_Write_Data ( Fg_Colour );				
			else
				LCD_Write_Data ( Bg_Colour );			
			temp <<= 1;			
		}		
	}	
}

/**
 * @brief  �� LCD ��ʾ������ʾ��Ӣ���ַ���
 * @param  X �����ض�ɨ�跽�����ַ�������ʼX����
 * @param  Y �����ض�ɨ�跽�����ַ�������ʼY����
 * @param  pStr ��Ҫ��ʾ���ַ������׵�ַ
 * @param  Bg_Colour ��ѡ���ַ����ı���ɫ
 * @param  Bg_Colour ��ѡ���ַ�����ǰ��ɫ
 * @retval ��
 */
void LCD_Show ( uint16_t X, uint16_t Y, const uint8_t * pStr, uint16_t Bg_Colour, uint16_t Fg_Colour )
{
	uint16_t ch;
	while( * pStr != '\0' )
	{
		if ( * pStr <= 126 )	           	//Ӣ���ַ�
		{
			if ( ( X - LCD_WindowX + WIDTH_EN ) > LCD_Column )
			{
				X = LCD_WindowX;
				Y += HEIGHT_EN;
			}
			
			if ( ( Y - LCD_WindowY + HEIGHT_EN ) > LCD_Line )
			{
				X = LCD_WindowX;
				Y = LCD_WindowY;
			}					
		    LCD_Show_EN ( X, Y, * pStr, Bg_Colour, Fg_Colour );			
			X += WIDTH_EN;		
		    pStr ++;
		}		
		else	                            //�����ַ�
		{
			if ( ( X - LCD_WindowX + WIDTH_CH ) > LCD_Column )
			{
				X = LCD_WindowX;
				Y += HEIGHT_CH;
			}			
			if ( ( Y - LCD_WindowY + HEIGHT_CH ) > LCD_Line )
			{
				X = LCD_WindowX;
				Y = LCD_WindowY;
			}				
			ch = * ( uint16_t * ) pStr;				
			ch = ( ch << 8 ) + ( ch >> 8 );		
			LCD_Show_CH ( X, Y, ch, Bg_Colour, Fg_Colour );			
			X += WIDTH_CH;			
			pStr += 2;           //һ�����������ֽ� 		
    }		
  }		
} 


void LCD_IMG( uint16_t x, uint16_t y,char *pic_name)
{
    uint16_t i, j, k;
	int width, height, l_width;
    uint8_t pColorData[960];					/* һ�����ɫ���ݻ��� 320 * 3 = 960 */
	BMP_FileHeader FileHeader;
	BMP_InfoHeader InfoHeader;
	fres=f_open(&file,pic_name, FA_OPEN_EXISTING|FA_READ);	
	if(fres == FR_OK)
	{
		DEBUG("Open file success\r\n");

		/* ��ȡ�ļ�ͷ��Ϣ  �����ֽ�*/         
		fres=f_read(&file,&FileHeader,sizeof(BMP_FileHeader),&fnum);     
    
		/* �ж��ǲ���bmp�ļ� "BM"*/
		if(FileHeader.bfType!=0x4d42)
		{
			DEBUG("file is not .bmp file!\r\n");
			return;
		}
		else
		{
			DEBUG("Ok this is .bmp file\r\n");	
		}
		/* ��ȡBMP�ļ�ͷ��Ϣ*/      
		showBmpHeader(&FileHeader);
   
		/* ��ȡλͼ��Ϣͷ��Ϣ */
		fres=f_read(&file,&InfoHeader,sizeof(BMP_InfoHeader),&fnum);      
		showBmpInforHeader(&InfoHeader);
	}    
	else
	{
		DEBUG("file open fail!\r\n");
		return;
	}  

	width  = InfoHeader.biWidth;
	height = InfoHeader.biHeight; 
  
	/* ����λͼ��ʵ�ʿ�Ȳ�ȷ����Ϊ32�ı���	*/
	l_width = WIDTHBYTES(width* InfoHeader.biBitCount);
  
	if((l_width>960)||(InfoHeader.biBitCount!=24))
	{
		DEBUG("\n SORRY, PIC IS TOO BIG (X<=320 and bit!=16)\n");
		return;
	 }
  f_lseek(&file,FileHeader.bfOffBits);
   
  if(InfoHeader.biBitCount == 24)
  {
    for(i=0;i<height;++i)
    {
      /* ��һ��ͼƬ��С�Ĵ���*/
      LCD_OpenWindow(x, y+height-i-1, width, 1);
      LCD_Write_Cmd(0x2C);
      /* ��ȡһ��bmp�����ݵ�����pColorData���� */
      f_read(&file,pColorData,l_width,&fnum);      
      for(j=0;j<width;j++) 											   //һ����Ч��Ϣ
      {        
        k = j*3;																	 //һ���е�K�����ص����        
        LCD_Write_Data(RGB24TORGB16(pColorData[k+2],pColorData[k+1],pColorData[k])); //д��LCD-GRAM
      }
    }
  }
	f_close(&file);    
}
