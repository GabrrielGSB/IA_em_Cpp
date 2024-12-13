#include "../include/Perceptron.h"
#include "myFuncoes.cpp"

Perceptron::Perceptron(int numEpisodiosTotais, double taxaAprendizado, int tamEntrada=2, string funcAtiv="degrau") : 
                       numEpisodiosTotais(numEpisodiosTotais),
                       n(taxaAprendizado, tamEntrada, funcAtiv), 
                       numEpisodiosAtual(0), 
                       existeErro(false) {}

void Perceptron::atualizarPesos(vector<float> entrada, float saidaDesejada)
{
    n.definirSinalBias(entrada);
    for (int i = 0; i < n.pesos.size(); i++) n.pesos[i] = n.pesos[i] + n.taxaAprendizado * (saidaDesejada - n.saida) * entrada[i];
    this->existeErro = true;
}

void Perceptron::treinar(vector<vector<float>> entradas, vector<float> saidaDesejada)
{
    n.inicializarPesos("random");

    do
    {
        this->existeErro = false;

        for (int i = 0; i < entradas.size(); i++)
        {
            n.aplicarEntrada(entradas[i]);
            if (n.saida != saidaDesejada[i]) atualizarPesos(entradas[i], saidaDesejada[i]);   
        }
        this->numEpisodiosAtual++;

        if (this->numEpisodiosAtual >= this->numEpisodiosTotais) break;
    } while (this->existeErro == true);
    
}

void Perceptron::mostrarResultados(vector<vector<float>> dadosEntrada)
{
    for (int i = 0; i < dadosEntrada.size(); i++)
    {
        n.aplicarEntrada(dadosEntrada[i]);
        printf("\n");
        printf("%.1f ", n.saida);
    }
}

// int main()
// {
//     // vector<vector<float>> entradas = {{0.0, 0.0}, {0.0, 1.0}, {1.0, 0.0}, {1.0, 1.0}};
//     // vector<float> saidasDesejadas  = {0.0, 0.0, 0.0, 1.0};
//     // vector<vector<float>> entradas = {{1.0, 2.0}, {3.0, 4.0}, {-1.0, -2.0}, {2.0, -1.0},
//     //                                   {0.0, 3,0}, {-2.0, 1.0}, {4.0, -2.0}, {-3.0, -1.0}, 
//     //                                   {2.0, 2.0}};
//     // vector<float> saidasDesejadas  = {0.0, 0.0, 1.0, 1.0, 0.0, 1.0, 1.0 , 1.0, 0.0};
//     vector<vector<float>> entradas = {{-0.6508, 0.1097, 4.0009}, 
//                                       {-1.4492, 0.8896, 4.4005}, 
//                                       { 2.0850, 0.6876, 12.0710}, 
//                                       { 0.2626, 1.1476, 7.7985},
//                                       { 0.6418, 1.0234, 7.0427}};
//     vector<float> saidasDesejadas  = {0.0, 0.0, 0.0, 1.0, 1.0};
//    Perceptron p(1000, 0.1, 2);
//     p.treinar(entradas, saidasDesejadas);
//     p.mostrarResultados(entradas);
//     printf("\nTreinamento terminou! em %d", p.numEpisodiosTotais);
//     return 0;
// }
// int main()
// {
//     Perceptron p(5000, 0.01, 2);
//     vector<vector<float>> entradas;
//     vector<float>         saidasDesejadas;
//     lerCSV("../DADOS/dados_treinamento.csv", 3, entradas, saidasDesejadas);
//     // for (float i : saidasDesejadas) printf("%.1f", i);
//     p.treinar(entradas, saidasDesejadas);
//     p.mostrarResultados(entradas);
//     printf("\nTreinamento terminou! em %d", p.numEpisodios);
//     return 0;
// }
