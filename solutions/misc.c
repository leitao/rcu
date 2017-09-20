#include <time.h>
#include <stdio.h>
#include <unistd.h>

long reads;
int done;

void *timer(void *args){
	struct timespec ts, ts2;
	timespec_get(&ts, TIME_UTC);
	while (!done){
		sleep(1);
		timespec_get(&ts2, TIME_UTC);
		time_t sec = ts2.tv_sec - ts.tv_sec;
		printf("%ld K reads/sec %ld\n", (reads/sec)/1000, reads/1000000);

	}

	return NULL;
}
