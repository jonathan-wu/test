#include"msp430f5438.h"

void PhotoelectricEncoder_init()
{
    P4DIR &= ~(BIT1+ BIT2);
    P4SEL |=  BIT1+ BIT2;
    
    TB0CCTL1 = CM_1+CCIS_0+CAP+SCS;                    // CCR1 capture mode P8.6

    TB0CCTL1 |= CCIE;
}

#pragma vector = Timer0_B1_VECTOR
__interrupt void TimerB0_ISR()
{
  
}