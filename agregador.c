#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "vendas.h"

int getVendaAgregada(off_t * code, int codigoVenda,Venda * vendaAgregada){
    int fd, numread;
    off_t agcode;

    numread = 0;
    agcode = 0;

    if(fd = open("./agregado", O_RDONLY, 0700)){
        while(numread = read(fd, vendaAgregada, sizeof(Venda))){
            if(vendaAgregada->codigo == codigoVenda) break;
            agcode++;
        }
    }
    close(fd);
    * code = agcode;
    return numread;
}

int readVendaAgregada(off_t code, Venda *v){
    int fd, numread;

    fd = open("./agregado", O_RDONLY, 0700);
    lseek(fd, code * sizeof(Venda), SEEK_SET);
    numread = read(fd, v, sizeof(Venda));
    close(fd);

    return numread;
}

void translateAgregado(){
    int fd, code, read;
    char string[100];;
    Venda v;

    code = 0;

    while(read = readVendaAgregada(code, &v) && read > 0){
        snprintf(string, 100, "Venda: %d Quantidade vendida: %d Montante: %d\n", v.codigo, v.quantidade, v.montante);
        if(code == 0)
            fd = open("./agregado.txt",  O_CREAT | O_WRONLY | O_TRUNC, 0700);
        else
            fd = open("./agregado.txt",  O_CREAT | O_WRONLY | O_APPEND, 0700);
        write(fd, string, strlen(string));
        close(fd);
        code++;
    }

    return;
}

void updateVendaAgregada(off_t codeAgregada, Venda v){
    int fd;

    fd = open("./agregado",O_WRONLY, 0700);
    lseek(fd,codeAgregada * sizeof(Venda), SEEK_SET);
    write(fd, &v, sizeof(Venda));
    close(fd);

    return;
}

int main(){
    int code, fd;
    off_t codeAgregada;
    Venda v, vendaAgregada, vendaNovaAgregada;

    code = 0;
    codeAgregada = 0;

    fd = open("./agregado",  O_CREAT, 0700);
    close(fd);

    while(getVenda(code, &v)){
        if(getVendaAgregada(&codeAgregada, v.codigo, &vendaAgregada)){
            vendaNovaAgregada.codigo = v.codigo;
            vendaNovaAgregada.montante = v.montante + vendaAgregada.montante;
            vendaNovaAgregada.quantidade = v.quantidade + vendaAgregada.quantidade;
            updateVendaAgregada(codeAgregada, vendaNovaAgregada);
        }
        else{
            updateVendaAgregada(codeAgregada, v);
        }
        code++;
    }
    translateAgregado();
    return 0;
}
