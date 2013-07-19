
#include"msp430f5438.h"

#include"UCS.h"
#include"delay.h"
//#include"adc12.h"
//#include"RTC.h"
//#include"DMA.h"
//#include"MPY.h"
//#include"DigtalTube.h"
//#include"I2C.h"
#include"LCD12864.h"

volatile unsigned long long res;
int main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  
  UCS_init();
  
//  ADC12_init();
  
  timerA1_init();  
  
//  RTC_init();
  
//  DMA_init();
  
//  DigtalTube_init();
  
//  I2C_Master_init();
  
  _EINT();

/*  
  RTC_setTypeDef ref;
  ref.year = 1970;
  ref.dow  = 3;
  
  while(RTC_set(&ref));
*/  
  LCD12864_init();
  Display();
  
//  res = MPY_32x32u(0x12345678,0x12345678);
//  DigtalTube_set(0);
//  ADC12CTL0 |= ADC12SC;
//  UCB0IFG |= UCTXIFG;
  while(1);
  {     
  }
}
