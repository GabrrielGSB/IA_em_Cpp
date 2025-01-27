#ifndef __PERCEPTRON_H
#define __PERCEPTRON_H

#include <vector>
#include <string>
using namespace std;

class Perceptron
{
    public:
    vector<vector<double>> entradas;
    vector<double> pesos; 
    vector<double> saidasDesejadas;
    vector<double> saidasObtidas = {0,0,0,0};
    vector<double> erros;
    double taxaAprendizado;

    Perceptron(vector<vector<double>> entradas, vector<double> saidasDesejadas, vector<double> pesos, vector<double> erros,
               double taxaAprendizado);

    int  step(double u);
    void calcularErro();
    void definirTaxaAprendizado(double taxaAprendizado);
    void transferencia();
    void atualizarPesos(int index);

};

#endif