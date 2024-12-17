#include "../include/MLP.h"

int main()
{
    MLP rede({2,2,2}, 0.1, 10, "sigmoide");
    rede.inicializarPesosRede();
    rede.feedFoward({1,1});
    rede.mostrarPesos();
    rede.backPropagation({1,1});
    rede.mostrarPesos();
    // rede.mostrarSaidas();
    // for (float saida : rede.saidasCamadas.back()) printf("%.3f ", saida);

    return 0;
}