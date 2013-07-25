#include"msp430f5438.h"
#include"Global.h"

#ifdef PhotoelectricEncoder_Used_
unsigned int L_before,L_now,L_T,L_interval;
unsigned int R_before,R_now,R_T,R_interval;

void PhotoelectricEncoder_init()
{
    P4DIR &= ~(BIT1+ BIT2);
    P4SEL |=  BIT1+ BIT2;
    
    TB0CCTL1 = CM_1+CCIS_0+CAP+SCS;                    // CCR1 capture mode P4.1
    TB0CCTL2 = CM_1+CCIS_0+CAP+SCS;                    // CCR1 capture mode P4.2
    TB0CCTL1 |= CCIE;
    TB0CCTL2 |= CCIE;
}

#pragma vector = TIMER0_B1_VECTOR
__interrupt void PhotoelectricEncoder_ISR()
{
  switch(TB0IV)
  {
    case  0: break;                          // No interrupt
    case  2:                                 // CCR1 used
      L_before= L_now;
      L_now   = TB0CCR1;
      L_T = (L_now-L_before)/100+L_interval;   //转一圈所需要的毫秒数
      L_interval=0;
      break;
    case  4:                                 // CCR2 used
      R_before= R_now;
      R_now   = TB0CCR2;
      R_T = (R_now-R_before)/100+R_interval;   //转一圈所需要的毫秒数
      R_interval=0;      
      break;
    case  6: break;                          // reserved
    case  8: break;                          // reserved
    case 10: break;                          // reserved
    case 12: break;                          // reserved
    case 14: break;                          // overflow
         
    default: break;     
  }
}

#pragma vector = TIMER0_B0_VECTOR
__interrupt void TimerB0_ISR()
{
  L_interval++;
  if (L_interval  > 200)
    L_T=0;
  R_interval++;
  if (R_interval  > 200)
    R_T=0;  
}

#endif