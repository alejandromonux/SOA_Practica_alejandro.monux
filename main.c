#include "./ext2/ext2_info.h"

int main(int argc, char const *argv[]) {

  if (argc < 3){
    printf("Not enough arguments provided. Current amount of arguments is: %d", argc);
    return 0;
  }

  int fd = open(argv[2], 'r');

  if(readFileTypeExt(fd) == 1){
    printf("Sam va de puta madre socio galaxy\n");
  }else{
    printf("Sam no va tambien la verdá\n");
  }


  return 0;
}
