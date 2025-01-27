#ifndef __CAMADA_HPP
#define __CAMADA_HPP

#include "neuronio.hpp"
#include <stdint.h>
#include <vector>

using namespace std;

static int id_camada = 0;

class camada
{
	public:
		int tamanhoCamadaAtual;
		vector<neuronio*> neuronios;
		vector<double> saidaCamada;
		
		camada(int,int);
		
};

#endif