#ifndef IIC_H_
#define IIC_H_
#define scl_1 P3OUT |= BIT0  //SCL
#define scl_0 P3OUT &=~BIT0
#define sda_1 P3OUT |= BIT1  //SDA
#define sda_0 P3OUT &=~BIT1
#define sda_H P3IN & BIT1
#define DIR_IN P3DIR &=~BIT1
#define DIR_OUT P3DIR |=BIT1
#define Address 0x3C        //�豸��ַ
extern void IIC_init(void);
extern void IIC_start(void);
extern void IIC_stop();
extern void IIC_writex(unsigned char j);
extern unsigned char IIC_readx(void);
extern void IIC_ack(void);
extern void IIC_sendack(unsigned char ack);
extern unsigned char IIC_read(unsigned char address);             //����ַΪaddress��ֵ
extern void IIC_write(unsigned char address, unsigned char info); //дֵinfo����ַaddress��
#endif 
