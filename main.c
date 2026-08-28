#include <LPC21xx.h>
#include <stdio.h>
#include <string.h>
#include "lcd.h"
#include "uart.h"
#include "gsm.h"
#include "ds18b20.h"
#include "delay.h"
#include "spi.h"
#include "eeprom.h"
#include "rtc.h"
#define BUZZER (1<<25)
#define PASSKEY "0786"
int setpoint = 20;
extern unsigned int nm_flag;
unsigned int m;
char mobile[20] = "7989026595";
s32 hour,min,sec,date,month,year;
int main()
{
    int temp;
    unsigned char tp,tpd;
	  char new_mobile[20];
		char alert_sms[100];
		char sensor_info[100];
    static int alert_sent = 0; // Only send SMS once per high temp event

    IODIR0 |= BUZZER;

    UART0_Init(9600);
    LCD_Init();
    Init_SPI0();
    RTC_Init();
    GSM_Init();
		delay_ms(1000);
		Write_CMD_LCD(0x01);
		Write_str_LCD("GSM init done!");
		delay_ms(1000);
		GSM_Send_SMS(mobile, "TEST SMS");
		delay_ms(2000);
		Write_CMD_LCD(0x01);
		ByteWrite_25LC512(0x00,20);
		delay_ms(20);

		// Load setpoint and mobile number
		setpoint = ByteRead_25LC512(0x00);

		if(setpoint == 0xFF || setpoint > 100 || setpoint < 1)
		{
			setpoint = 20;
		}

		SetRTCTimeInfo(4,19,00);
		SetRTCDateInfo(27,8,26);

		Write_str_LCD("DS18B20 Interface!");
		delay_ms(1000);

		Write_CMD_LCD(0x01);

		while(1)
		{
			temp = ReadTemp();       // reading temperature from DS18B20 using 1-wire protocol

			tp = temp >> 4;         // getting integer part
			tpd = temp & 0x08?0x35:0x30;      // getting fractional part

    // Display
			Write_CMD_LCD(0x80);

			Write_str_LCD("T:");
			Write_int_LCD(tp);
			Write_DAT_LCD('.');
			Write_DAT_LCD(tpd);
			Write_str_LCD("C ");

			Write_str_LCD(" SP:");
			Write_int_LCD(setpoint);

			Write_CMD_LCD(0xC0);

			// Get and display the current time on LCD
			GetRTCTimeInfo(&hour, &min, &sec);
			DisplayRTCTime(hour, min, sec);

			delay_ms(100);

			// Buzzer + SMS Alert
			if(tp > setpoint)
			{
					IOSET0 = BUZZER;       // Buzzer ON
					delay_ms(1000);        // Buzzer ON for 5 seconds
					IOCLR0 = BUZZER;       // Buzzer OFF
					/* Send alert SMS only once */
          if(alert_sent == 0)
          {
                sprintf(alert_sms,"TEMP HIGH: %d C TIME:%02d:%02d:%02d",tp, hour, min, sec);

                GSM_Send_SMS(mobile, alert_sms);

                alert_sent = 1;
          }
      }
      else
      {
            IOCLR0 = BUZZER;

            /* Reset alert when temperature becomes normal */
      //      alert_sent = 0;
      }


        /* -------- READ INCOMING SMS -------- */

        if(nm_flag)
        {
            if(GSM_Read_SMS())
            {
                char sender[20] = {0};
                char *ptr;
                int i = 0;

      /*          Write_CMD_LCD(0x01);

                Write_CMD_LCD(0x80);
                Write_str_LCD("RX:");

                Write_CMD_LCD(0xC0);
                Write_str_LCD(rx_buffer);

                delay_ms(2000);*/


                /* -------- PARSE SENDER NUMBER -------- */

                ptr = strstr(rx_buffer, "91");

                if(ptr)
                {
                    ptr = ptr + 2;

                    while(*ptr >= '0' &&
                          *ptr <= '9')
                    {
                        if(i < 10)
                        {
                            sender[i++] = *ptr;
                        }

                        ptr++;

                        if(i >= 10)
                            break;
                    }

                    sender[i] = '\0';
                }


                /* -------- CHECK STORED MOBILE NUMBER -------- */

                if(strcmp(sender, mobile) == 0)
                {
                    int new_sp;
                    char *ptr1;
										int j=0;
                    ptr1 = strstr(rx_buffer, PASSKEY);

                    if(ptr1)
                    {
                        /* Skip 4 digit passkey */
                        ptr1 = ptr1 + 4;


                        /* -------- SETPOINT COMMAND -------- */

                        if(*ptr1 == 'T')
                        {
                            ptr1++;

                            new_sp = atoi(ptr1);

                            if(new_sp >= 1 &&
                               new_sp <= 100)
                            {
                                setpoint = new_sp;

                                ByteWrite_25LC512(0x00,
                                                  setpoint);

                                delay_ms(100);

                                GSM_Send_SMS(mobile,
                                             "SETPOINT UPDATED");

                                delay_ms(100);

                                Write_CMD_LCD(0x01);

                                delay_ms(2000);

                                Write_CMD_LCD(0x80);
                                Write_str_LCD(
                                    "Setpoint updated!");

                                Write_CMD_LCD(0xC0);
                                Write_str_LCD("SP:");
                                Write_int_LCD(setpoint);

                                delay_ms(2000);

                                Write_CMD_LCD(0x01);
                            }
                        }


                        /* -------- MOBILE NUMBER COMMAND -------- */

                        else if(*ptr1 == 'M')
                        {
                            //int j = 0;
                            char new_mobile[20];

                            ptr1++;

                            while(*ptr1 >= '0' &&
                                  *ptr1 <= '9' &&
                                  j < 10)
                            {
                                new_mobile[j++] =
                                    *ptr1++;
                            }

                            new_mobile[j] = '\0';

                            strcpy(mobile,
                                   new_mobile);

                            Save_Mobile_EEPROM(mobile);

                            GSM_Send_SMS(
                                mobile,
                                "MOBILE UPDATED");

                            //delay_ms(2000);
                        }


                        /* -------- SENSOR INFORMATION COMMAND -------- */

                        else if(*ptr1 == 'I')
                        {
                            ptr1++;

                            sprintf(sensor_info,
                                    "TEMP:%d C TIME:%02d:%02d:%02d",
                                    tp, hour, min, sec);

                            GSM_Send_SMS(
                                mobile,
                                sensor_info);
                        }


                        /* -------- INVALID COMMAND -------- */

                        else
                        {
                            GSM_Send_SMS(
                                mobile,
                                "INVALID COMMAND");
                        }
                    }
                    else
                    {
                        GSM_Send_SMS(
                            mobile,
                            "PASSKEY INVALID");
                    }
                }
                else
                {
                    /* Unauthorized sender */
                    GSM_Send_SMS(sender,"NOT AUTHORIZED");
                }
							}


                /* Clear SMS flag */
                nm_flag = 0;

                /* Delete SMS */
                UART0_ClearBuffer();
                UART0_Str("AT+CMGD=1\r\n");
                GSM_Wait_Response();
						}
                delay_ms(2000);
         }
}


    