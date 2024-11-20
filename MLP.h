#ifndef __MLP_HPP
#define __MLP_HPP

#include "neuronio.hpp"
using namespace std;

class MLP
{
	public:
		int numEntradas, numSaidas;
		vector<int> camadasOcultas; 
		vector<vector<#ifndef __MLP_HPP
#define __MLP_HPP

#include "neuronio.hpp"
using namespace std;

class MLP
{
	public:
		int numEntradas, numSaidas;
		vector<int> camadasOcultas; 
		vector<vector<float>> entradas;
		vector<float> saidas, saidasDesejadas;
		vector<vector<Neuronio>> rede;
		float erroQuad, erroQuadMed;
		int episodios;
		
		MLP(int numEnt, int numSai, vector<int> camOcu);
		
		void feedFoward();
		void backPropagation();
		void calcularErroQuad();
		void calcularErroQuadMed();
		void definirEntrada(vector<float>);
		void definirSaidasDesejadas(vector<float>);
		void definirCamOcultas(vector<int>);
		void atualizarPesos();
	    void definirEpisodios();
	    //void salvarPesos(); 
	    //void obterInformacoesRede();
	    void treinar();
	    
			
			
};

#endiffloat>> entradas;
		vector<float> saidas, saidasDesejadas;
		vector<vector<Neuronio>> rede;
		float erroQuad, erroQuadMed;
		int episodios;
		
		MLP(int numEnt, int numSai, vector<int> camOcu);
		
		void feedFoward();
		void backPropagation();
		void calcularErroQuad();
		void calcularErroQuadMed();
		void definirEntrada(vector<float>);
		void definirSaidasDesejadas(vector<float>);
		void definirCamOcultas(vector<int>);
		void atualizarPesos();
	    void definirEpisodios();
	    //void salvarPesos(); 
	    //void obterInformacoesRede();
	    void treinar();
	    
			
			
};

#endif