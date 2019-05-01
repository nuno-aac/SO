#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "artigo.h"

Artigo newArtigo(off_t string, double preco){
    Artigo a;

    a.preco =  preco;
    a.string = string;

    return a;
}

int artigoPreco(Artigo *a){
    return (a -> preco);
}

void artigoTrocaPreco(Artigo *a, double preco){
    (a -> preco) = preco;
}

double getPreco(Artigo *a, double preco){
    return (a -> preco);
}

off_t getStringPos(Artigo *a, double preco){
    return (a -> string);
}

void saveArtigo(Artigo *a){
    int fd;

    fd = open("./ARTIGOS", O_CREAT | O_APPEND | O_WRONLY, 0700);
    write(fd, a, sizeof(Artigo));
    close(fd);

    return;
}
