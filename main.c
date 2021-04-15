#include "./ext2/ext2_info.h"

int printExtInfo(int fd){
  char name[16];
  char lastMounted[256];
  printf("INFO INODE\n");
  printf("Mida Inode:     %d\n",       readInodeSizeExt(fd));
  printf("Num Inodes:     %d\n",       readInodeCount(fd));
  printf("Primer Inode:   %d\n",       readFirstInodeExt(fd));
  printf("Inodes Grup:    %d\n",       readInodeGroups(fd));
  printf("Inodes Lliures: %d\n\n",     readFreeInodes(fd));

  printf("INFO BLOC\n");
  printf("Mida Bloc:        %u\n",    readBlockSize(fd));
  printf("Blocs Reservats:  %d\n",    readReservedBlocks(fd));
  printf("Blocs Lliures:    %d\n",    readFreeBlocks(fd));
  printf("Total Blocs:      %d\n",    readTotalBlocks(fd));
  printf("Primer Bloc:      %d\n",    readFirstBlock(fd));
  printf("Blocs Grup:       %d\n",    readBlocksGroup(fd));
  printf("Frags Grup:       %d\n\n",  readFragsGroup(fd));

  printf("INFO VOLUM\n");
  printf("Nom volum:            %s\n", readBlockName(fd, name));
  printf("Ultima Comprov:     %s\n", readLastWritten(fd, lastMounted));
  printf("Ultim Muntatge:     %s\n", readLastMounted(fd, lastMounted));
  printf("Ultima Escriptura:  %s\n", readLastWritten(fd, lastMounted));

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
