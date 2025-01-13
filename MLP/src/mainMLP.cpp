#include "../include/MLP.h"
#include "../../Comum/include/myFuncoes.h"
#include <chrono>


int main()
{
    vector<vector<double>> dadosEntradaTreinamento1;
    vector<vector<double>> dadosEntradaValidacao1;
    vector<vector<double>> saidasDesejadasTreinamento1;
    vector<vector<double>> saidasDesejadasValidacao1;

    vector<vector<double>> dadosEntradaTreinamento2;
    vector<vector<double>> dadosEntradaValidacao2;
    vector<vector<double>> saidasDesejadasTreinamento2;
    vector<vector<double>> saidasDesejadasValidacao2;

    vector<vector<double>> dadosEntradaTreinamento3;
    vector<vector<double>> dadosEntradaValidacao3;
    vector<vector<double>> saidasDesejadasTreinamento3;
    vector<vector<double>> saidasDesejadasValidacao3;
 
 

    lerCSV("Dados/dadosTreinamento2.csv", 5, 
            dadosEntradaTreinamento1, 
            saidasDesejadasTreinamento1);

    lerCSV("Dados/dadosValidacao2.csv", 5, 
            dadosEntradaValidacao1, 
            saidasDesejadasValidacao1);

    lerCSV("Dados/dadosTreinamento3.csv", 10, 
            dadosEntradaTreinamento2, 
            saidasDesejadasTreinamento2);

    lerCSV("Dados/dadosValidacao3.csv", 10, 
            dadosEntradaValidacao2, 
            saidasDesejadasValidacao2);


    lerCSV("Dados/dadosTreinamento4.csv", 15, 
            dadosEntradaTreinamento3, 
            saidasDesejadasTreinamento3);

    lerCSV("Dados/dadosValidacao4.csv", 15, 
            dadosEntradaValidacao3, 
            saidasDesejadasValidacao3);

    

    auto start = chrono::high_resolution_clock::now();

    for (int i = 0; i < 3; i++)
    {    
        printf("\nRede 5 entradas 10 ocultos\n");
        MLP rede1({5,10,1}, 0.1, 1, 0.5e-6, "sigmoide");

        rede1.treinar(dadosEntradaTreinamento1, 
                     saidasDesejadasTreinamento1, 
                     "erroMinimo", "momentum", 1.3e-5, i);
        rede1.testarRede(dadosEntradaValidacao1, 
                        saidasDesejadasValidacao1);


        printf("Rede 10 entradas 15 ocultos\n");
        MLP rede2({10,15,1}, 0.1, 1000, 0.5e-6, "sigmoide");

        rede2.treinar(dadosEntradaTreinamento2, 
                     saidasDesejadasTreinamento2, 
                     "erroMinimo", "momentum", 1.3e-5, i+3);
        rede2.testarRede(dadosEntradaValidacao2, 
                        saidasDesejadasValidacao2);


        printf("rede 15 entradas 25 ocultos\n");
        MLP rede3({15,25,1}, 0.1, 1000, 0.5e-6, "sigmoide");

        rede3.treinar(dadosEntradaTreinamento3, 
                     saidasDesejadasTreinamento3, 
                     "erroMinimo", "momentum", 1.3e-5, i+6);
        rede3.testarRede(dadosEntradaValidacao3, 
                        saidasDesejadasValidacao3);

        // printf("\n");

        
    }

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    printf("\nTempo de execução total: %.5f segundos\n", (double)(duration.count()/1e6));
    // :)
    //4.15 sweet spot
    return 0;
}















// modificarCSV("Dados/dadosBrutos.csv","dadosValidacao4.csv",15,1);



// rede.transferirPesos(rede.primeirosPesosCamadas);
// rede.reiniciarRede();

// printf("\n");

// auto start2 = chrono::high_resolution_clock::now();

// printf("Treinamento com a adição do Momentum:");
// rede.treinar(dadosEntradaTreinamento, 
//              saidasDesejadasTreinamento, 
//              "erroMinimo", "momentum", 4.15e-5, i+1);

// auto end2 = chrono::high_resolution_clock::now();
// auto duration2 = chrono::duration_cast<chrono::microseconds>(end2 - start2);
// printf("Tempo de execução total do segundo algoritmo: %.5f segundos\n", (double)(duration2.count()/1e6));

// rede.testarRede(dadosEntradaValidacao, 
//                 saidasDesejadasValidacao);
























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