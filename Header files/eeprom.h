#ifndef SPI_EEPROM_H
#define SPI_EEPROM_H

#include "types.h"

// EEPROM read/write
void ByteWrite_25LC512(u16 addr, u8 data);
u8 ByteRead_25LC512(u16 addr);

// Mobile and Setpoint helpers
int Get_Setpoint(void);                 // parse "SET xx" from rx_buffer
int Get_Mobile(char *new_mobile);       // parse "MOBILE +xxxxxxxxxxx" from rx_buffer
void Save_Mobile_EEPROM(char *num);     // save mobile to EEPROM
void Load_Mobile_EEPROM(char *num);     // load mobile from EEPROM

#endif
