#include "../include/Neuronio.h"
#include <random>

Neuronio::Neuronio(int tamEntrada, string funcAtiv) : 
				   tamEntrada(tamEntrada), funcAtiv(funcAtiv){}

float gerarNumAleatorio(float min, float max)
{
	float aleatorio = (float)rand() / RAND_MAX;
    return min + aleatorio * (max - min);
}
		
void  Neuronio::inicializarPesos()
{
	default_random_engine gerador;
    normal_distribution<float> distribuicao(0.0, 1.0);
    
    for(int i = 0; i < tamEntrada + 1; i++ )
    {
    	pesos.push_back(gerarNumAleatorio(0, 1.0));
    }
}	

void  Neuronio::definirTaxaAprendizado(float TaxaAprendizado)
{
	taxaAprendizado = taxaAprendizado;
}

float Neuronio::degrau(float u, string derivada="false") 
{ 
	return u > 0 ? 1 : 0; 
}

void  Neuronio::aplicarFuncAtivacao(float y, string funcAtiv)
{
	if (funcAtiv == "degrau") saida = degrau(y);
}

void  Neuronio::aplicarEntrada(vector<float> entrada, string funcAtiv)
{
	entrada.insert(entrada.begin(), -1);

	for (int i = 0; i < entrada.size(); i++)
	{ 
		U.push_back(entrada[i+1] * pesos[i+1]);
	}

	saida = accumulate(U.begin(), U.end(), 0.0) - pesos[0];

	aplicarFuncAtivacao(saida, funcAtiv);
}


// int main()
// {
// 	Neuronio n(2, 1, "h");
// 	n.inicializarPesos();
// 	n.aplicarEntrada({2.0,2.0}, "degrau");
// 	for (float c : n.entrada) printf("%.3f\n", c);
// 	printf("\n");
// 	for (float a : n.pesos) printf("%.3f\n", a);
// 	printf("\n");
// 	for (float b : n.U) printf("%.3f\n", b);
// 	printf("\n");
// 	printf("%.4f", n.saida);
// 	 return 0;			
// }					


					
//vector<float> obterPesos();
	
//void mudarAtivacao();