#ifndef __DATA_H // Essas diretivas são usadas para garantir que o arquivo de cabeçalho data.h... 
#define __DATA_H // não seja incluído mais de uma vez em um mesmo arquivo de código (prevenindo a inclusão múltipla)

// O #ifndef (if not defined) verifica se a macro __DATA_H está definida. 
// Caso não esteja, define a macro com #define __DATA_H.

// vec == vetor; rec == recurso; pont == ponteiro

using namespace std; // simplificação pra não precisar ficar escrevendo std:: em todo lugar 

#include <vector>   // vetor dinâmico
#include "stdint.h" // tipos de dados com tamanhos fixos
#include "stdio.h"  // Funções básicas de entrada e saída

class data
{
  vector<uint8_t> * vec_de_rec  // definição do ponteiro  "vec_de_rec" que contem dados no formato vector<uint8_t>.
  uint8_t label;  // representa a classe, char como 'A', 'B' etc.
  int enum_label; // representa o valor de cada classe A -> 1, B -> 2, etc.
  
  public:
	data(); // construtor e destruidor da classe, são chamaos automaticamente quando a classe...
	~data();// é construida ou destruida, servem para criar a classe como vc quer e limpar a memória quando a classe não for mais usada.

  void def_pont_para_vec_de_rec(vector<uint8_t> *); // Atribui o ponteiro vetor_de_recurso para apontar para um vetor passado como argumento.
  void incluir_no_vec_de_rec(uint8_t);                  // colocar um elemento no vetor de recursos
  void definir_label(uint8_t);                          // define o valor da label
  void definir_enum_label(int);                         // define o valor da label enumerada

  // Metodos para obter os valores dos arrays
  int     obter_tamanho_do_vec_de_rec();      
  uint8_t obter_label(); 
  uint8_t obter_label_enumerada();

  vector<uint8_t> * obter_vec_de_rec(); // Esse método retorna o ponteiro para o vetor de recursos, ...
                                        // permitindo acessar ou manipular o vetor fora da classe.
};

#endif 
