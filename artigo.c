#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "artigo.h"

Artigo newArtigo(off_t code, int preco){
    Artigo a;

    a.preco =  preco;
    a.code = code;

    return a;
}

int artigoPreco(Artigo *a){
    return (a -> preco);
}

void artigoTrocaPreco(Artigo *a, int preco){
    (a -> preco) = preco;
}

int getPreco(Artigo *a){
    return (a -> preco);
}

off_t getStringPos(Artigo *a){
    return (a -> code);
}

void saveArtigo(Artigo a, char * stdName){
    int fd;

    fd = open("./artigos", O_CREAT | O_APPEND | O_WRONLY, 0700);
    write(fd, &a, sizeof(Artigo));
    close(fd);

    fd = open("./strings", O_CREAT | O_APPEND | O_WRONLY, 0700);
    write(fd, stdName, sizeof(stdName));
    close(fd);

    return;
}

int getArtigo(off_t code, char * stdName, Artigo *a){
    int fd, numread;

    fd = open("./artigos", O_RDONLY, 0700);
    lseek(fd, code * sizeof(Artigo), SEEK_SET);
    numread = read(fd, a, sizeof(Artigo));
    close(fd);

    fd = open("./strings", O_RDONLY, 0700);
    lseek(fd, code * sizeof(stdName), SEEK_SET);
    read(fd, stdName, sizeof(stdName));
    close(fd);

    return numread;
}

void updateArtigoPreco(off_t code, int preco){
    int fd;
    char stdName[10];
    Artigo a;

    getArtigo(code, stdName, &a);
    a.preco = preco;

    fd = open("./artigos", O_WRONLY, 0700);
    lseek(fd, code * sizeof(Artigo), SEEK_SET);
    write(fd, &a, sizeof(Artigo));
    close(fd);

    return;
}

void updateArtigoNome(off_t code, char * stdName){
    int fd;

    fd = open("./strings", O_WRONLY, 0700);
    lseek(fd,code * sizeof(stdName), SEEK_SET);
    write(fd, stdName, sizeof(stdName));
    close(fd);

    return;
}

void translateArtigos(){
    int fd, code, read;
    char string[50];
    char stdName[10];
    Artigo a;

    code = 0;

    while(read = getArtigo(code, stdName, &a) && read > 0){
        snprintf(string, 50, "Artigo:%s Preco:%d\n\0", stdName, a.preco);
        if(code == 0)
            fd = open("./artigos.txt",  O_CREAT | O_WRONLY | O_TRUNC, 0700);
        else
            fd = open("./artigos.txt",  O_CREAT | O_WRONLY | O_APPEND, 0700);
        write(fd, string, strlen(string));
        close(fd);
        code++;
    }

    return;
}
