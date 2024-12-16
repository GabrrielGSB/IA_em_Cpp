#ifndef __PERCEPTRON_HPP
#define __PERCEPTRON_HPP

#include "../../Comum/include/Neuronio.h"
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>

using namespace std;

class Perceptron 
{
    private:
        Neuronio n;

    public:
        Perceptron(int numEpisodiosTotais, double taxaAprendizado, int tamEntrada, string funcAtiv);

        int    numEpisodiosAtual, 
               numEpisodiosTotais;
        bool   existeErro;
        vector<float> erros;
        
        void atualizarPesos(vector<float> dadosEntrada, float saidaDesejada);
        void treinar(vector<vector<float>> entradas, vector<float> saidaDesejada);
        void treinar(vector<vector<float>> entradas, vector<float> saidaDesejada, string info);
        void mostrarResultados(vector<vector<float>> entradas, vector<float> saidasDesejadas);
        void mostrarPesos();
};

#endif
