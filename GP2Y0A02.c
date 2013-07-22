#include "msp430f5438.h"
/*
需要和ADC12.c配合使用
*/
#define   Num_of_Results   1000
  
volatile unsigned int results[Num_of_Results][2];
                                            // Needs to be global in this
                                            // example. Otherwise, the
                                            // compiler removes it because it
                                            // is not used for anything.

unsigned char DataReady;
double dist1,dist2,dist3;

void GP2Y0A02_DistCompute(double aver1,double aver2)
{
  double volt1,volt2;
  
    volt1 = (aver1*3.3)/4095;       //3.3v参考电压下信号电压值
    
    if (volt1>2.221)
      dist1 = 20.0-(volt1-2.221)*23.9;
    else if (volt1 >2.006)
      dist1 = 25.0-(volt1-2.006)*23.3;
    else if (volt1 >1.768)
      dist1 = 30.0-(volt1-1.768)*21;
    else if (volt1 >1.546)
      dist1 = 35.0-(volt1-1.546)*22.5;    
    else if (volt1 >1.360)
      dist1 = 40.0-(volt1-1.360)*26.9;
    else if (volt1 >0.87)
      dist1 = 70.0-(volt1-0.87)*6;

    volt2 = (aver2*3.3)/4095;       //3.3v参考电压下信号电压值
    
    if (volt2>2.221)
      dist2 = 20.0-(volt2-2.221)*23.9;
    else if (volt2 >2.006)
      dist2 = 25.0-(volt2-2.006)*23.3;
    else if (volt2 >1.768)
      dist2 = 30.0-(volt2-1.768)*21;
    else if (volt2 >1.546)
      dist2 = 35.0-(volt2-1.546)*22.5;    
    else if (volt2 >1.360)
      dist2 = 40.0-(volt2-1.360)*26.9;
    else if (volt2 >0.87)
      dist2 = 70.0-(volt2-0.87)*6;
    
    dist3=((1/volt1)-0.103309314204)/0.0143793026254; //参数还没调
}

void GP2Y0A02_DataProcess()
{
  unsigned char j;
  unsigned int i,shift,maxi,mini;
  unsigned int max,min;
  unsigned long sum1=0, sum2=0;
  
  if (DataReady == 1)
    shift = 0;
  else shift = 500;
  

  
  for (j=0;j<100;j++)    //先尝试去掉50个最大、50个最小
  {
    max = 0;
    min = 65535;
    for (i=shift; i<500+shift; i++)
    {
      if ((min>results[i][0])&&(results[i]!=0))
      {
        min = results[i][0];
        mini = i;
      }
      if ((max<results[i][0])&&(results[i]!=0))
      {
        max = results[i][0];
        maxi = i;
      }
    }
    results[mini][0]=0;
    results[maxi][0]=0;
  }

  for (j=0;j<100;j++)
  {
    max = 0;
    min = 65535;
    for (i=shift; i<500+shift; i++)
    {
      if ((min>results[i][1])&&(results[i]!=0))
      {
        min = results[i][1];
        mini = i;
      }
      if ((max<results[i][1])&&(results[i]!=0))
      {
        max = results[i][1];
        maxi = i;
      }
    }
    results[mini][1]=0;
    results[maxi][1]=0;
  }
  
  for (i=shift; i<500+shift; i++)
  {
    sum1  +=results[i][0];
    sum2  +=results[i][1];
  }
  
  GP2Y0A02_DistCompute((double)sum1/300.0,(double)sum2/300.0);
  DataReady ++;
}

void GP2Y0A02_Calibration()
{
  
}