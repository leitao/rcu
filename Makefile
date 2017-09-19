all:
	gcc -g example1.c -o example1 -lurcu -lpthread
	gcc -g example2.c -o example2 -lurcu -lpthread
