#include "../include/Perceptron.h"
#include "../../Comum/include/myFuncoes.h"

Perceptron::Perceptron(int numEpisodiosTotais, double taxaAprendizado, int tamEntrada, string funcAtiv="degrau") : 
                       numEpisodiosTotais(numEpisodiosTotais),
                       n(taxaAprendizado, tamEntrada, funcAtiv), 
                       numEpisodiosAtual(0), 
                       existeErro(false) {}

void Perceptron::atualizarPesos(vector<float> dadoEntrada, float saidaDesejada)
{
    n.definirSinalBias(dadoEntrada);
    float erro = saidaDesejada - n.saida; 
    if (erro != 0) 
    { 
        for (int i = 0; i < n.pesos.size(); i++) n.pesos[i] += n.taxaAprendizado * erro * dadoEntrada[i]; // Atualização dos pesos
        this->existeErro = true;
    } 
    else this->existeErro = false;
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
    printf("\nTreinamento concluido!\n");
}

void Perceptron::treinar(vector<vector<float>> entradas, vector<float> saidaDesejada, string info)
{
    n.inicializarPesos("random");

    int numAcertos = 0;
    int numErros = 0;

    do
    {
        this->existeErro = false;
        float erroTotal = 0.0;  
        
        for (int i = 0; i < entradas.size(); i++)
        {
            n.aplicarEntrada(entradas[i]);
            float erro = saidaDesejada[i] - n.saida;
            erroTotal += fabs(erro);

            if (erro != 0)
            {
                numErros++;
                atualizarPesos(entradas[i], saidaDesejada[i]);
            }
            else numAcertos++;   
        }

        if (info == "info")
        {
        printf("Erro total na epoca %d: %.1f (", numEpisodiosAtual, erroTotal);
        printf("Acertos: %d | Erros: %d)\n", numAcertos, numErros);
        }

        numErros = 0, numAcertos = 0;
        this->numEpisodiosAtual++;

    } while (this->existeErro == true);
    printf("\nTreinamento concluido!");
}


void Perceptron::mostrarResultados(vector<vector<float>> dadosEntrada, vector<float> saidasDesejadas)
{
    int acertos = 0;
    int erros = 0;

    printf("\nResultados do treinamento:\n");

    for (int i = 0; i < dadosEntrada.size(); i++)
    {
        n.aplicarEntrada(dadosEntrada[i]);

        if (n.saida == saidasDesejadas[i]) acertos++;
        else                               erros++;
        
    }
    printf("Numero de acertos: %d\n", acertos);
    printf("Numero de erros: %d\n", erros);
    printf("Precisao = %.3f \%\n", ((float)acertos / dadosEntrada.size() * 100));
}


void Perceptron::mostrarPesos()
{
    uint8_t cont = 0;

    printf("\nPesos apos o treinamento:\n");
    for (float peso : n.pesos)
    {
        if (cont == 0) printf("bias -> %.3f\n", peso);
        else printf("w%d -> %.3f\n", cont, peso);
        cont++;
    }
}

