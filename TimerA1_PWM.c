#include "msp430f5438.h"

void TimerA1_PWM_1(unsigned int n)
{
	TA1CCR1 = n;                            // CCR1 PWM duty cycle
}

void TimerA1_PWM_2(unsigned int n)
{
	TA1CCR2 = n;                            // CCR1 PWM duty cycle
}

void TimerA1_PWM_init()
{
    P8DIR |= BIT6;           // P8.6 output
    P8SEL |= BIT6;	     // P8.6 options select
    P7DIR |= BIT3;           // P7.3 output
    P7SEL |= BIT3;	     // P7.3 options select
    
    TA1CCTL1 = OUTMOD_7;                    // CCR1 reset/set
    TA1CCTL2 = OUTMOD_7;                    // CCR2 reset/set

    TimerA1_PWM_1(2000);
    TimerA1_PWM_2(2000);
}
