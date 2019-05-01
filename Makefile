CC = gcc
CFLAGS = -O3 -Wall

sgv: artigo.o manutencao.o
	$(CC) $(CFLAGS) artigo.o manutencao.o -o prog

manutencao.o: manutencao.c artigo.h
	$(CC) $(CFLAGS) -c manutencao.c

artigo.o: artigo.c artigo.h
	$(CC) $(CFLAGS) -c artigo.c

clean:
	rm *.o sgv
