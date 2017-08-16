#ifndef INCLUDE_DEBUG_H_
#define INCLUDE_DEBUG_H_

#include "vargs.h"
#include "console.h"
//内核的打印函数
void printk(const char *format, ...);

//内核的带颜色的打印函数
void printk_color(real_color_t back, real_color_t fore, const char *format, ...);

#endif
