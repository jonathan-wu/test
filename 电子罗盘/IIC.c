#include "msp430x54x.h"
#include "UCS.h"
#include "IIC.h"
void IIC_init(void)
{
  P3DIR |= BIT0+BIT1;
  P3OUT &=~(BIT0+BIT1);
  scl_1;
  delay_us(5);
  sda_1;
  delay_us(5);
}
void IIC_start(void)
{
	scl_1; 
	delay_us(5);
	sda_1;
	delay_us(5); 
	sda_0; 
	delay_us(5); 
	scl_0; 
	delay_us(5);
}
void IIC_stop() 
{
	scl_0;
	delay_us(5);
	sda_0; 
	delay_us(5);
	scl_1;
	delay_us(5);
	sda_1;
	delay_us(5);
}
void IIC_writex(unsigned char j)
{  
	unsigned char i,temp;
	temp = j;
	for(i=0; i<8; i++)
	{
		scl_0; 
		delay_us(5); 
                if(temp & 0x80) sda_1;
                else sda_0;
		delay_us(5);
		scl_1; 
		delay_us(5);
		temp = temp << 1; 
	}
	scl_0;
	delay_us(5); 
}
unsigned char IIC_readx(void)
{
	unsigned char i, j, k = 0;
	for(i=0; i<8; i++)
	{
		scl_0;
		delay_us(5);	
                DIR_IN;
		if(sda_H)
		{
			j = 1;
		}
		else j = 0;
                DIR_OUT;
		k = (k << 1) | j; 
		scl_1;
		delay_us(5);
	} 
	return(k);
}
void IIC_ack(void)
{
	unsigned char i = 0;
	scl_1;
	delay_us(5);
        DIR_IN;
	while((sda_H) && (i < 255)) 
	{
		i++;
	}
        DIR_OUT;
	scl_0;
	delay_us(5);
}
void IIC_sendack(unsigned char ack)
{
  if(ack) sda_1;
  else sda_0;
//    SDA = ack;                  //写应答信号
  scl_1;                    //拉高时钟线
  delay_us(5);                 //延时
  scl_0;                    //拉低时钟线
  delay_us(5);                 //延时
}
unsigned char IIC_read(unsigned char address)
{
	unsigned char i;
	IIC_start();
	IIC_writex(Address);
	IIC_ack();
	IIC_writex(address);
	IIC_ack();
	IIC_start();
	IIC_writex(Address+1);
	IIC_ack();
	i = IIC_readx();
	IIC_stop();
	return(i);
}
void IIC_write(unsigned char address, unsigned char info)
{
	IIC_start();
	IIC_writex(Address);
	IIC_ack();
	IIC_writex(address);
	IIC_ack();
	IIC_writex(info);
	IIC_ack();
	IIC_stop();
}