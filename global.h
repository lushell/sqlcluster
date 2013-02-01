#include <sys/errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#define debug

#define TCP 6
#define backlog 1023
#define lsnport 13608
#define max_connections 1023

/* socket descriptor */
int ip_sock;

/* Structure kernel data */
#define net_length  16383
typedef struct _command
{
	char str[net_length];
	int command;
	int cmd_sum;
} command;

typedef struct _packet
{
	int	fd;
	char net[net_length];
	int net_error;
} packet;

/* Connection redis server */
#define redis_addr  "127.0.0.1"
#define redis_port  6379
//#define redis_auth 
