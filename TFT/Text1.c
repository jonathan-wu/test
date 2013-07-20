
/* http://zq281598585.taobao.com/  �������	  ELH    enlighten  sunny
�������Ҫ��:51�ں�STC12C5A60S2+22M����	  ����
��ͨ�ĵ���51Ҳ����   ����ˢ���ٶȻ������һЩ
����Ĭ��IO���ӷ�ʽ��
�����ߣ�RS-P3^3;    WR-P3^4;   RD-P3^5;   CS-P3^6;   REST-P3^7;
������: DB0-DB7��������P0^0-P0^7(�������ͨ��8051����������);  
DB8-DB15��������P2^0-P2^7;��8λģʽ��DB0-DB7���Բ����ӣ�
�����������ӷ�ʽ��(��ʹ�ô����ɲ�����)
D_CLK-P1^2;  D_CS-P1^1;  D_DIN-P1^3;  D_OUT-P1^4;  D_PENIRQ-P1^0;
*/


#include  "reg52.h"

#define Bus_16        //16λ����ģʽ,���ʹ��8λģʽ����ע�ʹ���䣬���ʹ��16λģʽ����򿪴˾�
#define  LCD_DataPortH P2     //��8λ���ݿ�,8λģʽ��ֻʹ�ø�8λ 
#define  LCD_DataPortL P0     //��8λ���ݿ�	,8λģʽ�µ�8λ���Բ�����
sbit LCD_RS = P3^3;  		 //����/�����л�
sbit LCD_WR = P3^4;		  //д����
sbit LCD_RD =P3^5;		     //������
sbit LCD_CS=P3^6;		//Ƭѡ	
sbit LCD_REST = P3^7;	      //��λ   



//��ʱ����
void delayms(int count)  // /* X1ms */
{
        int i,j;
        for(i=0;i<count;i++)
                for(j=0;j<1000;j++);
}


 //TFT���ݼ������

#ifdef  Bus_16    //��������-16λ����ģʽ   
void LCD_Writ_Bus(char VH,char VL)   //��������д�뺯��
{
    LCD_DataPortH=VH;	
	LCD_DataPortL=VL;		
	LCD_WR=0;
	LCD_WR=1; 
}
#else			//��������-8λ����ģʽ 
void LCD_Writ_Bus(char VH,char VL)   //��������д�뺯��
{	
    LCD_DataPortH=VH;	
   	LCD_WR=0;
	LCD_WR=1;
	LCD_DataPortH=VL;		
	LCD_WR=0;
	LCD_WR=1;
}
#endif



void Lcd_Write_Com(char VH,char VL)	 //��������-8λ����
{	
    LCD_RS=0;
	LCD_Writ_Bus(VH,VL);
}
void Lcd_Write_Data(char VH,char VL) //��������-8λ����
{
    LCD_RS=1;
	LCD_Writ_Bus(VH,VL);
}
void Lcd_Write_Com_Data(int com,int val)		   //������������
{
	Lcd_Write_Com(com>>8,com);
    Lcd_Write_Data(val>>8,val);
}

//�������귶Χ		��tft����IC�й�
void Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2)
{
	Lcd_Write_Com(0x00,0x50);Lcd_Write_Data(x1>>8,x1);
	Lcd_Write_Com(0x00,0x51);Lcd_Write_Data(x2>>8,x2);
	Lcd_Write_Com(0x00,0x52);Lcd_Write_Data(y1>>8,y1);
	Lcd_Write_Com(0x00,0x53);Lcd_Write_Data(y2>>8,y2);  
  	Lcd_Write_Com(0x00,0x20);Lcd_Write_Data(x1>>8,x1);	  
    Lcd_Write_Com(0x00,0x21);Lcd_Write_Data(y1>>8,y1); 
    Lcd_Write_Com(0x00,0x22);							 
}

//Һ����ʼ��
void Lcd_Init(void)
{

    LCD_REST=1;
    delayms(5);	
	LCD_REST=0;
	delayms(5);
	LCD_REST=1;
	LCD_CS=1;
	LCD_RD=1;
	LCD_WR=1;
	delayms(5);

	LCD_CS =0;  //��Ƭѡʹ��

 Lcd_Write_Com_Data(0x00,0x0000);		
    Lcd_Write_Com_Data(0x00,0x0000);		
    Lcd_Write_Com_Data(0x00,0x0000);	
	Lcd_Write_Com_Data(0x00,0x0001);	
	Lcd_Write_Com_Data(0xA4,0x0001);		
	delayms(10); 
	Lcd_Write_Com_Data(0x60,0x2700);			
	Lcd_Write_Com_Data(0x08,0x0808);		
	Lcd_Write_Com_Data(0x30,0x0214);
	Lcd_Write_Com_Data(0x31,0x3715);
	Lcd_Write_Com_Data(0x32,0x0604);
	Lcd_Write_Com_Data(0x33,0x0E16);
	Lcd_Write_Com_Data(0x34,0x2211);
	Lcd_Write_Com_Data(0x35,0x1500);
	Lcd_Write_Com_Data(0x36,0x8507);
	Lcd_Write_Com_Data(0x37,0x1407);
	Lcd_Write_Com_Data(0x38,0x1403);
	Lcd_Write_Com_Data(0x39,0x0020);
	Lcd_Write_Com_Data(0x90,0x0015);
	Lcd_Write_Com_Data(0x10,0x0410);
	Lcd_Write_Com_Data(0x11,0x0237);
	Lcd_Write_Com_Data(0x29,0x0046);
	Lcd_Write_Com_Data(0x2A,0x0046);
	Lcd_Write_Com_Data(0x07,0x0000);
	Lcd_Write_Com_Data(0x12,0x0189);
	Lcd_Write_Com_Data(0x13,0x1100);
    delayms(150);
	Lcd_Write_Com_Data(0x12,0x01B9);
	Lcd_Write_Com_Data(0x01,0x0100);
	Lcd_Write_Com_Data(0x02,0x0200);
	Lcd_Write_Com_Data(0x03,0x1030);
	Lcd_Write_Com_Data(0x09,0x0001);
	Lcd_Write_Com_Data(0x0A,0x0000);
	Lcd_Write_Com_Data(0x0D,0x0000);
	Lcd_Write_Com_Data(0x0E,0x0030);
	Lcd_Write_Com_Data(0x50,0x0000);
	Lcd_Write_Com_Data(0x51,0x00EF);
	Lcd_Write_Com_Data(0x52,0x0000);
	Lcd_Write_Com_Data(0x53,0x013F);
	Lcd_Write_Com_Data(0x61,0x0001);
	Lcd_Write_Com_Data(0x6A,0x0000);
	Lcd_Write_Com_Data(0x80,0x0000);
	Lcd_Write_Com_Data(0x81,0x0000);
	Lcd_Write_Com_Data(0x82,0x005F);
	Lcd_Write_Com_Data(0x92,0x0100);
	Lcd_Write_Com_Data(0x93,0x0701);
	delayms(80);
	Lcd_Write_Com_Data(0x07,0x0100);
	Lcd_Write_Com_Data(0x20,0x0000);
	Lcd_Write_Com_Data(0x21,0x0000);
	Lcd_Write_Com(0x00,0x22);
	LCD_CS =1;  //�ر�Ƭѡʹ��

}	  

//������ ˢ��
void Pant(char VH,char VL)
{
	int i,j;
	Address_set(0,0,239,319);
    for(i=0;i<320;i++)
	 {
	  for (j=0;j<240;j++)
	   	{
        	 Lcd_Write_Data(VH,VL);
	    }

	  }
}



main()
{  		
	
	Lcd_Init();   //tft��ʼ��
	LCD_CS =0;  //��Ƭѡʹ��	
	Pant(0xff,0xff);	//����	
    while(1)	
    {
     Pant(0xff,0xff);
     delayms(2000);
     Pant(0x00,0x00);
     delayms(2000);
     Pant(0x00,0x1f);
     delayms(2000);
     Pant(0xf8,0x00);
     delayms(2000);
     Pant(0xf8,0x1f);
     delayms(2000);
     Pant(0x07,0xe0);
     delayms(2000);
     Pant(0x7f,0xff);
     delayms(2000);
     Pant(0xff,0xe0);
     delayms(2000);
     }


 	
   	
}	  




