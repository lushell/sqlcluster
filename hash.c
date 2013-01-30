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

/* data node */
typedef struct _NODE
{
	char *key;
	char *data;
	struct _NODE *next;
} node;

#define hash_size	1024

/* key value */
typedef struct _HASH_TABLE
{
	node* value[hash_size];			/* data */
} hash_table;

/* Create hash table */
hash_table *create_hash_table()
{
	hash_table *table = 
		(hash_table *)malloc(sizeof(hash_table));
	memset(table, 0, sizeof(hash_table));
	return table;
}

/* Hash */
unsigned int simple_hash(void *src)
{
	if (src == NULL)
		return -1;

	char *str = (char *)src;
	int length = strlen(str);

	int i;
	unsigned int hashres = 0;
	unsigned int res = 0;
	unsigned short *s;
	s = (unsigned short *)str;

	for (i = 0; i < length; i++) 
	{
		res ^= s[i]<<(i&0x0f);
		hashres += res;
	}
	return hashres%hash_size;
}
