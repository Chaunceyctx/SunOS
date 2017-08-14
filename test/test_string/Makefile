#------------------------------#
#			       #	
#	Test Makefile	       #	
#			       #
#		---Chauncey    #
#                   2017.8.13  #
#------------------------------#

C_SOURCES = $(wildcard *.c)
C_OBJECTS = $(patsubst %.c, %.o, $(C_SOURCES))


CC = gcc
C_FLAGS = -c -Wall -g -fno-builtin


TARGET = result  
  
all: $(C_OBJECTS)
	@echo 链接文件: $(C_OBJECTS) ... 
	$(CC) $(C_OBJECTS) -o $(TARGET)    
	@#让gcc来链接ld链接要指定标准链接库
  
.c.o:  
	@echo 编译文件: $< ...
	$(CC) $(C_FLAGS) $< -o $@   
  
clean:  
	@echo 删除文件: $(TARGET) $(C_OBJECTS) ...
	rm -rf $(TARGET) $(C_OBJECTS) 

