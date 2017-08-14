#----------------------------------#
#	     Makefile		   #
#----------------------------------#

C_SOURCES = $(shell find . -name "*.c")
C_OBJECTS = $(patsubst %.c, %.o, $(C_SOURCES))
S_SOURCES = $(shell find . -name "*.s")
S_OBJECTS = $(patsubst %.s, %.o, $(S_SOURCES))

CC = gcc
LD = ld
ASM = nasm

C_FLAGS = -c -Wall -m32 -ggdb -gstabs+ -nostdinc -fno-builtin -fno-stack-protector -I include
LD_FLAGS = -T scripts/kernel.ld -m elf_i386 -nostdlib
ASM_FLAGS = -f elf -g -F stabs

all: $(S_OBJECTS) $(C_OBJECTS) link update_image

.c.o:
	@echo 编译代码文件 $< ...
	$(CC) $(C_FLAGS) $< -o $@

.s.o:
	@echo 编译汇编文件 $< ...
	$(ASM) $(ASM_FLAGS) $<

link:
	@echo 链接内核文件...
	$(LD) $(LD_FLAGS) $(S_OBJECTS) $(C_OBJECTS) -o Sunny_kernel

.PHONY:clean
clean:
	$(RM) $(S_OBJECTS) $(C_OBJECTS) Sunny_kernel

.PHONY:update_image
update_image:
	sudo mount floppy.img /mnt/
	sudo cp Sunny_kernel /mnt
	sleep 1
	sudo umount /mnt
	@#比如我在光驱里面放一个光盘，硬盘的文件系统是EXT的，但光盘是ISO，而且光盘原本不存在于已经挂载的目录中，那我们怎么可以访问光盘呢？
	@#mount命令就是把光盘挂载到某个目录中，同时你要指定文件系统（也可以不指定，但最好指定）这样，光盘就会作为整个操作系统文件系统的一个分支。
	@#你就可以想访问硬盘文件一样访问光盘上的内容,此处无非是想吧floppy镜像文件放到mnt，然后进行cp访问
.PHONY:mount_image
mount_image:
	sudo mount floppy.img /mnt/

.PHONY:umount_image
umount_image:
	sudo umount /mnt
.PHONY:qemu
qemu:
	sudo qemu -fda floppy.img -boot a

.PHONY:bochs
bochs:
	bochs -f scripts/bochsrc.txt

.PHONY:debug
debug:
	sudo qemu -S -s -fda floppy.img -boot a &
	sleep 1
	cgdb -x scripts/gdbinit
