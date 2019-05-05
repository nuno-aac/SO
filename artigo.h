typedef struct artigo{
    off_t code;
    double preco;
} Artigo;

//API
Artigo newArtigo(off_t string, double preco);
int artigoPreco(Artigo *a);
void artigoTrocaPreco(Artigo *a, double preco);
double getPreco(Artigo *a);
off_t getStringPos(Artigo *a);
void saveArtigo(Artigo a, char * stdName);
int getArtigo(off_t code, char * stdName, Artigo * a);
void updateArtigoPreco(off_t code, double preco);
void updateArtigoNome(off_t code, char * stdName);
void translateArtigos();
