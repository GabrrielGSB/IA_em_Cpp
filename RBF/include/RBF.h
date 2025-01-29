#ifndef __RBF_HPP
#define __RBF_HPP

using namespace std;

#include "../../K_MEANS/include/K_MEANS.h"
#include "../../Comum/include/myFuncoes.h"
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <cmath>

class RBF
{
    private:
        kMeans K;

    public:
        RBF(int numEntradas, int numNeuroniosOcultos, int numSaidas, double taxaAprendizado, 
            vector<vector<double>> &dadosEntrada, vector<vector<double>> &saidasDesejadas);

        int numNeuroniosOcultos;
        int numSaidas;

        double erroAtual;
        double somaErro;
        double gradienteSaida;
        double taxaAprendizado;

        vector<double> pesosSaida;
        vector<double> saidas;
        vector<vector<double>> dadosEntrada;
        vector<vector<double>> saidasDesejadas;
        vector<vector<double>> saidasCamadasOcultas;

        void aplicarKmeans();
        void aplicarGaussiana();
        void inicializarPesosCamadaSaida(string modo);
        void obterSaida();
        void calcularErro(int indiceDadoEntrada);
        void calcularGradienteSaida(int indiceDadoEntrada);
        void atualizarPesos(int indiceDadoEntrada);
};

#endif