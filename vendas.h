typedef struct venda{
    int codigo;
    int quantidade;
    double montante;
} Venda;

//API
Venda newVenda(int codigo, int quantidade, double montante);
int getVenda(off_t code, Venda *v);
void saveVenda(Venda v);
