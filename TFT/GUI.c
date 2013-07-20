#include "msp430x54x.h"
#include "TFT.h"
#include "GUI.h"
void GUI_init(void)
{
  TFT_init();
}
void Fill_Window(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,unsigned int color)
{
  int i,j,it,jt;
  it=x2-x1;
  jt=y2-y1;
  LCD_CS_0;
  Address_set(x1,y1,x2,y2);
  for(i=0;i<=it;i++)
  {
    for (j=0;j<=jt;j++)
    {
      Lcd_Write_Data(color);
    }
  }
  LCD_CS_1;
}
void Clear_Screen(void)
{
  Fill_Window(0,0,239,319,0xffff);
}
void Draw_Point(unsigned int x,unsigned int y,unsigned int color)
{
  LCD_CS_0;
  Address_set(x,y,x,y);
  Lcd_Write_Data(color);
  LCD_CS_1;
}
void Draw_Vline(unsigned int x,unsigned int y1,unsigned int y2,unsigned int color)
{
  Fill_Window(x,y1,x,y2,color);
}
void Draw_Hline(unsigned int x1,unsigned int x2,unsigned int y,unsigned int color)
{
  Fill_Window(x1,y,x2,y,color);
}
void Draw_Rectangle(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,unsigned int color)
{
  Draw_Vline(x1,y1,y2,color);
  Draw_Vline(x2,y1,y2,color);
  Draw_Hline(x1,x2,y1,color);
  Draw_Hline(x1,x2,y2,color);
}

/********************************************************
* 名称 Draw_Line()
      采用布兰森汉姆(Bresenham)算法画线
* 功能：任意两点间的直线。根据硬件特点，实现加速。
* 入口参数：x0       直线起点所在行的位置
*         y0       直线起点所在列的位置
*         x1     直线终点所在行的位置
'       y1     直线终点所在列的位置
* 出口参数：   无
* 说明：操作失败原因是指定地址超出缓冲区范围。
*********************************************************/
void Draw_Line(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, unsigned int color)
{
  signed int temp;
  signed int dx,dy;               //定义起点到终点的横、纵坐标增加值
  signed int s1,s2,status,i;
  signed int Dx,Dy,sub;

  dx=x1-x0;
  if(dx>=0)                 //X的方向是增加的
    s1=1;
  else                     //X的方向是降低的
    s1=-1;
  dy=y1-y0;                 //判断Y的方向是增加还是降到的
  if(dy>=0)
    s2=1;
  else
    s2=-1;
    
  Dx=(x1-x0)*s1;             //计算横、纵标志增加值的绝对值
  Dy=(y1-y0)*s2;
  if(Dy>Dx)                                
  {                         //以45度角为分界线，靠进Y轴是status=1,靠近X轴是status=0 
    temp=Dx;
    Dx=Dy;
    Dy=temp;
    status=1;
  } 
  else
    status=0;
  
  /********判断垂直线和水平线********/
  if(dx==0)                   //横向上没有增量，画一条垂直线
  {
	Draw_Vline(x0,y0,y1,color);
	return;
  }
  if(dy==0)                   //纵向上没有增量，画一条水平线
  {
    Draw_Hline(x0,x1,y1,color);
    return;
  }
  
  
  /*********Bresenham算法画任意两点间的直线********/ 
    sub=(Dy<<1)-Dx;                 //第1次判断下个点的位置
    for(i=0;i<Dx;i++)
    { 
      Draw_Point(x0, y0, color);           //画点 
      if(sub>=0)                               
      { 
        if(status==1)               //在靠近Y轴区，x值加1
          x0+=s1; 
        else                     //在靠近X轴区，y值加1               
          y0+=s2; 
        sub-=Dx<<1;                 //判断下下个点的位置 
      } 
      if(status==1)
        y0+=s2; 
      else       
        x0+=s1; 
      sub+=Dy<<1; 
    } 
}
void Draw_Circle(unsigned int x0,unsigned int y0,unsigned int r, unsigned int color)
{
  int x=0,y=r,f=0;  
  while(x<=y)   
  { 
    if ((x0+x<240)&&(x0+x>=0)&&(y0+y<320)&&(y0+y>=0))
        Draw_Point(x0+x,y0+y,color);    
    if ((x0+x<240)&&(x0+x>=0)&&(y0-y<320)&&(y0-y>=0))    	
        Draw_Point(x0+x,y0-y,color);    
    if ((x0-x<240)&&(x0-x>=0)&&(y0+y<320)&&(y0+y>=0))
        Draw_Point(x0-x,y0+y,color);    
    if ((x0-x<240)&&(x0-x>=0)&&(y0-y<320)&&(y0-y>=0))
        Draw_Point(x0-x,y0-y,color);    
    if ((x0+y<240)&&(x0+y>=0)&&(y0+x<320)&&(y0+x>=0))	    
        Draw_Point(x0+y,y0+x,color);    
    if ((x0+y<240)&&(x0+y>=0)&&(y0-x<320)&&(y0-x>=0))	    
        Draw_Point(x0+y,y0-x,color);    
    if ((x0-y<240)&&(x0-y>=0)&&(y0+x<320)&&(y0+x>=0))	    
        Draw_Point(x0-y,y0+x,color);    
    if ((x0-y<240)&&(x0-y>=0)&&(y0-x<320)&&(y0-x>=0))	    
        Draw_Point(x0-y,y0-x,color);    
    if(f<=0)     
    {      
      f=f+2*x+1;      
      x++;     
    }     
    else      
    {       
      f=f-2*y+1;       
      y--;      
    }   
  }
}
