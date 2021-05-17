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
* Reads Volume Name
*
* Parameters:
*   · fd: file descriptor from which to read
*
* Returns:
*   ·8 char array of Volume Name
*/
char * readVolumeName(int fd, char * name){
lseek(fd, 3, SEEK_SET);
read(fd, name, 8);

return name;
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

/*
* Reads Root Entries
*
* Parameters:
*   · fd: file descriptor from which to read
*
* Returns:
*   · short of Root Entries
*/
short readMaxRootEnt(int fd){
short aux;
lseek(fd, 17, SEEK_SET);
read(fd, &aux, 2);

return aux;
}

/*
* Reads Bytes Per Sector
*
* Parameters:
*   · fd: file descriptor from which to read
*
* Returns:
*   · short of Bytes Per Sector
*/
short readBytesPerSector(int fd){
short aux;
//Obtenim BPB_BytsPerSec
lseek(fd, 11, SEEK_SET);
read(fd, &aux, 2);

return aux;
}


/*
* Reads Sectors per FAT
*
* Parameters:
*   · fd: file descriptor from which to read
*
* Returns:
*   · short of Sectors per FAT
*/
short readSectorsPerFat(int fd){
short aux, out;
char fats;
//Obtenim BPB_NumFATs
lseek(fd, 16, SEEK_SET);
read(fd, &fats, 1);
//Obtenim BPB_TotSec16
lseek(fd, 19, SEEK_SET);
read(fd, &aux, 2);
out = round(aux/fats);
return out;
}

/*
* Reads FATSz16
*
* Parameters:
*   · fd: file descriptor from which to read
*
* Returns:
*   · short of FATSz16
*/
short readFATSz16(int fd){
short aux;
//Obtenim BPB_BytsPerSec
lseek(fd, 22, SEEK_SET);
read(fd, &aux, 2);

return aux;
}

/*
* Reads Root cluster
*
* Parameters:
*   · fd: file descriptor from which to read
*
* Returns:
*   · short of Root cluster
*/
int readRootCluster(int fd){
int aux;
//Obtenim BPB_BytsPerSec
lseek(fd, 44, SEEK_SET);
read(fd, &aux, 4);

return aux;
}

/*
* Reads filesize
*
* Parameters:
*   · fd: file descriptor from which to read
*
* Returns:
*   · int of filesize
*/
int readFilesize(int fd, int offset){
int aux;
//Obtenim BPB_BytsPerSec
lseek(fd, offset+28, SEEK_SET);
read(fd, &aux, 4);

return aux;
}

/*
* Reads filename
*
* Parameters:
*   · fd: file descriptor from which to read
*
* Returns:
*   · char * of filename
*/

int readLongName(int fd, int offset, char * out, int nameIndex){
  lseek(fd, offset, SEEK_SET);
  int index = nameIndex;
  LFN aux;

  lseek(fd, offset, SEEK_SET);
  read(fd, &aux.sequenceNo, 1);
  lseek(fd, offset+11, SEEK_SET);
  read(fd, &aux.fileattribute, 1);
  lseek(fd, offset+1, SEEK_SET);
  read(fd, &aux.fileName_Part1, 10);
  lseek(fd, offset+14, SEEK_SET);
  read(fd, &aux.fileName_Part2, 12);
  lseek(fd, offset+28, SEEK_SET);
  read(fd, &aux.fileName_Part3, 4);

  if (aux.fileattribute == 0x0f) {
    if (aux.sequenceNo != 0x01) {
     index = readLongName(fd, offset+32, out, index);
    }
    for (int i = 0; i < 10; i++) {
      if ((aux.fileName_Part1[i]!= 0)&&(aux.fileName_Part1[i]!= -1)) {
        out[index++] = aux.fileName_Part1[i];
      }
    }
    for (int i = 0; i < 12; i++) {
      if ((aux.fileName_Part2[i]!= 0)&&(aux.fileName_Part2[i]!= -1)) {
        out[index++] = aux.fileName_Part2[i];
      }
    }
    for (int i = 0; i < 4; i++) {
      if ((aux.fileName_Part3[i]!= 0)&&(aux.fileName_Part3[i]!= -1)) {
        out[index++] = aux.fileName_Part3[i];
      }
    }
  }else{
    return index;
  }

  return index;
};

char * readfilenameFAT(int fd, int offset, char * out){
char aux;
char espacio = 0;
int index = 0;

if (readFileType(fd, offset) == 0x0f) {
  readLongName(fd, offset, out, 0);
  return out;
}

lseek(fd, offset, SEEK_SET);
for (int i = 0; i < 11; i++) {
  read(fd, &aux, 1);
  if((aux == 32)||(aux == 0)){
    if (espacio == 0) {
      espacio = 1;
      if (out[index-1] == 'h') {
        char temp = out[index-1];
        out[index-1] = '.';
        out[index] = temp;
      }else{
        out[index] = '.';
        index++;
      }
    }
  }else{
    //printf("%c -- %d\n", aux, aux);
    if ((aux >= 65) && (aux <= 90)){
      out[index] = (aux+32);
    }else{
      out[index] = aux;
    }
    index++;
  }
}

return out;
}


/*
* Reads root entries
*
* Parameters:
*   · fd: file descriptor from which to read
*
* Returns:
*   · short of root entries
*/
short readRootEntries(int fd){
short aux;
//Obtenim BPB_BytsPerSec
lseek(fd, 17, SEEK_SET);
read(fd, &aux, 2);

return aux;
}

/*
* Reads file type
*
* Parameters:
*   · fd: file descriptor from which to read
*
* Returns:
*   · char of file type
*/
char readFileType(int fd, int offset){
char aux;
//Obtenim BPB_BytsPerSec
lseek(fd, offset+11, SEEK_SET);
read(fd, &aux, 1);

return aux;
}



/*
* Reads dir first cluster
*
* Parameters:
*   · fd: file descriptor from which to read
*
* Returns:
*   · short dir first cluster
*/
short readDirCluster(int fd, int offset){
short aux;
lseek(fd, offset+26, SEEK_SET);
read(fd, &aux, 2);

return aux;
}
