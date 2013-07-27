#include"msp430f5438.h"
#include"Global.h"
#include"UART.h"

#ifdef PhotoelectricEncoder_Used_
unsigned int L_before,L_now,L_T,L_interval;
unsigned int R_before,R_now,R_T,R_interval;

extern int flag;

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
  static unsigned char L_phase,L_before_phase=2;
  switch(TB0IV)
  {
    case  0: break;                          // No interrupt
    case  2:                                 // CCR1 used
      L_phase=TB0CCTL1 & CCI;
      L_before= L_now;
      L_now   = TB0CCR1;
      L_T = L_interval*40+((signed)L_now-(signed)L_before)/100;   //转一圈所需要的毫秒数
      if ((L_T>1000) && (L_T<1200))
        __no_operation();
//      if (L_before_phase!=L_phase)
//      {
        UART_sendint(UCA1, L_T);
        UART_sendstr(UCA1, ", ");
//      }
//      else
//     {
//        UART_sendint(UCA1, L_T/2);
//        UART_sendstr(UCA1, ", ");
//        UART_sendint(UCA1, L_T/2);
//        UART_sendstr(UCA1, ", ");        
//      }
      L_before_phase=L_phase;
      L_interval=0;
      if (TB0CCTL1& COV)
        while(1);
      
      if (flag == 5)
      {
        while(1);
      }
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