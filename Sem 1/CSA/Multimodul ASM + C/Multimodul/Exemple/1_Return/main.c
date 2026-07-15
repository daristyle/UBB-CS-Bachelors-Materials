#include <stdio.h>

// declarata in asamblare
int return_10();

// main entry point
int main()
{
    int res = return_10();
	printf("Programul returneaza %d !", res);
    
	return 0;
}
