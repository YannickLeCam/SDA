#CFLAGS= -Wall -Wextra -Werror
#all : arbre

test: main.o arbre.o
	gcc -o test main.o arbre.o

main.o: main.c arbre.h
	gcc -o main.o -c main.c

arbre.o: arbre.c arbre.h
	gcc -o arbre.o -c arbre.c

clean:
	rm *.o test
	
git:
	make clean
	git add .
	git commit -m "Description du .h fait !"
	git push
