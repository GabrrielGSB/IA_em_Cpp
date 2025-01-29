#include "../include/RBF.h"

RBF::RBF(int numEntradas, int numNeuroniosOcultos, int numSaidas, double taxaAprendizado,
         vector<vector<double>> &dadosEntrada, vector<vector<double>> &saidasDesejadas) :
         K(numEntradas, numNeuroniosOcultos, dadosEntrada), 
         numNeuroniosOcultos(numNeuroniosOcultos), numSaidas(numSaidas), taxaAprendizado(taxaAprendizado),
         dadosEntrada(dadosEntrada), saidasDesejadas(saidasDesejadas)
{
    this->saidasCamadasOcultas.resize(numNeuroniosOcultos);
    this->saidas.resize(dadosEntrada.size());

    this->erroAtual = 0;
    this->somaErro  = 0;
}

void RBF::aplicarKmeans()
{
    this->K.aplicarAlgoritmo();
    this->K.mostrarCentrosObtidos();
    this->K.mostrarVariancias();
}

void RBF::aplicarGaussiana()
{
    int indiceCentro = 0;
    for (auto &centro : K.centros)
    {
        int indicePonto = 0;
        for (auto &dadoEntrada : this->dadosEntrada)
        {
            vector<double> diferenca(dadoEntrada.size());

            transform(dadoEntrada.begin(), dadoEntrada.end(), centro.begin(), diferenca.begin(), []
                     (double Xi, double Wi) { return Xi - Wi; });

            double normaEucliQuad = inner_product(diferenca.begin(), diferenca.end(), diferenca.begin(), 0.0);
            double variancia      = K.variancias[indiceCentro];

            this->saidasCamadasOcultas[indiceCentro].push_back( exp(-(1 / 2*variancia) * normaEucliQuad) );

            indicePonto++;
        }
        indiceCentro++;
    }
}

void RBF::inicializarPesosCamadaSaida(string modo)
{
    if      (modo == "random") for (int i = 0; i < this->numNeuroniosOcultos + 1; i++ ) this->pesosSaida.push_back(gerarNumAleatorio());
	else if (modo == "zero")   for (int i = 0; i < this->numNeuroniosOcultos + 1; i++ ) this->pesosSaida.push_back(0);
}

void RBF::obterSaida()
{
    int indiceNeuronioOculto = 0;
    for (auto &saidasNeuronioOculto : this->saidasCamadasOcultas)
    {
        int indiceSaidaNeuronioOculto = 0;
        for (auto &saidaNeuronioOculto : saidasNeuronioOculto)
        {
            this->saidas[indiceSaidaNeuronioOculto] += saidaNeuronioOculto * this->pesosSaida[indiceNeuronioOculto];

            indiceSaidaNeuronioOculto++;
        }    
        indiceNeuronioOculto++;
    }
}

void RBF::calcularErro(int indiceDadoEntrada)
{
    this->erroAtual = this->saidasDesejadas[indiceDadoEntrada][0] - this->saidas[indiceDadoEntrada];
    this->somaErro += this->erroAtual; 
}

void RBF::calcularGradienteSaida(int indiceDadoEntrada)
{
    this->gradienteSaida = this->erroAtual * this->saidas[indiceDadoEntrada];
}

void RBF::atualizarPesos(int indiceDadoEntrada)
{
    for (int i = 0; i < this->numSaidas; i++)
    {
        calcularErro(indiceDadoEntrada);
        calcularGradienteSaida(indiceDadoEntrada);

        bool pesoBias = true;

        int indicePeso = 0;
        for (double &peso : this->pesosSaida)
        {
            if (pesoBias)
            {
                peso = peso + 
                    this->taxaAprendizado * 
                    this->gradienteSaida;

                pesoBias = false;
            }
            else
            {
                peso = peso + 
                        this->taxaAprendizado * 
                        this->gradienteSaida * 
                        this->saidasCamadasOcultas[indicePeso][indiceDadoEntrada]; 

                indicePeso++;
            }
        }
    } 
}



