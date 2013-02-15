/* MD5 32bit capital
*/
#include <openssl/md5.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, char *argv[]){
        char *md;
        int l = strlen(argv[1]);
        md = (char *)MD5((const unsigned char *)argv[1],l,NULL);
        int len = strlen((char *)md);
        char strmd5[1024] = {0};
		int i = 0;
        for(i=0; i<len; i++){
                sprintf(strmd5+strlen(strmd5),"%02X",md[i]&0xFF);
        }
        printf("%s\n",strmd5);
}

