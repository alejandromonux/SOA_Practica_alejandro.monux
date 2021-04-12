#include "./ext2_info.h"


/**
*Function to determine if FS is Ext2 or not
*
*parameters:
* ·fd = File descriptor of file
*
*
*returns:
*  1 if EXT2, 0 if not
*
**/
int readFileTypeExt(int fd){
  unsigned short aux;

  lseek(fd, EXT2_OFFSET+56, SEEK_SET);
  read(fd, &aux, 2);

  if(aux == EXT2_ID){
    return 1;
  }else{
    return 0;
  }
}
