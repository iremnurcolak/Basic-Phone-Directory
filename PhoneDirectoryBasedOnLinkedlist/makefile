executable: main.o linkedlist.o menu.o
	gcc -o executable main.o linkedlist.o menu.o -I.
main.o: main.c main.h linkedlist.h menu.h
	gcc -c main.c
linkedlist.o: linkedlist.c linkedlist.h main.h
	gcc -c linkedlist.c
menu.o: menu.c menu.h main.h
	gcc -c menu.c
