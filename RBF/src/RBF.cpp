#include "../include/RBF.h"

RBF::RBF(vector<int> estruturaRede, double taxaAprendizado,
         vector<vector<double>> &dadosEntrada, vector<vector<double>> &saidasDesejadas) :
         numEntradas(estruturaRede[0]), numNeuroniosOcultos(estruturaRede[1]), numSaidas(estruturaRede[2]),
         taxaAprendizado(taxaAprendizado), dadosEntrada(dadosEntrada), saidasDesejadas(saidasDesejadas),
         K(estruturaRede[0], estruturaRede[1], dadosEntrada)
{
    this->erroAtual = 0;
    this->somaErro  = 0;
    this->variacaoErro = 1e5;
    this->erroQuadraticoMedio = 0;
    this->erroRelativoMedio = 0;
    this->numSaidasDesejadas = this->saidasDesejadas.size();
    
    this->erros.resize(this->numSaidasDesejadas * this->numSaidas);
    this->rede.resize(estruturaRede.size() - 1);

    for (size_t i = 1; i < estruturaRede.size(); i++) 
    {
        if (i == 1)
        {
            for (int j = 0; j < estruturaRede[i]; j++) this->rede[i-1].emplace_back(Neuronio(estruturaRede[i-1], "gaussiana"));
        }

        if (i == 2)
        {
            for (int j = 0; j < estruturaRede[i]; j++) this->rede[i-1].emplace_back(Neuronio(taxaAprendizado,estruturaRede[i-1], "linear"));
        }
    }

    this->saidasCamadas.resize(this->rede.size());
    
    int indiceCamada = 0;
    for (vector<Neuronio> &camada : this->rede)
    {
       this->saidasCamadas[indiceCamada].resize(camada.size());
       indiceCamada++;
    }
}

void RBF::inicializarPesosCamadaSaida(string modo)
{
    for (Neuronio &Ni: this->rede.back()) Ni.inicializarPesos(modo);
}

void RBF::aplicarKmeans()
{
    this->K.aplicarAlgoritmo();
    this->K.mostrarCentrosObtidos();
    this->K.mostrarVariancias();
}

void RBF::mostrarPesos()
{
    printf("\n");

    printf("*Pesos Camada Final\n");

    int neuronioCount = 1;  
    for (Neuronio &ni: this->rede.back()) 
    {
        printf(" ->Neurônio %d:\n", neuronioCount++);

        int pesoCount = 1;  
        for (double &peso : ni.pesos) 
        {
            if (pesoCount == 1) printf("  ->θ%d: %.8f\n", pesoCount++, peso);
            else                printf("  ->W%d: %.8f\n", pesoCount++, peso);
        }
    }
    printf("\n");
}

void RBF::feedFoward(vector<double> dadoEntrada)
{
    int indiceCamada = 0;
    for (vector<Neuronio> &camada : this->rede)
    {
        if (indiceCamada == 0)
        {
          
            int indiceNeuronio = 0;
            for (Neuronio &Ni : camada)
            {
                Ni.aplicarEntrada(dadoEntrada, K.centros[indiceNeuronio], K.variancias[indiceNeuronio]);
                this->saidasCamadas[indiceCamada][indiceNeuronio] = Ni.saida;

                indiceNeuronio++;
            }
        }

        if (indiceCamada == 1)
        {
            int indiceNeuronio = 0;
            for (Neuronio &Ni : camada)
            {
                Ni.aplicarEntrada(this->saidasCamadas[0]);
                this->saidasCamadas[indiceCamada][indiceNeuronio] = Ni.saida;

                indiceNeuronio++;
            } 
        }

        indiceCamada++;    
    }
}

void RBF::calcularErro(Neuronio &n, double &saidaDesejada)
{
    this->erroAtual = saidaDesejada - n.saida;
    this->somaErro += erroAtual;
}
void RBF::calcularErro(double &saida, double &saidaDesejada)
{
    this->erroAtual = saidaDesejada - saida;
    this->somaErro += erroAtual;
}

void RBF::calcularMediaErro()
{
    this->mediaErro = this->somaErro / (this->numSaidasDesejadas * this->numSaidas);
}

void RBF::calcularVarianciaErro()
{
    for (double erro : this->erros)
    {
        this->variancia += pow((erro - this->mediaErro), 2);
    }
    this->variancia /= (this->numSaidasDesejadas * this->numSaidas);

    this->variancia = sqrt(this->variancia);
    this->variancia /= this->mediaErro;
    this->variancia *= 100;
}

void RBF::calcularErroQuadraticoMedio()
{
    double erroQuadratico      = 0.5 * pow((this->erroAtual), 2);
    this->erroQuadraticoMedio += erroQuadratico / this->numSaidasDesejadas;
}

void RBF::calcularErroRelativoMedio(double &saida, double &saidaDesejada)
{
    this->erroRelativoMedio += abs((saida - saidaDesejada) / saida);   
}

void RBF::salvarErro()
{
    this->erros.push_back(this->erroAtual);
}

void RBF::salvarErroQuaMedCSV(string &nomeArquivo, vector<double> dadosErroQuadMed)
{
    salvarCSV(nomeArquivo, "Erro Quadrático Médio/Época", dadosErroQuadMed);
}


void RBF::calcularGradienteSaida(Neuronio &n)
{
    n.gradienteLocal = (this->erroAtual) * 1;
}

void RBF::atualizarPesosSaida(vector<double> dadoEntrada, vector<double> saidaDesejada)
{
    int indiceNeuronio = 0;
    for (Neuronio &Ni : this->rede.back())
    {
        calcularErro(Ni, saidaDesejada[indiceNeuronio]);
        salvarErro();

        calcularErroQuadraticoMedio();
        calcularGradienteSaida(Ni);

        bool pesoBias = true;
       
        int indicePeso = 0;
        for (double &peso : Ni.pesos)
        {
            if (pesoBias)
            {
                peso = peso + 
                       this->taxaAprendizado * 
                       Ni.gradienteLocal;

                pesoBias = false;
            }
            else
            {
                peso = peso + 
                       this->taxaAprendizado * 
                       Ni.gradienteLocal * 
                       this->saidasCamadas[saidasCamadas.size() - 2][indicePeso]; 

                indicePeso++;
            }
        }
        indiceNeuronio++;
    }
}

void RBF::treinarPorNumEpisodios(int numEpisodios)
{
    aplicarKmeans();
 
    for (int i = 0; i < numEpisodios; i++)
    {
        int indiceDadoEntrada = 0;
        for (auto &dadoEntrada : this->dadosEntrada)
        {
            feedFoward(dadoEntrada);
            atualizarPesosSaida(dadoEntrada, this->saidasDesejadas[indiceDadoEntrada]);

            indiceDadoEntrada++;
        }
    }
}

void RBF::treinarPorErroMinimo(double erroMinimo, int IDtreinamento)
{
    aplicarKmeans();
 
    vector<double> errosQuadraticosMedios = {};

    int episodioCount = 0;
    while(this->variacaoErro >= erroMinimo)
    {
        double erroQuadraticoMedioOld = this->erroQuadraticoMedio;
        this->erroQuadraticoMedio = 0;

        int indiceDado = 0;
        for (auto &dadoEntrada : this->dadosEntrada)
        {
            feedFoward(dadoEntrada);
            atualizarPesosSaida(dadoEntrada, this->saidasDesejadas[indiceDado]);

            indiceDado++;
        }

        this->variacaoErro = abs(this->erroQuadraticoMedio - erroQuadraticoMedioOld);

        errosQuadraticosMedios.push_back(this->erroQuadraticoMedio);
        
        episodioCount++;
        
        if (episodioCount >= 20e3) break;
    }

    string nomeArquivo = "ErroQuadMed(" + to_string(IDtreinamento) + ")" + ".csv";
    salvarErroQuaMedCSV(nomeArquivo, errosQuadraticosMedios);

    printf("\n");
    printf(" -> Treinamento terminou em %d episódios\n", episodioCount);
    printf(" -> Erro quadrático médio final: %.6f\n", this->erroQuadraticoMedio);
    printf(" -> Variação do erro final: %.12f\n", this->variacaoErro);
}

void RBF::testar(vector<vector<double>> dadosEntrada, vector<vector<double>> saidasDesejadas)
{
    this->erroRelativoMedio = 0;
    this->erroAtual = 0;
    this->somaErro  = 0;
    this->variancia = 0;
    this->mediaErro = 0;

    this->numSaidasDesejadas = saidasDesejadas.size();

    this->erros.clear();
    this->erros.resize(this->numSaidasDesejadas * this->numSaidas);

    printf("*Teste da Rede:\n");

    int saidaPosProcessada = 0;
    int saidaDesejadaCount = 0;
    int acertos = 0;

    for (vector<double> entrada : dadosEntrada)
    {
        feedFoward(entrada);
        calcularErro(this->saidasCamadas.back()[0], saidasDesejadas[saidaDesejadaCount][0]);
        calcularErroRelativoMedio(this->saidasCamadas.back()[0], saidasDesejadas[saidaDesejadaCount][0]);
        salvarErro();

        printf(" *A saida é (%.4f) para um desejado de (%.4f), o que equivale a um erro de (%.6f)\n",
               this->saidasCamadas.back()[0], saidasDesejadas[saidaDesejadaCount][0], this->erroAtual);

        saidaDesejadaCount++;
        // if (this->saidasCamadas.back()[0] > 0) saidaPosProcessada =  1;
        // else                                   saidaPosProcessada = -1;

        // if (saidaPosProcessada == int(saidasDesejadas[saidaDesejadaCount][0])) acertos++;
        // printf("%d %d\n",acertos,  int(saidasDesejadas.size()));
        

        // printf(" ->A saida é (%.4f/%d) para um desejado de (%.1f)\n",
        //        this->saidasCamadas.back()[0], saidaPosProcessada, saidasDesejadas[saidaDesejadaCount][0]);
    }

    this->erroRelativoMedio /= this->numSaidasDesejadas;
    this->erroRelativoMedio *= 100;

    calcularMediaErro();
    calcularVarianciaErro();

    printf("\n");
    printf("  -> Erro Relativo Médio é: %.2f%% \n", this->erroRelativoMedio);
    printf("  -> A média do erro é: %.4f \n",       this->mediaErro);
    printf("  -> A variância do erro é: %4f \n",    this->variancia);
    printf("\n");
    printf("\n");

    // printf("\n");
    // printf("A taxa de acertos final foi de %.4f %%\n", (float(acertos)/float(saidasDesejadas.size())*100));
}
