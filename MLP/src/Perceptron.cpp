#include "../include/Perceptron.h"

Perceptron::Perceptron(int tamEntrada, string funcAtiv="degrau") : 
                       n(tamEntrada, funcAtiv), tamEntrada(tamEntrada), episodios(0), existeErro(false) {}

void Perceptron::atualizarPesos(float taxaAprendizado, vector<float> entrada, float saidaDesejada)
{
    printf("\n");
    n.definirTaxaAprendizado(taxaAprendizado);
    entrada.insert(entrada.begin(), -1.0);


    for (int i = 0; i < n.pesos.size(); i++)
    {   
        printf("velho peso %d: %.15f // ", i, n.pesos[i]);
        n.pesos[i] = n.pesos[i] + 0.1 * (saidaDesejada - n.saida) * entrada[i];
        printf("novo peso %d: %.15f // ", i, n.pesos[i]);
        printf("\n");
        printf("Saida desejada: %.3f // ", saidaDesejada);
        printf("Saida: %.3f // ", n.saida);
        printf("Entrada: %.3f", entrada[i]);
        printf("\n");
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
    vector<vector<float>> entradas = {{0.0, 0.0}, {0.0, 1.0}, {1.0, 0.0}, {1.0, 1.0}};
    vector<float> saidasDesejadas  = {0.0, 0.0, 0.0, 1.0};

    Perceptron p(2);

    p.treinar(0.1, entradas, saidasDesejadas);

    p.mostrarResultados(entradas);

    printf("\nTreinamento terminou! em %d", p.episodios);

    return 0;
}
