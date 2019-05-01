#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "artigo.h"

int main(int argc, char * argv[]){
    Artigo a;

    if(strcmp(argv[1], "-a") == 0){
        a = newArtigo(1,atof(argv[3]));
        saveArtigo(&a);
    }

    return 0;
}
