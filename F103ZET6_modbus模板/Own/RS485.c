#include "../Own/RS485.h"

uint16_t   usRegInputStart = REG_INPUT_START;
uint16_t   usRegInputBuf[REG_INPUT_NREGS];
uint16_t usRegHoldingBuf[REG_HOLDING_NREGS];

eMBErrorCode eMBRegInputCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs )
{
  eMBErrorCode    eStatus = MB_ENOERR;
  int             iRegIndex;
  printf("eMBRegInputCB\n");
  if((usAddress>=REG_INPUT_START)&&(usAddress+usNRegs<=REG_INPUT_START+REG_INPUT_NREGS))
  {
    iRegIndex=(int)(usAddress-usRegInputStart);
    while( usNRegs > 0 )
    {
      *pucRegBuffer++ = (unsigned char)(usRegInputBuf[iRegIndex]>>8);
      *pucRegBuffer++ = (unsigned char)(usRegInputBuf[iRegIndex]&0xFF);
      iRegIndex++;
      usNRegs--;
    }
  }
  else
  {
    eStatus = MB_ENOREG;
  }
  return eStatus;
}

eMBErrorCode eMBRegHoldingCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs,eMBRegisterMode eMode )
{
    //错误状态
    eMBErrorCode eStatus = MB_ENOERR;
    //偏移量
    int16_t iRegIndex;
    printf("eMBRegHoldingCB\n");
    //判断寄存器是不是在范围内
    if( ( (int16_t)usAddress >= REG_HOLDING_START )&&( usAddress + usNRegs <= REG_HOLDING_START + REG_HOLDING_NREGS ) )
    {
    //计算偏移量
        iRegIndex = ( int16_t )( usAddress - REG_HOLDING_START);
        switch ( eMode )
        {
        //读处理函数 
        case MB_REG_READ:
            while( usNRegs > 0 )
                {
                    *pucRegBuffer++ = ( uint8_t )( usRegHoldingBuf[iRegIndex] >> 8 );
                    *pucRegBuffer++ = ( uint8_t )( usRegHoldingBuf[iRegIndex] & 0xFF );
                    iRegIndex++;
                    usNRegs--;
                }
            break;
        //写处理函数 
        case MB_REG_WRITE:
            while( usNRegs > 0 )
                {
                    usRegHoldingBuf[iRegIndex] = *pucRegBuffer++ << 8;
                    usRegHoldingBuf[iRegIndex] |= *pucRegBuffer++;
                    iRegIndex++;
                    usNRegs--;
                }
            break;
        }
    }
    else
        eStatus = MB_ENOREG;
    return eStatus;
}


eMBErrorCode eMBRegCoilsCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNCoils,eMBRegisterMode eMode )
{
  printf("eMBRegCoilsCB\n");
  return MB_ENOREG;
}

eMBErrorCode eMBRegDiscreteCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNDiscrete )
{
  printf("eMBRegDiscreteCB\n");
  return MB_ENOREG;
}
