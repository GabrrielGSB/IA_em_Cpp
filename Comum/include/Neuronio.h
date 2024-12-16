#ifndef __NEURONIO_HPP
#define __NEURONIO_HPP

using namespace std;
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>

class Neuronio
{
	private:
		//Funções
		void definirTaxaAprendizado(float TaxaAprendizado);
		void aplicarFuncAtivacao(float saida);
		float degrau(float entrada);
	
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