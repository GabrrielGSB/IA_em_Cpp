#include "../include/Neuronio.h"
#include <random>

Neuronio::Neuronio(int tamEntrada, string funcAtiv) : 
				   tamEntrada(tamEntrada), funcAtiv(funcAtiv){}

float gerarNumAleatorio(float min, float max)
{
	float aleatorio = (float)rand() / RAND_MAX;
    return min + aleatorio * (max - min);
}
		
void  Neuronio::inicializarPesos(string mode)
{
	if (mode == "random")
	{
		default_random_engine gerador;
    	normal_distribution<float> distribuicao(0.0, 1.0);
    
    	for(int i = 0; i < tamEntrada + 1; i++ )
    	{
    		pesos.push_back(gerarNumAleatorio(0.0, 1.0));
    	}
		// for (float j : pesos) printf("%.2f", j);
	}
	else if (mode == "zero")
	{
		for(int i = 0; i < tamEntrada + 1; i++ )
    	{
    		pesos.push_back(0);
    	}
	}
	
}	

void  Neuronio::definirTaxaAprendizado(float taxaAprend)
{
	taxaAprendizado = taxaAprend;
}

float Neuronio::degrau(float u, string derivada="false") 
{ 
	return u > 0 ? 1.0 : 0.0; 
}

void  Neuronio::aplicarFuncAtivacao(float y, string funcAtiv)
{
	if (funcAtiv == "degrau") saida = degrau(y);
}

void  Neuronio::aplicarEntrada(vector<float> entrada, string funcAtiv)
{
	U = {};
	entrada.insert(entrada.begin(), -1.0);

	for (int i = 0; i < entrada.size(); i++)
	{ 
		U.push_back(entrada[i] * pesos[i]);
	}

	saida = accumulate(U.begin(), U.end(), 0.0);
	aplicarFuncAtivacao(saida, funcAtiv);
}

