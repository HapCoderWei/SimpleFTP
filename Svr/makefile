server: main.o command.o
	gcc main.o command.o -o server -pthread
main.o: main.c
	gcc -c main.c
command.o: command.c
	gcc -c command.c
clean:
	rm *.o