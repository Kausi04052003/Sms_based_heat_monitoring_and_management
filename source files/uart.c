#include <LPC21xx.h>
#include <string.h>
#include "uart.h"

unsigned int nm_flag;

char buff[200];

unsigned char i = 0;
unsigned char r_flag = 0;


/* UART0 ISR declaration */
void UART0_ISR(void) __irq;


/* UART0 INITIALIZATION */
void UART0_Init(unsigned int baud)
{
    PINSEL0 |= 0x00000005;

    U0LCR = 0x83;

    if(baud == 9600)
    {
        U0DLL = 97;
        U0DLM = 0;
    }

    U0LCR = 0x03;

    /* Enable UART0 Receive Interrupt */
    U0IER = 0x01;

    /* Configure VIC */
    VICIntSelect &= ~(1 << 6);
    VICIntEnable |= (1 << 6);

    VICVectCntl0 = 0x26;
    VICVectAddr0 = (unsigned)UART0_ISR;
}


/* UART0 TRANSMIT ONE CHARACTER */
void UART0_Tx(char ch)
{
    while(!(U0LSR & 0x20));

    U0THR = ch;
}


/* UART0 TRANSMIT STRING */
void UART0_Str(char *str)
{
    while(*str)
    {
        UART0_Tx(*str++);
    }
}


/* CLEAR UART RECEIVE BUFFER */
void UART0_ClearBuffer(void)
{
    memset(buff, '\0', 200);

    i = 0;
    r_flag = 0;
}


/* UART0 INTERRUPT SERVICE ROUTINE */
void UART0_ISR(void) __irq
{
    char ch;

    if((U0IIR & 0x04))
    {
        ch = U0RBR;

        if(i < 198)
        {
            buff[i++] = ch;
            buff[i] = '\0';
        }

        /*
         * GSM response normally contains:
         * +CMTI -> New SMS notification
         * OK    -> Command successful
         * ERROR -> Command failed
         */

        if(strstr(buff, "+CMTI") != NULL)
        {
            nm_flag = 1;
        }
        else if(strstr(buff, "OK\r\n") != NULL)
        {
            r_flag = 1;
        }
        else if(strstr(buff, "ERROR\r\n") != NULL)
        {
            r_flag = 1;
        }
    }

    VICVectAddr = 0;
}