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
    char buf[128], stdName[10], op, *currentTok;
    int numread, preco, codigo;

    numread = getOp(0, buf);

    while(numread > 1){
        currentTok = strtok(buf, " ");
        op = currentTok[0];
        switch (op) {
            case 'a':
                currentTok = strtok(NULL, " ");
                stdizeName(stdName, currentTok);
                //printf("[DEBUG] stdName = %s(com %lu elem mas tamanho %lu)\n", stdName, strlen(stdName), sizeof(stdName));
                currentTok = strtok(NULL, " ");
                preco = atoi(currentTok);
                a = newArtigo(sizeof(stdName),preco);
                saveArtigo(a, stdName);
                break;
            case 'g':
                currentTok = strtok(NULL, " ");
                codigo = atoi(currentTok);
                a = getArtigo(codigo, stdName);
                printf("[DEBUG] O Preco do produto %s é: %f\n", stdName, a.preco);
                break;
            case 'p':
                currentTok = strtok(NULL, " ");
                codigo = atoi(currentTok);
                currentTok = strtok(NULL, " ");
                preco = atoi(currentTok);
                updateArtigoPreco(codigo, preco);
                break;
            case 'n':
                currentTok = strtok(NULL, " ");
                codigo = atoi(currentTok);
                currentTok = strtok(NULL, " ");
                stdizeName(stdName, currentTok);
                updateArtigoNome(codigo, stdName);
                break;
        }

        numread = getOp(0, buf);
    }

    return 0;
}
