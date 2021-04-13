
#ifndef EXT2_INFO
#define EXT2_INFO

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <fcntl.h>

#define EXT2_ID 61267
#define EXT2_OFFSET 1024

/* FILETYPE */
int readFileTypeExt(int fd);
/* INODE INFO */
int readInodeSizeExt(int fd);
int readFirstInodeExt(int fd);
int readInodeGroups(int fd);
int readInodeCount(int fd);
int readFreeInodes(int fd);
/* BLOCK INFO */
unsigned int readBlockSize(int fd);
int readReservedBlocks(int fd);
int readFreeBlocks(int fd);
int readTotalBlocks(int fd);


#endif
