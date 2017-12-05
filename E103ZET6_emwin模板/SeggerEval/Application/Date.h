#ifndef __DATE_H
#define __DATE_H

#include "math.h"
typedef unsigned          char uint8_t;
typedef unsigned short     int uint16_t;
typedef unsigned           int uint32_t;
enum Pressure_uint//参数单位
{
    Pa,KPa,MPa,KgF,Kg,T,L,m3
}Pu;
typedef struct//测量值
{
    uint8_t MODE;//工作模式
    double CY;
    double YL;
    double T;
    double PT;
    double F;//瞬时
    double EF;//累计
}Measure;

typedef struct
{
    uint8_t Type;
    uint8_t Uint[3];
    double  Ssresction[3];//CY YL T(PT) 小信号
    double  Range[3][3];//CY YL T(PT) ZERO MIN MAX
}TongDao;

typedef struct
{
    float atmosphere;
    float k[8];
    float density[2];// 标况 工况
}BuChang;

typedef struct
{
    double  EF;//累计流量
    double  jiaozhun[3][2];//校准，零点，比例
    uint8_t Uint[3];
}System;



void Date_convert(void);
void Date_Init(void);
extern uint32_t Adc_Value[4];
extern Measure measure;
extern TongDao tongdao;
extern System  system;
extern BuChang buchang;
#endif
