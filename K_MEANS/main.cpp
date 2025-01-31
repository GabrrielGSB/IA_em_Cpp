#include "include/K_MEANS.h"
#include "../Comum/include/myFuncoes.h"

int main()
{
    // vector<vector<double>> pontos;
    // lerCSV("dados/teste.csv", pontos);

    vector<vector<double>> pontos;
    vector<vector<double>> a;

    lerCSV("dados/teste1.csv", 3, 
            pontos, 
            a);


    kMeans km(3, 3, pontos);

    // km.atualizarCentros();
    // km.preencherAgrupamentos();
    // km.atualizarCentros();
    km.aplicarAlgoritmo();
    km.mostrarVariancias();
    km.mostrarCentrosObtidos();

    // for (auto i : km.centros) printf("(%.2f,%.2f)\n", i[0],i[1]);

    return 0;
}