#ifndef _LCD_H_
#define _LCD_H_

#include <LPC21xx.h>

/* Pin configuration */
#define LCD_DAT 8
#define RS 17
#define RW 19
#define EN 18

/* Macros (your style) */
#define WRITEBYTE(reg,pos,val) reg = (reg & ~(0xFF<<pos)) | ((val)<<pos)
#define WRITEBIT(reg,bit,val)  (val ? (reg |= (1<<bit)) : (reg &= ~(1<<bit)))

/* Function declarations */
void LCD_Init(void);
void Write_CMD_LCD(char cmd);
void Write_DAT_LCD(char dat);
void Write_LCD(char ch);
void Write_str_LCD(char *p);
void Write_int_LCD(int n);
void Write_float_LCD(float f,char afterpoint);

#endif
