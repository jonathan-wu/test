
#include "msp430x54x.h"
#include "UCS.h"
#include "GUI.h"

void Pant(int Val);
int main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  UCS_init();
  GUI_init();
  //LCD_CS_0;  //打开片选使能	
  Clear_Screen();
  Draw_Circle(100,100,200,0xf000);
  Draw_Line(1,1,2,240,0x000f);
  Draw_Line(1,100,200,105,0x00ff);
  while(1);
}
  




