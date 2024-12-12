#include "../include/Perceptron.h"

Perceptron::Perceptron(int tamEntrada, string funcAtiv="degrau") : 
                       n(tamEntrada, funcAtiv), tamEntrada(tamEntrada), episodios(0), existeErro(false) {}

void Perceptron::atualizarPesos(float taxaAprendizado, vector<float> entrada, float saidaDesejada)
{
    n.definirTaxaAprendizado(taxaAprendizado);
    entrada.insert(entrada.begin(), -1.0);


    for (int i = 0; i < n.pesos.size(); i++)
    {   
        n.pesos[i] = n.pesos[i] + 0.1 * (saidaDesejada - n.saida) * entrada[i];
    }
    existeErro = true;
}

void Perceptron::treinar(float taxaAprendizado, vector<vector<float>> entradas, vector<float> saidaDesejada)
{
    n.inicializarPesos("random");
    n.definirTaxaAprendizado(taxaAprendizado);
    do
    {
        existeErro = false;
        for (int i = 0; i < entradas.size(); i++)
        {
            n.aplicarEntrada(entradas[i], "degrau");

            if (n.saida != saidaDesejada[i]) 
            {
                atualizarPesos(taxaAprendizado, entradas[i], saidaDesejada[i]);   
            }
        }
        episodios++;
    } while (existeErro == true);
    
}

void Perceptron::mostrarResultados(vector<vector<float>> entradas)
{
    for (int i = 0; i < entradas.size(); i++)
    {
        n.aplicarEntrada(entradas[i], "degrau");
        printf("\n");
        printf("%.1f ", n.saida);
    }
}

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

    Perceptron p(2);

    p.treinar(0.1, entradas, saidasDesejadas);

    p.mostrarResultados(entradas);

    printf("\nTreinamento terminou! em %d", p.episodios);

    return 0;
}
