#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "vendas.h"

Venda newVenda(int codigo, int quantidade, double montante){
    Venda v;

    v.codigo =  codigo;
    v.quantidade = quantidade;
    v.montante = montante;


    return v;
}

int getVenda(off_t code, Venda *v){
    int fd, numread;

    fd = open("./vendas", O_RDONLY, 0700);
    lseek(fd, code * sizeof(Venda), SEEK_SET);
    numread = read(fd, v, sizeof(Venda));
    close(fd);

    return numread;
}

void saveVenda(Venda v){
    int fd;

    fd = open("./vendas", O_CREAT | O_APPEND | O_WRONLY, 0700);
    write(fd, &v, sizeof(Venda));
    close(fd);

    return;
}
