all: lsh

lsh : main.o lsh_ls.o lsh_mv.o
	gcc -o lsh lsh_ls.o lsh_mv.o main.o -lm

lsh_ls.o : lsh_ls.c lsh.h

lsh_mv.o : lsh_mv.c lsh.h

main.o : main.c lsh.h

clean:
	rm *.o lsh