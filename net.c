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

#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netinet/in.h>
#include "global.h"

void open_listen_port()
{
	if((ip_sock = socket(PF_INET, SOCK_STREAM, TCP)) == -1)
	{
		perror("socket()");
		exit(1);
	}

	struct timeval timeout = {10, 0};
	socklen_t len = sizeof(timeout);
	setsockopt(ip_sock, SOL_SOCKET, SO_SNDTIMEO, &timeout, len); 
	setsockopt(ip_sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, len); 
    int reuse = 1;
    setsockopt(ip_sock, SOL_SOCKET, SO_REUSEADDR,
                            (char *)&reuse,sizeof(reuse));
	struct sockaddr_in lsnaddr;
	lsnaddr.sin_family = AF_INET;
	lsnaddr.sin_port = htons(lsnport);
	lsnaddr.sin_addr.s_addr	= htonl(INADDR_ANY);
	if(bind(ip_sock, (struct sockaddr *)&lsnaddr, sizeof(lsnaddr)) < 0)
	{
		perror("bind()");
		exit(-1);
	}
	if(listen(ip_sock, backlog))
	{
		perror("listen()");
		exit(-1);
	}
#ifdef debug
	printf("[OPEN TCP]:success. TCP port is %d.\n", lsnport);
#endif
	return ;
}
