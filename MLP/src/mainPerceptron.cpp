
#include "../include/Neuronio.h"
#include "../include/Perceptron.h"

int main()
{
    // vector<vector<float>> entradas = {{0.0, 0.0}, {0.0, 1.0}, {1.0, 0.0}, {1.0, 1.0}};
    // vector<float> saidasDesejadas  = {0.0, 0.0, 0.0, 1.0};

    // vector<vector<float>> entradas = {{1.0, 2.0}, {3.0, 4.0}, {-1.0, -2.0}, {2.0, -1.0},
    //                                   {0.0, 3,0}, {-2.0, 1.0}, {4.0, -2.0}, {-3.0, -1.0}, 
    //                                   {2.0, 2.0}};
    // vector<float> saidasDesejadas  = {0.0, 0.0, 1.0, 1.0, 0.0, 1.0, 1.0 , 1.0, 0.0};

    vector<vector<float>> entradas = {{-0.6508, 0.1097, 4.0009}, 
                                      {-1.4492, 0.8896, 4.4005}, 
                                      { 2.0850, 0.6876, 12.0710}, 
                                      { 0.2626, 1.1476, 7.7985},
                                      { 0.6418, 1.0234, 7.0427}};
    vector<float> saidasDesejadas  = {0.0, 0.0, 0.0, 1.0, 1.0};

    Perceptron p(1000, 0.1, 2, "degrau");

    p.treinar(entradas, saidasDesejadas);

    p.mostrarResultados(entradas);

    printf("\nTreinamento terminou! em %d", p.numEpisodiosTotais);

    return 0;
}