#include "./ext2/ext2_info.h"
#include "./FAT16/FAT16_info.h"

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

int printFAT16Info(int fd){
  char name[11];
  char VolName[8];
  //char lastMounted[256];
  printf("System Name:         %s\n", readVolumeName(fd, VolName));
  printf("Mida del Sector:     %u\n", readBytesPerSector(fd));
  printf("Sectors Per Cluster: %u\n", readSectorsPerCluster(fd));
  printf("Sectors Reservats:   %u\n", readReservedSectors(fd));
  printf("Numero de FATs:      %u\n", readNumOfFAT(fd));
  printf("MaxRootEntries:      %u\n", readMaxRootEnt(fd));
  printf("Sectors per FAT:     %u\n", readSectorsPerFat(fd));
  printf("Label:               %s\n", readVolumeLabel(fd, name));


  return 0;
}

int main(int argc, char const *argv[]) {

  if (argc < 3){
    printf("Not enough arguments provided. Current amount of arguments is: %d", argc);
    return 0;
  }
  if (strcmp(argv[1],"/info") == 0  ){
      int fd = open(argv[2], 'r');

      if(readFileTypeExt(fd) == 1){
        printf("FILESYSTEM: EXT2\n\n");
        printExtInfo(fd);
      }else{
        if(isItFAT16(fd)){
            printf("FILESYSTEM: FAT16\n\n");
            printFAT16Info(fd);
        }else{
          printf("El sistema no es ni EXT2 ni FAT16\n");
        }
      }
    return 0;
  }else{
      printf("No mode selected\n");
      return 0;
  }
}
