#include "../include/MLP.h"
/*  
---------------{N1,Nx,...,No}----------------------------
N1: quantidade de entradas da rede.
Nx: quantidade de neurônios na camada oculta -> Ex. {..., a, b, ...}: a e b são camadas ocultas com Nx neurônios.
No: Número de saídas da rede, cada saída representa um neurônio.
---------------------------------------------------------
*/
MLP::MLP(vector<int> estruturaRede, float taxaAprendizado, 
         int numEpisodiosTotais, string funcAtiv) : taxaAprendizado(taxaAprendizado), numEpisodiosTotais(numEpisodiosTotais)
{
    // Monta o MLP em uma matriz
    this->numEntradas = estruturaRede.front();
    this->numSaidas   = estruturaRede.back();

    this->rede.resize(estruturaRede.size() - 1);

    for (size_t i = 1; i < estruturaRede.size(); i++) // Itera sobre a estrutura definida da rede
    {
        for (int j = 0; j < estruturaRede[i]; j++)    // Itera sobre os num de neurônios definidos para cada posição
        {
            this->rede[i-1].emplace_back(Neuronio(taxaAprendizado, estruturaRede[i-1], funcAtiv));
        }
    }
}

void MLP::inicializarPesosRede()
{//O atributo "rede" é uma matriz onde as linhas são as camadas e cada coluna representa um neurônio.
    for(size_t i = 0; i < this->rede.size(); i++) // Iteração sobre as camadas da rede
    {
        for(size_t j = 0; j < this->rede[i].size(); j++) // Iteração sobre os neurônios de uma camada
        {
            this->rede[i][j].inicializarPesos("random");
        }
    }
}

void MLP::feedFoward(vector<float> dadosEntrada)
{
    this->saidasCamadas.resize(this->rede.size()); 
    vector<float> entradaCamada;
    vector<float> saidasRede;

    entradaCamada = dadosEntrada;
    
    for (size_t i = 0; i < this->rede.size(); i++) // Iterar sobre as camadas da rede
    {
        entradaCamada.resize(this->rede[i][0].tamEntrada); // Para a entrada da camada se adecuar com a saída da camada anterior 
        // saidasRede.resize(this->rede[i].size()); 
        this->saidasCamadas[i].resize(this->rede[i].size()); 
        
        for (size_t j = 0; j < this->rede[i].size(); j++) // Itera sobre os neurônios da camada
        {
            this->rede[i][j].aplicarEntrada(entradaCamada);
            this->saidasCamadas[i][j] = this->rede[i][j].saida;
        }
        entradaCamada = saidasCamadas[i];
        // this->saidasCamadas[i].emplace_back(saidasRede);
    }
}

void MLP::mostrarSaidas()
{
    printf("\n");
    printf("Saídas de cada uma das camadas da rede:\n");
    for (size_t i = 0; i < this->saidasCamadas.size(); i++) 
    {
        printf(" ->Camada %zu:\n", i + 1);

        for (size_t j = 0; j < this->saidasCamadas[i].size(); j++) 
        {
            printf("   ->Y%zu: %.3f\n", j + 1, this->saidasCamadas[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void MLP::mostrarPesos()
{
    printf("\n");
    printf("Pesos de cada conexão dos neurônios:\n");
    // Itera sobre as camadas da rede
    for (size_t i = 0; i < this->rede.size(); i++)
    {
        printf(" ->Camada %zu:\n", i + 1);
        
        // Itera sobre os neurônios de uma camada
        for (size_t j = 0; j < this->rede[i].size(); j++)
        {
            printf("   ->Neurônio %zu:\n", j + 1);
            
            // Itera sobre os pesos do neurônio
            for (size_t a = 0; a < this->rede[i][j].pesos.size(); a++)
            {
                printf("     ->W%zu: %.3f\n", a + 1, this->rede[i][j].pesos[a]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

void MLP::backPropagation(vector<float> saidasDesejadas)
{
    /* 
    O backpropagation é dividido em duas partes:
        ->Atualização de pesos da camada de saída
        ->Atualização de pesos das camadas ocultas 
    */
    
    int numCalculoGradienteAtual = 1;

    for (size_t i = 0; i < this->numSaidas; i++) // Iteração sobre os neurônios de saída
    {
        rede.back()[i].calcularGradienteLocal(saidasDesejadas[i]);
        for (size_t j = 0; j < rede.back()[i].pesos.size(); j++)
        {
            rede.back()[i].pesos[j] = rede.back()[i].pesos[j] - 
                                      this->taxaAprendizado * 
                                      rede.back()[i].gradienteLocal * 
                                      this->saidasCamadas[saidasCamadas.size() - 2][i];
        }
    }

    for (size_t i = 0; i < (this->rede.size() - 1); i++)
    {
        calcularSomaGradiente(numCalculoGradienteAtual);
        for (Neuronio &ni : rede[rede.size() - numCalculoGradienteAtual - 1])
        {
            int numSaidaCount = 0;
            for (size_t j = 0; j < ni.pesos.size(); j++)
            {
                ni.pesos[j] = ni.pesos[j] - 
                              this->taxaAprendizado * 
                              (-ni.gradienteLocal) *
                              this->saidasCamadas[saidasCamadas.size() - 2 - numCalculoGradienteAtual][numSaidaCount];
                
                numSaidaCount++;
            }

        }
        numCalculoGradienteAtual++;
    }
}

void MLP::calcularSomaGradiente(int &numCalculoGradienteAtual)
{
    // size_t numCamadasOcultas = this->rede.size() - 1;
    int indiceNeuronioAnterior = 0;
    for (Neuronio &ni : rede[rede.size() - numCalculoGradienteAtual - 1])
    {
        for (Neuronio &nj : rede[rede.size() - numCalculoGradienteAtual])
        {
            ni.gradienteLocal += nj.gradienteLocal * nj.pesos[0 + indiceNeuronioAnterior];
        }
        ni.gradienteLocal *= ni.sigmoide(ni.somaEntradasPonderadas, true);

        indiceNeuronioAnterior++;
    }
}

void MLP::treinar(){}