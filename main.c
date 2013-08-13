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
#include"UltraSonic.h"
//#include"Hall.h"

#include"Motor.h"

#include"PhotoelectricEncoder.h"
//#include"RotaryEncoder.h"
//#include"Traction.h"

//#include"UART.h"
//#include"StepMotor.h"
#include"PID.h"

#define LEAST 550
signed char turn;
volatile unsigned char distState;
int j,i=500,flag=1,k=1,tx;
unsigned long xianshi,nowTime,lastDist=0xFFFF;
PID_struct Motor_L,Motor_R;

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
  
  UltraSonic_init();

//  UART_init(UCA1,9600);
  
  Motor_init();
  
  PhotoelectricEncoder_init();
  
//  RotaryEncoder_init();
  
//  StepMotor_init();
  
  P1DIR &=~BIT4;
  P1DIR &=~BIT5;
  P1DIR &=~BIT6;
  P1DIR &=~BIT7;
  
  /*
  P1IES |= BIT4;
  P1IES |= BIT5;
  P1IES |= BIT6;
  P1IES |= BIT7;
  P1IFG=0;
  P1IE |=BIT4+BIT5+BIT6+BIT7;  
  */
  
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

//…≤≥µ≤‚ ‘
/*
  P4DIR |= BIT7;
  P4OUT &= ~BIT7;  
  Motor_config(1000,1000,-1000,-1000);
  while(TimeBase!=500);
  Motor_brake(0x0F);
  P4OUT |= BIT7;
  while(!(L_speed==0) || !(R_speed ==0));
  P4OUT &=~BIT7;
*/

//PID init
/*  
  Motor_L.myOutput = 0;
  Motor_L.myInput = &L_speed;
  Motor_L.mySetpoint = 200;
  Motor_L.inAuto = 1;
  PID_setOutputLimits(&Motor_L, 0, (signed long)1000*Accuracy);
  Motor_L.SampleTime = 10;
  PID_setControllerDirection(&Motor_L, 0);
  PID_setTunings(&Motor_L, 2100, 3800, 70);//kp2100,ki4000
  if (TimeBase>Motor_L.SampleTime)
    Motor_L.lastTime = TimeBase-Motor_L.SampleTime;
  else
    Motor_L.lastTime = 0;
  
  Motor_R=Motor_L;
  Motor_R.mySetpoint = 201;
  Motor_R.myInput = &R_speed;
  
  Motor_config(600,600,600,600);
  while(TimeBase!=500);
*/
     
  Motor_config(700,700,700,700);  
  
  while(1)
  {
    
//±‹’œ(while—≠ª∑◊Ó–°10ms)    
/*    
      if (nowTime != TimeBase)
      {
        nowTime = TimeBase;
        
        if ((nowTime % 20 ==0)&&(!(distState & BIT0)))
        {
          distState = ~P1IN;
          distState &= 0xF0;
          if (distState | 0x00)
          {
            if ((distState & 0x10)&&(distState & 0x40))
              Motor_config(-500,-500,700,700);
            else if ((distState & 0x40)&&(distState & 0x80))            
              Motor_config(0,0,700,700);
            else if (distState & 0x40)
              Motor_config(-700,-700,700,700);
            else if (distState & 0x80)
              Motor_config(700,700,700,700);
//            else Motor_config(0,0,0,0);
          }
          else
            Motor_config(850,850,475,475);
        }
        
        if (nowTime % 50 == 0)
        {
          lastDist = sonicDist;
          UltraSonic_Tx();
          if (lastDist < 50)
          {
            Motor_config(-700,-700,700,700);
            distState |= BIT0;
          }
          else
            distState &=~BIT0;
        }        
      }*/

//PID
    /*
    if((!PID_compute(&Motor_L))||(!PID_compute(&Motor_R)))
    {
      Motor_config(Motor_L.myOutput,Motor_L.myOutput,Motor_R.myOutput,Motor_R.myOutput);
      tx=Motor_L.myOutput;
    }
    */
//PID
    
//º”ºıÀŸ°¢’˝∑¥

    /*
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
        Motor_config(i,i,i,i);
      else Motor_config(-i,-i,-i,-i);
//      flag ^=1;

    }*/

//≥¨…˘≤®≤‚ ‘    
/*    if (TimeBase %1000==0)
    {
      UltraSonic_Tx();
      while(TimeBase %1000==0);
    }
    
    if (sonicDist!=0)
      sonicDist=0;*/
//∫ÏÕ‚≤‚ ‘
//   if (DataReady % 2 == 1)
//      GP2Y0A02_DataProcess();
//PWM
//    WDT_PWM1();
  }
}
