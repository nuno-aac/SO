typedef struct venda{
    int codigo;
    int quantidade;
    int montante;
} Venda;

//API
Venda newVenda(int codigo, int quantidade, int montante);
int getVenda(off_t code, Venda *v);
void saveVenda(Venda v);
void translateVendas();
