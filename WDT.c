#include"msp430f5438.h"
#include"delay.h"

//#define WDT_PWM_
#ifdef WDT_PWM_
#define WDT_CYCLE 125
  unsigned char WDT_cnt   = 0;
  unsigned char WDT_duty1 = 0;
#endif

void WDT_init()
{
#ifdef WDT_PWM_
  WDTCTL = WDTPW + WDTSSEL__SMCLK + WDTTMSEL + WDTIS_7;
  SFRIE1  |= WDTIE;
  
  P8DIR |= BIT6;
  P8OUT |= BIT6;
  P8DS  |= BIT6;
  
  //更多PWM口定义...
  
#else
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
#endif
}

#ifdef WDT_PWM_
void WDT_PWM1()
{
  WDT_duty1 = TimeBase/1000+64;
}

#pragma vector = WDT_VECTOR
__interrupt void WDT_ISR()
{
  WDT_cnt++;
  if (WDT_cnt == WDT_duty1)
  {
    P8OUT &=~BIT6;
  }
  //更多定义
  if (WDT_cnt == WDT_CYCLE)
  {
    WDT_cnt =   0;
    P8OUT   |=  BIT6;
  }
}
#endif