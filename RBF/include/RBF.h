#ifndef __RBF_HPP
#define __RBF_HPP

using namespace std;

#include "../../K_MEANS/include/K_MEANS.h"
#include "../../Comum/include/myFuncoes.h"
#include "../../Comum/include/Neuronio.h"
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
        RBF(vector<int> estruturaRede, double taxaAprendizado, 
            vector<vector<double>> &dadosEntrada, vector<vector<double>> &saidasDesejadas);

        int numEntradas, numNeuroniosOcultos, numSaidas;

        double erroAtual;
        double somaErro;
        double gradienteSaida;
        double taxaAprendizado;

        vector<double> pesosSaida;
        vector<vector<double>> dadosEntrada;
        vector<vector<double>> saidasDesejadas;
        vector<vector<double>> saidasCamadas;
        vector<vector<Neuronio>> rede;

        void aplicarKmeans();
        void inicializarPesosCamadaSaida(string modo);
        void feedFoward(vector<double> dadoEntrada);
        void calcularErro(Neuronio &n, double &saidaDesejada);
        void calcularErro(double &saida, double &saidaDesejada);
        void calcularGradienteSaida(Neuronio &n);
        void atualizarPesosSaida(vector<double> dadoEntrada, vector<double> saidaDesejada);
        void treinar(vector<vector<double>> &dadosEntrada, 
                     vector<vector<double>> &saidasDesejadas,
                     int numEpisodios, int IDtreinamento);
        void testar(vector<vector<double>> &dadosEntrada, 
                    vector<vector<double>> &saidasDesejadas);
};

#endif