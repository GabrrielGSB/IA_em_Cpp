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
		MLP(vector<int> estruturaRede, double taxaAprendizado, 
			int numEpisodiosTotais, double erroMinimo, string funcAtiv);

		vector<vector<vector<double>>> pesosCamadas;
		vector<vector<vector<double>>> pesosCamadasOld;
		vector<vector<Neuronio>> rede;
		vector<vector<double>> saidasCamadas;
		vector<double> erros;

		double taxaAprendizado, momentum, somaGradienteCamada, erroAtual,
			   somaErro, mediaErro, erroMinimo, variacaoErro, 
			   erroQuadratico, erroQuadraticoMedio, erroRelativoMedio,
			   variancia;
		int numEpisodiosTotais, 
			numEntradas, numSaidas,
			numDados, erroCount;
		
		void inicializarPesosRede(string modo);
		void mostrarSaida(vector<double> entradaAtual);
		void mostrarPesos();
		void calcularErro(Neuronio &n, double &saidaDesejada);
		void calcularErro(double &saida, double &saidaDesejada);
		void calcularMediaErro();
		void calcularErroQuadratico();
		void calcularErroQuadraticoMedio(double erroQuadratico, size_t numDados);
		void calcularErroRelativoMedio(vector<double> &saidaDesejada);
		void calcularVarianciaErro();
		void calcularGradienteNeuronioOculto(int &numCalculoGradienteAtual);
		void calcularGradienteNeuronioFinal(Neuronio &n);
		void feedFoward(vector<double> dadosEntrada);

		void backPropagation(vector<double> dadoEntrada, 
							 vector<double> saidaDesejada, 
							 string mode);

	    void treinar(vector<vector<double>> &dadosEntrada, 
					 vector<vector<double>> &saidasDesejadas,
					 string mode,
					 string backPropagationMode = "",
					 double momentum = 0.0);

		void testarRede(vector<vector<double>> &dadosEntrada, 
				        vector<vector<double>> &saidasDesejadas);	
		void salvarPesos();
		void zerarPesos();
		void salvarErroQuaMedCSV(string &nomeArquivo, vector<double> dadosErroQuadMed);
		void salvarErro();
		void salvarErro(int erroCount);
		void salvarErroCSV(int episodioCount);
};

#endif