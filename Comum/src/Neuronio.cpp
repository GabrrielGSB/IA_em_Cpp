#include "../include/Neuronio.h"
#include "../include/myFuncoes.h"

Neuronio::Neuronio(double taxaAprendizado, int tamEntrada, string funcAtiv) : 
				   taxaAprendizado(taxaAprendizado),
				   tamEntrada(tamEntrada),
				   funcAtiv(funcAtiv)
{
	inicializarPesos("random");
}

Neuronio::Neuronio(int tamEntrada, string funcAtiv) : 
				   tamEntrada(tamEntrada),
				   funcAtiv(funcAtiv)
{
	inicializarPesos("random");
}

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

void  Neuronio::definirTaxaAprendizado(double taxaAprendizado)
{
	this->taxaAprendizado = taxaAprendizado;
}

double Neuronio::degrau(double entrada) 
{ 
	return entrada > 0 ? 1.0 : 0.0; 
}

double Neuronio::sigmoide(double entrada)
{
	return (1 / (1 + exp(-entrada)));
}
double Neuronio::sigmoide(double entrada, bool derivada)
{
	if (derivada == true) return (sigmoide(entrada) * (1 - sigmoide(entrada)));
	else                  return sigmoide(entrada);
}
double Neuronio::gaussiana(double normaEucliQuad, double variancia)
{
	return exp(-(1 / 2*variancia) * normaEucliQuad); 
}

void Neuronio::definirSinalBias(vector<double> &entrada)
{
	entrada.insert(entrada.begin(), 1.0);
}

void  Neuronio::aplicarFuncAtivacao(double entrada)
{
	if (this->funcAtiv == "degrau")   this->saida = degrau(entrada);
	if (this->funcAtiv == "sigmoide") this->saida = sigmoide(entrada);
	if (this->funcAtiv == "Linear")   this->saida = entrada;
}
void  Neuronio::aplicarFuncAtivacao(double normaEucliQuad, double variancia)
{
    this->saida = gaussiana(normaEucliQuad, variancia); 
}

void  Neuronio::aplicarEntrada(vector<double> entrada)
{
	definirSinalBias(entrada);

	this->somaEntradasPonderadas = 0;

	int pesoCount = 0;
	for (double &dadoEntrada : entrada) 
	{
		this->somaEntradasPonderadas += dadoEntrada * this->pesos[pesoCount];
		pesoCount++;
	}

	aplicarFuncAtivacao(this->somaEntradasPonderadas);
}
void  Neuronio::aplicarEntrada(vector<double> entrada, vector<double> centro, double variancia)
{
	vector<double> diferenca(entrada.size());

	transform(entrada.begin(), entrada.end(), centro.begin(), diferenca.begin(), []
			 (double Xi, double Wi) { return Xi - Wi; });

	double normaEucliQuad = inner_product(diferenca.begin(), diferenca.end(), diferenca.begin(), 0.0);

	aplicarFuncAtivacao(normaEucliQuad, variancia);
}



