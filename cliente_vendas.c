#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

ssize_t readInput(int fildes, char *buf){
    ssize_t n;
    int i;
    char byte;

    i = 0;

    while((n=read(fildes, &byte, 1)) > 0){
        buf[i] = byte;
        i++;
        if(byte == '\n') break;
    }
    if(fildes == 0)
        buf[i-1] = '\0';
    else
        buf[i] = '\0';

    return i;
}

int main(int argc, char* argv[]) {
	char buf[128], string[64], *currentTok;
    int numread, codigo, stock, op, pid;

    pid = getpid();

    printf("Starting client...%d\n",pid);
	mkfifo("server_to_client", 0644);

    int client = open("server_to_client", O_RDONLY);
    int server = open("client_to_server", O_WRONLY);

	if (server < 0) {
		printf("Server offline\n");
		return 1;
	}

    numread = readInput(0, buf);
	while (numread > 1){
		currentTok = strtok(buf, " ");
        codigo = atoi(currentTok);
        currentTok = strtok(NULL, " ");

        if(currentTok == NULL){
            op = 0;
            write(server, &op, sizeof(int));
            write(server, &codigo, sizeof(int));
            readInput(client, string);
            write(1, string, strlen(string));
        }
        else{
            stock = atoi(currentTok);
            op = 1;
            write(server, &op, sizeof(int));
            write(server, &codigo, sizeof(int));
            write(server, &stock, sizeof(int));
            readInput(client, string);
            write(1, string, strlen(string));
        }
		numread = readInput(0, buf);
    }

    close(client);
    close(server);
    return 0;
}
