#include "rede.hpp"
#include "camada.hpp"
#include "dataHandler.hpp"
#include <numeric>

Rede::Rede(vector<int> spec, int tamanhoEntrada,int numClasses, double taxaAprendizado)
{
	for(int i = 0; i < spec.size(); i++)
	{
		if(i==0) camadas.push_back(new camada(tamanhoEntrada, spec.at(i)));
		else camadas.push_back(new camada(camadas.at(i-1)->neuronios.size(),spec.at(i)));
	}
	
	camadas.push_back(new camada(camadas.at(camadas.size()-1)->neuronios.size(), numClasses));
	
	this->taxaAprendizado = taxaAprendizado;
}

double Rede::ativar(vector<double> pesos, vector<double> entrada)
{
	double ativacao = pesos.back();
	for(int i = 0; i < pesos.size() - 1; i++) 
	{
		ativacao += pesos[i] * entrada[i];
	}
	return ativacao;
}

double Rede::transferencia(double ativacao)
{
	return 1.0 / (1.0 + exp(-ativacao)));
}

double Rede::derivadaTransf()
{
	return saida * (1 - saida);
}

vector<double> Rede::fowardProp(Data *data)
{
	vector<double> entradas = *data->vetorRecursoNormalizado();
	
	for(int i = 0; i < camadas.size(); i++)
	{
		Camada *camada = camadas.at(i);
		vector<double> novaEntrada;
		
		for(Neuronio *n : camada->neuronios)
		{
			double ativacao = this->ativar(n->pesos, estradas);
			n->saida = this->transferencia(ativacao);
			novasEntradas.push_back(n->saida);
		}
		entradas = novasEntradas;
	}
	return entradas 
}

void Rede::backProp(Data *data)
{
	for(int i = camadas.size() - 1; i >= 0; i--)
	{
		Camada *camada = camadas.at(i);
		vector<double> erros;
		
		if(i != camadas.size() - 1)
		{
			for(int j = 0; j < camada->neuronios.size(); j++)
			{
				double erro = 0.0;
				for(Neuronio *n : camadas.at(i + 1)->neuronios)
				{
					erro += (n->pesos.at(j) * n->delta);
				}
				erros.push_back(erro);
			}
		}
		else
		{
			for(int j = 0; j < camada->neuronios.size(); j++)
			{
				Neuronio *n = camada->neuronios.at(j);
				erros.push_back((double)data->obterVetorClasse().at(j) - n->saida);
			}
		}
		for(int j = 0; j < camada->neuronios.size(); j++)
		{
			Neuronio *n = camada->neuronios.at(j);
			n->delta = erros.at(j) * this->derivadaTransf(n->saida);
		}
	}
}

void Rede::atualizarPesos(Data *data)
{
	vector<double> entradas = *data->vetorRecursoNormalizado();
	for(int i = 0; i < camadas.size(); i++)
	{
		if(i != 0)
		{
			for(Neuronio *n : camadas.at(i - 1)->neuronios)
			{
				entradas.push_back(n->saida);
			}	
		}
		for(Neuronio *n : camadas.at(i)->neuronios)
		{
			for(int j = 0; j < entradas.size(); j++)
			{
				n->pesos.at(j) += this->taxaAprendizado * n->delta * entradas.at(j);
			}
			n->pesos.back() += this->taxaAprendizado * n->delta;
		}
		entradas.clear();
	}
}

int Rede::prever(Data *data)
{
	vector<double> saidas = fowardProp(data);
	return distance(saidas.begin(), max_element(saidas.begin(), saidas.end()));
}

void Rede::treinar(int numEpocas)
{
	for(int i = 0; i < numEpocas; i++)
	{
		double sumErro = 0.0;
		for(Data *data : *this->dadosTreinamento)
		{
			vector<double> saidas   = fowardProp(data);
			vectort<int>   esperado = data->ObterVetorClasse();

			double tempErroSum = 0.0;
			for(int j = 0; j < saidas.size(); j++)
			{
				tempErroSum += pow((double)esperado.at(j) - saidas.at(j), 2);
			}
			sumErro += tempErroSum;
			backProp(data);
			atualizarPesos(data);
		}
		printf("Iteração: %d \t Erro = %.4f\n", i, sumErro);
	}
}

void Rede::testar()
{
	double numCorretos = 0.0;
	double count       = 0.0;

	for(Data *data : *this->dadosTeste)
	{
		count++;
		int index = prever(data);
		if(data->obterVetorClasse().at(index) == 1) numCorretos++;
	}
	testePerformance = (numCorretos / count);
	return testePerformance;	
}

void Rede::validar()
{
	double numCorretos = 0.0;
	double count       = 0.0;

	for(Data *data : *this->dadosValidacao)
	{
		count++;
		int index = prever(data);
		if(data->obterVetorClasse().at(index) == 1) numCorretos++;
	}
	printf("Performance da Validação: %4.f\n", (numCorretos/count));	
}