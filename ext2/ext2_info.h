
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

//READ INFO
int readFileTypeExt(int fd);

#endif
