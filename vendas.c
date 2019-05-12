#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "vendas.h"

Venda newVenda(int codigo, int quantidade, int montante){
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

int saveVenda(Venda v){
    int fd, r;

    fd = open("./vendas", O_CREAT | O_APPEND | O_WRONLY, 0700);
    r = write(fd, &v, sizeof(Venda));
    close(fd);

    return r;
}

void translateVendas(){
    int fd, code;
    char string[100];
    Venda v;

    code = 0;

    while(getVenda(code, &v) > 0){
        snprintf(string, 100, "Venda: %d Quantidade vendida: %d Montante: %d\n", v.codigo, v.quantidade, v.montante);
        if(code == 0)
            fd = open("./vendas.txt",  O_CREAT | O_WRONLY | O_TRUNC, 0700);
        else
            fd = open("./vendas.txt",  O_CREAT | O_WRONLY | O_APPEND, 0700);
        if(write(fd, string, strlen(string)) == 0){
            perror("couldn't write string");
        }
        close(fd);
        code++;
    }

    return;
}
