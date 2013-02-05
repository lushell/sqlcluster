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
#include <stdlib.h>
#include <unistd.h>

table *create_new_table(tbdef *create_str)
{
	table *new_table, *next_link, *head;
	tbdef *str = (tbdef *)create_str;
	if(str[0] == NULL)
	{
		printf("Create table failed.\n");
		exit(1);
	}
	if(head = (table *)malloc(sizeof(table)) == NULL)
	{
		perror("malloc");
		break;
	}
	head->link = NULL;
	head->def = NULL;
	int i;
	for(i = 0; i < max_column; i++)
	{
		if(str[i] == NULL)
		{
			break;
		}
/* Store definitions */
		
	}
	return new_table;
}
