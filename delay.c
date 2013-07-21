#include"msp430f5438.h"
//#include"DigtalTube.h"

unsigned int CountDown = 0;
unsigned long TimeBase = 0;

void TimerA1_init()
{
    TA1CCTL0 |= CCIE;                 //TA1CCR0 允许中断
    TA1CCR0 = 4000-1;                   //设置延时时间(4MHz/4000=1KHz)
    TA1CTL |= TASSEL_2;               //SMCLK
    TA1CTL |= MC_1;
}

void delayus()
{
    _DINT();
    __no_operation();
    __no_operation();    
    __no_operation();    
    __no_operation();
    __no_operation();
    __no_operation();    
    __no_operation();
    _EINT();
}

unsigned char delayms(unsigned int n)
{
    if (CountDown != 0)
      return 1;
    else
    {
      CountDown = n;
      return 0;
    }
}

#pragma vector = TIMER1_A0_VECTOR
__interrupt void TA1ISR(void)
{
  TimeBase ++;

  if (CountDown != 0)
  {
      CountDown --;
  }
  
/*数码管扫描程序*/  
#ifdef DigtalTube_H_ 
    P7OUT &= ~(BIT4+ BIT5+ BIT6+ BIT7);  
    switch(TimeBase % 4)
    {
    case 0:
      P7OUT |= BIT4;
      P9OUT =  Digtal[Display_Number[1]];
      if (Display_Number[0]==1)
        P9OUT &= ~BIT7;
      break;
    case 1:
      P7OUT |= BIT5;
      P9OUT =  Digtal[Display_Number[2]];
      if (Display_Number[0]==2)
        P9OUT &= ~BIT7;      
      break;
    case 2:
      P7OUT |= BIT6;
      P9OUT =  Digtal[Display_Number[3]];
      if (Display_Number[0]==3)
        P9OUT &= ~BIT7;      
      break;
    case 3:
      P7OUT |= BIT7;
      P9OUT =  Digtal[Display_Number[4]];
      if (Display_Number[0]==4)
        P9OUT &= ~BIT7;      
      break;
    }
#endif    
}

