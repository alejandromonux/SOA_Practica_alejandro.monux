
#ifndef EXT2_INFO
#define EXT2_INFO

#include "../tools/utils.h"

#define EXT2_ID 61267
#define EXT2_OFFSET 1024

int printExtInfo(int fd);
/* FILETYPE */
int readFileTypeExt(int fd);
/* INODE INFO */
int readBG_INODE_TABLE_Ext(int fd);
int readInodeSizeExt(int fd);
int readFirstInodeExt(int fd);
int readInodeGroups(int fd);
int readInodeCount(int fd);
int readFreeInodes(int fd);
/* BLOCK INFO */
unsigned int readBlockSize(int fd);
int readReservedBlocks(int fd);
int readFreeBlocks(int fd);
int readTotalBlocks(int fd);
int readBlocksGroup(int fd);
int readFragsGroup(int fd);
int readFirstBlock(int fd);
int* read_i_block(int fd, int offset, int * out);
/* DIRECTORY INFO */
char * llegirNomArxiu(int fd, int offset, char * out);
short read_rec_len(int fd, int offset);
int llegirFileSize(int fd, int offset);
char llegirFileType(int fd, int offset);
int llegirInode(int fd, int offset);
/*  VOLUME INFO */
char * readBlockName(int fd, char* container);
char * readLastMounted(int fd, char* container);
char * readLastWritten(int fd, char* container);
char * readLastCheck(int fd, char* container);
#endif
