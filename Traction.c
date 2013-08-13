#include "msp430f5438.h"
#include "Global.h"

#ifdef Traction_Used_

void Traction_init()
{
  P1DIR &=~BIT0;
  P1DIR &=~BIT1;
  P1DIR &=~BIT2;
  P1DIR &=~BIT3;
  
  P1IES &=~BIT0;
  P1IES &=~BIT1;
  P1IES &=~BIT2;
  P1IES &=~BIT3;
  P1IFG=0;
  P1IE |=BIT0+BIT1+BIT2+BIT3;
  
  Motor_config(LEAST+200,LEAST+200,LEAST+200,LEAST+200);
}

#pragma vector=PORT1_VECTOR
__interrupt void P1ISR(void)
{      
    switch(P1IV)
    {
    case 0:  
      break;
    case 2:  
      Motor_config(-LEAST,-LEAST,LEAST+300,LEAST+300);
     if (turn!=10)
       {
         turn=10;
         xianshi=TimeBase;
       }  
     break;
    case 4:  
      if ((xianshi!=0)&&(xianshi+250>TimeBase))
        {
          return;
        }
      Motor_config(LEAST-250,LEAST-250,LEAST+150,LEAST+150);
      if (turn!=5)
        {
          turn=5;
        }
      break;
    case 6:
      if ((xianshi!=0)&&(xianshi+250>TimeBase))
        {
          return;
        }
      Motor_config(LEAST+150,LEAST+150,LEAST-250,LEAST-250);
      if (turn!=-5)
        {
          turn=-5;
        }  
      break;
    case 8:
      Motor_config(LEAST+300,LEAST+300,-LEAST,-LEAST);
      if (turn!=-10)
      {
        turn=-10;
        xianshi=TimeBase;
      }  
      break;
    }
  
}

#endif