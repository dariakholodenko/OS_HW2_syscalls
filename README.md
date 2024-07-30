adding possibiity for user to set process weights and implementing its support with new syscalls in the linux kernel:
1. declaring new syscalls in include/linux/syscalls.h
2. reserving a syscall number in arch/x86/entry/syscalls/syscall_64.tbl
3. adding my_weight field to the task_struct
4. implementing the new syscalls in kernel/hw2.c to maintenance and keep track of the weights of processes and their children 
