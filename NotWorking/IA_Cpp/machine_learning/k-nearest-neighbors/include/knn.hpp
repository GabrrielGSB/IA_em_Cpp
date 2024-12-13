#ifndef __KNN_H
#define __KNN_H

#include <vector>
#include "data.hpp"

// def == definir / dist == distancia
using namespace std; 

class knn
{
    int k;
    vector<data*> * vizinhos;
    vector<data*> * dados_de_treinamento;
    vector<data*> * dados_de_teste;
    vector<data*> * dados_de_validacao;

    public:
    knn(int);
    knn();
    ~knn();

    void achar_Kproximos(data *ponto_ref);
    void def_dados_de_treinamento(vector<data*> * vetor);
    void def_dados_de_teste(vector<data *> * vetor);
    void def_dados_de_validacao(vector<data *> * vetor);
    void def_k(int val);

    int prever();
    double calcular_dist(data* ponto_ref, data* entrada);
    double validar_performance();
    double testar_performance();
};

#endif