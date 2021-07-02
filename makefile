all: ./adt/stack_adt.c ./adt/queue.c sandwich_shop.c main.c
	gcc -Wall -Iadt main.c ./adt/stack_adt.c ./adt/queue.c sandwich_shop.c -o sshop 
