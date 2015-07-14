Client: main.o command.o input.o
	gcc main.o command.o input.o -o Client
main.o: main.c
	gcc -c main.c
command.o: command.c
	gcc -c command.c
input.o: input.c
	gcc -c input.c
.PHONY:clean
clean:
	rm *.o
