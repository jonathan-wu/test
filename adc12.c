#include<msp430f5438.h>
#include"DigtalTube.h"

#define   Num_of_Results   8
  
volatile unsigned int results[Num_of_Results];
                                            // Needs to be global in this
                                            // example. Otherwise, the
                                            // compiler removes it because it
                                            // is not used for anything.
float dist,volt,ave=0,tmp;
volatile unsigned int cnt=0;


//采样多个通道时，设置模式为重复多通道，设置ADC12MCTLn寄存器，注意设置结束位ADC12EOS，根据需要设置中断
//io口设置为模拟量入口An
void ADC12_init()
{
  ADC12CTL0 |= ADC12SHT0_8+ ADC12MSC+ ADC12ON;  //设置采样时间为64个adc时钟周期，多次采样，开启adc
  ADC12CTL1 |= ADC12SHP+ ADC12SSEL_3+ ADC12CONSEQ_2;    //使能采样时钟，选择时钟源为SMCLK, 设置为重复单通道模式
  ADC12CTL2 |= ADC12RES_2;  //设置分辨率为12位
  
  P6SEL |= BIT0;
  ADC12MCTL0|= ADC12SREF_0+ ADC12INCH_0;//设置+-参考电压分别为Vcc与Vss， 通道为A0
  ADC12IE   |= 0x01;                    //使能中断
  
  ADC12CTL0 |= ADC12ENC;    //使能转换
}


#pragma vector=ADC12_VECTOR
__interrupt void ADC12ISR (void)
{
  static unsigned char index = 0;

  switch(ADC12IV)
  {
  case  0: break;                           // Vector  0:  No interrupt
  case  2: break;                           // Vector  2:  ADC overflow
  case  4: break;                           // Vector  4:  ADC timing overflow
  case  6:                                  // Vector  6:  ADC12IFG0
    results[index] = ADC12MEM0;             // Move results
    volt = (results[index]*3.3)/4095;       //3.3v参考电压下信号电压值
/*    cnt++;
    if (cnt == 1) ave=volt[index];
    else {tmp= (volt[index]-ave)/cnt;ave+=tmp;}
    if (cnt == 60000)
    {
      __no_operation();      
      cnt = 0;
      ave = 0;
    }*/
    
    if (volt>2.221)
      dist = 20.0-(volt-2.221)*23.9;
    else if (volt >2.006)
      dist = 25.0-(volt-2.006)*23.3;
    else if (volt >1.768)
      dist = 30.0-(volt-1.768)*21;
    else if (volt >1.546)
      dist = 35.0-(volt-1.546)*22.5;    
    else if (volt >1.360)
      dist = 40.0-(volt-1.360)*26.9;
    else if (volt >0.87)
      dist = 70.0-(volt-0.87)*6;
    
    cnt ++;
    ave += (dist-ave)/cnt;
    if (cnt == 1000)
    {
//      DigtalTube_set((int)ave);
      cnt = 0;
      ave = 0;
    }
    
    index++;                                // Increment results index, modulo; Set Breakpoint1 here
    
    if (index == 8)
    {
      index = 0;
    }
    break;
  case  8: break;                           // Vector  8:  ADC12IFG1
  case 10: break;                           // Vector 10:  ADC12IFG2
  case 12: break;                           // Vector 12:  ADC12IFG3
  case 14: break;                           // Vector 14:  ADC12IFG4
  case 16: break;                           // Vector 16:  ADC12IFG5
  case 18: break;                           // Vector 18:  ADC12IFG6
  case 20: break;                           // Vector 20:  ADC12IFG7
  case 22: break;                           // Vector 22:  ADC12IFG8
  case 24: break;                           // Vector 24:  ADC12IFG9
  case 26: break;                           // Vector 26:  ADC12IFG10
  case 28: break;                           // Vector 28:  ADC12IFG11
  case 30: break;                           // Vector 30:  ADC12IFG12
  case 32: break;                           // Vector 32:  ADC12IFG13
  case 34: break;                           // Vector 34:  ADC12IFG14
  default: break; 
  }
}