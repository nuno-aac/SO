#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>

int pid;

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
	char buf[128], string[64], *currentTok, stc[12], cts[12];
    int numread, codigo, stock, op;

    pid = getpid();

    printf("Starting client...%d\n",pid);
    snprintf(stc, 12, "stc%d", pid);
	mkfifo(stc, 0644);
	snprintf(cts, 12, "cts%d", pid);
	mkfifo(cts, 0644);

	int server = open("client_to_server", O_WRONLY);


    numread = readInput(0, buf);
	while (numread > 1){
        if(fork() == 0){
		currentTok = strtok(buf, " ");
        codigo = atoi(currentTok);
        currentTok = strtok(NULL, " ");
        write(server, &pid, sizeof(int));
		int c2s = open(cts, O_WRONLY);
		int s2c = open(stc, O_RDONLY);

        if(currentTok == NULL){
            op = 0;
            while(write(c2s, &op, sizeof(int)) == 0);
            while(write(c2s, &codigo, sizeof(int)) == 0);
            readInput(s2c, string);
            while(write(1, string, strlen(string)) == 0);
        }
        else{
            stock = atoi(currentTok);
            op = 1;
            printf("[DEBUG] op:%d, codigo: %d stock: %d\n",op, codigo, stock);
            while(write(c2s, &op, sizeof(int)) == 0);
            while(write(c2s, &codigo, sizeof(int)) == 0);
            while(write(c2s, &stock, sizeof(int)) == 0);
            printf("reading from server\n");
            while(readInput(s2c, string) == 0){
                printf("help i'm stuck\n");
            }
            while(write(1, string, strlen(string)) == 0);
            printf("read!\n");
        }
        close(s2c);
        close(c2s);
        _exit(0);
        }
        else{
            wait(NULL);
            numread = readInput(0, buf);
        }
    }

    remove(cts);
    remove(stc);;

    close(server);
    return 0;
}
