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
			  taxaAprendizado, somaGradienteCamada;
		int numEpisodiosTotais, 
			numEntradas, numSaidas;
		
		void inicializarPesosRede(string modo);
		void mostrarSaidas();
		void mostrarPesos();
		void feedFoward(vector<float> dadosEntrada);
		void backPropagation(vector<float> dadoEntrada, vector<float> saidaDesejada);
		void calcularGradienteOculto(int &numCalculoGradienteAtual);
		void calcularGradienteCamadaFinal(float saidaDesejada);
	    void treinar();
		// void calcularErroQuad();
		// float calcularErroQuadMed();
	    //void salvarPesos(); 
	    //void obterInformacoesRede();
	    
			
			
};

#endif