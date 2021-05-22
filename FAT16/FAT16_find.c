#include "FAT16_find.h"

int trobarArxiuFAT(int fd, const char *nomArxiu, int dirCluster, char delete){
  int firstRootDirSecNum = readReservedSectors(fd) + (readNumOfFAT(fd) * readFATSz16(fd));
  //int rootCluster = readRootCluster(fd);
  int BytesPerCluster = readBytesPerSector(fd)*readSectorsPerCluster(fd);
  int offsetRootDir = firstRootDirSecNum*readBytesPerSector(fd);
  int counter;
  int entryActual = 0;

  if (dirCluster == 0) {
    counter = offsetRootDir;
  }else{
    double reservedBytes = readReservedSectors(fd)*readBytesPerSector(fd);
    long  FATBytes = readNumOfFAT(fd)*readBytesPerSector(fd)*readFATSz16(fd);
    double rootEntries = readRootEntries(fd)*32;
    counter = reservedBytes + (FATBytes + rootEntries) + (dirCluster - 2)*BytesPerCluster;
  }

  while(entryActual <= (readRootEntries(fd))){
    char nombre[200];
    int filesize;
    memset(nombre, '\0', 200);
    readfilenameFAT(fd, counter, nombre);

    if(nombre[0] == 0){
      counter+=32;
      continue;
    }
    while (readFileType(fd, counter) == 0x0f) {
      counter += 32;
    }
    filesize = readFilesize(fd, counter);
    switch (filesize) {
      case -1:
      break;
      case 0:
        if (readFileType(fd, counter) == 16 /*16=0x10*/) {
          short dirClus = readDirCluster(fd, counter);
          if ((strcmp(nombre, "..") != 0)&&(strcmp(nombre, "...") != 0)&&(strcmp(nombre,"lost+found") != 0)) {
            if (trobarArxiuFAT(fd, nomArxiu, dirClus, delete)) {
              return 1;
            }
          }
        }else if (readFileType(fd, counter) == (16*2) /* 16*2=0x20*/) {
          if(strcmp(nombre, nomArxiu) == 0){
            printf("Fitxer trobat. Ocupa %d bytes\n", filesize);
            return 1;
          }
        }
        break;
      default:
        if (readFileType(fd, counter) == (16*2) /* 16*2=0x20*/) {
          if(strcmp(nombre, nomArxiu) == 0){
            if (delete) {
              printf("HE DE BORRAR EL ARXIU\n");
              borrarArxiuFat(fd, counter, entryActual);
            }else{
              printf("Fitxer trobat. Ocupa %d bytes\n", filesize);
            }
            return 1;
          }
        }

      break;
    }

    counter +=32;
    entryActual++;
  }
  if (dirCluster == 0) {
    printf("Error. Fitxer no trobat.\n");
  }
  return 0;
}
