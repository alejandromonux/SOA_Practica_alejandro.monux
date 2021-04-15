#include "./ext2/ext2_info.h"

int printExtInfo(int fd){
  char name[16];
  char lastMounted[64];
  printf("INFO INODE\n");
  printf("INODE SIZE      -> %d\n",       readInodeSizeExt(fd));
  printf("NUM   INODES    -> %d\n",       readInodeCount(fd));
  printf("FIRST INODE     -> %d\n",       readFirstInodeExt(fd));
  printf("INODE GROUPS    -> %d\n",       readInodeGroups(fd));
  printf("INODES LLIURES  -> %d\n\n",     readFreeInodes(fd));

  printf("INFO BLOC\n");
  printf("MIDA BLOC       -> %u\n", readBlockSize(fd));
  printf("BLOCS RESERVATS -> %d\n", readReservedBlocks(fd));
  printf("BLOCS LLIURES   -> %d\n", readFreeBlocks(fd));
  printf("BLOCS TOTALS    -> %d\n", readTotalBlocks(fd));
  printf("PRIMER BLOC     -> %d\n", readFirstBlock(fd));
  printf("BLOCS GRUP      -> %d\n", readBlocksGroup(fd));
  printf("FRAGS GRUP      -> %d\n\n", readFragsGroup(fd));

  printf("INFO VOLUM\n");
  printf("NOM VOLUM       -> %s\n", readBlockName(fd, name));
  printf("ULTIM MUNTATGE    -> %s\n", readLastMounted(fd, lastMounted));

  return 0;
}

int main(int argc, char const *argv[]) {

  if (argc < 3){
    printf("Not enough arguments provided. Current amount of arguments is: %d", argc);
    return 0;
  }

  int fd = open(argv[2], 'r');

  printf("FILESYSTEM: ");
  if(readFileTypeExt(fd) == 1){
    printf("EXT2\n\n");
    printExtInfo(fd);
  }else{
    printf("Sam no va tambien la verdá\n");
  }



  return 0;
}
