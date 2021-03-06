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

struct foo *gl;
int done = 0;
pthread_t tid[3];
long reads = 0;

extern void *timer(void *args);

void *updater(void *args)
{
	struct foo *x;
	struct foo *old;


	for (int i = 0 ; i < 4096; i++) {
		x = malloc(sizeof(struct foo));
		x->a = i;
		x->b = i+1;
		old = gl;
		rcu_assign_pointer(gl, x);
		synchronize_rcu();
		free(old);
	}

	free(x);
	done = 1;

	return NULL;

}

void *reader(void *args)
{ 
	rcu_register_thread();

	struct foo *d;
	while (!done){
		rcu_read_lock();
		d = rcu_dereference(gl);
		int a = d->a;
		int b = d->b;
		rcu_read_unlock();
		if (b - a != 1){
			printf("\nWrong update: %d %d\n", a, b );
			pthread_cancel(tid[0]);
			break;
		}
		reads++;
	}

	rcu_unregister_thread();

	return NULL;
}

int main(){
	int err;

	// Initing gl
	gl = malloc(sizeof(struct foo));
	gl->a = 1;
	gl->b = 2;

	// Init RCU
	rcu_init();

	err = pthread_create(&tid[0], NULL, &updater, NULL);
	err = pthread_create(&tid[1], NULL, &reader, NULL);
	err = pthread_create(&tid[2], NULL, &reader, NULL);
	err = pthread_create(&tid[3], NULL, &timer, NULL);

	if (err){
		perror("Thread error\n");
		exit(255);
	}

	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);
	pthread_join(tid[2], NULL);
	pthread_join(tid[3], NULL);

	// Free RCU
	return 0;
}
