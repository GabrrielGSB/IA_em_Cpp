#ifndef __PERCEPTRON_HPP
#define __PERCEPTRON_HPP

#include "Neuronio.h"
#include <string>
#include <vector>

using namespace std;

class Perceptron
{
    private:
        Neuronio n;

    public:
        int    tamEntrada;
        int    episodios;
        bool   existeErro;
        string funcAtiv;
        // vector<float> saidaDesejada;

        Perceptron(int tamEntrada, string funcAtiv);

        void atualizarPesos(float taxaAprendizado, vector<float> entrada, vector<float> saidaDesejada);
        void treinar(float taxaAprendizado, vector<vector<float>> entradas, vector<float> saidaDesejada);
        void mostrarResultados(vector<vector<float>> entradas);
};

#endif