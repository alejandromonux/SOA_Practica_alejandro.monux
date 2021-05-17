#include "./ext2_find.h"

int trobarArxiuExt(int fd, const char *nomArxiu, unsigned int offset){
  int saltsFins1erInode = readInodeSizeExt(fd)*(readFirstInodeExt(fd)-1);
  int i_block[15];
  int counter;
  int trobat = 0;
  //Anar al primer inode (Inode 11).
  int inodeDir= readFirstInodeExt(fd)*readInodeSizeExt(fd);
  lseek(fd, inodeDir, SEEK_SET);

  int offset_Al_Inode_Table = 2048 + (readBG_INODE_TABLE_Ext(fd) - 2)*readBlockSize(fd) + saltsFins1erInode;
  read_i_block(fd, offset_Al_Inode_Table, i_block);

  char nom[255];
  int  directory_offset = 2048 + (i_block[0] -3)*readBlockSize(fd);

  if (offset != 0)  directory_offset = offset;
  counter = directory_offset;
  while(counter < (directory_offset + readInodeSizeExt(fd))){
    memset(nom, '\0', 255);
	short nextEntry = read_rec_len(fd, counter);

    llegirNomArxiu(fd, counter, nom);
    int filesize = llegirFileSize(fd, counter);

    if (llegirFileType(fd, counter) == 2) {
      if ((strcmp(nom, ".") != 0)&&(strcmp(nom, "..") != 0)&&(strcmp(nom,"lost+found") != 0)) {
        int inodeDest = llegirInode(fd, counter);
        trobat = trobarArxiuExt(fd, nomArxiu, inodeDest);
      }
    }else if (llegirFileType(fd,counter) == 1){
      if (strcmp(nom, nomArxiu) == 0) {
        printf("fitxer trobat. Ocupa %d\n", filesize);
        return 1;
      }
    }

    counter += nextEntry;

  }
      if ((offset == 0)&&(trobat)) {
        printf("Error. Fitxer inexistent\n");
      }
      return 0;
}
