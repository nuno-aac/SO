typedef struct artigo{
    off_t code;
    int preco;
} Artigo;

//API
Artigo newArtigo(off_t string, int preco);
int artigoPreco(Artigo *a);
void artigoTrocaPreco(Artigo *a, int preco);
int getPreco(Artigo *a);
off_t getStringPos(Artigo *a);
void saveArtigo(Artigo a, char * stdName);
int getArtigo(off_t code, char * stdName, Artigo * a);
void updateArtigoPreco(off_t code, int preco);
void updateArtigoNome(off_t code, char * stdName);
void translateArtigos();
