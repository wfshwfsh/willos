
#ifndef INCLUDE_COMMON_H_
#define INCLUDE_COMMON_H_

#include "types.h"

// write byte to register
void outb(uint16_t port, uint8_t data);

// read byte to register
uint8_t inb(uint16_t port);

// read word to register
uint16_t inw(uint16_t port);


#endif // INCLUDE_COMMON_H_
