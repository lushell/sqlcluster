obj = main.o md5hash.o rbtree.o
link=-lcrypto
opt=-O3
main:$(obj) $(link)
	gcc -Wall $(opt) $(link) $(obj) -o main
.PHYON:clean
clean:
	rm -f $(obj) main
