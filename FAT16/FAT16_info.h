#ifndef FAT16_INFO
#define FAT16_INFO

#include "../tools/utils.h"

/*VERIFICACIO*/
char isItFAT16(int fd);
/*INFO DEL VOLUM*/
char * readVolumeName(int fd, char * name);
char * readVolumeLabel(int fd, char * name);
char readSectorsPerCluster(int fd);
short readReservedSectors(int fd);
char readNumOfFAT(int fd);
short readMaxRootEnt(int fd);

#endif
