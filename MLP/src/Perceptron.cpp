#include "../include/Perceptron.h"

Perceptron::Perceptron(int tamEntrada, string funcAtiv="degrau") : n(tamEntrada, funcAtiv){}

void Perceptron::atualizarPesos(float taxaAprendizado, vector<float> entrada, vector<float> saidaDesejada)
{
    for (int i = 0; i < n.pesos.size(); i++)
    {
        n.pesos[i] = n.pesos[i] + n.taxaAprendizado * (saidaDesejada[i] - n.saida) * entrada[i];
    }
    existeErro = true;
}

void Perceptron::treinar(float taxaAprendizado, vector<vector<float>> entradas, vector<float> saidaDesejada)
{
    episodios = 0;
    n.inicializarPesos();

    n.definirTaxaAprendizado(taxaAprendizado);

    do
    {
        existeErro = false;
        for (int i = 0; i < entradas.size(); i++)
        {
            n.aplicarEntrada(entradas[i], "degrau");
            if (n.saida != saidaDesejada[i]) 
            {
                atualizarPesos(taxaAprendizado, entradas[i], saidaDesejada);   
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
        printf("%.1f ", n.saida);
    }
}

int main()
{
    vector<vector<float>> entradas = {{0.0, 0.0}, {0.0, 1.0}, {1.0, 0.0}, {1.0, 1.0}};
    vector<float> saidasDesejadas  = {0.0, 1.0, 1.0, 1.0};

    Perceptron p(2);

    p.treinar(1, entradas, saidasDesejadas);

    p.mostrarResultados(entradas);

    printf("\nTreinamento terminou! em %d", p.episodios);

    return 0;
}