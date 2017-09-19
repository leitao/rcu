Examples on how to use RCU

These files show a file that describes the problem that RCU solves  in file `problem.c` and how to solve it using different methods:

`spinlock.c` solves it using spinlocks
`mutex.c` solves it using mutex locks
`rcu.c` solves it using RCU

On all solution, you can see a performance number of reads/sec
