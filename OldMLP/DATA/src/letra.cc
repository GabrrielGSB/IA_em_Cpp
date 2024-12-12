#include "letra.hpp"
using namespace std;

// vec == vetor; rec == recurso; pont == ponteiro

data::data() { vec_de_pixels = new vector<uint8_t>; }

data::~data(){}

// O operador "->" é usado para acessar membros (como métodos, "push_back", ou atributos) de um objeto, "vector", ...
// quando você tem um ponteiro para esse objeto.
// O método "push_back()" é uma função membro da classe "std::vector" que adiciona um novo elemento ao final do vetor.

void data::definir_enum_label          (int val)               { enum_label    = val; }
void data::def_pont_para_vec_de_pixels (vector<uint8_t> *vect) { vec_de_pixels = vect; }
void data::definir_label               (uint8_t val)           { label         = val; }
void data::incluir_no_vec_de_pixels    (uint8_t val)           { vec_de_pixels -> push_back(val); }

int data::obter_tamanho_do_vec_de_pixels()                    { return vec_de_pixels -> size(); }

uint8_t data::obter_label()                                { return label; }
uint8_t data::obter_label_enumerada()                      { return enum_label; }

vector<uint8_t> * data::obter_vec_de_pixels()                 { return vec_de_pixels; }