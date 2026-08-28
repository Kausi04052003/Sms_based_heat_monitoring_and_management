#include <LPC21xx.h>
#include "lcd.h"
#include "delay.h"

/* Initialize LCD */
void LCD_Init(void)
{
    WRITEBYTE(IODIR0, LCD_DAT, 0xFF); // Data pins output
    WRITEBIT(IODIR0, RS, 1);
    WRITEBIT(IODIR0, RW, 1);
    WRITEBIT(IODIR0, EN, 1);

    delay_ms(20);

    Write_CMD_LCD(0x30);
    delay_ms(5);
    Write_CMD_LCD(0x30);
    delay_ms(1);
    Write_CMD_LCD(0x30);

    Write_CMD_LCD(0x38); // 8-bit, 2 line
    Write_CMD_LCD(0x0C); // Display ON
    Write_CMD_LCD(0x01); // Clear
    Write_CMD_LCD(0x06); // Cursor increment
}

/* Send command */
void Write_CMD_LCD(char cmd)
{
    WRITEBIT(IOCLR0, RS, 1); // RS = 0
    Write_LCD(cmd);
}

/* Send data */
void Write_DAT_LCD(char dat)
{
    WRITEBIT(IOSET0, RS, 1); // RS = 1
    Write_LCD(dat);
}

/* Low-level write */
void Write_LCD(char ch)
{
    WRITEBIT(IOCLR0, RW, 1); // RW = 0 (write)

    WRITEBYTE(IOPIN0, LCD_DAT, ch);

    WRITEBIT(IOSET0, EN, 1);
    delay_ms(1);
    WRITEBIT(IOCLR0, EN, 1);

    delay_ms(2);
}

/* Print string */
void Write_str_LCD(char *p)
{
    while(*p)
        Write_DAT_LCD(*p++);
}

/* Print integer */
void Write_int_LCD(int n)
{
    char a[10];
    int i = 0;

    if(n < 0)
    {
        Write_DAT_LCD('-');
        n = -n;
    }

    do
    {
        a[i++] = (n % 10) + '0';
        n = n / 10;
    } while(n);

    while(i--)
        Write_DAT_LCD(a[i]);
}

/* Print float */
void Write_float_LCD(float f, char afterpoint)
{
    int n = (int)f;

    Write_int_LCD(n);
    Write_DAT_LCD('.');

    while(afterpoint--)
    {
        f = f * 10;
        n = (int)f;
        Write_DAT_LCD((n % 10) + '0');
    }
}
