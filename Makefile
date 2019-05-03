CC = gcc
CFLAGS = -O3 -Wall

sgv: artigo.o manutencao.o vendas.o stock.o
	$(CC) $(CFLAGS) artigo.o manutencao.o vendas.o stock.o -o prog

manutencao.o: manutencao.c artigo.h
	$(CC) $(CFLAGS) -c manutencao.c

artigo.o: artigo.c artigo.h
	$(CC) $(CFLAGS) -c artigo.c

vendas.o: vendas.c vendas.h
	$(CC) $(CFLAGS) -c vendas.c

stock.o: stock.c stock.h aritog.h
		$(CC) $(CFLAGS) -c stock.c

clean:
	rm *.o sgv
