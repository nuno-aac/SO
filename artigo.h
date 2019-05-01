typedef struct artigo{
    off_t string;
    double preco;
} Artigo;

//API
Artigo newArtigo(off_t string, double preco);
int artigoPreco(Artigo *a);
void artigoTrocaPreco(Artigo *a, double preco);
double getPreco(Artigo *a);
off_t getStringPos(Artigo *a);
void saveArtigo(Artigo *a);
