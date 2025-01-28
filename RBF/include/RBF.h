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
        RBF(int numEntradas, int numNeuroniosOcultos, vector<vector<double>> &dadosEntrada);

        int numNeuroniosOcultos;

        vector<double> pesosSaida;
        vector<double> saidas;
        vector<vector<double>> dadosEntrada;
        vector<vector<double>> saidasCamadasOcultas;

        void aplicarKmeans();
        void aplicarGaussiana();
        void inicializarPesosCamadaSaida(string modo);
        void obterSaida();
        void atualizarPesos();
};

#endif