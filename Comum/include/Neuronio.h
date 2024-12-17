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
		float sigmoide(float entrada);
		float sigmoide(float entrada, bool derivada);
	
	public:
		//Construtor
		Neuronio(float taxaAprendizado, int tamEntrada, string funcAtiv);

		//Atributos
		float saida, gradienteLocal, 
			  taxaAprendizado, somaEntradasPonderadas;
		int tamEntrada;
		string funcAtiv;
		vector<float> pesos;

		//Funções
		void definirSinalBias(vector<float> &entrada);
		void aplicarEntrada(vector<float> entrada);
		void inicializarPesos(string mode);	
		void calcularGradienteLocal(float saidaDesejada);
};

#endif