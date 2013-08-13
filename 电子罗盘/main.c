
#include "msp430x54x.h"
#include "UCS.h"
#include "IIC.h"
#include "HMC5883.h"
int x[100],y[100],z[100];
volatile double angle;
int i;
int main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  UCS_init();
  HMC5883_init();
  delay_ms(500);
  for(i=0;i<100;i++)
  {
    x[i]=HMC5883_Get_x();
    y[i]=HMC5883_Get_y();
    z[i]=HMC5883_Get_z();
    delay_ms(10);
  }
  while(1);
}