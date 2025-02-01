#include "include/RBF.h"
#include "../Comum/include/myFuncoes.h"

int main()
{
    vector<vector<double>> dadosEntradaTreinamento;
    vector<vector<double>> saidasDesejadasTreinamento;
    vector<vector<double>> dadosEntradaValidacao;
    vector<vector<double>> saidasDesejadasValidacao;

    lerCSV("dados/dadosTreinamento1.csv", 3,
           dadosEntradaTreinamento,
           saidasDesejadasTreinamento);
    lerCSV("dados/dadosValidacao1.csv", 3,
           dadosEntradaValidacao,
           saidasDesejadasValidacao);

//     RBF rede({3, 5, 1}, 0.01, dadosEntradaTreinamento, saidasDesejadasTreinamento);
    
    for (int i = 0; i < 3; i++)
    {
       RBF rede({3, 10, 1}, 0.01, dadosEntradaTreinamento, saidasDesejadasTreinamento);
       rede.treinarPorErroMinimo(1e-7, i+1);
       rede.testar(dadosEntradaValidacao, saidasDesejadasValidacao);

    }
   
//     rede.mostrarPesos();

//     rede.testar(dadosEntradaValidacao, saidasDesejadasValidacao);

    return 0;
}

















// rede.treinar(dadosEntradaTreinamento1, saidasDesejadasTreinamento1, 5000, 0);
// rede.testar(dadosEntradaTreinamento1, saidasDesejadasTreinamento1);

// rede.aplicarKmeans();
// rede.feedFoward({0.9532,    0.6949,    0.4451});
// rede.mostrarPesos();