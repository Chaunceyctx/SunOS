#include "String.h"

inline void memcpy(uint8_t *dest, uint8_t *src, uint32_t len)
{
	if (len > strlen(dest)) {
		return;
	}
	for (; len; --len){
		*dest++ = *src++;
	}
}

inline void memset(uint8_t *dest, uint8_t val, uint32_t len)
{
	if (len > strlen(dest)) {
		return;
	}
	for (; len; --len){
		*dest++ = val;
	}
}

inline void bzero(void *dest, uint32_t len)
{
	memset(dest, 0, len);
}

inline int strcmp(const char *str1, const char *str2)
{
	while (*str1 && *str2 && *str1 == *str2){
		str1++;
		str2++;
	}
	return *str1 - *str2; //为0即相同，反之
}

inline char *strcpy(char *dest, const char *src)
{
	char *temp = dest;
	while (*src) {
		*dest++ = *src++;
	}
	*dest = '\0';
	return temp;
}

inline char *strcat(char *dest, const char *src)//涉及到地址重叠问题，src在栈中内存可能紧连着dest尾部
{
	char *temp = dest;
	while (*dest) {
	 	dest++;
	}
	while (*src) {
		*dest++ = *src++;
	}
	return temp;
}

inline int strlen(const char *src)
{
	int len = 0;
	while (*src++) {
		len++;
	}
	return len;
}


