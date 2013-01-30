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
#include <netinet/in.h>
#include <fcntl.h>
#include "global.h"
#include "mutthread.h"

int sock_array[backlog];
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
	int listener_pid_t = 0;
	if(listener_pid_t == 0)
	{
		struct sockaddr_in client;
		int clientSock;
		int client_len = sizeof(client);

	    int ret;
		int sock, new_sock;
	    fd_set readfds;
	    FD_ZERO(&readfds);
		sock = ip_sock;
	    FD_SET(ip_sock, &readfds);

	    while(1)
	    { 
/*
			ret = select(sock + 1, &readfds, 0, 0, 0);
	        if(ret == -1) 
	        { 
	        	perror("select()");
				break;
	        } 
	        if(ret > 0)
	        { 
				if(!FD_ISSET(sock, &readfds))
				{
					printf("sock %d can't reads.\n", sock);
					continue;
				}
*/
				if((new_sock = accept(sock, (struct sockaddr *)&client,
							(socklen_t *)&client_len)) == -1)
				{
					perror("accept()");
					break;
				}
#ifdef debug
				printf("Start new event!\naccept sock is %d.\nCreate new thread.\n", new_sock);
#endif
				create_thread(new_sock);
//			} 
        } 
	}
    return ;
}
