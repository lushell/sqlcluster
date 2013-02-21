#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <hiredis.h>
#include "global.h"

redisContext *context;
redisReply *reply;

/* Create connection for redis */
int 
create_redis_connect()
{
    struct timeval timeout = {1, 500000}; // 1.5 seconds
        context = 
            redisConnectWithTimeout((char *)redis_addr, 
                                    redis_port, timeout);
    if (context->err) 
    {   
        printf("Could not connect to Redis at ");
        printf("%s:%d: %s\n", redis_addr, redis_port,context->errstr);
        redisFree(context);
        context = NULL;
		return -1;
    }   
#ifdef debug
	else
	{
		printf("Redis connect ok.\n");
	}
#endif

#ifdef redis_auth
	if(redis_auth == NULL)
	{
#ifdef debug
		printf("redis auth password is null.\n");
#endif
		return 0;
	}
    reply = redisCommand(context,"AUTH %s", redis_auth);
    if (reply == NULL) 
    {   
#ifdef debug
		printf("Redis auth failed!!\n");
#endif
		return -1;
    }   
    freeReplyObject(reply);
#endif

	return 0;
}

/* Call it before close server */
void 
close_redis_connect()
{
	redisFree(context);
	context = NULL;
}

/* Fetch next sequence size */
unsigned long long int 
sequence_incr(char *s) 
{
	char buffer[63];
	sprintf(buffer, "incr %s", s);
    reply = redisCommand(context, buffer);
	return reply->integer;
    freeReplyObject(reply);
}

/* Reset key value 
Call ok, Return value == reset_value */
unsigned long long int 
sequence_reset(
		char *s, 
		unsigned long long int reset_value) 
{
	char buffer[63];
	sprintf(buffer, "set %s %lld", s, reset_value);
    reply = redisCommand(context, buffer);
/***************** Check reply ********************/

/***************** Check reply ********************/
    freeReplyObject(reply);
	memset(buffer, 0, 63 + 1);
	sprintf(buffer, "get %s", s);
    reply = redisCommand(context, buffer);
    unsigned long long int ret = reply->integer;
    freeReplyObject(reply);
	return ret;
}

void 
mini_storage(unsigned int key, 
			char *value)
{
    reply = redisCommand(context, "set %ld %s", key, value);
#ifdef debug
	printf(" set %s, key = %ld, value = %s.\n", 
									reply->str, key, value);
#endif
	if(strcmp(reply->str, "OK"))
	{
		printf(" set %s, key = %ld, value = %s.\n", 
									reply->str, key, value);
	}
    freeReplyObject(reply);
}
