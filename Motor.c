#include "msp430f5438.h"
#include "PWM.h"

#define MOTORDIR  P8DIR
#define MOTOROUT  P8OUT

void Motor_init()
{
  PWM_init();
  MOTORDIR |= 0xff;
  MOTOROUT =  0;
}

void Motor_config(signed int l1, signed int l2, signed int r1, signed int r2)
{
  if(l1 >= 0)
  {
    PWM_1((unsigned)l1);
    MOTOROUT &=~BIT0;
    MOTOROUT |= BIT1;
  }
  else
  {
    PWM_1((unsigned)-l1);    
    MOTOROUT |= BIT0;
    MOTOROUT &=~BIT1;    
  }
  
  if(l2 >= 0)
  {
    PWM_2((unsigned)l2);
    MOTOROUT |= BIT2;
    MOTOROUT &=~BIT3;
  }
  else
  {
    PWM_2((unsigned)-l2);
    MOTOROUT &=~BIT2;
    MOTOROUT |= BIT3;    
  }
  
  if(r1 >= 0)
  {
    PWM_3((unsigned)r1);
    MOTOROUT |= BIT6;
    MOTOROUT &=~BIT7;
  }
  else
  {
    PWM_3((unsigned)-r1);
    MOTOROUT &=~BIT6;
    MOTOROUT |= BIT7;    
  } 
  
  if(r2 >= 0)
  {
    PWM_4((unsigned)r2);
    MOTOROUT &=~BIT4;
    MOTOROUT |= BIT5;        
  }
  else
  {
    PWM_4((unsigned)-r2);
    MOTOROUT |= BIT4;
    MOTOROUT &=~BIT5; 
  }
}