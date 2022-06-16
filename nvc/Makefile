all: banker
CC=gcc
CFLAGS=-I.

banker: nvc.o errors.o functions.o
	gcc -o banker nvc.o errors.o functions.o

.PHONY: clean run

run: 
	./banker

clean: 
	rm -rf banker nvc.o errors.o functions.o