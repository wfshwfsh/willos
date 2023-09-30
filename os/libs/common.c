#include "common.h"

// write byte to register
void outb(uint16_t port, uint8_t data)
{
	asm volatile("outb %0,%w1" :: "a" (data), "d" (port));
}

// read byte to register
uint8_t inb(uint16_t port)
{
	uint8_t data;
	asm volatile("inb %w1,%0" : "=a" (data) : "d" (port));
	return data;
}

// read word to register
uint16_t inw(uint16_t port)
{
	uint16_t data;
	asm volatile("inw %w1,%0" : "=a" (data) : "d" (port));
	return data;
}

void memcpy(void *dst, void *src, int32_t sz)
{
	uint8_t *_src = (uint8_t *)src; 
	uint8_t *_dst = (uint8_t *)dst; 
  
	int i;
	for(i=0;i<sz;i++)
		_dst[i] = _src[i];
}