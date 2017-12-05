 #include "Date.h"

uint32_t Adc_Value[4];
#define A       3.9083e-3
#define B       -5.775e-7
#define P0      101.325
#define T0      273.15

Measure measure;
TongDao tongdao;
System  system;
BuChang buchang;

void Date_Init(void)
{
    measure.MODE=2;
    tongdao.Type=0;
    tongdao.Uint[0]=1;
    tongdao.Range[0][0]=0;
    tongdao.Range[0][1]=-123.456;
    tongdao.Range[0][2]=9878.987;
    tongdao.Range[1][2]=9878.987;
    tongdao.Range[2][2]=9878.987;
}

void Date_convert(void)
{
    double vol,Rt,temp[4],t,p1,p0,DP,P,DS,P1,Qm,k,D;
    uint8_t i;
//    HAL_ADC_Stop_DMA(&hadc1);
    for(i=0;i<4;i++)
        temp[i]=(Adc_Value[i])*3.3/4096;
//    HAL_ADC_Start_DMA(&hadc1, Adc_Value, 4);
    for(i=0;i<3;i++)
    {
    temp[i]=(temp[i]/0.16-4)/16*(tongdao.Range[i][2]-tongdao.Range[i][1])+tongdao.Range[i][1];
    }
    measure.CY=temp[0];
    measure.YL=temp[1];
    measure.T =temp[2];
    for(i=0;i<3;i++)
    {
        if(tongdao.Range[i][0]!=0)
        {
            if((temp[i]>-tongdao.Range[i][0])&&(temp[i]<tongdao.Range[i][0]))
            temp[i]=0;
        }
        if(tongdao.Ssresction[i]!=0)
        {
            if((temp[i]<=tongdao.Ssresction[i])&&(temp[i]>=-tongdao.Ssresction[i]))
                temp[i]=0;
            else if(temp[i]>tongdao.Ssresction[i])
                temp[i]-=tongdao.Ssresction[i];
            else if(temp[i]<-tongdao.Ssresction[i])
                temp[i]+=tongdao.Ssresction[i];
        }
    }
    if(tongdao.Type==2||tongdao.Type==4)
    {
    	vol=temp[3];
	    Rt=2000*(vol/33+75.0/2075)/(1-vol/33-75.0/2075);
	    measure.PT=(-A+sqrt(A*A-4*B*(1-Rt/100)))/(2*B);
    	t=measure.PT;
    }
    else
    	t=temp[2];
    DP=temp[0];
    P=temp[1];
    p0=buchang.density[0];
    p1=(DP*(T0+20)*p0)/(P0*(T0+t));

     Qm=k*(1-1.0893*DP/1.4/P)*M_PI*D*D/4*sqrt(2*DP*p1); //kg/s
     //Qn=Qm/p0;//nm3/s*/
     measure.F=Qm;
}


    //pa



