typedef struct artigo{
    off_t code;
    int preco;
} Artigo;

//API
Artigo newArtigo(off_t string, int preco);
int saveArtigo(Artigo a, char * stdName);
int getArtigo(off_t code, char * stdName, Artigo * a);
int updateArtigoPreco(off_t code, int preco);
int updateArtigoNome(off_t code, char * stdName);
void translateArtigos();
