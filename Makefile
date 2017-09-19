all:
	gcc -g problem.c -o problem -lpthread
	gcc -g misc.c rcu.c -o rcu -lurcu -lpthread
	gcc -g misc.c mutex.c -o mutex -lurcu -lpthread
	gcc -g misc.c spinlock.c -o spinlock -lurcu -lpthread
	gcc -g misc.c spinlock_parallel.c -o spinlock_parallel -lurcu -lpthread
	gcc -g misc.c rcu_parallel.c -o rcu_parallel -lurcu -lpthread

clean:
	rm -fr problem rcu mutex spinlock spinlock_parallel rcu_parallel
