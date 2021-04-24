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
*Function to read EXT2 bg_inode_table
*
*parameters:
* ·fd = File descriptor of file
*
*
*returns:
*  bg_inode_table
*
**/
int readBG_INODE_TABLE_Ext(int fd){
  int aux;

  lseek(fd, EXT2_OFFSET*2+8, SEEK_SET);
  read(fd, &aux, 4);

  return aux;
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


/**
*Function to read EXT2 i_block of designated inode table.
*
*parameters:
* ·fd = File descriptor of file.
*
*
*returns:
* ID of first data block.
*
**/
int* read_i_block(int fd, int offset, int * out){
  unsigned int aux;

  lseek(fd, offset+40, SEEK_SET);
  for (int i = 0; i < 15; i++) {
    read(fd, &aux, 4);
    out[i] = aux;
  }

  return out;
}


/* DIRECTORY INFO */

/**
*Function to read CURRENT Directory entry rec_len.
*
*parameters:
* ·fd = File descriptor of file.
* · offset = offset from which to write
* · out = char * to output
*
*returns:
* name.
*
**/
short read_rec_len(int fd, int offset){
  unsigned short aux;

  lseek(fd, offset+4, SEEK_SET);
  read(fd, &aux, 2);


  return aux;
}


/**
*Function to read CURRENT file/Directory name.
*
*parameters:
* ·fd = File descriptor of file.
* · offset = offset from which to write
* · out = char * to output
*
*returns:
* name.
*
**/
char * llegirNomArxiu(int fd, int offset, char * out){
  unsigned char aux;

  lseek(fd, offset+6, SEEK_SET);
  read(fd, &aux, 1);
  lseek(fd, offset+8, SEEK_SET);
  for (int i = 0; i < aux; i++) {
    char aux2;
    read(fd, &aux2, 1);
    out[i] = aux2;
  }


  return out;
}



/**
*Function to read CURRENT file size.
*
*parameters:
* · fd = File descriptor of file.
* · offset = offset from which to write
*
*
*returns:
* name.
*
**/
int llegirFileSize(int fd, int offset){
  unsigned int aux;

  //Llegim el inode on pertany
  lseek(fd, offset, SEEK_SET);
  read(fd, &aux, 4);

  //Anem al inode
  lseek(fd, 2048 + (readBG_INODE_TABLE_Ext(fd) - 2)*readBlockSize(fd) + (aux-1)*readInodeSizeExt(fd) + 4, SEEK_SET);
  read(fd, &aux, 4);


  return aux;
}

/*  VOLUME INFO */

/**
*Function to read EXT2 Volume name
*
*parameters:
* ·fd = File descriptor of file.
*
*
*returns:
* Volume name
*
**/
char * readBlockName(int fd, char* container){


  lseek(fd, EXT2_OFFSET+120, SEEK_SET);
  read(fd, &container, 16);

  return container;
}


/**
*Function to read EXT2 Last Time Mounted
*
*parameters:
* ·fd = File descriptor of file.
*
*
*returns:
* Last Time Mounted
*
**/
char * readLastMounted(int fd, char* container){
  int aux;
  lseek(fd, EXT2_OFFSET+44, SEEK_SET);
  read(fd, &aux, 4);

  container = timestampToText(aux, container);

  return container;
}


/**
*Function to read EXT2 Last Time Written
*
*parameters:
* ·fd = File descriptor of file.
*
*
*returns:
* Last Time Written
*
**/
char * readLastWritten(int fd, char* container){
  int aux;
  lseek(fd, EXT2_OFFSET+48, SEEK_SET);
  read(fd, &aux, 4);

  container = timestampToText(aux, container);

  return container;
}

/**
*Function to read EXT2 Last Time Checked
*
*parameters:
* ·fd = File descriptor of file.
*
*
*returns:
* Last Time Checked
*
**/
char * readLastCheck(int fd, char* container){
  int aux;
  lseek(fd, EXT2_OFFSET+64, SEEK_SET);
  read(fd, &aux, 4);

  container = timestampToText(aux, container);

  return container;
}
