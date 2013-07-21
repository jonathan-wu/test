#ifndef DELAY_H_
#define DELAY_H_
extern unsigned int CountDown;
extern unsigned long TimeBase;
extern void TimerA1_init();
extern void delayus();
extern unsigned char delayms(unsigned int);
#endif
