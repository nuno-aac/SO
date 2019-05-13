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

int saveArtigo(Artigo a, char * stdName){
    int fd, numwrite;

    fd = open("./artigos", O_CREAT | O_APPEND | O_WRONLY, 0700);
    numwrite = write(fd, &a, sizeof(Artigo));
    close(fd);

    fd = open("./strings", O_CREAT | O_APPEND | O_WRONLY, 0700);
    numwrite = write(fd, stdName, sizeof(stdName));
    close(fd);

    return numwrite;
}

int getArtigo(off_t code, char * stdName, Artigo *a){
    int fd, numread;

    fd = open("./artigos", O_RDONLY, 0700);
    lseek(fd, code * sizeof(Artigo), SEEK_SET);
    numread = read(fd, a, sizeof(Artigo));
    close(fd);

    fd = open("./strings", O_RDONLY, 0700);
    lseek(fd, code * sizeof(stdName), SEEK_SET);
    numread = read(fd, stdName, sizeof(stdName));
    close(fd);

    return numread;
}

int updateArtigoPreco(off_t code, int preco){
    int fd, numwrite;
    char stdName[80];
    Artigo a;

    getArtigo(code, stdName, &a);
    a.preco = preco;

    fd = open("./artigos", O_WRONLY, 0700);
    lseek(fd, code * sizeof(Artigo), SEEK_SET);
    numwrite = write(fd, &a, sizeof(Artigo));
    close(fd);

    return numwrite;
}

int updateArtigoNome(off_t code, char * stdName){
    int fd, numwrite;

    fd = open("./strings", O_WRONLY, 0700);
    lseek(fd,code * sizeof(stdName), SEEK_SET);
    numwrite = write(fd, stdName, sizeof(stdName));
    close(fd);

    return numwrite;
}

void translateArtigos(){
    int fd, code;
    char string[50];
    char stdName[80];
    Artigo a;

    code = 0;

    while(getArtigo(code, stdName, &a) > 0){
        snprintf(string, 50, "Artigo: %s Preco: %d\n", stdName, a.preco);
        if(code == 0)
            fd = open("./artigos.txt",  O_CREAT | O_WRONLY | O_TRUNC, 0700);
        else
            fd = open("./artigos.txt",  O_CREAT | O_WRONLY | O_APPEND, 0700);
        if(write(fd, string, strlen(string)) == 0){
            perror("couldn't write string");
        }
        close(fd);
        code++;
    }

    return;
}
