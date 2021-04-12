.PHONY : clean

OBJS		= main.o ext2_info.o
SOURCE	= main.c ./ext2/ext2_info.c
HEADER	= ./ext2/ext2_info.h ./semaphore_v2.h
OUT			= main
CC	 		= gcc
FLAGS	 	= -g -c -Wall -Wextra


all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT)
	make clean

main.o: main.c
	$(CC) $(FLAGS) main.c

ext2_info.o: ./ext2/ext2_info.c
	$(CC) $(FLAGS) ./ext2/ext2_info.c

clean :
	-rm $(OBJS)
