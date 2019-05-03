#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stock.h"
#include "artigo.h"

Stock newStock(Artigo *a, int quantidade){
    Stock s;

    s.artigo = a;
    s.quantidade = quantidade;


    return s;
}

int getQuantidade(Stock *s){
    return (s -> quantidade);
}

void saveToStock(Stock *s){
    int fd;

    fd = open("./STOCKS", O_CREAT | O_APPEND | O_WRONLY, 0700);
    write(fd, s, sizeof(Stock));
    close(fd);

    return;
}
