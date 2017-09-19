#include <pthread.h>
#include <unistd.h>
#include <urcu.h>
#include <stdio.h>
#include <limits.h>
#include <time.h>

#define MAX INT_MAX

struct foo {
	int a;
	int b;
};

struct foo *gl;
int done = 0;
pthread_t tid[3];
pthread_spinlock_t spin;
// amount of reads
long reads = 0;

extern void *timer(void *args);

void *updater(void *args)
{
	struct foo *x;
	struct foo *old;


	for (int i = 0 ; i < INT_MAX; i++) {
		x = malloc(sizeof(struct foo));
		x->a = i;
		x->b = i+1;
		old = gl;
		pthread_spin_lock(&spin);
		gl = x;
		pthread_spin_unlock(&spin);
		free(old);
	}

	done = 1;

}

void *reader(void *args)
{
	while (!done){
		int a, b;
		pthread_spin_lock(&spin);
		a =  gl->a;
		b =  gl->b;
		pthread_spin_unlock(&spin);
		if (b - a != 1){
			printf("\nWrong update: %d %d\n", b, a);
			pthread_cancel(tid[0]);
			break;
		}
		reads++;
	}
}


int main(){
	int err;

	// Initing gl
	gl = malloc(sizeof(struct foo));
	gl->a = 1;
	gl->b = 2;

	printf("read tid is %d and updater tid is %d\n", tid[0], tid[1]);

	err = pthread_create(&tid[0], NULL, &updater, NULL);
	err = pthread_create(&tid[1], NULL, &reader, NULL);
	err = pthread_create(&tid[2], NULL, &timer, NULL);

	if (err){
		perror("Thread error\n");
		exit(255);
	}

	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);
	pthread_join(tid[2], NULL);
	return 0;
}
