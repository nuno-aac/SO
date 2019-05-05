CC = gcc
CFLAGS = -O3 -Wall

ma: artigo.o manutencao.o
	$(CC) $(CFLAGS) artigo.o manutencao.o -o ma

sv: stock.o vendas.o
	$(CC) $(CFLAGS) stock.o vendas.o svendas.o -o sv

manutencao.o: manutencao.c artigo.h
	$(CC) $(CFLAGS) -c manutencao.c

svendas.o: svendas.c stock.h
	$(CC) $(CFLAGS) -c svendas.c

artigo.o: artigo.c artigo.h
	$(CC) $(CFLAGS) -c artigo.c

vendas.o: vendas.c vendas.h
	$(CC) $(CFLAGS) -c vendas.c

stock.o: stock.c stock.h artigo.h
	$(CC) $(CFLAGS) -c stock.c

clean:
	rm *.o ma STRINGS ARTIGOS artigos.txt
