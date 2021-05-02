.PHONY : clean

OBJS		= main.o ext2_info.o utils.o FAT16_info.o ext2_find.o FAT16_find.o
SOURCE	= main.c ./ext2/ext2_info.c ./tools/utils.c ./FAT16/FAT16_info.c ./ext2/ext2_find.c ./FAT16/FAT16_find.c
HEADER	= ./ext2/ext2_info.h ./tools/utils.h ./FAT16/FAT16_info.h ./ext2/ext2_find.h ./FAT16/FAT16_find.h
OUT			= main
CC	 		= gcc
FLAGS	 	= -g -c -Wall -Wextra


all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT)
	make clean

main.o: main.c
	$(CC) $(FLAGS) main.c

utils.o: ./tools/utils.c
	$(CC) $(FLAGS) ./tools/utils.c


ext2_find.o: ./ext2/ext2_find.c
	$(CC) $(FLAGS) ./ext2/ext2_find.c


ext2_info.o: ./ext2/ext2_info.c
	$(CC) $(FLAGS) ./ext2/ext2_info.c

FAT16_info.o: ./FAT16/FAT16_info.c
	$(CC) $(FLAGS) ./FAT16/FAT16_info.c

FAT16_find.o: ./FAT16/FAT16_find.c
	$(CC) $(FLAGS) ./FAT16/FAT16_find.c




clean :
	-rm $(OBJS)
