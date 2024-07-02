#ifndef __DATA_H
#define __DATA_H
using namespace std;

#include <vector>
#include "stdint.h"
#include "stdio.h"

class data
{
  vector<uint8_t> * vetor_de_recurso
  uint8_t label;
  int enum_label;
  
  public:
	data();
	~data();
  void definir_vetor_de_recurso(vector<uint8_t> *);
  void incluir_no_vetor_de_recurso(uint8_t);
  void definir_label(uint8_t); 
  void definir_vetor_enumerado(int);

  int     obter_tamanho_do_vetor_de_recurso();
  uint8_t obter_label(); 
  uint8_t obter_label_enumerada();

  vector<uint8_t> * obter_vetor_de_recurso();
};

#endif 
