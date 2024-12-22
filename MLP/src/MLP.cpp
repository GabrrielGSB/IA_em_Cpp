#include "../include/MLP.h"

namespace funcAux
{
    bool checarIndiceCamadaSaida(vector<vector<float>> &saidasCamadas, int &numCalculoGradienteAtual);
}

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

void MLP::inicializarPesosRede(string modo)
{//O atributo "rede" é uma matriz onde as linhas são as camadas e cada coluna representa um neurônio.
    for(size_t i = 0; i < this->rede.size(); i++) // Iteração sobre as camadas da rede
    {
        for(size_t j = 0; j < this->rede[i].size(); j++) // Iteração sobre os neurônios de uma camada
        {
            this->rede[i][j].inicializarPesos(modo);
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
                printf("     ->W%zu: %.8f\n", a + 1, this->rede[i][j].pesos[a]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

void MLP::backPropagation(vector<float> dadoEntrada, vector<float> saidaDesejada)
{
    /* 
    O backpropagation é dividido em duas partes:
        ->Atualização de pesos da camada de saída
        ->Atualização de pesos das camadas ocultas 
    */
    
    /* 
    numCalculoGradienteAtual: Número de cálculos de gradiente que serão feitos para as camadas ocultas.
     -> ele começa em 1, pois a primeira camada oculta é a penúltima camada da rede.
    count: Contador para iterar sobre as saídas desejadas.
     -> ele começa em 0, pois a primeira saída desejada é a primeira saída da rede.
    */
    int numCalculoGradienteAtual = 1;
    int count = 0;
   
    //---------------- Primeira Parte do BackPropagation -------------------------
    // Itera sobre os neurônios da camada de saída
    for (Neuronio &ni : rede.back())
    {
        bool pesoBias = true;

        calcularGradienteCamadaFinal(saidaDesejada[count]);

        //-------------- Atualização dos pesos da camada de saída ----------------
        // Itera sobre os pesos do neurônio
        for (float &peso : ni.pesos)
        {
            if (pesoBias)
            {
                peso = peso - 
                       this->taxaAprendizado * 
                       ni.gradienteLocal;
                pesoBias = false;
            }
            else
            peso = peso - 
                   this->taxaAprendizado * 
                   ni.gradienteLocal * 
                   this->saidasCamadas[saidasCamadas.size() - 2][count];
        }
        count++;
        //------------------------------------------------------------------------
    }
    //----------------------------------------------------------------------------

    //---------------- Segunda Parte do BackPropagation --------------------------
    //Itera sobre o número de camadas ocultas (todas menos a camada de saída)
    for (size_t i = 0; i < (this->rede.size() - 1); i++) 
    {
        // Calcula o gradiente local dos neurônios da camada oculta atual.
        calcularGradienteOculto(numCalculoGradienteAtual);

        //-------------- Atualização dos pesos das camadas ocultas ---------------
        // Itera sobre os neurônios da camada oculta atual
        for (Neuronio &ni : rede[rede.size() - numCalculoGradienteAtual - 1])
        {
            /*
            numSaidaCount: é usado para pegar a saída correta que liga o neurônio atual
            */
            int numSaidaCount = -1;
            bool pesoBias = true;

            for (float &peso : ni.pesos)
            {
                if (!pesoBias) numSaidaCount++;

                if (pesoBias)
                {
                    peso = peso - 
                           this->taxaAprendizado * 
                           -ni.gradienteLocal;
                    pesoBias = false;
                }
                else if (!funcAux::checarIndiceCamadaSaida(this->saidasCamadas, numCalculoGradienteAtual))
                {
                    peso = peso - 
                           this->taxaAprendizado * 
                           -ni.gradienteLocal    *
                           this->saidasCamadas[saidasCamadas.size() - 2 - numCalculoGradienteAtual][numSaidaCount];
                }
                else 
                {
                    peso = peso - 
                           this->taxaAprendizado * 
                           -ni.gradienteLocal    *
                           dadoEntrada[numSaidaCount];
                }
            }
        }
        //------------------------------------------------------------------------

        numCalculoGradienteAtual++;
    }
    //----------------------------------------------------------------------------
}

void MLP::calcularGradienteCamadaFinal(float saidaDesejada)
{
    for (Neuronio &ni : rede[rede.size() - 1])
    {
        ni.gradienteLocal = (saidaDesejada - ni.saida) * ni.sigmoide(ni.somaEntradasPonderadas, true);
    }
}

void MLP::calcularGradienteOculto(int &numCalculoGradienteAtual)
{    
    /*
    numCalculoGradienteAtual: é usado para pegar a camada oculta de acordo 
    com o número de cálculos de gradiente.
    */
    
    /*
    indicePeso: é usado para pegar o peso correto que liga o neurônio atual 
    com os neurônios da camada seguinte.
    */
    int indicePeso = 0;

    // ------- Calcula o gradiente local dos neurônios da camada oculta ----------
    // Itera sobre os neurônios das camada oculta
    for (Neuronio &ni : rede[rede.size() - numCalculoGradienteAtual - 1])
    {
        /*
        Somatório do 'gradiente local' dos neurônios da camada seguinte ponderado pelos pesos
        da conexão entre o neurônio atual e os neurônios da camada seguinte.
        */
        for (Neuronio &nj : rede[rede.size() - numCalculoGradienteAtual])
        {
            ni.gradienteLocal += nj.gradienteLocal * nj.pesos[1 + indicePeso];
        }
        ni.gradienteLocal *= ni.sigmoide(ni.somaEntradasPonderadas, true);

        indicePeso++;
    }
    //----------------------------------------------------------------------------
}

void MLP::treinar(){}

namespace funcAux
{
    bool checarIndiceCamadaSaida(vector<vector<float>> &saidasCamadas, int &numCalculoGradienteAtual)
    {
        size_t camadaSaidaIndex = saidasCamadas.size() - 2 - numCalculoGradienteAtual;

        if (camadaSaidaIndex >= saidasCamadas.size()) return true;
        else                                          return false;
    }
}