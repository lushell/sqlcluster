objects = hash.o hiredis.o parse.o lex.yy.o proc_main.o mutthread.o listener.o net.o main.o
wall=-Wall
opt=-O3
lib=-lpthread -lhiredis
bin=cluster
depend = -I./include -L./lib


all:$(objects)
	gcc $(wall) $(opt) $(objects) $(depend) $(lib) -g -o $(bin)
lex.yy.o:lex.yy.c
lex.yy.c:parse.yy
	flex   parse.yy
.PHONY:clean
clean:
	rm -f $(objects) $(bin)
	rm -f lex.yy.c
