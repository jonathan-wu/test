#include "msp430x54x.h"
#include "UART.h"
void UART_init(unsigned char UCAx,unsigned long int baud)
{
	switch(UCAx)
	{
	case UCA0:
	{
            P3SEL |= BIT4+BIT5;
	    UCA0CTL1 |= UCSWRST;
	    UCA0CTL1 |= UCSSEL_2;
	    if(baud==9600)
	    {
		UCA0BR0 = 0x1a;                           // 
		UCA0BR1 = 0x00;                           //
		UCA0MCTL = UCBRS_0+UCBRF_1+UCOS16;          
	    }   
	    if(baud==115200)
	    {
		UCA0BR0 = 0x22;                           // 32k/9600 - 3.41
		UCA0BR1 = 0x00;                           //
		UCA0MCTL = UCBRS_6+UCBRF_0;
	    }
	    UCA0CTL1 &= ~UCSWRST;
//            UCA0IE |= UCTXIE + UCRXIE;
	} break;
	case UCA1:
          {
            P5SEL |= BIT6+BIT7;
	    UCA1CTL1 |= UCSWRST;
	    UCA1CTL1 |= UCSSEL_2;
	    if(baud==9600)
	    {
		UCA1BR0 = 0x1a;                           // 
		UCA1BR1 = 0x00;                           //
		UCA1MCTL = UCBRS_0+UCBRF_1+UCOS16;          
	    }   
	    if(baud==115200)
	    {
		UCA1BR0 = 0x22;                           // 32k/9600 - 3.41
		UCA1BR1 = 0x00;                           //
		UCA1MCTL = UCBRS_6+UCBRF_0;
	    }
	    UCA1CTL1 &= ~UCSWRST;
            UCA1IE |= UCTXIE + UCRXIE;
	} break;
	case UCA2:
          {
            P9SEL |= BIT4+BIT5;
	    UCA2CTL1 |= UCSWRST;
	    UCA2CTL1 |= UCSSEL_2;
	    if(baud==9600)
	    {
		UCA2BR0 = 0x1a;                           // 
		UCA2BR1 = 0x00;                           //
		UCA2MCTL = UCBRS_0+UCBRF_1+UCOS16;          
	    }   
	    if(baud==115200)
	    {
		UCA2BR0 = 0x22;                           // 32k/9600 - 3.41
		UCA2BR1 = 0x00;                           //
		UCA2MCTL = UCBRS_6+UCBRF_0;
	    }
	    UCA2CTL1 &= ~UCSWRST;
            UCA2IE |= UCTXIE + UCRXIE;
	} break;
	case UCA3:
          {
            P10SEL |= BIT4+BIT5;
	    UCA3CTL1 |= UCSWRST;
	    UCA3CTL1 |= UCSSEL_2;
	    if(baud==9600)
	    {
		UCA3BR0 = 0x1a;                           // 
		UCA3BR1 = 0x00;                           //
		UCA3MCTL = UCBRS_0+UCBRF_1+UCOS16;          
	    }   
	    if(baud==115200)
	    {
		UCA3BR0 = 0x22;                           // 32k/9600 - 3.41
		UCA3BR1 = 0x00;                           //
		UCA3MCTL = UCBRS_6+UCBRF_0;
	    }
	    UCA3CTL1 &= ~UCSWRST;
            UCA3IE |= UCTXIE + UCRXIE;
	} break;
	default:break;
	}
}
void UART_sendstr(unsigned char UCAx,char *str)
{
 unsigned char i=0;
  while(str[i]!='\0')
  {
	switch(UCAx)
	{
	case UCA0:
		{
			if(UCA0IFG&0x02)
			{
				UCA0TXBUF = str[i];
				i++;
			}
		}
                 break;
        case UCA1:
		{
			if(UCA1IFG&0x02)
			{
				UCA1TXBUF = str[i];
				i++;
			}
		}
                 break;
        case UCA2:
		{
			if(UCA2IFG&0x02)
			{
				UCA2TXBUF = str[i];
				i++;
			}
		}
                 break;
        case UCA3:
		{
			if(UCA3IFG&0x02)
			{
				UCA3TXBUF = str[i];
				i++;
			}
		}
                 break;
        default:break;
	}
  }
}