#ifndef __KMEANS_HPP
#define __KMEANS_HPP

using namespace std;

#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <cmath>

class kMeans
{
    public:
        kMeans(int numAgrupamentos, vector<vector<double>> &dadosEntrada);
        bool aglomeradosFormados;
        int numAgrupamentos;
        vector<double> variancias;
        vector<vector<double>> centros;
        vector<vector<double>> dadosEntrada;
        vector<vector<vector<double>>> agrupamentos;

        void preencherAgrupamentos();
        void atualizarCentros();
        void calcularVariancia();
        void aplicarAlgoritmo();

};

#endif