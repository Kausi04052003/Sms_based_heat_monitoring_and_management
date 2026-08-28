#ifndef UART_H
#define UART_H

extern char buff[200];

extern unsigned char i;

extern unsigned char r_flag;

extern unsigned int nm_flag;

void UART0_Init(unsigned int baud);

void UART0_Tx(char ch);

void UART0_Str(char *str);

void UART0_ClearBuffer(void);

#endif