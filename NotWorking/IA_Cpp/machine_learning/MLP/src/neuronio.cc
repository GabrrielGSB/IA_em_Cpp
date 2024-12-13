     #include "neuronio.hpp"
     #include <random>
     using namespace std;
     
     double gerarNumAleatorio(double min, double max)
     {
     	double aleatorio = (double)rand() / RAND_MAX;
     	return min + aleatorio * (max - min);
     }
     
     neuronio::neuronio(int tamanhoCamadaAnterior, int tamanhoCamadaAtual)
     {
     	inicializarPesos(tamanhoCamadaAnterior);
     }
     
     void neuronio::inicializarPesos(int TamanhoCamadaAnterior)
     {
     	default_random_engine gerador;
     	normal_distribution<double> distribuicao(0.0, 1.0);
     	for(int i = 0; i < tamanhoCamadaAnterior + 1; i++ )
         {
         	pesos.push_back(gerarNumAleatorio(-1.0, 1.0));
         }
     }