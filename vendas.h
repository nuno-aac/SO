typedef struct venda{
    int codigo;
    int quantidade;
    double montante;
} Venda;

//API
Venda newVenda(int codigo, int quantidade, double montante);
int getCodigo(Venda *v);
int getQuantidade(Venda *v);
double getMontante(Venda *v);
void vendaTrocaMontante(Venda *v, double montante);
int getVenda(off_t code, Venda *v);
void saveVenda(Venda *v);
