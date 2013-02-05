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

#include <sys/types.h>
#include <sys/socket.h>
#include <time.h>
#include <string.h>
#include <netinet/in.h>

/* Global */

/* Thread mutex , cond */
pthread_mutex_t connections_mutex;

int init_kernel()
{
	pthread_mutex_init(&connections_mutex, NULL);
	create_redis_connect();			/* Redis storage server */
	return 0;
}

void close_server()
{ 
	pthread_mutex_destroy(&connections_mutex);
	close_redis_connect();
}

int main(int argc, char *argv[])
{
	open_listen_port();
	init_kernel();
	create_listener();
	close_server();
	return 0;
}
