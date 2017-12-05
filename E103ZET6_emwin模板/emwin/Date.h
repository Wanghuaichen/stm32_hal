#ifndef __DATE_H_
#define __DATE_H_

#include "math.h"
typedef unsigned          char uint8_t;
typedef unsigned short     int uint16_t;
typedef unsigned           int uint32_t;
//enum Pressure_uint//������λ
//{
//    Pa,KPa,MPa,KgF,Kg,T,L,m3
//}Pu;

typedef struct//����ֵ
{
    uint8_t MODE;//ѹ��/��ѹ�л���ʾ
    uint32_t ADC_V[4];
    double CY;
    double YL;
    double T;
    double PT;
    double F;//˲ʱ
    double EF;//�ۼ�
    double F_S;//��ʾ����
    double EF_S;
    double T_S;
    double Qn;
    float V[4];
    uint8_t Setflag;
}Measure;
//"Pa","KPa","MPa","KgF","Bar"
//"��C","K"
//"Kg/s","t/s","l/s","m3/s","Kg/m","t/m","l/m","m3/m","Kg/h","t/h","l/h","m3/h"
//"Kg","t","l","m3"
typedef struct
{
    uint8_t Type;//��������
    uint8_t Unit[5];//��λ cy yl t f ef  
    double  Ssresction[3];//CY YL T(PT) С�ź�
    double  Range[3][3];//CY YL T(PT) ZERO MIN MAX
    float R[3];
}TongDao;

typedef struct
{
    float atmosphere;
    float k[8];
    float density[2];// ��� ����
}BuChang;

typedef struct
{
    uint8_t Unit;//I PLUSE
    float Range[2];//i pluse
    uint8_t Mode[2];
    uint8_t OnOff[2];
    double F;
    uint32_t Value_i;
    uint32_t Period;
    uint32_t Pulse;
    uint16_t PSC;
    uint16_t PL;
    float R;
}ShuChu;

typedef struct
{
    uint8_t Mode[3];//CY YL T �� ���� ���� ������
    float   Range[3][2];
    uint8_t State;
}
BaoJing;

typedef struct
{
    uint8_t OnOff[3];
    uint8_t Mode[3];
    float  Move[4];//ƫ�� CY YL T PT
    //float R[3];
}JiaoDui;

typedef struct
{
    uint8_t s;
    uint8_t m;
    uint8_t h;
    uint16_t D;
    uint8_t M;
    uint8_t W;
    uint8_t Y;
    uint8_t flags;
}Time;

typedef struct
{
    float R[3];
    //double  EF;//�ۼ�����
    //uint8_t Uint[3];
    uint32_t Password;
    uint8_t SChange_485;
    uint8_t Addr_485;
    uint32_t Bps_485;
    uint8_t OnOff_485;
    uint8_t OnOff_Print[2];//���� ������ӡ
    uint32_t Cyc_Print;
    uint8_t Time_Print_fg;
    uint8_t PVD_flag;
    uint8_t PVD_Number;
    uint32_t PVD_Total_Time;
    uint8_t Reset_All;
}System;


void JIAODUI(void);

void DAC_CONVERT(void);
void Date_convert(void);
void Date_Init(void);
extern uint32_t Adc_Value[4];
extern Measure measure;
extern TongDao tongdao;
extern System  system;
extern BuChang buchang;
extern ShuChu  shuchu;
extern BaoJing baojing;
extern JiaoDui jiaodui;
extern Time time;
extern Time PVD_stack[8][2];
#endif
