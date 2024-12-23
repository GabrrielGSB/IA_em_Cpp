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
		void definirTaxaAprendizado(double TaxaAprendizado);
		void aplicarFuncAtivacao(double saida);
		double degrau(double entrada);
	
	public:
		//Construtor
		Neuronio(double taxaAprendizado, int tamEntrada, string funcAtiv);

		//Atributos
		double saida, gradienteLocal, 
			  taxaAprendizado, somaEntradasPonderadas;
		int tamEntrada, numLigacoesSaida;
		string funcAtiv;
		vector<double> pesos;

		//Funções
		void definirSinalBias(vector<double> &entrada);
		void aplicarEntrada(vector<double> entrada);
		void inicializarPesos(string mode);	
		double sigmoide(double entrada);
		double sigmoide(double entrada, bool derivada);
};

#endif