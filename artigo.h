typedef struct artigo{
    off_t string;
    double preco;
} Artigo;

//API
Artigo newArtigo(off_t string, double preco);
int artigoPreco(Artigo *a);
void artigoTrocaPreco(Artigo *a, double preco);
double getPreco(Artigo *a, double preco);
off_t getStringPos(Artigo *a, double preco);
void saveArtigo(Artigo *a);
