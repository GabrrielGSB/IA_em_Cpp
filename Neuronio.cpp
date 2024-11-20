#include "neuronio.hpp"
#include <random>

Neuronio::Neuronio(int tamEntrada, int tamSaida, vector<float> entrada, string funcAtiv) : tamEntrada(tamEntrada), tamSaida(tamSaida), entrada(entrada), funcAtiv(funcAtiv){}

float gerarNumAleatorio(float min, float max)
{
	float aleatorio = (float)rand() / RAND_MAX;
    return min + aleatorio * (max - min);
}

		
void Neuronio::inicializarPesos()
{
	default_random_engine gerador;
    normal_distribution<float> distribuicao(0.0, 1.0);
    
    for(int i = 0; i < tamEntrada; i++ )
    {
    	pesos.push_back(gerarNumAleatorio(-1.0, 1.0));
    }
}	

int main()
{
	 Neuronio n(10,5,{1,2}, "h");
	 n.inicializarPesos();
	 for (float peso : n.pesos) printf("%.3f\n", peso);
	 return 0;			
}					


					
//vector<float> obterPesos();
	
//void aplicarEntrada();
//void mudarAtivacao();