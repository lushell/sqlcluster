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
#include <string.h>
#include <math.h>
#define buf_length 1023

/* MD5 hash 
Used openssl MD5()

typedef struct MD5state_st
        {   
        MD5_LONG A,B,C,D;
        MD5_LONG Nl,Nh;
        MD5_LONG data[MD5_LBLOCK];
        unsigned int num;
        } MD5_CTX;

#ifdef OPENSSL_FIPS
int private_MD5_Init(MD5_CTX *c);
#endif
int MD5_Init(MD5_CTX *c);
int MD5_Update(MD5_CTX *c, const void *data, size_t len);
int MD5_Final(unsigned char *md, MD5_CTX *c);
unsigned char *MD5(const unsigned char *d, size_t n, unsigned char *md);
void MD5_Transform(MD5_CTX *c, const unsigned char *b);
*/
#include <openssl/md5.h>

/* MD5hash range 0 ~ 0xffffffff. */
unsigned long md5hash(void *data)
{
	if(data == NULL)
	{
		return -1;
	}
/* Unsafe if your data > 1K  */
	unsigned char buf[buf_length], *str = (unsigned char *)data;
	memset(buf, 0, buf_length + 1);
	int i;
	for(i = 0; i < buf_length; i++)
	{
		if(str[i] == '\0') 
		{
			buf[i] = '\0';
			break;
		}
		buf[i] = str[i];
	}
	unsigned char md[16];
	i = strlen((unsigned char *)buf);
	MD5(buf, i, md);
/* for debug, printf every element 
	for(i = 0; i < 16; i++)
	{
		printf("md[%d] = %c\n", i, md[i]);
	}
*/
	int a = md[0] + md[1] + md[2] + md[3];
	int b = md[4] + md[5] + md[6] + md[7];
	int c = md[8] + md[9] + md[10] + md[11];
	int d = md[12] + md[13] + md[14] + md[15];
	unsigned long hash = 0;
	hash += ((long)(a & 0xff) << 24)
		| ((long)(b & 0xff) << 16)
		| ((long)(c & 0xff) << 8)	
		| ((long)(d & 0xff));
	return hash;
}
