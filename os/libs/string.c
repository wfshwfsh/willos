#include <types.h>
#include <string.h>

void memcpy(void *dst, void *src, int32_t sz)
{
	uint8_t *_src = (uint8_t *)src;
	uint8_t *_dst = (uint8_t *)dst;
	
	while(sz--){
		*_dst++ = *_src++;
	};
}

void *memset(void *s, int c, int32_t n)
{
	uint8_t *_dst = (uint8_t *)s;
	
	while(n--){
		*_dst++ = c;
	};
}

void bzero(void *s, int32_t n)
{
	memset(s, 0, n);
}

int strcmp(const char *s1, const char *s2)
{
	while( (*s1!=0) || (*s2!=0))
	{
		int diff = *s1 - *s2;
		if(diff != 0)
			return diff;
	}
	
	return 0;
}

char *strcpy(char *dest, const char *src)
{
	char *beg = dest;
	
	while(*src != 0){
		*dest++ = *src++;
	}
	
	*dest = 0;
	return beg;
}

char *strcat(char *dest, const char *src)
{
	char *cur = dest;
	while(*cur != 0){
		cur++;
	}
	
	while(*src != 0){
		*cur++ = *src++;
	}
	
	*cur = 0;
	return dest;
}

int strlen(const char *s)
{
	const char *beg = s;
	while(*s++)
		;
	
	return (s-beg-1);
	
}
