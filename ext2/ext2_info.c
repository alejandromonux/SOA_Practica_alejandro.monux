#include "./ext2_info.h"

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
  //read(fd, &aux, 4);
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

  //Anem al inode table
  lseek(fd, 2048 + (readBG_INODE_TABLE_Ext(fd) - 2)*readBlockSize(fd) + (aux-1)*readInodeSizeExt(fd) + 4, SEEK_SET);
  read(fd, &aux, 4);


  return aux;
}

/**
*Function to read EXT2 current file filetype
*
*parameters:
* ·fd = File descriptor of file
*
*
*returns:
*  char of filetype
*
**/
char llegirFileType(int fd, int offset){
  char aux;

  //Llegim el tipus on pertany
  lseek(fd, offset+7, SEEK_SET);
  read(fd, &aux, 1);

  return aux;
}

/**
*Function to read EXT2 current file inode location
*
*parameters:
* ·fd = File descriptor of file
*
*
*returns:
*  unsigned int of inode adress
*
*
*/
int llegirInode(int fd, int offset){
  int aux;

  //Llegim el inode on pertany
  lseek(fd, offset, SEEK_SET);
  read(fd, &aux, 4);
	//Operar per mirar a quin grup es (Dividir entre inodes per grup)
	//Anar al inodeTable del grup
  int grup = (aux-1)/readInodeGroups(fd);
  if(grup == 0){
    aux=1024 + (readBG_INODE_TABLE_Ext(fd) - 1)*readBlockSize(fd) + (aux-1)*readInodeSizeExt(fd);
  }else{
    //Mirar de restar-li a aux el num de block * size de block per que si block es 1024 i aux es 1028 doncs que aux passi a ser 4 :3
    aux -= grup*readInodeGroups(fd);
    aux=1024 + (readBG_INODE_TABLE_Ext(fd) - 1)*readBlockSize(fd) + (aux-1)*readInodeSizeExt(fd) +  grup*(readBlockSize(fd)*readBlocksGroup(fd));
  }

  int offset_Al_Inode_Table = aux;
  /*
  int i_block[15];
  read_i_block(fd, offset, i_block);
  grup = (i_block[0] -1)/readBlocksGroup(fd);
  int block = (i_block[0] -1) - (grup*readBlocksGroup(fd));
  int directory_offset = 1024 + grup*readBlockSize(fd)*readBlocksGroup(fd) + block*readBlockSize(fd);
  return directory_offset;*/
  return offset_Al_Inode_Table;
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
