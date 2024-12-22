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
         int numEpisodiosTotais, float erroMinimo, string funcAtiv) : 
         taxaAprendizado(taxaAprendizado), 
         erroMinimo(erroMinimo),
         numEpisodiosTotais(numEpisodiosTotais)
{
    /*
    Esse constrututor (MLP) inicializa a rede com a estrutura definida pelo usuário,
    defininfo a taxa de aprendizado e a função de ativação.
    */
    this->numEntradas = estruturaRede.front();
    this->numSaidas   = estruturaRede.back();

    /* 
    Reestrutura a rede o número de camadas correto (iguinorando a camada de entrada,
    pois ela não é uma camada de neurônios).
    */
    this->rede.resize(estruturaRede.size() - 1);

    // ------------------ Inicialização da rede ---------------------
    // Itera sobre a estrutura definida da rede
    for (size_t i = 1; i < estruturaRede.size(); i++) 
    {
        // Itera sobre os num de neurônios definidos para cada posição
        for (int j = 0; j < estruturaRede[i]; j++)    
        {
            this->rede[i-1].emplace_back(Neuronio(taxaAprendizado, estruturaRede[i-1], funcAtiv));
        }
    }
    //----------------------------------------------------------------
}

void MLP::inicializarPesosRede(string modo)
{
    /*
    Função utilizada para inicializar os pesos de forma
    diferênte caso o usuário deseje, uma vez que os pesos
    já são inicializados na construção do neurônio.
    */

    // Iteração sobre as camadas da rede
    for (vector<Neuronio> &camada : this->rede) 
    {
        // Iteração sobre os neurônios de uma camada
        for (Neuronio &ni: camada) 
        {
            ni.inicializarPesos(modo);
        }
    }
}

void MLP::feedFoward(vector<float> dadosEntrada)
{
    /*
    Função para aplicar os dados de entrada na rede e calcular
    a saída respectiva de cada neurônio, guardando esses valores,
    para uso no backpropagation.
    */

    //Redimenciona a matriz de saídas para se adequar com a rede.
    this->saidasCamadas.resize(this->rede.size()); 
    
    int camadasCount = 0;
    for (vector<Neuronio> &camada : this->rede) 
    {
        /*
        Redimensionamento da lista de saídas de uma camada
        para se adequar com número de neurônios da camada.
        */
        this->saidasCamadas[camadasCount].resize(camada.size());

        int saidaCount = 0;
        for (Neuronio &ni : camada)
        {
            ni.aplicarEntrada(dadosEntrada);
            this->saidasCamadas[camadasCount][saidaCount] = ni.saida;
            
            saidaCount++;
        } 
        dadosEntrada = this->saidasCamadas[camadasCount];

        camadasCount++;
    }
}

void MLP::mostrarSaida(vector<float> entradaAtual)
{
    /*
    Função para mostrar a saída de uma determinada entrada
    */

    printf("\n");
    printf("Entradas atuais:\n");

    int entradaCount = 0;
    for (float dadoEntrada : entradaAtual) printf(" ->Entrada %d: %.3f \n", entradaCount++, dadoEntrada);

    printf("Saídas final da rede:\n");

    int saidaCount = 0;
    for (float saida : this->saidasCamadas.back()) printf(" ->Y%d: %.3f \n", saidaCount, saida);

    printf("\n");
}

void MLP::mostrarPesos()
{
    printf("\n");
    printf("Pesos de cada conexão dos neurônios:\n");

    int camadaCount = 1;  
    for (vector<Neuronio> &camada : this->rede) 
    {
        printf(" ->Camada %d:\n", camadaCount++);

        int neuronioCount = 1;  
        for (Neuronio &ni: camada) 
        {
            printf("   ->Neurônio %d:\n", neuronioCount++);

            int pesoCount = 1;  
            for (float &peso : ni.pesos) 
            {
                printf("     ->W%d: %.8f\n", pesoCount++, peso);
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
     -> tem o propósito de pegar a camada oculta correta de acordo com o número de cálculos de gradiente.
    */
    int numCalculoGradienteAtual = 1;
    
    //---------------- Primeira Parte do BackPropagation -------------------------
    int neuronioCount = 0;
    for (Neuronio &ni : this->rede.back())
    {
        bool pesoBias = true;

        calcularGradienteCamadaFinal(saidaDesejada[neuronioCount]);

        //-------------- Atualização dos pesos da camada de saída ----------------
        // Itera sobre os pesos do neurônio
        int pesoCount = 0;
        for (float &peso : ni.pesos)
        {
            if (pesoBias)
            {
                peso = peso + 
                       this->taxaAprendizado * 
                       ni.gradienteLocal;
                pesoBias = false;
            }
            else
            {
                peso = peso + 
                       this->taxaAprendizado * 
                       ni.gradienteLocal * 
                       this->saidasCamadas[saidasCamadas.size() - 2][pesoCount]; 

                pesoCount++;
            }
        }
        //------------------------------------------------------------------------
        neuronioCount++;
    }
    //----------------------------------------------------------------------------

    //---------------- Segunda Parte do BackPropagation --------------------------
    //Itera sobre o número de camadas ocultas (todas menos a camada de saída)
    for (size_t i = 0; i < (this->rede.size() - 1); i++) 
    {
        calcularGradienteOculto(numCalculoGradienteAtual);

        //-------------- Atualização dos pesos das camadas ocultas ---------------
        for (Neuronio &ni : this->rede[this->rede.size() - numCalculoGradienteAtual - 1])
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
                    peso = peso +
                           this->taxaAprendizado * 
                           ni.gradienteLocal;
                    pesoBias = false;
                }
                else if (funcAux::checarIndiceCamadaSaida(this->saidasCamadas, numCalculoGradienteAtual))
                {
                    peso = peso + 
                           this->taxaAprendizado * 
                           ni.gradienteLocal     *
                           this->saidasCamadas[saidasCamadas.size() - 2 - numCalculoGradienteAtual][numSaidaCount];
                }
                else 
                {
                    peso = peso + 
                           this->taxaAprendizado * 
                           ni.gradienteLocal     *
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
    for (Neuronio &ni : rede.back())
    {
        ni.gradienteLocal = (saidaDesejada - ni.saida) * ni.sigmoide(ni.somaEntradasPonderadas, true);
        // printf("erro: %.3f\n", (saidaDesejada - ni.saida));
    }
}

void MLP::calcularGradienteOculto(int &numCalculoGradienteAtual)
{    
    /*
    numCalculoGradienteAtual: é usado para pegar a camada oculta de acordo 
    com o número de cálculos de gradiente (começa em 1).
    */
    
    // ------- Calcula o gradiente local dos neurônios da camada oculta ----------
     /*
    indicePeso: é usado para pegar o peso correto que liga o neurônio atual 
    com os neurônios da camada seguinte.
    */
    int indicePeso = 0;

    // Itera sobre os neurônios das camadas ocultas
    for (Neuronio &n_atual : rede[rede.size() - numCalculoGradienteAtual - 1])
    {
        /*
        Somatório do 'gradiente local' dos neurônios da camada seguinte ponderado pelos pesos
        da conexão entre o neurônio atual e os neurônios da camada seguinte.
        */

        n_atual.gradienteLocal = 0;

        for (Neuronio &n_prox : rede[rede.size() - numCalculoGradienteAtual])
        {
            n_atual.gradienteLocal += n_prox.gradienteLocal * n_prox.pesos[1 + indicePeso];
        }

        n_atual.gradienteLocal *= n_atual.sigmoide(n_atual.somaEntradasPonderadas, true);

        indicePeso++;
    }
    //----------------------------------------------------------------------------
}

void MLP::treinar(vector<vector<float>> &dadosEntrada, 
                  vector<vector<float>> &saidasDesejadas,
                  string mode)
{
    
    // --------------------- Loop de treinamento -----------------------
    // Itera sobre o número de episódios totais
    if (mode == "numeroEpisodios")
    {
        for (int i = 0; i < this->numEpisodiosTotais; i++)
        {
            // printf("Episódio: %d\n", i + 1);

            // Itera sobre os dados de entrada
            for (size_t j = 0; j < dadosEntrada.size(); j++)
            {
                feedFoward(dadosEntrada[j]);
                backPropagation(dadosEntrada[j], saidasDesejadas[j]);
            }
        }
    }
    else if (mode  == "erroMinimo")
    {
    }
    
    //------------------------------------------------------------------

}

void MLP::testarRede(vector<vector<float>> &dadosEntrada, vector<vector<float>> &saidasDesejadas)
{
    // --------------------- Loop de teste -----------------------
    // Itera sobre os dados de entrada
    for (vector<float> entrada : dadosEntrada)
    {
        feedFoward(entrada);
        // mostrarSaida(entrada);
    }
    //------------------------------------------------------------------
    
}


namespace funcAux
{
    bool checarIndiceCamadaSaida(vector<vector<float>> &saidasCamadas, int &numCalculoGradienteAtual)
    {
        /*
        Checa se a camada atual, para atualização de pesos, é a primeira camada oculta.
        */
        size_t camadaSaidaIndex = saidasCamadas.size() - 2 - numCalculoGradienteAtual;

        if (camadaSaidaIndex >= saidasCamadas.size()) return false; // Primeira camada oculta
        else                                          return true;  // Camadas ocultas seguintes
    }
}