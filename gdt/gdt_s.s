[GLOBAL gdt_flush]

gdt_flush:
	mov eax, [esp+4]	;参数存入eax寄存器
	lgdt [eax]		;加载到GDTR修改原先[GRUB设置的GDTR]，GRUB引导过程中会自己创建临时GDT
	
	mov ax, 0x10		;加载数据段描述符
	mov ds, ax		;更新所有可以更新的段寄存器
	mov es, ax		
	mov fs, ax
	mov gs, ax
	mov ss, ax
	jmp 0x08:.flush		;远跳转，0x08是代码段描述符
				;远跳的目的是清空流水线并串行化处理器

.flush:
	ret
	
