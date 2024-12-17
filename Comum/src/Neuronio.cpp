#include "../include/Neuronio.h"
#include "myFuncoes.h"

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

float Neuronio::sigmoide(float entrada)
{
	return (1 / (1 + exp(-entrada)));
}
float Neuronio::sigmoide(float entrada, bool derivada)
{
	if (derivada == true) return (sigmoide(entrada) * (1 - sigmoide(entrada)));
	else                  return sigmoide(entrada);
}

void  Neuronio::aplicarFuncAtivacao(float entrada)
{
	if (this->funcAtiv == "degrau")   this->saida = degrau(entrada);
	if (this->funcAtiv == "sigmoide") this->saida = sigmoide(entrada);
}

void  Neuronio::aplicarEntrada(vector<float> entrada)
{
	definirSinalBias(entrada);
	this->saida = 0;

	for (size_t i = 0; i < entrada.size(); i++) this->saida += entrada[i] * this->pesos[i];

	this->somaEntradasPonderadas = this->saida;

	aplicarFuncAtivacao(this->saida);
}

void Neuronio::definirSinalBias(vector<float> &entrada)
{
	entrada.insert(entrada.begin(), 1.0);
}

void Neuronio::calcularGradienteLocal(float saidaDesejada)
{
	this->gradienteLocal = (saidaDesejada - this->saida) * sigmoide(this->somaEntradasPonderadas, true);
}