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

        int numEntradas, numNeuroniosOcultos, numSaidas, numSaidasDesejadas;

        double erroAtual;
        double somaErro;
        double gradienteSaida;
        double taxaAprendizado;
        double erroQuadraticoMedio, erroRelativoMedio, mediaErro, variancia;
        double variacaoErro;

        vector<double> pesosSaida;
        vector<double> erros;
        vector<vector<double>> dadosEntrada;
        vector<vector<double>> saidasDesejadas;
        vector<vector<double>> saidasCamadas;
        vector<vector<Neuronio>> rede;

        void aplicarKmeans();
        void inicializarPesosCamadaSaida(string modo);
        void feedFoward(vector<double> dadoEntrada);
        void calcularErro(Neuronio &n, double &saidaDesejada);
        void calcularErro(double &saida, double &saidaDesejada);
        void calcularMediaErro();
        void calcularVarianciaErro();
        void calcularErroQuadraticoMedio();
        void calcularErroRelativoMedio(double &saida, double &saidaDesejada);
        void salvarErro();
        void salvarErroQuaMedCSV(string &nomeArquivo, vector<double> dadosErroQuadMed);
        void calcularGradienteSaida(Neuronio &n);
        void atualizarPesosSaida(vector<double> dadoEntrada, vector<double> saidaDesejada);
        void treinarPorNumEpisodios(int numEpisodios);
        void treinarPorErroMinimo(double erroMinimo, int IDtreinamento);
        void testar(vector<vector<double>> dadosEntrada, vector<vector<double>> saidasDesejadas);
        void mostrarPesos();
};

#endif