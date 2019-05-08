CC = gcc
CFLAGS = -O3 -Wall

ma: stock.o artigo.o manutencao.o
	$(CC) $(CFLAGS) artigo.o manutencao.o stock.o -o ma

sv: stock.o vendas.o servidor.o
	$(CC) $(CFLAGS) stock.o vendas.o servidor.o -o sv

cv: cliente_vendas.o
	$(CC) $(CFLAGS) cliente_vendas.o -o cv

manutencao.o: manutencao.c artigo.h stock.h
	$(CC) $(CFLAGS) -c manutencao.c

artigo.o: artigo.c artigo.h
	$(CC) $(CFLAGS) -c artigo.c

vendas.o: vendas.c vendas.h
	$(CC) $(CFLAGS) -c vendas.c

stock.o: stock.c stock.h
	$(CC) $(CFLAGS) -c stock.c

servidor.o: servidor.c
	$(CC) $(CFLAGS) -c servidor.c

cliente_vendas.o: cliente_vendas.c
	$(CC) $(CFLAGS) -c cliente_vendas.c

clean:
	rm *.o ma strings artigos vendas stocks artigos.txt
