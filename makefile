main : main.o todo.o todo.h
	gcc -o main main.o todo.o

todo.o : todo.h todo.c
	gcc -c todo.c
