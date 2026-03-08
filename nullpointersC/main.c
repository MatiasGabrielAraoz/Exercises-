
#include <stdio.h>
int main(){
	int *p = NULL;

	printf("%p", p);
	*p = 69;
	return 0;
}
