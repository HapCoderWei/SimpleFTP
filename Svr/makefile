Server: main.o command.o
	gcc main.o command.o -o Server -lpthread
main.o: main.c
	gcc -c main.c
command.o: command.c
	gcc -c command.c
clean:
	rm *.o
