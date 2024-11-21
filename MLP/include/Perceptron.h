#ifndef __PERCEPTRON_HPP
#define __PERCEPTRON_HPP

#include "Neuronio.h"
#include <string>
#include <vector>

using namespace std;

class Perceptron 
{
    public:
        Neuronio n;

        int    tamEntrada;
        int    episodios;
        bool   existeErro;
        string funcAtiv;
        
        Perceptron(int tamEntrada, string funcAtiv);

        void atualizarPesos(float taxaAprendizado, vector<float> entrada, float saidaDesejada);
        void treinar(float taxaAprendizado, vector<vector<float>> entradas, vector<float> saidaDesejada);
        void mostrarResultados(vector<vector<float>> entradas);
};

#endif
