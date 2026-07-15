#include <stdio.h>

// definita in asamblare
int sum(int, int);

int main()
{
	int res = sum(2, 3);
	printf("Suma: %d\n", res);
    
	return 0;
}
