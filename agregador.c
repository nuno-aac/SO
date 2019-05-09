#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "vendas.h"

int getVendaAgregada(off_t * code, int codigoVenda,Venda * vendaAgregada){
    int fd, numread;
    off_t agcode;
    Venda v;

    agcode = 0;

    fd = open("./agregado", O_RDONLY, 0700);
    while(numread = read(fd, &v, sizeof(Venda))  && numread > 0){
        if(v.codigo == codigoVenda) break;
        agcode++;
    }

    code = &agcode;
    vendaAgregada = &v;

    return numread;
}

void updateVendaAgregada(off_t codeAgregada, Venda v){
    int fd;

    fd = open("./agregado", O_WRONLY, 0700);
    lseek(fd,codeAgregada * sizeof(Venda), SEEK_SET);
    write(fd, &v, sizeof(Venda));
    close(fd);

    return;
}

int main(){
    int code;
    off_t codeAgregada;
    Venda v, vendaAgregada;

    code = 0;
    codeAgregada = 0;

    while(getVenda(code, &v)){
        if(getVendaAgregada(&codeAgregada, v.codigo, &vendaAgregada)){
            v.montante += vendaAgregada.montante;
            v.quantidade += vendaAgregada.quantidade;
        }
        updateVendaAgregada(codeAgregada, v);
        code++;
    }
    return 0;
}
