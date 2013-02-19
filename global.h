#include <sys/errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
//#define debug

#define TCP 6
#define backlog 1023
#define lsnport 13608
#define max_connections 1023

/* socket descriptor */
int ip_sock;

/* Structure kernel data */
#define net_length  0xffff /* 64K, Compatible Text type. */
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

/* Table structure definition */
#define column_length 31	/* Db name add table name <= 32 */
#define max_clomun 127	/* Max columns */
typedef struct _tbdef
{
    char cname[column_length];
    short sequence;
} tbdef;

typedef struct _table
{
	tbdef *def;
	struct table *link;
} table;
