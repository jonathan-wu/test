#include "msp430x54x.h"
#include "UCS.h"
#include "HMC5883.h"
#include "IIC.h"
void HMC5883_init(void)
{
  IIC_init();
  IIC_write(0x00,0x78);
  IIC_write(0x01,0x20);
  IIC_write(0x02,0x00);
}
void Multiple_read_HMC5883(unsigned char *BUF)
{
  unsigned char i;
  for (i=0; i<8; i++)                      //连续读取6个地址数据，存储中BUF
  {
      BUF[i] = IIC_read(0x03+i);          //BUF[0]存储数据
  }
}
int HMC5883_Get_x(void)
{
  union
  {
    int x;
    unsigned char val[2];
  };
  while(!(IIC_read(0x09) & BIT0)); 
  val[1]=IIC_read(0x03);
  val[0]=IIC_read(0x04);
  return x;
}
int HMC5883_Get_y(void)
{
  union
  {
    int y;
    unsigned char val[2];
  };
  while(!(IIC_read(0x09) & BIT0)); 
  val[1]=IIC_read(0x05);
  val[0]=IIC_read(0x06);
  return y;
}
int HMC5883_Get_z(void)
{
  union
  {
    int z;
    unsigned char val[2];
  };
  while(!(IIC_read(0x09) & BIT0)); 
  val[1]=IIC_read(0x07);
  val[0]=IIC_read(0x08);
  return z;
}