#ifndef __PERCEPTRON_HPP
#define __PERCEPTRON_HPP

#include "Neuronio.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
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
        
        void atualizarPesos(vector<float> dadosEntrada, float saidaDesejada);
        void treinar(vector<vector<float>> entradas, vector<float> saidaDesejada);
        void mostrarResultados(vector<vector<float>> entradas);
};

#endif
