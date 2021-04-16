#include "FAT16_info.h"


/*
* Checks if the volume is FAT16
*
* Parameters:
*   · fd: file descriptor from which to read
*
* Returns:
*   ·0 if not FAT16, 1 if FAT16
*/
char isItFAT16(int fd){
  float RootDirSectors, DataSec, CountofClusters;
  short BPB_BytsPerSec, BPB_RootEntCnt, BPB_FATSz16, BPB_TotSec16, BPB_ResvdSecCnt;
  int BPB_TotSec32, FATSz, TotSec;
  char BPB_SecPerClus, BPB_NumFATs;

  //Obtenim BPB_BytsPerSec
  lseek(fd, 11, SEEK_SET);
  read(fd, &BPB_BytsPerSec, 2);
  //Obtenim BPB_RootEntCnt
  lseek(fd, 17, SEEK_SET);
  read(fd, &BPB_RootEntCnt, 2);
  //Obtenim BPB_FATSz16
  lseek(fd, 22, SEEK_SET);
  read(fd, &BPB_FATSz16, 2);
  //Obtenim BPB_TotSec16
  lseek(fd, 19, SEEK_SET);
  read(fd, &BPB_TotSec16, 2);
  //Obtenim BPB_TotSec32
  lseek(fd, 32, SEEK_SET);
  read(fd, &BPB_TotSec32, 4);
  //Obtenim BPB_SecPerClus
  lseek(fd, 13, SEEK_SET);
  read(fd, &BPB_SecPerClus, 1);
  //Obtenim BPB_NumFATs
  lseek(fd, 16, SEEK_SET);
  read(fd, &BPB_NumFATs, 1);
  //Obtenim BPB_ResvdSecCnt
  lseek(fd, 14, SEEK_SET);
  read(fd, &BPB_ResvdSecCnt, 2);

  //Calculem RootDirSectors
  RootDirSectors = ((BPB_RootEntCnt * 32) + (BPB_BytsPerSec-1)) / BPB_BytsPerSec;

  if(RootDirSectors == 0){
    //Es FAT32
    return 0;
  }

  //Calculem numero de sectors
  if(BPB_FATSz16 != 0){
    FATSz = BPB_FATSz16;
  }else{
    //FATSz = BPB_FATSz32;
  }
  if(BPB_TotSec16 != 0){
    TotSec = BPB_TotSec16;
  }else{
    TotSec = BPB_TotSec32;
  }
  DataSec = TotSec-(BPB_ResvdSecCnt + (BPB_NumFATs * FATSz) + RootDirSectors);

  CountofClusters = DataSec / BPB_SecPerClus;

  if(CountofClusters < 4085) {
    /* Volume es FAT12 */
    return 0;
  } else if(CountofClusters < 65525) {
   /* Volume es FAT16 */
   return 1;
  } else {
   /* Volume es FAT32 */
   return 0;
  }
}

/*
* Reads Volume Label
*
* Parameters:
*   · fd: file descriptor from which to read
*
* Returns:
*   ·11 char array of Volume Label
*/
char * readVolumeLabel(int fd, char * name){
  lseek(fd, 43, SEEK_SET);
  read(fd, name, 11);

  return name;
}

/*
* Reads sectors per cluster
*
* Parameters:
*   · fd: file descriptor from which to read
*
* Returns:
*   · char of sectors per cluster
*/
char readSectorsPerCluster(int fd){
  char aux;
  lseek(fd, 13, SEEK_SET);
  read(fd, &aux, 1);

  return aux;
}

/*
* Reads reserved sectors
*
* Parameters:
*   · fd: file descriptor from which to read
*
* Returns:
*   · char of reserved sectors
*/
short readReservedSectors(int fd){
  short aux;
  lseek(fd, 14, SEEK_SET);
  read(fd, &aux, 2);

  return aux;
}

/*
* Reads Num FATs
*
* Parameters:
*   · fd: file descriptor from which to read
*
* Returns:
*   · char of Num FATs
*/
char readNumOfFAT(int fd){
  char aux;
  lseek(fd, 16, SEEK_SET);
  read(fd, &aux, 1);

  return aux;
}
