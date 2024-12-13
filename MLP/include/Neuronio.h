#ifndef __NEURONIO_HPP
#define __NEURONIO_HPP

using namespace std;
#include <vector>
#include <string>
#include <random>
#include <numeric>
#include <algorithm>

class Neuronio
{
	private:
		//Funções
		float degrau(float entrada);
		void definirTaxaAprendizado(float TaxaAprendizado);
		void aplicarFuncAtivacao(float saida);
	
	public:
		//Construtor
		Neuronio(float taxaAprendizado, int tamEntrada, string funcAtiv);

		//Atributos
		int tamEntrada;
		float saida, gradienteLocal, taxaAprendizado;
		string funcAtiv;
		vector<float> pesos, entradasPonderadas;

		//Funções
		void definirSinalBias(vector<float> &entrada);
		void aplicarEntrada(vector<float> entrada);
		void inicializarPesos(string mode);	
};

#endif