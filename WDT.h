#ifndef WDT_H_
#define WDT_H_
extern void WDT_init();
#ifdef WDT_PWM_
extern unsigned char WDT_cnt;
extern unsigned char WDT_duty1;
extern void WDT_PWM1();
#endif
#endif