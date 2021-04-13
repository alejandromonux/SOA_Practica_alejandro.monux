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


/**
*Function to read EXT2 volume inode size
*
*parameters:
* ·fd = File descriptor of file
*
*
*returns:
*  inode size
*
**/
int readInodeSizeExt(int fd){
  unsigned short aux;

  lseek(fd, EXT2_OFFSET+88, SEEK_SET);
  read(fd, &aux, 2);

  return aux;
}

/**
*Function to read EXT2 first inode
*
*parameters:
* ·fd = File descriptor of file
*
*
*returns:
*  first inode
*
**/
int readFirstInodeExt(int fd){
  unsigned int aux;

  lseek(fd, EXT2_OFFSET+84, SEEK_SET);
  read(fd, &aux, 4);

  return aux;
}


/**
*Function to read EXT2 inodes group
*
*parameters:
* ·fd = File descriptor of file
*
*
*returns:
*  inodes group
*
**/
int readInodeGroups(int fd){
  unsigned int aux;

  lseek(fd, EXT2_OFFSET+40, SEEK_SET);
  read(fd, &aux, 4);

  return aux;
}


/**
*Function to read EXT2 inode count
*
*parameters:
* ·fd = File descriptor of file
*
*
*returns:
*  inode count
*
**/
int readInodeCount(int fd){
  unsigned int aux;

  lseek(fd, EXT2_OFFSET+0, SEEK_SET);
  read(fd, &aux, 4);

  return aux;
}

/**
*Function to read EXT2 free inode count
*
*parameters:
* ·fd = File descriptor of file
*
*
*returns:
*  free inode count
*
**/
int readFreeInodes(int fd){
  unsigned int aux;

  lseek(fd, EXT2_OFFSET+16, SEEK_SET);
  read(fd, &aux, 4);

  return aux;
}
