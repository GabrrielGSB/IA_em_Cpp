#ifndef __MLP_HPP
#define __MLP_HPP

#include "Neuronio.h"
using namespace std;

class MLP
{
	public:
		vector<int> camadasOcultas; 
		vector<float> saidas, saidasDesejadas;
		vector<vector<float>> entradas;
		vector<vector<Neuronio>> rede;
		float erroQuad, erroQuadMed;
		int episodios, numEntradas, numSaidas;
		
		MLP(int numEnt, vector<int> camOcu, int numSai);
		
		void feedFoward();
		void backPropagation();
		void calcularErroQuad();
		void calcularErroQuadMed();
		void definirEntrada(vector<float>);
		void definirSaidasDesejadas(vector<float>);
		void definirCamOcultas(vector<int>);
		void atualizarPesos();
	    void definirEpisodios();
	    void treinar();
	    //void salvarPesos(); 
	    //void obterInformacoesRede();
	    
			
			
};

#endif