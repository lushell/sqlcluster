#include <stdio.h>
#include <string.h>
#include <math.h>

int main(void)
{
	char str1[1024];
	strcpy(str1, "shell");
	printf("%s\n", str1);
	char str2[] = "mystery";
	strcat(str1, str2);
	printf("%s\n", str1);
	return 0;
}
