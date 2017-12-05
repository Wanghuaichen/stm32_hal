#include "../Own/af_lcd.h"




static void                   LCD_Delay               ( __IO uint32_t nCount );
static void                   LCD_REG_Config          ( void );
static void                   LCD_SetCursor           ( uint16_t X, uint16_t Y );
static __inline void          LCD_FillColor           ( uint32_t ulAmout_Point, uint16_t Colour );
static uint16_t               LCD_Read_PixelData      ( void );
static void                   LCD_OpenWindow          ( uint16_t X, uint16_t Y, uint16_t WIDTH, uint16_t HEIGTH );


/**
  * @brief  向LCD写入命令
  * @param  usCmd :要写入的命令（表寄存器地址）
  * @retval 无
  */	
__inline void LCD_Write_Cmd ( uint16_t cmd )
{
	* ( __IO uint16_t * ) ( LCD_CMD ) = cmd;
	
}


/**
  * @brief  向LCD写入数据
  * @param  data :要写入的数据
  * @retval 无
  */	
__inline void LCD_Write_Data ( uint16_t data )
{
	* ( __IO uint16_t * ) ( LCD_DATA ) = data;
	
}


/**
  * @brief  从LCD读取数据
  * @param  无
  * @retval 读取到的数据
  */	
__inline uint16_t LCD_Read_Data ( void )
{
	return ( * ( __IO uint16_t * ) ( LCD_DATA ) );
	
}


/**
  * @brief  用于 LCD 简单延时函数
  * @param  nCount ：延时计数值
  * @retval 无
  */	
static void LCD_Delay ( __IO uint32_t nCount )
{
  for ( ; nCount != 0; nCount -- );
	
}


/**
 * @brief  初始化LCD寄存器
 * @param  无
 * @retval 无
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
	LCD_Write_Data ( 0xC8 );    /*竖屏  左上角到 (起点)到右下角 (终点)扫描方式*/
	
	
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
 * @brief  LCD背光LED控制
 * @param  enumState ：决定是否使能背光LED
  *   该参数为以下值之一：
  *     @arg ENABLE :使能背光LED
  *     @arg DISABLE :禁用背光LED
 * @retval 无
 */
void LCD_BL( FunctionalState enumState )
{
	if ( enumState )
		HAL_GPIO_WritePin ( GPIOG, GPIO_PIN_6,GPIO_PIN_RESET );
	else
		HAL_GPIO_WritePin ( GPIOG, GPIO_PIN_6,GPIO_PIN_SET );	
}



/**
 * @brief  LCD 软件复位
 * @param  无
 * @retval 无
 */
 void LCD_Rst ( void )
{			
	HAL_GPIO_WritePin ( GPIOG, GPIO_PIN_11,GPIO_PIN_RESET );	 //低电平复位
	LCD_Delay ( 0xAFFf<<2 ); 					   
	HAL_GPIO_WritePin ( GPIOG, GPIO_PIN_11,GPIO_PIN_SET );		 	 
	LCD_Delay ( 0xAFFf<<2 ); 		
}

/**
 * @brief  LCD初始化函数，如果要用到lcd，一定要调用这个函数
 * @param  无
 * @retval 无
 */
void LCD_Init ( uint16_t Bg_Colour)
{
	LCD_BL ( ENABLE );      //点亮LCD背光灯
	LCD_Rst ();
	LCD_REG_Config ();
    LCD_ClearScreen(Bg_Colour);
    
}


/**
 * @brief  设置LCD的GRAM的扫描方向 
 * @param  ucOption ：选择GRAM的扫描方向 
  *   该参数为以下值之一：
  *     @arg 1 :左上角->右下角
  *     @arg 2 :左下角->右上角
  *     @arg 3 :右下角->左上角
  *     @arg 4 :右上角->左下角
 * @retval 无
 */
void LCD_GramScan ( uint8_t MODE )
{	
	switch ( MODE )
	{
		case 1:
//   左上角->右下角      显示中英文时用的是这种模式 
//		____ x(240)       //液晶正面为参考面
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
//		左下角->右上角      显示摄像头图像时用的是这种模式 
//		|x(320)            //液晶正面为参考面
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
//		右下角->左上角        显示BMP图片时用的是这种模式 
//		           |x(320)   //液晶背面为参考面
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
//		左下角角->右上角
//		|y(320)              //液晶背面为参考面
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
 * @brief  在LCD显示器上开辟一个窗口
 * @param  X ：在特定扫描方向下窗口的起点X坐标
 * @param  Y ：在特定扫描方向下窗口的起点Y坐标
 * @param  WIDTH ：窗口的宽度
 * @param  HEIGTH ：窗口的高度
 * @retval 无
 */
static void LCD_OpenWindow ( uint16_t X, uint16_t Y, uint16_t WIDTH, uint16_t HEIGTH )
{	
	LCD_Write_Cmd ( CMD_SetX ); 				 /* 设置X坐标 */
	LCD_Write_Data ( X >> 8  );	 /* 先高8位，然后低8位 */
	LCD_Write_Data ( X & 0xff  );	 /* 设置起始点和结束点*/
	LCD_Write_Data ( ( X + WIDTH - 1 ) >> 8  );
	LCD_Write_Data ( ( X + WIDTH - 1 ) & 0xff  );

	LCD_Write_Cmd ( CMD_SetY ); 			     /* 设置Y坐标*/
	LCD_Write_Data ( Y >> 8  );
	LCD_Write_Data ( Y & 0xff  );
	LCD_Write_Data ( ( Y + HEIGTH - 1 ) >> 8 );
	LCD_Write_Data ( ( Y + HEIGTH - 1) & 0xff );	
}


/**
 * @brief  设定LCD的光标坐标
 * @param  X ：在特定扫描方向下光标的X坐标
 * @param  Y ：在特定扫描方向下光标的Y坐标
 * @retval 无
 */
static void LCD_SetCursor ( uint16_t X, uint16_t Y )	
{
	LCD_OpenWindow ( X, Y, 1, 1 );
}


/**
 * @brief  在LCD显示器上以某一颜色填充像素点
 * @param  ulAmout_Point ：要填充颜色的像素点的总数目
 * @param  Colour ：颜色
 * @retval 无
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
 * @brief  对LCD显示器的某一窗口以某种颜色进行清屏
 * @param  X ：在特定扫描方向下窗口的起点X坐标
 * @param  Y ：在特定扫描方向下窗口的起点Y坐标
 * @param  WIDTH ：窗口的宽度
 * @param  HEIGTH ：窗口的高度
 * @param  Colour ：颜色
 * @retval 无
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
 * @brief  对LCD显示器的某一点以某种颜色进行填充
 * @param  X ：在特定扫描方向下该点的X坐标
 * @param  Y ：在特定扫描方向下该点的Y坐标
 * @param  Colour ：用于填充的颜色
 * @retval 无
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
 * @brief  读取LCD GRAN 的一个像素数据
 * @param  无
 * @retval 像素数据
 */
static uint16_t LCD_Read_PixelData ( void )	
{	
	uint16_t usR=0, usG=0, usB=0 ;	
	LCD_Write_Cmd ( 0x2E );   /* 读数据 */	
	usR = LCD_Read_Data (); 	/*FIRST READ OUT DUMMY DATA*/	
	usR = LCD_Read_Data ();  	/*READ OUT RED DATA  */
	usB = LCD_Read_Data ();  	/*READ OUT BLUE DATA*/
	usG = LCD_Read_Data ();  	/*READ OUT GREEN DATA*/		
  return ( ( ( usR >> 11 ) << 11 ) | ( ( usG >> 10 ) << 5 ) | ( usB >> 11 ) );
	
}


/**
 * @brief  获取 LCD 显示器上某一个坐标点的像素数据
 * @param  X ：在特定扫描方向下该点的X坐标
 * @param  Y ：在特定扫描方向下该点的Y坐标
 * @retval 像素数据
 */
uint16_t LCD_GetPointPixel ( uint16_t X, uint16_t Y )
{ 
	uint16_t PixelData;
	LCD_SetCursor ( X, Y );	
	PixelData = LCD_Read_PixelData ();	
	return PixelData;	
}


/**
 * @brief  在 LCD 显示器上使用 Bresenham 算法画线段 
 * @param  X1 ：在特定扫描方向下线段的一个端点X坐标
 * @param  Y1 ：在特定扫描方向下线段的一个端点Y坐标
 * @param  X2 ：在特定扫描方向下线段的另一个端点X坐标
 * @param  Y2 ：在特定扫描方向下线段的另一个端点Y坐标
 * @param  Colour ：线段的颜色
 * @retval 无
 */
void LCD_DrawLine ( uint16_t X1, uint16_t Y1, uint16_t X2, uint16_t Y2, uint16_t Colour )
{
	uint16_t us; 
	uint16_t X_Current, Y_Current;
	
	int32_t lError_X = 0, lError_Y = 0, lDelta_X, lDelta_Y, lDistance; 
	int32_t lIncrease_X, lIncrease_Y; 	
	
	
	lDelta_X = X2 - X1; //计算坐标增量 
	lDelta_Y = Y2 - Y1; 
	
	X_Current = X1; 
	Y_Current = Y1; 
	
	
	if ( lDelta_X > 0 ) 
		lIncrease_X = 1; //设置单步方向 
	
	else if ( lDelta_X == 0 ) 
		lIncrease_X = 0;//垂直线 
	
	else 
  { 
    lIncrease_X = -1;
    lDelta_X = - lDelta_X;
  } 

	
	if ( lDelta_Y > 0 )
		lIncrease_Y = 1; 
	
	else if ( lDelta_Y == 0 )
		lIncrease_Y = 0;//水平线 
	
	else 
  {
    lIncrease_Y = -1;
    lDelta_Y = - lDelta_Y;
  } 

	
	if (  lDelta_X > lDelta_Y )
		lDistance = lDelta_X; //选取基本增量坐标轴 
	
	else 
		lDistance = lDelta_Y; 

	
	for ( us = 0; us <= lDistance + 1; us ++ )//画线输出 
	{  
		LCD_SetPointPixel ( X_Current, Y_Current, Colour );//画点 
		
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
 * @brief  在 LCD 显示器上画一个矩形
 * @param  X ：在特定扫描方向下矩形的起始点X坐标
 * @param  Y ：在特定扫描方向下矩形的起始点Y坐标
 * @param  WIDTH：矩形的宽度（单位：像素）
 * @param  HEIGTH：矩形的高度（单位：像素）
 * @param  Colour ：矩形的颜色
 * @param  Filled ：选择是否填充该矩形
  *   该参数为以下值之一：
  *     @arg 0 :空心矩形
  *     @arg 1 :实心矩形
 * @retval 无
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
 * @brief  在 LCD 显示器上使用 Bresenham 算法画圆
 * @param  X_Center ：在特定扫描方向下圆心的X坐标
 * @param  Y_Center ：在特定扫描方向下圆心的Y坐标
 * @param  Radius：圆的半径（单位：像素）
 * @param  Colour ：圆的颜色
 * @param  Filled ：选择是否填充该圆
  *   该参数为以下值之一：
  *     @arg 0 :空心圆
  *     @arg 1 :实心圆
 * @retval 无
 */
void LCD_DrawCircle ( uint16_t X_Center, uint16_t Y_Center, uint16_t Radius, uint16_t Colour, uint8_t Filled )
{
	int16_t sCurrentX, sCurrentY;
	int16_t sError;
	sCurrentX = 0; sCurrentY = Radius;	  	
	sError = 3 - ( Radius << 1 );     //判断下个点位置的标志	
	while ( sCurrentX <= sCurrentY )
	{
		int16_t sCountY;	
		if ( Filled ) 			
			for ( sCountY = sCurrentX; sCountY <= sCurrentY; sCountY ++ ) 
			{                      
				LCD_SetPointPixel ( X_Center + sCurrentX, Y_Center + sCountY,   Colour );           //1，研究对象 
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
			LCD_SetPointPixel ( X_Center + sCurrentX, Y_Center + sCurrentY, Colour );             //1，研究对象
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
  * 函数功能: 从SD卡读取GBK码
  * 输入参数: pBuffer：数据保存地址
  *           gbk ：汉字字符低字节码
  *           font：字体选择
  *           可选值：USE_FONT_16 ：16号字体
  *                   USE_FONT_24 ：24号字体 
  * 返 回 值: uint8_t: 0:读取失败，1：读取成功
  * 说    明：使用该函数之前确保已运行了f_mount(&fs,"0:",1);程序。
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

    // 16*16大小的汉字 其字模 占用16*16/8个字节
    pos=((high8bit-0xa1)*94+low8bit-0xa1)*16*16/8;
    fres=f_open(&file,"0:/GBK_1616.FON",FA_OPEN_EXISTING|FA_READ);
  if(fres == FR_OK ) 
  {
    f_lseek (&file, pos);		//指针偏移
    fres=f_read(&file,pBuffer,32,&fnum); 
    f_close(&file);      
    return 1;  
  }    
  else
    return 0;    
}

/**
  * 函数功能: 从FLASH读取GBK码
  * 输入参数: pBuffer：数据保存地址
  *           gbk ：汉字字符低字节码
  *           font：字体选择
  *           可选值：USE_FONT_16 ：16号字体
  *                   USE_FONT_24 ：24号字体 
  * 返 回 值: uint8_t: 0:读取失败，1：读取成功
  * 说    明：使用该函数之前确保已运行了f_mount(&fs,"0:",1);程序。
  */
static uint8_t GetGBKCode_FLASH(uint8_t * pBuffer,const uint16_t Char,uint8_t font=16)
{
  uint32_t pos;
  uint8_t high8bit,low8bit;

  high8bit=Char>> 8;
  low8bit=Char& 0x00FF;

    // 16*16大小的汉字 其字模 占用16*16/8个字节
    pos=((high8bit-0xa1)*94+low8bit-0xa1)*16*16/8;
		SPI_FLASH_BufferRead(pBuffer,GBK_1616_ADDR+pos,32);
	return 1;
}



/**
 * @brief  在 LCD 显示器上显示一个英文字符
 * @param  X ：在特定扫描方向下字符的起始X坐标
 * @param  Y ：在特定扫描方向下该点的起始Y坐标
 * @param  Char ：要显示的英文字符
 * @param  Bg_Colour ：选择英文字符的背景色
 * @param  Bg_Colour ：选择英文字符的前景色
 * @retval 无
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
		}/* 写完一行 */		
	}/* 全部写完 */	
}

/**
 * @brief  在 LCD 显示器上显示一个中文字符
 * @param  X ：在特定扫描方向下字符的起始X坐标
 * @param  Y ：在特定扫描方向下字符的起始Y坐标
 * @param  Char ：要显示的中文字符（国标码）
 * @param  Bg_Colour ：选择中文字符的背景色
 * @param  Bg_Colour ：选择中文字符的前景色
 * @retval 无
 */ 
static void LCD_Show_CH ( uint16_t X, uint16_t Y, uint16_t Char, uint16_t Bg_Colour, uint16_t Fg_Colour )
{
	uint8_t line, column;
	uint8_t buff [ 32 ];	
    uint16_t temp; 		
	LCD_OpenWindow ( X, Y, WIDTH_CH, HEIGHT_CH );	
	LCD_Write_Cmd ( CMD_SetPixel );
		if(FAFTS_SD) 
			GetGBKCode_SD ( buff, Char );	//取字模数据	
		else if(FAFTS_FLASH)
			GetGBKCode_FLASH ( buff, Char );		
	for ( line = 0; line < HEIGHT_CH; line ++ )
	{
    /* 取出两个字节的数据，在lcd上即是一个汉字的一行 */
		temp = buff [ line * 2 ];
		temp = ( temp << 8 );
		temp |= buff [ line * 2 + 1 ];		
		for ( column = 0; column < WIDTH_CH; column ++ )
		{			
			if ( temp & ( 0x01 << 15 ) )  //高位在前 
                LCD_Write_Data ( Fg_Colour );				
			else
				LCD_Write_Data ( Bg_Colour );			
			temp <<= 1;			
		}		
	}	
}

/**
 * @brief  在 LCD 显示器上显示中英文字符串
 * @param  X ：在特定扫描方向下字符串的起始X坐标
 * @param  Y ：在特定扫描方向下字符串的起始Y坐标
 * @param  pStr ：要显示的字符串的首地址
 * @param  Bg_Colour ：选择字符串的背景色
 * @param  Bg_Colour ：选择字符串的前景色
 * @retval 无
 */
void LCD_Show ( uint16_t X, uint16_t Y, const uint8_t * pStr, uint16_t Bg_Colour, uint16_t Fg_Colour )
{
	uint16_t ch;
	while( * pStr != '\0' )
	{
		if ( * pStr <= 126 )	           	//英文字符
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
		else	                            //汉字字符
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
			pStr += 2;           //一个汉字两个字节 		
    }		
  }		
} 


void LCD_IMG( uint16_t x, uint16_t y,char *pic_name)
{
    uint16_t i, j, k;
	int width, height, l_width;
    uint8_t pColorData[960];					/* 一行真彩色数据缓存 320 * 3 = 960 */
	BMP_FileHeader FileHeader;
	BMP_InfoHeader InfoHeader;
	fres=f_open(&file,pic_name, FA_OPEN_EXISTING|FA_READ);	
	if(fres == FR_OK)
	{
		DEBUG("Open file success\r\n");

		/* 读取文件头信息  两个字节*/         
		fres=f_read(&file,&FileHeader,sizeof(BMP_FileHeader),&fnum);     
    
		/* 判断是不是bmp文件 "BM"*/
		if(FileHeader.bfType!=0x4d42)
		{
			DEBUG("file is not .bmp file!\r\n");
			return;
		}
		else
		{
			DEBUG("Ok this is .bmp file\r\n");	
		}
		/* 读取BMP文件头信息*/      
		showBmpHeader(&FileHeader);
   
		/* 读取位图信息头信息 */
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
  
	/* 计算位图的实际宽度并确保它为32的倍数	*/
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
      /* 开一个图片大小的窗口*/
      LCD_OpenWindow(x, y+height-i-1, width, 1);
      LCD_Write_Cmd(0x2C);
      /* 读取一行bmp的数据到数组pColorData里面 */
      f_read(&file,pColorData,l_width,&fnum);      
      for(j=0;j<width;j++) 											   //一行有效信息
      {        
        k = j*3;																	 //一行中第K个像素的起点        
        LCD_Write_Data(RGB24TORGB16(pColorData[k+2],pColorData[k+1],pColorData[k])); //写入LCD-GRAM
      }
    }
  }
	f_close(&file);    
}
