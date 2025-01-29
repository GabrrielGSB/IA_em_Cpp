#include "include/RBF.h"
#include "../Comum/include/myFuncoes.h"

int main()
{
    vector<vector<double>> dadosEntradaTreinamento1;
    vector<vector<double>> saidasDesejadasTreinamento1;

    lerCSV("dados/dadosTreinamento1.csv", 3, 
            dadosEntradaTreinamento1, 
            saidasDesejadasTreinamento1);

    RBF rede({3,3,1}, 0.1, dadosEntradaTreinamento1, saidasDesejadasTreinamento1);

    rede.treinar(dadosEntradaTreinamento1, saidasDesejadasTreinamento1, 2000, 0);
    // rede.testar(dadosEntradaTreinamento1, saidasDesejadasTreinamento1);

    return 0;
}