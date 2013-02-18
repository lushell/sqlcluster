/* author: tangchao@360buy.com */

#include <stdio.h>
#include <string.h>
#include <math.h>
#define buf_length 1023

/* MD5 hash */
#include <openssl/md5.h>
/*
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

/*
	MD5hash range 0 ~ 0xffffffff.
	Return -1 hash failed.
*/
long md5hash(void *data)
{
	if(data == NULL)
	{
		return -1;
	}
	
/* Unsafe if your data > 1K  */
	int str_len = strlen((char *)data);
	unsigned char buf[buf_length], *str = (char *)data;
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
	MD5(buf, strlen(buf), md);
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
	long hash = 0;
	hash += ((long)(a & 0xff) << 24)
		| ((long)(b & 0xff) << 16)
		| ((long)(c & 0xff) << 8)	
		| ((long)(d & 0xff));
	return hash;
}
