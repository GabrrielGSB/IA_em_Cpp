#include "../include/MLP.h"

namespace funcAux
{
    bool checarIndiceCamadaSaida(vector<vector<double>> &saidasCamadas, int &numCalculoGradienteAtual);
    void print3DMatrix(const std::vector<std::vector<std::vector<double>>>& matrix);
}

/*  
---------------{N1,Nx,...,No}----------------------------
N1: quantidade de entradas da rede.
Nx: quantidade de neurônios na camada oculta -> Ex. {..., a, b, ...}: a e b são camadas ocultas com Nx neurônios.
No: Número de saídas da rede, cada saída representa um neurônio.
---------------------------------------------------------
*/

MLP::MLP(vector<int> estruturaRede, double taxaAprendizado, 
         int numEpisodiosTotais, double erroMinimo, string funcAtiv) : 
         taxaAprendizado(taxaAprendizado), 
         erroMinimo(erroMinimo),
         numEpisodiosTotais(numEpisodiosTotais)
{
    this->erroQuadratico = 0;
    this->erroQuadraticoMedio = 0;
    this->variacaoErro = 1;
    this->erroRelativoMedio = 0;
    this->somaErro = 0;
    this->variacaoErro = 1;
    this->erroCount = 0;
    this->momentum = 0;

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

void MLP::mostrarSaida(vector<double> entradaAtual)
{
    /*
    Função para mostrar a saída de uma determinada entrada
    */

    printf("\n");
    printf(" *Entradas atuais:\n");

    int entradaCount = 0;
    for (double dadoEntrada : entradaAtual) printf("  ->Entrada %d: %.4f \n", entradaCount++, dadoEntrada);

    printf(" *Saídas final da rede:\n");

    int saidaCount = 0;
    for (double saida : this->saidasCamadas.back()) printf("  ->Y%d: %.4f \n", saidaCount, saida);

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
            for (double &peso : ni.pesos) 
            {
                printf("     ->W%d: %.8f\n", pesoCount++, peso);
            }
        }
        printf("\n");
    }
    printf("\n");
}

void MLP::calcularErro(Neuronio &n, double &saidaDesejada)
{
    this->erroAtual = saidaDesejada - n.saida;
    this->somaErro += erroAtual;
}

void MLP::calcularErro(double &saida, double &saidaDesejada)
{
    this->erroAtual = saidaDesejada - saida;
    this->somaErro += erroAtual;
}

void MLP::calcularMediaErro()
{
    this->mediaErro = this->somaErro / (this->numDados * this->numSaidas);
}

void MLP::calcularErroQuadratico()
{
    this->erroQuadratico += 0.5 * pow((this->erroAtual), 2);
}

void MLP::calcularErroQuadraticoMedio(double erroQuadratico, size_t numDados)
{
    this->erroQuadraticoMedio += erroQuadratico / numDados;
    this->erroQuadratico = 0;
}

void MLP::calcularErroRelativoMedio(vector<double> &saidaDesejada)
{
    /*
    Aplicação do cálculo Erro Absoluto Percentual Médio (MAPE) nos dados de validação.
    */
    // --------------------- Loop de Cálculo da Precisão -----------------------
    for (size_t j = 0; j < saidaDesejada.size(); j++)
    {
        this->erroRelativoMedio += abs((this->saidasCamadas.back()[j] - saidaDesejada[j]) / this->saidasCamadas.back()[j]);
    }
    //------------------------------------------------------------------
}

void MLP::calcularVarianciaErro()
{
    for (double erro : this->erros)
    {
        this->variancia += pow((erro - this->mediaErro), 2);
    }
    this->variancia /= (this->numDados * this->numSaidas);
    printf("Variância do erro: %.5f\n", variancia);
}

void MLP::calcularGradienteNeuronioFinal(Neuronio &n)
{
    n.gradienteLocal = (this->erroAtual) * n.sigmoide(n.somaEntradasPonderadas, true);
}

void MLP::calcularGradienteNeuronioOculto(int &numCalculoGradienteAtual)
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

void MLP::feedFoward(vector<double> dadosEntrada)
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

void MLP::backPropagation(vector<double> dadoEntrada, vector<double> saidaDesejada, string mode)
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
    this->erroCount = 0;

    if (mode == "" || mode == "classico")
    {
        //------------ Primeira Parte do BackPropagation (clássico)-------------------
        int neuronioCount = 0;
        for (Neuronio &ni : this->rede.back())
        {
            calcularErro(ni, saidaDesejada[neuronioCount]);
            salvarErro();

            calcularErroQuadratico();
            
            calcularGradienteNeuronioFinal(ni);

            bool pesoBias = true;

            //-------------- Atualização dos pesos da camada de saída ----------------
            // Itera sobre os pesos do neurônio
            int pesoCount = 0;
            for (double &peso : ni.pesos)
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
            this->erroCount++;
        }
        calcularErroQuadraticoMedio(this->erroQuadratico, this->numDados);
        //----------------------------------------------------------------------------
        
        //------------ Segunda Parte do BackPropagation (clássico) ------------------
        //Itera sobre o número de camadas ocultas (todas menos a camada de saída)
        for (size_t i = 0; i < (this->rede.size() - 1); i++) 
        {
            calcularGradienteNeuronioOculto(numCalculoGradienteAtual);

            //-------------- Atualização dos pesos das camadas ocultas ---------------
            for (Neuronio &ni : this->rede[this->rede.size() - numCalculoGradienteAtual - 1])
            {
                /*
                numSaidaCount: é usado para pegar a saída correta que liga o neurônio atual
                */
                int numSaidaCount = -1;
                bool pesoBias = true;

                for (double &peso : ni.pesos)
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

    if (mode == "momentum")
    {
        //------------ Primeira Parte do BackPropagation (momentum)-------------------
        int neuronioCount = 0;
        for (Neuronio &ni : this->rede.back())
        {
            calcularErro(ni, saidaDesejada[neuronioCount]);
            salvarErro();

            calcularErroQuadratico();
            
            calcularGradienteNeuronioFinal(ni);

            bool pesoBias = true;

            //-------------- Atualização dos pesos da camada de saída ----------------
            // Itera sobre os pesos do neurônio
            int pesoCount = 0;
            for (double &peso : ni.pesos)
            {
                if (pesoBias)
                {
                    peso = peso + 
                           (this->momentum * (peso - this->pesosCamadasOld.back()[neuronioCount][pesoCount])) -
                           this->taxaAprendizado * ni.gradienteLocal;

                    pesoBias = false;
                }
                else
                {
                    // printf("Peso: %.4f (%d)(%d)\n", this->pesosCamadasOld.back()[neuronioCount][pesoCount], neuronioCount, pesoCount);
                    peso = peso + 
                           (this->momentum * (peso - this->pesosCamadasOld.back()[neuronioCount][pesoCount])) -
                           this->saidasCamadas[saidasCamadas.size() - 2][pesoCount]; 

                    pesoCount++;
                }
            }
            //------------------------------------------------------------------------
            neuronioCount++;
            this->erroCount++;
        }
        calcularErroQuadraticoMedio(this->erroQuadratico, this->numDados);
        //----------------------------------------------------------------------------

        //------------ Segunda Parte do BackPropagation (momentum) ------------------
        //Itera sobre o número de camadas ocultas (todas menos a camada de saída)
        for (size_t i = 0; i < (this->rede.size() - 1); i++) 
        {
            calcularGradienteNeuronioOculto(numCalculoGradienteAtual);

            //-------------- Atualização dos pesos das camadas ocultas ---------------
            int neuronioCount = 0;
            for (Neuronio &ni : this->rede[this->rede.size() - numCalculoGradienteAtual - 1])
            {
                /*
                numSaidaCount: é usado para pegar a saída correta que liga o neurônio atual
                */
                int numSaidaCount = -1;
                bool pesoBias = true;

                int pesoCount = 0;
                for (double &peso : ni.pesos)
                {
                    if (!pesoBias) numSaidaCount++;

                    if (pesoBias)
                    {
                        peso = peso +
                               this->momentum * (peso - pesosCamadasOld[this->rede.size()-2-i][neuronioCount][pesoCount]) - 
                               this->taxaAprendizado *
                               ni.gradienteLocal;
                        
                        pesoBias = false;
                    }
                    else if (funcAux::checarIndiceCamadaSaida(this->saidasCamadas, numCalculoGradienteAtual))
                    {
                        peso = peso +
                               this->momentum * (peso - pesosCamadasOld[this->rede.size()-2-i][neuronioCount][pesoCount]) - 
                               this->taxaAprendizado * 
                               ni.gradienteLocal     *
                               this->saidasCamadas[saidasCamadas.size() - 2 - numCalculoGradienteAtual][numSaidaCount];
                    }
                    else 
                    {
                        peso = peso + 
                               this->momentum * (peso - pesosCamadasOld[this->rede.size()-2-i][neuronioCount][pesoCount]) - 
                               this->taxaAprendizado * 
                               ni.gradienteLocal     *
                               dadoEntrada[numSaidaCount];
                    }
                    pesoCount++;
                }
                neuronioCount++;
            }
            //------------------------------------------------------------------------

            numCalculoGradienteAtual++;
        }
        //----------------------------------------------------------------------------
        
        salvarPesos();
    }
}

void MLP::treinar(vector<vector<double>> &dadosEntrada, 
                  vector<vector<double>> &saidasDesejadas,
                  string mode, string backPropagationMode,
                  double momentum)
{
    this->momentum = momentum;
    this->numDados = dadosEntrada.size();
    this->erros.resize(this->numDados * this->numSaidas);   
    bool atualizarMatrizPesos = false;

    salvarPesos();
    this->pesosCamadasOld = this->pesosCamadas;
    vector<vector<vector<double>>> pesosCamadasTemp = pesosCamadasOld;


    // --------------------- Loop de treinamento -----------------------
    // Itera sobre o número de episódios totais
    if (mode == "numeroEpisodios")
    {
        for (int i = 0; i < this->numEpisodiosTotais; i++)
        {
            // Itera sobre os dados de entrada
            for (size_t j = 0; j < dadosEntrada.size(); j++)
            {
                feedFoward(dadosEntrada[j]);
                backPropagation(dadosEntrada[j], saidasDesejadas[j], backPropagationMode);

                pesosCamadasTemp = this->pesosCamadas;
                
                if (atualizarMatrizPesos == true) this->pesosCamadasOld = pesosCamadasTemp;
                else                              atualizarMatrizPesos = true;
            }
        }
    }
    else if (mode  == "erroMinimo")
    {
        vector<double> dadosErroQuadMed = {};

        int episodioCount = 0;
        while(this->variacaoErro >= this->erroMinimo)
        {
            double erroQuadraticoMedioOld = this->erroQuadraticoMedio;
            this->erroQuadraticoMedio = 0;

            this->erroCount = 0;
            for (size_t j = 0; j < dadosEntrada.size(); j++)
            {
                feedFoward(dadosEntrada[j]);
                backPropagation(dadosEntrada[j], saidasDesejadas[j], backPropagationMode);

                pesosCamadasTemp = this->pesosCamadas;
                if (atualizarMatrizPesos == true) pesosCamadasOld = pesosCamadasTemp;
                else                             atualizarMatrizPesos = true;
            funcAux::print3DMatrix(this->pesosCamadas);
            }

            this->variacaoErro = abs(this->erroQuadraticoMedio - erroQuadraticoMedioOld);

            dadosErroQuadMed.push_back(this->erroQuadraticoMedio);

            episodioCount++;

        if (episodioCount >= 5e3) break;
        }

        // string nomeArquivo = "ErroQuadMed(" + to_string(IDtreinamento) + ")" + ".csv";
        // salvarErroQuaMedCSV(nomeArquivo, dadosErroQuadMed);
        
        printf("\nTreinamento terminou em %d episódios\n", episodioCount);
        calcularVarianciaErro();
    }
    //------------------------------------------------------------------
}

void MLP::testarRede(vector<vector<double>> &dadosEntrada, vector<vector<double>> &saidasDesejadas)
{
    this->erroAtual = 0;
    this->somaErro  = 0;
    this->mediaErro = 0;

    this->numDados = saidasDesejadas.size();

    this->erros.resize(numDados * this->numSaidas);

    // --------------------- Loop de teste -----------------------
    int saidaDesejadaCount = 0;
    printf("\nTeste da Rede:\n");
    // Itera sobre os dados de entrada
    for (vector<double> entrada : dadosEntrada)
    {
        feedFoward(entrada);

        calcularErro(this->saidasCamadas.back()[0], saidasDesejadas[saidaDesejadaCount][0]);
        salvarErro(saidaDesejadaCount);

        mostrarSaida(entrada);

        calcularErroRelativoMedio(saidasDesejadas[saidaDesejadaCount]);
        saidaDesejadaCount++;
    }
    //------------------------------------------------------------------
    this->erroRelativoMedio *= 100;
    this->erroRelativoMedio /= this->numDados;

    calcularMediaErro();
    calcularVarianciaErro();

    printf("Erro Relativo Médio do Conjunto de Validação: %.4f%% \n", this->erroRelativoMedio);
}

void MLP::salvarPesos()
{
    this->pesosCamadas.resize(this->rede.size());

    int camadaCount = 0;
    for (vector<Neuronio> &camada : this->rede) 
    {
        this->pesosCamadas[camadaCount].resize(camada.size());

        int neuronioCount = 0;
        for (Neuronio &ni : camada)
        {
            this->pesosCamadas[camadaCount][neuronioCount] = ni.pesos;
            neuronioCount++;
        }
        camadaCount++;
    }
}

void MLP::salvarErro()
{
    this->erros[this->erroCount] = this->erroAtual;
}

void MLP::salvarErro(int erroCount)
{
    this->erros[erroCount] = this->erroAtual;
}

void MLP::salvarErroCSV(int episodioCount)
{
    string nomeArquivo = "Erros(" + to_string(episodioCount) + ")" + ".csv";
    salvarCSV(nomeArquivo, "Erros", this->erros);
}

void MLP::salvarErroQuaMedCSV(string &nomeArquivo, vector<double> dadosErroQuadMed)
{
    salvarCSV(nomeArquivo, "Erro Quadrático Médio/Época", dadosErroQuadMed);
}

namespace funcAux
{
    bool checarIndiceCamadaSaida(vector<vector<double>> &saidasCamadas, int &numCalculoGradienteAtual)
    {
        /*
        Checa se a camada atual, para atualização de pesos, é a primeira camada oculta.
        */
        size_t camadaSaidaIndex = saidasCamadas.size() - 2 - numCalculoGradienteAtual;

        if (camadaSaidaIndex >= saidasCamadas.size()) return false; // Primeira camada oculta
        else                                          return true;  // Camadas ocultas seguintes
    }

    void print3DMatrix(const std::vector<std::vector<std::vector<double>>>& matrix) 
    {
        for (size_t i = 0; i < matrix.size(); ++i) 
        {
            std::cout << "Layer " << i << ":\n";
            for (size_t j = 0; j < matrix[i].size(); ++j) 
            {
                for (size_t k = 0; k < matrix[i][j].size(); ++k) 
                {
                    std::cout << matrix[i][j][k] << " ";
                }
                std::cout << "\n";
            }
            std::cout << "----------\n";
        }
    }
}