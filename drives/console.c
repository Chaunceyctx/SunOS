#include "console.h"
#include "common.h"
#include "vmm.h"
//VGA的显示缓冲起点是0xB8000
static uint16_t *video_memory = (uint16_t*)(0xB8000 + PAGE_OFFSET);


//屏幕光标的坐标
static uint8_t cursor_x = 0;
static uint8_t cursor_y = 0;

static void move_cursor()
{
	//屏幕是80字节宽
	uint16_t cursorLocation = cursor_y * 80 + cursor_x;

	//在这里用到的两个内部寄存器编号为0x3D4和0x3D5，分别表示光标位置的
	//高位与低位
	outb(0x3D4,14);   			//告诉VGA我们要设置的光标的高字节
	outb(0x3D5,cursorLocation >> 8);        //发送高8位
	outb(0x3D4,15);				//告诉VGA我们要设置的光标>    的低字节
	outb(0x3D5,cursorLocation);		//发送低8位
}

void console_clear()
{
	uint8_t attribute_byte = (0 << 4) | (15 & 0x0F); 
	uint16_t blank = 0x20 | (attribute_byte << 8);

	int i;
	for(i = 0;i < 80 * 25;++i){
		video_memory[i] = blank;
	}

	cursor_x = 0;
	cursor_y = 0;
	move_cursor();
}

static void scroll()
{
	//attribute_byte 被构造出一个黑底白字的描述格式
	uint8_t attribute_byte = (0 << 4) | (15 & 0x0F);
 	uint16_t blank = 0x20|(attribute_byte << 8);//space是0x20

	//cursor_y到25的时候就该换行
	if(cursor_y >= 25){
		//将所有行的显示数据复制到上一行，第一行永远消失了
		int i;

		for(i = 0 * 80; i < 24 * 80; ++i){
			video_memory[i] = video_memory[i+80];
		}

		//最后一行数据被填充空格，不显示任何字符
		for(i = 24 * 80; i < 25; ++i){
			video_memory[i] = blank;
		}

		//向上移动了一行，所以cursor_y现在是24
		cursor_y = 24;
	}
}

void console_putc_color(char c, real_color_t back, real_color_t fore)
{
	uint8_t back_color = (uint8_t)back;
	uint8_t fore_color = (uint8_t)fore;

	uint8_t attribute_byte = (back_color << 4) | (fore_color & 0x0f);
	uint16_t attribute = attribute_byte << 8;

	//0x08是退格键的ASCII码
	//0x09是tab键的ASCII码

	if (c == 0x08 && cursor_x){
		cursor_x--;
	} else if (c == 0x09) {
		cursor_x = (cursor_x+8) & ~(8-1);
	} else if (c == '\r') {
		cursor_x = 0;
	} else if (c == '\n') {
		cursor_x = 0;
		cursor_y++;
	} else if (c >= ' ') {
		video_memory[cursor_y * 80 + cursor_x] = c | attribute;
		cursor_x++;
	} 

	//字符满80就换行
	if (cursor_x >= 80){
		cursor_x = 0;
		cursor_y++;
	} 
	
	//如果需要的话换行
	scroll();

	move_cursor();

}


void console_write(char *cstr)
{
	while (*cstr) {
		console_putc_color(*cstr++, rc_black, rc_white);
	}
}


void console_write_color(char *cstr, real_color_t back, real_color_t fore)
{
	while (*cstr) {
		console_putc_color(*cstr++,back,fore);
	} 
}
