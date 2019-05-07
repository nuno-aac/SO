#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

ssize_t getOp(int fildes, char *buf){
    ssize_t n;
    int i;
    char byte;

    i = 0;

    while((n=read(fildes, &byte, 1)) > 0){
        buf[i] = byte;
        i++;
        if(byte == '\n') break;
    }

    buf[i-1] = '\0';

    return i;
}

int main(int argc, char* argv[]) {
	char buf[128], *currentTok;
    int numread, codigo, stock, op;

	int server = open("pip", O_WRONLY);
	if (server < 0) {
		printf("Server offline\n");
		return 1;
	}

    numread = getOp(0, buf);
	while (numread > 1){
		currentTok = strtok(buf, " ");
        codigo = atoi(currentTok);
        currentTok = strtok(NULL, " ");

        if(currentTok == NULL){
            op = 0;
            write(server, &op, sizeof(int));
            write(server, &codigo, sizeof(int));
        }
        else{
            stock = atoi(currentTok);
            op = 1;
            write(server, &op, sizeof(int));
            write(server, &codigo, sizeof(int));
            write(server, &stock, sizeof(int));
        }
		numread = getOp(0, buf);
    }

    close(server);
    return 0;
}
