#include "include/RBF.h"
#include "../Comum/include/myFuncoes.h"

int main()
{
    vector<vector<double>> dadosEntradaTreinamento1;
    vector<vector<double>> saidasDesejadasTreinamento1;

    lerCSV("dados/dadosTreinamento1.csv", 3,
           dadosEntradaTreinamento1,
           saidasDesejadasTreinamento1);

    RBF rede({3, 10, 1}, 0.1, dadosEntradaTreinamento1, saidasDesejadasTreinamento1);

    rede.treinar(dadosEntradaTreinamento1, saidasDesejadasTreinamento1, 5000, 0);
    rede.testar(dadosEntradaTreinamento1, saidasDesejadasTreinamento1);

    // rede.aplicarKmeans();
    // rede.feedFoward({0.9532,    0.6949,    0.4451});
    // rede.mostrarPesos();

    return 0;
}