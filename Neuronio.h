#ifndef __NEURONIO_HPP
#define __NEURONIO_HPP

using namespace std;
#include <vector>
#include <string>

class Neuronio
{
	public:
		vector<float> entrada;
		vector<float> pesos;
		float saida, gradienteLocal;
		int tamEntrada, tamSaida;
		string funcAtiv;
		
		Neuronio(int tamEntrada, int tamSaida, vector<float> entrada, string funcAtiv);
		
		vector<float> obterPesos();
		void inicializarPesos();	
		void aplicarEntrada();
		//void mudarAtivacao();
};

#endif