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
        kMeans(int numEntradas, int numAgrupamentos, vector<vector<double>> &dadosEntrada);
        
        int numEntradas;
        int numAgrupamentos;
        bool aglomeradosFormados;
        vector<double> variancias;
        vector<vector<double>> centros;
        vector<vector<double>> dadosEntrada;
        vector<vector<vector<double>>> agrupamentos;

        void preencherAgrupamentos();
        void atualizarCentros();
        void aplicarAlgoritmo();
        void calcularVariancia();
        void mostrarVariancias();
        void mostrarCentrosObtidos();

};

#endif