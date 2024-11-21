#ifndef __NEURONIO_HPP
#define __NEURONIO_HPP

using namespace std;
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>

class Neuronio
{
	public:
		vector<float> pesos, U;
		float saida, gradienteLocal, taxaAprendizado;
		int tamEntrada;
		string funcAtiv;

		Neuronio(int tamEntrada, string funcAtiv);
		
		void inicializarPesos(string mode);	
		void definirTaxaAprendizado(float TaxaAprendizado);
		void aplicarFuncAtivacao(float saida, string funcAtiv);
		void aplicarEntrada(vector<float> input, string funcAtiv);
		//void mudarAtivacao();
		// vector<float> obterPesos();

		// FUNÇÕES DE ATIVAÇÃO-------------------------
		float degrau(float u, string derivada);
		// void sigmoid();
};

#endif
