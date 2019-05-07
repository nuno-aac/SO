#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include "stock.h"

int main() {
	int fstock, fvendas, input;
	int op, numread, stock, code;

	printf("Starting server...\n");
	mkfifo("pip", 0644);

	printf("Forking..\n");
	if (!fork()) {
		printf("Opening pipe\n");
		input = open("pip", O_RDONLY);
		printf("Opening vendas\n");
		fvendas = open("vendas", O_CREAT | O_WRONLY | O_APPEND, 0644);
		printf("Reading\n");
		while (1) {
			char buf[1024];
			numread = read(input, &op, sizeof(int));
			//printf("[DEBUG] OP %d", op);
			if (numread > 0){
				switch (op) {
					case 0:
						//printf("[DEBUG] OP %d", op);
						read(input, &code, sizeof(int));
						getStock(code, &stock);
						printf("[DEBUG] Stock do produto %d: %d\n", code, stock);
				}
			}
		}
	}
	else {
		wait(NULL);
	}
	return 0;
}
