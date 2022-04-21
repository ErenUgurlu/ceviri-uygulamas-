CLASSDIR = ../B181210082
INCLUDE = -I$(CLASSDIR)/include
LIBS = $(CLASSDIR)/lib/libfdr.a
CC = gcc

all: derle 

clean: 
	rm -f bin/*
	
derle: src/ceviri.c $(LIBS)
	$(CC) $(INCLUDE) -o bin/ceviri src/ceviri.c $(LIBS)
