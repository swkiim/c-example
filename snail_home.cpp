#include <stdio.h>

int main()
{
	int a[5][5] = {0};
	int n = 0;
	int s = 1;
	int i = 1;
	int j = 0;
	int k = 5;
	do
	{
		for(int p = 0; p < k; p++)
		{
			n++;
			j = j + s;
			a[i - 1][j - 1] = n;
		}
		k = k - 1;
		for(int r = 0; r < k; r++)
		{
			n = n + 1;
			i = i + s;
			a[i - 1][j - 1] = n;
		}
		s = s * (-1);
	}
	while(k > 0);
	for(i = 0; i < 5; i++)
	{
		for(j = 0; j < 5; j++)
		{
			printf("%4d", a[i][j]);
		}
		printf("\n");
	}
	return 0;
}
