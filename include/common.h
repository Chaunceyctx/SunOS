#ifndef INCLUDE_COMMON_H_
#define INCLUDE_COMMON_H_

#include "types.h"

void outb(uint16_t port,uint8_t value);
//往端口写入一字节

uint8_t inb(uint16_t port);
//从端口读一个字节

uint16_t inw(uint16_t port);
//从端口读一个字

// 开启中断
void enable_intr();

// 关闭中断
void disable_intr();

#endif 
