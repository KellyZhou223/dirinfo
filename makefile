all: main.o
	gcc -o dirinfo main.c

main.o: main.c
	gcc -c main.c

run:
	./dirinfo

clean:
	rm *.o
	rm *.exe
