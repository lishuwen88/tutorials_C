#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main(){
	if (fork()==0){
		printf("I am Child.\n");
	} else {
		printf("I am Parent. %d\n", getpid());
	}
}
