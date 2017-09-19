all:
	gcc -g problem.c -o problem -lpthread
	gcc -g rcu.c -o rcu -lurcu -lpthread
	gcc -g mutex.c -o mutex -lurcu -lpthread
	gcc -g spinlock.c -o spinlock -lurcu -lpthread
