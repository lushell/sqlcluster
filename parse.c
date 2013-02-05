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

#include "global.h"
#include "hash.h"
#include "hiredis.h"

int command_parse(packet *command_packet)
{
	command cmd;
	memcpy(cmd.str, command_packet->net, net_length);
#ifdef debug
	printf("cmd.str = %s\n", cmd.str);
#endif
<<<<<<< HEAD
	return sql_parse(&cmd);
=======
//	return sql_parse(&cmd);
//	mini_storage(key, value)
	return 0;	
>>>>>>> c43e9e766be03fa9ec79c2bd3568b372730a7f34
}
