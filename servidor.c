#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include "stock.h"
#include "vendas.h"
#include "artigo.h"

int makeVenda(off_t code, int quant){
	char stdName[10];
	int montante;
	Venda v;
	Artigo a;
	quant *= -1;

	if(getArtigo(code, stdName, &a)){
		montante = quant * a.preco;
		v = newVenda(code, quant, montante);
		saveVenda(v);
		updateStock(code, -quant);
		return 1;
	}

	return 0;
}

int main() {
	int input;
	int op, numread, stock, code;

	printf("Starting server...\n");
	mkfifo("pip", 0644);

	printf("Forking..\n");
	if (!fork()) {
		printf("Opening pipe\n");
		input = open("pip", O_RDONLY);
		printf("Reading\n");
		while (1) {
			numread = read(input, &op, sizeof(int));
			//printf("[DEBUG] OP %d", op);
			if (numread > 0){
				switch (op) {
					case 0:
						//printf("[DEBUG] OP %d", op);
						read(input, &code, sizeof(int));
						getStock(code, &stock);
						printf("[DEBUG] Stock do produto %d: %d\n", code, stock);
						break;
					case 1:
						read(input, &code, sizeof(int));
						read(input, &stock, sizeof(int));
						if(stock < 0){
							if(!makeVenda(code, stock))
								printf("O produto %d não existe\n", code);
						}
						else
							if(!updateStock(code, stock))
								printf("O produto %d não existe\n", code);
						break;

				}
			}
		}
	}
	else {
		wait(NULL);
	}
	return 0;
}
