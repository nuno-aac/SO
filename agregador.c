#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "vendas.h"

Venda getVendaAgregada(off_t * code, int codigoVenda){
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
    if(numread > 0)
        return v;
    else
        return NULL;
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
    int code, codeAgregada;
    Venda v, vendaAgregada:

    code = 0;

    while(getVenda(code, &v)){
        vendaAgregada = getVendaAgregada(&codeAgregado, v.codigo);
        v.montante += vendaAgregada.montante;
        v.quantidade += vendaAgregada.quantidade;
        updateVendaAgregada(codeAgregada, v);
    }
    return 0;
}
