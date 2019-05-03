#include "artigo.h"

typedef struct stock{
    Artigo artigo;
    int quantidade;
} Stock;


//API
int getQuantidadeStock(Stock *s);
void saveToStock(Stock *s);
