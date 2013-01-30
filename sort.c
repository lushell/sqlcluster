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

void insert_sort(int *array)
{
	int i, j, s;
	int length = sizeof(array)/sizeof(int);
	
	for(i = 0; i < length - 1; i++)
	{
		for(j = 0; j < i; j++)
		{
			if(array[i] < array[j])
			{
				s = array[i];
				array[i] = array[j];
				array[j] = s;
			}
		}
	}
#ifdef debug
	for(i = 0; i < length - 1; i++)
	{
		printf("array[%d] = %d\n", i, array[i]);
	}
#endif
	return ;
}
