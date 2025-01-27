#ifndef __KMEANS_HPP
#define __KMEANS_HPP

using namespace std;

#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <cmath>
#include <limits>

class kMeans
{
    public:
        kMeans(int numAgrupamentos);
        int numAgrupamentos;
        vector<double> variancias;
        vector<vector<double>> centros;
        vector<vector<vector<double>>> agrupamentos;

        void preencherAgrupamentos(vector<vector<double>> &dadosEntrada);
        void atualizarCentros(vector<vector<double>> &dadosEntradas);
        void calcularVariancia();
};

#endif