#include "camada.hpp"

camada::camada(int tamanhoCamadaAnterior, int tamanhoCamadaAtual)
{
	for(int i = 0; i < tamanhoCamadaAtual; i++)
	{
		neuronios.push_back(new neuronio(tamanhoCamadaAnterior, tamanhoCamadaAtual));
	}
	this->tamanhoCamadaAtual = tamanhoCamadaAtual;
}