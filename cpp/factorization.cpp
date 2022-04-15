#include <stdio.h>
#define LEN 40

int main()
{
	int a[LEN] = {0, };
	int cinput = 0;
	int z = 0;
	do
	{
		printf("\nninput number?");
		scanf("%d", &cinput);
		printf(" input = %d \n", cinput);
		int d = 0;
		for (int c = 1; c <= cinput; c++)
		{
			if((cinput % c) == 0)
			{
				a[d++] = c;
			}
		}
		printf("s0 yaksu count = %d \n\n", d);
		int i = 0;
		do
		{
			printf("%3d", a[i++]);
		}
		while(d > i);
		z++;
	}
	while(z == 1);
}
