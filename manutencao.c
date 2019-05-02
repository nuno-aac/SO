#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "artigo.h"

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

    buf[i] = '\0';

    return i;
}

void stdizeName(char * stdName, char * name){
    int i;

    for(i = 0; i < strlen(name); i++)
        stdName[i] = name[i];
    stdName[i] = '\0';

    return;
}

int main(int argc, char * argv[]){
    Artigo a;
    char buf[128], stdName[10], *op, *currentTok;
    int numread, preco;

    numread = getOp(0, buf);

    while(numread > 1){
        printf("%s\n", buf);
        if(buf[0] == 'a') printf("era A!\n");

        currentTok = strtok(buf, " ");
        //printf("[DEBUG] OP = %s\n", currentTok);
        op = strdup(currentTok);
        currentTok = strtok(NULL, " ");
        //printf("[DEBUG] String = %s(com %lu elem)\n", currentTok, strlen(currentTok));
        stdizeName(stdName, currentTok);
        //printf("[DEBUG] stdName = %s(com %lu elem mas tamanho %lu)\n", stdName, strlen(stdName), sizeof(stdName));
        currentTok = strtok(NULL, " ");
        //printf("[DEBUG] preco = %s\n", currentTok);
        preco = atoi(currentTok);
        //printf("[DEBUG] preco não é %d\n", preco + 5);

        if(strcmp(op, "a") == 0){
            a = newArtigo(sizeof(stdName),preco);
            saveArtigo(&a);
        }

        numread = getOp(0, buf);
    }

    return 0;
}
