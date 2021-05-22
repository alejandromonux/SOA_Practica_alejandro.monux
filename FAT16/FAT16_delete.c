#include "FAT16_delete.h"

void borrarArxiuFat(int fd, int offset, int entryActual){
  DEntry entrada;
  int rootEntries = readRootEntries(fd);
  for (int i = entryActual; i < rootEntries ; i++) {
    offset+=32;
    lseek(fd, offset, SEEK_SET);
    read(fd, &entrada, 32);
    lseek(fd, offset-32, SEEK_SET);
    write(fd, &entrada, 32);
    printf("NOMBRE: %s\n", entrada.nom);
  }
}
