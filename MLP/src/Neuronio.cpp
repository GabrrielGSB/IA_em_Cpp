#include "../include/Neuronio.h"
#include <random>
#include "../include/myFuncoes.h"

Neuronio::Neuronio(float taxaAprendizado, int tamEntrada, string funcAtiv) : 
				   taxaAprendizado(taxaAprendizado),
				   tamEntrada(tamEntrada), 
				   funcAtiv(funcAtiv){}

void  Neuronio::inicializarPesos(string modo)
{
	if (modo == "random")
	{
    	for(int i = 0; i < tamEntrada + 1; i++ ) this->pesos.push_back(gerarNumAleatorio());
	}
	else if (modo == "zero")
	{
		for(int i = 0; i < tamEntrada + 1; i++ ) this->pesos.push_back(0);
	}
}

void  Neuronio::definirTaxaAprendizado(float taxaAprendizado)
{
	this->taxaAprendizado = taxaAprendizado;
}

float Neuronio::degrau(float entrada) 
{ 
	return entrada > 0 ? 1.0 : 0.0; 
}

void  Neuronio::aplicarFuncAtivacao(float entrada)
{
	if (this->funcAtiv == "degrau") this->saida = degrau(entrada);
}

void  Neuronio::aplicarEntrada(vector<float> entrada)
{
	definirSinalBias(entrada);

	entradasPonderadas = {};
	for (int i = 0; i < entrada.size(); i++) entradasPonderadas.push_back(entrada[i] * this->pesos[i]);

	this->saida = accumulate(entradasPonderadas.begin(),
                             entradasPonderadas.end(), 0.0);
	aplicarFuncAtivacao(this->saida);
}

void Neuronio::definirSinalBias(vector<float> &entrada)
{
	entrada.insert(entrada.begin(), -1.0);
}