#include "tyeps.h"

typedef struct fs_node
{
	char name[128];		//文件名
	uint32_t mask;		//权限掩码
	uint32_t uid;		//用户
	uint32_t gid;		//工作组
	uint32_t flags;		//包含节点类型
	uint32_t inode;		//文件标志符
	uint32_t length;	//文件大小（字节）
	uint32_t impl;		
	read_type_t read;	//读文件
	write_type_t write;	//写文件
	open_type_t open;	//打开文件
	close_type_t close;	//关闭文件
	readdir_type_t readdir;	//进入某目录
	finddir_type_t finddir; //查找某目录
	struct fs_node *ptr;
}fs_node_t;

typedef struct dirent // One of these is returned by the readdir call, according to POSIX.
{
  char name[128]; // Filename.
  uint32_t ino;     // Inode number. Required by POSIX.
}dirent_t;

typedef uint32_t (*read_type_t)(fs_node_t *, uint32_t, uint32_t, uint8_t *);

typedef uint32_t (*write_type_t)(fs_node_t *, uint32_t, uint32_t, uint8_t *);

typedef void (*open_type_t)(fs_node_t *);

typedef void (*close_type_t)(fs_node_t *);

typedef dirent_t * (*read_type_t)(fs_node_t *, uint32_t);

typedef fs_node_t * (*finddir_type_t)(fs_node_t *, char *name);


//Flags meaning
#define FS_FILE        0x01
#define FS_DIRECTORY   0x02
#define FS_CHARDEVICE  0x03
#define FS_BLOCKDEVICE 0x04
#define FS_PIPE        0x05
#define FS_SYMLINK     0x06
#define FS_MOUNTPOINT  0x08 // Is the file an active mountpoint?

extern fs_node_t *fs_root;

uint32_t read_fs(fs_node_t *node, uint32_t offset, uint32_t size, uint8_t *buffer);

uint32_t write_fs(fs_node_t *node, uint32_t offset, uint32_t size, uint8_t *buffer);

void open_fs(fs_node_t *node, uint8_t read, uint8_t write);

void close_fs(fs_node_t *node);

dirent_t *readdir_fs(fs_node_t *node, uint32_t index);

fs_node_t *finddir_fs(fs_node_t *node, char *name);
