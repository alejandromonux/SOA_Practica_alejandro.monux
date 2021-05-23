#include "./ext2/ext2_find.h"
#include "./ext2/ext2_info.h"
#include "./FAT16/FAT16_find.h"
#include "./FAT16/FAT16_info.h"





int main(int argc, char const *argv[]) {

  if (argc < 3){
    printf("No hi ha suficients arguments. El nombre actual d'arguments es: %d\n", argc);
    return 0;
  }

  int fd = open(argv[2], O_RDWR);
  if (fd < 0) {
    printf("Volum inexistent.\n");
    return -1;
  }
  if(readFileTypeExt(fd) == 1){
    printf("FILESYSTEM: EXT2\n\n");
    if(strcmp("/info", argv[1]) == 0){
      printExtInfo(fd);
    }else if (strcmp("/find", argv[1]) == 0) {
      if (argc < 4){
        printf("No hi ha suficients arguments. El nombre actual d'arguments es: %d\n", argc);
        return 0;
      }
      trobarArxiuExt(fd, argv[3],0,0);
    }else if (strcmp("/delete", argv[1]) == 0){
      if (argc < 4){
        printf("No hi ha suficients arguments. El nombre actual d'arguments es: %d\n", argc);
        return 0;
      }
      trobarArxiuExt(fd, argv[3],0,1);
    }else{
        printf("Operació no suportada.\n");
    }
  }else{
    if(isItFAT16(fd)){
        printf("FILESYSTEM: FAT16\n\n");
        if(strcmp("/info", argv[1]) == 0){
          printFAT16Info(fd);
        }else if (strcmp("/find", argv[1]) == 0) {
          if (argc < 4){
            printf("No hi ha suficients arguments. El nombre actual d'arguments es: %d\n", argc);
            return 0;
          }
          trobarArxiuFAT(fd, argv[3],0,0);
        }else if (strcmp("/delete", argv[1]) == 0){
          if (argc < 4){
            printf("No hi ha suficients arguments. El nombre actual d'arguments es: %d\n", argc);
            return 0;
          }
          trobarArxiuFAT(fd, argv[3],0,1);
        }else{
          printf("Operació no suportada.\n");
        }

    }else{
      printf("El sistema no es ni EXT2 ni FAT16\n");
    }
  }
  close(fd);
  return 0;
}
