#include "../include/RBF.h"

RBF::RBF(vector<int> estruturaRede, double taxaAprendizado,
         vector<vector<double>> &dadosEntrada, vector<vector<double>> &saidasDesejadas) :
         numEntradas(estruturaRede[0]), numNeuroniosOcultos(estruturaRede[1]), numSaidas(estruturaRede[2]),
         taxaAprendizado(taxaAprendizado), dadosEntrada(dadosEntrada), saidasDesejadas(saidasDesejadas),
         K(numEntradas, numNeuroniosOcultos, dadosEntrada)
{
    this->erroAtual = 0;
    this->somaErro  = 0;

    this->rede.resize(estruturaRede.size() - 1);

    for (size_t i = 1; i < estruturaRede.size(); i++) 
    {
        if (i == 1)
        {
            for (int j = 0; j < estruturaRede[i]; j++) this->rede[i-1].emplace_back(Neuronio(estruturaRede[i-1], "gaussiana"));
        }

        if (i == 2)
        {
            for (int j = 0; j < estruturaRede[i]; j++) this->rede[i-1].emplace_back(Neuronio(taxaAprendizado,estruturaRede[i-1], "gaussiana"));
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

void RBF::treinar(vector<vector<double>> &dadosEntrada, 
                  vector<vector<double>> &saidasDesejadas,
                  int numEpisodios, int IDtreinamento)
{
    aplicarKmeans();

    // for (int i = 0; i < numEpisodios; i++)
    // {
    //     int indiceDadoEntrada = 0;
    //     for (auto &dadoEntrada : dadosEntrada)
    //     {
    //         feedFoward(dadoEntrada);
    //         atualizarPesosSaida(dadoEntrada, saidasDesejadas[indiceDadoEntrada]);

    //         indiceDadoEntrada++;
    //     }
    // }
}

void RBF::testar(vector<vector<double>> &dadosEntrada, vector<vector<double>> &saidasDesejadas)
{
    printf("->Teste da Rede:\n");

    int saidaDesejadaCount = 0;
    for (vector<double> entrada : dadosEntrada)
    {
        feedFoward(entrada);
        calcularErro(this->saidasCamadas.back()[0], saidasDesejadas[saidaDesejadaCount][0]);

        printf(" *A saida é (%.4f) para um desejado de (%.4f), o que equivale a um erro de (%.6f)\n",
               this->saidasCamadas.back()[0], saidasDesejadas[saidaDesejadaCount][0], this->erroAtual);

        saidaDesejadaCount++;
    }
}
