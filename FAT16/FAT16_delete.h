#ifndef FAT16_DELETE
#define FAT16_DELETE

#include "./FAT16_info.h"

typedef struct DirectoryEntry{
  char nom[8];
  char extensio[3];
  char atribut;
  char reservat[10];
  short lastTime;
  short lastDate;
  short Cluster;
  int   filesize;
}DEntry;

void borrarArxiuFat(int fd, int offset, int entryActual);
#endif
