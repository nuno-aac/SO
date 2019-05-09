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

    fd = open("./agregado", O_RDONLY | O_CREAT, 0700);
    while(numread = read(fd, &v, sizeof(Venda))  && numread > 0){
        if(v.codigo == codigoVenda) break;
        agcode++;
    }
    printf("[debug] agcode:%lu\n", agcode);
    * code = agcode;
    * vendaAgregada = v;

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
        snprintf(string, 100, "Venda: %d Quantidade vendida: %d Montante: %f\n\0", v.codigo, v.quantidade, v.montante);
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

    printf("[DEBUG]Escrevendo no codigo:%lu\n", codeAgregada);
    fd = open("./agregado",  O_CREAT | O_WRONLY, 0700);
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
        printf("Venda do produto: %d, quant: %d montante: %f\n",v.codigo , v.quantidade, v.montante);
        if(getVendaAgregada(&codeAgregada, v.codigo, &vendaAgregada)){
            printf("[DEBUG] Encontrou no agregado CODIGO:%lu\n", codeAgregada);
            printf("[UPDATED]Venda Agregada: %d, quant: %d montante: %f\n",vendaAgregada.codigo , vendaAgregada.quantidade, vendaAgregada.montante);
            v.montante += vendaAgregada.montante;
            v.quantidade += vendaAgregada.quantidade;
            printf("[UPDATED]Venda do produto: %d, quant: %d montante: %f\n",v.codigo , v.quantidade, v.montante);
        }
        printf("[DEBUG main] Escrevendo no codigo CODIGO:%lu\n", codeAgregada);
        updateVendaAgregada(codeAgregada, v);
        code++;
    }
    translateAgregado();
    return 0;
}
