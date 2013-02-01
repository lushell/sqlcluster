/* Copyright (c) 2000, 2011, tangchao@360buy.com and/or its affiliates. 
						All rights reserved.

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
#include <sys/types.h>
#include <string.h>
#include <pthread.h>
#include "global.h"
#include "proc_main.h"

void *do_create_thread(void *agc)
{
	int sockfd  = *((int *)agc);
#ifdef debug
	printf("sockfd = %d, agc = %d\n", sockfd, *(int *)agc);
#endif
	if(proc_main(sockfd))
	{
		printf("proc_main(): excute unsuccessful.\n");
	}
	pthread_exit(NULL);
}

int thread_incr = -1;
void create_thread(int fd_sock)
{
    pthread_t pt[1023];
	int res;
	thread_incr++;
	int fd = fd_sock;
    res = pthread_create(&pt[thread_incr], NULL, 
							do_create_thread, &fd);
    if(res)
    { 
        printf("Create thread failed\n");
		exit(-1);
    }
#ifdef debug
	printf("Create thread[%d] success.\n", thread_incr);
#endif
	return ;
}
