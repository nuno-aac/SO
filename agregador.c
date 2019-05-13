#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "vendas.h"

int getVendaAgregada(off_t * code, int codigoVenda,Venda * vendaAgregada){
    int fd, numread;
    off_t agcode;

    numread = 0;
    agcode = 0;

    fd = open("./agregado", O_RDONLY, 0700);
    if(fd != 0){
        while(read(fd, vendaAgregada, sizeof(Venda))){
            if(vendaAgregada->codigo == codigoVenda){
                numread = 1;
                break;
            }
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

void translateAgregado(char* fich){
    int fd, code;
    char string[100];;
    Venda v;

    code = 0;

    while(readVendaAgregada(code, &v)){
        snprintf(string, 100, "Venda: %d Quantidade vendida: %d Montante: %d\n", v.codigo, v.quantidade, v.montante);
        if(code == 0)
            fd = open(fich,  O_CREAT | O_WRONLY | O_TRUNC, 0700);
        else
            fd = open(fich,  O_CREAT | O_WRONLY | O_APPEND, 0700);
        if(write(fd, string, strlen(string)) == 0){
            perror("couldn't write string");
        }
        close(fd);
        code++;
    }

    return;
}

int updateVendaAgregada(off_t codeAgregada, Venda v){
    int fd, numwrite;

    fd = open("./agregado",O_WRONLY, 0700);
    lseek(fd,codeAgregada * sizeof(Venda), SEEK_SET);
    numwrite = write(fd, &v, sizeof(Venda));
    close(fd);

    return numwrite;
}

int main(){
    int code, fd;
    off_t codeAgregada;
    Venda v, vendaAgregada, vendaNovaAgregada;
    char fich[50];
    char* timeAux;

    code = 0;
    codeAgregada = 0;
    time_t hora;

    hora = time(NULL);
    timeAux = ctime(&hora);
    timeAux[strlen(timeAux)-1] = '\0';
    snprintf(fich,50,"./%s.dat", timeAux);

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
    translateAgregado(fich);
    remove("./agregado");
    return 0;
}
