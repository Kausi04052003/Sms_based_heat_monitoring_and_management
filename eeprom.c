#include <LPC21xx.h>
#include <string.h>
#include "spi.h"
#include "eeprom.h"
#include "spi_defines.h"
#include "delay.h"
#include "gsm.h"   // needed for rx_buffer
#include "types.h"

#define WREN  0x06
#define WRITE 0x02
#define READ  0x03
#define MOBILE_EEPROM_ADDR 0x10

/* --- SPI EEPROM Basic --- */
void EEPROM_Write_Enable()
{
    IOCLR0 = CS;
    SPI0(WREN);
    IOSET0 = CS;
}

void ByteWrite_25LC512(u16 addr, u8 data)
{
    EEPROM_Write_Enable();

    IOCLR0 = CS;
    SPI0(WRITE);
    SPI0(addr>>8);
    SPI0(addr);
    SPI0(data);
    IOSET0 = CS;

    delay_ms(10);
}

u8 ByteRead_25LC512(u16 addr)
{
    u8 data;
    IOCLR0 = CS;
    SPI0(READ);
    SPI0(addr>>8);
    SPI0(addr);
    data = SPI0(0xFF);
    IOSET0 = CS;

    return data;
}

/* --- Parse new setpoint from SMS --- */
int Get_Setpoint(void)
{
    char *ptr = strstr(rx_buffer,"T");
    if(ptr)
    {
        int val=0;
        ptr ++;
        while(*ptr>='0' && *ptr<='9')
        {
            val = val*10 + (*ptr-'0');
            ptr++;
        }
        return val;
    }
    return -1;
}

/* --- Parse new mobile number from SMS --- */
/*int Get_Mobile(char *new_mobile)
{
	   int i=0;
    char *ptr = strstr(rx_buffer,"MOBILE");
    if(ptr)
    {
        ptr += 6; // Skip "MOBILE"
        while(*ptr==' ') ptr++;
        while((*ptr>='0' && *ptr<='9') || *ptr=='+')
        {
            new_mobile[i++] = *ptr++;
        }
        new_mobile[i] = '\0';
        return 1;
    }
    return 0;
}*/

/* --- Save mobile to EEPROM --- */
void Save_Mobile_EEPROM(char *num)
{
    u8 len = strlen(num);
	   u8 i=0;
    ByteWrite_25LC512(MOBILE_EEPROM_ADDR, len);
    for(i=0; i<len; i++)
        ByteWrite_25LC512(MOBILE_EEPROM_ADDR + 1 + i, num[i]);
}

/* --- Load mobile from EEPROM --- */
void Load_Mobile_EEPROM(char *num)
{
    u8 len = ByteRead_25LC512(MOBILE_EEPROM_ADDR);
	   u8 i=0;
    if(len==0xFF || len==0)
    {
        strcpy(num,"+919876543210"); // default
        return;
    }
    for(i=0; i<len; i++)
        num[i] = ByteRead_25LC512(MOBILE_EEPROM_ADDR + 1 + i);
    num[len]='\0';
}
