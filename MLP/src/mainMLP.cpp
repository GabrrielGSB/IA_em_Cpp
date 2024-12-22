#include "../include/MLP.h"

int main()
{
    MLP rede({3,2,2}, 0.1, 5000, 1e-7, "sigmoide");

    vector<vector<float>> dadosEntrada = { {0.2, 0.9, 0.4}, {0.1, 0.3, 0.5}, 
                                           {0.9, 0.7, 0.8}, {0.6, 0.4, 0.3} };
    vector<vector<float>> saidasDesejadas = { {0.7, 0.3}, {0.6, 0.4}, 
                                              {0.5, 0.5}, {0.2, 0.8} };

    // vector<vector<float>> dadosEntrada = { {0,0}, {0,1}, 
    //                                        {1,0}, {1,1} };
    // vector<vector<float>> saidasDesejadas = { {0}, {1}, 
    //                                           {1}, {0} };

    rede.treinar(dadosEntrada, saidasDesejadas, "erroMinimo");
    rede.testarRede(dadosEntrada, saidasDesejadas);

    // rede.feedFoward({1.2, 0.5});
    // rede.mostrarPesos();
    // rede.backPropagation({1, 1.2, 0.5},{2});
    // rede.mostrarPesos();
    // rede.mostrarSaidas();
    // for (float saida : rede.saidasCamadas.back()) printf("%.3f ", saida);

    return 0;
}