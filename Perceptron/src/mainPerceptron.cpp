
#include "../../Comum/include/Neuronio.h"
#include "../include/Perceptron.h"
#include "../../Comum/include/myFuncoes.h"

int main()
{
    Perceptron p(10000, 0.01, 3, "degrau");

    const char* caminhoDados = getenv("DADOS_TREINAMENTO");

    if (caminhoDados == nullptr) {
        printf("\nA variavel de ambiente DADOS_TREINAMENTO nao esta configurada!\n");
        return 1;
    }

    string caminhoDadosTreinamento = string(caminhoDados) + "/dados_treinamento.csv";
    string caminhoDadosValidacao   = string(caminhoDados) + "/dados_validacao.csv";
    
    cout << "\nCaminho para os dados de treinamento: " << caminhoDadosTreinamento << endl;
    cout << "Caminho para os dados de validacao: "   << caminhoDadosValidacao   << endl;

    //Treinamento------------------------------------------------------------
    vector<vector<float>> dadosEntrada, dadosEntradaValid;
    vector<float>         saidasDesejadas, saidasDesejadasValid;
    lerCSV(caminhoDadosTreinamento, 3, dadosEntrada, saidasDesejadas);

    p.treinar(dadosEntrada, saidasDesejadas);

    p.mostrarResultados(dadosEntrada, saidasDesejadas);
    p.mostrarPesos();

    printf("\nTreinamento terminou! em %d episodios", p.numEpisodiosAtual);
    //-----------------------------------------------------------------------

    //Validação--------------------------------------------------------------
    lerCSV(caminhoDadosValidacao, 3, dadosEntradaValid, saidasDesejadasValid);
    p.mostrarResultados(dadosEntradaValid, saidasDesejadasValid);
    //-----------------------------------------------------------------------

    return 0;
}