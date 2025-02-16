#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stock.h"


int saveToStock(int quantidade){
    int fd, numread;

    fd = open("./stocks", O_CREAT | O_APPEND | O_WRONLY, 0700);
    numread = write(fd, &quantidade, sizeof(int));
    close(fd);

    return numread;
}

int getStock(off_t code, int * quantidade){
    int fd, numread;

    fd = open("./stocks", O_RDONLY, 0700);
    lseek(fd, code * sizeof(int), SEEK_SET);
    numread = read(fd, quantidade, sizeof(int));
    close(fd);

    return numread;
}

int updateStock(off_t code, int changeQuant){
    int fd, quantActual, numread;

    if(getStock(code, &quantActual)){
        quantActual += changeQuant;
        fd = open("./stocks", O_WRONLY, 0700);
        lseek(fd, code * sizeof(int), SEEK_SET);
        numread = write(fd, &quantActual, sizeof(int));
        close(fd);
        return numread;
    }

    return 0;
}
