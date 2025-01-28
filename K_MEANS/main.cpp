#include "include/K_MEANS.h"
#include "../Comum/include/myFuncoes.h"

int main()
{
    vector<vector<double>> pontos;

    lerCSV("dados/teste.csv", pontos);

    kMeans km(2, 3, pontos);

    km.aplicarAlgoritmo();
    km.mostrarVariancias();
    km.mostrarCentrosObtidos();

    // for (auto i : km.centros) printf("(%.2f,%.2f)\n", i[0],i[1]);

    return 0;
}