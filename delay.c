#include "delay.h"
void delay_ms(unsigned int ms){unsigned int i,j;for(i=0;i<ms;i++)for(j=0;j<6000;j++);}
void DelayUs(int us)
{
	unsigned int i,j;
	for(j=0;j<us;j++)
	for(i=0;i<10;i++);
}
