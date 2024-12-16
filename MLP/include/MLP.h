#ifndef __MLP_HPP
#define __MLP_HPP

using namespace std;

#include "../../Comum/include/Neuronio.h"
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>

class MLP
{
	public:
		MLP(vector<int> estruturaRede, float taxaAprendizado, 
			int numEpisodiosTotais, string funcAtiv);

		vector<float> saidas; 
		vector<vector<Neuronio>> rede;
		float erroQuad, erroQuadMed;
		int numEpisodiosTotais, numEntradas, numSaidas;
		
		void inicializarRede();
		void feedFoward(vector<float> dadosEntrada);
		void backPropagation();
		void calcularErroQuad();
		void calcularErroQuadMed();
		void atualizarPesos();
	    void treinar();
	    //void salvarPesos(); 
	    //void obterInformacoesRede();
	    
			
			
};

#endif