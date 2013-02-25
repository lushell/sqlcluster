obj = main.o md5hash.o rbtree.o init.o node.o
link=-lcrypto
opt=-O3
bin=test
all:$(obj) $(link)
	gcc -g -Wall $(opt) $(link) $(obj) -o $(bin)
.PHYON:clean
clean:
	rm -f $(obj) $(bin)
