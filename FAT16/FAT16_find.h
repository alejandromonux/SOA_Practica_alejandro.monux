#ifndef FAT16_FIND
#define FAT16_FIND

#include "./FAT16_delete.h"

int trobarArxiuFAT(int fd, const char *nomArxiu, int dirCluster, char delete);
#endif
