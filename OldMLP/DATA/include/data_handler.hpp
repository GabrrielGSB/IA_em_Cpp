#ifndef __DATA_HANDLER_H
#define __DATA_HANDLER_H
using namespace std;

// vec == vetor; rec == recurso
// perc== porcentagem; p == para

#include<fstream>
#include "stdint.h"
#include "letra.hpp"
#include <vector>
#include <string>
#include <map>
#include <unordered_set>

class data_handler
{
  vector<data*> *vetor_de_dados;      // Criação de ponteiros para um vetor de ponteiros.
  vector<data*> *dados_de_treinamento;
  vector<data*> *dados_de_teste;
  vector<data*> *dados_de_validacao;
  
  int num_classes;                    // Numero de classes presentes nos dados.
  int tamanho_do_vec_de_rec;
  int mapa_classes;

  map<uint8_t, int> mapa_da_classe;   // cria um mapeamento de valores "uint8_t" para "int", como uma classe python.

  const double PERC_DE_TREINAMENTO = 0.75; // poncentagem de treinamento, teste e validação na rede neural
  const double PERC_DO_TESTE       = 0.20;
  const double PERC_DE_VALIDACAO   = 0.05;

  public:
  data_handler();
  ~data_handler();

  void guardarLetra   (string path); 
  void lerLabels      (string path);
  void dividirDados   ();            // Função para dividir os dados de acordo com as const definidas acima.
  void contarClasses  ();

	uint32_t conv_p_little_endian(const unsigned char* bytes); // converte um dado para o formato little endian, onde...
                                                             // o byte menos significativo vem primeiro na memória.
  map<uint8_t, int> getClassMap();

	vector<data*> * obter_dados_de_treinamento();	 // retorna os dados de treinamento, teste, e validação no formato de...
	vector<data*> * obter_dados_de_teste      ();  // ponteiro de vetor de ponteiros
	vector<data*> * obter_dados_de_validacao  ();
};

#endif