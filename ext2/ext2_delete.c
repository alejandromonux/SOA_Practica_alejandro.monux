#include "./ext2_delete.h"

void borrarArxiuExt(int fd, int counter, int directory_offset, int inodeTableOffset){
  DEntryExt entrada;
  short rec_len_aux = 0;
  int i_size;
  int diff_rec_len=0;
  char * padding;
  int bitmapOffset;
  int offsetBaseArxiu = counter;

  lseek(fd, counter+4, SEEK_SET);
  read(fd, &rec_len_aux, 2);

  //EDITAR LA INODE TABLE, el size
  lseek(fd, inodeTableOffset+4, SEEK_SET);
  read(fd, &i_size, 4);
  i_size -= rec_len_aux;
  lseek(fd, inodeTableOffset+4, SEEK_SET);
  write(fd, &i_size, 4);


  //EDITAR LA LLISTA DE DIRECTORIS
  lseek(fd, directory_offset, SEEK_SET);
  entrada.name = (char *) malloc(sizeof(char)*1);
  counter += rec_len_aux;

  do{
    //Leer INFO
    lseek(fd, counter, SEEK_SET);
    read(fd, &entrada, 8);
    free(entrada.name);
    entrada.name = (char *) malloc(sizeof(char)*entrada.name_len);
    padding = (char *) malloc(sizeof(char) * (rec_len_aux - (8 + entrada.name_len)));

    memset(entrada.name, '\0', entrada.name_len);
    read(fd, entrada.name, entrada.name_len);
    read(fd,padding,rec_len_aux - (8 + entrada.name_len));


    //Escribir en el anterior
    printf("NOM ARXIU: %s\n", entrada.name);
    printf("NAME: %d\n", entrada.name_len);
    printf("REC: %d\n", entrada.rec_len);
    lseek(fd, counter-rec_len_aux+diff_rec_len, SEEK_SET);

    write(fd, &entrada.inode, 4);
    write(fd, &entrada.rec_len, 2);
    write(fd, &entrada.name_len, 1);
    write(fd, &entrada.file_type, 1);
    write(fd, entrada.name, sizeof(char) * entrada.name_len);
    write(fd, padding, rec_len_aux - (8 + entrada.name_len));

    diff_rec_len = (entrada.rec_len-rec_len_aux);

    rec_len_aux = entrada.rec_len;
    counter += rec_len_aux;
  }while(counter < (directory_offset + readInodeSizeExt(fd)));


  free(entrada.name);

  //Esto me lleva al bitmap
  lseek(fd, EXT2_OFFSET*2+4, SEEK_SET);
  read(fd,&bitmapOffset,4);
  bitmapOffset= inodeTableOffset - (readBG_INODE_TABLE_Ext(fd) - 1)*readBlockSize(fd) + (bitmapOffset-1)*readBlockSize(fd);

  //Desactivar el inode en cuestión.
  char * inodeBitmap = (char*) malloc(readBlockSize(fd));
  lseek(fd, bitmapOffset, SEEK_SET);
  read(fd, inodeBitmap, readBlockSize(fd));

  //Llegim el inode on pertany
  int inode;
  lseek(fd, offsetBaseArxiu, SEEK_SET);
  read(fd, &inode, 4);
  //Operar per mirar a quin grup es (Dividir entre inodes per grup)
  //Anar al inodeTable del grup
  int grup = (inode-1)/readInodeGroups(fd);
  if(grup != 0){
    inode -= grup*readInodeGroups(fd);
  }
  //Canviem a 0 el bit del bitmap del inode
  *inodeBitmap &= ~(1 << inode);


  lseek(fd, bitmapOffset, SEEK_SET);
  write(fd, inodeBitmap, readBlockSize(fd));
  free(inodeBitmap);
}
