all:
	gcc -Wall -g misc.c rcu.c -o rcu -lurcu -lpthread
	gcc -Wall -g misc.c mutex.c -o mutex -lurcu -lpthread
	gcc -Wall -g misc.c spinlock.c -o spinlock -lurcu -lpthread
	gcc -Wall -g misc.c spinlock_parallel.c -o spinlock_parallel -lurcu -lpthread
	gcc -Wall -g misc.c rcu_parallel.c -o rcu_parallel -lurcu -lpthread
	gcc -Wall -g misc.c htm.c -o htm -lurcu -lpthread
	gcc -Wall -g misc.c sem.c -o sem -lurcu -lpthread

clean:
	rm -fr sem htm problem rcu mutex spinlock spinlock_parallel rcu_parallel perf.data\*
