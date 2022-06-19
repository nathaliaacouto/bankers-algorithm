all: banker
CC=gcc
CFLAGS=-I.

banker: nvc.o errors.o functions.o
	gcc nvc.o errors.o functions.o -o banker

errors.o: errors.c errors.h
	gcc -c errors.c -o errors.o

functions.o: functions.c functions.h
	gcc -c functions.c -o functions.o

nvc.o: nvc.c functions.h errors.h
	gcc -c nvc.c -o nvc.o

.PHONY: clean run

run: 
	./banker

clean: 
	rm -rf .o~ banker
	rm -rf .o~ errors.o
	rm -rf .o~ functions.o
	rm -rf .o~ nvc.o