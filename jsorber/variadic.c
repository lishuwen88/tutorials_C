#include <stdio.h>
#include <stdarg.h>

void print_ints(int num, ...){	// the ... part means i can put in any number of variables?
	va_list args;

	va_start(args,num);
	printf("starting sequence:...\n");
	for(int i=0; i<num; i++){
		int value = va_arg(args, int);
		printf("%d: %d\n", i, value);
	}
	printf("ending sequence:.\n");
	va_end(args); // not really required for gcc, clang
}

int main(){
	print_ints(4,34,135423,352,231);
	print_ints(6,9,87,65,4,3,2);
	print_ints(9,2,3,4,5,6,7,8,9,0);

	return 0;
}

