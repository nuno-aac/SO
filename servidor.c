#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include "stock.h"
#include "vendas.h"
#include "artigo.h"

int makeVenda(off_t code, int quant){
	char stdName[10];
	int montante, stock;
	Venda v;
	Artigo a;
	quant *= -1;

	stock = 0;
	if(!getStock(code, &stock))
		return 0;

	if((stock - quant) > 0)
		if(getArtigo(code, stdName, &a)){
			montante = quant * a.preco;
			v = newVenda(code, quant, montante);
			updateStock(code, -quant);
			return saveVenda(v);;
		}

	return -1;
}

int main() {
	int pidPipe, output, input;
	int op, numread, stock, code, resVenda, pid;
	char string[64], cts[12], stc[12];
//	sigaction(SIGPIPE, &(struct sigaction){SIG_IGN}, NULL);
	printf("Starting server...\n");
	mkfifo("client_to_server", 0644);

	numread = 0;

	printf("Opening pipe\n");
	pidPipe = open("client_to_server", O_RDONLY);
	printf("Reading\n");
	while (1) {
		numread = read(pidPipe, &pid, sizeof(int));
		if(fork() == 0){
		if (numread > 0){
			snprintf(cts, 12, "cts%d", pid);
			snprintf(stc, 12, "stc%d", pid);
			input = open(cts, O_RDONLY);
			output = open(stc, O_WRONLY);
			while(read(input, &op, sizeof(int)) == 0);
			switch (op) {
				case 0:
					while(read(input, &code, sizeof(int)) == 0);
					if(getStock(code, &stock)){
						snprintf(string, 64, "[SERVER] Stock do produto %d: %d\n", code, stock);
						printf("[SERVER] Stock do produto %d: %d\n", code, stock);
						write(output, string, strlen(string));
					}
					else{
						snprintf(string, 64, "[SERVER] O produto %d não existe\n", code);snprintf(string, 64, "[SERVER] O produto %d não existe\n", code);
						printf("[SERVER] O produto %d não existe\n", code);
						write(output, string, strlen(string));
					}
					break;
				case 1:
					while(read(input, &code, sizeof(int)) == 0);
					while(read(input, &stock, sizeof(int)) == 0);
					if(stock < 0){
						resVenda = makeVenda(code, stock);
						if(resVenda > 0){
							getStock(code, &stock);
							snprintf(string, 64, "[SERVER] Novo stock do produto %d: %d\n", code, stock);
							while(write(output, string, strlen(string)) == 0){
								printf("help seerver is stuuuck\n");
							}
						}
						else if(resVenda == 0){
							printf("nao fiz venda hehehe\n");
							snprintf(string, 64, "[SERVER] O produto %d não existe\n", code);
							write(output, string, strlen(string));
						}
						else{
							snprintf(string, 64, "[SERVER] O produto %d não tem stock disponivel\n", code);
							printf("nao fiz venda hehehe\n");
							write(output, string, strlen(string));
						}
					}
					else
						if(updateStock(code, stock)){
							getStock(code, &stock);
							snprintf(string, 64, "[SERVER] Novo stock do produto %d: %d\n", code, stock);
							write(output, string, strlen(string));
						}
						else{
							snprintf(string, 64, "[SERVER] O produto %d não existe\n", code);
							write(output, string, strlen(string));
						}
					break;
			}
			close(input);
			close(output);
		}
		_exit(0);
	}
	else{
		wait(NULL);
	}
	}
	close(pidPipe);
	return 0;
}
