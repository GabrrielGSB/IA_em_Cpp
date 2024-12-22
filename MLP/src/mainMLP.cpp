#include "../include/MLP.h"

int main()
{
    MLP rede({2,2,3,2,1}, 0.1, 10, "sigmoide");
    rede.feedFoward({1.2, 0.5});
    rede.mostrarPesos();
    rede.backPropagation({1, 1.2, 0.5},{2});
    rede.mostrarPesos();
    // rede.mostrarSaidas();
    // for (float saida : rede.saidasCamadas.back()) printf("%.3f ", saida);

    return 0;
}