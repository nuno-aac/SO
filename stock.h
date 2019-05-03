typedef struct stock{
    Artigo a;
    int quantidade;
} Stock;


//API
int getQuantidade(Stock *s);
void saveToStock(Stock *s);
