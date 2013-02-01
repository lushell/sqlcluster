/* Copyright (c) 2000, 2011, tangchao@360buy.com and/or its affiliates. All rights reserved.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; version 2 of the License.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., Beijing China - 2013.1.24 */
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <fcntl.h>
#include "global.h"
#include "mutthread.h"

#define QUEUE_LENGTH	1023
int client_socket[QUEUE_LENGTH];
int connections = -1;

void create_listener()
{
/*
	pid_t listener_pid_t = fork();
	if(listener_pid_t < 0)
	{
		printf("[LSNCTL]:create listener failed\n");
		exit(-1);
	}

	if(listener_pid_t > 0 )
	{
		printf("[LSNCTL]:create listener successfull. "
				"process id is %d.\n", listener_pid_t);
	}
*/
	pid_t listener_pid_t = 0;
	int ret, i;
	if(listener_pid_t == 0)
	{
		struct sockaddr_in client;
		int clientSock;
		int client_len = sizeof(client);

		int sock, new_sock, maxsock;
		maxsock = ip_sock;
/* Init fd set */
	    fd_set readfds;
	    FD_ZERO(&readfds);
	    FD_SET(ip_sock, &readfds);
		for(i = 0; i < QUEUE_LENGTH; i++)
		{
			if(FD_ISSET(client_socket[i], &readfds))
			{
				FD_SET(client_socket[i], &readfds);
			}
		}

		while(1)
		{
			ret = select(maxsock + 1, &readfds, 0, 0, 0);
	        if(ret < 0) 
	        { 
	        	perror("select()");
				break;
	        } 
			if(FD_ISSET(ip_sock, &readfds))
			{
				if((new_sock = accept(ip_sock, (struct sockaddr *)&client,
										(socklen_t *)&client_len)) <= 0)
				{
					perror("accept()");
					continue;
				}
				if(connections < QUEUE_LENGTH)
				{
					connections++;
					client_socket[connections] = new_sock;
#ifdef debug
					printf("New client_socket[%d]=%d %s:%d, new_sock = %d.\n", connections, 
												client_socket[connections], 
												inet_ntoa(client.sin_addr), 
												ntohs(client.sin_port), new_sock);
#endif
				}
				if(new_sock > maxsock)
				{
					maxsock = new_sock;
					create_thread(client_socket[connections]);
				}
				else
				{
					close(new_sock);
				}
			}
		}
/* Close fd */
		for(i = 0; i < QUEUE_LENGTH; i++)
		{
			if(client_socket[i] != 0)
			{
				close(client_socket[i]);
			}
		}
	}
    return ;
}
