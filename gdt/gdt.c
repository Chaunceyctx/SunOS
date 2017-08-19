#include "gdt.h"
#include "String.h"

//全局描述符表长度
#define GDT_LENGTH 5	//5个段描述符

//全局描述符表定义
gdt_entry_t gdt_entries[GDT_LENGTH];

//GDTR
gdt_ptr_t gdt_ptr;

//设置段描述符内容
static void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);

//声明内核栈地址
extern uint32_t stack;

//初始化全局描述符表
void init_gdt() {
	//全局描述符表界限
	gdt_ptr.limit = sizeof(gdt_entry_t) * GDT_LENGTH - 1;	//从0开始，所以总长减去1
	gdt_ptr.base = (uint32_t)(&gdt_entries);
	
	//采用Intel Flat Mode
	gdt_set_gate(0, 0, 0, 0, 0);	//按照Intel 文档要求，第一个描述符必须全0
	gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);	//指令段
	gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);	// 数据段
	gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);	// 用户模式代码段
	gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);	// 用户模式数据段
	
	// 加载全局描述符表地址到GPTR寄存器
	gdt_flush((uint32_t)&gdt_ptr);
}

//全局描述符表构造函数，根据下标构造
//参数分别是数组下标，基地址，限长，访问标志，其他访问标志
static void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
	gdt_entries[num].base_low	= (base & 0xFFFF);	//只取后16位（0～15）
	gdt_entries[num].base_middle	= (base >> 16) & 0xFF;	//去掉后16位，取中间8位（16～23）
	gdt_entries[num].base_high	= (base >> 24) & 0xFF;	//去掉后24位，去最后8位（24～31）
	
	gdt_entries[num].limit_low	= (limit && 0xFFFF);	//界限低16位（0～15）
	gdt_entries[num].granularity	= (limit >> 16) & 0x0F;	//得到界限高4位（19～16），实际上granularity是段描述符中间一堆内容
	gdt_entries[num].granularity	|= gran &0xF0;
	gdt_entries[num].access = access; 
		
}


