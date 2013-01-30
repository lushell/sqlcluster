objects=sqlclient.o redis.o
bin=sqlclient redis
sqlclient:$(objects)
	gcc -Wall -O3 sqlclient.o -o sqlclient
	gcc -Wall -O3 -I../include -L../lib -lpthread -lhiredis redis.o -o redis
sqlclient.o:
redis.o:

.PHONY:clean
clean:
	rm -f $(objects) $(bin)
