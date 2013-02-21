objects = hash.o hiredis.o parse.o lex.yy.o proc_main.o mutthread.o listener.o net.o main.o sort.o
wall=-Wall
opt=-O3
lib=-lpthread -lhiredis
bin=cluster
depend = -I./include -L./lib

all:$(objects)
	gcc $(wall) $(opt) $(objects) \
	$(depend) $(lib) -g -o $(bin)
	cd heartbeat && make
	cd sqlclient && make
	cd chash && make
lex.yy.o:lex.yy.c
lex.yy.c:parse.yy
	flex   parse.yy
redis.o:redis.c redis.h libredis.h
	cc -c -o redis.o redis.c $(depend)

.PHONY:clean

clean:
	rm -f $(objects) $(bin)
	rm -f lex.yy.c
	cd heartbeat && make clean
	cd sqlclient && make clean
	cd chash && make clean
