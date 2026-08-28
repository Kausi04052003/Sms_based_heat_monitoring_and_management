#include <string.h>

#include "gsm.h"
#include "uart.h"
#include "delay.h"
#include "lcd.h"


char rx_buffer[200];


/* =========================================================
                    GSM WAIT RESPONSE
   ========================================================= */

void GSM_Wait_Response(void)
{
    while(r_flag == 0);

    strcpy(rx_buffer, buff);

    UART0_ClearBuffer();
}


/* =========================================================
                    GSM INITIALIZATION
   ========================================================= */

void GSM_Init(void)
{
    /* ---------- AT COMMAND ---------- */

    UART0_Str("AT\r\n");

    GSM_Wait_Response();

    if(strstr(rx_buffer, "OK") != NULL)
    {
        Write_CMD_LCD(0x01);
        Write_str_LCD("AT-OK");

        delay_ms(2000);
    }
    else
    {
        Write_CMD_LCD(0x01);
        Write_str_LCD("AT-ERROR");

        delay_ms(2000);

        return;
    }


    /* ---------- ECHO OFF ---------- */

    UART0_ClearBuffer();

    UART0_Str("ATE0\r\n");

    GSM_Wait_Response();

    if(strstr(rx_buffer, "OK") != NULL)
    {
        Write_CMD_LCD(0x01);
        Write_str_LCD("ATE0-OK");

        delay_ms(2000);
    }
    else
    {
        Write_CMD_LCD(0x01);
        Write_str_LCD("ATE0-ERROR");

        delay_ms(2000);

        return;
    }


    /* ---------- SMS TEXT MODE ---------- */

    UART0_ClearBuffer();

    UART0_Str("AT+CMGF=1\r\n");

    GSM_Wait_Response();

    if(strstr(rx_buffer, "OK") != NULL)
    {
        Write_CMD_LCD(0x01);
        Write_str_LCD("AT+CMGF-OK");

        delay_ms(2000);
    }
    else
    {
        Write_CMD_LCD(0x01);
        Write_str_LCD("AT+CMGF-ERROR");

        delay_ms(2000);

        return;
    }


    /* ---------- NEW SMS NOTIFICATION ---------- */

    UART0_ClearBuffer();

    UART0_Str("AT+CNMI=2,1,0,0,0\r\n");

    GSM_Wait_Response();

    if(strstr(rx_buffer, "OK") != NULL)
    {
        Write_CMD_LCD(0x01);
        Write_str_LCD("AT+CNMI-OK");

        delay_ms(2000);
    }
    else
    {
        Write_CMD_LCD(0x01);
        Write_str_LCD("AT+CNMI-ERROR");

        delay_ms(2000);

        return;
    }


    /* ---------- DELETE SMS ---------- */

    UART0_ClearBuffer();

    UART0_Str("AT+CMGD=1\r\n");

    GSM_Wait_Response();

    if(strstr(rx_buffer, "OK") != NULL)
    {
        Write_CMD_LCD(0x01);
        Write_str_LCD("AT+CMGD-OK");

        delay_ms(2000);
    }
    else
    {
        Write_CMD_LCD(0x01);
        Write_str_LCD("AT+CMGD-ERROR");

        delay_ms(2000);
    }

    UART0_ClearBuffer();
}


/* =========================================================
                    SEND SMS
   ========================================================= */

void GSM_Send_SMS(char *number, char *msg)
{
    char cmd[50];

    r_flag = 0;

    UART0_Str("AT+CMGF=1\r\n");

    delay_ms(1000);

    sprintf(cmd, "AT+CMGS=\"%s\"\r\n", number);

    UART0_Str(cmd);

    delay_ms(2000);

    UART0_Str(msg);

    delay_ms(500);

    /* CTRL+Z */
    UART0_Tx(0x1A);

    delay_ms(5000);

    r_flag = 0;
}


/* =========================================================
                    READ SMS
   ========================================================= */

int GSM_Read_SMS(void)
{
    r_flag = 0;

    UART0_ClearBuffer();

    UART0_Str("AT+CMGF=1\r\n");

    GSM_Wait_Response();

    UART0_Str("AT+CMGR=1\r\n");

    GSM_Wait_Response();

    return 1;
}