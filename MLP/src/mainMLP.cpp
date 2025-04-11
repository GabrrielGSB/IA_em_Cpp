#include "../include/MLP.h"
#include "../../Comum/include/myFuncoes.h"
#include <chrono>


int main()
{
        vector<vector<double>> dadosEntradaTreinamento1;
        vector<vector<double>> saidasDesejadasTreinamento1;
        

        lerCSV("Dados/csv_coluna3_ao_inicio.csv", 3, 
                dadosEntradaTreinamento1, 
                saidasDesejadasTreinamento1);

        // auto start = chrono::high_resolution_clock::now();


        MLP rede({3,10,10,10,1}, 0.0001, 200, 0.5e-6, "sigmoide");

        rede.treinar(dadosEntradaTreinamento1, 
                     saidasDesejadasTreinamento1, 
                     "numeroEpisodios", "", 1.3e-5, 0);

        rede.testarRede(dadosEntradaTreinamento1, 
                        saidasDesejadasTreinamento1);

//     auto end = chrono::high_resolution_clock::now();
//     auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
//     printf("\nTempo de execução total: %.5f segundos\n", (double)(duration.count()/1e6));
//     // :)
//     //4.15 sweet spot
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