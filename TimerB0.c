#include"msp430f5438.h"

void TimerB0_init()
{
    TB0CCTL0 |= CCIE;                 //TB0CCR0 �����ж�
    TB0CCR0 = 4000-1;                 //������ʱʱ��(4MHz/4000=1KHz)
    TB0CTL |= TBSSEL_2;               //SMCLK
    TB0CTL |= MC_1;
}
