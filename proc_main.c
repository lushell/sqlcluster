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

#include "global.h"
#include "parse.h"

int proc_main(packet *net)
{
	packet *pkt = net;
    pkt->net = malloc(sizeof(char) * net_length);
	for(;;)
	{
		memset(pkt->net, 0, net_length);
		pkt->net_error = read(pkt->fd, pkt->net, net_length);
    	if(pkt->net_error > 0) // && errno != ESPIPE)	/* ESPIPE 29, wait fix */
		{
#ifdef debug
			printf("Net length = %d, sockfd = %d, buffer = %s\n", 
										pkt->net_error, pkt->fd, pkt->net);
#endif
			if(command_parse(pkt))
			{			/* Parse command */
				return -1;
			}
		}
/* Eerror */
/*
#ifdef debug
		else if(pkt->net_error == -1)
		{
			perror("read()");
			printf("Net error, errno is %d.\n", errno);  
		}
#endif
*/
/* By peer */
		else if(pkt->net_error == 0)
		{
#ifdef debug
			printf("Connection closed.\n");
#endif
			return close(pkt->fd);		/* Close current connection */
		}
	}
	return close(pkt->fd);
}
