#ifndef GSM_H
#define GSM_H

extern char rx_buffer[200];

void GSM_Init(void);
void GSM_Send_SMS(char *number, char *msg);
int GSM_Read_SMS(void);

#endif
