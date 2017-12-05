#include "Date.h"

#define A       3.9083e-3
#define B       -5.775e-7
#define P0      101.325
#define T0      273.15
#define M_PI	3.14159265358979323846
#define D       1

Measure measure;
TongDao tongdao;
System  system;
BuChang buchang;
ShuChu  shuchu;
BaoJing baojing;
JiaoDui jiaodui;
Time time;
Time PVD_stack[8][2];


void Date_Init(void)
{
    //DS1302_TIME(17,10,18,0,0,0);
    tongdao.Type=2;
    tongdao.Unit[0]=1;
    tongdao.Unit[1]=1;
    tongdao.Unit[2]=0;
    tongdao.Unit[3]=3;
    tongdao.Unit[4]=3;
    tongdao.Range[0][0]=0;
    tongdao.Range[0][1]=0;
    tongdao.Range[0][2]=22;
    tongdao.Range[1][0]=0;
    tongdao.Range[1][1]=10;
    tongdao.Range[1][2]=110;
    tongdao.Range[2][0]=0;
    tongdao.Range[2][1]=-20;
    tongdao.Range[2][2]=100;
    buchang.density[0]=1;
    buchang.k[5]=0.34;
    shuchu.R=160;
    system.R[0]=160;
    system.R[1]=160;
    system.R[2]=160;
    jiaodui.Move[0]=1;
    jiaodui.Move[1]=1;
    jiaodui.Move[2]=1;
    jiaodui.Move[3]=1;
    system.Password=0000;
    measure.EF=0;
    shuchu.OnOff[1]=1;
    system.OnOff_485=1;
    system.Addr_485=1;
    system.Bps_485=9600;
}

void Date_convert(void)
{
    double vol,Rt,temp[4],t,p1,p0,DP,P,DS,P1,Qm,k,Qn;
    uint8_t i,j;
//    HAL_ADC_Stop_DMA(&hadc1);
    for(i=0;i<4;i++)
    {
         //temp[i]=(Adc_Value[i])*3.3/4096;
        temp[i]=measure.ADC_V[i]*3.3/4096;
        measure.V[i]=temp[i];
    }
//    HAL_ADC_Start_DMA(&hadc1, Adc_Value, 4);
    for(i=0;i<3;i++)
    {
        if(temp[i]/system.R[i]<=0.004)
            temp[i]=0;
        else
        {
            temp[i]=temp[i]/system.R[i]-0.004;
            temp[i]=temp[i]/0.016*(tongdao.Range[i][2]-tongdao.Range[i][1])+tongdao.Range[i][1];
        }
    }
    measure.CY=temp[0];
    measure.YL=temp[1];
    measure.T =temp[2];

    vol=temp[3];
    Rt=2000*(vol/33.0-75.0/2075)/(1-(vol/33.0-75.0/2075))*jiaodui.Move[3];
    if(Rt>0)
        measure.PT=(-A+sqrt(A*A-4*B*(1-Rt/100)))/(2*B);
    else
        measure.PT=0;
    if(tongdao.Type==2||tongdao.Type==4)//模式选择
    {
        t=measure.PT;
        //printf("%f %f %f %f %f\n",vol,Rt,t,A,B);
    }
    else
    	t=temp[2];
    if(tongdao.Type==0||tongdao.Type==4||tongdao.Type==1)//模式选择
        measure.MODE=2;
    else
        measure.MODE=0;
    if(tongdao.Unit[2]==0)
        measure.T_S=t;
    else
        measure.T_S=t-T0;


    for(i=0;i<3;i++)//信号过滤 切除
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

    for(i=0;i<2;i++)//CY YL单位换算
    {
        switch(tongdao.Unit[i])
        {
            case 0:break;
            case 1:temp[i]*=1000;break;
            case 2:temp[i]*=1000000;break;
            case 3:temp[i]*=98066.5;break;
            case 4:temp[i]*=100000;break;
        }
    }

    DP=temp[0];
    P=temp[1];
    p0=buchang.density[0];
    p1=(DP*(T0+20)*p0)/(P0*(T0+t));
    buchang.density[1]=p1;
    k=pow(DP,5)*buchang.k[0]+pow(DP,4)*buchang.k[1]+pow(DP,3)*buchang.k[2]+pow(DP,2)*buchang.k[3]+pow(DP,1)*buchang.k[4]+buchang.k[5];
    Qm=k*M_PI*D*D/4*sqrt(2*DP*p1); //kg/s
    //*(1-1.0893*DP/1.4/P)=E
     measure.F=Qm;
     measure.Qn=Qm/p0;//nm3/s*/
    switch(tongdao.Unit[3])//瞬时流量
    {
        case 0:measure.F_S=measure.F;break;
        case 1:measure.F_S=measure.F/1000.0;break;
        case 2:measure.F_S=measure.Qn/1000.0;break;
        case 3:measure.F_S=measure.Qn;break;
        case 4:measure.F_S=measure.F*60;break;
        case 5:measure.F_S=measure.F/1000.0*60;break;
        case 6:measure.F_S=measure.Qn/1000.0*60;break;
        case 7:measure.F_S=measure.Qn*60;break;
        case 8:measure.F_S=measure.F*3600;break;
        case 9:measure.F_S=measure.F/1000.0*3600;break;
        case 10:measure.F_S=measure.Qn/1000.0*3600;break;
        case 11:measure.F_S=measure.Qn*3600;break;
    }
    shuchu.F=measure.F_S;
    switch(tongdao.Unit[4])//累计流量
    {
        case 0:measure.EF_S=measure.EF;break;
        case 1:measure.EF_S=measure.EF/1000.0;break;
        case 2:measure.EF_S=measure.EF/p0/1000.0;break;
        case 3:measure.EF_S=measure.EF/p0;break;
    }
    DAC_CONVERT();
    ALARM();
    JIAODUI();
}



void DAC_CONVERT(void)
{
    float percentage=0;

        if(shuchu.Range[1]<=shuchu.Range[0])
            percentage=1;
        else
        percentage=(shuchu.F-shuchu.Range[0])/(shuchu.Range[1]-shuchu.Range[0]);
        if(percentage>1)
            percentage=1;
        if(percentage<0)
            percentage=0;

        switch(shuchu.Mode[0])
        {
            case 0:
                shuchu.Value_i=(uint32_t)((percentage*16+4)/1000*shuchu.R/3.2*4096);
                break;
            case 1:
                shuchu.Value_i=(uint32_t)((percentage*20.0)/1000*shuchu.R/3.2*4096);
                break;
        }

//PWM

        switch(shuchu.Mode[1])
        {
            case 0:shuchu.PL=(uint16_t)(percentage*1000);break;
            case 1:shuchu.PL=(uint16_t)(percentage*5000);break;
            case 2:shuchu.PL=(uint16_t)(percentage*10000);break;
        }
        if(shuchu.PL>=1200)
            shuchu.PSC=0;
        else if(shuchu.PL>=120&&shuchu.PL<1200)
            shuchu.PSC=11;
        else if(shuchu.PL>=12&&shuchu.PL<120)
            shuchu.PSC=119;
        else if(shuchu.PL>=1&&shuchu.PL<12)
            shuchu.PSC=1199;
        else if(shuchu.PL>=0&&shuchu.PL<1)
            shuchu.PSC=11999;
        shuchu.Period=(uint32_t)(72000000/shuchu.PL/(shuchu.PSC+1)-1);
        shuchu.Pulse=(uint32_t)(shuchu.Period/2);

}



void JIAODUI(void)
{
    uint8_t i;
    for(i=0;i<3;i++)
    {
        if(jiaodui.OnOff[i])
        {
            jiaodui.OnOff[i]=0;
            system.R[i]=system.R[i]*jiaodui.Move[i];
        }
    }
}



