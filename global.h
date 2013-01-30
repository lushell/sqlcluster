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
} command;

typedef struct _packet
{
	int	fd;
	command *net;
	int net_error;
} packet;


#define redis_addr  "172.17.4.49"
#define redis_port  6379
#define redis_auth  "hello,kitty"
