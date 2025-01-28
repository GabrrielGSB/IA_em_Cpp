#include "../include/RBF.h"

RBF::RBF(int numEntradas, int numNeuroniosOcultos, vector<vector<double>> &dadosEntrada) :
         K(numEntradas, numNeuroniosOcultos, dadosEntrada), 
         numNeuroniosOcultos(numNeuroniosOcultos), dadosEntrada(dadosEntrada)
{
    this->saidasCamadasOcultas.resize(numNeuroniosOcultos);
    this->saidas.resize(dadosEntrada.size());
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

void RBF::atualizarPesos()
{

}