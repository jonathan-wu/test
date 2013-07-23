#include "msp430f5438.h"

void Hall_init()
{
    ADC12CTL0 &= ~ADC12ENC;    //Ê§ÄÜ×ª»»
}