#ifndef UART_H_
#define UART_H_
#define UCA0 0x01
#define UCA1 0x02
#define UCA2 0x04
#define UCA3 0x08
extern void UART_init(unsigned char UCAx,unsigned long int baud);
extern void UART_sendstr(unsigned char UCAx,char *str);
#endif /* UCS_H_ */
