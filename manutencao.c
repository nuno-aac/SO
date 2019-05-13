#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include "artigo.h"
#include "vendas.h"
#include "stock.h"

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

void stdizeName(char * stdName, char * name){
    int i;

    for(i = 0; i < strlen(name); i++)
        stdName[i] = name[i];
    stdName[i] = '\0';

    return;
}

int main(int argc, char * argv[]){
    Artigo a;
    char buf[128], stdName[80], op, *currentTok;
    int numread, preco, codigo;

    numread = getOp(0, buf);

    while(numread > 1){
        currentTok = strtok(buf, " ");
        op = currentTok[0];
        switch (op) {
            case 'i':
                currentTok = strtok(NULL, " ");
                stdizeName(stdName, currentTok);
                currentTok = strtok(NULL, " ");
                preco = atoi(currentTok);
                a = newArtigo(sizeof(stdName),preco);
                saveArtigo(a, stdName);
                saveToStock(0);
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
            case 'a':
                if(fork() == 0){
                    execlp("./ag", "./ag", NULL);
                }
                else{
                    wait(NULL);
                }
                break;
            case 't':
                translateArtigos();
                break;
            case 'v':
                translateVendas();
                break;
            default:
                printf("Introduza uma operação válida\n");
                break;

        }

        numread = getOp(0, buf);
    }

    return 0;
}
