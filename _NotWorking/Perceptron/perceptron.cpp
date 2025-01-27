#include "perceptron.hpp"

Perceptron::Perceptron(vector<vector<double>> entradas, vector<double> saidasDesejadas, vector<double> pesos, vector<double> erros,
                       double taxaAprendizado) : entradas(entradas), saidasDesejadas(saidasDesejadas), pesos(pesos), erros(erros), 
                                                 taxaAprendizado(taxaAprendizado) {}

void  Perceptron::definirTaxaAprendizado(double taxaAprendizado) {taxaAprendizado = taxaAprendizado;}

int   Perceptron::step(double u)
{
    if(u > 0) u = 1;
    else      u = 0;
    return u;
}

void Perceptron::calcularErro() 
{ 
    for (int i = 0; i < saidasDesejadas.size(); i++) {erros[i] = (saidasDesejadas[i] - saidasObtidas[i]);}
    
    for (int i = 0; i < erros.size(); i++) {if (erros[i] != 0) atualizarPesos(i);}
}

void Perceptron::transferencia()
{
    for(int i = 0; i < entradas.size(); i++)
    {
        double u = 0;
        for (int j = 0; j < entradas[i].size(); j++) {u += entradas[i][j] * pesos[j+1];}
        u += pesos[0];
        saidasObtidas[i] = step(u);
    }
}

void   Perceptron::atualizarPesos(int index)                 
{   
    for(int i = 0; i < pesos.size()-1; i++)
    {
        // printf("index = %d, taxa = %.1f, erro = %.2f, entrada = %.1f, peso = %0.2f\n", index, taxaAprendizado, erros[index], entradas[i][index], pesos[i]);
        pesos[i+1] = pesos[i+1] + taxaAprendizado * erros[index] * entradas[index][i];
        // printf("%.2f\n",pesos[i+1]);
        // printf("index = %d, taxa = %.1f, erro = %.2f, entrada = %.1f, peso = %0.2f\n", index, taxaAprendizado, erros[index], entradas[i][index], pesos[i]);

        // printf("\n");
        // printf("%.2f\n",pesos[i+1]);
    }    
}