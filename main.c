#include"msp430f5438.h"

#include"Global.h"

#include"WDT.h"
#include"UCS.h"
#include"TimerA1.h"
#include"TimerB0.h"
#include"delay.h"
//#include"adc12.h"
//#include"RTC.h"
//#include"DMA.h"
//#include"MPY.h"
//#include"DigtalTube.h"
//#include"I2C.h"
//#include"LCD12864.h"
//#include"DHT11.h"
//#include"TimerA1_PWM.h"
//#include"GP2Y0A02.h"
//#include"UltraSonic.h"
//#include"Hall.h"

#include"Motor.h"

#include"PhotoelectricEncoder.h"
//#include"RotaryEncoder.h"

#include"UART.h"
//#include"StepMotor.h"

int j,i=500,flag=1,k=1,nowtime;

int main( void )
{
  WDT_init();
  
  UCS_init();
  
  TimerA1_init();    
  
  TimerB0_init();
  
//  ADC12_init();
  
//  RTC_init();
  
//  DMA_init();
  
//  DigtalTube_init();
  
//  I2C_Master_init();
  
//  DHT11_init();  
  
//  TimerA1_PWM_init();
  
//  UltraSonic_init();

  UART_init(UCA1,115200);
  
  Motor_init();
  
  PhotoelectricEncoder_init();
  
//  RotaryEncoder_init();
  
//  StepMotor_init();
  
  _EINT();

/*  
  RTC_setTypeDef ref;
  ref.year = 1970;
  ref.dow  = 3;
  
  while(RTC_set(&ref));
*/  
  

//  ADC12CTL0 |= ADC12SC;
//  UCB0IFG |= UCTXIFG;
  
//  TimerA1_PWM_2(3000);

//  while(StepMotor_set(5000,1,0));

  Motor_config(0,900,0,0);
  while(1)
  {}
  while(1)
  {
    nowtime = TimeBase;
    if((nowtime % 1000 == 0)
       &&(k!=nowtime)) 
    {
      k=nowtime;
      j=(TimeBase/1000)%12;
      if(0<=j&&j<=5) i=500+j*100;
      else if(6<=j&&j<=10) i=1500-j*100;
      else 
      {
        i=0;
        flag++;
      }
      if (flag)
        Motor_config(0,i,0,0);
      else Motor_config(0,-i,-0,-0);
//      flag ^=1;

    }

//³¬Éù²¨²âÊÔ    
/*    if (TimeBase %1000==0)
    {
      UltraSonic_Tx();
      while(TimeBase %1000==0);
    }
    
    if (sonicDist!=0)
      sonicDist=0;*/
//ºìÍâ²âÊÔ
//   if (DataReady % 2 == 1)
//      GP2Y0A02_DataProcess();
//PWM
//    WDT_PWM1();
  }
}
