#ifndef __MLP_HPP
#define __MLP_HPP

using namespace std;

#include "../../Comum/include/Neuronio.h"
#include "../../Comum/include/myFuncoes.h"
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <cmath>

class MLP
{
	public:
		MLP(vector<int> estruturaRede, float taxaAprendizado, 
			int numEpisodiosTotais, string funcAtiv);

		vector<vector<Neuronio>> rede;
		vector<vector<float>> saidasCamadas;
		float erroQuad, erroQuadMed,
			  taxaAprendizado;
		int numEpisodiosTotais, 
			numEntradas, numSaidas;
		
		void inicializarPesosRede();
		void mostrarSaidas();
		void mostrarPesos();
		void feedFoward(vector<float> dadosEntrada);
		void backPropagation(vector<float> saidasDesejadas);
		void atualizarPesos();
	    void treinar();
		// void calcularErroQuad();
		// float calcularErroQuadMed();
	    //void salvarPesos(); 
	    //void obterInformacoesRede();
	    
			
			
};

#endif