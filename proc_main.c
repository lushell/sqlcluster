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

int proc_main(int net)
{
	packet pkt;
	pkt.fd = net;
	for(;;)
	{
		memset(pkt.net, 0, net_length);
		pkt.net_error = read(pkt.fd, pkt.net, net_length);
    	if(pkt.net_error > 0) 
		{
#ifdef debug
			printf("Net length = %d, sockfd = %d, buffer = %s\n", 
									pkt.net_error, pkt.fd, pkt.net);
#endif
			if(command_parse(&pkt))
			{			/* Parse command */
				return -1;
			}
		}
		else if(pkt.net_error == 0)
		{
#ifdef debug
			printf("close socket fd %d\n", pkt.fd);
#endif
			close(pkt.fd);
		}
	}
	return 0;
}
