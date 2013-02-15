#include <stdio.h>
#include <assert.h>
#include <net/ethernet.h>
#include <netinet/ip.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <sys/errno.h>
#include <net/if.h>
#include <net/if_arp.h>
#include <net/ethernet.h>
#include <sys/ioctl.h>
#include <ctype.h>
#include <string.h>

#define debug

void my_help()
{
	printf("usage: sqlclient -h127.0.0.1 -p13306\n"
		"-h connect addr.\n"
		 "-p connect tcp port\n");
}

void welcome()
{
	printf("Welcome to sqlcluster, shell@Copyleft.\n"
		"Author, tangchao@360buy.com.\n"
		"-----------------------------------------\n");
	
}

int main(int argc, char *argv[])
{
	int test_port = 13608;
	char test_addr[14] = "127.0.0.1";
	struct timeval timeout = {600, 500000};

/* Input Check */	
	if (argv[1] == NULL) 
	{
		goto start;
	}

/* Parse command line */
	int opt;
	while( 1 )
	{
		opt = getopt(argc, argv, "h:p:");
		if(opt == EOF) break;
		switch(opt)
		{
			case 'h':
				memset(test_addr, 0, 15);	
				memcpy(test_addr, optarg, 15);
				break;
			case 'p':
				test_port = atoi(optarg);
				break;
			case '?':
				printf("Unknown options\n");
				my_help();
				break;
			case ':':
				printf("Format error\n");
				my_help();
				break;
			default:
				goto err;
			
		}
	}

	start:
	printf("");

	int sock;
	if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("socket()");
		return -1; 		
	}
	int reuse = 1;
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR,
				(char *)&reuse,sizeof(reuse));

	struct sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(test_port);
	serverAddr.sin_addr.s_addr = inet_addr(test_addr);
	if(connect(sock, (struct sockaddr *)&serverAddr,
					sizeof(serverAddr)) < 0)
	{
		perror("connect()");
		exit(1);
	}	

	char *buffer;
	buffer = malloc(256);
	ssize_t send_length;
	int buffer_size;

    fd_set writefds;
    FD_ZERO(&writefds);
	FD_SET(sock, &writefds);
	int ret;

	welcome();
	while(1)
	{
		printf("COMMAND>");
		memset(buffer, 0, 256);

		fgets(buffer, 256, stdin);
		buffer_size = strlen(buffer);
		buffer[buffer_size - 1] = '\0';

		if(strcmp(buffer, "quit") == 0) 
		{
			close(sock);
			return 0;
		}
		if(strcmp(buffer, "help") == 0)
		{
			my_help();
			continue;
		}
		printf("buffer is %s, size is %d\n", buffer, buffer_size - 1);

        ret = select(sock + 1, NULL, &writefds, NULL, &timeout);
		if(ret == -1)
		{
			perror("select()");
			return -1;
		}
		if(ret > 0 && buffer[0] != '\n')
		{
			send_length = send(sock, buffer, 
						(size_t)strlen(buffer), 0);
#ifdef debug
//			perror("send()");
			printf("send data size %d byte.\n", 
						send_length);
#endif
		}
		else
		{
			printf("Connections timeout.\n");
			close(sock);
			break;
		}
	}
	close(sock);
	return 0;

	err:
		printf("error\n");
		my_help();
		return -1;
}
