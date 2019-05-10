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
			saveVenda(v);
			updateStock(code, -quant);
			return 1;
		}

	return -1;
}

int main() {
	int input, output;
	int op, numread, stock, code, resVenda;
	char string[64];

	printf("Starting server...\n");
	mkfifo("client_to_server", 0644);

	printf("Opening pipe\n");
	output = open("server_to_client", O_WRONLY);
	input = open("client_to_server", O_RDONLY);
	printf("Reading\n");
	while (1) {
		numread = read(input, &op, sizeof(int));
		//printf("[DEBUG] OP %d", op);
		if (numread > 0){
			switch (op) {
				case 0:
					read(input, &code, sizeof(int));
					if(getStock(code, &stock)){
						snprintf(string, 64, "[SERVER] Stock do produto %d: %d\n", code, stock);
						write(output, string, strlen(string));
					}
					else{
						snprintf(string, 64, "[SERVER] O produto %d não existe\n", code);
						write(output, string, strlen(string));
					}
					break;
				case 1:
					read(input, &code, sizeof(int));
					read(input, &stock, sizeof(int));
					if(stock < 0){
						resVenda = makeVenda(code, stock);
						if(resVenda == 1){
							getStock(code, &stock);
							snprintf(string, 64, "[SERVER] Novo stock do produto %d: %d\n", code, stock);
							write(output, string, strlen(string));
						}
						else if(resVenda == 0){
							snprintf(string, 64, "[SERVER] O produto %d não existe\n", code);
							write(output, string, strlen(string));
						}
						else{
							snprintf(string, 64, "[SERVER] O produto %d não tem stock disponivel\n", code);
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
		}
	}
	return 0;
}
