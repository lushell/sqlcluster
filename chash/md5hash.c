#include <stdio.h>
#include <string.h>
#include <math.h>

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
	MD5hash range 0 ~ 4*0xffffffff.
	Return -1 hash failed.
*/
long md5hash(void *data)
{
	if(data == NULL)
	{
		return -1;
	}
/* 1K data */
	char buf[1024];
	sprintf(buf, "%s", (char *)data);
//	printf("%s\n", buf);
	int i;
	unsigned char md[16];
	MD5(buf, strlen(buf), md);
/* for debug, printf every element 
	for(i = 0; i < 16; i++)
	{
		printf("md[%d] = %c\n", i, md[i]);
	}
*/
	long hash = 0;
	for(i = 0; i < 4; i++)
	{
		hash += ((long)(md[i*4 + 3]&0xff) << 24)
			| ((long)(md[i*4 + 2]&0xff) << 16)
			| ((long)(md[i*4 + 1]&0xff) << 8)	
			| ((long)(md[i*4 + 0]&0xff));
	}
	return hash;
}
