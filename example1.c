#include <pthread.h>
#include <unistd.h>
#include <urcu.h>
#include <stdio.h>
#include <limits.h>

#define MAX INT_MAX

struct foo {
	int a;
	int b;
};

struct foo gl;
int done = 0;
pthread_t tid[3];

void *updater(void *args)
{
	struct foo x;
	for (int i = 0 ; i < MAX-10; i++) {
		x.a = i;
		x.b = i+1;
		gl = x;
		printf(".");
	}
	done = 1;

}

void *reader(void *args)
{
	while (!done){
		int a = gl.a;
		int b = gl.b;
		if (b - a != 1){
			printf("\nWrong update: %d %d\n", a, b );
			pthread_cancel(tid[0]);
			break;
		}
	}
}


int main(){
	int err;

	printf("read tid is %d and updater tid is %d\n", tid[0], tid[1]);

	err = pthread_create(&tid[0], NULL, &updater, NULL);
	err = pthread_create(&tid[1], NULL, &reader, NULL);



	if (err){
		perror("Thread error\n");
		exit(255);
	}

	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);
	return 0;
}
