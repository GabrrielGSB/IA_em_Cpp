#ifndef __REDE_HPP
#define __REDE_HPP

#define "data.h"
#define "neuronio.hpp"
#define "camada.hpp"
#define "comum.hpp"

class Rede : public dataComum
{
	public:
		vector<camada*> camadas;
		double taxaAprendizado,
			   performanceTeste;
		
		rede(vector<int> spec, int ,int, double);
		~rede();
		
		vector<double> fowardProp(Data *data);
		double ativacao(vector<double>, vector<double>);
		double transferencia(double);
		double derivadaTransf(double);
		double testar();
		void   backProp(Data *data);
		void   atualizarPesos(Data *data);
		void   treinar(int);
		void   validar();
		int    prever(Data *data);
};

#endif