#ifndef EXT2_DELETE
#define EXT2_DELETE

#include "./ext2_info.h"

typedef struct DirectoryEntryExt{
  int inode;
  short rec_len;
  char name_len;
  char file_type;
  char *name;
}DEntryExt;

void borrarArxiuExt(int fd, int offset, int entryActual, int inodeTableOffset);
#endif
