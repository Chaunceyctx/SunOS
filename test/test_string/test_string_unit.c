#include "String.h"
#include <stdio.h>

int main(int argc, char *argv[]){
	uint8_t memcpy_dest[] =	"hello ";
	uint8_t memcpy_src[] = "world";
	uint32_t memcpy_len  = (uint32_t)strlen(memcpy_src);
	memcpy(memcpy_dest, memcpy_src, 3);
	memset(memcpy_dest, 'a', 4);
	bzero(memcpy_dest, 3);
	for(int i = 0;i < sizeof(memcpy_dest)/sizeof(uint8_t);++i) {
		printf("%c",memcpy_dest[i]);
	}
	printf("%d",strcmp(memcpy_dest,memcpy_src));
	printf("%s",strcpy(memcpy_dest, memcpy_src));
	//printf("%s",strcat(memcpy_dest, memcpy_src));
	return 0;
}
