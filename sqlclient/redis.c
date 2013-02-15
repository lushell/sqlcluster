#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <hiredis.h>

int process(char *s) 
{
	redisContext *context;
	redisReply *reply;
	char ip[] = "172.17.4.49";
	int port = 6379;
	char auth[] = "hello,kitty";

	struct timeval timeout = {1, 500000}; // 1.5 seconds
        context = redisConnectWithTimeout(ip, port, timeout);

        if (context->err) 
	{
            printf("Could not connect to Redis at ");
            printf("%s:%d: %s\n", ip, port,context->errstr);
            redisFree(context);
            context = NULL;
            exit(-1);
        }

	reply = redisCommand(context,"AUTH %s", auth);
	if (reply == NULL) 
	{
        	exit(1);
	}
	freeReplyObject(reply);

	char buffer[31];
	sprintf(buffer, "incr %s", s);
	printf("buffer is %s\n", buffer);
	int i, max = 1000000;
	for(i = 0; i < max; i++)
	{
        	reply = redisCommand(context, buffer);
		if(i == 1)
		{
			printf("[%s] start id is %lld\n", buffer, reply->integer);
		}
		if( i == (max -1))
		{
			printf("[%s] stop id is %lld\n", buffer, reply->integer);
		}
       	 	freeReplyObject(reply);
	}
	return 0;
}

void *test(void *agc)
{
	char *tid = (char *)agc;
	process(tid);
	pthread_exit(NULL);
}


int main(void)
{
    int i = 0;
    char tt[][10] = {"aaaa","bbbb","cccc","dddd","eeee","ffff","gggg","hhhh",
			"select","insert","update","delete","create", "mysql",
			"oracle", "shell", "tangchao", "name", "oce", "shift",
			"okay", "hello", "kitty", "china", "360buy", "www", "com",
			"linux", "unix"};
	pthread_mutex_t mutex;
    pthread_mutex_init( &mutex, NULL);
    pthread_t thd[50];
    int res, max_thread=20;
    printf("create thread start.\n");
    for(i = 0; i < max_thread; i++)
    {   
        res = pthread_create(&thd[i], NULL, &test, tt[i]);
   		if(res)
	{ 
        	printf("thread create failed.\n");
	    } 
    } 
    printf("exit i = %d\n", i); 
    for(i-- ; i > 0; i--)
    { 
   	printf("%d---------------------------------%d\n",i, i); 
        pthread_join(thd[i], NULL);
    } 
    return 0;
}
