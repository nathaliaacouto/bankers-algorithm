all: banker
CC=gcc

banker: nvc.o 
	gcc -o banker nvc.o 

.PHONY: clean run

run: 
	./banker

clean: 
	rm -rf banker nvc.o 