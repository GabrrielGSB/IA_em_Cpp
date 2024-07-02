#ifndef __DATA_HANDLER_H
#define __DATA_HANDLER_H
using namespace std;

#include<fstream>
#include "stdint.h"
#include "data.hpp"
#include <vector>
#include <string>
#include <map>
#include <unordered_set>

class data_handler
{
  vector<data *> *vetor_de_dados;
  vector<data *> *dados_de_treinamento;
  vector<data *> *dados_de_teste;
  vector<data *> *dados_de_validacao;
  
  int num_classes;
  int tamanho_do_vetor_de_recursos;
  map<uint8_t, int> classe_map;

  const double PORCENTAGEM_DE_TREINAMENTO = 0.75;
  const double PORCENTAGEM_DE_TESTE       = 0.20;
  const double PORCENTAGEM_DE_VALIDACAO   = 0.05;

  public:
  data_handler();
  ~data_handler();

  void ler_vetor_de_recursos(string path); 
  void ler_labels_de_recursos(string path);
  void dividir_dados();
  void contar_classes();

	uint32_t converta_para_pequeno_endian(const unsigned char* bytes);
  
	vector<data *> * obter_dados_de_treinamento();	
	vector<data *> * obter_dados_de_teste();
	vector<data *> * obter_dados_de_validacao();
};
