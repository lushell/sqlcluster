OBJECT=ifname.o master.o main.o slave.o
GCC_OPT=-O3
GCC_WALL=-Wall
hbt:$(OBJECT)
	gcc $(GCC_OPT) $(GCC_WALL) $(OBJECT) -o hbt
ifname.o:global.h
master.o:global.h
main.o:global.h 
slave.o:global.h

.PHONY:clean
clean:
	rm $(OBJECT) hbt 
