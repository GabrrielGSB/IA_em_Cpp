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
			int numEpisodiosTotais, float erroMinimo, string funcAtiv);

		vector<vector<Neuronio>> rede;
		vector<vector<float>> saidasCamadas;
		float taxaAprendizado, somaGradienteCamada,
			  erroMinimo;
		int numEpisodiosTotais, 
			numEntradas, numSaidas;
		
		void inicializarPesosRede(string modo);
		void mostrarSaida(vector<float> entradaAtual);
		void mostrarPesos();
		void feedFoward(vector<float> dadosEntrada);
		void backPropagation(vector<float> dadoEntrada, vector<float> saidaDesejada);
		void calcularGradienteOculto(int &numCalculoGradienteAtual);
		void calcularGradienteCamadaFinal(float saidaDesejada);
	    void treinar(vector<vector<float>> &dadosEntrada, 
					 vector<vector<float>> &saidasDesejadas,
					 string mode);
		void testarRede(vector<vector<float>> &dadosEntrada, vector<vector<float>> &saidasDesejadas);	
};

#endif