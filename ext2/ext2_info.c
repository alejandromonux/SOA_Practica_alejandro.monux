#include "./ext2_info.h"

/* FILETYPE */

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

/* INODE INFO */

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
  int aux;

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
  int aux;

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
  int aux;

  lseek(fd, EXT2_OFFSET+16, SEEK_SET);
  read(fd, &aux, 4);

  return aux;
}

/* BLOCK INFO */

/**
*Function to read EXT2 Block Size
*
*parameters:
* ·fd = File descriptor of file
*
*
*returns:
*  Block Size
*
**/
unsigned int readBlockSize(int fd){
  unsigned int aux;

  lseek(fd, EXT2_OFFSET+24, SEEK_SET);
  read(fd, &aux, 4);

  return 1024 << aux ;
}

/**
*Function to read EXT2 number of reserved blocks.
*
*parameters:
* ·fd = File descriptor of file.
*
*
*returns:
* number of reserved blocks.
*
**/
int readReservedBlocks(int fd){
  unsigned int aux;

  lseek(fd, EXT2_OFFSET+8, SEEK_SET);
  read(fd, &aux, 4);

  return aux;
}

/**
*Function to read EXT2 number of free blocks.
*
*parameters:
* ·fd = File descriptor of file.
*
*
*returns:
* number of free blocks.
*
**/
int readFreeBlocks(int fd){
  unsigned int aux;

  lseek(fd, EXT2_OFFSET+12, SEEK_SET);
  read(fd, &aux, 4);

  return aux;
}

/**
*Function to read EXT2 number of free blocks.
*
*parameters:
* ·fd = File descriptor of file.
*
*
*returns:
* number of free blocks.
*
**/
int readTotalBlocks(int fd){
  unsigned int aux;

  lseek(fd, EXT2_OFFSET+4, SEEK_SET);
  read(fd, &aux, 4);

  return aux;
}

/**
*Function to read EXT2 blocks per group.
*
*parameters:
* ·fd = File descriptor of file.
*
*
*returns:
* blocks per group.
*
**/
int readBlocksGroup(int fd){
  unsigned int aux;

  lseek(fd, EXT2_OFFSET+32, SEEK_SET);
  read(fd, &aux, 4);

  return aux;
}

/**
*Function to read EXT2 fragments per group.
*
*parameters:
* ·fd = File descriptor of file.
*
*
*returns:
* fragments per group.
*
**/
int readFragsGroup(int fd){
  unsigned int aux;

  lseek(fd, EXT2_OFFSET+36, SEEK_SET);
  read(fd, &aux, 4);

  return aux;
}


/**
*Function to read EXT2 ID of first data block.
*
*parameters:
* ·fd = File descriptor of file.
*
*
*returns:
* ID of first data block.
*
**/
int readFirstBlock(int fd){
  unsigned int aux;

  lseek(fd, EXT2_OFFSET+20, SEEK_SET);
  read(fd, &aux, 4);

  return aux;
}
