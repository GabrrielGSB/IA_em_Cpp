#include "../include/MLP.h"
#include "../../Comum/include/myFuncoes.h"


int main()
{
    vector<vector<double>> dadosEntradaTreinamento;
    vector<vector<double>> dadosEntradaValidacao;
    vector<vector<double>> saidasDesejadasTreinamento;
    vector<vector<double>> saidasDesejadasValidacao;
    vector<double> saidaDesejada;

    lerCSV("Dados/dadosTreinamento1.csv", 4, 
            dadosEntradaTreinamento, 
            saidasDesejadasTreinamento);

    lerCSV("Dados/dadosValidacao1.csv", 4, 
            dadosEntradaValidacao, 
            saidasDesejadasValidacao);
    
    for (int i = 0; i < 1; i++)
    {    
        MLP rede({4,15,3}, 0.1, 1000, 1e-6, "sigmoide");

        rede.treinar(dadosEntradaTreinamento, 
                     saidasDesejadasTreinamento, 
                     "erroMinimo", 
                     i);

        rede.testarRede(dadosEntradaValidacao, 
                        saidasDesejadasValidacao);
    }
    // :)
    return 0;
}
























// int main()
// {
//     vector<vector<double>> dados = {{1,2,3},{4,5,6},{7,8,9},{10,11,12},{13,14,15}};
//     string nomeArquivo = "teste.csv";

//     salvarCSV(nomeArquivo, "Erro Quadrático Médio/Episódio" ,dados);

//     return 0;
// }







































// int main()
// {
//     MLP rede({3,64,64,2}, 0.1, 5000, 1e-7, "sigmoide");

//     vector<vector<double>> dadosEntrada = { {0.2, 0.9, 0.4}, {0.1, 0.3, 0.5}, 
//                                            {0.9, 0.7, 0.8}, {0.6, 0.4, 0.3} };
//     vector<vector<double>> saidasDesejadas = { {0.7, 0.3}, {0.6, 0.4}, 
//                                               {0.5, 0.5}, {0.2, 0.8} };

//     // vector<vector<double>> dadosEntrada = { {0,0}, {0,1}, 
//     //                                        {1,0}, {1,1} };
//     // vector<vector<double>> saidasDesejadas = { {0}, {1}, 
//     //                                           {1}, {0} };

//     rede.treinar(dadosEntrada, saidasDesejadas, "erroMinimo");
//     rede.testarRede(dadosEntrada);

//     // rede.feedFoward({1.2, 0.5});
//     // rede.mostrarPesos();
//     // rede.backPropagation({1, 1.2, 0.5},{2});
//     // rede.mostrarPesos();
//     // rede.mostrarSaidas();
//     // for (double saida : rede.saidasCamadas.back()) printf("%.3f ", saida);

//     return 0;
// }