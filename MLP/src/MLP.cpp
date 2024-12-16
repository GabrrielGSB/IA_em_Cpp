#include "../include/MLP.h"
/*  
---------------{N1,Nx,...,No}----------------------------
N1: quantidade de entradas da rede
Nx: quantidade de neurônios na camada oculta
{..., a, b, ...}: a e b são camadas ocultas com Nx neurônios
No: Número de saídas da rede
---------------------------------------------------------
*/

MLP::MLP(vector<int> estruturaRede, float taxaAprendizado, 
         int numEpisodiosTotais, string funcAtiv) : numEpisodiosTotais(numEpisodiosTotais)
{
    // Monta o MLP em uma matriz
    this->numEntradas = estruturaRede.front();
    this->numSaidas   = estruturaRede.back();

    for (int i = 1; i < estruturaRede.size(); i++)
    {
        for (int j = 0; j < estruturaRede[i]; j++) 
        {
            this->rede[i-1].emplace_back(Neuronio(taxaAprendizado, estruturaRede[i-1], funcAtiv));
        }
    }
}

//O atributo "rede" é uma matriz onde as linhas são as camadas e cada coluna representa um neurônio.
void MLP::inicializarRede()
{
    for(int i = 0; i < rede.size(); i++) // Iteração sobre as camadas da rede
    {
        for(int j = 0; j < rede[i].size(); i++) // Iteração sobre os neurônios de uma camada
        {
            rede[i][j].inicializarPesos("random");
        }
    }
}

void MLP::feedFoward(vector<float> dadosEntrada)
{

}

void MLP::backPropagation(){}

void MLP::calcularErroQuad(){}

void MLP::calcularErroQuadMed(){}

void MLP::atualizarPesos(){}

void MLP::treinar(){}