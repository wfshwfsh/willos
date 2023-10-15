#ifndef INCLUDE_STRING_H_
#define INCLUDE_STRING_H_

#include <types.h>

void memcpy(void *dst, void *src, int32_t sz);
void *memset(void *s, int c, int32_t n);

void bzero(void *s, int32_t n);
int strcmp(const char *s1, const char *s2);

char *strcpy(char *dest, const char *src);
char *strcat(char *dest, const char *src);



#endif