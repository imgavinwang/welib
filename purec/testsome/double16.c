#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

int main()
{
	int a = 15;
	int b = 0;
	if(a & 0x0F != 0) {
		b = (a & 0xF0 + 16);
	}
	printf("%d\n", b);

	char str[]="hello";
	char *p = str;
	void *t = malloc(100);
	int i;
	printf("%ld %ld %ld %ld\n", sizeof(str), sizeof(p), sizeof(i), sizeof(t));
}
