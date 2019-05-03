#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "artigo.h"

Artigo newArtigo(off_t code, double preco){
    Artigo a;

    a.preco =  preco;
    a.code = code;

    return a;
}

int artigoPreco(Artigo *a){
    return (a -> preco);
}

void artigoTrocaPreco(Artigo *a, double preco){
    (a -> preco) = preco;
}

double getPreco(Artigo *a){
    return (a -> preco);
}

off_t getStringPos(Artigo *a){
    return (a -> code);
}

void saveArtigo(Artigo a, char * stdName){
    int fd;

    fd = open("./ARTIGOS", O_CREAT | O_APPEND | O_WRONLY, 0700);
    write(fd, &a, sizeof(Artigo));
    close(fd);

    fd = open("./STRINGS", O_CREAT | O_APPEND | O_WRONLY, 0700);
    write(fd, stdName, sizeof(stdName));
    close(fd);

    return;
}

Artigo getArtigo(off_t code, char * stdName){
    int fd;
    Artigo a;

    fd = open("./ARTIGOS", O_RDONLY, 0700);
    lseek(fd, code * sizeof(Artigo), SEEK_SET);
    read(fd, &a, sizeof(Artigo));
    close(fd);

    fd = open("./STRINGS", O_RDONLY, 0700);
    lseek(fd, code * sizeof(stdName), SEEK_SET);
    read(fd, stdName, sizeof(stdName));
    close(fd);

    return a;
}

void updateArtigoPreco(off_t code, double preco){
    int fd;
    char stdName[10];
    Artigo a;

    a = getArtigo(code, stdName);
    a.preco = preco;

    fd = open("./ARTIGOS", O_WRONLY, 0700);
    lseek(fd, code * sizeof(Artigo), SEEK_SET);
    write(fd, &a, sizeof(Artigo));
    close(fd);

    return;
}

void updateArtigoNome(off_t code, char * stdName){
    int fd;

    fd = open("./ARTIGOS", O_WRONLY, 0700);
    lseek(fd, code * sizeof(stdName), SEEK_SET);
    write(fd, stdName, sizeof(stdName));
    close(fd);

    return;
}
