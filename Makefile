CC = gcc
CFLAGS = -O3 -Wall

ma: stock.o artigo.o manutencao.o vendas.o
	$(CC) $(CFLAGS) artigo.o manutencao.o stock.o vendas.o -o ma

sv: stock.o vendas.o artigo.o servidor.o
	$(CC) $(CFLAGS) stock.o vendas.o servidor.o artigo.o -o sv

cv: cliente_vendas.o
	$(CC) $(CFLAGS) cliente_vendas.o -o cv

ag: agregador.o vendas.o
	$(CC) $(CFLAGS) agregador.o vendas.o -o ag

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

agregador.o: agregador.c vendas.h
		$(CC) $(CFLAGS) -c agregador.c

clean:
	rm *.o ma sv cv ag strings artigos vendas agregado stocks artigos.txt vendas.txt agregado.txt *.dat client_to_server
