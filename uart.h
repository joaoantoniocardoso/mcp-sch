#ifndef __UART_H
#define __UART_H

#include "types.h"
#include "system.h"

void   uart_init(uint32 BAUDRATE, uint32 bits, uint32 parity, uint32 stop_bits);

uint32 uart_bytesAvailable();
uint8  uart_get();
bool   uart_send(uint8 byte);

uint32 uart_getBuffer(uint8 * buffer, uint32 size);
uint32 uart_sendBuffer(uint8 * buffer, uint32 size);
void   uart_sendString(const char *str);

#endif
