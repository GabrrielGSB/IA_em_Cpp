#ifndef __RBF_HPP
#define __RBF_HPP

using namespace std;

#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <cmath>
#include "../../K_MEANS/include/K_MEANS.h"

class RBF
{
    public:
        RBF(int numEntradas, int numNeuroniosOcultos, vector<vector<double>> &dadosEntrada);

        int numEntradas;
        int numNeuroniosOcultos;
        vector<double> pesosSaida;
        vector<vector<double>> dadosEntrada;
};

#endif